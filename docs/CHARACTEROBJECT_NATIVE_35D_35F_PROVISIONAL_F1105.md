# F1104/F1105 — Real 0x35D randomized projectile and original 0x35F terminal; provisional GPR phase

The SHA-pinned Japanese TH075 1.11 game contains ONE independently
authored original `CharacterObject::Advance` at `0050A580`:
**81,539 original native CODE B /17,435 x86**, plus 567 genuine
afterRET jump/sparse DATA bytes. F1104/F1105 implement two *inner
switch states* as genuine C++ gameplay in the still-NONEXACT
entire original-shaped parent. These state interiors remain
**PROVISIONAL, NOT fully original-register-matched or exact**.

## Original actual state behavior and native PE evidence

**`0x35D`**: native `00516517..00516646` (**303 original CODE B /
67 x86**). On stage/frame-zero the actor resets signed +0xD8.
At stage-one/frame-zero it invokes original parent+0xE4
`0046D000(20)` animation and launches game action **`0x330`**
through the native parent `00453A70` using real actor X plus global
`00657888` minus `float(RandomBoundaryAt00455580(0,200))`, signed
facing and the actual original trailing arguments. The pinned PE
computes `FLD [actor+0x44]; FADD [00657888]; FSTP [real scratch]`
**before** calling the original random helper, then uses a genuine
`FILD; FSUBR` to form randomized X. Ordinary C++ with raw actor
field first instead reversed the x87 field location. The selected
real borrowed X-position lvalue `(*(&F1037_POSITION(this).xPosition))`
preserves the original `FLD actor` then `FADD global` at native
ordinals **28/29**, and **all 7 original physical nonlocal PE fields**
are now correctly positioned and typed. It advances signed +0xD8,
checks original `0040FA30` animation completion, and either performs
native `0040FB40(1)` while its counter remains below 5, or expires
through original `0045B830`.

**`0x35F`**: native `00516CE4..00516D10` (**44 original CODE B /
10 x86**). This is a real independent switch table entry with
native `0040FA30` getter, comparison against the actual current
+0x70 signed animation WORD, and conditional `0045B830` expiry.
Both authentic external PE call targets and all ten actual native
mnemonic positions are preserved.

| Native comparison | `0x35D` | `0x35F` |
| --- | ---: | ---: |
| Original CODE B /x86 | **303 /67** | **44 /10** |
| Selected normal current-source CODE B/x86 | **299 /67** | **44 /10** |
| Matching original mnemonic positions | **67/67** | **10/10** |
| Native instruction widths | **66/67** | **10/10** |
| Native GPR operand roles | **32/67** | **6/10** |
| True original physical PE destinations | **7/7** | **2/2** |
| Nonrelocated original scalar values verified | **11** | **0** |

**Not exact:** one original `0x35D` branch width remains different,
and both native game states still have original GPR lifetime errors.
Do not treat identical mnemonic counts or 9 actual PE destinations
as whole callable acceptance. No target bytes or source relocation
masks have been applied.

## Full one-parent live proof and honest exclusion

The tracked `verify-characterobject-current-recovered-f1068.py`
now cold-builds **only one current partial entire 81KB C++ parent**.
It independently SHA-checks the pinned original entire CODE,
verifies **92 native afterRET DIR32 jump-target equivalence classes**
and all **199 original sparse-map literal bytes**. It requires exact
ordered original mnemonics, original physical nonlocal field
positions/types/PE-calculated destinations, and original scalar
immediates for the added states. It **records** their original
GPR-role debt without granting strict phase or CODE exact credit.

There are now **seven separate PROVISIONAL source-authored inner cases**
(`0x358/359/35A/35B/35C/35D/35F`): **2,660 original native inner
CODE B /576 original x86**, **576/576 original mnemonic positions**,
**199/576 original GPR-role positions**, **44/44 true original PE
external fields** and **111 nonrelocated native scalar values**.
The source genuinely implements all their game logic, but their
register phases are *not* reconstructed; none belongs in the count
of strict recovered-native case intervals.

The prior **54 STRICT recovered native interiors** remain separately
verified: **46,518 original native CODE B /10,086 original x86**,
**10,086/10,086 original mnemonic and GPR positions**, **771/771
real original physical PE fields** and **1,895 native scalar
immediate positions**. Current partial whole C++ emits **49,806
CODE B /10,768 x86** and 567 genuine afterRET DATA, compared with
original full **81,539B /17,435 x86**, authentic `ESP 0x3A0` and
saved receiver EBP-0xAC versus current partial ESP 0x210 and
EBP-0x88. Real original widths, branches, many game states and
exact stack slots remain unresolved. **Whole original GAME remains
NONEXACT; newly accepted exact whole CODE = 0B.**

Reproduce this **one affected current whole partial source only**:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

All original independent PE field positions, rejected global-first
FPU operand source and the selected ordinary pinned VC7.1 COFF/PDB
results are retained under ignored `.analysis/f1105-native35d35f/`,
`.analysis/f1103-native35b35c/`, and
`.analysis/f1068-boss-live-all-native/`. No all-979 replay.
