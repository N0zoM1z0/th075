# F1080 — Original 621B action 0x348, authentic global-first x87 and stage-1 parent transition

TH075 Japanese 1.11 has ONE original authored `CharacterObject::Advance`
callable at `0050A580`: **81,539 original CODE B /17,435 x86** and
567 separate afterRET jump/sparse DATA B. The original whole is
NONEXACT. F1080 restores a previously synthetic `0x348` marker in the
selected normal MSVC7.1 whole-parent C++ source with genuine original
game logic; it does not create an independently exact callable.

## Original game behavior

The actual original native state `0x348` occupies
**005125A8..00512815 = 621 CODE B /132 original x86**. It initialises
motion at genuine `0040FBB0`, status at actor+0x7C, both scale floats,
all four opacity bytes and native signed +0xD8 timer at stage/frame
zero. Every frame it invokes real `0040FB70` using the signed parent
**+0xF0E** as a float, the native **`006590A8`** global multiplier,
actual actor+0xC8 angle/scale and signed +0xD8 counter. It increments
that timer in steps of 20 and caps at 120, then sets actor X to real
X velocity plus actual parent X, actor Y to real Y velocity plus
parent Y plus native `00657888`, and increases native +0x30 angle
using original `00657850`.

The stage-1 check preserves the independently original **repeated**
parent action 0x2BE comparisons and native parent stage threshold 8,
then original `0040FB40(2)` action transition. Later stage alpha
reduces by 25 or expires through native `0045B830`; the actual
`0040FA30` getter and completion call remain in their native order.

## Float operand grammar and original physical PE truth

A first ordinary whole-parent C++ emitted 136 instructions, because
an overly nested source action condition duplicated the native
`0040FB40(2)` call. Rewriting the *genuine short-circuit source
condition* restores exactly **132/132 native x86 mnemonic positions**.
A second, less obvious error persisted: apparently equivalent
`g_F1080_ParentScaleAt006590A8 * SELF_FIELD(float,0xC8)` expressions
compiled to `FLD [actor+C8]; FMUL [global]`, while **original PE
ordinal 41 requires `FLD [006590A8]`** then ordinal 42
`FMUL [actor+C8]`. That is a different original **DIR32 field
instruction position**, even though both source versions have
132 x86 mnemonics and identical GPR roles. F1080 compiled
**12 distinct complete normal C++ parent expressions** under actual
VC7.1 and found the genuine borrower syntax:

    g_F1080_ParentScaleAt006590A8 * static_cast<const float&>(SELF_FIELD(float,0xC8))

It emits the real `FLD global; FMUL actor` sequence without fake
variables, patching instructions, altered floating semantics or
register-binding assembly. Five other pointer-lvalue spellings still
placed the global relocation on the wrong original ordinal 42;
double conversion also changed total source instruction count.

The selected entire one-switch source, recompiled under original
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and independently checked
against the SHA-pinned Japanese PE, now yields:

| Original game case | Verified result |
| --- | ---: |
| Real original state CODE/x86 | **621B /132** |
| Natural source inner CODE/x86 | **498B /132** |
| Matching original x86 mnemonics | **132/132** |
| Matching original GPR roles | **132/132** |
| Original instruction widths matching | 91/132 |
| Original PE nonlocal call/global field positions/targets | **9/9** |
| Native global-first x87 float position | **41/42 correct** |

The live `verify-characterobject-current-recovered-f1068.py` also
checks every nonrelocated original scalar immediate, all 92 genuine
DIR32 switch-label partitions and the 199 native sparse-map bytes.
It now covers **39 original recovered case interiors** spanning
**33,213 original state CODE B /7,232 native x86**, with
**7,232/7,232 mnemonic and GPR matches**, **582/582 physical original
PE external fields** and **1,344/1,344 original nonrelocated
scalar-immediate positions**. The selected incomplete C++ parent
emits **27,457 CODE B /7,382 x86** and 567B native afterRET DATA.
Real original whole CODE remains 81,539B/17,435 x86, with saved
receiver EBP-0xAC and `ESP 0x3A0`, versus current prototype
EBP-0x60 and `ESP 0x180`, plus missing game cases and branch/stack
width debt. No new original whole-callable exact CODE was accepted.

Reproduce just this one source parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Scoped historical state/float grammar verifiers were also rerun
against the current parent, without the full exact-unit corpus.
The twelve source x87 alternatives, original physical PE, normal
C++/OBJ/PDB/compiler receipts remain under ignored
`.analysis/f1080-native348/` and `.analysis/f1068-boss-live-all-native/`.
