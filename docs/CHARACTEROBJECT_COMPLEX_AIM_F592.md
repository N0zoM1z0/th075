# F592 — five complete native CharacterObject angle/trajectory and effect bodies

**Original Japanese TH075 v1.11 PE and newly compiled pinned MSVC7.1
ordinary C++ evidence; the 33,293-byte original giant remains NONEXACT.**
Original executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original `004EBDA0` CharacterObject `Advance()` still owns **33,293
whole native CODE bytes and 438 distinct post-RET sparse switch DATA
bytes**. F592 extends one normal C++ switch, first rechecking the prior
49 real original gameplay action cases and adding five new *entire*
physical nondefault case bodies, with all original register/x87/branch
roles, instruction widths and authentic PE `REL32`/`DIR32` fields.
No standalone internal case is an independently exact function.

## New whole native action source and original typed fields

| Original physical game-action body | Native entire x86 instructions | Original internal CODE (uncredited) | Actual zero-addend typed COFF |
| --- | ---: | ---: | ---: |
| **`0x388`** | **92** | **334 B** | **12** |
| **`0x389`** | **174** | **627 B** | **12** |
| **`0x38A`** | **234** | **971 B** | **12** |
| **`0x38B`** | **260** | **953 B** | **18** |
| **`0x38C`** | **74** | **276 B** | **10** |
| **Total new F592 complete source cases** | **834** | **3,161 B** | **64** |

### `0x388`: native parent guard, angle scatter and float contact

Original signed parent `+0x3A0>0` guard controls `0045B830` reset.
On true stage0/frame0 it calls original `0040FBB0(0,0,0)`,
initializes 1.0f scales/white color, then calls real
`00455580(0,45)`, performs `FILD; FSUB [00659728];
FADD [006581DC]; FCHS` and passes the computed float with
18.0f to real `0040FB70`. It updates signed facing-based x87
motion, subtracts actual global **`00659454`** and adds **`00657CBC`**,
then compares float position with genuine **`0065912C`** through
`FCOMP; FNSTSW; TEST AH,5; JP`. Its `0040FA30`/`0045B830`
reset behavior is preserved. The compiled complete source is
**92 x86 /334 bytes**, with all 12 real physical call/global fields.

### `0x389`: independent stage transitions and original light/fade effects

Stage0 initializes actual signed `+0xD8=-30`, `+0xDA=150`,
`+0xDC=0`, original `0040FBB0`, 1.0f scales and black opacity
with other channels white. Native stage4/frame0 invokes
`00453A70(0x371)` with real x87 y-offset **`00657850`** and
parent `00453D40(2)`. Stage0 brightens opacity by 30 with
original saturation at 255. If signed stage `<8` and timer
`+0x80==0` it invokes real `0040FB40(stage+4)`; at stages
`>7` it applies genuine double x87 **`00659730`**, float
**`006583FC`**, and unsigned ten-step fade. It uses actual
`0040FA30`/`0040FB40(8)` state progression and native stage8,
frame0, `S16(+0xDC)<5` to invoke `0040FB40(4)` and increment
the signed counter. The full original **174/627** source is
strictly recovered with 12 native-PE-grounded relocations.

### `0x38A`: two separate, state-mutating angle branches — not `if/else`

This **234 native x86 /971-CODE-byte** case is genuinely complex:
parent live guard, stage-zero signed counter/opacity setup,
`00453A70(0x389)` effect on stage1, then dynamically aims at
the opponent using original `PARENT->+0x2E8`, signed facing byte,
**`FIMUL`** (not a floating multiply of converted direction),
real global **`00657888`**, and actual external two-float
angle wrapper **`00483300`**. Its x87 return divides by float
**`00657828`** and uses the real CRT `__ftol2` at
**`006406AC`** before storing signed `+0xDA`. Neither external
angle wrapper nor CRT body receives game-authored CODE credit.

