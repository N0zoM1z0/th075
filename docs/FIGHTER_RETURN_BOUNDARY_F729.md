# F729 — two full original 1F6/1F7 fighter boundary-return actions

**Original-native meaningful C++ source reconstruction, still whole-function NONEXACT.**
The pinned original Japanese TH075 v1.11 `resources/th075.exe` has SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The enclosing authored `00543210` has 58,294 original CODE B and 943
independently owned after-RET switch DATA bytes; internal action interiors
are **not** separate authored complete game functions.

## Entire physical original case source

| Actual native handler | Original PE boundaries | Native complete original | Full-parent normal VC7.1 source | Typed physical PE/COFF |
| --- | --- | --- | --- | --- |
| `0x1F6` | `0054AB00`–`0054AF9D` | **1,181 B /348 x86** | **1,183 B /350 x86** | **35/35** |
| `0x1F7` | `0054AF9D`–`0054B43A` | **1,181 B /348 x86** | **1,183 B /350 x86** | **35/35** |
| Total original source newly represented | | **2,362 original CODE B /696 x86** | **2,366 emitted B /700 x86** | **70/70** |

The tracked natural C++ [`FighterBoundaryReturnF729.inc`](../probes/FighterBoundaryReturnF729.inc)
is instantiated twice using distinct genuine stage-14 horizontal/vertical
velocity and stage-15 projectile identities (0x336/0x337). It restores
the complete native stage-zero reset, state flags, downward Y collision,
real stage 10–13 contact and facing repair, four independent physical X
boundary comparisons, stage-14/15 status-dependent action transition to
0x1FA, collision and speed reduction, late horizontal drag,
completion-state callback, real stage-three reversed-direction 0x7D and
0x7E projectiles, original stage 14/15/18/11 motion/shot/action logic.
Nothing is an invented stack filler or an instruction-byte graft.

## Native C++ comparator evidence and still-open x87 codegen

Original x86 ordinal 107 is `TEST AH,5` followed at 108 by `JP`, for
both genuine native handlers. Initially, C++ `X>=sideEdge` emitted
`TEST AH,1; JNE`, which is **not the same native floating predicate**.
F729 compiled **nine complete original-shaped giant source alternatives**
using strict, nonstrict, negated and reversed real side-edge tests and
natural source comparator argument order. The **strict `<`** form
recovers the actual original `TEST AH,5; JP`. The selected source
uses that evidence-backed test.

Two subsequent genuine native `FCOMP dword ptr [this+0x44]` operations
at original x86 ordinals **127 and 139** still compile as
`FLD dword ptr [this+0x44]` plus `FCOMPP`. Thus each entire case
has **two additional x86 instructions and two extra CODE bytes**.
The complete original physical ordered relocation list remains
identical in **type, original PE target, matching source symbol,
zero addend and true owning mnemonic**: native ordinals before 127
retain their index; ordinals 127–138 shift +1 and 139 onward +2
in the actual compiled code. Every one of the **35 fields in each
case** is explicitly checked against that real x87 shift, with the
two overloads of `00453C80` independently identified as original
`SpawnAt453C80` and `SpawnMixedAt453C80`. No field is silently
reclassified as exact machine CODE.

The native real signed-direction×80 `MOV/FILD` scratch uses
`EBP−0xF8` for 1F6 and `EBP−0xFC` for 1F7; the actual compiled
source uses `−0x6C` and `−0x70`, respectively. Full-parent
normalization excluding only physically typed original float globals
still finds **286/285 real nonfield GPR/x87/CFG operand discrepancies**.
The original saved receiver is `EBP−0x44` while the generated source
receiver remains `−0x28`. Neither case nor the whole original
fighter is byte-exact; NaN/unordered behavior around the two remaining
`FCOMP` operations also requires further original-source recovery.

## Current compiler context and independently owned switch data

[`scripts/verify-fighter-return-boundary-f729.py`](../scripts/verify-fighter-return-boundary-f729.py)
rebuilds **one entire original-shaped 58KB VC7.1 parent**, inserts both
meaningful case interiors in the correct physical `1F4→1F5→1F6→1F7→1F8`
order, rereads the two native complete bounded originals, and checks
all 70 physically typed native targets and the exact x87 opcode edit
blocks. It rechecks prior 1F4/1F5 physical float globals and the
actual **upstream register-phase regression** already documented in
F728: original full 0x200 has **67** and 0x201 **85** nonfield GPR
operand differences in this NEW compiler parent; 0x2EF remains strict
with **zero**. The old F724 27-strict-case count is **not** inherited.

The same new compiled parent independently proves the complete
**943-byte original after-RET switch DATA**, including all **156**
physical `DIR32` fields targeting authentic original and current
source instruction starts and **319/319 byte-identical original
sparse-map bytes**. Neither the 943 DATA nor these internal cases
are accepted as new whole game CODE.

The F728 earlier verifier accepts an optional independently verified
real following 1F6 instead of requiring its older source placeholder,
while retaining the old default test behavior.

```bash
scripts/repo-python scripts/verify-fighter-return-boundary-f729.py
scripts/repo-python scripts/verify-fighter-random-arcs-f728.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Private full source/OBJ/PDB, compiler logs, nine original comparator
alternatives and detailed PE/COFF comparison receipts are retained
under ignored `.analysis/f729-fighter-return-boundary/`. The tracked
normal source and portable one-parent native verifier are reproducible.
**No original EXE edit, no artificial machine padding, no credited
whole-game function exact CODE and no all-943-unit cold replay.**
The formal authored exact ledger remains **943 whole functions and
862,726 original CODE B (43.71% reviewed)**.
