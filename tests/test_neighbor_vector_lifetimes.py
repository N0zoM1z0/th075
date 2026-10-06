"""Reject false origin gains from clear aliases, missing states or partial EH carriers."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('neighbor_vector_tests', ROOT / 'scripts/verify-neighbor-vector-lifetime-origins.py')
V = importlib.util.module_from_spec(spec)
spec.loader.exec_module(V)


class NeighborVectorLifetimeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan = json.loads((ROOT / V.EVIDENCE).read_text())

    def test_immutable_whole_manifest_and_inputs(self):
        V.verify_plan(self.plan)
        V.verify_context(self.plan)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, value in self.plan['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), value, path)

    def test_origin_transition_has_no_extent_abi_source_or_exact_gain(self):
        bad = copy.deepcopy(self.plan)
        bad['functions'][0]['accepted_function']['source_file'] = 'invented-owner.cpp'
        with self.assertRaisesRegex(ValueError, 'immutable'):
            V.verify_plan(bad)
        self.assertEqual(sum(V.WHOLE.values()), 76)
        self.assertEqual(self.plan['retained_unknown'], V.UNKNOWN)

    def test_missing_constructor_state_cannot_bootstrap_from_library_callee(self):
        bad = copy.deepcopy(self.plan)
        bad['context']['links'].pop()
        with self.assertRaisesRegex(ValueError, 'construction-state cohort'):
            V.verify_context(bad)

    def test_receiver_offset_changes_are_rejected(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['native'] if r['address'] == '0x004587E0')
        next(i for i in row['instructions'] if i['offset'] == 61)['operands'] = 'ecx, 0x54'
        with self.assertRaisesRegex(ValueError, 'same receiver'):
            V.verify_context(bad)

    def test_state_must_be_stored_immediately_after_completed_construction(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['native'] if r['address'] == '0x004587E0')
        next(i for i in row['instructions'] if i['offset'] == 69)['operands'] = 'byte ptr [ebp - 4], 1'
        with self.assertRaisesRegex(ValueError, 'completed construction state'):
            V.verify_context(bad)

    def test_real_unwind_entry_must_destroy_the_constructed_subobject(self):
        bad = copy.deepcopy(self.plan)
        next(r for b in bad['context']['blocks'] for r in b['callbacks'] if r['address'] == '0x006561D3')['destination'] = '0x00458A80'
        with self.assertRaisesRegex(ValueError, 'EH state/provider'):
            V.verify_context(bad)

    def test_compiler_source_callback_uses_actual_library_definition(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['control']['comparisons'] if r['role'] == 'whole-compiler-base-cleanup-and-dispatch18')
        row['fields'][0]['symbol'] = '?Cleanup@WordVectorPolicy@@QAEXXZ'
        with self.assertRaisesRegex(ValueError, 'full compiler code/data'):
            V.verify_context(bad)

    def test_full_handler_code_and_metadata_cannot_be_cropped_to_cleanup8(self):
        for role, size in [('whole-compiler-base-cleanup-and-dispatch18', 8),
                           ('whole-compiler-unwind-and-function-info36', 8)]:
            bad = copy.deepcopy(self.plan)
            next(r for r in bad['control']['comparisons'] if r['role'] == role)['size'] = size
            with self.assertRaisesRegex(ValueError, 'full compiler code/data'):
                V.verify_context(bad)

    def test_local_funcinfo_and_unwind_providers_cannot_be_substituted(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['control']['comparisons'] if r['role'] == 'whole-compiler-unwind-and-function-info36')
        row['fields'][0]['symbol_offset'] = 8
        with self.assertRaisesRegex(ValueError, 'actual local providers'):
            V.verify_context(bad)

    def test_ordinary_clear_positives_remain_unknown(self):
        ordinary = [r for r in self.plan['control']['comparisons'] if r['role'].startswith('ordinary-cleanup')]
        self.assertEqual([r['address'] for r in ordinary], V.UNKNOWN)
        self.assertTrue(all(r['size'] == 19 and r['symbol'].startswith('?Cleanup@') for r in ordinary))
        bad = copy.deepcopy(self.plan)
        bad['control']['comparisons'].remove(next(r for r in bad['control']['comparisons'] if r['role'].startswith('ordinary-cleanup')))
        with self.assertRaisesRegex(ValueError, 'counterexample'):
            V.verify_context(bad)

    def test_complete_ordinary_parents_and_natural_multi_member_difference(self):
        alternatives = {r['symbol']: r for r in self.plan['control']['alternatives']}
        self.assertEqual(alternatives['??0LargeVectorPolicy@@QAE@XZ']['size'], 93)
        self.assertEqual(alternatives['??0SixteenVectorPolicy@@QAE@XZ']['size'], 75)
        self.assertEqual(alternatives['??0WordVectorPolicy@@QAE@XZ']['size'], 72)
        self.assertEqual(alternatives['__ehhandler$??0ThreeVectorObservation@@QAE@XZ']['size'], 40)
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['control']['comparisons'] if r['role'] == 'ordinary-policy-parent93-positive')['size'] = 75
        with self.assertRaisesRegex(ValueError, 'complete ordinary inherited parent'):
            V.verify_context(bad)

    def test_two_element_boundaries_preserve_original_unknown_decisions(self):
        boundaries = self.plan['control']['provider_alternatives']
        self.assertEqual([(r['address'], r['size'], r['target_size']) for r in boundaries],
                         [('0x0045B6B0', 5, 15), ('0x005FAAD0', 5, 15)])
        bad = copy.deepcopy(self.plan)
        bad['control']['provider_alternatives'].pop()
        with self.assertRaisesRegex(ValueError, 'element destruction boundaries'):
            V.verify_context(bad)

    def test_every_provider_field_keeps_its_actual_source_section(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['control']['comparisons'] if r['role'] == 'vendor-destructor19')
        row['fields'][0]['symbol_section'] = 0
        with self.assertRaisesRegex(ValueError, 'actual source provider'):
            V.verify_context(bad)

    def test_historical_view_accepts_only_literal_original_or_accepted_pairs(self):
        selected = {r['address']: r for r in self.plan['functions']}
        for evidence_only in [True, False]:
            state = 'original' if evidence_only else 'accepted'
            for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]:
                current = [selected[r['address']][state + '_' + kind] if r['address'] in selected else r
                           for r in V.rows(name)]
                historical = V.historical_rows(self.plan, name, current, evidence_only)
                self.assertEqual([r for r in historical if r['address'] in selected],
                                 [selected[r['address']]['original_' + kind] for r in current if r['address'] in selected])
                bad = copy.deepcopy(current)
                next(r for r in bad if r['address'] in selected)[
                    'evidence' if kind == 'function' else 'evidence_id'] = 'unsupported'
                with self.assertRaises(ValueError):
                    V.historical_rows(self.plan, name, bad, evidence_only)
                with self.assertRaisesRegex(ValueError, 'loses or duplicates'):
                    V.historical_rows(self.plan, name, current + [next(r for r in current if r['address'] in selected)], evidence_only)

    def test_retained_r254_view_still_rejects_unrelated_changes(self):
        prior = V.module('neighbor_test_prior', 'verify-member-vector-lifetime-origins.py')
        old = json.loads((ROOT / prior.EVIDENCE).read_text())
        selected = {r['address']: r for r in self.plan['functions']}
        source = {name: V.rows(name) for name in ['functions.csv', 'function-origins.csv']}
        outer_spec = importlib.util.spec_from_file_location(
            'outer_successor_view', ROOT / 'scripts/verify-outer-vector-policy-origins.py')
        outer_view = importlib.util.module_from_spec(outer_spec)
        outer_spec.loader.exec_module(outer_view)
        newest_outer = json.loads((ROOT / outer_view.EVIDENCE).read_text())
        outer_view.verify_plan(newest_outer)
        original_outer = all(q['original_function'] in source['functions.csv'] for q in newest_outer['functions'])
        source = {name: outer_view.historical_rows(newest_outer, name, actual, original_outer)
                  for name, actual in source.items()}
        view = {name: V.historical_rows(self.plan, name, [selected[r['address']]['accepted_' + kind]
                    if r['address'] in selected else r for r in source[name]])
                for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]}
        with patch.object(prior, 'rows', side_effect=lambda name: view[name]):
            prior.verify_canonical(old)
        bad = copy.deepcopy(view)
        next(r for r in bad['functions.csv'] if r['address'] not in V.WHOLE)['notes'] = 'unapproved'
        with patch.object(prior, 'rows', side_effect=lambda name: bad[name]):
            with self.assertRaisesRegex(ValueError, 'unrelated canonical'):
                prior.verify_canonical(old)

    def test_historical_csv_representation_requires_pin_and_identical_git_content(self):
        name, blob = 'config/sample.csv', b'a,b\n1,2\n'
        body = blob.replace(b'\n', b'\r\n')
        pinned = {name: {V.digest(body)}}
        V.HISTORY.check_representation(name, body, blob, pinned)
        for bad_body, bad_pin in [(body, {}), (body + b'3,4\r\n', pinned)]:
            with self.assertRaisesRegex(ValueError, 'Historical tracked content'):
                V.HISTORY.check_representation(name, bad_body, blob, bad_pin)
        with self.assertRaises(ValueError):
            V.HISTORY.check_representation('sample.cpp', body, blob, {'sample.cpp': {V.digest(body)}})

    def test_original_historical_scripts_and_manifests_are_immutable(self):
        self.assertEqual([r['evidence_id'] for r in self.plan['history']], ['R254', 'R212', 'R227'])
        self.assertEqual(len(self.plan['history'][0]['cold_prerequisites']), 3)
        self.assertTrue(all(r['source_root_characters'] == 59 for r in self.plan['history']))
        bad = copy.deepcopy(self.plan)
        bad['history'][0]['commit'] = bad['history'][1]['commit']
        with self.assertRaisesRegex(ValueError, 'immutable'):
            V.verify_plan(bad)

    def test_full_ordinary_storage_is_an_observation_without_game_layout_credit(self):
        ctl = self.plan['control']
        self.assertEqual(ctl['layouts'][0]['values'], [16, 116, 4, 16, 20, 16, 48])
        self.assertEqual(ctl['emission']['bss'][0]['size'], 148)
        self.assertEqual(len(ctl['emission']['initialized']), 166)
        self.assertEqual(len(ctl['comparisons']), 82)
        self.assertNotIn('target_address', ctl['emission']['bss'][0])


if __name__ == '__main__':
    unittest.main()
