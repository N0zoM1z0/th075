"""Guard import identity, call ownership and complete scalar evidence."""
from __future__ import annotations

import copy
import importlib.util
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


VERIFIER = module("test_crt_external", "verify-runtime-external-origins.py")
RUNTIME = module("test_crt_external_calls", "verify-runtime-origins.py")
SDK = module("test_crt_external_cfg", "verify-sdk-origins.py")


class RuntimeExternalOriginTests(unittest.TestCase):
    def setUp(self):
        self.code = bytes.fromhex("ff1500000000e800000000c3")
        self.relocations = [
            {"offset": 2, "type": "DIR32", "symbol": "__imp__VirtualAlloc@16",
             "addend": 0, "local_symbol_offset": None},
            {"offset": 7, "type": "REL32", "symbol": "_verified_callee",
             "addend": 0, "local_symbol_offset": None},
        ]
        self.bindings = [
            {"offset": 2, "type": "DIR32", "symbol": "__imp__VirtualAlloc@16",
             "addend": 0, "target_address": "0x2000", "target_kind": "import",
             "import_dll": "KERNEL32.dll", "import_name": "VirtualAlloc"},
            {"offset": 7, "type": "REL32", "symbol": "_verified_callee",
             "addend": 0, "target_address": "0x3000", "target_kind": "callee"},
        ]
        self.symbols = {0x3000: "_verified_callee"}
        self.imports = {0x2000: ("KERNEL32.dll", "VirtualAlloc")}

    def bind(self):
        return VERIFIER.bind_body(self.code, self.relocations, self.bindings,
                                  self.symbols, 0x1000, b"", None, RUNTIME, SDK,
                                  b"", self.imports, [])

    def test_full_iat_and_verified_direct_call(self):
        result = self.bind()
        self.assertEqual(result[:6], bytes.fromhex("ff1500200000"))
        self.assertEqual(result[-1], 0xC3)

    def test_correct_spelling_cannot_hide_wrong_import_slot(self):
        self.imports[0x2000] = ("KERNEL32.dll", "VirtualFree")
        with self.assertRaisesRegex(ValueError, "raw PE import"):
            self.bind()

    def test_callee_requires_independent_symbol_anchor(self):
        self.symbols.clear()
        with self.assertRaisesRegex(ValueError, "independently verified"):
            self.bind()

    def test_iat_pointer_cannot_be_an_arbitrary_memory_read(self):
        self.code = bytes.fromhex("8b0500000000e800000000c3")
        with self.assertRaisesRegex(ValueError, "absolute IAT call"):
            self.bind()

    def test_every_relocation_is_typed(self):
        self.bindings = copy.deepcopy(self.bindings)
        self.bindings[0]["type"] = "REL32"
        with self.assertRaisesRegex(ValueError, "metadata"):
            self.bind()

    def test_scalar_requires_all_bytes_and_readonly_extent(self):
        scalar = (0x3FF0000000000000).to_bytes(8, "little")
        readonly = [(0x4000, 8, 0x40000040)]
        VERIFIER.check_scalar(scalar, scalar, 8, readonly, 0x4000)
        with self.assertRaises(ValueError):
            VERIFIER.check_scalar(scalar, scalar[:4], 8, readonly, 0x4000)
        with self.assertRaises(ValueError):
            VERIFIER.check_scalar(scalar, scalar, 4, readonly, 0x4000)
        with self.assertRaises(ValueError):
            VERIFIER.check_scalar(scalar, scalar, 8, [(0x4000, 7, 0x40000040)], 0x4000)
        with self.assertRaises(ValueError):
            VERIFIER.check_scalar(scalar, scalar, 8, [(0x4000, 8, 0xC0000040)], 0x4000)
        with self.assertRaises(ValueError):
            VERIFIER.check_scalar(scalar, bytes(8), 8, readonly, 0x4000)


if __name__ == "__main__":
    unittest.main()
