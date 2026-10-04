#!/usr/bin/env python3
"""Replay the bounded R139 floating conversion and operation dependency graph."""
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
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_REG_EAX

ROOT = Path(__file__).resolve().parents[1]
ACCEPTED = {'0x0064F7F0': ('__atoldbl', 62), '0x00653105': ('___STRINGTOLD', 76), '0x0064E980': ('__floor_default', 211), '0x00643C38': ('__logb', 235), '0x00643D23': ('__nextafter', 675), '0x0064EA53': ('_ldexp', 491)}
LEDGER_SIZES = {'0x0064F7F0': 62, '0x00653105': 76, '0x0064E980': 211, '0x00643C38': 235, '0x00643D23': 675, '0x0064EA53': 491}
AUXILIARIES = {}
LABELS = {}
STATE = {(2915526, '__real@0000000000000000', '0x0065F4C8', 8), (2648162, '__real@3ff0000000000000', '0x00657D00', 8), (1236214, '___security_cookie', '0x0066FE30', 4), (2925530, '__real@0000000000000000', '0x0065F4C8', 8), (2925530, '__real@3ff0000000000000', '0x00657D00', 8), (2915526, '__real@3ff0000000000000', '0x00657D00', 8), (2648162, '_newcw', '0x00670920', 4), (2931994, '__d_inf', '0x00670388', 40)}
LAYOUT_OBJECTS = [{'symbol': '_FloatingOperationLayoutProbe', 'offset': 0, 'size': 108, 'storage_span': 108, 'values': [4, 4, 8, 8, 10, 10, 32, 0, 4, 8, 16, 24, 12, 4, 768, 0, 256, 512, 768, 196608, 65536, 0, 16, 8, 4, 2, 1]}]
LAYOUT_HEADERS = {'crt/src/float.h', 'crt/src/fpieee.h', 'crt/src/math.h'}
CALL_CONTROLS = [{'coff_symbol': '_FloatingUnaryCallControl', 'size': 20, 'source_sha256': 'bdb064d9c5c91c5d8b2b0996cc22e1a7a668bac8dd8ed06f7ec4d7d3b928f640', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000013', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'fld', 'operands': 'qword ptr [ebp + 0xc]'}, {'site': '0x00000006', 'mnemonic': 'sub', 'operands': 'esp, 8'}, {'site': '0x00000009', 'mnemonic': 'fstp', 'operands': 'qword ptr [esp]'}, {'site': '0x0000000C', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x0000000F', 'mnemonic': 'add', 'operands': 'esp, 8'}, {'site': '0x00000012', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000013', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_FloatingBinaryCallControl', 'size': 29, 'source_sha256': '0729475d281945633b851833c34761f5b7943f7ebbb1dda6fb20f2b7bdc4aead', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x0000001C', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'fld', 'operands': 'qword ptr [ebp + 0x14]'}, {'site': '0x00000006', 'mnemonic': 'sub', 'operands': 'esp, 8'}, {'site': '0x00000009', 'mnemonic': 'fstp', 'operands': 'qword ptr [esp]'}, {'site': '0x0000000C', 'mnemonic': 'fld', 'operands': 'qword ptr [ebp + 0xc]'}, {'site': '0x0000000F', 'mnemonic': 'sub', 'operands': 'esp, 8'}, {'site': '0x00000012', 'mnemonic': 'fstp', 'operands': 'qword ptr [esp]'}, {'site': '0x00000015', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x00000018', 'mnemonic': 'add', 'operands': 'esp, 0x10'}, {'site': '0x0000001B', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x0000001C', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_FloatingScaleCallControl', 'size': 24, 'source_sha256': 'f424035eac924659873a0d9c73ff1f8b146a8d2f17440c9dc0894027fc944b29', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000017', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x14]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'fld', 'operands': 'qword ptr [ebp + 0xc]'}, {'site': '0x0000000A', 'mnemonic': 'sub', 'operands': 'esp, 8'}, {'site': '0x0000000D', 'mnemonic': 'fstp', 'operands': 'qword ptr [esp]'}, {'site': '0x00000010', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x00000013', 'mnemonic': 'add', 'operands': 'esp, 0xc'}, {'site': '0x00000016', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000017', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_FloatingOutputCallControl', 'size': 19, 'source_sha256': 'ee7a1fe390def25841af42437ce457fc91951eb51218bc05003e0826d198ffc8', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000012', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x10]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0xc]'}, {'site': '0x0000000A', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000000B', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x0000000E', 'mnemonic': 'add', 'operands': 'esp, 8'}, {'site': '0x00000011', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000012', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_FloatingParseConvertControl', 'size': 88, 'source_sha256': '268034c7da07a317f9dd37ba57f869533463ffbf5a55ef57a0bc7992cf9a30dd', 'relocation_metadata': [{'offset': 7, 'type': 'DIR32', 'symbol': '___security_cookie', 'addend': 0, 'local_symbol_offset': None}, {'offset': 80, 'type': 'REL32', 'symbol': '@__security_check_cookie@4', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000057', 'cleanup': 0}], 'direct_calls': [{'site': '0x0000004F', 'target': '0x00000054'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'sub', 'operands': 'esp, 0x14'}, {'site': '0x00000006', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [0]'}, {'site': '0x0000000B', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], eax'}, {'site': '0x0000000E', 'mnemonic': 'push', 'operands': '0'}, {'site': '0x00000010', 'mnemonic': 'push', 'operands': '0'}, {'site': '0x00000012', 'mnemonic': 'push', 'operands': '0'}, {'site': '0x00000014', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x1c]'}, {'site': '0x00000017', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000018', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0x18]'}, {'site': '0x0000001B', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000001C', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0x14]'}, {'site': '0x0000001F', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x00000020', 'mnemonic': 'lea', 'operands': 'eax, [ebp - 0x10]'}, {'site': '0x00000023', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000024', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x00000027', 'mnemonic': 'add', 'operands': 'esp, 0x1c'}, {'site': '0x0000002A', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 0x14], eax'}, {'site': '0x0000002D', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0x10]'}, {'site': '0x00000030', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000031', 'mnemonic': 'lea', 'operands': 'edx, [ebp - 0x10]'}, {'site': '0x00000034', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x00000035', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 0xc]'}, {'site': '0x00000038', 'mnemonic': 'add', 'operands': 'esp, 8'}, {'site': '0x0000003B', 'mnemonic': 'cmp', 'operands': 'eax, 1'}, {'site': '0x0000003E', 'mnemonic': 'jne', 'operands': '0x49'}, {'site': '0x00000040', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp - 0x14]'}, {'site': '0x00000043', 'mnemonic': 'or', 'operands': 'eax, 2'}, {'site': '0x00000046', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 0x14], eax'}, {'site': '0x00000049', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp - 0x14]'}, {'site': '0x0000004C', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp - 4]'}, {'site': '0x0000004F', 'mnemonic': 'call', 'operands': '0x54'}, {'site': '0x00000054', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x00000056', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000057', 'mnemonic': 'ret', 'operands': ''}]}]
VENDOR_SOURCES = set()
CONFIDENCE = 'complete-vendor-floating-conversion-operation-code-data-abi-provenance'
LABEL_CONFIDENCE = 'unused-no-new-floating-operation-labels'

