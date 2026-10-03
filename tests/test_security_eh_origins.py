"""Reject incomplete SEH graphs, substituted SDK fields and premature termination credit."""
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
def module(name):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/f'{name}.py')
    result=importlib.util.module_from_spec(spec);spec.loader.exec_module(result);return result
SECURITY=module('verify-security-eh-origins')
STARTUP=module('verify-startup-dependency-origins')


class SecurityEhOriginTests(unittest.TestCase):
    def setUp(self):
        self.manifest=json.loads((ROOT/'config/security-eh-origin-evidence.json').read_text())
        self.rows={r['address']:r for r in self.manifest['functions']}

    def test_exit_cannot_gain_origin_from_a_short_source_wrapper(self):
        self.rows['0x0064425B']['decision']='library'
        with self.assertRaisesRegex(ValueError,'unresolved termination decisions'):
            SECURITY.verify_plan(self.manifest)

    def test_handler_call_requires_a_complete_independent_callee(self):
        self.manifest['handler_context']['relocation_bindings'][0]['target_address']='0x0064529E'
        with self.assertRaisesRegex(ValueError,'independently compared whole source callee'):
            SECURITY.verify_plan(self.manifest)

    def test_noninventoried_handler_does_not_gain_a_candidate(self):
        self.manifest['handler_context']['ledger_size']=230
        with self.assertRaisesRegex(ValueError,'gains candidate credit'):
            SECURITY.verify_plan(self.manifest)

    def test_nlg_tiny_entry_requires_the_whole_shared_carrier(self):
        self.manifest['nlg_shared_tail']['size']=9
        with self.assertRaisesRegex(ValueError,'complete shared-tail carrier'):
            SECURITY.verify_plan(self.manifest)

    def test_nlg_cleanup_cannot_be_guessed_as_cdecl(self):
        self.manifest['nlg_shared_tail']['cleanup']=0
        with self.assertRaisesRegex(ValueError,'RET 4'):
            SECURITY.verify_plan(self.manifest)

    def test_sdk_memory_protection_offset_cannot_use_a_same_width_neighbor(self):
        self.manifest['sdk_layout']['values'][6]=24
        with self.assertRaisesRegex(ValueError,'complete SDK'):
            SECURITY.verify_plan(self.manifest)

    def test_register_api_call_requires_its_actual_import_load(self):
        witness=next(w for w in self.rows['0x0064FCF7']['instruction_witnesses'] if w['site']=='0x0064FEA4')
        witness['operands']='ebx, dword ptr [0x657100]'
        with self.assertRaisesRegex(ValueError,'indirect API/scope callbacks'):
            SECURITY.verify_plan(self.manifest)

    def test_cookie_registration_requires_the_actual_source_subsection(self):
        self.manifest['initializer_registration']['section_name']='.CRT$XCU'
        with self.assertRaisesRegex(ValueError,'whole actual CRT registration'):
            SECURITY.verify_plan(self.manifest)

    def test_initializer_range_cannot_be_truncated_to_one_callback(self):
        self.manifest['initializer_table']['size']=4
        with self.assertRaisesRegex(ValueError,'full merged startup table'):
            SECURITY.verify_plan(self.manifest)

    def test_initializer_marker_cannot_be_a_guessed_zero_word(self):
        self.manifest['initializer_markers'].pop()
        with self.assertRaisesRegex(ValueError,'complete defining source boundary markers'):
            SECURITY.verify_plan(self.manifest)

    def test_handler_filter_slot_cannot_be_substituted_for_handler_slot(self):
        witness=next(w for w in self.manifest['handler_context']['instruction_witnesses'] if w['site']=='0x006454B0')
        witness['operands']='eax, dword ptr [edi + ecx*4 + 8]'
        with self.assertRaisesRegex(ValueError,'scope callbacks'):
            SECURITY.verify_plan(self.manifest)

    def test_page_cache_cannot_use_arbitrary_zero_storage(self):
        self.manifest['state_data'][0]['target_address']='0x0068E708'
        with self.assertRaisesRegex(ValueError,'complete actual defining sections'):
            SECURITY.verify_plan(self.manifest)

    def test_pending_failure_source_cannot_omit_the_terminal_trap(self):
        self.rows['0x006405E0']['size']=48
        with self.assertRaisesRegex(ValueError,'terminal INT3'):
            SECURITY.verify_plan(self.manifest)

    def test_historical_prolog_exception_is_specific_to_closed_r117_evidence(self):
        row=next(r for r in json.loads((ROOT/'config/startup-dependency-origin-evidence.json').read_text())['functions'] if r['address']=='0x00645414')
        key=row['address']
        function={'size':'59','span_end':row['span_end'],'source_file':'','match_percent':'0.00','owner':'library','status':'excluded','proposed_name':'__SEH_prolog'}
        origin={'origin':'library','disposition':'exclude','evidence_id':'R117'}
        STARTUP.check_ledger(row,{key:function},{key:origin},False)
        origin['evidence_id']='unverified-handler-name'
        with self.assertRaisesRegex(ValueError,'unearned ownership'):
            STARTUP.check_ledger(row,{key:function},{key:origin},False)

    def test_origin_does_not_grant_exact_or_source_credit(self):
        row=self.rows['0x00645238'];key=row['address']
        function={'size':'102','span_end':row['span_end'],'source_file':'src/Cookie.cpp','match_percent':'100.00'}
        with self.assertRaisesRegex(ValueError,'source or exact credit'):
            SECURITY.check_ledger(row,{key:function},{},True)


if __name__=='__main__':
    unittest.main()
