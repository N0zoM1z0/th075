"""Whole SDK blit/codec CFGs, source-guarded tables and mutable dispatch paths."""
import hashlib
import importlib.util
from pathlib import Path
import struct
import capstone

_SPEC = importlib.util.spec_from_file_location('blit_graphics_flow', Path(__file__).with_name('sdk_graphics_carriers.py'))
_G = importlib.util.module_from_spec(_SPEC)
_SPEC.loader.exec_module(_G)
instructions = _G.instructions


def switch_edges(raw, address, fields, ins, spec):
    if spec is None or spec.get('register','eax') == 'eax':
        return _G.switch_edges(raw,address,fields,ins,spec)
    # The original Box2D switch indexes ECX, after unsigned ECX <= 7.
    by = {i.address-address:i for i in ins}
    cmp, guard, jump = (by[spec[k]] for k in ['compare','guard','jump'])
    code, count = spec['code_size'], spec['count']
    if (spec['register']!='ecx' or spec['maximum']!=7 or count!=8
            or cmp.mnemonic!='cmp' or cmp.op_str!='ecx, 7'
            or guard.mnemonic!='ja' or guard.operands[0].type!=capstone.x86.X86_OP_IMM
            or guard.operands[0].imm-address not in by
            or guard.address+guard.size!=jump.address
            or jump.mnemonic!='jmp' or jump.operands[0].type!=capstone.x86.X86_OP_MEM):
        raise ValueError('Blit actual source unsigned ECX switch differs')
    mem = jump.operands[0].mem
    if mem.base or mem.index!=capstone.x86.X86_REG_ECX or mem.scale!=4 or mem.disp!=address+code:
        raise ValueError('Blit indexed complete ECX table differs')
    local = [f for f in fields if code<=f['offset']<len(raw)]
    if len(raw)!=code+4*count or len(local)!=count:
        raise ValueError('Blit truncates its complete table')
    targets = list(struct.unpack('<8I',raw[code:]))
    for j,f in enumerate(local):
        if (f['offset']!=code+4*j or f['type']!='DIR32' or f['symbol_type']
                or f['symbol_storage']!=6 or f['local_symbol_offset']!=f['symbol_offset']
                or f['addend'] or targets[j]!=address+f['symbol_offset'] or targets[j]-address not in by):
            raise ValueError('Blit complete original table label/field differs')
    return {jump.address:targets}, {address+f['offset'] for f in local}


def register_tail_choices(ins, address, data):
    by={i.address:i for i in ins}; todo=[(address,None)]; seen=set(); choices=set()
    while todo:
        at,value=todo.pop()
        if (at,value) in seen:continue
        seen.add((at,value)); i=by[at]
        if i.mnemonic=='jmp' and i.op_str=='eax':
            if value is None:raise ValueError('Blit register tail has an unowned reaching definition')
            choices.add(value);continue
        if i.mnemonic=='mov' and i.op_str.startswith('eax, '):
            if i.operands[1].type!=capstone.x86.X86_OP_IMM or data.get(at+i.imm_offset)!=i.operands[1].imm:
                raise ValueError('Blit EAX definition is not a real owned DIR32 function field')
            value=i.operands[1].imm
        elif i.group(capstone.CS_GRP_CALL):value=None
        else:
            _,writes=i.regs_access()
            if capstone.x86.X86_REG_EAX in writes:value=None
        if i.group(capstone.CS_GRP_JUMP):
            if i.operands[0].type!=capstone.x86.X86_OP_IMM:
                raise ValueError('Blit unreviewed branch before register tail')
            todo.append((i.operands[0].imm,value))
            if i.mnemonic=='jmp':continue
        todo.append((at+i.size,value))
    if len(choices)!=2:raise ValueError('Blit register tail loses an actual runtime alternative')
    return [f'0x{x:08X}' for x in sorted(choices)]


def dispatch_paths(raw, address, fields, calls, data):
    """Replay zero/nonzero CPU paths, retaining mutable destinations as alternatives."""
    ins=instructions(raw,address,len(raw)); by={i.address:i for i in ins}
    if calls!={address+4:0x00620A70}:
        raise ValueError('Blit initializer loses its complete original CPU dependency')
    result=[]
    for cpu in [0,1]:
        at=address; eax=None; zero=None; stores={}; path=[]
        while True:
            if at in path or at not in by:
                raise ValueError('Blit initializer path loops or leaves whole instructions')
            path.append(at);i=by[at];op=i.operands
            if i.mnemonic=='call':
                if i.operands[0].type!=capstone.x86.X86_OP_IMM or calls.get(at+i.imm_offset)!=i.operands[0].imm:
                    raise ValueError('Blit initializer substitutes a CPU call')
                eax=cpu
            elif i.mnemonic=='test' and i.op_str=='eax, eax':
                zero=eax==0
            elif i.mnemonic in ('je','jne'):
                if zero is None:raise ValueError('Blit initializer branch lacks actual CPU flags')
                if zero==(i.mnemonic=='je'):
                    at=op[0].imm;continue
            elif i.mnemonic=='mov' and op[0].type==capstone.x86.X86_OP_REG and op[0].reg==capstone.x86.X86_REG_EAX:
                if op[1].type!=capstone.x86.X86_OP_IMM or data.get(at+i.imm_offset)!=op[1].imm:
                    raise ValueError('Blit initializer EAX is not a real function-address field')
                eax=op[1].imm
            elif i.mnemonic=='mov' and op[0].type==capstone.x86.X86_OP_MEM:
                mem=op[0].mem;slot=mem.disp
                if mem.base or mem.index or data.get(at+i.disp_offset)!=slot or slot not in (0x66cf68,0x66cf6c):
                    raise ValueError('Blit initializer store lacks its complete owning slot')
                if op[1].type==capstone.x86.X86_OP_IMM:
                    if data.get(at+i.imm_offset)!=op[1].imm:
                        raise ValueError('Blit initializer store invents a function address')
                    value=op[1].imm
                elif op[1].type==capstone.x86.X86_OP_REG and op[1].reg==capstone.x86.X86_REG_EAX:
                    value=eax
                else:raise ValueError('Blit initializer has an unsupported pointer store')
                if value not in (0x611afb,0x611c72,0x611d5a):
                    raise ValueError('Blit initializer stores an unowned runtime alternative')
                stores[slot]=value
            elif i.mnemonic=='jmp':
                if op[0].type==capstone.x86.X86_OP_IMM:
                    at=op[0].imm;continue
                if op[0].type==capstone.x86.X86_OP_REG and op[0].reg==capstone.x86.X86_REG_EAX:
                    dest=eax
                elif op[0].type==capstone.x86.X86_OP_MEM and not op[0].mem.base and not op[0].mem.index:
                    dest=stores.get(op[0].mem.disp)
                else:raise ValueError('Blit initializer tail lacks a proven reaching value')
                if dest is None:raise ValueError('Blit initializer tail remains unbound')
                break
            elif i.mnemonic not in ('push','pop') and not (i.mnemonic=='mov' and i.op_str=='ebp, esp'):
                raise ValueError('Blit initializer has an unreviewed state-changing instruction')
            at+=i.size
        result.append(dict(cpu_condition='zero' if not cpu else 'nonzero',
                           instruction_offsets=[p-address for p in path],
                           writes={f'0x{k:08X}':f'0x{v:08X}' for k,v in sorted(stores.items())},
                           tail_destination=f'0x{dest:08X}'))
    if set(p for r in result for p in r['instruction_offsets'])!={i.address-address for i in ins}:
        raise ValueError('Blit CPU alternatives hide an instruction path')
    return result


