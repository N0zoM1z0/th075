# F1097 — Distinct original 0x356: −7.5f vertical launch and real 00657F74 acceleration

The SHA-pinned Japanese TH075 1.11 executable has ONE original
`CharacterObject::Advance` callable at `0050A580`: **81,539 native
original CODE B /17,435 x86** and 567 genuine separate afterRET
switch DATA bytes. This work restores genuine inner game action
**0x356 at 005154ED..005159A0 = 1,203 native original CODE B /251
x86**, not a separately callable original exact function.

Original 0x356 belongs to a recognizably similar state family as
previously recovered 0x354: it performs true parent `(0x31,0x96)`
check, native `0045B830` expiry and **eight shots of `0x3E4`**
plus conditional extra `0x3E3`, stage-zero scale 0.1f,
real +0xD8/+0xDA/+0x80 countdown, true x87 scale/velocity threshold
checks at original `TEST AH,5; JP`, alpha and signed-facing movement,
and native animation stage 0x17 transitions.

**But the two cases are not aliases.** Original 0x354 sets initial
Y speed zero and adds original float `006583F8` to Y motion.
Original 0x356 sets **Y speed −7.5f** (native 32-bit immediate
`0xC0F00000`) and adds float **00657F74**, which has a separate
original physical DIR32 field at native x86 ordinal 101. Both
cases retain distinct original sparse dispatch table entries and
independent physical scratch variable locations. The source keeps
a genuine independent C++ `case 0x356`, rather than merging the
original native states or substituting the wrong gameplay constant.

Original opcode ordinal 100 of the selected state must be
`FLD dword ptr [actor+0x54]`; ordinal 101 must be
`FADD dword ptr [00657F74]`. The selected original-shaped ordinary
VC7.1 C++ uses the actual borrowed Y-motion lvalue
`(*(&F1037_MOTION(this).yMotion))` to preserve that exact native
operand and physical external global field order. No forced source
register, artificial local, original binary-byte patch or fabricated
floating-point runtime call is introduced.

| Actual pinned original 0x356 evidence | Verification |
| --- | ---: |
| Original game CODE B /x86 | **1,203 /251** |
| Normal C++ inner source CODE B /x86 | **963 /251** |
| Original native ordered mnemonic matches | **251/251** |
| Original GPR operand roles | **251/251** |
| Original matching x86 instruction widths | 171/251 |
| Original actual physical PE call/global fields | **14/14** |
| Native Y speed at original ordinal 85 | **−7.5f, bits `0xC0F00000`** |
| Native Y additive float global at original ordinal 101 | **`00657F74`** |
| Original x87 parity tests at 108/109 and 120/121 | **exact** |

The live `scripts/verify-characterobject-current-recovered-f1068.py`
compiles ONLY the changed entire current partial C++ parent and
independently SHA-checks original whole 81KB game PE, 92 authentic
native afterRET DIR32 jump-label equivalence classes, all 199 native
sparse literal index bytes and every recovered state's actual
mnemonic/GPR/physical PE fields and nonrelocated scalar immediates.

Now **53 genuine original game-state interiors** represent **45,896
original native CODE B /9,955 native x86**, with **9,955/9,955
matching mnemonic and GPR roles**, **764/764 genuine physically
original PE nonlocal fields** and **1,868/1,868 scalar-immediate
positions**. The selected original-shaped C++ emits **37,550 CODE B
/10,077 x86** with 567 native afterRET DATA, versus entire original
**81,539 B /17,435 x86**, ESP `0x3A0` and saved receiver EBP-`0xAC`.
Current incomplete parent frame `ESP 0x1F4`, receiver EBP-`0x80`,
and still unrecovered original actions/branch widths prevent whole
byte exactness. **The original 81KB callable is NONEXACT; new
accepted whole original GAME CODE = 0 B.**

Reproduce only this affected large original-shaped parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Full source/object/PDB/compiler and original Japanese PE field
receipts are retained under ignored `.analysis/f1097-native356/`
and `.analysis/f1068-boss-live-all-native/`. No 979-unit cold replay.
