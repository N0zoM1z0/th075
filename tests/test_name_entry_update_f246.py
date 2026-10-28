"""Fast complete-native F246 name-entry checks without broad cold replay."""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
UNIT='name-entry-scene-update-player-0042a340'
SHA='a8e48f26ffb990e03b5420dd7f1be9cac608b81502f89c902c9883f299c955da'

def native(va,size):
    raw=(ROOT/'resources/th075.exe').read_bytes()
    pe=struct.unpack_from('<I',raw,0x3c)[0]
    assert raw[pe:pe+4]==b'PE\x00\x00'
    n=struct.unpack_from('<H',raw,pe+6)[0]
    sect=pe+24+struct.unpack_from('<H',raw,pe+20)[0]
    rva=va-0x400000
    for i in range(n):
        _,vs,start,rs,ptr=struct.unpack_from('<8sIIII',raw,sect+i*40)
        if start<=rva and rva+size<=start+min(vs,rs):
            pos=ptr+rva-start
            return raw[pos:pos+size]
    raise AssertionError('entire original PE interval unavailable')

class NameEntryF246Tests(unittest.TestCase):
    def test_entire_541_native_code_and_return(self):
        body=native(0x0042A340,541)
        self.assertEqual(len(body),541)
        self.assertEqual(hashlib.sha256(body).hexdigest(),SHA)
        self.assertEqual(body[-1],0xc3)
        # This is native signed-short 16-bit ADD, not 32-bit promoted addition.
        self.assertIn(bytes.fromhex('6683c201'),body)
        self.assertIn(bytes.fromhex('6683ea01'),body)

    def test_all_actual_fields_11_and_source_hash(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            u=tomllib.load(f)['units'][UNIT]
        m=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual((u['target_address'],u['size']),(0x0042A340,541))
        self.assertEqual(m['added_units'][UNIT],u)
        self.assertNotIn('compare_size',u)
        fields=u['relocations']
        self.assertEqual(len(fields),11)
        offs=[r['offset'] for r in fields]
        self.assertEqual(offs,sorted(offs))
        self.assertEqual(len(set(offs)),11)
        self.assertTrue(all(r['type'] in ('DIR32','REL32') for r in fields))
        targets=[r['target'] for r in fields]
        self.assertEqual(targets.count(0x006718F8),2)
        self.assertEqual(targets.count(0x004079C0),2)
        for v in (0x0042AB90,0x004169E0,0x00416E80,0x004028F0,0x006714CE):
            self.assertIn(v,targets)
        src=u['source']
        self.assertEqual(src,'src/NameEntryUpdateF246.cpp')
        code=(ROOT/src).read_bytes()
        self.assertEqual(m['source_sha256'][src],hashlib.sha256(code).hexdigest())
        self.assertIn('++FIELD(short,0x14);',code.decode('utf-8'))
        self.assertIn('--FIELD(short,0x14);',code.decode('utf-8'))

if __name__=='__main__':unittest.main()
