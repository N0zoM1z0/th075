#!/usr/bin/env python3
"""Replay complete R141 exception-frame, unwind, scope and private register-ABI provenance."""
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
CONFIDENCE = 'complete-vendor-exception-frame-unwind-scope-code-data-private-abi-provenance'
LABEL_CONFIDENCE = 'interior-cleanup-in-complete-vendor-exception-frame-primary'
ACCEPTED = {'0x006455D6': ('___FrameUnwindToState', 206),
 '0x006456D4': ('___DestructExceptionObject', 69),
 '0x0064592D': ('?CallCatchBlock@@YAPAXPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAU_CONTEXT@@PBU_s_FuncInfo@@PAXHK@Z',
                452),
 '0x00645AF1': ('?BuildCatchObject@@YAXPAUEHExceptionRecord@@PAXPBU_s_HandlerType@@PBU_s_CatchableType@@@Z',
                380),
 '0x00645C6D': ('___CxxExceptionFilter', 293),
 '0x00645D92': ('?CatchIt@@YAXPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAU_CONTEXT@@PAXPBU_s_FuncInfo@@PBU_s_HandlerType@@PBU_s_CatchableType@@PBU_s_TryBlockMapEntry@@H1E@Z',
                103),
 '0x006464C5': ('?_inconsistency@@YAXXZ', 45),
 '0x00646500': ('__CallSettingFrame@12', 76),
 '0x00640751': ('?_CallMemberFunction0@@YGXPAX0@Z', 7),
 '0x00640A36': ('?_CreateFrameInfo@@YAPAUFrameInfo@@PAU1@PAX@Z', 40),
 '0x00640ACB': ('?_CallCatchBlock2@@YAPAXPAUEHRegistrationNode@@PBU_s_FuncInfo@@PAXHK@Z', 89),
 '0x00640A7F': ('?_FindAndUnlinkFrame@@YAXPAUFrameInfo@@@Z', 76),
 '0x00640A5E': ('?IsExceptionObjectToBeDestroyed@@YAHPAX@Z', 33),
 '0x00640BCE': ('__abnormal_termination', 35),
 '0x0064FF20': ('?_ValidateRead@@YAHPBXI@Z', 28),
 '0x0064FF3C': ('?_ValidateWrite@@YAHPAXI@Z', 28),
 '0x00645719': ('?AdjustPointer@@YAPAXPAXABUPMD@@@Z', 31),
 '0x0064075F': ('?_CallMemberFunction2@@YGXPAX00H@Z', 7),
 '0x00640758': ('?_CallMemberFunction1@@YGXPAX00@Z', 7),
 '0x00640766': ('?_UnwindNestedFrames@@YGXPAUEHRegistrationNode@@PAUEHExceptionRecord@@@Z', 82),
 '0x00640721': ('?_JumpToContinuation@@YGXPAXPAUEHRegistrationNode@@@Z', 48),
 '0x006460BB': ('___InternalCxxFrameHandler', 162),
 '0x00645EB7': ('?FindHandler@@YAXPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAU_CONTEXT@@PAXPBU_s_FuncInfo@@EH1@Z',
                516),
 '0x006409BC': ('?_GetRangeOfTrysToCheck@@YAPBU_s_TryBlockMapEntry@@PBU_s_FuncInfo@@HHPAI1@Z', 122),
 '0x00645DF9': ('?FindHandlerForForeignException@@YAXPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAU_CONTEXT@@PAXPBU_s_FuncInfo@@HH1@Z',
                190),
 '0x00640843': ('?_CallSETranslator@@YAHPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAX2PBU_s_FuncInfo@@H1@Z',
                199),
 '0x0064090A': ('?TranslatorGuardHandler@@YA?AW4_EXCEPTION_DISPOSITION@@PAUEHExceptionRecord@@PAUTranslatorGuardRN@@PAX2@Z',
                178)}
LEDGER_SIZES = {'0x006455D6': 173,
 '0x006456D4': 52,
 '0x0064592D': 332,
 '0x00645AF1': 368,
 '0x00645C6D': 293,
 '0x00645D92': 103,
 '0x006464C5': 45,
 '0x00646500': 76,
 '0x00640751': 7,
 '0x00640A36': 40,
 '0x00640ACB': 89,
 '0x00640A7F': 76,
 '0x00640A5E': 33,
 '0x00640BCE': 35,
 '0x0064FF20': 28,
 '0x0064FF3C': 28,
 '0x00645719': 31,
 '0x0064075F': 7,
 '0x00640758': 7,
 '0x00640766': 82,
 '0x00640721': 43,
 '0x006460BB': 162,
 '0x00645EB7': 516,
 '0x006409BC': 122,
 '0x00645DF9': 190,
 '0x00640843': 199,
 '0x0064090A': 178}
