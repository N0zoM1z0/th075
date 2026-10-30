# F771 — original fighter 2FB X/Y angle operands restore real MOV/FLD order

**Original giant-function source reconstruction, NOT a complete game
function exact match.** The target is original Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The independently authored complete `00543210` is **58,294 native
CODE bytes** with **943 separately owned after-RET switch DATA bytes**.
Its original internal action `0x2FB` at `00550D97..0055101E` is
**647 complete native CODE bytes, 181 original x86 instructions and
17 genuine physically typed PE/COFF fields**. This inner action is
not independently callable, so gains **zero new exact game CODE**.

## Wrong source expression ordering, not just byte formatting

Earlier F696 game source already had the actual stage-zero reset,
vertical motion and ground contact, angled `0x391` projectile,
real indexed `0x392` volley loop, cloud-conditioned loop count
and genuine auxiliary/animation control. In the complete F768
native-shaped VC7.1 parent it emitted the correct **647 B/181 x86
/17 original COFF geometry**, but **four real x87 and GPR opcode
positions** were in the wrong order. The original PE instructions
at original ordinals **64–65** do
`MOV EAX,[EBP−0x44]; FLD [EDX+0x44]` before `FSUB [EAX+0x44]`,
whereas raw-offset C++ loaded opponent X first via `FLD` and
only then read actor this. At ordinals **75–76**, the original
reads actor `this` before `FLD [ECX+0x48]` for opponent Y, whereas
the raw-source generator again emitted the `FLD` too early.

The original PE independently observes borrowed opponent and actor
position floats at **`+0x44` (X)** and **`+0x48` (Y)**. A new
pointer-only, never-instantiated
[`FighterBorrowedXYViewF771.hpp`](../probes/FighterBorrowedXYViewF771.hpp)
models exactly this observed 0x4C-byte view without assuming the
historical full fighter class or private field meanings. The
[`FighterGroundedVolleyTypedF771.inc`](../probes/FighterGroundedVolleyTypedF771.inc)
source evaluates the actual opponent X and actor X via those typed
borrowed float members, then the actual opponent Y member relative
to actor Y. VC7.1 naturally recovers original `MOV` before `FLD`
for both angle operands, without fabricated unused locals,
assembly, register forcing or original PE byte copying.

Eleven **fresh entire-parent** VC7.1 C++ source trials tested
one-sided opponent vs actor X ownership, both typed X, independent
opponent vs actor Y ownership, both typed Y, and meaningful lvalue
alternatives. The native source measurements were:

| Whole-source 2FB candidate | Complete 2FB geometry | Original x86 mnemonic mismatches | Wrong nonfield/nonshared-tail bytes |
| --- | --- | ---: | ---: |
| Historical raw offset source | 647 B/181 x86/17 refs | **4** | **119** |
| Typed opponent Y alone | 647 B/181 x86/17 refs | 2 | 115 |
| Typed opponent and actor X alone | 647 B/181 x86/17 refs | 2 | 115 |
| Typed opponent X and Y, actor X still raw | 647 B/181 x86/17 refs | 1 | 110 |
| **Typed both X plus typed opponent Y** | **647 B/181 x86/17 refs** | **0** | **111** |

The last source is the preferred genuine grammar: **all four wrong
x86 mnemonic positions have been repaired**, while **111 true
original nonrelocation/nonshared-tail machine bytes remain wrong**
(mainly EAX/ECX/EDX/EBP operand allocation). Those bytes remain
explicit negative evidence, not normalized away as harmless register
variation or credited as byte-exact source. One alternative had only
110 wrong bytes but still had a wrong original x86 instruction;
that is a weaker original source recovery.

## Entire original parent plus genuine physical fields checked

The tracked
[`verify-fighter-grounded-volley-typed-f771.py`](../scripts/verify-fighter-grounded-volley-typed-f771.py)
reconstructs the **same one 58KB original-shaped fighter parent** from
tracked F759–F768 C++ actions plus this 2FB source, and compiles
only the affected TU under pinned VC7.1 `/Od /Ob0 /Gy /GR-
/GX /GS /Zi`. The verifier rereads the original pinned PE, checks
all **647 original CODE B/181 x86 mnemonic/size positions**, all
**17 physical zero-addend DIR32/REL32 COFF fields** against their
original offsets, owner instructions, source symbols and independently
resolved original PE targets, and independently asserts that the
**111 real operand bytes remain nonmatching**.

The fresh parent additionally rechecks F768 2F8 (original 928 B/
252 x86/23 refs; 166 genuine remaining operand differences), F767
2F9 (1,367 B/381 x86/34 refs; 249 wrong), F764 2FA
(971 B/279 x86/31 refs; 156 wrong), and prior strict internal
C8–CE, 1F6–1F8 and 2DB source. The **943 original after-RET
jump DATA bytes** retain 156 valid actual `DIR32` labels and
319/319 identical nonfield sparse bytes, with zero new callable
CODE credit.

```bash
scripts/repo-python scripts/verify-fighter-grounded-volley-typed-f771.py
# F771 2FB: 647 B/181 x86/17 original PE fields, no opcode/width errors
# 111 remaining real GPR/operand bytes: NOT exact
# One affected 58KB parent only, not a 975-unit cold replay
```

The original full function is **58,294 native CODE B**; this normal
C++ source still emits **58,261 B**, with an original **33-B
whole-function length deficit**, differing registers and shared
branch displacement fields. Therefore the *entire original boss*
remains NONEXACT. Formal whole-author ledger remains **975
complete exact functions /866,072 original CODE bytes** (43.88%
reviewed), no partial case credit. The generated CPP/OBJ/PDB,
compiler transcript and evidence receipt remain under ignored
`.analysis/f771-fighter-grounded-volley-whole/`; the genuine
source, physically observed borrowed view and verifier are tracked.
No mass cold replay, original EXE editing or compiler/SDK carrier
CODE duplication was performed.
