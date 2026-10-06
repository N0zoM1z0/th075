"""Protect GUID/age lookup against framing gaps and false absence conclusions."""
import importlib.util
import hashlib
import json
from pathlib import Path
import struct
import tempfile
import unittest
import uuid

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('pdb_identity_test', ROOT / 'scripts/pdb_identity.py')
P = importlib.util.module_from_spec(spec)
spec.loader.exec_module(P)
spec = importlib.util.spec_from_file_location('pdb_audit_test', ROOT / 'scripts/audit-local-pdb-identities.py')
A = importlib.util.module_from_spec(spec)
spec.loader.exec_module(A)

GUID = '9306058f-6d68-4650-b80b-1e0d05dd1e18'
REFERENCE = dict(guid=GUID, age=3)


def msf():
    raw = bytearray(8 * 512)
    raw[:32] = P.MAGIC
    struct.pack_into('<6I', raw, 32, 512, 1, 8, 20, 0, 3)
    struct.pack_into('<I', raw, 3 * 512, 6)
    struct.pack_into('<5I', raw, 6 * 512, 3, 0xffffffff, 28, 0, 5)
    struct.pack_into('<III', raw, 5 * 512, 20000404, 123, 3)
    raw[5 * 512 + 12:5 * 512 + 28] = uuid.UUID(GUID).bytes_le
    return raw


def portable():
    raw = bytearray(160)
    struct.pack_into('<4sHHII', raw, 0, b'BSJB', 1, 1, 0, 12)
    raw[16:28] = b'PDB v1.0\0\0\0\0'
    struct.pack_into('<HH', raw, 28, 0, 2)
    struct.pack_into('<II8s', raw, 32, 80, 32, b'#Pdb\0\0\0\0')
    struct.pack_into('<II4s', raw, 48, 112, 24, b'#~\0\0')
    raw[80:96] = uuid.UUID(GUID).bytes_le
    struct.pack_into('<IIQ', raw, 96, 123, 0, 0)
    return raw


class PdbIdentityTests(unittest.TestCase):
    def test_frozen_r267_snapshot_keeps_format_and_historical_gaps(self):
        plan = json.loads((ROOT / 'config/local-pdb-identity-audit-evidence.json').read_text())
        self.assertEqual((plan['required_guid'], plan['required_age']), (GUID, 3))
        self.assertEqual(plan['summary']['formats'], {'MSF7': 3203, 'PortablePDB': 21})
        self.assertEqual(plan['summary']['statuses'], {'parsed-nonmatch': 3224})
        self.assertEqual(plan['summary']['msf_trailing_extents'], 14)
        self.assertEqual(plan['initial_inventory']['subsequently_missing'], 3)
        self.assertEqual(plan['canonical_state']['pending'], 97)
        self.assertEqual(plan['decision'], 'No matching identity in the current bounded named corpus; no origin transition, source, ABI, mapping or exact credit.')
        for path, digest in plan['reader_sha256'].items():
            self.assertEqual(hashlib.sha256((ROOT / path).read_bytes()).hexdigest(), digest)

    def read(self, raw, **kwargs):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'renamed.PDB'
            path.write_bytes(raw)
            return P.read_identity(path, **kwargs)

    def test_msf_noncontiguous_directory_guid_endian_and_age(self):
        identity = self.read(msf())
        self.assertEqual(identity['guid'], GUID)
        self.assertEqual(identity['age'], 3)
        self.assertTrue(P.matches(identity, REFERENCE))

    def test_same_guid_wrong_age_is_not_a_match(self):
        raw = msf()
        struct.pack_into('<I', raw, 5 * 512 + 8, 2)
        self.assertFalse(P.matches(self.read(raw), REFERENCE))

    def test_trailing_pages_require_explicit_identity_only_mode(self):
        raw = msf() + bytes(512)
        with self.assertRaises(ValueError):
            self.read(raw)
        identity = self.read(raw, allow_trailing=True)
        self.assertFalse(identity['file_extent_equal'])
        self.assertEqual(identity['trailing_bytes'], 512)
        self.assertTrue(P.matches(identity, REFERENCE))

    def test_truncated_physical_extent_is_never_tolerated(self):
        with self.assertRaises(ValueError):
            self.read(msf()[:-1], allow_trailing=True)

    def test_page_cannot_read_beyond_declared_extent_into_trailing_bytes(self):
        raw = msf() + bytes(512)
        struct.pack_into('<I', raw, 6 * 512 + 16, 8)
        with self.assertRaises(ValueError):
            self.read(raw, allow_trailing=True)

    def test_nil_info_stream_is_a_gap(self):
        raw = msf()
        struct.pack_into('<I', raw, 6 * 512 + 8, 0xffffffff)
        with self.assertRaises(ValueError):
            self.read(raw)

    def test_unexplained_directory_bytes_are_rejected(self):
        raw = msf()
        struct.pack_into('<I', raw, 44, 24)
        with self.assertRaises(ValueError):
            self.read(raw)

    def test_unrecognized_format_is_not_nonmatch(self):
        with self.assertRaises(P.UnsupportedPDB):
            self.read(bytes(100))

    def test_portable_guid_stamp_cannot_invent_native_age(self):
        identity = self.read(portable())
        self.assertEqual((identity['guid'], identity['stamp'], identity['age']), (GUID, 123, None))
        with self.assertRaises(P.UnsupportedPDB):
            P.matches(identity, REFERENCE)
        self.assertFalse(P.matches(identity, dict(guid=str(uuid.UUID(int=1)), age=3)))

    def test_portable_out_of_file_stream_is_rejected(self):
        raw = portable()
        struct.pack_into('<I', raw, 32, len(raw))
        with self.assertRaises(ValueError):
            self.read(raw)

    def test_portable_duplicate_names_are_rejected(self):
        raw = portable()
        raw[56:64] = b'#Pdb\0\0\0\0'
        with self.assertRaises(ValueError):
            self.read(raw)

    def test_portable_referenced_table_rows_must_fill_stream(self):
        raw = portable()
        struct.pack_into('<Q', raw, 104, 1)
        with self.assertRaises(ValueError):
            self.read(raw)

    def test_audit_deduplicates_alias_and_preserves_missing_file_gap(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'x.PDB'
            path.write_bytes(msf())
            report = A.audit([str(path), str(path), str(path.parent / 'missing.pdb')], REFERENCE)
            self.assertEqual(report['summary']['unique_physical_files'], 1)
            self.assertEqual(report['summary']['enumeration_errors'], 1)
            self.assertEqual(report['summary']['statuses'], {'match': 1})

    def test_portable_equal_guid_is_an_unsupported_candidate_not_nonmatch(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'x.pdb'
            path.write_bytes(portable())
            self.assertEqual(A.audit([str(path)], REFERENCE)['summary']['statuses'], {'unsupported': 1})


if __name__ == '__main__':
    unittest.main()
