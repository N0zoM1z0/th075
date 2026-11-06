# F1183 — Reimu 60KB parent: eleven actual falling/recovery states

**Historical F1183 source checkpoint:** F1185 now clears the 623 GPR
differences below through genuine additional earlier states; see
[the current command-state proof](REIMU_COMMAND_STATES_F1185.md).
F1184 previously extended the same
tracked parent to 21,723B/5,881 x86 and 72 nondefault markers;
[current source/CFG proof](REIMU_EARLY_RECOVERY_STATES_F1184.md).
The dimensions, hashes and old/new prefix comparison below describe commit
`9d2c157b`, before those additional earlier states changed the compiler frame.

The live normal C++ research parent for the independently R063-authored
original `0045DD70` is now
`probes/FighterWhole0045DD70F1183.cpp`, continued from the existing local
F652 D1/D2 parent. It includes `ReimuFallingStatesF1183.inc` for the newly
reconstructed `0x12C..0x136` states. The old F652 source and prior local
research are retained. This parent is **substantially incomplete and NONEXACT**;
none of the new switch interiors is an independently callable exact unit.

## Original extent, source extension and native checks

The original complete callable remains **60,999 CODE bytes /16,837 x86**,
with **1,090 owned after-RET DATA bytes**, six indexed jumps, 142 dense
DWORD entries and 522 sparse bytes. The original SHA256 and complete
boundaries are independently checked through the existing dispatch manifest
and `report-fighter-action-handlers.py`; see
[the original native layout](REIMU_ACTION_BOSS_DISPATCH.md).

| State | Original complete interior CODE | Native x86 | Physical external fields |
| --- | ---: | ---: | ---: |
| `12C` | 207 | 59 | 6 |
| `12D` | 219 | 61 | 6 |
| `12E` | 428 | 122 | 12 |
| `12F` | 339 | 102 | 9 |
| `130` | 421 | 118 | 10 |
| `131` | 386 | 111 | 8 |
| `132` | 202 | 58 | 5 |
| `133` | 342 | 91 | 8 |
| `134` | 207 | 59 | 6 |
| `135` | 487 | 138 | 12 |
| `136` | 291 | 82 | 9 |
| **New source-backed interiors** | **3,529** | **1,001** | **91** |

A fresh affected-parent compilation verifies all 1,001 original mnemonic
and instruction-width positions and all 91 actual PE destinations. Every
direct conditional/return edge in these eleven complete native intervals
reaches the same handler-relative instruction or real function epilogue.
Scalar operands, memory displacements and x87 operand identities agree
when register identity and stack displacement are diagnosed separately.
All 142 live COFF dense-label identities and all 522 sparse DATA bytes
remain correct. No comparison is cropped to hide a difficult case tail.

The prior candidate emitted **15,918 CODE bytes /4,203 x86**. The extended
candidate emits **19,282 /5,182**, plus the same 1,090-byte table area.
The difference is smaller than the new original interiors because eleven
old marker-store/exit pairs were removed. A separate old/new object review
preserves all **53 previously real handler intervals before 12C**: their
mnemonics, GPR roles, widths, stack operands, nonbranch operands and actual
handler-relative branch destinations remain unchanged.

## Reimu behavior is independently observed

The three simple recovery siblings reuse the existing F653 source body
with Reimu-specific stage/animation values: 12C uses stage 3 /animation
0x1B, 12D uses stage 2 /animation 0x1C and clears +0xF00, and 134 uses
stage 4 /animation 0x1C. They are not copied with another fighter's policy.

The new bodies retain the unsigned +0x4E8 threshold in 12E, its early
stage-3 return, effect **0x325** with signed-facing X offset **170** and
Y subtraction, the 12F repeated preparation cadence, stage-limited landing
in 130, and effect **0x328** with X offset **145** and Y constant
`006590A4` in 131. The 131 argument uses an actual lvalue borrow to
preserve original FLD(member)/FADD(global) order; the unborrowed expression
reverses those operands and is rejected.

Original **004639D2..00463A2C** in state 135 genuinely checks stage 3/frame 0
and then stage 5/frame 0 before its limited repeat. Both JNE edges bypass
the repeat. The source retains this apparently contradictory native path;
it is target behavior, not an invented register seed or padding condition.
The 136 branch keeps its separate later brake constant and stage-4 speed
15 /animation 0x1D transition.

## Honest remaining debt and reproduction

These new interiors still contain **623 wrong GPR positions**, and native
stack operands remain wrong. The current source frame is **0x24**, with
saved-this **EBP-8**, versus original **0x380 /EBP-0x34**. Source-local
integer-to-float scratch slots also differ. There are still **79 nondefault
marker statements** in the parent, plus its old default marker and incomplete
native common tail. The original full callable is nowhere near accepted exact.
All pending original bytes remain in the conservative denominator.

Build only this affected parent, serially and headlessly:

    env -u DISPLAY -u WAYLAND_DISPLAY \
      WINEDLLOVERRIDES='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d' \
      WINEPREFIX="$PWD/.analysis/vc71-wine" \
      scripts/compile-probe.sh probes/FighterWhole0045DD70F1183.cpp \
      .analysis/f1183-reimu-whole/recovered-borrowed-y.obj \
      /Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes

Original whole-function/native-handler receipts, both cold objects,
per-state disassembly, full field/CFG comparisons and the prefix-preservation
receipt are retained in ignored `.analysis/f1183-reimu-whole/`. The local
`native.py`, `compare.py` and `preserve-prefix.py` scripts reproduce that
research using `scripts/repo-python`; they are diagnostic evidence, not
canonical acceptance or additions to the test suite.

Canonical exact coverage remains **982 whole functions /871,649 CODE
bytes**, 44.16% reviewed and 44.09% conservative. No accepted source,
match unit, origin decision or comparison infrastructure changed; no full
CI, corpus cold replay or historical origin-test run was required.
