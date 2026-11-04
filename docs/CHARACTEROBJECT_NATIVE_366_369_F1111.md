# F1111 — Four additional original 2,214B homing actions 0x366..0x369, 1,808 x86 with complete native widths and GPR roles

TH075 Japanese v1.11 has one genuine original 81,539-byte
`CharacterObject::Advance` callable at `0050A580`, with 17,435 x86
instructions and 567 genuine afterRET switch DATA bytes. These
FOUR independent physical native switch-case intervals are now
represented by natural C++ in the incomplete **one original-shaped
whole parent**, not four newly exact whole functions.

| Genuine original game action | Physical original PE CODE interval | Original B/x86 | Real spawned object |
| --- | --- | ---: | --- |
| `0x366` | `00518865..0051910B` | **2,214 /452** | `0x33E` |
| `0x367` | `0051910B..005199B1` | **2,214 /452** | `0x340` |
| `0x368` | `005199B1..0051A257` | **2,214 /452** | `0x342` |
| `0x369` | `0051A257..0051AAFD` | **2,214 /452** | `0x344` |
| **Four original native game-state interiors** | — | **8,856 /1,808** | Four distinct physical original IDs |

All original Japanese PE state interiors have exactly **452
ordered x86 mnemonics and identical ordered instruction widths**,
but each has its own original native register phase, physical
scratch slots, native parent-state caller and literal sprite object.
The selected source reuses the genuine C++ homing/angle-control
logic independently established for [F1110 native 0x365](CHARACTEROBJECT_NATIVE_365_F1110.md)
using **four distinct C++ original switch entries**, with literal
`0x33E/0x340/0x342/0x344` respectively. It does not merge the
physical original switch indices into one alias or falsely credit a
separate original callable.

The real C++ reproduces original four arena bounds and native
parent `(0x31,0x96)`/stage guard; real two-shot 0x3E4 and extra
parent-conditional 0x3E3; genuine motion, opacity and countdown
initialization; signed angle +0xDA/+0xDC pursuit toward real
**grandparent** X/Y through actual `00483300`, real CRT float-to-
integer `006406AC` and signed 2°/±180°/±360° wrapping; native
`0040FB70` movement; per-frame real `0x33E/340/342/344`
projectile via `00453A70`; native random `00455580(0,4)` and
original **double-precision constants `00658A20/00657D00`** for
scale initialization; authentic status/hit fades, sprite alpha and
`0040FA30` animation completion.

## Original real PE evidence — not whole-function exact credit

All four cases were *cold compiled inside the ONE entire currently
selected VC7.1 normal original-shaped C++ parent* and independently
compared instruction-by-instruction to the SHA-pinned original PE.
The physical COFF REL32/DIR32 fields were resolved using each
original x86 instruction ordinal plus the original **field byte
position, relocation kind and original PE-calculated destination**,
not by symbol name alone. All original scalar immediate operands
were also checked to catch wrong sprite IDs while mnemonics/PE
external calls remain the same.

| Native original property | All four handlers |
| --- | ---: |
| **Correct original x86 mnemonic positions** | **1,808/1,808** |
| **Original native GPR operand roles** | **1,808/1,808** |
| **Native instruction width positions** | **1,808/1,808** |
| **Correct physical original call/global PE fields** | **128/128** |
| **Real non-relocated scalar immediate positions** | **312/312** |
| **Original inner CODE lengths** | **8,856/8,856 B** |

Unlike some preceding actual native game states, these four have
**no remaining instruction width/GPR mismatches within their own
case interiors**. That does **not** prove entire original 81KB
CODE, branch displacements, stack temporary lifetimes or physical
COFF source offsets are byte-identical: the partial source still
uses a different EBP stack frame and omits other real game states.
No exact-original bytes were newly accepted.

The live `verify-characterobject-current-recovered-f1068.py`
now verifies **65 strict original game-state interiors** totaling
**62,415 original native CODE B /13,386 original x86**,
**13,386/13,386 original mnemonic and GPR-role matches**,
**1,008/1,008 original physical PE external fields** and
**2,455 native scalar-immediate positions**. Another seven
source-backed inner cases remain **PROVISIONAL** due to GPR debt.
Current partial C++ whole emits **67,237 CODE B /14,386 x86** and
native original 567B afterRET jump/sparse DATA, versus original
whole **81,539B /17,435 x86**. The source EBP-0xC8, ESP 0x2F4
frame remains different from original saved-this EBP-0xAC,
ESP 0x3A0; the real original callable is still **NONEXACT**.

Reproduce only the affected whole-partial C++ game parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Genuine original PE, all normal native C++/COFF/PDB/compiler
artifacts and original per-case physical external fields are
retained under ignored `.analysis/f1111-native366369/` and
`.analysis/f1068-boss-live-all-native/`. No mass 979-unit cold replay.
