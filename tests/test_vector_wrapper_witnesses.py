"""Short wrappers need a source-typed call and the complete same-family callee."""
from copy import deepcopy
import importlib.util
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "vector_wrapper_witnesses", ROOT / "scripts/verify-vendor-vector-wrapper-origins.py")
VERIFIER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VERIFIER)


class VectorWrapperWitnessTests(unittest.TestCase):
    def setUp(self):
        self.evidence = VERIFIER.rows("vendor-vector-wrapper-origins.csv")
        self.anchors = VERIFIER.callee_anchors()

    def test_every_wrapper_has_its_same_family_complete_callee(self):
        for row in self.evidence:
            with self.subTest(address=row["address"]):
                VERIFIER.verify_witness(row, self.anchors)

    def test_other_callee_cannot_supply_the_same_function_shape(self):
        changed = deepcopy(next(row for row in self.evidence if row["family_key"] == "?assign"))
        changed["callee_source_symbol"] = changed["callee_source_symbol"].replace("?_Assign_n", "?_Ufill")
        with self.assertRaisesRegex(ValueError, "complete source-typed callee witness"):
            VERIFIER.verify_witness(changed, self.anchors)

    def test_iterator_alias_requires_a_complete_reviewed_base(self):
        row = next(row for row in self.evidence if row["family_key"] == "??Hiterator")
        changed = deepcopy(self.anchors)
        del changed[(row["callee_file"], row["callee_address"])]
        with self.assertRaisesRegex(ValueError, "complete source-typed callee witness"):
            VERIFIER.verify_witness(row, changed)


if __name__ == "__main__":
    unittest.main()
