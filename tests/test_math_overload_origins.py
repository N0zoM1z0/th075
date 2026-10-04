"""Prevent wrong source/ABI labels and false ownership from whole math alternatives."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('math_overload_tests',ROOT/'scripts/verify-math-overload-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class MathOverloadOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()

    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_complete_plan(self):V.verify_plan(self.m)

    def test_whole_wrapper(self):self.reject(lambda m:m['functions'][0].update(size=16))

    def test_whole_float_worker(self):self.reject(lambda m:m['controls'][1].update(size=27))

    def test_unknown_wrapper_cannot_gain_library_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_origin'].update(origin='library'))

    def test_unknown_worker_cannot_gain_authored_credit(self):
        self.reject(lambda m:m['functions'][5]['accepted_origin'].update(origin='authored'))

    def test_unknown_abs_worker_stays_unknown(self):
        self.reject(lambda m:m['functions'][-1]['accepted_origin'].update(origin='library'))

    def test_no_recovered_name(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(proposed_name='std::cos(float)'))

    def test_no_private_float_abi(self):
        self.reject(lambda m:m['functions'][5]['accepted_function'].update(signature='float cosf(float)'))

    def test_no_source_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))

    def test_no_exact_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_actual_float_worker_destination(self):
        self.reject(lambda m:m['controls'][1]['bindings'][0].update(target_address='0x00641804'))

    def test_c_stack_entry_is_not_x87_register_entry(self):
        self.reject(lambda m:m['controls'][1]['bindings'][0].update(target_address='0x00641740'))

    def test_full_independent_runtime_parent(self):
        self.reject(lambda m:m['runtime'][0].update(size=9))

    def test_existing_c_label_owner(self):
        self.reject(lambda m:next(r for r in m['retained'] if r['collection']=='interior_labels')['record'].update(parent='0x006417F0'))

    def test_existing_c_label_is_interior(self):
        self.reject(lambda m:next(r for r in m['retained'] if r['collection']=='interior_labels')['record'].update(source_offset=0))

    def test_full_ordinary_chain(self):
        self.reject(lambda m:m['controls'][12].update(size=27))

    def test_ordinary_control_is_distinct(self):
        self.reject(lambda m:m['controls'][11]['source_definition'].update(symbol=m['controls'][0]['source_definition']['symbol']))

    def test_no_call_masking(self):self.reject(lambda m:m['controls'][1]['bindings'].pop())

    def test_actual_field_offset(self):
        self.reject(lambda m:m['controls'][1]['section']['fields'][0].update(offset=8))

    def test_abs_and_labs_are_complete(self):
        self.reject(lambda m:m['abs_archive_alternatives'][0].update(size=10))

    def test_int_and_long_expressions_both_retained(self):
        self.reject(lambda m:m['abs_expression_control']['functions'].pop())

    def test_prior_abs_ambiguity_unchanged(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00641DAA')['origin'].update(origin='library'))

    def test_protected_lifetime(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040D8E0')['origin'].update(origin='authored'))

    def test_full_cold_emission(self):self.reject(lambda m:m['emission'].pop())

    def test_full_actual_headers(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))

    def test_complete_layout(self):self.reject(lambda m:m['layout_values'].__setitem__(1,4))

    def test_exact_bounded_evidence_transitions(self):
        for r in self.m['functions']:
            self.assertTrue(V.accepted_snapshot(dict(function=r['original_function'],origin=r['original_origin']),r['accepted_function'],r['accepted_origin']))

    def test_altered_old_row_is_not_an_accepted_transition(self):
        r=self.m['functions'][0];old=dict(function=copy.deepcopy(r['original_function']),origin=r['original_origin']);old['function']['notes']+=' changed'
        self.assertFalse(V.accepted_snapshot(old,r['accepted_function'],r['accepted_origin']))

    def test_evidence_only_is_not_a_canonical_update(self):
        r=self.m['functions'][0];V.check_ledger(r,r['original_function'],r['original_origin'],evidence_only=True)
        with self.assertRaises(ValueError):V.check_ledger(r,r['original_function'],r['original_origin'])


if __name__=='__main__':unittest.main()
