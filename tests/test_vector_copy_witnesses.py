"""Cross-family source aliases still require complete reviewed callee identity."""
from copy import deepcopy
import importlib.util
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "vector_copy_witnesses", ROOT / "scripts/verify-vendor-vector-copy-origins.py")
VERIFIER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VERIFIER)


class VectorCopyWitnessTests(unittest.TestCase):
    def setUp(self):
        self.evidence = VERIFIER.VECTOR.rows("vendor-vector-copy-origins.csv")
        self.anchors = {row["address"]: row for row in
                        VERIFIER.VECTOR.rows("vendor-deque-helper-origins.csv")}

    def test_every_alias_has_the_same_complete_reviewed_target_callee(self):
        for row in self.evidence:
            with self.subTest(address=row["address"]):
                VERIFIER.verify_witness(row, self.anchors)

    def test_another_copy_like_body_cannot_replace_the_complete_alias(self):
        row = self.evidence[0]
        changed = deepcopy(self.anchors)
        changed[row["callee_address"]]["body_sha256"] = "0" * 64
        with self.assertRaisesRegex(ValueError, "complete ambiguous callee witness"):
            VERIFIER.verify_witness(row, changed)

    def test_alias_metadata_cannot_change_the_source_typed_call(self):
        changed = deepcopy(self.evidence[0])
        changed["callee_source_symbol"] = changed["callee_source_symbol"].replace("PAKPAK", "PAEPAE")
        with self.assertRaisesRegex(ValueError, "complete ambiguous callee witness"):
            VERIFIER.verify_witness(changed, self.anchors)


if __name__ == "__main__":
    unittest.main()
