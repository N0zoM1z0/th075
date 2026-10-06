"""Protect complete archive coverage and reject signatures masquerading as PDBs."""
import gzip
import hashlib
import importlib.util
import io
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('supplied_symbol_archive_test', ROOT / 'scripts/audit-supplied-symbol-archive.py')
A = importlib.util.module_from_spec(spec)
spec.loader.exec_module(A)


def table():
    plain = bytearray(216)
    for i, (name, size, offset) in enumerate([(b'a.pdb', 3, 218), (b'b.dat', 2, 221)]):
        plain[i*108:i*108+len(name)] = name
        struct.pack_into('<II', plain, i*108+100, size, offset)
    key, step, encrypted = 100, 100, bytearray()
    for byte in plain:
        encrypted.append(byte ^ key)
        key, step = (key + step) & 255, (step + 77) & 255
    return struct.pack('<H', 2) + encrypted


class SuppliedSymbolArchiveTests(unittest.TestCase):
    def test_all_bytes_hashed_and_cross_chunk_signature_counted_once(self):
        raw = b'x' * ((1 << 20) - 2) + A.PATTERNS['msf7'] + A.PATTERNS['msf7']
        report, prefix = A.scan(io.BytesIO(raw))
        self.assertEqual(report['size'], len(raw))
        self.assertEqual(report['sha256'], hashlib.sha256(raw).hexdigest())
        self.assertEqual(report['hits']['msf7'], [(1 << 20) - 2, (1 << 20) + 30])

    def test_gzip_cross_chunk_window_validates_complete_trailer(self):
        raw = b'x' * ((1 << 20) - 2) + gzip.compress(b'ordinary content', mtime=0)
        report, prefix = A.scan(io.BytesIO(raw))
        self.assertEqual(len(report['gzip_windows']), 1)
        self.assertEqual(report['gzip_windows'][0]['status'], 'valid')
        self.assertEqual(report['gzip_windows'][0]['output_size'], len(b'ordinary content'))

    def test_truncated_gzip_stays_a_gap(self):
        self.assertEqual(A.gzip_window(gzip.compress(b'content')[:-5])['status'], 'incomplete-window-gap')

    def test_long_optional_gzip_header_is_checked_past_initial_window(self):
        normal = gzip.compress(b'content', mtime=0)
        extended = normal[:3] + b'\x04' + normal[4:10] + struct.pack('<H', 6000) + bytes(6000) + normal[10:]
        report, prefix = A.scan(io.BytesIO(extended))
        self.assertEqual(report['gzip_windows'][0]['status'], 'valid')
        self.assertEqual(A.gzip_window(extended[:4096])['status'], 'incomplete-window-gap')

    def test_accidental_gzip_magic_is_invalid(self):
        self.assertEqual(A.gzip_window(b'\x1f\x8b\x08\xff' + bytes(16))['status'], 'invalid')

    def test_full_directory_recurrence_matches_closed_form_and_ranges(self):
        result = A.directory(table(), 223)
        self.assertEqual(result['count'], 2)
        self.assertEqual(result['rows'][0], dict(name='a.pdb', name_bytes_hex=b'a.pdb'.hex(), size=3, offset=218))
        self.assertEqual(result['rows'][1]['offset'], 221)

    def test_directory_requires_complete_table_and_payload_coverage(self):
        for prefix, size in [(table()[:-1], 223), (table(), 222), (table(), 224)]:
            with self.subTest(size=size, length=len(prefix)):
                with self.assertRaises(ValueError):
                    A.directory(prefix, size)

    def test_directory_rejects_nonterminated_fixed_name(self):
        raw = bytearray(table())
        for i in range(100):
            raw[2+i] = ord('x') ^ ((100 + 100*i + 77*i*(i-1)//2) & 255)
        with self.assertRaises(ValueError):
            A.directory(raw, 223)

    def test_archive_listing_cannot_omit_entries_or_encryption_gap(self):
        rows = ['Path = file' + str(i) + '\nFolder = -\nSize = 0\nCRC = 00000000\nEncrypted = -' for i in range(16)]
        raw = '----------\n' + '\n\n'.join(rows)
        self.assertEqual(len(A.listing(raw)), 16)
        for changed in [raw.replace('Encrypted = -', 'Encrypted = +', 1), '----------\n' + rows[0]]:
            with self.assertRaises(ValueError):
                A.listing(changed)


if __name__ == '__main__':
    unittest.main()
