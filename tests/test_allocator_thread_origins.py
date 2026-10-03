"""Guard complete heap extents, defining state and the unresolved allocator/TLS cycle."""
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('allocator_thread', ROOT / 'scripts/verify-allocator-thread-origins.py')
HEAP = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(HEAP)


class AllocatorThreadOriginTests(unittest.TestCase):
    def setUp(self):
        self.manifest = json.loads((ROOT / 'config/allocator-thread-origin-evidence.json').read_text())
        self.rows = {r['address']: r for r in self.manifest['functions']}

    def witness(self, address):
        return next(w for r in self.manifest['functions'] for w in r['instruction_witnesses'] if w['site'] == address)

    def test_heap_allocation_cannot_truncate_its_complete_primary(self):
        self.rows['0x0064428A']['size'] = 111
        with self.assertRaisesRegex(ValueError, 'complete allocation source'):
            HEAP.verify_plan(self.manifest)

    def test_allocation_cleanup_cannot_gain_origin_from_an_interior_slice(self):
        self.manifest['pending_funclets'][0]['decision'] = 'library'
        with self.assertRaisesRegex(ValueError, 'interior cleanup'):
            HEAP.verify_plan(self.manifest)

    def test_calloc_cleanup_preserves_the_earlier_eh_entry(self):
        self.manifest['pending_funclets'][1]['eh_source_offset'] = 170
        with self.assertRaisesRegex(ValueError, 'EH head'):
            HEAP.verify_plan(self.manifest)

    def test_malloc_cannot_inherit_origin_from_reviewed_small_block_children(self):
        self.rows['0x00644331']['decision'] = 'library'
        with self.assertRaisesRegex(ValueError, 'open lock/TLS cycle'):
            HEAP.verify_plan(self.manifest)

    def test_errno_cannot_inherit_origin_from_a_correct_field_offset(self):
        self.rows['0x00647F98']['decision'] = 'library'
        with self.assertRaisesRegex(ValueError, 'open lock/TLS cycle'):
            HEAP.verify_plan(self.manifest)

    def test_small_block_allocator_requires_its_actual_region_callee(self):
        b = next(b for b in self.rows['0x0064B339']['relocation_bindings'] if b['symbol'] == '___sbh_alloc_new_region')
        b['target_address'] = '0x0064428A'
        with self.assertRaisesRegex(ValueError, 'unreviewed callee'):
            HEAP.verify_plan(self.manifest)

    def test_free_dependency_cannot_lose_its_complete_coalescing_body(self):
        self.rows['0x0064A740']['size'] = 541
        with self.assertRaisesRegex(ValueError, 'complete own source identity'):
            HEAP.verify_plan(self.manifest)

    def test_memmove_anchor_keeps_code_and_embedded_switch_data(self):
        next(r for r in self.manifest['anchors'] if r['address'] == '0x00641260')['size'] = 674
        with self.assertRaisesRegex(ValueError, 'complete independently replayed heap anchors'):
            HEAP.verify_plan(self.manifest)

    def test_sdk_layout_requires_the_full_region_and_group_sizes(self):
        self.manifest['sdk_layout']['values'][6] = 324
        with self.assertRaisesRegex(ValueError, 'complete CRT heap/thread layout'):
            HEAP.verify_plan(self.manifest)

    def test_new_handler_cannot_use_an_arbitrary_zero_dword(self):
        self.manifest['state_data'][0]['target_address'] = '0x0068E700'
        with self.assertRaisesRegex(ValueError, 'whole callback/mode/TLS'):
            HEAP.verify_plan(self.manifest)

    def test_exception_table_cannot_compare_only_its_first_record(self):
        self.manifest['state_data'][4]['size'] = 12
        with self.assertRaisesRegex(ValueError, 'whole callback/mode/TLS'):
            HEAP.verify_plan(self.manifest)

    def test_small_block_state_requires_the_real_deferred_group_definition(self):
        self.manifest['common_globals'].pop()
        with self.assertRaisesRegex(ValueError, 'all actual COMMON definitions'):
            HEAP.verify_plan(self.manifest)

    def test_allocator_eh_scope_cannot_point_at_the_later_shared_entry(self):
        self.manifest['scope_tables'][0]['relocations'][0]['target_address'] = '0x006442FC'
        with self.assertRaisesRegex(ValueError, 'actual parent label bindings'):
            HEAP.verify_plan(self.manifest)

    def test_tls_fallback_preserves_ignored_callback_argument_cleanup(self):
        self.witness('0x00646163')['operands'] = ''
        with self.assertRaisesRegex(ValueError, 'heap layout/API/callback/TLS/ABI'):
            HEAP.verify_plan(self.manifest)

    def test_new_handler_passes_the_requested_allocation_size(self):
        self.witness('0x0064EC71')['operands'] = '0'
        with self.assertRaisesRegex(ValueError, 'heap layout/API/callback/TLS/ABI'):
            HEAP.verify_plan(self.manifest)

    def test_thread_allocator_preserves_the_complete_runtime_data_size(self):
        self.witness('0x006461B2')['operands'] = '0x54'
        with self.assertRaisesRegex(ValueError, 'heap layout/API/callback/TLS/ABI'):
            HEAP.verify_plan(self.manifest)

    def test_fls_dispatch_cannot_omit_a_whole_export_literal(self):
        self.manifest['literal_controls'].pop()
        with self.assertRaisesRegex(ValueError, 'whole readonly literal definitions'):
            HEAP.verify_plan(self.manifest)

    def test_origin_review_cannot_grant_source_or_exact_credit(self):
        row = self.rows['0x0064EC68']
        key = row['address']
        f = dict(size='27', span_end=row['span_end'], source_file='src/Handler.cpp', match_percent='100.00')
        with self.assertRaisesRegex(ValueError, 'source or exact credit'):
            HEAP.check_ledger(row, {key: f}, {}, True)


if __name__ == '__main__':
    unittest.main()
