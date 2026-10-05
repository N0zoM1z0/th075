#!/usr/bin/env python3
"""Verify complete native game switches and independent full receiver contexts."""
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/game-switch-policy-origin-evidence.json'
MANIFEST_SHA256 = 'f72ea7b37b4de087dc4f69dfb6adf3585a86ea66d0f97143b46dd9a1efea5a05'
PLAN_DIGESTS = {'evidence_id': '195cead377781d611ec966be01a087ea23922956de081117b1306b551efba372', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': 'e48891b205c9274487e561895536b731956852d4252158ef58abdb45947e931d', 'anchors': '1cf2743b45e8e67d7f5a3f1e3e52531e52a61bab65be02d6687f5d871cf5182c', 'retained_unknowns': 'd93924fdf57a11d76137d2032812bc29061ac69fb80e7a5761ded6cc448723fc', 'tables': '74b0f53c1c6005e68cf13ef5807729b7f2a67ff16be43cf07b07031a884ac162', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'context': '194738e2a4250d0ec99711cbf99be11f2973060aecc17b6a9f3f5f01f17f7669', 'data': 'cd0751c726ce89778acf5c8a1a7e2337fb8746639637d81356820bd5b50b4d60', 'authored_path': '6bbe8db1af1d51f48096bab894498fe0cec40ad9e0d35223caf22b1c1d5c8600', 'switch_path': 'a6c2b520b39e80d06bdd6acf9d5bed300baa2d26a5c8a114fc8ca7c643d01073', 'direct_switch_path': 'e7c5aebe69d8350edbc255b137285d2e7fac228fb256d01374b64cbde29b743e', 'retained_sha256': '1e0d538db27c52e725db51143b78a81b2371670492d60a9ad2487bb6aac6cca1'}
KEYS = {'0x00444650': 230, '0x004483F0': 768, '0x00454C20': 193}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


def digest(raw):
    return hashlib.sha256(raw).hexdigest()


def metadata_digest(value):
    return digest(json.dumps(value, sort_keys=True, separators=(',', ':')).encode())


def rows(path):
    with (ROOT / path).open(newline='') as stream: return list(csv.DictReader(stream))


def verify_plan(m):
    for key, sha in PLAN_DIGESTS.items():
        if metadata_digest(m[key]) != sha: raise ValueError('GameSwitch complete immutable evidence differs: ' + key)
    if (m['evidence_id'] != 'R215' or {r['address']: r['size'] for r in m['functions']} != KEYS
            or len(m['functions']) != 3 or len(m['anchors']) != 10
            or sum(r['size'] for r in m['anchors']) != 10779
            or [r['cfg'] for r in m['functions']] != [[1, 5], [1, 26], [1, 10]]
            or len(m['tables']) != 3 or sum(r['count'] * 4 + r['selector_count'] for r in m['tables']) != 98
            or len(m['data']) != 3 or [r['size'] for r in m['retained_unknowns']] != [17, 11]
            or m['historical_snapshots'] or sum(len(r['call_sequences']) for r in m['anchors']) != 4):
        raise ValueError('GameSwitch loses the complete bounded bodies, tables or independent contexts')
    mutable = {'proposed_name', 'module', 'owner', 'evidence', 'notes'}
    for r in m['functions']:
        f, o, af, ao = (r[k] for k in ['original_function', 'original_origin', 'accepted_function', 'accepted_origin'])
        record = r['record']
        if (o['origin'] != 'unknown' or f['status'] != 'unclassified' or f['owner']
                or {k: v for k, v in f.items() if k not in mutable} != {k: v for k, v in af.items() if k not in mutable}
                or int(f['size']) != r['size'] or af['owner'] != 'authored' or ao['origin'] != 'authored'
                or ao['disposition'] != 'authored' or ao['evidence_id'] != 'R215'
                or any(af[k] for k in ['source_file', 'signature', 'calling_convention']) or af['match_percent'] != '0.00'
                or record != dict(address=r['address'], size=str(r['size']), body_sha256=r['body_sha256'],
                                  inferred_role=af['proposed_name'], return_count=str(r['cfg'][0]),
                                  internal_branch_count=str(r['cfg'][1]), external_branch_count='0', evidence_id='R215')):
            raise ValueError('GameSwitch grants unsupported extent, private ABI, source, mapping or exact credit')
    for r in m['retained_unknowns']:
        if (r['origin']['origin'] != 'unknown' or r['function']['owner'] or r['function']['status'] != 'unclassified'
                or r['prior_record']['decision'] != 'unknown' or r['prior_record']['accepted_function'] != r['function']
                or r['prior_record']['accepted_origin'] != r['origin']):
            raise ValueError('GameSwitch classifies the independent abs declaration/ownership ambiguity')


def native_instructions(raw, address):
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32
    decoded = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, address))
    if sum(i.size for i in decoded) != len(raw): raise ValueError('GameSwitch crops native instructions')
    return [dict(offset=i.address-address, size=i.size, mnemonic=i.mnemonic, operands=i.op_str) for i in decoded]


