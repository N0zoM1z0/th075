# F555 — full 77-byte Shift-JIS lead-byte classifier, exact cold C++ source

**Native target:** user-supplied Japanese TH075 v1.11 PE, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original complete function begins `0041CA30` and ends exclusively
`0041CA7D`: **77 entire CODE bytes / 28 native x86 instructions**;
original SHA256 `ced8af85dcbe5d3260f506a47ab810905d7d2d7fb9cb9d9ca1f623bb4c020655`.
It ends `RET 4`, takes a true stack byte argument and has no external PE
references: **zero physical COFF relocations**.

## Real bytes and new interpretation of the old R183 ambiguity

Its C++ implementation is a Shift-JIS lead-byte policy, returning `true`
for 0x81–0x9F and 0xE0–0xFE and `false` otherwise. The compiler-generated
`MOVZX`, four `CMP` boundaries at 0x81/0xA0/0xE0/0xFF, signed branches,
AL-return values and `RET 4` all match the entire original, without
pasted assembly, opaque byte constants or linker patching.

Crucially, the **only original PE caller** is original
`FontSurface::DecodePackedTextUnitAt0041C9D0` (85 full CODE, cold exact in
F293). This actual parent calls `0041CA30` at `0041C9E0`, with the
existing accepted parent's **genuine physical REL32** COFF relocation at
+17. Its original behavior is to decide between one- and two-byte text
units and keep correct signed-char and 16-bit codepoint extraction.

Historical R183 correctly compared two naturally equivalent VC7.1
source forms: an ordinary function taking a receiver pointer and a member
function taking `this`. It therefore retained this 77-byte function as
**origin unknown** in that older snapshot. F555 does not pretend to solve
that indistinguishable source-name question; we independently reassessed
the **game-local byte-policy authorship**, using the exact native game font
parent, sole original call edge, and the fact that this helper uses
hand-coded fixed Shift-JIS intervals rather than the compiler/CRT SDK
`_ismbblead` macro's external `__mbctype` table access. This supports
**inferred authored** game font policy, not proven original class-name or
exclusive vendor-source provenance. The old frozen R183 files and tests
remain unmodified; the active owner attribution is explicitly provisional.

## Source and strict local exactness

`src/FontLeadByteF555.cpp` is a normal native VC7.1 C++ member declaration
using only the borrowed `PackedFontUnitF293` interface already defined by
the 85-byte exact caller. The original member identity and complete class
layout are **not** asserted. Its standalone compile used
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src`. Original-to-object comparison
reported **77/77** bytes and **zero** relocation fields. Only the new
unit was rebuilt and accepted via:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/replay-exact-units.py --unit font-surface-shift-jis-lead-byte-0041ca30
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/update-progress.py --check
```

Cold replay returned **1/1 full-function exact**. This grants precisely
**77 original authored CODE bytes**, no external data, CRT/SDK CODE,
partial function coverage, all-unit cold replay or external Oracle receipt.
The live function and origin rows, matching-unit manifest, SHA-pinned source,
exact-adoptions checkpoint and status card are synchronized. The 22 separate
fighter megabosses remain nonexact and untouched by this targeted replay.
