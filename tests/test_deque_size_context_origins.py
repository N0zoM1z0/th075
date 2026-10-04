"""Guard independent receiver provenance, full SDK families and pending nested origins."""
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('size_context', ROOT / 'scripts/verify-deque-size-context-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class DequeSizeContextTests(unittest.TestCase):
    def setUp(self):
        self.m = json.loads((ROOT / 'config/deque-size-context-origin-evidence.json').read_text())

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def test_complete_plan(self):
        REVIEW.verify_plan(self.m)

    def test_identical_getter_without_context_is_insufficient(self):
        self.m['contexts'].pop()
        self.reject()

    def test_reviewed_child_without_shared_receiver_is_insufficient(self):
        self.m['contexts'][0]['instruction_windows'][1][0]['operands'] = 'ecx, 0x6713b4'
        self.reject()

    def test_intervening_call_cannot_preserve_assumed_receiver(self):
        window = self.m['contexts'][0]['instruction_windows'][0]
        window.insert(1, dict(address='0x00407A7C', mnemonic='call', operands='0x00401000'))
        self.reject()

    def test_indexed_receiver_register_variants_prove_same_object(self):
        windows = self.m['contexts'][-1]['instruction_windows']
        self.assertEqual(REVIEW.receiver(windows[0]), REVIEW.receiver(windows[1]))
        self.assertEqual(REVIEW.receiver(windows[0]), ('indexed-local', -52, -4, 20, 4))

    def test_indexed_receiver_with_different_owner_is_insufficient(self):
        self.m['contexts'][-1]['instruction_windows'][1][2]['operands'] = 'ecx, dword ptr [ebp - 0x38]'
        self.reject()

    def test_indexed_receiver_with_different_index_is_insufficient(self):
        self.m['contexts'][-1]['instruction_windows'][0][0]['operands'] = 'ecx, dword ptr [ebp - 8]'
        self.reject()

    def test_indexed_receiver_with_different_field_is_insufficient(self):
        self.m['contexts'][-1]['instruction_windows'][1][3]['operands'] = 'ecx, [ecx + eax + 8]'
        self.reject()

    def test_mapped_library_name_does_not_replace_whole_anchor(self):
        self.m['anchors'].clear()
        self.reject()

    def test_wrong_actual_callee_is_rejected(self):
        self.m['contexts'][0]['instruction_windows'][1][-1]['operands'] = '0x4094b0'
        self.reject()

    def test_prefix_cannot_replace_complete_getter(self):
        self.m['functions'][0]['size'] = 14
        self.reject()

    def test_source_family_does_not_establish_original_element_type(self):
        self.m['functions'][0]['shape_symbols'] = [self.m['functions'][0]['coff_symbol']]
        self.reject()

    def test_sdk_partial_container_layout_is_rejected(self):
        self.m['sdk_layout']['values'][0] = 16
        self.reject()

    def test_independent_cold_context_proof_is_required(self):
        self.m['retained_verifiers'].pop()
        self.reject()

    def test_nested_shape_cannot_gain_origin_credit(self):
        self.m['pending'][0]['decision'] = 'library'
        self.reject()
