import importlib.util
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    'floating_operation', ROOT / 'scripts/verify-floating-operation-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class FloatingOperationOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.rows = {r['address']: r for r in self.m['functions']}
        self.graph = {r['address']: r for r in self.m['functions'] + self.m['anchors']}
        self.parser = self.graph['0x00652CD1']

    def reject(self, message):
        with self.assertRaisesRegex(ValueError, message):
            REVIEW.verify_plan(self.m)

    def remove_witness(self, address, mnemonic, operands):
        row = self.graph[address]
        row['instruction_witnesses'] = [w for w in row['instruction_witnesses']
                                        if (w['mnemonic'], w['operands']) != (mnemonic, operands)]

    def table_fixture(self):
        # Only synthetic pointer fields are needed; no target opcodes are copied.
        actual = bytearray(self.parser['size'])
        entries = self.parser['embedded_tables'][0]['entries']
        for entry in entries:
            struct.pack_into('<I', actual, entry['offset'], int(entry['target_address'], 16))
        starts = [SimpleNamespace(address=int(e['target_address'], 16)) for e in entries]
        return actual, starts

    def test_complete_plan_is_supported(self):
        REVIEW.verify_plan(self.m)

    def test_converter_wrapper_requires_its_return_and_cookie_check(self):
        self.rows['0x0064F7F0']['size'] = 55
        self.reject('complete own auxiliary extent')

    def test_ldexp_requires_overflow_underflow_and_restore_paths(self):
        self.rows['0x0064EA53']['code_size'] = 330
        self.reject('complete own auxiliary extent')

    def test_nextafter_requires_full_675_byte_owner(self):
        self.rows['0x00643D23']['size'] = 633
        self.reject('complete own auxiliary extent')

    def test_private_sources_cannot_be_invented(self):
        self.m['vendor_sources']['crt/src/intrncvt.c'] = 'unknown'
        self.reject('available source/header context')

    def test_complete_fp80_definition_is_required(self):
        self.m['sdk_layout']['headers'].pop('crt/src/fpieee.h')
        self.reject('available source/header context')

    def test_long_double_is_not_sdk_fp80(self):
        self.m['sdk_layout']['objects'][0]['values'][3] = 10
        self.reject('operation/layout controls')

    def test_private_storage_span_is_not_sdk_fp80(self):
        self.m['floating_protocol']['parser_storage_span'] = 10
        self.reject('source/storage/layout/ABI')

    def test_parser_requires_seven_stack_arguments(self):
        self.m['floating_protocol']['parser_stack_arguments'] = 6
        self.reject('source/storage/layout/ABI')

    def test_combined_cleanup_requires_both_calls(self):
        self.m['floating_protocol']['combined_caller_cleanup'] = 28
        self.reject('source/storage/layout/ABI')

    def test_converter_status_flag_is_not_parser_status(self):
        self.m['floating_protocol']['converter_status_flag'] = 1
        self.reject('source/storage/layout/ABI')

    def test_abstract_rounding_macro_is_not_raw_x87_word(self):
        self.m['floating_protocol']['raw_operation_control'] = 256
        self.reject('source/storage/layout/ABI')

    def test_current_fp_state_cannot_be_claimed(self):
        self.m['floating_protocol']['runtime_unknowns'] = 'known default rounding and handler'
        self.reject('source/storage/layout/ABI')

    def test_infinity_requires_complete_40_byte_defining_section(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__d_inf')['size'] = 8
        self.reject('complete defining sections')

    def test_all_folded_constant_definitions_are_required(self):
        self.m['state_data'].pop()
        self.reject('complete defining sections')

    def test_retained_error_and_parser_graph_is_required(self):
        self.m['retained_controls'] = []
        self.reject('independently retained')

    def test_unary_abi_control_requires_stack_double_argument(self):
        self.m['call_controls'][0]['instructions'][3]['operands'] = 'esp, 4'
        self.reject('source/storage/layout/ABI')

    def test_natural_parser_control_requires_complete_local_storage(self):
        self.m['call_controls'][-1]['size'] = 77
        self.reject('source/storage/layout/ABI')

    def test_original_atoldbl_end_pointer_storage_is_required(self):
        self.remove_witness('0x0064F7F0', 'lea', 'eax, [ebp - 0x14]')
        self.reject('actual conversion/status/control')

    def test_stringtold_requires_converter_status_merge(self):
        self.remove_witness('0x00653105', 'or', 'esi, 2')
        self.reject('actual conversion/status/control')

    def test_floor_requires_real_cdecl_frnd_dependency(self):
        self.remove_witness('0x0064E980', 'call', '0x65151b')
        self.reject('actual conversion/status/control')

    def test_logb_requires_real_decomposition_dependency(self):
        self.remove_witness('0x00643C38', 'call', '0x64762b')
        self.reject('actual conversion/status/control')

    def test_nextafter_requires_downward_scale_path(self):
        self.remove_witness('0x00643D23', 'add', 'eax, 0xfffffa00')
        self.reject('actual conversion/status/control')

    def test_ldexp_requires_integer_limit_branch(self):
        self.remove_witness('0x0064EA53', 'cmp', 'ecx, 0x7fffffff')
        self.reject('actual conversion/status/control')

    def test_target_returns_are_caller_cleaned(self):
        self.rows['0x00643C38']['body_facts']['returns'][0]['cleanup'] = 8
        self.reject('caller-cleaned returns')

    def test_full_parser_anchor_cannot_be_truncated_to_instructions(self):
        self.parser['size'] = 1028
        self.reject('independent complete anchors')

    def test_parser_table_cannot_be_decoded_as_instructions(self):
        self.parser['code_regions'] = [dict(offset=0, size=1076)]
        self.reject('source code/data partition')

    def test_parser_requires_all_twelve_entries(self):
        self.parser['embedded_tables'][0]['entries'].pop()
        self.reject('twelve-entry table owner')

    def test_parser_requires_actual_dispatch_address(self):
        self.parser['indirect_jumps'][0]['operand'] = 'dword ptr [eax*4 + 0x6530d1]'
        self.reject('actual full-table dispatch')

    def test_parser_table_case_cannot_be_a_data_label(self):
        binding = self.parser['embedded_tables'][0]['entries'][0]
        definition = next(r['source_definition'] for r in self.m['code_definitions']
                          if r['owner'] == self.parser['address'] and r['source_definition']['symbol'] == '$L1157')
        binding.update(symbol='$L1157', target_address='0x006530D5')
        binding['code_entry'].update(source_definition=definition, source_offset=1028)
        with self.assertRaisesRegex(ValueError, 'defining source owner/entry'):
            REVIEW.check_code_entry(binding, self.graph)

    def test_parser_partition_covers_all_owner_bytes(self):
        actual, starts = self.table_fixture()
        REVIEW.check_parser_partition(self.parser, actual, starts)
        self.parser['size'] += 1
        with self.assertRaisesRegex(ValueError, 'omits or pads'):
            REVIEW.check_parser_partition(self.parser, actual, starts)

    def test_parser_table_requires_actual_case_instruction_starts(self):
        actual, starts = self.table_fixture()
        starts.pop()
        with self.assertRaisesRegex(ValueError, 'actual code case starts'):
            REVIEW.check_parser_partition(self.parser, actual, starts)

    def test_parser_table_requires_source_selector(self):
        actual, starts = self.table_fixture()
        next(b for b in self.parser['relocation_bindings'] if b['offset'] == 102)['symbol'] = '$L873'
        with self.assertRaisesRegex(ValueError, 'source selector field'):
            REVIEW.check_parser_partition(self.parser, actual, starts)

    def test_new_primary_cannot_gain_unresolved_indirect_dispatch(self):
        self.rows['0x0064EA53']['indirect_calls'] = [dict(site='0x0064EC15', operand='eax')]
        self.reject('unsupported indirect dispatch')


if __name__ == '__main__':
    unittest.main()