AUXILIARIES = {'0x006455B8': ('?FrameUnwindFilter@@YAHPAU_EXCEPTION_POINTERS@@@Z', 30),
 '0x00640808': ('?CatchGuardHandler@@YA?AW4_EXCEPTION_DISPOSITION@@PAUEHExceptionRecord@@PAUCatchGuardRN@@PAX2@Z',
                59),
 '0x00640B44': ('__unwind_handler', 34)}
LABELS = {'0x00645689': ('0x006455D6', 27, 179, '$L19974'), '0x00645A82': ('0x0064592D', 111, 341, '$L20060')}
ANCHORS = [('0x00645414', '__SEH_prolog', 59, 1244382, 'R117'),
 ('0x00646196', '__getptd', 113, 1724384, 'R120'),
 ('0x0064544F', '__SEH_epilog', 17, 1244382, 'R115'),
 ('0x00646478', '?terminate@@YAXXZ', 53, 411468, 'R125'),
 ('0x00641260', '_memmove', 829, 2177430, 'R025'),
 ('0x0064FF58', '?_ValidateExecute@@YAHP6GHXZ@Z', 24, 661594, 'R125'),
 ('0x00645569',
  '?TypeMatch@@YAHPBU_s_HandlerType@@PBU_s_CatchableType@@PBU_s_ThrowInfo@@@Z',
  79,
  379030,
  'R007'),
 ('0x00640BF1', '__NLG_Notify1', 9, 1210238, 'R117')]
STATE = {(379030, '$T19981', '0x006614E8', 24),
 (379030, '$T20002', '0x00661500', 12),
 (379030, '$T20075', '0x00661530', 24),
 (379030, '$T20094', '0x00661548', 12),
 (411468, '$T18949', '0x006615C0', 12),
 (411468, '?__pInconsistency@@3P6AXXZA', '0x00670140', 4),
 (1236214, '___security_cookie', '0x0066FE30', 4)}
LAYOUT_OBJECTS = [{'symbol': '_ExceptionFrameLayoutProbe',
  'offset': 0,
  'size': 128,
  'storage_span': 128,
  'values': [4,
             4,
             80,
             0,
             4,
             8,
             12,
             16,
             20,
             60,
             8,
             0,
             4,
             716,
             140,
             116,
             124,
             128,
             136,
             4,
             1,
             15,
             0,
             1,
             2,
             3,
             4294967295,
             0,
             1,
             4,
             4,
             4]}]
LAYOUT_HEADERS = {'PlatformSDK/Include/WinBase.h',
 'PlatformSDK/Include/WinNT.h',
 'crt/src/eh.h',
 'crt/src/excpt.h',
 'crt/src/mtdll.h',
 'crt/src/stddef.h'}
FRAME_PROTOCOL = {'exception_record_size': 80,
 'exception_flags_offset': 4,
 'exception_parameter_count_offset': 16,
 'exception_information_offset': 20,
 'exception_pointers_size': 8,
 'thread_size': 140,
 'thread_translator_offset': 116,
 'thread_exception_offset': 124,
 'thread_context_offset': 128,
 'thread_frame_chain_offset': 136,
 'raw_unwind_flag_mask': 102,
 'cpp_exception_code': 3765269347,
 'eh_magic': 429065504,
 'alternate_magic': 429065505,
 'func_info_magic_mask': 536870911,
 'translator_caller_cleanup': 8,
 'call_setting_frame_callee_cleanup': 12,
 'nested_unwind_callee_cleanup': 8,
 'scope_record_size': 12,
 'existing_handler_label_prefix': 6,
 'source_basis': 'Complete pinned COFF definitions/AUX extents, scope source sections and all fields; '
                 'original private frame.cpp/ehdata.h/ehhooks.h/trnsctrl.h unavailable; exsup.inc provides '
                 'real support constants',
 'abi_basis': 'Real SDK/thread headers and independent natural stdcall/member/translator/SEH/C++ models; '
              'private static helpers use observed register contracts, with canonical declarations left '
              'unset',
 'runtime_unknowns': 'Original complete private record identities/layouts, current '
                     'handler/translator/frame/exception state, opaque '
                     'funclet/member/continuation/forward-compatible handler targets and callback outcomes'}