ANCHORS = [('0x00652CD1', '___strgtold12', 1076, 2454722, 'R124'), ('0x0064F737', '__ld12told', 124, 2436458, 'R007'), ('0x00640611', '@__security_check_cookie@4', 14, 1230768, 'R120'), ('0x006476FE', '__ctrlfp', 36, 2652462, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x006475D0', '__sptype', 91, 2931994, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x0064730F', '__handle_qnan1', 83, 2888292, 'R129'), ('0x0065151B', '__frnd', 17, 2656120, 'R130'), ('0x006473C1', '__except1', 184, 2888292, 'R129'), ('0x0064762B', '__decomp', 188, 2931994, 'R098'), ('0x00647542', '__set_exp', 42, 2931994, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00647479', '__except2', 201, 2888292, 'R130'), ('0x00647362', '__handle_qnan2', 95, 2888292, 'R130'), ('0x00643BDB', '__copysign', 33, 2915526, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG')]
IO_PROTOCOL = {'pointer_size': 4, 'int_size': 4, 'double_size': 8, 'long_double_size': 8, 'sdk_fp80_size': 10, 'parser_storage_span': 12, 'parser_stack_arguments': 7, 'parser_argument_bytes': 28, 'converter_stack_arguments': 2, 'converter_argument_bytes': 8, 'combined_caller_cleanup': 36, 'converter_status_flag': 2, 'converter_flag_trigger': 1, 'raw_x87_control_mask': 65535, 'raw_operation_control': 4927, 'source_basis': 'Pinned complete vendor COFF definitions/AUX extents and every typed relocation; original private math/conversion C sources and typedefs unavailable', 'abi_basis': 'Natural SDK and independent function-pointer models; 12-byte local buffer storage is observed, not a recovered private record typedef; SDK FP80 is ten bytes and C long double is eight', 'runtime_unknowns': 'Original private signedness/type names, current x87 control/status, runtime math error handler, caller values and parser output validity; abstract CRT control macros are distinct from raw x87 words'}

