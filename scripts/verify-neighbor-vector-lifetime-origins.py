#!/usr/bin/env python3
"""Cold-check four neighboring vector lifetimes with complete ordinary-policy counterexamples."""
import argparse
import json
from pathlib import Path
import tempfile

ROOT = Path(__file__).resolve().parents[1]
# Reuse full COFF inventories; historical proofs run unchanged in pinned Git checkouts.
import importlib.util


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


HISTORY = module('neighbor_history', 'origin_history.py')
GLOBAL = module('neighbor_vector_global', 'verify-global-vector-lifetime-origins.py')
COMMON = GLOBAL.COMMON
rows = COMMON.rows
digest = COMMON.digest
metadata_digest = COMMON.metadata_digest
EVIDENCE = 'config/neighbor-vector-lifetime-origin-evidence.json'
MANIFEST_SHA256 = '8ec69e406cde96992cebc9a83e41db3d5e95c1e348b084860936940830fb1f64'
PLAN_DIGESTS = {'evidence_id': '2561ed29c636427b2fc7f1cfea8861d217bee0ab1cb7fc492b02276b16c03ea5', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'baseline_commit': 'c60a2d830276c331098f7e39645aad5343b432922b079a451e5140c830168e0e', 'functions': 'f26098a6f70e6d93b6d1e0ddcdf54b6ed4a98dc990ea8206bb46c5c0867ca9fa', 'retained_unknown': 'c7ed25a685b10923225c14f9058951406f502dfc930da695547e6820cb871424', 'native': 'cb5c2b43df5938ba8a5eec8ae3a58713338bf95d3fa9bc3863e225d1e072e5ad', 'canonical': '39b6a999a7d12b53ff8738de96b3b22dcea9dd9b0bbc9b6d3541e81aa942b8cf', 'unselected_sha256': 'fb03bc9f9a7323936ccd20b86aed70ecc56fbe51c4884729111b3b76f4f53b7b', 'context': '0c00211dddb7f9da4c3d7e939a8dd963d67e4f30ccba429d9b3cf6d9370e4cef', 'control': '5717b418c1df39a680af9fcc008a08513d1f41e8cb7e9fe9402f4b861beaf29a', 'history': 'bdf05ae37bde948b85893e821fd8a7cbf092274125d8804e89a426059bf0d3d7', 'retained_sha256': '5837b656764d54cdc121f1fcdfb63b2b44ff024befc7c479fb32590643ab40cb', 'interpretation': 'aa09b41e9a78be294d4d5246cfe0c31d6611c51a97f7ffcc5263ba621e1133aa'}
WHOLE = {'0x004589F0': 19, '0x00458AD0': 19, '0x00458BA0': 19, '0x005F7FA0': 19}
UNKNOWN = ['0x00458A80', '0x00458B50', '0x00458C20', '0x005F8020']


def verify_plan(plan):
    if set(plan) != set(PLAN_DIGESTS):
        raise ValueError('Neighbor vector immutable schema differs')
    for key, value in PLAN_DIGESTS.items():
        if metadata_digest(plan[key]) != value:
            raise ValueError('Neighbor vector immutable whole evidence differs: ' + key)
    if (plan['evidence_id'] != 'R255' or plan['retained_unknown'] != UNKNOWN
            or {r['address']: r['size'] for r in plan['functions']} != WHOLE):
        raise ValueError('Neighbor vector bounded scope differs')
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
                or r['accepted_origin']['evidence_id'] != 'R255'):
            raise ValueError('Neighbor vector gains unsupported extent/ABI/source/exact credit')


def historical_rows(plan, name, actual, evidence_only=False):
    """Project only the four independently validated literal transitions to R254."""
    if name not in ['functions.csv', 'function-origins.csv']:
        return actual
    kind = 'function' if name == 'functions.csv' else 'origin'
    selected = {r['address']: r for r in plan['functions']}
    observed = [r['address'] for r in actual if r['address'] in selected]
    if len(observed) != len(set(observed)) or set(observed) != set(selected):
        raise ValueError('Neighbor vector historical view loses or duplicates a selected pair')
    result = []
    for r in actual:
        if r['address'] in selected:
            entry = selected[r['address']]
            state = 'original' if evidence_only else 'accepted'
            if r != entry[state + '_' + kind]:
                raise ValueError('Neighbor vector historical view rejects an unapproved pair')
            r = entry['original_' + kind]
        result.append(r)
    return result


