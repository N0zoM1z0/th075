# F767 — original fighter 2F9 angle-storm x87 evaluation order restored

**Whole-original-parent semantic C++ reconstruction, not new byte-exact callable
game CODE.** The target is the original Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The complete original game-authored `00543210` fighter function consists of
**58,294 native CODE bytes** and **943 separately owned after-RET switch
DATA bytes**. Its substantial action `0x2F9`, at
`00550475..005509CC`, is **1,367 whole native CODE bytes, 381 x86
instructions and 34 real zero-addend PE/COFF relocation fields**.
It is not a separately callable authored original function.

## Physical original float evaluation, not historical source assumptions

F684/F706 had recovered the 2F9 state, four entire authentic x87
projectile-spawn calls, two original angle calculations, original
`__ftol2` conversions, staged motion/loop controls and the native 34
physical PE-targeted fields. In the newest full F764 giant source,
2F9 was already **1,367 B/381 x86**, but eight actual native
instruction-order/mnemonic positions were wrong and **265**
nonrelocation/non-tail machine bytes differed. Full geometric length
alone did not imply original C++ grammar or even the same evaluation
order.

The original PE's two genuine `CalculateAngleAt483300` invocations
read the **actual opponent X at observed `+0x44`** and the actor's
actual `+0x44` float member. Both original Y computations consume
opponent `+0x48` float storage relative to the actor's `POS48`.
The source
[`FighterAngleStormTypedF767.inc`](../probes/FighterAngleStormTypedF767.inc)
uses independently observed borrowed X member views and meaningful
read-only lvalues for the actual opponent Y/actor Y subtraction.
These are genuinely used game fields, not fabricated stack locals.

Eleven independently rebuilt entire 58KB original-shaped VC7.1 C++
parent source alternatives varied the real actor/opponent X expression
ownership, the separately observed opponent Y lvalue and combined
X/Y source evaluation. Examples of native results measured with their
entire original PE action extents:

| Actual C++ angle-operand model | Original 2F9 source geometry | Wrong original mnemonics | Wrong nonfield/nontail bytes |
| --- | --- | ---: | ---: |
| Former full F764 source | 1,367 B /381 x86 /34 fields | **8** | **265** |
| Typed opponent X only | 1,367 B /381 x86 /34 fields | 6 | 256 |
| Typed both X coordinates | 1,367 B /381 x86 /34 fields | 4 | 257 |
| True read-only opponent and actor Y lvalues | 1,367 B /381 x86 /34 fields | 4 | 257 |
| **Typed both X + read-only both Y** | **1,367 B /381 x86 /34 fields** | **0** | **249** |

The actor X typed-only control was a useful negative: it generated only
1,343 B/375 x86 and failed to preserve native physical geometry.
The accepted **research** source restores **all 381 original ordered
instruction mnemonics and exact widths**, including the genuine
`MOV/FLD/FSUB` ordering around both original angle calculations.
It improves native **nonfield differences 265→249**, but **249
genuine machine bytes remain wrong**, largely due to the original
EAX/ECX/EDX/EBP operand ownership in this and other state handlers.
None is hidden by normalizing registers, suppressing discrepancies,
patching target bytes or adding synthetic unused locals. No
`structural-exact` or whole-callable-function `exact` is claimed.

## Actual PE/COFF and enclosing-function regression checks

The tracked one-owner verifier
[`scripts/verify-fighter-angle-storm-typed-f767.py`](../scripts/verify-fighter-angle-storm-typed-f767.py)
regenerates the actual complete fighter from the F759–F764 tracked
source, inserting the newly recovered 2F9 action, then **fresh-compiles
only ONE affected original-shaped VC7.1 giant** using
`/Od /Ob0 /Gy /GR- /GX /GS /Zi`. It rereads the pinned
original PE and verifies the entire 1,367-byte original case,
all 381 actual x86 opcode/size positions, all **34 original
DIR32/REL32 physical COFF fields** with original owner, zero
addend, source symbol and independently decoded native PE target.
It explicitly asserts the **249 remaining nonfield wrong byte
positions**, and refuses to promote the case to exact CODE.

The same full parent revalidates prior C8–CE, 1F6/1F7/1F8 and
2DB native complete game interiors; it also verifies that 2FA's
**971 native CODE B /279 original x86 /31 genuine fields** still
have **156 wrong real operand bytes** despite complete opcode/width
geometry. The original 943-byte after-RET switch DATA remain
independently owned, with **156 valid physical DIR32 label references**
and **319/319 other sparse-map bytes** identical; none is new callable
CODE.

```bash
scripts/repo-python scripts/verify-fighter-angle-storm-typed-f767.py
# 2F9: 1367 native B /381 x86 /34 PE fields, ZERO opcode/width errors
# 249 genuine nonfield operand bytes still wrong (was 265)
# Only one affected whole giant rebuilt, no all-unit cold replay
```

The complete generated fighter is **58,261 CODE bytes** versus the
original **58,294**, a remaining 33-byte whole-function size
deficit in addition to genuine wrong register and parent-tail branch
bytes. Thus the whole fighter remains NONEXACT, and formal
accepted authored whole-function matching remains **973 functions /
865,627 native CODE B** (43.86% reviewed). Generated CPP, COFF,
PDB, trial logs and final receipts are under ignored local
`.analysis/f767-fighter-2f9-crosscase/` and
`.analysis/f767-fighter-angle-storm-whole/`. No full 973-unit
cold replay, no original EXE edit and no independent split-case credit.
