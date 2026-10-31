# F941 — Original 004AC040 action 0x5F has fully native 44-instruction GPR geometry

The SHA-pinned Japanese TH075 v1.11 original fighter at
**004AC040** spans **82,796 complete callable game CODE
bytes /22,721 x86**, plus **1,126 separate afterRET DATA B**.
This original giant is NOT whole-function exact; the
tracked C++ father source still has many real game action
placeholders and saves the receiver in a wrong stack slot.

The real original **0x5F** handler is
**004AE300..004AE390**, exactly **144 native CODE
B/44 x86/three original PE-targeted external fields**.
The original logic checks native action/frame completion
using getter 0040FA30, changes the action with
0040FAC0 (both 0 and 1 transitions), and uses genuine
actor/opponent float X at +0x44 and signed actor
direction +0x66 to face the opponent.
This is a different original parent from 58KB
00543210, although both share native C++ semantics
observed in F762's original-facing state.

Tracked new real source:
[`probes/FighterThirdBossFacing5FF941.inc`](../probes/FighterThirdBossFacing5FF941.inc).
The source is **ordinary, naturally typed C++**,
reusing an already independently observed borrowed
opponent X view rather than inventing a full historical
class or a fake register local.

Tracked replay:
[`scripts/verify-third-fighter-facing-f941.py`](../scripts/verify-third-fighter-facing-f941.py)
regenerates **two entire original-shaped normal VC7.1
C++ parents**, one with the old 0x5F marker and
one with the genuine new facing body. Both retain
the previous F938/F939 real physical actions
0x58,0x59,0x5D,0x5E, and all original PE-backed
source mapping comes from actual original
**151 afterRET local DIR32 labels**, not assumed
stub instruction offsets. It checks 522/522
native DATA nonfield bytes and physically resolves
original calls/globals with zero-addend REL32/DIR32.

| Whole partial original-shaped parent | Previous marker | New F941 body |
| --- | ---: | ---: |
| Generated whole parent CODE B | 16,956 | **17,086** |
| Generated whole x86 | 4,478 | **4,520** |
| Source action0x5F CODE B /x86 | 15/2 | **144/44** |
| Original action0x5F ordered wrong mnemonic/width positions | Not comparable | **0/0** |
| Original action0x5F wrong GPR-role instructions | Not comparable | **0/44** |
| Physically original action0x5F external call/COFF fields | Stub | **3/3** |
| Whole original 82KB exact | **NO** | **NO** |

The source 0x5F natural instruction GPR phase is
remarkably **all 44 instructions original-matching**
even though both adjacent 337B 0x5D/0x5E still
have 61 wrong GPR roles apiece in the same
incomplete full-father C++. This demonstrates
that register phase must be treated **per actual
game state and source control flow**, not assumed
to propagate monotonically. The receiver location
in the current partial father is EBP−8 instead
of the original 82KB EBP−0x64; absolute code and
shared-exit jump displacement bytes are NOT exact.

Reproduce only the changed giant:

    scripts/repo-python scripts/verify-third-fighter-facing-f941.py

Native original-PE-verifiable complete C++ source
objects/PDB and logs remain in ignored
`.analysis/f941-third-original-facing/`.
**No independently accepted whole original callable
CODE, no all-unit cold replay.**
