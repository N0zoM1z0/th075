"""Recorded origin extents cannot silently accept missing code or shared tails."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("authored_origins", ROOT / "scripts/verify-authored-origins.py")
AUTHORED = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(AUTHORED)


class AuthoredOriginExtentTests(unittest.TestCase):
    def test_incomplete_final_instruction_cannot_match_a_prefix(self):
        with self.assertRaisesRegex(ValueError, "incomplete"):
            AUTHORED.verify_body(b"\xc3\xb8", 0x401000)

    def test_return_does_not_hide_an_unresolved_external_tail(self):
        with self.assertRaisesRegex(ValueError, "external/shared tail"):
            AUTHORED.verify_body(b"\xeb\x7f\xc3", 0x401000)

    def test_internal_branch_must_land_at_an_instruction_start(self):
        with self.assertRaisesRegex(ValueError, "unresolved authored jump"):
            AUTHORED.verify_body(b"\xb8\0\0\0\0\xeb\xfa\xc3", 0x401000)


if __name__ == "__main__":
    unittest.main()
