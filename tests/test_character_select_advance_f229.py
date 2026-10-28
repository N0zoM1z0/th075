"""Lock the exact whole F229 character-select dispatch and its owned table.

This lightweight test is not a new cold-replay receipt; cold replay is run
separately only for the affected F229 unit during acceptance.
"""
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[1]
UNIT = 'character-select-scene-advance-00433470'
CODE_SIZE = 1442
COMPARE_SIZE = 1478
CODE_SHA256 = '88d95852e72a14f2c4769a778506b382ae586604e6e7ca6db04a718942550a68'
FULL_SHA256 = 'dc3dd8d70688b8abb748c39579d1d997826d09a14f05e6542494f22351d7e679'
TABLE = (0x004338E2, 0x004338F0, 0x004338FE, 0x00433926,
         0x0043390C, 0x00433926, 0x00433926, 0x00433926, 0x0043391A)


def native_bytes(address, count):
    raw = (ROOT / 'resources/th075.exe').read_bytes()
    pe_offset = struct.unpack_from('<I', raw, 0x3C)[0]
    assert raw[pe_offset:pe_offset + 4] == b'PE\0\0'
    section_count = struct.unpack_from('<H', raw, pe_offset + 6)[0]
    table_offset = pe_offset + 24 + struct.unpack_from('<H', raw, pe_offset + 20)[0]
    rva = address - 0x400000
    for i in range(section_count):
        _, vsize, vaddr, rawsize, rawptr = struct.unpack_from('<8sIIII', raw, table_offset + i * 40)
        if vaddr <= rva and rva + count <= vaddr + min(vsize, rawsize):
            start = rawptr + rva - vaddr
            return raw[start:start + count]
    raise AssertionError('complete native extent not backed by target PE section')


class CharacterSelectAdvanceF229Tests(unittest.TestCase):
    def test_complete_pinned_code_and_nine_owned_dispatch_addresses(self):
        whole = native_bytes(0x00433470, COMPARE_SIZE)
        self.assertEqual(len(whole), COMPARE_SIZE)
        self.assertEqual(hashlib.sha256(whole[:CODE_SIZE]).hexdigest(), CODE_SHA256)
        self.assertEqual(hashlib.sha256(whole).hexdigest(), FULL_SHA256)
        self.assertEqual(whole[CODE_SIZE - 1], 0xC3)
        self.assertEqual(struct.unpack_from('<9I', whole, CODE_SIZE), TABLE)

    def test_manifest_registers_every_physical_table_field_without_code_credit(self):
        with (ROOT / 'config/match-units.toml').open('rb') as stream:
            unit = tomllib.load(stream)['units'][UNIT]
        self.assertEqual(unit['target_address'], 0x00433470)
        self.assertEqual(unit['size'], CODE_SIZE)
        self.assertEqual(unit['compare_size'], COMPARE_SIZE)
        self.assertEqual(len(unit['relocations']), 76)
        table_relocs = unit['relocations'][-9:]
        self.assertEqual([x['offset'] for x in table_relocs], list(range(CODE_SIZE, COMPARE_SIZE, 4)))
        self.assertEqual([x['type'] for x in table_relocs], ['DIR32'] * 9)
        self.assertEqual(tuple(x['target'] for x in table_relocs), TABLE)
        self.assertEqual(unit['source'], 'src/CharacterSelectAdvanceF229.cpp')
        adoptions = json.loads((ROOT / 'config/exact-adoptions.json').read_text())
        self.assertEqual(adoptions['added_units'][UNIT], unit)
        source_sha256 = hashlib.sha256((ROOT / unit['source']).read_bytes()).hexdigest()
        self.assertEqual(adoptions['source_sha256'][unit['source']], source_sha256)


if __name__ == '__main__':
    unittest.main()
