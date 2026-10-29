# F656 — five more full native fighter stage/case interiors in 00543210

Original supplied Japanese TH075 version 1.11 `resources/th075.exe`,
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is a normal genuine pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
reconstruction in **one fresh complete 58,294-byte original giant
fighter source parent**. The containing original entire giant is
**NOT whole exact**, so its inner cases earn no independently callable
whole-function authored CODE credit. There are separately owned 943
after-RET sparse/dense switch DATA bytes, also checked unchanged.

## Real original native physical dispatch, not inferred handlers

The original jump-table action `0x132` points to the **shared default
handler** (the same actual address as action `0x50`), and therefore
has **no independent physical native CODE case body**. The original
next physical handlers are `0x131→0x133→0x134→0x135→0x136→0x186`,
not a falsely invented `0x132` source handler.

| True original action | Full original physical native extent | Original x86 roles | Original internal CODE | Actual physical typed PE/COFF refs |
| --- | --- | ---: | ---: | ---: |
| `0x131` | `00548710`–`00548828` | 81 | 280 B | 6 |
| `0x133` | `00548828`–`0054899A` | 110 | 370 B | 9 |
| `0x134` | `0054899A`–`00548A75` | 61 | 219 B | 6 |
| `0x135` | `00548A75`–`00548BD2` | 102 | 349 B | 8 |
| `0x136` | `00548BD2`–`00548CDC` | 80 | 266 B | 7 |
| **Five newly reconstructed real complete original interiors** | | **434** | **1,484 B** | **36** |

`0x131` starts with the actual x87 vertical-velocity and collision
path, transitions to action 10 upon ground contact while clearing
members `+0x48/+0x5C/+0x54`, otherwise prepares animation `0x1C`
at native stage 3, resets the paired state words at stage 5, and
prepares `0x1D` at stage 6. `0x133` initializes velocity and stage
state, applies a separate positive-velocity drag at actual global
float `006581E0`, prepares two actual resource shots kind `0x341`
and `0x342` at stages 3 and 8 (with `0x1C` animation), and loads
15.0f at stage 6. The native `0x133` x87 zero comparison uses an
original `TEST AH,0x41; JNE` (strictly positive only), unlike
clamping via `TEST AH,5; JP`; both have been matched rather than
interchanged.

`0x134` matches the authentic reset/flag-gated falling pattern, clears
short `+0xF00` after action completion, and prepares `0x1D` at stage
1. `0x135` has an **additional actual stage-10-or-11 velocity
subtraction** using distinct original float `00657478`, initializes
20.0f at stage 7 and spawns kind `0x33F` at stage 10. `0x136`
spawns kind `0x33E` at stage 5, and prepares animation `0x1D` at
stage 6. Both preserve native signed action/frame checks, GPR
register ownership, two separate animation/shot phases and original
shared exit at `005515C2`.

## Fresh full-parent verification and true COFF field ownership

The ordinary C++ fragments
[`FighterLateGroundF656.inc`](../probes/FighterLateGroundF656.inc)
and [`FighterLateShotsF656.inc`](../probes/FighterLateShotsF656.inc)
are included in the same normal complete original giant C++ probe.
[`verify-fighter-late-stages-f656.py`](../scripts/verify-fighter-late-stages-f656.py)
independently reads real original PE case extents and checks **every
physical original REL32/DIR32 reference**, original x86 instruction
ordinal/target, generated COFF symbol/type, zero addend and physical
ownership. Specifically the five real PE-targeted field counts are
**6/9/6/8/7**; the new global `006581E0` must appear as an actual
`DIR32` float field, not be silently masked as a register difference.
The unlinked compiler object has zero placeholder values for genuine
absolute PE float fields. The verifier normalizes **only** those
independently verified typed global fields, and requires all other
original GPR/x87/CFG mnemonic, source role, branch shape, widths
and counts to agree.

F656 also invokes the earlier genuine-source verification on the
**same newly compiled parent** for preceding original native cases
`CF/D0/D1/D2/12C/12D/12E/12F/130`, plus F645/F642 and earlier
original native cases and the **complete independently owned after-RET
switch DATA**. Across all 14 consecutive actual native case bodies,
now **997 original x86 roles /3,425 original inner CODE bytes /
96 genuine typed PE/COFF fields** have strict source evidence in
one original giant. This is **not** a 3,425-byte whole-function
exact claim, and the remaining enclosing function is not exact.

The general F598–F656 giant research cohort now contains **582
strict native inner case bodies /157,127 original internal CODE
bytes**, all uncredited until their respective whole original
parents exactly match. Formal authored exact functions remain
**943/862,726 native CODE bytes** (43.71% reviewed); **22 complete
fighter giants + three other authored whole functions** remain
nonexact. All 95 origin-unknown native candidate classifications
remain pending, including the separately verified F655 small leaves.

```bash
scripts/repo-python scripts/verify-fighter-late-stages-f656.py
scripts/repo-python scripts/verify-fighter-falling-finish-f654.py
scripts/repo-python scripts/verify-game-unattributed-leaves-f655.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The new whole-parent CPP/COFF/PDB and compiler log, real original
native bounds and typed field JSON receipt remain under ignored
`.analysis/f656-fighter-native-late-stages/`. One selected whole
fighter source TU was compiled; no original game binary patch,
manual assembly, fake locals, mass 943-unit cold replay or external
Oracle acceptance was performed.
