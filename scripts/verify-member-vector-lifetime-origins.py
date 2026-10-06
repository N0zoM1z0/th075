#!/usr/bin/env python3
"""Cold-check vector subobject destruction without classifying ordinary clear aliases."""
import argparse
import json
from pathlib import Path
import tempfile

ROOT = Path(__file__).resolve().parents[1]
# Reuse complete COFF inventories and the unchanged R253 proof, not cached objects.
import importlib.util


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


GLOBAL = module('member_vector_global', 'verify-global-vector-lifetime-origins.py')
COMMON = GLOBAL.COMMON
rows = COMMON.rows
digest = COMMON.digest
metadata_digest = COMMON.metadata_digest
EVIDENCE = 'config/member-vector-lifetime-origin-evidence.json'
MANIFEST_SHA256 = '9408b4e5a5f04f24cba62e54d4e236c999b98562b93148ba9681ee622d43e14f'
PLAN_DIGESTS = {'evidence_id': '74ddac49ef1c90a8e90186e356610d588a4613e32cc585247f0f547192bf4fca', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'baseline_commit': '60487f00704d484346d7c77d8307736d45e865fb0e0c38df7898311f692731db', 'functions': '035af3f22034e79da12b7e877fb3ae43caa1c8c78f89706bc2a03215e44a6b18', 'retained_unknown': '23f615d306d0f5e257273c71fd792dc28fd38cf227a48c14df03cb1d5783fc72', 'native': '4f3392ec15b0f29566a93c03449318d5782d37a3f1be08fea1e25facce58b835', 'canonical': '7a684a539d8bc49bcf514a1416347d1968e544055f0842fed4515112db2f6578', 'unselected_sha256': 'd4bbca45490c99eb1c0f1fa7f5aa8b50f66a6d7276fe53a7670f69f4b5b8758a', 'context': 'df29036bfc4ae0591ea4449a5216a75e513b90478ff25519470bde76ffe9af31', 'control': '9c8d02986e8fedcb88b5da9e509a65ba5e09ad42d1844b5f851f147a179c3945', 'retained_sha256': '71771d520523012123994e88b770aabc2476244461637d097ccc3168a6ba8d68', 'interpretation': 'dd448a04d7d210b12f46bfdac139dad27f553bbcf7694745421a83d1e021c91a'}
WHOLE = {'0x00409380': 19, '0x0040DCC0': 19, '0x0040DE80': 19}
UNKNOWN = ['0x00409490', '0x0040DE30', '0x0040DF40']


def verify_plan(plan):
    if set(plan) != set(PLAN_DIGESTS):
        raise ValueError('Member vector immutable schema differs')
    for key, value in PLAN_DIGESTS.items():
        if metadata_digest(plan[key]) != value:
            raise ValueError('Member vector immutable whole evidence differs: ' + key)
    if (plan['evidence_id'] != 'R254' or plan['retained_unknown'] != UNKNOWN
            or {r['address']: r['size'] for r in plan['functions']} != WHOLE):
        raise ValueError('Member vector bounded scope differs')
    for r in plan['functions']:
        old, new = r['original_function'], r['accepted_function']
        mutable = {'proposed_name', 'module', 'status', 'owner', 'evidence', 'notes'}
        if (r['original_origin']['origin'] != 'unknown' or old['owner']
                or {k: v for k, v in old.items() if k not in mutable}
                != {k: v for k, v in new.items() if k not in mutable}
                or new['owner'] != 'library' or new['status'] != 'excluded'
                or new['match_percent'] != '0.00'
                or any(new[k] for k in ['source_file', 'signature', 'calling_convention'])
                or r['accepted_origin']['origin'] != 'library'
                or r['accepted_origin']['evidence_id'] != 'R254'):
            raise ValueError('Member vector gains unsupported extent/ABI/source/exact credit')


def historical_rows(plan, name, actual, evidence_only=False):
    """Project only the three independently validated literal transitions to R253."""
    if name not in ['functions.csv', 'function-origins.csv']:
        return actual
    kind = 'function' if name == 'functions.csv' else 'origin'
    selected = {r['address']: r for r in plan['functions']}
    observed = [r['address'] for r in actual if r['address'] in selected]
    if len(observed) != len(set(observed)) or set(observed) != set(selected):
        raise ValueError('Member vector historical view loses or duplicates a selected pair')
    result = []
    for r in actual:
        if r['address'] in selected:
            entry = selected[r['address']]
            state = 'original' if evidence_only else 'accepted'
            if r != entry[state + '_' + kind]:
                raise ValueError('Member vector historical view rejects an unapproved pair')
            r = entry['original_' + kind]
        result.append(r)
    return result


