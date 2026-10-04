"""Guard full iterator/node/EH evidence and exact bounded historical transitions."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('iterator_tests',ROOT/'scripts/verify-list-iterator-policy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class ListIteratorPolicyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()

    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_complete_plan(self):V.verify_plan(self.m)
    def test_node_never_accepts_old_primary_prefix(self):self.reject(lambda m:m['functions'][12].update(size=137))
    def test_shared_tail_extent(self):self.reject(lambda m:m['functions'][12]['accepted_function'].update(span_end='0x004122C8'))
    def test_real_library_source(self):self.reject(lambda m:m['functions'][0].update(decision='authored'))
    def test_no_source_presence_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_no_original_private_abi(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='GameList::begin()'))
    def test_seven_whole_roots(self):self.reject(lambda m:m['controls'][6].update(size=41))
    def test_complete_catch_try_state(self):self.reject(lambda m:m['controls'][35].update(size=28))
    def test_real_catch_field(self):
        self.reject(lambda m:next(b for b in m['controls'][35]['bindings'] if b['target_address']=='0x004122C9').update(target_address='0x00412240'))
    def test_whole_cleanup_handler_carrier(self):self.reject(lambda m:m['controls'][23].update(size=17))
    def test_no_masked_field(self):self.reject(lambda m:m['controls'][18]['bindings'].pop())
    def test_no_substituted_source_field(self):self.reject(lambda m:m['controls'][18]['section']['fields'][0].update(offset=5))
    def test_whole_rtti_throw_data(self):self.reject(lambda m:m['controls'][32].update(size=12))
    def test_actual_exception_runtime(self):self.reject(lambda m:m['external'].__setitem__('__CxxThrowException@8','0x006407B8'))
    def test_ordinary_alternative_stays_distinct(self):self.reject(lambda m:m['controls'][90]['source_definition'].update(symbol='SDKSize'))
    def test_ordinary_arrow_real_child(self):self.reject(lambda m:m['controls'][91]['bindings'][0].update(target_address='0x00411E00'))
    def test_full_ordinary_postincrement(self):self.reject(lambda m:m['controls'][92].update(size=22))
    def test_entire_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_sdk_headers(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_full_original_probe_include(self):self.reject(lambda m:m['headers'].pop('probes/VC7ListPolicyDependencies.cpp'))
    def test_full_combined_layout(self):self.reject(lambda m:m['layout_values'].__setitem__(9,4))
    def test_full_original_game_parent(self):self.reject(lambda m:m['anchors'][1].update(size=745))
    def test_original_authored_parent_owner(self):self.reject(lambda m:m['anchors'][0]['origin'].update(origin='compiler'))
    def test_original_registered_frames(self):self.reject(lambda m:m['retained_frames'].pop())
    def test_selected_slot_is_not_whole_vtable(self):self.reject(lambda m:m['selected_slot'].update(size=8))
    def test_unknown_value_getter(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004124C0')['origin'].update(origin='library'))
    def test_unknown_node_getter(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004124B0')['origin'].update(origin='library'))
    def test_empty_child_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00412580')['origin'].update(origin='compiler'))
    def test_catch_interior_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004122C9')['origin'].update(origin='library'))
    def test_prior_pointer_accessor_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00411E80')['origin'].update(origin='library'))
    def test_prior_lifetime_ambiguity(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040D8E0')['origin'].update(origin='authored'))

    def test_exact_original_and_accepted_transition(self):
        r=self.m['functions'][4];old=dict(function=r['original_function'],origin=r['original_origin'])
        self.assertTrue(V.accepted_snapshot(old,r['accepted_function'],r['accepted_origin']))
        wrong=copy.deepcopy(r['accepted_function']);wrong['signature']='FalseOriginalType'
        self.assertFalse(V.accepted_snapshot(old,wrong,r['accepted_origin']))
        wrong_old=copy.deepcopy(old);wrong_old['function']['notes']='Replaced historical observation'
        self.assertFalse(V.accepted_snapshot(wrong_old,r['accepted_function'],r['accepted_origin']))

    def test_old_producer_only_allows_exact_new_bounded_acceptance(self):
        prior=V.module('iterator_old_producer_test','verify-vector-producer-origins.py')
        for a in ('0x00411C90','0x00411D30'):
            r=next(r for r in self.m['functions'] if r['address']==a);old=next(s for s in prior.manifest()['snapshots'] if s['address']==a)
            self.assertTrue(prior.preserved_snapshot(old,r['accepted_function'],r['accepted_origin']))
            wrong=dict(r['accepted_origin'],origin='compiler')
            self.assertFalse(prior.preserved_snapshot(old,r['accepted_function'],wrong))
        for a in ('0x00411CC0','0x004121C0'):
            r=next(r for r in self.m['functions'] if r['address']==a);old=next(s for s in prior.manifest()['functions'] if s['address']==a)
            prior.check_ledger(old,r['accepted_function'],r['accepted_origin'])
            wrong=dict(r['accepted_origin'],origin='compiler')
            with self.assertRaises(ValueError):prior.check_ledger(old,r['accepted_function'],wrong)
        old=next(s for s in prior.manifest()['snapshots'] if s['address']=='0x00411E80')
        self.assertFalse(prior.preserved_snapshot(old,old['function'],dict(old['origin'],origin='library')))


if __name__=='__main__':unittest.main()
