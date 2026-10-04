"""Reject incomplete initializer callbacks, IO carriers and overlapping cleanup credit."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('initializer_startup', ROOT / 'scripts/verify-initializer-startup-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class InitializerStartupOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = json.loads((ROOT / 'config/initializer-startup-origin-evidence.json').read_text())
        self.rows = {r['address']: r for r in self.m['functions']}

    def reject(self, text):
        with self.assertRaisesRegex(ValueError, text):
            REVIEW.verify_plan(self.m)

    def ledger(self, row):
        return (dict(size=str(row['size']), span_end=row['span_end'], source_file='', match_percent='0.00',
                     owner='library', module='VC71CRT', status='excluded', proposed_name=row['coff_symbol']),
                dict(evidence_id='R125', origin='library', subsystem='VC71CRT', disposition='exclude', confidence=REVIEW.CONFIDENCE))

    def test_cinit_requires_complete_xc_loop_and_return(self):
        self.rows['0x0064411D']['size'] = 69
        self.reject('whole own auxiliary extent')

    def test_ioinit_requires_all_error_and_cleanup_paths(self):
        self.rows['0x00649449']['code_size'] = 490
        self.reject('whole own auxiliary extent')

    def test_abort_requires_its_real_terminal_trap(self):
        self.rows['0x00650517']['size'] = 23
        self.reject('whole own auxiliary extent')

    def test_callee_cannot_be_substituted_by_a_name(self):
        b = next(b for b in self.rows['0x0064654C']['relocation_bindings'] if b['target_kind'] == 'callee')
        b['symbol'] = '?unreviewed_terminate'
        self.reject('unreviewed actual code/callback')

    def test_auxiliary_initstdio_cannot_gain_candidate_credit(self):
        self.m['auxiliary_bodies'][0]['ledger_size'] = 169
        self.reject('fabricated candidates')

    def test_raise_cleanup_retains_earlier_eh_head(self):
        self.m['interior_labels'][0]['eh_source_offset'] = 315
        self.reject('earlier EH head')

    def test_cleanup_cannot_become_a_standalone_function(self):
        self.m['interior_labels'][0]['extent_basis'] = 'function-auxiliary-record'
        self.reject('actual shared entry')

    def test_iob_requires_all_twenty_file_records(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__iob')['size'] = 96
        self.reject('whole initializer state|prefixes')

    def test_exception_table_requires_counts_as_well_as_records(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__XcptActTab')['size'] = 120
        self.reject('whole initializer state|prefixes')

    def test_signal_actions_require_entire_defining_section(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '_ctrlc_action')['size'] = 16
        self.reject('whole initializer state|prefixes')

    def test_pioinfo_requires_all_sixty_four_pointers(self):
        next(r for r in self.m['common_globals'] if r['symbol'] == '___pioinfo')['size'] = 128
        self.reject('whole defining arrays')

    def test_stdin_buffer_requires_full_common_definition(self):
        row = next(r for r in self.m['common_globals'] if r['symbol'] == '__bufin')
        definition = copy.deepcopy(row['source_definition']); definition['offset'] = 512
        with self.assertRaisesRegex(ValueError, 'complete defining object'):
            REVIEW.check_common(row, definition)

    def test_common_cannot_be_an_undefined_reference(self):
        row = self.m['common_globals'][0]; definition = copy.deepcopy(row['source_definition']); definition['offset'] = 0
        with self.assertRaisesRegex(ValueError, 'complete defining object'):
            REVIEW.check_common(row, definition)

    def test_xi_callback_source_cell_requires_actual_coff_symbol(self):
        self.m['initializer_registrations'][0]['relocations'][0]['symbol'] = '_unreviewed_initializer'
        self.reject('real complete callback')

    def test_registration_cannot_replace_a_whole_defining_cell(self):
        self.m['initializer_registrations'][0]['relocations'] = []
        self.reject('incomplete typed callback')

    def test_cxx_registration_cannot_remain_unreviewed(self):
        self.m['auxiliary_bodies'][1]['decision'] = 'pending'
        self.reject('fabricated candidates')

    def test_rtc_initializer_range_cannot_hide_a_callback(self):
        self.m['callback_ranges'][-1]['entries'][0] = '0x0064232C'
        self.reject('unreviewed actual callback')

    def test_xc_requires_every_independent_compiler_wrapper(self):
        self.m['compiler_callbacks'].pop()
        self.reject('compiler-emission provenance')

    def test_ioinfo_stride_cannot_be_guessed(self):
        self.m['sdk_layout']['values'][0] = 32
        self.reject('natural IO/thread/exception')

    def test_startupinfo_reserved_buffer_requires_actual_offset(self):
        self.m['sdk_layout']['values'][35] = 48
        self.reject('natural IO/thread/exception')

    def test_terminate_requires_real_thread_callback_offset(self):
        self.m['sdk_layout']['values'][42] = 104
        self.reject('natural IO/thread/exception')

    def test_exception_record_requires_actual_information_offset(self):
        self.m['sdk_layout']['values'][62] = 16
        self.reject('natural IO/thread/exception')

    def test_historical_cinit_rejects_changed_fields(self):
        row = copy.deepcopy(self.rows['0x0064411D']); f, o = self.ledger(row)
        row['relocation_bindings'][0]['addend'] = 4
        with self.assertRaisesRegex(ValueError, 'relocation provenance'):
            REVIEW.check_historical_root(row, f, o)

    def test_historical_guard_cannot_waive_unrelated_parents(self):
        row = self.rows['0x00649449']; f, o = self.ledger(row)
        with self.assertRaisesRegex(ValueError, 'outside cinit'):
            REVIEW.check_historical_root(row, f, o)

    def test_origin_review_cannot_grant_exact_credit(self):
        row = self.rows['0x0064411D']; f, o = self.ledger(row); f['match_percent'] = '100.00'
        with self.assertRaisesRegex(ValueError, 'origin-only extent'):
            REVIEW.check_ledger(row, f, o)


if __name__ == '__main__':
    unittest.main()
