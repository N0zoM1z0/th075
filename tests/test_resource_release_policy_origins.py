"""Guard whole explicit policies, cleanup carriers and ownership boundaries."""
import importlib.util
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('resource_release_tests',ROOT/'scripts/verify-resource-release-policy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class ResourceReleasePolicyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_whole_interface_release(self):self.reject(lambda m:m['functions'][0].update(size=82))
    def test_whole_handle_release(self):self.reject(lambda m:m['functions'][1].update(size=97))
    def test_whole_character_release(self):self.reject(lambda m:m['functions'][2].update(size=104))
    def test_character_has_no_false_source_match(self):self.reject(lambda m:m['functions'][2].update(symbol='FakeSource'))
    def test_no_reconstructed_source(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_type(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='FalseOwner::~FalseOwner()'))
    def test_no_private_abi(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_full_authored_record(self):self.reject(lambda m:m['functions'][0]['accepted_authored_record'].update(size='82'))
    def test_actual_virtual_release(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x00412E80').update(operands='dword ptr [ecx + 4]'))
    def test_actual_handle_guard(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x0041D219').update(mnemonic='jne'))
    def test_actual_character_clear(self):self.reject(lambda m:next(r for r in m['functions'][2]['witnesses'] if r['site']=='0x0052D055').update(operands='0x531c40'))
    def test_sdk_owner_independent(self):self.reject(lambda m:m['functions'][3].update(decision='authored'))
    def test_entire_sdk_clear(self):self.reject(lambda m:m['functions'][3].update(size=152))
    def test_complete_sdk_fields(self):self.reject(lambda m:m['controls'][2]['bindings'].pop())
    def test_actual_closed_route(self):self.reject(lambda m:m['controls'][2]['bindings'][0].update(target_address='0x0041E100'))
    def test_no_masked_field(self):self.reject(lambda m:m['controls'][0]['section']['fields'][0].update(offset=7))
    def test_whole_eh_carrier(self):self.reject(lambda m:next(r for r in m['controls'] if r['kind']=='eh-code').update(size=11))
    def test_whole_state_data(self):self.reject(lambda m:next(r for r in m['controls'] if r['kind']=='state-data').update(size=28))
    def test_whole_ordinary_alternative(self):self.reject(lambda m:m['controls'][-1].update(size=18))
    def test_whole_implicit_negative(self):self.reject(lambda m:m['alternatives'][0].update(size=21))
    def test_character_small_layout_stays_separate(self):self.reject(lambda m:m['alternatives'][2].update(size=105))
    def test_implicit_destructor_call_order(self):self.reject(lambda m:m['alternatives'][3]['call_symbols'].reverse())
    def test_complete_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_headers(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_complete_layout(self):self.reject(lambda m:m['layout'].update(size=40))
    def test_original_payload_widths(self):self.reject(lambda m:m['layout_values'].__setitem__(0,164))
    def test_whole_base_policy(self):self.reject(lambda m:m['anchors'][1].update(size=587))
    def test_original_deleting_records(self):self.reject(lambda m:m['retained'].pop())
    def test_original_complete_frames(self):self.reject(lambda m:m['retained_frames'].pop())
    def test_real_import(self):self.reject(lambda m:m['import_slot'].update(name='DeleteFileA'))
    def test_selected_slot_is_not_whole_vtable(self):self.reject(lambda m:m['selected_slot'].update(size=8))
    def test_link_getter_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041E100')['origin'].update(origin='library'))
    def test_empty_destructor_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00532480')['origin'].update(origin='library'))


if __name__=='__main__':unittest.main()
