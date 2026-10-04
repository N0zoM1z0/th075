"""Protect complete element-source alternatives and bounded follow-up transitions."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('element_tests', ROOT / 'scripts/verify-deque-element-origins.py')
V = importlib.util.module_from_spec(spec)
spec.loader.exec_module(V)


class DequeElementOrigins(unittest.TestCase):
    def setUp(self):
        self.m = V.manifest()

    def reject(self, mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):
            V.verify_plan(self.m)

    def test_complete_plan(self):
        V.verify_plan(self.m)

    def test_four_whole_owners(self):
        self.reject(lambda m: m['functions'].pop())

    def test_no_truncated_aux(self):
        self.reject(lambda m: m['functions'][1].update(size=107))

    def test_actual_typed_parent(self):
        self.reject(lambda m: m['functions'][0].update(parent='0x0042E000'))

    def test_no_pointer_map_allocator(self):
        self.reject(lambda m: m['functions'][0].update(symbol=m['functions'][0]['symbol'].replace('@UQueueRecordObservation', '@PAUQueueRecordObservation')))

    def test_no_wrong_observation(self):
        self.reject(lambda m: m['functions'][3].update(observation_type='QueueRecordObservation'))

    def test_parent_cannot_inherit_game_origin(self):
        self.reject(lambda m: m['parents'][0]['origin'].update(origin='authored'))

    def test_parent_complete_extent(self):
        self.reject(lambda m: m['parents'][1]['function'].update(size='28'))

    def test_ordinary_control_cannot_be_omitted(self):
        self.reject(lambda m: m['controls'].pop(0))

    def test_real_ordinary_source(self):
        self.reject(lambda m: m['functions'][0].update(ordinary_symbol='?VendorAllocator@@YAPAXI@Z'))

    def test_full_exception_carrier(self):
        self.reject(lambda m: m['controls'][4].update(size=10))

    def test_full_data_including_unwind(self):
        self.reject(lambda m: m['controls'][5].update(size=28))

    def test_actual_field(self):
        self.reject(lambda m: m['controls'][1]['bindings'][4].update(target_address='0x00422A50'))

    def test_whole_independent_owner(self):
        self.reject(lambda m: m['controls'][1].update(retained_symbol=m['controls'][0]['retained_symbol']))

    def test_no_new_source_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))

    def test_no_new_private_abi(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(calling_convention='cdecl'))

    def test_no_new_exact_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_preserve_canonical_boundary(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(span_end='0x004228B4'))

    def test_complete_emission(self):
        self.reject(lambda m: m['emission'].pop())

    def test_actual_sdk_headers(self):
        self.reject(lambda m: m['headers'].pop(next(k for k in m['headers'] if k.endswith('/xmemory'))))

    def test_actual_included_observation_source(self):
        self.reject(lambda m: m['headers'].update({'probes/VC7PairedDequeProducers.cpp': '0' * 64}))

    def test_whole_retained_layout(self):
        self.reject(lambda m: m['retained_layout'].pop())

    def test_accepted_snapshot_is_exact_bounded_transition(self):
        for row in self.m['functions']:
            old = dict(function=row['original_function'], origin=row['original_origin'])
            self.assertTrue(V.accepted_snapshot(old, row['accepted_function'], row['accepted_origin']))
            self.assertTrue(V.PAIRED.preserved_snapshot(old, row['accepted_function'], row['accepted_origin']))

    def test_snapshot_rejects_unrelated_metadata_change(self):
        row = self.m['functions'][0]; f = copy.deepcopy(row['accepted_function']); f['notes'] += ' altered'
        old = dict(function=row['original_function'], origin=row['original_origin'])
        self.assertFalse(V.accepted_snapshot(old, f, row['accepted_origin']))

    def test_snapshot_rejects_wrong_original_row(self):
        row = self.m['functions'][0]; old = dict(function=copy.deepcopy(row['original_function']), origin=row['original_origin'])
        old['function']['size'] = '19'
        self.assertFalse(V.accepted_snapshot(old, row['accepted_function'], row['accepted_origin']))

    def test_unchanged_snapshot_is_preserved(self):
        row = self.m['functions'][0]; old = dict(function=row['original_function'], origin=row['original_origin'])
        self.assertTrue(V.PAIRED.preserved_snapshot(old, row['original_function'], row['original_origin']))

    def test_ledger_keeps_pending_evidence_mode(self):
        row = self.m['functions'][0]
        V.check_ledger(row, row['original_function'], row['original_origin'], evidence_only=True)
        with self.assertRaises(ValueError):
            V.check_ledger(row, row['original_function'], row['original_origin'])

    def test_ledger_rejects_false_acceptance(self):
        row = self.m['functions'][0]; o = dict(row['accepted_origin']); o['evidence_id'] = 'R156'
        with self.assertRaises(ValueError):
            V.check_ledger(row, row['accepted_function'], o)


if __name__ == '__main__':
    unittest.main()
