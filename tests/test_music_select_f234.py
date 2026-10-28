"""Protect the complete R040 music-room selection code and 24 relocation fields.

The separate F234 cold replay proves compiler bytes; these fast regression
checks independently re-read original PE and review the canonical ledgers.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
UNIT='music-room-scene-update-selection-004259d0'
TARGET_SHA256='da7be73a54b77cebacf43215e0f5502722393f166bcf2c79ee92326805761c6a'

def pe_interval(virtual_address,size):
    raw=(ROOT/'resources/th075.exe').read_bytes()
    pe=struct.unpack_from('<I',raw,0x3c)[0]
    assert raw[pe:pe+4]==b'PE\0\0'
    n=struct.unpack_from('<H',raw,pe+6)[0]
    table=pe+24+struct.unpack_from('<H',raw,pe+20)[0]
    rva=virtual_address-0x400000
    for i in range(n):
        _,vs,va,rs,ptr=struct.unpack_from('<8sIIII',raw,table+40*i)
        if va<=rva and rva+size<=va+min(vs,rs):
            pos=ptr+rva-va
            return raw[pos:pos+size]
    raise AssertionError('entire original native extent is not PE-backed')

class MusicSelectF234Tests(unittest.TestCase):
    def test_exact_original_code_extent(self):
        data=pe_interval(0x004259D0,675)
        self.assertEqual(len(data),675)
        self.assertEqual(data[-1],0xC3)
        self.assertEqual(hashlib.sha256(data).hexdigest(),TARGET_SHA256)

    def test_every_true_coff_relocation_and_source_guard(self):
        with (ROOT/'config/match-units.toml').open('rb') as stream:
            unit=tomllib.load(stream)['units'][UNIT]
        adoption=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual(unit['target_address'],0x004259D0)
        self.assertEqual(unit['size'],675)
        self.assertNotIn('compare_size',unit)
        self.assertEqual(adoption['added_units'][UNIT],unit)
        self.assertEqual(len(unit['relocations']),24)
        offsets=[x['offset'] for x in unit['relocations']]
        self.assertEqual(offsets,sorted(offsets))
        self.assertEqual(len(set(offsets)),24)
        self.assertTrue(all(x['type'] in ('DIR32','REL32') for x in unit['relocations']))
        target_values=[x['target'] for x in unit['relocations']]
        self.assertEqual(target_values.count(0x00416DC0),3)
        self.assertEqual(target_values.count(0x006718F8),3)
        self.assertEqual(target_values.count(0x00407E60),2)
        self.assertEqual(target_values.count(0x00426A70),2)
        self.assertIn(0x00419CB0,target_values)
        self.assertIn(0x00407170,target_values)
        source=unit['source']
        self.assertEqual(adoption['source_sha256'][source], hashlib.sha256((ROOT/source).read_bytes()).hexdigest())

if __name__=='__main__':
    unittest.main()
