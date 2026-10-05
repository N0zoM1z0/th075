#!/usr/bin/env python3
"""Cold-replay frame_indexing authored policies and original vector count assignment."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('frame_index_prior', ROOT / 'scripts/verify-paired-clear-policy-origins.py')
PRIOR = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(PRIOR)
SOURCE = PRIOR.SOURCE
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/frame-index-policy-origin-evidence.json'
MANIFEST_SHA256 = 'bb5d5d550cf326252c7bf9a83961a4a90334bc75196f2c460ef2cc7a29236a22'
PLAN_DIGESTS = {'groups': 'ecffd22eb68fb892079e89b7e885a21ce909d6990c6d2ae35c410109fc43813d', 'sections': '50527d6e879c70e96ab0f2787709e87aab3bca81dfe63494e5e1e1e7e5a9befb', 'weak_references': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'evidence_id': '39a6faea79b61340bca966ac1d0d5804ef6a9d9f857f90a254f4fce2391a369b', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'prior': 'eb1cc5139c9f9e729bd1d36aee8a3603c53d8b71fa6ad891fdbfcf824eaa1684', 'functions': '6f05f2cb36b85d4ff012f59b2897cca723ba36463d7539351b959cef2733906f', 'retained_unknowns': 'b4657ddec4dc073619536ddbf74a09828c89c2a508923c66a57895285b35e6ba', 'parents': 'dd9cb9fc7d4092767102a1147b4db557bfd718cb05b9e5b646a0fb030230103d', 'historical_snapshots': '139e66e831e596d56fe6de5df8acf91b3369fac8ef1ceacf79dc130810cd17bb', 'memset': '078e6f9e489d82cafd1e133ba0dcc33afcd8b9a83cfcdd5036aae782d06342f2', 'authored_path': '82c9e0c2b7ca2e447afbf37961a2ff3c160777e23107ba2d7cbd35ec280625ed', 'game_context': '245bd052e1dda9e742e86968656c458786422fc5586a91fbeaa186a5faee1c06', 'public_control': '9fe6a136fee7f6a0058469b83f071ab8a7c8732dcaf9750ef6506bb0d72d44e3', 'alternatives': 'da36ed0ef30f0dc79be94c419f61f0700c4427027385ccc1a73443eea30047bc', 'retained_sha256': 'b388ccebf1424427c888e7213fb6d4149760fcb88f0e7facf45bec931037332e', 'additional_shared': '081612a5fecc8576084a90eb2f34553b773136bfbdfe6d1e2877fd95f3c15f24'}
WHOLE = {'0x005FACD0': 70, '0x005F8490': 31, '0x005F8E70': 45, '0x005F8E50': 19, '0x005F95B0': 28, '0x005F95F0': 16, '0x005FAD20': 70, '0x005F9640': 16, '0x005FAC60': 101, '0x00454BC0': 61}


def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:', 1)[1].strip().replace('\\', '/')
        if value[:3].lower() != 'z:/': raise ValueError('FrameIndex original include loses host mapping')
        path = Path(value[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/') and relative not in (
                'tests/origin_probes/VectorAtPolicyProbe.cpp',):
            raise ValueError('FrameIndex original include imports an unrelated source')
        found[relative] = digest(path.read_bytes())
    return found


def verify_plan(m):
    for key, sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('FrameIndex immutable complete evidence differs: ' + key)
    if (m['evidence_id'] != 'R213' or {r['address']: r['size'] for r in m['functions']} != WHOLE
            or len(m['functions']) != 10 or len(m['groups']) != 2
            or len(m['sections']) != 26 or sum(r['size'] for r in m['sections']) != 978
            or sum(len(r['fields']) for r in m['sections']) != 46
            or sum(r['kind'] == 'code' for r in m['sections']) != 22
            or len(m['retained_unknowns']) != 2 or len(m['parents']) != 4 or len(m['historical_snapshots']) != 10
            or len(m['public_control']['emission']) != 130
            or sum(r['size'] for r in m['public_control']['emission']) != 5568
            or [r['size'] for r in m['alternatives']] != [32, 32, 70, 70]):
        raise ValueError('FrameIndex loses complete bounded policies and carrier/default controls')
    for r in m['functions']:
        is_author = r['accepted_origin']['origin'] == 'authored'
        f, o, af, ao = (r[k] for k in ['original_function', 'original_origin', 'accepted_function', 'accepted_origin'])
        if (o['origin'] != 'unknown' or f['status'] != 'unclassified'
                or any(f[k] or af[k] for k in ['source_file', 'signature', 'calling_convention']) or f['owner']
                or f['match_percent'] != '0.00' or af['match_percent'] != '0.00'
                or any(af[k] != f[k] for k in ['address', 'size', 'span_end', 'current_name'])
                or af['size'] != str(r['size']) or ao['evidence_id'] != 'R213'
                or (is_author and (af['owner'] or af['status'] != 'unclassified' or ao['disposition'] != 'authored'))
                or (not is_author and (af['owner'] != 'library' or af['status'] != 'excluded'
                    or ao['origin'] != 'library' or ao['disposition'] != 'exclude'))):
            raise ValueError('FrameIndex gains unsupported extent/private ABI/source/origin/exact credit')

    for r in m['retained_unknowns']:
        if (r['origin']['origin'] != 'unknown' or r['function']['status'] != 'unclassified'
                or r['function']['owner'] or r['function']['source_file']):
            raise ValueError('FrameIndex assigns unresolved short/private ownership')


def check_call(raw, address, call):
    site = int(call['site'], 16); offset = site - address
    if (offset < 0 or offset + 5 > len(raw) or raw[offset] != 0xe8
            or site + 5 + struct.unpack_from('<i', raw, offset + 1)[0] != int(call['target'], 16)):
        raise ValueError('FrameIndex loses complete native parent/policy call evidence')


def verify_history(m, target, c, functions, origins, state):
    """Keep old records literal and permit only these independently proved successors."""
    selected = {r['address']: r for r in m['functions']}
    for h in m['historical_snapshots']:
        document = json.loads((ROOT / h['path']).read_text()); old = document
        for key in h['trail']: old = old[key]
        row = h['record']; address = row['function']['address']; current = selected[address]
        raw = c.pe_bytes_at(target, int(address, 16), int(row['size']))
        historical_function = dict(row['function'])
        if h['path'] == 'config/vector-producer-origin-evidence.json' and address in ['0x005F8490', '0x005F95B0']:
            # R162 kept these unknown and recorded its negative observations in
            # the canonical evidence/notes after taking its literal snapshots.
            annotation = next(q for q in document['functions'] if q['address'] == address)
            if (annotation['original_function'] != historical_function or annotation['decision'] != 'unknown'
                    or annotation['accepted_origin'] != current['original_origin']
                    or annotation['accepted_function'] != current['original_function']):
                raise ValueError('FrameIndex historical metadata loses its actual R162 annotation')
            historical_function = annotation['accepted_function']
        if (old != row or historical_function != current['original_function'] or row['origin'] != current['original_origin']
                or int(row['size']) != current['size'] or digest(raw) != row['body_sha256']
                or functions[address] != current[state + '_function'] or origins[address] != current[state + '_origin']):
            raise ValueError('FrameIndex rewrites historical evidence or invents an unbounded successor')


def verify_native_context(m, target, c, flow):
    """Prove game receiver provenance and composition with complete native owners."""
    rows = {r['address']: r for r in [*m['functions'], *m['parents']]}
    context = m['game_context']

    def pairs(address):
        return [(i['mnemonic'], i['operands']) for i in rows[address]['instructions']]

    frame = pairs('0x005FAC60'); parent = pairs(context['frame_parent'])
    if (context['frame_resource_field'] != 0x90 or context['frame_container_field'] != 0x7c
            or context['frame_resource_container_offset'] != 0x78 or context['index_fields'] != [0x60, 0x62]
            or context['output_fields'] != [8, 0x72, 0x70]
            or ('add', 'ecx, 0x78') not in parent or ('mov', 'dword ptr [edx + 0x7c], ecx') not in parent
            or not all(any(f'+ {hex(field) if field >= 10 else str(field)}]' in op for _, op in frame)
                       for field in [0x60, 0x62, 0x7c, 8, 0x72, 0x70])):
        raise ValueError('FrameIndex loses independently initialized game frame receiver/storage')
    calls = rows['0x005FAC60']['calls']
    if [r['target'] for r in calls] != [context['outer_at'], context['inner_at'], context['outer_at'], '0x005F9E90']:
        raise ValueError('FrameIndex changes complete nested selection/size composition')
    # Both public functions consume one stack argument. The second index stays
    # below the first until the outer RET4 returns the inner receiver.
    if (frame[6:12] != [('push', 'ecx'), ('mov', 'edx, dword ptr [ebp - 4]'),
                       ('movsx', 'eax, word ptr [edx + 0x60]'), ('push', 'eax'),
                       ('mov', 'ecx, dword ptr [ebp - 4]'), ('mov', 'ecx, dword ptr [ecx + 0x7c]')]
            or frame[13] != ('mov', 'ecx, dword ptr [eax]')
            or not all(rows[a]['instructions'][-1]['operands'] == '4' for a in [context['outer_at'], context['inner_at']])):
        raise ValueError('FrameIndex invents a two-argument ABI or loses the actual nested stack protocol')
    command = pairs('0x00454BC0'); loader = pairs(context['command_resource_parent'])
    if (context['command_owner_field'] != 0x480 or context['command_selection_field'] != 0x47c
            or context['setters'] != ['0x00410FA0', '0x00410FE0'] or context['setter_fields'] != [0x10, 0x14]
            or ('mov', 'dword ptr [eax + 0x47c], ecx') not in command
            or ('mov', 'dword ptr [ecx + 0x480], edx') not in loader
            or [r['target'] for r in rows['0x00454BC0']['calls']] != context['setters']
            or sum('+ 0x480]' in op for _, op in command) != 2 or command[-1] != ('ret', '0xc')):
        raise ValueError('FrameIndex command composition loses its independently created game owner')
    action = rows['0x0045DD70']; raw = c.pe_bytes_at(target, int(action['address'], 16), action['size'])
    ins = SOURCE.instructions(raw, int(action['address'], 16), flow)
    for sequence in action['call_sequences']:
        index = next(j for j, i in enumerate(ins) if int(action['address'], 16) + i['offset'] == int(sequence['site'], 16))
        actual = ins[index-4:index+1]
        if (actual != sequence['instructions'] or [i['mnemonic'] for i in actual] != ['push', 'push', 'push', 'mov', 'call']
                or actual[3]['operands'] != 'ecx, dword ptr [ebp - 0x34]' or actual[-1]['operands'] != '0x454bc0'):
            raise ValueError('FrameIndex command call loses its actual game receiver/three arguments')


def replay(m, evidence_only=False):
    c = module('frame_index_target', 'compare-coff-function.py'); coff = module('frame_index_coff', 'coff_data.py')
    extra = module('frame_index_carriers', 'sdk_x3d_carriers.py'); flow = module('frame_index_flow', 'sdk_image_carriers.py')
    pe = module('frame_index_permissions', 'verify-sdk-x3d-origins.py'); rt = module('frame_index_crt', 'verify-runtime-origins.py')
    authored = module('frame_index_authored', 'verify-authored-origins.py')
    inventory = module('frame_index_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('FrameIndex target identity differs')
    functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').open())}
    origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').open())}
    selected = {r['address']: r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    own = list(csv.DictReader((ROOT / m['authored_path']).open()))
    if own != [r['record'] for r in m['functions'] if r['accepted_origin']['origin'] == 'authored']: raise ValueError('FrameIndex own authored records differ')
    for r in m['functions']:
        if digest(c.pe_bytes_at(target, int(r['address'], 16), r['size'])) != r['record']['body_sha256']:
            raise ValueError('FrameIndex own authored record lacks the complete body')
        if functions[r['address']] != r[state + '_function'] or origins[r['address']] != r[state + '_origin']:
            raise ValueError('FrameIndex bounded canonical transition differs')
        a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
        if (digest(raw) != r['body_sha256'] or list(authored.verify_body(raw, a)) != r['cfg']
                or SOURCE.instructions(raw, a, flow) != r['instructions']):
            raise ValueError('FrameIndex complete authored native body/CFG differs')
        for call in r['calls']: check_call(raw, a, call)
    for r in m['retained_unknowns']:
        if functions[r['function']['address']] != r['function'] or origins[r['origin']['address']] != r['origin']:
            raise ValueError('FrameIndex changes a protected short/private unknown')
        a = int(r['function']['address'], 16); raw = c.pe_bytes_at(target, a, int(r['function']['size']))
        if (digest(raw) != r['body_sha256'] or list(authored.verify_body(raw, a)) != r['cfg']
                or SOURCE.instructions(raw, a, flow) != r['instructions']):
            raise ValueError('FrameIndex crops a protected complete short setter')
    verify_native_context(m, target, c, flow)
    verify_history(m, target, c, functions, origins, state)
    prior = json.loads((ROOT / m['prior']['path']).read_text())
    if (digest((ROOT / m['prior']['path']).read_bytes()) != m['prior']['manifest_sha256']
            or prior['prior']['shared'] != m['prior']['shared'] or prior['prior']['absolute'] != m['prior']['absolute']
            or prior['prior']['crt_archive_sha256'] != m['prior']['crt_archive_sha256']):
        raise ValueError('FrameIndex replaces independent prior source ownership')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'), str(ROOT / 'scripts/verify-paired-clear-policy-origins.py')],
                            cwd=ROOT, capture_output=True, text=True)
    if result.returncode: raise ValueError('FrameIndex complete prior cold graph failed: ' + result.stderr)
    print(result.stdout.strip(), flush=True)
    old = json.loads((ROOT / 'config/nested-deque-size-origin-evidence.json').read_text())
    source_catalog = SOURCE.BASE.retained_catalog(old); shared = {'__except_list': 0}
    for r in m['prior']['shared']:
        owner = r['owner']
        if old[owner['collection']][owner['index']] != owner['record'] or source_catalog.get(r['symbol']) != int(r['address'], 16):
            raise ValueError('FrameIndex field observation overrides retained full source definition')
        shared[r['symbol']] = source_catalog[r['symbol']]
    at_prior = json.loads((ROOT / 'config/vector-at-policy-origin-evidence.json').read_text())
    for r in m['additional_shared']:
        owner = r['owner']
        if (old[owner['collection']][owner['index']] != owner['record']
                or r['prior_record'] not in at_prior['shared'] or r['prior_record']['record'] != owner['record']
                or source_catalog.get(r['symbol']) != int(r['address'], 16)):
            raise ValueError('FrameIndex out_of_range borrows a native field instead of a complete retained definition')
        if 'function' in r['prior_record']:
            q = r['prior_record']
            if functions[r['address']] != q['function'] or origins[r['address']] != q['origin']:
                raise ValueError('FrameIndex changes the retained complete out_of_range owner')
        shared[r['symbol']] = source_catalog[r['symbol']]
    records = list(csv.DictReader((ROOT / 'config/authored-origin-evidence.csv').open()))
    switches = list(csv.DictReader((ROOT / 'config/authored-origin-switches.csv').open()))
    direct = list(csv.DictReader((ROOT / 'config/authored-origin-direct-switches.csv').open()))
    for r in m['parents']:
        a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
        decoded_instructions = SOURCE.instructions(raw, a, flow)
        if (r['record'] not in records or functions[r['address']] != r['function'] or origins[r['address']] != r['origin']
                or r['origin']['origin'] != 'authored' or digest(raw) != r['body_sha256']
                or digest(raw) != r['record']['body_sha256']
                or [q for q in switches if q['address'] == r['address']] != r['switches']
                or [q for q in direct if q['address'] == r['address']] != r['direct_switches']
                or list(authored.verify_body(raw, a, r['switches'], lambda x, n: c.pe_bytes_at(target, x, n), r['direct_switches'])) != r['cfg']
                or len(decoded_instructions) != r['instruction_count']
                or SOURCE.BASE.metadata_digest(decoded_instructions) != r['instructions_sha256']
                or (r['instructions'] is not None and decoded_instructions != r['instructions'])):
            raise ValueError('FrameIndex complete authored game parent/CFG differs')
        for call in r['calls']: check_call(raw, a, call)
    p = m['memset']; q = p['record']; crt = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(crt) != q['archive_sha256'] or q not in list(csv.DictReader((ROOT / 'config/runtime-origin-evidence.csv').open())):
        raise ValueError('FrameIndex original memset archive/record differs')
    name, body = {a: (n, b) for a, n, b in rt.archive_members(crt)}[int(q['member_offset'])]
    raw, fields, source = extra.section_carrier(body, p['source']['section'], c, coff); a = int(q['address'], 16)
    aux = next(x for x in source['aux_records'] if x['symbol'] == '_memset')
    if (name != q['member'] or digest(body) != p['member_sha256'] or SOURCE.BASE.canonical_source(source, body) != p['source']
            or fields != p['fields'] or fields or len(raw) != 96 or aux['aux_count'] != 1
            or struct.unpack_from('<I', bytes.fromhex(aux['aux_hex']), 4)[0] != len(raw)
            or raw != c.pe_bytes_at(target, a, 96) or digest(raw) != q['body_sha256']
            or list(authored.verify_body(raw, a)) != p['cfg'] or SOURCE.instructions(raw, a, flow) != p['instructions']
            or functions[q['address']] != p['function'] or origins[q['address']] != p['origin']):
        raise ValueError('FrameIndex memset lacks its complete original own-AUX/native/CFG proof')
    shared['_memset'] = a
    scratch = ROOT / 'build/origin-frame-index-policy-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / 'FrameIndex.obj'; control = m['public_control']
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / control['probe']), str(obj), *control['profile']],
                                cwd=ROOT, capture_output=True, text=True)
        if result.returncode or headers(result.stdout + result.stderr) != control['headers']:
            raise ValueError('FrameIndex cold generic source/original includes differ')
        body = obj.read_bytes()
        if inventory(body, c, coff) != control['emission']: raise ValueError('FrameIndex omits ordinary code/data/EH emission')
        # Reopen the complete retained code and throw metadata in this cold
        # object as well as their independently cold-replayed R150 owners.
        for r in m['additional_shared']:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            a = int(r['address'], 16); is_data = r['owner']['collection'] == 'state_data'
            linked, calls, data = SOURCE.BASE.BASE.bind_fields(raw, fields, r['bindings'], source_catalog, 0, a, data_image=is_data)
            actual = c.pe_bytes_at(target, a, len(raw))
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields']
                    or len(raw) != r['owner']['record']['size'] or digest(raw) != r['source_sha256']
                    or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000
                    or linked != actual or digest(actual) != r['body_sha256']
                    or (not is_data and (list(authored.verify_body(actual, a)) != r['cfg']
                        or SOURCE.instructions(actual, a, flow) != r['instructions']))):
                raise ValueError('FrameIndex loses the full retained out_of_range code/data/fields/CFG')
        layout, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
        if len(layout) != 56 or list(struct.unpack('<14I', layout)) != control['layout_values']:
            raise ValueError('FrameIndex crops the complete generic observation carrier')
        if [SOURCE.weak_record(body, r['symbol'], c, coff) for r in m['weak_references']] != m['weak_references']:
            raise ValueError('FrameIndex loses actual weak AUX/strong fallback')
        rows = m['sections']; decoded = {}
        for r in rows:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff); a = int(r['base'], 16)
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields']
                    or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                    or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000):
                raise ValueError('FrameIndex complete source/AUX/fields/permissions differ')
            decoded[r['source']['section']] = (raw, fields)
            if r['kind'] == 'code':
                actual = [dict(function=f, origin=origins[k]) for k, f in functions.items() if a <= int(k, 16) < a + r['size']]
                expected = [dict(function=selected[q['function']['address']][state + '_function'],
                                 origin=selected[q['function']['address']][state + '_origin'])
                            if q['function']['address'] in selected else q for q in r['inventory_entries']]
                if actual != expected: raise ValueError('FrameIndex full source hides an inventory entry')
        for g in m['groups']:
            rows = [r for r in m['sections'] if r['group'] == g['id']]
            catalog = SOURCE.owned_catalog(rows, shared, g['id'], [r for r in m['weak_references'] if r['symbol'] in g['weak_symbols']])
            for r in rows:
                raw, fields = decoded[r['source']['section']]; a = int(r['base'], 16)
                linked, calls, data = SOURCE.BASE.BASE.bind_fields(raw, fields, r['bindings'], catalog, g['id'], a, data_image=r['kind'] == 'data')
                actual = c.pe_bytes_at(target, a, len(raw))
                if linked != actual or digest(actual) != r['body_sha256']: raise ValueError('FrameIndex complete unmasked body differs')
                if r['kind'] == 'code':
                    roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type'] == 32 and d['storage'] == 3)
                    roots.update(f['symbol_offset'] + f['addend'] for q in rows for f in q['fields']
                                 if f['symbol_section'] == r['source']['section'] and f['symbol_storage'] == 6)
                    if sorted(roots) != r['roots'] or flow.flow(actual, a, r['roots'], fields, calls, data, None, None, None) != r['flow']:
                        raise ValueError('FrameIndex complete normal/EH/unwind/shared-exit CFG differs')
        for r in m['alternatives']:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff)
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields'] or len(raw) != r['size']
                    or digest(raw) != r['source_sha256'] or SOURCE.instructions(raw, 0x100000, flow) != r['instructions']):
                raise ValueError('FrameIndex complete default/value-initialization control differs')
        advances = [r for r in m['sections'] if r['base'] in ['0x005F95D0', '0x005F9620']]
        if (any(r['fields'] for r in m['alternatives'][:2])
                or any(r['source_sha256'] in {q['source_sha256'] for q in advances} for r in m['alternatives'][:2])
                or not all(r['fields'][-1]['symbol'].startswith('??Dconst_iterator@') for r in m['alternatives'][2:])):
            raise ValueError('FrameIndex substitutes a wrong stride or const route for the full mutable policy')



def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE, MANIFEST_SHA256), (m['public_control']['probe'], m['public_control']['probe_sha256']), *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha: raise ValueError('FrameIndex immutable source/evidence differs: ' + path)
    replay(m, args.evidence_only)
    print('R213 origins OK: eight complete public vector/iterator library entries295 and two native game policies162; '
          '26 scoped whole code/data carriers978/all46 fields/22 CFGs; 130 ordinary emissions5568/28 original '
          'includes/full observation56; complete stride32/32 and const70/70 alternatives; four whole game contexts62405 '
          '/nine actual calls; full R212 retained cold proof; ten literal historical snapshots have explicit bounded '
          'successors; two command setters remain unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__': raise SystemExit(main())