def verify_canonical(plan, evidence_only=False):
    fs = {r['address']: r for r in rows('functions.csv')}
    os = {r['address']: r for r in rows('function-origins.csv')}
    selected = {r['address']: r for r in plan['functions']}
    for name in ['functions.csv', 'function-origins.csv']:
        if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE]) != plan['unselected_sha256'][name]:
            raise ValueError('Member vector changes unrelated canonical rows')
    for pair in plan['canonical']:
        a = pair['function']['address']
        expected = pair
        if a in selected:
            state = 'original' if evidence_only else 'accepted'
            expected = dict(function=selected[a][state + '_function'], origin=selected[a][state + '_origin'])
        if dict(function=fs[a], origin=os[a]) != expected:
            raise ValueError('Member vector full canonical pair differs: ' + a)
    if any(os[a]['origin'] != 'unknown' or fs[a]['owner'] for a in UNKNOWN + ['0x0040F9F0', '0x0040D8E0']):
        raise ValueError('Member vector resolves an ordinary clear or unresolved element lifetime')


def verify_receiver_links(plan):
    bodies = {r['address']: r for r in plan['native']}
    for link in plan['context']['links']:
        ins = bodies[link['owner']]['instructions']
        by = {r['offset']: r for r in ins}
        call, state = by[link['constructor_site']], by[link['state_site']]
        prefix = [r for r in ins if r['offset'] < call['offset']]
        receiver = link['receiver_offset']
        expected = [('mov', 'ecx, dword ptr [ebp - 0x10]')]
        if receiver:
            expected.append(('add', 'ecx, ' + (str(receiver) if receiver < 10 else hex(receiver))))
        if (call['mnemonic'] != 'call' or int(call['operands'], 16) != int(link['constructor'], 16)
                or [(r['mnemonic'], r['operands']) for r in prefix[-len(expected):]] != expected
                or state['offset'] != call['offset'] + call['size'] or state['mnemonic'] != 'mov'
                or state['operands'] != ('dword' if not receiver else 'byte') + ' ptr [ebp - 4], ' + str(link['state'])):
            raise ValueError('Member vector loses same receiver and completed construction state')
        callback = next(r for b in plan['context']['blocks'] for r in b['callbacks'] if r['address'] == link['cleanup'])
        if [(r['mnemonic'], r['operands']) for r in callback['instructions'][:-1]] != expected:
            raise ValueError('Member vector callback uses a different constructed subobject')

