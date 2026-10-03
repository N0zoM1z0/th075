"""Reject partial locale defaults, guessed layouts and callback label credit."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('locale_thread',ROOT/'scripts/verify-locale-thread-origins.py')
REVIEW=importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class LocaleThreadOriginTests(unittest.TestCase):
    def setUp(self):
        self.m=json.loads((ROOT/'config/locale-thread-origin-evidence.json').read_text())
        self.rows={r['address']:r for r in self.m['functions']}

    def ledger(self,row):
        return (dict(size=str(row['size']),span_end=row['span_end'],source_file='',match_percent='0.00',
                     owner='library',module='VC71CRT',status='excluded',proposed_name=row['coff_symbol']),
                dict(evidence_id='R122',origin='library',subsystem='VC71CRT',disposition='exclude',confidence=REVIEW.CONFIDENCE))

    def test_time_cleanup_requires_all_unrolled_fields(self):
        self.rows['0x0064C5C6']['size']=267
        with self.assertRaisesRegex(ValueError,'complete own source extent'):
            REVIEW.verify_plan(self.m)

    def test_locale_cleanup_requires_its_actual_children(self):
        self.rows['0x0064CA47']['decision']='pending'
        with self.assertRaisesRegex(ValueError,'complete own source extent|unreviewed callee'):
            REVIEW.verify_plan(self.m)

    def test_thread_initializer_requires_complete_fiber_callback(self):
        self.m['auxiliary_bodies'][0]['size']=301
        with self.assertRaisesRegex(ValueError,'whole non-inventoried callback'):
            REVIEW.verify_plan(self.m)

    def test_callback_cannot_be_added_as_an_inventoried_candidate(self):
        self.m['auxiliary_bodies'][0]['ledger_size']=327
        with self.assertRaisesRegex(ValueError,'candidate credit'):
            REVIEW.verify_plan(self.m)

    def test_multibyte_initializer_cannot_inherit_locale_origin(self):
        self.rows['0x006504F9']['decision']='library'
        with self.assertRaisesRegex(ValueError,'unclosed multibyte initializer'):
            REVIEW.verify_plan(self.m)

    def test_multibyte_context_cannot_stop_before_cleanup(self):
        self.m['diagnostic_contexts'][0]['size']=327
        with self.assertRaisesRegex(ValueError,'complete codepage context'):
            REVIEW.verify_plan(self.m)

    def test_fiber_cleanup_preserves_the_earlier_eh_head(self):
        self.m['interior_labels'][0]['eh_source_offset']=306
        with self.assertRaisesRegex(ValueError,'earlier EH heads'):
            REVIEW.verify_plan(self.m)

    def test_fiber_cleanup_cannot_gain_standalone_source(self):
        self.m['interior_labels'][1]['extent_basis']='function-auxiliary-record'
        with self.assertRaisesRegex(ValueError,'standalone source'):
            REVIEW.verify_plan(self.m)

    def test_default_lconv_cannot_compare_one_pointer(self):
        next(r for r in self.m['state_data'] if r['symbol']=='___lconv_static_decimal')['size']=4
        with self.assertRaisesRegex(ValueError,'defining data|whole locale defaults'):
            REVIEW.verify_plan(self.m)

    def test_ctype_cannot_compare_only_the_pctype_tail(self):
        next(r for r in self.m['state_data'] if r['symbol']=='___newctype')['size']=514
        with self.assertRaisesRegex(ValueError,'defining data|whole locale defaults'):
            REVIEW.verify_plan(self.m)

    def test_locale_time_defaults_require_all_literals(self):
        self.m['literal_controls'].pop(0)
        with self.assertRaisesRegex(ValueError,'defining data'):
            REVIEW.verify_plan(self.m)

    def test_common_reference_count_requires_real_storage(self):
        self.m['common_globals'][0]['target_address']='0x0068FA54'
        with self.assertRaisesRegex(ValueError,'COMMON state'):
            REVIEW.verify_plan(self.m)

    def test_thread_layout_cannot_guess_locale_pointer_at_end(self):
        self.m['sdk_layout']['values'][9]=136
        with self.assertRaisesRegex(ValueError,'natural CRT locale/thread layout'):
            REVIEW.verify_plan(self.m)

    def test_multibyte_layout_requires_entire_case_map(self):
        self.m['sdk_layout']['values'][10]=285
        with self.assertRaisesRegex(ValueError,'natural CRT locale/thread layout'):
            REVIEW.verify_plan(self.m)

    def test_time_layout_requires_reference_count_offset(self):
        self.m['sdk_layout']['values'][52]=176
        with self.assertRaisesRegex(ValueError,'natural CRT locale/thread layout'):
            REVIEW.verify_plan(self.m)

    def test_historical_parent_reconciliation_rejects_changed_source(self):
        row=copy.deepcopy(self.rows['0x00646389']);f,o=self.ledger(row);row['body_sha256']='0'*64
        with self.assertRaisesRegex(ValueError,'source identity'):
            REVIEW.check_historical_root(row,f,o)

    def test_historical_parent_reconciliation_cannot_waive_other_roots(self):
        row=self.rows['0x00642B09'];f,o=self.ledger(row)
        with self.assertRaisesRegex(ValueError,'outside its source parent'):
            REVIEW.check_historical_root(row,f,o)

    def test_origin_review_cannot_grant_exact_credit(self):
        row=self.rows['0x00646389'];f,o=self.ledger(row);f['match_percent']='100.00'
        with self.assertRaisesRegex(ValueError,'origin-only extent'):
            REVIEW.check_ledger(row,f,o)


if __name__=='__main__':
    unittest.main()
