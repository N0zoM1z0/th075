"""Keep whole object geometry, duplicate source alternatives and literal origin guards."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('sdk_identifier_tests', ROOT / 'scripts/verify-sdk-identifier-contribution-origins.py')
V = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(V)


class SdkIdentifierContributionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan = json.loads((ROOT / V.EVIDENCE).read_text())

    def test_whole_proof_and_independent_inputs_are_immutable(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, sha in self.plan['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha)
        ctl = self.plan['control']
        self.assertEqual(V.digest((ROOT / ctl['source']).read_bytes()), ctl['source_sha256'])
        self.assertEqual(V.provider_catalog(self.plan), self.plan['providers'])

    def test_source_order_cannot_be_replaced_by_a_neighbor_match(self):
        bad = copy.deepcopy(self.plan)
        bad['units'][0]['code'].pop(0)
        with self.assertRaisesRegex(ValueError, 'whole original'):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan)
        bad['units'][0]['code'][5]['address'] = '0x00609B1E'
        with self.assertRaisesRegex(ValueError, 'source-order'):
            V.verify_context(bad)

    def test_reused_guid_and_displaced_wrapper_placements_are_preserved(self):
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['units'][1]['code'] if r['source']['section'] == 9)['address'] = '0x00609B1E'
        with self.assertRaisesRegex(ValueError, 'duplicate GUID'):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['units'][0]['code'] if r['source']['section'] == 10)['address'] = '0x00608D8B'
        with self.assertRaisesRegex(ValueError, 'displaced/reused'):
            V.verify_context(bad)
        matches = self.plan['survey']['matches']
        self.assertEqual(len(matches), 12)
        self.assertEqual(len({r['member_offset'] for r in matches}), 8)
        self.assertEqual({d['symbol'] for r in matches for d in r['source']['definitions'] if d['type'] == 32}, {'_IsEqualGUID', '_=='})

    def test_comdat_selection_and_cdecl_exit_are_actual_source_evidence(self):
        bad = copy.deepcopy(self.plan)
        r = next(r for r in bad['units'][0]['code'] if r['source']['section'] == 14)
        aux = next(a for a in r['source']['aux_records'] if a['symbol'] == '.text')
        value = bytearray.fromhex(aux['aux_hex']); value[14] = 1; aux['aux_hex'] = value.hex()
        with self.assertRaisesRegex(ValueError, 'COMDAT ANY'):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['units'][0]['code'] if r['source']['section'] == 14)['flow']['returns'][0]['cleanup'] = 8
        with self.assertRaisesRegex(ValueError, 'COMDAT ANY'):
            V.verify_context(bad)

    def test_ordinary_equality_and_lifetime_ambiguity_are_kept(self):
        bad = copy.deepcopy(self.plan)
        bad['control']['layout'][0] = 12
        with self.assertRaisesRegex(ValueError, 'ordinary storage'):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan)
        bad['protected_pairs'][0]['origin']['origin'] = 'library'
        with self.assertRaisesRegex(ValueError, 'private lifetimes'):
            V.verify_context(bad)

    def test_only_two_literal_pairs_may_transition(self):
        for r in self.plan['functions']:
            self.assertTrue(V.allows_transition(r['address'], r['original_function'], r['original_origin'], r['accepted_function'], r['accepted_origin']))
            self.assertFalse(V.allows_transition(r['address'], r['original_function'], r['original_origin'], dict(r['accepted_function'], notes='unapproved'), r['accepted_origin']))
        self.assertFalse(V.allows_transition('0x00608D8E', {}, {}, {}, {}))
        selected = {r['address']: r for r in self.plan['functions']}
        for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]:
            for original in [True, False]:
                state = 'original_' if original else 'accepted_'
                actual = [selected[r['address']][state + kind] if r['address'] in selected else r for r in V.rows(name)]
                V.historical_rows(self.plan, name, actual, original)
                with self.assertRaisesRegex(ValueError, 'literal selected pair'):
                    V.historical_rows(self.plan, name, actual + [selected[next(iter(selected))][state + kind]], original)

    def test_global_unselected_guard_remains_strict(self):
        selected = {r['address']: r for r in self.plan['functions']}
        source = {name: V.rows(name) for name in ['functions.csv', 'function-origins.csv']}
        absolute_spec = importlib.util.spec_from_file_location(
            'crt_absolute_successor_view', ROOT / 'scripts/verify-crt-absolute-contribution-origins.py')
        absolute = importlib.util.module_from_spec(absolute_spec)
        absolute_spec.loader.exec_module(absolute)
        absolute_plan = json.loads((ROOT / absolute.EVIDENCE).read_text())
        original_absolute = all(q['original_function'] in source['functions.csv'] for q in absolute_plan['functions'])
        source = {name: absolute.historical_rows(absolute_plan, name, actual, original_absolute)
                  for name, actual in source.items()}
        for original in [True, False]:
            state = 'original_' if original else 'accepted_'
            view = {name: [selected[r['address']][state + kind] if r['address'] in selected else r for r in source[name]] for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]}
            with patch.object(V, 'rows', side_effect=lambda name: view[name]):
                V.verify_canonical(self.plan, original)
            bad = copy.deepcopy(view)
            next(r for r in bad['functions.csv'] if r['address'] not in selected)['notes'] = 'unapproved'
            with patch.object(V, 'rows', side_effect=lambda name: bad[name]):
                with self.assertRaisesRegex(ValueError, 'unrelated canonical'):
                    V.verify_canonical(self.plan, original)


if __name__ == '__main__':
    unittest.main()
