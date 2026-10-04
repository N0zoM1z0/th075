"""Guard real file paths, rolling-key context and unmasked whole source negatives."""
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('file_resource_tests',ROOT/'scripts/verify-file-resource-policy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class FileResourcePolicyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_whole_music_transform(self):self.reject(lambda m:m['functions'][0].update(size=297))
    def test_whole_readable_file_policy(self):self.reject(lambda m:m['functions'][1].update(size=132))
    def test_no_equal_length_byte_credit(self):self.reject(lambda m:m['functions'][0].update(symbol='FalsePositive'))
    def test_no_source_presence(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_original_owner_type(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='FalseOwner::encode()'))
    def test_no_private_abi(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_entire_authored_record(self):self.reject(lambda m:m['functions'][1]['accepted_authored_record'].update(size='132'))
    def test_original_text_path(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x0042731B').update(operands='0x657ca0'))
    def test_original_binary_path(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x0042738C').update(operands='0x657c90'))
    def test_actual_key_seed(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x004273A0').update(operands='byte ptr [ebp - 0x12], 0x5a'))
    def test_actual_key_step(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x004273EA').update(operands='ecx, 0x3e'))
    def test_actual_unsigned_loop(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x004273C0').update(mnemonic='jge'))
    def test_actual_write_before_close(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x00427404').update(operands='dword ptr [0x657138]'))
    def test_actual_invalid_file_guard(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x0041D6F6').update(operands='0x41d732'))
    def test_actual_archive_list_offset(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x0041D72F').update(operands='ecx, 0'))
    def test_copied_record_initial_state(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x0041D6F8').update(operands='dword ptr [ebp - 0x10], 1'))
    def test_copied_record_file_size(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x0041D70B').update(operands='dword ptr [ebp - 0x14], ecx'))
    def test_complete_independent_loader(self):self.reject(lambda m:m['anchors'][0].update(size=915))
    def test_independent_loader_key(self):self.reject(lambda m:next(r for r in m['anchors'][0]['witnesses'] if r['site']=='0x00426E35').update(operands='byte ptr [ebp - 9], 0x5b'))
    def test_full_source_operation(self):self.reject(lambda m:m['policies'][1].update(size=133))
    def test_no_fake_target_positive(self):self.reject(lambda m:m['policies'][0].update(target_positive=True))
    def test_actual_source_cleanup_order(self):self.reject(lambda m:m['policies'][0]['call_symbols'].reverse())
    def test_entire_ordinary_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_sdk_includes(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_whole_readonly_layout(self):self.reject(lambda m:m['layout'].update(size=12))
    def test_no_original_owner_layout_credit(self):self.reject(lambda m:m['layout_values'].__setitem__(3,16))
    def test_whole_unmasked_negative(self):self.reject(lambda m:m['negative'].update(size=297))
    def test_all_genuine_fields(self):self.reject(lambda m:m['negative']['bindings'].pop())
    def test_actual_array_delete_binding(self):self.reject(lambda m:m['negative']['bindings'][-1].update(target_address='0x00640F15'))
    def test_all_difference_bytes_retained(self):self.reject(lambda m:m['negative']['differences'].pop())
    def test_entire_text_filename(self):self.reject(lambda m:m['strings'][0].update(size=13))
    def test_distinct_independent_catalog_string(self):self.reject(lambda m:m['independent_catalog_string'].update(address='0x00657CA0'))
    def test_real_file_import(self):self.reject(lambda m:m['import_slots'][2].update(name='WriteFile'))
    def test_interface_owner_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004170B0')['origin'].update(origin='authored'))
    def test_sdk_list_ownership_independent(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041D9C0')['origin'].update(origin='authored'))

if __name__=='__main__':unittest.main()
