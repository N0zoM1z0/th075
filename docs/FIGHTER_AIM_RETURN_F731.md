# F731 — entire original 1F8 aiming-return handler restores actual 200/201 register phases

**Substantial original-grounded source recovery, NOT an original whole-function
byte-exact match.** Source target: user-supplied Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The enclosing authored `00543210` fighter is still **58,294 original CODE B**
and **943 separately owned original after-RET switch DATA B**. An internal
action cannot be adopted as an independently callable complete game
function; this work adds **zero accepted whole-game CODE bytes**.

## Physical original handler and genuine complete C++ gameplay

| Original native case | Pinned PE interval | Original entire CODE/x86 | Fresh whole-parent VC7.1 | Physical typed PE/COFF fields |
| --- | --- | --- | --- | --- |
| `0x1F8` | `0054B43A`–`0054B9F9` | **1,471 B /422 x86** | **1,455 B /424 x86** | **45/45** original typed fields, actual source owner instructions |

New tracked ordinary C++ [`FighterAimReturnF731.inc`](../probes/FighterAimReturnF731.inc)
restores the actual complete source-shaped action: stage-zero original
reset and state/byte flags; stage-three–ten grounded Y descent and
floor-crossing transition to auxiliary 15; stage 11–13 facing repairs
and the original contact/boundary tests against real `+0x2D8/+0x2DC`
position limits; conditional stage-14/15 transition to `0x1FA` with
real `0040FBB0(0,0,0)` motion reset; true stage-14 landing with
speed damping, auxiliary 16, motion reset and position zeroing;
late X-velocity slowdown, native completion and real stage-three
reverse-facing `0x7D/0x7E` projectiles with stage velocities and
ground-adapted Y speed.

The *new* original stage 14 is not a guessed filler. It calls the true
native `00453D40(6)`, sets X/Y speed to 30.0f/-30.0f, and computes
signed target angle using the actual original **first
`00483300` angle function** and physical global `[00657828]`, then
calls the original CRT `__ftol2`, stores the result at `+0xF04`, and
clamps it to -15. It computes the native negative signed-short
angle as an **integer `NEG` before `FILD`**, then calls the true
`0040FB70(angle,28.0f)` motion method. It calls the real
`0040FBB0(0,80.0f,0)`; native original instruction is exactly
`PUSH 0x42A00000` (**80.0f**, not historical provisional 85.0f).
The **second genuine `00483300`** computes a float argument using
actual velocity member registers, divides by the same original
physical global and applies `[00657CBC]` before storing `+0x30`.
Stage 15 converts native short `+0xF04` to float member `+0x314`
and emits real native `0x338` projectile, with original stage 18/11
auxiliary dispatch. Every input is used for authentic game behavior;
no unused local or original machine-byte graft is present.

## Compiler grammar investigation and remaining genuine native negatives

The first complete C++ source compiled to **1,458 B/425 x86** with all
45 original call/global destinations, but it had real integer and
float source grammar errors. F731 compiled **six entire original-shaped
58KB parents** to probe integer versus float direction multiply and
negative signed-short angle, **seven more** for natural float argument
lvalue access to the second original `00483300` call, and **eight
more** for target/source X/Y lvalue ownership at the first angle call.
All trials built the complete VC7.1 parent under
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, never a cropped action body.

Independent original PE disassembly resolved several problems:

- Native signed `0xF04` angle conversion is real **`NEG integer;
  MOV [EBP]; FILD`**, not a floating-point `FCHS`. Moving the
  negative operation before the float cast fixes this genuine
  instruction order.
- Native 80.0f motion constant was corrected from an earlier wrong
  85.0f source hypothesis. This is an actual game-behavior fix,
  not a register/geometry trick.
- Natural `*(&POS)` float lvalue in the **second** angle call
  reproduces the native direct integer-register `MOV/PUSH` argument
  grammar rather than an extra `FLD/PUSH/FSTP` sequence. Source
  total falls from **425 to 424 x86**.
- A genuinely used target-Y member lvalue in the **first** angle
  changes actual `MOV/FLD` ordering to the more original-shaped
  form, eliminating one float-operand-order edit block.

Current whole-parent compiler source emits **1,455 B/424 x86**. All
**45 original PE/COFF relocations** match their real native target,
source decorated symbol, `REL32/DIR32` type, zero addend and owning
instruction mnemonic, at the actual `+1/+2` x86 instruction ordinal
shift due to the two non-native x87 operations.

