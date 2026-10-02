"""Reject origin bindings that would hide an unreviewed callee or instruction."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "runtime_origins", ROOT / "scripts/verify-runtime-origins.py")
RUNTIME = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(RUNTIME)


class RuntimeOriginBindingsTests(unittest.TestCase):
    def setUp(self):
        self.code = bytearray(b"\xe8\0\0\0\0\xc3")
        self.relocation = {"offset": 1, "type": "REL32", "symbol": "_vendor",
                           "addend": 0, "local_symbol_offset": None}
        self.binding = {"offset": "0x1", "type": "REL32", "symbol": "_vendor",
                        "target_address": "0x00402000"}

    def test_unverified_callee_cannot_supply_origin_evidence(self):
        with self.assertRaisesRegex(ValueError, "independently verified"):
            RUNTIME.bind_calls(self.code, [self.relocation], [self.binding], {}, 0x401000)

    def test_binding_cannot_cover_a_non_call_opcode(self):
        self.code[0] = 0xB8  # MOV EAX, imm32, not CALL.
        with self.assertRaisesRegex(ValueError, "call relocation"):
            RUNTIME.bind_calls(self.code, [self.relocation], [self.binding],
                               {0x402000: "_vendor"}, 0x401000)

    def test_vendor_symbol_alias_cannot_be_guessed(self):
        with self.assertRaisesRegex(ValueError, "independently verified"):
            RUNTIME.bind_calls(self.code, [self.relocation], [self.binding],
                               {0x402000: "_different_vendor"}, 0x401000)


if __name__ == "__main__":
    unittest.main()
