"""Guard independent script map policy, complete owners and actual game use."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('script_policy', ROOT / 'scripts/verify-script-count-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class ScriptCountTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def change(self, windows, mnemonic, old, new):
        row = next(r for w in windows for r in w if r['mnemonic'] == mnemonic and r['operands'] == old)
        row['operands'] = new

    def test_complete_independent_policy(self):
        REVIEW.verify_plan(self.m)

    def test_partial_count_body_is_rejected(self):
        self.m['functions'][0]['size'] -= 1
        self.reject()

    def test_cold_observation_does_not_grant_game_source(self):
        self.m['functions'][0]['source_file'] = 'probes/VC7NestedDequeSizeContexts.cpp'
        self.reject()

    def test_missing_map_zero_is_actual_policy(self):
        self.change([self.m['functions'][0]['instructions']], 'xor', 'ax, ax', 'eax, eax')
        self.reject()

    def test_map_lookup_must_preserve_signed_width(self):
        self.change([self.m['functions'][0]['instructions']], 'movsx', 'edx, word ptr [ecx + eax*2]', 'edx, byte ptr [ecx + eax]')
        self.reject()

    def test_returned_inner_receiver_is_required(self):
        self.change([self.m['functions'][0]['instructions']], 'mov', 'ecx, eax', 'ecx, edx')
        self.reject()

    def test_actual_abi_cannot_drop_stack_argument(self):
        self.change([self.m['functions'][0]['instructions']], 'ret', '4', '')
        self.reject()

    def test_independent_parser_cannot_be_omitted(self):
        self.m['anchors'].pop(3)
        self.reject()

    def test_prior_game_origin_cannot_be_reassigned(self):
        self.m['anchors'][4]['evidence']['evidence_id'] = 'R152'
        self.reject()

    def test_initializer_cannot_use_different_domain(self):
        self.change([self.m['instruction_windows'][0]['instructions']], 'cmp', 'dword ptr [ebp - 0x10], 0x3e8', 'dword ptr [ebp - 0x10], 0x400')
        self.reject()

    def test_missing_sentinel_cannot_be_zero_initialized(self):
        self.change([self.m['instruction_windows'][0]['instructions']], 'mov', 'word ptr [edx + ecx*2], 0xffff', 'word ptr [edx + ecx*2], 0')
        self.reject()

    def test_parser_write_must_derive_actual_outer_index(self):
        self.change([self.m['instruction_windows'][2]['instructions']], 'sub', 'eax, 1', 'eax, 2')
        self.reject()

    def test_decimal_label_cannot_be_binary_accumulation(self):
        self.change([self.m['instruction_windows'][3]['instructions']], 'imul', 'ecx, ecx, 0xa', 'ecx, ecx, 2')
        self.reject()

    def test_game_receiver_cannot_be_unrelated_field(self):
        self.change([self.m['instruction_windows'][4]['instructions']], 'add', 'ecx, 0x714', 'ecx, 0x718')
        self.reject()

    def test_game_loop_cannot_use_unsigned_eax_result(self):
        self.change([self.m['instruction_windows'][4]['instructions']], 'movsx', 'eax, ax', 'eax, al')
        self.reject()

    def test_one_game_caller_does_not_replace_all_context(self):
        self.m['instruction_windows'].pop()
        self.reject()

    def test_observed_domain_is_not_an_input_bounds_guarantee(self):
        self.m['observed_policy']['input_bounds_checked'] = True
        self.reject()

    def test_full_retained_cold_source_is_required(self):
        self.m['retained_verifier'] = 'verify-authored-origins.py'
        self.reject()

    def test_missing_authored_extent_record_is_rejected(self):
        with self.assertRaises(ValueError):
            REVIEW.check_authored_record(self.m['functions'][0], [])

    def test_duplicate_authored_extent_records_are_rejected(self):
        r = self.m['functions'][0]
        row = dict(address=REVIEW.KEY, size='66', body_sha256=r['body_sha256'], inferred_role=r['inferred_role'],
                   return_count='1', internal_branch_count='2', external_branch_count='0', evidence_id='R152')
        REVIEW.check_authored_record(r, [row])
        with self.assertRaises(ValueError):
            REVIEW.check_authored_record(r, [row, row])
