"""Guard complete owner/entry extents, genuine EH fields and narrow transitions."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('list_construction_tests',ROOT/'scripts/verify-list-construction-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class ListConstructionOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_no_old_node_prefix_acceptance(self):self.reject(lambda m:m['functions'][2].update(size=143))
    def test_full_list_constructor(self):self.reject(lambda m:m['functions'][0].update(size=55))
    def test_full_list_base_constructor(self):self.reject(lambda m:m['functions'][1].update(size=52))
    def test_full_shared_catch_entry(self):self.reject(lambda m:m['functions'][3].update(size=53))
    def test_only_node_extent_changes(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(span_end='0x0041D928'))
    def test_original_node_size_is_frozen(self):self.reject(lambda m:m['functions'][2]['original_function'].update(size='223'))
    def test_node_new_extent_is_exact(self):self.reject(lambda m:m['functions'][2]['accepted_function'].update(size='222'))
    def test_node_end_is_exact(self):self.reject(lambda m:m['functions'][2]['accepted_function'].update(span_end='0x0041E27F'))
    def test_no_source_presence(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_abi(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_incomplete_owner_type(self):self.reject(lambda m:m['functions'][2]['accepted_function'].update(signature='OriginalOwner::node()'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][3]['accepted_function'].update(match_percent='100.00'))
    def test_no_authored_credit(self):self.reject(lambda m:m['functions'][2].update(accepted_authored_record={}))
    def test_no_fictitious_standalone_callback(self):self.reject(lambda m:m['functions'][3].update(source_owner='0x0041E22F'))
    def test_source_entry_is_local(self):self.reject(lambda m:m['functions'][3]['source_definition'].update(storage=2))
    def test_full_primary_owner_for_local_entry(self):self.reject(lambda m:m['shared_entry'].update(owner_size=143))
    def test_original_jump_site_retained(self):self.reject(lambda m:m['shared_entry'].update(original_jump_site='0x0041E22C'))
    def test_shared_exit_retained(self):self.reject(lambda m:m['shared_entry'].update(shared_exit='0x0041E263'))
    def test_source_entry_offset_retained(self):self.reject(lambda m:m['shared_entry'].update(offset=142))
    def test_source_entry_size_retained(self):self.reject(lambda m:m['shared_entry'].update(size=79))
    def test_source_entry_has_no_fake_primary_aux(self):self.reject(lambda m:m['shared_entry']['definition'].update(storage=2))
    def test_full_owner_cfg(self):self.reject(lambda m:m['controls'][2].update(cfg=[0,0]))
    def test_all_ordinary_sections(self):self.reject(lambda m:m['emission'].pop())
    def test_all_headers(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_entire_coalesced_layout(self):self.reject(lambda m:m['layout'].update(size=12))
    def test_full_authored_anchor(self):self.reject(lambda m:m['anchors'][1].update(size=130))
    def test_full_frame(self):self.reject(lambda m:m['frame'].update(try_count='0'))
    def test_full_eh_owner(self):self.reject(lambda m:m['frame'].update(handler_address='0x00655450'))
    def test_all_full_controls(self):self.reject(lambda m:m['controls'].pop(6))
    def test_all_real_fields(self):self.reject(lambda m:m['controls'][2]['bindings'].pop())
    def test_no_masked_field(self):self.reject(lambda m:m['controls'][2]['bindings'][0].update(type='MASKED'))
    def test_no_inert_field_addend(self):self.reject(lambda m:m['controls'][2]['bindings'][0].update(addend=1))
    def test_no_fake_empty_ctor_ownership(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041E330')['origin'].update(origin='library'))
    def test_keep_link_getter_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041E100')['origin'].update(origin='library'))
    def test_keep_noop_destruction_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041FDF0')['origin'].update(origin='library'))
    def test_empty_ctor_ordinary_alternative(self):self.reject(lambda m:m['controls'][-1].update(role='library-proof'))
    def test_whole_empty_ctor_alternative(self):self.reject(lambda m:m['controls'][-1].update(size=13))
    def test_complete_snapshot_inventory(self):self.reject(lambda m:m['snapshots'].pop())
    def test_only_exact_accepted_transitions(self):
        for r in self.m['functions']:
            snapshot=dict(function=r['original_function'],origin=r['original_origin'])
            self.assertTrue(V.accepted_snapshot(snapshot,r['accepted_function'],r['accepted_origin']))
            self.assertFalse(V.accepted_snapshot(snapshot,r['original_function'],r['original_origin']))
    def test_reject_wrong_original_snapshot(self):
        r=self.m['functions'][2];original=copy.deepcopy(r['original_function']);original['size']='142'
        self.assertFalse(V.accepted_snapshot(dict(function=original,origin=r['original_origin']),r['accepted_function'],r['accepted_origin']))
    def test_reject_wrong_accepted_extent(self):
        r=self.m['functions'][2];new=copy.deepcopy(r['accepted_function']);new['size']='224'
        self.assertFalse(V.accepted_snapshot(dict(function=r['original_function'],origin=r['original_origin']),new,r['accepted_origin']))
    def test_reject_wrong_accepted_provenance(self):
        r=self.m['functions'][0];new=dict(r['accepted_origin'],evidence_id='R020')
        self.assertFalse(V.accepted_snapshot(dict(function=r['original_function'],origin=r['original_origin']),r['accepted_function'],new))
    def test_prior_allows_only_new_original_to_accepted_pairs(self):
        p=V.module('list_prior_transition_tests','verify-indexed-owner-policy-origins.py')
        for r in self.m['functions']:
            snapshot=dict(function=r['original_function'],origin=r['original_origin'])
            self.assertEqual(p.accepted_pending_snapshot(snapshot,r['accepted_function'],r['accepted_origin']),r['address']!='0x0041E22F')
        original=next(r for r in self.m['snapshots'] if r['address']=='0x0041E330')
        self.assertFalse(p.accepted_pending_snapshot(dict(function=original['function'],origin=original['origin']),original['function'],original['origin']))

if __name__=='__main__':unittest.main()
