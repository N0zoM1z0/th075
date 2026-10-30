# F808 — Complete native action49 restores the scripted giant's default GPR register phase

**Positive original gameplay source integration and physical
compiler-context proof; enclosing giant is still NOT exact.**

Pinned Japanese TH075 v1.11 native `005214B0`
is an independently authored **46,755-B** fighter
state advance with **901 separate after-RET
switch DATA B**. F806 restored its real 46-B/
16-x86 default and shared getter, plus the genuine
four native early jumps from action0/2/4/5.
F807 then integrated complete original
`0x46/0x47/0x48` motion cases with that shared
tail in one 7,817-B/1,920-x86 whole C++ source.
Those genuinely added cases altered the compiler's
later register phase, producing four extra
non-relocation GPR operand differences in the
native default guard.

F808 reconstructs **the very next native action
`0x49`**, as bounded by the original packed
second-switch dense slots 14/15 at
`00522C78..00522DD5`: **350
original CODE B /99 x86 /15 independently
verified typed PE/COFF fields**.
The original game's distinct action behavior
includes true 32-bit position/velocity bit
copies, actual `+0xF00/+0xF02`
trajectory counters, two physical
`FLD/FUCOMPP` status comparisons, original
`__ftol2` integer conversions and the
state-3/state-2 transition callbacks.
The code is natural C++ from tracked
`probes/FighterTrajectoryLanding49F607.inc`
with no fake temporaries or register patches.

## All 27 original actions in ONE newly compiled parent

The tracked F808 verifier first regenerates
and revalidates F607's entire source for
the target's **27 complete original actions**
(original 26 plus native 0x49). It then
injects F806's real default and shared getter
source and cold-compiles the entire affected
original-shaped fighter C++ parent using
pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`.

The complete generated callable source increases
from **7,817 CODE B /1,920 x86** in F807 to
**8,152 CODE B /2,017 x86** in F808,
while **all earlier 26 native action bodies**,
original PE call/global field identities and
901B afterRET jump DATA are rechecked
in the same NEW compiled COFF object.
The original game is 46,755 CODE B;
remaining diagnostic placeholder actions
mean the whole native function is not matched.

## A meaningful GPR result from restoring TRUE preceding gameplay

The native original `0052CB25..0052CB52`
default/shared getter remains **46 B/16 x86**
and has three genuine zero-addend PE
calls `0040FA30/0040FAC0/0040FA30`.
Its four native action0/2/4/5
shared-getter entry JMPs also retain
their precise positions within each full
original case.

**Unlike F807, F808 naturally restores the
original default guard GPR rotation.**
The native sequence
`MOVSX EDX,AX` /
`MOV EAX,[EBP-10h]` /
`MOVSX ECX,[EAX+70h]` /
`CMP EDX,ECX`
is now compiler-generated with precisely
the same registers and instruction widths.
No artificial GPR assignments were introduced;
only actual source action `0x49` was added
earlier in the same function. This
independently demonstrates source context
affecting downstream VC7.1 register allocation.

The **only four remaining non-relocation
tail differences** are real saved-this
EBP displacement bytes at suffix-relative
`2/13/26/36`:
original `EBP-0x10`,
current incomplete parent `EBP-4`.
They are never masked as exact.
The whole giant has other missing actions
and is not officially accepted.

To independently reproduce the selected
27-action source plus the genuine shared
tail, without corpus-wide cold replay:

```bash
scripts/repo-python scripts/verify-scripted-fighter-landing-shared-f808.py
```

Fresh selected F607 source generation and one
additional whole-parent compilation are
performed. COFF, native PE diagnostics and
verified JSON remain preserved under
`.analysis/f808-scripted-landing/`.
No new independently callable authored
whole-function unit or CODE bytes credited.
