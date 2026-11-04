# F1070/F1071 — Real 0x323 and 0x324 projectile/physics states, native x87 branch and raw-angle stack ABI

**Historical F1071 checkpoint:** Later [F1074](CHARACTEROBJECT_NATIVE_328_329_32A_F1074.md) restored 0x328/0x329/0x32A long projectile states and the live PE verifier now covers **36** cases. The 33-case/21,045B parent figures below represent this earlier valid source checkpoint, not the current live source geometry; native F1071 323/324 PE fields remain exact.

The SHA-pinned Japanese TH075 v1.11 original game has ONE authored
`CharacterObject::Advance` at **0050A580**, original **81,539 callable
CODE B /17,435 x86**, followed by **567 separate afterRET sparse-switch
DATA bytes**. This work reconstructs genuine **inner** original game
states in an incomplete normal MSVC7.1 C++ whole-parent. Original
full-game exactness remains **NONEXACT**, not 33 independent exact
callables and no new accepted whole GAME CODE.

## Two newly recovered original game states

| Native action | Actual original PE interval | Native original CODE/x86 | Current emitted natural C++ case |
| --- | --- | ---: | ---: |
| `0x323` | **0050AD46..0050B150** | **1,034B /220 x86** | 795B /220 x86 |
| `0x324` | **0050B150..0050B654** | **1,284B /278 x86** | 1,012B /278 x86 |
| **Both genuine original state interiors** | — | **2,318B /498 x86** | **1,807B /498 x86** |

The native original states are adjacent independently indexed
jump-table handler entries, NOT independently callable or separately
credited game functions. Both are real ordinary C++ game control flow
and have no marker-only dummy body.

`0x323` implements actual status-5 cleanup `0045B830`, stage-zero
motion and opacity initialization, native angle/speed helpers at
`0040FB70`, action/scale counters, true `00483300` atan2 of the
borrowed X/Y motion fields, real current position update, four
independently original arena bounds, alpha/color fade and native
`0040FA30`/`0040FB40` transitions. Its scaling uses authentic
`00657858`, `006592A4`, `006590B4`, `0065747C` and two original
`00659454` fade-multiplier fields.

`0x324` independently includes the real parent-action `(0x31,0x96)`
guard with a true **three-shot `0x3E4` loop**, conditional native
`0x3E3` extra shot and parent+`0xEFA` reset, initial native
`0040FBB0`, **15.0f (bit pattern `0x41700000`)** angle-associated
speed argument, original Y motion and `00483300` atan2, stage
scaling and opacity, real original landing conversion through
`0040FAC0(0x325)`, four actual arena bounds, alpha fade and action
completion. Original global values at `00657878`, `0065782C` and
`00659454` are retained.

### Exact physical code-generation details recovered

An initial genuine `0x323` C++ attempt reused the floating-argument
method type for actor+`0xC8`. The original PE actually **loads the
32-bit actor+0xC8 angle value using `MOV`, then `PUSH`es the unchanged
DWORD bit pattern** at both original helper call sites. Ordinary
MSVC7.1 with a float-typed argument instead emitted extra
`FLD/FSTP` and **222** source x86 rather than the actual original
**220** instructions. Passing the **genuinely observed native raw
32-bit angle bits** through a dedicated prototype naming that
original stack ABI preserves the original `MOV/PUSH` order, actual
float secondary argument, both native `0040FB70` call targets and
restores the real 220-instruction stream. This establishes the
**physical DWORD stack argument**; it does not claim the entire
unrecovered historical C++ helper declaration has been discovered.

`0x324` originally uses native `FCOMP [0065782C]`, `TEST AH,0x41`,
**`JP`** to skip ground contact. The natural C++ `Y - verticalVelocity
<= ground` preserves the actual original unordered-float behavior
and emits the original branch kind. No forced register, inline
assembly, direct PE patch, fabricated stack padding or relocation
mask was introduced.

## Entire game parent and original physical field proof

The tracked current-parent source was cold built normally with pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. The independent **full
original 81KB PE** SHA, all 92 original afterRET DIR32 jump-label
equality partitions and 199 native sparse literal bytes were
checked. Every actual original case x86 ordinal was compared with
the current **one** whole-parent C++ COFF, and all physical REL32
call/DIR32 float field bytes resolved from the original actual PE,
not merely matching names.

| Native instruction evidence | `0x323` | `0x324` |
| --- | ---: | ---: |
| Native original mnemonic positions equal | **220/220** | **278/278** |
| Native original GPR roles equal | **220/220** | **278/278** |
| Native instruction width matches | 141/220 | 188/278 |
| Original physically correct PE nonlocal fields | **24/24** (10 calls/14 globals) | **27/27** (14 calls/13 globals) |

Restoring both real states, including the three-shot loop in 0x324,
also restores the immediately following `0x325` original GPR phase
from **35/100 to 100/100**, without an artificial marker. Older
whole-parent controls and original PE target verifiers still pass.

The new **live scoped verifier**
`scripts/verify-characterobject-current-recovered-f1068.py` now
cold-builds ONLY the current one changed whole parent and
independently verifies **33 real source-recovered original state
interiors**, totaling **25,131 actual native original state CODE B,
5,373 native x86 positions, all 5,373/5,373 original mnemonic and
GPR roles, and 422/422 physically original call/global PE fields**.
The current C++ emits **21,045 CODE B /5,535 x86**, with **19,978
compiled source inner-case CODE B** and 567 authentic afterRET data
bytes. Native full original remains **81,539 CODE B /17,435 x86**
with `ESP 0x3A0` and saved receiver `EBP-0xAC`; this incomplete
parent has smaller `ESP 0x110` and saved receiver `EBP-0x50`, many
marker cases and real original instruction width/branch-distance
debt. Thus no whole original GAME function or original byte was
newly accepted exact. The previous 979 complete exact functions
and their existing CODE credit remain unchanged.

Reproduce **only this one affected whole parent**, not 979 cold units:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Optional previous grammar controls for original 0x320/0x321, five
long 402-x86 states, x87 parent Y and all native later states are
still executable and were replayed against the new parent.
Real C++/COFF/PDB/compile and original PE receipts are retained under
ignored `.analysis/f1070-object323/`, `.analysis/f1071-object324/`
and `.analysis/f1068-boss-live-all-native/`. No byte-array body,
original EXE mutation or 979-unit mass cold replay.
