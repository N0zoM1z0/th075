"""Guard full vector graphs, independent game context and precise historical transitions."""
import copy
import importlib.util
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('texture_vector_tests',ROOT/'scripts/verify-texture-vector-access-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class TextureVectorAccessOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_whole_index_extent(self):self.reject(lambda m:m['functions'][2].update(size=48))
    def test_whole_step_extent(self):self.reject(lambda m:m['functions'][6].update(size=31))
    def test_genuine_sdk_owner(self):self.reject(lambda m:m['functions'][0].update(decision='authored'))
    def test_no_source_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_type_claim(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='TextureOwner::begin()'))
    def test_no_private_abi_change(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_actual_begin_child(self):self.reject(lambda m:m['controls'][0]['bindings'][0].update(target_address='0x0040E990'))
    def test_actual_index_add(self):self.reject(lambda m:m['controls'][2]['bindings'][1].update(target_address='0x0040E4E0'))
    def test_no_dropped_real_field(self):self.reject(lambda m:m['controls'][2]['bindings'].pop())
    def test_no_substituted_source_field(self):self.reject(lambda m:m['controls'][2]['section']['fields'][0].update(offset=26))
    def test_full_size_context(self):self.reject(lambda m:m['controls'][4].update(size=56))
    def test_full_erase_context(self):self.reject(lambda m:m['controls'][5].update(size=98))
    def test_complete_ordinary_begin(self):self.reject(lambda m:m['controls'][22].update(size=30))
    def test_complete_ordinary_index(self):self.reject(lambda m:m['controls'][24].update(size=48))
    def test_ordinary_stays_distinct(self):self.reject(lambda m:m['controls'][24]['source_definition'].update(symbol=m['controls'][2]['source_definition']['symbol']))
    def test_actual_ordinary_field(self):self.reject(lambda m:m['controls'][24]['bindings'][1].update(target_address='0x0040E4E0'))
    def test_complete_compiler_source_kind(self):self.reject(lambda m:m['controls'][21].update(kind='code'))
    def test_compiler_owner_unchanged(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040FA00')['origin'].update(origin='library'))
    def test_actual_external_lifetime(self):self.reject(lambda m:m['external'].__setitem__('??1TextureAccessObservation@@QAE@XZ','0x0041A380'))
    def test_full_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_includes(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_whole_layout(self):self.reject(lambda m:m['layout'].update(size=20))
    def test_width_independent_of_prior_guess(self):self.reject(lambda m:m['layout_values'].__setitem__(0,16))
    def test_full_first_game_policy(self):self.reject(lambda m:m['anchors'][0].update(size=726))
    def test_full_second_game_policy(self):self.reject(lambda m:m['anchors'][1].update(size=574))
    def test_authored_parent_unchanged(self):self.reject(lambda m:m['anchors'][0]['origin'].update(origin='library'))
    def test_original_consumer_edges(self):self.reject(lambda m:m['parent_edges'].pop())
    def test_pointer_getter_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040E9B0')['origin'].update(origin='library'))
    def test_destroy_wrapper_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040F9F0')['origin'].update(origin='library'))
    def test_assignment_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040E000')['origin'].update(origin='library'))
    def test_full_original_records(self):self.reject(lambda m:m['retained'].pop())
    def test_exact_historical_transition(self):
        prior=V.module('texture_vector_old_producer','verify-vector-producer-origins.py')
        for a in ('0x0040DCE0','0x0040DD00','0x0040E4A0'):
            r=next(r for r in self.m['functions'] if r['address']==a);old=next(r for r in prior.manifest()['functions'] if r['address']==a)
            prior.check_ledger(old,r['accepted_function'],r['accepted_origin'])
            wrong=dict(r['accepted_origin'],origin='compiler')
            with self.assertRaises(ValueError):prior.check_ledger(old,r['accepted_function'],wrong)
            wrong_function=dict(r['accepted_function'],signature='FalseOriginalType')
            with self.assertRaises(ValueError):prior.check_ledger(old,wrong_function,r['accepted_origin'])
            old_snapshot=dict(function=r['original_function'],origin=r['original_origin']);wrong_old=copy.deepcopy(old_snapshot);wrong_old['function']['notes']='Replaced historical state'
            self.assertFalse(V.accepted_snapshot(wrong_old,r['accepted_function'],r['accepted_origin']))


if __name__=='__main__':unittest.main()
