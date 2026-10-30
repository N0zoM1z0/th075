# F744 — two full original 19A/19B fighter actions restore six-case and cross-case native GPR grammar

**Substantial native-source recovery in one complete 58KB fighter C++ parent;
NOT independently authored byte-exact game functions.** The original target is
the user-provided Japanese TH075 ver1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The authored game function `00543210` owns **58,294 original CODE B**
plus **943 separately owned after-RET switch DATA B**. Its internal
switch action interiors cannot be accepted as whole callable functions.

## Two complete native action interiors — previously placeholders

| Real original game action | Entire native physical PE CODE interval | Original and freshly generated C++ CODE/x86 | Original genuine PE/COFF fields |
| --- | --- | ---: | ---: |
| `0x19A` | `00549D5C`–`00549FBB` | **607 B /166 original x86** | **17/17** |
| `0x19B` | `00549FBB`–`0054A21A` | **607 B /166 original x86** | **17/17** |
| **Total new meaningful physical original action source** | | **1,214 original CODE B /332 x86** | **34/34** original typed fields |

Tracked ordinary [`FighterDoubleRepeatF744.inc`](../probes/FighterDoubleRepeatF744.inc)
implements the whole authentic game source for each case: stage-zero
signed short `+0xF00=0`, actual `+0x7C=1` state, real X/Y velocities
multiplied by the original `[00657F74]` global, native grounded
deceleration after stage five and actual `FCOMP [0065782C]`
threshold handling, early `ResetAt453E20` and native action **10**
on grounded completion, independent landing zeroing, original
completion callback to action **9**, and two real **`0x330`**
float-projectile attacks at animation stage **4** and **5**.

The projectile X uses signed direction ×**35** (`19A`) versus
×**27** (`19B`); the genuine Y globals are respectively original
`[00659A24]` and `[00659A20]`. Angle `+0x314` is **0.0f**
versus **−20.0f**. The stage-four projectile animates **100**;
stage five is additionally gated on physical unsigned `+0x4E8>0`,
signed repeat counter `+0xF00<6` and signed stock `+0x3B0>0`,
then animates **20**, sets original auxiliary action **4** and
increments the actual signed short repeat counter. Both real
projectiles are emitted via original `SpawnFloatXYAt453A70` using
actual actor facing and original game member positions. These are
actual consumed gameplay values, not fabricated compiler fillers.

### An important original COFF relocation ownership repair

The first full VC7.1 parent emitted exactly **607 B /166 x86 per
case** with the correct overall 17 field *count*, but in the
**second** X/Y velocity scaling operation the generated code used
`FLD [00657F74]; FMUL [actor+0x54]` rather than original
`FLD [actor+0x54]; FMUL [00657F74]`. This moved the original
physical `DIR32` source-field owner from native **`FMUL` at
x86 ordinal 19** to an incorrect **`FLD` at ordinal 18**,
even though the two instruction width differences balanced to
zero total bytes. It would be incorrect to call that structure
an original exact-match even with 607/166 overall size.

A **real actor Y-velocity lvalue**:
`POS54 = (*(&POS54)) * g_BounceScaleAt00657F74`
restores exactly the pinned VC7.1 native `FLD actor; FMUL global`
order, physical original 6-byte FMUL and correctly typed native
`DIR32` owner, in **both** complete actions. All 34 original
relocations now match the original owning x86 ordinal, actual
PE target, decorated source symbol, zero COFF addend and real
`REL32`/`DIR32` kind. No assembler, manual relocation edits,
source-code semantic padding or copied executable bytes.

## Meaningful whole-parent compiler register-phase recovery

Restoring these two genuinely needed earlier game actions changes
VC7.1 register lifetimes across the *same entire* parent. This
is observed in the new freshly compiled whole-parent object, not
an inherited historical F737 context claim:

