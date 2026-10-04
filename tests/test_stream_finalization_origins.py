import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    'stream_finalization', ROOT / 'scripts/verify-stream-finalization-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class StreamFinalizationOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.rows = {r['address']: r for r in self.m['functions']}
        self.graph = {r['address']: r for r in self.m['functions'] + self.m['anchors']}
        self.alternative = self.m['source_alternatives'][0]

    def reject(self, message):
        with self.assertRaisesRegex(ValueError, message):
            REVIEW.verify_plan(self.m)

    def remove_witness(self, address, mnemonic, operands):
        row = self.graph[address]
        row['instruction_witnesses'] = [w for w in row['instruction_witnesses']
                                        if (w['mnemonic'], w['operands']) != (mnemonic, operands)]

    def test_complete_plan_is_supported(self):
        REVIEW.verify_plan(self.m)

    def test_freebuf_requires_all_pointer_count_resets_and_return(self):
        self.rows['0x00654953']['size'] = 35
        self.reject('complete own auxiliary extent')

    def test_flush_requires_complete_short_write_and_reset_paths(self):
        self.rows['0x00652588']['code_size'] = 77
        self.reject('complete own auxiliary extent')

    def test_close_requires_flag_reset_after_all_paths(self):
        self.rows['0x00653E01']['size'] = 67
        self.reject('complete own auxiliary extent')

    def test_access_requires_both_returns(self):
        self.rows['0x00641B37']['size'] = 67
        self.reject('complete own auxiliary extent')

    def test_stream_cannot_gain_invented_finally_scope(self):
        self.m['scope_tables'] = [dict(address='0x00653E44')]
        self.reject('unsupported owners/scopes')

    def test_stream_cannot_gain_invented_data_credit(self):
        self.m['state_data'] = [dict(size=4)]
        self.reject('complete defining sections')

    def test_actual_file_tmpfname_offset_is_required(self):
        self.m['sdk_layout']['objects'][0]['values'][10] = 24
        self.reject('operation/layout controls')

    def test_stream_buffer_ownership_masks_are_distinct(self):
        self.m['stream_protocol']['owned_buffer_mask'] = 264
        self.reject('ownership/layout/error/ABI')

    def test_buffer_release_requires_setvbuf_flag_clear(self):
        self.m['stream_protocol']['buffer_release_mask'] = 8
        self.reject('ownership/layout/error/ABI')

    def test_write_requires_three_cdecl_arguments(self):
        self.m['stream_protocol']['write_caller_cleanup'] = 8
        self.reject('ownership/layout/error/ABI')

    def test_access_dos_error_is_not_crt_errno(self):
        self.m['stream_protocol']['access_doserrno'] = 13
        self.reject('ownership/layout/error/ABI')

    def test_runtime_stream_ownership_cannot_be_assumed(self):
        self.m['stream_protocol']['runtime_unknowns'] = 'all buffers and filenames are CRT owned'
        self.reject('ownership/layout/error/ABI')

    def test_complete_freebuf_source_is_required(self):
        self.m['vendor_sources'].pop('crt/src/_freebuf.c')
        self.reject('available source/header context')

    def test_actual_win32_header_is_required(self):
        self.m['sdk_layout']['headers'].pop('PlatformSDK/Include/WinBase.h')
        self.reject('available source/header context')

    def test_retained_stream_handle_heap_error_graph_is_required(self):
        self.m['retained_controls'] = []
        self.reject('independently retained')

    def test_free_control_requires_void_ownership_contract(self):
        self.m['call_controls'][0]['size'] = 60
        self.reject('ownership/layout/error/ABI')

    def test_close_control_requires_real_freebuf_dependency(self):
        self.m['call_controls'][2]['relocation_metadata'][1]['symbol'] = '_free'
        self.reject('ownership/layout/error/ABI')

    def test_narrow_and_wide_controls_require_different_imports(self):
        self.m['call_controls'][-1]['relocation_metadata'][0]['symbol'] = '__imp__GetFileAttributesA@4'
        self.reject('ownership/layout/error/ABI')

    def test_freebuf_requires_inuse_guard(self):
        self.remove_witness('0x00654953', 'test', 'al, 0x83')
        self.reject('actual ownership/flush/close/path/error')

    def test_freebuf_requires_malloc_owned_buffer_guard(self):
        self.remove_witness('0x00654953', 'test', 'al, 8')
        self.reject('actual ownership/flush/close/path/error')

    def test_freebuf_requires_original_flag_mask(self):
        self.remove_witness('0x00654953', 'and', 'word ptr [esi + 0xc], 0xfbf7')
        self.reject('actual ownership/flush/close/path/error')

    def test_flush_requires_positive_byte_count(self):
        self.remove_witness('0x00652588', 'jle', '0x6525d6')
        self.reject('actual ownership/flush/close/path/error')

    def test_flush_requires_full_requested_write_count(self):
        self.remove_witness('0x00652588', 'cmp', 'eax, edi')
        self.reject('actual ownership/flush/close/path/error')

    def test_flush_requires_error_flag_on_short_write(self):
        self.remove_witness('0x00652588', 'or', 'dword ptr [esi + 0xc], 0x20')
        self.reject('actual ownership/flush/close/path/error')

    def test_flush_requires_count_reset_after_errors(self):
        self.remove_witness('0x00652588', 'and', 'dword ptr [esi + 4], 0')
        self.reject('actual ownership/flush/close/path/error')

    def test_close_requires_success_guard_before_filename_free(self):
        self.remove_witness('0x00653E01', 'jge', '0x653e32')
        self.reject('actual ownership/flush/close/path/error')

    def test_close_requires_temp_filename_reset(self):
        self.remove_witness('0x00653E01', 'and', 'dword ptr [esi + 0x1c], 0')
        self.reject('actual ownership/flush/close/path/error')

    def test_access_requires_real_write_mode_bit(self):
        self.remove_witness('0x00641B37', 'test', 'byte ptr [esp + 8], 2')
        self.reject('actual ownership/flush/close/path/error')

    def test_access_requires_both_error_domains(self):
        self.remove_witness('0x00641B37', 'mov', 'dword ptr [eax], 5')
        self.reject('actual ownership/flush/close/path/error')

    def test_access_import_cannot_be_selected_by_masked_similarity(self):
        self.rows['0x00641B37']['relocation_bindings'][0]['symbol'] = '__imp__GetFileAttributesW@4'
        self.reject('actual A/error API identity')

    def test_extra_api_dispatch_is_rejected(self):
        self.rows['0x00641B37']['indirect_calls'].pop()
        self.reject('unsupported indirect dispatch')

    def test_cdecl_stream_return_cannot_pop_the_argument(self):
        self.rows['0x00652588']['body_facts']['returns'][0]['cleanup'] = 4
        self.reject('caller-cleaned returns')

    def test_complete_wide_alternative_is_required(self):
        self.alternative['size'] = 67
        self.reject('independently rejected wide variant')

    def test_wide_variant_requires_actual_independent_import_contradiction(self):
        REVIEW.check_rejected_variant_import(
            self.alternative, {0x0065718C: ('KERNEL32.dll', 'GetFileAttributesA')})
        with self.assertRaisesRegex(ValueError, 'independent PE import contradiction'):
            REVIEW.check_rejected_variant_import(
                self.alternative, {0x0065718C: ('KERNEL32.dll', 'GetFileAttributesW')})

    def test_wide_variant_rejection_requires_original_source_field(self):
        self.alternative['relocation_bindings'][0]['symbol'] = '__imp__GetFileAttributesA@4'
        with self.assertRaisesRegex(ValueError, 'independent PE import contradiction'):
            REVIEW.check_rejected_variant_import(
                self.alternative, {0x0065718C: ('KERNEL32.dll', 'GetFileAttributesA')})


if __name__ == '__main__':
    unittest.main()
