"""Reject ambiguous short matches without their complete typed call witness."""
from copy import deepcopy
import importlib.util
import json
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "vector_callee_witnesses", ROOT / "scripts/verify-vendor-vector-callee-origins.py")
VERIFIER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VERIFIER)


class VectorCalleeWitnessTests(unittest.TestCase):
    def setUp(self):
        self.evidence = {row["address"]: row for row in
                         VERIFIER.rows("vendor-vector-callee-origins.csv")}
        self.operations = {row["address"]: row for row in
                           VERIFIER.rows("vendor-vector-operation-origins.csv")}
        self.anchors = {(filename, row["address"]): row
                        for filename in VERIFIER.ANCHOR_FILES
                        for row in VERIFIER.rows(filename)}

    def test_every_child_and_wrapper_has_an_independent_anchor(self):
        for row in self.evidence.values():
            with self.subTest(address=row["address"]):
                VERIFIER.verify_witness(row, self.evidence, self.operations, self.anchors)

    def test_same_shape_begin_and_end_cannot_exchange_source_identity(self):
        row = self.evidence["0x00445470"]
        changed = deepcopy(self.operations)
        parent = changed[row["parent_address"]]
        calls = json.loads(parent["relocation_bindings"])
        call = next(call for call in calls if call["offset"] == int(row["parent_call_offset"]))
        call["symbol"] = self.evidence["0x00458C80"]["coff_symbol"]
        parent["relocation_bindings"] = json.dumps(calls)
        with self.assertRaisesRegex(ValueError, "exact source-typed parent call"):
            VERIFIER.verify_witness(row, self.evidence, changed, self.anchors)

    def test_copy_variant_requires_the_same_complete_reviewed_callee(self):
        row = self.evidence["0x0040F430"]
        changed = deepcopy(self.anchors)
        changed[(row["callee_file"], row["callee_address"])]["body_sha256"] = "0" * 64
        with self.assertRaisesRegex(ValueError, "complete typed copy callee"):
            VERIFIER.verify_witness(row, self.evidence, self.operations, changed)

    def test_copy_wrapper_cannot_credit_itself_after_removing_its_callee(self):
        row = self.evidence["0x0045B230"]
        changed = deepcopy(self.anchors)
        del changed[(row["callee_file"], row["callee_address"])]
        with self.assertRaisesRegex(ValueError, "complete typed copy callee"):
            VERIFIER.verify_witness(row, self.evidence, self.operations, changed)


if __name__ == "__main__":
    unittest.main()
