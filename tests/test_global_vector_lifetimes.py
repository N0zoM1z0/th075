"""Reject ambiguous short-body shortcuts and incomplete global lifetime proofs."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('global_vector_lifetimes', ROOT / 'scripts/verify-global-vector-lifetime-origins.py')
V = importlib.util.module_from_spec(spec)
spec.loader.exec_module(V)


class GlobalVectorLifetimeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan = json.loads((ROOT / V.EVIDENCE).read_text())

    def test_whole_immutable_manifest_and_retained_source_inputs(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, value in self.plan['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), value, path)

    def test_only_two_library_origins_without_abi_source_extent_or_exact_credit(self):
        self.assertEqual({r['address']: r['size'] for r in self.plan['functions']}, V.WHOLE)
        for r in self.plan['functions']:
            old, new = r['original_function'], r['accepted_function']
            self.assertEqual(r['accepted_origin']['origin'], 'library')
            self.assertEqual([old[k] for k in ['size', 'span_end', 'current_name']],
                             [new[k] for k in ['size', 'span_end', 'current_name']])
            self.assertFalse(any(new[k] for k in ['signature', 'calling_convention', 'source_file']))
            self.assertEqual(new['match_percent'], '0.00')
        bad = copy.deepcopy(self.plan)
        bad['functions'][0]['accepted_function']['signature'] = 'invented original owner'
        with self.assertRaises(ValueError):
            V.verify_plan(bad)

    def test_paired_source_context_is_independent_of_a_short_cleanup_fingerprint(self):
        V.verify_context(self.plan)
        self.assertEqual(len(self.plan['context']['static_records']), 4)
        self.assertEqual({r['address'] for r in self.plan['native']},
                         {r['address'] for ctl in self.plan['controls'] for r in ctl['comparisons']}
                         | {'0x00640F15', '0x00642A61', '0x0064168B'})

    def test_missing_whole_constructor_cannot_bootstrap_from_library_callee(self):
        bad = copy.deepcopy(self.plan)
        bad['controls'][0]['comparisons'] = [r for r in bad['controls'][0]['comparisons']
                                            if r['role'] != 'original-R090-constructor42']
        with self.assertRaisesRegex(ValueError, 'unique whole source'):
            V.verify_context(bad)

    def test_mixed_global_construction_and_finalization_are_rejected(self):
        bad = copy.deepcopy(self.plan)
        end = next(r for r in bad['controls'][0]['comparisons'] if r['address'] == '0x00656E60')
        end['bindings'][0]['target'] = '0x00671358'
        with self.assertRaisesRegex(ValueError, 'same-global'):
            V.verify_context(bad)

    def test_actual_provider_substitution_cannot_make_outer_destructor_positive(self):
        bad = copy.deepcopy(self.plan)
        end = next(r for r in bad['controls'][0]['comparisons'] if r['address'] == '0x00656E60')
        end['fields'][1]['symbol'] = '??1ImplicitDerivedVector@@QAE@XZ'
        with self.assertRaisesRegex(ValueError, 'actual whole provider'):
            V.verify_context(bad)

    def test_ordinary_positive_cleanup_and_callback_keep_no_ownership_credit(self):
        ctl = self.plan['controls'][1]
        self.assertEqual([(r['size'], r['role']) for r in ctl['comparisons']],
                         [(19, 'ordinary-policy19-positive-no-ownership-credit'),
                          (15, 'ordinary-global-policy15-positive-no-ownership-credit')])
        ordinary = {r['symbol']: r for r in ctl['alternatives']}
        destructor = ordinary['??1ImplicitDerivedVector@@QAE@XZ']
        self.assertEqual(destructor['fields'][0]['symbol'], '??1?$vector@KV?$allocator@K@std@@@std@@QAE@XZ')
        self.assertEqual(ordinary['??1ExplicitTidyDerivedVector@@QAE@XZ']['size'], 72)
        bad = copy.deepcopy(self.plan)
        library = next(r for r in bad['controls'][0]['comparisons'] if r['role'] == 'vendor-destructor19')
        library['symbol'] = '?Cleanup@ExplicitTidyDerivedVector@@QAEXXZ'
        with self.assertRaises(ValueError):
            V.verify_context(bad)

    def test_four_profiles_keep_full_actual_outer_bodies_instead_of_cropping(self):
        inherited = self.plan['controls'][1:]
        self.assertEqual([r['profile'][:2] for r in inherited],
                         [['/Od', '/Ob0'], ['/Od', '/Ob1'], ['/O1', '/Ob0'], ['/O1', '/Ob1']])
        sizes = []
        for ctl in inherited:
            sources = {r['symbol']: r for r in ctl['alternatives']}
            sizes.append(tuple(sources[s]['size'] for s in [
                '??0ImplicitDerivedVector@@QAE@XZ', '??1ImplicitDerivedVector@@QAE@XZ',
                '??1ExplicitTidyDerivedVector@@QAE@XZ']))
        self.assertEqual(sizes, [(22, 19, 72), (26, 21, 74), (12, 5, 16), (14, 5, 16)])
        self.assertTrue(all(ctor != 42 for ctor, _, _ in sizes))

    def test_free113_preserves_its_original_interior_finally_without_new_credit(self):
        native = {r['address']: r for r in self.plan['native']}
        self.assertEqual(native['0x00642A61']['size'], 113)
        self.assertEqual(self.plan['context']['interior_labels'][0]['source_offset'], 83)
        self.assertNotIn('0x00642AB4', V.WHOLE)
        bad = copy.deepcopy(self.plan)
        bad['context']['interior_labels'] = []
        with self.assertRaisesRegex(ValueError, 'interior finally'):
            V.verify_context(bad)

    def test_original_and_accepted_views_allow_only_literal_selected_pairs(self):
        source = {name: V.rows(name) for name in ['functions.csv', 'function-origins.csv']}
        next_spec = importlib.util.spec_from_file_location(
            'global_neighbor_successor', ROOT / 'scripts/verify-neighbor-vector-lifetime-origins.py')
        next_view = importlib.util.module_from_spec(next_spec)
        next_spec.loader.exec_module(next_view)
        newest = json.loads((ROOT / next_view.EVIDENCE).read_text())
        next_view.verify_plan(newest)
        original_next = all(q['original_function'] in source['functions.csv'] for q in newest['functions'])
        source = {name: next_view.historical_rows(newest, name, actual, original_next)
                  for name, actual in source.items()}
        # R254 projects only its literal, independently verified three transitions.
        # Preserve the original R253 manifest and strict unrelated-row assertion.
        spec = importlib.util.spec_from_file_location(
            'global_vector_successor_view', ROOT / 'scripts/verify-member-vector-lifetime-origins.py')
        successor = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(successor)
        latest = json.loads((ROOT / successor.EVIDENCE).read_text())
        successor.verify_plan(latest)
        original = all(r in source['functions.csv'] for r in
                       [q['original_function'] for q in latest['functions']])
        source = {name: successor.historical_rows(latest, name, actual, original)
                  for name, actual in source.items()}
        selected = {r['address']: r for r in self.plan['functions']}
        for original in [True, False]:
            state = 'original' if original else 'accepted'
            view = {name: [selected[r['address']][state + '_' + ('function' if name == 'functions.csv' else 'origin')]
                           if r['address'] in selected else r for r in rows]
                    for name, rows in source.items()}
            with patch.object(V, 'rows', side_effect=lambda name: view[name]):
                V.verify_canonical(self.plan, original)
            bad = copy.deepcopy(view)
            next(r for r in bad['functions.csv'] if r['address'] not in selected)['notes'] = 'unapproved change'
            with patch.object(V, 'rows', side_effect=lambda name: bad[name]):
                with self.assertRaisesRegex(ValueError, 'unrelated canonical'):
                    V.verify_canonical(self.plan, original)

    def test_complete_bss_symbols_are_retained_as_storage_not_invented_target_mapping(self):
        for ctl in self.plan['controls']:
            storage = ctl['emission']['bss']
            self.assertEqual(len(storage), 1)
            count = 4 if ctl is self.plan['controls'][0] else 3
            self.assertEqual(storage[0]['size'], count * 16)
            globals_ = [d for d in storage[0]['definitions'] if d['storage'] == 2]
            self.assertEqual(sorted(d['offset'] for d in globals_), list(range(0, count * 16, 16)))
            self.assertNotIn('target_address', storage[0])
            self.assertEqual(len(ctl['emission']['weak_references']), 2)

    def test_every_selected_source_field_remains_present_and_unmasked(self):
        for ctl in self.plan['controls']:
            for r in ctl['comparisons']:
                self.assertEqual([f['offset'] for f in r['fields']], [b['offset'] for b in r['bindings']])
                self.assertTrue(all(f['addend'] == 0 for f in r['fields']))
        bad = copy.deepcopy(self.plan)
        bad['controls'][0]['comparisons'][0]['fields'].pop()
        with self.assertRaisesRegex(ValueError, 'immutable'):
            V.verify_plan(bad)


if __name__ == '__main__':
    unittest.main()
