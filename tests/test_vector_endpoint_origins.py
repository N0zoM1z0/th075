"""Protect whole endpoint/lifetime source evidence and genuine operation refinement."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('vector_endpoint_tests', ROOT/'scripts/verify-vector-endpoint-origins.py')
V = importlib.util.module_from_spec(spec); spec.loader.exec_module(V)


class VectorEndpointOrigins(unittest.TestCase):
    def setUp(self):
        self.m = V.manifest()

    def reject(self, mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):
            V.verify_plan(self.m)

    def test_complete_plan(self):
        V.verify_plan(self.m)

    def test_complete_endpoint(self):
        self.reject(lambda m: m['functions'][0].update(size=30))

    def test_whole_assign_parent(self):
        self.reject(lambda m: m['controls'][9].update(size=95))

    def test_whole_erase_source_context(self):
        self.reject(lambda m: m['controls'][21].update(size=98))

    def test_real_constructor_base(self):
        self.reject(lambda m: m['controls'][4]['bindings'][0].update(target_address='0x0040A5E0'))

    def test_constructor_source_identity(self):
        self.reject(lambda m: m['functions'][4].update(symbol=m['functions'][5]['symbol']))

    def test_actual_source_field(self):
        self.reject(lambda m: m['controls'][4]['section']['fields'][0]['symbol'].update(symbol='OrdinaryBase'))

    def test_no_field_masking(self):
        self.reject(lambda m: m['controls'][9]['bindings'].pop())

    def test_negative_offset_actual_operation(self):
        self.reject(lambda m: m['controls'][6]['bindings'][0].update(target_address='0x0040A190'))

    def test_subtraction_parent_uses_actual_subtraction_source(self):
        self.reject(lambda m: m['controls'][13]['source_definition'].update(symbol=m['negative_operation']['source_definition']['symbol']))

    def test_addition_alternative_is_whole(self):
        self.reject(lambda m: m['negative_operation'].update(size=56))

    def test_addition_alternative_has_real_addition_callee(self):
        self.reject(lambda m: m['negative_operation']['bindings'][0].update(target_address='0x0040A190'))

    def test_historical_addition_shaped_evidence_preserved(self):
        self.reject(lambda m: next(r for r in m['retained'] if r['address']=='0x00409DF0')['record'].update(coff_symbol=m['controls'][13]['source_definition']['symbol']))

    def test_historical_real_target_preserved(self):
        def mutation(m):
            row = next(r for r in m['retained'] if r['address']=='0x00409DF0')['record']
            row['relocation_bindings'] = row['relocation_bindings'].replace('0x0040A190','0x0040A5E0')
        self.reject(mutation)

    def test_parent_refinement_gives_no_new_origin(self):
        self.reject(lambda m: m['functions'][-1]['accepted_origin'].update(evidence_id='R161'))

    def test_whole_ordinary_endpoint(self):
        self.reject(lambda m: m['controls'][25].update(size=30))

    def test_distinct_ordinary_constructor(self):
        self.reject(lambda m: m['controls'][27]['source_definition'].update(symbol=m['controls'][4]['source_definition']['symbol']))

    def test_whole_ordinary_destruction(self):
        self.reject(lambda m: m['controls'][-1].update(size=14))

    def test_destroy_cannot_bypass_compiler_wrapper(self):
        self.reject(lambda m: m['controls'][7]['bindings'][0].update(target_address='0x004092F0'))

    def test_independent_compiler_wrapper(self):
        self.reject(lambda m: next(r for r in m['snapshots'] if r['address']=='0x0040A9F0')['origin'].update(origin='authored'))

    def test_independent_authored_policy(self):
        self.reject(lambda m: next(r for r in m['snapshots'] if r['address']=='0x004092F0')['origin'].update(origin='library'))

    def test_protected_r108_policy(self):
        self.reject(lambda m: next(r for r in m['snapshots'] if r['address']=='0x0040D8E0')['origin'].update(origin='authored'))

    def test_protected_record_copy(self):
        self.reject(lambda m: next(r for r in m['snapshots'] if r['address']=='0x004229D0')['origin'].update(origin='compiler'))

    def test_second_destroy_cannot_gain_origin(self):
        self.reject(lambda m: m['functions'][8]['accepted_origin'].update(origin='library'))

    def test_second_destroy_cannot_gain_name(self):
        self.reject(lambda m: m['functions'][8]['accepted_function'].update(proposed_name='RecoveredDestructor'))

    def test_full_emission(self):
        self.reject(lambda m: m['emission'].pop())

    def test_actual_sdk_headers(self):
        self.reject(lambda m: m['headers'].pop(next(k for k in m['headers'] if k.endswith('/deque'))))

    def test_full_observation_layout(self):
        self.reject(lambda m: m['layout_values'].pop())

    def test_no_source_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))

    def test_no_private_abi_credit(self):
        self.reject(lambda m: m['functions'][4]['accepted_function'].update(calling_convention='thiscall'))

    def test_no_exact_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_ten_exact_bounded_transitions(self):
        for row in self.m['functions']:
            self.assertTrue(V.accepted_snapshot(dict(function=row['original_function'],origin=row['original_origin']), row['accepted_function'], row['accepted_origin']))

    def test_unrelated_old_snapshot_rejected(self):
        row = self.m['functions'][0]; old = dict(function=copy.deepcopy(row['original_function']),origin=row['original_origin'])
        old['function']['notes'] += ' changed'
        self.assertFalse(V.accepted_snapshot(old,row['accepted_function'],row['accepted_origin']))

    def test_unrelated_new_snapshot_rejected(self):
        row = self.m['functions'][0]; changed = dict(row['accepted_function']); changed['size'] = '30'
        self.assertFalse(V.accepted_snapshot(dict(function=row['original_function'],origin=row['original_origin']),changed,row['accepted_origin']))

    def test_evidence_only_mode_grants_no_origin(self):
        row = self.m['functions'][0]
        V.check_ledger(row,row['original_function'],row['original_origin'],evidence_only=True)
        with self.assertRaises(ValueError):
            V.check_ledger(row,row['original_function'],row['original_origin'])


if __name__ == '__main__':
    unittest.main()
