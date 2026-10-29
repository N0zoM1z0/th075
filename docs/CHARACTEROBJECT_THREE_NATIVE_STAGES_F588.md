# F588 — three complete native actor stages 0x34D/0x34E/0x34F and original EBP temp identity

**Original Japanese TH075 1.11 PE and freshly compiled ordinary MSVC7.1
C++ source proof, not an accepted exact whole giant.** The original
executable SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The entire original `004EBDA0` CharacterObject giant has **33,293 CODE
bytes** plus **438 separate after-RET sparse switch DATA bytes**. F588
reads the entire original PE and source handler boundaries, then newly
compiles just ONE ordinary VC7.1 C++ function implementing all earlier
F572–F587 original action cases **plus three more complete native
nondefault actions**; case `0x370` onward remains explicitly diagnostic.
The original compressed sparse switch goes **directly from nondefault
`0x34F` to nondefault `0x370`**, not to fictional action `0x350`.

## The three complete real game-action source bodies

| Native original case | Whole x86 instructions | Original inner CODE (uncredited) | Actual zero-addend typed COFF refs | Original gameplay distinction |
| --- | ---: | ---: | ---: | --- |
| **`0x34D`** | **190** | **697 B** | **13** | Parent effect loop ×5, real raw motion bits, distinct contact spawns |
| **`0x34E`** | **163** | **603 B** | **11** | Parent effect loop ×4, signed fade timer greater than 2, state callback |
| **`0x34F`** | **161** | **599 B** | **11** | Parent effect loop ×4, signed fade timer greater than 1, immediate reset |
| **Added actual source** | **514** | **1,899 B** | **35** | Strict native GPR/x87/branch and individual instruction width matches |

### Original `0x34D`: stage contact and bit-preserved velocity

The native actor checks parent signed action `+0x60` in
`(0x31,0x96)`, invokes real `0045B830`, then loops exactly **five**
times over true `00453A70(0x3E4)` and performs the original parent
saturation effect `00453A70(0x3E3)`. Later, actor `+0x7C==6`
resets its stage state. The native stage-zero source resets the actor
using `0040FBB0(0,0,0)`, then **copies original 32-bit values from
`+0xC8` into `+0x50`, and `+0xCC` into `+0x54` directly**. These
are raw DWORD field copies, **NOT x87 floating-point arithmetic**:
writing `F32(0x50)=F32(0xC8)` emits an incorrect `FLD/FSTP`
sequence. The natural C++ instead uses the genuine source bit-copy
semantics `I32(0x50)=I32(0xC8)` and `I32(0x54)=I32(0xCC)`, and
recovers the original exact `MOV/MOV/MOV/MOV` register order.

Each tick it subtracts original global **`00659090`** from vertical
velocity, advances real signed-facing x87 motion, and for stage `<2`
grows field `+0x30` via **`00657CC0`**. If the float sum
`+0x48 + +0x54` crosses real threshold **`0065782C`**, the native
x87 `FCOMP/TEST AH,0x41/JP` path calls original parent
`00453D40(4)`, spawns two different effects **`0x32B` and
`0x32D`** via original parent `00453A70`, changes real action to
**`0x33B`** using `0040FAC0`, zeroes four motion fields and exits.
A natural C++ double-lvalue expression preserves the native
independent `MOV/MOV/FLD/FADD` load order.

### Original `0x34E` versus `0x34F`: genuine distinct timer and reset source

Both physical original cases have the parent action range, **four**
real effect-loop iterations and a separate x87 `F64 00659730`
scale shrink with float `006583FC` and unsigned opacity fade.
But these are NOT safe to clone without checking the Japanese native
instructions:

- Original **`0x34E`** shrinks only when signed `S16(+0xD8)>2`.
  During stage-zero reset, it stores float horizontal speed 20.0f,
  vertical speed zero, short timer zero, scale 1.0f and white colors.
  It **does not store actor +0x7C or +0x80 again inside this reset**.
  It subtracts native float **`0065747C`** from speed, applies the
  original x87 comparison against **`00657480`** and clamps to
  2.0f. Current-action completion calls **`0040FB40(1)`** and
  increments signed short `+0xD8`.
