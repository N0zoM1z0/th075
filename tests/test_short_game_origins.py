"""Keep a reviewed callee graph from turning into guessed owner evidence."""
import importlib.util
from pathlib import Path
import unittest

from capstone import Cs, CS_ARCH_X86, CS_MODE_32


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "short_game_edges", ROOT / "scripts/verify-short-game-origins.py")
VERIFIER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VERIFIER)


class ShortGameOriginTests(unittest.TestCase):
    def setUp(self):
        decoder = Cs(CS_ARCH_X86, CS_MODE_32)
        decoder.detail = True
        # Synthetic direct call to 0x2000 and return; no target bytes.
        self.instructions = list(decoder.disasm(bytes.fromhex("e8fb0f0000c3"), 0x1000))
        self.calls = [{"site": "0x00001000", "target": "0x00002000"}]
        self.origins = {"0x00002000": {"origin": "authored"}}

    def test_complete_direct_edge_with_reviewed_owner(self):
        VERIFIER.check_calls(self.instructions, self.calls, self.origins)

    def test_mapped_or_library_callee_cannot_prove_game_owner(self):
        for origin in ("unknown", "library", "compiler"):
            self.origins["0x00002000"]["origin"] = origin
            with self.assertRaises(ValueError):
                VERIFIER.check_calls(self.instructions, self.calls, self.origins)

    def test_actual_call_cannot_be_omitted(self):
        with self.assertRaises(ValueError):
            VERIFIER.check_calls(self.instructions, [], self.origins)

    def test_another_reviewed_function_cannot_replace_the_actual_destination(self):
        self.origins["0x00003000"] = {"origin": "authored"}
        self.calls[0]["target"] = "0x00003000"
        with self.assertRaises(ValueError):
            VERIFIER.check_calls(self.instructions, self.calls, self.origins)


if __name__ == "__main__":
    unittest.main()
