"""Recorded origin extents cannot silently accept missing code or shared tails."""
import importlib.util
from pathlib import Path
import unittest
from unittest.mock import patch

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


class ReviewedNameAliasTests(unittest.TestCase):
    def setUp(self):
        self.function = {"address": "0x00401000", "proposed_name": "Owner::ShortName",
                         "status": "matching", "size": "20"}
        self.records = {
            "authored-origin-name-aliases.csv": [
                {"address": "0x00401000", "reviewed_role": "Owner::LongReviewedName",
                 "mapped_role": "Owner::ShortName", "origin_evidence": "R104", "exact_unit": "accepted-unit"}],
            "matches.csv": [{"address": "0x00401000", "name": "Owner::ShortName",
                             "status": "matching", "size": "20", "unit": "accepted-unit"}],
            "function-origins.csv": [{"address": "0x00401000", "evidence_id": "R104"}],
        }

    def test_exact_rename_preserves_the_previous_reviewed_role(self):
        with patch.object(AUTHORED, "rows", side_effect=self.records.__getitem__):
            self.assertTrue(AUTHORED.role_matches(self.function, "Owner::LongReviewedName"))
            self.assertFalse(AUTHORED.role_matches(self.function, "Unrelated::Name"))

    def test_alias_cannot_borrow_a_different_exact_unit_or_origin(self):
        with patch.object(AUTHORED, "rows", side_effect=self.records.__getitem__):
            self.records["matches.csv"][0]["unit"] = "different-unit"
            self.assertFalse(AUTHORED.role_matches(self.function, "Owner::LongReviewedName"))
            self.records["matches.csv"][0]["unit"] = "accepted-unit"
            self.records["function-origins.csv"][0]["evidence_id"] = "R999"
            self.assertFalse(AUTHORED.role_matches(self.function, "Owner::LongReviewedName"))


if __name__ == "__main__":
    unittest.main()
