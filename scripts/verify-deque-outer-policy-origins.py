#!/usr/bin/env python3
"""Cold-check coherent deque cleanup with whole implicit lifetime alternatives."""
import argparse
import importlib.util
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


PRIOR = module('deque_outer_prior', 'verify-outer-vector-policy-origins.py')
GLOBAL = PRIOR.GLOBAL
COMMON = PRIOR.COMMON
HISTORY = PRIOR.PREVIOUS.HISTORY
rows = COMMON.rows
digest = COMMON.digest
metadata_digest = COMMON.metadata_digest
EVIDENCE = 'config/deque-outer-policy-origin-evidence.json'
MANIFEST_SHA256 = '13d995130f18671b9463070aa66f089cbef6cccc248690e82c4a0f849eb15c20'
PLAN_DIGESTS = {'evidence_id': '38fce3e37827e35141e084f8db19ecc9fd5061c8271e6d5e66b84b6e63a107f7', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'baseline_commit': '09e6ecbc1e29ac2e54f63e2041db286ea089e0ace4470bb4b4c544d718d8cf3e', 'functions': '7549714f6223fcff4cc70a29687b8b891d915072669dd293738acad4fb5bba0e', 'authored_path': 'd16aaf5b02cdd980a7c2e82959c2f43b3bd4c20eb0b04a5c9f23f2b7dcca9fcf', 'authored': 'b046b5f80658df7f0f2b822653104b7982df1de2c2f0d6c7e33f4871c95684a5', 'native': '0db4ca9d0ec3480d3d88243b85a53a712f7c7cee314c1a0a4c1fb0704d26c6c7', 'canonical': '673ec61f42cf7bce0dbc5c3b9bc6daae3c01ca36d193a33f4202bec58d663f72', 'unselected_sha256': '998af1a9654562a174faca9e06c16d153667ed7e80dc9f02c3934ae3d0e11e72', 'context': '3d8b335666b46a1c82b70bbf5d55b24e1a2637fa9ece342e77a581537d2df1ed', 'controls': 'a3890f4cfccb1aa15bb69acb68f1270265317bff27ccfb0f8405eea7c7570f2e', 'history': '464fa4c8fadaf33b2d26c4ca81b267c29931bce32936996a26b84a3e6d84c93d', 'retained_sha256': '6b9a09eabc5ec92d027895a6108deb6618666cde1997fe61de2f0f87c5f22f92', 'interpretation': '75ffd8424d673d70272663d9703cfdf644a1a25f3e8738ebee54a9c666c69737'}
WHOLE = {'0x004212A0': 72}


def verify_plan(plan):
    if set(plan) != set(PLAN_DIGESTS):
        raise ValueError('Deque outer immutable schema differs')
    for key, value in PLAN_DIGESTS.items():
        if metadata_digest(plan[key]) != value:
            raise ValueError('Deque outer immutable evidence differs: ' + key)
    if plan['evidence_id'] != 'R257' or {r['address']: r['size'] for r in plan['functions']} != WHOLE:
        raise ValueError('Deque outer bounded scope differs')
    for r in plan['functions']:
        old, new = r['original_function'], r['accepted_function']
        mutable = {'proposed_name', 'module', 'evidence', 'notes'}
        if (r['original_origin']['origin'] != 'unknown'
                or r['accepted_origin']['origin'] != 'authored'
                or r['accepted_origin']['evidence_id'] != 'R257'
                or {k: v for k, v in old.items() if k not in mutable}
                != {k: v for k, v in new.items() if k not in mutable}
                or any(new[k] for k in ['signature', 'calling_convention', 'source_file', 'owner'])
                or new['match_percent'] != '0.00' or new['status'] != 'unclassified'):
            raise ValueError('Deque outer gains unsupported extent/layout/ABI/source/mapping/exact credit')


def historical_rows(plan, name, actual, evidence_only=False):
    """Restore only the literal independently validated R257 transition."""
    if name not in ['functions.csv', 'function-origins.csv']:
        return actual
    kind = 'function' if name == 'functions.csv' else 'origin'
    selected = plan['functions'][0]
    hits = [r for r in actual if r['address'] in WHOLE]
    expected = selected[('original_' if evidence_only else 'accepted_') + kind]
    if len(hits) != 1 or hits[0] != expected:
        raise ValueError('Deque outer historical view loses, duplicates or substitutes the literal pair')
    return [selected['original_' + kind] if r['address'] in WHOLE else r for r in actual]