def verify_context(plan):
    comparisons = plan['control']['comparisons']
    links = plan['context']['links']
    if (len(links) != 4 or {r['destructor'] for r in links} != set(WHOLE)
            or [(r['owner'], r['state'], r['receiver_offset']) for r in links] != [
                ('0x004071C0', 0, 0), ('0x0040AD80', 1, 8),
                ('0x0040AD80', 2, 24), ('0x0040AD80', 3, 40)]):
        raise ValueError('Member vector loses a complete construction-state cohort')
    verify_receiver_links(plan)
    def one(address, role):
        found = [r for r in comparisons if r['address'] == address and r['role'] == role]
        if len(found) != 1:
            raise ValueError('Member vector loses a unique whole source carrier')
        return found[0]
    for link in plan['context']['links']:
        ctor = one(link['constructor'], 'vendor-constructor42')
        dtor = one(link['destructor'], 'vendor-destructor19')
        if (ctor['size'] != 42 or dtor['size'] != 19
                or not ctor['symbol'].startswith('??0?$vector@')
                or not dtor['symbol'].startswith('??1?$vector@')
                or ctor['symbol'][3:] != dtor['symbol'][3:]):
            raise ValueError('Member vector substitutes the vendor constructor/destructor namespace')
        block = next(r for r in plan['context']['blocks'] if any(
            o['owner_address'] == link['owner'] for o in json.loads(r['frame']['owners'])))
        callback = next(r for r in block['callbacks'] if r['address'] == link['cleanup'])
        if (callback['destination'] != link['destructor'] or callback['state_index'] != link['state']
                or callback['to_state'] != link['state'] - 1):
            raise ValueError('Member vector changes the completed subobject EH state/provider')
    ordinary = [r for r in comparisons if r['role'] == 'ordinary-cleanup19-positive-retains-unknown']
    if ([r['address'] for r in ordinary] != UNKNOWN or any(
            r['size'] != 19 or not r['symbol'].startswith('?Cleanup@') for r in ordinary)):
        raise ValueError('Member vector drops an actual ordinary whole-body counterexample')
    code = one('0x00654DE0', 'whole-compiler-base-cleanup-and-dispatch18')
    data = one('0x00667CA4', 'whole-compiler-unwind-and-function-info36')
    dtor = one('0x00409380', 'vendor-destructor19')
    if (code['size'] != 18 or code['roots'] != [0, 8] or code['definition']['offset'] != 8
            or data['size'] != 36 or data['roots'] or data['definition']['offset'] != 8
            or code['fields'][0]['symbol'] != dtor['symbol']
            or code['fields'][0]['symbol_section'] != dtor['section']
            or code['bindings'][0]['target'] != dtor['address']
            or code['fields'][1]['symbol'] != data['symbol']
            or code['fields'][1]['symbol_section'] != data['section']
            or code['fields'][1]['symbol_offset'] != 8
            or code['bindings'][1]['target'] != '0x00667CAC'
            or data['bindings'][0]['target'] != code['address']
            or data['fields'][0]['symbol_section'] != code['section']
            or data['fields'][0]['symbol_offset'] != 0
            or data['bindings'][1]['target'] != data['address']
            or data['fields'][1]['symbol_section'] != data['section']
            or data['fields'][1]['symbol_offset'] != 0):
        raise ValueError('Member vector loses full compiler code/data carriers or actual local providers')
    alternatives = {r['symbol']: r for r in plan['control']['alternatives']}
    for owner, ctor in [('WordVectorPolicy', '0x00409350'), ('RecordVectorPolicy', '0x0040DC90')]:
        policy = alternatives['??0' + owner + '@@QAE@XZ']
        handler = alternatives['__ehhandler$??0' + owner + '@@QAE@XZ']
        construction = one(ctor, 'vendor-constructor42')
        field = next(f for f in policy['fields'] if f['offset'] == 32)
        if (policy['size'] != 72 or handler['size'] != 18
                or field['symbol'] != construction['symbol']
                or field['symbol_section'] != construction['section']
                or not handler['fields'][0]['symbol'].startswith('??1?$vector@')):
            raise ValueError('Member vector loses genuine inherited policy/base cleanup distinction')
    if alternatives['__ehhandler$??0ThreeVectorObservation@@QAE@XZ']['size'] != 40:
        raise ValueError('Member vector crops or pads the natural multi-member EH alternative')
    negative = plan['control']['provider_alternatives']
    if (len(negative) != 1 or negative[0]['address'] != '0x0040F9F0'
            or negative[0]['size'] != 5 or negative[0]['target_size'] != 15):
        raise ValueError('Member vector hides the unresolved original element destruction boundary')
    providers = {(r['symbol'], r['address']): r for r in comparisons}
    boundaries = {(r['symbol'], r['address']): r for r in plan['control']['external'] + negative}
    for r in comparisons:
        for f, binding in zip(r['fields'], r['bindings']):
            if f['type'] != 'REL32':
                continue
            key = (f['symbol'], binding['target'])
            if r['symbol'].startswith('?_Xlen@?$vector@') or f['symbol'] == '___CxxFrameHandler':
                continue  # Whole failure carrier and retained R142 exception graph; no new credit.
            provider = providers.get(key)
            if provider:
                d = provider['definition']
            elif key in boundaries:
                boundary = boundaries[key]
                d = boundary.get('definition') or next(x for x in boundary['source']['definitions'] if x['symbol'] == f['symbol'])
            else:
                raise ValueError('Member vector loses a full provider or declared retained boundary')
            if (f['symbol_section'], f['symbol_offset']) != (d['section'], d['offset']):
                raise ValueError('Member vector substitutes an actual source provider')


