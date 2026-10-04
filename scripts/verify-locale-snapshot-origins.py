#!/usr/bin/env python3
"""Replay the bounded R138 locale construction dependency graph."""
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
ACCEPTED = {'0x0064B635': ('__Getdays', 127), '0x0064B6B4': ('__Getmonths', 149), '0x0064B749': ('__Gettnames', 563), '0x0064274D': ('_isalpha', 63), '0x006428ED': ('_isalnum', 63)}
LEDGER_SIZES = {'0x0064B635': 127, '0x0064B6B4': 149, '0x0064B749': 563, '0x0064274D': 63, '0x006428ED': 63}
AUXILIARIES = {}
LABELS = {}
STATE = {(2326218, '___lc_time_curr', '0x00670800', 4), (2326218, '??_C@_08HACCIKIA@Thursday?$AA@', '0x00662644', 9), (2326218, '??_C@_03BMAOKBAD@Oct?$AA@', '0x00662608', 4), (2326218, '??_C@_08GNJGEPFN@February?$AA@', '0x006625EC', 9), (2326218, '??_C@_03CNMDKL@May?$AA@', '0x0066261C', 4), (2326218, '??_C@_07BAAGCFCM@Tuesday?$AA@', '0x0066265C', 8), (2326218, '??_C@_03LBGABGKK@Jul?$AA@', '0x00662614', 4), (2326218, '??_C@_02CJNFDJBF@PM?$AA@', '0x00662590', 3), (2326218, '??_C@_03HJBDCHOM@Feb?$AA@', '0x00662628', 4), (1398330, '___lconv_static_null', '0x0068E684', 1), (2326218, '??_C@_02DEDBPAFC@AM?$AA@', '0x00662594', 3), (2326218, '??_C@_03GGCAPAJC@Sep?$AA@', '0x0066260C', 4), (2326218, '??_C@_07CGJPFGJA@January?$AA@', '0x006625F8', 8), (2326218, '??_C@_09DLIGFAKA@Wednesday?$AA@', '0x00662650', 10), (2326218, '??_C@_04CNLMGBGM@June?$AA@', '0x006625D4', 5), (2326218, '??_C@_08BPBNCDIB@MM?1dd?1yy?$AA@', '0x00662584', 9), (2326218, '??_C@_03JPJOFNIA@Nov?$AA@', '0x00662604', 4), (2326218, '___lc_time_c', '0x00670808', 184), (2326218, '??_C@_03IFJFEIGA@Aug?$AA@', '0x00662610', 4), (2326218, '??_C@_03FEFJNEK@Sat?$AA@', '0x00662674', 4), (2326218, '??_C@_07JJNFCEND@October?$AA@', '0x006625B0', 8), (2326218, '??_C@_03KOEHGMDN@Sun?$AA@', '0x0066268C', 4), (2326218, '??_C@_09BHHEALKD@September?$AA@', '0x006625B8', 10), (2326218, '??_C@_08EDHMEBNP@December?$AA@', '0x00662598', 9), (2326218, '??_C@_03ODNJBKGA@Mar?$AA@', '0x00662624', 4), (2326218, '??_C@_06LBBHFDDG@August?$AA@', '0x006625C4', 7), (1444790, '__clocalestr', '0x0066FF20', 403), (2326218, '??_C@_06JECMNKMI@Friday?$AA@', '0x0066263C', 7), (2326218, '??_C@_03PDAGKDH@Mon?$AA@', '0x00662688', 4), (2326218, '??_C@_03MHOMLAJA@Wed?$AA@', '0x00662680', 4), (2326218, '??_C@_05HPCKOFNC@March?$AA@', '0x006625E4', 6), (2326218, '??_C@_04MIEPOIFP@July?$AA@', '0x006625CC', 5), (2326218, '??_C@_06OOPIFAJ@Sunday?$AA@', '0x0066266C', 7), (2326218, '??_C@_03MKABNOCG@Dec?$AA@', '0x00662600', 4), (1398330, '___lconv_static_decimal', '0x006708C8', 56), (2326218, '??_C@_05DMJDNLEJ@April?$AA@', '0x006625DC', 6), (2326218, '??_C@_06JLEDEDGH@Monday?$AA@', '0x00662664', 7), (2326218, '??_C@_03IDIOELNC@Fri?$AA@', '0x00662678', 4), (2326218, '??_C@_03LEOLGMJP@Apr?$AA@', '0x00662620', 4), (2326218, '??_C@_0BE@CKGJFCPC@dddd?0?5MMMM?5dd?0?5yyyy?$AA@', '0x00662570', 20), (2326218, '??_C@_03IOFIKPDN@Thu?$AA@', '0x0066267C', 4), (2326218, '??_C@_03IDFGHECI@Jun?$AA@', '0x00662618', 4), (2326218, '??_C@_03NAGEINEP@Tue?$AA@', '0x00662684', 4), (2326218, '??_C@_08HCHEGEOA@November?$AA@', '0x006625A4', 9), (2326218, '??_C@_08JCCMCCIL@HH?3mm?3ss?$AA@', '0x00662564', 9), (2326218, '??_C@_08INBOOONO@Saturday?$AA@', '0x00662630', 9), (2326218, '??_C@_03JIHJHPIE@Jan?$AA@', '0x0066262C', 4), (1308928, '___newctype', '0x006626B0', 1284)}
LAYOUT_OBJECTS = [{'symbol': '_LocaleSnapshotLayoutProbe', 'offset': 0, 'size': 132, 'storage_span': 132, 'values': [4, 4, 4, 2, 184, 0, 7, 28, 7, 56, 12, 104, 12, 152, 2, 160, 164, 168, 172, 176, 180, 43, 84, 40, 72, 140, 100, 259, 263, 1, 2, 4, 4294967295]}]
LAYOUT_HEADERS = {'PlatformSDK/Include/WinBase.h', 'crt/src/ctype.h', 'crt/src/mtdll.h', 'crt/src/locale.h', 'crt/src/stdio.h', 'PlatformSDK/Include/WinNls.h', 'PlatformSDK/Include/WinNT.h', 'crt/src/string.h', 'crt/src/setlocal.h'}
CALL_CONTROLS = [{'coff_symbol': '_TimeSnapshotCopyControl', 'size': 26, 'source_sha256': '9d9999b58ba49bb8d73db00afb80e47f5724da359973ff04002ce458eba3b4ee', 'relocation_metadata': [{'offset': 17, 'type': 'REL32', 'symbol': '_memcpy', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000019', 'cleanup': 0}], 'direct_calls': [{'site': '0x00000010', 'target': '0x00000015'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'push', 'operands': '0xb8'}, {'site': '0x00000008', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0xc]'}, {'site': '0x0000000B', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x0000000C', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x0000000F', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000010', 'mnemonic': 'call', 'operands': '0x15'}, {'site': '0x00000015', 'mnemonic': 'add', 'operands': 'esp, 0xc'}, {'site': '0x00000018', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000019', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_SnapshotAlphabetControl', 'size': 67, 'source_sha256': '3038cded49805a74f5111a0734c706703c7bf8f91b4a826a38add0a94cda6587', 'relocation_metadata': [{'offset': 27, 'type': 'REL32', 'symbol': '___isctype_mt', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000042', 'cleanup': 0}], 'direct_calls': [{'site': '0x0000001A', 'target': '0x0000001F'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000004', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000007', 'mnemonic': 'cmp', 'operands': 'dword ptr [eax + 0x28], 1'}, {'site': '0x0000000B', 'mnemonic': 'jle', 'operands': '0x27'}, {'site': '0x0000000D', 'mnemonic': 'push', 'operands': '0x103'}, {'site': '0x00000012', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0xc]'}, {'site': '0x00000015', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000016', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x00000019', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000001A', 'mnemonic': 'call', 'operands': '0x1f'}, {'site': '0x0000001F', 'mnemonic': 'add', 'operands': 'esp, 0xc'}, {'site': '0x00000022', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], eax'}, {'site': '0x00000025', 'mnemonic': 'jmp', 'operands': '0x3c'}, {'site': '0x00000027', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x0000002A', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [eax + 0x48]'}, {'site': '0x0000002D', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0xc]'}, {'site': '0x00000030', 'mnemonic': 'movzx', 'operands': 'eax, word ptr [ecx + edx*2]'}, {'site': '0x00000034', 'mnemonic': 'and', 'operands': 'eax, 0x103'}, {'site': '0x00000039', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], eax'}, {'site': '0x0000003C', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp - 4]'}, {'site': '0x0000003F', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x00000041', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000042', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_SnapshotAlnumControl', 'size': 67, 'source_sha256': '0c5801e3f3454f674720e73e2f4208672e0fe65bd5f6afbc571f2918171c908b', 'relocation_metadata': [{'offset': 27, 'type': 'REL32', 'symbol': '___isctype_mt', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000042', 'cleanup': 0}], 'direct_calls': [{'site': '0x0000001A', 'target': '0x0000001F'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000004', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000007', 'mnemonic': 'cmp', 'operands': 'dword ptr [eax + 0x28], 1'}, {'site': '0x0000000B', 'mnemonic': 'jle', 'operands': '0x27'}, {'site': '0x0000000D', 'mnemonic': 'push', 'operands': '0x107'}, {'site': '0x00000012', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0xc]'}, {'site': '0x00000015', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000016', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x00000019', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000001A', 'mnemonic': 'call', 'operands': '0x1f'}, {'site': '0x0000001F', 'mnemonic': 'add', 'operands': 'esp, 0xc'}, {'site': '0x00000022', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], eax'}, {'site': '0x00000025', 'mnemonic': 'jmp', 'operands': '0x3c'}, {'site': '0x00000027', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x0000002A', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [eax + 0x48]'}, {'site': '0x0000002D', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0xc]'}, {'site': '0x00000030', 'mnemonic': 'movzx', 'operands': 'eax, word ptr [ecx + edx*2]'}, {'site': '0x00000034', 'mnemonic': 'and', 'operands': 'eax, 0x107'}, {'site': '0x00000039', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], eax'}, {'site': '0x0000003C', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp - 4]'}, {'site': '0x0000003F', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x00000041', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000042', 'mnemonic': 'ret', 'operands': ''}]}]
VENDOR_SOURCES = {'crt/src/strftime.c', 'crt/src/_ctype.c', 'crt/src/intel/memcpy.asm'}
CONFIDENCE = 'complete-vendor-locale-snapshot-classification-code-data-abi-provenance'
LABEL_CONFIDENCE = 'unused-no-new-locale-snapshot-labels'

