"""Additional record widths must not collapse distinct STL template families."""
import importlib.util
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "vendor_additional_records", ROOT / "scripts/verify-vendor-additional-records.py")
ADDITIONAL = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(ADDITIONAL)


def candidate(symbol, code=b"\x55\x8b\xec\x5d\xc3"):
    return symbol, len(code), bytearray(code), [], set(), ADDITIONAL.family(symbol)


class VendorAdditionalRecordTests(unittest.TestCase):
    def test_different_widths_can_still_name_one_family(self):
        first = candidate("?_Assign_n@Rec4")
        second = candidate("?_Assign_n@Rec64")
        self.assertEqual(ADDITIONAL.unique_family(bytes(first[2]), [first, second],
                                                  first[0], "?_Assign_n@RecN"),
                         [first[0], second[0]])

    def test_copy_and_copy_backward_remain_separate_families(self):
        first = candidate("??$copy@Rec4")
        second = candidate("??$copy_backward@Rec4")
        with self.assertRaisesRegex(ValueError, "one complete template family"):
            ADDITIONAL.unique_family(bytes(first[2]), [first, second],
                                     first[0], ADDITIONAL.family(first[0]))


if __name__ == "__main__":
    unittest.main()
