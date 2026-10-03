"""Reject incomplete floating-point graphs, parser extents and inherited origins."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('floating_point', ROOT / 'scripts/verify-floating-point-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class FloatingPointOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = json.loads((ROOT / 'config/floating-point-origin-evidence.json').read_text())
        self.rows = {r['address']: r for r in self.m['functions']}

    def reject(self, text):
        with self.assertRaisesRegex(ValueError, text):
            REVIEW.verify_plan(self.m)

    def ledger(self, row, pending=False):
        return (dict(size=str(row['size']), span_end=row['span_end'], source_file='', match_percent='0.00',
                     owner='' if pending else 'library', module='' if pending else 'VC71CRT',
                     status='unclassified' if pending else 'excluded', proposed_name=row['coff_symbol']),
                dict(evidence_id='R124', origin='unknown' if pending else 'library',
                     subsystem='' if pending else 'VC71CRT', disposition='review' if pending else 'exclude',
                     confidence=REVIEW.PENDING[row['address']] if pending else REVIEW.CONFIDENCE))

    def test_parser_requires_embedded_dispatch_data(self):
        self.rows['0x00652CD1']['size'] = 1028
        self.reject('complete own source extent')

    def test_parser_retains_original_provisional_boundary(self):
        self.rows['0x00652CD1']['ledger_size'] = 1076
        self.reject('original provisional boundary')

    def test_parser_data_cannot_be_disassembled_as_code(self):
        self.rows['0x00652CD1']['code_size'] = 1076
        self.reject('hidden from the full extent')

    def test_parser_requires_all_twelve_entries(self):
        self.rows['0x00652CD1']['embedded_tables'][0]['entries'].pop()
        self.reject('twelve-entry table')

    def test_parser_requires_typed_same_source_labels(self):
        b = next(b for b in self.rows['0x00652CD1']['relocation_bindings'] if b['offset'] >= 1028)
        b['local_symbol_offset'] += 1
        self.reject('same-source local labels')

    def test_parser_requires_actual_indirect_dispatch(self):
        self.rows['0x00652CD1']['indirect_jumps'] = []
        self.reject('twelve-entry table')

    def test_registration_requires_all_six_slots(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__cfltcvt_tab')['size'] = 20
        self.reject('state/scopes|carriers')

    def test_fpinit_cannot_compare_a_pointer_prefix(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__fltused')['size'] = 4
        self.reject('state/scopes|carriers')

    def test_powers_require_positive_and_negative_records(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '__pow10pos')['size'] = 352
        self.reject('state/scopes|carriers')

    def test_formats_require_both_float_and_double(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '_DoubleFormat')['size'] = 24
        self.reject('state/scopes|carriers')

    def test_division_state_requires_both_actual_definitions(self):
        next(r for r in self.m['state_data'] if r['symbol'] == '___fastflag')['size'] = 4
        self.reject('state/scopes|carriers')

    def test_complete_trap_cannot_be_omitted(self):
        self.rows['0x0064FA08']['decision'] = 'pending'
        self.reject('complete own source extent')

    def test_auxiliary_controls_cannot_gain_candidate_credit(self):
        self.m['auxiliary_bodies'][0]['ledger_size'] = 75
        self.reject('fabricated candidates')

    def test_cinit_cannot_inherit_fp_child_ownership(self):
        self.rows['0x0064411D']['decision'] = 'library'
        self.reject('unresolved initializer callbacks')

    def test_converter_requires_actual_complete_callee(self):
        b = next(b for b in self.rows['0x00645070']['relocation_bindings'] if b['target_kind'] == 'callee')
        b['symbol'] = '_unreviewed_converter'
        self.reject('unreviewed actual callee')

    def test_control87_retains_real_mapping_children(self):
        row = next(r for r in self.m['anchors'] if r['address'] == '0x0064FBB6')
        row['relocation_bindings'][0]['target_address'] = '0x0064411D'
        self.reject('unreviewed actual callee')

    def test_undefined_data_cannot_be_an_accepted_binding(self):
        self.rows['0x006405C2']['relocation_bindings'][0]['target_kind'] = 'diagnostic'
        self.reject('unresolved code/data/API')

    def test_natural_fp_layout_requires_denormal_mask(self):
        self.m['sdk_layout']['values'][21] = 0
        self.reject('natural FP/locale/API')

    def test_natural_locale_layout_requires_clike_offset(self):
        self.m['locale_layout']['values'][6] = 32
        self.reject('natural FP/locale/API')

    def test_feature_query_requires_actual_feature_and_abi(self):
        self.m['dynamic_api']['feature'] = 1
        self.reject('actual API/ABI/fallback')

    def test_feature_query_cannot_substitute_export(self):
        self.m['dynamic_api']['export_literal'] = 'IsDebuggerPresent'
        self.reject('actual API/ABI/fallback')

    def test_historical_cinit_rejects_changed_source_fields(self):
        row = copy.deepcopy(self.rows['0x0064411D']); f, o = self.ledger(row, True)
        row['relocation_bindings'][0]['addend'] = 4
        with self.assertRaisesRegex(ValueError, 'relocation provenance'):
            REVIEW.check_historical_root(row, f, o)

    def test_historical_guard_cannot_waive_unrelated_parents(self):
        row = self.rows['0x006405C2']; f, o = self.ledger(row)
        with self.assertRaisesRegex(ValueError, 'outside its pending startup parent'):
            REVIEW.check_historical_root(row, f, o)

    def test_origin_review_cannot_grant_source_credit(self):
        row = self.rows['0x006405C2']; f, o = self.ledger(row); f['source_file'] = 'src/FP.cpp'
        with self.assertRaisesRegex(ValueError, 'origin-only extent'):
            REVIEW.check_ledger(row, f, o)

    def test_origin_review_cannot_grant_exact_credit(self):
        row = self.rows['0x006405C2']; f, o = self.ledger(row); f['match_percent'] = '100.00'
        with self.assertRaisesRegex(ValueError, 'origin-only extent'):
            REVIEW.check_ledger(row, f, o)


if __name__ == '__main__':
    unittest.main()
