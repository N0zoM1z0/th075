# F1087 — Original 1,216B state 0x34E, native parent combinations and eight 0x362 shots

**Historical F1087 checkpoint:** the live parent now also restores authentic [F1088 0x34F](CHARACTEROBJECT_NATIVE_34F_F1088.md). Previous 45-state/31,430B partial source figures below are for the earlier checkpoint, while original 34E 18/18 PE targets remain verified.

The pinned Japanese TH075 1.11 original contains ONE authored
`CharacterObject::Advance` at `0050A580` (81,539 native original
CODE B /17,435 x86), plus separate authentic 567B sparse-switch
DATA. The C++ parent is still incomplete and NONEXACT; original
switch interiors are not independent original whole callables.

Original game case `0x34E` is physically
**005136C8..00513B88 = 1,216 original CODE B /263 x86**.
Restored real C++ resets native motion, scale, status and alpha,
retains the genuine signed +0xD8 timer 140, then computes actual
parent-relative X/Y movement, native 0065989C/00657F74/0065835C
float effects and real parent/target health. It invokes actual
`0040FB70`, preserves genuine parent stage `0x2C1/2` checks,
and controls timer increments and stage-specific expiry/action.

Unlike previously reconstructed `0x34D`, its original stage-zero
parent triggers are **`0x195/4`, `0x1F4/14`, `0x1F5/14`**, with a
real **eight-iteration game loop**. That loop writes genuine parent
+0x314 orientation `float(shot*45)` and emits physical **`0x362`
projectiles** through actual `00453A70`, not `0x361`.
The source also preserves the original fade, native stage-one
`0x2C1/3` transition, `0040FA30` completion, and stage-two
parent+0x36C adjustment through real 006592A4.

Before adopting the C++ grammar, **all 263 native opcode ordinals,
physical original parent value checks and PE calls were independently
read**. The original differs from the adjacent `0x34D` by 10
native instruction ordinals for its third real parent action/phase
condition. The selected source has the corresponding true C++
condition rather than guessed dummy branches or register bindings.

| Original state `0x34E` | Current whole-parent C++ result |
| --- | ---: |
| Actual original CODE/x86 | **1,216B /263** |
| Generated normal C++ inner CODE/x86 | **1,004B /263** |
| Native ordered mnemonics | **263/263** |
| Original GPR roles | **263/263** |
| Native instruction widths matching | 193/263 |
| Original physically positioned PE nonlocal fields | **18/18** |
| Original 8 × action 0x362 / 45° counter | correct |

`verify-characterobject-current-recovered-f1068.py` cold builds
**only the one affected whole partial C++** under normal pinned
VC7.1 and independently verifies the SHA-pinned entire Japanese
original executable CODE, all authentic original **92 DIR32
jump-target equivalence classes and 199 sparse index bytes**, plus
each original case x86 ordinal, GPR role, real original physical
REL32/DIR32 PE destinations and nonrelocated scalar immediate.

The live original PE proof now covers **45 genuine original game
states**, **38,192 native original state CODE B /8,302 original
x86**, **8,302/8,302 mnemonic and GPR roles**,
**656/656 true native original physical PE targets**, and
**1,542/1,542 nonrelocated scalar immediate positions**.
The selected incomplete C++ emits **31,430 CODE B /8,440 x86**
versus authentic original 81,539B/17,435 x86, with saved receiver
EBP-0x6C and stack frame ESP 0x1B4 versus original EBP-0xAC,
ESP 0x3A0. Many real original cases and stack/branch widths
remain missing. **Whole original callable NONEXACT; newly accepted
original whole-function exact CODE = 0B.**

Reproduce only the changed one-switch game parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Historical VC7.1 C++/COFF/PDB, actual native original PE receipts
and previous stage verifiers are retained under ignored
`.analysis/f1087-native34e/` and `.analysis/f1068-boss-live-all-native/`.
No compiler hacks, dummy locals, byte grafts or 979-unit replay.