Native `FCOMP dword ptr [this+0x44]` at original x86 ordinals
**127 and 139** still compiles as **extra `FLD [this+0x44]` plus
`FCOMPP`**. The source has a further two-instruction original
first-angle owner-order swap, not a source-exact reconstruction.
The actual original integer-to-x87 used stack slots are much deeper:

| Original native x86 ordinals | Generated x86 ordinals | Native EBP scratch | Compiler EBP scratch |
| --- | --- | --- | --- |
| 256/257 | 258/259 | `−0x100` | `−0x74` |
| 317/318 | 319/320 | `−0x104` | `−0x78` |
| 344/345 | 346/347 | `−0x108` | `−0x7C` |
| 378/379 | 380/381 | `−0x10C` | `−0x80` |

All **eight actual `MOV/FIMUL/FILD` integer-x87 scratch accesses**
are asserted individually against original and source operands.
Native saved receiver is `EBP−0x44`, while this source parent
still allocates it at `EBP−0x28`. The enclosing 58KB function and
this internal case are **NONEXACT**; 45 matching references and
some restored register roles cannot earn separate CODE credit.

## Major genuine natural compiler register-phase recovery

Crucially, adding this full 1F8 source naturally changes how VC7.1
allocates registers in *other native complete actions*. The previous
F728 and F729 entire-parent contexts had restored real 1F4–1F7
source, but showed original `0x200` and `0x201` **67 and 85 genuine
nonfield GPR/CFG operand differences**. In the **same newly
compiled F731 full original-shaped parent**, these are naturally
**both reduced to zero**, without dummy stack padding, register
assembly or moving any original PE target:

| Native earlier whole physical internal handler | Original CODE/x86 | Prior source context GPR errors | New F731 whole-source parent GPR errors |
| --- | --- | ---: | ---: |
| `0x200` | **343 B /102 x86** | **67** | **0** |
| `0x201` | **436 B /126 x86** | **85** | **0** |
| `0x2D0` / `0x2D1` | 416 B /120 x86 each | 60 /60 (prior F728 context) | **0 /0** |
| `0x2DD` / `0x2DE` | 680 B/189 and 660 B/189 | 80 /0 | **0 /0** |
| `0x2EF` | **788 B /224 x86** | 0 | **0** |

These seven original internal cases have freshly checked **entire
bounded original CODE sizes, ordered mnemonics and instruction
widths, original PE/COFF typed field counts, actual jump-table case
addresses and full normalized GPR/CFG roles**, all in this single
newly built parent. This is a *source-context strict grammar
recovery*, **NOT proof that these action CODE bytes or the original
whole giant are byte-exact**. Other old cases are not presumed
strict: the historical F724 **27-strict** total has **not** been
revalidated exhaustively for F731, and must not be transplanted.

Tracked [`scripts/verify-fighter-aim-return-f731.py`](../scripts/verify-fighter-aim-return-f731.py)
cold-compiles just **one affected entire original-shaped 58KB
VC7.1 fighter C++ TU** and independently validates all 45 new
physical native fields, complete bounded 1471B source case and
its honest x87/stack differences. It also rechecks the previous
1F4/1F5 and 1F6/1F7 complete original native cases, the seven
strict current-context original actions above and the entire
**943-B original after-RET DATA**: all **156 authentic physical
`DIR32` fields** link original and C++ valid decoded instruction
starts, and the other **319/319 original nonrelocation bytes** are
byte-identical. No original switch index is fabricated or bypassed.

```bash
scripts/repo-python scripts/verify-fighter-aim-return-f731.py
scripts/repo-python scripts/verify-fighter-return-boundary-f729.py
scripts/repo-python scripts/verify-fighter-random-arcs-f728.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

All full source/OBJ/PDB, native PE field evidence and the 21 actual
C++ grammar builds are retained locally under ignored
`.analysis/f731-fighter-aim-return/`. The F728/F729 selected verifier
helpers now optionally accept a **physically proven real adjacent
1F8 source** and **current-parent zero-GPR** expected counts; their
older default original-source contexts are preserved separately.

There is **no** newly accepted whole function CODE, no change to
source-origin ledgers and **no full 943-unit cold replay**. The
formal exact authored ledger remains **943 whole game functions,
862,726 original CODE bytes (43.71% reviewed)**.
