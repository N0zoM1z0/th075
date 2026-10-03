"""Reject untyped lookalikes and unrooted short-body origin claims."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "deque_game_dependencies", ROOT / "scripts/verify-deque-game-dependency-origins.py")
DEPENDENCIES = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(DEPENDENCIES)


class TypedDependencyTests(unittest.TestCase):
    def setUp(self):
        self.manifest = json.loads((ROOT / "config/deque-game-dependency-origin-evidence.json").read_text())

    def test_postfix_decrement_shape_cannot_replace_increment(self):
        altered = copy.deepcopy(self.manifest)
        for node in altered["nodes"]:
            node["coff_symbol"] = node["coff_symbol"].replace("??Eiterator@", "??Fiterator@")
            for call in node["relocation_bindings"]:
                call["symbol"] = call["symbol"].replace("??Eiterator@", "??Fiterator@")
        with self.assertRaisesRegex(ValueError, "postfix increment"):
            DEPENDENCIES.verify_graph(altered)

    def test_same_short_shape_cannot_redirect_to_a_game_constructor(self):
        node = next(n for n in self.manifest["nodes"] if n["address"] == "0x004453C0")
        node["relocation_bindings"][0]["target_address"] = "0x0041A2D0"
        with self.assertRaisesRegex(ValueError, "source-typed callee"):
            DEPENDENCIES.verify_graph(self.manifest)

    def test_tiny_getter_needs_the_exact_typed_parent_call(self):
        parent = next(n for n in self.manifest["nodes"] if n["address"] == "0x005F7D80")
        parent["relocation_bindings"][0]["symbol"] = "Game::UnrelatedGetter"
        with self.assertRaisesRegex(ValueError, "source-typed callee"):
            DEPENDENCIES.verify_graph(self.manifest)

    def test_unchecked_access_cannot_replace_the_actual_at_callee(self):
        parent = next(n for n in self.manifest["nodes"] if n["address"] == "0x005F7D80")
        call = parent["relocation_bindings"][1]
        call["symbol"] = call["symbol"].replace("?at@?$deque@", "??A?$deque@")
        with self.assertRaisesRegex(ValueError, "source-typed callee"):
            DEPENDENCIES.verify_graph(self.manifest)

    def test_byte_equal_short_body_without_parent_is_not_accepted(self):
        parent = next(n for n in self.manifest["nodes"] if n["address"] == "0x005F7D80")
        # Keep counts and a valid typed edge, but disconnect size() entirely.
        parent["relocation_bindings"][0].update({
            "target_address": parent["relocation_bindings"][2]["target_address"],
            "symbol": parent["relocation_bindings"][2]["symbol"]})
        with self.assertRaisesRegex(ValueError, "independent source-typed game parent"):
            DEPENDENCIES.verify_graph(self.manifest)

    def test_probe_does_not_earn_game_source_or_exact_credit(self):
        node = next(n for n in self.manifest["nodes"] if n["address"] == "0x005F8110")
        function = {"size": "17", "span_end": node["span_end"], "owner": "library",
                    "status": "matching", "source_file": "src/Invented.cpp", "match_percent": "100.00"}
        origin = {"origin": "library", "disposition": "exclude", "evidence_id": "R110"}
        with self.assertRaisesRegex(ValueError, "incorrect origin/source/exact credit"):
            DEPENDENCIES.check_ledger(node, {node["address"]: function}, {node["address"]: origin}, False)


if __name__ == "__main__":
    unittest.main()
