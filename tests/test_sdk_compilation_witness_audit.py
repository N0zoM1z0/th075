"""Keep metadata discovery complete and separate from ownership acceptance."""
import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('sdk_compilation_audit_test', ROOT / 'scripts/verify-sdk-compilation-witness-audit.py')
A = importlib.util.module_from_spec(spec)
spec.loader.exec_module(A)


class SDKCompilationWitnessAuditTests(unittest.TestCase):
    def setUp(self):
        self.plan = json.loads((ROOT / A.EVIDENCE).read_text())

    def test_complete_immutable_unresolved_audit(self):
        self.assertEqual(A.V.digest((ROOT / A.EVIDENCE).read_bytes()), A.MANIFEST_SHA256)
        A.verify_scope(self.plan)

    def test_no_partial_archive_inventory(self):
        self.plan['units'].pop()
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def test_no_lost_frame_inventory(self):
        unit = next(u for u in self.plan['units'] if u['frame_inventory']['count'])
        unit['frame_inventory']['count'] -= 1
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def test_no_missing_or_cropped_candidate(self):
        self.plan['reviews'][0]['frame']['frame']['procedure_size'] -= 1
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def test_field_excluded_discovery_never_becomes_exact_evidence(self):
        self.plan['reviews'][0]['comparison'] = 'exact'
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def test_metadata_absence_does_not_assign_compiler_origin(self):
        self.plan['candidates'][0]['origin']['origin'] = 'compiler'
        with self.assertRaises(ValueError):
            A.verify_scope(self.plan)

    def test_resource_framing_and_new_type_record_are_not_ignored(self):
        resource = next(u for u in self.plan['units'] if u['member_offset'] == 2148824)
        debug = resource['debug'][0]['stream']
        raw = struct.pack('<I', 1) + b''.join(struct.pack('<HH', r['length'], int(r['kind'], 16)) + bytes.fromhex(r['payload_hex']) for r in debug['records'])
        self.assertEqual(A.resource_debug(raw), debug)
        with self.assertRaises(ValueError):
            A.resource_debug(raw[:-1])
        with self.assertRaises(ValueError):
            A.resource_debug(raw + struct.pack('<HH', 2, 0x1003))

    def test_compact_inventory_still_pins_every_field(self):
        record = copy.deepcopy(self.plan['reviews'][0]['frame'])
        full = [dict(frames=[record])]
        baseline = A.compact_units(full)
        full[0]['frames'][0]['field']['symbol'] = 'unrelated_source'
        self.assertNotEqual(A.compact_units(full), baseline)
        full[0]['frames'][0] = copy.deepcopy(record)
        full[0]['frames'][0]['frame']['has_seh'] = not record['frame']['has_seh']
        self.assertNotEqual(A.compact_units(full), baseline)

    def test_fpo_decoder_requires_whole_frame_and_preserves_bit_fields(self):
        raw = struct.pack('<IIIHBB', 0, 39, 2, 3, 4, 0xdc)
        decoded = A.frame(raw)
        self.assertEqual(decoded['procedure_size'], 39)
        self.assertEqual(decoded['saved_registers'], 4)
        self.assertTrue(decoded['has_seh'])
        self.assertTrue(decoded['uses_bp'])
        self.assertEqual(decoded['frame_type'], 3)
        with self.assertRaises(ValueError):
            A.frame(raw[:-1])


if __name__ == '__main__':
    unittest.main()
