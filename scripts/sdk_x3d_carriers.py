"""Whole source sections with original math aliases, inline tables and tails."""
import hashlib
import struct
import capstone


def section_carrier(body, number, c, coff):
    count, defs=coff.parse_symbols(body,c.coff_name)
    if not 1<=number<=count:raise ValueError('invalid whole source section')
    h=struct.unpack_from('<8sIIIIIIHHI',body,20+(number-1)*40)
    if not h[3] or not h[4] or h[4]+h[3]>len(body):raise ValueError('incomplete initialized source section')
    raw=body[h[4]:h[4]+h[3]];syoff,n=struct.unpack_from('<II',body,8);strings=body[syoff+n*18:];indexed={};aux_records=[];i=0
    while i<n:
        nm,val,sec,typ,storage,aux=struct.unpack_from('<8sIhHBB',body,syoff+i*18);sn=c.coff_name(nm,strings)
        indexed[i]=(sn,val,sec,typ,storage)
        if sec==number:aux_records.append(dict(symbol=sn,index=i,aux_count=aux,aux_hex=body[syoff+(i+1)*18:syoff+(i+1+aux)*18].hex()))
        i+=1+aux
    fields=[]
    for i in range(h[7]):
        at,si,typ=struct.unpack_from('<IIH',body,h[5]+10*i)
        if si not in indexed or at+4>len(raw):raise ValueError('invalid whole source field')
        sn,val,sec,ty,storage=indexed[si]
        fields.append(dict(offset=at,type_id=typ,type=c.COFF_RELOCATION_NAMES.get(typ,f'0x{typ:04X}'),symbol=sn,addend=struct.unpack_from('<I',raw,at)[0],local_symbol_offset=val if sec==number else None,symbol_index=si,symbol_section=sec,symbol_offset=val,symbol_type=ty,symbol_storage=storage))
    return raw,fields,dict(section=number,flags=h[9],size=h[3],definitions=[d for d in defs if d['section']==number],aux_records=aux_records)


