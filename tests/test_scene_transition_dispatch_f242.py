"""Pin the complete F242 scene transition dispatcher and actual relocations.

The F242 whole-function cold replay is separate; these fast guards do not
replay any previously accepted unrelated unit.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
UNIT='scene-transition-dispatch-mode-00431f60'
SHA='c2548722489fb02941d2068f23f8b9a512fddbc1a373318b88f60b61fb1465c7'


def native_extent(addr,size):
    raw=(ROOT/'resources/th075.exe').read_bytes()
    p=struct.unpack_from('<I',raw,0x3C)[0]
    if raw[p:p+4]!=b'PE\0\0':raise AssertionError('not native TH075 PE')
    n=struct.unpack_from('<H',raw,p+6)[0]
    sec=p+24+struct.unpack_from('<H',raw,p+20)[0]
    rva=addr-0x400000
    for i in range(n):
        _,vsz,vaddr,rsz,rptr=struct.unpack_from('<8sIIII',raw,sec+i*40)
        if vaddr<=rva and rva+size<=vaddr+min(vsz,rsz):
            start=rptr+rva-vaddr
            return raw[start:start+size]
    raise AssertionError('not PE-backed complete code')


class TransitionF242Tests(unittest.TestCase):
    def test_full_663_code_bytes_and_real_callee_cleanup(self):
        body=native_extent(0x00431F60,663)
        self.assertEqual(len(body),663)
        self.assertEqual(hashlib.sha256(body).hexdigest(),SHA)
        self.assertEqual(body[-3:],b'\xc2\x04\x00')
        # Two distinct masked mode arms must not be collapsed.
        self.assertIn(bytes.fromhex('81e1000f0000'),body)
        self.assertIn(bytes.fromhex('81e100f00000'),body)

    def test_all_27_physical_fields_and_six_real_transition_callbacks(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            unit=tomllib.load(f)['units'][UNIT]
        m=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual((unit['target_address'],unit['size']), (0x00431F60,663))
        self.assertNotIn('compare_size',unit)
        self.assertEqual(m['added_units'][UNIT],unit)
        fields=unit['relocations']
        self.assertEqual(len(fields),27)
        offsets=[r['offset'] for r in fields]
        self.assertEqual(offsets,sorted(offsets))
        self.assertEqual(len(set(offsets)),27)
        self.assertTrue(all(r['type'] in ('DIR32','REL32') for r in fields))
        t=[r['target'] for r in fields]
        self.assertEqual(t.count(0x004028A0),7)
        self.assertEqual(t.count(0x006714D2),2)
        self.assertEqual(t.count(0x004028F0),1)
        for v in (0x00432360,0x00432200,0x004324D0,
                  0x00432410,0x004322B0,0x00432660):
            self.assertEqual(t.count(v),1)
        src=unit['source']
        self.assertEqual(src,'src/SceneTransitionDispatchF242.cpp')
        self.assertEqual(m['source_sha256'][src],hashlib.sha256((ROOT/src).read_bytes()).hexdigest())


if __name__=='__main__':unittest.main()
