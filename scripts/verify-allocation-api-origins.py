#!/usr/bin/env python3
"""Replay complete CRT allocation API owners and natural SDK call provenance."""
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
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
KEYS = {'0x0064159D': ('??2@YAPAXI@Z', 14, 856822),
        '0x0064169D': ('??_V@YAXPAX@Z', 5, 854462),
        '0x006416A2': ('??_U@YAPAXI@Z', 5, 858348)}
CONFIDENCE = 'complete-vendor-allocation-api-typed-sdk-runtime-and-game-context'
MANIFEST_SHA256 = '88471391a30ca23574ab4409b5504df592fee47d2e23c368bbc71b204eb6531c'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


BUFFER = module('allocation_buffer', 'verify-script-buffer-origins.py')


def digest(data):
    return hashlib.sha256(data).hexdigest()


def manifest():
    return json.loads((ROOT / 'config/allocation-api-origin-evidence.json').read_text())


def verify_plan(m):
    if (m['evidence_id'] != 'R154' or m['probe'] != 'probes/VC7AllocationCalls.cpp'
            or m['profile'] != BUFFER.PROFILE or len(m['functions']) != 3
            or {r['address']: (r['symbol'], r['size'], r['member_offset']) for r in m['functions']} != KEYS
            or any(r['decision'] != 'library' for r in m['functions'])
            or len(m['controls']) != 8 or sum(r['size'] for r in m['controls']) != 196
            or len(m['sections']) != 9 or sum(r['size'] for r in m['sections']) != 212
            or m['layout'] != [4, 4, 8, 4]
            or m['retained_verifiers'] != ['verify-runtime-cycle-origins.py', 'verify-script-buffer-origins.py']
            or m['allocation']['address'] != '0x00644305' or m['allocation']['size'] != 44
            or m['allocation']['coff_symbol'] != '__nh_malloc'
            or m['scalar_delete']['address'] != '0x00640F15' or m['scalar_delete']['size'] != 5
            or m['scalar_delete']['coff_symbol'] != '??3@YAXPAX@Z'):
        raise ValueError('allocation API loses bounded whole source/SDK/independent runtime provenance')
    edges = {'0x0064159D': (7, '__nh_malloc', '0x00644305'),
             '0x0064169D': (1, '??3@YAXPAX@Z', '0x00640F15'),
             '0x006416A2': (1, '??2@YAPAXI@Z', '0x0064159D')}
    for r in m['functions']:
        if (len(r['bindings']) != 1 or r['bindings'][0]['type'] != 'REL32' or r['bindings'][0]['addend']
                or (r['bindings'][0]['offset'], r['bindings'][0]['symbol'], r['bindings'][0]['target_address']) != edges[r['address']]):
            raise ValueError('allocation API binds a masked shape or unrelated/incomplete callee')
    new = next(r for r in m['functions'] if r['address'] == '0x0064159D')
    if [(r['mnemonic'], r['operands']) for r in new['instructions']] != [
            ('push', '1'), ('push', 'dword ptr [esp + 8]'), ('call', '0x644305'),
            ('pop', 'ecx'), ('pop', 'ecx'), ('ret', '')]:
        raise ValueError('allocation API loses actual new-handler flag/input/stack protocol')
    counts = {'??_U@YAPAXI@Z': 0, '??_V@YAXPAX@Z': 0, '??2@YAPAXI@Z': 0, '??3@YAXPAX@Z': 0}
    for r in m['controls']:
        fields = r['fields']
        if (len(fields) != 1 or fields[0]['symbol'] not in counts or fields[0]['type'] != 'REL32'
                or fields[0]['addend']):
            raise ValueError('actual SDK control loses a whole declared typed allocation operation')
        counts[fields[0]['symbol']] += 1
    if counts != {'??_U@YAPAXI@Z': 3, '??_V@YAXPAX@Z': 3, '??2@YAPAXI@Z': 1, '??3@YAXPAX@Z': 1}:
        raise ValueError('array/scalar SDK operations are conflated')


