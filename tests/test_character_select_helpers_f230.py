"""Guard F230's two whole native selector branches without broad cold replay.

The original game binary, frozen manifest and actual COFF relocation targets
are checked independently of diagnostic `structural-exact` preview logs.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[1]
CASES = (
    ('character-select-scene-process-player-options-00433a40', 0x00433A40,
     404, '14fa30b51abb4fcd520b51eeab01433d87f8d9f7d30d2921b323d3d8aa4bf3fc', 18),
    ('character-select-scene-process-subselection-00433be0', 0x00433BE0,
     264, '6f6fbddee5b1d6792e9184fa7df9736f25c8f30bc35a69ee0269313bad2992b9', 16),
)


def target_bytes(addr, size):
    raw = (ROOT / 'resources/th075.exe').read_bytes()
    pe = struct.unpack_from('<I', raw, 0x3c)[0]
    if raw[pe:pe + 4] != b'PE\0\0':
        raise AssertionError('target must be the original PE')
    sections = struct.unpack_from('<H', raw, pe + 6)[0]
    sec_table = pe + 24 + struct.unpack_from('<H', raw, pe + 20)[0]
    rva = addr - 0x400000
    for i in range(sections):
        _, vs, va, rs, ptr = struct.unpack_from('<8sIIII', raw, sec_table + i * 40)
        if va <= rva and rva + size <= va + min(vs, rs):
            start = ptr + rva - va
            return raw[start:start + size]
    raise AssertionError('entire function not PE-backed')


class CharacterSelectHelpersF230Tests(unittest.TestCase):
    def test_original_whole_function_extents_and_returns(self):
        for name, address, size, digest, _ in CASES:
            with self.subTest(name=name):
                body = target_bytes(address, size)
                self.assertEqual(len(body), size)
                self.assertEqual(hashlib.sha256(body).hexdigest(), digest)
                self.assertEqual(body[-3:] if size == 404 else body[-1:],
                                 b'\xc2\x04\x00' if size == 404 else b'\xc3')

    def test_exact_units_and_all_relocation_fields_remain_registered(self):
        with (ROOT / 'config/match-units.toml').open('rb') as stream:
            units = tomllib.load(stream)['units']
        record = json.loads((ROOT / 'config/exact-adoptions.json').read_text())
        expected_fields = {CASES[0][0]: (23,39,44,136,152,157,168,183,230,235,
                                         246,267,292,297,308,329,354,359),
                           CASES[1][0]: (16,32,37,58,63,73,78,112,117,131,150,
                                         156,163,221,230,235)}
        for name, address, size, _, relocs in CASES:
            with self.subTest(name=name):
                unit = units[name]
                self.assertEqual((unit['target_address'], unit['size']), (address, size))
                self.assertNotIn('compare_size', unit)
                self.assertEqual(len(unit['relocations']), relocs)
                self.assertEqual(tuple(x['offset'] for x in unit['relocations']),expected_fields[name])
                self.assertEqual(record['added_units'][name], unit)
                source=unit['source']
                self.assertEqual(record['source_sha256'][source],
                                 hashlib.sha256((ROOT/source).read_bytes()).hexdigest())


if __name__ == '__main__':
    unittest.main()
