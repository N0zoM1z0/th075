# F579 — strict 130/80-instruction native fade/effect actions 0x338/0x339

**Original Japanese TH075 v1.11 PE and actual VC7.1 natural C++ codegen,
not accepted whole-fighter CODE exactness.** Pinned Japanese PE SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This new source-level investigation extends the actual same one-TU
CharacterObject C++ action implementation of F572–F578 inside original
`004EBDA0`, a **33,293 whole CODE-byte still-unmatched giant**.
The complete native original CODE SHA256 and 438 separate after-RET
switch DATA bytes are verified before any diagnostic compilation.
No borrowed nominal class/interface identity is claimed as certain.

## Two physically different complete native action bodies

The real compressed native handler jump table, not a decompiler
snippet, bounds the two next nondefault game-action bodies:

- **`0x338`**: **130 complete native x86 instructions /478 original
  CODE bytes**. The original stage-zero signed frame test
  `S16(+0x62)==0 && S16(+0x64)==0` calls native
  `0040FBB0(0,0,0)`, resets `+0xD8`, motion/scale/counter/color,
  sets scale float fields to 1.0f, invokes actual parent
  `00453E60(10.0f)` and spawns original parent effect
  **`00453A70(0x33A)`** with true actor positions and signed
  direction byte. The code then handles a native `+0x7C==6`
  frame-state reset with signed `++S16(+0x80)`, separately
  increments `F32(+0x1C)` and `F32(+0x20)` from native float
  global **`00659428`**, and fades unsigned color byte `+0x11`
  by **20** if `S16(+0x62)>1`, otherwise resets. A genuine
  `0040FA30` action query controls another reset, and native
  stage-two entry creates a **different parent effect `0x339`**.
- **`0x339`**: a separate physical **80-instruction /309-byte**
  native body, *not* the same default handler. Its stage-zero
  initialization is similar but starts true float scale fields at
  **1.3f** (native immediate 0x3FA66666), does not call the
  extra `00453E60` parent setup or effect spawn, and fades the
  unsigned byte by **40**, not 20. Its native `0040FA30` / reset
  conditional is preserved. Two original x87 `FADD`s still use
  real float global `00659428`; no extra effect callback is
  invented or copied from the other action.

**Normal C++ produces the entire original x86 instruction order,
GPR registers, member/x87 operand grammar, conditional branch targets
and individual instruction lengths for both actions**, with no
exceptions: **130/478 and 80/309** respectively, not just
semantically equivalent hand-wavy fragments.

## Genuine PE/COFF source and all earlier case regressions

The tracked C++ source is
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp),
rechecked by
[`scripts/verify-characterobject-fade-spawns-f579.py`](../scripts/verify-characterobject-fade-spawns-f579.py).
The verifier freshly compiles **only the affected normal VC7.1
C++ translation unit** under pinned
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, then separately verifies the
entire 33,293-byte native original fighter CODE, the physical native
case boundaries (including every original shared-default alias),
and each of the now **21 genuinely nondefault complete game-action
bodies** under one compiler function.

- True action `0x338`: **9** physical typed `REL32`/`DIR32` COFF
  calls/float globals at the original instruction ordinals, including
  the **two different actual effects 0x33A/0x339** with native
  `00453A70` callee and float global 00659428.
- True action `0x339`: **6** physical typed COFF entries at their
  actual original native ordinal and symbol/type/zero addend.
- Source rechecks all older native original complete case ranges,
  including the F573/F574 and F578 known **three independent
  adjacent read-only MOV/FLD operand-order swaps**. None of the
  two newly restored cases needs that exception.
- It distinguishes original compact-vs-deep EBP physical spill
  width (remaining +18 native bytes each in real actions 0x330 and
  0x331) from real source behavior; F578 already demonstrated
  neighboring action `0x332` naturally moves its diagnostic C++
  temporary to disp32 and now has original 1,019-byte case length.

| Native complete game-action subranges | Original instructions | Real inner original CODE (no independent exact credit) | True typed COFF fields | Source-native order |
| --- | ---: | ---: | ---: | --- |
| Previous 19 F572–F578 genuine bodies | 2,602 | 9,634 B | 178 | Three bounded older swaps; separate EBP width expansions |
| New `0x338` full body | **130** | **478 B** | **9** | **Strict machine instruction grammar** |
| New `0x339` full body | **80** | **309 B** | **6** | **Strict machine instruction grammar** |
| **Total 21 real game actions** | **2,812** | **10,421 B** | **193** | Whole original giant nonexact |

The full native compressed sparse switch still reproduces **all
60 zero-addend physical `DIR32` jump-target COFF fields**, original
shared-default/repeated handler equivalence groups and
**198 literal original compressed byte indexes**. The complete
**438-byte after-RET DATA layout** is kept physically separate from
original executable CODE. Original `0x32F`, `0x333/0x334`,
`0x336/0x337` remain shared-default aliases, NOT fake reconstructed
game-action bodies. Original `0x33A` is now the *next unfinished
nondefault handler*, retained as an explicit diagnostic marker.

### Affected-only reproduction, no full all-unit cold replay

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-fade-spawns-f579.py
# Recheck earlier source cases in same larger function:
scripts/repo-python scripts/verify-characterobject-contact-stage-f578.py
scripts/repo-python scripts/verify-characterobject-direction-reversal-f577.py
```

Selected source/object/PDB/compiler logs and original-aligned cases
are retained in ignored `.analysis/f579-characterobject-fade-spawns-source/`
and `.analysis/f579-characterobject-following-338/`.
**These 10,421 original inner CODE bytes are not 21 original
independently exact functions.** The complete native **33,293-byte
giant remains nonexact**, including unimplemented later game actions
and unrecovered entire original class/stack lifetime. There is zero
new accepted whole/split CODE or DATA credit and no external
Factory/Oracle acceptance receipt.
