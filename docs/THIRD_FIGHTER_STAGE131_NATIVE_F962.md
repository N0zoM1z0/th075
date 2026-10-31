# F962 — Native 004AC040 action131 restored, GPR-phase difference preserved

Pinned original Japanese TH075 v1.11 entire fighter
at **004AC040** owns **82,796 callable native
CODE B /22,721 x86** plus **1,126 independently
owned original afterRET jump DATA B**. The growing
[tracked partial whole source](../probes/FighterWhole004AC040F962.cpp)
emits 22,896 CODE B/6,247 x86, still with many
other true game actions not reconstructed; it has
a nonnative saved-`this` EBP location and incomplete
original stack-frame ownership. The whole fighter
is NONEXACT.

Original physical action **131** occupies
**004B14C9..004B1593**: complete internal original
**202 CODE B /58 x86 /5 physically PE-targeted
original calls/globals**. Its natural C++ in
[`FighterThirdBossStage131F962.inc`](../probes/FighterThirdBossStage131F962.inc)
recovers the original velocity-minus-drag,
ground contact `0065782C`, action
`0040FAC0(0xA)`, real stage0/frame0
`+0x80` short and `+0x7C` int
state initialization, native frame completion
and action9, and the real **stage5/frame0
PrepareActionAt453D60(0x1D)**.

An older historical F845 action131 source
from another 46KB actor uses similar meaningful
C++, but was NOT assumed exact for this third
82KB fighter. Native physical disassembly
confirms the actual values and control flow
independently. No fake local registers,
original-byte grafts, dead stack padding,
assembler or invented full historical class
is used to force source equality.

## Complete-parent original-PE results

The bounded
[`verify-third-fighter-stage131-f962.py`](../scripts/verify-third-fighter-stage131-f962.py)
serially compiles four ENTIRE original-shaped,
normal VC7.1 82KB *partial-parent* C++ sources,
from actual tracked F961/F962 masters: old
131 marker, real native 131 C++, alternate
const short lvalue, and genuine void
function returns rather than switch breaks.
It independently reads the native original
PE physical action131 extent and all
**5 actual zero-addend typed PE/COFF target
fields**, the genuine predecessor 130
265B/81 x86/6 real fields, all
**151 original afterRET DIR32 case labels**
and **522 nonfield DATA bytes**.

| Whole partial source | F961 prior | F962 real 131 |
| --- | ---: | ---: |
| Emitted partial parent CODE B | 22,709 | **22,896** |
| Emitted whole-partial x86 | 6,191 | **6,247** |
| Original native 131 C++ bytes/x86 | 15B/2 marker | **202B/58** |
| Wrong native 131 positional mnemonics | n/a | **0** |
| Wrong native 131 x86 widths | n/a | **0** |
| **Wrong native 131 GPR roles** | unaligned | **36** |
| Original 131 native PE targets checked | marker | **5/5** |
| Original 130 prior GPR roles and native PE targets | 0 wrong/6 | **0 wrong/6** |
| Original afterRET DIR32/nonfield bytes | 151/522 | **151/522** |
| Whole 82KB original exact | NO | **NO** |

The first incorrect original 131 GPR role
is original 131-local x86 **ordinal0**:
native loads actual `this` from EBP−0x64
into **EAX**, whereas the current partial
parent loads its receiver from EBP−0x10
into **EDX**. The following state has
36 different register-role positions even
though all 58 mnemonic and width positions
and all five external PE targets match.

An additional ignored F962 research matrix
compiled **28 complete real source variants**
of this whole partial father using actual
short field value categories, stage/frame
comparison spellings, real float contact
source order, return vs break and native
action calls. None repaired the original
36 wrong GPR roles; source alternatives
that changed original x87/branch mnemonic
order are retained as negative evidence,
not counted as native source acceptance.

The tracked four-source verifier reproduces
the bounded original PE-backed negative:

    scripts/repo-python scripts/verify-third-fighter-stage131-f962.py

Full source/OBJ/PDB/VC7.1 compiler logs
and native original receipt are under ignored
`.analysis/f962-third-stage131-proof/`; the
28 natural whole source alternatives are retained
at `.analysis/f962-third-stage131/`.

**No additional original whole callable
function or accepted native CODE bytes,
and no 979-unit all-unit cold replay.**
