#!/usr/bin/env python3
"""Replay the bounded R128 complete elementary math parents and shared entries."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
ACCEPTED = {'0x00641740': ('__CIcos', 174), '0x006417F0': ('__CIsin', 174), '0x00641E40': ('__CIsqrt', 186)}
AUXILIARY = {'0x00646BEE': ('__fast_exit', 13)}
LABELS = {'0x00641754': ('0x00641740', 9, 20, '_cos'), '0x0064175D': ('0x00641740', 145, 29, None), '0x00641804': ('0x006417F0', 9, 20, '_sin'), '0x0064180D': ('0x006417F0', 145, 29, None), '0x00641E54': ('0x00641E40', 9, 20, '_sqrt'), '0x00641E5D': ('0x00641E40', 157, 29, None)}
STATE = {(2709246, '_NAME_', '0x0066FED0', 4), (2559836, 'One', '0x00661600', 68), (2705778, '_NAME_', '0x0066FEE0', 4), (2733890, '_NAME_', '0x0066FEF0', 8), (2486736, '__indefinite', '0x00670270', 44), (2432134, '___fastflag', '0x0068E2C0', 8)}
LAYOUT_OBJECTS = [{'symbol': '_ElementaryMathLayoutProbe', 'offset': 0, 'size': 48, 'storage_span': 48, 'values': [4, 8, 10, 32, 0, 8, 16, 24, 1, 18, 30, 5]}]
LAYOUT_HEADERS = {'crt/src/cruntime.h', 'PlatformSDK/Include/WinBase.h', 'crt/src/fpieee.h', 'crt/src/math.h', 'PlatformSDK/Include/WinNT.h'}
CONFIDENCE = 'complete-vendor-elementary-math-code-data-entry-abi-provenance'
LABEL_CONFIDENCE = 'interior-entry-in-complete-vendor-elementary-math-primary'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/elementary-math-origin-evidence.json').read_text())
    identity = module('elementary_math_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R128' or m['target_sha256'] != identity.TARGET:
        raise ValueError('FP dispatch target identity differs')
    return m


def check_code_entry(binding, graph):
    entry = binding['code_entry']; owner = graph.get(entry['owner'])
    if not owner or owner['decision'] not in ('library','library-control','anchor'):
        raise ValueError('dispatch retains an unreviewed actual code entry')
    source = entry['source_definition']; primary = owner['source_definition']
    if (entry['source_member_offset'] != owner['member_offset']
            or source['symbol'] != binding['symbol'] or source['section'] != primary['section']
            or source['offset'] - primary['offset'] != entry['source_offset']
            or source['storage'] not in (2,3,6)
            or not 0 <= entry['source_offset'] < owner['size']
            or int(binding['target_address'],16) != int(owner['address'],16) + entry['source_offset']):
        raise ValueError('dispatch code pointer loses its actual defining source owner/entry')


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(m['functions']) != 3 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete elementary math cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != 20
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('elementary math function loses its complete own auxiliary extent')
    if (len(m['auxiliary_bodies']) != 1
            or {r['address']: (r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']} != AUXILIARY
            or any(r['decision'] != 'library-control' or r['ledger_size'] is not None
                   or r['code_size'] != r['size'] for r in m['auxiliary_bodies'])):
        raise ValueError('elementary math complete source controls gain invented candidates')
    if (len(m['interior_labels']) != 6 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('elementary math shared entries lose complete source parents or gain standalone credit')
    if len(m['anchors']) != 6 or sum(r['size'] for r in m['anchors']) != 239:
        raise ValueError('elementary math independent complete anchors differ')
    if any(m[k] for k in ('common_globals','pending_labels','diagnostic_contexts','scope_tables',
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('elementary math graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 6 or sum(r['size'] for r in m['state_data']) != 136
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('elementary math graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 48 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural elementary math operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R127',manifest='fp-dispatch-origin-evidence.json'),
                                   dict(evidence_id='R107',manifest='runtime-leaf-origin-evidence.json')]:
        raise ValueError('elementary math loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] == 'callee':
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('elementary math graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('elementary math shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('elementary math direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] != 'code-entry' or b['type'] != 'DIR32':
                raise ValueError('elementary math table loses full typed entry provenance')
            check_code_entry(b, graph)
    check_dispatch_protocol(m, graph)
    return rows


def check_dispatch_protocol(m, graph):
    expected = [dict(address=key,operation=operation,c_entry_offset=20,shared_entry_offset=29,
                     intrinsic_call_offset=11,intrinsic_stack_bytes=12,control_word=639)
                for key,operation in [('0x00641740',18),('0x006417F0',30),('0x00641E40',5)]]
    if m['elementary_protocol'] != expected:
        raise ValueError('elementary operation/stack/control-word protocol differs')
    for p in expected:
        row = graph[p['address']]; a = int(row['address'],16)
        witnesses = {int(w['site'],16)-a:(w['mnemonic'],w['operands']) for w in row['instruction_witnesses']}
        required = {0:('sub','esp, 0xc'),3:('fst','qword ptr [esp]'),
                    11:('call',hex(a+29)),16:('add','esp, 0xc'),19:('ret',''),
                    20:('lea','edx, [esp + 4]'),29:('push','edx')}
        if any(witnesses.get(offset) != witness for offset,witness in required.items()):
            raise ValueError('elementary complete intrinsic/C/shared-entry ABI differs')
        ins = row['instruction_witnesses']
        operation_text = str(p['operation']) if p['operation'] < 10 else hex(p['operation'])
        moves = [w for w in ins if w['mnemonic']=='mov' and w['operands']==f'edx, {operation_text}']
        if len(moves) != 2:
            raise ValueError('elementary normal/error paths lose actual operation codes')
        if not any(w['mnemonic']=='cmp' and w['operands']=='word ptr [esp], 0x27f' for w in ins):
            raise ValueError('elementary source/control-word comparison differs')
        if p['operation'] in (18,30):
            op = 'fcos' if p['operation']==18 else 'fsin'
            if sum(w['mnemonic']==op for w in ins) != 2 or sum(w['mnemonic']=='fprem1' for w in ins) != 1:
                raise ValueError('elementary trigonometric computation/range-reduction paths differ')
        elif (sum(w['mnemonic']=='fsqrt' for w in ins) != 1
              or not any(w['mnemonic']=='test' and w['operands']=='eax, 0x80000000' for w in ins)):
            raise ValueError('elementary square-root sign/computation paths differ')


def check_interior_entry(label, parent, definitions, target_ins, source_ins):
    offset = label['source_offset']; base = int(parent['address'],16)
    if int(label['address'],16) != base+offset or base+offset not in {i.address for i in target_ins}:
        raise ValueError('elementary interior entry is not an actual full-owner instruction')
    if label['source_symbol'] is not None:
        actual = next((d for d in definitions if d['symbol']==label['source_symbol']
                       and d['section']==parent['source_definition']['section']),None)
        if (actual != label['source_definition'] or actual is None
                or actual['offset']-parent['source_definition']['offset'] != offset
                or offset != 20 or actual['storage'] != 2
                or label['source_entry_basis'] != 'defined-C-entry' or label['entry_call_offset'] is not None):
            raise ValueError('elementary C entry loses its actual full-owner defining source symbol')
    else:
        if (label['source_definition'] is not None or offset != 29
                or label['source_entry_basis'] != 'internal-call-and-C-entry-fallthrough'
                or label['entry_call_offset'] != 11):
            raise ValueError('unnamed computation entry gains an invented source definition')
        source_base = parent['source_definition']['offset']
        call = next((i for i in source_ins if i.address==source_base+11),None)
        target_call = next((i for i in target_ins if i.address==base+11),None)
        predecessor = next((i for i in source_ins if i.address==source_base+24),None)
        if (not call or call.mnemonic!='call' or call.operands[0].type!=X86_OP_IMM
                or call.operands[0].imm != source_base+29
                or not target_call or target_call.operands[0].imm != base+29
                or not predecessor or predecessor.mnemonic!='call' or predecessor.size!=5
                or predecessor.address+predecessor.size!=source_base+29):
            raise ValueError('unnamed computation entry loses actual source call/fallthrough evidence')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('elementary math loses complete origin-only extent')
    if (origin['evidence_id'] != 'R128' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row['coff_symbol']):
        raise ValueError('elementary math canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('elementary math shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R128' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('elementary math shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('elementary math external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('elementary math member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('elementary_math_old','verify-runtime-error-origins.py')
    c = module('elementary_math_target','compare-coff-function.py')
    archive_reader = module('elementary_math_archive','verify-runtime-origins.py')
    coff = module('elementary_math_coff','coff_data.py')
    startup = module('elementary_math_geometry','verify-startup-dependency-origins.py')
    record = module('elementary_math_ledger','verify-vendor-record-origins.py')
    facts = module('elementary_math_facts','verify-game-lifetime-origins.py')
    imports_module = module('elementary_math_imports','verify-import-origins.py')
    literal = module('elementary_math_scalar','verify-runtime-external-origins.py')
    sections = module('elementary_math_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete elementary math source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('elementary math complete primary loses an actual interior candidate')
    archive = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest() != m['archive_sha256']:
        raise ValueError('pinned whole CRT archive differs')
    members = {off:(name,data) for off,name,data in archive_reader.archive_members(archive)}
    def member(row):
        name,data = members[row['member_offset']]
        if name != row['member'] or hashlib.sha256(data).hexdigest() != row['member_sha256']:
            raise ValueError('complete source member identity differs')
        return data
    target_sections = sections.sections(target); imports = imports_module.pe_imports(target,c)
    state_map = {}; global_state = {}
    for row in m['state_data']:
        raw,desc = old.whole_section(member(row),row['symbol'],c,coff)
        a = int(row['target_address'],16)
        if desc != row['source_section'] or desc['size'] != row['size']:
            raise ValueError('elementary math whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('elementary math source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('elementary math state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('elementary math whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('elementary math initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('elementary math complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('elementary math state loses whole writable target storage')
        else:
            literal.check_scalar(raw,actual,row['size'],target_sections,a)
    for use in m['state_uses']:
        state_map[(use['member_offset'],use['symbol'])] = resolve_state_reference(use,state_map,global_state)
    decoder = Cs(CS_ARCH_X86,CS_MODE_32); decoder.detail = True
    scratch = ROOT / 'build/origin-fp-dispatch-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural math control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned math control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_ElementaryMathLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural math data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural math/math offsets or bitfields differ')
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R127 and R107'):
                    raise ValueError('elementary math retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = c.object_function(path,row['coff_symbol'])
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('elementary math complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('elementary math full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = list(decoder.disasm(actual,a)); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('elementary math whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('elementary math complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] == 'anchor':
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('elementary math field lacks member-local/whole strong data provenance')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('elementary math code entry catalog differs from actual complete source definitions')
        for row in m['functions']+m['auxiliary_bodies']:
            a = int(row['address'],16); ins = decoded[row['address']]; starts = {i.address for i in ins}
            edges = {e['site']:e for e in row['direct_edges']}; observed_sites = set()
            # Direct source branches without relocations must retain the same
            # section and actual complete target owner, including shared tails.
            path.write_bytes(member(row)); code,_ = c.object_function(path,row['coff_symbol'])
            source_ins = {i.address-row['source_definition']['offset']:i for i in decoder.disasm(code,row['source_definition']['offset'])}
            for i in ins:
                if ((i.mnemonic != 'call' and not i.group(CS_GRP_JUMP)) or not i.operands
                        or i.operands[0].type != X86_OP_IMM):
                    continue
                dest = i.operands[0].imm
                if a <= dest < a+row['size']:
                    if dest not in starts:
                        raise ValueError('elementary math local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('elementary math direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('elementary math direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('elementary math same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('elementary math shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('elementary math complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('elementary math data pointer does not reach a complete actual code entry')
        for label in m['interior_labels']:
            parent = graph[label['parent']]
            path.write_bytes(member(parent)); source,_ = c.object_function(path,parent['coff_symbol'])
            defs = coff.parse_symbols(member(parent),c.coff_name)[1]
            source_ins = list(decoder.disasm(source,parent['source_definition']['offset']))
            check_interior_entry(label,parent,defs,decoded[parent['address']],source_ins)
            if not args.evidence_only:
                check_label(label,functions[label['address']],origins[label['address']],functions,origins,graph)
    for verifier in ('verify-fp-dispatch-origins.py','verify-runtime-leaf-origins.py'):
        result = subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+verifier],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:
            raise ValueError('retained independent complete graph replay failed: '+verifier+': '+result.stderr[-1500:])
    print('R128 origins OK: three complete library primaries / 534 bytes / 41 fields; six existing C/shared entries / 474 overlapping bytes; one full fast-exit auxiliary / 13 bytes; six independent anchors / 239 bytes / three fields; six whole defining data sections / 136 bytes; natural 48-byte math controls and retained cold R127 graph; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
