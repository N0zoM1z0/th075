"""Guard the entire native result-scene init constructor (F243).

The exact cold build covers only the new unit. These tests read original PE
and the accepted source/COFF field ledger, never recold prior units.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
UNIT='result-scene-initialize-0042e640'
BODY_SHA='6fef0a170924d019037ccdb3c264dc8e357dd9c09c0edce3db3af9be94ae786a'


def original_bytes(addr,size):
    raw=(ROOT/'resources/th075.exe').read_bytes()
    p=struct.unpack_from('<I',raw,0x3c)[0]
    if raw[p:p+4]!=b'PE\0\0':raise AssertionError('not original TH075')
    count=struct.unpack_from('<H',raw,p+6)[0]
    sec=p+24+struct.unpack_from('<H',raw,p+20)[0]
    rva=addr-0x400000
    for i in range(count):
        _,vs,va,rs,ptr=struct.unpack_from('<8sIIII',raw,sec+i*40)
        if va<=rva and rva+size<=va+min(vs,rs):
            return raw[ptr+rva-va:ptr+rva-va+size]
    raise AssertionError('native extent not PE-backed')


class ResultSceneInitF243Tests(unittest.TestCase):
    def test_full_native_body_hash_eh_and_return(self):
        body=original_bytes(0x0042E640,547)
        self.assertEqual(len(body),547)
        self.assertEqual(hashlib.sha256(body).hexdigest(),BODY_SHA)
        self.assertEqual(body[-1],0xc3)
        self.assertEqual(body[0:5],b'\x55\x8b\xec\x6a\xff')

    def test_all_33_physical_relocations_and_borrowed_owner_source(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            u=tomllib.load(f)['units'][UNIT]
        m=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual((u['target_address'],u['size']), (0x0042E640,547))
        self.assertEqual(len(u['relocations']),33)
        self.assertEqual(m['added_units'][UNIT],u)
        f=u['relocations'];offsets=[r['offset'] for r in f]
        self.assertEqual(offsets,sorted(offsets))
        self.assertEqual(len(set(offsets)),33)
        self.assertTrue(all(r['type'] in ('DIR32','REL32') for r in f))
        targets=[r['target'] for r in f]
        self.assertEqual(targets.count(0x004251C0),1)
        self.assertEqual(targets.count(0x0040AD80),1)
        self.assertEqual(targets.count(0x0040B1D0),1)
        self.assertEqual(targets.count(0x0040BB80),1)
        self.assertEqual(targets.count(0x00671418),8)
        for v in (0x006559E3,0x00658038,0x0064159D,
                  0x0065801C,0x00658014,0x0067141C,
                  0x0067160C,0x006714BC,0x006714C0,
                  0x00671622,0x00658034,0x00657888,0x0065747C):
            self.assertIn(v,targets)
        src=u['source']
        self.assertEqual(src,'src/ResultSceneCtorF243.cpp')
        contents=(ROOT/src).read_bytes()
        self.assertEqual(m['source_sha256'][src],hashlib.sha256(contents).hexdigest())
        s=contents.decode('utf-8')
        self.assertIn('sizeof(TextureManagerF243)==80',s)
        self.assertIn('class ResultSceneCtorF243 : public SceneBaseF243',s)


if __name__=='__main__':unittest.main()
