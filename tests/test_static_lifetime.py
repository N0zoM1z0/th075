"""Reject unpaired compiler global-lifetime evidence."""
import importlib.util
from pathlib import Path
import unittest

SPEC = importlib.util.spec_from_file_location(
    "static_lifetime_tests", Path(__file__).resolve().parents[1] / "scripts/static_lifetime.py")
STATIC = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(STATIC)


def fixture():
    startup = [0x401000 + index * 0x20 for index in range(11)]
    records = []
    for index, address in enumerate(startup):
        records.append(dict(address=f"0x{address:08X}",
                            table_slot=f"0x{0x66C008 + 4 * index:08X}",
                            template_kind="object-init" if index < 10 else "init-only",
                            object_address=f"0x{0x670000 + index * 8:08X}",
                            registered_callback=f"0x{0x402000 + index * 0x20:08X}" if index < 10 else "",
                            destructor_callback="", count="", stride=""))
        if index < 10:
            records.append(dict(address=f"0x{0x402000 + index * 0x20:08X}",
                                table_slot="", template_kind="object-finalizer",
                                object_address=f"0x{0x670000 + index * 8:08X}",
                                registered_callback="", destructor_callback="", count="", stride=""))
    return records, startup


class StaticLifetimeTests(unittest.TestCase):
    def test_complete_startup_table_and_all_finalizers(self):
        records, startup = fixture()
        self.assertEqual(len(STATIC.check_links(records, startup)), 10)

    def test_missing_finalizer_cannot_claim_complete_lifetime(self):
        records, startup = fixture()
        records.pop(1)
        with self.assertRaisesRegex(ValueError, "static finalizer"):
            STATIC.check_links(records, startup)

    def test_finalizer_must_use_the_same_global(self):
        records, startup = fixture()
        records[1]["object_address"] = "0x00670008"
        with self.assertRaisesRegex(ValueError, "global differs"):
            STATIC.check_links(records, startup)

    def test_finalizer_cannot_appear_in_startup_table(self):
        records, startup = fixture()
        records[0]["template_kind"] = "object-finalizer"
        with self.assertRaisesRegex(ValueError, "cannot run"):
            STATIC.check_links(records, startup)

    def test_recorded_startup_slot_must_equal_real_table_position(self):
        records, startup = fixture()
        records[0]["table_slot"] = records[2]["table_slot"]
        with self.assertRaisesRegex(ValueError, "table slot"):
            STATIC.check_links(records, startup)


if __name__ == "__main__":
    unittest.main()
