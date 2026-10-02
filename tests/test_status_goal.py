"""Keep authored-byte progress separate from completion of origin review."""
import importlib.util
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch


spec = importlib.util.spec_from_file_location(
    "th075_status", Path(__file__).resolve().parents[1]
    / "scripts/report-reconstruction-status.py")
STATUS = importlib.util.module_from_spec(spec)
spec.loader.exec_module(STATUS)


class GoalAccountingTests(unittest.TestCase):
    def summary(self, dispositions, sizes, exact_addresses):
        addresses = [f"0x{0x401000 + index * 0x100:08X}"
                     for index in range(len(sizes))]
        ledgers = {
            "functions.csv": [dict(address=address, size=str(size), current_name=address)
                              for address, size in zip(addresses, sizes)],
            "function-origins.csv": [dict(address=address, disposition=disposition,
                                          origin="unknown" if disposition == "review"
                                          else "library" if disposition == "exclude"
                                          else "authored")
                                     for address, disposition in zip(addresses, dispositions)],
            "reccmp-functions.csv": [],
            "matches.csv": [dict(address=addresses[index]) for index in exact_addresses],
        }
        with tempfile.TemporaryDirectory() as temporary:
            config = Path(temporary)
            (config / "implemented.csv").write_text("")
            (config / "match-units.toml").write_text("[units]\n")
            with patch.object(STATUS, "CONFIG", config), \
                 patch.object(STATUS, "rows", side_effect=lambda name: ledgers[name]):
                return STATUS.load()[1]

    def test_pending_origin_blocks_goal_even_at_one_hundred_percent(self):
        result = self.summary(["authored", "review"], [100, 900], [0])
        self.assertEqual(result["authored_exact_percent"], 100.0)
        self.assertFalse(result["origin_review_complete"])
        self.assertFalse(result["fifty_percent_goal_complete"])

    def test_goal_counts_bytes_and_excludes_library_bytes(self):
        result = self.summary(["authored", "authored", "exclude"], [60, 40, 900], [0])
        self.assertEqual(result["authored_bytes"], 100)
        self.assertEqual(result["exact_authored_bytes"], 60)
        self.assertTrue(result["fifty_percent_goal_complete"])

    def test_many_small_exact_functions_do_not_satisfy_byte_goal(self):
        result = self.summary(["authored"] * 4, [10, 10, 10, 100], [0, 1, 2])
        self.assertTrue(result["origin_review_complete"])
        self.assertFalse(result["fifty_percent_goal_complete"])

    def test_empty_authored_set_has_no_percentage_or_goal_credit(self):
        result = self.summary(["exclude"], [100], [])
        self.assertIsNone(result["authored_exact_percent"])
        self.assertFalse(result["fifty_percent_goal_complete"])
