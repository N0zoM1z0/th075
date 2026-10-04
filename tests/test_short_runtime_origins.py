import copy
import importlib.util
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('short_runtime', ROOT / 'scripts/verify-short-runtime-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class ShortRuntimeOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.rows = {r['address']: r for r in self.m['functions']}

    def reject(self, message):
        with self.assertRaisesRegex(ValueError, message):
            REVIEW.verify_plan(self.m)

    def test_vector_requires_entire_96_byte_section(self):
        self.rows['0x00641D4A']['size'] = 72
        self.reject('complete own auxiliary extent')

    def test_vector_cannot_claim_nonexistent_auxiliary(self):
        self.rows['0x00641D4A']['extent_basis'] = 'function-auxiliary-record'
        self.reject('complete own auxiliary extent')

    def test_array_unwind_requires_its_full_94_byte_auxiliary(self):
        self.rows['0x00641CEC']['size'] = 47
        self.reject('complete own auxiliary extent')

    def test_fabs_requires_all_177_bytes(self):
        self.rows['0x006418CD']['code_size'] = 100
        self.reject('complete own auxiliary extent')

    def test_existing_vector_cleanup_must_keep_owner_offset_72(self):
        self.m['interior_labels'][0]['source_offset'] = 0
        self.reject('shared entries lose complete source parents')

    def test_vector_cleanup_cannot_be_separate_primary(self):
        self.m['functions'].append(self.m['interior_labels'][0])
        self.reject('bounded complete short runtime cohort')

    def test_no_invented_auxiliary_inventory_credit(self):
        self.m['auxiliary_bodies'].append({'address': '0x00641D92'})
        self.reject('invented auxiliary candidates')

    def test_math_names_require_full_232_byte_carrier(self):
        next(r for r in self.m['state_data'] if r['size'] == 232)['size'] = 8
        self.reject('complete defining sections')

    def test_all_29_typed_string_pointers_are_required(self):
        next(r for r in self.m['state_data'] if r['size'] == 232)['relocations'].pop()
        self.reject('29-entry operation/name table')

    def test_math_name_pointer_offsets_are_not_arbitrary(self):
        next(r for r in self.m['state_data'] if r['size'] == 232)['relocations'][0]['offset'] = 0
        self.reject('29-entry operation/name table')

    def test_scope_requires_full_twelve_byte_definition(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '$T18597')['size'] = 8
        self.reject('complete defining sections')

    def test_scope_pointer_cannot_name_unreviewed_code(self):
        field = next(r for r in self.m['state_data'] if r['symbol'] == '$T18597')['relocations'][0]
        field['code_entry']['owner'] = '0x00641DAA'
        self.reject('unreviewed actual code entry')

    def test_rand_seed_offset_requires_vendor_thread_layout(self):
        self.m['short_runtime_protocol']['seed_offset'] = 16
        self.reject('seed/math/name/array-callback protocol')

    def test_rand_multiplier_is_complete_target_policy(self):
        self.m['short_runtime_protocol']['multiplier'] += 1
        self.reject('seed/math/name/array-callback protocol')

    def test_rand_result_mask_cannot_be_truncated(self):
        self.m['short_runtime_protocol']['result_mask'] = 255
        self.reject('seed/math/name/array-callback protocol')

    def test_seed_store_must_bind_actual_getptd_return(self):
        witness = next(w for w in self.rows['0x0064189E']['instruction_witnesses'] if w['operands'] == 'dword ptr [eax + 0x14], ecx')
        witness['operands'] = 'dword ptr [ecx + 0x14], eax'
        self.reject('thread seed store')

    def test_rand_updates_same_thread_state(self):
        witness = next(w for w in self.rows['0x006418AB']['instruction_witnesses'] if w['operands'] == 'dword ptr [eax + 0x14], ecx')
        witness['operands'] = 'dword ptr [eax + 0x10], ecx'
        self.reject('seed/update/result provenance')

    def test_fabs_operation_is_not_inferred_from_name(self):
        witness = next(w for w in self.rows['0x006418CD']['instruction_witnesses'] if w['operands'] == '0x15')
        witness['operands'] = '0x12'
        self.reject('actual exception operation code')

    def test_destructor_callback_requires_actual_parameter_slot(self):
        self.rows['0x00641D4A']['indirect_calls'][0]['operand'] = 'dword ptr [ebp + 0x10]'
        self.reject('callback receiver/parameter/stdcall provenance')

    def test_natural_callback_requires_ecx_receiver(self):
        self.m['callback_control']['instructions'][2]['operands'] = 'eax, dword ptr [ebp + 8]'
        self.reject('member callback ABI control')

    def test_natural_layout_keeps_int_and_long_four_bytes(self):
        self.m['sdk_layout']['objects'][0]['values'][2] = 8
        self.reject('operation/layout controls')

    def test_abs_cannot_gain_library_origin_from_vendor_shape(self):
        self.m['diagnostic_contexts'][0]['decision'] = 'library'
        self.reject('unproved library/source identity')

    def test_abs_original_symbol_spelling_remains_unknown(self):
        self.m['diagnostic_contexts'][0]['proposed_name'] = '_abs'
        self.reject('unproved library/source identity')

    def test_labs_complete_alternative_cannot_be_discarded(self):
        self.m['abs_alternatives'].clear()
        self.reject('abs/labs source-family ambiguity')

    def test_both_ordinary_abs_expression_controls_are_required(self):
        self.m['abs_expression_controls']['functions'].pop()
        self.reject('ordinary abs expression controls')

    def test_pending_abs_cannot_gain_exact_credit(self):
        function = {'owner': '', 'proposed_name': '', 'source_file': '', 'size': '11', 'match_percent': '100.00'}
        with self.assertRaisesRegex(ValueError, 'invented ownership/source/exact credit'):
            REVIEW.check_pending(function, {'origin': 'unknown', 'disposition': 'review'})

    def section_fixture(self):
        row = copy.deepcopy(self.rows['0x00641D4A'])
        definitions = copy.deepcopy(row['source_code_section']['definitions'])
        section = row['source_definition']['section']
        raw = bytearray(20+section*40)
        struct.pack_into('<8sIIIIIIHHI', raw, 20+(section-1)*40, b'.text', 0, 0,
                         96, 0, 0, 0, 0, 0, int(row['source_code_section']['flags'], 16))
        coff = SimpleNamespace(parse_symbols=lambda data, name: (None, definitions))
        comparison = SimpleNamespace(coff_name=None)
        return row, raw, definitions, coff, comparison

    def test_full_single_function_code_section_is_supported(self):
        row, raw, _, coff, comparison = self.section_fixture()
        REVIEW.check_code_section(row, raw, coff, comparison)

    def test_code_section_extent_comes_from_source_header(self):
        row, raw, _, coff, comparison = self.section_fixture()
        struct.pack_into('<I', raw, 20+(row['source_definition']['section']-1)*40+16, 72)
        with self.assertRaisesRegex(ValueError, 'entire sole defining code section'):
            REVIEW.check_code_section(row, raw, coff, comparison)

    def test_code_section_cannot_swallow_second_global_function(self):
        row, raw, definitions, coff, comparison = self.section_fixture()
        definitions.append(dict(symbol='other', offset=72, section=row['source_definition']['section'], type=32, storage=2))
        row['source_code_section']['definitions'] = definitions
        with self.assertRaisesRegex(ValueError, 'entire sole defining code section'):
            REVIEW.check_code_section(row, raw, coff, comparison)

    def test_retained_full_runtime_graph_is_required(self):
        self.m['retained_controls'].clear()
        self.reject('independently retained')


if __name__ == '__main__':
    unittest.main()
