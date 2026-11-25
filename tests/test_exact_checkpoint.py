"""An exact addition must not relax historical source or canonical guards."""
import copy
from pathlib import Path
import unittest
from unittest.mock import patch

import exact_checkpoint as E


class ExactCheckpointTests(unittest.TestCase):
    def test_current_additions_and_every_frozen_prefix(self):
        E.verify_adoptions()

    def test_only_complete_function_pairs_can_be_projected(self):
        changes = E.plan()["functions"]
        for item in [changes[0], changes[-1]]:
            self.assertEqual(E.historical_functions([item["after"]]), [item["before"]])
            bad = copy.deepcopy(item["after"])
            bad["calling_convention"] = "unapproved"
            with self.assertRaises(ValueError):
                E.historical_functions([bad])

    def test_unrelated_rows_are_never_projected(self):
        # The former hard-coded fixture 0x00401020 is now independently
        # reconstructed exact (F454). Select a genuinely excluded origin
        # instead: it cannot be an approved authored adoption and keeps
        # this test meaningful as reconstruction coverage grows.
        import csv
        with (E.ROOT / "config/function-origins.csv").open(newline="") as stream:
            excluded = next((item["address"] for item in csv.DictReader(stream)
                             if item["disposition"] == "exclude"), None)
        self.assertIsNotNone(excluded)
        self.assertNotIn(excluded, {item["after"]["address"]
                                    for item in E.plan()["functions"]})
        row = {"address": excluded, "calling_convention": "unapproved"}
        self.assertEqual(E.historical_functions([row]), [row])

    def test_no_unregistered_or_duplicate_function_units(self):
        import csv
        import tomllib

        with (E.ROOT / "config/match-units.toml").open("rb") as stream:
            units = tomllib.load(stream)["units"]
        with (E.ROOT / "config/matches.csv").open(newline="") as stream:
            rows = list(csv.DictReader(stream))
        with (E.ROOT / "config/function-origins.csv").open(newline="") as stream:
            origins = {int(row["address"], 0): row for row in csv.DictReader(stream)}
        mapped = [row["unit"] for row in rows]
        self.assertEqual(len(set(mapped)), len(mapped))
        self.assertLessEqual(set(mapped), set(units))
        for name in set(units) - set(mapped):
            origin = origins[int(units[name]["target_address"])]
            self.assertEqual(origin["disposition"], "exclude", name)
            self.assertIn(origin["origin"], {"compiler", "library"}, name)
        extents = [(int(item["target_address"]), int(item["size"]),
                    int(item.get("compare_size", item["size"])))
                   for item in units.values()]
        self.assertEqual(len(set(extents)), len(extents))

    def test_unknown_origins_receive_no_adoption_credit(self):
        plan = E.plan()
        self.assertTrue(all(item["origin"]["disposition"] == "authored"
                            for item in plan["functions"]))
        # Every accepted function must have one independently complete unit;
        # exact CODE byte credit must agree with original whole extents.
        self.assertEqual(len(plan["functions"]), len(plan["added_units"]))
        self.assertEqual(
            sum(int(item["after"]["size"]) for item in plan["functions"]),
            sum(int(unit["size"]) for unit in plan["added_units"].values()))
        self.assertEqual(
            len({item["after"]["address"] for item in plan["functions"]}),
            len(plan["functions"]))