REGISTER_CONTRACTS = {'0x00645AF1': {'incoming': ['ECX copied to ESI', 'EDX copied to EDI', 'EBP+8 and EBP+12 are stack inputs'],
                'basis': 'Private static helper; full local callers/bodies prove register use, not a '
                         'four-stack-argument cdecl prototype'},
 '0x00645719': {'incoming': ['EAX base pointer', 'ECX points to adjustment fields'],
                'basis': 'Private static register ABI; no incomplete PMD record instantiated'},
 '0x00645569': {'incoming': ['ESI and EDI pointer inputs', 'ESP+4 stack input'],
                'basis': 'Retained private optimized type matcher; decoration does not recover actual '
                         'register ABI'},
 '0x006455B8': {'incoming': ['EAX points to exception pointer storage'],
                'basis': 'Complete private filter helper reached from source-defined local filter; no false '
                         'stack-argument prototype'}}
MEMMOVE_REGIONS = [{'offset': 0, 'size': 100},
 {'offset': 112, 'size': 112},
 {'offset': 256, 'size': 76},
 {'offset': 348, 'size': 148},
 {'offset': 508, 'size': 128},
 {'offset': 668, 'size': 76},
 {'offset': 760, 'size': 69}]
THUNKS = [{'address': '0x00654B54',
  'size': 6,
  'iat_slot': '0x00657180',
  'dll': 'KERNEL32.dll',
  'symbol': 'RtlUnwind',
  'origin_evidence': 'R030',
  'body_sha256': '3d85e6c2d8eb4847e98d355d7d355ffc2850fd629ffc1b45bc98775ddd3d9e1d',
  'basis': 'Complete independently accepted compiler linker thunk; imported implementation uncredited'}]
METADATA_DIGESTS = {'scope_tables': '63bc7ef5f6cf0f7de9b5ebd07c3cda6d0cd2a141b7eb0a83ceec605edc549570',
 'call_controls': '91183a1a84091dfe25817107eb202a6e55c19ff01a92214dc5b871df795b317c',
 'probe_generated_data': 'f427fbcc8c33b45b052e6f1dbbc9d1a570e309704b19c6eb06b7ae068fe3e5bc',
 'probe_generated_code': '1ceefc98dc62e2e2908562fac7f8f1db55947d5937349c2b22c2a3a3ef621270',
 'runtime_dispatch': '3511a6c234f5f7cf1d167e0a44e1e741ebc619072aeba668ffb4ea8659d32e0f',
 'extent_reconciliations': 'ef90547bba6f3beffae9cefe22987fdd01d2df887b85e5ed39beea9430e29e6c'}


def metadata_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result

def manifest():
    m = json.loads((ROOT / 'config/exception-frame-origin-evidence.json').read_text())
    identity = module('exception_frame_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R141' or m['target_sha256'] != identity.TARGET:
        raise ValueError('exception-frame target identity differs')
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
            or not any(r['offset']<=entry['source_offset']<r['offset']+r['size'] for r in owner['code_regions'])
            or int(binding['target_address'],16) != int(owner['address'],16) + entry['source_offset']):
        raise ValueError('dispatch code pointer loses its actual defining source owner/entry')