def verify_native(plan, target, c, flow):
    auth = module('member_vector_auth', 'verify-authored-origins.py')
    eh = module('member_vector_eh', 'compiler_eh.py')
    entries = {int(r['address'], 16) for r in rows('functions.csv')}
    bodies = {r['address']: r for r in plan['native']}
    for a, r in bodies.items():
        at = int(a, 16)
        raw = c.pe_bytes_at(target, at, r['size'])
        cfg = (flow.flow(raw, at, [0], [], {at + 1: 0x642A61}, {}) if a == '0x00640F15'
               else list(auth.verify_body(raw, at, [], lambda x, n: c.pe_bytes_at(target, x, n), [])))
        if (digest(raw) != r['body_sha256'] or COMMON.SOURCE.instructions(raw, at, flow) != r['instructions']
                or cfg != r['cfg']):
            raise ValueError('Member vector complete native body/CFG differs: ' + a)
    for r in plan['context']['alignment']:
        raw = c.pe_bytes_at(target, int(r['address'], 16), r['size'])
        if raw != b'\xcc' * r['size'] or digest(raw) != r['sha256']:
            raise ValueError('Member vector claims external alignment')
    for r in plan['context']['parents']:
        if r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Member vector original authored parent evidence differs')
    for r in plan['context']['constructors']:
        if r['helpers_record'] not in rows('vendor-vector-helper-origins.csv'):
            raise ValueError('Member vector original independently accepted constructor differs')
    for block in plan['context']['blocks']:
        frame = block['frame']
        if frame not in rows('compiler-eh-frames.csv'):
            raise ValueError('Member vector original EH frame differs')
        eh.verify_frame(frame, lambda a, n: c.pe_bytes_at(target, a, n),
                        lambda a, n: c.pe_bytes_at(target, a, n), entries, set())
        at = int(block['address'], 16)
        raw = c.pe_bytes_at(target, at, block['size'])
        instructions = COMMON.SOURCE.instructions(raw, at, flow)
        calls = {at + x['offset'] + x['size'] - 4: int(x['operands'], 16)
                 for x in instructions if x['mnemonic'] == 'jmp'}
        cfg = flow.flow(raw, at, block['roots'], [], calls,
                        {int(frame['handler_address'], 16) + 1: int(frame['funcinfo_address'], 16)})
        if (digest(raw) != block['body_sha256'] or instructions != block['instructions'] or cfg != block['cfg']
                or digest(c.pe_bytes_at(target, int(block['data_address'], 16), block['data_size'])) != block['data_sha256']):
            raise ValueError('Member vector complete compiler code/data differs')
        for r in block['callbacks']:
            raw = c.pe_bytes_at(target, int(r['address'], 16), r['size'])
            kind, dest = eh.cleanup_template(raw, int(r['address'], 16), entries)
            if kind != r['kind'] or dest != int(r['destination'], 16):
                raise ValueError('Member vector actual compiler callback differs')
    if any(r not in rows('compiler-origin-evidence.csv') for r in plan['context']['callback_records']):
        raise ValueError('Member vector original callback proof differs')
    verify_context(plan)


def verify_control(plan, body, target, c, coff, carrier, flow):
    ctl = plan['control']
    if GLOBAL.inventory(body, c, coff, carrier) != ctl['emission']:
        raise ValueError('Member vector full ordinary emission/AUX/fields/storage differs')
    for r in ctl['comparisons']:
        raw, fields, source = carrier.section_carrier(body, r['section'], c, coff)
        if (r['definition'] not in source['definitions'] or fields != r['fields']
                or COMMON.SOURCE.BASE.canonical_source(source, body) != r['source'] or digest(raw) != r['source_sha256']):
            raise ValueError('Member vector actual full source definition/fields differs')
        linked, proof = COMMON.bind(raw, fields, int(r['address'], 16), r['bindings'], flow, r['roots'])
        if proof != r['linked_flow'] or len(linked) != r['size'] or linked != c.pe_bytes_at(target, int(r['address'], 16), r['size']):
            raise ValueError('Member vector unmasked whole source comparison differs')
    GLOBAL.verify_control(dict(ctl, comparisons=[]), body, target, c, coff, carrier, flow)
    definitions = {d['symbol']: d for d in coff.parse_symbols(body, c.coff_name)[1]}
    for r in ctl['provider_alternatives']:
        raw, fields, src = carrier.section_carrier(body, definitions[r['symbol']]['section'], c, coff)
        if (len(raw) != r['size'] or digest(raw) != r['source_sha256'] or fields != r['fields']
                or COMMON.SOURCE.BASE.canonical_source(src, body) != r['source']
                or len(raw) == r['target_size']):
            raise ValueError('Member vector erases the full unresolved element-provider difference')


def endpoint_historical_rows(plan, name, actual):
    if name not in ['functions.csv', 'function-origins.csv']:
        return actual
    kind = 'function' if name == 'functions.csv' else 'origin'
    selected = {r['address']: r for r in plan['context']['endpoint_successor_pairs']}
    found = [r['address'] for r in actual if r['address'] in selected]
    if len(found) != len(set(found)) or set(found) != set(selected):
        raise ValueError('Member vector endpoint history loses/duplicates the R208 pair')
    result = []
    for r in actual:
        if r['address'] in selected:
            entry = selected[r['address']]
            if r != entry['accepted_' + kind]:
                raise ValueError('Member vector endpoint history rejects unapproved R208 state')
            r = entry['original_' + kind]
        result.append(r)
    return result


