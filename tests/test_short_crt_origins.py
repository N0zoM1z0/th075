"""Reject incomplete CRT provenance and unsupported short-leaf ownership."""
import csv
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('short_crt_review', ROOT / 'scripts/verify-short-crt-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class ShortCrtTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def test_complete_bounded_plan(self):
        REVIEW.verify_plan(self.m)

    def test_atoi_tail_cannot_be_prefix(self):
        self.m['functions'][0]['size'] -= 1
        self.reject()

    def test_seh_owner_cannot_drop_final_ret(self):
        self.m['functions'][2]['size'] -= 1
        self.reject()

    def test_identical_ordinary_memset_owner_cannot_be_library(self):
        self.m['functions'][3]['decision'] = 'library'
        self.reject()

    def test_finite_sdk_name_cannot_grant_origin(self):
        self.m['functions'][1]['decision'] = 'library'
        self.reject()

    def test_atoi_cannot_bind_itself(self):
        self.m['functions'][0]['bindings'][0]['target_address'] = '0x006426A1'
        self.reject()

    def test_seh_field_cannot_bind_global_unwind(self):
        self.m['functions'][2]['bindings'][0]['symbol'] = '__global_unwind2'
        self.reject()

    def test_wide_formatter_requires_actual_typed_division(self):
        self.m['x64_fields'][0]['target_address'] = '0x00651CA6'
        self.reject()

    def test_original_runtime_provenance_cannot_be_skipped(self):
        self.m['retained_verifiers'].pop()
        self.reject()

    def test_real_sdk_jump_layout_cannot_be_private_observation(self):
        self.m['layout'][3] = 20
        self.reject()

    def test_actual_sdk_header_cannot_disappear(self):
        self.m['headers'].popitem()
        self.reject()

    def test_sdk_owner_cannot_be_smaller_than_its_full_carrier(self):
        self.m['controls'][0]['size'] -= 1
        self.reject()

    def test_carrier_must_keep_eight_byte_source_header(self):
        self.m['carrier']['size'] -= 8
        self.reject()

    def test_seh_owner_requires_actual_carrier_entry(self):
        definition = next(d for d in self.m['carrier']['section']['definitions'] if d['symbol'] == '__seh_longjmp_unwind@4')
        definition['offset'] -= 1
        self.reject()

    def test_saved_try_level_cannot_use_unwind_callback_field(self):
        self.m['functions'][2]['instructions'][3]['operands'] = 'eax, dword ptr [ecx + 0x24]'
        self.reject()

    def test_seh_stack_cleanup_is_actual(self):
        self.m['functions'][2]['instructions'][-1]['operands'] = '8'
        self.reject()

    def test_sdk_finite_cannot_call_unrelated_same_sized_owner(self):
        self.m['controls'][1]['fields'][0]['symbol'] = '_atoi'
        self.reject()

    def test_ordinary_memset_control_cannot_disappear(self):
        self.m['pending_controls'].pop()
        self.reject()

    def test_finite_cannot_compare_only_twenty_byte_prefix(self):
        self.m['pending_controls'][0]['target_size'] = 20
        self.reject()

    def test_independent_atol_requires_complete_body(self):
        self.m['independent'][0]['row']['size'] -= 1
        self.reject()

    def test_library_origin_cannot_grant_private_abi(self):
        row = self.m['functions'][0]
        functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').read_text().splitlines())}
        origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').read_text().splitlines())}
        function = dict(functions[row['address']], signature='int __cdecl atoi(const char*)')
        with self.assertRaises(ValueError):
            REVIEW.check_ledger(row, function, origins[row['address']], evidence_only=True)

    def test_pending_leaf_cannot_gain_library_ledger_credit(self):
        row = self.m['functions'][3]
        functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').read_text().splitlines())}
        origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').read_text().splitlines())}
        origin = dict(origins[row['address']], origin='library', disposition='exclude')
        with self.assertRaises(ValueError):
            REVIEW.check_ledger(row, functions[row['address']], origin, evidence_only=True)
