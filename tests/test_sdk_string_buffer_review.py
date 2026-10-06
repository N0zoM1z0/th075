"""Guard whole unresolved contributions and distinct compiler/source witnesses."""
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('string_buffer_review_test', ROOT / 'scripts/verify-sdk-string-buffer-review.py')
V = importlib.util.module_from_spec(spec)
spec.loader.exec_module(V)


class StringBufferReviewTests(unittest.TestCase):
    def setUp(self):
        self.plan = json.loads((ROOT / V.EVIDENCE).read_text())

    def test_complete_frozen_unresolved_review(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_scope(self.plan)

    def test_no_isolated_forwarder_in_place_of_full_contribution(self):
        self.plan['native']['code'] = [r for r in self.plan['native']['code'] if r['source']['section'] == 52]
        with self.assertRaises(ValueError):
            V.verify_scope(self.plan)

    def test_no_factory_or_constructor_prefix(self):
        r = next(r for r in self.plan['native']['code'] if r['source']['section'] == 54)
        r['size'] -= 1
        with self.assertRaises(ValueError):
            V.verify_scope(self.plan)

    def test_no_vtable_or_constant_omission(self):
        self.plan['native']['data'].pop()
        with self.assertRaises(ValueError):
            V.verify_scope(self.plan)

    def test_compiler_records_are_unit_specific(self):
        self.plan['native']['debug']['records'][1]['compile']['backend'] = [13, 10, 3077]
        with self.assertRaises(ValueError):
            V.verify_scope(self.plan)

    def test_positive_implicit_family_cannot_be_discarded(self):
        cold = self.plan['cold'][0]
        r = next(r for r in cold['comparisons'] if r['symbol'] == '??1ImplicitDestructorBuffer@@UAE@XZ')
        r['whole_equal'] = False
        with self.assertRaises(ValueError):
            V.verify_scope(self.plan)

    def test_explicit_negative_cannot_be_cropped_to_five(self):
        r = next(r for r in self.plan['cold'][1]['comparisons'] if r['symbol'] == '??1ExplicitDestructorBuffer@@UAE@XZ')
        r['size'] = 5
        with self.assertRaises(ValueError):
            V.verify_scope(self.plan)

    def test_unknown_is_not_changed_by_source_association(self):
        self.plan['protected_pairs'][1]['origin']['origin'] = 'compiler'
        with self.assertRaises(ValueError):
            V.verify_scope(self.plan)

    def test_original_record_framing_and_private_type_absence(self):
        debug = self.plan['native']['debug']
        raw = struct.pack('<I', 2) + b''.join(struct.pack('<HH', r['length'], int(r['kind'], 16)) + bytes.fromhex(r['payload_hex']) for r in debug['records'])
        self.assertEqual(V.source_debug(raw), debug)
        with self.assertRaises(ValueError):
            V.source_debug(raw[:-1])
        # A source/type record would be new evidence, never silently ignored.
        with self.assertRaises(ValueError):
            V.source_debug(raw + struct.pack('<HH', 2, 0x1003))


if __name__ == '__main__':
    unittest.main()
