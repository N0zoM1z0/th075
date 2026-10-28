"""Guard the complete F235 music-room list/title rendering admissions.

This checks the original TH075 executable, physical fields and source hashes.
The full exact VC7.1 proof is the two separate targeted F235 cold replays.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[1]
CASES = (
    ('music-room-render-track-catalog-text-00426670', 0x00426670, 555, 21,
     'e4fa7a8d0959984efd8330089a6c75c21d33ef3ad7c983ff7d47bc796053ab24',
     'src/MusicListRenderF235.cpp'),
    ('music-room-render-selected-title-004268a0', 0x004268A0, 452, 16,
     'a023fd37218cf93c70c7ba2cd13ece2bcd2baafc00df0c1fb00cabedc6ba24ad',
     'src/MusicTitleRenderF235.cpp'),
)


def target_bytes(addr, size):
    raw = (ROOT / 'resources/th075.exe').read_bytes()
    off = struct.unpack_from('<I', raw, 0x3C)[0]
    assert raw[off:off + 4] == b'PE\x00\x00'
    count = struct.unpack_from('<H', raw, off + 6)[0]
    sections = off + 24 + struct.unpack_from('<H', raw, off + 20)[0]
    rva = addr - 0x400000
    for i in range(count):
        _, virtual_size, virtual_addr, raw_size, raw_off = struct.unpack_from(
            '<8sIIII', raw, sections + 40*i)
        if virtual_addr <= rva and rva + size <= virtual_addr + min(virtual_size, raw_size):
            beg = raw_off + rva - virtual_addr
            return raw[beg:beg+size]
    raise AssertionError('incomplete native target extent')


class MusicRoomRenderingF235Tests(unittest.TestCase):
    def test_whole_code_extents_and_native_return_paths(self):
        for unit, addr, size, _, expected_sha, _ in CASES:
            with self.subTest(unit=unit):
                data = target_bytes(addr, size)
                self.assertEqual(len(data), size)
                self.assertEqual(hashlib.sha256(data).hexdigest(), expected_sha)
                self.assertEqual(data[-1:] if size==555 else data[-3:],
                                 b'\xc3' if size==555 else b'\xc2\x04\x00')

    def test_all_actual_relocations_and_exact_source_hashes(self):
        with (ROOT / 'config/match-units.toml').open('rb') as stream:
            units = tomllib.load(stream)['units']
        manifest = json.loads((ROOT / 'config/exact-adoptions.json').read_text())
        for unit, addr, size, count, _, source in CASES:
            with self.subTest(unit=unit):
                entry = units[unit]
                self.assertEqual((entry['target_address'],entry['size']), (addr,size))
                self.assertNotIn('compare_size',entry)
                self.assertEqual(entry['source'],source)
                self.assertEqual(len(entry['relocations']),count)
                fields=entry['relocations']
                self.assertEqual([f['offset'] for f in fields], sorted(f['offset'] for f in fields))
                self.assertEqual(len({f['offset'] for f in fields}),count)
                self.assertTrue(all(f['type'] in ('DIR32','REL32') for f in fields))
                self.assertEqual(manifest['added_units'][unit],entry)
                self.assertEqual(manifest['source_sha256'][source], hashlib.sha256((ROOT/source).read_bytes()).hexdigest())
                targets={r['target'] for r in fields}
                self.assertIn(0x0066FE30,targets)
                self.assertIn(0x0041BF90,targets)
                self.assertIn(0x0041C060,targets)
                self.assertIn(0x0041C2E0,targets)
                self.assertIn(0x00413620,targets)
                self.assertIn(0x00640611,targets)
        self.assertIn('char message[2000];',(ROOT/CASES[0][5]).read_text())
        self.assertIn('char message[300];',(ROOT/CASES[1][5]).read_text())


if __name__=='__main__':
    unittest.main()
