"""Protect full SDK dispatch, category alternatives and exact bounded snapshot updates."""
import copy
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('endpoint_tests', ROOT / 'scripts/verify-deque-endpoint-dispatch-origins.py')
V = importlib.util.module_from_spec(spec); spec.loader.exec_module(V)


class EndpointDispatchOrigins(unittest.TestCase):
    def setUp(self):
        self.m = V.manifest()

    def reject(self, mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):
            V.verify_plan(self.m)

    def test_complete_plan(self):
        V.verify_plan(self.m)

    def test_complete_endpoint_extent(self):
        self.reject(lambda m: m['functions'][1].update(size=40))

    def test_complete_insert_parent(self):
        self.reject(lambda m: m['controls'][9].update(size=1483))

    def test_copy_parent_cannot_drop_shared_return(self):
        self.reject(lambda m: m['parents'][0]['function'].update(size='195'))

    def test_parent_source_ownership(self):
        self.reject(lambda m: m['parents'][1]['origin'].update(origin='compiler'))

    def test_real_const_endpoint_source(self):
        self.reject(lambda m: m['functions'][0].update(symbol=m['functions'][1]['symbol']))

    def test_actual_field_destination(self):
        self.reject(lambda m: m['controls'][6]['bindings'][0].update(target_address='0x004239A0'))

    def test_no_field_masking(self):
        self.reject(lambda m: m['controls'][2]['bindings'].pop())

    def test_real_field_source_owner(self):
        self.reject(lambda m: m['controls'][4]['section']['fields'][1]['symbol'].update(symbol='FakeAdvance'))

    def test_category_alternative_is_whole(self):
        self.reject(lambda m: m['controls'][10].update(size=10))

    def test_category_alternative_has_independent_trait_type(self):
        self.reject(lambda m: m['controls'][10]['source_definition'].update(symbol=m['controls'][11]['source_definition']['symbol']))

    def test_same_length_input_category_is_not_byte_equal(self):
        self.reject(lambda m: m['negative_operations'][0].update(tag='random_access_iterator_tag'))

    def test_input_distance_is_whole_different_operation(self):
        self.reject(lambda m: m['negative_operations'][1]['section'].update(size=27))

    def test_bidirectional_advance_is_whole_different_operation(self):
        self.reject(lambda m: m['negative_operations'][2]['section'].update(size=17))

    def test_actual_source_overload(self):
        self.reject(lambda m: m['negative_operations'][1]['source_definition'].update(symbol='OrdinaryDistance'))

    def test_full_sdk_traits_layout(self):
        self.reject(lambda m: m['layout_values'].pop())

    def test_actual_observation_include(self):
        self.reject(lambda m: m['headers'].update({'probes/VC7PairedDequeProducers.cpp': '0' * 64}))

    def test_actual_sdk_iterator_header(self):
        self.reject(lambda m: m['headers'].pop(next(k for k in m['headers'] if k.endswith('/iterator'))))

    def test_whole_ordinary_emission(self):
        self.reject(lambda m: m['emission'].pop())

    def test_r085_algorithms_preserved(self):
        self.reject(lambda m: m['legacy'][0]['origin'].update(evidence_id='R159'))

    def test_no_new_game_source(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))

    def test_no_new_private_abi(self):
        self.reject(lambda m: m['functions'][5]['accepted_function'].update(calling_convention='stdcall'))

    def test_no_new_exact_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_canonical_extent_preserved(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(span_end='0x00422B73'))

    def test_eight_exact_bounded_transitions(self):
        for row in self.m['functions']:
            old = dict(function=row['original_function'], origin=row['original_origin'])
            self.assertTrue(V.accepted_snapshot(old, row['accepted_function'], row['accepted_origin']))
            self.assertTrue(V.PAIRED.preserved_snapshot(old, row['accepted_function'], row['accepted_origin']))

    def test_r158_parent_and_alignment_transitions(self):
        rows = {r['address']: r for r in self.m['functions']}
        old = V.COPY.manifest()
        for function, origin in [(old['parents'][1]['function'], old['parents'][1]['origin']),
                                 (old['alignment'][0]['next_function'], old['alignment'][0]['next_origin'])]:
            row = rows[function['address']]
            self.assertTrue(V.PAIRED.preserved_snapshot(dict(function=function, origin=origin), row['accepted_function'], row['accepted_origin']))

    def test_unrelated_metadata_is_rejected(self):
        row = self.m['functions'][0]; f = copy.deepcopy(row['accepted_function']); f['notes'] += ' changed'
        self.assertFalse(V.accepted_snapshot(dict(function=row['original_function'], origin=row['original_origin']), f, row['accepted_origin']))

    def test_unrelated_old_snapshot_is_rejected(self):
        row = self.m['functions'][0]; old = dict(function=copy.deepcopy(row['original_function']), origin=row['original_origin']); old['function']['size'] = '34'
        self.assertFalse(V.accepted_snapshot(old, row['accepted_function'], row['accepted_origin']))

    def test_r158_pending_copy_cannot_gain_owner(self):
        row = V.COPY.manifest()['functions'][0]; f = dict(row['accepted_function']); f['owner'] = 'compiler'
        self.assertFalse(V.accepted_snapshot(dict(function=row['original_function'], origin=row['original_origin']), f, row['accepted_origin']))

    def test_ledger_evidence_only_mode(self):
        row = self.m['functions'][0]
        V.check_ledger(row, row['original_function'], row['original_origin'], evidence_only=True)
        with self.assertRaises(ValueError):
            V.check_ledger(row, row['original_function'], row['original_origin'])


if __name__ == '__main__':
    unittest.main()
