"""Reject partial PE startup provenance and invented game/vendor ownership."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('environment_startup', ROOT / 'scripts/verify-environment-startup-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class EnvironmentStartupOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.rows = {r['address']: r for r in self.m['functions']}

    def reject(self, text):
        with self.assertRaisesRegex(ValueError, text):
            REVIEW.verify_plan(self.m)

    def ledger(self, row):
        return (dict(size=str(row['size']), span_end=row['span_end'], source_file='', match_percent='0.00',
                     owner='library', module='VC71CRT', status='excluded', proposed_name=row['coff_symbol']),
                dict(evidence_id='R126', origin='library', subsystem='VC71CRT', disposition='exclude', confidence=REVIEW.CONFIDENCE))

    def test_entry_retains_local_exception_filter_handler_and_return(self):
        self.rows['0x0064232C']['size'] = 395
        self.reject('whole own auxiliary extent')

    def test_complete_standard_parser_cannot_be_wildcard_alternative(self):
        self.rows['0x00649119']['size'] = 405
        self.reject('whole own auxiliary extent')

    def test_environment_retains_ansi_fallback_and_both_cleanup_exits(self):
        self.rows['0x00649327']['code_size'] = 180
        self.reject('whole own auxiliary extent')

    def test_exception_filter_retains_fpe_and_optional_handler_paths(self):
        self.rows['0x00648E76']['code_size'] = 335
        self.reject('whole own auxiliary extent')

    def test_known_children_cannot_replace_an_unreviewed_parent(self):
        b = next(b for b in self.rows['0x0064232C']['relocation_bindings'] if b['target_kind'] == 'callee')
        b['target_address'] = '0x00423B20'
        self.reject('unreviewed actual complete callee')

    def test_chkstk_requires_real_same_source_alloca_alias(self):
        next(r for r in self.m['anchors'] if r['address'] == '0x00642510')['source_aliases'] = []
        self.reject('unreviewed actual complete callee')

    def test_game_entry_cannot_inherit_vendor_ownership(self):
        self.m['game_entry']['origin'] = 'library'
        self.reject('cannot infer game entry')

    def test_game_entry_requires_actual_stdcall_cleanup(self):
        self.m['game_entry']['body_facts']['returns'][0]['cleanup'] = 0
        self.reject('cannot infer game entry')

    def test_game_call_requires_typed_actual_symbol_and_field(self):
        next(b for b in self.rows['0x0064232C']['relocation_bindings'] if b['target_kind'] == 'authored-entry')['symbol'] = '_WinMain'
        self.reject('typed stdcall provenance')

    def test_program_name_requires_full_261_byte_definition(self):
        next(r for r in self.m['state_data'] if 'pgmname' in r['symbol'])['size'] = 260
        self.reject('convenient prefixes')

    def test_environment_pointer_cannot_be_a_four_byte_section_prefix(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__aenvptr')['size'] = 4
        self.reject('convenient prefixes')

    def test_exception_carrier_requires_counts_after_ten_records(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__XcptActTab')['size'] = 120
        self.reject('convenient prefixes')

    def test_mbctype_requires_whole_257_element_common(self):
        next(r for r in self.m['common_globals'] if r['symbol'] == '__mbctype')['size'] = 256
        self.reject('full actual COMMON')

    def test_common_cannot_be_an_undefined_reference(self):
        row = self.m['common_globals'][0]
        definition = copy.deepcopy(row['source_definition']); definition['offset'] = 0
        with self.assertRaisesRegex(ValueError, 'complete defining object'):
            REVIEW.check_common(row, definition)

    def test_c_exit_cannot_gain_fabricated_inventory_credit(self):
        self.m['auxiliary_bodies'][0]['ledger_size'] = 15
        self.reject('fabricated candidate')

    def test_eh_scope_requires_both_local_filter_and_handler(self):
        self.m['scope_tables'][0]['relocations'].pop()
        self.reject('full EH scope')

    def test_pe32_plus_managed_directory_offset_cannot_follow_pe32(self):
        self.m['sdk_layout']['values'][32] = 232
        self.reject('PE32/PE32\+')

    def test_version_info_requires_actual_sdk_layout(self):
        self.m['sdk_layout']['values'][8] = 144
        self.reject('natural PE32')

    def test_matching_startup_requires_actual_defining_member(self):
        self.m['definition_choices'][1]['selected_member_offset'] = 1655960
        self.reject('matching root definition')

    def test_rejected_parser_does_not_become_accepted_by_prefix(self):
        self.m['rejected_alternatives'][0]['size'] = 364
        self.reject('rejected wildcard parser')

    def test_frozen_r114_entry_requires_all_original_fields(self):
        old = next(r for r in json.loads((ROOT / 'config/queue-lifetime-origin-evidence.json').read_text())['functions'] if r['address'] == '0x0064232C')
        f, o = self.ledger(self.rows[old['address']])
        old['archive_source']['relocations'][0]['addend'] = 4
        with self.assertRaisesRegex(ValueError, 'relocation provenance'):
            REVIEW.check_historical_root(old, f, o)

    def test_frozen_r115_context_requires_complete_entry(self):
        old = json.loads((ROOT / 'config/startup-dependency-origin-evidence.json').read_text())['entry_context']
        f, o = self.ledger(self.rows[old['address']]); old['body_facts']['returns'].pop()
        with self.assertRaisesRegex(ValueError, 'whole context differs'):
            REVIEW.check_historical_context(old, f, o)

    def test_reconciliation_cannot_accept_unrelated_historical_root(self):
        row = self.rows['0x00649119']; f, o = self.ledger(row)
        with self.assertRaisesRegex(ValueError, 'outside its frozen pending roots'):
            REVIEW.check_historical_root(row, f, o)

    def test_origin_comparison_cannot_earn_exact_credit(self):
        row = self.rows['0x0064232C']; f, o = self.ledger(row); f['match_percent'] = '100.00'
        with self.assertRaisesRegex(ValueError, 'origin-only extent'):
            REVIEW.check_ledger(row, f, o)
