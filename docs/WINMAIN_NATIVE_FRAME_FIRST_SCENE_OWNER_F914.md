# F914/F915 — WinMain actual native stack triad recovered, but not whole exact

Original SHA-pinned Japanese TH075 1.11 PE at **00602A60**:
**2,987 complete callable CODE bytes / 654 x86** and a separate
15-entry/60-byte afterRET switch jump table. Source-generated function
is not a whole match; no original byte credit is added.

Previous F911 selected source emitted 2,984 B /654 x86 and 645/654
original instruction widths, with HWND/currentScene/path physically
**EBP-0x180/-0x17C/-0x178** instead of original
**EBP-0x188/-0x184/-0x180**, and a source frame 0x274 rather
than original 0x278.

F914 tests **18 genuinely used field-owner variations plus the
baseline whole source**. The first Scene4 pointer is either a
`GameScenesF455*` or a derived typed `Scene4F455*` member of
the same live context at every possible member boundary. Every
candidate compiles the **entire original-shaped /GX- WinMain** and
calls the original constructors at native ordinal positions.
Source classes are partial borrowed interfaces, not claimed historical
complete game classes. The original PE's physical slots, not old
source placement assumptions, determine the comparison.

Placing the real first-constructed-scene pointer **immediately
after the actual 260-byte `path`** yields:

| Whole-function/owner observation | Prior F911 | New F914 |
| --- | ---: | ---: |
| Compiler CODE / original CODE | 2984 / 2987 | **2978 / 2987** |
| Source/original instructions | 654 / 654 | 654 / 654 |
| Original frame `SUB ESP` | 0x274 | **0x278 exact** |
| Source HWND / original EBP | -0x180 / -0x188 | **-0x188 / -0x188** |
| Source currentScene / original EBP | -0x17C / -0x184 | **-0x184 / -0x184** |
| Source path / original EBP | -0x178 / -0x180 | **-0x180 / -0x180** |
| Matching original instruction widths | **645/654** | **643/654** |
| Correct new-size/ctor mappings | 16/16 | 16/16 |
| Correct native case-index / jump-target ordinal | 15/15 | 15/15 |

This is an **improvement in three real physical stack slots
and the actual frame**, but **not an overall machine-byte
improvement**: the actual source first-scene pointer uses EBP-0x7C,
while original ordinal281/282 use EBP-0x19C. That shortens both
source MOV instructions by 3 bytes apiece, creating two extra wrong
widths. Native widths wrong remain
`[10,92,122,149,170,190,281,282,635,637,643]`.
The source's graphics and archive/data RAII owner lifetimes are
also still incorrect. No padding, inert member or ABI trick is
permitted to conceal those differences.

F915 independently tried **24 actual typed
first-scene pointer declaration locations**, as local variables,
plus six actual member placements. Moving a standalone used
variable's declaration did not restore native stack ownership;
the derived-vs-base member pointer changed no original native
instruction width. These controls constrain a real historical
object-lifetime hypothesis rather than guessing the size difference
comes from mere spelling.

Tracked complete alternative:
`probes/WinMainNativeFirstSceneOwnerF914.cpp`.
Targeted normal compiler/original PE checker:

    scripts/repo-python scripts/verify-winmain-native-first-scene-owner-f914.py

Original function, 16 native allocation/constructor call pairs,
all 15 physically resolved afterRET DIR32 case targets and the
entire original 654-x86 ordinal comparison are revalidated.
Ignored serial source/OBJ/PDB/full-PE receipts survive under
`.analysis/f914-winmain-first-scene-owner/`,
`.analysis/f915-winmain-first-scene-placement/` and
`.analysis/f914-winmain-first-scene-proof/`.
**WinMain is NONEXACT; F911 remains the overall best width match.**
No all-unit cold replay.
