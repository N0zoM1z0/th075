# F921/F927 — A 20-byte native firstScene/HWND gap is not four arbitrary real members

**Original pinned Japanese TH075 v1.11** independently
authored WinMain at 00602A60: **2,987 complete callable
CODE B/654 x86**, with 15 separately owned afterRET
scene jump-table words (60 DATA bytes).

The real physical original stack observes a first-constructed
scene pointer at **EBP-0x19C**, followed 20 bytes later by
**HWND -0x188**, **currentScene -0x184**, and the actual
260-byte module-path buffer starting at **-0x180**.
Their numerical proximity does **not** establish a single
historical source aggregate, nor justify inventing 16 bytes
of invisible local fields.

F914 previously made concrete progress in an alternative full
source lifetime: it reproduced the **native 0x278 frame and
HWND/scene/path trio** by making the genuinely used firstScene
pointer a member *after* the real path. But that model put
the firstScene value into a short-offset EBP-0x7C local
rather than its genuine native EBP-0x19C, introducing two
extra width mismatches. F911 remains better in total
native x86 width positions (645/654).

## New original source hypothesis and 66 whole VC7.1 compiles

To test whether the missing 20-byte firstScene/HWND spacing
corresponds to other **real used C++ values**, F921 generated
**66 whole WinMain** original-shaped sources. They combine
the live first Scene4 pointer with subsets/permutations of
the following original WinMain operands, placed in member
order ahead of the HWND/currentScene/path trio:

- Actually used `HANDLE readyEvent`, the real event
  later passed to ConfigureEvent, WaitForSingleObject
  and CloseHandle.
- Actually used `char* directoryEnd`, the pointer returned
  by the native module pathname's last backslash search.
- Actual calculated `int windowWidth` and `int windowHeight`
  passed to native CreateWindowExA.

**Every member is actually read/written by original game
logic**; no inert padding, fake locals, bogus ABI or target
byte graft. The sources retain all native 16 scene allocations,
archive/graphics/sound/input lifetimes and return paths.
All 66 compiler runs succeed under normal pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. All have the
original 654 ordered x86 mnemonics, 173 original-shaped
COFF field records, and a 60B afterRET table.

The physical comparison is decisive: **none of the 66
sources restores all four real EBP values**, or even any
of the four ordinal-specific desired stack locations.
Widening real source aggregates instead moves HWND/scene
and path too far toward the shallow frame, and introduces
actual native opcode-width differences; 66 genuinely compiled
whole-function results remain in ignored local
`.analysis/f921-winmain-real-owner-gap/research.json`.

Representative whole-function results:

| Full natural source model | Whole emitted CODE B | Original x86 widths matching | All four native EBP roles |
| --- | ---: | ---: | ---: |
| F911 original source control | 2,984 | **645/654** | 0/4 |
| FirstScene member only | 2,984 | **645/654** | 0/4 |
| FirstScene + event + directory gap | 3,005 | 638/654 | 0/4 |
| FirstScene + all four actually used gap fields | 3,017 | 634/654 | 0/4 |

The tracked bounded verifier
[`verify-winmain-used-gap-owners-f927.py`](../scripts/verify-winmain-used-gap-owners-f927.py)
regenerates these four **entire real WinMain** representatives
from tracked F911 C++, serially recompiles all four, and
independently reads the pinned native PE. It additionally
checks every original **654 x86 ordinal**, all **16 physically
positioned scene allocation sizes and actual constructor COFF
identities**, all **15 genuine afterRET DIR32 case-index to
physical-instruction-ordinal targets**, and the actual
frame and original source EBP stack slots.

    scripts/repo-python scripts/verify-winmain-used-gap-owners-f927.py

Reproducible source/COFF/PDB/compiler outputs:
`.analysis/f927-winmain-used-gap-proof/`.
Full experimental 66-source matrix, logs and original
PE comparisons: `.analysis/f921-winmain-real-owner-gap/`.
Both folders are intentionally ignored research, not exact
adoption manifests.

**Interpretation:** the simple hypothesis that four
real HWND-related 32-bit source members naturally account
for the observed native 20-byte gap has been disproven
for the tested VC7.1 source/lifetime model. It does **not**
disprove a different genuine object lifetime or a
compiler-generated temp of original semantics, and it
does not undo the separately established F914 EBP
triad recovery. The whole 2,987-byte WinMain remains
**NONEXACT**; zero new whole callable CODE accepted and
no all-unit cold replay.