def flow(raw, address, roots, fields, calls, data, switch=None, dynamic_tail=None):
    size = switch['code_size'] if switch else len(raw)
    ins = instructions(raw, address, size); by = {i.address: i for i in ins}
    edges, table_fields = switch_edges(raw, address, fields, ins, switch)
    todo = [address+r for r in roots]; seen = set(); tails = []
    used_calls = set(); used_data = set(); indirect = []; returns = []
    while todo:
        at = todo.pop()
        if at in seen:
            continue
        if at not in by:
            raise ValueError('Graphics SDK entry/branch/fallthrough is not an instruction')
        seen.add(at); i = by[at]
        if i.group(capstone.CS_GRP_RET):
            returns.append(dict(offset=at-address, cleanup=i.operands[0].imm if i.operands else 0))
            continue
        if i.group(capstone.CS_GRP_JUMP):
            if at in edges:
                todo.extend(edges[at]); continue
            if i.operands[0].type != capstone.x86.X86_OP_IMM:
                if dynamic_tail == 'eax' and i.mnemonic == 'jmp' and i.op_str == 'eax':
                    choices = register_tail_choices(ins, address, data)
                    tails.append(dict(offset=at-address, runtime_callee='unknown', alternatives=choices))
                    continue
                slot = dynamic_tail if isinstance(dynamic_tail,int) else None
                if (slot is None or i.mnemonic != 'jmp' or bytes(i.bytes[:2]) != b'\xff\x25'
                        or i.operands[0].type != capstone.x86.X86_OP_MEM
                        or i.operands[0].mem.base or i.operands[0].mem.index
                        or i.operands[0].mem.disp != slot or data.get(at+i.disp_offset) != slot):
                    raise ValueError('Graphics SDK unresolved indirect tail')
                used_data.add(at+i.disp_offset)
                tails.append(dict(offset=at-address, slot=f'0x{slot:08X}', runtime_callee='unknown'))
                continue
            dest = i.operands[0].imm
            if dest in by:
                todo.append(dest)
            elif i.mnemonic == 'jmp' and calls.get(at+i.imm_offset) == dest:
                used_calls.add(at+i.imm_offset)
                tails.append(dict(offset=at-address, destination=f'0x{dest:08X}'))
            else:
                raise ValueError('Graphics SDK unbound external branch')
            if i.mnemonic == 'jmp':
                continue
        todo.append(at+i.size)
    # These carriers have no instruction padding. A switch label alone is not
    # an additional root: every normal instruction must be reachable from entry.
    if seen != set(by):
        raise ValueError('Graphics SDK unreachable instructions need independent extent evidence')
    for i in ins:
        for off, n in [(i.imm_offset, i.imm_size), (i.disp_offset, i.disp_size)]:
            site = i.address+off
            if site in data and n == 4:
                if struct.unpack_from('<I', raw, site-address)[0] != data[site]:
                    raise ValueError('Graphics SDK decoded genuine data field differs')
                used_data.add(site)
        if i.group(capstone.CS_GRP_CALL):
            if i.operands[0].type == capstone.x86.X86_OP_IMM:
                site = i.address+i.imm_offset; dest = i.operands[0].imm
                if calls.get(site) == dest:
                    used_calls.add(site)
                elif dest not in by:
                    raise ValueError('Graphics SDK call has no original complete owner')
            else:
                indirect.append(dict(offset=i.address-address, bytes=bytes(i.bytes).hex(), operands=i.op_str))
    if used_calls != set(calls) or used_data | table_fields != set(data):
        raise ValueError('Graphics SDK code/table fields are hidden or unconsumed')
    return dict(code_size=size, whole_size=len(raw), roots=roots,
                instruction_count=len(seen), table_size=len(raw)-size,
                table_sha256=hashlib.sha256(raw[size:]).hexdigest(),
                returns=sorted(returns, key=lambda r: r['offset']),
                tails=tails, indirect_calls=indirect)
