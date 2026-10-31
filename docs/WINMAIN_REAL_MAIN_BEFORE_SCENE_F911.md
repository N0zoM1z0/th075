# F911 — A real HWND before scene/path repairs eight whole-WinMain instruction widths

The pinned original TH075 1.11 Japanese `00602A60`
is **2,987 complete callable CODE bytes / 654 x86**, with
15 independent postRET switch TABLE entries / 60 DATA bytes.
F910 previously established native physical switch source order
`4,0,1,2,3,5,…,14`, all 16 original scene allocation sizes
and constructor target identities, and all fifteen original
switch-entry-to-physical-instruction ordinal mappings. Nothing
in F911 reassigns original scene sizes, alters target bytes or
claims independent switch-case exactness.

## Why the C++ layout matters

The original has real, independently observed contiguous stack
values:

- Graphics object used at **EBP-0x189**, constructed before
  window initialization.
- Actual `HWND main` at **EBP-0x188**.
- Actual `currentScene` pointer at **EBP-0x184**.
- Actual 260-byte `path` begins **EBP-0x180**.

In F910, the source had `currentScene; path[260];
WNDCLASSEXA win; HWND main; ...` and the compiler put the
used HWND at **EBP-0x48**, generating short
`[EBP+disp8]` instead of the original long
`[EBP+disp32]` at EIGHT genuine native instruction
ordinals 114,115,130,133,192,207,219,229.

F911 tests the live owner relationship rather than
inventing padding. It moves the real, repeatedly used
`HWND main` field **before** `currentScene; path[260]`
inside one actual source runtime state group. All field
loads/stores still operate on genuine values. The original
physical HWND/sceneptr/path relation now shares the
right **order**, though not yet the correct **absolute**
EBP positions.

32 complete original-shaped normal VC7.1 source variants
crossed real HWND placement with naturally used
`WNDCLASSEXA`, `HANDLE readyEvent` and
`directoryEnd` member versus standalone owners.
All 32 compiled successfully to complete 654-mnemonic,
173-COFF-record functions with original-shaped 60-B data;
they remain preserved locally in ignored
`.analysis/f911-winmain-real-owner-layout/`.
The best four used main-before-scene and readyEvent
as a real aggregate field; independent `win` or
`directoryEnd` scope changes produced no further
original CODE-width gain.

The selected tracked complete C++ variant
[`WinMainNativeOwnerOrderF911.cpp`](../probes/WinMainNativeOwnerOrderF911.cpp)
and its replay compare as follows:

| Entire original-shaped normal /GX- WinMain | F910 | F911 |
| --- | ---: | ---: |
| Generated callable CODE B | 2,960 | **2,984** |
| Generated x86 instructions | 654 | 654 |
| Original matching ordered mnemonic instructions | 654 | 654 |
| **Native matching x86 instruction widths** | **637/654** | **645/654** |
| Physically correct original scene allocation/constructor pairs | 16/16 | 16/16 |
| Correct original switch index/physical ordinal relocations | 15/15 | 15/15 |
| Generated COFF references / separately generated switch DATA B | 173 / 60 | 173 / 60 |
| Source actual HWND EBP store | -0x48 | **-0x180** (native -0x188) |

The eight original short-versus-long HWND machine-width
mismatches are repaired by a real owner rearrangement,
bringing complete generated CODE to within **three bytes**
of the original 2,987. This is a **geometric improvement,
NOT three bytes away from native exactness**: many operand
bytes, GPR assignments, physical PE relocation field
offsets and original frame lifetime positions still differ.

Precisely nine native x86 width ordinals remain wrong:
**10,92,122,149,170,190,635,637,643**.
Five are the actual graphics object address width:
original EBP-0x189, compiler EBP-9. Four are the
source's real two cleanup/local addresses around
EBP-0x181/-0x182 that the original places near
EBP-0x35/-0x36. The original scene/path/HWND
positions still differ by eight EBP bytes and are NOT
byte-identical. Recover natural original game object
lifetime and allocation order next, rather than
arbitrary fake stack fillers.

Reproduce **only this WinMain whole source**, not the
979 previously accepted units:

    scripts/repo-python scripts/verify-winmain-native-owner-order-f911.py

Targeted replay freshly builds both F910 and F911,
then verifies all original x86 ordinal widths,
all original 16 scene-ctor allocation sizes/COFF
symbol identities and all original fifteen original
afterRET jump-table physical ordinal destinations.
Full OBJ/PDB and original-game PE receipts remain
in ignored `.analysis/f911-winmain-real-owner-order-replay/`.
No newly accepted independently authored whole game
CODE; the WinMain remains NONEXACT.
