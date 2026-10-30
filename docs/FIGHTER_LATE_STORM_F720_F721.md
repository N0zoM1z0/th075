# F720/F721 — complete native fighter 2DF and 2E5 C++ restores strict 2EF context

**Substantial source reconstruction, still NOT a byte-exact whole original
boss.** Original target is the user's pinned Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original authored `00543210` fighter boss is **58,294 whole CODE
bytes plus 943 independently owned after-RET switch DATA bytes**.
The two cases below are physically bounded *internal handler bodies*;
no case alone is a separately callable whole game function, and no
new whole-function CODE is accepted or credited.

## Original entire native cases and full-parent source

| Native complete original handler | Original physical interval | Original entire CODE/x86 | Source entire CODE/x86 | Original typed PE/COFF refs |
| --- | --- | ---: | ---: | ---: |
| `0x2DF` | `0054EFE7`–`0054F241` | **602 B/169 x86** | **602 B/169 x86** | **18/18** |
| `0x2E5` | `0054F241`–`0054F55F` | **798 B/223 x86** | **798 B/223 x86** | **20/20** |
| **Both true original game cases** | | **1,400 B/392 x86** | **1,400 B/392 x86** | **38/38** |

Tracked ordinary C++ source
[`FighterLateStormF720.inc`](../probes/FighterLateStormF720.inc)
and [`FighterRandomVolleyF721.inc`](../probes/FighterRandomVolleyF721.inc)
retains real, distinct original behavior and typed game member calls.

**2DF** implements its true storm initialization
`00454BC0(3,4,0xFF0000)`, native stage-zero member and velocity
initialization, early descent/ground threshold and three real
position/speed resets on contact, two native kind `0x333` and
`0x387` float-projectile attacks with difficulty gate, late X-speed
slowdown/clamp, original completion counter, real native game
random `100–180` minus difficulty×30, and its native auxiliary
stage-four termination. The source is based on the separately
decoded native `2DF` case, not accepted merely because the nearby
`2DC` looks similar.

**2E5** is a more complicated full **798-B** action and reconstructs:
its native reset and true seven-argument kind `0x38E` projectile
call at `00453B50`; native completion and randomized 60–80 timer;
stage-three action 9; native stage-seven real owner-height equality
and two nested random decisions that assign `+0xF00=0/20`;
x87 cast from actual signed stage count into angle member `+0x314`;
kind `0x386` float projectile with signed facing×65 and native Y
offset; stage-ten `(3 − difficulty)×2` `+0xF02` loop and action 9;
and stage-twelve angle conversion and mutually gated kinds
`0x384/0x388`, followed by original action 10.

