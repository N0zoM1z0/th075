#!/usr/bin/env python3
"""Replay the bounded R140 stream finalization and path-access dependency graph."""
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
ACCEPTED = {'0x00654953': ('__freebuf', 43), '0x00653E01': ('__fclose_lk', 76), '0x00652588': ('__flush', 93), '0x00641B37': ('__access', 70)}
LEDGER_SIZES = {'0x00654953': 43, '0x00653E01': 76, '0x00652588': 93, '0x00641B37': 70}
AUXILIARIES = {}
LABELS = {}
STATE = set()
LAYOUT_OBJECTS = [{'symbol': '_StreamFinalizationLayoutProbe', 'offset': 0, 'size': 112, 'storage_span': 112, 'values': [4, 4, 1, 2, 32, 0, 4, 8, 12, 16, 28, 1, 2, 128, 8, 256, 1024, 32, 131, 264, 4294966263, 64503, 4294967293, 1, 4294967295, 13, 5, 4294967295]}]
LAYOUT_HEADERS = {'crt/src/internal.h', 'crt/src/stdlib.h', 'crt/src/errno.h', 'crt/src/stdio.h', 'PlatformSDK/Include/WinBase.h', 'crt/src/file2.h', 'PlatformSDK/Include/WinNT.h', 'crt/src/io.h', 'crt/src/msdos.h'}
CALL_CONTROLS = [{'coff_symbol': '_StreamFinalFreeControl', 'size': 92, 'source_sha256': 'f0dcb41b5083b9764b9b430afa8a47aeadf450bf0879794d79a73b0aa9a0152f', 'relocation_metadata': [{'offset': 36, 'type': 'REL32', 'symbol': '_free', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x0000005B', 'cleanup': 0}], 'direct_calls': [{'site': '0x00000023', 'target': '0x00000028'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000006', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [eax + 0xc]'}, {'site': '0x00000009', 'mnemonic': 'and', 'operands': 'ecx, 0x83'}, {'site': '0x0000000F', 'mnemonic': 'je', 'operands': '0x5a'}, {'site': '0x00000011', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x00000014', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [edx + 0xc]'}, {'site': '0x00000017', 'mnemonic': 'and', 'operands': 'eax, 8'}, {'site': '0x0000001A', 'mnemonic': 'je', 'operands': '0x5a'}, {'site': '0x0000001C', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x0000001F', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ecx + 8]'}, {'site': '0x00000022', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x00000023', 'mnemonic': 'call', 'operands': '0x28'}, {'site': '0x00000028', 'mnemonic': 'add', 'operands': 'esp, 4'}, {'site': '0x0000002B', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x0000002E', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [eax + 0xc]'}, {'site': '0x00000031', 'mnemonic': 'and', 'operands': 'ecx, 0xfffffbf7'}, {'site': '0x00000037', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x0000003A', 'mnemonic': 'mov', 'operands': 'dword ptr [edx + 0xc], ecx'}, {'site': '0x0000003D', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000040', 'mnemonic': 'mov', 'operands': 'dword ptr [eax], 0'}, {'site': '0x00000046', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x00000049', 'mnemonic': 'mov', 'operands': 'dword ptr [ecx + 8], 0'}, {'site': '0x00000050', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x00000053', 'mnemonic': 'mov', 'operands': 'dword ptr [edx + 4], 0'}, {'site': '0x0000005A', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x0000005B', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_StreamFinalFlushControl', 'size': 172, 'source_sha256': '93582ffa8c0943af5f1efddaa0d1972ba1382361fdeba6d66695589be7146622', 'relocation_metadata': [{'offset': 79, 'type': 'REL32', 'symbol': '__write', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x000000AB', 'cleanup': 0}], 'direct_calls': [{'site': '0x0000004E', 'target': '0x00000053'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'sub', 'operands': 'esp, 8'}, {'site': '0x00000006', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 8], 0'}, {'site': '0x0000000D', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000010', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [eax + 0xc]'}, {'site': '0x00000013', 'mnemonic': 'and', 'operands': 'ecx, 3'}, {'site': '0x00000016', 'mnemonic': 'cmp', 'operands': 'ecx, 2'}, {'site': '0x00000019', 'mnemonic': 'jne', 'operands': '0x90'}, {'site': '0x0000001B', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x0000001E', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [edx + 0xc]'}, {'site': '0x00000021', 'mnemonic': 'and', 'operands': 'eax, 0x108'}, {'site': '0x00000026', 'mnemonic': 'je', 'operands': '0x90'}, {'site': '0x00000028', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x0000002B', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x0000002E', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ecx]'}, {'site': '0x00000030', 'mnemonic': 'sub', 'operands': 'eax, dword ptr [edx + 8]'}, {'site': '0x00000033', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], eax'}, {'site': '0x00000036', 'mnemonic': 'cmp', 'operands': 'dword ptr [ebp - 4], 0'}, {'site': '0x0000003A', 'mnemonic': 'jle', 'operands': '0x90'}, {'site': '0x0000003C', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp - 4]'}, {'site': '0x0000003F', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000040', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x00000043', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [edx + 8]'}, {'site': '0x00000046', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000047', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x0000004A', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ecx + 0x10]'}, {'site': '0x0000004D', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000004E', 'mnemonic': 'call', 'operands': '0x53'}, {'site': '0x00000053', 'mnemonic': 'add', 'operands': 'esp, 0xc'}, {'site': '0x00000056', 'mnemonic': 'cmp', 'operands': 'eax, dword ptr [ebp - 4]'}, {'site': '0x00000059', 'mnemonic': 'jne', 'operands': '0x7a'}, {'site': '0x0000005B', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x0000005E', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [eax + 0xc]'}, {'site': '0x00000061', 'mnemonic': 'and', 'operands': 'ecx, 0x80'}, {'site': '0x00000067', 'mnemonic': 'je', 'operands': '0x78'}, {'site': '0x00000069', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x0000006C', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [edx + 0xc]'}, {'site': '0x0000006F', 'mnemonic': 'and', 'operands': 'eax, 0xfffffffd'}, {'site': '0x00000072', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x00000075', 'mnemonic': 'mov', 'operands': 'dword ptr [ecx + 0xc], eax'}, {'site': '0x00000078', 'mnemonic': 'jmp', 'operands': '0x90'}, {'site': '0x0000007A', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x0000007D', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [edx + 0xc]'}, {'site': '0x00000080', 'mnemonic': 'or', 'operands': 'eax, 0x20'}, {'site': '0x00000083', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x00000086', 'mnemonic': 'mov', 'operands': 'dword ptr [ecx + 0xc], eax'}, {'site': '0x00000089', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 8], 0xffffffff'}, {'site': '0x00000090', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x00000093', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000096', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [eax + 8]'}, {'site': '0x00000099', 'mnemonic': 'mov', 'operands': 'dword ptr [edx], ecx'}, {'site': '0x0000009B', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x0000009E', 'mnemonic': 'mov', 'operands': 'dword ptr [edx + 4], 0'}, {'site': '0x000000A5', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp - 8]'}, {'site': '0x000000A8', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x000000AA', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x000000AB', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_StreamFinalCloseControl', 'size': 131, 'source_sha256': '9cc72f1a9d6544d8121f277264164698a8eff273f7e65dc78d2da02af52514bf', 'relocation_metadata': [{'offset': 30, 'type': 'REL32', 'symbol': '__flush', 'addend': 0, 'local_symbol_offset': None}, {'offset': 45, 'type': 'REL32', 'symbol': '__freebuf', 'addend': 0, 'local_symbol_offset': None}, {'offset': 60, 'type': 'REL32', 'symbol': '__close', 'addend': 0, 'local_symbol_offset': None}, {'offset': 97, 'type': 'REL32', 'symbol': '_free', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000082', 'cleanup': 0}], 'direct_calls': [{'site': '0x0000001D', 'target': '0x00000022'}, {'site': '0x0000002C', 'target': '0x00000031'}, {'site': '0x0000003B', 'target': '0x00000040'}, {'site': '0x00000060', 'target': '0x00000065'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000004', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], 0xffffffff'}, {'site': '0x0000000B', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x0000000E', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [eax + 0xc]'}, {'site': '0x00000011', 'mnemonic': 'and', 'operands': 'ecx, 0x83'}, {'site': '0x00000017', 'mnemonic': 'je', 'operands': '0x72'}, {'site': '0x00000019', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 8]'}, {'site': '0x0000001C', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000001D', 'mnemonic': 'call', 'operands': '0x22'}, {'site': '0x00000022', 'mnemonic': 'add', 'operands': 'esp, 4'}, {'site': '0x00000025', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], eax'}, {'site': '0x00000028', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x0000002B', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x0000002C', 'mnemonic': 'call', 'operands': '0x31'}, {'site': '0x00000031', 'mnemonic': 'add', 'operands': 'esp, 4'}, {'site': '0x00000034', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x00000037', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ecx + 0x10]'}, {'site': '0x0000003A', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000003B', 'mnemonic': 'call', 'operands': '0x40'}, {'site': '0x00000040', 'mnemonic': 'add', 'operands': 'esp, 4'}, {'site': '0x00000043', 'mnemonic': 'test', 'operands': 'eax, eax'}, {'site': '0x00000045', 'mnemonic': 'jge', 'operands': '0x50'}, {'site': '0x00000047', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], 0xffffffff'}, {'site': '0x0000004E', 'mnemonic': 'jmp', 'operands': '0x72'}, {'site': '0x00000050', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000053', 'mnemonic': 'cmp', 'operands': 'dword ptr [eax + 0x1c], 0'}, {'site': '0x00000057', 'mnemonic': 'je', 'operands': '0x72'}, {'site': '0x00000059', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x0000005C', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ecx + 0x1c]'}, {'site': '0x0000005F', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x00000060', 'mnemonic': 'call', 'operands': '0x65'}, {'site': '0x00000065', 'mnemonic': 'add', 'operands': 'esp, 4'}, {'site': '0x00000068', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x0000006B', 'mnemonic': 'mov', 'operands': 'dword ptr [eax + 0x1c], 0'}, {'site': '0x00000072', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 8]'}, {'site': '0x00000075', 'mnemonic': 'mov', 'operands': 'dword ptr [ecx + 0xc], 0'}, {'site': '0x0000007C', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp - 4]'}, {'site': '0x0000007F', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x00000081', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000082', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_StreamPathAccessControl', 'size': 92, 'source_sha256': 'da569e741feea8bdf7a19dc7d53f3d2fb8fdd2095896158fd767ae7c4ae0510b', 'relocation_metadata': [{'offset': 10, 'type': 'DIR32', 'symbol': '__imp__GetFileAttributesA@4', 'addend': 0, 'local_symbol_offset': None}, {'offset': 25, 'type': 'DIR32', 'symbol': '__imp__GetLastError@0', 'addend': 0, 'local_symbol_offset': None}, {'offset': 31, 'type': 'REL32', 'symbol': '__dosmaperr', 'addend': 0, 'local_symbol_offset': None}, {'offset': 60, 'type': 'REL32', 'symbol': '__errno', 'addend': 0, 'local_symbol_offset': None}, {'offset': 71, 'type': 'REL32', 'symbol': '___doserrno', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x0000005B', 'cleanup': 0}], 'direct_calls': [{'site': '0x0000001E', 'target': '0x00000023'}, {'site': '0x0000003B', 'target': '0x00000040'}, {'site': '0x00000046', 'target': '0x0000004B'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000004', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000007', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000008', 'mnemonic': 'call', 'operands': 'dword ptr [0]'}, {'site': '0x0000000E', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], eax'}, {'site': '0x00000011', 'mnemonic': 'cmp', 'operands': 'dword ptr [ebp - 4], -1'}, {'site': '0x00000015', 'mnemonic': 'jne', 'operands': '0x2b'}, {'site': '0x00000017', 'mnemonic': 'call', 'operands': 'dword ptr [0]'}, {'site': '0x0000001D', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x0000001E', 'mnemonic': 'call', 'operands': '0x23'}, {'site': '0x00000023', 'mnemonic': 'add', 'operands': 'esp, 4'}, {'site': '0x00000026', 'mnemonic': 'or', 'operands': 'eax, 0xffffffff'}, {'site': '0x00000029', 'mnemonic': 'jmp', 'operands': '0x58'}, {'site': '0x0000002B', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp - 4]'}, {'site': '0x0000002E', 'mnemonic': 'and', 'operands': 'ecx, 1'}, {'site': '0x00000031', 'mnemonic': 'je', 'operands': '0x56'}, {'site': '0x00000033', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0xc]'}, {'site': '0x00000036', 'mnemonic': 'and', 'operands': 'edx, 2'}, {'site': '0x00000039', 'mnemonic': 'je', 'operands': '0x56'}, {'site': '0x0000003B', 'mnemonic': 'call', 'operands': '0x40'}, {'site': '0x00000040', 'mnemonic': 'mov', 'operands': 'dword ptr [eax], 0xd'}, {'site': '0x00000046', 'mnemonic': 'call', 'operands': '0x4b'}, {'site': '0x0000004B', 'mnemonic': 'mov', 'operands': 'dword ptr [eax], 5'}, {'site': '0x00000051', 'mnemonic': 'or', 'operands': 'eax, 0xffffffff'}, {'site': '0x00000054', 'mnemonic': 'jmp', 'operands': '0x58'}, {'site': '0x00000056', 'mnemonic': 'xor', 'operands': 'eax, eax'}, {'site': '0x00000058', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x0000005A', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x0000005B', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_StreamWidePathAccessControl', 'size': 92, 'source_sha256': 'da569e741feea8bdf7a19dc7d53f3d2fb8fdd2095896158fd767ae7c4ae0510b', 'relocation_metadata': [{'offset': 10, 'type': 'DIR32', 'symbol': '__imp__GetFileAttributesW@4', 'addend': 0, 'local_symbol_offset': None}, {'offset': 25, 'type': 'DIR32', 'symbol': '__imp__GetLastError@0', 'addend': 0, 'local_symbol_offset': None}, {'offset': 31, 'type': 'REL32', 'symbol': '__dosmaperr', 'addend': 0, 'local_symbol_offset': None}, {'offset': 60, 'type': 'REL32', 'symbol': '__errno', 'addend': 0, 'local_symbol_offset': None}, {'offset': 71, 'type': 'REL32', 'symbol': '___doserrno', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x0000005B', 'cleanup': 0}], 'direct_calls': [{'site': '0x0000001E', 'target': '0x00000023'}, {'site': '0x0000003B', 'target': '0x00000040'}, {'site': '0x00000046', 'target': '0x0000004B'}], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000004', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000007', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000008', 'mnemonic': 'call', 'operands': 'dword ptr [0]'}, {'site': '0x0000000E', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], eax'}, {'site': '0x00000011', 'mnemonic': 'cmp', 'operands': 'dword ptr [ebp - 4], -1'}, {'site': '0x00000015', 'mnemonic': 'jne', 'operands': '0x2b'}, {'site': '0x00000017', 'mnemonic': 'call', 'operands': 'dword ptr [0]'}, {'site': '0x0000001D', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x0000001E', 'mnemonic': 'call', 'operands': '0x23'}, {'site': '0x00000023', 'mnemonic': 'add', 'operands': 'esp, 4'}, {'site': '0x00000026', 'mnemonic': 'or', 'operands': 'eax, 0xffffffff'}, {'site': '0x00000029', 'mnemonic': 'jmp', 'operands': '0x58'}, {'site': '0x0000002B', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp - 4]'}, {'site': '0x0000002E', 'mnemonic': 'and', 'operands': 'ecx, 1'}, {'site': '0x00000031', 'mnemonic': 'je', 'operands': '0x56'}, {'site': '0x00000033', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0xc]'}, {'site': '0x00000036', 'mnemonic': 'and', 'operands': 'edx, 2'}, {'site': '0x00000039', 'mnemonic': 'je', 'operands': '0x56'}, {'site': '0x0000003B', 'mnemonic': 'call', 'operands': '0x40'}, {'site': '0x00000040', 'mnemonic': 'mov', 'operands': 'dword ptr [eax], 0xd'}, {'site': '0x00000046', 'mnemonic': 'call', 'operands': '0x4b'}, {'site': '0x0000004B', 'mnemonic': 'mov', 'operands': 'dword ptr [eax], 5'}, {'site': '0x00000051', 'mnemonic': 'or', 'operands': 'eax, 0xffffffff'}, {'site': '0x00000054', 'mnemonic': 'jmp', 'operands': '0x58'}, {'site': '0x00000056', 'mnemonic': 'xor', 'operands': 'eax, eax'}, {'site': '0x00000058', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x0000005A', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x0000005B', 'mnemonic': 'ret', 'operands': ''}]}]
VENDOR_SOURCES = {'crt/src/access.c', 'crt/src/fflush.c', 'crt/src/waccess.c', 'crt/src/_freebuf.c', 'crt/src/fclose.c'}
CONFIDENCE = 'complete-vendor-stream-finalization-path-api-code-layout-abi-provenance'
LABEL_CONFIDENCE = 'unused-no-new-stream-finalization-labels'