def verify_canonical(plan, evidence_only=False):
    fs = {r['address']: r for r in rows('functions.csv')}
    os = {r['address']: r for r in rows('function-origins.csv')}
    selected = {r['address']: r for r in plan['functions']}
    for name in ['functions.csv', 'function-origins.csv']:
        if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE]) != plan['unselected_sha256'][name]:
            raise ValueError('Neighbor vector changes unrelated canonical rows')
    for pair in plan['canonical']:
        a = pair['function']['address']
        expected = pair
        if a in selected:
            state = 'original' if evidence_only else 'accepted'
            expected = dict(function=selected[a][state + '_function'], origin=selected[a][state + '_origin'])
        if dict(function=fs[a], origin=os[a]) != expected:
            raise ValueError('Neighbor vector full canonical pair differs: ' + a)
    if any(os[a]['origin'] != 'unknown' or fs[a]['owner'] for a in UNKNOWN + ['0x0045B6B0', '0x005FAAD0', '0x004591E0', '0x0045AAE0']):
        raise ValueError('Neighbor vector resolves an ordinary clear or unresolved element lifetime')


def verify_receiver_links(plan):
    bodies = {r['address']: r for r in plan['native']}
    for link in plan['context']['links']:
        ins = bodies[link['owner']]['instructions']
        by = {r['offset']: r for r in ins}
        call, state = by[link['constructor_site']], by[link['state_site']]
        prefix = [r for r in ins if r['offset'] < call['offset']]
        receiver = link['receiver_offset']
        expected = [('mov', 'ecx, dword ptr [ebp - ' + hex(-link['receiver_local']) + ']')]
        if receiver:
            expected.append(('add', 'ecx, ' + (str(receiver) if receiver < 10 else hex(receiver))))
        if (call['mnemonic'] != 'call' or int(call['operands'], 16) != int(link['constructor'], 16)
                or [(r['mnemonic'], r['operands']) for r in prefix[-len(expected):]] != expected
                or state['offset'] != call['offset'] + call['size'] or state['mnemonic'] != 'mov'
                or state['operands'] != ('dword' if link['state'] == 0 else 'byte') + ' ptr [ebp - 4], ' + str(link['state'])):
            raise ValueError('Neighbor vector loses same receiver and completed construction state')
        callback = next(r for b in plan['context']['blocks'] for r in b['callbacks'] if r['address'] == link['cleanup'])
        if [(r['mnemonic'], r['operands']) for r in callback['instructions'][:-1]] != expected:
            raise ValueError('Neighbor vector callback uses a different constructed subobject')

