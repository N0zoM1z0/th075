import copy
import importlib.util
from pathlib import Path
from types import SimpleNamespace
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('low_io',ROOT/'scripts/verify-low-io-origins.py')
REVIEW=importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)

class LowIoOriginTests(unittest.TestCase):
    def setUp(self):
        self.m=REVIEW.manifest()
        self.rows={r['address']:r for r in self.m['functions']}
        self.graph={r['address']:r for r in self.m['functions']+self.m['anchors']}

    def reject(self,message):
        with self.assertRaisesRegex(ValueError,message):
            REVIEW.verify_plan(self.m)

    def test_complete_plan_is_supported(self):
        REVIEW.verify_plan(self.m)

    def test_lock_requires_entire_exceptional_tail(self):
        self.rows['0x006520A7']['size']=148
        self.reject('complete own auxiliary extent')

    def test_read_requires_entire_translation_body(self):
        self.rows['0x006538A6']['code_size']=300
        self.reject('complete own auxiliary extent')

    def test_write_requires_both_binary_and_text_paths(self):
        self.rows['0x0064EDA2']['size']=200
        self.reject('complete own auxiliary extent')

    def test_seek_requires_all_failure_and_success_exits(self):
        self.rows['0x0064EC83']['size']=50
        self.reject('complete own auxiliary extent')

    def test_int64_seek_cannot_be_32_bit_prefix(self):
        self.rows['0x006523AC']['size']=116
        self.reject('complete own auxiliary extent')

    def test_close_requires_standard_stream_alias_paths(self):
        self.rows['0x00654835']['code_size']=80
        self.reject('complete own auxiliary extent')

    def test_cleanup_cannot_be_separate_primary(self):
        self.m['functions'].append(self.m['interior_labels'][0])
        self.reject('bounded complete')

    def test_cleanup_cannot_start_at_scope_stack_adjustment(self):
        self.m['interior_labels'][0]['source_offset']=132
        self.reject('shared entries lose complete source parents')

    def test_lock_cleanup_cannot_discard_three_byte_stack_adjustment(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T20252')['relocations'][0]['code_entry']['source_offset']=151
        self.reject('actual defining source owner/entry')

    def test_wrapper_scope_cannot_point_at_normal_cleanup_subentry(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T20664')['relocations'][0]['code_entry']['source_offset']=135
        self.reject('actual defining source owner/entry')

    def test_scope_cannot_point_at_unreviewed_code(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T20378')['relocations'][0]['code_entry']['owner']='0x00652588'
        self.reject('unreviewed actual code entry')

    def test_complete_scope_field_is_required(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T20377')['relocations']=[]
        self.reject('pre-label stack adjustment')

    def test_all_45_error_entries_are_required(self):
        next(r for r in self.m['state_data'] if r['symbol']=='_errtable')['size']=352
        self.reject('complete defining sections')

    def test_error_order_and_duplicate_os_code_are_preserved(self):
        self.m['error_table_values'][60]=124
        self.reject('full ordered 45-entry table')

    def test_handle_common_requires_whole_64_pointer_array(self):
        self.m['common_globals'][0]['size']=128
        self.reject('COMMON/loader definitions')

    def test_handle_count_common_cannot_be_dropped(self):
        self.m['common_globals'].pop()
        self.reject('COMMON/loader definitions')

    def test_common_source_size_is_not_runtime_initialization(self):
        self.m['common_globals'][0]['source_definition']['offset']=4
        self.reject('COMMON/loader definitions')

    def test_sdk_layout_requires_actual_36_byte_ioinfo(self):
        self.m['sdk_layout']['objects'][0]['values'][4]=32
        self.reject('operation/layout controls')

    def test_sdk_layout_requires_doserrno_thread_offset(self):
        self.m['sdk_layout']['objects'][0]['values'][19]=8
        self.reject('operation/layout controls')

    def test_int64_control_requires_both_return_registers(self):
        self.m['call_controls'][0]['instructions'].pop(3)
        self.reject('handle/thread/int64 protocol')

    def test_handle_protocol_cannot_use_32_byte_stride(self):
        self.m['io_protocol']['ioinfo_size']=32
        self.reject('handle/thread/int64 protocol')

    def test_unknown_auxiliary_cannot_gain_inventory_credit(self):
        self.m['auxiliary_bodies'].append(copy.deepcopy(self.m['functions'][0]))
        self.reject('complete auxiliary owners')

    def test_application_state_requires_full_two_word_carrier(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__aexit_rtn')['size']=4
        self.reject('complete defining sections')

    def test_application_state_cannot_pick_first_archive_definition(self):
        self.m['definition_choices'][0]['selected_member_offset']=1655960
        self.reject('GUI defining parent/alternatives')

    def test_all_five_strong_app_type_alternatives_are_retained(self):
        self.m['definition_choices'][0]['alternatives'].pop()
        self.reject('GUI defining parent/alternatives')

    def test_application_state_retains_actual_exit_pointer(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__aexit_rtn')['relocations']=[]
        self.reject('actual GUI owner and exit pointer')

    def test_startup_anchor_requires_actual_source_member(self):
        self.m['anchors'][0]['member_offset']=1655960
        self.reject('independent complete anchors')

    def test_retained_complete_io_initialization_graph_is_required(self):
        self.m['retained_controls']=[]
        self.reject('independently retained')

    def test_complete_vendor_source_files_are_pinned(self):
        self.m['vendor_sources'].pop('crt/src/lseeki64.c')
        self.reject('pinned complete vendor sources')

    def test_full_owner_cleanup_definition_is_read_back(self):
        label=self.m['interior_labels'][3];parent=self.graph[label['parent']]
        definition=copy.deepcopy(label['source_definition']);definition['offset']-=3
        with self.assertRaisesRegex(ValueError,'full-owner defining source symbol'):
            REVIEW.check_interior_entry(label,parent,[definition],
                [SimpleNamespace(address=int(label['address'],16))],[])

    def test_binary_write_cannot_lose_text_append_policy(self):
        row=self.rows['0x0064EDA2']
        row['instruction_witnesses']=[w for w in row['instruction_witnesses']
            if w['operands']!='byte ptr [eax + esi + 4], 0x20']
        self.reject('error/seek/text/alias/lock witnesses')

    def test_read_must_preserve_control_z_eof(self):
        row=self.rows['0x006538A6']
        row['instruction_witnesses']=[w for w in row['instruction_witnesses']
            if w['operands']!='al, 0x1a']
        self.reject('error/seek/text/alias/lock witnesses')

if __name__=='__main__':
    unittest.main()
