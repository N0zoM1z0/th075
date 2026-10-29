# F586 — two complete native CharacterObject late-stage effects, plus real EBP context refinement

**Japanese TH075 1.11 original PE/VC7.1 C++ original source verification,
NOT exact 33,293-byte whole giant.** Original executable SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Original entire CharacterObject giant `004EBDA0` contains **33,293
CODE bytes and 438 separately owned after-RET sparse-switch DATA bytes**.
F586 extends the same normal, source-only
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
by two independently original-PE-bounded *complete game-action bodies*,
retaining all 37 actual earlier actions and leaving `0x34C` onward
as visibly **diagnostic marker stores**. It does not assert the real
owner's nominal C++ type or entire frame layout.

## Real action `0x34A`: 295 x86 instructions /1,093 original CODE bytes

This source is NOT identical to earlier action `0x330` despite much
shared physical control. It resets parent state/effects through
original `0045B830`, runs the actual **eight-effect** parent
`00453A70(0x3E4)` loop, handles original parent saturation/`0x3E3`
and stage-zero transform via `0040FBB0(0,0,0)`. Crucial native
differences that the source independently reproduces:

- Stage-zero horizontal/vertical motion stores native **`+3.0f/-3.0f`**
  rather than earlier `−4.0f/+6.0f`.
- Within the signed stage-zero scope it performs **an additional 22
  original x86 instructions**, checking the real x87 sum
  `F32(+0x48)+F32(+0x54)` against authentic absolute float global
  **`0065786C`** via `FCOMP; FNSTSW AX; TEST AH,0x41; JP`.
  On contact it sets real actor `+0x48=20.0f`, zeroes motion,
  invokes `0040FB40(1)`, zeroes `+0x30` and resets opacity FF;
  this path exits the original whole action.
- A later stage-six signed counter check is **`S16(+0xDC)<1`**,
  not `<0`, and the stage-nine original `00455580(0,60)` result
  is converted to float *without* the earlier `−5` offset.
  The distinct effect ID is **`0x323`** via original
  `00453A70`, followed by real `00453D40(6)`.

All **295 native x86 instructions /1,093 original CODE bytes**
match the new natural VC7.1 source's exact GPR/x87/branch/width
instruction grammar. Native case-relative memory preload order is
recovered via *real float lvalues*, not a byte patch. **18 typed
physical call/global COFF fields**, including original `0065786C`
`DIR32`, are checked against actual original PE target identity,
source symbol, instruction ordinal and zero addend.

## Real action `0x34B`: 278 instructions /1,012 original CODE bytes

The second physically independent original case also runs the native
parent-state effect loop and signed stage transitions but uses a
**different original ABI** in its stage-zero motion call to
`0040FB70`: the original instructions directly load raw 32-bit
values from actor **`+0xC8` then `+0xCC`**, and push those two
dwords, *without* x87 `FLD/FSTP` or an integer/floating conversion.

Writing normal C++ using one `float` and one raw `int` parameter
incorrectly emits an x87 load and extra instructions. A genuine
`int,int` source-only interface
`MotionRawPairAt40FB70(I32(+0xCC), I32(+0xC8))`
preserves the original caller's **right-to-left push order** and
real physical `REL32` target **`0040FB70`**, naturally compiling
its entire 278 original x86 instruction sequence /1,012 bytes.
The borrowed C++ method name/prototype is provisional ABI evidence,
not proof of original original-class naming.

It subtracts distinct original global **`00657478`** from stage-zero
velocity (not the earlier `006583FC`), calls native
`00455580(0,15)` then subtracts 60 from the result, and spawns
original effect ID **`0x324`**, not 0x320 or 0x323. All **17 true
typed PE COFF** records are independently verified at original
instruction ordinals; this adds **no new tolerated source-order
exception** or fake local variable.

## Substantive cross-case native EBP allocation improvement

Adding only real `0x34A/0x34B` C++ game behavior to this **same
containing `switch`** also changes code generation in the older
`0x331` 274-instruction native actor state. In the previous
37-case source, original `0x331` was **1,003 native bytes versus
985 compiled bytes**, because three original int-to-x87 temps
`EBP−0x90/−0x94/−0x98` use six disp32 `MOV/FILD` instructions
and the small compiler source used disp8 for all six.