def verify_context(plan):
    comparisons = plan['control']['comparisons']
    links = plan['context']['links']
    if (len(links) != 5 or {r['destructor'] for r in links} != set(WHOLE)
            or [(r['owner'], r['state'], r['receiver_offset']) for r in links] != [
                ('0x004567B0', 0, 1128), ('0x004587E0', 1, 84),
                ('0x004587E0', 2, 100), ('0x00458960', 0, 0), ('0x005F7F20', 0, 0)]):
        raise ValueError('Neighbor vector loses a complete construction-state cohort')
    verify_receiver_links(plan)
    def one(address, role):
        found = [r for r in comparisons if r['address'] == address and r['role'] == role]
        if len(found) != 1:
            raise ValueError('Neighbor vector loses a unique whole source carrier')
        return found[0]
    for link in plan['context']['links']:
        ctor = one(link['constructor'], 'vendor-constructor42')
        dtor = one(link['destructor'], 'vendor-destructor19')
        if (ctor['size'] != 42 or dtor['size'] != 19
                or not ctor['symbol'].startswith('??0?$vector@')
                or not dtor['symbol'].startswith('??1?$vector@')
                or ctor['symbol'][3:] != dtor['symbol'][3:]):
            raise ValueError('Neighbor vector substitutes the vendor constructor/destructor namespace')
        block = next(r for r in plan['context']['blocks'] if any(
            o['owner_address'] == link['owner'] for o in json.loads(r['frame']['owners'])))
        callback = next(r for r in block['callbacks'] if r['address'] == link['cleanup'])
        if (callback['destination'] != link['destructor'] or callback['state_index'] != link['state']
                or callback['to_state'] != link['state'] - 1):
            raise ValueError('Neighbor vector changes the completed subobject EH state/provider')
    ordinary = [r for r in comparisons if r['role'] == 'ordinary-cleanup19-positive-retains-unknown']
    if ([r['address'] for r in ordinary] != UNKNOWN or any(
            r['size'] != 19 or not r['symbol'].startswith('?Cleanup@') for r in ordinary)):
        raise ValueError('Neighbor vector drops an actual ordinary whole-body counterexample')
    for code_address, data_address, dtor_address in [
            ('0x00656220', '0x006697DC', '0x00458AD0'),
            ('0x006566D0', '0x0066A08C', '0x005F7FA0')]:
        code = one(code_address, 'whole-compiler-base-cleanup-and-dispatch18')
        data = one(data_address, 'whole-compiler-unwind-and-function-info36')
        dtor = one(dtor_address, 'vendor-destructor19')
        if (code['size'] != 18 or code['roots'] != [0, 8] or code['definition']['offset'] != 8
                or data['size'] != 36 or data['roots'] or data['definition']['offset'] != 8
                or code['fields'][0]['symbol'] != dtor['symbol']
                or code['fields'][0]['symbol_section'] != dtor['section']
                or code['bindings'][0]['target'] != dtor['address']
                or code['fields'][1]['symbol'] != data['symbol']
                or code['fields'][1]['symbol_section'] != data['section']
                or code['fields'][1]['symbol_offset'] != 8
                or int(code['bindings'][1]['target'], 16) != int(data_address, 16) + 8
                or data['bindings'][0]['target'] != code['address']
                or data['fields'][0]['symbol_section'] != code['section']
                or data['fields'][0]['symbol_offset'] != 0
                or data['bindings'][1]['target'] != data['address']
                or data['fields'][1]['symbol_section'] != data['section']
                or data['fields'][1]['symbol_offset'] != 0):
            raise ValueError('Neighbor vector loses full compiler code/data carriers or actual local providers')
    alternatives = {r['symbol']: r for r in plan['control']['alternatives']}
    for owner, parent, size, ctor, cleanup in [
            ('LargeVectorPolicy', '0x00458960', 93, '0x00458AA0', '0x00458B50'),
            ('SixteenVectorPolicy', '0x005F7F20', 75, '0x005F7F70', '0x005F8020')]:
        policy = one(parent, 'ordinary-policy-parent' + str(size) + '-positive')
        construction = one(ctor, 'vendor-constructor42')
        clear = one(cleanup, 'ordinary-cleanup19-positive-retains-unknown')
        if (policy['size'] != size or policy['symbol'] != '??0' + owner + '@@QAE@XZ'
                or alternatives[policy['symbol']]['size'] != size
                or alternatives['__ehhandler$' + policy['symbol']]['size'] != 18):
            raise ValueError('Neighbor vector loses a complete ordinary inherited parent counterexample')
        for offset, provider in [(32, construction), (47, clear)]:
            field = next(f for f in policy['fields'] if f['offset'] == offset)
            binding = next(b for b in policy['bindings'] if b['offset'] == offset)
            if (field['symbol'] != provider['symbol'] or field['symbol_section'] != provider['section']
                    or binding['target'] != provider['address']):
                raise ValueError('Neighbor vector ordinary parent substitutes the actual provider')
    if (alternatives['??0WordVectorPolicy@@QAE@XZ']['size'] != 72
            or alternatives['__ehhandler$??0ThreeVectorObservation@@QAE@XZ']['size'] != 40):
        raise ValueError('Neighbor vector crops or pads the natural multi-member EH alternative')
    negative = plan['control']['provider_alternatives']
    if ([(r['address'], r['size'], r['target_size']) for r in negative]
            != [('0x0045B6B0', 5, 15), ('0x005FAAD0', 5, 15)]):
        raise ValueError('Neighbor vector hides unresolved original element destruction boundaries')
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
                raise ValueError('Neighbor vector loses a full provider or declared retained boundary')
            if (f['symbol_section'], f['symbol_offset']) != (d['section'], d['offset']):
                raise ValueError('Neighbor vector substitutes an actual source provider')


