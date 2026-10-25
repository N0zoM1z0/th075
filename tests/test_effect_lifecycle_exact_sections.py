"""Reject incomplete EH evidence even when a main function still matches."""
import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "effect_lifecycle_exact", ROOT / "scripts/verify-effect-lifecycle-exact.py")
VERIFY = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VERIFY)
PLAN_SHA256 = "fed9959345e8d697eff2d315e3eceaa078a97c2bd148ed671a67add34f6ae872"


def fixture():
    def definition(name, offset=0):
        return dict(symbol=name, offset=offset, type=32, storage=3)
    main = definition("main")
    cleanup = definition("cleanup")
    handler = definition("handler", 3)
    info = definition("info")
    call = dict(offset=1, type="REL32", symbol="handler", addend=0)
    unwind = dict(offset=0, type="DIR32", symbol="cleanup", addend=0)
    sections = {
        1: dict(name=".text", flags=0x20, raw=b"\xe8\0\0\0\0",
                definitions=[main], relocations=[call]),
        2: dict(name=".text$x", flags=0x20, raw=b"\x90\x90\x90\xc3",
                definitions=[cleanup, handler], relocations=[]),
        3: dict(name=".xdata$x", flags=0x40, raw=bytes(4),
                definitions=[info], relocations=[unwind]),
        4: dict(name=".sxdata", flags=0x40, raw=struct.pack("<I", 1),
                definitions=[], relocations=[]),
    }
    targets = {0x1000: b"\xe8\xfe\x0f\0\0", 0x2000: b"\x90\x90\x90\xc3",
               0x3000: struct.pack("<I", 0x2000)}
    parts = []
    for number, address, anchor in ((1, 0x1000, main), (2, 0x2000, handler), (3, 0x3000, info)):
        section = sections[number]
        fields = [dict(f, target=0x2003 if number == 1 else 0x2000)
                  for f in section["relocations"]]
        parts.append(dict(symbol=anchor["symbol"], symbol_offset=anchor["offset"],
                          address=address, size=len(section["raw"]), name=section["name"],
                          flags=section["flags"], definitions=copy.deepcopy(section["definitions"]),
                          relocations=fields, kind="authored" if number == 1 else "compiler-code",
                          target_sha256=hashlib.sha256(targets[address]).hexdigest()))
    symbols = {1: dict(handler, section=2), 2: dict(main, section=1)}
    return sections, symbols, dict(sections=parts, safe_handlers=["handler"]), targets


class EffectLifecycleExactSectionsTests(unittest.TestCase):
    def verify(self, sections, symbols, plan, targets):
        return VERIFY.verify_sections(sections, symbols, plan, lambda a, n: targets[a][:n])

    def test_complete_graph_accepts_both_nonzero_handler_and_unwind_root(self):
        self.assertEqual(len(self.verify(*fixture())), 3)

    def test_changed_exception_body_fails_with_identical_main_body(self):
        sections, symbols, plan, targets = fixture()
        sections[2]["raw"] = b"\xcc\x90\x90\xc3"
        with self.assertRaisesRegex(ValueError, "byte mismatch"):
            self.verify(sections, symbols, plan, targets)

    def test_appended_exception_or_metadata_bytes_cannot_be_cropped(self):
        for number in (2, 3):
            with self.subTest(section=number):
                sections, symbols, plan, targets = fixture()
                sections[number]["raw"] += b"\0"
                with self.assertRaisesRegex(ValueError, "extent/definitions"):
                    self.verify(sections, symbols, plan, targets)

    def test_shifted_local_handler_cannot_keep_old_absolute_binding(self):
        sections, symbols, plan, targets = fixture()
        sections[2]["definitions"][1]["offset"] = 2
        plan["sections"][1]["definitions"][1]["offset"] = 2
        plan["sections"][1]["symbol_offset"] = 2
        symbols[1]["offset"] = 2
        with self.assertRaisesRegex(ValueError, "local destination"):
            self.verify(sections, symbols, plan, targets)

    def test_missing_real_unwind_relocation_fails(self):
        sections, symbols, plan, targets = fixture()
        sections[3]["relocations"] = []
        with self.assertRaisesRegex(ValueError, "relocation fields"):
            self.verify(sections, symbols, plan, targets)

    def test_safeseh_indices_must_identify_actual_registered_handler(self):
        sections, symbols, plan, targets = fixture()
        sections[4]["raw"] = struct.pack("<I", 2)
        with self.assertRaisesRegex(ValueError, "SafeSEH roots"):
            self.verify(sections, symbols, plan, targets)

    def test_unlisted_owned_section_is_rejected(self):
        sections, symbols, plan, targets = fixture()
        sections[5] = dict(name=".xdata$x", flags=0x40, raw=b"\0",
                           definitions=[], relocations=[])
        with self.assertRaisesRegex(ValueError, "unverified.*section"):
            self.verify(sections, symbols, plan, targets)

    def test_changed_metadata_relocation_destination_fails(self):
        sections, symbols, plan, targets = fixture()
        plan["sections"][2]["relocations"][0]["target"] += 1
        with self.assertRaisesRegex(ValueError, "local destination"):
            self.verify(sections, symbols, plan, targets)

    def test_frozen_production_scope_inputs_and_independent_origins(self):
        path = ROOT / "config/effect-lifecycle-exact-sections.json"
        self.assertEqual(hashlib.sha256(path.read_bytes()).hexdigest(), PLAN_SHA256)
        plan = json.loads(path.read_text())
        self.assertEqual(plan["schema_version"], 1)
        self.assertEqual(len(plan["sections"]), 24)
        authored = [p for p in plan["sections"] if p["kind"] == "authored"]
        self.assertEqual({p["address"]: p["size"] for p in authored},
                         {0x45B920: 131, 0x45B9B0: 85, 0x45BA10: 21})
        self.assertEqual(sum(p["size"] for p in plan["sections"] if p["kind"] == "metadata"), 72)
        self.assertEqual(sum(p["size"] for p in plan["sections"] if p["kind"] == "compiler-code"), 64)
        self.assertEqual(sum(len(p["relocations"]) for p in plan["sections"]), 46)
        self.assertEqual(len(plan["safe_handlers"]), 2)
        for name, digest in {**plan["inputs"], **plan["origin_evidence"]}.items():
            self.assertEqual(hashlib.sha256((ROOT / name).read_bytes()).hexdigest(), digest, name)
        for part in authored:
            self.assertEqual(part["native_origin"]["origin"], "authored")
        self.assertEqual({p["native_origin"]["evidence_id"] for p in authored}, {"R166", "R241", "R244"})


if __name__ == "__main__":
    unittest.main()
