"""Whole original image CFGs, bounded state switches and retained nonreturn suffixes."""
import hashlib
import importlib.util
from pathlib import Path
import struct
import capstone

_SPEC=importlib.util.spec_from_file_location('image_blit_flow',Path(__file__).with_name('sdk_blit_carriers.py'))
_B=importlib.util.module_from_spec(_SPEC);_SPEC.loader.exec_module(_B)
instructions=_B.instructions


def aliases(register):
    return ({capstone.x86.X86_REG_EAX,capstone.x86.X86_REG_AX,capstone.x86.X86_REG_AL,capstone.x86.X86_REG_AH}
            if register=='eax' else
            {capstone.x86.X86_REG_ECX,capstone.x86.X86_REG_CX,capstone.x86.X86_REG_CL,capstone.x86.X86_REG_CH})


def switch_edges(raw,address,fields,ins,spec):
    if spec is None:return {},set()
    code=spec['code_size'];count=spec['count'];reg=spec['register'];by={i.address-address:i for i in ins}
    if reg not in ('eax','ecx') or count not in (10,14) or len(raw)!=code+4*count:
        raise ValueError('Image switch whole extent/register/count differs')
    jump=by[spec['jump']]
    if jump.mnemonic!='jmp' or jump.operands[0].type!=capstone.x86.X86_OP_MEM:
        raise ValueError('Image switch is not its actual source indexed jump')
    mem=jump.operands[0].mem;index=capstone.x86.X86_REG_EAX if reg=='eax' else capstone.x86.X86_REG_ECX
    if mem.base or mem.index!=index or mem.scale!=4 or mem.disp!=address+code:
        raise ValueError('Image switch table source address/index differs')
    local=[f for f in fields if code<=f['offset']<len(raw)];targets=list(struct.unpack('<'+'I'*count,raw[code:]))
    if len(local)!=count:raise ValueError('Image switch omits a real original table field')
    for j,f in enumerate(local):
        if (f['offset']!=code+4*j or f['type']!='DIR32' or f['symbol_type'] or f['symbol_storage']!=6
                or f['local_symbol_offset']!=f['symbol_offset'] or f['addend']
                or targets[j]!=address+f['symbol_offset'] or targets[j]-address not in by):
            raise ValueError('Image switch loses its entire original local label/field')
    edges={jump.address:targets}
    prove_index_paths(ins,address,spec,edges)
    return edges,{address+f['offset'] for f in local}


def prove_index_paths(ins,address,spec,edges):
    """Every root-to-table path must retain its actual unsigned comparison bound."""
    by={i.address:i for i in ins};reg=spec['register'];idx=aliases(reg);guards={address+g['compare']:g for g in spec['guards']}
    constants=spec.get('constants',[]);definitions={}
    for constant in constants:
        push=by[address+constant['push']];pop=by[address+constant['pop']]
        if (constant['register']!='ebp' or constant['value'] not in (13,31) or push.mnemonic!='push'
                or push.operands[0].type!=capstone.x86.X86_OP_IMM or push.operands[0].imm!=constant['value']
                or pop.mnemonic!='pop' or pop.op_str!='ebp'):
            raise ValueError('Image state bound lacks its actual nonvolatile constant definition')
        between=[i for i in ins if push.address+push.size<=i.address<pop.address]
        for i in between:
            _,writes=i.regs_access()
            if capstone.x86.X86_REG_ESP in writes:
                raise ValueError('Image constant stack definition is overwritten')
            if i.mnemonic=='mov' and i.operands[0].type==capstone.x86.X86_OP_MEM:
                mem=i.operands[0].mem
                if mem.index==capstone.x86.X86_REG_ESP or (mem.base==capstone.x86.X86_REG_ESP and mem.disp<4):
                    raise ValueError('Image constant stack cell is overwritten')
        entries={i.address for i in between}|{pop.address}
        if any(i.group(capstone.CS_GRP_JUMP) or i.group(capstone.CS_GRP_CALL)
               for i in between) or any(i.group(capstone.CS_GRP_JUMP) and i.operands[0].type==capstone.x86.X86_OP_IMM
               and i.operands[0].imm in entries for i in ins):
            raise ValueError('Image bound definition has an alternate entry')
        definitions[pop.address]=constant['value']
    for at,g in guards.items():
        cmp=by[at];branch=by[address+g['guard']]
        rhs=g.get('bound_register')
        if (g['maximum']!=spec['count']-1 or cmp.mnemonic!='cmp' or cmp.operands[0].type!=capstone.x86.X86_OP_REG
                or cmp.operands[0].reg!=(capstone.x86.X86_REG_EAX if reg=='eax' else capstone.x86.X86_REG_ECX) or branch.mnemonic!='jbe'
                or branch.operands[0].type!=capstone.x86.X86_OP_IMM or branch.operands[0].imm not in by
                or (rhs and (rhs!='ebp' or cmp.operands[1].type!=capstone.x86.X86_OP_REG
                    or cmp.operands[1].reg!=capstone.x86.X86_REG_EBP))
                or (not rhs and (cmp.operands[1].type!=capstone.x86.X86_OP_IMM
                    or cmp.operands[1].imm!=g['maximum']))):
            raise ValueError('Image actual state comparison/unsigned guard differs')
    todo=[(address,None,None,None)];seen=set();used=set();jump_bounds=set();reaching=set()
    while todo:
        state=todo.pop()
        if state in seen:continue
        seen.add(state);at,bounded,flag,ebp=state
        if at not in by:raise ValueError('Image bound path escapes whole code')
        i=by[at]
        if at in edges:
            if bounded!=spec['count']-1:raise ValueError('Image table has an unbounded root path')
            jump_bounds.add(bounded)
            todo.extend((dest,bounded,flag,ebp) for dest in edges[at]);continue
        if i.group(capstone.CS_GRP_RET):continue
        if at in guards:
            g=guards[at]
            if g.get('bound_register') and ebp not in {q['value'] for q in constants}:
                raise ValueError('Image nonvolatile state bound is not independently reaching')
            limit=ebp if g.get('bound_register') else g['maximum']
            reaching.add((at-address,limit));flag=(at,limit)
        else:
            _,writes=i.regs_access()
            if idx & set(writes):bounded=None;flag=None
            if capstone.x86.X86_REG_EBP in writes:ebp=definitions.get(at)
            if capstone.x86.X86_REG_EFLAGS in writes:flag=None
            if i.group(capstone.CS_GRP_CALL):bounded=None;flag=None
        if i.group(capstone.CS_GRP_JUMP):
            if i.operands[0].type!=capstone.x86.X86_OP_IMM:raise ValueError('Image range proof has an opaque branch')
            dest=i.operands[0].imm
            if i.mnemonic=='jmp':
                if dest in by:todo.append((dest,bounded,flag,ebp))
                continue
            if flag is not None and flag[0] in guards and at==address+guards[flag[0]]['guard']:
                used.add(flag[0]);todo.append((dest,flag[1],flag,ebp))
            else:todo.append((dest,bounded,flag,ebp))
        todo.append((at+i.size,bounded,flag,ebp))
    if used!=set(guards) or not jump_bounds:raise ValueError('Image state bounds are incomplete/unreachable')
    report=dict(reaching_comparison_bounds=[dict(compare=a,maximum=v) for a,v in sorted(reaching)],
                table_path_bounds=sorted(jump_bounds),
                opaque_index_overapproximation=list(range(spec['count'],max(jump_bounds)+1)))
    if report!=spec['index_paths']:
        raise ValueError('Image actual index paths or unproven runtime state contract differs: '+repr(report))
    return report


