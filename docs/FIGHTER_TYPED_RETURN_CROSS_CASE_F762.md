# F762 — true fighter 05F, 1F6/1F7/1F8 and cross-case typed float returns

**Major normal-C++ restoration inside the whole authored 58KB original
fighter; NOT an accepted byte-exact entire game function.** The target is
Japanese TH075 1.11 `resources/th075.exe`, pinned SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The real game-authored callable function begins at `00543210`, is
**58,294 native CODE bytes**, with **943 separate after-RET switch DATA
bytes**. An interior switch handler is not a separate callable game
function and is never credited independently.

## Complete original source and independently rechecked physical evidence

Source [FighterFacing05FF762.inc](../probes/FighterFacing05FF762.inc)
replaces the original state `0x05F` placeholder with genuine frame
transitions, signed facing selection, opponent position and the two real
`+0x44` float members. In the complete source parent, this naturally
emits the original **144 CODE bytes /44 x86 /3 native typed COFF
fields**; the **05F GPR allocation phase is still NONEXACT**, and this
negative is not hidden or promoted.

The two real original state handlers `1F6` and `1F7` are restored by
[FighterBoundaryReturnTypedF762.inc](../probes/FighterBoundaryReturnTypedF762.inc),
which naturally emits the complete paired states using the actual
original actor/opponent `+0x44` float lvalues and the original
`ContactAt454EE0` short-circuit structure. The later `1F8` is
restored by [FighterAimReturnTypedF762.inc](../probes/FighterAimReturnTypedF762.inc),
including the native signed-angle calculation and both read-only
borrowed X-coordinate lvalues.

| Entire original game action, inside ONE giant | True PE interval | Original and new CODE | Original x86 | Original typed PE/COFF fields |
| --- | --- | ---: | ---: | ---: |
| `0x1F6` | `0054AB00..0054AF9D` | **1,181 B** | **348** | **35** |
| `0x1F7` | `0054AF9D..0054B43A` | **1,181 B** | **348** | **35** |
| `0x1F8` | `0054B43A..0054B9F9` | **1,471 B** | **422** | **45** |
| **Original complete case total** | | **3,833 B** | **1,118** | **115** |

A fresh pinned VC7.1 compiler build of the **same entire parent** gives
exact original x86 instruction boundaries, widths and mnemonics for
all three full handlers. Every one of their **115 genuine zero-addend
physical PE/COFF reference fields** has its original instruction owner,
DIR32/REL32 type, original decorated source symbol and *independently
read original PE destination*. All other machine bytes are identical,
**except for legitimate relative branches to the not-yet-complete
external whole-parent continuation**. Those original exit JMP bytes
are not masked for a formal whole-function acceptance claim: the
parent remains NONEXACT.

## Previously incorrect C++ game semantics and compiler grammar

The older `1F6/1F7` source incorrectly required
`ContactAt454EE0()` as a prerequisite for **four** separate
collision/facing conditions. The original physical PE branch at
`1F6+0x16C` (corresponding state `1F7+0x16C`) instead goes forward
only 62 bytes to the two opponent-relative float comparisons, not
past all four conditions. The *correct* C++ nests the genuine
contact call only over the first two signed side-edge predicates;
the opponent-position predicates are independently evaluated
regardless of contact. This restores the **native two-byte `JE`**
instead of an incorrect six-byte long `JE`, shrinking each actual
complete game handler by four **real machine-code bytes** while
preserving the native algorithm.

The two later comparisons are against the *actual observed float
member at actor `this+0x44`*. Replacing a raw offset-cast expression
with this borrowed float member naturally makes VC7.1 emit original
`FCOMP DWORD PTR [ACTOR+0x44]`, not the nonnative extra
`FLD` + `FCOMPP`. These are genuine differently ordered x87
instructions, not trivially tolerated floating-point substitutions.

`1F8` has the analogous correct contact guard and directly typed
actor and opponent `+0x44` float members. An independently compiled
8-variant entire-parent evaluation-order experiment showed that
one-sided typing reduced the last wrong machine-byte count from six
to **two**, but typing **both sides** restores the native exact
`MOV EDX,[EBP−0x44]; FLD [ECX+0x44]; FSUB [EDX+0x44]`
grammar at original instruction ordinals `312–314`. This also
restores the full original 1,471-B case without added locals,
assembly, original byte arrays or artificial stack padding.

## Actual enclosing function and distinct negative contexts

With the real C8–CE source accepted as *internal research only*
(F759/F760), plus these genuine 05F/1F6/1F7/1F8 fragments, the
complete source emits **58,277 CODE B**, against the **58,294-B
original game function** — a remaining **17-byte original whole
CODE deficit**, **not** a whole-function byte match. The compiler
also emits the genuine separate **943-B original after-RET dispatch
DATA**: 156 original and source valid DIR32 switch references and
319/319 identical sparse-map nonfield bytes. DATA does not count as
callable game CODE.

The real 05F and following 062 GPR phases still differ. The later
large game actions `2DB` and `2FA` still each have two extra
`FLD/FCOMPP` native-geometry operations when using their older
source. Several long whole-parent relative branch displacements
still differ. Do NOT conflate near-matching function length,
strict case interiors or partially exact x87 with a formal accepted
whole boss.

## Reproducible ordinary C++ verification

The tracked one-owner verifier
[`scripts/verify-fighter-typed-returns-f762.py`](../scripts/verify-fighter-typed-returns-f762.py)
regenerates all prior real C8–CE and existing other action source,
inserts genuine complete 05F/1F6/1F7/1F8 source, compiles **only
this affected original-shaped complete fighter** under pinned
`/Od /Ob0 /Gy /GR- /GX /GS /Zi` VC7.1 and independently
checks all 115 native typed fields and their original PE destinations,
the exact original whole-case nonfield bytes, authentic shared-tail
JMP negatives, prior C8–CE source and full original after-RET DATA.

```bash
scripts/repo-python scripts/verify-fighter-typed-returns-f762.py
# Complete 1F6/1F7/1F8: 3833 native CODE B, 1118 x86 and 115 fields;
# no nonfield differences except genuine external parent exits
# Whole native 00543210 remains NONEXACT (58277/58294 CODE B)
```

The one rebuilt complete C++, OBJ, PDB, compiler transcript and native
receipt are stored under ignored local `.analysis/f762-typed-returns-whole/`.
No unrelated accepted source units were recompiled, no full 971-unit
cold replay was run, and the official count remains **971 whole exact
functions /865,244 native authored CODE bytes** (43.84% reviewed).
