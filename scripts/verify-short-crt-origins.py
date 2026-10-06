#!/usr/bin/env python3
"""Replay bounded short CRT provenance while preserving unsupported leaf ownership."""
from __future__ import annotations
import argparse
import csv
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
KEYS = {'0x006426A1': ('_atoi', 5, 157246, 'library'),
        '0x00643FC6': ('__finite', 21, 2915526, 'pending'),
        '0x0064554E': ('__seh_longjmp_unwind@4', 27, 1221154, 'library'),
        '0x0064F513': ('__FillZeroMan', 12, 2436458, 'pending'),
        '0x00651D44': ('__ui64toa', 27, 232636, 'library')}
PROFILE = ['/O1', '/Oi', '/Ob0', '/Gy', '/GR-', '/GX', '/Zi', '/GS', '/I', 'src', '/showIncludes']
LAYOUT = [64, 64, 0, 24, 28, 4, 8, 2, 12, 16, 1024]
CONFIDENCE = 'complete-vendor-short-crt-typed-sdk-independent-runtime-and-carrier-provenance'
MANIFEST_SHA256 = 'f46b071ab92cb29e63c03d9f18af025ddfc5100b07fd2e3079b76376edd11c1d'
RETAINED = ['verify-codepage-nls-origins.py', 'verify-jump-unwind-origins.py',
            'verify-security-eh-origins.py', 'verify-runtime-origins.py']


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


BUFFER = module('short_crt_buffer', 'verify-script-buffer-origins.py')


def digest(data):
    return hashlib.sha256(data).hexdigest()


def manifest():
    return json.loads((ROOT / 'config/short-crt-origin-evidence.json').read_text())


def rows(filename):
    with (ROOT / 'config' / filename).open(newline='') as stream:
        return list(csv.DictReader(stream))


