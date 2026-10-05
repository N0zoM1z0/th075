"""Read whole SDK code carriers, real source metadata, reachable bodies and alignment."""
from __future__ import annotations
import struct
import hashlib
import capstone


def zero_region(target,address,size):
    pe=struct.unpack_from('<I',target,0x3c)[0]
    n=struct.unpack_from('<H',target,pe+6)[0];opt=struct.unpack_from('<H',target,pe+20)[0];base=struct.unpack_from('<I',target,pe+24+28)[0]
    for i in range(n):
        nm,vsize,rva,rawsize,rawptr,_,_,_,_,flags=struct.unpack_from('<8sIIIIIIHHI',target,pe+24+opt+40*i)
        if base+rva+rawsize<=address and address+size<=base+rva+vsize and flags&0x80000000 and flags&0x40000000 and not flags&0x20000000:
            return dict(section=nm.rstrip(b'\0').decode(),base=f'0x{base+rva:08X}',virtual_size=vsize,raw_size=rawsize,raw_offset=rawptr,flags=flags)
    raise ValueError('source zero-fill allocation is not entirely in writable PE virtual zero-fill storage')


def code_carrier(body, symbol, c, coff):
    count, defs = coff.parse_symbols(body, c.coff_name)
    own = [d for d in defs if d['symbol'] == symbol and d['section'] > 0]
    if len(own) != 1:
        raise ValueError('one actual source primary required')
    d = own[0]; h = struct.unpack_from('<8sIIIIIIHHI', body, 20+(d['section']-1)*40)
    peers = [p for p in defs if p['section'] == d['section'] and p['type'] == 32]
    if (d['offset'] or d['type'] != 32 or d['storage'] != 2 or not h[9]&0x20
            or not h[9]&0x1000 or not h[3] or h[4]+h[3] > len(body)
            or any(p != d and (p['storage'] != 3 or not ('$$' in p['symbol'] or p['symbol'].startswith('TAG_PACKET_')) or not 0 < p['offset'] < h[3]) for p in peers)):
        raise ValueError('unsupported complete source carrier or separate public peer')
    raw = body[h[4]:h[4]+h[3]]; syoff, n = struct.unpack_from('<II', body, 8); strings = body[syoff+n*18:]; symbols = {}; aux_records=[]; i=0
    while i<n:
        nm, val, sec, typ, storage, aux = struct.unpack_from('<8sIhHBB', body, syoff+i*18)
        sn=c.coff_name(nm, strings);symbols[i]=(sn,val,sec,typ,storage)
        if sec==d['section'] and typ==32:
            aux_records.append(dict(symbol=sn,index=i,aux_count=aux,aux_hex=body[syoff+(i+1)*18:syoff+(i+1+aux)*18].hex()))
        i+=1+aux
    fields=[]
    for i in range(h[7]):
        at, si, typ = struct.unpack_from('<IIH', body, h[5]+i*10)
        sn,val,sec,typ2,storage=symbols[si]
        fields.append(dict(offset=at,type_id=typ,type=c.COFF_RELOCATION_NAMES.get(typ,f'0x{typ:04X}'),symbol=sn,addend=struct.unpack_from('<I',raw,at)[0],local_symbol_offset=val if sec==d['section'] else None,symbol_index=si,symbol_section=sec,symbol_offset=val,symbol_type=typ2,symbol_storage=storage))
    return raw,fields,dict(primary=d,section=d['section'],flags=h[9],size=h[3],peers=peers,aux_records=aux_records)


def carrier_flow(code,address,source,fields,calls,data,sdk):
    dec=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);dec.detail=True; ins=list(dec.disasm(bytes(code),address));by={i.address:i for i in ins}
    if sum(i.size for i in ins)!=len(code):raise ValueError('whole code carrier does not decode')
    roots={address+p['offset'] for p in source['peers']};todo=list(roots);reachable=set(); external_jumps=[]
    while todo:
        at=todo.pop()
        if at in reachable:continue
        if at not in by:raise ValueError('entry/branch/fallthrough is not an instruction')
        reachable.add(at);i=by[at]
        if i.group(capstone.CS_GRP_RET):continue
        if i.group(capstone.CS_GRP_JUMP):
            if len(i.operands)!=1 or i.operands[0].type!=capstone.x86.X86_OP_IMM:
                raise ValueError('unresolved indirect carrier tail')
            dest=i.operands[0].imm
            if dest in by:todo.append(dest)
            elif i.mnemonic=='jmp' and calls.get(i.address+i.imm_offset)==dest:
                external_jumps.append(dict(address=f'0x{i.address:08X}',destination=f'0x{dest:08X}'))
            else:raise ValueError('external jump lacks a whole source callee')
            if i.mnemonic=='jmp':continue
        todo.append(i.address+i.size)
    ends=[i.address+i.size for i in ins if i.address in reachable];extent=max(ends)-address
    trailing=[i for i in ins if i.address>=address+extent]
    for i in trailing:
        if i.mnemonic=='nop':continue
        if i.mnemonic=='mov' and len(i.operands)==2 and all(o.type==capstone.x86.X86_OP_REG for o in i.operands) and i.operands[0].reg==i.operands[1].reg:continue
        if i.mnemonic!='lea' or len(i.operands)!=2 or i.operands[0].type!=capstone.x86.X86_OP_REG or i.operands[1].type!=capstone.x86.X86_OP_MEM:
            raise ValueError('unreachable carrier tail is not independently recognized alignment')
        mem=i.operands[1].mem
        if i.operands[0].reg!=mem.base or mem.index or mem.disp:
            raise ValueError('unreachable LEA changes a register')
    if any(f['offset']+4>extent for f in fields):raise ValueError('field hidden in purported alignment')
    if external_jumps:raise ValueError(('real-external-tail',external_jumps))
    indirect=sdk.verify_control_flow(code[:extent],address,calls,data)
    return dict(extent=extent,alignment_size=len(code)-extent,alignment_sha256=hashlib.sha256(code[extent:]).hexdigest(),roots=sorted(roots),reachable_instruction_count=len(reachable),indirect_call_count=indirect)
