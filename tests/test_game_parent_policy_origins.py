"""Guard complete game policy ownership, source controls and independent helpers."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('game_parent_tests',ROOT/'scripts/verify-game-parent-policy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class GameParentPolicyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()

    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_complete_plan(self):V.verify_plan(self.m)
    def test_whole_policy(self):self.reject(lambda m:m['functions'][0].update(size=103))
    def test_whole_virtual_policy(self):self.reject(lambda m:m['functions'][1].update(size=31))
    def test_virtual_policy_is_not_a_source_match(self):self.reject(lambda m:m['controls'][0].update(address='0x0045B760'))
    def test_no_library_credit_for_custom_policy(self):self.reject(lambda m:m['functions'][0]['accepted_origin'].update(origin='library'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_no_source_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_abi_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='GameOwner(unsigned)'))
    def test_complete_authored_extent_record(self):self.reject(lambda m:m['functions'][0]['accepted_authored_record'].update(size='31'))
    def test_complete_policy_instructions(self):self.reject(lambda m:m['functions'][1]['witnesses'].pop())
    def test_actual_sparse_default(self):self.reject(lambda m:m['functions'][1]['witnesses'][9].update(operands='word ptr [eax + 0x82], 1'))
    def test_whole_natural_array_policy(self):self.reject(lambda m:m['controls'][1].update(size=40))
    def test_real_array_constructor(self):self.reject(lambda m:m['controls'][1]['bindings'][4].update(target_address='0x00411C30'))
    def test_actual_deletion_runtime(self):self.reject(lambda m:m['controls'][2]['bindings'][2].update(target_address='0x006407B8'))
    def test_no_field_mask(self):self.reject(lambda m:m['controls'][2]['bindings'].pop())
    def test_real_source_field(self):self.reject(lambda m:m['controls'][0]['section']['fields'][0].update(offset=5))
    def test_whole_cleanup_handler_carrier(self):self.reject(lambda m:m['controls'][15].update(size=11))
    def test_whole_array_cleanup(self):self.reject(lambda m:m['controls'][17].update(size=22))
    def test_whole_state_data(self):self.reject(lambda m:m['controls'][16].update(size=28))
    def test_actual_frame(self):self.reject(lambda m:m['retained_frames'][0].update(handler_address='0x00655010'))
    def test_source_alias_stays_clear_alternative(self):self.reject(lambda m:m['controls'][9]['source_definition'].update(symbol='??1deque'))
    def test_implicit_negative_is_entire(self):self.reject(lambda m:m['negatives'][0].update(size=24))
    def test_implicit_array_negative_is_distinct(self):self.reject(lambda m:m['negatives'][1].update(role='candidate-natural-policy'))
    def test_implicit_virtual_negative_uses_actual_base(self):self.reject(lambda m:m['negatives'][2]['bindings'][0].update(target_address='0x00411C30'))
    def test_implicit_negative_has_one_whole_definition(self):
        self.reject(lambda m:m['negatives'][0]['section']['definitions'].append(dict(m['negatives'][0]['source_definition'],symbol='OtherFunction')))
    def test_implicit_negative_is_defining_code_comdat(self):self.reject(lambda m:m['negatives'][0]['section'].update(flags=0))
    def test_full_independent_parent(self):self.reject(lambda m:m['anchors'][0].update(size=1185))
    def test_original_parent_ownership(self):self.reject(lambda m:m['anchors'][0]['origin'].update(origin='library'))
    def test_actual_parent_call(self):self.reject(lambda m:m['anchors'][0].update(call_site='0x00456F97'))
    def test_both_whole_switch_tables(self):self.reject(lambda m:m['anchors'][3]['direct_switches'].pop())
    def test_whole_switch_extent(self):self.reject(lambda m:m['anchors'][3]['direct_switches'][0].update(table_size='40'))
    def test_list_constructor_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00411C30')['origin'].update(origin='library'))
    def test_base_constructor_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00458650')['origin'].update(origin='authored'))
    def test_existing_sdk_constructor_is_retained(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0045BEE0')['origin'].update(origin='unknown'))
    def test_opaque_virtual_slot_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0045B880')['origin'].update(origin='compiler'))
    def test_pending_destruction_child(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004229C0')['origin'].update(origin='library'))
    def test_one_slot_is_not_a_whole_vtable(self):self.reject(lambda m:m['selected_slot'].update(size=20))
    def test_whole_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_headers(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_observation_layout(self):self.reject(lambda m:m['layout_values'].__setitem__(5,76))

    def test_negative_checks_the_entire_actual_extent(self):
        row=copy.deepcopy(self.m['negatives'][0]);raw=b'a'*25;row['source_sha256']=V.digest(raw)
        V.verify_negative(raw,raw,b'b'*104,row)
        with self.assertRaises(ValueError):V.verify_negative(raw,raw,b'b'*25,row)

    def test_negative_cannot_use_a_source_prefix(self):
        row=copy.deepcopy(self.m['negatives'][0]);raw=b'a'*25;row['source_sha256']=V.digest(raw)
        with self.assertRaises(ValueError):V.verify_negative(raw[:-1],raw[:-1],b'b'*104,row)


if __name__=='__main__':unittest.main()
