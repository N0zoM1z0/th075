"""Guard full floor carrier, alternative operation binding and signed rounding paths."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('floor_review', ROOT/'scripts/verify-floor-math-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class FloorMathOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.graph = {r['address']:r for r in self.m['functions']+self.m['auxiliary_bodies']+self.m['anchors']}

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def test_complete_plan(self):
        REVIEW.verify_plan(self.m)

    def test_wrapper_own_aux_is_not_entire_carrier(self):
        self.m['functions'][0]['size'] = 289
        self.reject()

    def test_full_carrier_cannot_be_wrapper_prefix(self):
        self.m['code_carriers'][0]['size'] = 64
        self.reject()

    def test_sse_owner_cannot_be_omitted(self):
        self.m['auxiliary_bodies'].clear()
        self.reject()

    def test_sse_owner_cannot_gain_inventory_credit(self):
        self.m['auxiliary_bodies'][0]['ledger_size'] = 225
        self.reject()

    def test_last_sse_return_byte_is_required(self):
        self.m['auxiliary_bodies'][0]['size'] = 224
        self.reject()

    def test_full_constant_section_is_not_bns_mask_only(self):
        self.m['state_data'][0]['size'] = 16
        self.reject()

    def test_constant_base_is_not_interior_bns_address(self):
        self.m['state_data'][0]['target_address'] = '0x006611A0'
        self.reject()

    def test_all_five_real_constant_definitions_are_required(self):
        self.m['state_data'][0]['source_section']['definitions'].pop()
        self.reject()

    def test_both_complete_prior_origins_are_retained(self):
        self.m['anchors'][0]['origin_evidence'] = 'R148'
        self.reject()

    def test_sse_common_cannot_be_initialized_symbol(self):
        self.m['common_globals'][0]['source_definition']['section'] = 1
        self.reject()

    def test_competing_dispatch_definition_cannot_be_ignored(self):
        self.m['common_alternatives'][0]['definitions'].append(self.m['common_alternatives'][0]['definitions'][0])
        self.reject()

    def test_modf_and_ceil_whole_alternatives_are_required(self):
        self.m['source_alternatives'].pop()
        self.reject()

    def test_equal_shaped_wrapper_is_not_full_alternative(self):
        self.m['source_alternatives'][0]['size'] = 64
        self.reject()

    def test_full_default_and_sse_dependency_replays_are_required(self):
        self.m['retained_controls'].pop()
        self.reject()

    def test_whole_carrier_has_no_invented_padding_gap(self):
        self.m['code_carriers'][0]['gaps'] = [dict(offset=64,size=1)]
        self.reject()

    def remove_witness(self,key,mnemonic,operands):
        row = self.graph[key]
        row['instruction_witnesses'] = [w for w in row['instruction_witnesses'] if (w['mnemonic'],w['operands']) != (mnemonic,operands)]

    def reject_protocol(self):
        with self.assertRaises(ValueError):
            REVIEW.check_floor_protocol(self.m,self.graph)

    def test_both_exception_masks_are_checked(self):
        self.remove_witness('0x006439C0','fnstcw','word ptr [esp]')
        self.reject_protocol()

    def test_scratch_stack_is_restored_before_tail_transfer(self):
        self.remove_witness('0x006439C0','lea','esp, [esp + 8]')
        self.reject_protocol()

    def test_default_branch_reaches_actual_floor_owner(self):
        self.remove_witness('0x006439C0','jne','0x64e980')
        self.reject_protocol()

    def test_sse_branch_reaches_actual_same_section_entry(self):
        self.remove_witness('0x006439C0','jmp','0x643a00')
        self.reject_protocol()

    def test_negative_fraction_correction_is_subtraction(self):
        self.remove_witness('0x00643A00','subsd','xmm1, xmm0')
        self.reject_protocol()

    def test_negative_fraction_mask_uses_full_one_constant(self):
        self.remove_witness('0x00643A00','andpd','xmm0, xmmword ptr [0x661190]')
        self.reject_protocol()

    def test_small_negative_and_negative_zero_path_is_retained(self):
        self.remove_witness('0x00643A00','orpd','xmm3, xmmword ptr [0x6611c0]')
        self.reject_protocol()

    def test_small_positive_zero_path_is_retained(self):
        self.remove_witness('0x00643A00','fldz','')
        self.reject_protocol()

    def test_nan_self_comparison_and_error_context_are_retained(self):
        self.remove_witness('0x00643A00','mov','edx, 0x3ed')
        self.reject_protocol()

    def test_nan_error_call_keeps_complete_libm_parent(self):
        self.remove_witness('0x00643A00','call','0x6485d7')
        self.reject_protocol()

    def test_all_sse_return_tails_are_required(self):
        self.graph['0x00643A00']['body_facts']['returns'].pop()
        self.reject_protocol()

    def test_carrier_contiguity_is_not_a_guessed_new_boundary(self):
        self.m['code_carriers'][0]['components'][1]['offset'] = 65
        self.reject_protocol()

    def test_actual_interior_constant_anchor_is_required(self):
        self.m['state_data'][0]['source_anchor']['offset'] = 0
        self.reject_protocol()

    def test_sdk_rounding_modes_keep_actual_downward_value(self):
        self.m['sdk_layout']['objects'][0]['values'][15] = 512
        self.reject()

    def test_runtime_numerical_and_private_abi_uncertainty_is_preserved(self):
        self.m['floor_protocol']['unknowns'].clear()
        self.reject()


if __name__ == '__main__':
    unittest.main()
