#!/usr/bin/env python3
"""Cold-check coherent outer cleanup policies and complete implicit alternatives."""
import argparse
import importlib.util
import json
from pathlib import Path
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


PREVIOUS = module('outer_policy_previous', 'verify-neighbor-vector-lifetime-origins.py')
COMMON = PREVIOUS.COMMON
GLOBAL = PREVIOUS.GLOBAL
rows = COMMON.rows
digest = COMMON.digest
metadata_digest = COMMON.metadata_digest
EVIDENCE = 'config/outer-vector-policy-origin-evidence.json'
MANIFEST_SHA256 = '76565cc94706a6f6c30b44292a4a41a601ff1208816c691484a885583e2e6e82'
PLAN_DIGESTS = {'evidence_id': 'bd35f57ff82c81dfc81687bc6aeef3f1dcfe0e717551033ead217caa1b7bde26', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'baseline_commit': '0998e32a79a989b44a1eaa00735bb7365e08857f5c5b6cf40252061e2e479618', 'functions': '9ba47e1bec9c9c21591de481a3d151a0292fe47f71ab67c0dd4b7f2bba1ae5c6', 'authored_path': '2aa7f40ab04980ca851ff8d5f19be56f0243ffd023d38ad7211c1938404a7485', 'authored': '70fca433f6e16d997760203f3657327229d74a13776b6ef3852f87969a875010', 'retained_unknown': 'c4bee6753e662f0716cb57f1f908a4382b5d5ec0953dafdaaac8ddf3a11ff4b6', 'native': '165530d583f3d4a5b166f56393081a50791e966424b2e2902141b42567e95f00', 'canonical': '36bf8aba88e6c1cfbabf9d084f13ce7220111ae26007e0afdbc8bd90da98d4ae', 'unselected_sha256': '7cf2ed9eb43ea6be414ea42116cb3a6918d1f05f55aab9319cad6266a29f055d', 'context': '28675808e217103c3a64408613a9bdf1587967e25e480f6e0c55d9b297c9be69', 'controls': '6743838cdd42b173bf3200db55140fef076707aa500fafde5020d75c6564b5f4', 'history': '8561e6333d5aa2d77a04910e90d9a344878a9217c8b39f206a544764a90585d2', 'retained_sha256': '7867f80dcf66e6704a7016746194cee5ed55fd22f5391776c4853b8856f7414a', 'interpretation': '605ea97ca1da549ea24686940ca5e414b4106f10588a4425238997b14fd2728d'}
WHOLE = {'0x004586C0': 72, '0x005F7ED0': 72}


def verify_plan(plan):
    if set(plan) != set(PLAN_DIGESTS):
        raise ValueError('Outer policy immutable schema differs')
    for key, value in PLAN_DIGESTS.items():
        if metadata_digest(plan[key]) != value:
            raise ValueError('Outer policy immutable evidence differs: ' + key)
    if plan['evidence_id'] != 'R256' or {r['address']: r['size'] for r in plan['functions']} != WHOLE:
        raise ValueError('Outer policy bounded scope differs')
    mutable = {'proposed_name', 'module', 'evidence', 'notes'}
    for r in plan['functions']:
        old, new = r['original_function'], r['accepted_function']
        if (r['original_origin']['origin'] != 'unknown'
                or r['accepted_origin']['origin'] != 'authored'
                or r['accepted_origin']['disposition'] != 'authored'
                or r['accepted_origin']['evidence_id'] != 'R256'
                or {k: v for k, v in old.items() if k not in mutable}
                != {k: v for k, v in new.items() if k not in mutable}
                or any(new[k] for k in ['source_file', 'signature', 'calling_convention'])
                or new['match_percent'] != '0.00'):
            raise ValueError('Outer policy gains unsupported layout/ABI/source/mapping/exact credit')


def historical_rows(plan, name, actual, evidence_only=False):
    """Restore only the two literal validated R256 pairs in the R255 view."""
    if name not in ['functions.csv', 'function-origins.csv']:
        return actual
    kind = 'function' if name == 'functions.csv' else 'origin'
    selected = {r['address']: r for r in plan['functions']}
    observed = [r['address'] for r in actual if r['address'] in selected]
    if len(observed) != 2 or set(observed) != set(selected):
        raise ValueError('Outer policy historical view loses or duplicates a pair')
    result = []
    for r in actual:
        if r['address'] in selected:
            expected = selected[r['address']]
            if r != expected[('original_' if evidence_only else 'accepted_') + kind]:
                raise ValueError('Outer policy historical view rejects an unsupported pair')
            r = expected['original_' + kind]
        result.append(r)
    return result


