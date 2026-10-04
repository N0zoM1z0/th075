#!/usr/bin/env python3
"""Replay the bounded R134 output formatting dependency graph."""
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
ACCEPTED = {'0x006404F0': ('_sprintf', 88), '0x00640548': ('__scprintf', 49), '0x0064254D': ('__snprintf', 87), '0x006425C3': ('__vsnprintf', 86), '0x006445C4': ('__output', 2042), '0x00644517': ('_write_char', 51), '0x0064456E': ('_write_string', 55), '0x0064454A': ('_write_multi_char', 36), '0x0064F250': ('_wctomb', 39), '0x0064F1F0': ('___wctomb_mt', 96)}
LEDGER_SIZES = {'0x006404F0': 88, '0x00640548': 49, '0x0064254D': 87, '0x006425C3': 86, '0x006445C4': 2010, '0x00644517': 51, '0x0064456E': 55, '0x0064454A': 36, '0x0064F250': 39, '0x0064F1F0': 96}
AUXILIARIES = {'0x00644DFA': ('__cropzeros', 75), '0x00644DBE': ('__forcdecpt', 60), '0x00644E45': ('__positive', 26)}
LABELS = {}
STATE = {(1398330, '___lconv_static_null', '0x0068E684', 1), (2326218, '??_C@_03BMAOKBAD@Oct?$AA@', '0x00662608', 4), (2326218, '??_C@_02CJNFDJBF@PM?$AA@', '0x00662590', 3), (2326218, '??_C@_04MIEPOIFP@July?$AA@', '0x006625CC', 5), (1308928, '___newctype', '0x006626B0', 1284), (1986670, '___lookuptable', '0x00661230', 89), (2326218, '??_C@_03JPJOFNIA@Nov?$AA@', '0x00662604', 4), (2326218, '??_C@_06JECMNKMI@Friday?$AA@', '0x0066263C', 7), (2326218, '??_C@_03CNMDKL@May?$AA@', '0x0066261C', 4), (2326218, '___lc_time_c', '0x00670808', 184), (2326218, '??_C@_0BE@CKGJFCPC@dddd?0?5MMMM?5dd?0?5yyyy?$AA@', '0x00662570', 20), (2326218, '??_C@_03IOFIKPDN@Thu?$AA@', '0x0066267C', 4), (2326218, '??_C@_08INBOOONO@Saturday?$AA@', '0x00662630', 9), (2326218, '??_C@_03MKABNOCG@Dec?$AA@', '0x00662600', 4), (2326218, '??_C@_03ODNJBKGA@Mar?$AA@', '0x00662624', 4), (2326218, '??_C@_03PDAGKDH@Mon?$AA@', '0x00662688', 4), (1444790, '__clocalestr', '0x0066FF20', 403), (2326218, '??_C@_04CNLMGBGM@June?$AA@', '0x006625D4', 5), (1236214, '___security_cookie', '0x0066FE30', 4), (2326218, '??_C@_08JCCMCCIL@HH?3mm?3ss?$AA@', '0x00662564', 9), (1303626, '__cfltcvt_tab', '0x00670120', 24), (2326218, '??_C@_09DLIGFAKA@Wednesday?$AA@', '0x00662650', 10), (2326218, '??_C@_03JIHJHPIE@Jan?$AA@', '0x0066262C', 4), (2421318, '__real@0000000000000000', '0x0065F4C8', 8), (2326218, '??_C@_03IFJFEIGA@Aug?$AA@', '0x00662610', 4), (1986670, '??_C@_06OJHGLDPL@?$CInull?$CJ?$AA@', '0x0066129C', 7), (2326218, '??_C@_07BAAGCFCM@Tuesday?$AA@', '0x0066265C', 8), (1408564, '___mb_cur_max', '0x00670910', 12), (2326218, '??_C@_03MHOMLAJA@Wed?$AA@', '0x00662680', 4), (2326218, '??_C@_08BPBNCDIB@MM?1dd?1yy?$AA@', '0x00662584', 9), (2326218, '??_C@_08HACCIKIA@Thursday?$AA@', '0x00662644', 9), (2326218, '??_C@_03GGCAPAJC@Sep?$AA@', '0x0066260C', 4), (2326218, '??_C@_03LEOLGMJP@Apr?$AA@', '0x00662620', 4), (2326218, '??_C@_06JLEDEDGH@Monday?$AA@', '0x00662664', 7), (2326218, '??_C@_09BHHEALKD@September?$AA@', '0x006625B8', 10), (2326218, '??_C@_08HCHEGEOA@November?$AA@', '0x006625A4', 9), (2326218, '??_C@_07JJNFCEND@October?$AA@', '0x006625B0', 8), (2326218, '??_C@_03KOEHGMDN@Sun?$AA@', '0x0066268C', 4), (1308928, '__pctype', '0x006708C0', 8), (2326218, '??_C@_03HJBDCHOM@Feb?$AA@', '0x00662628', 4), (2326218, '??_C@_08GNJGEPFN@February?$AA@', '0x006625EC', 9), (2326218, '??_C@_06OOPIFAJ@Sunday?$AA@', '0x0066266C', 7), (1986670, '___nullstring', '0x00670118', 8), (2326218, '??_C@_03FEFJNEK@Sat?$AA@', '0x00662674', 4), (2326218, '??_C@_03LBGABGKK@Jul?$AA@', '0x00662614', 4), (2326218, '??_C@_03IDFGHECI@Jun?$AA@', '0x00662618', 4), (2326218, '??_C@_07CGJPFGJA@January?$AA@', '0x006625F8', 8), (2326218, '??_C@_05HPCKOFNC@March?$AA@', '0x006625E4', 6), (2326218, '??_C@_03NAGEINEP@Tue?$AA@', '0x00662684', 4), (2326218, '??_C@_02DEDBPAFC@AM?$AA@', '0x00662594', 3), (2326218, '??_C@_03IDIOELNC@Fri?$AA@', '0x00662678', 4), (1986670, '??_C@_1O@CEDCILHN@?$AA?$CI?$AAn?$AAu?$AAl?$AAl?$AA?$CJ?$AA?$AA@', '0x0066128C', 14), (1398330, '___lconv_static_decimal', '0x006708C8', 56), (2326218, '??_C@_08EDHMEBNP@December?$AA@', '0x00662598', 9), (2326218, '??_C@_05DMJDNLEJ@April?$AA@', '0x006625DC', 6), (2326218, '??_C@_06LBBHFDDG@August?$AA@', '0x006625C4', 7)}
LAYOUT_OBJECTS = [{'symbol': '_OutputFormatLayoutProbe', 'offset': 0, 'size': 136, 'storage_span': 136, 'values': [4, 4, 4, 2, 1, 2, 8, 8, 4, 8, 32, 0, 4, 8, 12, 16, 20, 24, 28, 66, 2147483647, 8, 8, 24, 4, 4, 4, 8, 0, 2, 4, 514, 512, 42]}]
LAYOUT_HEADERS = {'crt/src/limits.h', 'crt/src/stdarg.h', 'crt/src/stdio.h', 'crt/src/errno.h', 'crt/src/fltintrn.h', 'crt/src/file2.h', 'crt/src/locale.h'}
CALL_CONTROLS = [{'coff_symbol': '_FormatVa64Control', 'size': 53, 'source_sha256': '8e29916bf2c646be3fefb63562a8279097d7265f67e650cb7777dcb4f7e0ba66', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000034', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'sub', 'operands': 'esp, 0xc'}, {'site': '0x00000006', 'mnemonic': 'lea', 'operands': 'eax, [ebp + 0xc]'}, {'site': '0x00000009', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 0xc], eax'}, {'site': '0x0000000C', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp - 0xc]'}, {'site': '0x0000000F', 'mnemonic': 'add', 'operands': 'ecx, 8'}, {'site': '0x00000012', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 0xc], ecx'}, {'site': '0x00000015', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp - 0xc]'}, {'site': '0x00000018', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [edx - 8]'}, {'site': '0x0000001B', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 8], eax'}, {'site': '0x0000001E', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [edx - 4]'}, {'site': '0x00000021', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], ecx'}, {'site': '0x00000024', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 0xc], 0'}, {'site': '0x0000002B', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp - 8]'}, {'site': '0x0000002E', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp - 4]'}, {'site': '0x00000031', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x00000033', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000034', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_FormatFloatCallControl', 'size': 25, 'source_sha256': 'ba3a48653b1d894ea5fcf3d22475891b0cc8b7e08ab3f2bca3715a52dbd77aae', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000018', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'push', 'operands': '0'}, {'site': '0x00000005', 'mnemonic': 'push', 'operands': '6'}, {'site': '0x00000007', 'mnemonic': 'push', 'operands': '0x67'}, {'site': '0x00000009', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x10]'}, {'site': '0x0000000C', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x0000000D', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0xc]'}, {'site': '0x00000010', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000011', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x00000014', 'mnemonic': 'add', 'operands': 'esp, 0x14'}, {'site': '0x00000017', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000018', 'mnemonic': 'ret', 'operands': ''}]}]
VENDOR_SOURCES = {'crt/src/sprintf.c', 'crt/src/vsnprint.c', 'crt/src/snprintf.c', 'crt/src/vsprintf.c', 'crt/src/output.c', 'crt/src/wctomb.c'}
CONFIDENCE = 'complete-vendor-output-format-code-data-dispatch-api-abi-provenance'
LABEL_CONFIDENCE = 'unused-no-new-interior-output-labels'

