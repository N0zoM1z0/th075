"""A full caller can disambiguate an STL helper only through its typed call."""
import importlib.util
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "vendor_record_witnesses", ROOT / "scripts/verify-vendor-record-witnesses.py")
WITNESSES = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(WITNESSES)


class VendorRecordWitnessTests(unittest.TestCase):
    def test_exact_typed_call_field_names_the_callee(self):
        binding = dict(offset=17, type="REL32", symbol="vendor_copy",
                       target_address="0x00402000")
        WITNESSES.require_typed_caller([binding], 17, "vendor_copy", "0x00402000")

    def test_wrong_symbol_or_destination_cannot_supply_a_witness(self):
        binding = dict(offset=17, type="REL32", symbol="vendor_copy",
                       target_address="0x00402000")
        with self.assertRaisesRegex(ValueError, "complete typed caller witness"):
            WITNESSES.require_typed_caller([binding], 17, "vendor_copy_backward",
                                           "0x00402000")
        with self.assertRaisesRegex(ValueError, "complete typed caller witness"):
            WITNESSES.require_typed_caller([binding], 17, "vendor_copy",
                                           "0x00403000")


if __name__ == "__main__":
    unittest.main()
