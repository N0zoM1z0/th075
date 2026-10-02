"""A helper's probe aliases may vary by synthetic width, not by STL family."""
import importlib.util
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "vendor_record_helpers", ROOT / "scripts/verify-vendor-record-helpers.py")
HELPERS = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(HELPERS)


def candidate(symbol, body=b"\x55\x8b\xec\x5d\xc3"):
    return symbol, len(body), bytearray(body), [], set(), HELPERS.template_family(symbol)


class VendorRecordHelperTests(unittest.TestCase):
    def test_synthetic_width_aliases_keep_one_family(self):
        first = candidate("?_Xlen@Record16")
        second = candidate("?_Xlen@Record44")
        matches = HELPERS.unique_family(bytes(first[2]), [first, second],
                                        first[0], "?_Xlen@RecordN")
        self.assertEqual(matches, [first[0], second[0]])

    def test_different_matching_template_families_remain_pending(self):
        first = candidate("??$copy@Record16")
        second = candidate("??$copy_backward@Record16")
        with self.assertRaisesRegex(ValueError, "unique VC7 template family"):
            HELPERS.unique_family(bytes(first[2]), [first, second],
                                  first[0], HELPERS.template_family(first[0]))

    def test_recorded_symbol_must_be_a_whole_body_match(self):
        first = candidate("?_Xlen@Record16")
        other = candidate("?_Xlen@Record44", b"\x55\x8b\xec\x90\xc3")
        with self.assertRaisesRegex(ValueError, "unique VC7 template family"):
            HELPERS.unique_family(bytes(first[2]), [first, other],
                                  other[0], "?_Xlen@RecordN")


if __name__ == "__main__":
    unittest.main()
