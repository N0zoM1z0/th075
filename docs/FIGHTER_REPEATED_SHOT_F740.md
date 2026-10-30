# F740 — three whole original 196/197/198 repeated and delayed shots in the 58KB fighter

**New normal C++ game-source recovery, not a complete original game-function byte-exact match.**
Original input: the user-provided Japanese TH075 1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The authored `00543210` giant has 58,294 original CODE bytes plus
943 independent post-RET switch DATA bytes. These actions are internal
case interiors, NOT separately callable authored whole functions.

## Entire physically bounded original PE game actions

| Actual native original handler | Physical original PE CODE interval | Original CODE/x86 | VC7.1 in newest complete parent | Typed original PE/COFF fields |
| --- | --- | ---: | ---: | ---: |
| `0x196` | `0054991A`–`00549ACE` | **436 B/118 x86** | **424 B/118 x86** | **12/12** |
| `0x197` | `00549ACE`–`00549C82` | **436 B/118 x86** | **424 B/118 x86** | **12/12** |
| `0x198` | `00549C82`–`00549D5C` | **218 B/62 x86** | **218 B/62 x86** | **7/7** |
| All newly recovered original game source interiors | | **1,090 original CODE B/298 x86** | **1,066 emitted B/298 x86** | **31/31 native typed fields** |

A particularly important *physical boundary* correction: the jump-table
entry for original action `0x199` points to the **shared default at
`00551598`**, not to the next sequential PE instruction. The original
native physical case after `0x198` is actually `0x19A` at `00549D5C`;
it begins with a continuation of the preceding original x87 `FNSTSW`
state and cannot be naively assumed to start with a separate ordinary
case prologue. F740 verifies `0x198` against that true native physical
extent, does not invent standalone `0x199` CODE or truncate the following
fall-through branch, and retains the later placeholders as NONEXACT.

Tracked natural [`FighterRepeatShotF740.inc`](../probes/FighterRepeatShotF740.inc)
implements original authored game logic from all three complete
physical case interiors, including:

- Both `196` and `197` genuinely reset action+0x7C to one at stage 0,
  call original `ResetAt453E20`, initialize the real signed short
  `+0xF00` repeat counter, and clear completed action status when
  `GetNativeActionAt40FA30()==S16(+0x70)`.
- At stage **6**, both call `PrepareActionAt453D40(2)`, set real
  `+0x314` action angle (`0.0f` for 196, **30.0f** for 197), emit
  true kind **`0x330`** float X/Y projectile with signed facing
  direction multiplier **60** or **68**, using original global
  Y offsets `[00659A1C]` or `[0065928C]`, and start native
  `StartAnimationAt46D000(100)`.
- At stage **7**, the second repeated shot is genuinely gated by
  nonzero unsigned `+0x4E8`, signed short `+0xF00 < 6`, and signed
  short `+0x3B0 > 0`. It prepares 2 again, assigns original angle
  (`0.0f` for 196, **20.0f** for 197), emits a second native
  `0x330` shot at the same original PE globals, animates **10**,
  calls real `SetAuxActionAt40FB40(6)` and increments signed short
  `+0xF00`. The true native unsigned `CMP`/`JBE` was deliberately
  recovered from an unsigned C++ comparison rather than a signed
  `<= 0` guard with different negative-value behavior.
- Actual `198` has distinct original stage-0 state reset, stage-4
  `PrepareActionAt453D40(1)`, angle **60.0f**, `StartAnimation(250)`,
  directional coefficient **28**, original physical Y global
  `[00659A18]` and a genuine kind **`0x347`** projectile. Its
  completion action is **2**, not 0.

