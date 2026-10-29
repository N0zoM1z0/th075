# F672 — original 259–25D native barrage C++ source and genuine EBP scratch negative

Pinned user-supplied original Japanese TH075 v1.11
`resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is **five complete real native action case bodies** inside the
original 58,294-CODE-byte fighter giant `00543210`, with its 943
separately owned after-RET switch DATA bytes. The normal C++ source
reproduces all original instruction counts and non-field register
roles, but **does not match real original stack-local EBP slots**:
these cases are **NONSTRICT**, do not count as any new exact case,
never mind new independently exact whole game functions.

## Original physical entire native case intervals and source

| Native action | Original physical CODE interval | Native x86 instructions | Original internal CODE B | New compiler CODE B | True typed PE/COFF fields |
| --- | --- | ---: | ---: | ---: | ---: |
| `0x259` | `0054CC18`–`0054CEF5` | 210 | **733** | 685 | 20 |
| `0x25A` | `0054CEF5`–`0054CFBB` | 60 | 198 | 192 | 6 |
| `0x25B` | `0054CFBB`–`0054D081` | 60 | 198 | 192 | 6 |
| `0x25C` | `0054D081`–`0054D12B` | 52 | 170 | 164 | 5 |
| `0x25D` | `0054D12B`–`0054D1D5` | 52 | 170 | 164 | 5 |
| **Five new source-backed, but NONSTRICT, interiors** | | **434** | **1,469** | **1,397** | **42** |

The ordinary source
[`FighterEightShotAndFollowF672.inc`](../probes/FighterEightShotAndFollowF672.inc)
reconstructs the entire real **eight-shot native action 259**: at
stage/frame zero it enables control `+0x7C=1` and calls actual reset
`00453E20`; completion compares original action `0040FA30` to native
short `+0x70` and triggers `0040FAC0(0)`; native stage 5/frame 0
calls real animation `0046D000(250)` and launches **eight separate
resource shots**, alternating genuine original kind `0x321/0x322`
in each of four pairs. Source sets actual float state `+0x314`
to `−10.0f`, `+10.0f`, `−6.0f`, `+6.0f` across the groups.
The first two pairs use signed direction `+0x66 *40` and original
y globals `006591F8` and `00658264`; the last two use signed
direction `*75` with y globals `0065908C` and `00658268`.
Original X adds actual float `+0x44`; Y adds float member `+0x48`
through genuinely observed PE global `DIR32` references; every
stage and original action ends at the true shared native epilogue.

The original `25A/25B` additionally apply real float scale at
`00657F74` to **both** original horizontal `+0x50` and vertical
`+0x54` movement at stage/frame zero, enabling genuine DWORD
`+0x7C=1`. Stage 5 spawns kind `0x32B` or `0x32D` using signed side
`*100` and actual native y globals `00657888`/`00658264`;
completion sets original action 9. For both, the ordinary C++ identity
lvalue form `(*(&POS54))*g_BounceScaleAt00657F74` is essential to
obtain original **`FLD` member before `FMUL` global** x87 order:
a naïve normal `POS54*global` source instead swaps their locations,
so even its native instruction widths differ.
Original `25C/25D` instead reset the stage-zero control via actual
`00453E20`, spawn native kind `0x332` or `0x333` with signed side
`*70` and real float y global `0065928C` at stage 5, then finish
through original `0040FAC0(0)`. The original native `25D` physical
case is only **170 bytes**: its next true physical body is `0x2BC`,
not the shared default handler `0x25E`.

## Genuine blocker — twenty-four real local slot/width errors

All 434 original native x86 mnemonic/GPR/x87/CFG roles and all
**42 genuine source COFF `REL32`/`DIR32` fields** individually match
the actual original PE target, compiler symbol, physical operand
ordinal and zero addend in a newly compiled *complete* giant. But
**twenty-four** actual `MOV [EBP],reg; FILD [EBP]` instruction operands
are nonexact: eight conversion pairs in `259`, plus one pair in each
of the four following cases. The meaningful original integer-to-float
scratch locations are:

| Native action | Original physical EBP temporaries | Compiled normal C++ temporaries |
| --- | --- | --- |
| `0x259` | `−0x124`, `−0x128`, `−0x12C`, `−0x130`, `−0x134`, `−0x138`, `−0x13C`, `−0x140` | `−0x3C`, `−0x40`, `−0x44`, `−0x48`, `−0x4C`, `−0x50`, `−0x54`, `−0x58` |
| `0x25A` | `−0x144` | `−0x5C` |
| `0x25B` | `−0x148` | `−0x60` |
| `0x25C` | `−0x14C` | `−0x64` |
| `0x25D` | `−0x150` | `−0x68` |

Each original `MOV` and `FILD` uses a six-byte wide displacement;
its compiler counterpart uses three bytes, accounting for **72
fewer emitted CODE bytes** across five cases (1,397 versus 1,469).
The old F598 normalized comparison erases all EBP stack offsets;
using it alone would be a false strict match. F672 *separately*
checks the original and compiler **raw physical EBP operands**, allows
only the original actual saved-receiver `EBP−0x44` becoming new
`EBP−8`, and **requires exactly these 24 original-local negative
ordinals**, with all other non-field operand roles matching.
No artificial previous local variable declarations, ABI misdirection,
manual machine-code grafts or unbounded relocation masks were added.
The missing historical parent-stack ownership is real unresolved work.

## Source-context integration and targeted full-parent regression checks

[`verify-fighter-eight-shot-and-follow-f672.py`](../scripts/verify-fighter-eight-shot-and-follow-f672.py)
rebuilds the complete original-shaped fighter giant under pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, and independently rechecks
all 25 preceding strict original case interiors and the complete
original action `258` four-shot **EBP-negative**. It proves all five
new real physical bounds/byte widths/ref counts/COFF field ownership,
then verifies the original **large 2BC ground-wave case stays
strict** in this **same newly compiled parent source context** even
with all five real 259–25D bodies inserted. Original 186/18A/18B
EBP-negative cases and the **entire independent after-RET compressed
switch DATA** also remain reverified. The selected parent remains
whole-NONEXACT. Its `2EF` source is *not* included in this particular
variant, and prior F666 demonstrated that combining additional
source contexts may change VC7.1 register allocation.

F672 therefore adds **zero new strict original native case bodies**,
and does not alter F598–F674's research **595 strict original case
interiors /161,569 original internal CODE bytes**. It supplies
**1,469 additional original CODE bytes /434 x86 /42 physical fields
of source-backed but NONSTRICT cases** for recovery of whole
parent stack lifetime. Formal authored exact coverage remains
**943 independently whole functions /862,726 original CODE bytes
(43.71% reviewed)**.

```bash
scripts/repo-python scripts/verify-fighter-eight-shot-and-follow-f672.py
scripts/repo-python scripts/verify-fighter-ground-wave-f673.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Selected compiler CPP/COFF/PDB and linked source field receipts are
retained under ignored `.analysis/f672-fighter-eight-shot-source/`;
original semantic trials under ignored `.analysis/f672-eight-shot/`.
No all-unit 943-function cold replay, original EXE patch, fake locals,
or external Oracle whole-function acceptance was performed.
