"""Non-destructive tests of F907 local original-probe storage allowlist."""
import importlib.util
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "f907_archiver_under_test",
    ROOT / "scripts/archive-recent-probe-objects-f907.py",
)
ARCHIVER = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = ARCHIVER
SPEC.loader.exec_module(ARCHIVER)


class TestArchiveAllowlist(unittest.TestCase):
    def test_allows_only_regenerable_binary_source_probes(self):
        for filename in (
            ".analysis/f650-real-source/sample.obj",
            ".analysis/f900-archive-grouped-locals/used.pdb",
            ".analysis/f906-fighter-first-gpr/real-research.obj",
            ".analysis/f750-foo/nested/real.obj",
        ):
            with self.subTest(filename=filename):
                self.assertTrue(ARCHIVER.eligible_relative(filename, "binaries"))

    def test_protects_original_source_current_coff_and_accepted_build(self):
        for filename in (
            ".analysis/f901-fighter-31b/Boss005214B0-F901-whole.obj",
            ".analysis/f901-fighter-31b/Boss005214B0-F901-whole.pdb",
            ".analysis/f649-original/probe.obj",
            ".analysis/f907-future/probe.obj",
            ".analysis/vc71-wine/drive_c/something.obj",
            ".analysis/cache-archives/prior.obj",
            ".analysis/h184-handoff/protected.obj",
            ".analysis/f906-fighter-first-gpr/verified-summary.json",
            ".analysis/f901-fighter-31b/Boss005214B0-F901-whole.cpp",
            "build/matching/original.obj",
            "resources/th075.exe",
            ".analysis/f900-stuff/../../resources/th075.exe",
            "/tmp/foo.obj",
        ):
            with self.subTest(filename=filename):
                self.assertFalse(ARCHIVER.eligible_relative(filename, "binaries"))

    def test_rejects_unknown_family_and_path_traversal(self):
        self.assertFalse(ARCHIVER.eligible_relative(
            ".analysis/f800-test/used.obj", "pdb"))
        self.assertFalse(ARCHIVER.eligible_relative(
            ".analysis/f800-test/../../build/matching/code.obj", "binaries"))
        self.assertFalse(ARCHIVER.eligible_relative(
            ".analysis/f800-test/real.obj/../../cache/pdb.obj", "binaries"))


if __name__ == "__main__":
    unittest.main()
