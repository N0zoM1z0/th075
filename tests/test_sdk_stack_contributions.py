"""Distinguish whole stack-policy provenance from special-member source ambiguity."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('sdk_stack_tests', ROOT / 'scripts/verify-sdk-stack-contribution-origins.py')
V = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(V)


class SdkStackContributionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan = json.loads((ROOT / V.EVIDENCE).read_text())

    def test_whole_proof_and_original_evidence_are_immutable(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, sha in self.plan['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha)
        for ctl in self.plan['controls']:
            self.assertEqual(V.digest((ROOT / ctl['source']).read_bytes()), ctl['source_sha256'])

    def test_omitting_a_primary_section_cannot_turn_neighbor_proximity_into_provenance(self):
        bad = copy.deepcopy(self.plan)
        bad['code'].pop(0)
        with self.assertRaisesRegex(ValueError, 'whole primary'):
            V.verify_context(bad)

    def test_associated_compiler_code_keeps_both_actual_roots_and_all_data(self):
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['code'] if r['size'] == 20)['roots'] = [10]
        with self.assertRaisesRegex(ValueError, 'two-root'):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan)
        bad['data'][0]['size'] = 28
        with self.assertRaisesRegex(ValueError, 'data36'):
            V.verify_context(bad)

    def test_coherent_implicit_positive_must_keep_destructor_unknown(self):
        V.verify_context(self.plan)
        protected = {r['function']['address']: r for r in self.plan['protected_pairs']}
        self.assertEqual(protected['0x0061FB37']['origin']['origin'], 'unknown')
        self.assertEqual(protected['0x006200DA']['origin']['origin'], 'unknown')
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['protected_pairs'] if r['function']['address'] == '0x0061FB37')['origin']['origin'] = 'library'
        with self.assertRaisesRegex(ValueError, 'special-member'):
            V.verify_context(bad)
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['controls'][1]['comparisons'] if r['symbol'] == '??1ImplicitStackObservation@@QAE@XZ')['source_sha256'] = 'omitted'
        with self.assertRaisesRegex(ValueError, 'coherent explicit/implicit'):
            V.verify_context(bad)

    def test_non_inlined_implicit_bodies_cannot_be_cropped_or_discarded(self):
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['controls'][0]['alternatives'] if r['symbol'] == '??0ImplicitStackObservation@@QAE@XZ')['size'] = 16
        with self.assertRaisesRegex(ValueError, 'non-inlined'):
            V.verify_context(bad)
        self.assertEqual([sum(r['size'] for r in c['emission']) for c in self.plan['controls']], [196, 203])
        self.assertEqual([c['layout']['values'] for c in self.plan['controls']], [[4, 4, 16, 16, 16, 16, 12, 12]] * 2)

    def test_only_two_literal_non_special_member_transitions_are_allowed(self):
        for r in self.plan['functions']:
            self.assertTrue(V.allows_transition(r['address'], r['original_function'], r['original_origin'], r['accepted_function'], r['accepted_origin']))
            self.assertFalse(V.allows_transition(r['address'], r['original_function'], r['original_origin'], dict(r['accepted_function'], notes='unapproved'), r['accepted_origin']))
            self.assertFalse(any(r['accepted_function'][k] for k in ['source_file', 'calling_convention', 'signature']))
            self.assertTrue(r['accepted_origin']['confidence'].startswith('inferred-'))
        self.assertFalse(V.allows_transition('0x0061FB37', {}, {}, {}, {}))

    def test_literal_views_reject_duplicates_and_substitution(self):
        selected = {r['address']: r for r in self.plan['functions']}
        for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]:
            for original in [True, False]:
                state = 'original_' if original else 'accepted_'
                actual = [selected[r['address']][state + kind] if r['address'] in selected else r for r in V.rows(name)]
                old = V.historical_rows(self.plan, name, actual, original)
                self.assertTrue(all(q['original_' + kind] in old for q in selected.values()))
                with self.assertRaisesRegex(ValueError, 'literal getter pair'):
                    V.historical_rows(self.plan, name, actual + [selected[next(iter(selected))][state + kind]], original)

    def test_unrelated_rows_stay_protected_in_original_and_accepted_views(self):
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
        identifier_spec = importlib.util.spec_from_file_location(
            'sdk_identifier_successor_view', ROOT / 'scripts/verify-sdk-identifier-contribution-origins.py')
        identifier = importlib.util.module_from_spec(identifier_spec)
        identifier_spec.loader.exec_module(identifier)
        identifier_plan = json.loads((ROOT / identifier.EVIDENCE).read_text())
        original_identifier = all(q['original_function'] in source['functions.csv'] for q in identifier_plan['functions'])
        source = {name: identifier.historical_rows(identifier_plan, name, actual, original_identifier)
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