- Original **`0x34F`** shrinks at the different signed threshold
  **`S16(+0xD8)>1`**. Its stage-zero initialization explicitly
  **also writes `+0x7C=0`, `+0x80=1`**, which would introduce
  four extra real instructions if copied into `0x34E`. It has the
  same genuine float subtraction and 2.0f clamp, but after the
  original current-action query **calls `0045B830` directly**,
  not `0040FB40(1)` or a timer increment.

All three fresh VC7.1 C++ case bodies match **the complete original
GPR allocation, x87 instruction/control order, real per-instruction
width and exact original inner case byte length**. The original
`0x34F` handler extends physically to next nondefault `0x370`;
empty default aliases in between earn no invented source credit.

## Stronger adjacent native stack-lifetime evidence: true EBP offsets now identical

This genuine expansion of the same one-function C++ has another
meaningful compiler-context effect. Prior F586/F587 studies showed
that real source additions can expand the original-matching stack
*widths* of earlier cases without synthetic locals. **F588's three
real new gameplay cases make the exact native original temporary EBP
operands emerge** in all three earlier x87 actor states:

| Earlier original case | Original Japanese integer-to-FPU temporary locations | Fresh F588 real-C++ locations | Result |
| --- | --- | --- | --- |
| `0x330` | `EBP−0x84`, `−0x88`, `−0x8C` | Same three locations | Six `MOV/FILD` op locations/widths identical |
| `0x331` | `EBP−0x90`, `−0x94`, `−0x98` | Same three locations | Six `MOV/FILD` op locations/widths identical |
| `0x332` | `EBP−0x9C` | Same location | Two `MOV/FILD` op locations/widths identical |

Each original PE location and each source COFF instruction ordinal is
checked directly, not copied from previous reports. The strict shared
[`verify-characterobject-native-frame-f586.py`](../scripts/verify-characterobject-native-frame-f586.py)
now accepts only these physically observed original/C++ modes and
validates all complete 274-instruction GPR/x87/branch operand roles
instead of permitting arbitrary EBP shifts. The per-case historical
verifier JSON now reports **the actual source/native width surplus,
zero for `0x330/0x331/0x332` under F588**, rather than hard-coded
`+18` for a context whose source has improved.

The original containing function has many more unimplemented cases,
and intra-case branches targeting the genuine shared original exit
may still have different physical offsets. Exact local EBP temporaries
and original case grammar **do not prove whole giant byte-exact CODE**.

## Typed native PE COFF and correct complete giant accounting

The tracked original native verifier
[`scripts/verify-characterobject-three-late-actions-f588.py`](../scripts/verify-characterobject-three-late-actions-f588.py)
reuses the F587 original-backed compiler on **one affected VC7.1 C++
translation unit** with `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. It rechecks
all **40 prior real complete native cases**, the actual full 33,293
original CODE bytes, all 60 original first-switch physical DWORD
COFF jump destinations, correct repeated/default handler partitions,
**198 original byte-identical compressed indexes** and **438
separate after-RET DATA bytes**. It then independently verifies
**13+11+11=35 real `REL32`/`DIR32` COFF source fields** in the
three new cases, requiring original PE target addresses, correct
symbols/field type/zero addends at the exact native instruction ordinal.

| One selected normal C++ source containing complete native game actions | Original x86 instruction roles | Original inner CODE bytes (NOT standalone credit) | Genuine physical typed COFF fields |
| --- | ---: | ---: | ---: |
| Prior F572–F587: 40 original complete bodies | 6,048 | 22,774 B | 414 |
| F588: three new complete original bodies | **514** | **1,899 B** | **35** |
| **Total 43 original whole action bodies** | **6,562** | **24,673 B** | **449** |

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-three-late-actions-f588.py
scripts/repo-python scripts/verify-characterobject-four-way-event-f587.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

New source/OBJ/PDB, compiler log and original physical source/COFF JSON
are retained under ignored `.analysis/f588-characterobject-three-source/`;
original Japanese x86 disassembly, native/C++ pairwise comparisons
and negative bit-cast/reset experiments remain under
`.analysis/f588-characterobject-34d/`.
The **entire 33,293 original CODE-byte giant remains NONEXACT**;
its **24,673 internal native bytes are not 43 separately exact
original functions**. Zero new accepted whole/split CODE or DATA,
no complete all-unit cold replay and no external Factory/Oracle receipt.
