#!/usr/bin/env python3
"""F599: cold original-PE/COFF checks of two natural 116-byte member copies.

This is *compiler-source-shape evidence*, not proof of original authored
source or permission to credit either unknown-origin complete function.
Compile only the one new VC7.1 probe translation unit; no all-unit replay.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import struct
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'probes/Record116ImplicitCopyF599.cpp'
OUT = ROOT / '.analysis/f599-record116-source'
READER_PATH = ROOT / 'scripts/compare-coff-function.py'
PROFILE = ['/Od', '/Ob0', '/Gy', '/GR-', '/GX', '/GS', '/Zi']
# Offsets are *entire original function* relocatable instruction operands,
# reconstructed as typed COFF records, not target bytes embedded in source.
CASES = (
    {
        'name': 'compiler-generated-record-assignment',
        'address': 0x0045AAE0,
        'size': 368,
        'instructions': 118,
        'symbol': '??4Record116F599@@QAEAAU0@ABU0@@Z',
        'fields': (
            (0x151, 'REL32', '??4OwnedSixteen@@QAEAAU0@ABU0@@Z', 0x0045AC50),
            (0x163, 'REL32', '??4OwnedSixteen@@QAEAAU0@ABU0@@Z', 0x0045AC50),
        ),
    },
    {
        'name': 'compiler-generated-record-copy-ctor-with-EH',
        'address': 0x004591E0,
        'size': 417,
        'instructions': 128,
        'symbol': '??0Record116F599@@QAE@ABU0@@Z',
        'fields': (
            (0x006, 'DIR32', '__ehhandler$??0Record116F599@@QAE@ABU0@@Z', 0x00656273),
            (0x00C, 'DIR32', '__except_list', 0x00000000),
            (0x014, 'DIR32', '__except_list', 0x00000000),
            (0x16D, 'REL32', '??0OwnedSixteen@@QAE@ABU0@@Z', 0x00459390),
            (0x183, 'REL32', '??0OwnedSixteen@@QAE@ABU0@@Z', 0x00459390),
            (0x197, 'DIR32', '__except_list', 0x00000000),
        ),
    },
)


def need(test: bool, detail: str) -> None:
    if not test:
        raise ValueError(detail)


def reader_module():
    spec = importlib.util.spec_from_file_location('f599_pe_reader', READER_PATH)
    need(spec is not None and spec.loader is not None, 'missing pinned original PE reader')
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def compile_source(name: str, gx: str) -> Path:
    OUT.mkdir(parents=True, exist_ok=True)
    obj = OUT / (name + '.obj')
    env = os.environ.copy()
    env.pop('DISPLAY', None)
    env.pop('WAYLAND_DISPLAY', None)
    env['WINEPREFIX'] = str(ROOT / '.analysis/vc71-wine')
    env['WINEDLLOVERRIDES'] = 'winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    flags = [f'/GX{gx}' if flag == '/GX' else flag for flag in PROFILE]
    result = subprocess.run(
        [str(ROOT / 'scripts/compile-probe.sh'), str(SOURCE), str(obj), *flags],
        env=env, cwd=ROOT, capture_output=True, text=True, timeout=180,
    )
    (OUT / (name + '.compile.log')).write_text(result.stdout + result.stderr)
    need(result.returncode == 0, f'original-profile VC7.1 compile failed: {result.stderr}')
    return obj


def prove_case(reader, pe: bytes, decoder, obj: Path, case: dict) -> dict:
    address, size = case['address'], case['size']
    original = reader.pe_bytes_at(pe, address, size)
    # Generated special members have no COFF function auxiliary size record;
    # pass the full original extent to the shared independent COFF parser.
    code, refs = reader.object_function(obj, case['symbol'], size)
    need(len(code) == size, f'{address:08X}: original whole CODE size differs')
    native_insns = list(decoder.disasm(original, address))
    generated_insns = list(decoder.disasm(code, address))
    need(len(native_insns) == len(generated_insns) == case['instructions']
         and sum(ins.size for ins in native_insns) == size
         and sum(ins.size for ins in generated_insns) == size
         and all((a.address, a.size, a.mnemonic) == (b.address, b.size, b.mnemonic)
                 for a, b in zip(native_insns, generated_insns)),
         f'{address:08X}: original complete native code geometry/mnemonic order differs')
    need(len(refs) == len(case['fields']), f'{address:08X}: physical source COFF field count differs')
    linked = bytearray(code)
    solved = []
    reloc_mask = set()
    for r, (offset, typ, symbol, destination) in zip(refs, case['fields']):
        need(r['offset'] == offset and r['type'] == typ and r['symbol'] == symbol
             and r['local_symbol_offset'] is None and r['addend'] == 0,
             f'{address:08X}: original typed COFF position/owner/addend differs')
        reloc_mask.update(range(offset, offset + 4))
        target_word = struct.unpack_from('<I', original, offset)[0]
        target_destination = ((address + offset + 4 + struct.unpack_from('<i', original, offset)[0]) & 0xFFFFFFFF) if typ == 'REL32' else target_word
        need(target_destination == destination,
             f'{address:08X} field +{offset:03X}: original native callee/handler differs')
        assembled = ((destination - address - offset - 4) if typ == 'REL32' else destination) & 0xFFFFFFFF
        struct.pack_into('<I', linked, offset, assembled)
        solved.append({'offset':f'0x{offset:X}', 'type':typ,
                       'source_COFF':symbol,'original_destination':f'0x{destination:08X}'})
    equal_nonfield = sum(code[i] == original[i] for i in range(size) if i not in reloc_mask)
    comparable = size - len(reloc_mask)
    need(equal_nonfield == comparable and linked == original,
         f'{address:08X}: full original PE not identical after typed original relocations')
    return {'function': case['name'], 'original_address':f'0x{address:08X}',
            'whole_native_CODE_bytes':size, 'original_x86_instructions':case['instructions'],
            'entire_CODE_original_offsets_lengths_mnemonics_equal': True,
            'whole_nonrelocation_exact_bytes':equal_nonfield,
            'whole_nonrelocation_comparable_bytes':comparable,
            'native_PE_backed_source_COFF_fields':solved,
            'all_original_linked_CODE_bytes_equal':True,
            'original_authored_origin_proven':False,
            'accepted_exact_authored_bytes':0}


def main():
    cli=argparse.ArgumentParser(description=__doc__)
    cli.add_argument('--with-negative-gxoff', action='store_true',
                     help='also compile one non-EH control, which must miss 417-byte ctor')
    opts=cli.parse_args()
    source=SOURCE.read_text()
    need('no asm or machine-byte patches' in source
         and 'Record116F599SizeGuard' in source,
         'original-source-shape probe unexpectedly changed')
    reader=reader_module()
    pe=reader.verified_target()
    decoder=Cs(CS_ARCH_X86, CS_MODE_32)
    obj=compile_source('implicit-GX', '')
    results=[prove_case(reader,pe,decoder,obj,case) for case in CASES]
    if opts.with_negative_gxoff:
        negative=compile_source('implicit-GX-off', '-')
        code, refs=reader.object_function(negative, CASES[1]['symbol'], 368)
        need(len(code)==368 and len(refs)==2,
             'non-EH control unexpectedly emits original 417-byte copy ctor')
        print('Negative /GX- control: 368-byte ctor, no original 417-byte EH frame',flush=True)
    OUT.mkdir(parents=True,exist_ok=True)
    manifest={'original_SHA256':hashlib.sha256(pe).hexdigest(),
              'probe_source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
              'compiler_object_sha256':hashlib.sha256(obj.read_bytes()).hexdigest(),
              'compiler_profile':' '.join(PROFILE),
              'observed_record_bytes':116,
              'whole_original_functions':results,
              'accepted_authored_CODE_bytes':0,
              'origin': 'unknown (explicit authored code vs implicit generated shape unresolved)',
              'all_unit_cold_replay':False}
    (OUT/'summary.json').write_text(json.dumps(manifest,indent=2)+'\n')
    for result in results:
        print(f"F599: {result['original_address']} whole {result['whole_native_CODE_bytes']}/"
              f"{result['whole_native_CODE_bytes']} original bytes, "
              f"{result['original_x86_instructions']} complete x86 instructions, "
              f"{len(result['native_PE_backed_source_COFF_fields'])} original physical "
              f"COFF fields; actual native destination and fully linked CODE exact",flush=True)
    print('F599: two authentic natural *implicit* C++ member functions verified. '
          'Original authored-vs-compiler ownership remains UNKNOWN; '
          'zero newly accepted game CODE, no all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 F599 original source-shape proof failed:',exc,file=sys.stderr)
        raise SystemExit(1)
