"""Pin the native F241 decimal painter and its nine physical call fields.

Cold compilation is deliberately a separate single-affected-unit action.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[1]
UNIT = 'result-scene-draw-decimal-digits-0042f530'
TARGET_SHA = '2d708f91fbaf060e21a87a4d066200fa0dda614c358a31d6276273b483240c55'


def native_range(addr, length):
    raw=(ROOT/'resources/th075.exe').read_bytes()
    pe=struct.unpack_from('<I',raw,0x3c)[0]
    assert raw[pe:pe+4]==b'PE\x00\x00'
    n=struct.unpack_from('<H',raw,pe+6)[0]
    sections=pe+24+struct.unpack_from('<H',raw,pe+20)[0]
    rva=addr-0x400000
    for i in range(n):
        _,vs,va,rs,start=struct.unpack_from('<8sIIII',raw,sections+40*i)
        if va<=rva and rva+length<=va+min(vs,rs):
            pos=start+rva-va
            return raw[pos:pos+length]
    raise AssertionError('incomplete target range')


class ResultDigitsF241Tests(unittest.TestCase):
    def test_whole_423_native_bytes_and_callee_stack_cleanup(self):
        body=native_range(0x0042F530,423)
        self.assertEqual(len(body),423)
        self.assertEqual(hashlib.sha256(body).hexdigest(),TARGET_SHA)
        self.assertEqual(body[-3:],b'\xc2\x18\x00')

    def test_nine_true_relocations_and_source_digest(self):
        with (ROOT/'config/match-units.toml').open('rb') as stream:
            u=tomllib.load(stream)['units'][UNIT]
        accepted=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual(u['target_address'],0x0042F530)
        self.assertEqual(u['size'],423)
        self.assertEqual(len(u['relocations']),9)
        self.assertNotIn('compare_size',u)
        self.assertEqual(accepted['added_units'][UNIT],u)
        fields=u['relocations']
        offs=[r['offset'] for r in fields]
        self.assertEqual(offs,sorted(offs))
        self.assertEqual(len(set(offs)),9)
        self.assertTrue(all(r['type'] in ('DIR32','REL32') for r in fields))
        targets=[r['target'] for r in fields]
        self.assertEqual(targets.count(0x00657210),2)
        self.assertEqual(targets.count(0x0040C9A0),2)
        self.assertEqual(targets.count(0x00411500),2)
        self.assertIn(0x0040DA00,targets)
        self.assertIn(0x00657CC0,targets)
        self.assertIn(0x0065786C,targets)
        source=u['source']
        self.assertEqual(source,'src/ResultDigitsF241.cpp')
        contents=(ROOT/source).read_bytes()
        self.assertEqual(accepted['source_sha256'][source],hashlib.sha256(contents).hexdigest())
        s=contents.decode('utf-8')
        self.assertIn('int remaining=number;',s)
        self.assertIn('SpriteQuad40CA80 quad(',s)
        self.assertIn('RECT rect;',s)


if __name__=='__main__':
    unittest.main()
