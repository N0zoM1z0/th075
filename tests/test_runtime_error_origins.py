"""Protect whole CRT extents, dynamic dispatch provenance and unresolved failure edges."""
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
def module(name):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/f'{name}.py')
    value=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value
RUNTIME=module('verify-runtime-error-origins')
STARTUP=module('verify-startup-dependency-origins')


class RuntimeErrorOriginTests(unittest.TestCase):
    def setUp(self):
        self.manifest=json.loads((ROOT/'config/runtime-error-origin-evidence.json').read_text())
        self.rows={r['address']:r for r in self.manifest['functions']}

    def test_exit_cannot_drop_its_terminal_trap(self):
        self.rows['0x006440A5']['span_end']='0x006440D3'
        with self.assertRaisesRegex(ValueError,'terminal INT3'):
            RUNTIME.verify_plan(self.manifest)

    def test_tiny_copy_entry_requires_the_whole_carrier(self):
        self.manifest['copy_carrier']['size']=7
        with self.assertRaisesRegex(ValueError,'full two-function carrier'):
            RUNTIME.verify_plan(self.manifest)

    def test_copy_tail_cannot_change_owner(self):
        self.manifest['copy_carrier']['shared_tail']['owner']='0x0064CFF0'
        with self.assertRaisesRegex(ValueError,'shared-tail relationship'):
            RUNTIME.verify_plan(self.manifest)

    def test_dynamic_export_cannot_swap_same_width_cache_slots(self):
        self.manifest['dynamic_exports'][1]['cache_slot']=RUNTIME.CACHE['GetActiveWindow']
        with self.assertRaisesRegex(ValueError,'DLL/export/slot provenance'):
            RUNTIME.verify_plan(self.manifest)

    def test_dynamic_export_requires_its_actual_store_instruction(self):
        witness=next(w for w in self.rows['0x0064FBFE']['instruction_witnesses'] if w['site']=='0x0064FC4B')
        witness['operands']='dword ptr [0x68e710], eax'
        with self.assertRaisesRegex(ValueError,'concrete lookup/store/call'):
            RUNTIME.verify_plan(self.manifest)

    def test_sdk_query_cannot_use_a_partial_or_wrong_structure(self):
        self.manifest['sdk_layout']['values'][0]=8
        with self.assertRaisesRegex(ValueError,'full SDK structure'):
            RUNTIME.verify_plan(self.manifest)

    def test_cookie_failure_cannot_gain_ownership_from_a_fingerprint(self):
        self.rows['0x00640611']['decision']='library'
        with self.assertRaisesRegex(ValueError,'unresolved cookie chain'):
            RUNTIME.verify_plan(self.manifest)

    def test_error_table_cannot_omit_a_message_pointer(self):
        self.manifest['error_table']['relocations'].pop()
        with self.assertRaisesRegex(ValueError,'nineteen-entry error table'):
            RUNTIME.verify_plan(self.manifest)

    def test_whole_literals_cannot_be_missing(self):
        self.manifest['literal_controls'].pop()
        with self.assertRaisesRegex(ValueError,'complete readonly source definition'):
            RUNTIME.verify_plan(self.manifest)

    def test_zero_cache_requires_its_real_defining_offsets(self):
        self.manifest['cache_data']['definitions'][0]['offset']=12
        with self.assertRaisesRegex(ValueError,'cache symbols/offsets'):
            RUNTIME.verify_plan(self.manifest)

    def test_failure_cannot_lose_its_embedded_filter_or_trap(self):
        next(r for r in self.manifest['diagnostic_contexts'] if r['address']=='0x006405E0')['terminal']='return'
        with self.assertRaisesRegex(ValueError,'filter/INT3 extent'):
            RUNTIME.verify_plan(self.manifest)

    def test_origin_does_not_grant_source_or_exact_credit(self):
        row=self.rows['0x00641B80']
        function={'size':'7','span_end':row['span_end'],'source_file':'src/Copy.cpp','match_percent':'100.00'}
        with self.assertRaisesRegex(ValueError,'source or exact credit'):
            RUNTIME.check_ledger(row,{row['address']:function},{},True)

    def test_historical_exit_reconciliation_requires_specific_accepted_evidence(self):
        row=next(r for r in json.loads((ROOT/'config/startup-dependency-origin-evidence.json').read_text())['diagnostic_boundaries'] if r['address']=='0x006440A5')
        key=row['address']
        function={'size':'48','span_end':row['span_end'],'owner':'library','status':'excluded','proposed_name':'___crtExitProcess'}
        origin={'origin':'library','evidence_id':'R116'}
        STARTUP.check_diagnostic_ledger(row,{key:function},{key:origin})
        origin['evidence_id']='guessed-source-name'
        with self.assertRaisesRegex(ValueError,'unaccepted diagnostic'):
            STARTUP.check_diagnostic_ledger(row,{key:function},{key:origin})


if __name__=='__main__':
    unittest.main()
