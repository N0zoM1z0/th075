# F645 — two complete native 60-instruction B4/B5 motion restart cases in all eleven giant fighters

Pinned Japanese TH075 1.11 original `resources/th075.exe`, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`. Normal original MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, compiled as each selected **entire enclosing fighter `Advance()` C++ source TU**. These are **physically bounded original internal game-action cases**, not complete independently callable original functions or accepted whole-function CODE. All containing giant fighters remain **NONEXACT**.

## Original PE semantics — physical handler boundaries, double break and per-actor auxiliary states

The actual original cases are **`0xB4→0xB5→0xC8`**, not `B4→B5→B6`: native B6 and following unmapped slots point at the common default handler; the **next physically located real game handler after B5 is C8**. Each original B4 and B5 owns **60 complete x86 instructions**. At stage/frame0, it calls actual `00453E20` reset, sets original horizontal/vertical position `+0x50` to **+8.0f for B4** or **−8.0f for B5**, sets `+0x54=12.5f`, `+0x5C=0.75f`, clears `+0x30`, and calls real motion reset `0040FC50`. The original ground-condition x87 compare is **strict** `POS48 > original float [0065782C]` (`TEST AH,0x41`); it subtracts `POS5C` from `POS54` and, when `POS48+POS54 <= original ground`, calls the true `0040FAC0(0xA)` game action, clears `POS48`, calls real `00453E20`, and exits this switch case. Otherwise frame completion via real `0040FA30` may call native auxiliary-state setter **`0040FB40` with an actor-and-action-specific argument**.

**Important: the original does not have one shared auxiliary parameter for all characters.** Independently read original native x86 ordinal55 arguments are:

| Original giant owner | B4 native auxiliary state | B5 native auxiliary state |
| --- | ---: | ---: |
| `0045DD70`, `0058AF60` | 7 | 5 |
| `00486550`, `004AC040`, `004F7130`, `005214B0`, `005AEEC0` | 8 | 10 |
| `004D7E70`, `00564BE0` | 7 | 7 |
| `00543210` | 6 | 6 |
| `005D73C0` | 7 | 6 |

The first natural C++ implementation produced **only 59 instructions per true case**: it placed the final `break` *outside* its auxiliary conditional, eliminating one actual original game `JMP`. The pinned native case has a branch-specific `JMP` at x86 ordinal58 **and a separate unconditional `JMP` at ordinal59**, with the same real original shared-exit destination. The corrected ordinary [`FighterMotionRestartB4F645.inc`](../probes/FighterMotionRestartB4F645.inc) uses `if (frame==native) { SetAuxActionAt40FB40(...); break; } break;`, recovering **both actual compiler-generated native jumps**, with no inline assembly, duplicate byte patches or fake stack locals.

## Strict full native cases and source PE/COFF physical fields

[`verify-fighter-motion-restart-f645.py`](../scripts/verify-fighter-motion-restart-f645.py) independently decodes actual original B4→B5→C8 native handler starts, full original 60 x86 GPR/x87/CFG operands and physical widths, each actor-specific original B4/B5 auxiliary argument, and **eight original zero-addend typed `DIR32/REL32` source COFF references per complete case** at actual native x86 ordinals:

`9 CALL 00453E20`, `19 CALL 0040FC50`, `22 FCOMP [0065782C]`, `36 FCOMP [0065782C]`, `42 CALL 0040FAC0`, `46 CALL 00453E20`, `49 CALL 0040FA30`, `57 CALL 0040FB40`. The real source symbol, actual original PE target, type, zero addend and physical C++ x86 instruction role are checked separately; relocation fields are never used to conceal an incorrect jump, x87 test or GPR operand.

The original `00564BE0` wide saved `this` receiver sits at `EBP−0x88`, so **exactly 20 genuine receiver MOVs widen by 3 bytes per original 60-x86 case**. This yields **275 original CODE bytes** versus the natural reference's 215 bytes. All ten other owners' real complete cases have **215 original CODE bytes** each.

| Still-NONEXACT enclosing original giant | Strict native complete B4/B5 cases | Original internal CODE bytes | Original x86 role matches | Real typed COFF fields |
| --- | ---: | ---: | ---: | ---: |
| `00564BE0`, true wide EBP−0x88 receiver | 2 | **550 B** | 120/120 | 16 |
| Other ten original fighter giants | 20 | **4,300 B** | 1,200/1,200 | 160 |
| **F645 verified original complete case interiors** | **22** | **4,850 B** | **1,320** | **176** |

Every **freshly compiled whole giant parent C++ object** also rechecks original F642 A7/A8 including its actual FILD signed scratch locals and member-first x87 float sum, F641 A3/A4/A5, F639 9F/A0/A1, F637 strict-vs-inclusive 9E, F636 9B/9C, F633 97/98/9A, F631 96, F629/F630 91 with original known honest register-role negatives, F628 earlier jump landings, native mode63 where strict, thirty earlier native F598–F614 source-backed game cases, and the **complete separately owned after-RET sparse/dense jump DATA**. Existing selected earlier verifiers were extended backward-compatibly for the actual 120-instruction B4/B5 followup and the native next C8 marker; their original earlier `--boss` commands remain valid.

## Accounting and reproducing only selected units

F598–F642 bounded strict source-backed study: **544 real original game-action interiors /148,405 original native internal CODE bytes**. F645 adds **22 whole internal case bodies /1,320 original GPR/x87/CFG instruction roles /4,850 original native inner CODE bytes /176 true physical PE-target COFF records**, yielding **566 strict original native case interiors /153,255 original internal CODE bytes**. These are **not 566 independent authored complete-function matches** and no original giant whole-function source is yet exact. Official accepted authored whole-function registry remains **943 whole exact functions /862,726 original CODE bytes (43.71% reviewed)**, with 22 giant originals and three other authored whole functions nonexact. No all-unit cold replay, target EXE patch, synthetic locals, manual original x86 graft or outside Oracle acceptance.

```bash
scripts/repo-python scripts/verify-fighter-motion-restart-f645.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-motion-restart-f645.py --boss 0x00543210
# Optional ONLY the eleven affected whole giant C++ source TUs:
scripts/repo-python scripts/verify-fighter-motion-restart-f645.py
scripts/repo-python scripts/verify-fighter-projectile-launch-f642.py --boss 0x005AEEC0
scripts/repo-python scripts/validate-tracking.py --require-target
```

Complete pinned original PE native case/field receipts, new whole VC7.1 C++/COFF/PDB, compiler logs and selected predecessor source proofs are retained under ignored `.analysis/f645-fighter-motion-restart-verified/`; initial independent 59→60-instruction natural C++ compiler trials are under ignored `.analysis/f645-native-motion-restart/`.
