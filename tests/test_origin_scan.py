"""Whole-body grouping retains data pointers, call ownership and stack cleanup."""
import importlib.util
from pathlib import Path
import struct
import unittest

from capstone import Cs, CS_ARCH_X86, CS_MODE_32


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("origin_batch_scan", ROOT / "scripts/scan-origin-candidates.py")
SCANNER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SCANNER)


def signature(address=0x1000, callee=0x3000, pointer=0x4000, cleanup=20):
    # Synthetic absolute pointer, direct call and method return; no target bytes.
    code = b"\xB8" + struct.pack("<I", pointer)
    code += b"\xE8" + struct.pack("<i", callee - address - 10)
    code += b"\xC2" + struct.pack("<H", cleanup)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    return SCANNER.body_signature(code, list(decoder.disasm(code, address)), address)


class OriginScanTests(unittest.TestCase):
    def test_absolute_location_does_not_split_the_same_whole_body(self):
        self.assertEqual(signature(), signature(address=0x2000))

    def test_different_actual_callee_does_not_share_the_same_group(self):
        self.assertNotEqual(signature(), signature(callee=0x5000))

    def test_data_or_vtable_pointer_is_never_normalized_away(self):
        self.assertNotEqual(signature(), signature(pointer=0x4010))

    def test_unused_stack_argument_still_splits_whole_body_groups(self):
        self.assertNotEqual(signature(), signature(cleanup=24))


if __name__ == "__main__":
    unittest.main()
