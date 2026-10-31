# F904 — 43 complete original WinMain live stage/scene-owner contexts, real VC7.1 /GX- control

Pinned Japanese TH075 v1.11 original authored WinMain
at 00602A60 has **2,987 callable CODE B/654 original
x86/123 original CALL instructions**, plus a distinct
60B afterRET jump table for all 15 physical original
scene constructors.

The native original startup's actual stack roles
are current scene EBP-0x184 and the live 260B
module pathname EBP-0x180, HWND main EBP-0x188,
window class EBP-0x30 and graphics resource
client EBP-0x189.

F904 tests **43 entire normal pinned VC7.1 /Od /GX-**
WinMain C++ sources with only genuinely used
runtime members, not fake stack padding:
30 combinations of real 16-bit sceneState and
previousState, the allocated firstScene pointer,
MSG, windowWidth and windowHeight grouped with
currentScene/path, and another 13 permutations
moving actual live state/scene/MSG fields BEFORE
currentScene/path inside the shared runtime owner.

Every source still performs all actual WinMain
graphics, input, sound, archives, window,
message-loop, dynamic scene allocation and
cleanup operations. All 43 whole compilers emit
**654 original ordered x86 mnemonics**, **173 source
COFF field records** and the true-shaped 60B
afterRET scene dispatch table. Note that matching
COFF *count* does not establish original absolute
relocation offsets or all original callable bytes.

Critically, the initial experimental batch
accidentally used **/GX**, which adds actual
compiler EH instructions and produced 749 x86.
Those invalid observations were caught before
any conclusion and ALL candidates were recompiled
under original /GX- (matching existing selected
native startup experiments). The verifier fixes
the correct option explicitly.

| Actual full-source lifetime model | Emitted CODE | Original native-width positions | Scene/path EBP |
| --- | ---: | ---: | --- |
| Baseline grouped scene/path/window/Main/Ready/directory | 3,002 B/654 x86 | 619/654 | -0x180 / -0x17C |
| Real grouped short sceneState plus previousState | **2,960 B/654 x86** | **633/654** | -0x180 / -0x17C |
| Some real firstScene-pointer allocations | 2,960 B/654 x86 | 629/654 | -0x188 / -0x184 |
| Real firstScene/sceneState/MSG leading group | 3,002–3,014 B/654 x86 | 615–619/654 | -0x17C / -0x178 or farther |

Grouping the two truly used 16-bit state values
changes the historical native instruction-width
matching count from **619/654 to 633/654**,
a concrete compiler-codegen improvement over
this chosen original-shaped source. However
the actual currentScene and path physical
EBP owners still differ from the native
-0x184/-0x180. No variant restores both,
and none emits the complete original 2,987
callable CODE bytes. All candidates remain
nonexact; none receives exact credit.

Reproduce only this independent WinMain unit
and its two focused source variant batches:

    scripts/repo-python scripts/verify-winmain-stage-live-context-f904.py
    scripts/repo-python scripts/verify-winmain-leading-live-context-f904.py

All complete C++/VC7.1 OBJ/PDB, compiler
logs and comparison receipts remain in ignored
.analysis/f904-winmain-staged-owners/.
No all-unit cold replay, no independent authored
whole-function exact CODE credit.
