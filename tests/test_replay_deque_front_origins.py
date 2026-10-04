"""Guard whole front carriers and independent original game consumers."""
import importlib.util
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('front_tests',ROOT/'scripts/verify-replay-deque-front-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class ReplayDequeFrontOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_whole_front_extent(self):self.reject(lambda m:m['functions'][0].update(size=31))
    def test_genuine_sdk_owner(self):self.reject(lambda m:m['functions'][0].update(decision='authored'))
    def test_no_source_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_type_claim(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='ReplayOwner::front()'))
    def test_no_abi_change(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_actual_word_begin(self):self.reject(lambda m:m['controls'][39]['bindings'][0].update(target_address='0x004143D0'))
    def test_actual_dword_dereference(self):self.reject(lambda m:m['controls'][40]['bindings'][1].update(target_address='0x00414950'))
    def test_actual_specialization(self):self.reject(lambda m:m['functions'][0].update(symbol=m['functions'][1]['symbol']))
    def test_no_dropped_real_field(self):self.reject(lambda m:m['controls'][38]['bindings'].pop())
    def test_no_substituted_field(self):self.reject(lambda m:m['controls'][38]['section']['fields'][0].update(offset=18))
    def test_complete_ordinary_alternative(self):self.reject(lambda m:m['controls'][41].update(size=31))
    def test_ordinary_stays_distinct(self):self.reject(lambda m:m['controls'][41]['source_definition'].update(symbol=m['controls'][38]['source_definition']['symbol']))
    def test_ordinary_real_field(self):self.reject(lambda m:m['controls'][41]['bindings'][1].update(target_address='0x00414A00'))
    def test_previous_full_control_unchanged(self):self.reject(lambda m:m['controls'][0]['bindings'][0].update(target_address='0x004156B0'))
    def test_full_inventory(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_prior_include(self):self.reject(lambda m:m['headers'].pop('probes/VC7ReplayDequeIterators.cpp'))
    def test_full_layout(self):self.reject(lambda m:m['layout'].update(size=72))
    def test_independent_word_width(self):self.reject(lambda m:m['layout_values'].__setitem__(13,4))
    def test_whole_fighter_parent(self):self.reject(lambda m:m['anchors'][0].update(size=2814))
    def test_whole_random_parent(self):self.reject(lambda m:m['anchors'][1].update(size=138))
    def test_whole_battle_parent(self):self.reject(lambda m:m['anchors'][2].update(size=1957))
    def test_original_game_owner(self):self.reject(lambda m:m['anchors'][0]['origin'].update(origin='library'))
    def test_all_consumer_edges(self):self.reject(lambda m:m['parent_edges'].pop())
    def test_actual_consumer_load(self):self.reject(lambda m:m['consumer_observations'][0]['load'].update(operands='cl, dword ptr [eax]'))
    def test_independent_load_width(self):self.reject(lambda m:m['consumer_observations'][1].update(width=4))
    def test_full_prior_records(self):self.reject(lambda m:m['retained'].pop())
    def test_protected_getter_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00531D80')['origin'].update(origin='library'))
    def test_catch_interior_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00532196')['origin'].update(origin='compiler'))


if __name__=='__main__':unittest.main()
