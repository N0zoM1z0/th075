"""Keep complete auxiliary contribution evidence and strict unresolved alternatives."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('crt_absolute_tests', ROOT / 'scripts/verify-crt-absolute-contribution-origins.py')
V = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(V)


class CrtAbsoluteContributionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan = json.loads((ROOT / V.EVIDENCE).read_text())

    def test_original_complete_plan_and_inputs_are_immutable(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, sha in self.plan['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha)
        ctl = self.plan['control']
        self.assertEqual(V.digest((ROOT / ctl['source']).read_bytes()), ctl['source_sha256'])

    def test_isolated_abs11_cannot_replace_full_abs39_contribution(self):
        bad = copy.deepcopy(self.plan); bad['code'].pop()
        with self.assertRaisesRegex(ValueError, 'two-function contribution'):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan); bad['code'][1]['address'] = '0x00641DB6'
        with self.assertRaises(ValueError):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan); bad['code'][1]['size'] = 27
        with self.assertRaises(ValueError):
            V.verify_context(bad)

    def test_auxiliary28_cannot_gain_an_invented_candidate(self):
        bad = copy.deepcopy(self.plan); bad['code'][1]['function'] = {'address': '0x00641DB5'}
        with self.assertRaisesRegex(ValueError, 'invented canonical candidate'):
            V.verify_context(bad)
        self.assertIsNone(self.plan['code'][1]['function'])
        self.assertIsNone(self.plan['code'][1]['origin'])

    def test_real_comdat_and_entire_return_are_required(self):
        bad = copy.deepcopy(self.plan)
        aux = next(a for a in bad['code'][0]['source']['aux_records'] if a['symbol'] == '.text')
        value = bytearray.fromhex(aux['aux_hex']); value[14] = 2; aux['aux_hex'] = value.hex()
        with self.assertRaisesRegex(ValueError, 'COMDAT'):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan); bad['code'][1]['flow']['returns'][0]['cleanup'] = 8
        with self.assertRaisesRegex(ValueError, 'complete exit'):
            V.verify_context(bad)

    def test_complete_ordinary_negatives_and_separate_labs_stay_unresolved(self):
        bad = copy.deepcopy(self.plan); bad['control']['alternatives'][0]['whole_same_size_differences'] = 0
        with self.assertRaisesRegex(ValueError, 'wide28/public22 negatives'):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan); bad['control']['alternatives'][1]['size'] = 28
        with self.assertRaisesRegex(ValueError, 'wide28/public22 negatives'):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan); bad['protected_pairs'][0]['origin']['origin'] = 'library'
        with self.assertRaisesRegex(ValueError, 'labs/overload/lifetime'):
            V.verify_context(bad)
        self.assertEqual(self.plan['protected_pairs'][0]['function']['address'], '0x00641FB8')

    def test_whole_old_clis_keep_original_snapshots(self):
        self.assertEqual([r['evidence_id'] for r in self.plan['history']], ['R129', 'R163'])
        self.assertTrue(all(r['commit'] == self.plan['baseline_commit'] for r in self.plan['history']))
        bad = copy.deepcopy(self.plan); bad['history'].pop()
        with self.assertRaisesRegex(ValueError, 'drops its original proof'):
            V.verify_context(bad)
        self.assertEqual([r['scanned_coff_members'] for r in self.plan['survey']['archives']], [146, 678])
        self.assertEqual([len(r['matches']) for r in self.plan['survey']['archives']], [0, 2])

    def test_only_one_literal_pair_may_transition(self):
        r = self.plan['functions'][0]
        self.assertTrue(V.allows_transition(r['address'], r['original_function'], r['original_origin'], r['accepted_function'], r['accepted_origin']))
        self.assertFalse(V.allows_transition(r['address'], r['original_function'], r['original_origin'], dict(r['accepted_function'], notes='unapproved'), r['accepted_origin']))
        self.assertFalse(V.allows_transition('0x00641FB8', {}, {}, {}, {}))
        for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]:
            for original in [True, False]:
                state = 'original_' if original else 'accepted_'
                actual = [r[state + kind] if q['address'] == r['address'] else q for q in V.rows(name)]
                V.historical_rows(self.plan, name, actual, original)
                with self.assertRaisesRegex(ValueError, 'literal selected pair'):
                    V.historical_rows(self.plan, name, actual + [r[state + kind]], original)

    def test_unselected_global_guard_remains_strict(self):
        r = self.plan['functions'][0]
        for original in [True, False]:
            state = 'original_' if original else 'accepted_'
            view = {name: [r[state + kind] if q['address'] == r['address'] else q for q in V.rows(name)] for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]}
            with patch.object(V, 'rows', side_effect=lambda name: view[name]):
                V.verify_canonical(self.plan, original)
            bad = copy.deepcopy(view); next(q for q in bad['functions.csv'] if q['address'] != r['address'])['notes'] = 'unapproved'
            with patch.object(V, 'rows', side_effect=lambda name: bad[name]):
                with self.assertRaisesRegex(ValueError, 'unrelated canonical'):
                    V.verify_canonical(self.plan, original)


if __name__ == '__main__':
    unittest.main()
