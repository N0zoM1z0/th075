"""Prevent partial or incorrectly typed script record lifetime acceptance."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('buffer_review', ROOT / 'scripts/verify-script-buffer-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class ScriptBufferTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def test_complete_typed_lifetime_plan(self):
        REVIEW.verify_plan(self.m)

    def test_constructor_prefix_is_not_complete(self):
        self.m['functions'][0]['size'] -= 1
        self.reject()

    def test_array_destructor_cannot_be_scalar_shape(self):
        self.m['families'][0]['destructor']['fields'][0]['symbol'] = '??3@YAXPAX@Z'
        self.reject()

    def test_whole_dereference_field_cannot_move(self):
        self.m['families'][0]['destructor']['fields'][0]['offset'] += 1
        self.reject()

    def test_full_array_delete_thunk_is_required(self):
        self.m['runtime']['size'] -= 1
        self.reject()

    def test_typed_array_delete_cannot_bind_itself(self):
        self.m['runtime']['bindings'][0]['target_address'] = '0x0064169D'
        self.reject()

    def test_independent_free_owner_cannot_be_prefix(self):
        self.m['runtime']['free']['size'] -= 1
        self.reject()

    def test_equal_scalar_shape_still_needs_distinct_typed_destination(self):
        next(r for r in self.m['rejected'] if r['symbol'] == '??1ScalarRecord@@QAE@XZ')['typed_difference'] = 0
        self.reject()

    def test_rejected_sdk_alternative_cannot_disappear(self):
        self.m['rejected'].pop(0)
        self.reject()

    def test_implicit_and_inline_profiles_are_required(self):
        self.m['profiles'].pop()
        self.reject()

    def test_ordinary_source_function_cannot_be_omitted(self):
        self.m['profiles'][0]['functions'].pop()
        self.reject()

    def test_compiler_eh_carrier_cannot_be_unchecked(self):
        self.m['profiles'][0]['sections'].pop()
        self.reject()

    def test_full_sdk_layout_cannot_be_prefix(self):
        self.m['layout'].pop()
        self.reject()

    def test_original_parser_origin_cannot_be_reassigned(self):
        self.m['parser']['evidence']['evidence_id'] = 'R153'
        self.reject()

    def test_actual_pointer_store_must_remain_at_observed_field(self):
        row = next(r for r in self.m['parser']['pointer_window'] if r['operands'] == 'dword ptr [eax + 4], edx')
        row['operands'] = 'dword ptr [eax + 8], edx'
        self.reject()

    def test_actual_terminated_buffer_policy_is_required(self):
        self.m['parser']['pointer_window'][-1]['operands'] = 'word ptr [edx + ecx], 0'
        self.reject()

    def test_original_unwind_owners_are_preserved(self):
        self.m['cleanup_entries'].pop()
        self.reject()

    def test_deleting_destructor_cannot_target_other_lifetime(self):
        self.m['scalar_deleting']['destructor_address'] = '0x004212A0'
        self.reject()

    def test_local_constructor_and_release_must_use_same_record(self):
        self.m['parser']['lifetime_pairs'][0]['release'][0]['operands'] = 'ecx, [ebp - 0x2c]'
        self.reject()

    def test_all_eight_real_local_lifetimes_are_required(self):
        self.m['parser']['lifetime_pairs'].pop()
        self.reject()

    def test_byte_record_producer_does_not_establish_raw_byte_element(self):
        self.m['parser']['producer']['coff_symbol'] = self.m['parser']['producer']['coff_symbol'].replace('DequeProbeRecord@$07', 'DequeProbeRecord@$00')
        self.reject()

    def test_missing_authored_body_records_are_rejected(self):
        with self.assertRaises(ValueError):
            REVIEW.check_authored_records(self.m, [])

    def test_duplicate_authored_body_records_are_rejected(self):
        rows = [dict(address=r['address'], size=str(r['size']), body_sha256=r['body_sha256'],
                     inferred_role=r['inferred_role'], return_count='1',
                     internal_branch_count=str(r['internal_branch_count']), external_branch_count='0', evidence_id='R153')
                for r in self.m['functions']]
        REVIEW.check_authored_records(self.m, rows)
        with self.assertRaises(ValueError):
            REVIEW.check_authored_records(self.m, rows + rows[:1])