Crucially, original native instruction 140 **re-reads signed
`+0xDC` and `+0xDA` after the first angular correction**, testing
`S16(+0xDC)<=S16(+0xDA)` independently. An initial C++
`if (...) {...} else {...}` was both *semantically wrong* and
compiled six native x86 instructions short. Restoring TWO
separate `if` conditions exactly reproduces the original
±2-degree angular convergence and ±180/360 wrapping, including
the native `0040FB70(angle,4.0f)` velocity, real negative y
motion and stage completion. The inner `break` after a native
reset is another **genuine source control requirement**: it
preserves the original distinct exit jumps instead of collapsing
them into one shortcut.

The original `MOVSX EAX,BYTE PTR [006714D0]` at ordinal **216**
uses a physical zero-addend **`DIR32`**. The new unlinked C++
COFF operand is `BYTE PTR [0]`; this **one source relocation
placeholder** is accepted *only* after checking the genuine
original PE destination, ordinal, symbol, field type, and
zero addend. All other 233 original x86 roles and all entire
971 bytes match strict source grammar. The real native stage
completion cap is `signed global byte ×5 + 10`.

### `0x38B`: complete 260-instruction native multi-stage effect policy

Original 0x38B stage0 scales floating velocity using actual
**`006590B4`** twice, performs signed random range
`00455580(-480,960)`, saves signed `+0xD8`, updates facing/x87
position and original opacity ramp, adds float **`00659738`** and
subtracts **`00658058`**. Stage12 fades scale with original
double **`00659730`** and float **`006583FC`**; stage6
can trigger `0040FB40(2)`, and stage8 copies a genuine
int-to-x87 `S16(+0xD8)` float into parent `+0x314` while
copying actor `+0x44/+0x48` into parent `+0x318/+0x31C`
as **raw DWORD bit-identical fields**, not incorrect `FLD/FSTP`
float conversions. It creates effect **`0x38C`**, calls
parent `00453D40(15)`, then later runs real stage10/11
`0040FB40(9)` and effect **`0x38D`**, with original
signed-counter/facing-position computation.

Natural C++ source preserves all **260 native x86 register/x87/
branch/length roles and 953 whole bytes**, plus **18 physical
zero-addend COFF fields**. Incomplete switch context initially
made its final exit jump only 2 bytes; adding **real subsequent
game action source**, rather than filler or disassembly grafts,
restored the genuine original 5-byte relative jump.

### `0x38C`: two-float magnitude and *raw* angle-call ABI

Its original stage0 computes the sum of **two squared actor float
fields** `+0xC8` and `+0xD0` in x87 with `FLD/FMUL` and
`FADDP`, calls the actual external float magnitude wrapper
**`00428D20`**, divides by original **`006583A0`**, multiplies
by **`00659720`**, sets 1.0f scale and white colors. Then it
calls original external two-float angle wrapper **`00483300`**
with *two raw DWORD member arguments*, not computed FPU
arguments, and divides x87 return by **`00657828`** before
saving angle field `+0x30`. The ordinary source intentionally
uses two provisional ABI declarations for this same native
address: computed floats for original `0x38A`, raw DWORD bit
inputs for `0x38C`. These are **original caller-byte-level
contracts, not a claim about the wrapper's actual original C++
prototype, type or provenance**. Runtime/source wrapper code is
not counted as game-authored original CODE.

New source reaches all **74 x86/276 bytes** with 10 genuine
PE-targeted call/global relocations and no unverified opcode
order differences. A float-by-value expression was a negative
control: VC7.1 emitted spurious `FLD/FSTP`; restoring raw
DWORD calls and actual double-lvalue multiply source matched
native GPR/x87 operand order exactly. Correct native final jump
width emerges when later real game cases are present.

## Explicit remaining source limitations inside the same giant

Natural C++ source *hypotheses* for later original `0x38D` and
`0x38E` are present in the same selected TU and match their
**155/570 and 87/348 native instruction counts/lengths** only
partially: the former has unmatched GPR ownership in later fade
branches; the latter has unmatched GPR allocation and a
still-short 345-byte natural case versus original 348 bytes.
They are **NOT included** in the 54 verified cases, 7,943
original instruction roles, or original internal CODE-byte
accounting. Next original case `0x3E3` and later remain
explicitly diagnostic markers. Whole giant codegen, original
receiver class and complete stack-frame lifetime are unproven.

