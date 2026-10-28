"""Protect the complete F245 result-stage input poll and native call fields."""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
UNIT='result-list-scene-poll-input-0042f450'
NATIVE_SHA='c6c63048374ca1109839baa4dce442cd6b38ffa10a8ec2a80cc104d11cae05ea'


def original_pe_bytes(va,size):
    raw=(ROOT/'resources/th075.exe').read_bytes()
    pe=struct.unpack_from('<I',raw,0x3c)[0]
    assert raw[pe:pe+4]==b'PE\0\0'
    n=struct.unpack_from('<H',raw,pe+6)[0]
    s=pe+24+struct.unpack_from('<H',raw,pe+20)[0]
    rva=va-0x400000
    for i in range(n):
        _,vs,sa,rs,ptr=struct.unpack_from('<8sIIII',raw,s+i*40)
        if sa<=rva and rva+size<=sa+min(vs,rs):
            off=ptr+rva-sa
            return raw[off:off+size]
    raise AssertionError('complete original PE interval not found')


class ResultPollF245Tests(unittest.TestCase):
    def test_whole_native_code_and_return(self):
        data=original_pe_bytes(0x0042F450,220)
        self.assertEqual(len(data),220)
        self.assertEqual(hashlib.sha256(data).hexdigest(),NATIVE_SHA)
        self.assertEqual(data[-1],0xc3)

    def test_full_21_relocation_graph_and_source_guard(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            unit=tomllib.load(f)['units'][UNIT]
        m=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual((unit['target_address'],unit['size']), (0x0042F450,220))
        self.assertEqual(len(unit['relocations']),21)
        self.assertEqual(m['added_units'][UNIT],unit)
        fields=unit['relocations']
        offsets=[r['offset'] for r in fields]
        self.assertEqual(offsets,sorted(offsets))
        self.assertEqual(len(set(offsets)),21)
        self.assertTrue(all(r['type'] in ('REL32','DIR32') for r in fields))
        targets=[r['target'] for r in fields]
        self.assertEqual(targets.count(0x00671638),4)
        self.assertEqual(targets.count(0x00407170),3)
        self.assertEqual(targets.count(0x00406E80),2)
        for val in (0x00403E50,0x00403F40,0x004018A0,0x00671680,
                    0x0067166C,0x006716B4,0x00671670,0x006716B8,
                    0x00671674,0x006716BC,0x00671678,0x006716C0):
            self.assertIn(val,targets)
        src=unit['source']
        self.assertEqual(src,'src/ResultPollF245.cpp')
        self.assertEqual(m['source_sha256'][src],hashlib.sha256((ROOT/src).read_bytes()).hexdigest())


if __name__=='__main__':unittest.main()
