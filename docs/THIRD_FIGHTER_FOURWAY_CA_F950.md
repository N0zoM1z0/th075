# F950 — Third original 004AC040 four-way CA: 123 native x86 roles, 11 original PE targets

The SHA-pinned Japanese TH075 v1.11 original
fighter at **004AC040** is **82,796 complete
callable game CODE bytes /22,721 x86** with
**1,126 independently owned afterRET DATA B**.
The growing ordinary VC7.1 C++ parent
is still *partial*, with many unrelated
native action handlers remaining as
markers. The entire original fighter is
**NONEXACT**.

New independently decoded original game
action **0xCA** is physically
**004B04CC..004B0680**, **436 native
CODE B /123 x86** and **eleven actual
original typed external PE fields**.
The previous C++ parent contained only
a 15-byte/two-instruction marker.

The native game body is NOT copied from
the other 58KB/46KB actors' CA originals.
It configures storm `00454BC0(3,4,0xFF)`;
on original signed-short stage/frame zero
clears real movement `+0x50/+0x54/+0x5C`
and source counter `+0xF00`; on
stage2/frame0 sets original floats
`+0x50=11.0f`, `+0x54=5.0f`,
`+0x5C=0.6f`, fires two original
`00453C80` bullets of kinds 0x7D
and 0x7E with signed facing, float X
constructed from original signed facing
times **80** plus actual actor `+0x44`,
and native projectile Y global **00658400**,
then calls `00453D60(31)`.
The later real ground test checks
`+0x48>0065782C` and signed
stage **greater than 1**, applies
velocity/drag, clears actual motion
and frame on landing, invokes original
`0040FAC0(0xA)`, and otherwise
transitions on animation completion
via `0040FA30` and `0040FAC0(9)`.

The new natural game C++ is
[`FighterThirdBossFourWayCAF950.inc`](../probes/FighterThirdBossFourWayCAF950.inc).
No dummy stack variables, manually
forced register assignment, original
machine-code bytes, fake historical
owner class or padding are used.

The bounded tracked verifier
[`verify-third-fighter-fourway-ca-f950.py`](../scripts/verify-third-fighter-fourway-ca-f950.py)
freshly compiles TWO whole original-shaped
*partial* fighter VC7.1 source units:
old CA marker vs new source.
It independently reads the pinned
original PE, original afterRET local
case label mapping, full physical CA
handler, all **eleven actual zero-addend
typed PE target fields** and the earlier
C8/C9 physical handlers (with their
honest remaining deficits), plus all
151 real afterRET labels and 522
native DATA nonfield bytes.

| Whole partial original-shaped source | Prior C9 + CA marker | F950 real CA |
| --- | ---: | ---: |
| Emitted source CODE B | 19,543 | **19,958** |
| Emitted source x86 | 5,244 | **5,365** |
| Original CA source CODE/x86 | 15B/2 | **430B/123** |
| Original CA native CODE/x86 | 436B/123 | **436B/123** |
| Wrong original CA mnemonic positions | Unaligned | **0** |
| Wrong original CA GPR-role positions | Unaligned | **0** |
| Wrong original CA x86 widths | Unaligned | **2** |
| Original CA typed PE/global targets | Marker | **11/11** |
| Original afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Whole 82KB original game callable function exact | NO | **NO** |

Two remaining native widths are
**original CA-local ordinals 47/48**:
the original integer-to-x87 temporary
is physically stored at **EBP−0x98**,
so the native MOV/FILD are two
**6-byte long-EBP-displacement**
instructions. The incomplete
19,958-B partial father source
instead has the scratch at
**EBP−0x44**; both generated
instructions are **3 bytes**.
Their **six real native missing
bytes** cannot be fixed by
fabricating inert local padding,
and the whole original parent
saved-`this` and EBP storage remain
different. Do not mistake the
compiler source's original 123
instruction roles for exact
physical game CODE.

The previous
[F948 C8](THIRD_FIGHTER_FOURWAY_C8_F948.md)
still has three independent widths
wrong at 106,121,122, and
[F949 C9](THIRD_FIGHTER_FOURWAY_C9_F949.md)
has all 158 native mnemonic/width/
GPR roles aligned. Both source/PE
target records are rechecked in
F950's newly compiled parent.

Reproduce only affected giant:

    scripts/repo-python scripts/verify-third-fighter-fourway-ca-f950.py

Full C++ source/OBJ/PDB, VC7.1 compiler
log, original PE and generated target
receipt are under ignored
`.analysis/f950-third-original-CA/`,
with preliminary original actor CA source
controls under `.analysis/f950-third-ca-native/`.

**0 newly accepted independently
callable original game functions,
0 exact CODE byte credit, no
979-unit full cold replay.**
