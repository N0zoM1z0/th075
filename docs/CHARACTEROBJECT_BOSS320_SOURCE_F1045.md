# F1044–F1045 — Real `0x320` gameplay in the 81KB CharacterObject Boss

The original pinned Japanese TH075 v1.11 CharacterObject Advance at
`0050A580` is a **single NONEXACT** game function: 81,539 callable
CODE bytes / 17,435 x86 instructions, followed by 567 separate sparse
switch DATA bytes. Its one native compressed switch dispatch covers 199
source action values, 92 physical DIR32 jump entries and 199 physical
byte-index entries. The older F569 full-source diagnostic emitted only
synthetic `g_FighterProbeMarker` writes for **all** handlers; these were
never original gameplay or independently callable functions.

F1044 reconstructed the **real original action `0x320`** at
`0050A658..0050A80F`: 439 native CODE bytes / 91 x86 instructions,
with six genuine PE call/global fields. The new whole function
source `probes/CharacterObjectWhole0050A580F1044.cpp` carries the real
`0x320` gameplay body, not a marker, while retaining clearly labeled
marker prototypes for the other, unimplemented state handlers. The
real `0x320` source performs the original parent-action/stage gate,
updates X from signed facing and borrowed parent X, initializes
motion/colors on stage zero, applies signed-short stage/frame guards,
advances vertical motion/gravity, clamps its velocity, and performs
native action/auxiliary transitions. Original calls used:

- `0045B830` — expired/invalid parent handler
- `0040FBB0` — motion setup
- `0065747C` and `0065782C` — original float constants
- `0040FA30` and `0040FB40` — actor action getter and setter

The source was not taken from decompiler output: its ordered real
x86 instructions, field widths, calls and floating-point behavior were
read independently from the pinned original PE. Ordinary VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` source grammars were compiled as
the **whole CharacterObject prototype**, always retaining the 92-entry
sparse table and 199 original index-map bytes.

## Genuine source and native code-generation improvements

Initially the natural `0x320` C++ produced a 335B/91-x86 inner region
with only **84/91** ordered original mnemonics and **83/91** GPR-role
positions. Tests of real parent X value categories and float operation
order found a much better expression using the independently reviewed
`F1037_POSITION(PARENT).xPosition + float(facing * 66)`.
Typing the actual Y position and motion as
`F1037_POSITION(this).yPosition = F1037_POSITION(this).yPosition +
F1037_MOTION(this).yMotion` corrected the remaining two misplaced
`MOV/FLD` instruction orders, without any ABI deception or padding.

| Complete native `0x320` case vs selected source | Before | F1045 |
| --- | ---: | ---: |
| Source complete inner x86 | 91 | **91** |
| Original matching ordered mnemonics | 84 | **91** |
| Original matching GPR roles | 83 | **91** |
| Original matching instruction widths | 56 | **57** |
| Actual original external field target/ordinal alignment | 6/6 | **6/6** |
| Original inner CODE / current prototype CODE | 439/335B | 439/335B |

The **remaining 34 wrong width positions** largely arise from the
incomplete parent source's EBP−4 saved receiver, versus the native
whole 81KB EBP−0xAC receiver/frame 0x3A0 and its live stack locals.
A matching x86 mnemonic stream **cannot** be promoted to byte-level
exactness or original CODE credit. The complete 81KB function is still
largely unimplemented; `0x320` is not a separate original callable.

The tracked `verify-characterobject-boss320-f1044.py` performs fresh
native PE reads and whole-prototype VC7.1 builds for the original
and 32 genuine source control variants; it checks physical original
call/global targets, original case instruction ordinals and operand
roles, the full source jump-table equality partitions and all 199
real sparse-map bytes. It independently reconstructs the selected
source, checks 91/91 native codegen roles, and verifies the tracked
C++ emits the same full prototype COFF image as the selected natural
source variant. Generated source/OBJ/PDB and PE proof remain under
ignored `.analysis/f1044-object320-grammars/` and
`.analysis/f1044-object-320/`.

Reproduce only this affected full-source research object:

    scripts/repo-python scripts/verify-characterobject-boss320-f1044.py

This is **source recovery for a previously missing large-game state**,
not a completed 81KB original callable, not independent 439B exact
CODE credit, not a new accepted authored function and not a 979-unit
cold replay. The true whole Boss still needs all other handlers,
frame/local-lifetime reconstruction, physical relocation offsets and
full callable matching.