def flow(code,address,roots,fields,calls,data,switch=None):
    """Derive code ends independently; compare tables/padding as whole carrier bytes."""
    code_end=switch['offset'] if switch else len(code)
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);decoder.detail=True
    ins=list(decoder.disasm(bytes(code[:code_end]),address));by={i.address:i for i in ins}
    if not ins or sum(i.size for i in ins)!=code_end:raise ValueError('whole x3d code region does not decode')
    switch_targets={};table_fields=set()
    if switch:
        off=switch['offset'];at=address+switch['jump_offset'];jump=by.get(at)
        local=[f for f in fields if f['offset']>=off]
        targets=list(struct.unpack('<8I',bytes(code[off:]))) if len(code)-off==32 else []
        if (len(local)!=8 or [f['offset'] for f in local]!=list(range(off,off+32,4))
                or any(f['type']!='DIR32' or f['symbol_type'] or f['symbol_storage']!=6
                       or f['local_symbol_offset'] is None or targets[i]!=address+f['symbol_offset']
                       or targets[i] not in by for i,f in enumerate(local))):
            raise ValueError('x3d full eight-entry local switch definition differs')
        pos=next((j for j,i in enumerate(ins) if i.address==at),-1)
        if pos<2 or not jump or len(jump.operands)!=1 or jump.operands[0].type!=capstone.x86.X86_OP_MEM:
            raise ValueError('x3d switch has no actual indexed jump')
        mem=jump.operands[0].mem;cmp,guard=ins[pos-2:pos]
        if (mem.base or mem.scale!=4 or mem.disp!=address+off or mem.index!=capstone.x86.X86_REG_EAX
                or cmp.mnemonic!='cmp' or cmp.op_str!='eax, 7' or guard.mnemonic!='ja'
                or guard.operands[0].type!=capstone.x86.X86_OP_IMM or guard.operands[0].imm not in by):
            raise ValueError('x3d switch lacks its independently decoded unsigned 0..7 guard')
        switch_targets[at]=targets;table_fields={address+f['offset'] for f in local}
    todo=[address+r for r in roots];seen=set();tails=[];used_calls=set();used_data=set()
    while todo:
        at=todo.pop()
        if at in seen:continue
        if at not in by:raise ValueError('x3d entry/branch/fallthrough is not an instruction')
        seen.add(at);i=by[at]
        if i.group(capstone.CS_GRP_RET):continue
        if i.group(capstone.CS_GRP_JUMP):
            if at in switch_targets:todo.extend(switch_targets[at]);continue
            if len(i.operands)!=1 or i.operands[0].type!=capstone.x86.X86_OP_IMM:raise ValueError('unresolved x3d indirect tail')
            dest=i.operands[0].imm
            if dest in by:todo.append(dest)
            elif i.mnemonic=='jmp' and calls.get(at+i.imm_offset)==dest:
                tails.append(dict(site=at-address,destination=f'0x{dest:08X}'));used_calls.add(at+i.imm_offset)
            else:raise ValueError('unbound x3d external branch')
            if i.mnemonic=='jmp':continue
        todo.append(at+i.size)
    extent=max(by[at].address+by[at].size for at in seen)-address
    padding=[];internal_padding=[]
    for i in ins:
        if i.address in seen:continue
        valid=i.mnemonic=='nop'
        if i.mnemonic=='mov' and len(i.operands)==2:
            valid=all(o.type==capstone.x86.X86_OP_REG for o in i.operands) and i.operands[0].reg==i.operands[1].reg
        elif i.mnemonic=='lea' and len(i.operands)==2:
            valid=(i.operands[0].type==capstone.x86.X86_OP_REG and i.operands[1].type==capstone.x86.X86_OP_MEM
                   and i.operands[0].reg==i.operands[1].mem.base and not i.operands[1].mem.index and not i.operands[1].mem.disp)
        elif i.mnemonic=='add' and i.op_str=='eax, 0':
            # Actual unreachable five-byte math.obj alignment; this changes EFLAGS.
            valid=i.address>=address+extent and i.size==5 and not switch and len(code)-extent==5
        if not valid:raise ValueError('x3d unreachable tail is not original bounded alignment')
        (padding if i.address>=address+extent else internal_padding).append(dict(offset=i.address-address,mnemonic=i.mnemonic,operands=i.op_str))
    for i in ins:
        if i.address not in seen:continue
        for off,size in [(i.imm_offset,i.imm_size),(i.disp_offset,i.disp_size)]:
            site=i.address+off
            if site in data and size==4:
                if struct.unpack_from('<I',code,site-address)[0]!=data[site]:raise ValueError('x3d decoded data field differs')
                used_data.add(site)
        if i.group(capstone.CS_GRP_CALL) and i.operands[0].type==capstone.x86.X86_OP_IMM:
            site=i.address+i.imm_offset;dest=i.operands[0].imm
            if calls.get(site)==dest:used_calls.add(site)
            elif dest not in by:raise ValueError('x3d call lacks a complete original code owner')
    if used_calls!=set(calls) or used_data|table_fields!=set(data):raise ValueError('x3d code/table fields are hidden in padding or unconsumed')
    return dict(extent=extent,table_size=32 if switch else 0,alignment_size=code_end-extent,
                alignment_sha256=hashlib.sha256(code[extent:code_end]).hexdigest(),padding=padding,internal_padding=internal_padding,
                roots=roots,reachable_instruction_count=len(seen),external_tails=tails,
                indirect_call_count=sum(i.group(capstone.CS_GRP_CALL) and i.operands[0].type!=capstone.x86.X86_OP_IMM for i in ins if i.address in seen))


def math_partitions(code,address,source,fields,data):
    peers=[d for d in source['definitions'] if d['type']==32]
    starts=sorted({d['offset'] for d in peers})
    if not starts or starts[0] or any(d['storage']!=2 for d in peers):raise ValueError('math whole public source roots differ')
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);decoder.detail=True
    transfers=[]
    for i in decoder.disasm(bytes(code),address):
        if i.group(capstone.CS_GRP_CALL):
            if i.operands[0].type!=capstone.x86.X86_OP_IMM or i.operands[0].imm-address not in starts:
                raise ValueError('math encoded internal call is not an actual whole public source entry')
            transfers.append(dict(site=i.address+i.imm_offset-address,destination=i.operands[0].imm-address,kind='source-internal-direct-call-without-coff-relocation'))
    result=[]
    for start,end in zip(starts,starts[1:]+[len(code)]):
        f=[dict(f,offset=f['offset']-start) for f in fields if start<=f['offset']<end]
        d={at:dest for at,dest in data.items() if address+start<=at<address+end}
        calls={address+r['site']:address+r['destination'] for r in transfers if start<=r['site']<end}
        proof=flow(code[start:end],address+start,[0],f,calls,d)
        result.append(dict(offset=start,carrier_size=end-start,aliases=[d['symbol'] for d in peers if d['offset']==start],flow=proof))
    return dict(partitions=result,internal_calls=transfers)
