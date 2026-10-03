"""Reject untyped queue lookalikes and loss of independent game context."""
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('event_queue', ROOT / 'scripts/verify-event-queue-origins.py')
QUEUE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(QUEUE)


class QueueOriginTests(unittest.TestCase):
    def setUp(self):
        self.manifest = json.loads((ROOT / 'config/event-queue-origin-evidence.json').read_text())

    def test_front_cannot_be_back_or_a_generic_getter(self):
        row = next(r for r in self.manifest['nodes'] if r['address'] == '0x00423DF0')
        row['coff_symbol'] = row['coff_symbol'].replace('?front@', '?back@')
        with self.assertRaisesRegex(ValueError, 'source family'):
            QUEUE.verify_graph(self.manifest)

    def test_size_needs_the_actual_complete_policy_call(self):
        row = next(r for r in self.manifest['nodes'] if r['address'] == '0x00423C80')
        row['relocation_bindings'][1]['target_address'] = '0x00424500'
        with self.assertRaisesRegex(ValueError, 'source-typed whole callee'):
            QUEUE.verify_graph(self.manifest)

    def test_constructor_pair_needs_used_iterators(self):
        row = next(r for r in self.manifest['contexts'] if r['address'] == '0x00423B40')
        row['body_facts']['direct_calls'] = [c for c in row['body_facts']['direct_calls'] if c['target'] != '0x00423F50']
        with self.assertRaisesRegex(ValueError, 'iterator-use context'):
            QUEUE.verify_graph(self.manifest)

    def test_queue_global_cannot_be_redirected(self):
        row = next(r for r in self.manifest['nodes'] if r['address'] == '0x00423C80')
        for call in row['relocation_bindings']:
            if call['type'] == 'DIR32':
                call['target_address'] = '0x0068BE34'
        with self.assertRaisesRegex(ValueError, 'worker global'):
            QUEUE.verify_graph(self.manifest)

    def test_reviewed_source_anchor_must_keep_its_ownership(self):
        row = next(r for r in self.manifest['nodes'] if r['address'] == '0x00423CE0')
        row['origin'] = 'unknown'
        with self.assertRaisesRegex(ValueError, 'independent library ownership'):
            QUEUE.verify_graph(self.manifest)

    def test_new_helper_cannot_reuse_an_unresolved_interior_extent(self):
        row = next(r for r in self.manifest['nodes'] if r['address'] == '0x00423D40')
        row['retained_interior_candidates'] = ['0x00423D4A']
        functions = {row['address']: {'size': '17', 'span_end': row['span_end']}, '0x00423D4A': {}}
        with self.assertRaisesRegex(ValueError, 'unresolved interior candidate'):
            QUEUE.check_ledger(row, functions, {row['address']: {}}, True, 'library')

    def test_probe_cannot_grant_game_source_or_exact_credit(self):
        row = next(r for r in self.manifest['nodes'] if r['address'] == '0x00423C80')
        function = {'size': '96', 'span_end': row['span_end'], 'source_file': 'src/Invented.cpp',
                    'match_percent': '100.00'}
        with self.assertRaisesRegex(ValueError, 'source or exact credit'):
            QUEUE.check_ledger(row, {row['address']: function}, {row['address']: {}}, True, 'authored')


if __name__ == '__main__':
    unittest.main()
