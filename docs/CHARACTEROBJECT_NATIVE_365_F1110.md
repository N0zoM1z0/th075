# F1110 — Real native 0x365, full 2,214B/452-x86 homing action with all original widths, registers and PE fields

The SHA-pinned Japanese TH075 v1.11 original contains **one**
`CharacterObject::Advance` at `0050A580` (**81,539 original callable
CODE B /17,435 native x86** plus 567 separately owned afterRET
switch DATA B). F1110 reconstructs genuine original action `0x365`
in the selected ordinary VC7.1 C++ parent, in its actual physical
native PE interval **00517FBF..00518865**. It is not a new callable
or separately accepted whole-function exact unit.

## Original game behavior and real parent/target ownership

The 365 action first performs the original four independently signed
x87 arena boundary comparisons at `0065925C/00659258/006583B4/
00658374` and expires through actual `0045B830` when outside. The
native parent action range `(0x31,0x96)`, with own stage below 2,
triggers an original **two-shot 0x3E4** loop and conditional extra
`0x3E3` projectile via the genuine parent's `00453A70`.

At initial stage/frame zero it resets motion with `0040FBB0`,
initializes all four alpha bytes, both scale floats to 1.0f,
collision status, signed countdown +0x80=1, signed timer +0xD8=60,
direction +0xDA/0xDC/0xDE=0. In later stages it increments timer
by 2, computes the actual target angle using **one original CRT
atan2 at `00483300`** on the *grandparent's native position minus
actor position*, original `00657888` target Y offset and signed
facing; divides by original `00657828` and converts the float to a
signed WORD through actual `006406AC`. The steering angle at +0xDC
moves in two-degree increments with the native **±180/±360 wrap
policy** and **two independent post-update comparisons**, rather
than an incorrect mutually exclusive `if/else`.

In stages 0/1 it calls `0040FB70` with signed +0xDC angle and real
velocity `float(+0xD8)*006578C0 + 00657CF8`, then spawns original
**`0x33C`** projectile through the parent, picks native random
`00455580(0,4)-2`, and derives both scale floats from real **64-bit
`00658A20` and `00657D00`** constants. It advances actual +0xD8
counter, adjusts actor+0xC8 angle using real target Y and original
`00657480`, moves signed-facing X and subtracts real Y velocity.
Native status+0x7C and +0x80 control the original stage-1 hit
transition `0040FB40(2)`, motion stop and scale reset to 2.5f.
Later stages fade the actual scale pair by original `006598A4`,
subtract unsigned alpha by 25 and either expire through
`0045B830` or advance native action on actual `0040FA30` completion.

## Actual native physical measurement

The source compiled **inside the current entire 81KB partial C++
parent**, not as a cropped standalone test. A freshly independently
read original game PE, normal VC7.1 OBJ/COFF symbol table and
Capstone disassembly establish:

| Native original `0x365` dimension | Pinned original | Natural C++ source |
| --- | ---: | ---: |
| Original game interval CODE B | **2,214** | **2,214** |
| Ordered x86 instructions | **452** | **452/452 mnemonic matches** |
| Native GPR operand roles | **452** | **452/452** |
| Native original instruction widths | **452** | **452/452** |
| Actual original external PE call/global fields | **32** | **32/32** physical positions/kinds/targets |
| Native scalar immediate positions | **78** | **78/78** |
| Original object ID, x87 helper, CRT conversion | `0x33C`, `00483300`, `006406AC` | correct |

Although all 452 original instruction **widths**, native mnemonic
positions, scalar immediate values and registers match, the selected
source is still one incomplete 81KB parent: original whole-function
branches, compiler stack scratch owners, field bytes and original
physical source CODE offset are not exact. This result **must not**
be called 2,214 newly accepted whole-function bytes or an exact
standalone 0x365 function.

The tracked `scripts/verify-characterobject-current-recovered-f1068.py`
now compiles only that one affected selected whole C++ parent and
checks **61 strictly native GPR-shaped original inner cases**:
**53,559 original native CODE B /11,578 original x86**,
**11,578/11,578 original mnemonics and GPR roles**, **880/880
real original physical PE external fields**, **2,143 verified
original scalar immediate values**, plus the original 92 DIR32
postRET switch-label partitions and 199 literal sparse data bytes.
Seven other genuinely implemented native cases remain separately
**PROVISIONAL** because their GPR allocation is still wrong.
The current partial C++ parent is **58,441 CODE B /12,586 x86**;
original is **81,539 CODE B /17,435 x86**. **The original whole
callable is NONEXACT, with zero newly accepted exact game CODE**.

Reproduce only this affected game parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Complete actual VC7.1 C++/COFF/PDB and original PE comparison receipts
are in ignored `.analysis/f1110-native365/` and
`.analysis/f1068-boss-live-all-native/`. No 979-unit mass replay.
