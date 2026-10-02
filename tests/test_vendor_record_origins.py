"""Complete VC7 template extents include local catch labels, not peer functions."""
import importlib.util
from pathlib import Path
import struct
import unittest


ROOT = Path(__file__).resolve().parents[1]


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


RECORD = load("vendor_record_origins", "verify-vendor-record-origins.py")
COFF = load("vendor_record_coff", "compare-coff-function.py")
SDK = load("vendor_record_cfg", "verify-sdk-origins.py")


def object_with_catch(peer_storage):
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 62, 3, 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 2, 60, 0, 0,
                          0, 0, 0x60501020)
    primary = struct.pack("<8sIhHBB", b"_primary", 0, 1, 0x20, 2, 1)
    auxiliary = bytearray(18)
    struct.pack_into("<I", auxiliary, 4, 2)
    peer = struct.pack("<8sIhHBB", b"$L1", 1, 1, 0x20, peer_storage, 0)
    return header + section + b"\xC3\xC3" + primary + auxiliary + peer + struct.pack("<I", 4)


class VendorRecordOriginTests(unittest.TestCase):
    def test_local_catch_label_does_not_split_the_auxiliary_extent(self):
        self.assertEqual(RECORD.complete_aux_section_size(
            object_with_catch(3), "_primary", COFF.coff_name), 2)

    def test_external_peer_cannot_be_hidden_inside_the_extent(self):
        with self.assertRaisesRegex(ValueError, "one complete code COMDAT"):
            RECORD.complete_aux_section_size(object_with_catch(2), "_primary",
                                             COFF.coff_name)

    def test_every_relocation_stays_typed_and_explicit(self):
        source = bytearray(b"\xB8\0\0\0\0\xC3")
        actual = b"\xB8\x00\x20\x40\x00\xC3"
        relocation = dict(offset=1, type_id=6, type="DIR32", symbol="global",
                          addend=0, local_symbol_offset=None)
        binding = dict(offset=1, type="DIR32", symbol="global",
                       addend=0, target_address="0x00402000")
        self.assertEqual(RECORD.compare_complete_body(
            source, [relocation], actual, 0x401000, [binding], COFF, SDK), 0)
        binding["symbol"] = "unrelated"
        with self.assertRaisesRegex(ValueError, "typed relocation"):
            RECORD.compare_complete_body(source, [relocation], actual, 0x401000,
                                         [binding], COFF, SDK)


if __name__ == "__main__":
    unittest.main()