## Entire original PE/physical COFF and safe accounting

Tracked normal C++: [`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
New original-target checker: [`scripts/verify-characterobject-five-complex-actions-f592.py`](../scripts/verify-characterobject-five-complex-actions-f592.py).
It reads the pinned entire native 33,293-byte executable CODE,
then **fresh-compiles ONE affected normal VC7.1 C++ TU**
(`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`) through F591's original
source verifier, revalidates all previous **49 whole true game
cases**, the original compressed dispatch, and all five new
complete original case geometries with strict GPR/x87/CFG and
native instruction widths. It validates **64/64 genuine
physical `REL32`/`DIR32` call/global COFF records** at the
true original instruction ordinals, PE targets, symbols and
zero relocation addends.

The full native first switch retains all **60 actual zero-addend
`DIR32` jump-label COFF DWORD fields**, original repeated/default
partitions, **198 byte-identical sparse indexes**, and
**438 separate post-RET DATA layout bytes**.

| One original giant with individually complete internal action source | Native original x86 roles | Native original inner CODE (not independent exact credit) | True PE-typed COFF records |
| --- | ---: | ---: | ---: |
| Previous 49 F572–F591 complete cases | 7,109 | 26,691 B | 498 |
| F592: five new complete 388..38C cases | **834** | **3,161 B** | **64** |
| **Total 54 completely source-verified native cases** | **7,943** | **29,852 B** | **562** |

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-five-complex-actions-f592.py
scripts/repo-python scripts/verify-characterobject-stage-fades-f591.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Original native full case disassemblies, alternate source/COFF and
wrong angle/ABI/compiler-context negative controls live under
ignored `.analysis/f592-characterobject-cases/`; newly selected
VC7.1 OBJ/PDB and physical original case summary under
`.analysis/f592-characterobject-five-complex-source/`.
The original **entire 33,293 CODE-byte giant remains NONEXACT**;
**29,852 real inner CODE bytes are NOT 54 independently exact
original functions**. No split/whole CODE or DATA credit, no
all-unit cold replay or external Oracle acceptance.

## F593 follow-up: entire original physical giant now has natural source

Previous F592's diagnostic `0x3E3` and `0x3E4/0x3E5` marker cases
have been replaced by genuine whole native game-action C++ source,
including the **real shared default `0040FA30` call**. The single
new VC7.1 TU has **33,293 bytes of whole CODE, 8,789 ordered
x86 instructions, 438 separate after-RET DATA bytes and 682
true typed original PE/COFF relocations**. New genuine `0x3E4`
(261 native instructions/1,126 bytes/19 COFF) and `0x3E5`
(96/396/5) strictly match original GPR/x87/CFG/byte widths.
`0x3E3` has only 24 case-local GPR source differences, all
within its first 31 instructions; F592's earlier `0x38D/0x38E`
remain nonexact. **155 nonfield bytes still differ** across the
whole fighter and no original exact CODE adoption occurs.
See [F593 true whole-original code/data geometry study](CHARACTEROBJECT_WHOLE_GEOMETRY_F593.md).

## F593 entire giant original CODE/DATA follow-up

The same natural VC7.1 C++ `Advance()` now has *ALL* physically
nondefault game-action bodies including last `0x3E3/0x3E4/0x3E5`
and an original-backed default callback `0040FA30` instead of a
diagnostic marker. Original whole giant and compiled source are
**33,293 identical CODE lengths and 8,789 instruction positions
and widths**, with all **622 original CODE +60 post-RET DATA
physical PE/COFF references** grounded to target. There remain
**155 actual nonrelocation byte differences**, so do not claim
whole CODE exact. Newly full-source strict actions 0x3E4
(261 x86/1,126 bytes) and 0x3E5 (96/396) raise the strict
case count to **56**; three cases 0x38D/38E/3E3 still have
compiler GPR mismatches and remain uncredited. See
[F593 whole giant source geometry](CHARACTEROBJECT_WHOLE_GEOMETRY_F593.md).