def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(rows) != 27 or len(m['functions']) != 27 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete exception-frame cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != LEDGER_SIZES[key] or row['decision'] != 'library'
                or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'], 16) != int(key, 16) + size - 1):
            raise ValueError('exception-frame function loses complete own AUX extent')
    aux = {r['address']: (r['coff_symbol'], r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies']) != 3 or aux != AUXILIARIES or any(
            r['decision'] != 'library-control' or r['extent_basis'] != 'function-auxiliary-record'
            or r['code_size'] != r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16) != int(r['address'],16) + r['size'] - 1
            for r in m['auxiliary_bodies']):
        raise ValueError('exception-frame auxiliary controls gain invented inventory credit')
    if (len(m['interior_labels']) != 2 or
            {r['address']: (r['parent'], r['size'], r['source_offset'], r['source_symbol'])
             for r in m['interior_labels']} != LABELS or any(
            r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary'
            for r in m['interior_labels'])):
        raise ValueError('exception-frame labels lose complete source parents')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence'])
            for r in m['anchors']] != ANCHORS:
        raise ValueError('exception-frame independent full anchors differ')
    if any(m[k] for k in ('range_markers','initializer_registrations','callback_ranges',
                          'literal_controls','retained_labels','diagnostic_contexts','common_globals',
                          'code_carriers','source_alternatives')):
        raise ValueError('exception-frame graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 7 or sum(r['size'] for r in m['state_data']) != 92 or
            {(r['member_offset'],r['symbol'],r['target_address'],r['size'])
             for r in m['state_data']} != STATE):
        raise ValueError('exception-frame loses complete defining data sections')
    if (m['sdk_layout']['source_section_size'] != 128 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS
            or set(m['sdk_layout']['headers']) != LAYOUT_HEADERS
            or set(m['vendor_sources']) != {'crt/src/exsup.inc'}):
        raise ValueError('exception-frame loses actual SDK or available source context')
    if m['retained_controls'] != [dict(evidence_id='R140',manifest='stream-finalization-origin-evidence.json')]:
        raise ValueError('exception-frame loses full retained independent R140 graph')
    if m['frame_protocol'] != FRAME_PROTOCOL or m['register_contracts'] != REGISTER_CONTRACTS:
        raise ValueError('exception-frame private ABI/SDK facts or unknowns differ')
    if m['retained_thunks'] != THUNKS:
        raise ValueError('exception-frame changes independent compiler thunk ownership')
    for key, digest in METADATA_DIGESTS.items():
        if metadata_digest(m[key]) != digest:
            raise ValueError('exception-frame reviewed complete '+key+' inventory differs')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors']}}
    for row in graph.values():
        if row['coff_symbol'] == '_memmove':
            if row['code_regions'] != MEMMOVE_REGIONS or row['code_size'] != 709:
                raise ValueError('memmove loses seven real code regions')
        elif row['code_regions'] != [dict(offset=0,size=row['size'])] or row['code_size'] != row['size']:
            raise ValueError('exception-frame loses complete code partition')
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind'] == 'import-thunk':
                check_thunk_field(b)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('exception-frame field lacks typed code/data/API provenance')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('exception-frame shared branch loses complete same-section owner')
            elif edge['basis'] not in ('typed-REL32','typed-import-thunk'):
                raise ValueError('exception-frame edge loses actual typed transfer')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('exception-frame defining data loses full typed provenance')
            if b['target_kind'] == 'code-entry':
                check_code_entry(b,graph)
    check_register_protocol(m, graph)
    return rows


def check_thunk_field(binding):
    expected = dict(type='REL32',symbol='_RtlUnwind@16',target_address='0x00654B54',
                    target_kind='import-thunk',dll='KERNEL32.dll',import_name='RtlUnwind',
                    iat_slot='0x00657180',origin_evidence='R030',addend=0,local_symbol_offset=None)
    if any(binding.get(k) != v for k,v in expected.items()) or 'code_entry' in binding:
        raise ValueError('RtlUnwind source field loses actual compiler thunk/IAT identity')