def verify_canonical(plan, evidence_only=False):
    actual = {name: rows(name) for name in ['functions.csv', 'function-origins.csv']}
    for name, value in actual.items():
        historical_rows(plan, name, value, evidence_only)
        if metadata_digest([r for r in value if r['address'] not in WHOLE]) != plan['unselected_sha256'][name]:
            raise ValueError('Outer policy changes unrelated canonical rows')
    fs = {r['address']: r for r in actual['functions.csv']}
    os = {r['address']: r for r in actual['function-origins.csv']}
    selected = {r['address']: r for r in plan['functions']}
    for pair in plan['canonical']:
        address = pair['function']['address']
        expected = pair
        if address in selected:
            r = selected[address]
            state = 'original' if evidence_only else 'accepted'
            expected = dict(function=r[state + '_function'], origin=r[state + '_origin'])
        if dict(function=fs[address], origin=os[address]) != expected:
            raise ValueError('Outer policy literal whole canonical pair differs: ' + address)
    if any(os[a]['origin'] != 'unknown' or fs[a]['owner'] for a in plan['retained_unknown']):
        raise ValueError('Outer policy resolves a protected clear/element/other lifetime')
    if rows(Path(plan['authored_path']).name) != plan['authored']:
        raise ValueError('Outer policy complete authored evidence differs')


