"""Protect the whole F240 result counter renderer and every physical call.

The independent F240 cold replay checks the full compiler object. These fast
checks read the original PE and accepted ledger without rebuilding old units.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[1]
UNIT = 'result-scene-render-counters-0042ef10'
CODE_HASH = '4caa7d7d4c0d1f0ea0db8d352f14f744b8cd8474a0146c368d7b5e4624d5c8b1'


def original_bytes(addr, size):
    raw = (ROOT/'resources/th075.exe').read_bytes()
    pe = struct.unpack_from('<I',raw,0x3c)[0]
    if raw[pe:pe+4] != b'PE\0\0':
        raise AssertionError('not the original PE')
    n = struct.unpack_from('<H',raw,pe+6)[0]
    sections = pe+24+struct.unpack_from('<H',raw,pe+20)[0]
    rva=addr-0x400000
    for i in range(n):
        _,vs,va,rs,p=struct.unpack_from('<8sIIII',raw,sections+40*i)
        if va<=rva and rva+size<=va+min(vs,rs):
            pos=p+rva-va
            return raw[pos:pos+size]
    raise AssertionError('whole native code interval unavailable')


class ResultRendererF240Tests(unittest.TestCase):
    def test_whole_1344_byte_code_native_hash_and_ret(self):
        body=original_bytes(0x0042EF10,1344)
        self.assertEqual(len(body),1344)
        self.assertEqual(hashlib.sha256(body).hexdigest(),CODE_HASH)
        self.assertEqual(body[-1],0xC3)
        # True original alpha path: FLD global constant (255f), FMUL member.
        self.assertEqual(body[0x183:0x18c],bytes.fromhex('d905f07c6500d84a14'))

    def test_all_44_native_relocations_and_source_are_pinned(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            entry=tomllib.load(f)['units'][UNIT]
        manifest=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual(entry['target_address'],0x0042EF10)
        self.assertEqual(entry['size'],1344)
        self.assertNotIn('compare_size',entry)
        self.assertEqual(manifest['added_units'][UNIT],entry)
        fields=entry['relocations']
        self.assertEqual(len(fields),44)
        offsets=[r['offset'] for r in fields]
        self.assertEqual(offsets,sorted(offsets))
        self.assertEqual(len(set(offsets)),44)
        self.assertTrue(all(r['type'] in ('REL32','DIR32') for r in fields))
        targets=[r['target'] for r in fields]
        self.assertEqual(targets.count(0x0042F530),6)
        self.assertEqual(targets.count(0x0040C9A0),3)
        self.assertEqual(targets.count(0x0040C860),2)
        self.assertEqual(targets.count(0x00657864),3)
        self.assertEqual(targets.count(0x00658048),3)
        self.assertEqual(targets.count(0x00658058),3)
        for target in (0x0040D990,0x00411400,0x004116F0,0x004115C0,
                       0x00411500,0x004171D0,0x00657CF0,0x006714C4,
                       0x00671418,0x006714D0,0x004027D0):
            self.assertIn(target,targets)
        src=entry['source']
        self.assertEqual(src,'src/ResultRendererF240.cpp')
        contents=(ROOT/src).read_bytes()
        self.assertEqual(manifest['source_sha256'][src],hashlib.sha256(contents).hexdigest())
        text=contents.decode('utf-8')
        self.assertIn('float physicallyObservedAlphaAt0014;',text)
        self.assertIn('class ResultRawScaleF240',text)
        self.assertIn('SpriteQuad40CA80 quad;',text)
        self.assertIn('RECT region;',text)


if __name__ == '__main__':
    unittest.main()
