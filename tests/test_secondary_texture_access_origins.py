"""Guard complete source ownership and independent secondary-vector evidence."""
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('secondary_texture_tests',ROOT/'scripts/verify-secondary-texture-access-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class SecondaryTextureAccessOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_whole_index(self):self.reject(lambda m:m['functions'][0].update(size=48))
    def test_whole_dereference(self):self.reject(lambda m:m['functions'][1].update(size=18))
    def test_library_owner(self):self.reject(lambda m:m['functions'][0].update(decision='authored'))
    def test_no_source_claim(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_type_claim(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='FalseOwner::entry()'))
    def test_no_private_abi_claim(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_actual_begin(self):self.reject(lambda m:m['controls'][0]['bindings'][0].update(target_address='0x0040DCE0'))
    def test_actual_arithmetic(self):self.reject(lambda m:m['controls'][0]['bindings'][1].update(target_address='0x0040DFD0'))
    def test_actual_const_getter(self):self.reject(lambda m:m['controls'][1]['bindings'][0].update(target_address='0x0040E9B0'))
    def test_actual_const_constructor(self):self.reject(lambda m:m['controls'][5]['bindings'][0].update(target_address='0x0040EA40'))
    def test_complete_real_fields(self):self.reject(lambda m:m['controls'][0]['bindings'].pop())
    def test_no_masked_field(self):self.reject(lambda m:m['controls'][0]['section']['fields'][0].update(offset=26))
    def test_whole_arithmetic_context(self):self.reject(lambda m:m['controls'][6].update(size=31))
    def test_whole_ordinary_begin(self):self.reject(lambda m:m['controls'][8].update(size=30))
    def test_whole_ordinary_index(self):self.reject(lambda m:m['controls'][9].update(size=48))
    def test_whole_ordinary_dereference(self):self.reject(lambda m:m['controls'][10].update(size=18))
    def test_ordinary_names_stay_distinct(self):self.reject(lambda m:m['controls'][9]['source_definition'].update(symbol=m['controls'][0]['source_definition']['symbol']))
    def test_all_emitted_sections(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_header_ownership(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_independent_four_byte_width(self):self.reject(lambda m:m['layout_values'].__setitem__(0,44))
    def test_whole_readonly_layout(self):self.reject(lambda m:m['layout'].update(size=20))
    def test_full_initialize_parent(self):self.reject(lambda m:m['anchors'][0].update(size=176))
    def test_full_release_parent(self):self.reject(lambda m:m['anchors'][1].update(size=433))
    def test_authored_parent_evidence(self):self.reject(lambda m:m['anchors'][0]['origin'].update(evidence_id='R019'))
    def test_actual_parent_calls(self):self.reject(lambda m:m['parent_edges'].pop())
    def test_const_getter_remains_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040EA20')['origin'].update(origin='library'))
    def test_prior_assignment_remains_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0040E000')['origin'].update(origin='library'))
    def test_prior_records_retained(self):self.reject(lambda m:m['retained'].pop())


if __name__=='__main__':unittest.main()
