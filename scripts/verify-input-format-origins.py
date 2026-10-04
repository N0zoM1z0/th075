#!/usr/bin/env python3
"""Replay the bounded R135 input formatting dependency graph."""
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
ACCEPTED = {'0x00642A2D': ('_sscanf', 52), '0x0064993C': ('__input', 3452), '0x006498FC': ('__inc', 22), '0x006517CE': ('___mbtowc_mt', 192), '0x0065188E': ('_mbtowc', 43), '0x006519EE': ('___getlocaleinfo', 295), '0x0064283A': ('_isxdigit', 63), '0x00642879': ('_isspace', 58), '0x00653B2C': ('___crtGetLocaleInfoW', 304), '0x00653C5C': ('___crtGetLocaleInfoA', 320)}
LEDGER_SIZES = {'0x00642A2D': 52, '0x0064993C': 3452, '0x006498FC': 22, '0x006517CE': 192, '0x0065188E': 43, '0x006519EE': 295, '0x0064283A': 63, '0x00642879': 58, '0x00653B2C': 304, '0x00653C5C': 320}
AUXILIARIES = {'0x00644DFA': ('__cropzeros', 75), '0x00644DBE': ('__forcdecpt', 60), '0x00644E45': ('__positive', 26)}
LABELS = {}
STATE = {(2421318, '__real@0000000000000000', '0x0065F4C8', 8), (2326218, '??_C@_04MIEPOIFP@July?$AA@', '0x006625CC', 5), (2326218, '??_C@_09BHHEALKD@September?$AA@', '0x006625B8', 10), (2326218, '??_C@_02DEDBPAFC@AM?$AA@', '0x00662594', 3), (1265604, '$T20173', '0x00667560', 12), (2326218, '??_C@_03HJBDCHOM@Feb?$AA@', '0x00662628', 4), (2326218, '??_C@_06OOPIFAJ@Sunday?$AA@', '0x0066266C', 7), (2326218, '??_C@_08HCHEGEOA@November?$AA@', '0x006625A4', 9), (2326218, '??_C@_06JECMNKMI@Friday?$AA@', '0x0066263C', 7), (2326218, '??_C@_03ODNJBKGA@Mar?$AA@', '0x00662624', 4), (2326218, '??_C@_08HACCIKIA@Thursday?$AA@', '0x00662644', 9), (2326218, '??_C@_03JPJOFNIA@Nov?$AA@', '0x00662604', 4), (1973972, '$T21139', '0x00662558', 12), (2326218, '??_C@_03IDIOELNC@Fri?$AA@', '0x00662678', 4), (2326218, '??_C@_0BE@CKGJFCPC@dddd?0?5MMMM?5dd?0?5yyyy?$AA@', '0x00662570', 20), (2326218, '___lc_time_c', '0x00670808', 184), (1308928, '___newctype', '0x006626B0', 1284), (1375360, '?wcbuffer@?4??__getlocaleinfo@@9@9', '0x0068E774', 8), (2326218, '??_C@_05HPCKOFNC@March?$AA@', '0x006625E4', 6), (1308928, '__pctype', '0x006708C0', 8), (1398330, '___lconv_static_null', '0x0068E684', 1), (2326218, '??_C@_03IOFIKPDN@Thu?$AA@', '0x0066267C', 4), (1498994, '$T20169', '0x00667550', 12), (2326218, '??_C@_07CGJPFGJA@January?$AA@', '0x006625F8', 8), (2326218, '??_C@_03MHOMLAJA@Wed?$AA@', '0x00662680', 4), (2326218, '??_C@_07JJNFCEND@October?$AA@', '0x006625B0', 8), (1303626, '__cfltcvt_tab', '0x00670120', 24), (2326218, '??_C@_08JCCMCCIL@HH?3mm?3ss?$AA@', '0x00662564', 9), (2326218, '??_C@_08BPBNCDIB@MM?1dd?1yy?$AA@', '0x00662584', 9), (2326218, '??_C@_03KOEHGMDN@Sun?$AA@', '0x0066268C', 4), (2326218, '??_C@_08EDHMEBNP@December?$AA@', '0x00662598', 9), (2326218, '??_C@_03LEOLGMJP@Apr?$AA@', '0x00662620', 4), (2326218, '??_C@_03IDFGHECI@Jun?$AA@', '0x00662618', 4), (1409460, '___lc_handle', '0x0068E6B4', 32), (2326218, '??_C@_02CJNFDJBF@PM?$AA@', '0x00662590', 3), (2326218, '??_C@_03CNMDKL@May?$AA@', '0x0066261C', 4), (2326218, '??_C@_03GGCAPAJC@Sep?$AA@', '0x0066260C', 4), (2326218, '??_C@_03IFJFEIGA@Aug?$AA@', '0x00662610', 4), (2326218, '??_C@_03FEFJNEK@Sat?$AA@', '0x00662674', 4), (2326218, '??_C@_08INBOOONO@Saturday?$AA@', '0x00662630', 9), (2326218, '??_C@_03NAGEINEP@Tue?$AA@', '0x00662684', 4), (2326218, '??_C@_03MKABNOCG@Dec?$AA@', '0x00662600', 4), (2326218, '??_C@_07BAAGCFCM@Tuesday?$AA@', '0x0066265C', 8), (1398330, '___lconv_static_decimal', '0x006708C8', 56), (1444790, '__clocalestr', '0x0066FF20', 403), (2326218, '??_C@_03BMAOKBAD@Oct?$AA@', '0x00662608', 4), (1498994, '?f_use@?1??__crtGetLocaleInfoW@@9@9', '0x0068E794', 4), (2326218, '??_C@_03PDAGKDH@Mon?$AA@', '0x00662688', 4), (1408564, '___mb_cur_max', '0x00670910', 12), (1236214, '___security_cookie', '0x0066FE30', 4), (2326218, '??_C@_09DLIGFAKA@Wednesday?$AA@', '0x00662650', 10), (2326218, '??_C@_04CNLMGBGM@June?$AA@', '0x006625D4', 5), (2326218, '??_C@_05DMJDNLEJ@April?$AA@', '0x006625DC', 6), (2326218, '??_C@_08GNJGEPFN@February?$AA@', '0x006625EC', 9), (2326218, '??_C@_06JLEDEDGH@Monday?$AA@', '0x00662664', 7), (1265604, '?f_use@?1??__crtGetLocaleInfoA@@9@9', '0x0068E798', 4), (2326218, '??_C@_06LBBHFDDG@August?$AA@', '0x006625C4', 7), (2326218, '??_C@_03LBGABGKK@Jul?$AA@', '0x00662614', 4), (2326218, '??_C@_03JIHJHPIE@Jan?$AA@', '0x0066262C', 4)}
LAYOUT_OBJECTS = [{'symbol': '_InputFormatLayoutProbe', 'offset': 0, 'size': 136, 'storage_span': 136, 'values': [4, 4, 4, 2, 1, 2, 4, 8, 32, 0, 4, 8, 12, 16, 20, 24, 28, 73, 4294967295, 32, 8, 8, 128, 32768, 4, 8, 8, 4, 24, 8, 8, 42, 349, 350]}]
LAYOUT_HEADERS = {'crt/src/fltintrn.h', 'crt/src/errno.h', 'crt/src/stdarg.h', 'crt/src/stdio.h', 'crt/src/ctype.h', 'crt/src/stdlib.h', 'crt/src/limits.h'}
CALL_CONTROLS = [{'coff_symbol': '_InputArgumentPointerControl', 'size': 44, 'source_sha256': 'a227945b25eca6c6a080596e117421490f46f354d80ad5caeae447079b390e56', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x0000002B', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'sub', 'operands': 'esp, 8'}, {'site': '0x00000006', 'mnemonic': 'lea', 'operands': 'eax, [ebp + 0x10]'}, {'site': '0x00000009', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], eax'}, {'site': '0x0000000C', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp - 4]'}, {'site': '0x0000000F', 'mnemonic': 'add', 'operands': 'ecx, 4'}, {'site': '0x00000012', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], ecx'}, {'site': '0x00000015', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp - 4]'}, {'site': '0x00000018', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [edx - 4]'}, {'site': '0x0000001B', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 8], eax'}, {'site': '0x0000001E', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], 0'}, {'site': '0x00000025', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp - 8]'}, {'site': '0x00000028', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x0000002A', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x0000002B', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_InputInt64MultiplyControl', 'size': 26, 'source_sha256': 'fc85708e422c7cfdc09568227cd51c5d56d24be9a477fd5dc85719b06dd8a625', 'relocation_metadata': [{'offset': 20, 'type': 'REL32', 'symbol': '__allmul', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000019', 'cleanup': 0}], 'direct_calls': [{'site': '0x00000013', 'target': '0x00000018'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x14]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0x10]'}, {'site': '0x0000000A', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000000B', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0xc]'}, {'site': '0x0000000E', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000000F', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000012', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000013', 'mnemonic': 'call', 'operands': '0x18'}, {'site': '0x00000018', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000019', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_InputFloatAssignControl', 'size': 21, 'source_sha256': '103a695f8b0b07d9df1bb09110a5c509d6c988ef028fdf760b50714e4f2deef2', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000014', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x10]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0xc]'}, {'site': '0x0000000A', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000000B', 'mnemonic': 'push', 'operands': '1'}, {'site': '0x0000000D', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x00000010', 'mnemonic': 'add', 'operands': 'esp, 0xc'}, {'site': '0x00000013', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000014', 'mnemonic': 'ret', 'operands': ''}]}]
VENDOR_SOURCES = {'crt/src/mbtowc.c', 'crt/src/a_loc.c', 'crt/src/sscanf.c', 'crt/src/_ctype.c', 'crt/src/input.c', 'crt/src/w_loc.c', 'crt/src/ctype.c', 'crt/src/inithelp.c', 'crt/src/isctype.c'}
CONFIDENCE = 'complete-vendor-input-format-code-data-seh-nls-api-abi-provenance'
LABEL_CONFIDENCE = 'unused-no-new-interior-input-labels'

