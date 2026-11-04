# F1109 — Three more native 206-x86 original game actions 0x362–0x364 and real projectiles 0x367/368/369

Japanese TH075 1.11 has ONE independently original-authored
`CharacterObject::Advance` at `0050A580`, **81,539 original CODE B /
17,435 x86**, plus 567 separately owned afterRET switch DATA bytes.
F1109 adds **three more actual original C++ switch-state interiors** to
the already restored actions `0x360`/`0x361`. The single parent remains
NONEXACT, and none of these cases is a separately exact original callable.

| Genuine original action | Original PE physical interval | Native original CODE B / x86 | Selected generated C++ case |
| --- | --- | ---: | ---: |
| `0x362` | **00517480..00517837** | **951 /206** | 963 /206 |
| `0x363` | **00517837..00517BFB** | **964 /206** | 964 /206 |
| `0x364` | **00517BFB..00517FBF** | **964 /206** | 964 /206 |
| **Three distinct original case interiors** | — | **2,879 /618** | **2,891 /618** |

Each original state shares all **206 original native instruction
mnemonics** of original `0x360/0x361`, but its native EAX/ECX/EDX
roles, physical scratch slots and the spawned action number are
independently original. F1109 instantiates the one genuine original
C++ gameplay family under three additional **distinct case labels**,
without changing the native sparse table equivalence partition or
merging game action ownership.

All five actual original game states `0x360..0x364` check parent
`(0x31,0x96)` and own stage below 2, expire, perform **two** genuine
`0x3E4` shot loop iterations plus optional original `0x3E3`, reset
motion/status/alpha/scales and initial +0xD8 timer to 15, and
invoke authentic native `0040FB70` with **unaltered DWORD actor+0xC8
angle** and real signed timer as float. They advance signed-facing X
and Y velocity, reduce timer, increase original angle+0x30 by global
`00657878`, and honor genuine four original arena boundaries.
On original animation completion they copy native +0xC8 DWORD to
parent+0x314, spawn the following *distinct* game action through
native `00453A70`, and expire:

| Original source case | Actual original first argument to final spawn |
| --- | --- |
| 0x360 | 0x365 |
| 0x361 | 0x366 |
| **0x362** | **0x367** |
| **0x363** | **0x368** |
| **0x364** | **0x369** |

The original compiler's instruction-width distinction is meaningful:
state 0x360/361/362 loops use original signed-byte stack counter
locations EBP-0x78/-0x7C/-0x80 respectively, while the next states
0x363/364 use disp32 counters at native EBP-0x84/-0x88. The selected
incomplete C++ parent uses EBP-0x8C/-0x90/-0x94/-0x98/-0x9C
respectively. Consequently the first THREE source cases have four
loop counter instructions **3 bytes wider each** than native.
For **0x363 and 0x364**, all **206/206 original instruction WIDTHS
match** as well, not just mnemonics and GPR roles; however the actual
stack displacement values still differ. Do NOT mistake equal inner
code lengths for a bitwise exact original whole function.

## Recompiled one whole C++ parent against original physical PE

The selected entire source compiled normally under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, then the tracked
`scripts/verify-characterobject-current-recovered-f1068.py` compared
each actual original game interval by **all original native ordered
mnemonics, GPR roles, true PE REL32/DIR32 physical field ordinal,
original PE-calculated call/global target and nonrelocated scalar
immediate**. For the 3 new actions:

| New original game-state proof | 0x362 | 0x363 | 0x364 |
| --- | ---: | ---: | ---: |
| Original matching ordered mnemonics | **206/206** | **206/206** | **206/206** |
| Original matching GPR roles | **206/206** | **206/206** | **206/206** |
| Original matching instruction widths | 202/206 | **206/206** | **206/206** |
| Original physically correct PE external fields | **15/15** | **15/15** | **15/15** |
| Original nonrelocated scalar immediates | **34/34** | **34/34** | **34/34** |

The live one-parent proof now covers **60 strictly original-role
matched game-state interiors**, totaling **51,345 original native
CODE B /11,126 x86**, **11,126/11,126 original mnemonic+GPR
positions**, **848/848 actual original external PE fields**, and
**2,065 original native scalar-immediate positions**. It still
separately reports **seven provisional original cases** (4,310
original CODE B /916 native x86, 469 GPR matches, 70 real PE fields)
without falsely claiming their register phases match.

The selected partial C++ whole emits **56,242 CODE B /12,136
x86**, versus full original **81,539B /17,435 x86**, and keeps
native **92 afterRET DIR32 jump-label equivalence classes** and all
**199 literal sparse-map bytes**. Original ESP `0x3A0` and receiver
EBP-0xAC still differ from source ESP `0x27C`/EBP-0xA0, other
game states and branch/local offsets remain unfinished. **The
original whole is NONEXACT; newly accepted whole-function native
CODE bytes = 0 B**, even though 0x363/364 local instruction widths
happen to match.

Reproduce **only the affected whole partial parent**:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Full normal compiler, source/COFF/PDB, real original Japanese PE
receipts and rejected extra-terminal-JMP source retained under
ignored `.analysis/f1108-native360361/` and
`.analysis/f1068-boss-live-all-native/`. No original EXE modification,
independent case exact credit, dummy locals or 979-unit cold replay.
