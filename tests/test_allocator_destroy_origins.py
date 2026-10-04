"""Keep wrapper ownership separate from ordinary shapes and destruction policy."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('allocator_tests',ROOT/'scripts/verify-allocator-destroy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class AllocatorDestroyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()

    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_complete_plan(self):V.verify_plan(self.m)
    def test_full_wrapper(self):self.reject(lambda m:m['functions'][0].update(size=24))
    def test_full_parent(self):self.reject(lambda m:m['controls'][2].update(size=150))
    def test_full_ordinary_wrapper(self):self.reject(lambda m:m['controls'][9].update(size=24))
    def test_full_noop_child(self):self.reject(lambda m:m['controls'][7].update(size=4))
    def test_actual_nontrivial_child(self):self.reject(lambda m:m['controls'][0]['bindings'][0].update(target_address='0x0042E580'))
    def test_real_deque_parent_field(self):self.reject(lambda m:m['controls'][2]['bindings'][1].update(target_address='0x0042E390'))
    def test_no_field_mask(self):self.reject(lambda m:m['controls'][2]['bindings'].pop())
    def test_actual_field_offset(self):self.reject(lambda m:m['controls'][0]['section']['fields'][0].update(offset=11))
    def test_genuine_sdk_owner(self):self.reject(lambda m:m['controls'][0]['source_definition'].update(symbol='OrdinaryAllocator'))
    def test_no_ordinary_parent_substitution(self):self.reject(lambda m:m['controls'][2]['source_definition'].update(symbol='OrdinaryPop'))
    def test_distinct_ordinary_control(self):self.reject(lambda m:m['controls'][9]['source_definition'].update(symbol=m['controls'][0]['source_definition']['symbol']))
    def test_no_source_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_abi_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='void destroy(Game*)'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_no_authored_credit(self):self.reject(lambda m:m['functions'][0]['accepted_origin'].update(origin='authored'))
    def test_nontrivial_child_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004229C0')['origin'].update(origin='library'))
    def test_noop_child_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0042E580')['origin'].update(origin='library'))
    def test_game_lifetime_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004212A0')['origin'].update(origin='compiler'))
    def test_compiler_wrapper_retained(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00422A20')['origin'].update(origin='library'))
    def test_independent_parent_retained(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00422290')['origin'].update(evidence_id='R165'))
    def test_whole_combined_layout(self):self.reject(lambda m:m['layout'].update(size=60))
    def test_both_layout_definitions(self):self.reject(lambda m:m['layout']['definitions'].pop())
    def test_full_layout_values(self):self.reject(lambda m:m['layout_values'].__setitem__(15,20))
    def test_full_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_probe_include(self):self.reject(lambda m:m['headers'].pop('probes/VC7SDKDependencyContexts.cpp'))

    def test_exact_accepted_snapshot(self):
        for r in self.m['functions']:
            old=dict(function=r['original_function'],origin=r['original_origin'])
            self.assertTrue(V.accepted_snapshot(old,r['accepted_function'],r['accepted_origin']))
            snapshot=next(x for x in V.SDK.manifest()['snapshots'] if x['address']==r['address'])
            self.assertTrue(V.SDK.preserved_snapshot(snapshot,r['accepted_function'],r['accepted_origin']))

    def test_changed_original_not_accepted(self):
        r=self.m['functions'][0];old=dict(function=copy.deepcopy(r['original_function']),origin=r['original_origin']);old['function']['notes']+=' changed'
        self.assertFalse(V.accepted_snapshot(old,r['accepted_function'],r['accepted_origin']))

    def test_changed_parent_not_preserved(self):
        snapshot=next(r for r in V.SDK.manifest()['snapshots'] if r['address']=='0x00422290');changed=copy.deepcopy(snapshot['function']);changed['notes']+=' changed'
        self.assertFalse(V.SDK.preserved_snapshot(snapshot,changed,snapshot['origin']))

    def test_changed_lifetime_not_preserved(self):
        snapshot=next(r for r in V.SDK.manifest()['snapshots'] if r['address']=='0x004212A0');changed=copy.deepcopy(snapshot['origin']);changed['origin']='authored'
        self.assertFalse(V.SDK.preserved_snapshot(snapshot,snapshot['function'],changed))


if __name__=='__main__':unittest.main()
