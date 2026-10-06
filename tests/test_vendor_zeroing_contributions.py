"""Keep full contribution provenance and literal transitions distinct from leaf equality."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('vendor_zeroing_tests', ROOT / 'scripts/verify-vendor-zeroing-contribution-origins.py')
V = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(V)


class VendorZeroingContributionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan = json.loads((ROOT / V.EVIDENCE).read_text())

    def test_complete_source_order_and_original_provider_records_are_immutable(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for provider in self.plan['providers']:
            self.assertEqual(V.digest((ROOT / provider['path']).read_bytes()), provider['path_sha256'])
        bad = copy.deepcopy(self.plan)
        bad['units'][0]['code'].pop(0)
        with self.assertRaisesRegex(ValueError, 'immutable'):
            V.verify_plan(bad)

    def test_ordinary_byte_positive_controls_are_retained_without_source_credit(self):
        ctl = self.plan['ordinary_control']
        self.assertEqual([r['size'] for r in ctl['comparisons']], [14, 12])
        self.assertEqual(sum(r['size'] for r in ctl['emission']), 38)
        self.assertEqual(V.digest((ROOT / ctl['source']).read_bytes()), ctl['source_sha256'])
        for r in self.plan['functions']:
            self.assertTrue(r['accepted_origin']['confidence'].startswith('inferred-'))
            self.assertFalse(any(r['accepted_function'][k] for k in ['source_file', 'signature', 'calling_convention']))
            self.assertEqual(r['accepted_function']['match_percent'], '0.00')

    def test_only_exact_literal_original_to_accepted_pairs_are_allowed(self):
        for r in self.plan['functions']:
            self.assertTrue(V.allows_transition(r['address'], r['original_function'], r['original_origin'], r['accepted_function'], r['accepted_origin']))
            bad = dict(r['accepted_function'], notes='unapproved replacement')
            self.assertFalse(V.allows_transition(r['address'], r['original_function'], r['original_origin'], bad, r['accepted_origin']))
        self.assertFalse(V.allows_transition('0x004135F0', {}, {}, {}, {}))

    def test_historical_view_rejects_duplicate_or_substituted_pairs(self):
        for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]:
            selected = {r['address']: r for r in self.plan['functions']}
            for original in [False, True]:
                state = 'original_' if original else 'accepted_'
                actual = [selected[r['address']][state + kind] if r['address'] in selected else r for r in V.rows(name)]
                old = V.historical_rows(self.plan, name, actual, original)
                self.assertEqual([r for r in old if r['address'] in selected], [selected[r['address']]['original_' + kind] for r in actual if r['address'] in selected])
                with self.assertRaisesRegex(ValueError, 'literal pair'):
                    V.historical_rows(self.plan, name, actual + [selected[next(iter(selected))][state + kind]], original)

    def test_full_unrelated_canonical_guard_remains_strict(self):
        selected = {r['address']: r for r in self.plan['functions']}
        stack = V.module('zeroing_test_stack_successor', 'verify-sdk-stack-contribution-origins.py')
        stack_plan = json.loads((ROOT / stack.EVIDENCE).read_text())
        source = {name: V.rows(name) for name in ['functions.csv', 'function-origins.csv']}
        original_stack = all(q['original_function'] in source['functions.csv'] for q in stack_plan['functions'])
        source = {name: stack.historical_rows(stack_plan, name, actual, original_stack)
                  for name, actual in source.items()}
        for original in [False, True]:
            state = 'original_' if original else 'accepted_'
            view = {name: [selected[r['address']][state + kind] if r['address'] in selected else r for r in source[name]] for name, kind in [('functions.csv', 'function'), ('function-origins.csv', 'origin')]}
            with patch.object(V, 'rows', side_effect=lambda name: view[name]):
                V.verify_canonical(self.plan, original)
            bad = copy.deepcopy(view)
            next(r for r in bad['functions.csv'] if r['address'] not in selected)['notes'] = 'unapproved change'
            with patch.object(V, 'rows', side_effect=lambda name: bad[name]):
                with self.assertRaisesRegex(ValueError, 'unrelated canonical'):
                    V.verify_canonical(self.plan, original)

    def test_relocations_are_written_and_cannot_be_omitted_or_masked(self):
        raw = bytes.fromhex('e800000000c3')
        fields = [dict(offset=1, type='REL32')]
        bindings = [dict(target_address='0x00002000')]
        self.assertEqual(V.linked(raw, fields, bindings, 0x1000), bytes.fromhex('e8fb0f0000c3'))
        with self.assertRaisesRegex(ValueError, 'drops an actual field'):
            V.linked(raw, fields, [], 0x1000)
        with self.assertRaisesRegex(ValueError, 'relative opcode'):
            V.linked(b'\x90' + raw[1:], fields, bindings, 0x1000)


if __name__ == '__main__':
    unittest.main()