def verify_context(plan):
    ctl = plan['controls'][0]
    comparisons = {(r['symbol'], r['address']): r for r in ctl['comparisons']}
    alternatives = {r['symbol']: r for r in ctl['alternatives']}
    native = {r['address']: r for r in plan['native']}
    pairs = plan['context']['pairs']
    if [(p['outer'], p['constructor'], p['allocation_size']) for p in pairs] != [
            ('0x004586C0', '0x00458960', 20), ('0x005F7ED0', '0x005F7F20', 16)]:
        raise ValueError('Outer policy loses the complete paired game/lifetime cohort')

    def binding(row, offset):
        field = next(f for f in row['fields'] if f['offset'] == offset)
        value = next(v for v in row['bindings'] if v['offset'] == offset)
        return field, value

    def provider(row, offset, expected):
        field, value = binding(row, offset)
        if value['target'] != expected:
            raise ValueError('Outer policy changes the actual ordered provider')
        result = comparisons.get((field['symbol'], expected))
        if (not result or field['symbol_section'] != result['definition']['section']
                or field['symbol_offset'] != result['definition']['offset']):
            raise ValueError('Outer policy substitutes the actual complete defining provider')
        return result

    for p in pairs:
        ctor = comparisons[('??0' + p['owner'] + 'QAE@XZ', p['constructor'])]
        outer = comparisons[('??1' + p['owner'] + 'QAE@XZ', p['outer'])]
        base_ctor = provider(ctor, 32, p['base_constructor'])
        clear = provider(ctor, 47, p['clear'])
        if (ctor['size'] != (93 if p['allocation_size'] == 20 else 75)
                or outer['size'] != 72 or base_ctor['size'] != 42
                or not base_ctor['symbol'].startswith('??0?$vector@')
                or clear['size'] != 19 or not clear['symbol'].startswith('?Cleanup@')):
            raise ValueError('Outer policy loses real whole construction/base/ordinary cleanup')
        if provider(outer, 39, p['clear']) != clear:
            raise ValueError('Outer policy constructor/destructor use different ordinary definitions')
        base_dtor = provider(outer, 54, p['base_destructor'])
        if (base_dtor['size'] != 19 or not base_dtor['symbol'].startswith('??1?$vector@')
                or base_ctor['symbol'][3:] != base_dtor['symbol'][3:]):
            raise ValueError('Outer policy changes the independently accepted vector lifetime')
        instructions = {r['offset']: r for r in native[p['outer']]['instructions']}
        for offset, value in [(28, '0'), (43, '0xffffffff')]:
            if (instructions[offset]['mnemonic'], instructions[offset]['operands']) != (
                    'mov', 'dword ptr [ebp - 4], ' + value):
                raise ValueError('Outer policy loses actual destruction-state ordering')
        for load, call, destination in [(35, 38, p['clear']), (50, 53, p['base_destructor'])]:
            if ((instructions[load]['mnemonic'], instructions[load]['operands'])
                    != ('mov', 'ecx, dword ptr [ebp - 0x10]')
                    or instructions[call]['mnemonic'] != 'call'
                    or int(instructions[call]['operands'], 16) != int(destination, 16)):
                raise ValueError('Outer policy loses identical real receiver and complete ordered calls')
        game = native[p['producer']]['instructions']
        at = {r['offset']: i for i, r in enumerate(game)}
        push, alloc = game[at[p['allocation_push_site']]], game[at[p['allocation_call_site']]]
        if ((push['mnemonic'], push['operands']) != ('push', hex(p['allocation_size']))
                or alloc['mnemonic'] != 'call' or alloc['operands'] != '0x64159d'
                or alloc['offset'] != push['offset'] + push['size']):
            raise ValueError('Outer policy loses independent whole game allocation size/provider')
        i = at[p['allocation_call_site']]
        local = hex(-p['receiver_local'])
        if [(r['mnemonic'], r['operands']) for r in game[i + 1:i + 3]] != [
                ('add', 'esp, 4'), ('mov', 'dword ptr [ebp - ' + local + '], eax')]:
            raise ValueError('Outer policy loses the actual newly allocated receiver')
        i = at[p['constructor_call_site']]
        if [(r['mnemonic'], r['operands']) for r in game[i - 1:i + 1]] != [
                ('mov', 'ecx, dword ptr [ebp - ' + local + ']'),
                ('call', hex(int(p['constructor'], 16)))]:
            raise ValueError('Outer policy game producer constructs a different receiver')
        deleting = comparisons[('??_G' + p['owner'] + 'QAEPAXI@Z', p['deleting'])]
        if deleting['size'] != 44 or provider(deleting, 11, p['outer']) != outer:
            raise ValueError('Outer policy replaces full independent compiler deleting context')
        for prefix, key in [('??0', 'ctor_handler'), ('??1', 'dtor_handler')]:
            code_address = f"0x{int(p[key], 16) - 8:08X}"
            code = comparisons[('__ehhandler$' + prefix + p['owner'] + 'QAE@XZ', code_address)]
            frame = next(b['frame'] for b in plan['context']['blocks'] if b['frame']['handler_address'] == p[key])
            data_field = next(f for f in code['fields'] if f['type'] == 'DIR32')
            data = comparisons[(data_field['symbol'], frame['unwind_address'])]
            if (code['size'] != 18 or code['roots'] != [0, 8] or code['definition']['offset'] != 8
                    or data['size'] != 36 or data['roots'] or data['definition']['offset'] != 8
                    or provider(code, 4, p['base_destructor']) != base_dtor
                    or data_field['symbol_section'] != data['section'] or data_field['symbol_offset'] != 8
                    or binding(code, data_field['offset'])[1]['target'] != frame['funcinfo_address']
                    or data['fields'][0]['symbol_section'] != code['section']
                    or data['fields'][0]['symbol_offset'] != 0
                    or data['bindings'][0]['target'] != code_address
                    or data['fields'][1]['symbol_section'] != data['section']
                    or data['fields'][1]['symbol_offset'] != 0
                    or data['bindings'][1]['target'] != data['address']):
                raise ValueError('Outer policy crops compiler code/data or substitutes a local provider')
        short = p['allocation_size'] == 20
        single = 'ImplicitShort@UValue116' if short else 'ImplicitSingle@UValue16'
        if alternatives['??1?$' + single + '@@@@QAE@XZ']['size'] != 19:
            raise ValueError('Outer policy hides a complete single-base implicit destructor')
        member = 'ImplicitMember116' if short else 'ImplicitMember16'
        positive = comparisons[('??0' + member + '@@QAE@XZ', p['constructor'])]
        member_field = binding(positive, 32)[0]
        member_definition = alternatives[member_field['symbol']]
        if (positive['role'] != 'implicit-member-parent-byte-positive'
                or member_definition['size'] != 22 or member_definition['size'] == base_ctor['size']
                or member_field['symbol_section'] != member_definition['section']):
            raise ValueError('Outer policy bootstraps a byte-positive member parent through a false provider')
        after = 'Implicit116' if short else 'Implicit16'
        first = 'EmptyFirst116' if short else 'EmptyFirst16'
        if (alternatives['??1' + after + '@@QAE@XZ']['size'] != 98
                or alternatives['??1?$EmptyCleanup@U' + after + '@@@@QAE@XZ']['size'] != 45
                or alternatives['??0' + first + '@@QAE@XZ']['size'] != (97 if short else 79)
                or alternatives['__ehhandler$??0' + first + '@@QAE@XZ']['size'] != 26):
            raise ValueError('Outer policy erases whole empty-base body/construction/EH differences')
        reversed_ = comparisons[('??1' + first + '@@QAE@XZ', p['outer'])]
        if (reversed_['size'] != 72 or reversed_['role'] != 'implicit-empty-first-destructor-byte-positive'
                or binding(reversed_, 39)[0]['symbol'] != base_dtor['symbol']
                or not binding(reversed_, 54)[0]['symbol'].startswith('??1?$EmptyCleanup@')):
            raise ValueError('Outer policy hides the genuine reversed-provider implicit72 positive')
    if ctl['layouts'][0]['values'] != [16, 20, 20, 24, 16, 1, 16, 20, 16, 20, 20]:
        raise ValueError('Outer policy hides complete observation/empty-base allocation differences')
    if {(r['address'], r['size'], r['target_size']) for r in ctl['provider_alternatives']} != {
            ('0x0045B6B0', 5, 15), ('0x005FAAD0', 5, 15)}:
        raise ValueError('Outer policy erases original nontrivial element boundaries')
    # Member/empty-first byte positives are deliberately outside the credited
    # provider graph. They retain their actual source definitions and failures.
    credited = {k: r for k, r in comparisons.items() if r['role'] not in [
        'implicit-member-parent-byte-positive', 'implicit-empty-first-destructor-byte-positive']}
    boundaries = {(r['symbol'], r['address']): r for r in ctl['external'] + ctl['provider_alternatives']}
    for r in credited.values():
        for f, value in zip(r['fields'], r['bindings']):
            if f['type'] != 'REL32' or f['symbol'] == '___CxxFrameHandler' or r['symbol'].startswith('?_Xlen@'):
                continue
            key = (f['symbol'], value['target'])
            result = credited.get(key)
            d = result['definition'] if result else boundaries.get(key, {}).get('definition')
            if d is None and key in boundaries and 'source' in boundaries[key]:
                d = next(d for d in boundaries[key]['source']['definitions'] if d['symbol'] == f['symbol'])
            if d is None or (f['symbol_section'], f['symbol_offset']) != (d['section'], d['offset']):
                raise ValueError('Outer policy loses a complete real provider or declared original boundary')


