# F890 — Original 2C2 complete 2,274B, 608 x86, fifty real PE fields

Original pinned Japanese TH075 v1.11 fighter at 005214B0
has 46,755 callable original CODE B and five packed
original afterRET jump DATA tables (901 separately owned B).

The actual original native physical handler for switch action
2C2 at 0052A468..0052AD49 has **2,274 complete inner CODE B,
608 original x86 and 50 physically typed PE call/global
fields**. It is NOT a separately callable original function.

This reconstruction restores the complete real stage handler:
stage0 resets short+F00/+F02/+F04, dword+7C and stage+80;
stage>9 applies actual single-precision gravity global6581E0,
tests the native height intersection, resets and sets action2C3
with an early enclosing-giant exit. Stage9 one-shot fires
sprite34C using actual borrowed owner float Y and prepares
animation E. Current action completion invokes aux10.

The enormous middle stage<9/frame0 branch really has EIGHT
separately executed short+F00 phases 0..7. Each phase uses
actual sprite34A/329 pairs, signed facing-byte arithmetic,
multiple truly observed associated-owner X/Y coordinates,
actual global offsets, float/int source parameter types and
native contact fields. Original X expressions naturally use
the actual borrowed owner float X left-lvalue BEFORE signed
facing multiplication, generating the correct x87 operand
ordering and native FILD scratch slots.

The state8 one-shot native branch is **INSIDE** the enclosing
stage<9/frame0 condition, and tests short+F04, resets F00=1,
increments true short+F04, invokes aux1 and fires both real
stage0 projectiles. Stage9/frame0 resets physical motion and
copies the actual associated owner's X field. The full
normal VC7.1 source naturally allocates THIRTEEN actual
integer-to-float FILD temporaries in the exact original
EBP -0xD4 through -0x104 native scratch sequence.
There are no inert locals, manual assembler, source-level
padding, cropped native extents or forced register assignments.

A new normal VC7.1 complete affected fighter emits
**39,312 callable CODE B/11,069 x86**, up from F888
37,053B/10,463 x86. Its 2C2 source has exactly
**2,274 B/608 x86** with all original instruction
mnemonics, widths, positions and ALL 50 original physical
PE operands at their actual original locations, types,
zero addends and original executable/global target
addresses. Only FOUR real nonrelocation bytes remain
wrong: +175/+176 and +2270/+2271, belonging to the two
original far whole-fighter epilogue JMP displacement
fields at native x86 ordinals44 and607. The complete
original 46,755B fighter is still NONEXACT.

## Two independently compiled full-parent false-source controls

An earlier plausible source placed the stage8 one-shot
outside its native stage<9/frame0 outer guard. It emitted
the SAME 2,274B/608-x86/50-field geometry but changed
the actual native branch destinations. The verifier
independently compiles this false full source and rejects
its genuine original nonrelocation wrong offsets
[175,176,334,335,349,350,2270,2271].
The corrected native-source parent only has
[175,176,2270,2271].

Another genuinely used C++ source computed facing*100
before accessing its real owner float X, making the
original x87 instruction order/width incorrect even
when full total bytes match. This false full source
is also independently compiled and rejected.

The same current complete VC7.1 parent physically
rechecks all **65 earlier original native source-backed
game case interiors**, including the original 1FD
one-byte CMP defect, 252/254 shifted physical PE
fields, original 259 physical successor 2BC, and
2BF and 2C0/2C1 native near-byte-exact cases.
It also verifies all five original packed 901B
afterRET DATA tables and the native shared 46B
getter's **34/34 matching nonrelocation bytes**
plus three actual original PE calls.

Reproduce ONLY this affected full native giant:

    scripts/repo-python scripts/verify-scripted-fighter-full2c2-f890.py

Whole C++, normal VC7.1 COFF/PDB, native/false
parent controls and strict Japanese PE JSON
receipt are in ignored .analysis/f890-scripted-2c2/.
No all-unit cold replay, no unearned split-case
or afterRET DATA accepted whole callable CODE.
