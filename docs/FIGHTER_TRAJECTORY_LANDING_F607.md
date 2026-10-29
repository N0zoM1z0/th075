# F607 — full original action0x49 native landing in nine giant fighter controllers

**Pinned Japanese TH075 1.11 original PE vs newly compiled natural VC7.1
C++ CODE/COFF evidence, not accepted whole-function exactness.** The real
target SHA256 remains
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
F605/F606 restored 0x47 and 0x48 in all eleven unfinished fighter
controllers. F607 extends the *same* nine non-projectile-spawning giant
C++ `Advance()` functions to the next actual second packed-switch native
case `0x49` while retaining all previous 26 real source cases and their
separately owned original jump DATA.

## Original native 99-instruction action versus the natural C++ expression

Read the physical sparse second switch map: `0x49` indexes dense jump
slot **14** and `0x4A` indexes slot **15**, bounding the entire real
case CODE, not a convenient cut-out. In eight original fighters the
complete action0x49 is **99 instructions /350 bytes**, with fifteen
original call/typed-float fields. One original `00564BE0` uses a
much wider `EBP−0x88` receiver stack frame: **441 bytes** for the same
99 instructions. The difference is native **29 widened 32-bit saved-this
receiver `MOV` loads (29×3 bytes) plus one widened local conditional
branch (4 bytes)**; no made-up stack padding was added.

The native behavior begins with stage/frame-zero movement initialization,
real `FLD/FCHS/FSTP` negation of `+0x94`, a **raw DWORD MOV** from
`+0x98` to `+0x54`, drag of 0.8f and counter `+0x7C` clear. On
contact it invokes two independent native x87 float→short conversion
paths through genuine CRT `__ftol2` (`006406AC`), stores adjacent signed
shorts at original `+0xF00` or unique `005AEEC0` `+0xEFC`, and calls
original game helpers to restore/transition trajectory. On noncontact
frame completion, it dispatches the actual *stage minus one* auxiliary
state; a separate stage-one/frame-zero branch checks the two real float
fields `+0x54` and `+0x50` against original global `0065782C` using
two distinct `FLD/FLD/FUCOMPP/FNSTSW/TEST AH,0x44` sequences, then
sends auxiliary action 3 or 2.

In the first candidate, ordinary C++ already emitted 99 original-style
instructions but only **347 bytes**, swapped the second `FLD`
operands and incorrectly jumped into the other auxiliary branch
instead of leaving the enclosing original switch. A bounded original
VC7.1 experiment with ordinary (no ASM, no fake register) C++ showed:

```cpp
if (*(&POS) == g_ThresholdAt0065782C) {
    SetAuxActionAt40FB40(3);
    break;
} else {
    SetAuxActionAt40FB40(2);
    break;
}
```

The genuine left-hand-side lvalue recovers the real original
`FLD global; FLD member; FUCOMPP` order. Separate `break`s recover
the true **350-byte /99-instruction** source case and both real
outer-switch exit jumps. First-class typed source
[`FighterTrajectoryLanding49F607.inc`](../probes/FighterTrajectoryLanding49F607.inc)
retains the original native condition `POS54 != original global` and
the exact 0/1/2/3 stage semantics without raw instruction grafts.

## Native PE relocation and full-prior-case proof

[`verify-fighter-trajectory-landing-f607.py`](../scripts/verify-fighter-trajectory-landing-f607.py)
first independently decodes each original 0x49/0x4A actual dense
DWORD boundary, 99 authentic x86 instructions, physical x87 statuses,
source constants and 15 original typed/zero-addend PE/COFF fields.
The two original `FLD` operations at ordinals 77 and 84 have source
unlinked `dword ptr [0]` operands, so they are only normalized
**after** checking their individual real `DIR32` source COFF symbol,
physical instruction position, and original target `0065782C`.
The other 13 real typed PE field destinations are checked in the same
way. All remaining native GPR/x87/CFG role operands and instruction
widths must match, not merely the instruction count.

Each selected giant is **cold source-compiled** under pinned ordinary
MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. The selected new object
also independently rechecks every previously reconstructed original
case0..10, 0x32, 0x33–0x41, 0x46, 0x47 and 0x48 plus the complete
physical after-RET switch DATA geometry via prior strict source
verifiers. There is no reuse of earlier COFF results for acceptance.

| Still-nonexact enclosing original giant | New entire real 0x49 CODE | Native x86 | Typed original COFF |
| --- | ---: | ---: | ---: |
| `005D73C0` | 350 B | 99 | 15 |
| `00486550` | 350 B | 99 | 15 |
| `004AC040` | 350 B | 99 | 15 |
| `00543210` | 350 B | 99 | 15 |
| `00564BE0` | **441 B** | 99 | 15 |
| `004D7E70` | 350 B | 99 | 15 |
| `004F7130` | 350 B | 99 | 15 |
| `005AEEC0` | 350 B | 99 | 15 |
| `005214B0` | 350 B | 99 | 15 |
| **F607 nine case subranges** | **3,241 B** | **891** | **135** |

Two original actors, `0045DD70` and `0058AF60`, have a different
**118-instruction /420-byte** action0x49 because original
stage-one once-only projectile generation occurs after their early
frame check. They are deliberately **not** called exact by this
99-instruction source; separate native source is still required.

These nine new case bodies bring the previous F598–F606 studied
inner source count **286 → 295 original case interiors** and
**66,880 → 70,121 source-backed internal native CODE bytes**.
**ZERO of these inner cases are independent complete functions, ZERO
new whole-giant exact CODE is accepted**. The official authored
whole-function ledger stays at 943 exact functions/862,726 bytes.
All later native `0x4A` actions and the full containing huge source
remain unfinished; no all-unit cold replay or external Oracle receipt.

## Rebuild only the selected affected giant C++ TU

```bash
scripts/repo-python scripts/verify-fighter-trajectory-landing-f607.py --boss 0x004F7130
scripts/repo-python scripts/verify-fighter-trajectory-landing-f607.py --boss 0x00564BE0
# Optional only nine newly affected whole-giant source TUs:
scripts/repo-python scripts/verify-fighter-trajectory-landing-f607.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Compiled original-backed C++ sources, COFF/PDBs, native x86 and field
receipts are preserved in ignored `.analysis/f607-fighter-landing-source/`.
Bounded positive/negative source expression trials are under
`.analysis/f607-landing/variants/`.