ANCHORS = [('0x00642A61', '_free', 113, 794604, 'R120'), ('0x006548B8', '__close', 155, 889344, 'R133'), ('0x0064EF70', '__write', 171, 991338, 'R132'), ('0x00647FAA', '__dosmaperr', 115, 280602, 'R132'), ('0x00647F98', '__errno', 9, 280602, 'R120'), ('0x00647FA1', '___doserrno', 9, 280602, 'R132')]
IO_PROTOCOL = {'file_size': 32, 'file_ptr_offset': 0, 'file_count_offset': 4, 'file_base_offset': 8, 'file_flag_offset': 12, 'file_descriptor_offset': 16, 'file_temp_name_offset': 28, 'inuse_mask': 131, 'owned_buffer_mask': 8, 'buffer_mask': 264, 'buffer_release_mask': 1032, 'buffer_release_word_mask': 64503, 'write_mask': 2, 'read_write_mask': 128, 'error_mask': 32, 'write_caller_cleanup': 12, 'write_stack_arguments': 3, 'path_write_mode_mask': 2, 'readonly_attribute': 1, 'invalid_attributes': 4294967295, 'access_errno': 13, 'access_doserrno': 5, 'path_import': 'GetFileAttributesA', 'wide_import_alternative': 'GetFileAttributesW', 'source_basis': 'Complete pinned freebuf/fclose/fflush/access/waccess sources and COFF owners; real FILE and SDK declarations', 'policy_basis': 'Free only active CRT-owned buffers; flush compares full requested byte count and always resets pointer/count; close orders flush/free/close and frees filename only after successful close; access uses attributes/write bit and actual A import, without added ACL or mode validation', 'runtime_unknowns': 'Caller-held stream lock, real stream/handle/buffer/name ownership, write/close results, caller path/mode, ACP and runtime error state'}