def verify_native(plan, target, c, flow):
    auth = module('neighbor_vector_auth', 'verify-authored-origins.py')
    eh = module('neighbor_vector_eh', 'compiler_eh.py')
    entries = {int(r['address'], 16) for r in rows('functions.csv')}
    bodies = {r['address']: r for r in plan['native']}
    for a, r in bodies.items():
        at = int(a, 16)
        raw = c.pe_bytes_at(target, at, r['size'])
        cfg = (flow.flow(raw, at, [0], [], {at + 1: 0x642A61}, {}) if a == '0x00640F15'
               else list(auth.verify_body(raw, at, [], lambda x, n: c.pe_bytes_at(target, x, n), [])))
        if (digest(raw) != r['body_sha256'] or COMMON.SOURCE.instructions(raw, at, flow) != r['instructions']
                or cfg != r['cfg']):
            raise ValueError('Neighbor vector complete native body/CFG differs: ' + a)
    for r in plan['context']['alignment']:
        raw = c.pe_bytes_at(target, int(r['address'], 16), r['size'])
        if raw != b'\xcc' * r['size'] or digest(raw) != r['sha256']:
            raise ValueError('Neighbor vector claims external alignment')
    for r in plan['context']['parents']:
        if r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Neighbor vector original authored parent evidence differs')
    for r in plan['context']['constructors']:
        if r['helpers_record'] not in rows('vendor-vector-helper-origins.csv'):
            raise ValueError('Neighbor vector original independently accepted constructor differs')
    for block in plan['context']['blocks']:
        frame = block['frame']
        if frame not in rows('compiler-eh-frames.csv'):
            raise ValueError('Neighbor vector original EH frame differs')
        eh.verify_frame(frame, lambda a, n: c.pe_bytes_at(target, a, n),
                        lambda a, n: c.pe_bytes_at(target, a, n), entries, set())
        at = int(block['address'], 16)
        raw = c.pe_bytes_at(target, at, block['size'])
        instructions = COMMON.SOURCE.instructions(raw, at, flow)
        calls = {at + x['offset'] + x['size'] - 4: int(x['operands'], 16)
                 for x in instructions if x['mnemonic'] in ['jmp', 'call'] and x['operands'].startswith('0x')}
        cfg = flow.flow(raw, at, block['roots'], [], calls,
                        {int(frame['handler_address'], 16) + 1: int(frame['funcinfo_address'], 16)})
        if (digest(raw) != block['body_sha256'] or instructions != block['instructions'] or cfg != block['cfg']
                or digest(c.pe_bytes_at(target, int(block['data_address'], 16), block['data_size'])) != block['data_sha256']):
            raise ValueError('Neighbor vector complete compiler code/data differs')
        for r in block['callbacks']:
            raw = c.pe_bytes_at(target, int(r['address'], 16), r['size'])
            kind, dest = eh.cleanup_template(raw, int(r['address'], 16), entries)
            if kind != r['kind'] or dest != int(r['destination'], 16):
                raise ValueError('Neighbor vector actual compiler callback differs')
    if any(r not in rows('compiler-origin-evidence.csv') for r in plan['context']['callback_records']):
        raise ValueError('Neighbor vector original callback proof differs')
    verify_context(plan)


