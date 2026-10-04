"""Protect complete producer evidence and conservative ownership decisions."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('producer_tests',ROOT/'scripts/verify-vector-producer-origins.py')
V = importlib.util.module_from_spec(spec); spec.loader.exec_module(V)


class VectorProducerOrigins(unittest.TestCase):
    def setUp(self):
        self.m = V.manifest()

    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError): V.verify_plan(self.m)

    def test_complete_plan(self):
        V.verify_plan(self.m)

    def test_whole_candidate(self):
        self.reject(lambda m:m['functions'][0].update(size=30))

    def test_no_96_byte_nontrivial_parent(self):
        self.reject(lambda m:m['controls'][21].update(size=96))

    def test_whole_texture_parent(self):
        self.reject(lambda m:m['controls'][22].update(size=166))

    def test_independent_accepted_parent(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x005F8B70')['origin'].update(origin='unknown'))

    def test_actual_constructor_base(self):
        self.reject(lambda m:m['controls'][14]['bindings'][0].update(target_address='0x005F9DB0'))

    def test_pending_short_leaf_cannot_gain_origin(self):
        self.reject(lambda m:m['functions'][0]['accepted_origin'].update(origin='library'))

    def test_pending_parent_cannot_gain_origin(self):
        self.reject(lambda m:m['functions'][-1]['accepted_origin'].update(origin='library'))

    def test_pending_parent_cannot_gain_recovered_name(self):
        self.reject(lambda m:m['functions'][-1]['accepted_function'].update(proposed_name='RecoveredVectorAssign'))

    def test_no_masked_field_acceptance(self):
        self.reject(lambda m:m['controls'][21]['bindings'].pop())

    def test_whole_erase_boundary(self):
        self.reject(lambda m:m['controls'][24].update(size=98))

    def test_real_source_field(self):
        self.reject(lambda m:m['controls'][21]['section']['fields'][0]['symbol'].update(symbol='UnverifiedHandler'))

    def test_full_cleanup_and_handler(self):
        self.reject(lambda m:m['controls'][35].update(size=10))

    def test_full_unwind_and_funcinfo(self):
        self.reject(lambda m:m['controls'][36].update(size=28))

    def test_state_symbol_is_own_interior_definition(self):
        self.reject(lambda m:m['controls'][36]['source_definition'].update(offset=0))

    def test_complete_original_registered_frames(self):
        self.reject(lambda m:m['retained_frames'].pop())

    def test_whole_ordinary_parent(self):
        self.reject(lambda m:m['controls'][33].update(size=157))

    def test_distinct_ordinary_source(self):
        self.reject(lambda m:m['controls'][30]['source_definition'].update(symbol=m['controls'][12]['source_definition']['symbol']))

    def test_nonaccepting_producer_is_42_bytes(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00411C90').update(size=31))

    def test_nonaccepting_bridge_stays_unknown(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00531D80')['origin'].update(origin='library'))

    def test_protected_lifetime(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040D8E0')['origin'].update(origin='authored'))

    def test_protected_copy(self):
        self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004229D0')['origin'].update(origin='compiler'))

    def test_full_cold_emission(self):
        self.reject(lambda m:m['emission'].pop())

    def test_complete_actual_header_set(self):
        self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))

    def test_complete_observation_layout(self):
        self.reject(lambda m:m['layout_values'].pop())

    def test_cookie_profile_is_negative_full_extent(self):
        self.reject(lambda m:m['negative_profile']['controls'][0]['section'].update(size=158))

    def test_cookie_control_retains_actual_cookie_field(self):
        self.reject(lambda m:m['negative_profile']['controls'][0]['section']['fields'][3]['symbol'].update(symbol='FakeCookie'))

    def test_cold_flags_are_valid_explicit_options(self):
        self.reject(lambda m:m['profile'].append('/GS-'))

    def test_no_source_credit(self):
        self.reject(lambda m:m['functions'][12]['accepted_function'].update(source_file='src/False.cpp'))

    def test_no_abi_credit(self):
        self.reject(lambda m:m['functions'][14]['accepted_function'].update(calling_convention='thiscall'))

    def test_no_exact_credit(self):
        self.reject(lambda m:m['functions'][12]['accepted_function'].update(match_percent='100.00'))

    def test_exact_bounded_transitions(self):
        for r in self.m['functions']:
            self.assertTrue(V.accepted_snapshot(dict(function=r['original_function'],origin=r['original_origin']),r['accepted_function'],r['accepted_origin']))

    def test_altered_snapshot_rejected(self):
        r=self.m['functions'][0]; old=dict(function=copy.deepcopy(r['original_function']),origin=r['original_origin']);old['function']['notes']+=' changed'
        self.assertFalse(V.accepted_snapshot(old,r['accepted_function'],r['accepted_origin']))

    def test_evidence_only_grants_no_credit(self):
        r=self.m['functions'][12]
        V.check_ledger(r,r['original_function'],r['original_origin'],evidence_only=True)
        with self.assertRaises(ValueError): V.check_ledger(r,r['original_function'],r['original_origin'])


if __name__=='__main__': unittest.main()