def verify_canonical(plan, evidence_only=False):
    actual = {name: rows(name) for name in ['functions.csv', 'function-origins.csv']}
    for name, value in actual.items():
        historical_rows(plan, name, value, evidence_only)
        if metadata_digest([r for r in value if r['address'] not in WHOLE]) != plan['unselected_sha256'][name]:
            raise ValueError('Deque outer changes unrelated canonical rows')
    fs = {r['address']: r for r in actual['functions.csv']}
    os = {r['address']: r for r in actual['function-origins.csv']}
    for pair in plan['canonical']:
        a = pair['function']['address']
        expected = pair
        if a in WHOLE:
            r = plan['functions'][0]
            state = 'original' if evidence_only else 'accepted'
            expected = dict(function=r[state + '_function'], origin=r[state + '_origin'])
        if dict(function=fs[a], origin=os[a]) != expected:
            raise ValueError('Deque outer complete canonical pair differs: ' + a)
    if rows(Path(plan['authored_path']).name) != plan['authored']:
        raise ValueError('Deque outer complete authored evidence differs')


def verify_context(plan):
    control = plan['controls'][0]
    comparisons = {(r['symbol'], r['address']): r for r in control['comparisons']}
    alternatives = {r['symbol']: r for r in control['alternatives']}
    native = {r['address']: r for r in plan['native']}

    def provider(row, offset, address):
        field = next(f for f in row['fields'] if f['offset'] == offset)
        binding = next(b for b in row['bindings'] if b['offset'] == offset)
        result = comparisons.get((field['symbol'], address))
        if (binding['target'] != address or not result
                or field['symbol_section'] != result['definition']['section']
                or field['symbol_offset'] != result['definition']['offset']):
            raise ValueError('Deque outer replaces the actual complete defining provider')
        return result

    for owner in ['ExplicitMember', 'ExplicitBase']:
        ctor = comparisons[('??0' + owner + '@@QAE@XZ', '0x00421250')]
        outer = comparisons[('??1' + owner + '@@QAE@XZ', '0x004212A0')]
        base = provider(ctor, 32, '0x004212F0')
        clear = provider(ctor, 47, '0x004214C0')
        dtor = provider(outer, 54, '0x00421340')
        if (ctor['size'], outer['size'], base['size'], clear['size'], dtor['size']) != (75, 72, 72, 19, 19):
            raise ValueError('Deque outer crops the coherent whole lifetime cohort')
        if (not base['symbol'].startswith('??0?$deque@')
                or not clear['symbol'].startswith('?clear@?$deque@')
                or not dtor['symbol'].startswith('??1?$deque@')
                or provider(outer, 39, '0x004214C0') != clear):
            raise ValueError('Deque outer changes real constructor/clear/destructor source identity')
        for prefix, handler in [('??0', '0x006555D8'), ('??1', '0x006555F8')]:
            code = comparisons[('__ehhandler$' + prefix + owner + '@@QAE@XZ', f'0x{int(handler,16)-8:08X}')]
            if code['size'] != 18 or provider(code, 4, '0x00421340') != dtor:
                raise ValueError('Deque outer loses whole compiler cleanup18/provider')
            field = next(f for f in code['fields'] if f['type'] == 'DIR32')
            binding = next(b for b in code['bindings'] if b['offset'] == field['offset'])
            frame = next(b['frame'] for b in plan['context']['blocks'] if b['frame']['handler_address'] == handler)
            data = comparisons.get((field['symbol'], frame['unwind_address']))
            if (not data or data['size'] != 36 or binding['target'] != frame['funcinfo_address']
                    or field['symbol_section'] != data['definition']['section'] or field['symbol_offset'] != 8
                    or [f['symbol_offset'] for f in data['fields']] != [0, 0]
                    or data['fields'][0]['symbol_section'] != code['definition']['section']
                    or data['fields'][1]['symbol_section'] != data['definition']['section']):
                raise ValueError('Deque outer crops or substitutes actual local compiler metadata36')

    outer = {r['offset']: r for r in native['0x004212A0']['instructions']}
    for offset, pair in {28: ('mov', 'dword ptr [ebp - 4], 0'),
                         35: ('mov', 'ecx, dword ptr [ebp - 0x10]'),
                         38: ('call', '0x4214c0'),
                         43: ('mov', 'dword ptr [ebp - 4], 0xffffffff'),
                         50: ('mov', 'ecx, dword ptr [ebp - 0x10]'),
                         53: ('call', '0x421340')}.items():
        if (outer[offset]['mnemonic'], outer[offset]['operands']) != pair:
            raise ValueError('Deque outer loses same receiver or actual cleanup/state ordering')
    parser = {r['offset']: r for r in native['0x00420880']['instructions']}
    for offset, pair in {1096: ('lea', 'ecx, [ebp - 0x70]'), 1099: ('call', '0x421250'),
                         1104: ('mov', 'dword ptr [ebp - 4], 8'), 1111: ('lea', 'eax, [ebp - 0x70]'),
                         1114: ('push', 'eax'), 1124: ('call', '0x4215f0'),
                         1167: ('mov', 'dword ptr [ebp - 4], 0xffffffff'),
                         1174: ('lea', 'ecx, [ebp - 0x70]'), 1177: ('call', '0x4212a0')}.items():
        if (parser[offset]['mnemonic'], parser[offset]['operands']) != pair:
            raise ValueError('Deque outer loses independent same-local parser creation/use/destruction')
    block = next(b for b in plan['context']['blocks'] if b['frame']['handler_address'] == '0x006555B8')
    if len(block['callbacks']) != 9 or block['frame']['state_count'] != '9':
        raise ValueError('Deque outer crops the full original parser frame')
    last = block['callbacks'][-1]
    if (last['state_index'], last['destination'], last['kind']) != (8, '0x004212A0', 'local-object'):
        raise ValueError('Deque outer changes actual parser state8 cleanup identity')
    if [(r['mnemonic'], r['operands']) for r in last['instructions']] != [
            ('lea', 'ecx, [ebp - 0x70]'), ('jmp', '0x4212a0')]:
        raise ValueError('Deque outer changes original EH same-local receiver')

    for owner in ['ImplicitMember', 'ImplicitBase']:
        if (alternatives['??1' + owner + '@@QAE@XZ']['size'] != 19
                or comparisons[('??0' + owner + '@@QAE@XZ', '0x00421250')]['size'] != 75):
            raise ValueError('Deque outer erases whole genuine default19/parent75 alternatives')
    for owner, prefix in [('EmptyFirst', 'EmptyCleanup'), ('MemberEmptyFirst', 'EmptyMemberCleanup')]:
        isolated = comparisons[('??1' + owner + '@@QAE@XZ', '0x004212A0')]
        first, second = [next(f for f in isolated['fields'] if f['offset'] == i) for i in [39, 54]]
        second_symbol = '??1?$' + prefix + '@U' + owner + '@@@@QAE@XZ'
        if (isolated['size'] != 72 or not first['symbol'].startswith('??1?$deque@')
                or second['symbol'] != second_symbol or alternatives[second_symbol]['size'] != 19
                or alternatives[second_symbol]['fields'][0]['symbol'] != clear['symbol']):
            raise ValueError('Deque outer erases real reversed-provider implicit72 positives')
        if (alternatives['??0' + owner + '@@QAE@XZ']['size'] != 79
                or alternatives['__ehhandler$??0' + owner + '@@QAE@XZ']['size'] != 26):
            raise ValueError('Deque outer crops empty-first construction79/two-state EH26 differences')
        handler = alternatives['__ehhandler$??0' + owner + '@@QAE@XZ']
        info = next(f for f in handler['fields'] if f['type'] == 'DIR32')
        data = next(r for r in control['emission']['initialized'] if r['source']['section'] == info['symbol_section'])
        if (info['symbol_offset'] != 16 or data['source']['size'] != 44
                or [(f['offset'], f['symbol_offset']) for f in data['fields']] != [(4, 0), (12, 8), (24, 0)]):
            raise ValueError('Deque outer crops whole two-state source compiler metadata44')
        # The isolated72 positive would require its real clear19 provider to
        # define original Tidy177; retaining that whole mismatch prevents folding
        # unrelated definitions into a fabricated coherent implicit cohort.
        native_second = native['0x00421340']
        if (next(i for i in native_second['instructions'] if i['mnemonic'] == 'call')['operands'] != '0x4219c0'
                or native['0x004219C0']['size'] != 177 or clear['size'] != 19):
            raise ValueError('Deque outer loses real implicit-provider19 versus native177 boundary')
    if alternatives['??1EmptyAfter@@QAE@XZ']['size'] != 98:
        raise ValueError('Deque outer crops the whole empty-after98 alternative')
    negative = control['negative_comparisons']
    if len(negative) != 1 or (negative[0]['symbol'], negative[0]['size'], negative[0]['difference_count']) != (
            '??0EmptyAfter@@QAE@XZ', 75, 1):
        raise ValueError('Deque outer erases the complete negative construction-state comparison')
    externals = {(r['symbol'], r['address']): r for r in plan['context']['external']}
    for r in control['comparisons']:
        if r['role'] == 'implicit-empty-first72-byte-positive':
            continue
        for field, binding in zip(r['fields'], r['bindings']):
            if field['type'] != 'REL32' or field['symbol'] == '___CxxFrameHandler':
                continue
            key = (field['symbol'], binding['target'])
            if field['symbol_section'] > 0:
                defined = comparisons.get(key)
                if (not defined or defined['definition']['section'] != field['symbol_section']
                        or defined['definition']['offset'] != field['symbol_offset']):
                    raise ValueError('Deque outer loses complete recursive defining provider')
            elif key not in externals or externals[key]['definition']['section'] != 0:
                raise ValueError('Deque outer loses independent complete external owner protocol')
    if [c['profile'][:2] for c in plan['controls']] != [['/Od', '/Ob0'], ['/Od', '/Ob1'], ['/O1', '/Ob0']]:
        raise ValueError('Deque outer loses independent whole compiler profiles')
    if [c['layouts'][0]['values'] for c in plan['controls']] != [[8, 20, 20, 20, 20, 20, 24, 20]] * 3:
        raise ValueError('Deque outer changes ordinary observations into an original layout')


