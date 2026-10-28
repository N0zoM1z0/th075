"""Pin the entire F238 result-counter page and its authentic relocation graph.

This is a fast original-PE guard, not a replay of unrelated cold objects.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
UNIT='result-scene-build-counter-page-00431350'
TARGET_SHA256='a6d5246bf6f9f3e343e3f991d863080b0937550137b631048a6946982594a86d'


def pe_range(addr,size):
    raw=(ROOT/'resources/th075.exe').read_bytes()
    p=struct.unpack_from('<I',raw,0x3c)[0]
    if raw[p:p+4]!=b'PE\x00\x00':
        raise AssertionError('not original target PE')
    n=struct.unpack_from('<H',raw,p+6)[0]
    sec=p+24+struct.unpack_from('<H',raw,p+20)[0]
    rva=addr-0x400000
    for i in range(n):
        _,vs,va,rs,start=struct.unpack_from('<8sIIII',raw,sec+40*i)
        if va<=rva and rva+size<=va+min(vs,rs):
            loc=start+rva-va
            return raw[loc:loc+size]
    raise AssertionError('complete original function not backed by PE')


class ResultCounterF238Tests(unittest.TestCase):
    def test_entire_native_body_and_real_ending(self):
        code=pe_range(0x00431350,664)
        self.assertEqual(len(code),664)
        self.assertEqual(hashlib.sha256(code).hexdigest(),TARGET_SHA256)
        self.assertEqual(code[-1],0xc3)

    def test_all_thirty_physical_fields_and_effective_caller_source(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            unit=tomllib.load(f)['units'][UNIT]
        manifest=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual(unit['target_address'],0x00431350)
        self.assertEqual(unit['size'],664)
        self.assertNotIn('compare_size',unit)
        self.assertEqual(manifest['added_units'][UNIT],unit)
        fields=unit['relocations']
        self.assertEqual(len(fields),30)
        offsets=[r['offset'] for r in fields]
        self.assertEqual(offsets,sorted(offsets))
        self.assertEqual(len(set(offsets)),30)
        self.assertTrue(all(r['type'] in ('DIR32','REL32') for r in fields))
        values=[r['target'] for r in fields]
        self.assertEqual(values.count(0x006718F8),2)
        self.assertEqual(values.count(0x006404F0),4)
        self.assertEqual(values.count(0x00641B90),4)
        self.assertIn(0x00655A83,values)
        self.assertIn(0x00640611,values)
        for target in (0x0041A1A0,0x0041A240,0x0041BF90,0x0041C060,0x0041C2E0,0x00413620):
            self.assertIn(target,values)
        source=unit['source']
        self.assertEqual(source,'src/ResultCounterF238.cpp')
        raw=(ROOT/source).read_bytes()
        self.assertEqual(manifest['source_sha256'][source],hashlib.sha256(raw).hexdigest())
        s=raw.decode('utf-8')
        self.assertIn('D3DLOCKED_RECT locked;',s)
        self.assertIn('char line[200];',s)
        self.assertIn('char message[500];',s)


if __name__=='__main__':
    unittest.main()
