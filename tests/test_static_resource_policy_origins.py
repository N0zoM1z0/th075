"""Guard explicit static policy, member order and independent opaque ownership."""
import importlib.util
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('static_resource_tests',ROOT/'scripts/verify-static-resource-policy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class StaticResourcePolicyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_whole_initializer(self):self.reject(lambda m:m['functions'][0].update(size=131))
    def test_whole_queue_destructor(self):self.reject(lambda m:m['functions'][1].update(size=160))
    def test_whole_queue_clear(self):self.reject(lambda m:m['functions'][2].update(size=66))
    def test_whole_pointer_loop(self):self.reject(lambda m:m['functions'][3].update(size=234))
    def test_no_custom_source_byte_match(self):self.reject(lambda m:m['functions'][0].update(symbol='FalseSource'))
    def test_no_reconstructed_source(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_type(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='FalseOwner::FalseOwner()'))
    def test_no_private_abi(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_entire_authored_record(self):self.reject(lambda m:m['functions'][2]['accepted_authored_record'].update(size='66'))
    def test_actual_handle_default(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x004136B6').update(operands='dword ptr [eax], 1'))
    def test_actual_handle_guard(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x00413711').update(mnemonic='jne'))
    def test_actual_close_then_zero(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x00413722').update(operands='dword ptr [eax], 1'))
    def test_ascending_clear_order(self):self.reject(lambda m:next(r for r in m['functions'][2]['witnesses'] if r['site']=='0x0041388A').update(operands='ecx, 0x190'))
    def test_reverse_automatic_order(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x0041372F').update(operands='ecx, 0x154'))
    def test_actual_owned_pointer_delete(self):self.reject(lambda m:next(r for r in m['functions'][3]['witnesses'] if r['site']=='0x005F7078').update(operands='0x640f15'))
    def test_sdk_owner_independent(self):self.reject(lambda m:m['functions'][4].update(decision='authored'))
    def test_entire_sdk_index(self):self.reject(lambda m:m['functions'][4].update(size=48))
    def test_real_sdk_fields(self):self.reject(lambda m:m['controls'][0]['bindings'].pop())
    def test_actual_sdk_route(self):self.reject(lambda m:m['controls'][0]['bindings'][0].update(target_address='0x0040E1F0'))
    def test_no_masked_field(self):self.reject(lambda m:m['controls'][0]['section']['fields'][0].update(offset=26))
    def test_whole_ordinary_index(self):self.reject(lambda m:m['controls'][18].update(size=48))
    def test_whole_ordinary_dereference(self):self.reject(lambda m:m['controls'][20].update(size=18))
    def test_entire_small_layout_control(self):self.reject(lambda m:m['policies'][0].update(size=132))
    def test_source_implicit_order(self):self.reject(lambda m:m['policies'][8]['call_symbols'].reverse())
    def test_exception_profile_independent(self):self.reject(lambda m:m['secondary']['profile'].append('/GX'))
    def test_both_full_emissions(self):self.reject(lambda m:m['secondary']['emission'].pop())
    def test_first_full_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_includes(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_whole_readonly_layout(self):self.reject(lambda m:m['layout'].update(size=44))
    def test_independent_whole_parent(self):self.reject(lambda m:m['anchors'][1].update(size=161))
    def test_original_complete_frames(self):self.reject(lambda m:m['retained_frames'].pop())
    def test_const_getter_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x005F9640')['origin'].update(origin='library'))
    def test_lifetime_child_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x005F7ED0')['origin'].update(origin='authored'))
    def test_deleting_thunk_stays_compiler(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x005F7EA0')['origin'].update(origin='authored'))
    def test_real_closehandle_import(self):self.reject(lambda m:m['import_slot'].update(name='DeleteFileA'))


if __name__=='__main__':unittest.main()
