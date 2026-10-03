"""Whole erase graphs must preserve source types, both paths and prior ownership."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "deque_erase", ROOT / "scripts/verify-vendor-deque-erase-origins.py")
ERASE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(ERASE)


class EraseGraphTests(unittest.TestCase):
    def setUp(self):
        self.manifest = json.loads((ROOT / "config/vendor-deque-erase-origins.json").read_text())
        self.nodes = {r["address"]: r for r in self.manifest["nodes"]}

    def test_same_method_from_another_specialization_is_not_a_typed_witness(self):
        node = self.nodes["0x0041E380"]
        relocations = copy.deepcopy(node["relocation_bindings"])
        call = relocations[-1]
        call["symbol"] = call["symbol"].replace("?$deque@K", "?$deque@E").replace("?$allocator@K", "?$allocator@E")
        with self.assertRaisesRegex(ValueError, "whole source-typed callee"):
            ERASE.typed_bindings(relocations, node["relocation_bindings"], self.nodes)

    def test_copy_direction_cannot_be_exchanged_for_an_equal_shape(self):
        node = self.nodes["0x0041E380"]
        calls = node["relocation_bindings"]
        forward = next(b for b in calls if b["offset"] == 192)
        backward = next(b for b in calls if b["offset"] == 116)
        backward.update({"symbol": forward["symbol"], "target_address": forward["target_address"]})
        with self.assertRaisesRegex(ValueError, "complete copy/pop paths"):
            ERASE.verify_graph(self.manifest)

    def test_single_erase_cannot_bind_another_ranges_same_source_shape(self):
        wrapper = self.nodes["0x0041DC90"]
        other = self.nodes["0x0041E800"]
        wrapper["relocation_bindings"][1].update({"target_address": other["address"], "symbol": other["coff_symbol"]})
        with self.assertRaisesRegex(ValueError, "addition/range-erase witnesses"):
            ERASE.verify_graph(self.manifest)

    def test_source_probe_does_not_grant_exact_or_source_credit(self):
        node = self.nodes["0x004143D0"]
        function = {"size": "35", "span_end": node["span_end"], "source_file": "src/Invented.cpp", "match_percent": "100.00"}
        with self.assertRaisesRegex(ValueError, "cannot grant source/exact credit"):
            ERASE.check_ledger(node, {node["address"]: function}, {node["address"]: {}}, True)

    def test_independently_reviewed_callee_ownership_is_not_replaceable(self):
        node = next(n for n in self.manifest["nodes"] if n["evidence_role"] == "anchor")
        function = {"size": str(node["size"]), "span_end": node["span_end"], "owner": "authored"}
        origin = {"origin": "authored", "evidence_id": node["origin_evidence"]}
        with self.assertRaisesRegex(ValueError, "independent anchor ownership"):
            ERASE.check_ledger(node, {node["address"]: function}, {node["address"]: origin}, False)


if __name__ == "__main__":
    unittest.main()