def verify_native(plan, target, c, flow):
    auth = module('deque_outer_authored', 'verify-authored-origins.py')
    eh = module('deque_outer_eh', 'compiler_eh.py')
    entries = {int(r['address'], 16) for r in rows('functions.csv')}
    for r in plan['native']:
        at = int(r['address'], 16)
        raw = c.pe_bytes_at(target, at, r['size'])
        cfg = list(auth.verify_body(raw, at, r['switches'], lambda a, n: c.pe_bytes_at(target, a, n), r['direct_switches']))
        if digest(raw) != r['body_sha256'] or COMMON.SOURCE.instructions(raw, at, flow) != r['instructions'] or cfg != r['cfg']:
            raise ValueError('Deque outer complete native body/CFG differs')
        if r['authored_record'] and r['authored_record'] not in rows('authored-origin-evidence.csv'):
            raise ValueError('Deque outer loses independently accepted authored context')
        for name, key in [('authored-origin-switches.csv', 'switches'), ('authored-origin-direct-switches.csv', 'direct_switches')]:
            if [v for v in rows(name) if v['address'] == r['address']] != r[key]:
                raise ValueError('Deque outer loses complete original switch records')
    for b in plan['context']['blocks']:
        frame = b['frame']
        if frame not in rows('compiler-eh-frames.csv'):
            raise ValueError('Deque outer original frame provenance differs')
        eh.verify_frame(frame, lambda a, n: c.pe_bytes_at(target, a, n), lambda a, n: c.pe_bytes_at(target, a, n), entries, set())
        at = int(b['address'], 16)
        raw = c.pe_bytes_at(target, at, b['size'])
        ins = COMMON.SOURCE.instructions(raw, at, flow)
        calls = {at + i['offset'] + i['size'] - 4: int(i['operands'], 16)
                 for i in ins if i['mnemonic'] in ['call', 'jmp'] and i['operands'].startswith('0x')}
        cfg = flow.flow(raw, at, b['roots'], [], calls, {int(frame['handler_address'], 16) + 1: int(frame['funcinfo_address'], 16)})
        if (digest(raw) != b['body_sha256'] or ins != b['instructions'] or cfg != b['cfg']
                or digest(c.pe_bytes_at(target, int(b['data_address'], 16), b['data_size'])) != b['data_sha256']):
            raise ValueError('Deque outer loses whole compiler code/data')
        for callback in b['callbacks']:
            raw = c.pe_bytes_at(target, int(callback['address'], 16), callback['size'])
            kind, destination = eh.cleanup_template(raw, int(callback['address'], 16), entries)
            if kind != callback['kind'] or destination != int(callback['destination'], 16):
                raise ValueError('Deque outer actual compiler cleanup provider differs')
    if (plan['context']['deleting_record'] not in rows('scalar-deleting-origin-evidence.csv')
            or any(r not in rows('compiler-origin-evidence.csv') for r in plan['context']['callback_records'])):
        raise ValueError('Deque outer independent compiler provenance differs')
    for r in plan['context']['alignment']:
        if c.pe_bytes_at(target, int(r['address'], 16), r['size']) != b'\xcc' * r['size']:
            raise ValueError('Deque outer consumes external alignment')
    verify_context(plan)