def replay_endpoint(plan):
    successor = module('member_vector_insertion', 'verify-vector-insertion-carrier-origins.py')
    current = json.loads((ROOT / successor.EVIDENCE).read_text())
    successor.verify_plan(current)
    old = json.loads((ROOT / 'config/vector-endpoint-origin-evidence.json').read_text())
    for r in plan['context']['endpoint_successor_pairs']:
        q = next(q for q in current['functions'] if q['address'] == r['address'])
        snapshot = next(q for q in old['snapshots'] if q['address'] == r['address'])
        if (any(q[k] != r[k] for k in r)
                or snapshot['function'] != r['original_function']
                or snapshot['origin'] != r['original_origin']):
            raise ValueError('Member vector rewrites R161/R208 original transition evidence')
    result = GLOBAL.run_checked([str(ROOT / 'scripts/repo-python'),
                                 'scripts/verify-vector-insertion-carrier-origins.py'],
                                'Member vector complete reconciled R208/R150 cold proof failed')
    print(result.stdout.strip(), flush=True)
    endpoint = module('member_vector_endpoint', 'verify-vector-endpoint-origins.py')
    holder = endpoint.PAIRED.BUFFER.PRIOR.PRIOR
    saved = holder.rows
    try:
        holder.rows = lambda name: endpoint_historical_rows(plan, name, saved(name))
        if endpoint.main() != 0:
            raise ValueError('Member vector complete unchanged R161 cold proof failed')
    finally:
        holder.rows = saved


def replay_retained(plan, evidence_only=False):
    old = json.loads((ROOT / GLOBAL.EVIDENCE).read_text())
    if digest((ROOT / GLOBAL.EVIDENCE).read_bytes()) != GLOBAL.MANIFEST_SHA256:
        raise ValueError('Member vector rewrites the original R253 manifest')
    GLOBAL.verify_plan(old)
    saved = GLOBAL.rows
    try:
        GLOBAL.rows = lambda name: historical_rows(plan, name, saved(name), evidence_only)
        GLOBAL.verify_canonical(old)
        GLOBAL.replay(old)
    finally:
        GLOBAL.rows = saved
    replay_endpoint(plan)
    for filename in ['verify-authored-origins.py', 'verify-compiler-origins.py']:
        result = GLOBAL.run_checked([str(ROOT / 'scripts/repo-python'), 'scripts/' + filename],
                                    'Member vector entire retained proof failed: ' + filename)
        print(result.stdout.strip())


def replay(plan, evidence_only=False):
    c = module('member_vector_target', 'compare-coff-function.py')
    coff = module('member_vector_coff', 'coff_data.py')
    carrier = module('member_vector_carrier', 'sdk_x3d_carriers.py')
    flow = module('member_vector_flow', 'sdk_image_carriers.py')
    target = c.verified_target()
    if digest(target) != plan['target_sha256']:
        raise ValueError('Member vector target identity differs')
    for path, value in plan['retained_sha256'].items():
        if digest((ROOT / path).read_bytes()) != value:
            raise ValueError('Member vector original retained input differs: ' + path)
    verify_canonical(plan, evidence_only)
    verify_native(plan, target, c, flow)
    scratch = ROOT / 'build/origin-member-vector-lifetime-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    ctl = plan['control']
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / ctl['object_name']
        result = GLOBAL.run_checked([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / ctl['probe']),
                                     str(obj), *ctl['profile']], 'Member vector fresh compiler failed; no cached fallback')
        if COMMON.included_headers(result.stdout + result.stderr) != ctl['headers']:
            raise ValueError('Member vector actual complete header set differs')
        verify_control(plan, obj.read_bytes(), target, c, coff, carrier, flow)
    print('R254 fresh controls, all57 whole comparisons and native/EH witnesses passed; replaying retained proofs.', flush=True)
    replay_retained(plan, evidence_only)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    plan = json.loads((ROOT / EVIDENCE).read_text())
    if digest((ROOT / EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('Member vector immutable manifest identity differs')
    verify_plan(plan)
    replay(plan, args.evidence_only)
    print('R254: three whole vector destructor19 bodies /57 bytes; complete same-receiver construction/EH '
          'state cleanup, fresh whole vendor carriers and original R253, R161, authored/compiler proofs; '
          'three ordinary clear aliases and original element lifetime retained unknown; '
          'no original private types/layouts, ABI, source, mapping or exact credit.')


if __name__ == '__main__':
    main()
