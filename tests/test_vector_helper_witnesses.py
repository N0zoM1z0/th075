"""Ownership graph checks; full body acceptance still requires the cold verifier."""
from copy import deepcopy
import importlib.util
import json
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "vector_helper_witnesses", ROOT / "scripts/verify-vendor-vector-helper-origins.py")
VERIFIER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VERIFIER)


class VectorHelperWitnessTests(unittest.TestCase):
    def setUp(self):
        self.evidence = {row["address"]: row for row in
                         VERIFIER.rows("vendor-vector-helper-origins.csv")}
        self.storage = {row["address"]: row for row in
                        VERIFIER.rows("vendor-vector-storage-origins.csv")}

    def test_every_short_helper_has_a_storage_anchor(self):
        for row in self.evidence.values():
            with self.subTest(address=row["address"]):
                VERIFIER.verify_witness(row, self.evidence, self.storage)

    def test_identical_address_cannot_replace_the_source_callee_symbol(self):
        row = next(row for row in self.evidence.values()
                   if row["family_key"] == "??0?$allocator" and row["size"] == "16")
        changed = deepcopy(self.evidence)
        parent = changed[row["parent_address"]]
        bindings = json.loads(parent["relocation_bindings"])
        binding = next(binding for binding in bindings
                       if binding["offset"] == int(row["parent_call_offset"]))
        binding["symbol"] += "unrelated_source_definition"
        parent["relocation_bindings"] = json.dumps(bindings)
        with self.assertRaisesRegex(ValueError, "exact source-typed parent call"):
            VERIFIER.verify_witness(row, changed, self.storage)

    def test_helper_chain_cannot_credit_itself_without_the_storage_anchor(self):
        row = next(row for row in self.evidence.values()
                   if row["family_key"] == "??0?$allocator" and row["size"] == "16")
        base = self.evidence[row["parent_address"]]
        constructor = self.evidence[base["parent_address"]]
        changed_storage = deepcopy(self.storage)
        del changed_storage[constructor["callee_address"]]
        with self.assertRaisesRegex(ValueError, "complete typed storage callee"):
            VERIFIER.verify_witness(row, self.evidence, changed_storage)


if __name__ == "__main__":
    unittest.main()
