"""Fast original-PE and canonical-source/relocation guards for F239.

The independent F239 cold replay already proved the entire compiler body;
this test must not recompile any previous or unrelated exact unit.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
UNIT='result-scene-build-record-page-00431070'
TARGET_SHA256='fe75efccccafb762e8d16e02634a192d793edf1f2b9acdc0b23ce006009c0e04'


def original_interval(addr,size):
    data=(ROOT/'resources/th075.exe').read_bytes()
    pe=struct.unpack_from('<I',data,0x3c)[0]
    if data[pe:pe+4]!=b'PE\x00\x00':
        raise AssertionError('not the pinned PE')
    cnt=struct.unpack_from('<H',data,pe+6)[0]
    table=pe+24+struct.unpack_from('<H',data,pe+20)[0]
    rva=addr-0x400000
    for i in range(cnt):
        _,vs,va,rs,ptr=struct.unpack_from('<8sIIII',data,table+i*40)
        if va<=rva and rva+size<=va+min(vs,rs):
            pos=ptr+rva-va
            return data[pos:pos+size]
    raise AssertionError('whole original code extent not PE backed')


class ResultRecordPageF239Tests(unittest.TestCase):
    def test_complete_721_native_code_bytes_and_final_return(self):
        target=original_interval(0x00431070,721)
        self.assertEqual(len(target),721)
        self.assertEqual(hashlib.sha256(target).hexdigest(),TARGET_SHA256)
        self.assertEqual(target[-1],0xc3)

    def test_all_26_native_relocations_and_source_digest(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            unit=tomllib.load(f)['units'][UNIT]
        manifest=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual(unit['target_address'],0x00431070)
        self.assertEqual(unit['size'],721)
        self.assertNotIn('compare_size',unit)
        self.assertEqual(len(unit['relocations']),26)
        self.assertEqual(manifest['added_units'][UNIT],unit)
        fields=unit['relocations']
        offs=[r['offset'] for r in fields]
        self.assertEqual(offs,sorted(offs))
        self.assertEqual(len(set(offs)),26)
        self.assertTrue(all(r['type'] in ('DIR32','REL32') for r in fields))
        targets=[r['target'] for r in fields]
        self.assertEqual(targets.count(0x006718F8),2)
        self.assertEqual(targets.count(0x006404F0),2)
        self.assertIn(0x0041DD50,targets)
        self.assertIn(0x0041DD70,targets)
        self.assertIn(0x0041C2E0,targets)
        self.assertIn(0x00655A6B,targets)
        self.assertIn(0x00640611,targets)
        source=unit['source']
        self.assertEqual(source,'src/ResultRecordF239.cpp')
        raw=(ROOT/source).read_bytes()
        self.assertEqual(manifest['source_sha256'][source],hashlib.sha256(raw).hexdigest())
        content=raw.decode('utf-8')
        self.assertIn('D3DLOCKED_RECT locked;',content)
        self.assertIn('char line[200];',content)
        self.assertIn('char message[2000];',content)


if __name__=='__main__':
    unittest.main()
