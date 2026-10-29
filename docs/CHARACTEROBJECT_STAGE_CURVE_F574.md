# F574 — original native CharacterObject stage-curve and collision actions 0x32B/0x32C

**Original Japanese TH075 1.11 source/VC7.1 compiler evidence, NOT an
accepted exact original whole giant.** Original executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This extends the same already tracked natural C++
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
which previously recovered ten native game actions in F572 and x87
`0x32A` in F573. The entire **33,293-byte original `004EBDA0` giant**
and its **438 original after-RET switch DATA bytes** are SHA/physical
entry-verified from the pinned Japanese PE before source compilation.

## Actual action `0x32B`: real two-pass integer-to-FPU stage curve

The complete original native 112-instruction / **422-byte** case
initializes actor stage 0 when `+0x62/+0x64 == 0`, resets via
`0040FBB0(0,0,0)`, zeros velocity, motion, and gameplay counters,
sets frame color bytes to `0xFF`, and calls original parent
`00453E60` with actual 5.0f floating effect intensity.

Each tick then separately adjusts `this+0x1C` and `this+0x20` by
ordinary C++ stage curve:

```cpp
F32(0x1C) = (float)(5 - S16(0x64)) * gCurveAt0065972C
          * (S16(0x64) < 5) + gStepAt00658044 + F32(0x1C);
```

This is **not a guessed pure floating polynomial**: original x86
uses actual signed-short to integer subtraction, `FILD`, global
`FMUL`, `SETL` on signed frame state, local `FIMUL` and true
`FADD` constant and member in sequence, twice, to reproduce its
**112 original x86 instructions / 422 bytes**. Higher stage checks
perform genuine byte-state fade, actual native `0045B830` reset,
and current-action query at `0040FA30`.

All 112 instructions, real GPR/x87/relative-branch order and physical
x86 lengths match the newly generated normal C++ source strictly,
including **9 true typed COFF call/global fields** at their native
physical instruction ordinals.

## Actual action `0x32C`: collision and effect-spawn loop

The next independent case is **176 native x86 instructions / 635
whole original internal CODE bytes**. It checks native parent state
`+0x60` within `(0x31,0x96)`, resets and spawns five parent effects
`0x3E4`, handles native `+0xEFA` saturation/`0x3E3` effect,
then switches to the native actor's stage-0 initialization:
`0040FBB0(0,0,0)`, `0040FB70` raw C8-field bits with float 15.0f,
real `+0x1C/+0x20` scaling, and four byte-color stores.

The natural source restores signed direction-byte `this+0x66`
motion and native x87 `this+0x44/+0x48` updates. On its native
`stage < 2` contact guard it raises `this+0x30`, compares the
true x87 floating collision threshold at original global `0065782C`,
then issues original `00453D40(4)`, two effect spawns `0x32B` and
`0x32D` via parent `00453A70`, original action switch
`0040FAC0(0x33B)` and four genuine zero motion stores.
The normal branch queries `0040FA30` and conditionally performs
`0040FB40(1)`.

The correctly typed source caller passes the native `this+0xC8`
float **raw bits** as an integer `0040FB70` argument (not a floating
point value conversion). Passing float directly would add native
`FLD/FSTP`, produce 177/638 instead of the real **176/635**.
The observed ABI is real; exact original method/class names remain
provisional.

**This case still has one native-order exception.** Original
instructions 114 and 115 are `MOV EAX,[saved_this]` followed by
`FLD DWORD PTR [EDX+0x48]`; the new source naturally emits these
two **independent read-only instructions in the opposite order**.
Both memory operands are read-only, EDX is not written by MOV EAX,
and there is no intervening branch, side effect or COFF field.
The tracked checker independently permits exactly this adjacent
read-read swap, and requires the other 174 instructions/operands,
real x87 and control graph to match. This is **source-semantic
rather than exact x86 machine order**; no compiler-byte padding or
patched instructions have been inserted.