def verify_native(r, target, c, authored):
    a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
    counts = list(authored.verify_body(raw, a, r.get('switches', []),
                                     lambda x, n: c.pe_bytes_at(target, x, n), r.get('direct_switches', [])))
    if digest(raw) != r['body_sha256'] or native_instructions(raw, a) != r['instructions'] or counts != r['cfg']:
        raise ValueError('GameSwitch complete native body/instructions/guarded CFG differs: ' + r['address'])
    return raw


def verify_tables(m, target, c, functions, origins, state):
    selected = {r['address']: r for r in m['functions']}
    for r in m['tables']:
        head = selected[r['address']]; start = int(r['address'], 16); code_end = start + head['size']
        table_at = int(r['table'], 16); table = c.pe_bytes_at(target, table_at, r['count'] * 4)
        selector = c.pe_bytes_at(target, int(r['selector'], 16), r['selector_count']) if r['selector_count'] else b''
        alignment = c.pe_bytes_at(target, int(r['alignment_address'], 16), len(bytes.fromhex(r['alignment_hex'])))
        ends = int(r['selector'], 16) + len(selector) if selector else table_at + len(table)
        entries = [f'0x{x:08X}' for x in struct.unpack('<' + 'I' * r['count'], table)]
        if (table_at != code_end or entries != r['entries'] or table.hex() != r['table_hex']
                or digest(table) != r['table_sha256'] or selector.hex() != r['selector_hex']
                or digest(selector) != r['selector_sha256']
                or (selector and (int(r['selector'], 16) != table_at + len(table) or max(selector) + 1 != r['count']))
                or int(r['alignment_address'], 16) != ends or ends + len(alignment) != int(r['next_head'], 16)
                or alignment.hex() != r['alignment_hex'] or digest(alignment) != r['alignment_sha256']
                or alignment != b'\xcc' * len(alignment)):
            raise ValueError('GameSwitch loses complete adjacent tables/selector/alignment or absorbs them as code')
        actual = [dict(function=f, origin=origins[k]) for k, f in functions.items() if start <= int(k, 16) < int(r['next_head'], 16)]
        expected = [dict(function=selected[q['function']['address']][state + '_function'],
                         origin=selected[q['function']['address']][state + '_origin'])
                    if q['function']['address'] in selected else q for q in r['inventory_entries']]
        if actual != expected: raise ValueError('GameSwitch hides an inventory interior or changes an unrelated entry')
        if not any(q['address'] == r['next_head'] for q in m['anchors']):
            raise ValueError('GameSwitch omits the complete independent next code owner')


