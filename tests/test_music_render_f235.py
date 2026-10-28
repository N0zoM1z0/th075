"""Independently pin complete F235 font-rendering functions and their real fields.

Do not cold-rebuild prior units here: the new F235 units were independently
cold-replayed and only their native mapping and immutable source are tested.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
CASES=(
 ('music-room-render-track-catalog-text-00426670',0x00426670,555,
  'e4fa7a8d0959984efd8330089a6c75c21d33ef3ad7c983ff7d47bc796053ab24',21),
 ('music-room-render-selected-title-004268a0',0x004268a0,452,
  'a023fd37218cf93c70c7ba2cd13ece2bcd2baafc00df0c1fb00cabedc6ba24ad',16),
)

def original_code(address,size):
    data=(ROOT/'resources/th075.exe').read_bytes()
    pe=struct.unpack_from('<I',data,0x3c)[0]
    assert data[pe:pe+4]==b'PE\0\0'
    num=struct.unpack_from('<H',data,pe+6)[0]
    sections=pe+24+struct.unpack_from('<H',data,pe+20)[0]
    rva=address-0x400000
    for i in range(num):
        _,vs,va,rs,p=struct.unpack_from('<8sIIII',data,sections+i*40)
        if va<=rva and rva+size<=va+min(vs,rs):
            start=p+rva-va
            return data[start:start+size]
    raise AssertionError('native original complete extent is not PE-backed')

class MusicRenderF235Tests(unittest.TestCase):
    def test_original_complete_code_hashes_and_native_returns(self):
        for name,address,size,digest,fields in CASES:
            with self.subTest(name=name):
                body=original_code(address,size)
                self.assertEqual(len(body),size)
                self.assertEqual(hashlib.sha256(body).hexdigest(),digest)
                self.assertTrue(body.endswith(b'\xc3' if size==555 else b'\xc2\x04\x00'))

    def test_all_real_eh_gs_font_and_deletion_fields_are_pinned(self):
        with (ROOT/'config/match-units.toml').open('rb') as stream:
            units=tomllib.load(stream)['units']
        adoption=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        for name,address,size,digest,field_count in CASES:
            with self.subTest(name=name):
                u=units[name]
                self.assertEqual((u['target_address'],u['size']),(address,size))
                self.assertNotIn('compare_size',u)
                self.assertEqual(len(u['relocations']),field_count)
                self.assertEqual(adoption['added_units'][name],u)
                offsets=[r['offset'] for r in u['relocations']]
                self.assertEqual(offsets,sorted(offsets))
                self.assertEqual(len(set(offsets)),field_count)
                targets=[r['target'] for r in u['relocations']]
                self.assertEqual(targets.count(0x0041BF90),1)
                self.assertEqual(targets.count(0x0041C060),1)
                self.assertEqual(targets.count(0x0041C2E0),1)
                self.assertEqual(targets.count(0x00413620),1)
                self.assertEqual(targets.count(0x0064159D),1)
                self.assertEqual(targets.count(0x0066FE30),1)
                self.assertEqual(targets.count(0x00640611),1)
                self.assertIn(0x00000000,targets)
                self.assertTrue(all(r['type'] in ('DIR32','REL32') for r in u['relocations']))
                source=u['source']
                self.assertEqual(adoption['source_sha256'][source],hashlib.sha256((ROOT/source).read_bytes()).hexdigest())

if __name__=='__main__':
    unittest.main()
