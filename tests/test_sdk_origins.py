"""Protect whole vendor extents from convenient prefixes and unresolved tails."""
import importlib.util
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


SDK = load("sdk_origins", "verify-sdk-origins.py")
COFF = load("sdk_origin_coff", "compare-coff-function.py")


def object_with_functions(functions):
    # Synthetic two-RET COMDAT with no auxiliary size records or game bytes.
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 62, len(functions), 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 2, 60, 0, 0, 0, 0, 0x60101020)
    symbols = b"".join(struct.pack("<8sIhHBB", name, offset, 1, 0x20, 2, 0)
                       for name, offset in functions)
    return header + section + b"\xc3\xc3" + symbols + struct.pack("<I", 4)


class SDKOriginExtentTests(unittest.TestCase):
    def test_whole_extent_comes_from_vendor_section_without_target_size(self):
        body = object_with_functions([(b"_first", 0)])
        self.assertEqual(SDK.complete_comdat_size(body, "_first", COFF.coff_name), 2)

    def test_multiple_functions_cannot_be_claimed_as_one_comdat(self):
        body = object_with_functions([(b"_first", 0), (b"_second", 1)])
        with self.assertRaisesRegex(ValueError, "one complete function"):
            SDK.complete_comdat_size(body, "_first", COFF.coff_name)

    def test_nonzero_symbol_cannot_select_a_convenient_prefix(self):
        body = object_with_functions([(b"_second", 1)])
        with self.assertRaisesRegex(ValueError, "one complete function"):
            SDK.complete_comdat_size(body, "_second", COFF.coff_name)

    def test_unresolved_jump_cannot_be_hidden_by_whole_byte_identity(self):
        with self.assertRaisesRegex(ValueError, "unresolved vendor jump"):
            SDK.verify_control_flow(b"\xff\xe0\xc3", 0x401000)  # JMP EAX; RET.

    def test_internal_loop_must_target_an_instruction_start(self):
        with self.assertRaisesRegex(ValueError, "unresolved vendor jump"):
            SDK.verify_control_flow(b"\xb8\0\0\0\0\xeb\xfa\xc3", 0x401000)


if __name__ == "__main__":
    unittest.main()
