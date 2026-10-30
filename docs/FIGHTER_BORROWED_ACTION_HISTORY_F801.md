# F801 — True fighter action-history array and opponent-pointer typed views in entire 58KB boss

**Full original Japanese TH075 v1.11 PE-backed compiler comparison;
not a whole-function exactness claim.** The original authored
`0x00543210` fighter is 58,294 callable CODE B /16,471 x86
and owns 943 independently accounted post-RET packed switch
DATA B. The currently best ordinary VC7.1 full source
emits 58,293 callable B and 16,471 x86, including all
current original source actions and real F781 four-entry
shared getter. Native case `0x63` at
`00545ADE..00545DA0` is 706 original CODE B,
189 x86, 15 authentic PE/COFF relocation fields;
current source still emits 705 B with x86 GPR role/width
differences.

## Real original fields independently observed

The native PE instruction sequence, not a guessed
historical C++ class, proves that action `0x63`
dereferences:
- `this+0x2E8` as a pointer to an opponent/owner,
  whose signed short stage is at `+0x60`.
- Signed actor index byte `this+0x39D`.
- Signed actor history bytes beginning at
  `this+0x32A`, indexed by the signed byte above.
- The physically distinct signed short actor stage
  at `this+0x62` and action transitions to
  actual `0040FAC0`.

F801 tests **eight meaningful natural C++ borrowed
layout hypotheses** for these real fields: old raw
control, typed history array, typed index byte,
combined history/index, typed opponent-pointer
chain, opponent-plus-history, all borrowed views
simultaneously, and a true reference-lvalue
reading of the history entry. The types contain
only observed offsets and are **never instantiated
or embedded** as complete historical classes.

## Fresh whole-parent physical comparison

Each separate source is built with pinned normal VC7.1
under `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` as
an **entire affected 58KB C++ parent**. Remarkably,
all eight *complete* 59,236-byte generated COFF
function sections (58,293 callable CODE +943 after-RET
DATA) are **byte-identical**. All 1,863 physical
COFF relocation shapes are also identical: each
offset, kind, source addend, original external
symbol/target identity and relative internal label
offset. Independent PE physical original
`0x63` verification checks all **15 original
typed call/global field destinations**, not just
relocation-masked source bytes.

The actual native original mode-63 CMP instructions
still differ:

| Native x86 ordinal | Original target | Current source, all eight variants |
| --- | --- | --- |
| 18 | `CMP EDX,0x96` (6B) | `CMP EAX,0x96` (5B) |
| 61 | `CMP EAX,0x96` (5B) | `CMP ECX,0x96` (6B) |
| 84 | `CMP EDX,0x96` (6B) | `CMP EAX,0x96` (5B) |

Their net 1-B signed-width difference is **not**
proof of a near-exact function: many other real
GPR operand bytes in 0x63 and earlier 0x59/0x60/0x61
remain nonnative. Baseline additionally verifies
original early action physical relocation targets,
the complete **46-B F781 shared getter suffix**,
and all 943 original post-RET DATA bytes including
156 true DIR32 switch labels and 319 independent
index bytes. The source C++ does not patch
register encodings or add fake locals.

Reproduce *only* these affected whole parent variants:

```bash
scripts/repo-python scripts/verify-fighter-native-borrowed-action-f801.py
```

Results and regenerated entire source/COFF objects
are stored locally in the ignored
`.analysis/f801-fighter-borrowed-action/`.
This result eliminates a new real layout hypothesis
while preserving the unresolved original game boss.
**Zero new accepted authored whole-function CODE and
no full 979-unit cold replay.**
