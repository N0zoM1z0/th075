"""Guard full acos extent, inherited helper flags and real shared source entries."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('acos_review', ROOT/'scripts/verify-acos-math-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class AcosMathOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.row = self.m['functions'][0]
        self.graph = {r['address']:r for r in self.m['functions']+self.m['anchors']}

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def test_complete_plan(self):
        REVIEW.verify_plan(self.m)

    def test_intrinsic_prefix_is_not_complete_parent(self):
        self.row['size'] = 20
        self.reject()

    def test_last_error_return_byte_is_required(self):
        self.row['size'] = 202
        self.reject()

    def test_provisional_huge_core_is_not_accepted_extent(self):
        self.m['interior_labels'][0]['size'] = 12494
        self.reject()

    def test_core_requires_actual_static_start_definition(self):
        self.m['interior_labels'][0]['source_definition']['storage'] = 2
        self.reject()

    def test_core_entry_is_plus_29(self):
        self.m['interior_labels'][0]['source_offset'] = 20
        self.reject()

    def test_shared_core_cannot_gain_an_independent_aux(self):
        self.m['interior_labels'][0]['extent_basis'] = 'function-auxiliary-record'
        self.reject()

    def test_parent_partition_retains_exported_c_and_core_regions(self):
        self.row['code_regions'] = [dict(offset=0,size=20),dict(offset=101,size=102)]
        self.reject()

    def test_complete_fastflag_state_keeps_both_words(self):
        self.m['state_data'][0]['size'] = 4
        self.reject()

    def test_whole_operation_name_keeps_complete_source_extent(self):
        self.m['state_data'][1]['size'] = 5
        self.reject()

    def test_whole_fp_constants_are_not_single_indefinite_value(self):
        self.m['state_data'][2]['size'] = 10
        self.reject()

    def test_real_control_word_helper_keeps_prior_origin(self):
        self.m['anchors'][2]['origin_evidence'] = 'R147'
        self.reject()

    def test_retained_non_inventory_fast_exit_has_full_source_proof(self):
        self.m['retained_source_controls'].clear()
        self.reject()

    def test_complete_independent_power_fp_context_is_required(self):
        self.m['retained_controls'].clear()
        self.reject()

    def test_generated_positive_and_negative_unit_sections_are_required(self):
        self.m['probe_generated_data'].pop()
        self.reject()

    def test_generated_unit_constant_is_full_eight_bytes(self):
        self.m['probe_generated_data'][0]['source_section']['size'] = 4
        self.reject()

    def remove_witness(self,mnemonic,operands):
        self.row['instruction_witnesses'] = [w for w in self.row['instruction_witnesses'] if (w['mnemonic'],w['operands']) != (mnemonic,operands)]

    def reject_protocol(self):
        with self.assertRaises(ValueError):
            REVIEW.check_acos_protocol(self.m,self.graph)

    def test_ci_must_store_without_popping_x87_argument(self):
        self.remove_witness('fst','qword ptr [esp]')
        self.reject_protocol()

    def test_actual_internal_call_reaches_static_core(self):
        self.remove_witness('call','0x643b2d')
        self.reject_protocol()

    def test_c_entry_passes_actual_stack_pointer_to_fload(self):
        self.remove_witness('lea','edx, [esp + 4]')
        self.reject_protocol()

    def test_helper_flags_must_survive_until_special_value_je(self):
        witness = next(w for w in self.row['instruction_witnesses'] if w['site']=='0x00643B2E')
        witness.update(mnemonic='test',operands='eax, eax')
        self.reject_protocol()

    def test_default_control_word_check_is_required(self):
        self.remove_witness('cmp','word ptr [esp], 0x27f')
        self.reject_protocol()

    def test_normal_path_retains_actual_sqrt_atan_sequence(self):
        self.remove_witness('fsqrt','')
        self.reject_protocol()

    def test_negative_unit_endpoint_keeps_pi_route(self):
        self.remove_witness('fldpi','')
        self.reject_protocol()

    def test_positive_unit_endpoint_keeps_zero_route(self):
        self.remove_witness('fldz','')
        self.reject_protocol()

    def test_nan_conversion_has_complete_real_helper(self):
        self.remove_witness('call','0x646b7c')
        self.reject_protocol()

    def test_indefinite_load_uses_real_extended_precision_constant(self):
        self.remove_witness('fld','xword ptr [0x670270]')
        self.reject_protocol()

    def test_actual_one_argument_error_call_is_required(self):
        self.remove_witness('call','0x646cf7')
        self.reject_protocol()

    def test_final_core_return_is_not_discarded(self):
        self.row['body_facts']['returns'].pop()
        self.reject_protocol()

    def test_error_and_normal_fastflag_fields_both_bind_full_state(self):
        self.row['relocation_bindings'][-4]['target_address'] = '0x0068E2C4'
        self.reject_protocol()

    def test_no_runtime_accuracy_or_original_private_abi_claim(self):
        self.m['acos_protocol']['unknowns'].clear()
        self.reject()


if __name__ == '__main__':
    unittest.main()
