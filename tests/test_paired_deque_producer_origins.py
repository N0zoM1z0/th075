"""Guard complete paired deque ownership without inferring original game types."""
import csv
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('paired_review', ROOT / 'scripts/verify-paired-deque-producer-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class PairedProducerTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def owner(self, address):
        return next(r for r in self.m['code'] if r['address'] == address)

    def test_complete_source_and_independent_context_plan(self):
        REVIEW.verify_plan(self.m)

    def test_full_push_back_cannot_be_prefix(self):
        self.m['functions'][0]['size'] -= 1
        self.reject()

    def test_allocator_root_cannot_drop_ret_cleanup(self):
        next(r for r in self.m['functions'] if r['address'] == '0x00421EE0')['size'] -= 1
        self.reject()

    def test_wrong_pointer_allocator_is_not_same_typed_owner(self):
        row = next(r for r in self.m['functions'] if r['address'] == '0x00421EE0')
        row['symbol'] = row['symbol'].replace('allocator@UQueue', 'allocator@PAUQueue')
        self.reject()

    def test_equal_shape_cannot_bind_other_element_allocator(self):
        self.owner('0x004215F0')['bindings'][1]['target_address'] = '0x0042E000'
        self.reject()

    def test_nontrivial_construct_cannot_bind_flat_copy_operation(self):
        self.owner('0x00421F00')['bindings'][0]['target_address'] = '0x0042E4F0'
        self.reject()

    def test_actual_producer_field_cannot_be_absolute(self):
        self.owner('0x004215F0')['bindings'][0]['type'] = 'DIR32'
        self.reject()

    def test_full_growmap_cannot_be_omitted(self):
        self.m['retained_growth'].pop()
        self.reject()

    def test_complete_copy_owner_cannot_stop_at_provisional_exit(self):
        self.owner('0x00422A50')['size'] = 195
        self.reject()

    def test_complete_insert_cannot_drop_shared_catch_tail(self):
        self.owner('0x00422D70')['size'] = 1483
        self.reject()

    def test_whole_data_carrier_cannot_be_omitted(self):
        self.m['state_data'].pop()
        self.reject()

    def test_whole_eh_registration_cannot_be_omitted(self):
        self.m['retained_frames'].pop()
        self.reject()

    def test_sdk_layout_cannot_replace_twenty_byte_owner_with_pointer(self):
        self.m['layout'][1] = 4
        self.reject()

    def test_original_game_element_sizes_cannot_be_recovered_by_alias(self):
        self.m['layout'][2] = 20
        self.reject()

    def test_actual_source_header_cannot_disappear(self):
        self.m['headers'].popitem()
        self.reject()

    def test_cold_ordinary_emission_cannot_hide_unlinked_probe_carrier(self):
        self.m['emission'].pop()
        self.reject()

    def test_sdk_complete_parent_context_cannot_be_prefix(self):
        self.m['contexts'][0]['size'] -= 1
        self.reject()

    def test_file_scan_must_call_its_actual_producer(self):
        self.m['contexts'][1]['candidate'] = '0x004215F0'
        self.reject()

    def test_external_destructor_declaration_needs_whole_original_policy(self):
        policy = next(r for r in self.m['external'] if r['kind'] == 'independent-authored-policy')
        policy['size'] -= 1
        self.reject()

    def test_declared_policy_cannot_inherit_library_origin(self):
        policy = next(r for r in self.m['external'] if r['kind'] == 'independent-authored-policy')
        policy['record']['decision'] = 'library'
        self.reject()

    def test_actual_weak_alias_requires_real_search_characteristic(self):
        self.m['weak'][0]['search_characteristics'] = 3
        self.reject()

    def test_weak_alias_cannot_gain_a_synthetic_strong_definition(self):
        self.m['weak'][0]['strong_archive_definitions'] = [{'member_offset': 0}]
        self.reject()

    def test_weak_alias_cannot_override_its_whole_strong_owner(self):
        symbol = self.m['weak'][0]['symbol']
        self.m['symbol_targets'][symbol] = '0x00654ACE'
        self.reject()

    def test_complete_typed_runtime_provenance_cannot_be_skipped(self):
        self.m['retained_verifiers'].pop()
        self.reject()

    def test_source_owner_requires_its_actual_primary_definition(self):
        self.owner('0x004215F0')['source_definition']['offset'] += 1
        self.reject()

    def test_source_owner_cannot_be_a_partial_section(self):
        self.owner('0x004215F0')['section']['size'] -= 1
        self.reject()

    def test_library_replay_cannot_grant_exact_or_private_abi(self):
        row = self.m['functions'][0]
        functions = {r['address']: r for r in csv.DictReader((ROOT / 'config/functions.csv').read_text().splitlines())}
        origins = {r['address']: r for r in csv.DictReader((ROOT / 'config/function-origins.csv').read_text().splitlines())}
        function = dict(functions[row['address']], match_percent='100.00')
        with self.assertRaises(ValueError):
            REVIEW.check_ledger(row, function, origins[row['address']], evidence_only=True)
