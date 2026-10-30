# F718 — complete original fighter 2DD/2DE source in one native-shaped giant

**New meaningful original-native C++ source, still whole-function NONEXACT.**
Target: user-supplied Japanese TH075 v1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original authored `00543210` boss owns **58,294 CODE bytes and 943
separately owned after-RET switch DATA bytes**. Its action case interiors
are **not** separate authored game functions; none is independently
credited to the whole-function match ledger.

## Two entire original physical handlers recovered as normal C++

| Native action | Actual pinned PE original interval | Native entire CODE | Native x86 | Original typed PE/COFF fields | New whole-parent VC7.1 source |
| --- | --- | ---: | ---: | ---: | --- |
| `0x2DD` | `0054EAAB`–`0054ED53` | **680 B** | **189** | **19** | **680 B/189 x86/19 fields**, original mnemonic/width geometry |
| `0x2DE` | `0054ED53`–`0054EFE7` | **660 B** | **189** | **18** | **660 B/189 x86/18 fields**, original mnemonic/width geometry |
| **Both authentic native actions** | | **1,340 B** | **378** | **37** | **1,340 B/378 x86/37 physical fields** |

New tracked [`FighterDoubleVolleyF718.inc`](../probes/FighterDoubleVolleyF718.inc)
recreates original actual gameplay rather than a dummy case stub:

**2DD** has genuine storm `00454BC0(3,4,0xFF0000)`, stage-zero
latch `+0xF00` and original state/flag resets; a 10.0f vertical
velocity, 30.0f horizontal velocity and 0.45f drag. Its distinct
stage-4–8 descending physics subtracts actual `[006581E0]`
from X speed, applies Y drag, clamps to the native `[00657480]`
limit and checks original `this+0x48` ground contact. It then calls
`0040FB40(9)`, clears Y and invokes `00453E20`. A separate stage-0–3
body emits both true kind `0x329` and `0x387` projectile shots via
`00453A70`, with signed direction × 62 and original `[00657868]`
float Y offsets. Original completion and random 100–180 counter are
retained, and original stage-4 repeated auxiliary `0` followed by
stage-9 auxiliary `7` are source-backed.

**2DE** has native storm setup and distinct state `+0x80=99`;
late stage-15–24 falling physics subtracts the original
`[00659090]` X speed and compares the real `[00657CF8]`
clamp, then invokes auxiliary `25` and resets original state on
floor collision. On animation completion it seeds the actual
`+0x516` timer by random 100–180 minus 30×difficulty. At stage
7 it fires the actual **raw-X/raw-Y kind `0x3C`** via native
`00453C80`, prepares action 11 and initializes 9.0f vertical,
20.0f horizontal and 0.8f drag. Stages 7–15 emit kind `0x329`
float-X/Y shots; stage 16 repeats action 12 up to three times via
`+0xF00`; stage 25 invokes native auxiliary `23`.

Both were compiled with the pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` profile **inside the entire
original-shaped 58KB boss source parent**, not as isolated callable
functions. Every original action's 189 instruction mnemonic AND
instruction-width positions match. Every authentic typed original
`REL32`/`DIR32` PE field is rechecked **at the original source x86
ordinal**, with exact native target, actual compiled source symbol,
zero addend and physically owning instruction. Their genuine native
shared exit and next `2DF` physical case boundary are attested.
There are no manual target-byte grafts, artificial saved registers,
inert stack locals or truncated case comparisons.

## Actual GPR and native EBP negatives, never masked

* `2DD`: **80 real nonfield GPR/CFG operand positions** differ;
  source x87 integer-to-float conversion operands at original
  x86 `101–102` and `122–123` use **`EBP−0xC0/−0xC4`** instead
  of original native **`EBP−0x1A0/−0x1A4`**. The six-byte original
  wide `MOV/FILD` operands match in width, **not in bytes**.
* `2DE`: **zero normalized nonfield GPR/CFG role differences**
  after the real independently attested saved-`this` mapping, but
  its original x86 `147–148` signed-direction float conversion
  scratch is **`EBP−0x1A8`**, versus source **`EBP−0xC8`**.
  This is a real two-instruction operand mismatch, so **2DE is
  still NONSTRICT**, not native byte-exact. The original entire
  boss saves `this` at `EBP−0x44` while this C++ compiler parent
  uses **`EBP−0x28`** (one original-shaped prologue store and
  3,014 genuine compiler reloads).

This is a useful finding about **natural compiler lifetime pressure**:
adding real action bodies restores all native opcode/width positions
without faking the original EBP layout. Neither one correct native
opcode nor 37 matching original typed fields proves a full
58KB original game function match.

## Same-parent regression verification and reproducibility

Tracked [`verify-fighter-double-volley-f718.py`](../scripts/verify-fighter-double-volley-f718.py)
freshly builds **one selected original-shaped giant VC7.1 TU**,
rereads both original physical native PE handlers and complete COFF
field ownership, then rechecks the older reconstructed `2DB/2DC`,
`2D0/2D1`, `2BF/2C4`, all five genuine `259–25D` handlers, and
later original `2F8–302` cases in the **SAME compiler parent**.
The previous 26 context-strict nonterminal original cases remain
strict in this selected parent, while `2EF`, `2F0` and `2F1` have
**144, 175 and 170** real GPR-role mismatches; their earlier strict
status from other, less-complete source contexts is **not reused**.
The **entire original independent 943-byte after-RET switch DATA**
is compared again in this same new parent.

`verify-fighter-complex-movement-f714-f715.py` now explicitly
supports a **real following 2DD** rather than assuming its old
source placeholder; its previous isolated 2DB/2DC context still
uses the old default check. No unverified source case is given
whole-function exact credit, and no 943-unit mass cold replay ran.

```bash
scripts/repo-python scripts/verify-fighter-double-volley-f718.py
scripts/repo-python scripts/verify-fighter-complex-movement-f714-f715.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Generated native-shaped whole parent source, real OBJ/PDB, compiler
log and structured PE/COFF summary are preserved locally (Git-ignored)
under `.analysis/f718-fighter-double-volley/`. Tracked normal C++
source and verifier remain portable. The enclosing giant remains
whole-NONEXACT. The **accepted whole authored function ledger stays
943 original functions /862,726 original CODE bytes (43.71%
reviewed)**; there is **no** newly accepted complete-function CODE.
