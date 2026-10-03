"""Protect complete CRT lock tables, callback ranges, dynamic APIs and pending cleanup extents."""
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('termination_lock',ROOT/'scripts/verify-termination-lock-origins.py')
LOCK=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(LOCK)


class TerminationLockOriginTests(unittest.TestCase):
    def setUp(self):
        self.manifest=json.loads((ROOT/'config/termination-lock-origin-evidence.json').read_text())
        self.rows={r['address']:r for r in self.manifest['functions']}

    def test_lazy_lock_cannot_drop_its_finally_tail(self):
        self.rows['0x00646685']['size']=151
        with self.assertRaisesRegex(ValueError,'complete source extent'):
            LOCK.verify_plan(self.manifest)

    def test_exit_cannot_hide_its_existing_interior_cleanup_candidate(self):
        self.manifest['pending_funclets'].pop()
        with self.assertRaisesRegex(ValueError,'pending interior finally entry'):
            LOCK.verify_plan(self.manifest)

    def test_cleanup_cannot_gain_origin_from_a_tiny_slice(self):
        self.manifest['pending_funclets'][0]['decision']='library'
        with self.assertRaisesRegex(ValueError,'pending interior finally entry'):
            LOCK.verify_plan(self.manifest)

    def test_lock_parent_cannot_gain_credit_from_named_allocator_dependencies(self):
        self.rows['0x00646725']['decision']='library'
        with self.assertRaisesRegex(ValueError,'unresolved allocator/termination decisions'):
            LOCK.verify_plan(self.manifest)

    def test_accepted_wrapper_cannot_substitute_an_unreviewed_callee(self):
        b=next(b for b in self.rows['0x0065053F']['relocation_bindings'] if b['symbol']=='___crtInitCritSecNoSpinCount@8')
        b['target_address']='0x00646725'
        with self.assertRaisesRegex(ValueError,'independently checked source callee'):
            LOCK.verify_plan(self.manifest)

    def test_lock_table_cannot_omit_a_static_initialization_flag(self):
        self.manifest['lock_flags'][0]=0
        with self.assertRaisesRegex(ValueError,'fourteen static slots'):
            LOCK.verify_plan(self.manifest)

    def test_static_storage_cannot_be_a_same_width_arbitrary_zero_region(self):
        self.manifest['state_data'][1]['target_address']='0x0068E350'
        with self.assertRaisesRegex(ValueError,'whole defining source topology'):
            LOCK.verify_plan(self.manifest)

    def test_sdk_critical_section_requires_the_full_spin_field(self):
        self.manifest['sdk_layout']['values'][6]=16
        with self.assertRaisesRegex(ValueError,'full SDK layout/error controls'):
            LOCK.verify_plan(self.manifest)

    def test_dynamic_api_cannot_store_into_an_unrelated_cache(self):
        w=next(w for w in self.rows['0x0065053F']['instruction_witnesses'] if w['site']=='0x00650578')
        w['operands']='dword ptr [0x68e708], eax'
        with self.assertRaisesRegex(ValueError,'API/fallback/range witnesses'):
            LOCK.verify_plan(self.manifest)

    def test_no_spin_fallback_preserves_both_argument_cleanup(self):
        w=next(w for w in self.rows['0x0065052F']['instruction_witnesses'] if w['site']=='0x0065053C')
        w['operands']='4'
        with self.assertRaisesRegex(ValueError,'API/fallback/range witnesses'):
            LOCK.verify_plan(self.manifest)

    def test_dynamic_api_eh_metadata_cannot_exchange_filter_and_handler(self):
        fields=self.manifest['scope_tables'][0]['relocations']
        fields[0]['target_address'],fields[1]['target_address']=fields[1]['target_address'],fields[0]['target_address']
        with self.assertRaisesRegex(ValueError,'filter/handler scope bindings'):
            LOCK.verify_plan(self.manifest)

    def test_callback_loop_preserves_the_observed_eax_begin_abi(self):
        w=next(w for w in self.rows['0x006440E7']['instruction_witnesses'] if w['site']=='0x006440E8')
        w['operands']='esi, dword ptr [esp + 8]'
        with self.assertRaisesRegex(ValueError,'API/fallback/range witnesses'):
            LOCK.verify_plan(self.manifest)

    def test_callback_range_cannot_compare_one_zero_word(self):
        self.manifest['callback_ranges'][0]['size']=4
        with self.assertRaisesRegex(ValueError,'truncated or lose end markers'):
            LOCK.verify_plan(self.manifest)

    def test_callback_markers_require_the_actual_source_subsection(self):
        self.manifest['range_markers'][0]['section_name']='.CRT$XCA'
        with self.assertRaisesRegex(ValueError,'actual complete boundary markers'):
            LOCK.verify_plan(self.manifest)

    def test_dynamic_export_cannot_omit_a_whole_literal_definition(self):
        self.manifest['literal_controls'].pop()
        with self.assertRaisesRegex(ValueError,'complete readonly definitions'):
            LOCK.verify_plan(self.manifest)

    def test_library_origin_cannot_grant_source_or_exact_credit(self):
        row=self.rows['0x00646658'];key=row['address']
        function={'size':'21','span_end':row['span_end'],'source_file':'src/Lock.cpp','match_percent':'100.00'}
        with self.assertRaisesRegex(ValueError,'source or exact credit'):
            LOCK.check_ledger(row,{key:function},{},True)


if __name__=='__main__':
    unittest.main()
