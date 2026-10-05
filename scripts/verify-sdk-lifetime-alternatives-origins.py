#!/usr/bin/env python3
"""Replay a whole PNG destruction policy and complete SDK lifetime alternatives."""
import argparse
import importlib.util
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('lifetime_source', ROOT / 'scripts/verify-sdk-presentation-origins.py')
BASE = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(BASE)
module = BASE.module
digest = BASE.digest
bind_fields = BASE.bind_fields


def metadata_digest(value):
    return digest(json.dumps(value, sort_keys=True, separators=(',', ':')).encode())


def verify_plan(m):
    if m['evidence_id'] != 'R204' or len(m['functions']) != 1:
        raise ValueError('Lifetime alternatives lose bounded acceptance')
    for key, expected in PLAN_DIGESTS.items():
        if metadata_digest(m[key]) != expected:
            raise ValueError('Lifetime alternatives lose whole frozen provenance: ' + key)
    r = m['functions'][0]; old = r['original_function']; source = next(q for q in m['sections'] if q['base'] == r['address'])
    confidence = 'whole-original-sdk-png-pointer-destruction-policy-with-full-lifetime-alternatives-and-independent-source-fields'
    if (r['address'] != '0x006255C6' or r['size'] != 38 or r['code_size'] != 38
            or source['function'] != old or source['origin'] != r['original_origin']
            or r['original_origin']['origin'] != 'unknown' or old['size'] != '38'
            or old['status'] != 'unclassified' or old['match_percent'] != '0.00'
            or any(old[k] for k in ['source_file', 'owner', 'signature', 'calling_convention'])
            or r['symbol'] != source['symbol'] or not r['symbol'].startswith('?png_destroy_info_struct@')
            or r['accepted_function'] != dict(old, proposed_name=r['symbol'], module='D3DX8', status='excluded',
                                               owner='library', evidence='R204', notes=r['notes'])
            or r['accepted_origin'] != dict(address=r['address'], origin='library', subsystem='D3DX8',
                                           disposition='exclude', confidence=confidence, evidence_id='R204')):
        raise ValueError('Lifetime alternatives change extent or give unsupported lifetime/source/ABI/exact credit')
    if (len(m['sections']) != 17 or sum(q['size'] for q in m['sections']) != 762
            or sum(q['kind'] == 'code' for q in m['sections']) != 12
            or sum(len(q.get('fields', [])) for q in m['sections']) != 54
            or len(m['anchors']) != 17 or len(m['data_anchors']) != 2
            or len(m['weak_references']) != 3 or len(m['retained_unknown']) != 6
            or sum(q['size'] for q in m['retained_unknown']) != 484
            or m['interiors'] or m['imports'] or m['alias_anchors'] or m['foreign_guids']):
        raise ValueError('Lifetime alternatives omit source/EH/vtable/weak/unknown context')
    for q in m['retained_unknown']:
        if q['origin']['origin'] != 'unknown' or q['function']['owner'] or q['function']['source_file']:
            raise ValueError('Lifetime alternatives receive unsupported ownership credit')
    if {q['address']: q['decision'] for q in m['reviewed_cohort']} != COHORT:
        raise ValueError('Lifetime alternatives lose complete six-root decisions')
    refs = [dict(owner=q['base'], kind=q['kind'], field=b) for q in m['sections'] for b in q.get('bindings', [])
            if b['target_address'] == r['address'] and b['symbol_type'] == 32]
    if m['policy_references'] != {r['address']: refs}:
        raise ValueError('Lifetime alternatives invent incoming ownership references')


def check_public(body, emission, flow):
    code = {}
    for r in emission:
        defs = [d for d in r['definitions'] if d['type'] == 32]
        if not defs: continue
        if len(defs) != 1 or defs[0]['offset']:
            raise ValueError('Lifetime alternative contains a partial function')
        h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + (r['section'] - 1) * 40)
        raw = body[h[4]:h[4] + h[3]]
        flow.instructions(raw, 0, len(raw))
        code[defs[0]['symbol']] = (raw, r['fields'])
    sn = '?ProbePngDestroyInfo@@YAXPAUpng_struct_def@D3DX@@PAPAUpng_info_struct@2@@Z'
    raw, fields = code[sn]; ins = flow.instructions(raw, 0, len(raw))
    if (len(raw) != 5 or len(ins) != 1 or ins[0].mnemonic != 'jmp'
            or [(f['offset'], f['type'], f['symbol']['symbol']) for f in fields]
            != [(1, 'REL32', '?png_destroy_info_struct@D3DX@@YAXPAUpng_struct_def@1@PAPAUpng_info_struct@1@@Z')]):
        raise ValueError('Lifetime alternative opaque PNG interface/tail lowering differs')
    for pair in PAIRS:
        a, af = code[pair['explicit']]; b, bf = code[pair['implicit']]
        if (a != b or len(a) != pair['size'] or len(af) != 1 or len(bf) != 1
                or [{k: f[k] for k in ['offset', 'type', 'addend']} for f in af]
                != [{k: f[k] for k in ['offset', 'type', 'addend']} for f in bf]
                or [af[0]['symbol']['symbol'], bf[0]['symbol']['symbol']] != pair['field_symbols']):
            raise ValueError('Lifetime complete explicit/implicit alternative differs')
    if len(code) != 24:
        raise ValueError('Lifetime alternatives omit ordinary emitted functions')


