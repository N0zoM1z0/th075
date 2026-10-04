"""Guard complete SDK dependency evidence and truthful ordinary alternatives."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('sdk_dependency_tests',ROOT/'scripts/verify-sdk-dependency-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class SDKDependencyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()

    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_complete_plan(self):V.verify_plan(self.m)

    def test_whole_candidate(self):self.reject(lambda m:m['functions'][1].update(size=150))

    def test_complete_parent(self):self.reject(lambda m:m['controls'][6].update(size=176))

    def test_actual_copy_assignment(self):
        self.reject(lambda m:m['controls'][3]['bindings'][0].update(target_address='0x004591E0'))

    def test_actual_copy_constructor(self):
        self.reject(lambda m:m['controls'][4]['bindings'][4].update(target_address='0x0045AAE0'))

    def test_no_source_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))

    def test_no_private_abi(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='unsigned max_size()'))

    def test_no_exact_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_no_compiler_credit_for_sdk_body(self):
        self.reject(lambda m:m['functions'][0]['accepted_origin'].update(origin='compiler'))

    def test_real_sdk_source(self):
        self.reject(lambda m:m['controls'][0]['source_definition'].update(symbol='OrdinaryCapacity'))

    def test_entire_ordinary_pop(self):self.reject(lambda m:m['controls'][33].update(size=150))

    def test_negative_ordinary_pop_is_not_byte_equal(self):
        self.reject(lambda m:m['controls'][33].update(role='byte-equal-ordinary-alternative'))

    def test_ordinary_copy_is_distinct(self):
        self.reject(lambda m:m['controls'][35]['source_definition'].update(symbol=m['controls'][3]['source_definition']['symbol']))

    def test_no_field_masking(self):self.reject(lambda m:m['controls'][1]['bindings'].pop())

    def test_actual_field_offset(self):
        self.reject(lambda m:m['controls'][1]['section']['fields'][0].update(offset=15))

    def test_whole_backward_negative(self):self.reject(lambda m:m['negative_backward'].update(size=47))

    def test_backward_member_is_assignment(self):
        self.reject(lambda m:m['negative_backward']['bindings'][0].update(target_address='0x004591E0'))

    def test_entire_eh_carrier(self):self.reject(lambda m:m['controls'][26].update(size=17))

    def test_entire_state_data(self):self.reject(lambda m:m['controls'][27].update(size=28))

    def test_original_frame_registration(self):
        self.reject(lambda m:m['retained_frames'][0].update(handler_address='0x00656380'))

    def test_opaque_constructor_remains_unknown(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004591E0')['origin'].update(origin='library'))

    def test_opaque_destructor_remains_unknown(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004212A0')['origin'].update(origin='authored'))

    def test_compiler_wrapper_retains_its_ownership(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00422A20')['origin'].update(origin='library'))

    def test_math_ambiguity_retained(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00641FB8')['origin'].update(origin='library'))

    def test_complete_emission(self):self.reject(lambda m:m['emission'].pop())

    def test_complete_actual_headers(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))

    def test_complete_layout(self):self.reject(lambda m:m['layout_values'].__setitem__(3,112))

    def test_exact_bounded_transitions(self):
        for r in self.m['functions']:
            self.assertTrue(V.accepted_snapshot(dict(function=r['original_function'],origin=r['original_origin']),r['accepted_function'],r['accepted_origin']))

    def test_changed_original_is_not_accepted(self):
        r=self.m['functions'][0];old=dict(function=copy.deepcopy(r['original_function']),origin=r['original_origin']);old['function']['notes']+=' changed'
        self.assertFalse(V.accepted_snapshot(old,r['accepted_function'],r['accepted_origin']))

    def test_evidence_only_is_not_acceptance(self):
        r=self.m['functions'][0];V.check_ledger(r,r['original_function'],r['original_origin'],True)
        with self.assertRaises(ValueError):V.check_ledger(r,r['original_function'],r['original_origin'])

    def negative_bytes(self):
        row=copy.deepcopy(self.m['controls'][33]);actual=bytearray(151);linked=bytearray(151)
        for i,(a,b) in V.ORDINARY_POP_DIFFERENCES.items():linked[i]=a;actual[i]=b
        raw=bytes(linked);row['source_sha256']=V.digest(raw);row['body_sha256']=V.digest(actual)
        return row,raw,bytes(linked),bytes(actual)

    def test_entire_negative_difference_evidence(self):V.verify_control_bytes(*self.negative_bytes())

    def test_negative_cannot_hide_additional_difference(self):
        row,raw,linked,actual=self.negative_bytes();linked=bytearray(linked);linked[120]=1
        with self.assertRaises(ValueError):V.verify_control_bytes(row,raw,bytes(linked),actual)

    def test_negative_cannot_compare_a_prefix(self):
        row,raw,linked,actual=self.negative_bytes()
        with self.assertRaises(ValueError):V.verify_control_bytes(row,raw[:-1],linked[:-1],actual[:-1])

    def test_negative_cannot_earn_positive_credit(self):
        row,raw,linked,actual=self.negative_bytes();row['role']='candidate-sdk-owner'
        with self.assertRaises(ValueError):V.verify_control_bytes(row,raw,linked,actual)


if __name__=='__main__':unittest.main()
