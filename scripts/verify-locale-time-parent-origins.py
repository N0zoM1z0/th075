#!/usr/bin/env python3
"""Replay the bounded R137 locale time parent dependency graph."""
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
ACCEPTED = {'0x00642E26': ('__setlocale_get_all', 191), '0x006432D0': ('__setlocale_lk', 473), '0x006434A9': ('_setlocale', 346), '0x0064BCB1': ('__store_winword', 1162), '0x0064C13B': ('__Strftime_mt', 197), '0x0064C200': ('__Strftime', 50), '0x0064BA4B': ('__expandtime', 614)}
LEDGER_SIZES = {'0x00642E26': 191, '0x006432D0': 473, '0x006434A9': 346, '0x0064BCB1': 1162, '0x0064C13B': 197, '0x0064C200': 50, '0x0064BA4B': 614}
AUXILIARIES = {'0x00642C9A': ('___init_dummy', 3), '0x0064CF9A': ('___init_collate', 3), '0x0064C756': ('___init_time', 95)}
LABELS = {'0x006435F2': ('0x006434A9', 9, 329, '$L20503')}
STATE = {(2326218, '??_C@_08EDHMEBNP@December?$AA@', '0x00662598', 9), (1444790, '??_C@_02BALPLPBG@?$DN?$DL?$AA@', '0x0066117C', 3), (2326218, '??_C@_03HJBDCHOM@Feb?$AA@', '0x00662628', 4), (1444790, '??_C@_06NEFDFEKB@LC_ALL?$AA@', '0x00661150', 7), (2326218, '??_C@_03CNMDKL@May?$AA@', '0x0066261C', 4), (2326218, '??_C@_04MIEPOIFP@July?$AA@', '0x006625CC', 5), (2326218, '??_C@_06JLEDEDGH@Monday?$AA@', '0x00662664', 7), (1409460, '___lc_clike', '0x00670900', 4), (1408564, '___mb_cur_max', '0x00670910', 12), (2326218, '??_C@_09DLIGFAKA@Wednesday?$AA@', '0x00662650', 10), (2326218, '??_C@_06JECMNKMI@Friday?$AA@', '0x0066263C', 7), (1398330, '___lconv_static_null', '0x0068E684', 1), (1444790, '??_C@_07LCBHPJJN@LC_TIME?$AA@', '0x00661118', 8), (2326218, '??_C@_03NAGEINEP@Tue?$AA@', '0x00662684', 4), (2326218, '??_C@_03IDFGHECI@Jun?$AA@', '0x00662618', 4), (2326218, '??_C@_08HCHEGEOA@November?$AA@', '0x006625A4', 9), (1444790, '___lc_category', '0x006700B8', 72), (2326218, '??_C@_03LBGABGKK@Jul?$AA@', '0x00662614', 4), (2326218, '??_C@_04CNLMGBGM@June?$AA@', '0x006625D4', 5), (2326218, '??_C@_08GNJGEPFN@February?$AA@', '0x006625EC', 9), (2326218, '??_C@_05HPCKOFNC@March?$AA@', '0x006625E4', 6), (2326218, '??_C@_03IFJFEIGA@Aug?$AA@', '0x00662610', 4), (1378176, '___lconv_intl', '0x0068E68C', 4), (2326218, '??_C@_07JJNFCEND@October?$AA@', '0x006625B0', 8), (2326218, '??_C@_08JCCMCCIL@HH?3mm?3ss?$AA@', '0x00662564', 9), (1409460, '___lc_handle', '0x0068E6B4', 32), (2326218, '??_C@_05JAMEPDIN@am?1pm?$AA@', '0x00662694', 6), (2326218, '??_C@_07BAAGCFCM@Tuesday?$AA@', '0x0066265C', 8), (2326218, '??_C@_08HACCIKIA@Thursday?$AA@', '0x00662644', 9), (2326218, '??_C@_03JIHJHPIE@Jan?$AA@', '0x0066262C', 4), (2326218, '??_C@_03GGCAPAJC@Sep?$AA@', '0x0066260C', 4), (2326218, '??_C@_07CGJPFGJA@January?$AA@', '0x006625F8', 8), (2326218, '??_C@_02CJNFDJBF@PM?$AA@', '0x00662590', 3), (1308928, '__pctype', '0x006708C0', 8), (2326218, '___lc_time_curr', '0x00670800', 4), (2326218, '??_C@_03KOEHGMDN@Sun?$AA@', '0x0066268C', 4), (1444790, '??_C@_0L@DLHIECNL@LC_NUMERIC?$AA@', '0x00661120', 11), (2326218, '??_C@_03FEFJNEK@Sat?$AA@', '0x00662674', 4), (2326218, '??_C@_09BHHEALKD@September?$AA@', '0x006625B8', 10), (1444790, '__clocalestr', '0x0066FF20', 403), (1398330, '___lconv_static_decimal', '0x006708C8', 56), (1308928, '___newctype', '0x006626B0', 1284), (2326218, '??_C@_03EBAPMIKO@a?1p?$AA@', '0x00662690', 4), (1444790, '??_C@_01ICJEACDI@?$DL?$AA@', '0x00661174', 2), (2326218, '___lc_time_c', '0x00670808', 184), (1444790, '??_C@_01NEMOKFLO@?$DN?$AA@', '0x00661178', 2), (1389094, '___lc_time_intl', '0x0068E688', 4), (2326218, '??_C@_08INBOOONO@Saturday?$AA@', '0x00662630', 9), (1236214, '___security_cookie', '0x0066FE30', 4), (2326218, '$T20935', '0x006626A0', 12), (2326218, '??_C@_03MHOMLAJA@Wed?$AA@', '0x00662680', 4), (2326218, '??_C@_0BE@CKGJFCPC@dddd?0?5MMMM?5dd?0?5yyyy?$AA@', '0x00662570', 20), (1444790, '??_C@_0M@MIENIKLA@LC_MONETARY?$AA@', '0x0066112C', 12), (2326218, '??_C@_05DMJDNLEJ@April?$AA@', '0x006625DC', 6), (2326218, '??_C@_02DEDBPAFC@AM?$AA@', '0x00662594', 3), (2326218, '??_C@_03LEOLGMJP@Apr?$AA@', '0x00662620', 4), (1444790, '??_C@_0L@KFJHEKIK@LC_COLLATE?$AA@', '0x00661144', 11), (2326218, '??_C@_06OOPIFAJ@Sunday?$AA@', '0x0066266C', 7), (2326218, '??_C@_03PDAGKDH@Mon?$AA@', '0x00662688', 4), (2326218, '??_C@_03JPJOFNIA@Nov?$AA@', '0x00662604', 4), (2326218, '??_C@_03ODNJBKGA@Mar?$AA@', '0x00662624', 4), (2326218, '??_C@_03IDIOELNC@Fri?$AA@', '0x00662678', 4), (1444790, '$T20508', '0x00661180', 12), (1444790, '??_C@_08EADHIDAD@LC_CTYPE?$AA@', '0x00661138', 9), (2326218, '??_C@_03MKABNOCG@Dec?$AA@', '0x00662600', 4), (2354040, '__timezone', '0x006703C8', 152), (2326218, '??_C@_06LBBHFDDG@August?$AA@', '0x006625C4', 7), (2326218, '??_C@_03IOFIKPDN@Thu?$AA@', '0x0066267C', 4), (2326218, '??_C@_08BPBNCDIB@MM?1dd?1yy?$AA@', '0x00662584', 9), (2326218, '??_C@_03BMAOKBAD@Oct?$AA@', '0x00662608', 4)}
LAYOUT_OBJECTS = [{'symbol': '_LocaleTimeParentLayoutProbe', 'offset': 0, 'size': 260, 'storage_span': 260, 'values': [4, 4, 4, 4, 2, 36, 0, 4, 8, 12, 16, 20, 24, 28, 32, 16, 0, 2, 4, 6, 8, 10, 12, 14, 84, 0, 4, 8, 12, 24, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 140, 100, 184, 0, 28, 56, 104, 152, 160, 164, 168, 172, 176, 180, 0, 5, 0, 131, 12, 0, 1, 2, 1]}]
LAYOUT_HEADERS = {'crt/src/locale.h', 'crt/src/time.h', 'crt/src/mtdll.h', 'PlatformSDK/Include/WinNT.h', 'PlatformSDK/Include/WinBase.h', 'crt/src/setlocal.h', 'PlatformSDK/Include/WinNls.h'}
CALL_CONTROLS = [{'coff_symbol': '_LocaleParentCallControl', 'size': 19, 'source_sha256': 'ee7a1fe390def25841af42437ce457fc91951eb51218bc05003e0826d198ffc8', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000012', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x10]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0xc]'}, {'site': '0x0000000A', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000000B', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x0000000E', 'mnemonic': 'add', 'operands': 'esp, 8'}, {'site': '0x00000011', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000012', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_TimeFormatCallControl', 'size': 35, 'source_sha256': 'f48d57236525f490b4c171115bacf0c0ddab147ed1515caaebaa0e6cb9ed3d5c', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000022', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x20]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0x1c]'}, {'site': '0x0000000A', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000000B', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0x18]'}, {'site': '0x0000000E', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000000F', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x14]'}, {'site': '0x00000012', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000013', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0x10]'}, {'site': '0x00000016', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000017', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0xc]'}, {'site': '0x0000001A', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000001B', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x0000001E', 'mnemonic': 'add', 'operands': 'esp, 0x18'}, {'site': '0x00000021', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000022', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_TimeExpandCallControl', 'size': 39, 'source_sha256': '8cca1c349f63c06f16bc5d90edacb449648d9269e088051132c28f0a4832c720', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000026', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x24]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0x20]'}, {'site': '0x0000000A', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000000B', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0x1c]'}, {'site': '0x0000000E', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000000F', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x18]'}, {'site': '0x00000012', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000013', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0x14]'}, {'site': '0x00000016', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000017', 'mnemonic': 'mov', 'operands': 'dl, byte ptr [ebp + 0x10]'}, {'site': '0x0000001A', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000001B', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0xc]'}, {'site': '0x0000001E', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x0000001F', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x00000022', 'mnemonic': 'add', 'operands': 'esp, 0x1c'}, {'site': '0x00000025', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000026', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_TimeApiCallControl', 'size': 66, 'source_sha256': 'e5d5f1a8491323b2e3ce4a70be7f264edc5446444996fafb6312601df19af5fe', 'relocation_metadata': [{'offset': 13, 'type': 'DIR32', 'symbol': '__imp__GetTimeFormatA@24', 'addend': 0, 'local_symbol_offset': None}, {'offset': 24, 'type': 'DIR32', 'symbol': '__imp__GetDateFormatA@24', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000041', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'sub', 'operands': 'esp, 8'}, {'site': '0x00000006', 'mnemonic': 'cmp', 'operands': 'dword ptr [ebp + 8], 2'}, {'site': '0x0000000A', 'mnemonic': 'jne', 'operands': '0x16'}, {'site': '0x0000000C', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [0]'}, {'site': '0x00000011', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 8], eax'}, {'site': '0x00000014', 'mnemonic': 'jmp', 'operands': '0x1f'}, {'site': '0x00000016', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [0]'}, {'site': '0x0000001C', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 8], ecx'}, {'site': '0x0000001F', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp - 8]'}, {'site': '0x00000022', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], edx'}, {'site': '0x00000025', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x1c]'}, {'site': '0x00000028', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000029', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0x18]'}, {'site': '0x0000002C', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000002D', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0x14]'}, {'site': '0x00000030', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x00000031', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x10]'}, {'site': '0x00000034', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000035', 'mnemonic': 'push', 'operands': '0'}, {'site': '0x00000037', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0xc]'}, {'site': '0x0000003A', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000003B', 'mnemonic': 'call', 'operands': 'dword ptr [ebp - 4]'}, {'site': '0x0000003E', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x00000040', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000041', 'mnemonic': 'ret', 'operands': ''}]}]
VENDOR_SOURCES = {'crt/src/strftime.c', 'crt/src/setlocal.c'}
CONFIDENCE = 'complete-vendor-locale-time-parent-code-data-seh-api-abi-provenance'
LABEL_CONFIDENCE = 'complete-source-defined-finally-in-reviewed-locale-parent'

