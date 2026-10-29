"""F555: original-only physical font helper, its exact caller and historical control."""
from __future__ import annotations

import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib
import unittest

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
ADDR=0x0041CA30
LENGTH=77
BODY_SHA='ced8af85dcbe5d3260f506a47ab810905d7d2d7fb9cb9d9ca1f623bb4c020655'
UNIT='font-surface-shift-jis-lead-byte-0041ca30'


def native_reader():
    p=ROOT/'scripts/compare-coff-function.py'
    spec=importlib.util.spec_from_file_location('f555_native',p)
    assert spec is not None and spec.loader is not None
    module=importlib.util.module_from_spec(spec)
    sys.modules[spec.name]=module
    spec.loader.exec_module(module)
    return module


class FontShiftJISF555(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.reader=native_reader()
        cls.target=cls.reader.verified_target()
        cls.native=cls.reader.pe_bytes_at(cls.target,ADDR,LENGTH)

    def test_entire_native_function_and_byte_range_policy(self):
        self.assertEqual(len(self.native),77)
        self.assertEqual(hashlib.sha256(self.native).hexdigest(),BODY_SHA)
        ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(self.native,ADDR))
        self.assertEqual(len(ins),28)
        self.assertEqual(ins[-1].address+ins[-1].size,ADDR+LENGTH)
        self.assertEqual((ins[-1].mnemonic,ins[-1].op_str),('ret','4'))
        self.assertEqual([int(i.op_str.split(', ',1)[1],0)
                          for i in ins if i.mnemonic=='cmp'],[0x81,0xA0,0xE0,0xFF])
        self.assertFalse(any(i.mnemonic in ('call','jmp') and '[0x' in i.op_str
                             for i in ins))

    def test_native_parent_real_direct_call(self):
        # One original CALL instruction in already exact 85-byte font parent.
        raw=self.reader.pe_bytes_at(self.target,0x0041C9E0,5)
        self.assertEqual(raw[0],0xE8)
        target=0x0041C9E5+struct.unpack('<i',raw[1:])[0]
        self.assertEqual(target,ADDR)
        with (ROOT/'config/match-units.toml').open('rb') as f:
            units=tomllib.load(f)['units']
        parent=units['font-surface-decode-packed-text-0041c9d0']
        self.assertIn({'offset':17,'type':'REL32',
                       'symbol':'?IsDoubleByte@PackedFontUnitF293@@QAE_ND@Z',
                       'target':ADDR}, parent['relocations'])

    def test_complete_exact_source_checkpoint_without_opaque_relocs(self):
        with (ROOT/'config/match-units.toml').open('rb') as f:
            unit=tomllib.load(f)['units'][UNIT]
        self.assertEqual(unit['target_address'],ADDR)
        self.assertEqual(unit['size'],LENGTH)
        self.assertEqual(unit['relocations'],[])
        self.assertEqual(unit['symbol'],'?IsDoubleByte@PackedFontUnitF293@@QAE_ND@Z')
        adoption=json.loads((ROOT/'config/exact-adoptions.json').read_text())
        self.assertEqual(adoption['added_units'][UNIT],unit)
        source=ROOT/unit['source']
        self.assertEqual(hashlib.sha256(source.read_bytes()).hexdigest(),
                         adoption['source_sha256'][unit['source']])
        with (ROOT/'config/functions.csv').open(newline='') as f:
            row=next(r for r in csv.DictReader(f) if r['address']=='0x0041CA30')
        self.assertEqual((row['size'],row['status'],row['owner']),('77','matching','authored'))
        self.assertIn('inferred',row['notes'])

    def test_historical_origin_hypothesis_is_retained(self):
        # R183 originally withheld authorship because two sources were equal.
        # This historical snapshot is NOT current origin classification.
        r183=json.loads((ROOT/'config/font-byte-policy-origin-evidence.json').read_text())
        self.assertEqual(r183['pending']['address'],'0x0041CA30')
        self.assertEqual(r183['pending']['origin']['origin'],'unknown')
        self.assertEqual([c['size'] for c in r183['controls'][2:]], [77,77])
        self.assertTrue(all(c['comparison']=='positive' for c in r183['controls'][2:]))


if __name__=='__main__':
    unittest.main()