All three compiled in one freshly generated *complete original-shaped*
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` fighter parent. All
**298 ordered original native x86 mnemonics**, every true original
branch/call and **31/31 physically owned typed original PE/COFF
fields** match their authentic original x86 instruction ordinals,
PE targets, decorated source symbols, `REL32`/`DIR32` kind and
zero addend. Each entire case has **zero normalized nonfield GPR/CFG
errors**; none is byte-exact.

## Actual EBP/width negatives, not fake exactness

`196/197` each have **four native 6-byte integer-to-x87 temporary
`MOV/FILD` operands** emitted as actual **3-byte** accesses, so
each complete source case is **12 bytes shorter** despite identical
118 native x86 mnemonic positions and 12 authentic typed fields.
`198` naturally has all **218 original CODE bytes and 62 x86
mnemonic/width positions**, but its real stack slot addresses still
differ. Full original native-vs-compiler used EBP locations:

| Native actual original | Original used signed-direction float scratch | Actual current compiler scratch |
| --- | --- | --- |
| `196`, first and second genuine projectile | `−0xA4`, `−0xA8` | `−0x74`, `−0x78` |
| `197`, first and second genuine projectile | `−0xAC`, `−0xB0` | `−0x7C`, `−0x80` |
| `198`, actual single directional projectile | `−0xB4` | `−0x84` |
| Whole native parent saved `this` receiver | `−0x44` | `−0x3C` |

All ten native/source actual float conversion `MOV/FILD` accesses
are individually compared. Although the `198` instruction widths
match naturally, its EBP **operand bytes** still do not; this
cannot earn internal-case or whole-function byte-exact CODE credit.

## New same-parent regression: a historical source-context warning

Earlier F737 showed that inserting original `194/195` native bodies
naturally restored *zero normalized GPR mismatches* for 13 selected
complete previous action contexts. Adding the real complete
`196/197/198` **changes the compiler allocation again** in this
new entire parent. These changes are actual original/source
register-role errors and may not be passed off as inherited exactness.

| Previously source-backed complete original case(s) | New source generated CODE geometry | **Real new parent GPR/CFG differences** |
| --- | --- | ---: |
| `1F4`, original 538B/149x86 | **538B, all original x86 mnemonic and widths**, but deep EBP still different | **71** |
| `1F5`, original 538B/149x86 | **538B, all original widths**, but allocation phase changes | **71** |
| `1FA/1FB` | Native 287B/82 and 603B/174 widths retained | **50 /111** |
| `1FE/1FF` | Native 526B/153 each width retained | **96 /96** |
| `200/201` | Native 343B/102 and 436B/126 widths retained | **67 /85** |
| `2D0/2D1` | Native 416B/120 each width retained | **60 /60** |
| `2DD/2DE` | Native 680B/189 and 660B/189 widths retained | **80 /0** |
| `2EF` | Native 788B/224 width retained | **0** (still strict in this selected source context) |

This is meaningful physical compiler-state evidence, **not a
progress regression to roll back** and not a reason to add artificial
locals or reorder actual original cases. The source still describes
three more authentic game actions, but recovering further real
following cases is required to resolve original register phases.
No previous *27-context-strict* count is reused in this new C++ parent.

## Whole native 58KB and separately owned 943B DATA validation

Portable targeted
[`scripts/verify-fighter-repeat-shot-f740.py`](../scripts/verify-fighter-repeat-shot-f740.py)
rebuilds just **one complete original-shaped native fighter C++
parent**, asserts all **1,090 original action CODE bytes** and its
298 native x86 ordinals, original complete native action bounds and
31 genuine PE/COFF relocations, checks every real deep EBP
operand, and reruns the preceding complete native `190–195`
actions in that same newly compiled object. The F737 physical
context checker now accepts optional independently measured new
source starts and **true GPR error counts**, while preserving its
older F737 default exact-context regression test.

The same full parent additionally verifies **13 selected earlier
original physical action contexts** and independently the entire
**943 native after-RET switch DATA bytes**, including all **156
true original/source `DIR32` jump label relocations** with actual
decoded x86 instruction targets and all other **319/319 original
sparse-array bytes**. No original after-RET DATA is added to
whole-function CODE credit.

```bash
scripts/repo-python scripts/verify-fighter-repeat-shot-f740.py
scripts/repo-python scripts/verify-fighter-eight-ground-f737.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Original whole source/OBJ/PDB/compiler transcripts and typed PE
comparisons are retained locally in Git-ignored
`.analysis/f740-fighter-repeating-shot/`. Tracked normal C++ source,
selected-parent verifier and original/native field evidence are
portable. **No executable edit, artificial stack locals, cropped
native instruction range or all-961-unit cold replay.** The formal
accepted original whole-game CODE ledger stays **961 functions /
863,592 native CODE B (43.75% reviewed)**; original 58KB fighter
remains NONEXACT.
