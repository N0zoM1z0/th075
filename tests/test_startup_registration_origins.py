"""Guard complete registration extents and preserve unresolved startup parents."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('registration', ROOT / 'scripts/verify-startup-registration-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class StartupRegistrationOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = json.loads((ROOT / 'config/startup-registration-origin-evidence.json').read_text())
        self.rows = {r['address']:r for r in self.m['functions']}

    def ledger(self, row):
        return (dict(size=str(row['size']),span_end=row['span_end'],source_file='',match_percent='0.00',
                     owner='library',module='VC71CRT',status='excluded',proposed_name=row['coff_symbol']),
                dict(evidence_id='R121',origin='library',subsystem='VC71CRT',disposition='exclude',confidence=REVIEW.CONFIDENCE))

    def test_onexit_cannot_stop_before_its_finally(self):
        self.rows['0x00641653']['size'] = 50
        with self.assertRaisesRegex(ValueError, 'complete own source extent'):
            REVIEW.verify_plan(self.m)

    def test_msize_cannot_stop_before_its_eh_head(self):
        self.rows['0x00646903']['size'] = 106
        with self.assertRaisesRegex(ValueError, 'complete own source extent'):
            REVIEW.verify_plan(self.m)

    def test_realloc_cannot_omit_its_second_heap_path(self):
        self.rows['0x00646756']['size'] = 369
        with self.assertRaisesRegex(ValueError, 'complete own source extent'):
            REVIEW.verify_plan(self.m)

    def test_atexit_requires_its_complete_onexit_dependency(self):
        self.rows['0x00641653']['decision'] = 'pending'
        with self.assertRaisesRegex(ValueError, 'complete own source extent|unreviewed callee'):
            REVIEW.verify_plan(self.m)

    def test_mtinit_cannot_inherit_credit_from_its_tls_api_slots(self):
        self.rows['0x00646389']['decision'] = 'library'
        with self.assertRaisesRegex(ValueError, 'parents gain ownership'):
            REVIEW.verify_plan(self.m)

    def test_cinit_cannot_inherit_credit_from_reviewed_registration(self):
        self.rows['0x0064411D']['decision'] = 'library'
        with self.assertRaisesRegex(ValueError, 'parents gain ownership'):
            REVIEW.verify_plan(self.m)

    def test_fast_error_exit_rejects_the_console_startup_member(self):
        self.rows['0x006422B2']['member_offset'] = 1655960
        with self.assertRaisesRegex(ValueError, 'source identity'):
            REVIEW.verify_plan(self.m)

    def test_teardown_requires_the_entire_lock_kind_table(self):
        self.m['state_data'][1]['size'] = 8
        with self.assertRaisesRegex(ValueError, 'lock/TLS/FP state'):
            REVIEW.verify_plan(self.m)

    def test_fls_free_slot_cannot_use_an_arbitrary_zero_dword(self):
        self.m['state_data'][4]['target_address'] = '0x0068E32C'
        with self.assertRaisesRegex(ValueError, 'lock/TLS/FP state'):
            REVIEW.verify_plan(self.m)

    def test_msize_preserves_the_earlier_eh_head(self):
        self.m['interior_labels'][1]['eh_source_offset'] = 109
        with self.assertRaisesRegex(ValueError, 'EH entry'):
            REVIEW.verify_plan(self.m)

    def test_realloc_preserves_the_earlier_eh_head(self):
        self.m['interior_labels'][2]['eh_source_offset'] = 360
        with self.assertRaisesRegex(ValueError, 'EH entry'):
            REVIEW.verify_plan(self.m)

    def test_noninventoried_rtc_cannot_gain_a_candidate(self):
        next(r for r in self.m['diagnostic_contexts'] if r['address'] == '0x006496D7')['ledger_size'] = 68
        with self.assertRaisesRegex(ValueError, 'candidate credit'):
            REVIEW.verify_plan(self.m)

    def test_fiber_cleanup_cannot_gain_origin_from_an_interior_slice(self):
        self.m['pending_labels'][0]['decision'] = 'library'
        with self.assertRaisesRegex(ValueError, 'unclosed fiber cleanup'):
            REVIEW.verify_plan(self.m)

    def test_historical_reconciliation_is_limited_to_the_whole_fast_exit(self):
        row = copy.deepcopy(self.rows['0x006422B2'])
        f,o = self.ledger(row)
        row['size'] = 35
        with self.assertRaisesRegex(ValueError, 'source identity'):
            REVIEW.check_historical_startup(row,f,o)

    def test_historical_reconciliation_cannot_waive_an_unrelated_root(self):
        row = self.rows['0x00646166']
        f,o = self.ledger(row)
        with self.assertRaisesRegex(ValueError, 'outside its startup source'):
            REVIEW.check_historical_startup(row,f,o)

    def test_origin_review_cannot_grant_exact_credit(self):
        row = self.rows['0x0064168B']
        f,o = self.ledger(row)
        f['match_percent'] = '100.00'
        with self.assertRaisesRegex(ValueError, 'origin-only extent'):
            REVIEW.check_ledger(row,f,o)


if __name__ == '__main__':
    unittest.main()
