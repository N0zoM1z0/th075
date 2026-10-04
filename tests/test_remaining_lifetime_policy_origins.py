"""Reject truncated policy evidence, masked layout differences and false ownership."""
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('remaining_lifetime_tests',ROOT/'scripts/verify-remaining-lifetime-policy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class RemainingLifetimePolicyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_full_constructor(self):self.reject(lambda m:m['functions'][0].update(size=141))
    def test_full_raster_release(self):self.reject(lambda m:m['functions'][1].update(size=128))
    def test_no_equal_length_source_credit(self):self.reject(lambda m:m['functions'][0].update(symbol='FalseMatch'))
    def test_no_reconstruction_presence(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_owner_type(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='FalseOwner()'))
    def test_no_private_abi(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(match_percent='100.00'))
    def test_entire_authored_record(self):self.reject(lambda m:m['functions'][1]['accepted_authored_record'].update(size='128'))
    def test_actual_postconstruction_clear(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x005F6FD1').update(operands='0x5f8320'))
    def test_actual_array_extent(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x005F6F86').update(operands='3'))
    def test_actual_vector_offset(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x005F6FAC').update(operands='ecx, 0x2c'))
    def test_actual_storage_guard(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x0041BFE0').update(mnemonic='jne'))
    def test_actual_storage_zero(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x0041BFFA').update(operands='dword ptr [ecx + 0x14], 1'))
    def test_actual_width_reset(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x0041C032').update(operands='dword ptr [ecx + 8], 1'))
    def test_actual_restore_delete_release_order(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x0041C016').update(operands='dword ptr [0x657214]'))
    def test_complete_source_constructor(self):self.reject(lambda m:m['policies'][0].update(size=108))
    def test_implicit_source_identity(self):self.reject(lambda m:m['policies'][1].update(implicit=False))
    def test_entire_implicit_source_control(self):self.reject(lambda m:m['policies'][3].update(size=4))
    def test_source_call_order_from_real_fields(self):self.reject(lambda m:m['policies'][0]['call_symbols'].reverse())
    def test_no_custom_source_positive(self):self.reject(lambda m:m['policies'][2].update(ambiguous_target='0x0041BFD0'))
    def test_entire_ordinary_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_sdk_include_ownership(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_entire_readonly_layout(self):self.reject(lambda m:m['layout'].update(size=44))
    def test_no_layout_padding(self):self.reject(lambda m:m['layout_values'].__setitem__(5,24))
    def test_full_negative_extent(self):self.reject(lambda m:m['negative'].update(size=128))
    def test_no_masked_field(self):self.reject(lambda m:m['negative']['bindings'].pop())
    def test_actual_delete_binding(self):self.reject(lambda m:m['negative']['bindings'][0].update(target_address='0x00641700'))
    def test_all_layout_differences_preserved(self):self.reject(lambda m:m['negative']['differences'].pop())
    def test_interface_release_stays_unknown(self):self.reject(lambda m:m['pending']['origin'].update(origin='authored'))
    def test_interface_release_gets_no_accepted_transition(self):self.reject(lambda m:m['pending'].update(accepted_origin='False'))
    def test_deleting_parent_stays_compiler(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041A140')['origin'].update(origin='authored'))
    def test_opaque_pointed_owner_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x005F7ED0')['origin'].update(origin='authored'))
    def test_real_gdi_import(self):self.reject(lambda m:m['import_slots'][0].update(name='DeleteObject'))

if __name__=='__main__':unittest.main()