def verify_control(ctl, body, target, c, coff, carrier, flow):
    if GLOBAL.inventory(body, c, coff, carrier) != ctl['emission']:
        raise ValueError('Deque outer full ordinary emission/storage/AUX/fields differs')
    for r in ctl['comparisons'] + ctl['negative_comparisons']:
        raw, fields, src = carrier.section_carrier(body, r['section'], c, coff)
        if (r['definition'] not in src['definitions'] or fields != r['fields']
                or COMMON.SOURCE.BASE.canonical_source(src, body) != r['source'] or digest(raw) != r['source_sha256']):
            raise ValueError('Deque outer actual full defining carrier differs')
        linked, cfg = PRIOR.PREVIOUS.bind_whole(r, raw, fields, target, c, flow)
        observed = c.pe_bytes_at(target, int(r['address'], 16), r['size'])
        if cfg != r['linked_flow'] or len(linked) != r['size']:
            raise ValueError('Deque outer complete linked source flow differs')
        if sum(a != b for a, b in zip(linked, observed)) != r.get('difference_count', 0):
            raise ValueError('Deque outer unmasked whole source comparison differs')
    GLOBAL.verify_control(dict(ctl, comparisons=[], alternatives=[]), body, target, c, coff, carrier, flow)
    definitions = {r['symbol']: r for r in coff.parse_symbols(body, c.coff_name)[1]}
    for r in ctl['alternatives']:
        d = definitions[r['symbol']]
        raw, fields, src = carrier.section_carrier(body, d['section'], c, coff)
        if (d != r['definition'] or len(raw) != r['size'] or digest(raw) != r['source_sha256'] or fields != r['fields']
                or COMMON.SOURCE.BASE.canonical_source(src, body) != r['source']):
            raise ValueError('Deque outer erases a genuine complete alternative/provider difference')


