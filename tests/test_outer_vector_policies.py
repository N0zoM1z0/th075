"""Reject origin gains from isolated lifetime fingerprints or substituted providers."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('outer_policy_tests', ROOT / 'scripts/verify-outer-vector-policy-origins.py')
V = importlib.util.module_from_spec(spec)
spec.loader.exec_module(V)


class OuterVectorPolicyTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan = json.loads((ROOT / V.EVIDENCE).read_text())

    def test_full_immutable_manifest_and_all_retained_inputs(self):
        V.verify_plan(self.plan)
        V.verify_context(self.plan)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, sha in self.plan['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_only_two_authored_origins_without_extent_layout_abi_or_exact_gain(self):
        self.assertEqual(sum(V.WHOLE.values()), 144)
        for r in self.plan['functions']:
            self.assertEqual(r['accepted_origin']['origin'], 'authored')
            old, new = r['original_function'], r['accepted_function']
            self.assertEqual([old[k] for k in ['current_name', 'size', 'span_end', 'status', 'owner']],
                             [new[k] for k in ['current_name', 'size', 'span_end', 'status', 'owner']])
            self.assertFalse(any(new[k] for k in ['source_file', 'signature', 'calling_convention']))
        bad = copy.deepcopy(self.plan)
        bad['functions'][0]['accepted_function']['source_file'] = 'invented-game-owner.cpp'
        with self.assertRaisesRegex(ValueError, 'immutable'):
            V.verify_plan(bad)

    def test_same_size_source_positive_does_not_replace_independent_game_allocation(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['native'] if r['address'] == '0x005F71F0')
        next(r for r in row['instructions'] if r['offset'] == 361)['operands'] = '0x14'
        with self.assertRaisesRegex(ValueError, 'game allocation'):
            V.verify_context(bad)

    def test_new_allocation_receiver_must_reach_the_actual_constructor(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['native'] if r['address'] == '0x00457660')
        next(r for r in row['instructions'] if r['offset'] == 527)['operands'] = 'ecx, dword ptr [ebp - 0x1f0]'
        with self.assertRaisesRegex(ValueError, 'different receiver'):
            V.verify_context(bad)

    def test_clear_precedes_same_receiver_base_destructor(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['native'] if r['address'] == '0x004586C0')
        next(r for r in row['instructions'] if r['offset'] == 50)['operands'] = 'ecx, dword ptr [ebp - 0x10] + 4'
        with self.assertRaisesRegex(ValueError, 'identical real receiver'):
            V.verify_context(bad)

    def test_state_transition_must_be_complete_before_base_destruction(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['native'] if r['address'] == '0x005F7ED0')
        next(r for r in row['instructions'] if r['offset'] == 43)['operands'] = 'dword ptr [ebp - 4], 0'
        with self.assertRaisesRegex(ValueError, 'destruction-state ordering'):
            V.verify_context(bad)

    def test_ordinary_cleanup_provider_cannot_be_substituted(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['controls'][0]['comparisons'] if r['role'] == 'whole-explicit-outer-destruction72')
        next(f for f in row['fields'] if f['offset'] == 39)['symbol_section'] = 0
        with self.assertRaisesRegex(ValueError, 'complete defining provider'):
            V.verify_context(bad)

    def test_isolated_member_constructor_byte_positive_retains_real22_provider(self):
        rows = [r for r in self.plan['controls'][0]['comparisons'] if r['role'] == 'implicit-member-parent-byte-positive']
        self.assertEqual(sorted(r['size'] for r in rows), [75, 93])
        bad = copy.deepcopy(self.plan)
        field = next(f for f in next(r for r in bad['controls'][0]['comparisons']
                     if r['role'] == 'implicit-member-parent-byte-positive')['fields'] if f['offset'] == 32)
        next(r for r in bad['controls'][0]['alternatives'] if r['symbol'] == field['symbol'])['size'] = 42
        with self.assertRaisesRegex(ValueError, 'false provider'):
            V.verify_context(bad)

    def test_default_single_destructor_is_whole19_not_a_cropped72(self):
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['controls'][0]['alternatives']
             if r['symbol'] == '??1?$ImplicitSingle@UValue16@@@@QAE@XZ')['size'] = 72
        with self.assertRaisesRegex(ValueError, 'single-base implicit'):
            V.verify_context(bad)

    def test_empty_after_keeps_whole98_and45_and_different_allocation_sizes(self):
        self.assertEqual(self.plan['controls'][0]['layouts'][0]['values'][:4], [16, 20, 20, 24])
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['controls'][0]['alternatives'] if r['symbol'] == '??1Implicit16@@QAE@XZ')['size'] = 72
        with self.assertRaisesRegex(ValueError, 'empty-base body'):
            V.verify_context(bad)

    def test_empty_first_genuine72_positive_keeps_opposite_actual_providers(self):
        positives = [r for r in self.plan['controls'][0]['comparisons']
                     if r['role'] == 'implicit-empty-first-destructor-byte-positive']
        self.assertEqual([r['size'] for r in positives], [72, 72])
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['controls'][0]['comparisons']
                   if r['role'] == 'implicit-empty-first-destructor-byte-positive')
        next(f for f in row['fields'] if f['offset'] == 54)['symbol'] = next(
            f for f in row['fields'] if f['offset'] == 39)['symbol']
        with self.assertRaisesRegex(ValueError, 'reversed-provider implicit72'):
            V.verify_context(bad)

    def test_empty_first_constructor_and_two_state_eh_cannot_be_truncated(self):
        for symbol, size in [('??0EmptyFirst16@@QAE@XZ', 75),
                             ('__ehhandler$??0EmptyFirst116@@QAE@XZ', 18)]:
            bad = copy.deepcopy(self.plan)
            next(r for r in bad['controls'][0]['alternatives'] if r['symbol'] == symbol)['size'] = size
            with self.assertRaisesRegex(ValueError, 'construction/EH differences'):
                V.verify_context(bad)

    def test_compiler_code18_data36_keep_actual_local_source_providers(self):
        for role, size in [('whole-compiler-base-cleanup-and-dispatch18', 8),
                           ('whole-compiler-unwind-and-function-info36', 28)]:
            bad = copy.deepcopy(self.plan)
            next(r for r in bad['controls'][0]['comparisons'] if r['role'] == role)['size'] = size
            with self.assertRaisesRegex(ValueError, 'crops compiler code/data'):
                V.verify_context(bad)

    def test_compiler_metadata_local_offset_cannot_be_substituted(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['controls'][0]['comparisons'] if r['role'] == 'whole-compiler-unwind-and-function-info36')
        row['fields'][0]['symbol_offset'] = 8
        with self.assertRaisesRegex(ValueError, 'local provider'):
            V.verify_context(bad)

    def test_element5_vs15_differences_remain_unclassified(self):
        bad = copy.deepcopy(self.plan)
        bad['controls'][0]['provider_alternatives'].pop()
        with self.assertRaisesRegex(ValueError, 'nontrivial element boundaries'):
            V.verify_context(bad)
        self.assertNotIn('0x0045B6B0', V.WHOLE)
        self.assertNotIn('0x005FAAD0', V.WHOLE)

    def test_three_complete_source_profiles_keep_one_body_and_full_inventories(self):
        self.assertEqual([r['profile'][:2] for r in self.plan['controls']],
                         [['/Od', '/Ob0'], ['/Od', '/Ob1'], ['/O1', '/Ob0']])
        self.assertEqual([len(r['emission']['initialized']) for r in self.plan['controls']], [197, 134, 166])
        self.assertEqual(self.plan['controls'][0]['emission']['bss'][0]['size'], 188)
        self.assertEqual(len(self.plan['controls'][0]['comparisons']), 60)

    def test_original_and_accepted_history_allows_only_two_literal_pairs(self):
        selected = {r['address']: r for r in self.plan['functions']}
        for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]:
            for evidence_only in [False, True]:
                state = 'original' if evidence_only else 'accepted'
                actual = [selected[r['address']][state + '_' + kind] if r['address'] in selected else r for r in V.rows(name)]
                old = V.historical_rows(self.plan, name, actual, evidence_only)
                self.assertEqual([r for r in old if r['address'] in selected],
                                 [selected[r['address']]['original_' + kind] for r in actual if r['address'] in selected])
                with self.assertRaisesRegex(ValueError, 'duplicates'):
                    V.historical_rows(self.plan, name, actual + [selected[next(iter(selected))][state + '_' + kind]], evidence_only)
                bad = copy.deepcopy(actual)
                next(r for r in bad if r['address'] in selected)['evidence' if kind == 'function' else 'evidence_id'] = 'unapproved'
                with self.assertRaisesRegex(ValueError, 'unsupported pair'):
                    V.historical_rows(self.plan, name, bad, evidence_only)

    def test_full_previous_canonical_view_keeps_unrelated_changes_rejected(self):
        old = json.loads((ROOT / V.PREVIOUS.EVIDENCE).read_text())
        selected = {r['address']: r for r in self.plan['functions']}
        source = {name: V.rows(name) for name in ['functions.csv', 'function-origins.csv']}
        contribution_spec = importlib.util.spec_from_file_location(
            'vendor_zeroing_successor_view', ROOT / 'scripts/verify-vendor-zeroing-contribution-origins.py')
        contribution = importlib.util.module_from_spec(contribution_spec)
        contribution_spec.loader.exec_module(contribution)
        contribution_plan = json.loads((ROOT / contribution.EVIDENCE).read_text())
        contribution.verify_plan(contribution_plan)
        original_contribution = all(q['original_function'] in source['functions.csv'] for q in contribution_plan['functions'])
        source = {name: contribution.historical_rows(contribution_plan, name, actual, original_contribution)
                  for name, actual in source.items()}
        deque_spec = importlib.util.spec_from_file_location(
            'deque_outer_successor_view', ROOT / 'scripts/verify-deque-outer-policy-origins.py')
        deque_view = importlib.util.module_from_spec(deque_spec)
        deque_spec.loader.exec_module(deque_view)
        newest_deque = json.loads((ROOT / deque_view.EVIDENCE).read_text())
        deque_view.verify_plan(newest_deque)
        original_deque = all(q['original_function'] in source['functions.csv'] for q in newest_deque['functions'])
        source = {name: deque_view.historical_rows(newest_deque, name, actual, original_deque)
                  for name, actual in source.items()}
        view = {name: V.historical_rows(self.plan, name, [selected[r['address']]['accepted_' + kind]
                    if r['address'] in selected else r for r in source[name]])
                for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]}
        with patch.object(V.PREVIOUS, 'rows', side_effect=lambda name: view[name]):
            V.PREVIOUS.verify_canonical(old)
        bad = copy.deepcopy(view)
        next(r for r in bad['functions.csv'] if r['address'] not in V.WHOLE)['notes'] = 'unapproved'
        with patch.object(V.PREVIOUS, 'rows', side_effect=lambda name: bad[name]):
            with self.assertRaisesRegex(ValueError, 'unrelated canonical'):
                V.PREVIOUS.verify_canonical(old)


if __name__ == '__main__':
    unittest.main()
