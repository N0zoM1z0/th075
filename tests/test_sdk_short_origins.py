"""Short vendor origins need complete caller identity and a typed direct call."""
import importlib.util
from pathlib import Path
import struct
import unittest

SPEC = importlib.util.spec_from_file_location(
    "sdk_short_test", Path(__file__).resolve().parents[1] / "scripts/verify-sdk-short-origins.py")
SHORT = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SHORT)


def fixture():
    parent, destination = 0x401000, 0x402000
    source = b"\x55\xe8\0\0\0\0\x5d\xc3"
    actual = source[:2] + struct.pack("<i", destination - parent - 6) + source[6:]
    relocations = [dict(offset=2, type="REL32", symbol="vendor_func", addend=0,
                        local_symbol_offset=None)]
    return source, actual, relocations, parent, destination


class SDKShortWitnessTests(unittest.TestCase):
    def test_complete_typed_caller_binds_the_actual_target(self):
        source, actual, relocations, parent, destination = fixture()
        SHORT.typed_call_witness(source, actual, relocations, 2, "vendor_func", parent, destination)

    def test_unrelated_caller_opcode_cannot_be_masked(self):
        source, actual, relocations, parent, destination = fixture()
        with self.assertRaisesRegex(ValueError, "outside"):
            SHORT.typed_call_witness(source, b"\x90" + actual[1:], relocations,
                                     2, "vendor_func", parent, destination)

    def test_different_relocation_symbol_cannot_name_a_short_callee(self):
        source, actual, relocations, parent, destination = fixture()
        with self.assertRaisesRegex(ValueError, "direct CALL"):
            SHORT.typed_call_witness(source, actual, relocations, 2, "different", parent, destination)

    def test_same_source_symbol_cannot_claim_a_different_target(self):
        source, actual, relocations, parent, destination = fixture()
        with self.assertRaisesRegex(ValueError, "direct CALL"):
            SHORT.typed_call_witness(source, actual, relocations, 2, "vendor_func", parent, destination + 1)


if __name__ == "__main__":
    unittest.main()
