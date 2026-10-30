# F734 — three complete original fighter 190/191/192 eight-shot actions

**New meaningful normal C++ source, still original whole-function NONEXACT.**
The pinned original is the user's Japanese TH075 1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The authored whole `00543210` has **58,294 original CODE bytes**, with
**943 independently owned after-RET switch DATA bytes**. Original action
interiors below are **not independently callable authored functions**;
none earns formal matched CODE while the giant remains nonexact.

## Three genuinely previously placeholder-backed complete physical actions

| Original native action | Full pinned PE interval | Original entire CODE/x86 | New entire VC7.1 case CODE/x86 | Actual original PE/COFF fields |
| --- | --- | ---: | ---: | ---: |
| `0x190` | `00549364`–`00549478` | **276 B /75 x86** | **266 B /75 x86** | **7/7** |
| `0x191` | `00549478`–`0054958C` | **276 B /75 x86** | **266 B /75 x86** | **7/7** |
| `0x192` | `0054958C`–`0054967C` | **240 B /68 x86** | **230 B /68 x86** | **7/7** |
| **All new original internal sources** | | **792 B /218 original x86** | **762 B /218 emitted x86** | **21/21 physical typed fields** |

Tracked natural [`FighterEightRoundF734.inc`](../probes/FighterEightRoundF734.inc)
reconstructs original actual game behavior, not dummy case markers:

- Native `0x190` and `0x191` initialize original `+0x7C=1`, call real
  `ResetAt453E20`, initialize the real `+0xF00` flag to zero, and set
  that flag to one if original `+0x4F0` is zero. At original animation
  stage **5** (190) or **4** (191), each calls genuine
  `PrepareActionAt453D40(0)`, writes the real `+0x314` angle member,
  starts animation **200**, and emits **eight real `0x324` shots**.
- `0x190` uses direction × **70**, angle **0.0f**, and original
  projectile Y global `[00659A30]`. `0x191` uses direction × **64**
  (native `SHL signed_dir,6`), angle **20.0f**, and original Y global
  `[00659A2C]`.
- `0x192` has no `+0x4F0`/`+0xF00` flag logic: it resets only at
  stage zero, triggers at stage **4**, sets angle **45.0f**, uses
  direction × **44** and original Y global `[00659A28]`, and
  finishes with the authentic **`SetNativeActionAt40FAC0(2)`**, not
  the 0 used by its neighboring handlers.
- All three correctly pass signed facing, true actor float X/Y
  position, genuine actor-facing signed integer-to-x87 conversion,
  the original eight-round loop count, and real native completion
  callback rather than synthesizing a fake loop or arbitrary stack.

## One original-shaped complete 58KB parent: genuine positives and negatives

[`verify-fighter-eight-round-f734.py`](../scripts/verify-fighter-eight-round-f734.py)
cold-builds a **single full original-shaped VC7.1 fighter parent**
using pinned flags `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and all previously
recovered real C++ actions, including 1F4–1F8, 1FA–1FF and 2xx cases.
It rereads original PE complete native case intervals and checks:

- **All 218 native x86 ordered mnemonics** in these three cases are
  identical to MSVC source (75/75/68), and all 21 original native
  typed `REL32` call or `DIR32` global fields have correct physical
  x86 owning instruction ordinal, source symbol, original PE target,
  zero addend and proper relocation type.
- **Zero normalized nonfield GPR/CFG operand discrepancies** in each
  complete internal case, after the explicit original/source saved
  receiver mapping. This does **not** mean exact bytes: native stores
  `this` at `EBP−0x44`, this more complete compiled parent uses
  **`EBP−0x34`**, and other real stack owner operands differ.
- The generated code is **10 B shorter** than native *per case*:
  actual original native conditional-branch x86 ordinal 26 for
  190/191 or ordinal 19 for 192 is **6 B**, generated only **2 B**;
  original signed-direction integer-to-x87 `MOV/FILD` pairs at
  x86 54/55 for 190/191 and 47/48 for 192 are each **6 B**,
  emitted **3 B**. These are exactly **three genuine instruction
  width differences per case (4 + 3 + 3 = 10 B)**, never
  silently normalized to fake byte-exactness.
- Real native eight-shot loop indices are `EBP−0x10/−0x14/−0x18`;
  source stores are `−0x8/−0xC/−0x10`. Original integer-to-float
  temps are `EBP−0x90/−0x94/−0x98`, versus current source
  `−0x58/−0x5C/−0x60`. Every actual source and native signed
  float scratch operand is checked independently at its x86 ordinal.

This is also a meaningful C++ lifetime finding. Three actually
used 8-shot loop indices and three actually used signed direction
conversion temporaries make the entire compiler frame deeper: this
selected parent saves `this` at `−0x34`, whereas the previous F732
selected parent used `−0x28`. The original `−0x44` has still **not**
been reached naturally. Other prior source-backed original case
interiors can also change x86 width/register phases when this source
is inserted. No old-context strict count is transplanted.

## Same-parent rechecks and full separate original switch data

The tracked verifier independently rereads bounded original/native
`1F4/1F5`, `1FA/1FB/1FE/1FF`, `200/201`, and `2EF` source contexts
in **this same new compiled giant**. It verifies their true
original PE bytes, full original/synthesized source case lengths,
authentic x86 counts, real typed PE/COFF field counts, and current
C++ GPR discrepancies rather than inheriting old results.
`200/201` remain **67/85 nonfield GPR errors** in this particular
parent; `2EF` is still strict in the tested GPR/CFG metric.

Original/native after-RET DATA is also independently checked in the
same newly compiled full parent: **all 943 bytes**, including
**156 actual physical native/source `DIR32` relocations**, each to
an actual decoded native or C++ instruction address, and all
**319/319 other native sparse-map bytes equal**. This is separate
jump-table DATA, not accepted original CODE. The older F728 native
DATA checker now supports optional, independently verified C++
case-start indices while preserving its original default context.

```bash
scripts/repo-python scripts/verify-fighter-eight-round-f734.py
scripts/repo-python scripts/verify-fighter-following-native-f732.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The generated whole parent, actual compiled OBJ/PDB, compiler logs,
and physical original PE/COFF comparison receipt are retained locally
in ignored `.analysis/f734-fighter-eight-round/` (not claimed as
tracked native input). Tracked normal C++ source and targeted verifier
are reproducible. **No original EXE modification, fake stack
padding, independently accepted inner-case CODE, or all-943-unit
cold replay.** Reviewed whole-function exact ledger remains
**943 functions /862,726 original CODE bytes (43.71%)**.
