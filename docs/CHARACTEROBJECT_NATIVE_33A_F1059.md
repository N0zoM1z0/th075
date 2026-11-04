# F1059 — Real 763B action 0x33A restores native GPR phase in eleven following states

The pinned Japanese TH075 1.11 has one original authored
`CharacterObject::Advance` callable at `0050A580` (**81,539 original
CODE B / 17,435 x86**) followed by **567 original afterRET switch DATA
bytes**. The source remains a NONEXACT partial prototype; case-local
matching cannot be counted as another original callable.

F1059 independently re-read the **actual original game PE** and
reconstructed original `0x33A` at **0050EF5F..0050F25A**, a real **763B
/ 168-x86** inner state previously a synthetic `g_FighterProbeMarker`.
Its new normal C++ body uses the genuine original actor stage/frame
zero transition, real `0040FBB0` reset, native `00455580` randomness
(three calls), +0xD8/+0xDA WORDs, original scale globals
`006590B4`/`00657478`, 8-bit alpha and stage counters. It then
reduces/clamps the original +0xD8 counter, passes actual signed
WORD-to-float values to `0040FB70`, computes the x87 atan2 through
`00483300` and `00657828`, advances signed-facing X and Y movement,
scales original +0x1C/+0x20 with `006598A8`, checks four true native
arena boundary constants and finishes the original alpha fade and
`0040FA30`/`0045B830` action completion.

The selected source is natural ordinary pinned VC7.1 C++ with genuine
`F1037_POSITION` / `F1037_MOTION` borrowed axis fields and real calls.
No forced register variables, fake stack pads, inline assembler,
byte-array function bodies or relocation name masks were added.
The whole partial parent was actually compiled from scratch under
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`.

## Native complete-function/PE-independent check

The tracked `verify-characterobject-native-33a-f1059.py` SHA-checks
**all 81,539 original callable CODE bytes** and the separately owned
567B afterRET data from the pinned game executable. It verifies the
92-entry original DIR32 jump-table *label equality partition* and
all 199 literal sparse-map bytes, then identifies the true physical
`0x33A` entry using the original sparse table, not a guessed source
index. For each nonlocal COFF field in the full source case, it maps
its **original native instruction ordinal, original PE field-byte
address, kind, signed REL32 or absolute DIR32 target**, and checks
that against the independently read original PE and actual natural
source symbol `AtXXXXXXXX` address.

| Original native `0x33A` | Selected ordinary source |
| --- | ---: |
| Native original 763B /168 x86 | **586B /168 x86** |
| Original ordered mnemonics | **168/168** |
| Original GPR roles | **168/168** |
| Original instruction widths | **109/168** |
| Actual physical original external call/global fields | **18/18** |
| Genuine native call fields / DIR32 globals | **9 / 9** |

The 59 remaining width differences are not ignored: the original
whole game owner has the large original frame `ESP 0x3A0` and
saved receiver EBP-`0xAC`, whereas the incomplete source emits
`ESP 0xA4` and saves `this` at EBP-`0x34`. Original near conditional
branches also have authentic longer displacements. These differences
mean no original whole callable was made exact.

## Important full-parent register-lifetime finding

Before the **real** 0x33A C++ existed, reconstructing the five
actual 1,908B/402-x86 long state actions `0x33B/33D/33F/341/343`
caused a genuine compiler GPR-phase regression: all five cases had
only **133/402** native GPR roles correct, and downstream original
five fade actions (`0x33C/33E/340/342/344`) had only **17/57**,
with later 0x345 at **13/35**. The old artificial *marker* at 0x33A
was not harmless: it changed normal VC7.1 register allocation for
a whole original game state family.

Replacing the actual 0x33A with its genuine 168-x86 gameplay causes
**all eleven following recovered cases** to return to the original
native GPR allocation, retaining their real existing gameplay:

| Following game states | Native original GPR roles now matching |
| --- | ---: |
| Five long `0x33B/33D/33F/341/343` cases | **402/402 each** |
| Five fade `0x33C/33E/340/342/344` cases | **57/57 each** |
| Following `0x345` case | **35/35** |

The F1059 entire-parent verifier independently checks these **11
complete switch-state x86 ordinal streams** against the original
pinned PE. The separate F1057 physical target verifier also rechecks
**all 165/165 external PE fields** in the five 402-instruction
long states, plus the 17 previous states' independent PE checks.

**Live selected C++ partial parent:** **13,426 generated CODE B /3,491
x86** and 567 original afterRET DATA B. It now contains **23 real
original state interiors** covering **15,470 actual native original
CODE B /3,309 native x86**, with **3,309/3,309 ordered original
mnemonics and GPR roles** and **270/270 original physically typed
PE nonlocal fields verified**. The source's compiled restored inner
case CODE bytes total 12,226, not 15,470, because the original
wide stack and branch widths remain different.

None of these 23 states is an original independent callable, and
most of the remainder of the **81KB whole** is still unimplemented
marker-only source. **Newly accepted whole exact game CODE = 0B;
current full original GAME callable remains NONEXACT.**

Reproduce only the affected original-shaped whole C++ source:

    scripts/repo-python scripts/verify-characterobject-native-33a-f1059.py
    scripts/repo-python scripts/verify-characterobject-multi-state-f1047.py
    scripts/repo-python scripts/verify-characterobject-five-long-actions-f1057.py
    scripts/repo-python scripts/verify-characterobject-five-fades-f1055.py

Those scoped checks compile only the changed whole partial parent;
none replays all 979 accepted exact units. Full normal source/OBJ/PDB,
original game physical PE fields and compiler logs are under ignored
`.analysis/f1059-33a-native-original-proof/`, and previous
`.analysis/f1055-*`/`.analysis/f1057-*` originals. No PE mutation,
ASM, or invented case-level exact credit was used.
