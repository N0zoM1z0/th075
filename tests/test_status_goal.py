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

    def test_ninety_eight_percent_boundary_uses_bytes(self):
        at_boundary = self.summary(["authored", "authored"], [98, 2], [0])
        below_boundary = self.summary(["authored", "authored"], [97, 3], [0])
        self.assertEqual(at_boundary["authored_exact_goal_percent"], 98)
        self.assertTrue(at_boundary["authored_exact_goal_complete"])
        self.assertFalse(below_boundary["authored_exact_goal_complete"])

    def test_pending_bytes_cannot_make_the_new_goal_easier(self):
        result = self.summary(["authored", "authored", "review"], [98, 2, 1], [0])
        self.assertEqual(result["authored_upper_bound_bytes"], 101)
        self.assertFalse(result["authored_exact_goal_complete"])

    def test_small_pending_set_can_be_covered_conservatively(self):
        result = self.summary(["authored", "authored", "review"], [990, 10, 10], [0])
        self.assertFalse(result["origin_review_complete"])
        self.assertEqual(result["pending_bytes"], 10)
        self.assertGreaterEqual(result["authored_exact_lower_bound_percent"], 98)
        self.assertTrue(result["authored_exact_goal_complete"])