def verify_control(plan, body, target, c, coff, carrier, flow):
    ctl = plan['control']
    if GLOBAL.inventory(body, c, coff, carrier) != ctl['emission']:
        raise ValueError('Neighbor vector full ordinary emission/AUX/fields/storage differs')
    for r in ctl['comparisons']:
        raw, fields, source = carrier.section_carrier(body, r['section'], c, coff)
        if (r['definition'] not in source['definitions'] or fields != r['fields']
                or COMMON.SOURCE.BASE.canonical_source(source, body) != r['source'] or digest(raw) != r['source_sha256']):
            raise ValueError('Neighbor vector actual full source definition/fields differs')
        linked, proof = bind_whole(r, raw, fields, target, c, flow)
        if proof != r['linked_flow'] or len(linked) != r['size'] or linked != c.pe_bytes_at(target, int(r['address'], 16), r['size']):
            raise ValueError('Neighbor vector unmasked whole source comparison differs')
    GLOBAL.verify_control(dict(ctl, comparisons=[]), body, target, c, coff, carrier, flow)
    definitions = {d['symbol']: d for d in coff.parse_symbols(body, c.coff_name)[1]}
    for r in ctl['provider_alternatives']:
        raw, fields, src = carrier.section_carrier(body, definitions[r['symbol']]['section'], c, coff)
        if (len(raw) != r['size'] or digest(raw) != r['source_sha256'] or fields != r['fields']
                or COMMON.SOURCE.BASE.canonical_source(src, body) != r['source']
                or len(raw) == r['target_size']):
            raise ValueError('Neighbor vector erases the full unresolved element-provider difference')


def bind_whole(r, raw, fields, target, c, flow):
    try:
        return COMMON.bind(raw, fields, int(r['address'], 16), r['bindings'], flow, r['roots'])
    except ValueError:
        if r['address'] != '0x00405460' or not r['symbol'].startswith('?_Copy@'):
            raise
        # The accepted R004 word-copy routine has an early RET. Verify the whole
        # decoded body and all internal branches after binding every field.
        linked, _ = COMMON.bind(raw, fields, int(r['address'], 16), r['bindings'], flow, [])
        auth = module('neighbor_copy_auth', 'verify-authored-origins.py')
        proof = dict(ret_based_complete_cfg=list(auth.verify_body(linked, int(r['address'], 16), [],
                     lambda a, n: c.pe_bytes_at(target, a, n), [])))
        return linked, proof


def replay_retained(plan):
    for item in plan['history']:
        HISTORY.replay(item)


def replay(plan, evidence_only=False):
    c = module('neighbor_vector_target', 'compare-coff-function.py')
    coff = module('neighbor_vector_coff', 'coff_data.py')
    carrier = module('neighbor_vector_carrier', 'sdk_x3d_carriers.py')
    flow = module('neighbor_vector_flow', 'sdk_image_carriers.py')
    target = c.verified_target()
    if digest(target) != plan['target_sha256']:
        raise ValueError('Neighbor vector target identity differs')
    for path, value in plan['retained_sha256'].items():
        if digest((ROOT / path).read_bytes()) != value:
            raise ValueError('Neighbor vector original retained input differs: ' + path)
    verify_canonical(plan, evidence_only)
    verify_native(plan, target, c, flow)
    scratch = ROOT / 'build/origin-neighbor-vector-lifetime-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    ctl = plan['control']
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / ctl['object_name']
        result = GLOBAL.run_checked([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / ctl['probe']),
                                     str(obj), *ctl['profile']], 'Neighbor vector fresh compiler failed; no cached fallback')
        if COMMON.included_headers(result.stdout + result.stderr) != ctl['headers']:
            raise ValueError('Neighbor vector actual complete header set differs')
        verify_control(plan, obj.read_bytes(), target, c, coff, carrier, flow)
    print('R255 fresh controls, all82 whole comparisons and native/EH witnesses passed; replaying retained proofs.', flush=True)
    replay_retained(plan)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    plan = json.loads((ROOT / EVIDENCE).read_text())
    if digest((ROOT / EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('Neighbor vector immutable manifest identity differs')
    verify_plan(plan)
    replay(plan, args.evidence_only)
    print('R255: four whole vector destructor19 bodies /76 bytes; five complete same-receiver '
          'construction-state connections and nine original EH frames; 82 fresh unmasked source '
          'comparisons, whole original R254/R212/R211/R210/R209/R227 cold proofs; four ordinary clear '
          'aliases and two element lifetimes retained unknown; no ABI/source/mapping/exact credit.')



if __name__ == '__main__':
    main()
