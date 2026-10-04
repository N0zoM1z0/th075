"""Reject partial x87 tables, wrong source scopes and invented shared-entry credit."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('fp_dispatch', ROOT / 'scripts/verify-fp-dispatch-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class FPDispatchOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.rows = {r['address']:r for r in self.m['functions']}
        self.graph = {**self.rows, **{r['address']:r for r in self.m['auxiliary_bodies']+self.m['anchors']}}

    def reject(self, message):
        with self.assertRaisesRegex(ValueError, message):
            REVIEW.verify_plan(self.m)

    def ledger(self, row):
        return (dict(size=str(row['size']), span_end=row['span_end'], source_file='', match_percent='0.00',
                     owner='library', module='VC71CRT', status='excluded', proposed_name=row['coff_symbol']),
                dict(evidence_id='R127', origin='library', subsystem='VC71CRT', disposition='exclude', confidence=REVIEW.CONFIDENCE))

    def test_two_argument_dispatch_requires_whole_shared_exit(self):
        self.rows['0x00648A6B']['size'] = 72
        self.reject('complete own auxiliary extent')

    def test_primitive_group_cannot_be_a_seven_byte_prefix(self):
        next(r for r in self.m['auxiliary_bodies'] if r['address'] == '0x00646A73')['size'] = 7
        self.reject('invented candidates')

    def test_atan_helper_requires_entire_source_primary(self):
        next(r for r in self.m['auxiliary_bodies'] if r['address'] == '0x00648940')['code_size'] = 108
        self.reject('invented candidates')

    def test_ciatan2_cannot_gain_inventory_credit(self):
        next(r for r in self.m['auxiliary_bodies'] if r['address'] == '0x0064224A')['ledger_size'] = 10
        self.reject('invented candidates')

    def test_shared_sign_entry_cannot_be_standalone_source(self):
        self.m['interior_labels'][0]['extent_basis'] = 'function-auxiliary-record'
        self.reject('standalone credit')

    def test_intrinsic_exit_requires_actual_offset_79(self):
        next(r for r in self.m['interior_labels'] if r['address'] == '0x00648ABA')['source_offset'] = 72
        self.reject('complete source parents')

    def test_atan_pi_entry_keeps_its_own_168_byte_owner(self):
        next(r for r in self.m['interior_labels'] if r['address'] == '0x006489AC')['parent'] = '0x00646A73'
        self.reject('complete source parents')

    def test_two_arg_error_handler_requires_actual_shared_tail(self):
        self.rows['0x00646CE0']['direct_edges'][0]['source_offset'] = 0
        self.reject('same-section owner')

    def test_shared_transfer_cannot_cross_unrelated_object_sections(self):
        self.rows['0x00646CE0']['direct_edges'][0]['source_section'] = 2
        self.reject('same-section owner')

    def test_complete_exception_filter_cannot_be_replaced_by_name(self):
        b = next(b for b in self.rows['0x006505CA']['relocation_bindings'] if b['target_kind'] == 'callee')
        b['code_entry']['owner'] = '0x00423B20'
        self.reject('unreviewed actual code entry')

    def test_code_pointer_requires_true_source_definition(self):
        table = next(r for r in self.m['state_data'] if r['symbol'] == '__OP_ATAN2jmptab')
        table['relocations'][0]['code_entry']['source_definition']['symbol'] = 'guessed_atan2'
        self.reject('defining source owner')

    def test_nan_entry_cannot_point_to_parent_start(self):
        table = next(r for r in self.m['state_data'] if r['symbol'] == '__OP_ATAN2jmptab')
        table['relocations'][2]['code_entry']['source_offset'] = 0
        self.reject('defining source owner')

    def test_table_requires_all_sixteen_typed_targets(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__OP_ATAN2jmptab')['relocations'].pop()
        self.reject('sixteen entries')

    def test_table_cannot_be_four_entry_one_argument_prefix(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__OP_ATAN2jmptab')['size'] = 32
        self.reject('carrier prefixes')

    def test_tag_lookup_requires_all_sixteen_classifier_bytes(self):
        self.m['dispatch_protocol']['tag_offsets'].pop()
        self.reject('table protocol')

    def test_tag_classifier_cannot_select_other_table_offsets(self):
        self.m['dispatch_protocol']['tag_offsets'][0] = 16
        self.reject('table protocol')

    def test_operation_must_be_actual_atan2_not_pow(self):
        self.m['dispatch_protocol']['operation'] = 29
        self.reject('table protocol')

    def test_table_requires_actual_complete_edx_caller(self):
        self.rows['0x00642240']['instruction_witnesses'][0]['operands'] = 'eax, 0x670660'
        self.reject('defining EDX callers')

    def test_classifier_requires_real_two_argument_index_combination(self):
        next(w for w in self.rows['0x006469E7']['instruction_witnesses'] if w['site'] == '0x00646A5F')['operands'] = 'al, cl'
        self.reject('indexed table guard')

    def test_indirect_jump_cannot_be_an_unknown_register(self):
        self.rows['0x00646980']['indirect_jumps'][0]['operand'] = 'eax'
        self.reject('indirect transfer inventory')

    def test_constants_require_whole_40_byte_carrier(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__d_inf')['size'] = 8
        self.reject('carrier prefixes')

    def test_fastflag_requires_both_bss_definitions(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '___fastflag')['size'] = 4
        self.reject('carrier prefixes')

    def test_member_local_one_constants_remain_distinct(self):
        use = dict(member_offset=2486736,symbol='One',target_address='0x00670284')
        states = {(2486736,'One'):0x670284,(2559836,'One'):0x661600}
        self.assertEqual(REVIEW.resolve_state_reference(use,states,{}),0x670284)
        use['target_address'] = '0x00661600'
        with self.assertRaisesRegex(ValueError, 'member-local data'):
            REVIEW.resolve_state_reference(use,states,{})

    def test_undefined_external_data_reference_is_insufficient(self):
        use = dict(member_offset=1,symbol='One',target_address='0x00670284')
        with self.assertRaisesRegex(ValueError, 'whole strong definition'):
            REVIEW.resolve_state_reference(use,{}, {})

    def test_ambiguous_external_definition_cannot_be_silently_selected(self):
        use = dict(member_offset=1,symbol='One',target_address='0x00670284')
        with self.assertRaisesRegex(ValueError, 'whole strong definition'):
            REVIEW.resolve_state_reference(use,{}, {'One':{0x670284,0x661600}})

    def test_ieee_record_requires_112_bytes(self):
        self.m['sdk_layout']['objects'][0]['values'][6] = 88
        self.reject('exception layouts')

    def test_ieee_operand2_requires_actual_offset_48(self):
        self.m['sdk_layout']['objects'][0]['values'][11] = 40
        self.reject('exception layouts')

    def test_ieee_valid_format_bitfield_requires_mask_three(self):
        self.m['sdk_layout']['objects'][2]['values'][4] = 2
        self.reject('bitfields differ')

    def test_flags_object_size_excludes_automatic_alignment_gap(self):
        self.m['sdk_layout']['objects'][1]['size'] = 12
        self.reject('bitfields differ')

    def test_origin_comparison_cannot_earn_exact_credit(self):
        row = self.rows['0x00648A6B']; function, origin = self.ledger(row); function['match_percent'] = '100.00'
        with self.assertRaisesRegex(ValueError, 'origin-only extent'):
            REVIEW.check_ledger(row,function,origin)

    def test_shared_label_cannot_acquire_proposed_standalone_name(self):
        row = self.m['interior_labels'][0]
        function = dict(size=str(row['size']),span_end=f"0x{int(row['address'],16)+row['size']-1:08X}",
                        source_file='',match_percent='0.00',owner='library',module='VC71CRT',status='excluded',proposed_name='__rtchsifneg')
        origin = dict(evidence_id='R127',origin='library',disposition='exclude',subsystem='VC71CRT',confidence=REVIEW.LABEL_CONFIDENCE)
        with self.assertRaisesRegex(ValueError, 'standalone/source/exact credit'):
            REVIEW.check_label(row,function,origin,{}, {},self.graph)
