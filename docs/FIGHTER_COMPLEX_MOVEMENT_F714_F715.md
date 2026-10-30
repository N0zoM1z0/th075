# F714/F715 — full physical fighter 2DB approach and 2DC dual-volley actions

**Meaningful original-native C++ source recovery; the enclosing authored
fighter is still NONEXACT.** The original target is the user-supplied
Japanese TH075 1.11 `resources/th075.exe`, pinned SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Original authored `00543210` owns **58,294 CODE bytes** and **943
separately owned after-RET switch DATA bytes**. The two actions below
are internal case interiors, not independently callable complete game
functions. No matched CODE has been credited from either case.

## Original whole physical case bounds and normal VC7.1 C++

| Real original physical handler | Native complete extent | Original CODE/x86/typed fields | New whole-parent generated CODE/x86/typed fields |
| --- | --- | --- | --- |
| `0x2DB` | `0054E451`–`0054E851` | **1,024 B /290 x86 /34 original PE/COFF** | **1,032 B /292 x86 /34 typed fields** |
| `0x2DC` | `0054E851`–`0054EAAB` | **602 B /169 x86 /18 original PE/COFF** | **602 B /169 x86 /18 typed fields** |
| **Together** | Two physically complete original cases | **1,626 B/459 x86/52 original fields** | **1,634 B/461 x86/52 typed fields** |

Tracked source
[`FighterApproachPhaseF715.inc`](../probes/FighterApproachPhaseF715.inc)
recovers the complete, complicated original `2DB`: stage-zero
reset, native flags, original height/acceleration and floor cross;
stage 10–12 facing-dependent horizontal repair and real
`00454EE0` contact checks; four separate wall/body-position predicates
with actual `2D8/2DC` member bounds and original physical globals;
action-completion counter and difficulty-dependent stage
`0x2DF/0x2DC` transitions (including the **two different native
branches calling 2DC**); stage-three real signed owner-distance
`00412D90`, random facing selection, two original kind `0x7D/0x7E`
projectiles, physical X/Y velocity initialization and stage-10
auxiliary action 8. These are meaningful C++ branches, not no-op
markers or copied native machine bytes.

[`FighterBossMovementF714.inc`](../probes/FighterBossMovementF714.inc)
recovers the entire original `2DC`: real native
`00454BC0(3,4,0xFF0000)`, stage-zero control (`0xF00` latch),
negative Y velocity and downward threshold; true two independent
kind-`0x333` and difficulty-gated `0x387` shots with signed facing ×62,
member-first Y+global floating operands and original direction; late
stage positive-X deceleration and zero clamp, native completion
random `100–180` modified by signed difficulty, and the authentic
frame/phase-zero reset. The natural compiler matches **every single
native `2DC` x86 mnemonic and instruction width at all 169 positions**,
with all 18 physical typed native fields at their **original
instruction ordinals**. It is nevertheless **NOT byte-exact** because
native/source GPR allocation and EBP operands differ.

## Real unresolved 2DB x87 comparison/evaluation difference

The F715 whole case builds **1,032 B /292 x86** against the original
**1,024 B /290 x86**. Every one of its **34 actual original PE/COFF
call/global destinations** remains in the same physical field
*ordering*, with original target, source symbol, `REL32/DIR32` type,
zero addend and genuine owning mnemonic checked; field ordinal may
shift because the two non-native x87 instructions are real, not
cosmetic relocations. Original native `2DB` x86 ordinals **129 and
141** are memory `FCOMP [this+0x44]` after `FLD/FADD` or `FLD/FSUB`
of the real opposing boundary. VC7.1 source emits **`FLD` of the
second operand followed by `FCOMPP`** at aligned generated ordinals
129–130 and 142–143. Original `TEST AH`/`JP`/`JNE` branch encoding
also differs: this source is provisional on NaN/unordered edge cases
until original codegen is solved. A genuine float-load ordering
change around native ordinal 212 and other branch phase differences
remain. No comparison window was trimmed to hide these differences.

**Nine additional entire original-shaped VC7.1 parent builds** tested
baseline, negated comparator A/B/both, reversed comparator A/B/both,
read-only member lvalue pointers, and actual `volatile float` member
operands (all original gameplay operands genuinely used). None
removed the two extra x87 instructions; the reversed comparator
cases changed some authentic x87 opcode order and did not improve
original code shape. Full candidate source/OBJ/log, original opcode
edit blocks and source `2DB` byte lengths are retained under
Git-ignored `.analysis/f715-fighter-boss-approach/`.

## EBP and GPR are actual native differences, not exact credit

The current new whole-parent source emits the `2DB` actual
signed direction×80 integer-to-x87 temporary at **`EBP−0xB4`**
versus native **`EBP−0x194`** (two native full six-byte operations);
`2DC` emits signed direction×62 temporaries at **`−0xB8/−0xBC`**
versus physical original **`−0x198/−0x19C`** (four real six-byte
operations). Native saved `this` is **`EBP−0x44`**, compiled is
**`EBP−0x28`**, independently audited across **2,904 physical
source MOV uses**. The actual normalized nonfield native GPR/CFG
operand mismatch counts are **236 for `2DB`** and **95 for `2DC`**.
Matching an opcode and its length does **not** mean those register,
stack and original branch bytes match.

## Affected whole-parent regressions, physically retested

[`scripts/verify-fighter-complex-movement-f714-f715.py`](../scripts/verify-fighter-complex-movement-f714-f715.py)
regenerates and compiles **one complete original-shaped fighter TU**
with the existing authentic F672, F706, F708 and F711 C++ cases plus
these two newly recovered bodies, rather than compiling an isolated
case that changes MSVC register lifetimes. It independently rereads
the two original PE physical intervals, **all 52 genuine typed native
fields**, exact native original `2DC` mnemonics and widths, the
`2DB` seven specific compiler opcode edit blocks and original/source
EBP scratch slots. It rechecks previous real `2D0/2D1`, twin
`2BF/2C4`, five `259–25D`, and late full `2F8/2F9/2FA/2FB/302`
bodies and their typed original fields.

Importantly, this more complete parent still has **26**, not 27,
strictly source-context matched preceding nonterminal actions:
`2EF` has **144** real nonfield GPR differences, and
`2F0/2F1` have **175/170**, despite original source full-case
mnemonic/width geometry. Earlier selected contexts may have 27
strict cases, but **their results are not transposed into this new
full parent**. The latest parent also rechecks every one of the
independent original **943-byte after-RET dispatch DATA**.

```bash
scripts/repo-python scripts/verify-fighter-complex-movement-f714-f715.py
scripts/repo-python scripts/verify-fighter-falling-radials-f711.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Every generated source, object, PDB, compiler log and full bounded
native comparison receipt is retained only in local Git-ignored
`.analysis/f714-fighter-boss-movement/` and
`.analysis/f715-fighter-boss-approach/`; the portable fragment and
verifier files above are tracked in Git. Neither internal case is a
credited independent function. No target EXE modification, no fake
stack variables or 943-unit cold replay. Formal authored exact ledger
remains **943 whole functions /862,726 original CODE B (43.71%)**.
