"""Reject false origin gains from clear aliases, missing states or partial EH carriers."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('member_vector_tests', ROOT / 'scripts/verify-member-vector-lifetime-origins.py')
V = importlib.util.module_from_spec(spec)
spec.loader.exec_module(V)


class MemberVectorLifetimeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan = json.loads((ROOT / V.EVIDENCE).read_text())

    def test_immutable_whole_manifest_and_inputs(self):
        V.verify_plan(self.plan)
        V.verify_context(self.plan)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, value in self.plan['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), value, path)

    def test_origin_transition_has_no_extent_abi_source_or_exact_gain(self):
        bad = copy.deepcopy(self.plan)
        bad['functions'][0]['accepted_function']['source_file'] = 'invented-owner.cpp'
        with self.assertRaisesRegex(ValueError, 'immutable'):
            V.verify_plan(bad)
        self.assertEqual(sum(V.WHOLE.values()), 57)
        self.assertEqual(self.plan['retained_unknown'], V.UNKNOWN)

    def test_missing_constructor_state_cannot_bootstrap_from_library_callee(self):
        bad = copy.deepcopy(self.plan)
        bad['context']['links'].pop()
        with self.assertRaisesRegex(ValueError, 'construction-state cohort'):
            V.verify_context(bad)

    def test_receiver_offset_changes_are_rejected(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['native'] if r['address'] == '0x0040AD80')
        next(i for i in row['instructions'] if i['offset'] == 61)['operands'] = 'ecx, 0x28'
        with self.assertRaisesRegex(ValueError, 'same receiver'):
            V.verify_context(bad)

    def test_state_must_be_stored_immediately_after_completed_construction(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['native'] if r['address'] == '0x0040AD80')
        next(i for i in row['instructions'] if i['offset'] == 69)['operands'] = 'byte ptr [ebp - 4], 1'
        with self.assertRaisesRegex(ValueError, 'completed construction state'):
            V.verify_context(bad)

    def test_real_unwind_entry_must_destroy_the_constructed_subobject(self):
        bad = copy.deepcopy(self.plan)
        next(r for b in bad['context']['blocks'] for r in b['callbacks'] if r['address'] == '0x00654EB3')['destination'] = '0x0040DF40'
        with self.assertRaisesRegex(ValueError, 'EH state/provider'):
            V.verify_context(bad)

    def test_compiler_source_callback_uses_actual_library_definition(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['control']['comparisons'] if r['role'] == 'whole-compiler-base-cleanup-and-dispatch18')
        row['fields'][0]['symbol'] = '?Cleanup@WordVectorPolicy@@QAEXXZ'
        with self.assertRaisesRegex(ValueError, 'full compiler code/data'):
            V.verify_context(bad)

    def test_full_handler_code_and_metadata_cannot_be_cropped_to_cleanup8(self):
        for role, size in [('whole-compiler-base-cleanup-and-dispatch18', 8),
                           ('whole-compiler-unwind-and-function-info36', 8)]:
            bad = copy.deepcopy(self.plan)
            next(r for r in bad['control']['comparisons'] if r['role'] == role)['size'] = size
            with self.assertRaisesRegex(ValueError, 'full compiler code/data'):
                V.verify_context(bad)

    def test_local_funcinfo_and_unwind_providers_cannot_be_substituted(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['control']['comparisons'] if r['role'] == 'whole-compiler-unwind-and-function-info36')
        row['fields'][0]['symbol_offset'] = 8
        with self.assertRaisesRegex(ValueError, 'actual local providers'):
            V.verify_context(bad)

    def test_ordinary_clear_positives_remain_unknown(self):
        ordinary = [r for r in self.plan['control']['comparisons'] if r['role'].startswith('ordinary-cleanup')]
        self.assertEqual([r['address'] for r in ordinary], V.UNKNOWN)
        self.assertTrue(all(r['size'] == 19 and r['symbol'].startswith('?Cleanup@') for r in ordinary))
        bad = copy.deepcopy(self.plan)
        bad['control']['comparisons'].remove(next(r for r in bad['control']['comparisons'] if r['role'].startswith('ordinary-cleanup')))
        with self.assertRaisesRegex(ValueError, 'counterexample'):
            V.verify_context(bad)

    def test_inherited_and_multi_member_owners_retain_actual_complete_differences(self):
        alternatives = {r['symbol']: r for r in self.plan['control']['alternatives']}
        self.assertEqual(alternatives['??0WordVectorPolicy@@QAE@XZ']['size'], 72)
        self.assertEqual(next(r for r in self.plan['native'] if r['address'] == '0x004071C0')['size'], 161)
        self.assertEqual(alternatives['__ehhandler$??0ThreeVectorObservation@@QAE@XZ']['size'], 40)
        self.assertEqual(self.plan['context']['blocks'][2]['size'], 62)
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['control']['alternatives'] if r['symbol'] == '__ehhandler$??0ThreeVectorObservation@@QAE@XZ')['size'] = 11
        with self.assertRaisesRegex(ValueError, 'crops or pads'):
            V.verify_context(bad)

    def test_element_boundary_preserves_r161_unknown_instead_of_claiming_full_identity(self):
        boundary = self.plan['control']['provider_alternatives'][0]
        self.assertEqual((boundary['size'], boundary['target_size']), (5, 15))
        self.assertNotIn(boundary['address'], V.WHOLE)
        self.assertFalse(any(r['address'] == boundary['address'] for r in self.plan['control']['comparisons']))
        original = json.loads((ROOT / 'config/vector-endpoint-origin-evidence.json').read_text())
        self.assertEqual(next(r for r in original['functions'] if r['address'] == boundary['address'])['decision'], 'unknown')

    def test_every_provider_field_keeps_its_actual_source_section(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['control']['comparisons'] if r['role'] == 'vendor-destructor19')
        row['fields'][0]['symbol_section'] = 0
        with self.assertRaisesRegex(ValueError, 'actual source provider'):
            V.verify_context(bad)

    def test_historical_view_accepts_only_literal_original_or_accepted_pairs(self):
        selected = {r['address']: r for r in self.plan['functions']}
        for evidence_only in [True, False]:
            state = 'original' if evidence_only else 'accepted'
            for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]:
                current = [selected[r['address']][state + '_' + kind] if r['address'] in selected else r
                           for r in V.rows(name)]
                historical = V.historical_rows(self.plan, name, current, evidence_only)
                self.assertEqual([r for r in historical if r['address'] in selected],
                                 [selected[r['address']]['original_' + kind] for r in current if r['address'] in selected])
                bad = copy.deepcopy(current)
                next(r for r in bad if r['address'] in selected)[
                    'evidence' if kind == 'function' else 'evidence_id'] = 'unsupported'
                with self.assertRaises(ValueError):
                    V.historical_rows(self.plan, name, bad, evidence_only)
                with self.assertRaisesRegex(ValueError, 'loses or duplicates'):
                    V.historical_rows(self.plan, name, current + [next(r for r in current if r['address'] in selected)], evidence_only)

    def test_retained_r253_view_still_rejects_unrelated_canonical_changes(self):
        old = json.loads((ROOT / V.GLOBAL.EVIDENCE).read_text())
        selected = {r['address']: r for r in self.plan['functions']}
        next_spec = importlib.util.spec_from_file_location(
            'member_neighbor_successor', ROOT / 'scripts/verify-neighbor-vector-lifetime-origins.py')
        next_view = importlib.util.module_from_spec(next_spec)
        next_spec.loader.exec_module(next_view)
        newest = json.loads((ROOT / next_view.EVIDENCE).read_text())
        next_view.verify_plan(newest)
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
        outer_spec = importlib.util.spec_from_file_location(
            'outer_successor_view', ROOT / 'scripts/verify-outer-vector-policy-origins.py')
        outer_view = importlib.util.module_from_spec(outer_spec)
        outer_spec.loader.exec_module(outer_view)
        newest_outer = json.loads((ROOT / outer_view.EVIDENCE).read_text())
        outer_view.verify_plan(newest_outer)
        original_outer = all(q['original_function'] in source['functions.csv'] for q in newest_outer['functions'])
        source = {name: outer_view.historical_rows(newest_outer, name, actual, original_outer)
                  for name, actual in source.items()}
        original_next = all(q['original_function'] in source['functions.csv'] for q in newest['functions'])
        source = {name: next_view.historical_rows(newest, name, actual, original_next)
                  for name, actual in source.items()}
        view = {name: V.historical_rows(self.plan, name, [selected[r['address']]['accepted_' + kind]
                    if r['address'] in selected else r for r in source[name]])
                for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]}
        with patch.object(V.GLOBAL, 'rows', side_effect=lambda name: view[name]):
            V.GLOBAL.verify_canonical(old)
        bad = copy.deepcopy(view)
        next(r for r in bad['functions.csv'] if r['address'] not in V.WHOLE)['notes'] = 'unapproved'
        with patch.object(V.GLOBAL, 'rows', side_effect=lambda name: bad[name]):
            with self.assertRaisesRegex(ValueError, 'unrelated canonical'):
                V.GLOBAL.verify_canonical(old)

    def test_r161_history_projects_only_validated_full_r208_successors(self):
        for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]:
            pairs = {r['address']: r for r in self.plan['context']['endpoint_successor_pairs']}
            actual = V.rows(name)
            historical = V.endpoint_historical_rows(self.plan, name, actual)
            for row in historical:
                if row['address'] in pairs:
                    self.assertEqual(row, pairs[row['address']]['original_' + kind])
                else:
                    self.assertIn(row, actual)
            bad = copy.deepcopy(actual)
            next(r for r in bad if r['address'] in pairs)[
                'notes' if kind == 'function' else 'evidence_id'] = 'unsupported'
            with self.assertRaisesRegex(ValueError, 'unapproved R208 state'):
                V.endpoint_historical_rows(self.plan, name, bad)
        self.assertEqual([(r['original_function']['size'], r['accepted_function']['size'])
                          for r in pairs.values()], [('777', '796'), ('777', '796')])


if __name__ == '__main__':
    unittest.main()
