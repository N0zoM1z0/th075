"""Unused stack arguments still distinguish whole x86 method contracts."""
import importlib.util
from pathlib import Path
import unittest

from capstone import Cs, CS_ARCH_X86, CS_MODE_32


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "effect_forwarder_abi", ROOT / "scripts/verify-effect-forwarder-origins.py")
VERIFIER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VERIFIER)


def decode(code):
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    return list(decoder.disasm(bytes.fromhex(code), 0x1000))


class EffectForwarderAbiTests(unittest.TestCase):
    def test_unused_argument_keeps_different_cleanup(self):
        five = decode("c21400")
        six = decode("c21800")
        VERIFIER.check_return(five, 20)
        VERIFIER.check_return(six, 24)
        with self.assertRaises(ValueError):
            VERIFIER.check_return(five, 24)
        with self.assertRaises(ValueError):
            VERIFIER.check_return(six, 20)

    def test_plain_ret_cannot_claim_method_argument_cleanup(self):
        with self.assertRaises(ValueError):
            VERIFIER.check_return(decode("c3"), 20)

    def test_earlier_ret_cannot_hide_an_unreviewed_tail(self):
        with self.assertRaises(ValueError):
            VERIFIER.check_return(decode("c2140090"), 20)


if __name__ == "__main__":
    unittest.main()