| True original complete internal action(s) | Previous F743 parent normalized GPR/CFG mismatches | Fresh F744 full-parent result |
| --- | ---: | ---: |
| Newly real **19A/19B** | Still placeholder-backed | **0/0**, both 607B/166 original x86/17 physical fields |
| **19C/19E/1A0/1A1** | **33/59/53/53** | **0/0/0/0**; all 1,202 original CODE B, all 334 opcode AND width positions, 32 original field owners |
| **1F4/1F5** | **71/71** | **0/0**; both 538 emitted B/149 x86 with original widths and native original PE field counts |
| **1FA/1FB/1FE/1FF** | **50/111/96/96** | **0/0/0/0** |
| **200/201** | **67/85** | **0/0** |
| **2D0/2D1** | **60/60** | **0/0** |
| **2DD/2DE** | **80/0** | **0/0** |
| **2EF** | **0** | **0** |

Thus **six physically bounded consecutive original actions
19A/19B/19C/19E/1A0/1A1** now have authentic native **full
instruction-length geometry and all original PE/COFF fields**:
**2,416 original internal CODE B, 666 complete x86 instruction
positions and 66 genuine typed fields** in one natural VC7.1
parent. In addition **13 other original complete action contexts**
were remeasured with zero normalized nonfield GPR mismatches in
THIS particular source parent. Register matching after the
explicit original/compiler receiver normalization does **NOT**
mean any standalone original internal case or the 58KB whole game
function is byte-exact. True absolute EBP operands remain wrong.

## Remaining genuine EBP negatives, not masked or credited

| Original native source action(s) | True original physically used signed-int-to-x87 EBP slots | Actual compiled VC7.1 source |
| --- | --- | --- |
| 19A (two projectiles) | `EBP−0xB8/−0xBC` | `−0x88/−0x8C` |
| 19B (two projectiles) | `EBP−0xC0/−0xC4` | `−0x90/−0x94` |
| 19C /19E | `−0xC8/−0xCC` | `−0x98/−0x9C` |
| 1A0 /1A1 | `−0xD0/−0xD4` | `−0xA0/−0xA4` |
| Whole native fighter saved `this` | `EBP−0x44` | `EBP−0x3C` |

Every actually used projectile `MOV/FILD` native and emitted
stack operand and both source/native six-byte widths are checked
at real original x86 positions. The **0x30 offset gap** between
the native and current x87 scratch ownership points to other
unrecovered genuine C++ game scopes before these six original
cases, not permission to fake local variables. The saved receiver
is still two real DWORDs shallower than original. Remaining
25 historically deeply studied nonexact complete original game
functions remain nonexact; no new entire-function CODE is accepted.

The native switch values `199`, `19D` and `19F` remain **shared
original default handler dispatches** at physical `00551598`;
not independent callable action bodies or zero-byte functions.
The native 198->19A->19B->19C source order is checked directly.

## Full original target verifier, including independent DATA

Tracked [`scripts/verify-fighter-double-repeat-f744.py`](../scripts/verify-fighter-double-repeat-f744.py)
cold builds **one entire original-shaped VC7.1 fighter** from
tracked ordinary C++ sources and independently compares the
full pinned physical 19A/19B native action interiors, all 34 typed
original PE/COFF fields including the two once-misplaced FMUL
globals, original x87 predicates, GPR and deep EBP negatives.
It rechecks the four F743 19C/19E/1A0/1A1 native case interiors
in their new authentic source context and additionally reruns
the preceding original 190–198 and 13 selected actual complete
original native case contexts with **zero GPR error** in this
newly compiled parent. F743 and F740's historical independent
verifiers keep their old source-context defaults and run unchanged.

The entire separately owned original **943-byte after-RET
jump-table DATA** is rechecked in the same new object: all
**156 native/source physical `DIR32` entries** target actual
decoded native or source x86 instruction starts, and all other
**319/319 original sparse array bytes are equal**. These DATA
bytes are not accepted as newly recovered whole-game CODE.

```bash
scripts/repo-python scripts/verify-fighter-double-repeat-f744.py
scripts/repo-python scripts/verify-fighter-later-early-f743.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The full generated C++ giant, real VC7.1 OBJ/PDB/compiler logs and
physical native COFF receipt stay under Git-ignored
`.analysis/f744-fighter-double-repeat/`; tracked normal C++ source,
portable verifier and documentation are committed. No original
executable edits, fake EBP padding, partial function byte-credit
or mass 964-unit cold replay. Formal accepted authored ledger
remains **964 whole-game functions /863,913 native CODE bytes
(43.77% reviewed)**.
