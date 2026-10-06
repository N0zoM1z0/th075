"""Reject isolated lifetime fingerprints and fabricated source/provider cohorts."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('deque_outer_tests', ROOT / 'scripts/verify-deque-outer-policy-origins.py')
V = importlib.util.module_from_spec(spec)
spec.loader.exec_module(V)


class DequeOuterPolicyTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan = json.loads((ROOT / V.EVIDENCE).read_text())

    def test_immutable_whole_proof_and_all_retained_inputs(self):
        V.verify_plan(self.plan)
        V.verify_context(self.plan)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, sha in self.plan['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)
        bad = copy.deepcopy(self.plan)
        bad['functions'][0]['accepted_function']['source_file'] = 'invented-owner.cpp'
        with self.assertRaisesRegex(ValueError, 'immutable'):
            V.verify_plan(bad)

    def test_independent_parser_uses_the_same_created_local(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['native'] if r['address'] == '0x00420880')
        next(i for i in row['instructions'] if i['offset'] == 1174)['operands'] = 'ecx, [ebp - 0x74]'
        with self.assertRaisesRegex(ValueError, 'same-local parser'):
            V.verify_context(bad)

    def test_actual_parser_eh_state8_cannot_be_reassigned(self):
        bad = copy.deepcopy(self.plan)
        callback = next(b for b in bad['context']['blocks'] if b['frame']['handler_address'] == '0x006555B8')['callbacks'][-1]
        callback['destination'] = '0x00421340'
        with self.assertRaisesRegex(ValueError, 'state8 cleanup identity'):
            V.verify_context(bad)

    def test_whole_parser_frame_is_not_reduced_to_one_useful_cleanup(self):
        bad = copy.deepcopy(self.plan)
        callbacks = next(b for b in bad['context']['blocks'] if b['frame']['handler_address'] == '0x006555B8')['callbacks']
        del callbacks[0]
        with self.assertRaisesRegex(ValueError, 'full original parser frame'):
            V.verify_context(bad)

    def test_cleanup_and_base_destruction_keep_actual_receiver_and_state_order(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['native'] if r['address'] == '0x004212A0')
        next(i for i in row['instructions'] if i['offset'] == 43)['operands'] = 'dword ptr [ebp - 4], 0'
        with self.assertRaisesRegex(ValueError, 'cleanup/state ordering'):
            V.verify_context(bad)

    def test_source_provider_must_be_the_real_complete_definition(self):
        bad = copy.deepcopy(self.plan)
        row = next(r for r in bad['controls'][0]['comparisons'] if r['symbol'] == '??1ExplicitMember@@QAE@XZ')
        next(f for f in row['fields'] if f['offset'] == 39)['symbol_section'] = 0
        with self.assertRaisesRegex(ValueError, 'actual complete defining provider'):
            V.verify_context(bad)

    def test_all_recursive_vendor_providers_remain_in_the_coherent_graph(self):
        bad = copy.deepcopy(self.plan)
        bad['controls'][0]['comparisons'] = [r for r in bad['controls'][0]['comparisons']
                                            if not r['symbol'].startswith('??0?$allocator@UClearValue8')]
        with self.assertRaisesRegex(ValueError, 'recursive defining provider'):
            V.verify_context(bad)

    def test_byte_positive_implicit72_does_not_erase_constructor_or_whole_eh(self):
        positives = [r for r in self.plan['controls'][0]['comparisons'] if r['role'] == 'implicit-empty-first72-byte-positive']
        self.assertEqual([r['size'] for r in positives], [72, 72])
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['controls'][0]['alternatives'] if r['symbol'] == '??0EmptyFirst@@QAE@XZ')['size'] = 75
        with self.assertRaisesRegex(ValueError, 'construction79/two-state EH26'):
            V.verify_context(bad)

    def test_two_state_compiler_metadata_is_not_cropped_to_one_state(self):
        bad = copy.deepcopy(self.plan)
        ctl = bad['controls'][0]
        row = next(r for r in ctl['alternatives'] if r['symbol'] == '__ehhandler$??0EmptyFirst@@QAE@XZ')
        field = next(f for f in row['fields'] if f['type'] == 'DIR32')
        next(r for r in ctl['emission']['initialized'] if r['source']['section'] == field['symbol_section'])['source']['size'] = 36
        with self.assertRaisesRegex(ValueError, 'two-state source compiler metadata44'):
            V.verify_context(bad)

    def test_implicit_provider19_cannot_define_actual_tidy177(self):
        bad = copy.deepcopy(self.plan)
        next(r for r in bad['native'] if r['address'] == '0x004219C0')['size'] = 19
        with self.assertRaisesRegex(ValueError, 'provider19 versus native177'):
            V.verify_context(bad)

    def test_negative_whole_parent_state_difference_remains_visible(self):
        bad = copy.deepcopy(self.plan)
        bad['controls'][0]['negative_comparisons'][0]['difference_count'] = 0
        with self.assertRaisesRegex(ValueError, 'negative construction-state'):
            V.verify_context(bad)

    def test_one_literal_historical_transition_rejects_substitution_or_duplicates(self):
        for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]:
            selected = self.plan['functions'][0]
            for evidence_only in [True, False]:
                state = 'original' if evidence_only else 'accepted'
                actual = [selected[state + '_' + kind] if r['address'] in V.WHOLE else r for r in V.rows(name)]
                old = V.historical_rows(self.plan, name, actual, evidence_only)
                self.assertIn(selected['original_' + kind], old)
                with self.assertRaisesRegex(ValueError, 'literal pair'):
                    V.historical_rows(self.plan, name, actual + [selected[state + '_' + kind]], evidence_only)
                bad = copy.deepcopy(actual)
                next(r for r in bad if r['address'] in V.WHOLE)['size' if kind == 'function' else 'evidence_id'] = 'unapproved'
                with self.assertRaisesRegex(ValueError, 'literal pair'):
                    V.historical_rows(self.plan, name, bad, evidence_only)


if __name__ == '__main__':
    unittest.main()