def main():
    p = argparse.ArgumentParser(description=__doc__); p.add_argument('--evidence-only', action='store_true'); args = p.parse_args()
    m = json.loads((ROOT / EVIDENCE).read_text()); verify_plan(m)
    for path, sha in [(EVIDENCE, MANIFEST_SHA256), (m['public_control']['probe'], m['public_control']['probe_sha256']),
                      *m['retained_sha256'].items()]:
        if digest((ROOT / path).read_bytes()) != sha:
            raise ValueError('Lifetime immutable evidence/source/prior provenance differs: ' + path)
    BASE.replay(m, args.evidence_only)
    c = module('lifetime_coff', 'compare-coff-function.py'); coff = module('lifetime_data', 'coff_data.py')
    flow = module('lifetime_flow', 'sdk_image_carriers.py')
    module('lifetime_cold', 'verify-sdk-blit-origins.py').cold_control(m['public_control'], 'LifetimeAlternatives', check_public, c, coff, flow)
    print('R204 origins OK:one whole original PNG destruction policy38; six reviewed roots503; '
          '17 complete source sections762/all54 fields,12 full CFGs;17 whole anchors3098/70 fields, '
          'two retained owner vtables88 and three actual weak fallbacks; six lifetime alternatives484 remain unknown; '
          '27 cold ordinary sections470,24 complete functions430,eight original headers and readonly generic layout32; '
          'three complete explicit/implicit source pairs retain ambiguity; no private owner/layout/source/ABI/mapping/exact credit.')
    return 0


EVIDENCE = 'config/sdk-lifetime-alternatives-origin-evidence.json'
MANIFEST_SHA256 = '551ee19c54232b82c06f5c261470dd1b0dc22069a895026c2e108aa2b68b0162'
COHORT = {'0x00609F58': 'unknown', '0x0060B728': 'unknown', '0x0061572C': 'unknown',
          '0x0061A453': 'unknown', '0x0060EBCD': 'unknown', '0x006255C6': 'library'}
PLAN_DIGESTS = {'sections': 'd40f5117fc70ae943cfebd1efcde9153ce902c97d98f8ee63b3c5a1495892182', 'anchors': 'e18445d2d7be08364ae5ff891c9c32a7aefd1b55ceec69c1338b2c5ddece7b5f', 'data_anchors': 'c29973710ad7638c28c884aacafa6b72c181f456c86ce40bc290e52e6f6798d1', 'foreign_guids': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'alias_anchors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'interiors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_unknown': '185ecb9bb75475635679f39bf1ff946bf3a20353650dde3815979ec4ded27f7d', 'policy_references': '39e6e0c728aca1ee392ede6ec8a97f280982d8de5a80a19c0246bb4619bf41ad', 'public_control': '6f492cf24463359fa5dba8a4ece6a29566a95379ec642b199bd73aca7b28e01c', 'absolute': '8e1f56739e02ad0900ff6fe1a81eecb7cfcf9597595512608c6e532445948d11', 'imports': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'weak_references': '52f01f5d4a597ba876ecbd03ccf585d4c2e4ca166bfb0ff3268153c76171e032', 'probe': '16bfe14069eae6a811520523832b62b9df45d057f24e8d0a9f5414b451672a16', 'profile': 'edbcdcf806e9869ccdd785e3c9e574a3734df2e10de3d8a70a694bb4a8e89307', 'headers': 'ea6cb00e0cd7986b212b6e6e1f220319d96b8ff32cb7c1faf5b4a474af61e00a', 'emission': '1a290b8f556201c105733da741889e1e6b6b8aed3422669eae6f858257cfcd92', 'layout': 'd0abe3567d07fd00f58b5b48314d56d6c8af186ae636c674dd8f7a2f1162427a', 'retained_sha256': '6e9bfe8bbe91905323bfdc812983bfd89f9bbbc74c1375fa2891f88be86ea9cb', 'game_parents': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'uuid_archive_sha256': '89cf9b03328ef4655c6df7206142964a22d95e8e823ad689d3d2e7ab792ad31b', 'reviewed_cohort': '329ae3f22b990a797c164508bdc0ceb3e2fe3747dcece5b84c4762db2f6405fc', 'alternative_pairs': '985e44b60cd9e385b2907bd17d38f2986064a3d6718081d8eb7deaefe1ed1781'}
PAIRS = [{'explicit': '??0ExplicitInitOwner@@QAE@XZ', 'implicit': '??0ImplicitInitOwner@@QAE@XZ', 'size': 23, 'field_symbols': ['??_7ExplicitInitOwner@@6B@', '??_7ImplicitInitOwner@@6B@'], 'same_complete_bytes': True}, {'explicit': '??1ExplicitCleanupOwner@@QAE@XZ', 'implicit': '??1ImplicitCleanupOwner@@QAE@XZ', 'size': 10, 'field_symbols': ['??3@YAXPAX@Z', '??3@YAXPAX@Z'], 'same_complete_bytes': True}, {'explicit': '??1ExplicitConditionalOwner@@QAE@XZ', 'implicit': '??1ImplicitConditionalOwner@@QAE@XZ', 'size': 21, 'field_symbols': ['??3@YAXPAX@Z', '??3@YAXPAX@Z'], 'same_complete_bytes': True}]

if __name__ == '__main__': raise SystemExit(main())