ANCHORS = [('0x00640620', '_strlen', 139, 2200788, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00644331', '_malloc', 18, 816374, 'R120'), ('0x00641B80', '_strcpy', 7, 2186124, 'R116'), ('0x00640F20', '_memcpy', 829, 2159808, 'R025'), ('0x00646196', '__getptd', 113, 1724384, 'R120'), ('0x00642DEB', '___updatetlocinfo', 59, 1444790, 'R123'), ('0x0064980B', '___isctype_mt', 119, 166568, 'R123')]
IO_PROTOCOL = {'time_size': 184, 'time_strings': 43, 'weekday_count': 7, 'month_count': 12, 'ampm_count': 2, 'separator': 58, 'classification_alpha': 259, 'classification_alnum': 263, 'ctype_width': 2, 'thread_size': 140, 'thread_locale_offset': 100, 'thread_locale_size': 84, 'mb_cur_max_offset': 40, 'pctype_offset': 72, 'copy_caller_cleanup': 12, 'classification_caller_cleanup': 12, 'locale_threshold': 1, 'basis': 'Complete defining source sizes, string ownership and classification masks; copy includes all record fields then retargets 43 strings in one allocation; runtime current pointers/refcounts/values and concurrent snapshot consistency unknown'}

CODE_SIZES = {'0x0064B635': 127, '0x0064B6B4': 149, '0x0064B749': 563, '0x0064274D': 63, '0x006428ED': 63}

SEH_SCOPES = []

COMMON_GLOBALS = []
MEMCPY_REGIONS = [{'offset': 0, 'size': 100}, {'offset': 112, 'size': 112}, {'offset': 256, 'size': 76}, {'offset': 348, 'size': 148}, {'offset': 508, 'size': 128}, {'offset': 668, 'size': 76}, {'offset': 760, 'size': 69}]
MEMCPY_TABLES = [{'symbol': 'LeadUpVec', 'offset': 100, 'size': 12, 'source_definition': {'symbol': 'LeadUpVec', 'offset': 100, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 100, 'symbol': 'LeadUp1', 'target_address': '0x00640F90', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 112, 'source_definition': {'symbol': 'LeadUp1', 'offset': 112, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 104, 'symbol': 'LeadUp2', 'target_address': '0x00640FBC', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 156, 'source_definition': {'symbol': 'LeadUp2', 'offset': 156, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 108, 'symbol': 'LeadUp3', 'target_address': '0x00640FE0', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 192, 'source_definition': {'symbol': 'LeadUp3', 'offset': 192, 'section': 1, 'type': 0, 'storage': 6}}}]}, {'symbol': 'UnwindUpVec', 'offset': 224, 'size': 32, 'source_definition': {'symbol': 'UnwindUpVec', 'offset': 224, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 224, 'symbol': 'UnwindUp0', 'target_address': '0x00641063', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 323, 'source_definition': {'symbol': 'UnwindUp0', 'offset': 323, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 228, 'symbol': 'UnwindUp1', 'target_address': '0x00641050', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 304, 'source_definition': {'symbol': 'UnwindUp1', 'offset': 304, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 232, 'symbol': 'UnwindUp2', 'target_address': '0x00641048', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 296, 'source_definition': {'symbol': 'UnwindUp2', 'offset': 296, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 236, 'symbol': 'UnwindUp3', 'target_address': '0x00641040', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 288, 'source_definition': {'symbol': 'UnwindUp3', 'offset': 288, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 240, 'symbol': 'UnwindUp4', 'target_address': '0x00641038', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 280, 'source_definition': {'symbol': 'UnwindUp4', 'offset': 280, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 244, 'symbol': 'UnwindUp5', 'target_address': '0x00641030', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 272, 'source_definition': {'symbol': 'UnwindUp5', 'offset': 272, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 248, 'symbol': 'UnwindUp6', 'target_address': '0x00641028', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 264, 'source_definition': {'symbol': 'UnwindUp6', 'offset': 264, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 252, 'symbol': 'UnwindUp7', 'target_address': '0x00641020', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 256, 'source_definition': {'symbol': 'UnwindUp7', 'offset': 256, 'section': 1, 'type': 0, 'storage': 6}}}]}, {'symbol': 'TrailUpVec', 'offset': 332, 'size': 16, 'source_definition': {'symbol': 'TrailUpVec', 'offset': 332, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 332, 'symbol': 'TrailUp0', 'target_address': '0x0064107C', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 348, 'source_definition': {'symbol': 'TrailUp0', 'offset': 348, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 336, 'symbol': 'TrailUp1', 'target_address': '0x00641084', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 356, 'source_definition': {'symbol': 'TrailUp1', 'offset': 356, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 340, 'symbol': 'TrailUp2', 'target_address': '0x00641090', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 368, 'source_definition': {'symbol': 'TrailUp2', 'offset': 368, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 344, 'symbol': 'TrailUp3', 'target_address': '0x006410A4', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 388, 'source_definition': {'symbol': 'TrailUp3', 'offset': 388, 'section': 1, 'type': 0, 'storage': 6}}}]}, {'symbol': 'LeadDownVec', 'offset': 496, 'size': 12, 'source_definition': {'symbol': 'LeadDownVec', 'offset': 496, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 496, 'symbol': 'LeadDown1', 'target_address': '0x0064111C', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 508, 'source_definition': {'symbol': 'LeadDown1', 'offset': 508, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 500, 'symbol': 'LeadDown2', 'target_address': '0x00641140', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 544, 'source_definition': {'symbol': 'LeadDown2', 'offset': 544, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 504, 'symbol': 'LeadDown3', 'target_address': '0x00641168', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 584, 'source_definition': {'symbol': 'LeadDown3', 'offset': 584, 'section': 1, 'type': 0, 'storage': 6}}}]}, {'symbol': 'UnwindDownVec', 'offset': 636, 'size': 32, 'source_definition': {'symbol': 'UnwindDownVec', 'offset': 636, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 636, 'symbol': 'UnwindDown7', 'target_address': '0x006411BC', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 668, 'source_definition': {'symbol': 'UnwindDown7', 'offset': 668, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 640, 'symbol': 'UnwindDown6', 'target_address': '0x006411C4', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 676, 'source_definition': {'symbol': 'UnwindDown6', 'offset': 676, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 644, 'symbol': 'UnwindDown5', 'target_address': '0x006411CC', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 684, 'source_definition': {'symbol': 'UnwindDown5', 'offset': 684, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 648, 'symbol': 'UnwindDown4', 'target_address': '0x006411D4', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 692, 'source_definition': {'symbol': 'UnwindDown4', 'offset': 692, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 652, 'symbol': 'UnwindDown3', 'target_address': '0x006411DC', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 700, 'source_definition': {'symbol': 'UnwindDown3', 'offset': 700, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 656, 'symbol': 'UnwindDown2', 'target_address': '0x006411E4', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 708, 'source_definition': {'symbol': 'UnwindDown2', 'offset': 708, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 660, 'symbol': 'UnwindDown1', 'target_address': '0x006411EC', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 716, 'source_definition': {'symbol': 'UnwindDown1', 'offset': 716, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 664, 'symbol': 'UnwindDown0', 'target_address': '0x006411FF', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 735, 'source_definition': {'symbol': 'UnwindDown0', 'offset': 735, 'section': 1, 'type': 0, 'storage': 6}}}]}, {'symbol': 'TrailDownVec', 'offset': 744, 'size': 16, 'source_definition': {'symbol': 'TrailDownVec', 'offset': 744, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 744, 'symbol': 'TrailDown0', 'target_address': '0x00641218', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 760, 'source_definition': {'symbol': 'TrailDown0', 'offset': 760, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 748, 'symbol': 'TrailDown1', 'target_address': '0x00641220', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 768, 'source_definition': {'symbol': 'TrailDown1', 'offset': 768, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 752, 'symbol': 'TrailDown2', 'target_address': '0x00641230', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 784, 'source_definition': {'symbol': 'TrailDown2', 'offset': 784, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 756, 'symbol': 'TrailDown3', 'target_address': '0x00641244', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 804, 'source_definition': {'symbol': 'TrailDown3', 'offset': 804, 'section': 1, 'type': 0, 'storage': 6}}}]}]

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/locale-snapshot-origin-evidence.json').read_text())
    identity = module('locale_snapshot_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R138' or m['target_sha256'] != identity.TARGET:
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
    if len(m['functions']) != 5 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete locale-snapshot cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != CODE_SIZES[key]
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('locale-snapshot function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=0 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('locale-snapshot loses complete auxiliary owners')
    if (len(m['interior_labels']) != 0 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('locale-snapshot shared entries lose complete source parents or gain standalone credit')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence']) for r in m['anchors']] != ANCHORS:
        raise ValueError('locale-snapshot independent complete anchors differ')
    if any(m[k] for k in (
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('locale-snapshot graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 48 or sum(r['size'] for r in m['state_data']) != 2191
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('locale-snapshot graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 132 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural locale-snapshot operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R137',manifest='locale-time-parent-origin-evidence.json')]:
        raise ValueError('locale-snapshot loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('locale-snapshot graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('locale-snapshot shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('locale-snapshot direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('locale-snapshot table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    return rows


def check_parent_protocol(m, graph):
    if m['snapshot_protocol']!=IO_PROTOCOL or m['call_controls']!=CALL_CONTROLS:
        raise ValueError('snapshot complete ownership/layout/classification ABI controls differ')
    if any(m[k] for k in ('auxiliary_bodies','interior_labels','retained_labels','diagnostic_contexts',
                          'scope_tables','common_globals','code_carriers','extent_reconciliations','source_alternatives')):
        raise ValueError('snapshot gains unsupported owners/scopes or invented inventory credit')
    if set(m['vendor_sources'])!=VENDOR_SOURCES or set(m['sdk_layout']['headers'])!=LAYOUT_HEADERS:
        raise ValueError('snapshot loses complete defining source/header context')
    for row in graph.values():
        expected=MEMCPY_REGIONS if row['address']=='0x00640F20' else [dict(offset=0,size=row['size'])]
        if row['code_regions']!=expected or row['code_size']!=sum(r['size'] for r in expected):
            raise ValueError('snapshot loses complete source code/data partition')
        if row['address']!='0x00640F20' and row.get('embedded_tables'):
            raise ValueError('snapshot gains unsupported code tables')
    if graph['0x00640F20'].get('embedded_tables')!=MEMCPY_TABLES:
        raise ValueError('snapshot memcpy loses full six-table owner')
    for table in MEMCPY_TABLES:
        for entry in table['entries']:check_code_entry(entry,graph)
    time=next(r for r in m['state_data'] if r['symbol']=='___lc_time_c')
    if time['size']!=184 or len(time['relocations'])!=43 or [b['offset'] for b in time['relocations']]!=list(range(0,172,4)):
        raise ValueError('snapshot loses full time record and all 43 defining strings')
    witnesses=lambda key:{(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    required={
        '0x0064B635':{('cmp','ebx, 7'),('mov','byte ptr [esi], 0x3a')},
        '0x0064B6B4':{('mov','byte ptr [esi], 0x3a')},
        '0x0064B749':{('push','0xb8'),('call','0x640f20'),('cmp','dword ptr [ebp - 4], 7')},
        '0x0064274D':{('mov','eax, dword ptr [eax + 0x64]'),('cmp','dword ptr [eax + 0x28], 1'),('push','0x103'),('call','0x64980b'),('add','esp, 0xc'),('mov','eax, dword ptr [eax + 0x48]'),('movzx','eax, word ptr [eax + ecx*2]'),('and','eax, 0x103')},
        '0x006428ED':{('mov','eax, dword ptr [eax + 0x64]'),('cmp','dword ptr [eax + 0x28], 1'),('push','0x107'),('call','0x64980b'),('add','esp, 0xc'),('mov','eax, dword ptr [eax + 0x48]'),('movzx','eax, word ptr [eax + ecx*2]'),('and','eax, 0x107')},
    }
    for key,expected in required.items():
        if not expected<=witnesses(key):
            raise ValueError('snapshot loses actual copy/separator/classification behavior')
    if any(row['indirect_calls'] or row['indirect_jumps'] for row in m['functions']):
        raise ValueError('snapshot gains unsupported indirect dispatch')


def decode_code(row,raw,address,decoder):
    return [i for region in row['code_regions']
            for i in decoder.disasm(raw[region['offset']:region['offset']+region['size']],address+region['offset'])]


def check_memcpy_partition(row,actual,instructions):
    if row['address']!='0x00640F20':return
    base=int(row['address'],16);starts={i.address for i in instructions};fields=row['relocation_bindings']
    covered=set()
    for region in row['code_regions']:
        covered.update(range(region['offset'],region['offset']+region['size']))
    for table in row['embedded_tables']:
        definition=table['source_definition']
        if (definition['symbol']!=table['symbol'] or definition['offset']!=table['offset']
                or definition['section']!=row['source_definition']['section']):
            raise ValueError('memcpy table loses actual whole source definition')
        data_offsets=set(range(table['offset'],table['offset']+table['size']))
        if covered&data_offsets:raise ValueError('memcpy table is incorrectly decoded as code')
        covered.update(data_offsets)
        values=struct.unpack('<'+'I'*(table['size']//4),actual[table['offset']:table['offset']+table['size']])
        if [f'0x{x:08X}' for x in values]!=[e['target_address'] for e in table['entries']] or any(x not in starts for x in values):
            raise ValueError('memcpy whole table loses actual code case starts')
        for entry in table['entries']:
            field=next(b for b in fields if b['offset']==entry['offset'])
            if (field['type']!='DIR32' or field['symbol']!=entry['symbol']
                    or field['target_address']!=entry['target_address']):
                raise ValueError('memcpy table loses its full source-typed field')
    if covered!=set(range(row['size'])):
        raise ValueError('memcpy source partition omits or pads complete owner bytes')


def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('locale-snapshot function loses its complete own AUX extent')
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
        raise ValueError('locale-snapshot cleanup gains an invented source entry')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('locale-snapshot loses complete origin-only extent')
    if (origin['evidence_id'] != 'R138' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('locale-snapshot canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('locale-snapshot shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R138' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('locale-snapshot shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('locale-snapshot external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('locale-snapshot member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('locale_snapshot_old','verify-runtime-error-origins.py')
    c = module('locale_snapshot_target','compare-coff-function.py')
    archive_reader = module('locale_snapshot_archive','verify-runtime-origins.py')
    coff = module('locale_snapshot_coff','coff_data.py')
    startup = module('locale_snapshot_geometry','verify-startup-dependency-origins.py')
    record = module('locale_snapshot_ledger','verify-vendor-record-origins.py')
    facts = module('locale_snapshot_facts','verify-game-lifetime-origins.py')
    imports_module = module('locale_snapshot_imports','verify-import-origins.py')
    literal = module('locale_snapshot_scalar','verify-runtime-external-origins.py')
    sections = module('locale_snapshot_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete locale-snapshot source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('locale-snapshot complete primary loses an actual interior candidate')
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
            raise ValueError('locale-snapshot whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('locale-snapshot source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('locale-snapshot state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('locale-snapshot whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('locale-snapshot initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('locale-snapshot complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('locale-snapshot state loses whole writable target storage')
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
    scratch = ROOT / 'build/origin-locale-snapshot-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural locale-snapshot control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned locale-snapshot control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_LocaleSnapshotLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural locale-snapshot data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural handle/thread/SDK offsets or constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete locale-snapshot vendor source differs')
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
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R137'):
                    raise ValueError('locale-snapshot retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('locale-snapshot complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('locale-snapshot full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('locale-snapshot whole code instruction/control-flow inventory differs')
            check_memcpy_partition(row,actual,ins)
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('locale-snapshot complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('locale-snapshot field lacks member-local/whole strong data provenance')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('locale-snapshot code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('locale-snapshot local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('locale-snapshot direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('locale-snapshot direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('locale-snapshot same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('locale-snapshot shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('locale-snapshot complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('locale-snapshot data pointer does not reach a complete actual code entry')
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
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-locale-time-parent-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R137 graph replay failed: '+result.stderr[-1500:])
    print('R138 origins OK: five complete locale-snapshot/classification library primaries / 965 bytes / 54 typed fields; seven full anchors / 1284 bytes / 65 fields; forty-eight whole data sections / 2191 bytes / 59 fields; complete 184-byte time record and all 43 strings, actual alpha/alnum masks and thread/locale paths; full 829-byte memcpy with seven code regions and six tables; cold 132-byte natural layouts and complete 26-/67-/67-byte copy/classification controls; full retained R137 graph; local acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