def verify_native(plan, target, c, flow, evidence_only=False):
    original = json.loads((ROOT / PREVIOUS.EVIDENCE).read_text())
    PREVIOUS.verify_plan(original)
    saved = PREVIOUS.rows
    try:
        PREVIOUS.rows = lambda name: historical_rows(plan, name, saved(name), evidence_only)
        PREVIOUS.verify_canonical(original)
        PREVIOUS.verify_native(original, target, c, flow)
    finally:
        PREVIOUS.rows = saved
    auth = module('outer_authored', 'verify-authored-origins.py')
    eh = module('outer_eh', 'compiler_eh.py')
    entries = {int(r['address'], 16) for r in rows('functions.csv')}
    for r in plan['native']:
        at = int(r['address'], 16)
        raw = c.pe_bytes_at(target, at, r['size'])
        cfg = (flow.flow(raw, at, [0], [], {at + 1: 0x642A61}, {}) if r['address'] == '0x00640F15'
               else list(auth.verify_body(raw, at, [], lambda a, n: c.pe_bytes_at(target, a, n), [])))
        if (digest(raw) != r['body_sha256'] or COMMON.SOURCE.instructions(raw, at, flow) != r['instructions']
                or cfg != r['cfg']):
            raise ValueError('Outer policy complete native body/CFG differs')
    for r in plan['context']['game_anchors']:
        if r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Outer policy loses independent whole authored game context')
    for r in plan['context']['deleting_records']:
        if r not in rows('scalar-deleting-origin-evidence.csv'):
            raise ValueError('Outer policy loses independent original compiler provenance')
    for r in plan['context']['alignment']:
        raw = c.pe_bytes_at(target, int(r['address'], 16), r['size'])
        if raw != b'\xcc' * r['size'] or digest(raw) != r['sha256']:
            raise ValueError('Outer policy consumes external alignment')
    for b in plan['context']['blocks']:
        frame = b['frame']
        if frame not in rows('compiler-eh-frames.csv'):
            raise ValueError('Outer policy changes original frame/owner provenance')
        eh.verify_frame(frame, lambda a, n: c.pe_bytes_at(target, a, n),
                        lambda a, n: c.pe_bytes_at(target, a, n), entries, set())
        at = int(b['address'], 16)
        raw = c.pe_bytes_at(target, at, b['size'])
        ins = COMMON.SOURCE.instructions(raw, at, flow)
        calls = {at + i['offset'] + i['size'] - 4: int(i['operands'], 16)
                 for i in ins if i['mnemonic'] in ['call', 'jmp'] and i['operands'].startswith('0x')}
        cfg = flow.flow(raw, at, b['roots'], [], calls,
                        {int(frame['handler_address'], 16) + 1: int(frame['funcinfo_address'], 16)})
        if (digest(raw) != b['body_sha256'] or ins != b['instructions'] or cfg != b['cfg']
                or digest(c.pe_bytes_at(target, int(b['data_address'], 16), b['data_size'])) != b['data_sha256']):
            raise ValueError('Outer policy loses complete original compiler code/data')
        for callback in b['callbacks']:
            raw = c.pe_bytes_at(target, int(callback['address'], 16), callback['size'])
            kind, destination = eh.cleanup_template(raw, int(callback['address'], 16), entries)
            if kind != callback['kind'] or destination != int(callback['destination'], 16):
                raise ValueError('Outer policy changes actual original cleanup provider')
    verify_context(plan)


