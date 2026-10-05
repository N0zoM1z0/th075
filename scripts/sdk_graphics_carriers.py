"""Whole original graphics SDK control flow, including its two parser switches."""
import hashlib
import struct
import capstone


def instructions(raw, address, size):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    result = list(decoder.disasm(bytes(raw[:size]), address))
    if not result or sum(i.size for i in result) != size:
        raise ValueError('Graphics SDK whole code region does not decode')
    return result


def switch_edges(raw, address, fields, ins, spec):
    """Validate actual guarded indexing, full source label fields and selector bytes."""
    if spec is None:
        return {}, set()
    code_size = spec['code_size']; count = spec['count']
    table_end = code_size + 4*count
    by = {i.address-address: i for i in ins}
    jump = by.get(spec['jump']); cmp = by.get(spec['compare']); guard = by.get(spec['guard'])
    if (not jump or jump.mnemonic != 'jmp' or jump.operands[0].type != capstone.x86.X86_OP_MEM
            or not cmp or cmp.mnemonic != 'cmp' or cmp.op_str != 'eax, '+hex(spec['maximum'])
            or not guard or guard.mnemonic != 'ja' or guard.operands[0].type != capstone.x86.X86_OP_IMM
            or guard.operands[0].imm-address not in by):
        raise ValueError('Graphics SDK actual unsigned switch guard differs')
    mem = jump.operands[0].mem
    if mem.base or mem.index != capstone.x86.X86_REG_EAX or mem.scale != 4 or mem.disp != address+code_size:
        raise ValueError('Graphics SDK switch loses actual indexed table')
    local = [f for f in fields if code_size <= f['offset'] < table_end]
    targets = list(struct.unpack('<'+str(count)+'I', raw[code_size:table_end]))
    if (len(local) != count or [f['offset'] for f in local] != list(range(code_size, table_end, 4))
            or any(f['type'] != 'DIR32' or f['symbol_type'] or f['symbol_storage'] != 6
                   or f['local_symbol_offset'] != f['symbol_offset'] or f['addend']
                   or targets[j] != address+f['symbol_offset'] or targets[j]-address not in by
                   for j, f in enumerate(local))):
        raise ValueError('Graphics SDK complete source switch labels differ')
    if spec.get('selector') is None:
        if len(raw) != table_end or spec['maximum']+1 != count or guard.address+guard.size != jump.address:
            raise ValueError('Graphics SDK direct switch bound/whole table differs')
    else:
        selector = by.get(spec['selector']); off = table_end
        if (len(raw) != off+spec['maximum']+1 or not selector or selector.mnemonic != 'movzx'
                or selector.operands[0].type != capstone.x86.X86_OP_REG
                or selector.operands[0].reg != capstone.x86.X86_REG_EAX
                or selector.operands[1].type != capstone.x86.X86_OP_MEM):
            raise ValueError('Graphics SDK full compressed selector differs')
        mem = selector.operands[1].mem
        if (mem.base != capstone.x86.X86_REG_EAX or mem.index or mem.disp != address+off
                or selector.operands[1].size != 1 or max(raw[off:]) >= count
                or guard.address+guard.size != selector.address):
            raise ValueError('Graphics SDK selector escapes source jump table')
        between = [i for i in ins if selector.address+selector.size <= i.address < jump.address]
        if any(i.mnemonic != 'push' or i.op_str != 'edi' for i in between):
            raise ValueError('Graphics SDK indexed register changes after selector')
    return {jump.address: targets}, {address+f['offset'] for f in local}


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
                slot = dynamic_tail
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
