# F1090 — Original game case 0x351: 1,091B, seven-argument 0x352 spawn and native float threshold

The pinned Japanese TH075 1.11 original has ONE `CharacterObject::Advance`
callable at `0050A580`, comprising **81,539 original CODE B /17,435
x86** plus genuine 567B afterRET jump/sparse DATA. F1090 restores
original action **0x351**, physically `00514537..0051497A`, **1,091
original CODE B /246 native x86**. This is an internal game case of
the still-incomplete original 81KB parent, NOT a separately callable
original game function and NOT new accepted exact CODE credit.

Original gameplay moves this actor's X to original parent X plus signed
parent facing times **20**, increments its +0xDA timer, and resets
motion, status, scale, alpha, the +0x80 countdown to **99** and
+0x54 vertical velocity to **−1.0f** at initial stage/frame zero.
The genuine parent-stage and own-stage gates transition into stages
6..10 with real `0040FB40` and parent `00453D40(15)`. At own
stages 6..10, it zeroes Y speed and adjusts the real X/Y scale
using the native **00657858** threshold and **00657480** step.
At stages 11..15, it emits an authentic **0x33A** projectile through
`00453A70`. After stage 15 it fades unsigned alpha by 5 or expires
through real `0045B830`.

At actual +0xDA tick **35**, native PE spawns game object **0x352**
through `00453B50`, the **seven-argument projectile ABI** actually
observed in other original states. It then advances signed-facing
X/Y motion, uses `0040FA30` action completion, and performs original
stage/frame 6/11/16 transitions with native `0040FB40`. The final
stage-16 parent action guard checks **0x2BF** and parent stage
**6..8**, matching its original immediate values and control flow.

## Correct native C++ expression and threshold semantics

The first ordinary full-parent VC7.1 C++ source used the equivalent
mathematical expression `float(parentFacing*20)+parentX`, but emitted
two fewer initial parent-pointer loads than the original, then
compensating loads later. Actual original x86 begins by loading
parent X, then loads parent facing separately, multiplies it by 20
and FILD/FADDs to parent X. Writing the genuine source as
`parentX + float(parentFacing*20)` restores all ordered 246 native
mnemonics and registers. The initial source also added an extra
terminal JMP through an unnecessary distinct `return`; following
the original common terminal path naturally restores **246**, not
247, instructions without a dummy operation.

A stronger native scalar-immediate check detected an additional,
meaningful game semantics bug: original ordinal **86** uses
`TEST AH,1; JNE` after its x87 `FCOMP [00657858]`, but C++ `>`
emitted `TEST AH,0x41; JNE`. This changes equality handling, even
though both are correct mnemonic streams. Using the original
**`>=`** threshold comparison reproduces native `TEST AH,1; JNE`.
Thus true branch semantics, native x87 flags and bitwise operands
are verified, not just x86 opcode names and physical calls.

| Real original 0x351 | Current ordinary C++ source |
| --- | ---: |
| Original CODE/x86 | **1,091 B /246** |
| Generated case CODE/x86 | **862 B /246** |
| Native mnemonic roles | **246/246** |
| Native GPR roles | **246/246** |
| Native widths matching | **170/246** |
| Genuine physical original PE external targets | **15/15** |
| Actual test flags at ordinal 86 | `TEST AH,1`, verified |
| Real seven-argument projectile ID/call | **0x352 /00453B50**, verified |

A full current original-shaped one-switch parent was cold-built under
pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and checked against
the **entire original 81,539B PE SHA**, native 92 DIR32 label
partitions and 199 sparse map bytes. The tracked
`verify-characterobject-current-recovered-f1068.py` now validates
**48 genuinely recovered original state interiors**, totaling
**41,762 native original CODE B /9,084 native x86 positions** with
**9,084/9,084 original mnemonic and GPR roles**, **707/707 original
physical PE fields**, and **1,685 independently checked original
nonrelocated scalar-immediate positions**. The selected incomplete
C++ source emits **34,304 CODE B /9,216 x86**, plus the authentic
567B afterRET DATA, versus entire original **81,539B /17,435 x86**.
The original wide stack ESP `0x3A0`, saved this EBP-`0xAC` and many
other original game states/widths remain unresolved. **Whole original
NONEXACT; newly accepted original whole-function CODE = 0B.**

Reproduce ONLY the affected large game source:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Full current normal C++/COFF/PDB, rejected and corrected probes and
independent pinned PE evidence are under ignored
`.analysis/f1090-native351/` and `.analysis/f1068-boss-live-all-native/`.
No cropped original callable credit or mass 979-unit cold replay.