def verify_control(ctl, body, target, c, coff, carrier, flow):
    if GLOBAL.inventory(body, c, coff, carrier) != ctl['emission']:
        raise ValueError('Outer policy full emission/storage/definitions/AUX/fields differ')
    for r in ctl['comparisons']:
        raw, fields, src = carrier.section_carrier(body, r['section'], c, coff)
        if (r['definition'] not in src['definitions'] or fields != r['fields']
                or COMMON.SOURCE.BASE.canonical_source(src, body) != r['source']
                or digest(raw) != r['source_sha256']):
            raise ValueError('Outer policy actual full defining carrier differs')
        linked, cfg = PREVIOUS.bind_whole(r, raw, fields, target, c, flow)
        if cfg != r['linked_flow'] or len(linked) != r['size'] or linked != c.pe_bytes_at(target, int(r['address'], 16), r['size']):
            raise ValueError('Outer policy unmasked whole source comparison differs')
    GLOBAL.verify_control(dict(ctl, comparisons=[], alternatives=[]), body, target, c, coff, carrier, flow)
    definitions = {r['symbol']: r for r in coff.parse_symbols(body, c.coff_name)[1]}
    for r in ctl['alternatives'] + ctl['provider_alternatives']:
        d = definitions[r['symbol']]
        raw, fields, src = carrier.section_carrier(body, d['section'], c, coff)
        if (len(raw) != r['size'] or digest(raw) != r['source_sha256'] or fields != r['fields']
                or COMMON.SOURCE.BASE.canonical_source(src, body) != r['source']):
            raise ValueError('Outer policy erases a genuine whole alternative/provider difference')


def replay(plan, evidence_only=False):
    c = module('outer_target', 'compare-coff-function.py')
    coff = module('outer_coff', 'coff_data.py')
    carrier = module('outer_carrier', 'sdk_x3d_carriers.py')
    flow = module('outer_flow', 'sdk_image_carriers.py')
    target = c.verified_target()
    if digest(target) != plan['target_sha256']:
        raise ValueError('Outer policy target identity differs')
    for path, expected in plan['retained_sha256'].items():
        if digest((ROOT / path).read_bytes()) != expected:
            raise ValueError('Outer policy original retained input differs: ' + path)
    verify_canonical(plan, evidence_only)
    verify_native(plan, target, c, flow, evidence_only)
    scratch = ROOT / 'build/origin-outer-vector-policy-verification'
    scratch.mkdir(parents=True, exist_ok=True)
    for ctl in plan['controls']:
        with tempfile.TemporaryDirectory(dir=scratch) as temp:
            obj = Path(temp) / ctl['object_name']
            result = GLOBAL.run_checked([str(ROOT / 'scripts/compile-probe.sh'),
                str(ROOT / 'tests/origin_probes/OuterVectorPolicies.cpp'), str(obj), *ctl['profile']],
                'Outer policy fresh compiler failed; no cached fallback')
            if COMMON.included_headers(result.stdout + result.stderr) != ctl['headers']:
                raise ValueError('Outer policy complete actual header set differs')
            verify_control(ctl, obj.read_bytes(), target, c, coff, carrier, flow)
    print('R256 all60 unmasked comparisons, three whole source profiles, original native/game/EH '
          'and implicit alternatives passed; replaying entire unchanged R255.', flush=True)
    PREVIOUS.HISTORY.replay(plan['history'])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    plan = json.loads((ROOT / EVIDENCE).read_text())
    if digest((ROOT / EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('Outer policy immutable manifest differs')
    verify_plan(plan)
    replay(plan, args.evidence_only)
    print('R256: two inferred authored outer cleanup policies /144 bytes; complete game20/16 '
          'allocation, construction93/75, compiler deleting44, real EH code/data and source '
          'providers; genuine implicit/member/empty-base alternatives retained; entire unchanged '
          'R255 cold proof passes; no original private layout/ABI/source/mapping/exact credit.')


if __name__ == '__main__':
    main()
