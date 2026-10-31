# F1015 — Native 248B Scene virtual destructor, three authentic free-pointer owner orders

The SHA-pinned Japanese TH075 v1.11 authored original
Scene virtual destructor at **0043B0B0..0043B1A8**
is one complete **248 CODE B/75 x86** function, including
its EH prologue and base virtual destructor. It is
not an internal Boss state or a collection of leaf callables.

The original PE physically has **12 typed COFF fields**:
the native EH bindings, vtable/global fields, game state
setter, native texture deleting destructor 00425460,
three distinct CRT free calls 00640F15, base destructor
00431F40, and native EH unwind. The five important original
local EBP operands are independently observed at specific
ordered native x86 positions:

| Real used C++ value | Original physical EBP slot | Current closest compiled slot |
| --- | --- | --- |
| texture receiver temporary | −0x14 | **−0x20** |
| deleting destructor receiver | −0x10 | **−0x1C** |
| scene member+0x4C passed to free | −0x18 | **−0x18** |
| member+0x50 passed to free | −0x1C | **−0x14** |
| member+0x54 passed to free | −0x20 | **−0x10** |

The previous F889 mixed aggregate tests explored genuine
two-plus-one or one-plus-two cleanup field owner groups.
They did not establish that putting a COMPLETE three-pointer
cleanup struct before the texture delete, or reversing its
real used member declaration order, could fix the original
texture receiver slots. F1015 tests that distinct hypothesis
without adding any fake locals.

The [pinned original source verifier](../scripts/verify-scene-natural-declaration-order-f1015.py)
freshly builds **13 ENTIRE ordinary VC7.1 /GX** virtual
destructors from the tracked
[scene original-shaped source](../probes/BattleSceneTextureDeleteF589.cpp):
the actual full three-field structure's natural,
reversed and two rotated member orders, each with the
declaration at whole-function entry, before the original
game clock branch, and immediately before the texture
delete, plus the unchanged baseline. All three released
pointer values are genuinely read from their original
scene member offsets and passed to free; no unused padding,
byte grafts, assembler or manually specified registers.

Original checks encompass the entire 248B/75 x86 body,
every real call/field's original physical PE type,
destination, zero addend and COFF symbol multiset.
All 13 compiles preserve **248B/75 x86/12 original PE
field offsets and all native ordered mnemonics/widths**.

| Genuine full-source variant | True original nonrelocation equal bytes | Native texture/delete slots |
| --- | ---: | --- |
| Original baseline | **191/200** | −0x20/−0x1C, wrong |
| Natural 3-member order, 3 declaration positions | **191/200** | −0x20/−0x1C, wrong |
| Reversed or rotated 3-member order, 9 sources | **189/200** | −0x20/−0x1C, wrong |

The declaration position has no effect on VC7.1's
texture/delete temporary slots; member order only rotates
which of the three genuine free-pointer slots is used.
Therefore this real three-member grouping cannot explain
the original −0x14/−0x10 texture/deleter allocation. It
does not rule out a different historical source lifetime
or owner interface, and it does not make the Scene
destructor exact.

Reproduce this bounded original one-function matrix:

    scripts/repo-python scripts/verify-scene-natural-declaration-order-f1015.py

The 13 natural C++ sources, serial compiler logs,
object/PDB files and exact per-byte original PE receipts
are retained under ignored
.analysis/f1015-scene-slot-rotation/.

**No newly accepted original callable CODE B/functions.
No 979-unit corpus cold replay.**
