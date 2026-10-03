"""Reject truncated codepage arrays, incomplete EH parents and inherited origin."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('codepage_nls',ROOT/'scripts/verify-codepage-nls-origins.py')
REVIEW=importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class CodePageNlsOriginTests(unittest.TestCase):
    def setUp(self):
        self.m=json.loads((ROOT/'config/codepage-nls-origin-evidence.json').read_text())
        self.rows={r['address']:r for r in self.m['functions']}

    def ledger(self,row):
        return (dict(size=str(row['size']),span_end=row['span_end'],source_file='',match_percent='0.00',
                     owner='library',module='VC71CRT',status='excluded',proposed_name=row['coff_symbol']),
                dict(evidence_id='R123',origin='library',subsystem='VC71CRT',disposition='exclude',confidence=REVIEW.CONFIDENCE))

    def test_setmbcp_requires_the_finally_tail(self):
        self.rows['0x006503A9']['size']=327
        with self.assertRaisesRegex(ValueError,'complete own auxiliary extent'):
            REVIEW.verify_plan(self.m)

    def test_mbc_updater_requires_eh_head_and_shared_entry(self):
        self.rows['0x0065019A']['size']=99
        with self.assertRaisesRegex(ValueError,'complete own auxiliary extent'):
            REVIEW.verify_plan(self.m)

    def test_locale_updater_requires_the_unlock_tail(self):
        self.rows['0x00642DEB']['size']=50
        with self.assertRaisesRegex(ValueError,'complete own auxiliary extent'):
            REVIEW.verify_plan(self.m)

    def test_boundary_reconciliation_preserves_the_initial_observation(self):
        self.rows['0x0065019A']['ledger_size']=111
        with self.assertRaisesRegex(ValueError,'historical provisional boundary'):
            REVIEW.verify_plan(self.m)

    def test_case_map_cannot_inherit_nls_origin(self):
        self.rows['0x0065275D']['decision']='pending'
        with self.assertRaisesRegex(ValueError,'complete own auxiliary extent'):
            REVIEW.verify_plan(self.m)

    def test_callee_requires_its_actual_coff_identity(self):
        b=next(b for b in self.rows['0x0065000E']['relocation_bindings'] if b['target_kind']=='callee')
        b['symbol']='_wrong_nls_child'
        with self.assertRaisesRegex(ValueError,'unreviewed callee'):
            REVIEW.verify_plan(self.m)

    def test_data_binding_cannot_remain_diagnostic(self):
        self.rows['0x0064FFE5']['relocation_bindings'][0]['target_kind']='diagnostic'
        with self.assertRaisesRegex(ValueError,'defining provenance'):
            REVIEW.verify_plan(self.m)

    def test_stack_probe_alias_requires_same_source_definition(self):
        next(r for r in self.m['anchors'] if r['address']=='0x00642510')['source_aliases']=[]
        with self.assertRaisesRegex(ValueError,'unreviewed callee'):
            REVIEW.verify_plan(self.m)

    def test_mbc_cleanup_cannot_move_the_earlier_eh_head(self):
        self.m['interior_labels'][1]['eh_source_offset']=102
        with self.assertRaisesRegex(ValueError,'earlier EH head'):
            REVIEW.verify_plan(self.m)

    def test_cleanup_cannot_gain_a_standalone_extent(self):
        self.m['interior_labels'][0]['extent_basis']='function-auxiliary-record'
        with self.assertRaisesRegex(ValueError,'standalone function'):
            REVIEW.verify_plan(self.m)

    def test_codepage_records_cannot_compare_a_single_record(self):
        next(r for r in self.m['state_data'] if r['symbol']=='___rgctypeflag')['size']=48
        with self.assertRaisesRegex(ValueError,'defining data|carriers'):
            REVIEW.verify_plan(self.m)

    def test_locale_codepage_cannot_replace_whole_lc_handle_carrier(self):
        next(r for r in self.m['state_data'] if r['symbol']=='___lc_handle')['size']=4
        with self.assertRaisesRegex(ValueError,'defining data|carriers'):
            REVIEW.verify_plan(self.m)

    def test_runtime_platform_requires_its_actual_whole_carrier(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__umaskval')['size']=4
        with self.assertRaisesRegex(ValueError,'defining data|carriers'):
            REVIEW.verify_plan(self.m)

    def test_ctype_common_requires_all_257_bytes(self):
        r=next(r for r in self.m['common_globals'] if r['symbol']=='__mbctype')
        r['size']=256
        with self.assertRaisesRegex(ValueError,'complete COMMON storage'):
            REVIEW.verify_plan(self.m)

    def test_mbulinfo_common_requires_six_ushorts(self):
        r=next(r for r in self.m['common_globals'] if r['symbol']=='___mbulinfo')
        d=copy.deepcopy(r['source_definition']);d['offset']=10
        with self.assertRaisesRegex(ValueError,'full defining array'):
            REVIEW.check_common(r,d)

    def test_common_cannot_be_an_undefined_reference(self):
        r=self.m['common_globals'][0];d=copy.deepcopy(r['source_definition']);d['offset']=0
        with self.assertRaisesRegex(ValueError,'full defining array'):
            REVIEW.check_common(r,d)

    def test_nls_scope_requires_every_filter_and_handler(self):
        self.m['scope_tables'].pop()
        with self.assertRaisesRegex(ValueError,'data/scopes/literals'):
            REVIEW.verify_plan(self.m)

    def test_nls_probe_requires_sdk_lead_byte_offset(self):
        self.m['sdk_layout']['values'][3]=4
        with self.assertRaisesRegex(ValueError,'natural codepage/SDK layout'):
            REVIEW.verify_plan(self.m)

    def test_locale_handle_offset_cannot_be_guessed(self):
        self.m['sdk_layout']['values'][24]=8
        with self.assertRaisesRegex(ValueError,'natural codepage/SDK layout'):
            REVIEW.verify_plan(self.m)

    def test_historical_context_rejects_changed_source_fields(self):
        r=copy.deepcopy(self.rows['0x006503A9']);f,o=self.ledger(r)
        r['relocation_bindings'][0]['addend']=4
        with self.assertRaisesRegex(ValueError,'relocation provenance'):
            REVIEW.check_historical_root(r,f,o)

    def test_historical_guard_cannot_waive_unrelated_roots(self):
        r=self.rows['0x0064FFE5'];f,o=self.ledger(r)
        with self.assertRaisesRegex(ValueError,'outside the reviewed graph'):
            REVIEW.check_historical_root(r,f,o)

    def test_origin_acceptance_cannot_grant_exact_credit(self):
        r=self.rows['0x006503A9'];f,o=self.ledger(r);f['match_percent']='100.00'
        with self.assertRaisesRegex(ValueError,'origin-only extent'):
            REVIEW.check_ledger(r,f,o)


if __name__=='__main__':
    unittest.main()