def verify_plan(m):
    if (m['evidence_id'] != 'R155' or m['probe'] != 'probes/VC7ShortCrtCalls.cpp'
            or m['profile'] != PROFILE or m['layout'] != LAYOUT
            or len(m['functions']) != 5
            or {r['address']: (r['symbol'], r['size'], r['member_offset'], r['decision']) for r in m['functions']} != KEYS
            or len(m['controls']) != 8 or sum(r['size'] for r in m['controls']) != 109
            or len(m['sections']) != 9 or sum(r['size'] for r in m['sections']) != 153
            or len(m['headers']) != 5 or m['retained_verifiers'] != RETAINED
            or len(m['independent']) != 3
            or [(r['row']['address'], r['row']['size']) for r in m['independent']] !=
               [('0x00642619', 136), ('0x00640B66', 104), ('0x00645468', 230)]
            or m['x64']['address'] != '0x00651CA6' or int(m['x64']['size']) != 109
            or m['x64']['coff_symbol'] != '_x64toa@20'
            or m['carrier']['address'] != '0x00645460' or m['carrier']['size'] != 265
            or m['carrier']['section']['size'] != 265 or len(m['carrier']['bindings']) != 6):
        raise ValueError('short CRT cohort loses complete source/SDK/independent carrier provenance')
    expected = {'0x006426A1': (1, '_atol', '0x00642619'),
                '0x0064554E': (16, '__local_unwind2', '0x00640B66'),
                '0x00651D44': (18, '_x64toa@20', '0x00651CA6')}
    for row in m['functions']:
        fields = row['bindings']
        if row['decision'] == 'pending':
            if fields:
                raise ValueError('unsupported leaf gains fabricated independent typed provenance')
        elif (len(fields) != 1 or fields[0]['type'] != 'REL32' or fields[0]['addend']
              or (fields[0]['offset'], fields[0]['symbol'], fields[0]['target_address']) != expected[row['address']]):
            raise ValueError('short CRT call/tail is masked or binds an unrelated source operation')
    pending = m['pending_controls']
    if (len(pending) != 2 or [(r['address'], r['target_size'], r['source_size'], r['result']) for r in pending] !=
            [('0x00643FC6', 21, 20, 'different-complete-extents'),
             ('0x0064F513', 12, 12, 'complete-unmasked-equal')]):
        raise ValueError('short CRT pending source alternative is truncated or falsely accepted')
    controls = {r['symbol']: r for r in m['controls']}
    sections = {r['section']: r for r in m['sections']}
    for control in m['controls']:
        definition = control['source_definition']
        section = sections.get(definition['section'])
        if (not section or definition not in section['definitions'] or definition['offset']
                or section['size'] != control['size'] or section['source_sha256'] != control['source_sha256']):
            raise ValueError('SDK/source owner loses its complete defining carrier')
    definitions = m['carrier']['section']['definitions']
    for symbol, offset in [('__except_handler3', 8), ('__seh_longjmp_unwind@4', 238)]:
        if len([d for d in definitions if d['symbol'] == symbol and d['offset'] == offset and d['type'] == 32]) != 1:
            raise ValueError('SEH carrier loses actual whole handler/longjmp source definitions')
    if [(f['offset'], f['symbol'], f['target_address']) for f in m['x64_fields']] != [('0x2f', '__aulldvrm', '0x0064F280')]:
        raise ValueError('independent wide formatter loses original typed division dependency')
    for p in pending:
        if p['symbol'] not in controls or controls[p['symbol']]['size'] != p['source_size'] or controls[p['symbol']]['fields']:
            raise ValueError('pending source alternative lacks its complete genuine own extent')
    expected_sdk = {'?ParseDecimalText@@YAHPBD@Z': '_atoi', '?CheckFiniteSdk@@YAHN@Z': '__finite',
                    '?FormatUnsignedWide@@YAPAD_KPADH@Z': '__ui64toa', '?RestoreSdkJump@@YAXQAHH@Z': '_longjmp'}
    for symbol, callee in expected_sdk.items():
        fields = controls[symbol]['fields']
        if len(fields) != 1 or fields[0]['symbol'] != callee or fields[0]['type'] != 'REL32' or fields[0]['addend']:
            raise ValueError('SDK declared operation loses its actual typed source field')
    seh = next(r for r in m['functions'] if r['address'] == '0x0064554E')
    if [r['operands'] for r in seh['instructions']] != [
            'ebp', 'ecx, dword ptr [esp + 8]', 'ebp, dword ptr [ecx]',
            'eax, dword ptr [ecx + 0x1c]', 'eax', 'eax, dword ptr [ecx + 0x18]',
            'eax', '0x640b66', 'esp, 8', 'ebp', '4']:
        raise ValueError('SEH longjmp loses complete real SDK saved-frame/registration/try-level protocol')