def check_ledger(r, function, origin, evidence_only=False):
    if (int(function['size']) != r['size'] or function['span_end'] != r['span_end']
            or function['source_file'] or function['calling_convention'] or function['signature']
            or function['match_percent'] != '0.00'):
        raise ValueError('allocation API changes whole extent or grants source/ABI/exact')
    if not evidence_only and (origin['origin'] != 'library' or origin['disposition'] != 'exclude'
            or origin['subsystem'] != 'VC71CRT' or origin['evidence_id'] != 'R154' or origin['confidence'] != CONFIDENCE
            or function['owner'] != 'library' or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != r['symbol']):
        raise ValueError('allocation API canonical complete library acceptance differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    m = manifest()
    verify_plan(m)
    if digest((ROOT / 'config/allocation-api-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('reviewed allocation API metadata differs')
    comparison = module('allocation_target', 'compare-coff-function.py')
    record = module('allocation_extent', 'verify-vendor-record-origins.py')
    coff = module('allocation_coff', 'coff_data.py')
    archive_reader = module('allocation_archive', 'verify-runtime-origins.py')
    target = comparison.verified_target()
    if digest(target) != m['target_sha256'] or digest((ROOT / m['probe']).read_bytes()) != m['probe_sha256']:
        raise ValueError('allocation API target or natural SDK source differs')
    functions = {r['address']: r for r in record.rows('functions.csv')}
    origins = {r['address']: r for r in record.rows('function-origins.csv')}
    for r in m['functions']:
        check_ledger(r, functions[r['address']], origins[r['address']], args.evidence_only)
    previous = json.loads((ROOT / 'config/runtime-cycle-origin-evidence.json').read_text())
    standard = json.loads((ROOT / 'config/standard-exception-origin-evidence.json').read_text())
    if (m['allocation'] not in previous['functions'] or m['scalar_delete'] not in standard['functions']
            or origins['0x00644305']['origin'] != 'library' or origins['0x00644305']['evidence_id'] != 'R120'
            or origins['0x00640F15']['origin'] != 'library' or origins['0x00640F15']['evidence_id'] != 'R142'):
        raise ValueError('allocation API rewrites independently accepted complete runtime owners')
    for row in [m['allocation'], m['scalar_delete']]:
        if (int(functions[row['address']]['size']) != row['size']
                or digest(comparison.pe_bytes_at(target, int(row['address'], 16), row['size'])) != row['body_sha256']):
            raise ValueError('allocation API loses full unchanged independent runtime boundary')
    for name in m['retained_verifiers']:
        result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts' / name)],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError('allocation API full retained provenance failed: ' + name + ': ' + result.stderr[-1000:])
    archive = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(archive) != m['archive_sha256']:
        raise ValueError('allocation API uses a different vendor archive')
    members = {offset: (name, data) for offset, name, data in archive_reader.archive_members(archive)}
    catalog = {r['symbol']: int(r['address'], 16) for r in m['functions']}
    catalog.update({'__nh_malloc': 0x00644305, '??3@YAXPAX@Z': 0x00640F15})
    scratch = ROOT / 'build/origin-allocation-api-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as name:
        temporary = Path(name)
        for row in m['functions']:
            filename, data = members[row['member_offset']]
            if filename != row['member'] or digest(data) != row['member_sha256']:
                raise ValueError('allocation API loses its complete source archive member')
            path = temporary / (str(row['member_offset']) + '.obj')
            path.write_bytes(data)
            size = record.complete_aux_section_size(data, row['symbol'], comparison.coff_name)
            source, fields = comparison.object_function(path, row['symbol'], size)
            actual = comparison.pe_bytes_at(target, int(row['address'], 16), size)
            if (size != row['size'] or fields != row['fields'] or digest(source) != row['source_sha256']
                    or digest(actual) != row['body_sha256']
                    or BUFFER.PRIOR.link_complete(source, fields, int(row['address'], 16), row['bindings'], catalog) != actual):
                raise ValueError('whole allocation API source/typed fields fail unmasked comparison')
            instructions = [dict(address=f'0x{i.address:08X}', mnemonic=i.mnemonic, operands=i.op_str)
                            for i in Cs(CS_ARCH_X86, CS_MODE_32).disasm(actual, int(row['address'], 16))]
            if instructions != row['instructions']:
                raise ValueError('allocation API complete return/tail inventory differs')
        path = temporary / 'VC7AllocationCalls.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / m['probe']), str(path), *m['profile']],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode or BUFFER.PRIOR.PRIOR.included_headers(result.stdout + result.stderr) != m['headers']:
            raise ValueError('allocation API actual cold SDK include/compiler provenance differs')
        data = path.read_bytes()
        if BUFFER.inventory(data, comparison, coff) != m['sections']:
            raise ValueError('allocation API has an omitted/partial ordinary code/data carrier')
        for row in m['controls']:
            size = record.complete_aux_section_size(data, row['symbol'], comparison.coff_name)
            source, fields = comparison.object_function(path, row['symbol'], size)
            if size != row['size'] or digest(source) != row['source_sha256'] or fields != row['fields']:
                raise ValueError('allocation API SDK call loses a complete own source/AUX/typed field')
        layout = next(s for s in m['sections'] if any(d['symbol'] == '_AllocationCallLayout' for d in s['definitions']))
        raw, _ = coff.readonly_section(data, layout['section'], comparison.coff_name)
        if list(struct.unpack('<4I', raw)) != m['layout']:
            raise ValueError('allocation API loses entire actual SDK observation layout')
    print('R154 origins OK: three complete library allocation API owners / 24 bytes; every actual typed '
          'field linked unmasked through independent whole scalar/array/new-handler owners; eight cold '
          'SDK operations / 196 bytes and nine whole code/data sections / 212 bytes; complete retained '
          'R120 allocation/handler/data/API/EH cold provenance and R153 game pointer/lifetime evidence; '
          'prior extents/owners preserved; runtime outcomes unknown; no source/mapping/private ABI/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, StopIteration, ValueError, struct.error, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
