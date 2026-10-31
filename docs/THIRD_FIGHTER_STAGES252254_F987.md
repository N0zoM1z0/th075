# F987 — Original fighter 252–254, native byte decrement and missing switch label

The SHA-pinned Japanese TH075 v1.11 004AC040 giant fighter has
**82,796 original callable CODE bytes /22,721 x86**, plus
1,126 independently owned afterRET switch DATA bytes.
The [tracked cumulative original-shaped source](../probes/FighterWhole004AC040F987.cpp)
still does NOT reproduce the full 82KB original callable.

| Native original state | Real executable PE range | Original CODE/x86 | Genuine PE external fields |
| --- | --- | ---: | ---: |
| 252 | 004B761E..004B7722 | **260B/72** | 6 |
| 253 | 004B7722..004B7825 | **259B/72** | 6 |
| 254 | 004B7825..004B7906 | **225B/63** | 6 |

Original game semantics were independently re-read rather than
copied from historical 46KB-fighter states. All three
states decrement original unsigned byte **+0x366** at
stage0/frame0, call ResetAt453E20, set real signed short
+0x80=1, int +0x7C=0, signed flag+0x3AC=0 and signed
short+0xF00=0. Genuine states252/253 additionally
check short +0x3B6 and int+0x7C and may set
short+0x3B0=1000; original 254 omits that branch.
All handle original 0040FA30/0040FAC0 animation completion
and stage6/frame0 launch authentic sprite **0x37**
with original RAW integer X, float Y+**00657888**,
signed-facing byte and real layer1, prepare action0x21
and zero the true opponent +0xEFA signed short.

The first natural VC7.1 source used
an arithmetic byte assignment and emitted an incorrect
**MOVZX** at native local ordinal9. Six independent
complete partial-father source experiments determined that
native-equivalent **--U8(0x366)** restores the
three original **MOV byte register; SUB byte register,1;
MOV byte field** instructions. Original register selection
still gives a one-byte x86 width difference in 252/253
at local ordinal10 (source AL vs original CL, then
source DL vs original AL). Native 254 aligns every
mnemonic and width position.

**Original 254 has no physical afterRET DIR32 label.**
The complete 72-x86 original 253 terminus and the
genuine following 255 afterRET target define its boundary;
a verifier must NOT invent a 254 label or crop the case.

The bounded
[original native-PE verifier](../scripts/verify-third-fighter-stages252254-f987.py)
freshly compiles TWO entire original-shaped partial 82KB VC7.1
fathers, tracked F985 markers and selected F987 source, then
independently checks the pinned Japanese original PE, all
**207 native ordered mnemonic positions**, real widths,
**18 genuine typed zero-addend PE/COFF target addresses**,
the unchanged preceding 1FD, all **151 actual afterRET
DIR32 labels** and **522 native nonfield DATA bytes**.

| Partial original-shaped father | F985 prior | F987 source |
| --- | ---: | ---: |
| Emitted partial CODE B | 47,016 | **47,715** |
| Emitted source x86 | 13,022 | **13,223** |
| Real 252 source B/x86 | 15/2 | **259/72** |
| Real 253 source B/x86 | 15/2 | **260/72** |
| Real 254 source B/x86 | 15/2 | **225/63** |
| Wrong original mnemonics | unaligned | **0/0/0** |
| Wrong native widths | unaligned | **1/1/0** |
| Wrong native GPR roles | unaligned | **47/47/40** |
| True PE target fields | markers | **6+6+6** |
| Entire original fighter exact | NO | **NO** |

The complete original still has different saved receiver
EBP−0x64, original 0x720 frame, many original-state
implementations and GPR/PE placement differences.
Matching internal code shapes is **not whole original
callable byte-exact acceptance**.

Reproduce only the affected complete partial father sources:

    scripts/repo-python scripts/verify-third-fighter-stages252254-f987.py

Native PE evidence, serial C++/OBJ/PDB build logs and
six natural byte-access grammar controls remain in
ignored .analysis/f987-third-original-proof/ and
.analysis/f987-third-252-254/.

**New accepted complete callable original functions: zero.
No 979-unit cold replay.**
