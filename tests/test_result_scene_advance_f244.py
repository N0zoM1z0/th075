"""Pin F244's entire 1529-byte result controller and two real owned tables.

This verifies original PE bytes and all 74 physical COFF fields without
broad cold builds; the separately affected F244 unit was cold-replayed exact.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]
UNIT='result-scene-advance-0042e8f0'
CODE_HASH='19736e382a7ced3ff5809c4d0f1f791969d7ac7e82bfad3e44f85866dda351f1'
WHOLE_HASH='6434768fdb2a0e649341109308e49032782d6166d136b41972aa002e72095eab'
TABLE=(0x0042E9C9,0x0042E9E2,0x0042E9FB,0x0042EA14,
       0x0042EDA5,0x0042EDBE,0x0042EDD7,0x0042EDF0)


def original(addr,size):
    raw=(ROOT/'resources/th075.exe').read_bytes()
    p=struct.unpack_from('<I',raw,0x3c)[0]
    if raw[p:p+4]!=b'PE\x00\x00':raise AssertionError('not original TH075')
    num=struct.unpack_from('<H',raw,p+6)[0]
    table=p+24+struct.unpack_from('<H',raw,p+20)[0]
    rva=addr-0x400000
    for i in range(num):
        _,vsz,va,rsz,ptr=struct.unpack_from('<8sIIII',raw,table+i*40)
        if va<=rva and rva+size<=va+min(vsz,rsz):
            loc=ptr+rva-va
            return raw[loc:loc+size]
    raise AssertionError('entire native interval not backed by original PE')


class ResultSceneAdvanceF244Tests(unittest.TestCase):
    def test_full_native_code_and_two_actual_case_tables(self):
        whole=original(0x0042E8F0,1561)
        self.assertEqual(len(whole),1561)
        self.assertEqual(hashlib.sha256(whole[:1529]).hexdigest(),CODE_HASH)
        self.assertEqual(hashlib.sha256(whole).hexdigest(),WHOLE_HASH)
        self.assertEqual(whole[1528],0xc3)
        self.assertEqual(struct.unpack_from('<8I',whole,1529),TABLE)

    def test_all_seventy_four_true_relocations_without_table_code_credit(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            u=tomllib.load(f)['units'][UNIT]
        m=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual(u['target_address'],0x0042E8F0)
        self.assertEqual(u['size'],1529)
        self.assertEqual(u['compare_size'],1561)
        self.assertEqual(u['functions'],['SceneController::AdvanceAt0042E8F0'])
        self.assertEqual(m['added_units'][UNIT],u)
        fields=u['relocations']
        self.assertEqual(len(fields),74)
        positions=[r['offset'] for r in fields]
        self.assertEqual(positions,sorted(positions))
        self.assertEqual(len(set(positions)),74)
        self.assertTrue(all(x['type'] in ('DIR32','REL32') for x in fields))
        self.assertEqual([r['offset'] for r in fields[-8:]],list(range(1529,1561,4)))
        self.assertEqual([r['type'] for r in fields[-8:]],['DIR32']*8)
        self.assertEqual(tuple(r['target'] for r in fields[-8:]),TABLE)
        self.assertEqual(len([r for r in fields if r['offset']<1529]),66)
        targets=[r['target'] for r in fields[:66]]
        self.assertIn(0x0042F450,targets)
        self.assertIn(0x004028F0,targets)
        self.assertIn(0x00407E60,targets)
        self.assertIn(0x00419CB0,targets)
        self.assertIn(0x00671418,targets)
        self.assertIn(0x006714B0,targets)
        self.assertIn(0x00658050,targets)
        self.assertIn(0x00657D00,targets)
        self.assertIn(0x00657D08,targets)
        self.assertEqual(targets.count(0x006406AC), 14)
        src=u['source']
        self.assertEqual(src,'src/ResultSceneAdvanceF244.cpp')
        data=(ROOT/src).read_bytes()
        self.assertEqual(m['source_sha256'][src],hashlib.sha256(data).hexdigest())
        s=data.decode('utf-8')
        self.assertIn('FIELD(signed char,0x40)',s)
        self.assertIn('switch (g_ResultFocusAt006714D0)',s)
        self.assertIn('switch (FIELD(int,0x3c))',s)


if __name__=='__main__':unittest.main()
