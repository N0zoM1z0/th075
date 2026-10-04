"""Guard complete iterator graph, independent replay policy and original owners."""
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('replay_iterator_tests',ROOT/'scripts/verify-replay-deque-iterator-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class ReplayDequeIteratorOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_complete_plan(self):V.verify_plan(self.m)
    def test_complete_default_const_body(self):self.reject(lambda m:m['functions'][7].update(size=32))
    def test_complete_endpoint_body(self):self.reject(lambda m:m['functions'][3].update(size=40))
    def test_genuine_library_origin(self):self.reject(lambda m:m['functions'][0].update(decision='authored'))
    def test_no_source_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_original_type_claim(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='ReplayQueue::iterator()'))
    def test_no_private_abi_claim(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_no_unrelated_boundary_change(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(span_end='0x00414946'))
    def test_actual_default_constructor_child(self):self.reject(lambda m:m['controls'][0]['bindings'][0].update(target_address='0x004156B0'))
    def test_actual_node_constructor_child(self):self.reject(lambda m:next(r for r in m['controls'] if r['address']=='0x00415670')['bindings'][0].update(target_address='0x00415EC0'))
    def test_independent_word_specialization(self):self.reject(lambda m:m['controls'][7]['source_definition'].update(symbol=m['controls'][1]['source_definition']['symbol']))
    def test_no_dropped_real_field(self):self.reject(lambda m:m['controls'][3]['bindings'].pop())
    def test_no_substituted_source_field(self):self.reject(lambda m:m['controls'][3]['section']['fields'][0].update(offset=12))
    def test_complete_ordinary_base(self):self.reject(lambda m:m['controls'][36].update(size=32))
    def test_complete_ordinary_derived(self):self.reject(lambda m:m['controls'][37].update(size=21))
    def test_ordinary_stays_distinct(self):self.reject(lambda m:m['controls'][36]['source_definition'].update(symbol=m['controls'][18]['source_definition']['symbol']))
    def test_actual_ordinary_base_field(self):self.reject(lambda m:m['controls'][37]['bindings'][0].update(target_address='0x004157C0'))
    def test_entire_ordinary_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_include_ownership(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_whole_combined_layout(self):self.reject(lambda m:m['layout'].update(size=44))
    def test_observed_width_is_independent(self):self.reject(lambda m:m['layout_values'].__setitem__(1,4))
    def test_whole_independent_game_parent(self):self.reject(lambda m:m['anchors'][0].update(size=1251))
    def test_authored_parent_stays_authored(self):self.reject(lambda m:m['anchors'][0]['origin'].update(origin='library'))
    def test_original_parent_batch(self):self.reject(lambda m:m['anchors'][0]['record'].update(evidence_id='R111'))
    def test_all_original_consumer_edges(self):self.reject(lambda m:m['parent_edges'].pop())
    def test_actual_consumer_destination(self):self.reject(lambda m:m['parent_edges'][0].update(target='0x004149E0'))
    def test_all_prior_peer_records(self):self.reject(lambda m:m['retained'].pop())
    def test_original_peer_identity(self):self.reject(lambda m:m['retained'][0].update(address='0x004155A0'))
    def test_prior_short_getter_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00531D80')['origin'].update(origin='library'))
    def test_prior_catch_interior_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00532196')['origin'].update(origin='compiler'))
    def test_prior_empty_destructor_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040D8E0')['origin'].update(origin='authored'))


if __name__=='__main__':unittest.main()
