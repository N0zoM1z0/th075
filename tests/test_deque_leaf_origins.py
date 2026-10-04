"""Protect whole leaf evidence, ordinary ambiguity and independent provenance roles."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('leaf_tests', ROOT / 'scripts/verify-deque-leaf-origins.py')
V = importlib.util.module_from_spec(spec); spec.loader.exec_module(V)


class DequeLeafOrigins(unittest.TestCase):
    def setUp(self):
        self.m = V.manifest()

    def reject(self, mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):
            V.verify_plan(self.m)

    def test_complete_plan(self):
        V.verify_plan(self.m)

    def test_complete_leaf_extent(self):
        self.reject(lambda m: m['functions'][0].update(size=43))

    def test_whole_parent_shared_tail(self):
        self.reject(lambda m: m['controls'][8].update(size=1483))

    def test_destroy_cannot_bypass_compiler_wrapper(self):
        self.reject(lambda m: m['controls'][3]['bindings'][0].update(target_address='0x00421220'))

    def test_whole_placement_cleanup(self):
        self.reject(lambda m: m['controls'][12].update(size=17))

    def test_whole_placement_state_data(self):
        self.reject(lambda m: m['controls'][13].update(size=28))

    def test_no_field_masking(self):
        self.reject(lambda m: m['controls'][12]['bindings'].pop())

    def test_real_placement_delete_source(self):
        self.reject(lambda m: m['controls'][12]['section']['fields'][0]['symbol'].update(symbol='OrdinaryDelete'))

    def test_real_local_data_offset(self):
        self.reject(lambda m: m['controls'][12]['section']['fields'][1]['symbol'].update(offset=0))

    def test_negative_offset_operation(self):
        self.reject(lambda m: m['controls'][2]['bindings'][0].update(target_address='0x00421F40'))

    def test_whole_ordinary_noop(self):
        self.reject(lambda m: m['controls'][-1].update(size=4))

    def test_distinct_ordinary_destructor_control(self):
        self.reject(lambda m: m['controls'][-2]['source_definition'].update(symbol=m['controls'][3]['source_definition']['symbol']))

    def test_independent_compiler_wrapper(self):
        self.reject(lambda m: m['contexts'][6]['origin'].update(origin='authored'))

    def test_independent_authored_destructor(self):
        self.reject(lambda m: m['contexts'][10]['origin'].update(origin='library'))

    def test_protected_copy_ambiguity(self):
        self.reject(lambda m: m['protected'][0]['origin'].update(origin='compiler'))

    def test_complete_emission(self):
        self.reject(lambda m: m['emission'].pop())

    def test_actual_complete_observation_include(self):
        self.reject(lambda m: m['headers'].pop('probes/VC7PairedDequeProducers.cpp'))

    def test_complete_layout(self):
        self.reject(lambda m: m['layout_values'].pop())

    def test_no_source_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))

    def test_no_private_abi_credit(self):
        self.reject(lambda m: m['functions'][3]['accepted_function'].update(calling_convention='cdecl'))

    def test_no_exact_credit(self):
        self.reject(lambda m: m['functions'][4]['accepted_function'].update(match_percent='100.00'))

    def test_only_five_exact_transitions(self):
        for row in self.m['functions']:
            old = dict(function=row['original_function'], origin=row['original_origin'])
            self.assertTrue(V.accepted_snapshot(old, row['accepted_function'], row['accepted_origin']))
            self.assertTrue(V.PAIRED.preserved_snapshot(old, row['accepted_function'], row['accepted_origin']))

    def test_arbitrary_old_snapshot_rejected(self):
        row = self.m['functions'][0]; old = dict(function=copy.deepcopy(row['original_function']), origin=row['original_origin'])
        old['function']['notes'] += ' changed'
        self.assertFalse(V.accepted_snapshot(old, row['accepted_function'], row['accepted_origin']))

    def test_arbitrary_new_snapshot_rejected(self):
        row = self.m['functions'][0]; changed = dict(row['accepted_function']); changed['size'] = '43'
        self.assertFalse(V.accepted_snapshot(dict(function=row['original_function'], origin=row['original_origin']), changed, row['accepted_origin']))

    def test_evidence_only_does_not_accept_origin(self):
        row = self.m['functions'][0]
        V.check_ledger(row, row['original_function'], row['original_origin'], evidence_only=True)
        with self.assertRaises(ValueError):
            V.check_ledger(row, row['original_function'], row['original_origin'])


if __name__ == '__main__':
    unittest.main()