CODE_SIZES = {'0x00654953': 43, '0x00653E01': 76, '0x00652588': 93, '0x00641B37': 70}

SEH_SCOPES = []

COMMON_GLOBALS = []

SOURCE_ALTERNATIVES = [{'member_offset': 322512, 'member': 'build\\intel\\mt_obj\\waccess.obj', 'member_sha256': '6b2e355480ea545f714cdd4a9749a28b2f0fd5a44750f3b9f32a0e6e365f10ad', 'coff_symbol': '__waccess', 'address': '0x00641B37', 'size': 70, 'extent_basis': 'function-auxiliary-record', 'decision': 'rejected-library-variant', 'source_definition': {'symbol': '__waccess', 'offset': 0, 'section': 2, 'type': 32, 'storage': 2}, 'source_sha256': 'a32d418ec43021d6616da469f7354dffc13fd40106c30dc3e394644195711aa8', 'body_sha256': '62619770567d0342409030b37bf71c57f2242608f0e99458a80ad9b8d9b7f9e4', 'relocation_bindings': [{'offset': 6, 'type': 'DIR32', 'symbol': '__imp__GetFileAttributesW@4', 'addend': 0, 'local_symbol_offset': None, 'target_address': '0x0065718C', 'target_kind': 'import', 'dll': 'KERNEL32.dll', 'import_name': 'GetFileAttributesW'}, {'offset': 17, 'type': 'DIR32', 'symbol': '__imp__GetLastError@0', 'addend': 0, 'local_symbol_offset': None, 'target_address': '0x00657080', 'target_kind': 'import', 'dll': 'KERNEL32.dll', 'import_name': 'GetLastError'}, {'offset': 23, 'type': 'REL32', 'symbol': '__dosmaperr', 'addend': 0, 'local_symbol_offset': None, 'target_address': '0x00647FAA', 'target_kind': 'callee', 'code_entry': {'owner': '0x00647FAA', 'source_member_offset': 280602, 'source_offset': 0, 'source_definition': {'symbol': '__dosmaperr', 'offset': 0, 'section': 9, 'type': 32, 'storage': 2}}}, {'offset': 44, 'type': 'REL32', 'symbol': '__errno', 'addend': 0, 'local_symbol_offset': None, 'target_address': '0x00647F98', 'target_kind': 'callee', 'code_entry': {'owner': '0x00647F98', 'source_member_offset': 280602, 'source_offset': 0, 'source_definition': {'symbol': '__errno', 'offset': 0, 'section': 3, 'type': 32, 'storage': 2}}}, {'offset': 55, 'type': 'REL32', 'symbol': '___doserrno', 'addend': 0, 'local_symbol_offset': None, 'target_address': '0x00647FA1', 'target_kind': 'callee', 'code_entry': {'owner': '0x00647FA1', 'source_member_offset': 280602, 'source_offset': 0, 'source_definition': {'symbol': '___doserrno', 'offset': 0, 'section': 6, 'type': 32, 'storage': 2}}}], 'rejected_import_field': 6, 'actual_import_name': 'GetFileAttributesA', 'required_import_name': 'GetFileAttributesW', 'basis': 'Complete equal-shaped vendor variant; actual PE slot at 0x0065718C imports GetFileAttributesA and rejects the wide variant'}]
PATH_DISPATCH = [{'site': '0x00641B3B', 'operand': 'dword ptr [0x65718c]'}, {'site': '0x00641B46', 'operand': 'dword ptr [0x657080]'}]

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/stream-finalization-origin-evidence.json').read_text())
    identity = module('stream_finalization_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R140' or m['target_sha256'] != identity.TARGET:
        raise ValueError('stream-finalization target identity differs')
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
    if len(m['functions']) != 4 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete stream-finalization cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != CODE_SIZES[key]
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('stream-finalization function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=0 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('stream-finalization loses complete auxiliary owners')
    if (len(m['interior_labels']) != 0 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('stream-finalization shared entries lose complete source parents or gain standalone credit')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence']) for r in m['anchors']] != ANCHORS:
        raise ValueError('stream-finalization independent complete anchors differ')
    if any(m[k] for k in (
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('stream-finalization graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 0 or sum(r['size'] for r in m['state_data']) != 0
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('stream-finalization graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 112 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural stream-finalization operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R139',manifest='floating-operation-origin-evidence.json')]:
        raise ValueError('stream-finalization loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('stream-finalization graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('stream-finalization shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('stream-finalization direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('stream-finalization table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    return rows


def check_parent_protocol(m, graph):
    if m['stream_protocol']!=IO_PROTOCOL or m['call_controls']!=CALL_CONTROLS:
        raise ValueError('stream complete ownership/layout/error/ABI controls differ')
    if any(m[k] for k in ('auxiliary_bodies','interior_labels','retained_labels','diagnostic_contexts',
                          'scope_tables','common_globals','code_carriers','extent_reconciliations')):
        raise ValueError('stream gains unsupported owners/scopes or invented inventory credit')
    if m['source_alternatives']!=SOURCE_ALTERNATIVES:
        raise ValueError('stream loses complete independently rejected wide variant')
    if set(m['vendor_sources'])!=VENDOR_SOURCES or set(m['sdk_layout']['headers'])!=LAYOUT_HEADERS:
        raise ValueError('stream loses complete available source/header context')
    for row in graph.values():
        if row['code_regions']!=[dict(offset=0,size=row['size'])] or row['code_size']!=row['size']:
            raise ValueError('stream loses complete source code/data partition')
        if row.get('embedded_tables'):
            raise ValueError('stream gains unsupported code tables')
    witnesses=lambda key:{(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    required={
        '0x00654953':{('test','al, 0x83'),('test','al, 8'),('push','dword ptr [esi + 8]'),('call','0x642a61'),('and','word ptr [esi + 0xc], 0xfbf7'),('mov','dword ptr [esi], eax'),('mov','dword ptr [esi + 8], eax'),('mov','dword ptr [esi + 4], eax')},
        '0x00653E01':{('test','byte ptr [esi + 0xc], 0x83'),('call','0x652588'),('call','0x654953'),('push','dword ptr [esi + 0x10]'),('call','0x6548b8'),('jge','0x653e32'),('mov','eax, dword ptr [esi + 0x1c]'),('call','0x642a61'),('and','dword ptr [esi + 0x1c], 0'),('and','dword ptr [esi + 0xc], 0')},
        '0x00652588':{('and','cl, 3'),('cmp','cl, 2'),('test','ax, 0x108'),('sub','edi, eax'),('jle','0x6525d6'),('call','0x64ef70'),('add','esp, 0xc'),('cmp','eax, edi'),('and','eax, 0xfffffffd'),('or','dword ptr [esi + 0xc], 0x20'),('or','ebx, 0xffffffff'),('and','dword ptr [esi + 4], 0'),('mov','dword ptr [esi], eax')},
        '0x00641B37':{('cmp','eax, -1'),('call','0x647faa'),('test','al, 1'),('test','byte ptr [esp + 8], 2'),('call','0x647f98'),('mov','dword ptr [eax], 0xd'),('call','0x647fa1'),('mov','dword ptr [eax], 5')},
    }
    for key,expected in required.items():
        if not expected<=witnesses(key):
            raise ValueError('stream loses actual ownership/flush/close/path/error behavior')
    for row in m['functions']:
        expected=PATH_DISPATCH if row['address']=='0x00641B37' else []
        if row['indirect_calls']!=expected or row['indirect_jumps']:
            raise ValueError('stream gains unsupported indirect dispatch')
        if not row['body_facts']['returns'] or any(r['cleanup']!=0 for r in row['body_facts']['returns']):
            raise ValueError('stream loses observed caller-cleaned returns')
    access=graph['0x00641B37']
    expected={(6,'__imp__GetFileAttributesA@4','GetFileAttributesA'),(17,'__imp__GetLastError@0','GetLastError')}
    if {(b['offset'],b['symbol'],b.get('import_name')) for b in access['relocation_bindings'] if b['target_kind']=='import'}!=expected:
        raise ValueError('stream path lacks actual A/error API identity')


def check_rejected_variant_import(row, imports):
    field=next((b for b in row['relocation_bindings'] if b['offset']==row['rejected_import_field']),None)
    if (not field or field['type']!='DIR32' or field['target_kind']!='import'
            or field['symbol']!='__imp__GetFileAttributesW@4'
            or field['import_name']!=row['required_import_name']
            or row['required_import_name']!='GetFileAttributesW'
            or row['actual_import_name']!='GetFileAttributesA'
            or imports.get(int(field['target_address'],16))!=(field['dll'],row['actual_import_name'])):
        raise ValueError('wide variant rejection loses actual independent PE import contradiction')


def check_path_dispatch(m, decoded, imports, startup):
    row=next(r for r in m['functions'] if r['address']=='0x00641B37')
    base=int(row['address'],16);seen=[]
    for i in decoded[row['address']]:
        if i.mnemonic!='call' or i.operands[0].type==X86_OP_IMM:continue
        op=i.operands[0]
        if op.type!=X86_OP_MEM or op.mem.base or op.mem.index:
            raise ValueError('stream path API call loses actual absolute IAT addressing')
        field=next((b for b in row['relocation_bindings'] if b['offset']==i.address-base+i.disp_offset),None)
        if (not field or field['type']!='DIR32' or field['target_kind']!='import'
                or int(field['target_address'],16)!=op.mem.disp):
            raise ValueError('stream path API call loses actual typed instruction field')
        startup.check_import_binding(field,imports);seen.append(dict(site=f'0x{i.address:08X}',operand=i.op_str))
    if seen!=PATH_DISPATCH:
        raise ValueError('stream path loses full API dispatch inventory')


def decode_code(row,raw,address,decoder):
    return [i for region in row['code_regions']
            for i in decoder.disasm(raw[region['offset']:region['offset']+region['size']],address+region['offset'])]


def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('stream-finalization function loses its complete own AUX extent')
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
        raise ValueError('stream-finalization cleanup gains an invented source entry')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('stream-finalization loses complete origin-only extent')
    if (origin['evidence_id'] != 'R140' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('stream-finalization canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('stream-finalization shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R140' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('stream-finalization shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('stream-finalization external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('stream-finalization member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('stream_finalization_old','verify-runtime-error-origins.py')
    c = module('stream_finalization_target','compare-coff-function.py')
    archive_reader = module('stream_finalization_archive','verify-runtime-origins.py')
    coff = module('stream_finalization_coff','coff_data.py')
    startup = module('stream_finalization_geometry','verify-startup-dependency-origins.py')
    record = module('stream_finalization_ledger','verify-vendor-record-origins.py')
    facts = module('stream_finalization_facts','verify-game-lifetime-origins.py')
    imports_module = module('stream_finalization_imports','verify-import-origins.py')
    literal = module('stream_finalization_scalar','verify-runtime-external-origins.py')
    sections = module('stream_finalization_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete stream-finalization source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('stream-finalization complete primary loses an actual interior candidate')
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
            raise ValueError('stream-finalization whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('stream-finalization source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('stream-finalization state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('stream-finalization whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('stream-finalization initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('stream-finalization complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('stream-finalization state loses whole writable target storage')
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
    scratch = ROOT / 'build/origin-stream-finalization-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural stream-finalization control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned stream-finalization control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_StreamFinalizationLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural stream-finalization data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural FILE/SDK offsets or ownership/error constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete stream-finalization vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete stream ownership/error/path controls differ')
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R139'):
                    raise ValueError('stream-finalization retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('stream-finalization complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('stream-finalization full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('stream-finalization whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('stream-finalization complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('stream-finalization field lacks member-local/whole strong data provenance')
        for alternative in m['source_alternatives']:
            path.write_bytes(member(alternative));source,fields=object_code(path,alternative,c,coff)
            a=int(alternative['address'],16);actual=c.pe_bytes_at(target,a,alternative['size'])
            defs=coff.parse_symbols(member(alternative),c.coff_name)[1]
            primary=next(d for d in defs if d['symbol']==alternative['coff_symbol'])
            if (primary!=alternative['source_definition'] or len(source)!=alternative['size']
                    or hashlib.sha256(source).hexdigest()!=alternative['source_sha256']
                    or hashlib.sha256(actual).hexdigest()!=alternative['body_sha256']):
                raise ValueError('wide alternative loses complete defining own-AUX source')
            # Full byte congruence remains diagnostic: API identity independently rejects it.
            old.compare_fields(source,fields,actual,a,alternative['relocation_bindings'],c)
            check_rejected_variant_import(alternative,imports)
            for field in alternative['relocation_bindings']:
                if field['offset']==alternative['rejected_import_field']:continue
                if field['target_kind']=='import':startup.check_import_binding(field,imports)
                elif field['target_kind']=='callee':check_code_entry(field,graph)
                else:raise ValueError('wide alternative retains an unsupported field')
        check_path_dispatch(m,decoded,imports,startup)
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('stream-finalization code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('stream-finalization local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('stream-finalization direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('stream-finalization direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('stream-finalization same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('stream-finalization shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('stream-finalization complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('stream-finalization data pointer does not reach a complete actual code entry')
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
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-floating-operation-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R139 graph replay failed: '+result.stderr[-1500:])
    print('R140 origins OK: four complete stream finalization/path-access primaries / 282 bytes / 11 typed fields; six full anchors / 572 bytes / 42 fields; complete 70-byte five-field wide vendor alternative independently rejected by actual A import; cold 112-byte FILE/SDK layouts and complete 92-/172-/131-/92-/92-byte natural ownership/error/API controls; all five original vendor sources and nine headers; full retained R139 graph; local acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
