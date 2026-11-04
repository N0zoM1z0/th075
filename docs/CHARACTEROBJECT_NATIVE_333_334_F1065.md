# F1065 — Two genuine 249-x86 CharacterObject actions, eight-shot native loop

**Corrected by [F1066](CHARACTEROBJECT_NATIVE_336_AND_IMMEDIATES_F1066.md):** this historical F1065 checkpoint missed the real original `0x334` argument at x86 ordinal 105: it is **0.0f**, not +30.0f. The current tracked C++ and original-PE verifier now check **+30.0f for 0x333, 0.0f for 0x334, −30.0f for 0x336** and the real 0x336 action restores downstream register roles. The partial-source size and following GPR totals below are historical, not current.

The pinned Japanese TH075 v1.11 original `CharacterObject::Advance` is
ONE independently authored **81,539 CODE-byte /17,435-x86** game
callable at `0050A580`, followed by 567 separately owned switch DATA
bytes. The current C++ original-shaped parent is incomplete, and the
original entire callable remains **NONEXACT**. Native switch cases
cannot independently accrue exact original callable CODE credit.

## Two real original game handlers, not an invented alias

The original game PE has independent physical action entries:

| Native action | Actual original PE CODE | Original x86 | Ordinary source |
| --- | --- | ---: | ---: |
| `0x333` | `0050D929..0050DDCF` (1,190B) | 249 | 943B /249 x86 |
| `0x334` | `0050DDCF..0050E274` (1,189B) | 249 | 945B /249 x86 |

Their original mnemonic sequences are exactly the same across all
249 x86 ordinals, **but their physical GPR assignments differ**, and
three original instruction-width positions differ. The actual
native eight-shot loop index and x87 conversion scratch also use
different genuine stack slots. The original two jump-table entries
remain distinct. Two natural C++ switch cases were inserted with the
same original gameplay grammar; no assembler, forced C++ registers,
merged switch case or synthetic padding was used.

Each handler checks genuine parent action `(0x45,0x96)` and own
animation stage `< 0x17`, expires through native `0045B830`, and
emits **eight real `0x3E4` objects** through parent `00453A70`.
It also handles the authentic parent+0xEFA timer and extra native
`0x3E3` projectile. Outside the parent branch, actual actor status 5
expires; at stage/frame (0,0), real motion is reset and native
float scales, opacity and action/angle WORDs are initialized.
The true `0040FB70` game motion initializer receives the original
constant 30.0f and a signed short +0xDC angle scaled by real
`006590B4`, with subsequent angle decrement/clamp. Stage-dependent
scale, byte alpha, hit-status and move/animation transitions are
preserved, including the real `0040FA30` and `0040FB40` calls.

## Pinned PE / normal VC7.1 complete-parent verification

Tracked `verify-characterobject-native-333334-f1065.py` compiles the
**entire current one-switch partial C++ parent** under real VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and freshly reads the SHA-pinned
original **entire 81KB CODE**, original 92 DIR32 postRET jump-label
equivalence partitions and all 199 literal sparse-map DATA bytes.
It checks all real native x86 ordinals for both cases and computes
all real original physical REL32 call/DIR32 global field targets
from **actual PE bytes**. No COFF source-symbol name alone is
accepted as proof without physical x86 field offset and destination.

| Proof | Action `0x333` | Action `0x334` |
| --- | ---: | ---: |
| Original complete action x86 | 249 | 249 |
| Correct native original mnemonics | **249/249** | **249/249** |
| Correct native GPR roles | **249/249** | **249/249** |
| Correct original x86 widths | 167/249 | 166/249 |
| Correct original PE nonlocal fields | **14/14** (10 calls +4 globals) | **14/14** |

The new 498 genuine original inner instructions and all 28 physical
original nonlocal field identities are preserved in the one partial
C++ function. The real original wide frame is `ESP 0x3A0`, with saved
receiver `EBP-0xAC`; current source instead has `ESP 0xDC` and
`EBP-0x44` saved receiver. Thus these are not byte-exact original
callable code, and they remain only inner source-game state progress.

A further genuine cross-state effect is measurable: restoring these
two sources corrects the next original `0x335` from 57/149 to
**149/149 GPR roles**, even though it is separate gameplay.
However, the currently still-unrecovered original `0x336` remains a
synthetic marker and several following states now regress to
non-native GPR allocation (`0x337` 13/35, `0x338` 56/175).
**Do not** revert the authentic `0x333/0x334` gameplay merely to
preserve their later old partial-parent metrics. A substantive next
investigation is reconstructing the true original `0x336` behavior
and measuring the full game source phase again.

At this checkpoint the selected partial parent is **16,864 generated
CODE B /4,404 x86**, with the authentic 567B afterRET sparse switch
DATA, compared to original 81,539B/17,435x86. Across **28 recovered
original game case interiors** it covers **19,809 original state CODE
B /4,232 original x86 mnemonics**, all matching source mnemonics and
**332 true original physically verified nonlocal call/global fields**.
The currently recovered GPR role total is **3,843/4,232** and is
lower than it would be with the remaining original states present.
The original game whole is not exact and has **zero newly accepted
whole CODE bytes** from these switch interiors.

Reproduce only this affected game parent:

    scripts/repo-python scripts/verify-characterobject-native-333334-f1065.py

Normal source/COFF/PDB/logs and original PE physical receipts retained
in ignored `.analysis/f1065-original-333334-proof/`. No all-979 exact
function cold replay or original executable mutation.