def check_register_protocol(m, graph):
    witnesses = lambda key: {(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    required = {
        '0x00645AF1': {('mov','esi, ecx'),('mov','edi, edx')},
        '0x00645719': {('mov','edx, dword ptr [ecx + 4]'),('mov','eax, dword ptr [ecx]'),('add','eax, esi')},
        '0x00645569': {('mov','eax, dword ptr [esp + 4]')},
        '0x006455B8': {('mov','eax, dword ptr [eax]'),('cmp','dword ptr [eax], 0xe06d7363')},
        '0x00640721': {('jmp','eax'),('pop','ebx'),('leave',''),('ret','8')},
        '0x00640843': {('call','dword ptr [eax + 0x74]'),('pop','ecx')},
        '0x006460BB': {('call','ecx'),('add','esp, 0x20')},
    }
    for key, items in required.items():
        if not items <= witnesses(key):
            raise ValueError('exception-frame loses observed register/stack ABI witness for '+key)
    for key in ('0x00640751','0x00640758','0x0064075F'):
        if ([(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']]
                != [('pop','eax'),('pop','ecx'),('xchg','dword ptr [esp], eax'),('jmp','eax')]
                or graph[key]['body_facts']['returns']):
            raise ValueError('member trampoline loses tail transfer or gains fake return')
    by_site = {w['site']:(w['mnemonic'],w['operands']) for w in graph['0x00640843']['instruction_witnesses']}
    if [by_site.get(k) for k in ('0x006408D8','0x006408D9')] != [('pop','ecx'),('pop','ecx')]:
        raise ValueError('translator loses the actual two-pop caller cleanup')
    special = {'0x00646500':12,'0x00640766':8,'0x00640721':8}
    for row in m['functions']:
        if any(r['cleanup'] != special.get(row['address'],0) for r in row['body_facts']['returns']):
            raise ValueError('exception-frame actual return cleanup differs')
    actual = [dict(owner=r['address'],calls=r['indirect_calls'],jumps=r['indirect_jumps'])
              for r in m['functions']+m['auxiliary_bodies'] if r['indirect_calls'] or r['indirect_jumps']]
    if actual != m['runtime_dispatch']:
        raise ValueError('exception-frame opaque/API runtime dispatch inventory differs')


def check_partition(row, raw, instructions, graph):
    covered = set()
    for region in row['code_regions']:
        offsets = set(range(region['offset'],region['offset']+region['size']))
        if covered & offsets:
            raise ValueError('code partition overlaps')
        covered.update(offsets)
    tables = row.get('embedded_tables',[])
    if row['coff_symbol'] == '_memmove' and (len(tables) != 6 or sum(t['size'] for t in tables) != 120):
        raise ValueError('memmove loses all six complete inline tables')
    if row['coff_symbol'] != '_memmove' and tables:
        raise ValueError('exception-frame gains unsupported inline table')
    starts = {i.address for i in instructions}
    for table in tables:
        d = table['source_definition']
        if (d['symbol'] != table['symbol'] or d['offset'] - row['source_definition']['offset'] != table['offset']
                or d['section'] != row['source_definition']['section']):
            raise ValueError('inline table loses actual defining source label')
        offsets = set(range(table['offset'],table['offset']+table['size']))
        if covered & offsets:
            raise ValueError('inline table is incorrectly decoded as code')
        covered.update(offsets)
        values = struct.unpack('<'+'I'*(table['size']//4),raw[table['offset']:table['offset']+table['size']])
        if ([f'0x{v:08X}' for v in values] != [e['target_address'] for e in table['entries']]
                or any(v not in starts for v in values)
                or [e['offset'] for e in table['entries']] != list(range(table['offset'],table['offset']+table['size'],4))):
            raise ValueError('inline table loses whole real code cases')
        for entry in table['entries']:
            field = next((b for b in row['relocation_bindings'] if b['offset']==entry['offset']),None)
            if (not field or field['type'] != 'DIR32' or field['symbol'] != entry['symbol']
                    or field['target_address'] != entry['target_address']):
                raise ValueError('inline table loses exhaustive source-typed field')
            # Retained anchors keep diagnostic bindings; source entry definitions
            # are still checked against the actual complete code catalog below.
            check_code_entry(dict(symbol=entry['symbol'],target_address=entry['target_address'],
                                  code_entry=entry['code_entry']),graph)
    if covered != set(range(row['size'])):
        raise ValueError('complete source code/data partition omits or pads bytes')


def check_catalog_entry(binding, catalog):
    entry = binding['code_entry']
    if not any(r['owner'] == entry['owner'] and r['member_offset'] == entry['source_member_offset']
               and r['source_offset'] == entry['source_offset'] and r['source_definition'] == entry['source_definition']
               and r['target_address'] == binding['target_address'] and r['source_definition']['symbol'] == binding['symbol']
               for r in catalog):
        raise ValueError('typed code entry is absent from complete actual COFF definitions')


def check_scope_records(scope, data, raw, graph, decoded):
    if (scope['record_size'] != 12 or scope['size'] != data['size']
            or scope['size'] != 12*len(scope['records']) or data['writable']
            or scope['callbacks'] != data['relocations']):
        raise ValueError('scope loses complete readonly whole defining records/fields')
    expected_fields = set()
    for index, record in enumerate(scope['records']):
        enclosing, filter_ptr, handler = struct.unpack_from('<iII',raw,index*12)
        if (record != dict(index=index,enclosing=enclosing,
                           filter=f'0x{filter_ptr:08X}' if filter_ptr else None,handler=f'0x{handler:08X}')
                or not -1 <= enclosing < index or handler == 0):
            raise ValueError('scope record loses actual enclosing/filter/handler topology')
        for field_offset, value in ((index*12+4,filter_ptr),(index*12+8,handler)):
            if not value:
                continue
            expected_fields.add(field_offset)
            field = next((b for b in data['relocations'] if b['offset']==field_offset),None)
            if (not field or field['target_kind'] != 'code-entry'
                    or field['code_entry']['owner'] != scope['owner']
                    or int(field['target_address'],16) != value):
                raise ValueError('scope callback loses actual complete source owner')
            check_code_entry(field,graph)
            if value not in {i.address for i in decoded[scope['owner']]}:
                raise ValueError('scope callback is not an actual whole-parent instruction start')
    if expected_fields != {b['offset'] for b in data['relocations']}:
        raise ValueError('scope omits or fabricates typed callbacks')


def check_probe_generated(data,path,m,comparison,coff,old,decoder,facts):
    definitions = coff.parse_symbols(data,comparison.coff_name)[1]
    count = struct.unpack_from('<H',data,2)[0]
    headers = [struct.unpack_from('<8sIIIIIIHHI',data,20+i*40) for i in range(count)]
    for row in m['probe_generated_data']:
        raw,desc = old.whole_section(data,row['symbol'],comparison,coff)
        if desc != row['source_section'] or hashlib.sha256(raw).hexdigest() != row['source_sha256']:
            raise ValueError('cold natural EH model loses whole generated defining data')
    for row in m['probe_generated_code']:
        entry = next(d for d in definitions if d['symbol']==row['coff_symbol'])
        header = headers[entry['section']-1]
        section_defs = [d for d in definitions if d['section']==entry['section'] and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')]
        if (entry != row['source_definition'] or entry['offset'] != 0 or header[3] != row['size']
                or f'0x{header[9]:08X}' != row['flags'] or section_defs != row['source_definitions']
                or row['extent_basis'] != 'whole-defining-code-section-without-AUX'):
            raise ValueError('cold natural EH carrier loses complete no-AUX defining code section')
        symbol_offset,symbol_count = struct.unpack_from('<II',data,8)
        string_offset = symbol_offset + symbol_count*18
        strings = data[string_offset:string_offset+struct.unpack_from('<I',data,string_offset)[0]]
        index = 0
        auxiliary = None
        while index < symbol_count:
            name,_,_,_,_,aux = struct.unpack_from('<8sIhHBB',data,symbol_offset+index*18)
            if comparison.coff_name(name,strings) == row['coff_symbol']:
                auxiliary = aux
                break
            index += 1+aux
        if auxiliary != 0:
            raise ValueError('cold model EH carrier no-AUX provenance differs')
        raw,fields = comparison.object_function(path,row['coff_symbol'],row['size'])
        ins = list(decoder.disasm(raw,0))
        metadata = [{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
        if (sum(i.size for i in ins) != len(raw) or metadata != row['relocation_metadata']
                or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or facts.body_facts(ins) != row['body_facts']):
            raise ValueError('cold natural EH carrier loses full code/typed metadata')
    # Every initialized model section except the whole SDK layout must appear;
    # this prevents accepting a descriptor prefix while dropping its neighbours.
    expected = {next(d['section'] for d in definitions if d['symbol']==r['symbol'])
                for r in m['probe_generated_data']}
    layout_section = next(d['section'] for d in definitions if d['symbol']=='_ExceptionFrameLayoutProbe')
    actual = {i+1 for i,h in enumerate(headers) if h[3] and h[9]&0x40 and h[9]&0x40000000
              and not h[9]&0x20000000 and h[0].rstrip(b'\0') not in (b'.debug$S',b'.debug$T',b'.debug$F',b'.drectve')}
    if actual != expected | {layout_section}:
        raise ValueError('cold natural EH model loses an entire generated initialized section')


def decode_code(row,raw,address,decoder):
    return [i for region in row['code_regions']
            for i in decoder.disasm(raw[region['offset']:region['offset']+region['size']],address+region['offset'])]

def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('exception-frame function loses its complete own AUX extent')
    return comparison.object_function(path,row['coff_symbol'])

def check_interior_entry(label, parent, definitions, target_ins, source_ins):
    offset=label['source_offset'];base=int(parent['address'],16)
    if int(label['address'],16)!=base+offset or base+offset not in {i.address for i in target_ins}:
        raise ValueError('shared entry loses actual complete-owner instruction start')
    if label['source_symbol'] is not None:
        actual=next((d for d in definitions if d['symbol']==label['source_symbol']
                     and d['section']==parent['source_definition']['section']),None)
        if (actual!=label['source_definition'] or actual is None or actual['storage'] not in (2,3,6)
                or actual['offset']-parent['source_definition']['offset']!=offset):
            raise ValueError('shared entry loses actual full-owner defining source symbol')
    else:
        raise ValueError('exception-frame cleanup gains an invented source entry')
    if parent['source_definition']['offset'] + offset not in {i.address for i in source_ins}:
        raise ValueError('cleanup body label is not an actual source instruction start')
    entry = label['scope_entry_offset']
    if (offset - entry != 6 or base + entry not in {i.address for i in target_ins}
            or label['size'] != parent['size'] - offset):
        raise ValueError('cleanup label loses full parent tail or preceding six-byte scope prologue')

def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'
            or function['calling_convention'] or function['signature']):
        raise ValueError('exception-frame loses complete origin-only extent')
    if (origin['evidence_id'] != 'R141' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('exception-frame canonical complete library acceptance differs')

def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('exception-frame shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R141' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'
            or function['calling_convention'] or function['signature']):
        raise ValueError('exception-frame shared entry gains unsupported standalone/source/exact credit')

def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('exception-frame external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('exception-frame member-local data reference changes its actual defining object')
    return dest

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('exception_frame_old','verify-runtime-error-origins.py')
    c = module('exception_frame_target','compare-coff-function.py')
    archive_reader = module('exception_frame_archive','verify-runtime-origins.py')
    coff = module('exception_frame_coff','coff_data.py')
    startup = module('exception_frame_geometry','verify-startup-dependency-origins.py')
    record = module('exception_frame_ledger','verify-vendor-record-origins.py')
    facts = module('exception_frame_facts','verify-game-lifetime-origins.py')
    imports_module = module('exception_frame_imports','verify-import-origins.py')
    literal = module('exception_frame_scalar','verify-runtime-external-origins.py')
    sections = module('exception_frame_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete exception-frame source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('exception-frame complete primary loses an actual interior candidate')
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
            raise ValueError('exception-frame whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('exception-frame source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('exception-frame state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('exception-frame whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('exception-frame initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('exception-frame complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('exception-frame state loses whole writable target storage')
        else:
            literal.check_scalar(linked,actual,row['size'],target_sections,a)
    for row in m['common_globals']:
        definitions=coff.parse_symbols(member(row),c.coff_name)[1]
        actual=next((d for d in definitions if d['symbol']==row['symbol'] and d['section']==0),None)
        a=int(row['target_address'],16)
        if actual!=row['source_definition'] or actual['offset']!=row['size'] or startup.zero_fill_region(target,a,row['size'])!=row['zero_fill_region']:
            raise ValueError('complete COMMON definition/loader zero-fill differs')
        state_map[(row['member_offset'],row['symbol'])]=a
        global_state.setdefault(row['symbol'],set()).add(a)
    for use in m['state_uses']:
        state_map[(use['member_offset'],use['symbol'])] = resolve_state_reference(use,state_map,global_state)
    decoder = Cs(CS_ARCH_X86,CS_MODE_32); decoder.detail = True
    scratch = ROOT / 'build/origin-exception-frame-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural exception-frame control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned exception-frame control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_ExceptionFrameLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural exception-frame data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural exception/thread SDK offsets or ABI constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete exception-frame vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete exception-frame ABI/SEH/C++ controls differ')
        check_probe_generated(data,path,m,c,coff,old,decoder,facts)
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R140'):
                    raise ValueError('exception-frame retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('exception-frame complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('exception-frame full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            check_partition(row,actual,ins,graph)
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('exception-frame whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('exception-frame complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('exception-frame field lacks member-local/whole strong data provenance')
        for scope in m['scope_tables']:
            data_row = next(r for r in m['state_data'] if r['symbol']==scope['symbol'] and r['member_offset']==scope['member_offset'])
            check_scope_records(scope,data_row,c.pe_bytes_at(target,int(scope['address'],16),scope['size']),graph,decoded)
        for thunk in m['retained_thunks']:
            key = thunk['address']; a = int(key,16); slot = int(thunk['iat_slot'],16)
            body = c.pe_bytes_at(target,a,thunk['size'])
            imports_module.check_thunk(body,slot,imports.get(slot),thunk['dll'],thunk['symbol'])
            if (hashlib.sha256(body).hexdigest()!=thunk['body_sha256'] or origins[key]['origin']!='compiler'
                    or origins[key]['evidence_id']!=thunk['origin_evidence'] or functions[key]['owner']!='compiler'
                    or int(functions[key]['size'])!=6 or functions[key]['source_file'] or functions[key]['match_percent']!='0.00'):
                raise ValueError('retained RtlUnwind compiler thunk changes ownership/extent')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('exception-frame code entry catalog differs from actual complete source definitions')
        bindings = [b for r in m['functions']+m['auxiliary_bodies'] for b in r['relocation_bindings'] if 'code_entry' in b]
        bindings += [b for r in m['state_data'] for b in r['relocations'] if 'code_entry' in b]
        bindings += [dict(symbol=e['symbol'],target_address=e['target_address'],code_entry=e['code_entry'])
                     for r in m['anchors'] for t in r.get('embedded_tables',[]) for e in t['entries']]
        for b in bindings:
            check_catalog_entry(b,observed_catalog)
        for row in m['functions']+m['auxiliary_bodies']:
            a = int(row['address'],16); ins = decoded[row['address']]; starts = {i.address for i in ins}
            edges = {e['site']:e for e in row['direct_edges']}; observed_sites = set()
            # Direct source branches without relocations must retain the same
            # section and actual complete target owner, including shared tails.
            path.write_bytes(member(row)); code,_ = object_code(path,row,c,coff)
            source_ins = {i.address-row['source_definition']['offset']:i for i in decode_code(row,code,row['source_definition']['offset'],decoder)}
            for i in ins:
                if ((i.mnemonic != 'call' and not i.group(CS_GRP_JUMP)) or not i.operands
                        or i.operands[0].type != X86_OP_IMM):
                    continue
                dest = i.operands[0].imm
                if a <= dest < a+row['size']:
                    if dest not in starts:
                        raise ValueError('exception-frame local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('exception-frame direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-import-thunk':
                    field = next((b for b in row['relocation_bindings'] if b['type']=='REL32' and b['offset']==i.address-a+i.imm_offset),None)
                    if not field or field['offset']!=edge['field_offset'] or field['target_address']!=edge['target']:
                        raise ValueError('RtlUnwind direct call loses actual typed source field')
                    check_thunk_field(field)
                    continue
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('exception-frame direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('exception-frame same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('exception-frame shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('exception-frame complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('exception-frame data pointer does not reach a complete actual code entry')
        for label in m['interior_labels']+m['retained_labels']:
            parent = graph[label['parent']]
            path.write_bytes(member(parent))
            defs = coff.parse_symbols(member(parent),c.coff_name)[1]
            source,_=object_code(path,parent,c,coff)
            source_ins=list(decoder.disasm(source,parent['source_definition']['offset']))
            check_interior_entry(label,parent,defs,decoded[parent['address']],source_ins)
            if label['decision']=='retained':
                origin=origins[label['address']];function=functions[label['address']]
                if origin['evidence_id']!=label['origin_evidence'] or origin['origin']!='library' or int(function['size'])!=label['size'] or function['source_file'] or function['match_percent']!='0.00':
                    raise ValueError('retained shared entry gains unsupported new acceptance')
            elif not args.evidence_only:
                check_label(label,functions[label['address']],origins[label['address']],functions,origins,graph)
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-stream-finalization-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R140 graph replay failed: '+result.stderr[-1500:])
    print('R141 origins OK: 27 complete exception-frame/unwind primaries / 3502 bytes / 116 fields; two existing interior labels; three non-inventory auxiliary controls / 123 bytes / four fields; eight full anchors / 1183 bytes / 65 fields, including all six memmove tables; seven whole data sections / 92 bytes / 13 fields including five complete SEH scope tables; five reconciled extents; independent six-byte R030 compiler thunk/IAT; cold 128-byte SDK/thread layout, nine natural ABI/SEH/C++ controls, all seven generated data sections and one complete no-AUX EH code carrier; full retained R140 graph; local origin-only acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