def check_nonreturn(raw,address,fields,calls,ins,spec):
    if spec is None:return set()
    by={i.address-address:i for i in ins};call=by[spec['call']];post=by[spec['suffix']['offset']]
    f=[f for f in fields if f['offset']==spec['call']+1]
    if (len(f)!=1 or f[0]['type']!='REL32' or f[0]['symbol']!=spec['symbol'] or call.mnemonic!='call'
            or call.operands[0].type!=capstone.x86.X86_OP_IMM or calls.get(address+spec['call']+1)!=int(spec['target'],16)
            or (spec['symbol'],spec['target']) not in [('_longjmp','0x00643604'),('_exit','0x0064424A')]
            or post.address!=call.address+call.size or post.address+post.size!=address+len(raw)
            or post.size!=1 or bytes(post.bytes).hex()!=spec['suffix']['bytes']
            or (post.mnemonic,post.op_str) not in [('pop','esi'),('int3','')]
            or post.mnemonic!=spec['suffix']['mnemonic'] or post.op_str!=spec['suffix']['operands']):
        raise ValueError('Image nonreturn source suffix/callee/whole extent differs')
    return {post.address}


def flow(raw, address, roots, fields, calls, data, switch=None, dynamic_tail=None, nonreturn=None):
    size = switch['code_size'] if switch else len(raw)
    ins = instructions(raw, address, size); by = {i.address: i for i in ins}
    edges, table_fields = switch_edges(raw, address, fields, ins, switch)
    suffix = check_nonreturn(raw,address,fields,calls,ins,nonreturn)
    todo = [address+r for r in roots]; seen = set(); tails = []
    used_calls = set(); used_data = set(); indirect = []; returns = []
    while todo:
        at = todo.pop()
        if at in seen:
            continue
        if at not in by:
            raise ValueError('Graphics SDK entry/branch/fallthrough is not an instruction')
        seen.add(at); i = by[at]
        if nonreturn and at == address+nonreturn['call']:
            continue
        if i.group(capstone.CS_GRP_RET):
            returns.append(dict(offset=at-address, cleanup=i.operands[0].imm if i.operands else 0))
            continue
        if i.group(capstone.CS_GRP_JUMP):
            if at in edges:
                todo.extend(edges[at]); continue
            if i.operands[0].type != capstone.x86.X86_OP_IMM:
                if dynamic_tail == 'eax' and i.mnemonic == 'jmp' and i.op_str == 'eax':
                    choices = _B.register_tail_choices(ins, address, data)
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
    if seen | suffix != set(by) or seen & suffix:
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
    if switch and switch['index_paths']['opaque_index_overapproximation']:
        tails.append(dict(offset=switch['jump'],runtime_callee='unknown',
                          opaque_index_overapproximation=switch['index_paths']['opaque_index_overapproximation'],
                          basis='Source owns only its complete local-label table; internal-state validity is unproven.'))
    return dict(code_size=size, whole_size=len(raw), roots=roots,
                instruction_count=len(by), reachable_instruction_count=len(seen),
                nonreturn_suffix=nonreturn, table_size=len(raw)-size,
                table_sha256=hashlib.sha256(raw[size:]).hexdigest(),
                returns=sorted(returns, key=lambda r: r['offset']),
                tails=tails, indirect_calls=indirect)
