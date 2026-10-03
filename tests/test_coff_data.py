"""Whole readonly evidence must not become a chosen prefix or mutable state."""
from pathlib import Path
import importlib.util
import hashlib
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


DATA = load("coff_readonly_data", "coff_data.py")
COFF = load("coff_readonly_names", "compare-coff-function.py")
SDK = load("coff_readonly_bindings", "verify-sdk-origins.py")
RUNTIME = load("coff_readonly_calls", "verify-runtime-origins.py")
CRT = load("coff_crt_readonly", "verify-runtime-external-origins.py")


def fixture(flags=0x40000040, relocation_count=0):
    # Two synthetic constants, eight bytes, no game or SDK contents.
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 68, 2, 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".rdata", 0, 0, 8, 60, 0, 0,
                          relocation_count, 0, flags)
    first = struct.pack("<8sIhHBB", b"_first", 0, 1, 0, 2, 0)
    second = struct.pack("<8sIhHBB", b"_second", 4, 1, 0, 3, 0)
    return header + section + b"12345678" + first + second + struct.pack("<I", 4)


class ReadonlyVendorDataTests(unittest.TestCase):
    def test_crt_binding_cannot_shrink_the_complete_section(self):
        binding = {"data_size": 8, "source_data_sha256": hashlib.sha256(b"12345678").hexdigest(),
                   "data_definitions": [{"symbol": "_first", "offset": 0},
                                        {"symbol": "_second", "offset": 4}]}
        self.assertEqual(CRT.readonly_member_data(fixture(), "_first", binding, COFF.coff_name),
                         b"12345678")
        binding["data_size"] = 4
        binding["source_data_sha256"] = hashlib.sha256(b"1234").hexdigest()
        with self.assertRaises(ValueError):
            CRT.readonly_member_data(fixture(), "_first", binding, COFF.coff_name)

    def test_crt_binding_cannot_hide_peer_definitions(self):
        binding = {"data_size": 8, "source_data_sha256": hashlib.sha256(b"12345678").hexdigest(),
                   "data_definitions": [{"symbol": "_first", "offset": 0}]}
        with self.assertRaises(ValueError):
            CRT.readonly_member_data(fixture(), "_first", binding, COFF.coff_name)

    def test_crt_binding_cannot_treat_an_interior_symbol_as_section_start(self):
        with self.assertRaisesRegex(ValueError, "section start"):
            CRT.readonly_member_data(fixture(), "_second", {}, COFF.coff_name)

    def test_evidence_keeps_the_entire_section_and_every_definition(self):
        data, definitions = DATA.readonly_section(fixture(), 1, COFF.coff_name)
        self.assertEqual(data, b"12345678")
        self.assertEqual(definitions, [{"symbol": "_first", "offset": 0},
                                      {"symbol": "_second", "offset": 4}])

    def test_mutable_initial_bytes_cannot_anchor_readonly_evidence(self):
        with self.assertRaisesRegex(ValueError, "readonly vendor data"):
            DATA.readonly_section(fixture(flags=0xC0000040), 1, COFF.coff_name)

    def test_relocated_table_requires_its_own_binding_evidence(self):
        with self.assertRaisesRegex(ValueError, "relocation-free readonly"):
            DATA.readonly_section(fixture(relocation_count=1), 1, COFF.coff_name)

    def test_section_outside_symbol_data_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "section number"):
            DATA.readonly_section(fixture(), 2, COFF.coff_name)

    def test_truncated_raw_data_cannot_claim_the_declared_full_extent(self):
        body = bytearray(fixture())
        struct.pack_into("<I", body, 40, len(body) - 4)  # Raw-data offset.
        with self.assertRaisesRegex(ValueError, "complete relocation-free"):
            DATA.readonly_section(body, 1, COFF.coff_name)

    def bind(self, destination=0x657004, member_digest=None):
        body = fixture()
        relocation = {"offset": 1, "type": "DIR32", "symbol": "_second",
                      "addend": 0, "local_symbol_offset": None}
        binding = {"offset": "1", "type": "DIR32", "symbol": "_second",
                   "target_address": hex(destination), "data_section_id": "whole",
                   "literal_hex": ""}
        sections = {"whole": {"symbols": {"_first": 0x657000, "_second": 0x657004},
                              "base": 0x657000, "size": 8,
                              "member_sha256": member_digest or hashlib.sha256(body).hexdigest()}}
        return SDK.bind_sdk_function(b"\xb8\0\0\0\0\xc3", [relocation], [binding], {},
                                     0x401000, body, COFF, RUNTIME, None, sections)

    def test_binding_uses_the_symbol_offset_inside_the_whole_section(self):
        linked, fields = self.bind()
        self.assertEqual(struct.unpack_from("<I", linked, 1)[0], 0x657004)
        self.assertEqual(fields, {0x401001: 0x657004})

    def test_same_bytes_at_another_offset_do_not_prove_a_symbol_binding(self):
        with self.assertRaisesRegex(ValueError, "complete section definition"):
            self.bind(destination=0x657000)

    def test_local_static_symbol_cannot_borrow_another_members_data(self):
        with self.assertRaisesRegex(ValueError, "same source member"):
            self.bind(member_digest="0" * 64)


if __name__ == "__main__":
    unittest.main()
