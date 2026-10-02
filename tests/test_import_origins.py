"""Import-thunk evidence must resolve through the raw PE descriptors."""
import importlib.util
from pathlib import Path
import struct
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("import_origins", ROOT / "scripts/verify-import-origins.py")
IMPORTS = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(IMPORTS)


class ImportOriginTests(unittest.TestCase):
    def fixture(self):
        base = 0x400000
        data = bytearray(0x1000)
        struct.pack_into("<IIIII", data, 0x100, 0x300, 0, 0, 0x400, 0x200)
        struct.pack_into("<I", data, 0x300, 0x500)
        struct.pack_into("<I", data, 0x200, 0x500)
        data[0x400:0x409] = b"TEST.dll\0"
        data[0x500:0x50B] = b"\0\0ImportMe\0"

        def read(address, size):
            offset = address - base
            if offset < 0 or offset + size > len(data):
                raise ValueError("synthetic PE read out of bounds")
            return bytes(data[offset:offset + size])

        return data, read, base

    def test_complete_descriptor_and_slot_prove_import_name(self):
        _, read, base = self.fixture()
        slots = IMPORTS.import_table(read, base, 0x100, 40)
        self.assertEqual(slots, {0x400200: ("TEST.dll", "ImportMe")})
        IMPORTS.check_thunk(b"\xFF\x25\x00\x02\x40\x00", 0x400200,
                            slots[0x400200], "TEST.dll", "ImportMe")

    def test_slot_and_symbol_cannot_be_guessed(self):
        _, read, base = self.fixture()
        slots = IMPORTS.import_table(read, base, 0x100, 40)
        with self.assertRaisesRegex(ValueError, "complete FF 25"):
            IMPORTS.check_thunk(b"\xFF\x25\x04\x02\x40\x00", 0x400200,
                                slots[0x400200], "TEST.dll", "ImportMe")
        with self.assertRaisesRegex(ValueError, "recorded import"):
            IMPORTS.check_thunk(b"\xFF\x25\x00\x02\x40\x00", 0x400200,
                                slots[0x400200], "TEST.dll", "Other")

    def test_iat_must_match_original_lookup(self):
        data, read, base = self.fixture()
        struct.pack_into("<I", data, 0x200, 0x504)
        with self.assertRaisesRegex(ValueError, "IAT slot differs"):
            IMPORTS.import_table(read, base, 0x100, 40)


if __name__ == "__main__":
    unittest.main()
