# F743 — complete original 19C/19E/1A0/1A1 giant fighter source and real GPR negatives

**Genuine natural C++ source recovery, NOT newly accepted original whole-function CODE.**
The pinned Japanese TH075 1.11 original is `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The enclosing authored native `00543210` is **58,294 original CODE B**
plus **943 separately owned after-RET dispatch DATA B**. Internal
switch-case action interiors are not independently callable original
functions; all new source here remains uncredited toward whole-function exactness.

## Four physically bounded original actions newly expressed as actual C++

| Original native action | Entire PE CODE interval | Entire native and VC7.1-generated CODE/x86 | Physical native PE/COFF fields |
| --- | --- | ---: | ---: |
| `0x19C` | `0054A21A`–`0054A2F4` | **218 B /62 original x86** | **7/7** |
| `0x19E` | `0054A2F4`–`0054A462` | **366 B /104 original x86** | **11/11** |
| `0x1A0` | `0054A462`–`0054A597` | **309 B /84 original x86** | **7/7** |
| `0x1A1` | `0054A597`–`0054A6CC` | **309 B /84 original x86** | **7/7** |
| **All four newly recovered complete internal action sources** | | **1,202 original native B /334 original x86** | **32/32 original typed fields** |

Tracked natural [`FighterLaterEarlyF743.inc`](../probes/FighterLaterEarlyF743.inc)
implements original game semantics in their real native order:

- `19C`: original stage-zero `+0x7C=1`, `ResetAt453E20` and real
  repeat counter `+0xF00=0`; on native completed action, set action 0;
  at **stage 5**, `PrepareActionAt453D40(3)`, angle 0,
  real kind **`0x335`** shot with signed direction×**40** and
  original Y offset `[00659A14]`, then animation **200**.
- `19E`: original stage-zero reset and counter; actual X/Y ground
  collision with native double x87 predicates against `[0065782C]`,
  real Y gravity `+0x54 -= +0x5C`, landing reset and transition
  to native action **10**; completed action can set auxiliary 10.
  Native stage 2 assigns X/Y speeds **−6.0f /17.5f**, drag **0.8f**.
  Native stage 5 prepares 3, sets angle **−20.0f**, spawns
  real kind **`0x335`** signed direction×**27** with original
  Y global `[00659A20]`, and animates 200.
- `1A0` and `1A1`: authentic stage-zero `+0x7C=1`, gravity and
  ground landing (zeroing X speed, Y speed and ground height),
  native stage **4** `PrepareActionAt453D40(3)`, speed
  **−8.0f/+10.0f**, drag **0.65f**, real angle **0.0f** versus
  **−20.0f**, original animation 200, then two distinct real
  kind `0x335` shots with signed direction×**45/27** and
  Y original `[00659288]` / `[00659A20]`, respectively.
  On completed native stage, both set original action **9**.

All four entire case interiors are part of the SAME original-shaped
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` parent, with no original
machine-byte patches, dummy stack locals, or isolated-case-sized
custom compiler profile. The compiler naturally emits **the same
CODE byte LENGTH and all ordered native x86 MNEMONIC AND WIDTH
positions** in every case; all **32 original physically typed
`REL32`/`DIR32` references** match actual native PE targets,
correct decorated C++ source symbols, zero addends and original
owning x86 ordinals. That is strong source control-flow grammar
evidence, **not original exact machine code**.

## Explicit real GPR and EBP negatives

| Entire original action | Normalized nonfield GPR/CFG mismatches in THIS full parent | Original used signed-int-to-x87 EBP scratch | Actual generated EBP scratch |
| --- | ---: | --- | --- |
| `19C` | **33** | `−0xC8` | `−0x88` |
| `19E` | **59** | `−0xCC` | `−0x8C` |
| `1A0` | **53** | `−0xD0` | `−0x90` |
| `1A1` | **53** | `−0xD4` | `−0x94` |

Each genuine `MOV`/`FILD` x87 scratch operand is checked in both
native and compiler outputs. The native original saved receiver is
`EBP−0x44`, current source remains **`EBP−0x3C`**. Full
instruction widths matching exactly does **not** establish native
GPR roles or saved-stack values; the original whole fighter remains
byte-NONEXACT.

The original `19A` and `19B` at `00549D5C` and `00549FBB` have
**607 actual original CODE B/166 x86 each**, but their source
remains **placeholder-marked and unrecovered** in this new
parent. The original dispatch values `199`, `19D` and `19F`
point to the real **shared default handler `00551598`**, not to
independent contiguous game functions; those defaults are not
falsely credited as source recovered. The physical native `1F4`
follows completed `1A1` at `0054A6CC`.

## Fresh whole-parent physical checks and independent DATA

The portable tracked
[`verify-fighter-later-early-f743.py`](../scripts/verify-fighter-later-early-f743.py)
recreates only one full original-shaped 58KB fighter, checks
all **four complete native physical PE case boundaries**, all
334 ordered native mnemonics and instruction widths, all 32
correctly owned physical native PE/COFF fields, actual status and
shot constants, and original/source real x87 stack negatives.

It rereads preceding original native `196/197/198`, `194/195`,
`190/191/192` source contexts in this same new parent and verifies
**13 selected previous complete native action contexts** with
honest source GPR differences: `1F4/1F5` **71/71**;
`1FA/1FB/1FE/1FF` **50/111/96/96**; `200/201`
**67/85**; `2D0/2D1` **60/60**; `2DD/2DE` **80/0**;
`2EF` **0**. A prior more optimistic selected context from F737
**must not** be transported into this newer full-source parent.

The same freshly built source independently rechecks the entire
**943-B original after-RET switch DATA**, all **156 physical
native/source `DIR32` original jump-table targets** as real
native/compiled decoded x86 instruction starts, and **319/319
other original sparse dispatch bytes**. These are independently
owned DATA, not accepted authored whole game CODE.

```bash
scripts/repo-python scripts/verify-fighter-later-early-f743.py
scripts/repo-python scripts/verify-fighter-repeat-shot-f740.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The full real compiler TU, COFF object, temporary PDB and original
field comparison receipt reside under ignored
`.analysis/f743-fighter-later-early/` for further genuine native
hypotheses. Zero new callable game function CODE is accepted;
**964 complete exact authored functions/863,913 native CODE B
(43.77% reviewed)** is unchanged. No mass cold replay.
