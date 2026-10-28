"""Lock the F231 complete replay-file producer and native call/relocation graph.

This tests the original PE, accepted ledger and source without recompiling
any unrelated units; the affected F231 unit has a separate exact cold replay.
"""
from pathlib import Path
import hashlib
import json
import struct
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[1]
UNIT = 'replay-browser-scan-files-0042d470'
EXPECTED_BODY_HASH = '5ffba6a61250b27ffe1656bd74db2b75c19b1caf44a278df087cca7ea6177362'
EXPECTED_CALL_TARGETS = {
    0x00657068, 0x00657064, 0x00657060, # Win32 directory iteration
    0x006416A2, 0x0041DE30, 0x0041DE00, # real file name ownership
    0x00641B80, 0x00641B90, 0x0041DD50, 0x0041DDC0,
    0x00657130, 0x0065712C, 0x00657138, # open/read/close
    0x0042DBE0, 0x00414450, 0x00640611, # queued header/flag and GS
}


def get_original_range(virtual_address, length):
    data = (ROOT / 'resources/th075.exe').read_bytes()
    pe = struct.unpack_from('<I', data, 0x3C)[0]
    if data[pe:pe + 4] != b'PE\0\0':
        raise AssertionError('not the native executable')
    sections = struct.unpack_from('<H', data, pe+6)[0]
    section_start = pe + 24 + struct.unpack_from('<H', data, pe+20)[0]
    rva = virtual_address - 0x400000
    for i in range(sections):
        _, vs, va, rs, start = struct.unpack_from('<8sIIII', data, section_start+40*i)
        if va <= rva and rva+length <= va+min(vs,rs):
            begin = start+rva-va
            return data[begin:begin+length]
    raise AssertionError('requested complete native interval not mapped')


class ReplayScanF231Tests(unittest.TestCase):
    def test_full_613_byte_native_body_and_independent_path_strings(self):
        source = get_original_range(0x0042D470,613)
        self.assertEqual(hashlib.sha256(source).hexdigest(),EXPECTED_BODY_HASH)
        self.assertEqual(source[-1],0xC3)
        self.assertEqual(get_original_range(0x00657FD8,13), b'replay\\*.rep\0')
        self.assertEqual(get_original_range(0x00657FE8,8), b'replay\\\0')
        self.assertEqual(get_original_range(0x00657FF0,8), b'replay\\\0')

    def test_whole_matching_unit_has_all_31_true_physical_fields(self):
        with (ROOT / 'config/match-units.toml').open('rb') as stream:
            u = tomllib.load(stream)['units'][UNIT]
        adoptions = json.loads((ROOT / 'config/exact-adoptions.json').read_text())
        self.assertEqual(u['target_address'],0x0042D470)
        self.assertEqual(u['size'],613)
        self.assertNotIn('compare_size',u)
        self.assertEqual(len(u['relocations']),31)
        self.assertEqual(adoptions['added_units'][UNIT],u)
        fields=u['relocations']
        self.assertEqual([x['offset'] for x in fields],sorted(x['offset'] for x in fields))
        self.assertEqual(sum(x['target']==0x0065712C for x in fields),2)
        self.assertEqual(sum(x['target']==0x006416A2 for x in fields),2)
        self.assertEqual(sum(x['target']==0x0041DE00 for x in fields),6)
        self.assertEqual({x['target'] for x in fields}-{0x0066FE30,0x00657FD8,0x00657FE8,0x00657FF0},EXPECTED_CALL_TARGETS)
        self.assertTrue(all(x['type'] in ('REL32','DIR32') for x in fields))
        src = u['source']
        self.assertEqual(adoptions['source_sha256'][src],hashlib.sha256((ROOT/src).read_bytes()).hexdigest())


if __name__ == '__main__':
    unittest.main()