## Full source/COFF original validation for 13 game actions

[The F574 tracked native case verifier](../scripts/verify-characterobject-following-actions-f574.py)
compiles only ONE affected native VC7.1 C++ source under
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, independently rechecks the
previous ten original strict F572 case bodies, plus F573's
248-instruction action `0x32A` with its previously proven read-only
swap, then verifies these two new actual action cases and all true
physical call/global COFF fields. No ignored C++/OBJ prior hypothesis
is assumed correct. All original physical sparse/dense jump-label
slots and the whole original CODE attestation remain mandatory.

| Original native action family | Native x86 instructions | Actual inner original CODE | True COFF references | C++ order |
| --- | ---: | ---: | ---: | --- |
| `0x320..0x326` (seven leaves) | 21 | 91 B | 7 | Strict |
| `0x327..0x329` (three boss policies) | 813 | 2,996 B | 54 | Strict |
| `0x32A` (six x87 equality gates) | 248 | 932 B | 19 | One independent read-only swap |
| **`0x32B`** (integer/FPU motion curve) | **112** | **422 B** | **9** | **Strict** |
| **`0x32C`** (collision/effects) | **176** | **635 B** | **13** | One independent read-only swap |
| **Total** | **1,370** | **5,076 B** | **102** | 11 strict cases, 2 limited equivalences |

All **102/102 true original per-case typed `REL32`/`DIR32`
COFF fields** match real native original PE target addresses,
original physical ordinal, C++ source symbol, type and zero addend.
The whole native original jump table retains **60 real zero-addend
physical DWORD COFF labels**, default/duplicate handler partitions,
**198 byte-identical original sparse index bytes** and **438 separate
original after-RET DATA bytes** (not CODE credit).

### Reproduce with affected-only native C++ compilation

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-following-actions-f574.py
# Independent regressions of previously recovered cases under the same source:
scripts/repo-python scripts/verify-characterobject-extended-action-f573.py
scripts/repo-python scripts/verify-characterobject-action-family-f572.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

All original-only native disassembly, failed source-expression/ABI
hypotheses and compilation logs are preserved under ignored
`.analysis/f574-characterobject-actions/`, with new F574 COFF/PDB/
summary under `.analysis/f574-following-action-source/`.
No independent original 112-/176-byte function exists: these
**5,076 original internal CODE bytes remain inside the still
unmatched 33,293-byte giant `004EBDA0`.** Original nominal owner,
full C++ locals and all later actions remain outstanding; no
accepted whole/split CODE/DATA credit, all-unit cold replay or
external Factory/Oracle receipt.

## F575 follow-up: two further genuine native fade case bodies

The tracked natural C++ source now additionally contains actions
`0x32D` (66 original instructions /229 CODE bytes) and `0x32E`
(70/282). F574's strict first-thirteen-action verification is
replayed with this extended source, and the new
[F575 native source verifier](CHARACTEROBJECT_FADE_ACTIONS_F575.md)
validates all 15 original physical case bodies. Action0x32F genuinely
maps to the original default handler, so the next actual 0x330
handler bounds the native 0x32E whole code body. Both added
fade cases match strict x86 instruction order. The giant remains
whole-function nonexact and receives no new exact coverage.

## F596 native collision source-order correction

The original read-only `MOV`/`FLD` source-order discrepancy
recorded above has now been **fully eliminated by an ordinary
VC7.1 C++ original-owner lvalue expression** in real action
`0x32C`. The exact native original original-PE machine
instructions now occur in the original order, byte-for-byte,
with no ASM, temporary stack filler, or source byte graft.
Historic original PE mismatch records remain valid for their
historical source versions, not the current source. The
[F596 whole giant source-order study](CHARACTEROBJECT_NATIVE_COLLISION_ORDER_F596.md)
rechecks 8,789 whole original x86 instruction ordinals and
reduces actual original nonrelocation whole CODE+DATA byte
differences from 155 to **137**. Original giant still nonexact.
