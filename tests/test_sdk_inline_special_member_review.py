"""Protect full inline linkage alternatives and the exact external PDB identity."""
import importlib.util
import json
from pathlib import Path
import struct
import unittest
from unittest.mock import patch
import uuid

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('inline_special_member_test', ROOT / 'scripts/verify-sdk-inline-special-member-review.py')
A = importlib.util.module_from_spec(spec)
spec.loader.exec_module(A)


class InlineSpecialMemberReviewTests(unittest.TestCase):
    def setUp(self):
        self.plan = json.loads((ROOT / A.EVIDENCE).read_text())

    def test_complete_frozen_unresolved_review(self):
        self.assertEqual(A.V.digest((ROOT / A.EVIDENCE).read_bytes()), A.MANIFEST_SHA256)
        A.verify_scope(self.plan)

    def test_inline_user_constructor_positive_cannot_be_erased(self):
        self.plan['cold'][0]['comparisons'][0]['whole_equal'] = False
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def test_any_selection_does_not_mean_generated(self):
        self.plan['protected_pairs'][0]['origin']['origin'] = 'compiler'
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def test_inline_explicit_destructor_is_not_cropped_to_target_five(self):
        r = next(r for r in self.plan['cold'][0]['comparisons'] if r['symbol'] == '??1ExplicitInlineStringBuffer@@UAE@XZ')
        r['size'] = 5
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def test_derived_inlining_negatives_keep_whole_extents(self):
        r = next(r for r in self.plan['cold'][1]['comparisons'] if r['symbol'] == '??0ExplicitInlineStringBuffer@@QAE@XZ')
        r['size'] = 22
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def test_implicit_positive_remains_separate_from_explicit_negative(self):
        r = next(r for r in self.plan['cold'][1]['comparisons'] if r['symbol'] == '??1ImplicitInlineStringBuffer@@UAE@XZ')
        r['selection'] = 1
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def test_all_ordinary_sections_are_retained(self):
        self.plan['cold'][0]['emission'].pop()
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def pdb_fixture(self):
        r = self.plan['target_symbol_reference']
        entry = r['entry']
        payload = b'RSDS' + uuid.UUID(r['guid']).bytes_le + struct.pack('<I', r['age']) + bytes.fromhex(r['path_bytes_hex'])
        raw = struct.pack('<IIHHIIII', *[entry[k] for k in ['characteristics', 'timestamp', 'major', 'minor', 'type', 'size', 'data_rva', 'file_offset']])
        body = bytearray(entry['file_offset'] + len(payload))
        pe = 64
        struct.pack_into('<I', body, 60, pe)
        body[pe:pe+4] = b'PE\0\0'
        struct.pack_into('<HHIIIHH', body, pe+4, 0x14c, 5, 0, 0, 0, 224, 0)
        struct.pack_into('<H', body, pe+24, 0x10b)
        struct.pack_into('<I', body, pe+24+92, 16)
        struct.pack_into('<II', body, pe+24+96+48, r['debug_directory']['rva'], 28)
        body[entry['file_offset']:] = payload
        return bytes(body), raw, payload

    def test_exact_pdb_identity_and_utf8_path_round_trip(self):
        body, raw, payload = self.pdb_fixture()
        with patch.object(A.V.C, 'pe_bytes_at', side_effect=[raw, payload]):
            self.assertEqual(A.target_symbol_reference(body), self.plan['target_symbol_reference'])

    def test_pdb_rva_and_file_payload_must_agree(self):
        body, raw, payload = self.pdb_fixture()
        with patch.object(A.V.C, 'pe_bytes_at', side_effect=[raw, payload[:-1] + b'x']):
            with self.assertRaises(ValueError):
                A.target_symbol_reference(body)


if __name__ == '__main__':
    unittest.main()
