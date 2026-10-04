"""Reject incomplete or incorrectly typed nested deque provenance."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('nested_helpers', ROOT / 'scripts/verify-nested-deque-helper-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class NestedDequeHelperTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def node(self, address):
        return next(r for r in self.m['solutions'][0]['nodes'] if r['address'] == address)

    def test_complete_plan(self):
        REVIEW.verify_plan(self.m)

    def test_prefix_does_not_replace_complete_const_dereference(self):
        self.m['functions'][3]['size'] -= 1
        self.reject()

    def test_count_observation_does_not_gain_game_origin(self):
        self.m['functions'].append(dict(address='0x0045DD00', size=66, decision='authored'))
        self.reject()

    def test_independent_graph_cannot_omit_constructor(self):
        self.m['solutions'][0]['nodes'].pop()
        self.reject()

    def test_original_callee_extent_cannot_change(self):
        self.node('0x00422500')['ledger_size'] -= 1
        self.reject()

    def test_edge_cannot_substitute_equal_shaped_other_type(self):
        self.node('0x004215C0')['relocations'][0]['symbol'] = 'unresolved_other_type'
        self.reject()

    def test_relative_call_cannot_be_absolute(self):
        self.node('0x004215C0')['relocations'][0]['type'] = 'DIR32'
        self.reject()

    def test_addend_cannot_offset_independent_owner(self):
        self.node('0x004215C0')['relocations'][0]['addend'] = 1
        self.reject()

    def test_actual_call_site_cannot_move(self):
        self.node('0x004215C0')['relocations'][0]['offset'] += 1
        self.reject()

    def test_mutable_dereference_must_reach_const_owner(self):
        self.node('0x00421FC0')['relocations'][0]['target_address'] = '0x00422540'
        self.reject()

    def test_subtraction_assignment_is_not_iterator_decrement(self):
        self.node('0x00422540')['symbol'] = self.node('0x00422540')['symbol'].replace('??Ziterator@', '??Fiterator@')
        self.reject()

    def test_subtraction_assignment_retains_signed_argument(self):
        self.node('0x00422540')['symbol'] = self.node('0x00422540')['symbol'].replace('QAEAAV012@H@Z', 'QAEAAV012@I@Z')
        self.reject()

    def test_one_equal_type_does_not_establish_original_element(self):
        self.m['solutions'].pop()
        self.reject()

    def test_equal_shape_family_cannot_discard_rejected_types(self):
        self.m['functions'][0]['shape_symbols'].pop()
        self.reject()

    def test_rejected_const_owner_cannot_lose_real_difference(self):
        owner = self.m['rejected_families'][0]['complete_const_owner']
        owner['size_difference'] = 0
        owner['non_field_differences'] = 0
        self.reject()

    def test_rejected_family_cannot_use_partial_source_graph(self):
        self.m['rejected_families'][0]['complete_source_symbols'].pop()
        self.reject()

    def test_sdk_layout_cannot_be_prefix(self):
        self.m['sdk_layout']['size'] -= 4
        self.reject()

    def test_independent_whole_parent_proof_is_required(self):
        self.m['retained_verifier'] = 'verify-sdk-origins.py'
        self.reject()

