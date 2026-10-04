"""Guard complete math parents, source ambiguity, shared entries and typed linking."""
import importlib.util
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('power_review', ROOT/'scripts/verify-power-math-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class PowerMathOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.graph = {r['address']:r for r in self.m['functions']+self.m['auxiliary_bodies']+self.m['anchors']}

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def test_complete_plan(self):
        REVIEW.verify_plan(self.m)

    def test_sse_parent_is_not_25_byte_prefix(self):
        self.graph['0x0064DC60']['size'] = 25
        self.reject()

    def test_wrapper_cannot_absorb_fallback_ci_prelude(self):
        self.graph['0x00643770']['size'] = 84
        self.reject()

    def test_fallback_shared_tail_cannot_be_omitted(self):
        self.graph['0x006437AB']['size'] = 255
        self.reject()

    def test_existing_fallback_core_must_keep_whole_tail(self):
        self.m['interior_labels'][1]['size'] = 221
        self.reject()

    def test_core_entry_cannot_gain_invented_aux(self):
        self.m['interior_labels'][0]['extent_basis'] = 'function-auxiliary-record'
        self.reject()

    def test_all_sse_returns_and_exception_tails_are_required(self):
        self.graph['0x0064DC60']['body_facts']['returns'].pop()
        self.reject()

    def test_sse_last_branch_is_required(self):
        self.graph['0x0064DC60']['branches'].pop()
        self.reject()

    def test_entire_table_is_required_from_interior_sigmask_anchor(self):
        self.m['state_data'][0]['size'] = 16
        self.reject()

    def test_table_base_is_not_interior_anchor_address(self):
        self.m['state_data'][0]['target_address'] = '0x00667290'
        self.reject()

    def test_actual_source_table_definitions_are_required(self):
        self.m['state_data'][0]['source_section']['definitions'].pop()
        self.reject()

    def test_whole_fpu_return_dispatch_table_is_required(self):
        self.m['state_data'][3]['relocations'].pop()
        self.reject()

    def test_cpu_dispatch_common_cannot_be_guessed(self):
        self.m['common_globals'][0]['target_address'] = '0x0068FBA4'
        self.reject()

    def test_competing_strong_dispatch_definition_is_not_silent(self):
        self.m['common_alternatives'][0]['definitions'].append(self.m['common_alternatives'][0]['definitions'][0])
        self.reject()

    def test_complete_pow_carrier_accounts_for_alignment_nop(self):
        self.m['code_carriers'][0]['gaps'].clear()
        self.reject()

    def test_complete_pow_carrier_accounts_for_default_body(self):
        self.m['code_carriers'][0]['components'].pop()
        self.reject()

    def test_atan_log_log10_own_wrapper_ambiguity_is_retained(self):
        self.m['source_alternatives'].pop()
        self.reject()

    def test_full_alternative_cannot_be_reduced_to_same_shaped_wrapper(self):
        self.m['source_alternatives'][0]['size'] = 59
        self.reject()

    def test_negative_whole_alternative_comparison_is_recorded(self):
        self.m['source_alternatives'][0]['non_field_difference_offsets'].clear()
        self.reject()

    def test_independent_libm_error_parent_is_required(self):
        self.m['anchors'].pop(0)
        self.reject()

    def test_full_retained_r130_replay_is_required(self):
        self.m['retained_controls'].clear()
        self.reject()

    def test_non_inventory_prior_owner_cannot_gain_candidate_credit(self):
        self.m['retained_source_controls'].clear()
        self.reject()

    def remove_witness(self,key,mnemonic,operands):
        row = self.graph[key]
        row['instruction_witnesses'] = [w for w in row['instruction_witnesses'] if (w['mnemonic'],w['operands']) != (mnemonic,operands)]

    def reject_protocol(self):
        with self.assertRaises(ValueError):
            REVIEW.check_power_protocol(self.m,self.graph)

    def test_dispatch_checks_both_sse_and_x87_masks(self):
        self.remove_witness('0x00643770','fnstcw','word ptr [esp]')
        self.reject_protocol()

    def test_dispatch_restores_scratch_stack_before_tail_transfer(self):
        self.remove_witness('0x00643770','lea','esp, [esp + 8]')
        self.reject_protocol()

    def test_sse_intrinsic_marshals_actual_x87_pair(self):
        self.remove_witness('0x0064DC60','fxch','st(1)')
        self.reject_protocol()

    def test_sse_internal_call_reaches_real_exported_entry(self):
        self.remove_witness('0x0064DC60','call','0x64dc79')
        self.reject_protocol()

    def test_default_internal_call_reaches_actual_static_start(self):
        self.remove_witness('0x006437AB','call','0x6437cd')
        self.reject_protocol()

    def test_fallback_preserves_high_argument_word_in_eax(self):
        self.remove_witness('0x006437AB','mov','eax, dword ptr [esp + 0xc]')
        self.reject_protocol()

    def test_actual_table_anchor_offset_is_required(self):
        self.m['state_data'][0]['source_anchor']['offset'] = 0
        self.reject_protocol()

    def fixture(self):
        row = self.graph['0x00643770']
        fields = [{k:b[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for b in row['relocation_bindings']]
        source = bytes(row['size'])
        state = {(row['member_offset'],'___use_sse2_mathfcns'):0x68FBA0}
        return source,fields,row,state

    def link(self,source,fields,row,state):
        return REVIEW.link_complete(source,fields,row,state,{},None,self.graph,self.m['code_definitions'])

    def test_independent_link_computes_dir32_and_signed_rel32(self):
        source,fields,row,state = self.fixture()
        actual = self.link(source,fields,row,state)
        expected = bytearray(source)
        struct.pack_into('<I',expected,2,0x68FBA0)
        struct.pack_into('<I',expected,55,(0x64DC60-(0x643770+55+4))&0xffffffff)
        self.assertEqual(actual,expected)
        self.assertEqual(len(actual),59)

    def test_full_link_preserves_bytes_outside_fields(self):
        source,fields,row,state = self.fixture();source = b'X'+source[1:]
        self.assertEqual(self.link(source,fields,row,state)[0],ord('X'))

    def test_target_solved_common_cannot_override_independent_definition(self):
        source,fields,row,state = self.fixture();state[(row['member_offset'],'___use_sse2_mathfcns')]+=4
        with self.assertRaisesRegex(ValueError,'override'):
            self.link(source,fields,row,state)

    def test_equal_shaped_atan_wrapper_cannot_use_pow_parent_symbol(self):
        source,fields,row,state = self.fixture();fields[1]['symbol']='__CIatan_pentium4';row['relocation_bindings'][1]['symbol']='__CIatan_pentium4'
        with self.assertRaises(ValueError):
            self.link(source,fields,row,state)

    def test_callee_field_cannot_target_core_instead_of_intrinsic_entry(self):
        source,fields,row,state = self.fixture();row['relocation_bindings'][1]['target_address']='0x0064DC79'
        with self.assertRaises(ValueError):
            self.link(source,fields,row,state)

    def test_relocation_cannot_escape_whole_wrapper(self):
        source,fields,row,state = self.fixture();fields[1]['offset']=57;row['relocation_bindings'][1]['offset']=57
        with self.assertRaisesRegex(ValueError,'escapes'):
            self.link(source,fields,row,state)

    def test_relocation_fields_cannot_overlap(self):
        source,fields,row,state = self.fixture();fields[1]['offset']=3;row['relocation_bindings'][1]['offset']=3
        with self.assertRaisesRegex(ValueError,'overlaps'):
            self.link(source,fields,row,state)

    def test_source_body_cannot_be_shorter_than_complete_extent(self):
        source,fields,row,state = self.fixture()
        with self.assertRaisesRegex(ValueError,'topology'):
            self.link(source[:-1],fields,row,state)

    def test_sdk_exception_record_is_complete(self):
        self.m['sdk_layout']['objects'][0]['values'][3] = 24
        self.reject()

    def test_original_private_abi_and_runtime_inputs_remain_unknown(self):
        self.m['power_protocol']['unknowns'].clear()
        self.reject()


if __name__ == '__main__':
    unittest.main()
