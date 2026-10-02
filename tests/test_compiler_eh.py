"""Compiler exclusion needs real frame/table links and complete pure dispatch."""
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("compiler_eh_tests", ROOT / "scripts/compiler_eh.py")
EH = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(EH)


def fixture(to_state=0, cleanup=0x404000):
    info = struct.pack("<7I", 0x19930520, 2, 0x6100, 0, 0, 0, 0)
    table = struct.pack("<iIiI", -1, cleanup, to_state, 0)
    handler = b"\xb8" + struct.pack("<I", 0x6000) + b"\xe9" + struct.pack("<i", 0x6407B8 - 0x40300A)
    parent = b"\x55\x8b\xec\x6a\xff\x68" + struct.pack("<I", 0x403000) + b"\x64\xa1\0\0\0\0"
    memory = {0x6000: info, 0x6100: table, 0x403000: handler, 0x401000: parent}
    record = {"handler_address": "0x00403000", "funcinfo_address": "0x00006000",
              "funcinfo_sha256": hashlib.sha256(info).hexdigest(), "state_count": "2",
              "unwind_address": "0x00006100", "unwind_sha256": hashlib.sha256(table).hexdigest(),
              "try_count": "0", "trymap_address": "0x00000000",
              "entries": json.dumps([{"state_index": 0, "to_state": -1,
                                      "cleanup_address": f"0x{cleanup:08X}"},
                                     {"state_index": 1, "to_state": to_state,
                                      "cleanup_address": "0x00000000"}]),
              "owners": json.dumps([{"owner_address": "0x00401000", "handler_push_site": "0x401005"}])}
    return record, lambda address, size: memory[address][:size], memory


class CompilerEHOriginTests(unittest.TestCase):
    def test_complete_frame_object_dispatch_is_recognized(self):
        body = b"\x8b\x4d\xf0\xe9" + struct.pack("<i", 0x402000 - 0x401008)
        self.assertEqual(EH.cleanup_template(body, 0x401000, {0x402000}), ("frame-object", 0x402000))

    def test_by_value_parameter_cleanup_uses_the_argument_frame_slot(self):
        body = b"\x8d\x4d\x08\xe9" + struct.pack("<i", 0x402000 - 0x401008)
        self.assertEqual(EH.cleanup_template(body, 0x401000, {0x402000}), ("parameter-object", 0x402000))

    def test_placement_failure_can_use_its_context_parameter(self):
        body = (b"\x8b\x45\x08\x50\x8b\x4d\xec\x51\xe8"
                + struct.pack("<i", 0x402000 - 0x40100D) + b"\x83\xc4\x08\xc3")
        self.assertEqual(EH.cleanup_template(body, 0x401000, {0x402000}),
                         ("placement-allocation", 0x402000))

    def test_absolute_application_global_cannot_be_hidden_as_a_frame_slot(self):
        body = b"\x8b\x0d\0\x50\0\0\xe9" + struct.pack("<i", 0x402000 - 0x40100B)
        with self.assertRaisesRegex(ValueError, "unsupported compiler cleanup"):
            EH.cleanup_template(body, 0x401000, {0x402000})

    def test_indirect_shared_tail_requires_separate_evidence(self):
        with self.assertRaisesRegex(ValueError, "unresolved destination"):
            EH.cleanup_template(b"\x8b\x4d\xf0\xff\xe0", 0x401000, {0x402000})

    def test_truncated_cleanup_cannot_select_a_convenient_prefix(self):
        with self.assertRaisesRegex(ValueError, "incomplete compiler cleanup"):
            EH.cleanup_template(b"\x8b\x4d\xf0\xe9", 0x401000, {0x402000})

    def test_unwind_table_must_reference_a_known_complete_candidate_entry(self):
        record, read, _ = fixture(cleanup=0x404001)
        with self.assertRaisesRegex(ValueError, "cleanup entry"):
            EH.verify_frame(record, read, read, {0x401000, 0x404000})

    def test_cleanup_state_must_unwind_to_an_earlier_state(self):
        record, read, _ = fixture(to_state=1)
        with self.assertRaisesRegex(ValueError, "state transition"):
            EH.verify_frame(record, read, read, {0x401000, 0x404000})

    def test_metadata_without_a_parent_registration_cannot_exclude_functions(self):
        record, read, memory = fixture()
        memory[0x401000] = b"\x90" * 16
        with self.assertRaisesRegex(ValueError, "registration prefix"):
            EH.verify_frame(record, read, read, {0x401000, 0x404000})

    def test_full_frame_and_all_state_entries_are_verified(self):
        record, read, _ = fixture()
        result = EH.verify_frame(record, read, read, {0x401000, 0x404000})
        self.assertEqual(result, json.loads(record["entries"]))


if __name__ == "__main__":
    unittest.main()
