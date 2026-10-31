# F910 — WinMain's real scene switch is case-4-first, NOT numeric order

The pinned Japanese TH075 v1.11 native **00602A60 WinMain**
is one **2,987-byte / 654-instruction callable function**
and a separate **60-byte afterRET, fifteen-entry** jump table
at original PE **0060360B**. It remains **NONEXACT**.

## Native evidence: source order and dispatch index differ

The original jump-table entries physically resolve to native
instruction ordinals:

| Dispatch value | Real original physical case x86 ordinal |
| --- | ---: |
| 0 | 383 |
| 1 | 399 |
| 2 | 415 |
| 3 | 431 |
| 4 | **367 (FIRST physical body)** |
| 5–14 | 447, 463, 479, 495, 511, 527, 543, 559, 575, 591 |

The original first scene allocated *before the loop* is the
same real scene type as case 4: both actually allocate **0x10 bytes**
and call the physical constructor **00425490**. Native switch
case 0 is the **0x11C-byte** allocation followed by
constructor **0043AD10**, case 1 is 0x10/004251F0,
case 2 is 0x3C/0043A020 and case 3 is 0xF4/00432EA0.
Those four source class sizes in the earlier F904 probe
were ALREADY correctly assigned to their actual numeric
scene indices.

The prior F904 normal compiler instead placed source case 0
**first**, then cases 1,2,3,4, whereas the original compiler
places **case 4 first**, then 0,1,2,3,5,...14. Comparing
ordinals without checking the table created misleading
new-size differences. We explicitly rejected the alternative
hypothesis of reassigning class sizes: doing so would corrupt
the original native scene-index-to-constructor relationship.

## Correction to an entire natural C++ source

The new tracked whole-function source
[`WinMainNativeSceneAllocationsF910.cpp`](../probes/WinMainNativeSceneAllocationsF910.cpp)
takes the previously best actual /GX- source with
both real 16-bit scene states grouped and moves ONLY the
complete real `case 4` body ahead of `case 0`, without
changing any scene class size, actual constructor,
memory allocation, destructor, message-loop or function
return. It is ordinary C++ under pinned VC7.1, **not**
manual assembly, artificial padding or isolated-case byte
matching.

Two serial fresh complete VC7.1 `/Od /Ob0 /Gy /GR-
/GX- /GS /Zi` compiles, compared against the ORIGINAL
PE each time:

| Verified whole WinMain property | Older numeric-order F904 | Corrected F910 |
| --- | ---: | ---: |
| Generated callable CODE B | 2,960 | 2,960 |
| Generated x86 instructions | 654 | 654 |
| Original mnemonic ordinals matching | 654 | 654 |
| **Original x86 width ordinals matching** | **633 / 654** | **637 / 654** |
| Original physical operator-new sizes at 16 original sites | 11 / 16 | **16 / 16** |
| Original scene-index constructor identities at 16 sites | 11 / 16 | **16 / 16** |
| Native table case-index to physical instruction ordinal mapping | 10 / 15 | **15 / 15** |
| Source COFF records | 173 | 173 |
| AfterRET switch table source shape | 60 B / 15 DIR32 local relocations | 60 B / 15 DIR32 local relocations |

The original 0x10/0x11C/0x3C/0xF4 allocation
opcode-width mismatches at ordinals 367/383/415/431
are gone. All five formerly wrong original physical
allocation operands are corrected. The **source-to-native
constructor assignment for all sixteen** sites, including
the initial logo scene, agrees with independently read
original native constructor CALL targets. The original
postRET 15-entry table also now maps each dispatch
value to the same physical **instruction ordinal** as
its source COFF local relocation, independently of
absolute generated CODE displacements.

**Still not an exact 2,987-byte function.** F910 emits
2,960 CODE bytes, with **17 other original x86 width
differences** and incorrect original frame/owner offsets.
Matching symbol class names, mnemonic ordinals and
logical local jump targets is not physical relocation
or complete native CODE equality. No original whole
function is accepted or added to `config/matches.csv`.

Reproduce ONLY the affected WinMain sources, never
the 979-unit cold replay:

    scripts/repo-python scripts/verify-winmain-native-scene-allocations-f910.py

The fresh complete compiler inputs, OBJ/PDB, logs
and full original-PE-backed sixteen-ctor/15-jump
receipts live under ignored
`.analysis/f910-winmain-native-scenes/`.
