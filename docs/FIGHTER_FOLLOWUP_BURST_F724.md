# F724 — complete native 2C5 in physically ordered fighter parent

**Normal C++ native-source recovery, not original whole-function
byte-exact acceptance.** Target is the user-supplied Japanese TH075
v1.11 `resources/th075.exe`, pinned SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original authored `00543210` owns **58,294 CODE bytes and
943 independent after-RET switch DATA bytes**. `0x2C5` is physically
one *internal action*, not an independent original game function.

## Entire original native action and meaningful C++

Original physical `0x2C5` has start `0054DDD2`, next handler
`0054E111`, **831 native CODE B /239 real x86 instructions /
23 native physically typed PE/COFF fields**. It follows the
already reconstructed native `2BF→2C0→2C1→2C4` cases and directly
precedes the real source-backed `2D0` storm header.

New tracked normal
[`FighterFollowupBurstF724.inc`](../probes/FighterFollowupBurstF724.inc)
restores the entire native action, including its true stage-zero
`ResetAt453E20`, state/latch setup (`+0x80=99`, `+0x7C=0`,
`+0x3AC=0`, `+0xF00=0`); native stage-16–24 fall and X/y drag
via original `[00659090]` and `[00657CF8]`; original ground
contact auxiliary `25`; game action completion/auxiliary state
reset; stage-one `InitTrajectoryAt453E80(40)` and
`PrepareActionAt453D60(23)`, followed by actual kind `0x74`
shot with signed direction ×46 and native Y offset `[0065826C]`;
and `+0x36C` member subtraction. Stage seven has the original
kind `0x3C` raw-coordinate projectile, kind **`0x344`** float
shot with signed direction ×55 and **original `[00659488]` Y
offset**, `StartAnimationAt46D000(500)`, action preparation 15,
and genuine 10.5f/25.0f/0.8f motion. Stage 7–14 emits native
kind `0x32E` float shots. Stage 15 repeats auxiliary action 11
up to five times through `+0xF00`; stage 25 terminates through
auxiliary 23. This is real executable gameplay source, not a
dummy body, guessed class owner or a machine-code graft.

Pinned MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` compiles this
entire case inside **one newly built original-shaped `00543210`
parent** to **831 B /239 x86**, matching every original native
instruction width and **238/239 actual mnemonic positions**.
Every one of the **23 original physical PE/COFF typed references**
is matched at its *original physical native x86 ordinal*, with
real PE target, source symbol, `REL32`/`DIR32` type and zero addend.
The original shared tail, real shots and next `2D0` handler
boundary are independently checked against the pinned native PE.

## Honest native x87/GPR and EBP negatives

`2C5` is **NONSTRICT**. Its original x86 ordinal 108 uses
`IMUL signed_dir,+0x2E`, followed at ordinal 112 by `FSUBR [X]`;
our algebraically equivalent source emits `IMUL −0x2E` and
`FADD [X]`, reproducing the required native `FILD`-first x87
evaluation order naturally but not identical original operand
bytes or the final opcode. Exactly **two normalized nonfield
GPR/x87 operand positions** differ (108 and 112), apart from
real original-vs-source EBP stack ownership.

Original real six-byte integer/x87 temporary operands at x86
109–110, 156–157 and 197–198 use
`EBP−0x178/−0x17C/−0x180`. The new compiler's
**actually used** temporaries live at
`EBP−0xB0/−0xB4/−0xB8`, all independently asserted. The
original saved `this` pointer is `EBP−0x44`, source is
`EBP−0x28` (one original-shaped prologue save and **3,316 real
compiler reload MOVs**), also independently validated.
Neither normalized GPR identity nor 831 matching *instruction
width bytes* is a claim of actual native byte-exact CODE.

## Significant cross-case compiler phase gain

Previously F722 put `2BF`, `2C0`, `2C1` and `2C4` in authentic
original physical order and fixed two important later GPR phases.
In F724, we replace the real following `2C5` source placeholder
with the complete genuine 831-byte gameplay handler. Its three
used integer-to-x87 intermediate objects further alter the *natural*
VC7.1 stack and register allocation of the later original cases:

| Previously reconstructed native action | F722 physical-order full parent nonfield GPR/CFG differences | F724 with real `2C5` added |
| --- | ---: | ---: |
| `2D0` | **60** | **0** |
| `2D1` | **60** | **0** |
| `2DB` | 235 | **159** |
| `2DC` | 80 | **1** |
| `2DD`, `2DE`, `2DF`, `2E5` | 0 each | **0 each** |
| `2EF` full 788B/224 x86 original interior | 0 strictly contextual | **0 strictly contextual** |
| `2F0`, `2F1` | 147, 170 | 147, 170 |

This improves two complete source-backed later actions from 60
GPR-role errors to **zero**, and reduces original `2DB/2DC` by
76/79 errors respectively. The latter still differ and all real
EBP native stack-owner roles continue to be validated, not
normalized away. The enclosing 58KB fighter is **NONEXACT**.

## One-parent native verification and reproducibility

Tracked [`verify-fighter-followup-burst-f724.py`](../scripts/verify-fighter-followup-burst-f724.py)
generates the complete original-shaped C++ giant from tracked
actual game source, inserts `2C5` after genuine `2C4` and before
`2D0`, compiles **just this one affected entire giant TU**, then
re-reads the complete original physical `2C5` 831-byte/239-x86
case and all 23 genuine PE/COFF field owners. It also reruns
physical original `2BF/2C0/2C1/2C4`, real `2D0/2D1`, `2DB/2DC`,
`2DD/2DE`, `2DF/2E5`, five `259–25D` and late `2F8–302`
in the **same new compiler source context**. All **27 previous
context-strict original nonterminal cases** (including `2EF`),
real `2F0/2F1` negative GPR phases, true saved-this and scratch
EBP source slots, and the **entire 943-byte after-RET switch DATA**
are checked anew. The older F722 checker accepts the independently
attested new **real 2C5 source neighbor** instead of assuming its
old marker, while F711 accepts explicit GPR phases from actual
new source-local lifetimes. Their older default cases remain
available and were regression tested separately.

```bash
scripts/repo-python scripts/verify-fighter-followup-burst-f724.py
scripts/repo-python scripts/verify-fighter-native-order-f722.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The generated CPP/OBJ/PDB, compiler transcript and physical PE/COFF
receipt are preserved in Git-ignored local
`.analysis/f724-fighter-followup-pair/`. Tracked natural source
and targeted full-original selected verifier are portable.
No original EXE byte edits, bogus stack locals, separate internal
case function credit or all-943-unit cold replay. The authored
**complete-function** exact ledger remains **943 functions,
862,726 native CODE B (43.71% reviewed)**.
