"""Protect entire SDK parents, interior catch policy and pending record-copy ownership."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('copy_origin_tests', ROOT / 'scripts/verify-deque-copy-insert-origins.py')
V = importlib.util.module_from_spec(spec); spec.loader.exec_module(V)


class DequeCopyInsertOrigins(unittest.TestCase):
    def setUp(self):
        self.m = V.manifest()

    def reject(self, mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):
            V.verify_plan(self.m)

    def test_complete_plan(self):
        V.verify_plan(self.m)

    def test_copy_must_include_shared_normal_return(self):
        self.reject(lambda m: m['functions'][1]['accepted_function'].update(size='195', span_end='0x00422B12'))

    def test_insert_must_include_shared_normal_return(self):
        self.reject(lambda m: m['functions'][3]['accepted_function'].update(size='1483', span_end='0x0042333A'))

    def test_catch_does_not_become_standalone_source(self):
        self.reject(lambda m: m['functions'][2].update(owner_address='0x00422B13'))

    def test_catch_cannot_change_source_offset(self):
        self.reject(lambda m: m['functions'][4].update(source_offset=798))

    def test_interior_source_policy_is_not_compiler_dispatch(self):
        self.reject(lambda m: m['functions'][4]['accepted_origin'].update(origin='compiler'))

    def test_catch_is_not_accepted_from_name(self):
        self.reject(lambda m: m['catches'].pop())

    def test_real_frame_association(self):
        self.reject(lambda m: m['catches'][1].update(frame_handler='0x006556B0'))

    def test_real_catch_state(self):
        self.reject(lambda m: m['catches'][2].update(low=0))

    def test_catch_all_is_not_typed_catch(self):
        self.reject(lambda m: m['catches'][0].update(type_address='0x00660F20'))

    def test_full_original_registered_frame(self):
        self.reject(lambda m: m['frames'][1].update(state_count='3'))

    def test_full_try_handler_unwind_data(self):
        self.reject(lambda m: m['controls'][6].update(size=28))

    def test_full_sdk_parent_source(self):
        self.reject(lambda m: m['controls'][2].update(size=1483))

    def test_no_relocation_masking(self):
        self.reject(lambda m: m['controls'][2]['bindings'].pop())

    def test_actual_rollback_operation(self):
        self.reject(lambda m: m['controls'][2]['bindings'][-3].update(target_address='0x00423470'))

    def test_shared_return_cannot_be_omitted(self):
        self.reject(lambda m: m['shared_returns'].pop())

    def test_shared_return_destination(self):
        self.reject(lambda m: m['shared_returns'][1].update(target='0x004230BD'))

    def test_alignment_is_outside_parent(self):
        self.reject(lambda m: m['alignment'][0].update(address='0x00422B40'))

    def test_entire_emission(self):
        self.reject(lambda m: m['emission'].pop())

    def test_entire_layout(self):
        self.reject(lambda m: m['layout_values'].pop())

    def test_original_sdk_header(self):
        self.reject(lambda m: m['headers'].pop(next(k for k in m['headers'] if k.endswith('/deque'))))

    def test_actual_retained_observation_include(self):
        self.reject(lambda m: m['headers'].update({'probes/VC7PairedDequeProducers.cpp': '0' * 64}))

    def test_implicit_control_is_whole(self):
        self.reject(lambda m: m['controls'][0].update(size=27))

    def test_explicit_control_is_whole(self):
        self.reject(lambda m: m['controls'][7].update(size=27))

    def test_byte_equal_ambiguity_does_not_gain_owner(self):
        self.reject(lambda m: m['functions'][0]['accepted_origin'].update(origin='compiler'))

    def test_pending_wrapper_has_no_original_name(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(proposed_name='OriginalRecord::copy'))

    def test_false_source_credit(self):
        self.reject(lambda m: m['functions'][1]['accepted_function'].update(source_file='src/False.cpp'))

    def test_false_private_abi(self):
        self.reject(lambda m: m['functions'][1]['accepted_function'].update(signature='void copy()'))

    def test_false_exact_credit(self):
        self.reject(lambda m: m['functions'][1]['accepted_function'].update(match_percent='100.00'))

    def test_six_exact_transitions_only(self):
        for row in self.m['functions']:
            old = dict(function=row['original_function'], origin=row['original_origin'])
            self.assertTrue(V.accepted_snapshot(old, row['accepted_function'], row['accepted_origin']))
            self.assertTrue(V.PAIRED.preserved_snapshot(old, row['accepted_function'], row['accepted_origin']))

    def test_transition_preserves_unrelated_metadata(self):
        row = self.m['functions'][1]; f = dict(row['accepted_function']); f['current_name'] = 'invented'
        self.assertFalse(V.accepted_snapshot(dict(function=row['original_function'], origin=row['original_origin']), f, row['accepted_origin']))

    def test_transition_preserves_original_snapshot(self):
        row = self.m['functions'][1]; old = dict(function=copy.deepcopy(row['original_function']), origin=row['original_origin']); old['function']['size'] = '241'
        self.assertFalse(V.accepted_snapshot(old, row['accepted_function'], row['accepted_origin']))

    def test_no_unrelated_followup_permission(self):
        old = V.PAIRED.manifest()['contexts'][0]; f = dict(old['function']); f['notes'] += ' changed'
        self.assertFalse(V.accepted_snapshot(dict(function=old['function'], origin=old['origin']), f, old['origin']))

    def test_ledger_requires_exact_full_transition(self):
        row = self.m['functions'][1]
        V.check_ledger(row, row['original_function'], row['original_origin'], evidence_only=True)
        with self.assertRaises(ValueError):
            V.check_ledger(row, row['original_function'], row['original_origin'])


if __name__ == '__main__':
    unittest.main()
