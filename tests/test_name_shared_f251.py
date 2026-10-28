"""Pin the complete original name-entry shared controller, not just its role.

This guard only reads the native PE and accepted manifest; cold validation is
performed separately for the single F251 affected unit.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
UNIT='name-entry-scene-update-shared-0042b380'
SHA='8ba26f2d27a8279ca52a9811ebdb7aa664726253349d2de6255a11f3ca75f1f0'


def original(va,size):
    raw=(ROOT/'resources/th075.exe').read_bytes()
    pe=struct.unpack_from('<I',raw,0x3c)[0]
    if raw[pe:pe+4]!=b'PE\x00\x00':raise AssertionError('invalid target PE')
    n=struct.unpack_from('<H',raw,pe+6)[0]
    table=pe+24+struct.unpack_from('<H',raw,pe+20)[0]
    rva=va-0x400000
    for i in range(n):
        _,vs,sa,rs,ptr=struct.unpack_from('<8sIIII',raw,table+i*40)
        if sa<=rva and rva+size<=sa+min(vs,rs):
            off=ptr+rva-sa
            return raw[off:off+size]
    raise AssertionError('complete native target range not available')


class NameSharedF251Tests(unittest.TestCase):
    def test_entire_original_code_and_real_return(self):
        body=original(0x0042B380,494)
        self.assertEqual(len(body),494)
        self.assertEqual(hashlib.sha256(body).hexdigest(),SHA)
        self.assertEqual(body[-1],0xc3)

    def test_all_sixteen_native_coff_relocations_and_accepted_source(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            u=tomllib.load(f)['units'][UNIT]
        m=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual((u['target_address'],u['size']),(0x0042B380,494))
        self.assertNotIn('compare_size',u)
        self.assertEqual(m['added_units'][UNIT],u)
        fields=u['relocations']
        self.assertEqual(len(fields),16)
        offsets=[r['offset'] for r in fields]
        self.assertEqual(offsets,sorted(offsets))
        self.assertEqual(len(set(offsets)),16)
        self.assertTrue(all(r['type'] in ('DIR32','REL32') for r in fields))
        targets=[r['target'] for r in fields]
        self.assertEqual(targets.count(0x004079C0),3)
        self.assertEqual(targets.count(0x00671618),3)
        self.assertEqual(targets.count(0x00671858),3)
        self.assertEqual(targets.count(0x0067185F),2)
        for x in (0x0042BCD0,0x004138E0,0x004028F0,0x00671750,0x0066C238):
            self.assertIn(x,targets)
        source=u['source']
        self.assertEqual(source,'src/NameSharedF251.cpp')
        code=(ROOT/source).read_bytes()
        self.assertEqual(m['source_sha256'][source],hashlib.sha256(code).hexdigest())
        self.assertIn('++SHORT(0x12);',code.decode('utf-8'))
        self.assertIn('--SHORT(0x12);',code.decode('utf-8'))

if __name__=='__main__':unittest.main()
