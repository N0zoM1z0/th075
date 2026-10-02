"""Guarded switches need full remaps, tables and decoded data flow."""
import hashlib
import importlib.util
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("authored_switch_tests", ROOT / "scripts/authored_switches.py")
SWITCHES = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SWITCHES)


def fixture(remap=b"\0\1"):
    # Synthetic two-case switch, no game instructions or tables.
    body = (b"\x83\x7d\xfc\x01\x77\x11\x8b\x45\xfc\x0f\xb6\x88"
            + struct.pack("<I", 0x5000) + b"\xff\x24\x8d" + struct.pack("<I", 0x5100) + b"\xc3")
    table = struct.pack("<II", 0x401017, 0x401017)
    record = {"jump_site": "0x401010", "range_site": "0x401000", "default_target": "0x401017",
              "remap_address": "0x5000", "remap_size": "2", "remap_sha256": hashlib.sha256(remap).hexdigest(),
              "table_address": "0x5100", "table_size": "8", "table_sha256": hashlib.sha256(table).hexdigest()}
    return body, record, lambda address, size: {0x5000: remap, 0x5100: table}[address][:size]


class AuthoredSwitchTests(unittest.TestCase):
    def test_complete_guard_remap_and_every_case_target_are_verified(self):
        body, record, read = fixture()
        self.assertEqual(SWITCHES.verify_switches(body, 0x401000, [record], read),
                         {0x401010: [0x401017, 0x401017]})

    def test_remap_reaching_an_unrecorded_case_cannot_match_a_table_prefix(self):
        body, record, read = fixture(remap=b"\0\2")
        with self.assertRaisesRegex(ValueError, "complete reachable jump table"):
            SWITCHES.verify_switches(body, 0x401000, [record], read)

    def test_remap_cannot_read_a_different_unbounded_index_register(self):
        body, record, read = fixture()
        body = bytearray(body)
        body[11] = 0x8B  # MOVZX ECX, [EBX+table] rather than the guarded EAX selector.
        with self.assertRaisesRegex(ValueError, "bounded selector"):
            SWITCHES.verify_switches(body, 0x401000, [record], read)


def direct_fixture(targets=(0x401010, 0x401010)):
    body = (b"\x83\x7d\xfc\x01\x77\x0a\x8b\x45\xfc\xff\x24\x85"
            + struct.pack("<I", 0x5100) + b"\xc3")
    table = struct.pack("<II", *targets)
    record = {"jump_site": "0x401009", "range_site": "0x401000",
              "default_target": "0x401010", "table_address": "0x5100",
              "table_size": "8", "table_sha256": hashlib.sha256(table).hexdigest()}
    return body, record, lambda address, size: table[:size]


class DirectAuthoredSwitchTests(unittest.TestCase):
    def test_guard_and_all_direct_table_targets_are_verified(self):
        body, record, read = direct_fixture()
        self.assertEqual(SWITCHES.verify_direct_switches(body, 0x401000, [record], read),
                         {0x401009: [0x401010, 0x401010]})

    def test_direct_table_target_outside_complete_body_is_rejected(self):
        body, record, read = direct_fixture((0x401010, 0x401011))
        with self.assertRaisesRegex(ValueError, "external tail or non-instruction"):
            SWITCHES.verify_direct_switches(body, 0x401000, [record], read)

    def test_direct_dispatch_must_load_the_guarded_slot(self):
        body, record, read = direct_fixture()
        body = body[:8] + b"\xf8" + body[9:]  # MOV EAX, [EBP-8], not [EBP-4].
        with self.assertRaisesRegex(ValueError, "differs from its range guard"):
            SWITCHES.verify_direct_switches(body, 0x401000, [record], read)


if __name__ == "__main__":
    unittest.main()