def verify_context(m):
    """Validate observed game policy composition without inventing private declarations."""
    f = {r['address']: r for r in m['functions']}; anchors = {r['address']: r for r in m['anchors']}; ctx = m['context']
    if (ctx['mode_global'] != '0x006714B4' or ctx['mode_value'] != 5
            or ctx['option_fields'] != [0x52c, 0x52d, 0x52f, 0x52e, 0x530, 0x531]
            or ctx['option_moduli'] != [6, 10, 4, 2, 4, 2] or ctx['cursor_field'] != 0x118 or ctx['cursor_modulus'] != 9
            or ctx['virtual_slot'] != 0x2c or ctx['direction_fields'] != [0x4e0, 0x4dc]
            or ctx['position_field'] != 0x44 or ctx['mode_field'] != 0x530 or ctx['position_option_field'] != 0x531
            or ctx['position_bounds'] != [620.0, 660.0] or ctx['reaction_scale'] != 1.25
            or ctx['reaction_state_field'] != 0x60 or ctx['reaction_base'] != 50 or ctx['reaction_limit'] != 37):
        raise ValueError('GameSwitch changes observed game receiver/selector/storage semantics')
    for parent, child in [('0x004461D0', '0x4483f0'), ('0x00452F10', '0x454c20')]:
        r = anchors[parent]; sequence = r['call_sequences'][0]['instructions']
        pairs = [(i['mnemonic'], i['operands']) for i in sequence]
        slot = '4' if parent == '0x004461D0' else '8'
        if (len(r['call_sequences']) != 1 or pairs[-1] != ('call', child)
                or pairs[-2] != ('mov', 'ecx, dword ptr [ebp - ' + slot + ']')
                or pairs[-4] != ('cmp', 'eax, 5') or pairs[-3][0] != 'jne'
                or pairs[-5] != ('movsx', 'eax, byte ptr [0x6714b4]')):
            raise ValueError('GameSwitch loses mode5 guard and original game member receiver')
    for parent in ['0x004431D0', '0x00444850']:
        r = anchors[parent]; seq = [(i['mnemonic'], i['operands']) for i in r['call_sequences'][0]['instructions']]
        if (len(r['call_sequences']) != 1 or seq[-8:] != [
                ('mov', 'eax, dword ptr [ebp + 0x10]'), ('push', 'eax'),
                ('mov', 'ecx, dword ptr [ebp + 0xc]'), ('push', 'ecx'),
                ('mov', 'edx, dword ptr [ebp + 8]'), ('push', 'edx'),
                ('mov', 'ecx, dword ptr [ebp - 4]'), ('call', '0x444650')]):
            raise ValueError('GameSwitch changes the complete three-argument battle member protocol')
    reaction = f['0x00444650']; rp = [(i['mnemonic'], i['operands']) for i in reaction['instructions']]
    if (reaction['calls'] != [dict(site='0x00444695', target='0x40fac0'), dict(site='0x004446F5', target='0x40fac0'),
                            dict(site='0x0044471A', target='0x4079c0'), dict(site='0x0044472B', target='0x4424e0')]
            or rp[-1] != ('ret', '0xc') or rp.count(('fmul', 'dword ptr [0x657f70]')) != 2
            or ('sub', 'edx, 0x32') not in rp or ('cmp', 'dword ptr [ebp - 8], 0x25') not in rp):
        raise ValueError('GameSwitch loses complete native reaction composition or actual RET12')
    menu = f['0x004483F0']; mp = [(i['mnemonic'], i['operands']) for i in menu['instructions']]
    direction = f['0x00454C20']; dp = [(i['mnemonic'], i['operands']) for i in direction['instructions']]
    for field in ctx['option_fields']:
        if not any(mn == 'mov' and '+ ' + hex(field) + '],' in op for mn, op in mp):
            raise ValueError('GameSwitch loses an actual cyclic option write')
    if (menu['calls'][0] != dict(site='0x00448413', target='0x438a60') or len(menu['calls']) != 7
            or any(q['target'] != '0x4079c0' for q in menu['calls'][1:])
            or ('mov', 'ecx, dword ptr [0x671618]') not in mp
            or mp.count(('mov', 'ecx, 9')) != 2 or ('mov', 'ecx, dword ptr [eax + 0x48]') not in mp
            or direction['calls'] != [dict(site='0x00454C7B', target='dword ptr [edx + 0x2c]')]
            or ('movsx', 'ecx, byte ptr [eax + 0x530]') not in dp
            or ('movsx', 'ecx, byte ptr [eax + 0x531]') not in dp
            or ('fcomp', 'dword ptr [0x658e7c]') not in dp or ('fcomp', 'dword ptr [0x658e78]') not in dp
            or mp[-1] != ('ret', '') or dp[-1] != ('ret', '')):
        raise ValueError('GameSwitch changes actual menu/direction state composition or virtual dispatch')


