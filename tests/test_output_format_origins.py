import copy
import importlib.util
from pathlib import Path
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('output_format',ROOT/'scripts/verify-output-format-origins.py')
REVIEW=importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)

class OutputFormatOriginTests(unittest.TestCase):
    def setUp(self):
        self.m=REVIEW.manifest()
        self.rows={r['address']:r for r in self.m['functions']}
        self.graph={r['address']:r for r in self.m['functions']+self.m['auxiliary_bodies']+self.m['anchors']}

    def reject(self,message):
        with self.assertRaisesRegex(ValueError,message):
            REVIEW.verify_plan(self.m)

    def test_complete_plan_is_supported(self):
        REVIEW.verify_plan(self.m)

    def test_output_cannot_truncate_full_aux_to_code(self):
        self.rows['0x006445C4']['size']=2010
        self.reject('complete own auxiliary extent')

    def test_output_table_cannot_be_decoded_as_executable_code(self):
        self.rows['0x006445C4']['code_size']=2042
        self.reject('complete own auxiliary extent')

    def test_sprintf_requires_full_termination_path(self):
        self.rows['0x006404F0']['size']=60
        self.reject('complete own auxiliary extent')

    def test_vsnprintf_requires_full_error_exit(self):
        self.rows['0x006425C3']['code_size']=85
        self.reject('complete own auxiliary extent')

    def test_wide_conversion_requires_full_failure_path(self):
        self.rows['0x0064F1F0']['size']=70
        self.reject('complete own auxiliary extent')

    def test_output_table_cannot_be_omitted(self):
        self.rows['0x006445C4']['embedded_tables']=[]
        self.reject('whole own-AUX eight-entry dispatch table')

    def test_output_table_requires_all_eight_entries(self):
        self.rows['0x006445C4']['embedded_tables'][0]['entries'].pop()
        self.reject('whole own-AUX eight-entry dispatch table')

    def test_output_table_cannot_move_into_code(self):
        self.rows['0x006445C4']['embedded_tables'][0]['offset']=2006
        self.reject('whole own-AUX eight-entry dispatch table')

    def test_table_field_cannot_target_unreviewed_code(self):
        self.rows['0x006445C4']['relocation_bindings'][-1]['code_entry']['owner']='0x00643B2D'
        self.reject('unreviewed actual code entry')

    def test_table_address_cannot_be_code_entry(self):
        self.rows['0x006445C4']['relocation_bindings'][3]['target_kind']='code-entry'
        self.reject('actual defining source owner/entry')

    def test_typed_table_reference_cannot_skip_first_entry(self):
        self.rows['0x006445C4']['relocation_bindings'][3]['local_symbol_offset']=2014
        self.reject('full same-owner table reference')

    def test_one_missing_source_case_field_is_rejected(self):
        self.rows['0x006445C4']['relocation_bindings'].pop()
        self.reject('defining case-entry fields')

    def test_actual_private_helper_source_parent_is_required(self):
        self.rows['0x0064456E']['member_offset']=1
        self.reject('actual defining source owner/entry|defining source parent')

    def test_helper_cannot_be_an_unrelated_global_definition(self):
        self.rows['0x00644517']['source_definition']['storage']=2
        self.reject('actual defining source owner/entry|defining source parent')

    def test_cropzeros_requires_whole_auxiliary_body(self):
        self.m['auxiliary_bodies'][0]['size']=60
        self.reject('complete auxiliary owners')

    def test_noninventoried_auxiliary_cannot_gain_candidate_credit(self):
        self.m['auxiliary_bodies'][1]['decision']='library'
        self.reject('complete auxiliary owners')

    def test_runtime_fp_view_cannot_replace_initial_image_stubs(self):
        self.m['runtime_dispatch']['initial_stub']='0x0064516C'
        self.reject('initial FP stubs')

    def test_all_six_fp_runtime_slots_are_required(self):
        self.m['runtime_dispatch']['slots'].pop()
        self.reject('initialized callback view')

    def test_long_double_slot_preserves_actual_shared_cfltcvt(self):
        self.m['runtime_dispatch']['slots'][5]['symbol']='__cldcvt'
        self.reject('initialized callback view')

    def test_fp_image_table_requires_all_six_stub_fields(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__cfltcvt_tab')['relocations'].pop()
        self.reject('all six fatal stub fields')

    def test_lookup_requires_whole_89_byte_state_and_class_carrier(self):
        next(r for r in self.m['state_data'] if r['symbol']=='___lookuptable')['size']=72
        self.reject('complete defining sections')

    def test_ctype_pointer_carrier_cannot_drop_wide_pointer(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__pctype')['size']=4
        self.reject('complete defining sections')

    def test_complete_ctype_arrays_are_required(self):
        next(r for r in self.m['state_data'] if r['symbol']=='___newctype')['size']=514
        self.reject('complete defining sections')

    def test_null_string_pointer_carrier_requires_narrow_and_wide(self):
        next(r for r in self.m['state_data'] if r['symbol']=='___nullstring')['size']=4
        self.reject('complete defining sections')

    def test_locale_pointer_carrier_cannot_be_a_prefix(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__clocalestr')['size']=84
        self.reject('complete defining sections')

    def test_sdk_va_list_is_actual_four_byte_pointer(self):
        self.m['sdk_layout']['objects'][0]['values'][8]=8
        self.reject('operation/layout controls')

    def test_sdk_double_carrier_is_complete_vendor_struct(self):
        self.m['sdk_layout']['objects'][0]['values'][21]=12
        self.reject('operation/layout controls')

    def test_locale_has_actual_84_byte_layout(self):
        self.m['locale_layout']['objects'][0]['values'][4]=380
        self.reject('independent locale layout')

    def test_thread_locale_slot_is_not_mbcinfo_slot(self):
        self.m['locale_layout']['objects'][0]['values'][3]=96
        self.reject('independent locale layout')

    def test_wide_conversion_uses_actual_mb_cur_max_offset(self):
        self.m['format_protocol']['locale_mb_cur_max_offset']=344
        self.reject('FP/locale protocol')

    def test_variadic_int64_requires_full_eight_byte_advance(self):
        self.m['call_controls'][0]['instructions'][5]['operands']='ecx, 4'
        self.reject('FP/locale protocol')

    def test_fp_control_preserves_caller_twenty_byte_cleanup(self):
        self.m['call_controls'][1]['instructions'][10]['operands']='esp, 0x10'
        self.reject('FP/locale protocol')

    def test_retained_complete_stream_graph_is_required(self):
        self.m['retained_controls']=[]
        self.reject('independently retained')

    def test_complete_output_vendor_source_is_pinned(self):
        self.m['vendor_sources'].pop('crt/src/output.c')
        self.reject('pinned complete vendor sources')

    def test_counting_stream_keeps_null_buffer(self):
        row=self.rows['0x00640548']
        row['instruction_witnesses']=[w for w in row['instruction_witnesses']
            if w['operands']!='dword ptr [ebp - 0x18], 0']
        self.reject('count/helper/locale/wide-conversion witnesses')

    def test_fp_initializer_requires_real_typed_callback_stores(self):
        row=self.graph['0x0064057A']
        row['instruction_witnesses']=[w for w in row['instruction_witnesses']
            if w['operands']!='dword ptr [0x67012c], 0x644dbe']
        self.reject('typed callback stores')

    def test_dispatch_targets_cannot_reach_table_storage(self):
        row=self.rows['0x006445C4']
        fake_table=struct.pack('<8I',*[0x644D9E]*8)
        with self.assertRaisesRegex(ValueError,'actual case instruction starts'):
            REVIEW.check_output_table(row,bytes(2010)+fake_table,[])

if __name__=='__main__':
    unittest.main()
