# F615 — thirty complete native WinMain object-lifetime/layout controls

**Author-classified whole `00602A60` original Japanese TH075 1.11
GameApplication startup; NO exact reconstruction accepted.**
Target executable SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is not a tiny isolated probe: it compiles the entire original-
shaped function with its 15-scene switch, real COM/Win32 message loop,
authentic archive/game-data and four game-client destructor lifetimes,
not a disconnected narrow subrange. The original complete PE owns
**2,987 CODE bytes /654 x86 instructions /123 actual calls**,
followed by a **separately owned 15-DWORD, 60-byte after-RET jump table**.
The original frame is `SUB ESP,0x278`, and the original full function
returns with `RET 0x10`. The independently original-byte-verified
`GameApplication::WindowCallback` following the table is a *different*
already accepted whole function, not part of this one.

## Rechecked original physical source problem

The best F528 original-shaped native C++ lifecycle had already
produced **2,981 compiler CODE bytes /654 real x86 instructions**
with **all 654 native ordered mnemonics** and genuine 60-byte
post-RET scene DATA. This is still not exact: the original has
2,987 CODE bytes and materially different actual stack locals.
Examples of original native physical slots versus F528 source are:

| Real original local and first-use x86 | Actual PE EBP | F528 ordinary source |
| --- | --- | --- |
| Application-mode object | `−0x3D` | `−0x01` |
| Active scene pointer | `−0x184` | `−0x0C` |
| Graphics client | `−0x189` | `−0x0D` |
| Input client | `−0x62` | `−0x15` |
| Sound client | `−0x61` | `−0x16` |
| Module-path buffer | `−0x180` | `−0x158` |

The native object order is significant: it determines the real
resource failure/shutdown cleanup and authentic adjacent scene/path
field ownership, not just stack alignment. A source with matching
mnemonics, a matching number of calls and the right total
`SUB ESP,0x278` can still be very far from original bytes.

## Thirty genuine C++ source-lifetime hypotheses, all fully built

Tracked exploratory baseline
[`WinMainLocalLayoutF615.cpp`](../probes/WinMainLocalLayoutF615.cpp)
uses **only actually used Win32 and game objects** and normal C++:
real `AppMode`, `GraphicsClient`, `InputClient`, `SoundClient`,
scene pointer and module pathname, native `WNDCLASSEXA`, real `MSG`,
actual HWND/ready-event handles, two used window dimensions and
15 owned scene allocations. Its provisional class declarations are
**not claims of historical original source identifiers**.

Tracked reproducible
[`verify-winmain-local-layout-f615.py`](../scripts/verify-winmain-local-layout-f615.py)
constructs and cold-compiles, using pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, **only the one selected whole
original WinMain TU** (`--case`) or all **30 distinct affected whole
WinMain source TUs** if explicitly requested. It independently
checks the pinned native 2,987-byte original function, all 654
native x86 instructions and 123 original call instructions, the
original physical EBP first-use slots, the actual 60-byte original
scene switch table, generated complete source's first `RET 0x10`,
all source x86 mnemonic ordinals, and its 173 physical COFF fields
**including source's separate post-RET table**. The generated
173 fields are a source grammar count, **not** a claim that all
original PE relocation targets or the whole 2,987 CODE bytes match.

The 30 real source variants were selected to test distinct, meaningful
source-language lifetime assumptions rather than fake saved-frame
padding: both natural field orders of the **actually used scene
pointer/260-byte path aggregate**; actual C++ declaration placement
of the existing `MSG`, `WNDCLASSEXA` and path before startup/graphics;
a predeclared but still genuinely used path-end pointer; a real
2-field window-metrics aggregate; and combinations which legitimately
move the existing HWND, real Win32 event and original width/height
variables to earlier lexical scopes without moving their assignment or
changing the application API calls.

Every candidate has **654 compiler x86 instructions with all 654
original ordered mnemonics**, **60 post-RET source scene-table bytes**
and **173 generated physical COFF fields**, but **none equals the
original whole 2,987-byte CODE size**. The measured generated lengths
range **2,930–3,053 bytes**. Important independent controls:

| Actual source hypothesis | Whole generated CODE | Matching original instruction widths | Physical scene/path first-use locations |
| --- | ---: | ---: | --- |
| F528 original-shaped baseline | 2,981 B | 594/654 | scene `−0xC`, path `−0x158` |
| Scene pointer before path in real used aggregate | 3,053 B | 618/654 | scene `−0x158`, path `−0x154` |
| Real MSG declared before startup | 2,969 B | 598/654 | scene `−0xC`, path `−0x178` |
| Aggregate scene/path plus MSG and earlier real HWND | 3,017 B | 614/654 | scene `−0x178`, path `−0x174` |
| Aggregate scene/path plus MSG and original ready event predeclaration | 3,026 B | **627/654** | scene `−0x178`, path `−0x174` |
| Existing MSG, HWND, HANDLE, window dimensions all predeclared naturally | **2,930 B** | 595/654 | scene **`−0xC`**, path **`−0x180`** |

The last row proves a subtle false-positive risk: one source
reproduces the genuine original physical **module pathname
`EBP−0x180`**, but its scene pointer is still wrongly at `EBP−0xC`
and its complete CODE length shrinks by **57 bytes**. Matching one
local displacement without reproducing actual source object ownership
cannot be accepted as whole-function exactness. Likewise, an
alternate real aggregate reaches 627/654 *instruction widths*, not
the original full operand bytes or 2,987-byte native function.

Original native byte mismatch remains dominated by actual EH/resource
lifetime placement and scene/window-object stack ownership, and the
original scene-state/call/afterRET table bounds must be preserved.
The additional C++ experiments are authentic negative constraints,
not a substitute for reconstructing the true ABI and local classes.

**F615 adds ZERO accepted whole original functions or authored exact
CODE bytes.** Official accepted coverage is still **943 complete
authored functions /862,726 original CODE bytes**. F613/F614's
fighter game case interiors also remain nonexact containing giants,
not valid independent whole-function credits. No original executable
was patched, no external Oracle receipt accepted, and **NO 943-unit
all-unit cold replay** was run.

## Run only an affected complete WinMain C++ source TU

```bash
scripts/repo-python scripts/verify-winmain-local-layout-f615.py --case baseline
scripts/repo-python scripts/verify-winmain-local-layout-f615.py --case scene-path-aggregate
scripts/repo-python scripts/verify-winmain-local-layout-f615.py --case scene-path-plus-msg-plus-actual-main
scripts/repo-python scripts/verify-winmain-local-layout-f615.py --case msg-before-app-plus-all-hwnd-event-int
# Optional exactly the 30 whole WinMain source variants, not the 943 exact units:
scripts/repo-python scripts/verify-winmain-local-layout-f615.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

All 30 independently compiled C++ whole-function translation units,
COFF/PDBs, generated source, compiler logs and source-local/physical
x86 receipts remain in ignored `.analysis/f615-winmain-local-layout/verified/`;
the first detailed source hypotheses are preserved alongside them.
