"""A generated deleting destructor must retain both typed call destinations."""
import importlib.util
from pathlib import Path
import struct
import unittest


ROOT = Path(__file__).resolve().parents[1]


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


SCALAR = load("scalar_test", "verify-scalar-deleting-origins.py")
CFG = load("scalar_cfg_test", "verify-authored-origins.py")
SOURCE = bytes.fromhex(
    "558bec51894dfc8b4dfce8000000008b450883e001740c8b4dfc51"
    "e80000000083c4048b45fc8be55dc20400")
OPTIMIZED = load("optimized_scalar_test", "verify-optimized-deleting-origins.py")
OPTIMIZED_SOURCE = bytes.fromhex(
    "568bf1e800000000f644240801740756e800000000598bc65ec20400")


def body(address=0x00412340, destructor=0x00415000, delete=SCALAR.DELETE_ADDRESS):
    code = bytearray(SOURCE)
    for offset, destination in [(11, destructor), (28, delete)]:
        struct.pack_into("<i", code, offset, destination - (address + offset + 4))
    return bytes(code)


class ScalarDeletingOriginTests(unittest.TestCase):
    def test_complete_emission_and_both_calls_are_accepted(self):
        self.assertEqual(SCALAR.verify_target_body(body(), 0x00412340, SOURCE,
                                                   {0x00415000}, CFG), 0x00415000)

    def test_wrong_delete_destination_cannot_inherit_compiler_origin(self):
        with self.assertRaisesRegex(ValueError, "known operator delete"):
            SCALAR.verify_target_body(body(delete=0x00416000), 0x00412340,
                                      SOURCE, {0x00415000}, CFG)

    def test_undocumented_destructor_entry_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "recorded function entry"):
            SCALAR.verify_target_body(body(), 0x00412340, SOURCE, set(), CFG)

    def test_changed_branch_or_extra_instruction_is_rejected(self):
        altered = bytearray(body())
        altered[22] = 0x0D
        with self.assertRaisesRegex(ValueError, "whole deleting-destructor body"):
            SCALAR.verify_target_body(bytes(altered), 0x00412340,
                                      SOURCE, {0x00415000}, CFG)
        with self.assertRaisesRegex(ValueError, "whole deleting-destructor body"):
            SCALAR.verify_target_body(body() + b"\x90", 0x00412340,
                                      SOURCE, {0x00415000}, CFG)

    def test_optimized_whole_body_uses_its_own_relocation_offsets(self):
        address, destructor = 0x00612340, 0x00615000
        code = bytearray(OPTIMIZED_SOURCE)
        for offset, destination in [(4, destructor), (17, SCALAR.DELETE_ADDRESS)]:
            struct.pack_into("<i", code, offset, destination - (address + offset + 4))
        self.assertEqual(SCALAR.verify_target_body(
            bytes(code), address, OPTIMIZED_SOURCE, {destructor}, CFG,
            size=OPTIMIZED.SIZE, fields=OPTIMIZED.FIELDS), destructor)
        with self.assertRaisesRegex(ValueError, "known operator delete"):
            struct.pack_into("<i", code, 17, 0x00616000 - (address + 21))
            SCALAR.verify_target_body(bytes(code), address, OPTIMIZED_SOURCE,
                                      {destructor}, CFG, size=OPTIMIZED.SIZE,
                                      fields=OPTIMIZED.FIELDS)


if __name__ == "__main__":
    unittest.main()
