"""Guard full retreat graphs and genuine addition/subtraction destinations."""
import importlib.util
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('deque_retreat_tests',ROOT/'scripts/verify-deque-retreat-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class DequeRetreatOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_whole_retreat(self):self.reject(lambda m:m['functions'][0].update(size=26))
    def test_library_owner(self):self.reject(lambda m:m['functions'][0].update(decision='authored'))
    def test_no_source_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_type(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='FalseOwner::retreat()'))
    def test_no_private_abi(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_actual_negated_argument(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x0041F65A').update(mnemonic='inc'))
    def test_complete_advance(self):self.reject(lambda m:m['controls'][1].update(size=30))
    def test_whole_subtraction_caller(self):self.reject(lambda m:m['controls'][2].update(size=56))
    def test_actual_retreat_call(self):self.reject(lambda m:m['controls'][0]['bindings'][0].update(target_address='0x0041ED00'))
    def test_actual_subtraction_child(self):self.reject(lambda m:m['controls'][2]['bindings'][0].update(target_address='0x0041F630'))
    def test_actual_addition_child(self):self.reject(lambda m:m['controls'][4]['bindings'][0].update(target_address='0x0041F650'))
    def test_no_dropped_field(self):self.reject(lambda m:m['controls'][0]['bindings'].pop())
    def test_no_masked_field(self):self.reject(lambda m:m['controls'][0]['section']['fields'][0].update(offset=18))
    def test_entire_ordinary_alternative(self):self.reject(lambda m:m['controls'][3].update(size=26))
    def test_ordinary_source_stays_distinct(self):self.reject(lambda m:m['controls'][3]['source_definition'].update(symbol=m['controls'][0]['source_definition']['symbol']))
    def test_complete_real_addition_negative(self):self.reject(lambda m:m['negatives'][0].update(size=56))
    def test_full_negative_target(self):self.reject(lambda m:m['negatives'][0].update(target_size=31))
    def test_real_negative_destination(self):self.reject(lambda m:m['negatives'][0]['bindings'][0].update(target_address='0x0041F650'))
    def test_all_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_headers(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_whole_readonly_layout(self):self.reject(lambda m:m['layout'].update(size=44))
    def test_distinct_width_observations(self):self.reject(lambda m:m['layout_values'].__setitem__(3,4))
    def test_original_whole_records(self):self.reject(lambda m:m['retained'].pop())
    def test_original_parent_owner(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041ED00')['origin'].update(origin='authored'))
    def test_prior_getter_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041E100')['origin'].update(origin='library'))
    def test_prior_destruction_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00532480')['origin'].update(origin='library'))


if __name__=='__main__':unittest.main()
