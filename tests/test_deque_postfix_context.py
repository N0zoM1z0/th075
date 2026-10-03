"""Reject postfix shape-only claims and changes to independent game controls."""
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('postfix_context', ROOT / 'scripts/verify-deque-postfix-context-origins.py')
POSTFIX = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(POSTFIX)


class PostfixContextTests(unittest.TestCase):
    def setUp(self):
        self.manifest = json.loads((ROOT / 'config/deque-postfix-context-origins.json').read_text())

    def test_decrement_cannot_replace_increment(self):
        self.manifest['postfix'][0]['coff_symbol'] = self.manifest['postfix'][0]['coff_symbol'].replace('??E', '??F')
        with self.assertRaisesRegex(ValueError, 'actual complete prefix'):
            POSTFIX.verify_graph(self.manifest)

    def test_same_shape_requires_whole_actual_callee(self):
        # The relocation fields are identical placeholders; only the callees differ.
        shape = b'\x90' * 54
        common = {'offset': 27, 'type': 'REL32', 'addend': 0}
        definitions = {'inc': (shape, [dict(common, symbol='prefix-inc')]),
                       'dec': (shape, [dict(common, symbol='prefix-dec')]),
                       'prefix-inc': (b'\x40\xc3', []), 'prefix-dec': (b'\x48\xc3', [])}
        self.assertEqual(POSTFIX.matching_alternatives(shape, b'\x40\xc3', definitions), (['dec', 'inc'], ['inc']))
        self.assertEqual(POSTFIX.matching_alternatives(shape, b'\x40', definitions), (['dec', 'inc'], []))

    def test_callback_cannot_be_rebound(self):
        self.manifest['callback']['iat_slot'] = '0x00657134'
        with self.assertRaisesRegex(ValueError, 'callback or CreateThread'):
            POSTFIX.verify_graph(self.manifest)

    def test_unknown_parent_cannot_supply_independent_game_ownership(self):
        next(r for r in self.manifest['contexts'] if r['address'] == '0x004724B0')['origin'] = 'unknown'
        with self.assertRaisesRegex(ValueError, 'independently authored game control'):
            POSTFIX.verify_graph(self.manifest)

    def test_probe_cannot_earn_source_or_exact_credit(self):
        row = self.manifest['postfix'][0]
        function = {'size': '54', 'span_end': row['span_end'], 'owner': 'library',
                    'source_file': 'src/Invented.cpp', 'match_percent': '100.00', 'status': 'matching'}
        origin = {'origin': 'library', 'disposition': 'exclude', 'evidence_id': 'R112'}
        with self.assertRaisesRegex(ValueError, 'incorrect origin/source/exact credit'):
            POSTFIX.check_ledger(row, {row['address']: function}, {row['address']: origin}, False, 'library')


if __name__ == '__main__':
    unittest.main()