ANCHORS = [('0x00642800', '_isdigit', 58, 132622, 'R124'), ('0x0064F3E5', '_tolower', 34, 192908, 'R124'), ('0x0064516C', '__cfltcvt', 81, 2421318, 'R124'), ('0x00644E5F', '__fassign', 62, 2421318, 'R124'), ('0x00646196', '__getptd', 113, 1724384, 'R120'), ('0x00642DEB', '___updatetlocinfo', 59, 1444790, 'R123'), ('0x00647F98', '__errno', 9, 280602, 'R120'), ('0x0064057A', '__cfltcvt_init', 56, 2432134, 'R124'), ('0x006443FE', '__flsbuf', 281, 1840654, 'R133'), ('0x00644331', '_malloc', 18, 816374, 'R120'), ('0x00640620', '_strlen', 139, 2200788, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x0064F280', '__aulldvrm', 149, 879402, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00642A61', '_free', 113, 794604, 'R120'), ('0x00640611', '@__security_check_cookie@4', 14, 1230768, 'R120'), ('0x0064FA08', '__fptrap', 9, 1676192, 'R124')]
IO_PROTOCOL = {'file_size': 32, 'string_flag': 66, 'max_string_count': 2147483647, 'va_list_size': 4, 'int64_size': 8, 'double_carrier_size': 8, 'long_double_carrier_size': 8, 'counted_string_size': 8, 'counted_string_buffer_offset': 4, 'lookup_size': 89, 'states': 8, 'classes': 9, 'buffer_size': 512, 'output_code_size': 2010, 'output_extent': 2042, 'output_table_size': 32, 'thread_locale_offset': 100, 'locale_size': 84, 'locale_codepage_offset': 4, 'locale_handle_offset': 12, 'locale_mb_cur_max_offset': 40, 'locale_pctype_offset': 72}

