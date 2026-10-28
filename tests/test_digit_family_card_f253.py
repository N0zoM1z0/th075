"""Pin five individually cold-exact F252/F253 source extents, not broad replay."""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
CASES=(
    ('music-room-draw-number-00427180',0x00427180,377,9,'8063f13302db50d2849318f67155f3e7b4a49e5af78a46312814af2c461659c5'),
    ('replay-scene-draw-number-0042ae70',0x0042AE70,377,9,'d0861536a0d25c2ad32eeca09c0de0a2d2d0177f0c6702c90309d27b4acb5295'),
    ('replay-scene-draw-slot-number-0042bfd0',0x0042BFD0,377,9,'d69ae88f62db4d39274c7289cc25a5b9460aca29e7b276272cfc380e15835d04'),
    ('result-scene-draw-counter-004315f0',0x004315F0,377,9,'382a5bed703c2eb0ef616aeb08a96edfd4b90c92b8caa4bd768e094d9c4270f6'),
    ('card-list-encode-character-file-00431d60',0x00431D60,432,15,'7260a159f1b3d592a52ace497f27a83264ac4b44321806b2681494bff65ea2ab'),
)


def native_bytes(addr,size):
    raw=(ROOT/'resources/th075.exe').read_bytes()
    pe=struct.unpack_from('<I',raw,0x3c)[0]
    if raw[pe:pe+4]!=b'PE\x00\x00':raise AssertionError('original TH075 executable required')
    n=struct.unpack_from('<H',raw,pe+6)[0]
    tbl=pe+24+struct.unpack_from('<H',raw,pe+20)[0]
    rva=addr-0x400000
    for i in range(n):
        _,vs,va,rs,ptr=struct.unpack_from('<8sIIII',raw,tbl+i*40)
        if va<=rva and rva+size<=va+min(vs,rs):return raw[ptr+rva-va:ptr+rva-va+size]
    raise AssertionError('whole native extent not mapped')


class DigitFamilyAndCardF253Tests(unittest.TestCase):
    def test_full_native_code_extents_and_returns(self):
        for unit,addr,size,_,digest in CASES:
            with self.subTest(unit=unit):
                body=native_bytes(addr,size)
                self.assertEqual(len(body),size)
                self.assertEqual(hashlib.sha256(body).hexdigest(),digest)
                self.assertEqual(body[-3:],b'\xc2\x04\x00' if size==432 else b'\xc2\x14\x00')

    def test_all_51_physical_fields_and_source_hashes(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            units=tomllib.load(f)['units']
        m=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual(sum(x[2] for x in CASES),1940)
        self.assertEqual(sum(x[3] for x in CASES),51)
        for unit,addr,size,nreloc,_ in CASES:
            with self.subTest(unit=unit):
                entry=units[unit]
                self.assertEqual((entry['target_address'],entry['size']), (addr,size))
                self.assertNotIn('compare_size',entry)
                self.assertEqual(len(entry['relocations']),nreloc)
                self.assertEqual(entry,m['added_units'][unit])
                offsets=[r['offset'] for r in entry['relocations']]
                self.assertEqual(offsets,sorted(offsets))
                self.assertEqual(len(set(offsets)),nreloc)
                self.assertTrue(all(r['type'] in ('REL32','DIR32') for r in entry['relocations']))
                source=entry['source']
                self.assertEqual(m['source_sha256'][source],hashlib.sha256((ROOT/source).read_bytes()).hexdigest())
                targets=[r['target'] for r in entry['relocations']]
                if size==377:
                    self.assertEqual(targets.count(0x0040C9A0),2)
                    self.assertEqual(targets.count(0x00411500),2)
                    self.assertEqual(targets.count(0x00657210),2)
                else:
                    for t in (0x00657130,0x0065712C,0x00657124,0x0064169D,0x00640611):
                        self.assertIn(t,targets)


if __name__=='__main__':unittest.main()
