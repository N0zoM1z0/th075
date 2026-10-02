"""Local CRT pointer bindings must stay within independently checked bodies."""
import importlib.util
from pathlib import Path
import struct
import unittest

SPEC = importlib.util.spec_from_file_location(
    "runtime_local_tests", Path(__file__).resolve().parents[1] / "scripts/verify-runtime-local-origins.py")
LOCAL = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(LOCAL)


class RuntimeLocalTests(unittest.TestCase):
    def test_complete_internal_pointer_uses_own_symbol_offset_and_addend(self):
        code = b"\xb8\0\0\0\0\x90\xc3"
        relocation = dict(offset=1, type="DIR32", local_symbol_offset=5, addend=1)
        linked, destinations = LOCAL.bind_local(code, [relocation], 0x401000, set())
        self.assertEqual(struct.unpack_from("<I", linked, 1)[0], 0x401006)
        self.assertEqual(destinations, [0x401006])

    def test_external_pointer_requires_an_independently_checked_dependency(self):
        code = b"\xb8\0\0\0\0\xc3"
        relocation = dict(offset=1, type="DIR32", local_symbol_offset=-10, addend=0)
        with self.assertRaisesRegex(ValueError, "escapes"):
            LOCAL.bind_local(code, [relocation], 0x401000, set())
        self.assertEqual(LOCAL.bind_local(code, [relocation], 0x401000, {0x400FF6})[1], [0x400FF6])

    def test_relocated_call_cannot_be_hidden_as_a_local_pointer(self):
        code = b"\xe8\0\0\0\0\xc3"
        relocation = dict(offset=1, type="REL32", local_symbol_offset=5, addend=0)
        with self.assertRaisesRegex(ValueError, "unsupported"):
            LOCAL.bind_local(code, [relocation], 0x401000, set())


if __name__ == "__main__":
    unittest.main()