ANCHORS = [('0x00640620', '_strlen', 139, 2200788, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00645414', '__SEH_prolog', 59, 1244382, 'R117'), ('0x0064544F', '__SEH_epilog', 17, 1244382, 'R115'), ('0x00642800', '_isdigit', 58, 132622, 'R124'), ('0x0065171D', '__ungetc_lk', 108, 2069764, 'R133'), ('0x00642510', '__chkstk', 61, 1654494, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x006518B9', '__resetstkoflw', 227, 785910, 'R123'), ('0x00644331', '_malloc', 18, 816374, 'R120'), ('0x00640490', '_memset', 96, 2184292, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x006498B0', '__allmul', 52, 871250, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00642A61', '_free', 113, 794604, 'R120'), ('0x00640611', '@__security_check_cookie@4', 14, 1230768, 'R120'), ('0x0065163C', '__filbuf', 225, 1828326, 'R133'), ('0x00647F98', '__errno', 9, 280602, 'R120'), ('0x00646196', '__getptd', 113, 1724384, 'R120'), ('0x00642DEB', '___updatetlocinfo', 59, 1444790, 'R123'), ('0x0064CFF0', '_strncpy', 292, 2207814, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x0064FA08', '__fptrap', 9, 1676192, 'R124'), ('0x0064057A', '__cfltcvt_init', 56, 2432134, 'R124'), ('0x00644E5F', '__fassign', 62, 2421318, 'R124'), ('0x0064516C', '__cfltcvt', 81, 2421318, 'R124'), ('0x0064980B', '___isctype_mt', 119, 166568, 'R123'), ('0x0064F3E5', '_tolower', 34, 192908, 'R124')]
IO_PROTOCOL = {'file_size': 32, 'string_flags': 73, 'va_list_size': 4, 'destination_pointer_size': 4, 'scanset_size': 32, 'scanset_bits': 256, 'float_buffer_size': 350, 'float_width_limit': 349, 'thread_size': 140, 'thread_locale_offset': 100, 'locale_size': 84, 'locale_codepage_offset': 4, 'locale_handle_offset': 12, 'locale_mb_cur_max_offset': 40, 'locale_pctype_offset': 72, 'wide_char_size': 2, 'space_flag': 8, 'hex_flag': 128, 'leadbyte_flag': 32768, 'conversion_flags': 9, 'error_ilseq': 42, 'nls_string_buffer_size': 128, 'nls_integer_buffer_count': 4, 'nls_integer_buffer_size': 8, 'nls_error_insufficient_buffer': 122, 'nls_error_unimplemented': 120}

CODE_SIZES = {'0x00642A2D': 52, '0x0064993C': 3452, '0x006498FC': 22, '0x006517CE': 192, '0x0065188E': 43, '0x006519EE': 295, '0x0064283A': 63, '0x00642879': 58, '0x00653B2C': 304, '0x00653C5C': 320}
LOCALE_OBJECTS = [{'symbol': '_InputLocaleLayoutProbe', 'offset': 0, 'size': 112, 'storage_span': 112, 'values': [4, 2, 140, 100, 84, 4, 12, 24, 40, 72, 2, 4, 4, 4, 4, 4, 1, 8, 9, 42, 1, 0, 122, 120, 1, 1, 8, 128]}]
LOCALE_HEADERS = {'PlatformSDK/Include/WinBase.h', 'crt/src/errno.h', 'PlatformSDK/Include/WinNls.h', 'crt/src/mtdll.h', 'crt/src/awint.h', 'PlatformSDK/Include/WinNT.h', 'crt/src/locale.h', 'crt/src/setlocal.h'}
EMBEDDED_TABLES = []
RUNTIME_DISPATCH = {'symbol': '__cfltcvt_tab', 'address': '0x00670120', 'size': 24, 'initial_stub': '0x0064FA08', 'initializer': '0x0064057A', 'initializer_evidence': 'R124', 'slots': [{'offset': 0, 'symbol': '__cfltcvt', 'target_address': '0x0064516C', 'code_entry': {'owner': '0x0064516C', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__cfltcvt', 'offset': 0, 'section': 28, 'type': 32, 'storage': 2}}}, {'offset': 4, 'symbol': '__cropzeros', 'target_address': '0x00644DFA', 'code_entry': {'owner': '0x00644DFA', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__cropzeros', 'offset': 0, 'section': 5, 'type': 32, 'storage': 2}}}, {'offset': 8, 'symbol': '__fassign', 'target_address': '0x00644E5F', 'code_entry': {'owner': '0x00644E5F', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__fassign', 'offset': 0, 'section': 12, 'type': 32, 'storage': 2}}}, {'offset': 12, 'symbol': '__forcdecpt', 'target_address': '0x00644DBE', 'code_entry': {'owner': '0x00644DBE', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__forcdecpt', 'offset': 0, 'section': 2, 'type': 32, 'storage': 2}}}, {'offset': 16, 'symbol': '__positive', 'target_address': '0x00644E45', 'code_entry': {'owner': '0x00644E45', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__positive', 'offset': 0, 'section': 8, 'type': 32, 'storage': 2}}}, {'offset': 20, 'symbol': '__cfltcvt', 'target_address': '0x0064516C', 'code_entry': {'owner': '0x0064516C', 'source_member_offset': 2421318, 'source_offset': 0, 'source_definition': {'symbol': '__cfltcvt', 'offset': 0, 'section': 28, 'type': 32, 'storage': 2}}}], 'used_slot_offsets': [8], 'basis': 'Complete R124 initializer source writes define supported initialized view; image starts with six fatal stubs; current runtime table contents are unknown'}

SEH_SCOPES = [{'symbol': '$T21139', 'address': '0x00662558', 'size': 12, 'parent': '0x0064993C', 'filter_symbol': '$L21022', 'filter_offset': 1578, 'handler_symbol': '$L21023', 'handler_offset': 1582}, {'symbol': '$T20169', 'address': '0x00667550', 'size': 12, 'parent': '0x00653B2C', 'filter_symbol': '$L20163', 'filter_offset': 184, 'handler_symbol': '$L20164', 'handler_offset': 188}, {'symbol': '$T20173', 'address': '0x00667560', 'size': 12, 'parent': '0x00653C5C', 'filter_symbol': '$L20167', 'filter_offset': 175, 'handler_symbol': '$L20168', 'handler_offset': 179}]
LOCALE_CALL_CONTROLS = [{'coff_symbol': '_InputWideCallControl', 'size': 42, 'source_sha256': 'e9eb3998c2a6a63e2a5d24265c0ad4d2df5756f4696ee7aadab8e7e0ceb16843', 'relocation_metadata': [{'offset': 36, 'type': 'DIR32', 'symbol': '__imp__MultiByteToWideChar@24', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000029', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'xor', 'operands': 'eax, eax'}, {'site': '0x00000005', 'mnemonic': 'cmp', 'operands': 'dword ptr [ebp + 0xc], 0'}, {'site': '0x00000009', 'mnemonic': 'setne', 'operands': 'al'}, {'site': '0x0000000C', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x0000000D', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0xc]'}, {'site': '0x00000010', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000011', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0x14]'}, {'site': '0x00000014', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x00000015', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x10]'}, {'site': '0x00000018', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000019', 'mnemonic': 'push', 'operands': '9'}, {'site': '0x0000001B', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x0000001E', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ecx + 4]'}, {'site': '0x00000021', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x00000022', 'mnemonic': 'call', 'operands': 'dword ptr [0]'}, {'site': '0x00000028', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000029', 'mnemonic': 'ret', 'operands': ''}]}]

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/input-format-origin-evidence.json').read_text())
    identity = module('input_format_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R135' or m['target_sha256'] != identity.TARGET:
        raise ValueError('Input-format target identity differs')
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
        raise ValueError('bounded complete input-format cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != CODE_SIZES[key]
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('input-format function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=3 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('input-format loses complete auxiliary owners')
    if (len(m['interior_labels']) != 0 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('input-format shared entries lose complete source parents or gain standalone credit')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence']) for r in m['anchors']] != ANCHORS:
        raise ValueError('input-format independent complete anchors differ')
    if any(m[k] for k in (
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('input-format graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 59 or sum(r['size'] for r in m['state_data']) != 2327
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('input-format graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 136 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural input-format operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R134',manifest='output-format-origin-evidence.json')]:
        raise ValueError('input-format loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('input-format graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('input-format shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('input-format direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('input-format table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    return rows


def check_parent_protocol(m, graph):
    if (m['input_protocol'] != IO_PROTOCOL or m['call_controls'] != CALL_CONTROLS
            or m['locale_call_controls'] != LOCALE_CALL_CONTROLS):
        raise ValueError('input FILE/pointer-varargs/scanset/FP/locale protocol differs')
    if any(m[k] for k in ('interior_labels','retained_labels','diagnostic_contexts',
                          'code_carriers','extent_reconciliations','source_alternatives','common_globals')):
        raise ValueError('input gains unresolved owners or duplicate origin credit')
    if any(row.get('embedded_tables') for row in graph.values()):
        raise ValueError('input gains an unsupported embedded data extent')
    if set(m['vendor_sources']) != VENDOR_SOURCES:
        raise ValueError('input loses complete defining vendor sources')
    if (m['locale_layout']['source_section_size'] != 112
            or m['locale_layout']['objects'] != LOCALE_OBJECTS):
        raise ValueError('input loses complete natural SDK/thread/locale layout')
    parent=graph['0x0064993C'];helper=graph['0x006498FC']
    if (parent['member_offset'] != helper['member_offset']
            or helper['source_definition']['storage'] != 3):
        raise ValueError('input inc loses its actual source-local defining parent')
    if m['scope_tables'] != SEH_SCOPES:
        raise ValueError('input/NLS lose three complete source-defined SEH scopes')
    for scope in m['scope_tables']:
        data=next(r for r in m['state_data'] if r['symbol']==scope['symbol'])
        fields=data['relocations']
        if (data['size']!=12 or data['target_address']!=scope['address'] or len(fields)!=2
                or [b['offset'] for b in fields]!=[4,8]
                or [b['symbol'] for b in fields]!=[scope['filter_symbol'],scope['handler_symbol']]
                or [b['code_entry']['source_offset'] for b in fields]!=[scope['filter_offset'],scope['handler_offset']]
                or any(b['target_kind']!='code-entry' or b['code_entry']['owner']!=scope['parent'] or b['addend'] for b in fields)):
            raise ValueError('input/NLS scope loses its full actual filter and handler fields')
        for field in fields:check_code_entry(field,graph)
        refs=[b for b in graph[scope['parent']]['relocation_bindings'] if b['symbol']==scope['symbol']]
        if len(refs)!=1 or refs[0]['target_kind']!='state' or refs[0]['target_address']!=scope['address']:
            raise ValueError('input/NLS scope loses actual complete parent reference')
    dispatch=m['runtime_dispatch']
    if dispatch!=RUNTIME_DISPATCH:
        raise ValueError('input loses complete initial/initialized six-slot FP view')
    for slot in dispatch['slots']:check_code_entry(slot,graph)
    table=next(r for r in m['state_data'] if r['symbol']=='__cfltcvt_tab')
    if (table['size']!=24 or len(table['relocations'])!=6
            or [b['offset'] for b in table['relocations']]!=list(range(0,24,4))
            or any(b['target_kind']!='code-entry' or b['code_entry']['owner']!='0x0064FA08' for b in table['relocations'])):
        raise ValueError('input FP image loses six complete fatal-stub fields')
    fp=[b for b in parent['relocation_bindings'] if b['symbol']=='__cfltcvt_tab']
    if len(fp)!=1 or fp[0]['addend']!=8 or fp[0]['target_address']!=dispatch['address']:
        raise ValueError('input loses actual fassign callback slot +8')
    initializer=graph[dispatch['initializer']]
    state=[b for b in initializer['relocation_bindings'] if b['symbol']=='__cfltcvt_tab']
    if (initializer['origin_evidence']!='R124' or len(state)!=6
            or [b['addend'] for b in state]!=list(range(0,24,4))
            or any(b['target_address']!=dispatch['address'] for b in state)):
        raise ValueError('input FP view loses independently reviewed full initializer writes')
    witnesses=lambda key:{(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    expected_writes={('mov','eax, 0x64516c'),('mov','dword ptr [0x670120], eax'),
        ('mov','dword ptr [0x670124], 0x644dfa'),('mov','dword ptr [0x670128], 0x644e5f'),
        ('mov','dword ptr [0x67012c], 0x644dbe'),('mov','dword ptr [0x670130], 0x644e45'),
        ('mov','dword ptr [0x670134], eax')}
    if not expected_writes<=witnesses(dispatch['initializer']):
        raise ValueError('input FP view loses actual six callback stores')
    required={
        '0x00642A2D':{('mov','dword ptr [ebp - 0x14], 0x49'),('lea','eax, [ebp + 0x10]'),('mov','dword ptr [ebp - 0x1c], eax')},
        '0x0064993C':{('push','0x20'),('call','dword ptr [0x670128]'),('cmp','dword ptr [ebp - 0x18c], 0x15d'),('cmp','byte ptr [eax + 1], 0x6e'),('or','eax, 0xffffffff')},
        '0x006498FC':{('dec','dword ptr [edx + 4]'),('movzx','eax, byte ptr [ecx]'),('push','edx')},
        '0x006517CE':{('mov','word ptr [eax], bx'),('test','byte ptr [ecx + eax*2 + 1], 0x80'),('push','9'),('mov','dword ptr [eax], 0x2a')},
        '0x0065188E':{('mov','eax, dword ptr [eax + 0x64]'),('cmp','eax, dword ptr [0x66ff7c]'),('add','esp, 0x10')},
        '0x006519EE':{('push','0x80'),('cmp','eax, 0x7a'),('mov','edi, 0x68e774'),('cmp','edi, 0x68e77c')},
        '0x0064283A':{('push','0x80'),('and','eax, 0x80')},
        '0x00642879':{('push','8'),('and','eax, 8')},
        '0x00653B2C':{('cmp','eax, 0x78'),('mov','dword ptr [0x68e794], 2'),('call','dword ptr [0x65707c]')},
        '0x00653C5C':{('cmp','eax, 0x78'),('mov','dword ptr [0x68e798], 2'),('call','dword ptr [0x657078]')},
    }
    for key,expected in required.items():
        if not expected<=witnesses(key):
            raise ValueError('input loses scan/EOF/private-helper/ctype/locale/NLS behavior witnesses')
    if any(r['body_facts']['returns'][0]['cleanup'] for r in m['functions']):
        raise ValueError('input public/private source changes zero callee cleanup')
    if {r['cleanup'] for r in graph['0x006498B0']['body_facts']['returns']}!={16}:
        raise ValueError('input int64 multiplication loses real helper RET 16')


def check_seh_scopes(m,target,comparison,decoded):
    for scope in m['scope_tables']:
        base=int(scope['parent'],16);flt=base+scope['filter_offset'];handler=base+scope['handler_offset']
        values=struct.unpack('<3I',comparison.pe_bytes_at(target,int(scope['address'],16),12))
        if values!=(0xffffffff,flt,handler):
            raise ValueError('input/NLS actual scope loses full -1/filter/handler record')
        instructions=decoded[scope['parent']]
        filter_body=[(i.mnemonic,i.op_str) for i in instructions if flt<=i.address<handler]
        if filter_body!=[('xor','eax, eax'),('inc','eax'),('ret','')]:
            raise ValueError('input/NLS exception filter loses complete constant-one return')
        entries={i.address:i for i in instructions}
        first=entries[handler];second=entries[handler+first.size]
        if ((first.mnemonic,first.op_str)!=('mov','esp, dword ptr [ebp - 0x18]')
                or (second.mnemonic,second.op_str)!=('call','0x6518b9')):
            raise ValueError('input/NLS handler loses stack restoration and real reset callee')


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
    entry=next(d for d in defs if d['symbol']=='_InputLocaleLayoutProbe')
    raw,names=coff.readonly_section(data,entry['section'],comparison.coff_name)
    if (len(raw)!=112 or names!=layout['definitions'] or hashlib.sha256(raw).hexdigest()!=layout['source_sha256']
            or list(struct.unpack('<28I',raw))!=LOCALE_OBJECTS[0]['values']):
        raise ValueError('cold complete locale carrier differs')

    for control in m['locale_call_controls']:
        source,fields=comparison.object_function(path,control['coff_symbol'])
        decoder=Cs(CS_ARCH_X86,CS_MODE_32);decoder.detail=True;ins=list(decoder.disasm(source,0))
        metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
        facts=module('input_locale_facts','verify-game-lifetime-origins.py')
        if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                or facts.body_facts(ins)!=control['body_facts']
                or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
            raise ValueError('cold complete SDK multibyte call control differs')


def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('input-format function loses its complete own AUX extent')
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
        raise ValueError('input-format cleanup gains an invented source entry')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('input-format loses complete origin-only extent')
    if (origin['evidence_id'] != 'R135' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('input-format canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('input-format shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R135' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('input-format shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('input-format external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('input-format member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('input_format_old','verify-runtime-error-origins.py')
    c = module('input_format_target','compare-coff-function.py')
    archive_reader = module('input_format_archive','verify-runtime-origins.py')
    coff = module('input_format_coff','coff_data.py')
    startup = module('input_format_geometry','verify-startup-dependency-origins.py')
    record = module('input_format_ledger','verify-vendor-record-origins.py')
    facts = module('input_format_facts','verify-game-lifetime-origins.py')
    imports_module = module('input_format_imports','verify-import-origins.py')
    literal = module('input_format_scalar','verify-runtime-external-origins.py')
    sections = module('input_format_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete input-format source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('input-format complete primary loses an actual interior candidate')
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
            raise ValueError('input-format whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('input-format source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('input-format state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('input-format whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('input-format initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('input-format complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('input-format state loses whole writable target storage')
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
    scratch = ROOT / 'build/origin-input-format-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural input-format control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned input-format control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_InputFormatLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural input-format data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural handle/thread/SDK offsets or constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete input-format vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete input pointer-varargs/int64/PF2 controls differ')
        cold_locale_layout(m,Path(temporary),profile,coff,c)
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R134'):
                    raise ValueError('input-format retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('input-format complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('input-format full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = list(decoder.disasm(actual[:row['code_size']],a)); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('input-format whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('input-format complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('input-format field lacks member-local/whole strong data provenance')
        check_seh_scopes(m,target,c,decoded)
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('input-format code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('input-format local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('input-format direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('input-format direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('input-format same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('input-format shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('input-format complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('input-format data pointer does not reach a complete actual code entry')
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
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-output-format-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R134 graph replay failed: '+result.stderr[-1500:])
    print('R135 origins OK: ten complete library primaries / 4801 bytes / 129 typed fields; three complete non-inventoried FP controls / 161 bytes / five fields; twenty-three retained anchors / 2021 bytes / 71 fields; fifty-nine whole data sections / 2327 bytes / 72 fields; three complete SEH scope/filter/handler records; cold 136-byte format and 112-byte SDK/locale layouts, 44-byte pointer-varargs, 26-byte int64 multiply, 21-byte PF2 and 42-byte SDK API controls; six-slot initial/initialized FP view with actual slot +8; full retained R134 graph; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
