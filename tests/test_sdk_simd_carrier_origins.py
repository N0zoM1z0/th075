import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result
verify = module('test_simd_verify', 'verify-sdk-simd-carrier-origins.py')
carrier = module('test_simd_carrier', 'sdk_code_carriers.py')
sdk = module('test_simd_sdk', 'verify-sdk-origins.py')


class SDKSimdCarrierTests(unittest.TestCase):
    def setUp(self):
        self.m = json.loads((ROOT/verify.EVIDENCE).read_text())

    def reject(self, mutate):
        m = copy.deepcopy(self.m); mutate(m)
        with self.assertRaises(ValueError):
            verify.verify_plan(m)

    def flow(self, code, peers=None, fields=None):
        return carrier.carrier_flow(code, 0x1000, {'peers': peers or [{'offset': 0}]}, fields or [], {}, {}, sdk)

    def test_whole_immutable_scope(self):
        verify.verify_plan(self.m)
        self.assertEqual(hashlib.sha256((ROOT/verify.EVIDENCE).read_bytes()).hexdigest(), verify.MANIFEST_SHA256)

    def test_source_carrier_cannot_be_cut_to_candidate_ret(self):
        self.reject(lambda m: m['controls'][0].update(size=262))

    def test_alignment_cannot_receive_function_credit(self):
        self.reject(lambda m: m['functions'][0].update(size=272))

    def test_pointer_callback_cannot_be_dropped(self):
        self.reject(lambda m: m['controls'][0]['fields'].pop())

    def test_local_secondary_entry_cannot_be_hidden(self):
        self.reject(lambda m: next(r for r in m['controls'] if len(r['source']['peers']) > 1)['flow']['roots'].pop())

    def test_common_declaration_is_not_an_initialized_definition(self):
        self.reject(lambda m: next(r for r in m['data'] if r['kind'] == 'source-common-zero-fill').update(kind='source-initialized-section'))

    def test_full_common_size_cannot_be_invented_from_target_pointer(self):
        self.reject(lambda m: next(r for r in m['data'] if r['kind'] == 'source-common-zero-fill')['declaration'].update(offset=1))

    def test_writable_initial_data_is_not_claimed_readonly(self):
        self.reject(lambda m: next(r for r in m['data'] if r['kind'] == 'source-initialized-section').update(flags=0x40000040))

    def test_whole_bss_extent_cannot_be_a_selected_word(self):
        self.reject(lambda m: next(r for r in m['data'] if r['kind'] == 'source-zero-fill-section').update(size=4))

    def test_noninventory_control_does_not_become_a_new_candidate(self):
        self.reject(lambda m: m['functions'].append(next(r for r in m['controls'] if r['origin'] is None)))

    def test_original_source_or_abi_credit_cannot_be_added(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(source_file='src/Fake.cpp'))

    def test_real_alignment_mov_and_lea_are_retained_but_not_credited(self):
        code = bytes.fromhex('c3 8bf6 8dbc2700000000')
        result = self.flow(code)
        self.assertEqual((result['extent'], result['alignment_size']), (1, 9))

    def test_unreachable_register_write_is_not_alignment(self):
        with self.assertRaises(ValueError):
            self.flow(bytes.fromhex('c3 b801000000'))

    def test_field_hidden_after_ret_is_not_alignment(self):
        with self.assertRaises(ValueError):
            self.flow(bytes.fromhex('c3 8dbc2700000000'), fields=[{'offset': 4}])

    def test_secondary_entry_inside_an_immediate_is_rejected(self):
        with self.assertRaises(ValueError):
            self.flow(bytes.fromhex('b801000000 c3'), peers=[{'offset': 0}, {'offset': 1}])

    def test_separate_member_local_data_names_keep_separate_keys(self):
        f = {'symbol': '.data', 'symbol_section': 3, 'symbol_type': 0, 'symbol_storage': 3, 'symbol_index': 10}
        self.assertNotEqual(verify.field_key(2081484, f), verify.field_key(2118836, f))

    def test_different_coff_section_declarations_are_not_name_aliases(self):
        f = {'symbol': '.data1', 'symbol_section': 7, 'symbol_type': 0, 'symbol_storage': 3, 'symbol_index': 10}
        g = dict(f, symbol_section=8, symbol_index=11)
        self.assertNotEqual(verify.field_key(2081484, f), verify.field_key(2081484, g))

    def test_external_tail_needs_an_independent_complete_callee(self):
        with self.assertRaises(ValueError):
            self.flow(bytes.fromhex('e910000000'))


if __name__ == '__main__':
    unittest.main()