def replay(plan, evidence_only=False):
    c = module('deque_outer_target', 'compare-coff-function.py')
    coff = module('deque_outer_coff', 'coff_data.py')
    carrier = module('deque_outer_carrier', 'sdk_x3d_carriers.py')
    flow = module('deque_outer_flow', 'sdk_image_carriers.py')
    target = c.verified_target()
    if digest(target) != plan['target_sha256']:
        raise ValueError('Deque outer target differs')
    verify_plan(plan)
    verify_canonical(plan, evidence_only)
    for path, sha in plan['retained_sha256'].items():
        if digest((ROOT / path).read_bytes()) != sha:
            raise ValueError('Deque outer retained source/provenance differs: ' + path)
    verify_native(plan, target, c, flow)
    for ctl in plan['controls']:
        command = [str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / ctl['probe']), str(ROOT / ctl['object']), *ctl['profile']]
        output = GLOBAL.run_checked(command, 'Deque outer fresh whole source profile')
        if COMMON.included_headers(output.stdout) != ctl['headers']:
            raise ValueError('Deque outer actual compiler/header identity differs')
        verify_control(ctl, (ROOT / ctl['object']).read_bytes(), target, c, coff, carrier, flow)
    print('R257 all34 unmasked positive comparisons and whole negative75, three full source profiles and original native/parser/EH pass; replaying entire original R212.', flush=True)
    HISTORY.replay(plan['history'])
    verify_canonical(plan, evidence_only)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    path = ROOT / EVIDENCE
    if digest(path.read_bytes()) != MANIFEST_SHA256:
        raise ValueError('Deque outer immutable manifest differs')
    replay(json.loads(path.read_text()), args.evidence_only)
    print('R257: one inferred authored deque outer cleanup72; whole paired construction75, independently accepted parser2301 same-local/state8 context, full vendor/element providers and original EH code/data; genuine default/member/empty-base alternatives retained; entire unchanged R212 and external R153 cold proofs pass; no original private layout/ABI/source/mapping/exact credit.')


if __name__ == '__main__':
    main()
