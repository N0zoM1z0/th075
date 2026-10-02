"""Public regression checks for fail-closed analysis and exact comparison."""
from __future__ import annotations
import contextlib
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]


def load(name: str, filename: str):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


GHIDRA = load("th075_ghidra", "ghidra.py")
COMPARE = load("th075_compare", "compare-coff-function.py")


class GhidraContractTests(unittest.TestCase):
    def test_native_option_cannot_be_an_address(self):
        with self.assertRaises(ValueError):
            GHIDRA.checked_addresses(["-overwrite"])

    def test_text_filter_is_not_a_headless_option(self):
        self.assertEqual(GHIDRA.query_script_args("search_strings", ["10", "-overwrite"]),
                         ["10", "text:-overwrite"])

    def test_native_query_bounds(self):
        with self.assertRaises(ValueError):
            GHIDRA.query_script_args("disassemble", ["501", "0x401000"])
        with self.assertRaises(ValueError):
            GHIDRA.query_script_args("list_functions", ["0", "501", ""])

    def test_zero_exit_without_operation_marker_is_rejected(self):
        completed = subprocess.CompletedProcess([], 0,
            "INFO VerifyTarget.java> TEST_ATTESTATION (GhidraScript)\n", "")
        with patch.object(GHIDRA, "find_analyzer", return_value=(Path("/fake"), Path("/fake/headless"))), \
             patch.object(GHIDRA.subprocess, "run", return_value=completed), \
             contextlib.redirect_stdout(io.StringIO()):
            with self.assertRaisesRegex(RuntimeError, "TEST_QUERY"):
                GHIDRA.run_headless([], "TEST_ATTESTATION", "TEST_QUERY")

    def test_marker_in_script_arguments_is_not_success(self):
        completed = subprocess.CompletedProcess([], 0,
            "INFO REPORT: Execute script: QueryProgram.java 'TEST_ATTESTATION'\n", "")
        with patch.object(GHIDRA, "find_analyzer", return_value=(Path("/fake"), Path("/fake/headless"))), \
             patch.object(GHIDRA.subprocess, "run", return_value=completed), \
             contextlib.redirect_stdout(io.StringIO()):
            with self.assertRaises(RuntimeError):
                GHIDRA.run_headless([], "TEST_ATTESTATION")


class ExactComparisonTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        (self.root / "build").mkdir()
        (self.root / "config").mkdir()
        (self.root / "source.cpp").write_text("// synthetic test source\n")
        # Synthetic i386 COFF: mov eax, relocated-global; ret. No game bytes.
        code = bytes.fromhex("b800000000c3")
        header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 76, 3, 0, 0)
        section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 6, 60, 66, 0, 1, 0, 0x60000020)
        relocation = struct.pack("<IIH", 1, 2, 6)
        function = struct.pack("<8sIhHBB", b"_f", 0, 1, 0x20, 2, 1)
        auxiliary = struct.pack("<IIIIH", 0, 6, 0, 0, 0)
        global_symbol = struct.pack("<8sIhHBB", b"_g", 0, 0, 0, 2, 0)
        (self.root / "build/probe.obj").write_bytes(
            header + section + code + relocation + function + auxiliary + global_symbol + struct.pack("<I", 4))
        self.target = bytes.fromhex("b878563412c3")
        self.relocations = '[{ offset = 1, type = "DIR32", symbol = "_g", target = 0x12345678 }]'
        self.write_manifest()

    def write_manifest(self, relocations=None, size=6, compare_size=6, manifest_hash=None):
        digest = "0" * 64
        (self.root / "config/target.toml").write_text(f'[target]\nsha256 = "{digest}"\n')
        (self.root / "config/match-units.toml").write_text(
            f'schema_version = 1\ntarget_sha256 = "{manifest_hash or digest}"\n'
            '[units.test]\nsource = "source.cpp"\nobject = "build/probe.obj"\n'
            'profile = ["/Od"]\nfunctions = ["f"]\nsymbol = "_f"\ntarget_address = 0x401000\n'
            f'size = {size}\ncompare_size = {compare_size}\nrelocations = {relocations or self.relocations}\n')

    def compare(self):
        with patch.object(COMPARE, "ROOT", self.root), \
             patch.object(COMPARE, "TARGET_MANIFEST", self.root / "config/target.toml"), \
             patch.object(COMPARE, "UNITS_MANIFEST", self.root / "config/match-units.toml"), \
             patch.object(COMPARE, "verified_target", return_value=self.target), \
             patch.object(COMPARE, "pe_bytes_at", return_value=self.target):
            return COMPARE.compare_unit("test")

    def test_complete_relocation_replay(self):
        result = self.compare()
        self.assertEqual(result["result"], "exact")
        self.assertEqual(result["matched_compared_bytes"], 6)

    def test_omitted_relocation_cannot_earn_exactness(self):
        self.write_manifest(relocations="[]")
        with self.assertRaisesRegex(ValueError, "relocations differ"):
            self.compare()

    def test_truncated_extent_is_rejected(self):
        self.write_manifest(size=5, compare_size=5)
        with self.assertRaisesRegex(ValueError, "object function size"):
            self.compare()

    def test_wrong_manifest_identity_is_rejected(self):
        self.write_manifest(manifest_hash="1" * 64)
        with self.assertRaisesRegex(ValueError, "target identity mismatch"):
            self.compare()

    def test_nonrelocation_byte_mismatch_is_not_exact(self):
        self.target = bytes.fromhex("b978563412c3")
        self.assertEqual(self.compare()["result"], "mismatch")

    def define_local_destination(self, offset):
        path = self.root / "build/probe.obj"
        data = bytearray(path.read_bytes())
        struct.pack_into("<Ih", data, 120, offset, 1)
        path.write_bytes(data)
        self.target = bytes.fromhex("b805104000c3")
        self.write_manifest(relocations='[{ offset = 1, type = "DIR32", symbol = "_g", target = 0x401005 }]')

    def test_local_destination_follows_coff_layout(self):
        self.define_local_destination(5)
        self.assertEqual(self.compare()["result"], "exact")

    def test_manifest_cannot_hide_a_moved_local_label(self):
        self.define_local_destination(4)
        with self.assertRaisesRegex(ValueError, "local relocation destination differs"):
            self.compare()

    def test_local_label_outside_function_is_rejected(self):
        self.define_local_destination(7)
        with self.assertRaisesRegex(ValueError, "outside the function extent"):
            self.compare()


if __name__ == "__main__":
    unittest.main()
