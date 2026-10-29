# F590 — complete original CharacterObject 0x370/0x371/0x384 guarded-state actions

**Genuine original Japanese TH075 v1.11 whole PE vs fresh normal
VC7.1 C++ source proof, not exact complete giant CODE.** Pinned
original PE SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The *entire* original CharacterObject boss `004EBDA0` has **33,293
whole CODE bytes** and **438 separate after-RET sparse-switch DATA
bytes**. F590 recompiles only ONE normal C++ `Advance()` TU containing
all previously original-backed F572–F588 action sources, plus three
more *whole physically bounded original game-action cases*. Original
later `0x385` and beyond remain deliberately test-marker C++ stores,
not falsely reconstructed game logic.

## Authentic native nondefault boundary: `0x34F` → `0x370` → `0x371` → `0x384`

The real native compressed index/handler jump table, not convenient
source case numbering, proves the next three physical original game
actions. The gap after `0x371` consists of **shared-default
aliases**, not actual distinct source/CODE bodies. F590 verifies
original target address and the *entire contiguous physical x86
case body* for all three:

| Real original game action | Whole native x86 instructions | Original inner CODE bytes (uncredited) | PE-grounded typed COFF records |
| --- | ---: | ---: | ---: |
| **`0x370`** | **79** | **286 B** | **7** |
| **`0x371`** | **44** | **156 B** | **4** |
| **`0x384`** | **128** | **473 B** | **14** |
| **New source this round** | **251** | **915 B** | **25** |

### Action `0x370`: parent-state signed angle placement and two real x87 scales

The native `P16(+0x60)==0x133` branch initializes its actor position
using signed facing byte `+0x66` times original **260** via actual
`IMUL/FILD`, added to parent x position `+0x44`. The y position
uses parent y `+0x48` plus the independently verified real float
absolute global **`006590A0`** (not copied from the earlier
`006590A8/006590AC` original parent modes). Its true stage-zero
frame resets transform via `0040FBB0(0,0,0)`, writes both scales
1.0f and colors FF.

On every frame it adds original floating global **`006583FC`**
to x scale and *multiplies* y scale by original global
**`00659090`**: the same original constant destination used as
an `FSUB` elsewhere, but here it is a physical **`FMUL`**.
It subtracts 20 from unsigned opacity only if still **strictly
greater than 20**, otherwise resets via original `0045B830`,
and also resets when native `0040FA30` matches actor `+0x70`.
The genuine C++ expression preloads parent x before the original
signed `IMUL/FILD` conversion, preserving all native GPR/x87/branch
roles and exact individual x86 lengths.

### Action `0x371`: a separate 44-instruction fade and sprite update

This physically different whole original action initializes
**0.85f** scales (`0x3F59999A` twice) and full color FF, writes
sprite short `+0x1A=0x4E2`, and the original offset float
**`+0x28=-65.0f`** (bits `0xC2820000`). It subtracts real
float global **`00659728`** from actor `+0x30` (native x87
`FSUB`), then invokes original `0040FA30`/`0045B830` reset.
The source precisely matches **44 whole native x86 instructions/
156 original CODE bytes** and all four authentic typed COFF fields.

### Action `0x384`: actual stage-motion contact with global selected-effect guard

The complete native original tests the parent signed short
`+0x3A0 >0` and otherwise resets via `0045B830`. Stage zero
calls original `0040FBB0`, initializes scale/color and uses two
separate native x87 `FMUL` references to real float constant
**`006590B4`** for actor velocities from fields `+0xC8/+0xCC`.
Then it subtracts actual **`00658058`**, updates direction-based
position and performs signed stage `<2` motion growth via
**`00657CC0`**. The original float contact condition uses real
**`0065782C`** with native `FCOMP/TEST AH,0x41/JP`.

On contact, the actual original parent spawns **effect `0x388`**
via `00453A70`, emits actual `00453D40(8)`, changes action to
**`0x385`** using `0040FAC0` and, if original signed global byte
**`006714D0 >1`**, changes action again to **`0x38E`**.
It zeros the four original motion fields and exits; the noncontact
path uses real `0040FA30`/`0040FB40(1)`.

**One important relocation distinction:** ordinary C++ emits a
zero-linked COFF `MOVSX ECX,BYTE PTR [0]` at genuine ordinal
**102**, while original PE has `MOVSX ECX,BYTE PTR [006714D0]`.
The actual source COFF carries an independently checked zero-addend
**`DIR32` field** at this instruction, with symbol
`gGlobalActorCountAt006714D0` resolving to the exact original
physical PE global. F590 permits **only this single verified
absolute relocation placeholder** in the instruction-operand
comparison. It does not pretend its encoded zero field is machine
byte-identical before linking or ignore any unrelated register/
branch difference.

## Entire original case/COFF proof and coverage limits

Tracked ordinary C++:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
New original-only target source checker:
[`scripts/verify-characterobject-guarded-stages-f590.py`](../scripts/verify-characterobject-guarded-stages-f590.py).

It reads full original original Japanese 33K giant CODE and complete
native compressed dense/sparse switch, **fresh-compiles ONE affected
normal VC7.1 TU** using pinned `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`,
rechecks all **43 prior real complete original action bodies**, then
checks the *whole* 79/44/128-instruction new cases, authentic
original PE native branch targets, EAX/ECX/EDX/x87 instruction
roles, individual opcode lengths and **25 physical zero-addend
`REL32`/`DIR32` source references** at their correct real original
instruction ordinal, including the unique signed-byte global
`006714D0` and all original actor methods.

The verifier also requires the entire original **60 physical
zero-addend `DIR32` jump-label DWORD COFF references**, preserved
repeated/default handler equivalence partitions, **198 literal
byte-identical compressed index bytes** and **438 separately owned
after-RET DATA layout bytes**. Neither DATA nor external CRT is
counted as original authored CODE.

| One incomplete native whole original giant, containing these complete gameplay subranges | Original x86 source instruction roles | Original internal CODE bytes (NO independent exact credit) | Actual typed PE/COFF call/global fields |
| --- | ---: | ---: | ---: |
| Previous 43 actual source cases F572–F588 | 6,562 | 24,673 B | 449 |
| New `0x370/371/384` cases | **251** | **915 B** | **25** |
| **Total 46 real complete game-action bodies** | **6,813** | **25,588 B** | **474** |

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-guarded-stages-f590.py
scripts/repo-python scripts/verify-characterobject-three-late-actions-f588.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

All selected source/OBJ/PDB/compiler and native-original typed COFF
summary files remain in ignored `.analysis/f590-characterobject-guarded-source/`,
with native disassemblies and first full-case C++ comparisons in
`.analysis/f590-characterobject-state-next/`.
The **entire 33,293 original CODE-byte giant is still NONEXACT**;
its 25,588 authentic internal native CODE bytes are not 46
separately exact native original functions. No standalone split/whole
CODE or DATA credit, no all-unit cold replay and no external
Factory/Oracle acceptance receipt.
