"""Guard whole CRT allocation owners and typed SDK operation provenance."""
import csv
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('allocation_review', ROOT / 'scripts/verify-allocation-api-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class AllocationApiTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def test_complete_plan(self):
        REVIEW.verify_plan(self.m)

    def test_new_owner_cannot_be_prefix(self):
        self.m['functions'][0]['size'] -= 1
        self.reject()

    def test_array_delete_owner_cannot_be_omitted(self):
        self.m['functions'].pop(1)
        self.reject()

    def test_archive_member_cannot_be_substituted(self):
        self.m['functions'][0]['member_offset'] += 1
        self.reject()

    def test_actual_field_cannot_be_masked(self):
        self.m['functions'][0]['bindings'] = []
        self.reject()

    def test_array_new_cannot_recurse_into_itself(self):
        self.m['functions'][2]['bindings'][0]['target_address'] = '0x006416A2'
        self.reject()

    def test_array_delete_cannot_target_array_new(self):
        self.m['functions'][1]['bindings'][0]['target_address'] = '0x006416A2'
        self.reject()

    def test_new_cannot_use_absolute_field(self):
        self.m['functions'][0]['bindings'][0]['type'] = 'DIR32'
        self.reject()

    def test_new_handler_field_offset_is_actual(self):
        self.m['functions'][0]['bindings'][0]['offset'] += 1
        self.reject()

    def test_new_handler_flag_is_observed(self):
        self.m['functions'][0]['instructions'][0]['operands'] = '0'
        self.reject()

    def test_actual_cdecl_input_is_preserved(self):
        self.m['functions'][0]['instructions'][1]['operands'] = 'dword ptr [esp + 4]'
        self.reject()

    def test_new_handler_owner_must_be_complete(self):
        self.m['allocation']['size'] -= 1
        self.reject()

    def test_scalar_delete_owner_must_be_complete(self):
        self.m['scalar_delete']['size'] -= 1
        self.reject()

    def test_sdk_array_operation_cannot_be_scalar(self):
        self.m['controls'][0]['fields'][0]['symbol'] = '??2@YAPAXI@Z'
        self.reject()

    def test_sdk_record_operation_cannot_disappear(self):
        self.m['controls'].pop(2)
        self.reject()

    def test_entire_sdk_data_carrier_is_required(self):
        self.m['sections'].pop(0)
        self.reject()

    def test_observation_layout_cannot_claim_other_record_size(self):
        self.m['layout'][2] = 16
        self.reject()

    def test_retained_game_and_runtime_provenance_cannot_be_skipped(self):
        self.m['retained_verifiers'].pop()
        self.reject()

    def test_library_acceptance_cannot_grant_exact_credit(self):
        functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').read_text().splitlines())}
        origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').read_text().splitlines())}
        row = self.m['functions'][0]
        function = dict(functions[row['address']], match_percent='100.00')
        with self.assertRaises(ValueError):
            REVIEW.check_ledger(row, function, origins[row['address']], evidence_only=True)
