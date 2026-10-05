"""Whole original SDK dispatch CFG; table slots retain runtime selection."""
import hashlib
import struct
import capstone

def flow(code,address,roots,fields,calls,data,switch=None,slots=()):
    """Derive complete original dispatch code ends and retain whole switch/alignment bytes."""
    code_end=switch['offset'] if switch else len(code)
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);decoder.detail=True
    ins=list(decoder.disasm(bytes(code[:code_end]),address));by={i.address:i for i in ins}
    if not ins or sum(i.size for i in ins)!=code_end:raise ValueError('whole SDK dispatch code region does not decode')
    switch_targets={};table_fields=set()
    if switch:
        off=switch['offset'];at=address+switch['jump_offset'];jump=by.get(at)
        local=[f for f in fields if f['offset']>=off]
        targets=list(struct.unpack('<8I',bytes(code[off:]))) if len(code)-off==32 else []
        if (len(local)!=8 or [f['offset'] for f in local]!=list(range(off,off+32,4))
                or any(f['type']!='DIR32' or f['symbol_type'] or f['symbol_storage']!=6
                       or f['local_symbol_offset'] is None or targets[i]!=address+f['symbol_offset']
                       or targets[i] not in by for i,f in enumerate(local))):
            raise ValueError('SDK dispatch full eight-entry local switch definition differs')
        pos=next((j for j,i in enumerate(ins) if i.address==at),-1)
        if pos<2 or not jump or len(jump.operands)!=1 or jump.operands[0].type!=capstone.x86.X86_OP_MEM:
            raise ValueError('SDK dispatch switch has no actual indexed jump')
        mem=jump.operands[0].mem;cmp,guard=ins[pos-2:pos]
        if (mem.base or mem.scale!=4 or mem.disp!=address+off or mem.index!=capstone.x86.X86_REG_EAX
                or cmp.mnemonic!='cmp' or cmp.op_str!='eax, 7' or guard.mnemonic!='ja'
                or guard.operands[0].type!=capstone.x86.X86_OP_IMM or guard.operands[0].imm not in by):
            raise ValueError('SDK dispatch switch lacks its independently decoded unsigned 0..7 guard')
        switch_targets[at]=targets;table_fields={address+f['offset'] for f in local}
    todo=[address+r for r in roots];seen=set();tails=[];used_calls=set();used_data=set()
    while todo:
        at=todo.pop()
        if at in seen:continue
        if at not in by:raise ValueError('SDK dispatch entry/branch/fallthrough is not an instruction')
        seen.add(at);i=by[at]
        if i.group(capstone.CS_GRP_RET):continue
        if i.group(capstone.CS_GRP_JUMP):
            if at in switch_targets:todo.extend(switch_targets[at]);continue
            if len(i.operands)==1 and i.operands[0].type==capstone.x86.X86_OP_MEM:
                mem=i.operands[0].mem;site=at+i.disp_offset
                if (bytes(i.bytes[:2])!=b'\xff\x25' or mem.base or mem.index
                        or mem.disp not in slots or data.get(site)!=mem.disp):
                    raise ValueError('SDK dispatch tail lacks an original mutable table slot')
                tails.append(dict(site=at-address,slot=f'0x{mem.disp:08X}',runtime_selected=True))
                used_data.add(site);continue
            if len(i.operands)!=1 or i.operands[0].type!=capstone.x86.X86_OP_IMM:raise ValueError('unresolved SDK dispatch indirect tail')
            dest=i.operands[0].imm
            if dest in by:todo.append(dest)
            elif i.mnemonic=='jmp' and calls.get(at+i.imm_offset)==dest:
                tails.append(dict(site=at-address,destination=f'0x{dest:08X}'));used_calls.add(at+i.imm_offset)
            else:raise ValueError('unbound SDK dispatch external branch')
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
        if not valid:raise ValueError('SDK dispatch unreachable tail is not original bounded alignment')
        (padding if i.address>=address+extent else internal_padding).append(dict(offset=i.address-address,mnemonic=i.mnemonic,operands=i.op_str))
    for i in ins:
        if i.address not in seen:continue
        for off,size in [(i.imm_offset,i.imm_size),(i.disp_offset,i.disp_size)]:
            site=i.address+off
            if site in data and size==4:
                if struct.unpack_from('<I',code,site-address)[0]!=data[site]:raise ValueError('SDK dispatch decoded data field differs')
                used_data.add(site)
        if i.group(capstone.CS_GRP_CALL) and i.operands[0].type!=capstone.x86.X86_OP_IMM:
            operand=i.operands[0]
            if (operand.type!=capstone.x86.X86_OP_MEM or operand.mem.base or operand.mem.index
                    or operand.mem.disp not in slots or data.get(i.address+i.disp_offset)!=operand.mem.disp):
                raise ValueError('SDK indirect call lacks an original mutable table slot')
        if i.group(capstone.CS_GRP_CALL) and i.operands[0].type==capstone.x86.X86_OP_IMM:
            site=i.address+i.imm_offset;dest=i.operands[0].imm
            if calls.get(site)==dest:used_calls.add(site)
            elif dest not in by:raise ValueError('SDK dispatch call lacks a complete original code owner')
    if used_calls!=set(calls) or used_data|table_fields!=set(data):raise ValueError('SDK dispatch code/table fields are hidden in padding or unconsumed')
    return dict(extent=extent,table_size=32 if switch else 0,alignment_size=code_end-extent,
                alignment_sha256=hashlib.sha256(code[extent:code_end]).hexdigest(),padding=padding,internal_padding=internal_padding,
                roots=roots,reachable_instruction_count=len(seen),external_tails=tails,
                indirect_call_count=sum(i.group(capstone.CS_GRP_CALL) and i.operands[0].type!=capstone.x86.X86_OP_IMM for i in ins if i.address in seen))
