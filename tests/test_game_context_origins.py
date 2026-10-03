"""Unresolved callee context must retain every external tail and full extent."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("game_context", ROOT / "scripts/verify-game-context-origins.py")
CONTEXT = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(CONTEXT)


class BoundedContextTests(unittest.TestCase):
    def test_external_tail_requires_its_exact_destination(self):
        code = b"\xe9\x10\0\0\0"
        tails = [{"site": "0x00401000", "target": "0x00401015"}]
        self.assertEqual(CONTEXT.verify_bounded_context(code, 0x401000, tails), [0, 0])
        with self.assertRaisesRegex(ValueError, "tails differ"):
            CONTEXT.verify_bounded_context(code, 0x401000, [])
        tails[0]["target"] = "0x00401016"
        with self.assertRaisesRegex(ValueError, "tails differ"):
            CONTEXT.verify_bounded_context(code, 0x401000, tails)

    def test_internal_jump_cannot_enter_the_middle_of_an_instruction(self):
        with self.assertRaisesRegex(ValueError, "partial instruction"):
            CONTEXT.verify_bounded_context(b"\xeb\x01\xb8\0\0\0\0\xc3", 0x401000, [])

    def test_return_does_not_hide_trailing_garbage_or_fallthrough(self):
        for code in (b"\xc3\xb8", b"\xc3\x90"):
            with self.assertRaisesRegex(ValueError, "incomplete|fallthrough"):
                CONTEXT.verify_bounded_context(code, 0x401000, [])


if __name__ == "__main__":
    unittest.main()