ANCHORS = [('0x00644331', '_malloc', 18, 816374, 'R120'), ('0x00642C9D', '__strcats', 36, 1444790, 'R007'), ('0x00641B90', '_strcat', 232, 2186124, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x006416B0', '_strcmp', 136, 2192172, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00642A61', '_free', 113, 794604, 'R120'), ('0x00643041', '__setlocale_set_cat', 655, 1444790, 'R136'), ('0x0064DBD0', '_strpbrk', 64, 2216870, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00641DE0', '_strncmp', 57, 2206258, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00640620', '_strlen', 139, 2200788, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x0064CFA0', '_strcspn', 70, 2194042, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x0064CFF0', '_strncpy', 292, 2207814, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00640611', '@__security_check_cookie@4', 14, 1230768, 'R120'), ('0x00642EE5', '__expandlocale', 348, 1444790, 'R136'), ('0x00645414', '__SEH_prolog', 59, 1244382, 'R117'), ('0x00646725', '__lock', 49, 1698134, 'R120'), ('0x00640B66', '__local_unwind2', 104, 1210238, 'R025'), ('0x00642B09', '___freetlocinfo', 208, 1444790, 'R122'), ('0x00642BD9', '___updatetlocinfo_lk', 193, 1444790, 'R123'), ('0x00646658', '__unlock', 21, 1698134, 'R118'), ('0x0064544F', '__SEH_epilog', 17, 1244382, 'R115'), ('0x00642510', '__chkstk', 61, 1654494, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x006518B9', '__resetstkoflw', 227, 785910, 'R123'), ('0x006519A0', '___ascii_stricmp', 78, 2197148, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00646196', '__getptd', 113, 1724384, 'R120'), ('0x00642DEB', '___updatetlocinfo', 59, 1444790, 'R123'), ('0x0064B9D2', '__store_num', 121, 2326218, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00647D5F', '___tzset', 76, 2355650, 'R131'), ('0x0064B97C', '__store_str', 32, 2326218, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x0064CD5F', '___init_ctype', 490, 1369054, 'R136'), ('0x0064CB20', '___init_monetary', 575, 1378176, 'R136'), ('0x0064C847', '___init_numeric', 461, 1383738, 'R136'), ('0x00644343', '_calloc', 187, 788256, 'R120'), ('0x0064C25F', '__get_lc_time', 871, 1389094, 'R136'), ('0x0064C5C6', '___free_lc_time', 400, 1389094, 'R122')]
IO_PROTOCOL = {'category_size': 12, 'category_entries': 6, 'category_array_size': 72, 'thread_locale_size': 84, 'thread_size': 140, 'thread_locale_offset': 100, 'locale_cache_capacity': 131, 'lock': 12, 'tm_size': 36, 'systemtime_size': 16, 'time_locale_size': 184, 'time_refcount_offset': 180, 'format_arguments': 6, 'format_caller_cleanup': 24, 'expand_arguments': 7, 'expand_caller_cleanup': 28, 'sdk_format_arguments': 6, 'sdk_format_callee_cleanup': 24, 'short_date': 0, 'long_date': 1, 'clock': 2, 'year_bias': 1900, 'month_bias': 1, 'calendar_gregorian': 1}

CODE_SIZES = {'0x00642E26': 191, '0x006432D0': 473, '0x006434A9': 346, '0x0064BCB1': 1162, '0x0064C13B': 197, '0x0064C200': 50, '0x0064BA4B': 614}

SEH_SCOPES = [{'symbol': '$T20508', 'address': '0x00661180', 'size': 12, 'parent': '0x006434A9', 'filter_offset': None, 'handler_offset': 329, 'kind': 'finally', 'lock': 12, 'cleanup': '0x00646658'}, {'symbol': '$T20935', 'address': '0x006626A0', 'size': 12, 'parent': '0x0064BCB1', 'filter_offset': 211, 'handler_offset': 215, 'kind': 'except', 'cleanup': '0x006518B9'}]

COMMON_GLOBALS = [{'member_offset': 1378176, 'member': 'build\\intel\\mt_obj\\initmon.obj', 'member_sha256': '883d0635b5d21a0dc1a68fc1860aa5b9d453f296d7a4972b04f3b06ca1aec4bf', 'symbol': '___lconv_intl_refcount', 'target_address': '0x0068FA50', 'size': 4, 'source_definition': {'symbol': '___lconv_intl_refcount', 'offset': 4, 'section': 0, 'type': 0, 'storage': 2}, 'zero_fill_region': {'section': '.data', 'base': '0x0066C000', 'raw_size': 24576, 'virtual_size': 146376, 'flags': '0xC0000040'}}, {'member_offset': 1383738, 'member': 'build\\intel\\mt_obj\\initnum.obj', 'member_sha256': '2795eb04ba1543675fe995c81465fd3ec482144c083b014ce0a22caad65bbca2', 'symbol': '___lconv_num_refcount', 'target_address': '0x0068FA54', 'size': 4, 'source_definition': {'symbol': '___lconv_num_refcount', 'offset': 4, 'section': 0, 'type': 0, 'storage': 2}, 'zero_fill_region': {'section': '.data', 'base': '0x0066C000', 'raw_size': 24576, 'virtual_size': 146376, 'flags': '0xC0000040'}}, {'member_offset': 1378176, 'member': 'build\\intel\\mt_obj\\initmon.obj', 'member_sha256': '883d0635b5d21a0dc1a68fc1860aa5b9d453f296d7a4972b04f3b06ca1aec4bf', 'symbol': '___lconv_mon_refcount', 'target_address': '0x0068FA4C', 'size': 4, 'source_definition': {'symbol': '___lconv_mon_refcount', 'offset': 4, 'section': 0, 'type': 0, 'storage': 2}, 'zero_fill_region': {'section': '.data', 'base': '0x0066C000', 'raw_size': 24576, 'virtual_size': 146376, 'flags': '0xC0000040'}}, {'member_offset': 1369054, 'member': 'build\\intel\\mt_obj\\initctyp.obj', 'member_sha256': '7abd883fbeb516b8f64bdda31e272d2400083c994ac7c299f221bc92b76103ac', 'symbol': '___ctype1_refcount', 'target_address': '0x0068FA48', 'size': 4, 'source_definition': {'symbol': '___ctype1_refcount', 'offset': 4, 'section': 0, 'type': 0, 'storage': 2}, 'zero_fill_region': {'section': '.data', 'base': '0x0066C000', 'raw_size': 24576, 'virtual_size': 146376, 'flags': '0xC0000040'}}, {'member_offset': 1369054, 'member': 'build\\intel\\mt_obj\\initctyp.obj', 'member_sha256': '7abd883fbeb516b8f64bdda31e272d2400083c994ac7c299f221bc92b76103ac', 'symbol': '___ctype1', 'target_address': '0x0068FA44', 'size': 4, 'source_definition': {'symbol': '___ctype1', 'offset': 4, 'section': 0, 'type': 0, 'storage': 2}, 'zero_fill_region': {'section': '.data', 'base': '0x0066C000', 'raw_size': 24576, 'virtual_size': 146376, 'flags': '0xC0000040'}}]
CATEGORY_DISPATCH = {'address': '0x006700B8', 'size': 72, 'stride': 12, 'entries': [{'index': 0, 'offset': 8, 'symbol': '___init_dummy', 'target_address': '0x00642C9A', 'code_entry': {'owner': '0x00642C9A', 'source_member_offset': 1444790, 'source_offset': 0, 'source_definition': {'symbol': '___init_dummy', 'offset': 0, 'section': 24, 'type': 32, 'storage': 2}}}, {'index': 1, 'offset': 20, 'symbol': '___init_collate', 'target_address': '0x0064CF9A', 'code_entry': {'owner': '0x0064CF9A', 'source_member_offset': 1363154, 'source_offset': 0, 'source_definition': {'symbol': '___init_collate', 'offset': 0, 'section': 2, 'type': 32, 'storage': 2}}}, {'index': 2, 'offset': 32, 'symbol': '___init_ctype', 'target_address': '0x0064CD5F', 'code_entry': {'owner': '0x0064CD5F', 'source_member_offset': 1369054, 'source_offset': 0, 'source_definition': {'symbol': '___init_ctype', 'offset': 0, 'section': 2, 'type': 32, 'storage': 2}}}, {'index': 3, 'offset': 44, 'symbol': '___init_monetary', 'target_address': '0x0064CB20', 'code_entry': {'owner': '0x0064CB20', 'source_member_offset': 1378176, 'source_offset': 0, 'source_definition': {'symbol': '___init_monetary', 'offset': 0, 'section': 9, 'type': 32, 'storage': 2}}}, {'index': 4, 'offset': 56, 'symbol': '___init_numeric', 'target_address': '0x0064C847', 'code_entry': {'owner': '0x0064C847', 'source_member_offset': 1383738, 'source_offset': 0, 'source_definition': {'symbol': '___init_numeric', 'offset': 0, 'section': 8, 'type': 32, 'storage': 2}}}, {'index': 5, 'offset': 68, 'symbol': '___init_time', 'target_address': '0x0064C756', 'code_entry': {'owner': '0x0064C756', 'source_member_offset': 1389094, 'source_offset': 0, 'source_definition': {'symbol': '___init_time', 'offset': 0, 'section': 8, 'type': 32, 'storage': 2}}}], 'call_site': '0x0064326A', 'operand': 'dword ptr [ebx + 0x6700c0]', 'basis': 'Complete six-record defining source table; source-local category helper invokes selected initializer; LC_ALL dummy is source-defined and documented unused; current runtime categories unknown'}

FORMAT_DISPATCH = {'owner': '0x0064BCB1', 'field_operand': 'dword ptr [ebp + 0xc]', 'clock_value': 2, 'date_iat': '0x0065714C', 'date_import': 'GetDateFormatA', 'time_iat': '0x00657150', 'time_import': 'GetTimeFormatA', 'slot_operand': 'dword ptr [ebp - 0x30]', 'calls': [{'site': '0x0064BD58', 'operand': 'eax', 'kind': 'capacity'}, {'site': '0x0064BDCD', 'operand': 'dword ptr [ebp - 0x30]', 'kind': 'output'}], 'basis': 'Full source chooses raw date/time API by field, sizes then formats through actual selected stack slot; runtime calendar, locale, pointer and API results unknown'}

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/locale-time-parent-origin-evidence.json').read_text())
    identity = module('locale_time_parent_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R137' or m['target_sha256'] != identity.TARGET:
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
            or not any(r['offset']<=entry['source_offset']<r['offset']+r['size'] for r in owner['code_regions'])
            or int(binding['target_address'],16) != int(owner['address'],16) + entry['source_offset']):
        raise ValueError('dispatch code pointer loses its actual defining source owner/entry')


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(m['functions']) != 7 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete locale-time-parent cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != CODE_SIZES[key]
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('locale-time-parent function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=3 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('locale-time-parent loses complete auxiliary owners')
    if (len(m['interior_labels']) != 1 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('locale-time-parent shared entries lose complete source parents or gain standalone credit')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence']) for r in m['anchors']] != ANCHORS:
        raise ValueError('locale-time-parent independent complete anchors differ')
    if any(m[k] for k in (
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('locale-time-parent graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 70 or sum(r['size'] for r in m['state_data']) != 2582
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('locale-time-parent graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 260 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural locale-time-parent operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R136',manifest='locale-construction-origin-evidence.json')]:
        raise ValueError('locale-time-parent loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('locale-time-parent graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('locale-time-parent shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('locale-time-parent direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('locale-time-parent table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    return rows


def check_parent_protocol(m, graph):
    if m['locale_parent_protocol']!=IO_PROTOCOL or m['call_controls']!=CALL_CONTROLS:
        raise ValueError('locale/time complete layouts and cdecl/stdcall protocol differ')
    if any(m[k] for k in ('retained_labels','diagnostic_contexts','code_carriers',
                          'extent_reconciliations','source_alternatives')):
        raise ValueError('locale/time gains unresolved owners or invented standalone credit')
    if set(m['vendor_sources'])!=VENDOR_SOURCES or set(m['sdk_layout']['headers'])!=LAYOUT_HEADERS:
        raise ValueError('locale/time loses complete defining source/header context')
    if m['common_globals']!=COMMON_GLOBALS:
        raise ValueError('locale/time loses five complete defining COMMON declarations')
    for row in graph.values():
        if row['code_regions']!=[dict(offset=0,size=row['size'])] or row['code_size']!=row['size'] or row.get('embedded_tables'):
            raise ValueError('locale/time loses complete executable source owner or invents code tables')
    if m['category_dispatch']!=CATEGORY_DISPATCH:
        raise ValueError('locale/time loses independently accepted six-record category graph')
    category=next(r for r in m['state_data'] if r['symbol']=='___lc_category')
    fields=[b for b in category['relocations'] if b['target_kind']=='code-entry']
    if (len(category['relocations'])!=17 or len(fields)!=6
            or [b['offset'] for b in fields]!=[8,20,32,44,56,68]
            or [b['target_address'] for b in fields]!=[e['target_address'] for e in CATEGORY_DISPATCH['entries']]
            or [b['code_entry'] for b in fields]!=[e['code_entry'] for e in CATEGORY_DISPATCH['entries']]):
        raise ValueError('locale/time category table loses actual defining callback fields')
    if m['scope_tables']!=SEH_SCOPES:
        raise ValueError('locale/time loses complete finally/exception scopes')
    for scope in m['scope_tables']:
        table=next(r for r in m['state_data'] if r['symbol']==scope['symbol'])
        offsets=[8] if scope['kind']=='finally' else [4,8]
        entries=[scope['handler_offset']] if scope['kind']=='finally' else [scope['filter_offset'],scope['handler_offset']]
        if table['target_address']!=scope['address'] or len(table['relocations'])!=len(offsets):
            raise ValueError('locale/time scope loses complete actual defining fields')
        for b,offset,entry in zip(table['relocations'],offsets,entries):
            if (b['offset']!=offset or b['target_kind']!='code-entry'
                    or b['code_entry']['owner']!=scope['parent'] or b['code_entry']['source_offset']!=entry):
                raise ValueError('locale/time scope loses actual complete parent entry')
        use=[b for b in graph[scope['parent']]['relocation_bindings'] if b['symbol']==scope['symbol']]
        if len(use)!=1 or use[0]['offset']!=3 or use[0]['target_address']!=scope['address']:
            raise ValueError('locale/time scope loses actual whole parent reference')
    if m['runtime_format_dispatch']!=FORMAT_DISPATCH:
        raise ValueError('locale/time loses actual date/time API selection and sizing/output dispatch')
    owner=graph[FORMAT_DISPATCH['owner']]
    if owner['indirect_calls']!=[dict(site=c['site'],operand=c['operand']) for c in FORMAT_DISPATCH['calls']]:
        raise ValueError('locale/time loses every real indirect format call')
    witnesses=lambda key:{(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    required={
        '0x006434A9':{('push','0xc'),('push','0x54'),('cmp','eax, 5'),('call','0x6435f2'),('mov','dword ptr [0x66ff7c], esi')},
        '0x0064C200':{('mov','eax, dword ptr [eax + 0x64]'),('call','0x64c13b'),('add','esp, 0x18')},
        '0x0064C13B':{('call','0x64ba4b')},
        '0x0064BCB1':{('cmp','dword ptr [ecx + 0xb0], 1'),('add','dx, 0x76c'),('inc','dx')},
    }
    for key,expected in required.items():
        if not expected<=witnesses(key):
            raise ValueError('locale/time loses category/lifetime/format behavior witnesses')


def decode_code(row,raw,address,decoder):
    return list(decoder.disasm(raw,address))


def check_dispatch_instructions(m,decoded):
    owner=decoded[m['runtime_format_dispatch']['owner']]
    sites={i.address:i for i in owner}
    selection=[('cmp','dword ptr [ebp + 0xc], 2'),('mov','eax, dword ptr [0x65714c]'),
               ('jne','0x64bd08'),('mov','eax, dword ptr [0x657150]'),('mov','dword ptr [ebp - 0x30], eax')]
    actual=[(i.mnemonic,i.op_str) for i in owner if 0x64bcf8<=i.address<=0x64bd08]
    if actual!=selection:
        raise ValueError('locale/time format loses actual raw SDK pointer selection/store')
    for call in m['runtime_format_dispatch']['calls']:
        i=sites[int(call['site'],16)]
        if (i.mnemonic,i.op_str)!=('call',call['operand']):
            raise ValueError('locale/time format loses actual sizing/output indirect instruction')
    expected={0x64bd48:('push','esi'),0x64bd49:('push','esi'),0x64bd4a:('push','dword ptr [ebp - 0x20]'),
              0x64bd50:('push','edx'),0x64bd51:('push','esi'),0x64bd52:('push','dword ptr [ecx + 0xac]'),
              0x64bdb8:('push','dword ptr [ebp - 0x2c]'),0x64bdbb:('push','edi'),
              0x64bdbc:('push','dword ptr [ebp - 0x20]'),0x64bdc2:('push','eax'),
              0x64bdc3:('push','esi'),0x64bdc7:('push','dword ptr [eax + 0xac]')}
    if any((sites[a].mnemonic,sites[a].op_str)!=value for a,value in expected.items()):
        raise ValueError('locale/time format loses real six-argument capacity/output contract')


def check_scopes(m,target,comparison,decoded):
    for scope in m['scope_tables']:
        base=int(scope['parent'],16);offset=scope['filter_offset']
        expected=(-1,0 if offset is None else base+offset,base+scope['handler_offset'])
        raw=comparison.pe_bytes_at(target,int(scope['address'],16),12)
        if struct.unpack('<iII',raw)!=expected:
            raise ValueError('locale/time actual scope loses full enclosing/filter/handler record')
        instructions=decoded[scope['parent']];by_address={i.address:i for i in instructions}
        handler=base+scope['handler_offset']
        if scope['kind']=='finally':
            actual=[(i.mnemonic,i.op_str) for i in instructions if handler<=i.address<handler+9]
            if actual!=[('push','0xc'),('call','0x646658'),('pop','ecx'),('ret','')]:
                raise ValueError('locale/time finally loses real SETLOCALE unlock and return')
            caller=by_address[0x6435e8]
            if (caller.mnemonic,caller.op_str)!=('call','0x6435f2'):
                raise ValueError('locale/time loses actual normal finally invocation')
        else:
            filter_start=base+offset
            actual=[i for i in instructions if filter_start<=i.address<handler]
            if (sum(i.size for i in actual)!=4 or [(i.mnemonic,i.op_str) for i in actual]!=
                    [('xor','eax, eax'),('inc','eax'),('ret','')]):
                raise ValueError('locale/time exception filter loses complete return-one body')
            first=by_address[handler];second=by_address[handler+first.size]
            if ((first.mnemonic,first.op_str)!=('mov','esp, dword ptr [ebp - 0x18]')
                    or (second.mnemonic,second.op_str)!=('call','0x6518b9')):
                raise ValueError('locale/time exception handler loses stack restoration/reset')


def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('locale-time-parent function loses its complete own AUX extent')
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
        raise ValueError('locale-time-parent cleanup gains an invented source entry')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('locale-time-parent loses complete origin-only extent')
    if (origin['evidence_id'] != 'R137' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('locale-time-parent canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('locale-time-parent shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R137' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('locale-time-parent shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('locale-time-parent external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('locale-time-parent member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('locale_time_parent_old','verify-runtime-error-origins.py')
    c = module('locale_time_parent_target','compare-coff-function.py')
    archive_reader = module('locale_time_parent_archive','verify-runtime-origins.py')
    coff = module('locale_time_parent_coff','coff_data.py')
    startup = module('locale_time_parent_geometry','verify-startup-dependency-origins.py')
    record = module('locale_time_parent_ledger','verify-vendor-record-origins.py')
    facts = module('locale_time_parent_facts','verify-game-lifetime-origins.py')
    imports_module = module('locale_time_parent_imports','verify-import-origins.py')
    literal = module('locale_time_parent_scalar','verify-runtime-external-origins.py')
    sections = module('locale_time_parent_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete locale-time-parent source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('locale-time-parent complete primary loses an actual interior candidate')
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
            raise ValueError('locale-time-parent whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('locale-time-parent source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('locale-time-parent state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('locale-time-parent whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('locale-time-parent initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('locale-time-parent complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('locale-time-parent state loses whole writable target storage')
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
    scratch = ROOT / 'build/origin-locale-time-parent-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural locale-time-parent control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned locale-time-parent control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_LocaleTimeParentLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural locale-time-parent data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural handle/thread/SDK offsets or constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete locale-time-parent vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete input pointer-varargs/int64/PF2 controls differ')
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R136'):
                    raise ValueError('locale-time-parent retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('locale-time-parent complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('locale-time-parent full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('locale-time-parent whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('locale-time-parent complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('locale-time-parent field lacks member-local/whole strong data provenance')
        check_dispatch_instructions(m,decoded)
        check_scopes(m,target,c,decoded)
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('locale-time-parent code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('locale-time-parent local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('locale-time-parent direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('locale-time-parent direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('locale-time-parent same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('locale-time-parent shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('locale-time-parent complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('locale-time-parent data pointer does not reach a complete actual code entry')
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
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-locale-construction-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R136 graph replay failed: '+result.stderr[-1500:])
    print('R137 origins OK: seven complete locale/time library primaries / 3033 bytes / 100 typed fields; one existing nine-byte finally entry within complete 346-byte parent; three non-inventoried category controls / 101 bytes / ten fields; thirty-four full anchors / 6576 bytes / 358 fields; seventy whole data sections / 2582 bytes; five complete COMMON declarations / 20 bytes; full finally/exception scopes and actual SDK date/time selection, sizing/output calls; cold 260-byte natural layouts and full 19-/35-/39-/66-byte ABI controls; full retained R136 graph; local acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
