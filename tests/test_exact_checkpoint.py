"""An exact addition must not relax historical source or canonical guards."""
import copy
from pathlib import Path
import unittest
from unittest.mock import patch

import exact_checkpoint as E


class ExactCheckpointTests(unittest.TestCase):
    def test_current_additions_and_every_frozen_prefix(self):
        E.verify_adoptions()

    def test_unapproved_appended_mapping_is_rejected(self):
        path = E.ROOT / "config/reccmp-functions.csv"
        read_bytes = Path.read_bytes
        def changed(current):
            raw = read_bytes(current)
            return raw + b"Unapproved,0x00400000,function\n" if current == path else raw
        with patch.object(Path, "read_bytes", changed):
            with self.assertRaises(ValueError):
                E.retained_bytes(path)

    def test_old_unit_edit_is_rejected(self):
        path = E.ROOT / "config/match-units.toml"
        read_bytes = Path.read_bytes
        def changed(current):
            raw = read_bytes(current)
            return raw.replace(b"size = 27\n", b"size = 26\n", 1) if current == path else raw
        with patch.object(Path, "read_bytes", changed):
            with self.assertRaises(ValueError):
                E.retained_bytes(path)

    def test_unapproved_origin_alias_is_rejected(self):
        path = E.ROOT / "config/authored-origin-name-aliases.csv"
        read_bytes = Path.read_bytes
        def changed(current):
            raw = read_bytes(current)
            return raw.replace(b"sprite-transform-build-quad\n", b"unapproved\n") if current == path else raw
        with patch.object(Path, "read_bytes", changed):
            with self.assertRaises(ValueError):
                E.retained_bytes(path)

    def test_only_complete_function_pairs_can_be_projected(self):
        item = E.plan()["functions"][0]
        self.assertEqual(E.historical_functions([item["after"]]), [item["before"]])
        bad = copy.deepcopy(item["after"])
        bad["signature"] = "unapproved"
        with self.assertRaises(ValueError):
            E.historical_functions([bad])

    def test_unrelated_rows_are_never_projected(self):
        row = {"address": "0x00401020", "calling_convention": "unapproved"}
        self.assertEqual(E.historical_functions([row]), [row])

    def test_unknown_origins_receive_no_adoption_credit(self):
        plan = E.plan()
        self.assertEqual(len(plan["functions"]), 114)
        self.assertTrue(all(item["origin"]["disposition"] == "authored"
                            for item in plan["functions"]))
        self.assertEqual(sum(unit["size"] for unit in plan["added_units"].values()), 539287)
