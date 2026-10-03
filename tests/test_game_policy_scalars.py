"""Scalar context must bind readonly storage, value and actual operand width."""
import importlib.util
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest

from capstone import Cs, CS_ARCH_X86, CS_MODE_32


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "game_scalar_verifier", ROOT / "scripts/verify-short-game-origins.py")
VERIFIER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VERIFIER)


def verify(pointer=0x3000, flags=0x40000040, value=40.0, opcode=b"\xD9\x05"):
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(opcode + struct.pack("<I", pointer), 0x1000))
    row = {"address": "0x00003000", "value": 40.0,
           "uses": [{"address": "0x00001000", "site": "0x00001000"}]}
    comparison = SimpleNamespace(pe_bytes_at=lambda target, address, size: struct.pack("<f", value))
    VERIFIER.check_readonly_float32(row, b"", comparison, [(0x3000, 4, flags)],
                                   {"0x00001000": instructions})


class GamePolicyScalarTests(unittest.TestCase):
    def test_readonly_scalar_with_bound_dword_use_passes(self):
        verify()

    def test_equal_value_in_writable_storage_is_insufficient(self):
        with self.assertRaises(ValueError):
            verify(flags=0xC0000040)

    def test_same_instruction_shape_with_another_pointer_is_insufficient(self):
        with self.assertRaises(ValueError):
            verify(pointer=0x3010)

    def test_wrong_scalar_value_is_rejected(self):
        with self.assertRaises(ValueError):
            verify(value=41.0)

    def test_qword_operand_cannot_bind_a_four_byte_scalar(self):
        with self.assertRaises(ValueError):
            verify(opcode=b"\xDD\x05")


if __name__ == "__main__":
    unittest.main()
