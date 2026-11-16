"""The frontier ratchet passes, catches regressions, records improvements."""
import hashlib
import importlib.util
import io
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("check_frontier", ROOT / "scripts/check-frontier.py")
FRONTIER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(FRONTIER)

TARGET = bytes(range(16))
HEADER = "# test frontiers\n"


class FrontierTest(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.path = Path(self.directory.name) / "frontiers.toml"
        entry = dict(character="Test", kind="object", source="probes/none.cpp",
                     flags=["/Od"], symbol="?Advance@T@@UAEXXZ", address=0x401000,
                     size=len(TARGET), target_sha256=hashlib.sha256(TARGET).hexdigest(),
                     object_size=16, differing="4-7,12")
        self.path.write_text(HEADER)
        self.path.write_text(self.dump({"t": entry}))
        self.code = bytearray(TARGET)
        self.code[4:8] = b"\xff" * 4
        self.code[12] = 0xFF
        # The relocation field 0-3 differs but is masked.
        self.code[0:4] = b"\xee" * 4
        self.saved = FRONTIER.FRONTIERS, FRONTIER.build, FRONTIER.COFF.pe_bytes_at
        FRONTIER.FRONTIERS = self.path
        FRONTIER.build = lambda entry: (bytes(self.code), [dict(offset=0)])
        FRONTIER.COFF.pe_bytes_at = lambda data, address, size: TARGET
        self.verified = FRONTIER.COFF.verified_target
        FRONTIER.COFF.verified_target = lambda: b""

    def tearDown(self):
        FRONTIER.FRONTIERS, FRONTIER.build, FRONTIER.COFF.pe_bytes_at = self.saved
        FRONTIER.COFF.verified_target = self.verified
        self.directory.cleanup()

    def dump(self, frontiers):
        saved = FRONTIER.FRONTIERS
        FRONTIER.FRONTIERS = self.path
        try:
            return FRONTIER.dump(frontiers)
        finally:
            FRONTIER.FRONTIERS = saved

    def run_main(self, *argv):
        out, err = io.StringIO(), io.StringIO()
        with redirect_stdout(out), redirect_stderr(err):
            code = FRONTIER.main(list(argv))
        return code, out.getvalue() + err.getvalue()

    def test_unchanged_parent_passes(self):
        code, output = self.run_main()
        self.assertEqual(code, 0, output)
        self.assertIn("5 differing of 16", output)

    def test_regression_fails(self):
        self.code[9] = 0xFF
        code, output = self.run_main("t")
        self.assertEqual(code, 1)
        self.assertIn("1 matching bytes now differ, first at 0x9", output)

    def test_size_change_fails(self):
        self.code += b"\x90"
        code, output = self.run_main("t")
        self.assertEqual(code, 1)
        self.assertIn("body size 17", output)

    def test_improvement_is_recorded_only_with_update(self):
        self.code[12] = TARGET[12]
        before = self.path.read_text()
        code, output = self.run_main("t")
        self.assertEqual((code, self.path.read_text()), (0, before))
        self.assertIn("run with --update", output)
        code, output = self.run_main("--update", "t")
        self.assertEqual(code, 0, output)
        self.assertEqual(FRONTIER.load(self.path)["t"]["differing"], "4-7")
        self.assertTrue(self.path.read_text().startswith(HEADER))
        self.assertEqual(self.run_main("t")[0], 0)

    def test_changed_original_extent_fails(self):
        FRONTIER.COFF.pe_bytes_at = lambda data, address, size: bytes(16)
        code, output = self.run_main("t")
        self.assertEqual(code, 1)
        self.assertIn("SHA-256 differs", output)

    def test_unknown_name_is_rejected(self):
        code, output = self.run_main("missing")
        self.assertEqual(code, 2)
        self.assertIn("unknown frontier: missing", output)

    def test_ranges_round_trip(self):
        offsets = {0, 1, 2, 5, 9, 10}
        self.assertEqual(FRONTIER.format_ranges(offsets), "0-2,5,9-10")
        self.assertEqual(FRONTIER.parse_ranges("0-2,5,9-10"), offsets)


if __name__ == "__main__":
    unittest.main()
