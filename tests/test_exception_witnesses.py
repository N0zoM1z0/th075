"""Same-shaped game lifetimes cannot borrow the standard exception witnesses."""
from copy import deepcopy
import importlib.util
import json
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "exception_witnesses", ROOT / "scripts/verify-vendor-exception-origins.py")
VERIFIER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VERIFIER)


class ExceptionWitnessTests(unittest.TestCase):
    def setUp(self):
        self.manifest = json.loads((ROOT / "config/vendor-exception-groups.json").read_text())

    def test_complete_exception_hierarchy_has_matching_typed_witnesses(self):
        VERIFIER.verify_graph(self.manifest)

    def test_same_shape_scene_destructor_cannot_replace_the_typed_base(self):
        changed = deepcopy(self.manifest)
        destructor = next(row for row in changed["bodies"] if row["role"] == "destructor")
        call = next(call for call in destructor["relocation_bindings"] if call["type"] == "REL32")
        call["target_address"] = "0x00431F40"
        with self.assertRaisesRegex(ValueError, "exact source-typed base/callee"):
            VERIFIER.verify_graph(changed)

    def test_scene_update_slot_cannot_substitute_for_inherited_what(self):
        changed = deepcopy(self.manifest)
        table = next(row for row in changed["vtables"] if row["role"] == "out_of_range")
        table["relocations"][1]["target_address"] = "0x00424F60"
        with self.assertRaisesRegex(ValueError, "complete deleting/what bodies"):
            VERIFIER.verify_graph(changed)

    def test_implicit_copy_stays_separate_from_library_methods(self):
        changed = deepcopy(self.manifest)
        copy = next(row for row in changed["bodies"] if row["role"] == "copy_constructor")
        copy["origin"] = "library"
        with self.assertRaisesRegex(ValueError, "ownership graph set"):
            VERIFIER.verify_graph(changed)

    def test_sibling_exception_shape_cannot_replace_the_recorded_type_name(self):
        changed = deepcopy(self.manifest)
        descriptor = next(row for row in changed["data_nodes"] if row["role"] == "type_descriptor")
        descriptor["type_name"] = ".?AVlength_error@std@@"
        with self.assertRaisesRegex(ValueError, "does not identify out_of_range"):
            VERIFIER.verify_graph(changed)


if __name__ == "__main__":
    unittest.main()
