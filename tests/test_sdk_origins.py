"""Protect whole vendor extents from convenient prefixes and unresolved tails."""
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


SDK = load("sdk_origins", "verify-sdk-origins.py")
COFF = load("sdk_origin_coff", "compare-coff-function.py")


def object_with_functions(functions):
    # Synthetic two-RET COMDAT with no auxiliary size records or game bytes.
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 62, len(functions), 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 2, 60, 0, 0, 0, 0, 0x60101020)
    symbols = b"".join(struct.pack("<8sIhHBB", name, offset, 1, 0x20, 2, 0)
                       for name, offset in functions)
    return header + section + b"\xc3\xc3" + symbols + struct.pack("<I", 4)


def object_with_real_constant(value):
    name = b"__real@3f800000\0"
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 64, 1, 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".rdata", 0, 0, 4, 60, 0, 0, 0, 0, 0x40301040)
    symbol = struct.pack("<8sIhHBB", struct.pack("<II", 0, 4), 0, 1, 0, 2, 0)
    return header + section + value + symbol + struct.pack("<I", 4 + len(name)) + name


class SDKOriginExtentTests(unittest.TestCase):
    def test_whole_extent_comes_from_vendor_section_without_target_size(self):
        body = object_with_functions([(b"_first", 0)])
        self.assertEqual(SDK.complete_comdat_size(body, "_first", COFF.coff_name), 2)

    def test_multiple_functions_cannot_be_claimed_as_one_comdat(self):
        body = object_with_functions([(b"_first", 0), (b"_second", 1)])
        with self.assertRaisesRegex(ValueError, "one complete function"):
            SDK.complete_comdat_size(body, "_first", COFF.coff_name)

    def test_nonzero_symbol_cannot_select_a_convenient_prefix(self):
        body = object_with_functions([(b"_second", 1)])
        with self.assertRaisesRegex(ValueError, "one complete function"):
            SDK.complete_comdat_size(body, "_second", COFF.coff_name)

    def test_unresolved_jump_cannot_be_hidden_by_whole_byte_identity(self):
        with self.assertRaisesRegex(ValueError, "unresolved vendor jump"):
            SDK.verify_control_flow(b"\xff\xe0\xc3", 0x401000)  # JMP EAX; RET.

    def test_internal_loop_must_target_an_instruction_start(self):
        with self.assertRaisesRegex(ValueError, "unresolved vendor jump"):
            SDK.verify_control_flow(b"\xb8\0\0\0\0\xeb\xfa\xc3", 0x401000)

    def test_bound_call_must_use_the_decoded_destination(self):
        with self.assertRaisesRegex(ValueError, "decoded destination"):
            SDK.verify_control_flow(b"\xe8\xfb\x0f\0\0\xc3", 0x401000,
                                    {0x401001: 0x403000})

    def test_recorded_call_cannot_hide_a_mov_immediate(self):
        with self.assertRaisesRegex(ValueError, "non-call instruction"):
            SDK.verify_control_flow(b"\xb8\0\0\0\0\xc3", 0x401000,
                                    {0x401001: 0x402000})

    def test_complete_internal_tail_is_not_truncated_at_first_return(self):
        self.assertEqual(SDK.verify_control_flow(b"\xc3\xeb\xfd", 0x401000), 0)

    def test_trailing_conditional_branch_cannot_fall_outside_extent(self):
        with self.assertRaisesRegex(ValueError, "trailing fallthrough"):
            SDK.verify_control_flow(b"\xc3\x75\xfd", 0x401000)

    def test_real_constant_requires_both_symbol_bits_and_vendor_data(self):
        body = object_with_real_constant(b"\0\0\x80\x3f")
        self.assertEqual(SDK.real_constant(body, "__real@3f800000", COFF.coff_name),
                         b"\0\0\x80\x3f")

    def test_real_constant_symbol_cannot_hide_different_vendor_data(self):
        body = object_with_real_constant(b"\0\0\0\x40")
        with self.assertRaisesRegex(ValueError, "scalar bits"):
            SDK.real_constant(body, "__real@3f800000", COFF.coff_name)

    def test_constant_binding_cannot_cover_an_opcode(self):
        with self.assertRaisesRegex(ValueError, "opcode or partial field"):
            SDK.verify_control_flow(b"\xc3", 0x401000, {}, {0x401000: 0x65747C})

    def test_function_pointer_requires_the_verified_callee_symbol(self):
        class RuntimeStub:
            @staticmethod
            def bind_calls(code, calls, bindings, symbols, address):
                return bytearray(code)

        relocation = dict(offset=1, type="DIR32", symbol="vendor_target",
                          addend=0, local_symbol_offset=None)
        binding = dict(offset="0x1", type="DIR32", symbol="vendor_target",
                       target_address="0x00402000", literal_hex="",
                       data_section_id="", target_kind="function")
        code = b"\xb8\0\0\0\0\xc3"
        linked, fields = SDK.bind_sdk_function(
            code, [relocation], [binding], {0x402000: "vendor_target"},
            0x401000, b"", None, RuntimeStub, None)
        self.assertEqual(struct.unpack_from("<I", linked, 1)[0], 0x402000)
        self.assertEqual(fields, {0x401001: 0x402000})
        with self.assertRaisesRegex(ValueError, "verified complete callee"):
            SDK.bind_sdk_function(code, [relocation], [binding], {}, 0x401000,
                                  b"", None, RuntimeStub, None)


if __name__ == "__main__":
    unittest.main()