Both were compiled with real VC7.1 build 3077 flags
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` in **one complete original-shaped
fighter switch parent**, with **all original 392 x86 mnemonic AND
instruction-width positions identical**, and all **38 real physical
typed PE/COFF fields** matched at their original native x86 owner
ordinals, with verified actual native PE destination, source symbol,
zero addend and `REL32/DIR32` type. No ASM graft, invented stack
variables or clipped partial-case comparison was used.

## Original floating equality and strict inequality source correction

Original physical `2DF` x86 ordinal `128` performs `TEST AH,5`
followed by `JP`, while the older neighboring `2DC` C++ source
used `if (POS <= 0.0f)` and produced `TEST AH,0x41` in the
reconstructed `2DF`. The two original conditions have genuinely
different ordered/unordered and equality behavior; equal-looking
finite-motion code is **not** native codegen proof.

F720 serially compiled **four whole-giant VC7.1 source variants** for
this real comparison: original baseline `<=`, strict `<`, negated
`!(>=)` and native member-lvalue strict `<` grammar. **Strict `<`**
and its genuine lvalue form reproduced the native **`TEST AH,5`**
and `JP`, retaining the complete original **602 B/169 x86/18 fields**
with no GPR role differences. Baseline `<=` still emits the wrong
`TEST AH,0x41` operand, while negated `!(>=)` changes an actual
branch opcode and emits `TEST AH,1`/`JE`. The source now uses the
**native-backed strict `<`**, not a mechanically substituted binary
operand. Compiler sources, objects, PDBs, logs and honest actual
native-test comparison are preserved in Git-ignored
`.analysis/f720-fighter-late-storm/threshold/`.

The original `2E5` stage-seven source equality
`*reinterpret_cast<float*>(OWNER+0x48) == g_ThresholdAt0065782C`
naturally emits the exact original **`FLD [0065782C]; FLD [owner+0x48];
FUCOMPP; FNSTSW AX; TEST AH,0x44`** order. Other cases requiring
extra `FLD/FCOMPP` now remain separately identified as nonexact;
they are **not** hidden by this successful true float equality.

## Honest EBP differences and major *cross-case* positive result

Normal C++ in the new parent has **zero normalized non-PE GPR/CFG
operand differences in either `2DF` or `2E5`**. This does not make
them byte-exact: the real native original `this` owner is
`EBP−0x44`, while source `this` is **`EBP−0x28`**, independently
proved across one compiler prologue store and **3,118 receiver MOV
reloads**. The true original six-byte x87 scratch operands differ:

| Original handler / native x86 ordinals | Original EBP locals | Actual whole-parent C++ EBP locals |
| --- | --- | --- |
| `2DF` 76/77, 100/101 | `−0x1AC`, `−0x1B0` | `−0xCC`, `−0xD0` |
| `2E5` 106/107, 122/123, 165/166, 185/186, 210/211 | `−0x1B4`, `−0x1B8`, `−0x1BC`, `−0x1C0`, `−0x1C4` | `−0xD4`, `−0xD8`, `−0xDC`, `−0xE0`, `−0xE4` |

All **14** of these actual native/source six-byte `MOV/FILD`
integer-to-x87 local accesses are individually checked and never
blanket-normalized into a spurious exact result.

**Cross-case improvement:** in the preceding F718 full-source
context, the original `2EF` (788 B/224 x86/20 typed refs) had
**144 genuine nonfield GPR role mismatches**, reducing the number
of context-strict earlier native action interiors from 27 to 26.
Adding these two actual native C++ bodies naturally changes
VC7.1's register phase and restores **all 224 original `2EF`
normalized GPR/CFG roles**. Its full original instruction widths,
physical fields, true shared exit and independent native receiver
mapping now check strict again: **27 source-context-strict earlier
nonterminal original actions**, exactly as verified in this NEW
parent. This is an **internal case-context finding**, not 788 B
of newly accepted independent whole-function CODE.

The later original `2F0` still has **147 real GPR differences** and
`2F1` still **170**, with native full 1,169/977 B geometry; neither
was silently promoted to strict. Original `2F8`, `2F9`, `2FA`,
`2FB`, `302`, terminal `31B/31C` retain their honestly measured
same-context positives and negatives. The **entire separate
943-byte original after-RET switch DATA** is rechecked in the same
newly compiled parent. The native whole giant remains NONEXACT.

## Reproduce (only the affected giant)

Tracked [`verify-fighter-late-storm-f720-f721.py`](../scripts/verify-fighter-late-storm-f720-f721.py)
reads the actual original PE, reconstructs the entire selected giant
from tracked normal C++, serially cold-compiles one complete
original-shaped giant, verifies full original `2DF/2E5` CFG,
all 38 PE/COFF field owners, original strict float comparisons,
all 14 real EBP scratch operands, previous source-backed
`2DD/2DE`, `2DB/2DC`, `2D0/2D1`, `2BF/2C4`, `259–25D`,
late `2F8–302`, and the restored original strict `2EF` (via
an independently verified source `2E5` next-case boundary).
Its F674/F696/F718 parent context helpers now accept an optional
**physically verified true source neighbor** instead of expecting
older fake source marker cases. Their older independent source
contexts remain verifiable by default; no older strict evidence is
falsely reused in the new compiler frame.

```bash
scripts/repo-python scripts/verify-fighter-late-storm-f720-f721.py
scripts/repo-python scripts/verify-fighter-double-volley-f718.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Generated full parent C++/OBJ/PDB/log and physical native comparison
receipt: Git-ignored `.analysis/f720-fighter-late-storm/`.
Formal whole authored exact ledger is still **943 matched complete
functions /862,726 native CODE bytes (43.71% reviewed)**. No new
complete game function byte-exact acceptance, no target EXE patch,
no synthetic locals and **no all-943-unit cold replay**.
