# F939 — Two more genuine 004AC040 giant-fighter states, 674 original native CODE B

Original Japanese TH075 v1.11 whole fighter **004AC040** has
82,796 native callable CODE bytes/22,721 native x86
plus 1,126 separate afterRET DATA bytes. The selected natural
original-shaped source is still **far from whole-function exact**,
with numerous remaining placeholder case interiors.

Previous F938 had recovered real original action 0x59
(356B/95 x86/16 original PE fields) but left two
immediately following real game states as 15-byte
two-instruction markers:

| Original action | Physical original interval | Original CODE and x86 |
| --- | --- | --- |
| **0x5D** | **004AE05E..004AE1AF** | **337 B/101 x86** |
| **0x5E** | **004AE1AF..004AE300** | **337 B/101 x86** |

Independent real original PE disassembly reveals an
actor-specific landing/transition source that differs
from the earlier 58KB Fighter's F752 C++:

| Original stage behavior | 0x5D | 0x5E |
| --- | --- | --- |
| Falling/grounded stage comparison | stage <12 | stage <9 |
| Landing auxiliary action | 12 | 9 |
| Initialization stage | 4 | 6 |
| Initial +0x50 float | +12.5f | −12.5f |
| Actual +0x54 float | 8.0f | 8.0f |
| Velocity/drag +0x5C | 0.7f | 0.7f |
| Last stage and auxiliary action | stage 12; aux 10 | stage 9; aux 8 |

These are not guessed names or reused literal constants.
The original stage CMP/push instructions, member-float
immediates, and original byte/short fields are independently
checked at original native x86 ordinals 2/28/77/86/88/91/97.

The new tracked
[`FighterThirdBossPair5D5EF939.inc`](../probes/FighterThirdBossPair5D5EF939.inc)
retains the authentic source operations:
native floor transition, signed short stage/frame
checks, game action getter/setter, opponent and actor
borrowed float x at +0x44, native signed direction
at +0x66 and true stage-specific initialization.
Only original actor-specific numeric parameters differ
from the previously reconstructed F752 source.
The borrowed X view does not claim a complete object.

The [F939 targeted verifier](../scripts/verify-third-fighter-pair-f939.py)
regenerates the complete partial C++ giant from tracked
F938 source, replacing ONLY the two real game markers.
It serially compiles THREE whole normal VC7.1
original-shaped fathers: previous two markers,
the new natural two-case body, and a diagnostic
preceding postincrement-loop alternate. No standalone
case is compiled as a fake independent whole function.

| Complete partial-parent property | F938 two markers | F939 two real cases |
| --- | ---: | ---: |
| Generated whole parent callable CODE B | 16,312 | **16,956** |
| Generated whole parent x86 | 4,280 | **4,478** |
| 0x5D native CODE B/ x86 from source | 15/2 | **337/101** |
| 0x5E native CODE B/ x86 from source | 15/2 | **337/101** |
| 0x5D native positional mnemonic/width differences | Not comparable | **0/0** |
| 0x5E native positional mnemonic/width differences | Not comparable | **0/0** |
| Real original PE external fields per new case | Not real | **8 + 8** |
| Generated parent afterRET DATA / native true DIR32 fields | 1,126/151 | **1,126/151** |
| Native afterRET nonfield bytes identical | 522/522 | **522/522** |
| Whole original 82KB giant exact | NO | **NO** |

The complete original 0x58/0x59 state bodies remain
present and original-size aligned in the growing parent.
The **native 0x58** retains exact mnemonic, width and
register-role geometry in the selected source. The
new source 0x5D and 0x5E have **61 GPR-role differences
each**, despite their identical native instruction
mnemonics, widths, original 337B size and all eight
actual independently resolved PE external targets.
Their source also stores the parent `this` at EBP−8,
whereas the native 82KB fighter at this point uses
EBP−0x64. Neither local geometry nor total same-sized
internal source is whole native byte-exactness.

The diagnostic `while (burst++<10)` predecessor
fixes the preceding 0x59's 19 wrong register roles,
but regresses the genuine original 0x58; it also
does not change the 61 wrong roles in 0x5D or 0x5E.
This is evidence of multiple state-dependent
register-phase transitions, not a reason to
force registers or accept partial cases.

Reproduce **only this large original partial-parent
source** and its three meaningful C++ variants:

    scripts/repo-python scripts/verify-third-fighter-pair-f939.py

The three whole C++ source/OBJ/PDB/PE comparisons remain
under ignored `.analysis/f939-verified-third-pair/`,
with initial independent experiments in
`.analysis/f939-third-pair/`.

**674 additional original *internal case* bytes now have
natural VC7.1 source geometry and native target backing;
0 newly accepted whole-original callable CODE bytes.
No all-unit cold replay or target-byte modification.**