CODE_SIZES = {'0x006404F0': 88, '0x00640548': 49, '0x0064254D': 87, '0x006425C3': 86, '0x006445C4': 2010, '0x00644517': 51, '0x0064456E': 55, '0x0064454A': 36, '0x0064F250': 39, '0x0064F1F0': 96}
LOCALE_OBJECTS = [{'symbol': '_OutputFormatLocaleLayoutProbe', 'offset': 0, 'size': 52, 'storage_span': 52, 'values': [4, 2, 140, 100, 84, 4, 12, 24, 40, 72, 2, 4, 4]}]
LOCALE_HEADERS = {'PlatformSDK/Include/WinNT.h', 'crt/src/mtdll.h', 'crt/src/locale.h', 'PlatformSDK/Include/WinBase.h'}
EMBEDDED_TABLES = [{'offset': 2010, 'size': 32, 'source_symbol': '$L20973', 'source_definition': {'symbol': '$L20973', 'offset': 2010, 'section': 23, 'type': 0, 'storage': 3}, 'field_offsets': [2010, 2014, 2018, 2022, 2026, 2030, 2034, 2038], 'entries': ['0x006447E0', '0x00644650', '0x0064466D', '0x006446B9', '0x006446FA', '0x00644703', '0x00644741', '0x00644822'], 'entry_offsets': [540, 140, 169, 245, 310, 319, 381, 606], 'dispatch_site': '0x00644649', 'guard_sites': ['0x00644638', '0x0064463E', '0x00644643']}]
RUNTIME_DISPATCH = {'symbol': '__cfltcvt_tab', 'address': '0x00670120', 'size': 24, 'initial_stub': '0x0064FA08', 'initializer': '0x0064057A', 'initializer_evidence': 'R124', 'slots': [{'offset': 0, 'symbol': '__cfltcvt', 'target_address': '0x0064516C', 'code_entry': {'owner': '0x0064516C', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__cfltcvt', 'offset': 0, 'section': 28, 'type': 32, 'storage': 2}}}, {'offset': 4, 'symbol': '__cropzeros', 'target_address': '0x00644DFA', 'code_entry': {'owner': '0x00644DFA', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__cropzeros', 'offset': 0, 'section': 5, 'type': 32, 'storage': 2}}}, {'offset': 8, 'symbol': '__fassign', 'target_address': '0x00644E5F', 'code_entry': {'owner': '0x00644E5F', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__fassign', 'offset': 0, 'section': 12, 'type': 32, 'storage': 2}}}, {'offset': 12, 'symbol': '__forcdecpt', 'target_address': '0x00644DBE', 'code_entry': {'owner': '0x00644DBE', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__forcdecpt', 'offset': 0, 'section': 2, 'type': 32, 'storage': 2}}}, {'offset': 16, 'symbol': '__positive', 'target_address': '0x00644E45', 'code_entry': {'owner': '0x00644E45', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__positive', 'offset': 0, 'section': 8, 'type': 32, 'storage': 2}}}, {'offset': 20, 'symbol': '__cfltcvt', 'target_address': '0x0064516C', 'code_entry': {'owner': '0x0064516C', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__cfltcvt', 'offset': 0, 'section': 28, 'type': 32, 'storage': 2}}}], 'used_slot_offsets': [0, 12, 4], 'basis': 'Complete R124 initializer source writes define supported initialized view; image starts with six fatal stubs; current runtime table contents are unknown'}

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/output-format-origin-evidence.json').read_text())
    identity = module('output_format_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R134' or m['target_sha256'] != identity.TARGET:
        raise ValueError('Output-format target identity differs')
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
            or not 0 <= entry['source_offset'] < owner['code_size']
            or int(binding['target_address'],16) != int(owner['address'],16) + entry['source_offset']):
        raise ValueError('dispatch code pointer loses its actual defining source owner/entry')


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(m['functions']) != 10 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete output-format cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != CODE_SIZES[key]
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('output-format function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=3 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('output-format loses complete auxiliary owners')
    if (len(m['interior_labels']) != 0 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('output-format shared entries lose complete source parents or gain standalone credit')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence']) for r in m['anchors']] != ANCHORS:
        raise ValueError('output-format independent complete anchors differ')
    if any(m[k] for k in ('scope_tables',
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('output-format graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 56 or sum(r['size'] for r in m['state_data']) != 2361
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('output-format graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 136 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural output-format operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R133',manifest='stream-buffer-origin-evidence.json')]:
        raise ValueError('output-format loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind']=='embedded-table':
                check_table_reference(b, row)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('output-format graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('output-format shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('output-format direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('output-format table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    return rows


def check_table_reference(binding, row):
    entry=binding['code_entry'];definition=entry['source_definition']
    if (row['address']!='0x006445C4' or binding['offset']!=136 or binding['type']!='DIR32'
            or binding['symbol']!='$L20973' or binding['local_symbol_offset']!=2010
            or binding['addend'] or entry['owner']!=row['address']
            or entry['source_member_offset']!=row['member_offset'] or entry['source_offset']!=2010
            or definition['symbol']!='$L20973' or definition['storage']!=3
            or definition['section']!=row['source_definition']['section']
            or definition['offset']!=row['source_definition']['offset']+2010
            or binding['target_address']!='0x00644D9E'):
        raise ValueError('output dispatch loses actual full same-owner table reference')


def check_parent_protocol(m, graph):
    if m['format_protocol'] != IO_PROTOCOL or m['call_controls'] != CALL_CONTROLS:
        raise ValueError('output FILE/va_list/FP/locale protocol differs')
    if any(m[k] for k in ('interior_labels','retained_labels','diagnostic_contexts','code_carriers',
                          'extent_reconciliations','source_alternatives','common_globals')):
        raise ValueError('output gains unreviewed owners or duplicate origin credit')
    if set(m['vendor_sources'])!=VENDOR_SOURCES:
        raise ValueError('output loses pinned complete vendor sources')
    if (m['locale_layout']['source_section_size']!=52 or m['locale_layout']['objects']!=LOCALE_OBJECTS):
        raise ValueError('output loses complete independent locale layout')
    output=graph['0x006445C4']
    if output.get('embedded_tables')!=EMBEDDED_TABLES:
        raise ValueError('output loses whole own-AUX eight-entry dispatch table')
    for row in m['functions']+m['auxiliary_bodies']:
        if row['address']!='0x006445C4' and row.get('embedded_tables'):
            raise ValueError('output gains an unsupported embedded table')
    fields=[b for b in output['relocation_bindings'] if b['offset']>=2010]
    if (len(fields)!=8 or [b['offset'] for b in fields]!=list(range(2010,2042,4))
            or [b['code_entry']['source_offset'] for b in fields]!=[540,140,169,245,310,319,381,606]
            or any(b['type']!='DIR32' or b['target_kind']!='code-entry'
                   or b['code_entry']['owner']!=output['address'] for b in fields)):
        raise ValueError('output table loses full actual defining case-entry fields')
    refs=[b for b in output['relocation_bindings'] if b['target_kind']=='embedded-table']
    if len(refs)!=1:raise ValueError('output loses its sole typed dispatch reference')
    check_table_reference(refs[0],output)
    for key in ('0x00644517','0x0064454A','0x0064456E'):
        row=graph[key]
        if row['member_offset']!=output['member_offset'] or row['source_definition']['storage']!=3:
            raise ValueError('output helper loses actual complete defining source parent')
    dispatch=m['runtime_dispatch']
    if dispatch!=RUNTIME_DISPATCH:
        raise ValueError('output loses initial FP stubs or complete initialized callback view')
    for slot in dispatch['slots']:
        check_code_entry(slot,graph)
    table=next(r for r in m['state_data'] if r['symbol']=='__cfltcvt_tab')
    if (table['size']!=24 or len(table['relocations'])!=6
            or [b['offset'] for b in table['relocations']]!=list(range(0,24,4))
            or any(b['target_kind']!='code-entry' or b['code_entry']['owner']!='0x0064FA08' for b in table['relocations'])):
        raise ValueError('output FP image table must retain all six fatal stub fields')
    actual_calls=[b['addend'] for b in output['relocation_bindings'] if b['symbol']=='__cfltcvt_tab']
    if actual_calls!=[0,12,4]:raise ValueError('output loses actual three typed FP slots')
    initializer=graph[dispatch['initializer']]
    if initializer['origin_evidence']!='R124':raise ValueError('FP view loses independent complete initializer')
    state=[b for b in initializer['relocation_bindings'] if b['symbol']=='__cfltcvt_tab']
    if (len(state)!=6 or [b['addend'] for b in state]!=list(range(0,24,4))
            or any(b['target_address']!=dispatch['address'] for b in state)):
        raise ValueError('FP view loses actual whole table updates')
    witnesses=lambda key: {(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    expected_writes={('mov','eax, 0x64516c'),('mov','dword ptr [0x670120], eax'),
        ('mov','dword ptr [0x670124], 0x644dfa'),('mov','dword ptr [0x670128], 0x644e5f'),
        ('mov','dword ptr [0x67012c], 0x644dbe'),('mov','dword ptr [0x670130], 0x644e45'),
        ('mov','dword ptr [0x670134], eax')}
    if not expected_writes<=witnesses(dispatch['initializer']):
        raise ValueError('FP view loses actual complete typed callback stores')
    for key in ('0x006404F0','0x00640548','0x0064254D','0x006425C3'):
        if ('mov','dword ptr [ebp - 0x14], 0x42') not in witnesses(key):
            raise ValueError('format wrapper loses actual string FILE flag')
    required={
        '0x006404F0':{('lea','eax, [ebp + 0x10]'),('mov','dword ptr [ebp - 0x1c], 0x7fffffff'),('mov','byte ptr [eax], 0')},
        '0x00640548':{('and','dword ptr [ebp - 0x18], 0'),('and','dword ptr [ebp - 0x20], 0')},
        '0x0064254D':{('lea','eax, [ebp + 0x14]'),('mov','dword ptr [ebp - 0x1c], eax'),('mov','byte ptr [eax], 0')},
        '0x006425C3':{('push','dword ptr [ebp + 0x14]'),('mov','dword ptr [ebp - 0x1c], eax'),('mov','byte ptr [eax], 0')},
        '0x00644517':{('test','byte ptr [ecx + 0xc], 0x40'),('mov','byte ptr [edx], al'),('inc','dword ptr [esi]')},
        '0x0064456E':{('mov','esi, eax'),('mov','ebx, ecx'),('add','dword ptr [esi], eax'),('cmp','dword ptr [esi], -1')},
        '0x0064454A':{('mov','esi, eax'),('mov','al, byte ptr [ebp + 8]'),('cmp','dword ptr [esi], -1')},
        '0x0064F250':{('mov','eax, dword ptr [eax + 0x64]'),('cmp','eax, dword ptr [0x66ff7c]')},
        '0x0064F1F0':{('cmp','dword ptr [eax + 0x14], esi'),('cmp','ax, 0xff'),('push','dword ptr [eax + 0x28]'),('mov','dword ptr [eax], 0x2a')},
    }
    for key,expected in required.items():
        if not expected<=witnesses(key):raise ValueError('output loses varargs/count/helper/locale/wide-conversion witnesses')


def check_output_table(row, actual, instructions):
    if row['address']!='0x006445C4':return
    table=row['embedded_tables'][0];starts={i.address for i in instructions}
    values=[f'0x{x:08X}' for x in struct.unpack('<8I',actual[2010:2042])]
    if values!=table['entries'] or any(int(x,16) not in starts for x in values):
        raise ValueError('whole output table fails actual case instruction starts')
    jump=next(i for i in instructions if i.address==0x644649)
    if (jump.operands[0].type!=X86_OP_MEM or jump.operands[0].mem.base
            or jump.operands[0].mem.index!=X86_REG_EAX or jump.operands[0].mem.scale!=4
            or jump.operands[0].mem.disp!=0x644D9E):
        raise ValueError('output dispatch loses actual full-table addressing')
    fields=[b for b in row['relocation_bindings'] if b['offset']==jump.address-int(row['address'],16)+jump.disp_offset]
    if len(fields)!=1 or fields[0]['target_kind']!='embedded-table':
        raise ValueError('output jump loses actual typed table displacement')
    required={(0x644638,'push','7'),(0x64463D,'pop','ecx'),(0x64463E,'cmp','eax, ecx'),(0x644643,'ja','0x644d75')}
    if not required<={(i.address,i.mnemonic,i.op_str) for i in instructions}:
        raise ValueError('output dispatch loses actual unsigned eight-state guard')


def cold_locale_layout(m, directory, profile, coff, comparison):
    layout=m['locale_layout'];probe=ROOT/layout['probe'];path=directory/'LocaleLayout.obj'
    if (layout['profile']!=profile or hashlib.sha256(probe.read_bytes()).hexdigest()!=layout['probe_sha256']
            or set(layout['headers'])!=LOCALE_HEADERS):
        raise ValueError('locale control source/profile/headers differ')
    for name,digest in layout['headers'].items():
        if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/name).read_bytes()).hexdigest()!=digest:
            raise ValueError('locale control header differs')
    subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
    data=path.read_bytes();defs=coff.parse_symbols(data,comparison.coff_name)[1]
    entry=next(d for d in defs if d['symbol']=='_OutputFormatLocaleLayoutProbe')
    raw,names=coff.readonly_section(data,entry['section'],comparison.coff_name)
    if (len(raw)!=52 or names!=layout['definitions'] or hashlib.sha256(raw).hexdigest()!=layout['source_sha256']
            or list(struct.unpack('<13I',raw))!=LOCALE_OBJECTS[0]['values']):
        raise ValueError('cold complete locale carrier differs')


def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('output-format function loses its complete own AUX extent')
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
        raise ValueError('output-format cleanup gains an invented source entry')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('output-format loses complete origin-only extent')
    if (origin['evidence_id'] != 'R134' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('output-format canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('output-format shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R134' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('output-format shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('output-format external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('output-format member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('output_format_old','verify-runtime-error-origins.py')
    c = module('output_format_target','compare-coff-function.py')
    archive_reader = module('output_format_archive','verify-runtime-origins.py')
    coff = module('output_format_coff','coff_data.py')
    startup = module('output_format_geometry','verify-startup-dependency-origins.py')
    record = module('output_format_ledger','verify-vendor-record-origins.py')
    facts = module('output_format_facts','verify-game-lifetime-origins.py')
    imports_module = module('output_format_imports','verify-import-origins.py')
    literal = module('output_format_scalar','verify-runtime-external-origins.py')
    sections = module('output_format_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete output-format source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('output-format complete primary loses an actual interior candidate')
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
            raise ValueError('output-format whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('output-format source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('output-format state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('output-format whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('output-format initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('output-format complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('output-format state loses whole writable target storage')
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
    scratch = ROOT / 'build/origin-output-format-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural output-format control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned output-format control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_OutputFormatLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural output-format data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural handle/thread/SDK offsets or constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete output-format vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete variadic/int64/FP cdecl controls differ')
        cold_locale_layout(m,Path(temporary),profile,coff,c)
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R133'):
                    raise ValueError('output-format retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('output-format complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('output-format full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = list(decoder.disasm(actual[:row['code_size']],a)); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('output-format whole code instruction/control-flow inventory differs')
            check_output_table(row,actual,ins)
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('output-format complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('output-format field lacks member-local/whole strong data provenance')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('output-format code entry catalog differs from actual complete source definitions')
        for row in m['functions']+m['auxiliary_bodies']:
            a = int(row['address'],16); ins = decoded[row['address']]; starts = {i.address for i in ins}
            edges = {e['site']:e for e in row['direct_edges']}; observed_sites = set()
            # Direct source branches without relocations must retain the same
            # section and actual complete target owner, including shared tails.
            path.write_bytes(member(row)); code,_ = object_code(path,row,c,coff)
            source_ins = {i.address-row['source_definition']['offset']:i for i in decoder.disasm(code[:row['code_size']],row['source_definition']['offset'])}
            for i in ins:
                if ((i.mnemonic != 'call' and not i.group(CS_GRP_JUMP)) or not i.operands
                        or i.operands[0].type != X86_OP_IMM):
                    continue
                dest = i.operands[0].imm
                if a <= dest < a+row['size']:
                    if dest not in starts:
                        raise ValueError('output-format local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('output-format direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('output-format direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('output-format same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('output-format shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('output-format complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('output-format data pointer does not reach a complete actual code entry')
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
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-stream-buffer-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R133 graph replay failed: '+result.stderr[-1500:])
    print('R134 origins OK: ten complete library primaries / 2629 bytes / 50 fields, including full 2042-byte output AUX with 2010 code and eight-entry 32-byte dispatch; three complete auxiliary controls / 161 bytes / five fields; fifteen retained anchors / 1195 bytes / 65 fields; fifty-six whole data sections / 2361 bytes / 68 fields; cold 136-byte format and 52-byte locale layouts, 53-byte variadic int64 and 25-byte PF0 controls; complete initial/initialized six-slot FP views; full retained R133 graph; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
