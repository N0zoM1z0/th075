"""Guard full iterator/node/EH evidence and exact bounded historical transitions."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('archive_list_tests',ROOT/'scripts/verify-archive-list-policy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class ArchiveListPolicyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()

    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_complete_plan(self):V.verify_plan(self.m)
    def test_node_never_accepts_old_entry_prefix(self):self.reject(lambda m:m['functions'][6].update(size=134))
    def test_complete_shared_tail(self):self.reject(lambda m:m['functions'][6]['accepted_function'].update(span_end='0x0041EFE5'))
    def test_genuine_library_owner(self):self.reject(lambda m:m['functions'][0].update(decision='authored'))
    def test_no_source_presence(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_no_original_archive_layout(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='ArchiveEntryList::begin()'))
    def test_complete_root(self):self.reject(lambda m:m['controls'][0].update(size=41))
    def test_whole_catch_try_state(self):self.reject(lambda m:m['controls'][24].update(size=28))
    def test_real_catch_entry(self):self.reject(lambda m:next(b for b in m['controls'][24]['bindings'] if b['target_address']=='0x0041EFE6').update(target_address='0x0041EF60'))
    def test_whole_placement_cleanup_handler(self):self.reject(lambda m:m['controls'][12].update(size=17))
    def test_no_field_mask(self):self.reject(lambda m:m['controls'][10]['bindings'].pop())
    def test_no_substituted_source_field(self):self.reject(lambda m:m['controls'][10]['section']['fields'][0].update(offset=5))
    def test_whole_throw_metadata(self):self.reject(lambda m:m['controls'][22].update(size=12))
    def test_actual_throw_runtime(self):self.reject(lambda m:m['external'].__setitem__('__CxxThrowException@8','0x006407B8'))
    def test_whole_ordinary_size(self):self.reject(lambda m:m['controls'][79].update(size=16))
    def test_ordinary_stays_distinct(self):self.reject(lambda m:m['controls'][79]['source_definition'].update(symbol='SDKSize'))
    def test_full_prior_node_negative(self):self.reject(lambda m:m['negatives'][0].update(size=20))
    def test_full_actual_node_negative(self):self.reject(lambda m:m['negatives'][1].update(target_size=19))
    def test_real_negative_allocation_runtime(self):self.reject(lambda m:m['negatives'][1]['bindings'][0].update(target_address='0x00640F15'))
    def test_entire_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_all_actual_headers(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_original_probe_include(self):self.reject(lambda m:m['headers'].pop('probes/VC7ListIteratorPolicies.cpp'))
    def test_archive_width_is_independent(self):self.reject(lambda m:m['layout_values'].__setitem__(19,164))
    def test_original_full_archive_parent(self):self.reject(lambda m:m['anchors'][1].update(size=428))
    def test_independent_archive_owner(self):self.reject(lambda m:m['anchors'][0]['origin'].update(origin='library'))
    def test_all_registered_frames(self):self.reject(lambda m:m['retained_frames'].pop())
    def test_selected_slot_is_not_whole_vtable(self):self.reject(lambda m:m['selected_slot'].update(size=8))
    def test_short_link_getter_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041E100')['origin'].update(origin='library'))
    def test_node_getter_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041F7E0')['origin'].update(origin='library'))
    def test_interior_catch_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041EFE6')['origin'].update(origin='compiler'))
    def test_prior_destructor_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040D8E0')['origin'].update(origin='authored'))

    def test_exact_original_and_accepted_transition(self):
        r=self.m['functions'][3];old=dict(function=r['original_function'],origin=r['original_origin'])
        self.assertTrue(V.accepted_snapshot(old,r['accepted_function'],r['accepted_origin']))
        wrong=copy.deepcopy(r['accepted_function']);wrong['signature']='FalseOriginalType'
        self.assertFalse(V.accepted_snapshot(old,wrong,r['accepted_origin']))
        wrong_old=copy.deepcopy(old);wrong_old['function']['notes']='Replaced historical observation'
        self.assertFalse(V.accepted_snapshot(wrong_old,r['accepted_function'],r['accepted_origin']))

    def test_old_producer_only_allows_exact_new_bounded_acceptance(self):
        prior=V.module('iterator_old_producer_test','verify-vector-producer-origins.py')
        for a in ('0x0041D950','0x0041D9C0'):
            r=next(r for r in self.m['functions'] if r['address']==a);old=next(s for s in prior.manifest()['snapshots'] if s['address']==a)
            self.assertTrue(prior.preserved_snapshot(old,r['accepted_function'],r['accepted_origin']))
            wrong=dict(r['accepted_origin'],origin='compiler')
            self.assertFalse(prior.preserved_snapshot(old,r['accepted_function'],wrong))
        for a in ('0x0041D980','0x0041EF00'):
            r=next(r for r in self.m['functions'] if r['address']==a);old=next(s for s in prior.manifest()['functions'] if s['address']==a)
            prior.check_ledger(old,r['accepted_function'],r['accepted_origin'])
            wrong=dict(r['accepted_origin'],origin='compiler')
            with self.assertRaises(ValueError):prior.check_ledger(old,r['accepted_function'],wrong)
        old=next(s for s in prior.manifest()['snapshots'] if s['address']=='0x00411E80')
        self.assertFalse(prior.preserved_snapshot(old,old['function'],dict(old['origin'],origin='library')))

    def test_negative_checks_the_whole_actual_body(self):
        r=copy.deepcopy(self.m['negatives'][0]);raw=b'a'*23;actual=b'b'*20
        r['source_sha256']=V.digest(raw);r['body_sha256']=V.digest(actual)
        V.verify_negative(raw,raw,actual,r)
        with self.assertRaises(ValueError):V.verify_negative(raw[:20],raw[:20],actual,r)
        with self.assertRaises(ValueError):V.verify_negative(raw,raw,actual[:19],r)

    def test_unsigned_negative_preserves_genuine_width_difference(self):
        r=copy.deepcopy(self.m['negatives'][1]);raw=b'a'*20;actual=bytearray(raw);actual[8]=98
        r['source_sha256']=V.digest(raw);r['body_sha256']=V.digest(actual)
        V.verify_negative(raw,raw,bytes(actual),r)
        actual[8]=97;actual[9]=98;r['body_sha256']=V.digest(actual)
        with self.assertRaises(ValueError):V.verify_negative(raw,raw,bytes(actual),r)


if __name__=='__main__':unittest.main()
