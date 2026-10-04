import copy
import importlib.util
from pathlib import Path
from types import SimpleNamespace
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('stream_buffer',ROOT/'scripts/verify-stream-buffer-origins.py')
REVIEW=importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)

class StreamBufferOriginTests(unittest.TestCase):
    def setUp(self):
        self.m=REVIEW.manifest()
        self.rows={r['address']:r for r in self.m['functions']}
        self.graph={r['address']:r for r in self.m['functions']+self.m['anchors']}

    def reject(self,message):
        with self.assertRaisesRegex(ValueError,message):
            REVIEW.verify_plan(self.m)

    def test_complete_plan_is_supported(self):
        REVIEW.verify_plan(self.m)

    def test_refill_requires_both_full_success_and_error_paths(self):
        self.rows['0x0065163C']['size']=195
        self.reject('complete own auxiliary extent')

    def test_flush_requires_complete_final_return(self):
        self.rows['0x006443FE']['code_size']=280
        self.reject('complete own auxiliary extent')

    def test_allocator_requires_inline_fallback(self):
        self.rows['0x0064F01B']['size']=40
        self.reject('complete own auxiliary extent')

    def test_pushback_requires_success_flag_update(self):
        self.rows['0x0065171D']['size']=82
        self.reject('complete own auxiliary extent')

    def test_close_requires_full_error_epilog(self):
        self.rows['0x006548B8']['size']=127
        self.reject('complete own auxiliary extent')

    def test_cleanup_cannot_gain_separate_primary_credit(self):
        self.m['functions'].append(self.m['interior_labels'][0])
        self.reject('bounded complete')

    def test_close_cleanup_is_not_scope_head(self):
        self.m['interior_labels'][0]['source_offset']=116
        self.reject('shared entries lose complete source parents')

    def test_scope_cannot_skip_register_restoration(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T20318')['relocations'][0]['code_entry']['source_offset']=119
        self.reject('actual defining source owner/entry')

    def test_scope_cannot_point_at_unreviewed_close_neighbor(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T20318')['relocations'][0]['code_entry']['owner']='0x00654953'
        self.reject('unreviewed actual code entry')

    def test_full_scope_field_is_required(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T20318')['relocations']=[]
        self.reject('pre-label register restoration')

    def test_file_array_requires_all_twenty_records(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__iob')['size']=96
        self.reject('complete defining sections')

    def test_invalid_handle_requires_complete_lock_and_padding_storage(self):
        next(r for r in self.m['state_data'] if r['symbol']=='___badioinfo')['size']=12
        self.reject('complete defining sections')

    def test_initial_stdin_requires_both_buffer_fields(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__iob')['relocations'].pop()
        self.reject('stdin/input-buffer fields')

    def test_stdin_buffer_must_be_actual_complete_common(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__iob')['relocations'][1]['target_address']='0x0068EA44'
        self.reject('stdin/input-buffer fields')

    def test_stdout_stderr_addends_cannot_swap(self):
        [b for b in self.rows['0x006443FE']['relocation_bindings'] if b['symbol']=='__iob'][0]['addend']=64
        self.reject('stdout/stderr array-entry offsets')

    def test_stdin_common_requires_all_4096_bytes(self):
        self.m['common_globals'][2]['size']=512
        self.reject('COMMON/loader definitions')

    def test_input_common_cannot_be_dropped(self):
        self.m['common_globals'].pop()
        self.reject('COMMON/loader definitions')

    def test_handle_table_requires_whole_pointer_array(self):
        self.m['common_globals'][0]['source_definition']['offset']=128
        self.reject('COMMON/loader definitions')

    def test_cflush_is_a_defining_bss_not_common(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__cflush')['source_section']['flags']='0xC0300040'
        self.reject('defining BSS section')

    def test_sdk_file_requires_all_eight_fields(self):
        self.m['sdk_layout']['objects'][0]['values'][5]=28
        self.reject('operation/layout controls')

    def test_sdk_charbuf_is_int_storage_not_a_two_byte_object(self):
        self.m['sdk_layout']['objects'][0]['values'][51]=2
        self.reject('operation/layout controls')

    def test_protocol_cannot_grow_inline_fallback(self):
        self.m['stream_protocol']['fallback_buffer_size']=4
        self.reject('narrow-byte/cdecl protocol')

    def test_byte_control_cannot_be_wide_load(self):
        self.m['call_controls'][0]['instructions'][4]['operands']='eax, word ptr [ecx]'
        self.reject('narrow-byte/cdecl protocol')

    def test_pushback_control_requires_source_typed_callee(self):
        self.m['call_controls'][1]['relocation_metadata'][0]['symbol']='__ungetwc_lk'
        self.reject('narrow-byte/cdecl protocol')

    def test_pushback_control_requires_caller_argument_cleanup(self):
        self.m['call_controls'][1]['instructions'][8]['operands']='esp, 4'
        self.reject('narrow-byte/cdecl protocol')

    def test_complete_read_anchor_cannot_be_a_prefix(self):
        self.m['anchors'][0]['size']=135
        self.reject('independent complete anchors')

    def test_retained_low_io_graph_is_required(self):
        self.m['retained_controls']=[]
        self.reject('independently retained')

    def test_complete_vendor_file_definitions_are_pinned(self):
        self.m['vendor_sources'].pop('crt/src/_file.c')
        self.reject('pinned complete vendor sources')

    def test_actual_cleanup_source_definition_is_read_back(self):
        label=self.m['interior_labels'][0];parent=self.graph[label['parent']]
        definition=copy.deepcopy(label['source_definition']);definition['offset']-=3
        with self.assertRaisesRegex(ValueError,'full-owner defining source symbol'):
            REVIEW.check_interior_entry(label,parent,[definition],
                [SimpleNamespace(address=int(label['address'],16))],[])

    def test_isatty_requires_raw_device_flag_return(self):
        row=self.rows['0x0064F05F']
        row['instruction_witnesses']=[w for w in row['instruction_witnesses']
            if w['operands']!='eax, 0x40']
        self.reject('allocation/EOF/append/string/handle/close witnesses')

    def test_pushback_requires_string_buffer_comparison(self):
        row=self.rows['0x0065171D']
        row['instruction_witnesses']=[w for w in row['instruction_witnesses']
            if w['operands']!='byte ptr [eax], bl']
        self.reject('allocation/EOF/append/string/handle/close witnesses')

    def test_initial_file_array_cannot_discard_later_records(self):
        values=[0x68EA40,0,0x68EA40,257,0,0,4096,0,
                0,0,0,2,1,0,0,0,0,0,0,2,2,0,0,0]+[0]*136
        values[-1]=1
        comparison=SimpleNamespace(pe_bytes_at=lambda target,address,size:struct.pack('<160I',*values))
        with self.assertRaisesRegex(ValueError,'all twenty actual records'):
            REVIEW.check_initial_streams(None,comparison)

if __name__=='__main__':
    unittest.main()
