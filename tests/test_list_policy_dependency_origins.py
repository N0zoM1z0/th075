"""Protect complete list-node/EH extents and bounded historical transitions."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('list_dependency_tests',ROOT/'scripts/verify-list-policy-dependency-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class ListPolicyDependencyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()

    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_complete_plan(self):V.verify_plan(self.m)
    def test_node_cannot_accept_old_entry_prefix(self):self.reject(lambda m:m['functions'][4].update(size=143))
    def test_full_shared_tail_extent(self):self.reject(lambda m:m['functions'][4]['accepted_function'].update(span_end='0x0041206E'))
    def test_custom_wrapper_is_authored(self):self.reject(lambda m:m['functions'][0].update(decision='library'))
    def test_no_reconstruction_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(match_percent='100.00'))
    def test_no_original_private_abi(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(signature='list<GameValue>()'))
    def test_whole_node_defining_source(self):self.reject(lambda m:m['controls'][8].update(size=143))
    def test_entire_catch_data(self):self.reject(lambda m:m['controls'][23].update(size=28))
    def test_real_catch_entry(self):self.reject(lambda m:m['controls'][23]['bindings'][0].update(target_address='0x00411FE0'))
    def test_entire_try_table(self):self.reject(lambda m:m['controls'][23]['bindings'][1].update(target_address='0x006681B4'))
    def test_no_relocation_mask(self):self.reject(lambda m:m['controls'][8]['bindings'].pop())
    def test_no_fake_source_field(self):self.reject(lambda m:m['controls'][8]['section']['fields'][0].update(offset=5))
    def test_complete_eh_carrier(self):self.reject(lambda m:m['controls'][1].update(size=11))
    def test_entire_layout(self):self.reject(lambda m:m['layout_values'].__setitem__(9,4))
    def test_whole_actual_headers(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_original_probe_include(self):self.reject(lambda m:m['headers'].pop('probes/VC7GameContextPolicies.cpp'))
    def test_whole_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_original_independent_parent(self):self.reject(lambda m:m['parent']['origin'].update(origin='library'))
    def test_original_game_anchor(self):self.reject(lambda m:m['anchor'].update(size=1185))
    def test_full_registered_frame(self):self.reject(lambda m:m['retained_frames'][1].update(handler_address='0x0065501B'))
    def test_real_implicit_destructor_callee(self):self.reject(lambda m:m['negatives'][0]['bindings'][0].update(target_address='0x00411D60'))
    def test_unsigned_negative_uses_entire_own_extent(self):self.reject(lambda m:m['negatives'][1].update(size=19))
    def test_full_actual_node_allocation(self):self.reject(lambda m:m['negatives'][1].update(target_size=20))
    def test_interior_catch_receives_no_origin(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041206F')['origin'].update(origin='library'))
    def test_empty_destruction_child_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00412580')['origin'].update(origin='compiler'))
    def test_prior_pointer_accessor_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00411E80')['origin'].update(origin='library'))
    def test_old_destruction_ambiguity_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004229C0')['origin'].update(origin='authored'))

    def test_only_exact_historical_transition_is_permitted(self):
        r=self.m['functions'][4];old=dict(function=r['original_function'],origin=r['original_origin'])
        self.assertTrue(V.accepted_snapshot(old,r['accepted_function'],r['accepted_origin']))
        wrong=copy.deepcopy(r['accepted_function']);wrong['size']='143'
        self.assertFalse(V.accepted_snapshot(old,wrong,r['accepted_origin']))
        wrong_old=copy.deepcopy(old);wrong_old['function']['notes']='Unreviewed replacement'
        self.assertFalse(V.accepted_snapshot(wrong_old,r['accepted_function'],r['accepted_origin']))

    def test_prior_snapshot_callback_rejects_unrelated_owner(self):
        r=next(r for r in V.PRIOR.manifest()['snapshots'] if r['address']=='0x00411E80')
        wrong=dict(r['origin'],origin='library')
        self.assertFalse(V.PRIOR.preserved_snapshot(r,r['function'],wrong))

    def test_negative_never_compares_a_target_prefix(self):
        r=copy.deepcopy(self.m['negatives'][1]);raw=b'a'*20;actual=b'b'*23
        r['source_sha256']=V.digest(raw);r['body_sha256']=V.digest(actual)
        V.verify_negative(raw,raw,actual,r)
        with self.assertRaises(ValueError):V.verify_negative(raw,raw,actual[:20],r)
        with self.assertRaises(ValueError):V.verify_negative(raw[:19],raw[:19],actual,r)

    def test_lifetime_negative_preserves_actual_callee_difference(self):
        r=copy.deepcopy(self.m['negatives'][0]);raw=b'a'*22;actual=bytearray(raw);actual[14]=98;actual[15]=98
        r['source_sha256']=V.digest(raw);r['body_sha256']=V.digest(actual)
        V.verify_negative(raw,raw,bytes(actual),r)
        actual[14]=97;actual[13]=98;r['body_sha256']=V.digest(actual)
        with self.assertRaises(ValueError):V.verify_negative(raw,raw,bytes(actual),r)


if __name__=='__main__':unittest.main()