def check_ledger(row, function, origin, evidence_only=False):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['calling_convention'] or function['signature']
            or function['match_percent'] != '0.00'):
        raise ValueError('short CRT changes complete extent or grants source/ABI/exact')
    if row['decision'] == 'pending':
        if row['address'] == '0x0064F513' and origin['evidence_id'] == 'R260':
            transition = module('short_crt_contribution_transition', 'verify-vendor-zeroing-contribution-origins.py')
            plan = json.loads((ROOT / transition.EVIDENCE).read_text())
            previous = next(r for r in plan['functions'] if r['address'] == row['address'])
            if transition.allows_transition(row['address'], previous['original_function'],
                    previous['original_origin'], function, origin):
                return
        if row['address'] == '0x00643FC6' and origin['evidence_id'] == 'R192':
            transition = module('short_crt_dispatch_transition', 'verify-sdk-dispatch-origins.py')
            manifest = json.loads((ROOT/transition.EVIDENCE).read_text())
            previous = next(r for r in manifest['functions'] if r['address'] == row['address'])
            if transition.allows_transition(row['address'], previous['original_function'],
                    previous['original_origin'], function, origin):
                return
        if (origin['origin'] != 'unknown' or origin['disposition'] != 'review'
                or function['owner'] or function['module'] or function['status'] != 'unclassified'
                or function['proposed_name']):
            raise ValueError('unsupported short CRT leaf gains origin or mapped-name credit')
    elif not evidence_only and (origin['origin'] != 'library' or origin['disposition'] != 'exclude'
            or origin['subsystem'] != 'VC71CRT' or origin['evidence_id'] != 'R155' or origin['confidence'] != CONFIDENCE
            or function['owner'] != 'library' or function['module'] != 'VC71CRT'
            or function['status'] != 'excluded' or function['proposed_name'] != row['symbol']):
        raise ValueError('short CRT canonical complete library acceptance differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    m = manifest()
    verify_plan(m)
    if digest((ROOT / 'config/short-crt-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('reviewed short CRT metadata differs')
    c = module('short_crt_target', 'compare-coff-function.py')
    coff = module('short_crt_coff', 'coff_data.py')
    record = module('short_crt_extent', 'verify-vendor-record-origins.py')
    runtime = module('short_crt_archive', 'verify-runtime-origins.py')
    target = c.verified_target()
    if digest(target) != m['target_sha256'] or digest((ROOT / m['probe']).read_bytes()) != m['probe_sha256']:
        raise ValueError('short CRT target or natural SDK/source controls differ')
    functions = {r['address']: r for r in rows('functions.csv')}
    origins = {r['address']: r for r in rows('function-origins.csv')}
    for row in m['functions']:
        check_ledger(row, functions[row['address']], origins[row['address']], args.evidence_only)
    for entry in m['independent']:
        prior = json.loads((ROOT / entry['manifest']).read_text())[entry['collection']]
        row = entry['row']
        if (row not in prior if isinstance(prior, list) else row != prior):
            raise ValueError('short CRT changes independent original full-runtime metadata')
        if digest(c.pe_bytes_at(target, int(row['address'], 16), row['size'])) != row['body_sha256']:
            raise ValueError('short CRT independent runtime loses its full original boundary/hash')
    if m['x64'] not in rows('runtime-origin-evidence.csv') or m['x64_fields'] != [r for r in rows('runtime-origin-relocations.csv') if r['address'] == '0x00651CA6']:
        raise ValueError('short CRT rewrites original whole R007 wide formatter/typed division evidence')
    for address, evidence in [('0x00642619', 'R123'), ('0x00640B66', 'R025'), ('0x00651CA6', 'R007')]:
        if origins[address]['origin'] != 'library' or origins[address]['evidence_id'] != evidence:
            raise ValueError('short CRT callee loses independent original origin')
    for name in m['retained_verifiers']:
        result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts' / name)],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise ValueError('short CRT full retained provenance failed: ' + name + ': ' + result.stderr[-1500:])
        print('retained ' + name + ': ' + result.stdout.splitlines()[-1], flush=True)
    archive = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(archive) != m['archive_sha256']:
        raise ValueError('short CRT archive identity differs')
    members = {offset: (name, data) for offset, name, data in runtime.archive_members(archive)}
    catalog = {'_atol': 0x00642619, '__local_unwind2': 0x00640B66, '_x64toa@20': 0x00651CA6}
    scratch = ROOT / 'build/origin-short-crt-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        temporary = Path(dirname)
        for row in m['functions']:
            name, data = members[row['member_offset']]
            if name != row['member'] or digest(data) != row['member_sha256']:
                raise ValueError('short CRT complete source member differs')
            path = temporary / (str(row['member_offset']) + '.obj')
            path.write_bytes(data)
            # No size override: require the positive own AUX extent, including
            # the 27-byte owner inside the larger exsup3 code carrier.
            source, fields = c.object_function(path, row['symbol'])
            actual = c.pe_bytes_at(target, int(row['address'], 16), row['size'])
            if (len(source) != row['size'] or fields != row['fields']
                    or digest(source) != row['source_sha256'] or digest(actual) != row['body_sha256']
                    or BUFFER.PRIOR.link_complete(source, fields, int(row['address'], 16), row['bindings'], catalog) != actual):
                raise ValueError('short CRT whole own-AUX source/actual typed fields fail unmasked comparison')
            instructions = [dict(address=f'0x{i.address:08X}', mnemonic=i.mnemonic, operands=i.op_str)
                            for i in Cs(CS_ARCH_X86, CS_MODE_32).disasm(actual, int(row['address'], 16))]
            if instructions != row['instructions']:
                raise ValueError('short CRT complete return/tail/control inventory differs')
        carrier = m['carrier']
        data = members[carrier['member_offset']][1]
        observed = next(r for r in BUFFER.inventory(data, c, coff) if r['section'] == carrier['section']['section'])
        if observed != carrier['section']:
            raise ValueError('SEH whole carrier source definitions/fields differ')
        head = struct.unpack_from('<8sIIIIIIHHI', data, 20 + (observed['section'] - 1) * 40)
        source = data[head[4]:head[4] + head[3]]
        source_fields = [dict(offset=f['offset'], type=f['type'], symbol=f['symbol']['symbol'],
                              addend=f['addend'], local_symbol_offset=None) for f in observed['fields']]
        actual = c.pe_bytes_at(target, int(carrier['address'], 16), carrier['size'])
        handler = m['independent'][2]['row']
        full_catalog = {f['symbol']: int(f['target_address'], 16) for f in handler['relocation_bindings']}
        if (source_fields != carrier['fields'] or digest(source) != carrier['source_sha256']
                or digest(actual) != carrier['body_sha256']
                or BUFFER.PRIOR.link_complete(source, source_fields, int(carrier['address'], 16), carrier['bindings'], full_catalog) != actual):
            raise ValueError('SEH complete 265-byte carrier/header/handler/longjmp fields differ')
        path = temporary / 'VC7ShortCrtCalls.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / m['probe']), str(path), *m['profile']],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode or BUFFER.PRIOR.PRIOR.included_headers(result.stdout + result.stderr) != m['headers']:
            raise ValueError('short CRT cold compiler/SDK includes differ')
        data = path.read_bytes()
        if BUFFER.inventory(data, c, coff) != m['sections']:
            raise ValueError('short CRT ordinary whole code/data inventory differs')
        for row in m['controls']:
            size = record.complete_aux_section_size(data, row['symbol'], c.coff_name)
            source, fields = c.object_function(path, row['symbol'])
            if size != row['size'] or digest(source) != row['source_sha256'] or fields != row['fields']:
                raise ValueError('short CRT actual complete SDK/source operation differs')
        for row in m['pending_controls']:
            source, fields = c.object_function(path, row['symbol'])
            actual = c.pe_bytes_at(target, int(row['address'], 16), row['target_size'])
            if (len(source) != row['source_size'] or fields
                    or (source == actual) != (row['result'] == 'complete-unmasked-equal')):
                raise ValueError('short CRT pending control was truncated or lost its ownership ambiguity')
        layout = next(r for r in m['sections'] if any(d['symbol'] == '_ShortCrtCallLayout' for d in r['definitions']))
        source, _ = coff.readonly_section(data, layout['section'], c.coff_name)
        if list(struct.unpack('<11I', source)) != LAYOUT:
            raise ValueError('short CRT whole actual SDK/observation layout differs')
    print('R155 origins OK: three complete library owners / 59 bytes; historical pending finite21/FillZeroMan12 controls retained, with only immutable R192 finite and R260 complete-contribution acceptance allowed; actual typed fields linked unmasked through unchanged independent atol/unwind/wide-format owners; entire 265-byte SEH carrier/header/handler/longjmp and all six fields; eight cold complete SDK/source controls / 109 bytes, nine whole code/data sections / 153 bytes and real 44-byte layout; complete ordinary memset control equals all twelve pending bytes; no prefix/source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError, KeyError, IndexError, StopIteration, ValueError, struct.error, json.JSONDecodeError) as error:
        print('error: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