Under the newly enlarged normal C++ source, the original PE remains
unchanged but VC7.1 naturally assigns source temporaries
**`EBP−0x80/−0x84/−0x88`**. The final four `MOV/FILD` instructions
now also use disp32, leaving **only native ordinals 97/98** with
source disp8, so the whole original `0x331` case is **274/1,003**
versus C++ **274/997**, an explained **6-byte** native width gap.
The older `0x330` remains 274/1,003 native versus 274/985 compiled,
with its own six real native EBP disp32 width differences.

Separately, the previous native `0x332` original real temporary is
`EBP−0x9C`; the richer C++ now places its candidate temporary at
**`EBP−0x8C`**, versus earlier candidate `EBP−0x84`, retaining
identical native *encoding widths* (279/1,019) without claiming
identical original stack-slot operands or whole-function exactness.

This is not a fuzzy relaxation. The new tracked strict native-frame
helper
[`verify-characterobject-native-frame-f586.py`](../scripts/verify-characterobject-native-frame-f586.py)
requires exactly the Japanese original `MOV/FILD` ordinals
**97/98, 244/245, 259/260**, the actual EBP offsets
`−0x84/−0x88/−0x8C` (action330) or
`−0x90/−0x94/−0x98` (action331), and either
previously proven **6 × 3 bytes** or newly proven **2 × 3
bytes** of source-only width difference at the specified physical
ordinals. It still compares all 274 GPR/x87/relative branch roles
in both cases. All affected historical native-source checks now use
these explicitly bounded physical modes. No artificial locals or
original bytes were inserted to force that layout.

## One selected VC7.1 compiler source, native-PE/COFF proof and accounting

[New F586 full original source verifier](../scripts/verify-characterobject-late-stage-actions-f586.py)
reads the SHA-attested entire original Japanese game PE and physical
compressed case handler bounds, then **freshly compiles exactly ONE
affected normal VC7.1 C++ TU** by reusing the previous F585
original-backed verifier. It checks all 37 previous complete original
case bodies before validating **every native 0x34A and 0x34B
instruction and physical field**. Actual after-RET original switch
DATA retains all **60 original-style zero-addend `DIR32` DWORD slots**,
matching real repeated/default handler partitions, **198 original
byte-identical compressed index bytes** and 438 separate DATA-layout
bytes.

| Independently real original game-action bodies in ONE incomplete giant | Native x86 instruction roles | Original inner CODE (uncredited) | Genuine typed PE COFF refs |
| --- | ---: | ---: | ---: |
| F572–F585: 37 previous whole native case bodies | 5,078 | 19,140 B | 354 |
| New complete action `0x34A` | **295** | **1,093 B** | **18** |
| New complete action `0x34B` | **278** | **1,012 B** | **17** |
| **Total 39 complete original cases** | **5,651** | **21,245 B** | **389** |

The three previously known original F573/F574/F578 independent
read-only MOV/FLD source-order differences remain disclosed, but
the **new F586 actions strictly match original machine grammar**.
Neither original 0x331's real frame identity nor the 33,293-byte
whole original giant have been recovered or accepted as exact.
The 21,245 inner native CODE bytes are **not 39 separate original
functions** and receive zero standalone CODE/after-RET DATA credit.

### Affected-only reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-late-stage-actions-f586.py
# Previous source + native real EBP context regression:
scripts/repo-python scripts/verify-characterobject-five-trajectory-actions-f585.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

New one-TU VC7.1 COFF/PDB, compiler log and original physical case
receipts live in ignored `.analysis/f586-characterobject-late-stage-source/`.
Original-only native role disassemblies, wrong-C++ raw-argument
controls and exact new `0x331` EBP-width evidence remain preserved
in `.analysis/f586-characterobject-context/`.
No accepted whole/split CODE/DATA, full all-unit cold replay or
external Factory/Oracle receipt.
