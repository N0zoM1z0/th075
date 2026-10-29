# F635 — original 33,293-byte CharacterObject giant: 25 real typed-member source experiments

**Pinned Japanese TH075 1.11** `th075.exe`, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`. This tests *entire genuine authored original native function `004EBDA0`* under ordinary pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`; no fake locals, register forcing, inline assembly, original byte grafts or game binary modification. **The original whole authored giant remains NONEXACT.**

## What the pinned original PE and compiler actually prove

The original contains **33,293 whole native CODE bytes /8,789 actual x86 instructions**, with **438 separately owned after-RET jump DATA bytes**. The tracked natural C++ [`CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp) produces the exact total 33,731-byte CODE+DATA extent, 8,789 original x86 starts/sizes/ordered mnemonics and **682 real physically typed zero-addend source COFF fields** (622 whole CODE/60 separately owned jump DATA). The pinned native PE and whole code/data comparison have **31,003 comparable nonrelocation bytes**, of which **30,866 are identical**. The remaining **137 original-byte differences** start at original whole-function byte offset **30,381 / instruction ordinal 8,076**, specifically the original stage-4 native case `0x38D` after its initial fade stage. These register allocation differences continue through native case `0x38E` and the first ~30 instructions of `0x3E3`; they are **actual nonrelocation CODE operand differences**, not unvalidated external call targets or padding. They prohibit whole-function acceptance despite matching length and instruction count.

## Real compiler hypothesis: bit-preserving C++ member types and original x87 register lifetime

The previous F596 float collision corrections demonstrated that ordinary C++ **expression and lvalue evaluation** can recover native machine-code order. F629/F631 game source investigations also found cases where raw DWORD member copy was needed rather than implicit `FLD/FSTP`; that observation motivated an independent *whole-original* type-ownership test on `004EBDA0`, rather than assuming another fighter had the same member semantics. F635 tests **25 genuinely recompiled full original-shaped C++ source variants** (baseline plus 24 actual changed C++ source shapes), limiting variations to complete native case `0x38D`, `0x38E` and `0x3E3`:

- Real member `+0x54/+0x50` zero initialization as the equivalent `I32=0` bit store rather than `F32=0.0f`; original `+0x1C/+0x20` constants 0.25f, 0.75f, 1.0f and −1.0f as their identical real original IEEE-754 DWORD patterns; simultaneous same-value bit stores in adjacent cases.
- Stage-4 native `+0x1C` float multiplication using the real `*=` operator, a direct typed member lvalue, native float-global reference, and explicit normal member left-value alias; real original fade test unsigned-byte type, signed-byte white-color bit store and native `U8` decrement via a value-preserving assignment expression.
- Actual original `0x3E3` direction byte and float member initialization written with type-equivalent, ordinary C++ data accesses. No dead stores, fake stack slots, invented calls, ABI changes, synthetic `DIFFBUILD` body, or manual offset adjustment was used.

[`verify-characterobject-typed-member-f635.py`](../scripts/verify-characterobject-typed-member-f635.py) can cold-build a single affected **whole giant** candidate using `--case`, or just these 25 affected source TUs with `--all` (never a 943-unit cold replay). For every candidate it independently reads the pinned original native 33,731 CODE+DATA bytes, compiles with the correct real VC7.1 flags, checks the entire original **8,789 native x86 counts**, complete **33,293 CODE /438 after-RET DATA extent**, **682 zero-addend typed source COFF fields** with physical **622/60 CODE/DATA ownership**, and counts *every nonrelocation byte difference across the entire original*. The original native exact-source baseline's PE-target mapping remains separately revalidated by F596; F635 does not claim that relocation-masked bytes constitute a new exact function.

| Full original-sized source candidates | Candidate count | Actual original x86 CODE geometry | Original non-COFF byte mismatches | Outcome |
| --- | ---: | --- | ---: | --- |
| Original tracked baseline plus bit-identical integer/float member writes, genuine unsigned/signed member aliases, equivalent value expressions, combined original typed init | **23** | **8,789/8,789 original instruction positions, sizes and mnemonics equal** | **137** each | Source register cycle unchanged |
| Native `0x38D` `F32(+0x1C) *= global` and `F32(+0x1C) = *(&F32(+0x1C)) * global` forms | **2** | **8,789 instructions and whole CODE length preserved, but actual instruction-start/width deviations at original whole x86 ordinals 8081/8082** | **140** each | Regressed: native physical x87 evaluation ordering changed |
| **Total** | **25 real whole giant C++ TUs** | **All 33,731 total bytes, 682 typed COFF fields** | **Zero exact variants** | Whole original function remains nonexact |

These are **compiler-observed negatives**, not guesses from earlier docs. In particular, changing a float constant assignment to the same 32-bit IEEE-754 integer store does not fix the first native `EAX/ECX/EDX` register cycle at x86 ordinal 8076. A C++ `*=` operation is *not* mechanically interchangeable with `a=a*b` in this original compiler: the two failing F635 candidate forms also shift the physical x86 start/width pair at ordinals **8081 and 8082**, despite the same total 8,789 instruction count and full original CODE length. Such a candidate cannot be accepted by total-length or relocation-count checks alone. The tracked current best source is **not edited** or degraded by these experiments.

## Next hypothesis and truthful acceptance status

The remaining byte evidence points to original **cross-case control-flow and register lifetime ownership** around native `0x38D` stage-4 fade, native `0x38E`, and the start of native `0x3E3`, not simple bit-punning a constant or replacing normal C++ `*` with `*=`. Further attempts must preserve full original GPR/x87/CFG role order, complete native CODE and all original after-RET jump DATA; an apparently promising smaller mismatch count is useless if the source changes actual x86 instruction starts or C++ semantics. The earlier F594 and F598 natural GPR/source-scope negatives are retained separately; F635 supplies 25 new targeted full-original compilation receipts.

**F635 adds ZERO accepted whole native authored functions/CODE bytes**, and ZERO artificial partial original case credit. Official accepted authored whole-function coverage remains **943 exact functions /862,726 original CODE bytes (43.71% reviewed)**. F633's more recent fighter cases and F634's source-backed but origin-unknown complete leaves are separate evidence and cannot alter this ledger. No all-unit cold replay, original executable patch, full-source acceptance receipt or external Oracle exact claim.

```bash
scripts/repo-python scripts/verify-characterobject-typed-member-f635.py --case 38d-zero-velocity-as-bits
scripts/repo-python scripts/verify-characterobject-typed-member-f635.py --case 38d-stage4-assign-op
scripts/repo-python scripts/verify-characterobject-typed-member-f635.py --case both-alpha-initializers-bits
# Optional ONLY these 25 affected whole original 004EBDA0 source TUs:
scripts/repo-python scripts/verify-characterobject-typed-member-f635.py --all
scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py
```

The complete source variants, normal VC7.1 compiled COFF/PDB, original full PE/COFF comparison metrics, compiler logs and both the initial and tracked selected rigorous validation receipts are retained under ignored `.analysis/f635-main-giant-type-ownership/` and `.analysis/f635-main-giant-type-ownership/verified/`.
