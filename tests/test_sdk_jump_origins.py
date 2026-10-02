"""Short SDK forwarding entries require a complete typed JMP definition."""
import importlib.util
from pathlib import Path
import struct
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "sdk_jump_test", ROOT / "scripts/verify-sdk-jump-origins.py")
JUMPS = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(JUMPS)


class SDKJumpOriginTests(unittest.TestCase):
    def test_whole_forwarder_reaches_recorded_destination(self):
        address, destination = 0x006190D7, 0x0061535A
        code = b"\xe9" + struct.pack("<i", destination - address - 5)
        self.assertEqual(JUMPS.forward_destination(code, address), destination)
        with self.assertRaisesRegex(ValueError, "one complete relative JMP"):
            JUMPS.forward_destination(code + b"\x90", address)

    def test_call_or_short_tail_cannot_replace_the_source_jmp(self):
        with self.assertRaisesRegex(ValueError, "one complete relative JMP"):
            JUMPS.forward_destination(b"\xe8\0\0\0\0", 0x006190D7)
        with self.assertRaisesRegex(ValueError, "one complete relative JMP"):
            JUMPS.forward_destination(b"\xeb\0", 0x006190D7)

    def test_source_symbol_and_typed_relocation_are_required(self):
        symbol = "??1CD3DXCodec@@UAE@XZ"
        source = b"\xe9\0\0\0\0"
        relocation = {"offset": 1, "type": "REL32", "symbol": symbol, "addend": 0}
        self.assertTrue(JUMPS.typed_source_forward(source, [relocation], symbol))
        self.assertFalse(JUMPS.typed_source_forward(source, [relocation], "another symbol"))
        self.assertFalse(JUMPS.typed_source_forward(source, [dict(relocation, type="DIR32")], symbol))
        self.assertFalse(JUMPS.typed_source_forward(source, [relocation, relocation], symbol))


if __name__ == "__main__":
    unittest.main()