CODE_SIZES = {'0x0064F7F0': 62, '0x00653105': 76, '0x0064E980': 211, '0x00643C38': 235, '0x00643D23': 675, '0x0064EA53': 491}

SEH_SCOPES = []

COMMON_GLOBALS = []
PARSER_REGIONS = [{'offset': 0, 'size': 1028}]
PARSER_TABLES = [{'symbol': '$L1157', 'offset': 1028, 'size': 48, 'source_definition': {'symbol': '$L1157', 'offset': 1028, 'section': 2, 'type': 0, 'storage': 3}, 'entries': [{'offset': 1028, 'symbol': '$L873', 'target_address': '0x00652D3B', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 106, 'source_definition': {'symbol': '$L873', 'offset': 106, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1032, 'symbol': '$L886', 'target_address': '0x00652D8E', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 189, 'source_definition': {'symbol': '$L886', 'offset': 189, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1036, 'symbol': '$L899', 'target_address': '0x00652DEF', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 286, 'source_definition': {'symbol': '$L899', 'offset': 286, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1040, 'symbol': '$L910', 'target_address': '0x00652E1A', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 329, 'source_definition': {'symbol': '$L910', 'offset': 329, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1044, 'symbol': '$L928', 'target_address': '0x00652E55', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 388, 'source_definition': {'symbol': '$L928', 'offset': 388, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1048, 'symbol': '$L947', 'target_address': '0x00652EAD', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 476, 'source_definition': {'symbol': '$L947', 'offset': 476, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1052, 'symbol': '$L952', 'target_address': '0x00652ECD', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 508, 'source_definition': {'symbol': '$L952', 'offset': 508, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1056, 'symbol': '$L969', 'target_address': '0x00652F5A', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 649, 'source_definition': {'symbol': '$L969', 'offset': 649, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1060, 'symbol': '$L963', 'target_address': '0x00652F05', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 564, 'source_definition': {'symbol': '$L963', 'offset': 564, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1064, 'symbol': '$L978', 'target_address': '0x00652FBF', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 750, 'source_definition': {'symbol': '$L978', 'offset': 750, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1068, 'symbol': '$L1113', 'target_address': '0x00652FA7', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 726, 'source_definition': {'symbol': '$L1113', 'offset': 726, 'section': 2, 'type': 0, 'storage': 3}}}, {'offset': 1072, 'symbol': '$L992', 'target_address': '0x00652F77', 'code_entry': {'owner': '0x00652CD1', 'source_member_offset': 2454722, 'source_offset': 678, 'source_definition': {'symbol': '$L992', 'offset': 678, 'section': 2, 'type': 0, 'storage': 3}}}]}]

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/floating-operation-origin-evidence.json').read_text())
    identity = module('floating_operation_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R139' or m['target_sha256'] != identity.TARGET:
        raise ValueError('floating-operation target identity differs')
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
    if len(m['functions']) != 6 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete floating-operation cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != CODE_SIZES[key]
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('floating-operation function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=0 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('floating-operation loses complete auxiliary owners')
    if (len(m['interior_labels']) != 0 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('floating-operation shared entries lose complete source parents or gain standalone credit')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence']) for r in m['anchors']] != ANCHORS:
        raise ValueError('floating-operation independent complete anchors differ')
    if any(m[k] for k in (
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('floating-operation graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 8 or sum(r['size'] for r in m['state_data']) != 88
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('floating-operation graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 108 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural floating-operation operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R138',manifest='locale-snapshot-origin-evidence.json')]:
        raise ValueError('floating-operation loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('floating-operation graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('floating-operation shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('floating-operation direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('floating-operation table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    return rows


def check_parent_protocol(m, graph):
    if m['floating_protocol']!=IO_PROTOCOL or m['call_controls']!=CALL_CONTROLS:
        raise ValueError('floating complete source/storage/layout/ABI controls differ')
    if any(m[k] for k in ('auxiliary_bodies','interior_labels','retained_labels','diagnostic_contexts',
                          'scope_tables','common_globals','code_carriers','extent_reconciliations','source_alternatives')):
        raise ValueError('floating gains unsupported owners/scopes or invented inventory credit')
    if set(m['vendor_sources'])!=VENDOR_SOURCES or set(m['sdk_layout']['headers'])!=LAYOUT_HEADERS:
        raise ValueError('floating changes available source/header context')
    for row in graph.values():
        expected=PARSER_REGIONS if row['address']=='0x00652CD1' else [dict(offset=0,size=row['size'])]
        if row['code_regions']!=expected or row['code_size']!=sum(r['size'] for r in expected):
            raise ValueError('floating loses complete source code/data partition')
        if row['address']!='0x00652CD1' and row.get('embedded_tables'):
            raise ValueError('floating gains unsupported code tables')
    parser=graph['0x00652CD1']
    if parser.get('embedded_tables')!=PARSER_TABLES:
        raise ValueError('floating parser loses complete twelve-entry table owner')
    for table in PARSER_TABLES:
        for entry in table['entries']:check_code_entry(entry,graph)
    if parser['indirect_jumps']!=[dict(site='0x00652D34',operand='dword ptr [eax*4 + 0x6530d5]')]:
        raise ValueError('floating parser loses actual full-table dispatch')
    witnesses=lambda key:{(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    required={
        '0x0064F7F0':{('lea','eax, [ebp - 0x10]'),('lea','eax, [ebp - 0x14]'),('push','1'),('call','0x652cd1'),('call','0x64f737'),('add','esp, 0x24')},
        '0x00653105':{('lea','eax, [ebp - 0x10]'),('push','dword ptr [ebp + 0x14]'),('push','dword ptr [ebp + 0xc]'),('call','0x652cd1'),('call','0x64f737'),('add','esp, 0x24'),('cmp','eax, 1'),('or','esi, 2')},
        '0x0064E980':{('push','dword ptr [0x670920]'),('call','0x6476fe'),('call','0x65151b'),('push','0xb'),('call','0x6473c1')},
        '0x00643C38':{('push','0x133f'),('call','0x6476fe'),('call','0x64762b'),('push','0x25'),('call','0x6473c1')},
        '0x00643D23':{('push','0x133f'),('call','0x64762b'),('call','0x647542'),('add','eax, 0x600'),('add','eax, 0xfffffa00'),('call','0x647479'),('call','0x647362'),('push','0x26')},
        '0x0064EA53':{('push','0x133f'),('call','0x64762b'),('call','0x643bdb'),('call','0x647542'),('cmp','ecx, 0x7fffffff'),('cmp','eax, 0xa00'),('cmp','eax, 0xfffff603'),('call','0x647479'),('push','0x19')},
    }
    for key,expected in required.items():
        if not expected<=witnesses(key):
            raise ValueError('floating loses actual conversion/status/control/decomposition behavior')
    if any(row['indirect_calls'] or row['indirect_jumps'] for row in m['functions']):
        raise ValueError('floating gains unsupported indirect dispatch')
    if any(not row['body_facts']['returns'] or any(r['cleanup']!=0 for r in row['body_facts']['returns']) for row in m['functions']):
        raise ValueError('floating loses observed caller-cleaned returns')


def decode_code(row,raw,address,decoder):
    return [i for region in row['code_regions']
            for i in decoder.disasm(raw[region['offset']:region['offset']+region['size']],address+region['offset'])]


def check_parser_partition(row,actual,instructions):
    if row['address']!='0x00652CD1':return
    base=int(row['address'],16);starts={i.address for i in instructions};fields=row['relocation_bindings']
    selector=next((b for b in fields if b['offset']==102),None)
    if (not selector or selector['type']!='DIR32' or selector['symbol']!='$L1157'
            or selector['local_symbol_offset']!=1028 or selector['target_address']!='0x006530D5'):
        raise ValueError('parser table loses actual source selector field')
    covered=set()
    for region in row['code_regions']:
        covered.update(range(region['offset'],region['offset']+region['size']))
    for table in row['embedded_tables']:
        definition=table['source_definition']
        if (definition['symbol']!=table['symbol'] or definition['offset']!=table['offset']
                or definition['section']!=row['source_definition']['section']):
            raise ValueError('parser table loses actual whole source definition')
        data_offsets=set(range(table['offset'],table['offset']+table['size']))
        if covered&data_offsets:raise ValueError('parser table is incorrectly decoded as code')
        covered.update(data_offsets)
        values=struct.unpack('<'+'I'*(table['size']//4),actual[table['offset']:table['offset']+table['size']])
        if [f'0x{x:08X}' for x in values]!=[e['target_address'] for e in table['entries']] or any(x not in starts for x in values):
            raise ValueError('parser whole table loses actual code case starts')
        if [e['offset'] for e in table['entries']]!=list(range(table['offset'],table['offset']+table['size'],4)):
            raise ValueError('parser table loses exhaustive source entry offsets')
        for entry in table['entries']:
            field=next(b for b in fields if b['offset']==entry['offset'])
            if (field['type']!='DIR32' or field['symbol']!=entry['symbol']
                    or field['target_address']!=entry['target_address']):
                raise ValueError('parser table loses its full source-typed field')
    if covered!=set(range(row['size'])):
        raise ValueError('parser source partition omits or pads complete owner bytes')


def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('floating-operation function loses its complete own AUX extent')
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
        raise ValueError('floating-operation cleanup gains an invented source entry')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('floating-operation loses complete origin-only extent')
    if (origin['evidence_id'] != 'R139' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('floating-operation canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('floating-operation shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R139' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('floating-operation shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('floating-operation external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('floating-operation member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('floating_operation_old','verify-runtime-error-origins.py')
    c = module('floating_operation_target','compare-coff-function.py')
    archive_reader = module('floating_operation_archive','verify-runtime-origins.py')
    coff = module('floating_operation_coff','coff_data.py')
    startup = module('floating_operation_geometry','verify-startup-dependency-origins.py')
    record = module('floating_operation_ledger','verify-vendor-record-origins.py')
    facts = module('floating_operation_facts','verify-game-lifetime-origins.py')
    imports_module = module('floating_operation_imports','verify-import-origins.py')
    literal = module('floating_operation_scalar','verify-runtime-external-origins.py')
    sections = module('floating_operation_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete floating-operation source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('floating-operation complete primary loses an actual interior candidate')
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
            raise ValueError('floating-operation whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('floating-operation source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('floating-operation state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('floating-operation whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('floating-operation initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('floating-operation complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('floating-operation state loses whole writable target storage')
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
    scratch = ROOT / 'build/origin-floating-operation-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural floating-operation control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned floating-operation control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_FloatingOperationLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural floating-operation data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural floating storage/SDK offsets or constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete floating-operation vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete floating function-pointer and parser-storage controls differ')
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R138'):
                    raise ValueError('floating-operation retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('floating-operation complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('floating-operation full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('floating-operation whole code instruction/control-flow inventory differs')
            check_parser_partition(row,actual,ins)
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('floating-operation complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('floating-operation field lacks member-local/whole strong data provenance')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('floating-operation code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('floating-operation local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('floating-operation direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('floating-operation direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('floating-operation same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('floating-operation shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('floating-operation complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('floating-operation data pointer does not reach a complete actual code entry')
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
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-locale-snapshot-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R138 graph replay failed: '+result.stderr[-1500:])
    print('R139 origins OK: six complete floating conversion/operation primaries / 1750 bytes / 52 typed fields; thirteen full anchors / 2184 bytes / 59 fields; eight whole defining data sections / 88 bytes / zero fields; complete 1076-byte parser split into 1028 code bytes and a 48-byte twelve-case table; cold 108-byte SDK layouts and complete 20-/29-/24-/19-/88-byte natural ABI/storage controls; full retained R138 graph; local acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