def replay(m, evidence_only=False):
    c = module('game_switch_target', 'compare-coff-function.py')
    authored = module('game_switch_cfg', 'verify-authored-origins.py')
    pe = module('game_switch_pe', 'verify-sdk-x3d-origins.py'); target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('GameSwitch target identity differs')
    functions = {r['address']: r for r in rows('config/functions.csv')}
    origins = {r['address']: r for r in rows('config/function-origins.csv')}
    state = 'original' if evidence_only else 'accepted'
    for path, expected in [(m['authored_path'], [r['record'] for r in m['functions']]),
                           (m['switch_path'], [q for r in m['functions'] for q in r['switches']]),
                           (m['direct_switch_path'], [q for r in m['functions'] for q in r['direct_switches']])]:
        if rows(path) != expected: raise ValueError('GameSwitch dedicated complete native/switch registry differs')
    for r in m['functions']:
        if functions[r['address']] != r[state + '_function'] or origins[r['address']] != r[state + '_origin']:
            raise ValueError('GameSwitch bounded canonical transition differs')
        verify_native(r, target, c, authored)
        if pe.image_permissions(target, int(r['address'], 16), r['size']) != r['permissions']:
            raise ValueError('GameSwitch full native code loses its mapped permissions')
    old_authored = {r['address']: r for r in rows('config/authored-origin-evidence.csv')}
    old_switches = rows('config/authored-origin-switches.csv'); old_direct = rows('config/authored-origin-direct-switches.csv')
    for r in m['anchors']:
        if (old_authored[r['address']] != r['record'] or functions[r['address']] != r['function']
                or origins[r['address']] != r['origin'] or r['origin']['origin'] != 'authored'
                or r['record']['body_sha256'] != r['body_sha256']
                or [q for q in old_switches if q['address'] == r['address']] != r['switches']
                or [q for q in old_direct if q['address'] == r['address']] != r['direct_switches']):
            raise ValueError('GameSwitch replaces an independent entire authored context')
        raw = verify_native(r, target, c, authored)
        for sequence in r['call_sequences']:
            index = next(j for j, i in enumerate(r['instructions']) if int(r['address'], 16) + i['offset'] == int(sequence['site'], 16))
            if r['instructions'][index-8:index+1] != sequence['instructions']:
                raise ValueError('GameSwitch crops or changes the actual argument/receiver call sequence')
        if pe.image_permissions(target, int(r['address'], 16), len(raw)) != r['permissions']:
            raise ValueError('GameSwitch whole retained code permission differs')
    prior = json.loads((ROOT / 'config/math-overload-origin-evidence.json').read_text())
    for r in m['retained_unknowns']:
        if (functions[r['address']] != r['function'] or origins[r['address']] != r['origin']
                or r['prior_record'] not in prior['functions']):
            raise ValueError('GameSwitch resolves or rewrites an independently unknown abs owner')
        verify_native(r, target, c, authored)
    verify_tables(m, target, c, functions, origins, state); verify_context(m)
    for r in m['data']:
        raw = c.pe_bytes_at(target, int(r['address'], 16), r['size'])
        if (r['size'] != 4 or raw.hex() != r['hex'] or digest(raw) != r['sha256']
                or struct.unpack('<f', raw)[0] != r['value'] or r['permissions'] != 0x40000000
                or pe.image_permissions(target, int(r['address'], 16), 4) != r['permissions']):
            raise ValueError('GameSwitch observed float cell value/readonly mapping differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE, MANIFEST_SHA256), *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha: raise ValueError('GameSwitch immutable prior/native evidence differs: ' + path)
    replay(m, args.evidence_only)
    print('R215 origins OK: three complete authored game switch policies1191 with unchanged extents; '
          'all15 table entries/38-byte selector/98 total data and exact0/8/15 alignment; '
          'ten independent whole native contexts10779/four actual receiver sequences; '
          'complete CFGs [1,5]/[1,26]/[1,10]; observed float cells1.25/620/660; '
          'R163 abs wrapper17/worker11 stay unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__': raise SystemExit(main())
