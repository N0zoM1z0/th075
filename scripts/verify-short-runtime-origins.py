#!/usr/bin/env python3
"""Replay the bounded R129 short runtime, math exception and array destruction graph."""
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
ACCEPTED = {'0x0064189E': ('_srand', 13), '0x006418AB': ('_rand', 34), '0x006418CD': ('_fabs', 177), '0x00641D4A': ('??_M@YGXPAXIHP6EX0@Z@Z', 96), '0x00641CEC': ('?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z', 94), '0x006473C1': ('__except1', 184), '0x0064730F': ('__handle_qnan1', 83), '0x00647271': ('__umatherr', 158)}
LEDGER_SIZES = {'0x0064189E': 13, '0x006418AB': 34, '0x006418CD': 177, '0x00641D4A': 72, '0x00641CEC': 47, '0x006473C1': 184, '0x0064730F': 83, '0x00647271': 158}
LABELS = {'0x00641D92': ('0x00641D4A', 24, 72, '$L18594')}
STATE = {(2888292, '??_C@_03IIINPABG@tan?$AA@', '0x006616AC', 4), (2888292, '??_C@_03MJLDFKDL@_y0?$AA@', '0x00661660', 4), (2888292, '??_C@_03MGHMBJCF@log?$AA@', '0x0065D52C', 4), (2888292, '??_C@_04ODHECPBC@fabs?$AA@', '0x00661694', 5), (2888292, '??_C@_04EIAKFFMI@sqrt?$AA@', '0x006616B8', 5), (2888292, '??_C@_05PBJFFIGL@floor?$AA@', '0x0066169C', 6), (2888292, '??_C@_04HPJJNFIM@cosh?$AA@', '0x006616E8', 5), (2888292, '??_C@_04KEPJIHGP@fmod?$AA@', '0x0066166C', 5), (2930386, '__matherr_flag', '0x00670CD8', 4), (2888292, '??_C@_04GFPJNGEK@ceil?$AA@', '0x006616A4', 5), (2888292, '??_C@_05HGHHAHAP@log10?$AA@', '0x006616F8', 6), (2888292, '??_C@_03NAKIGLHK@_y1?$AA@', '0x0066165C', 4), (2888292, '??_C@_03BLEJJJBH@sin?$AA@', '0x006616B4', 4), (2888292, '??_C@_05KNGEOGJB@atan2?$AA@', '0x006616C0', 6), (2888292, '?_names@?1??_get_fname@@9@9', '0x006702A0', 232), (2888292, '??_C@_04MLLJIGOK@atan?$AA@', '0x006616C8', 5), (2888292, '??_C@_03KHJOGHMM@exp?$AA@', '0x0065D530', 4), (2888292, '??_C@_04FJHINJAO@tanh?$AA@', '0x006616E0', 5), (2888292, '??_C@_04FIHNOPOL@asin?$AA@', '0x006616D8', 5), (370224, '$T18597', '0x00660F20', 12), (370224, '$T18578', '0x00660F10', 12), (2888292, '??_C@_04EHEDPDJG@modf?$AA@', '0x0066168C', 5), (1236214, '___security_cookie', '0x0066FE30', 4), (2888292, '??_C@_0L@KDOEJCKC@_nextafter?$AA@', '0x00661644', 11), (2888292, '??_C@_04COOMCNPB@sinh?$AA@', '0x006616F0', 5), (2566740, '__real@3ff0000000000000', '0x00657D00', 8), (2888292, '??_C@_06MEIMCGCF@_hypot?$AA@', '0x00661674', 7), (2888292, '??_C@_05KBKMEMPO@_cabs?$AA@', '0x0066167C', 6), (2888292, '??_C@_03ONILCKOB@_yn?$AA@', '0x00661658', 4), (2888292, '??_C@_05JGDBENOH@_logb?$AA@', '0x00661650', 6), (2888292, '??_C@_04PDIFKINK@acos?$AA@', '0x006616D0', 5), (2888292, '??_C@_03LALBNOCG@cos?$AA@', '0x006616B0', 4), (2888292, '??_C@_03JGHBODFD@pow?$AA@', '0x00661700', 4), (2888292, '??_C@_05CEJMAHNP@ldexp?$AA@', '0x00661684', 6), (2888292, '??_C@_05GKKHEGJL@frexp?$AA@', '0x00661664', 6)}
LAYOUT_OBJECTS = [{'symbol': '_ShortRuntimeLayoutProbe', 'offset': 0, 'size': 80, 'storage_span': 80, 'values': [4, 4, 4, 140, 20, 32767, 32, 0, 4, 8, 16, 24, 21, 10, 4, 8, 0, 4, 1, 0]}]
LAYOUT_HEADERS = {'crt/src/fpieee.h', 'crt/src/mtdll.h', 'crt/src/cruntime.h', 'PlatformSDK/Include/WinNT.h', 'PlatformSDK/Include/WinBase.h', 'crt/src/math.h', 'crt/src/stdlib.h'}
CALLBACK_CONTROL = {'coff_symbol': '_ShortRuntimeCallbackProbe@8', 'size': 13, 'source_sha256': '3b90c5d57fa4656263948a91f0fafbbbd3f4e275dfc1140459c441f9e0fd38ea', 'body_facts': {'returns': [{'site': '0x0000000A', 'cleanup': 8}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x00000006', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 0xc]'}, {'site': '0x00000009', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x0000000A', 'mnemonic': 'ret', 'operands': '8'}]}
CONFIDENCE = 'complete-vendor-short-runtime-fp-exception-eh-code-data-abi-provenance'
LABEL_CONFIDENCE = 'interior-entry-in-complete-vendor-array-destruction-primary'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/short-runtime-origin-evidence.json').read_text())
    identity = module('short_runtime_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R129' or m['target_sha256'] != identity.TARGET:
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
    if len(m['functions']) != 8 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete short runtime cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != ('whole-defining-code-section' if key=='0x00641D4A' else 'function-auxiliary-record')
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('short runtime function loses its complete own auxiliary extent')
    if m['auxiliary_bodies']:
        raise ValueError('short runtime gains invented auxiliary candidates')
    if (len(m['interior_labels']) != 1 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('short runtime shared entries lose complete source parents or gain standalone credit')
    if len(m['anchors']) != 14 or sum(r['size'] for r in m['anchors']) != 1762:
        raise ValueError('short runtime independent complete anchors differ')
    if any(m[k] for k in ('common_globals','pending_labels','scope_tables',
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('short runtime graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 35 or sum(r['size'] for r in m['state_data']) != 423
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('short runtime graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 80 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural short runtime operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R128',manifest='elementary-math-origin-evidence.json')]:
        raise ValueError('short runtime loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] == 'callee':
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('short runtime graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('short runtime shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('short runtime direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('short runtime table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_dispatch_protocol(m, graph)
    return rows


def check_dispatch_protocol(m, graph):
    expected = dict(seed_offset=20,multiplier=214013,increment=2531011,result_shift=16,
                    result_mask=32767,fabs_operation=21,name_pair_count=29,name_pair_size=8,
                    vector_parent='0x00641D4A',vector_size=96,vector_cleanup_offset=72,
                    array_unwind='0x00641CEC',array_unwind_size=94,
                    callback_operand='dword ptr [ebp + 0x14]',callback_argument_register='ecx',vector_return_bytes=16)
    if m['short_runtime_protocol'] != expected:
        raise ValueError('short runtime seed/math/name/array-callback protocol differs')
    pairs = next(r for r in m['state_data'] if r['symbol']=='?_names@?1??_get_fname@@9@9')
    if (pairs['size'] != 232 or len(pairs['relocations']) != 29
            or [b['offset'] for b in pairs['relocations']] != list(range(4,232,8))
            or any(b['target_kind']!='state' for b in pairs['relocations'])):
        raise ValueError('complete 29-entry operation/name table loses typed string pointers')
    witnesses = lambda key: {(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    if not {('mov','ecx, dword ptr [esp + 4]'),('mov','dword ptr [eax + 0x14], ecx')} <= witnesses('0x0064189E'):
        raise ValueError('srand loses its actual thread seed store')
    required = {('mov','ecx, dword ptr [eax + 0x14]'),('imul','ecx, ecx, 0x343fd'),
                ('add','ecx, 0x269ec3'),('mov','dword ptr [eax + 0x14], ecx'),
                ('shr','eax, 0x10'),('and','eax, 0x7fff')}
    if not required <= witnesses('0x006418AB'):
        raise ValueError('rand loses actual thread seed/update/result provenance')
    if sum(w['mnemonic']=='push' and w['operands']=='0x15'
           for w in graph['0x006418CD']['instruction_witnesses']) != 2:
        raise ValueError('fabs loses its actual exception operation code')
    for key in ('0x00641D4A','0x00641CEC'):
        row=graph[key]
        if (len(row['indirect_calls'])!=1 or row['indirect_calls'][0]['operand']!=expected['callback_operand']
                or ('mov','ecx, dword ptr [ebp + 8]') not in witnesses(key)
                or row['indirect_jumps'] or ('ret','0x10') not in witnesses(key)):
            raise ValueError('array destructor loses actual callback receiver/parameter/stdcall provenance')
    if m['callback_control'] != CALLBACK_CONTROL:
        raise ValueError('natural member callback ABI control differs')
    pending = m['diagnostic_contexts']
    if (len(pending)!=1 or pending[0]['address']!='0x00641DAA' or pending[0]['coff_symbol']!='_abs'
            or pending[0]['size']!=11 or pending[0]['decision']!='pending' or pending[0]['proposed_name']):
        raise ValueError('abs family gains unproved library/source identity')
    alternatives=m['abs_alternatives']
    if (len(alternatives)!=1 or alternatives[0]['coff_symbol']!='_labs' or alternatives[0]['size']!=11
            or alternatives[0]['extent_basis']!='function-auxiliary-record'):
        raise ValueError('abs/labs source-family ambiguity loses a full alternative')
    if (m['abs_expression_controls']['profile'] != ['/O1','/Ob0','/Gy','/GR-','/GX','/Zi','/GS','/I','src']
            or [(r['coff_symbol'],r['size']) for r in m['abs_expression_controls']['functions']]
               != [('_AbsIntExpressionControl',11),('_AbsLongExpressionControl',11)]):
        raise ValueError('ordinary abs expression controls lose whole natural alternatives')
    if (m['abs_context']['address']!='0x00641DAA' or m['abs_context']['previous_whole']!='0x00641D4A'
            or m['abs_context']['next_whole']!='0x00641DE0'):
        raise ValueError('abs ambiguity loses its actual independently closed neighbors')


def check_code_section(row, data, coff, comparison):
    definitions=coff.parse_symbols(data,comparison.coff_name)[1]
    primary=next(d for d in definitions if d['symbol']==row['coff_symbol'])
    header=struct.unpack_from('<8sIIIIIIHHI',data,20+(primary['section']-1)*40)
    section=dict(size=header[3],flags=f'0x{header[9]:08X}',
                 definitions=[d for d in definitions if d['section']==primary['section']])
    global_functions=[d for d in section['definitions'] if d['storage']==2 and d['type']==32]
    if (section!=row['source_code_section'] or header[3]!=row['size'] or primary['offset']
            or primary['type']!=32 or primary['storage']!=2 or global_functions!=[primary]
            or not header[9]&0x20 or not header[9]&0x20000000
            or not header[9]&0x40000000 or header[9]&0x80000000):
        raise ValueError('aux-less vector destructor loses its entire sole defining code section')


def object_code(path, row, comparison, coff):
    if row['extent_basis']=='function-auxiliary-record':
        return comparison.object_function(path,row['coff_symbol'])
    if row['extent_basis']!='whole-defining-code-section' or row['address']!='0x00641D4A':
        raise ValueError('unsupported complete code extent basis')
    check_code_section(row,path.read_bytes(),coff,comparison)
    try:
        comparison.object_function(path,row['coff_symbol'])
    except ValueError as error:
        if str(error)!='function symbol lacks a definition auxiliary record':
            raise
    else:
        raise ValueError('whole-section vector control unexpectedly gains an AUX extent')
    return comparison.object_function(path,row['coff_symbol'],row['source_code_section']['size'])


def check_interior_entry(label, parent, definitions, target_ins):
    actual=next((d for d in definitions if d['symbol']==label['source_symbol']
                 and d['section']==parent['source_definition']['section']),None)
    if (actual != label['source_definition'] or actual is None or actual['storage']!=3
            or actual['offset']-parent['source_definition']['offset']!=72
            or int(label['address'],16)!=int(parent['address'],16)+72
            or int(label['address'],16) not in {i.address for i in target_ins}):
        raise ValueError('vector cleanup loses actual full-section source label/owner')


def check_pending(function, origin):
    if (function['owner'] or function['proposed_name'] or function['source_file']
            or int(function['size'])!=11 or function['match_percent']!='0.00'
            or origin['origin']!='unknown' or origin['disposition']!='review'):
        raise ValueError('indistinguishable abs expression gains invented ownership/source/exact credit')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('short runtime loses complete origin-only extent')
    if (origin['evidence_id'] != 'R129' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('short runtime canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('short runtime shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R129' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('short runtime shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('short runtime external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('short runtime member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('short_runtime_old','verify-runtime-error-origins.py')
    c = module('short_runtime_target','compare-coff-function.py')
    archive_reader = module('short_runtime_archive','verify-runtime-origins.py')
    coff = module('short_runtime_coff','coff_data.py')
    startup = module('short_runtime_geometry','verify-startup-dependency-origins.py')
    record = module('short_runtime_ledger','verify-vendor-record-origins.py')
    facts = module('short_runtime_facts','verify-game-lifetime-origins.py')
    imports_module = module('short_runtime_imports','verify-import-origins.py')
    literal = module('short_runtime_scalar','verify-runtime-external-origins.py')
    sections = module('short_runtime_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete short runtime source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('short runtime complete primary loses an actual interior candidate')
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
            raise ValueError('short runtime whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('short runtime source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('short runtime state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('short runtime whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('short runtime initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('short runtime complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('short runtime state loses whole writable target storage')
        else:
            literal.check_scalar(linked,actual,row['size'],target_sections,a)
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
        entry = next(d for d in defs if d['symbol'] == '_ShortRuntimeLayoutProbe')
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
        callback=m['callback_control']; source,fields=c.object_function(path,callback['coff_symbol'])
        ins=list(decoder.disasm(source,0))
        if (len(source)!=callback['size'] or fields or hashlib.sha256(source).hexdigest()!=callback['source_sha256']
                or facts.body_facts(ins)!=callback['body_facts']
                or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=callback['instructions']):
            raise ValueError('cold complete natural member callback ABI differs')
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R128'):
                    raise ValueError('short runtime retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('short runtime complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('short runtime full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = list(decoder.disasm(actual,a)); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('short runtime whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('short runtime complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('short runtime field lacks member-local/whole strong data provenance')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('short runtime code entry catalog differs from actual complete source definitions')
        for row in m['functions']+m['auxiliary_bodies']:
            a = int(row['address'],16); ins = decoded[row['address']]; starts = {i.address for i in ins}
            edges = {e['site']:e for e in row['direct_edges']}; observed_sites = set()
            # Direct source branches without relocations must retain the same
            # section and actual complete target owner, including shared tails.
            path.write_bytes(member(row)); code,_ = object_code(path,row,c,coff)
            source_ins = {i.address-row['source_definition']['offset']:i for i in decoder.disasm(code,row['source_definition']['offset'])}
            for i in ins:
                if ((i.mnemonic != 'call' and not i.group(CS_GRP_JUMP)) or not i.operands
                        or i.operands[0].type != X86_OP_IMM):
                    continue
                dest = i.operands[0].imm
                if a <= dest < a+row['size']:
                    if dest not in starts:
                        raise ValueError('short runtime local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('short runtime direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('short runtime direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('short runtime same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('short runtime shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('short runtime complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('short runtime data pointer does not reach a complete actual code entry')
        for label in m['interior_labels']:
            parent = graph[label['parent']]
            path.write_bytes(member(parent))
            defs = coff.parse_symbols(member(parent),c.coff_name)[1]
            check_interior_entry(label,parent,defs,decoded[parent['address']])
            if not args.evidence_only:
                check_label(label,functions[label['address']],origins[label['address']],functions,origins,graph)
        pending=m['diagnostic_contexts'][0]
        if not args.evidence_only:
            check_pending(functions[pending['address']],origins[pending['address']])
        actual=c.pe_bytes_at(target,0x641DAA,11)
        for alternate in m['abs_alternatives']:
            path.write_bytes(member(alternate)); source,fields=c.object_function(path,alternate['coff_symbol'])
            defs=coff.parse_symbols(member(alternate),c.coff_name)[1]
            definition=next(d for d in defs if d['symbol']==alternate['coff_symbol'])
            if (len(source)!=11 or fields or source!=actual or definition!=alternate['source_definition']
                    or hashlib.sha256(source).hexdigest()!=alternate['source_sha256']
                    or hashlib.sha256(actual).hexdigest()!=alternate['body_sha256']):
                raise ValueError('whole abs/labs source alternatives differ')
        control=m['abs_expression_controls']; probe=ROOT/control['probe']
        if hashlib.sha256(probe.read_bytes()).hexdigest()!=control['probe_sha256']:
            raise ValueError('natural abs alternative source differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*control['profile']],cwd=ROOT,capture_output=True,text=True,check=True)
        for row in control['functions']:
            source,fields=c.object_function(path,row['coff_symbol'])
            if (len(source)!=11 or fields or source!=actual
                    or hashlib.sha256(source).hexdigest()!=row['source_sha256']
                    or hashlib.sha256(actual).hexdigest()!=row['body_sha256']):
                raise ValueError('cold whole ordinary abs expression no longer demonstrates ambiguity')
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-elementary-math-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R128 graph replay failed: '+result.stderr[-1500:])
    print('R129 origins OK: eight complete library primaries / 839 bytes / 38 fields; one existing 24-byte vector cleanup; fourteen independent anchors / 1762 bytes / 43 fields; thirty-five whole data sections / 423 bytes / 32 fields; natural 80-byte layout and 13-byte callback controls; both complete abs/labs and cold ordinary expression alternatives remain pending; retained cold R128 graph; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
