# F983 — Twelve genuine native FSUBR projectile chains in two giant fighter cases

Pinned Japanese TH075 v1.11 original fighter **004AC040** owns
**82,796 original callable CODE B/22,721 x86** and 1,126
separately owned afterRET jump DATA B. The [tracked cumulative
normal VC7.1 C++](../probes/FighterWhole004AC040F983.cpp)
is still a PARTIAL reconstruction of the entire original function:
original saved receiver at EBP−0x64, real 0x720 stack frame,
other original actions, GPR allocation and relocation offsets
remain incomplete. **Whole original game function NONEXACT.**

Two physical original handlers are distinct despite nearly equal
native internal lengths:

| Real original handler | Physical PE range | Native inner CODE/x86 | Original typed PE fields |
| --- | --- | ---: | ---: |
| **1F8** | **004B5A75..004B5F05** | **1,168B/339 x86** | **28** |
| **1F9** | **004B5F05..004B6394** | **1,167B/339 x86** | **28** |

Both have genuine signed 8-bit opacity +0x11 changes, native
ground/fall collision, an independent random projectile profile,
six individually authentic sprites **0x338..0x33D** with native
Y float global **00659490**, real signed facing multiplied by
**positive 7**, actual float world X at +0x44, genuine
four/five-parameter native calls, and stage-based auxiliary
action/counter logic. Their native case0 motion differs in
velocity sign. These are not copies of another historical actor.

## Physical x87 source grammar correction

The first meaningful whole-source C++ used the algebraically
natural expression worldX - float(signedFacing*7).
Original VC7.1 emitted FLD worldX/FISUB signed-integer temporary
instead of the pinned original sequence. Each case had **30
incorrect original mnemonics and 31 wrong x86 widths** despite
a deceptively nearly correct overall case length.

Independent true-source experiments with the *already original
PE-backed borrowed float X* in
[FighterProjectileXViewF917.hpp](../probes/FighterProjectileXViewF917.hpp)
recovered the real original positive signed facing product,
FILD and FSUBR sequence. The new
[normal original-shaped source](../probes/FighterThirdBossStages1F81F9F983.inc)
uses typed borrowed world X followed by subtraction of the
converted signed facing×7. Across both entire handlers,
**twelve six-x86 chains at native case ordinals 183,
204, 225, 246, 267, 288** now naturally compile into
MOVSX, IMUL, MOV scratch, FILD, MOV actual X receiver,
FSUBR. The source is genuine gameplay C++ with no manual
register forcing, original-byte grafts or artificial stack
padding. The earlier failed FISUB spelling is preserved as
negative compiler evidence.

### The still-unmatched native GPR opacity compare

Even with all **678 original native mnemonics matched**, the
source has **one real CMP width error per handler**, both at
case-local x86 ordinal64:

- **1F8:** original CMP ECX,0xEB is 6B; current source
  CMP EAX,0xEB is 5B, producing source **1,167B/339 x86**.
- **1F9:** original CMP EAX,0xEB is 5B; current source
  CMP ECX,0xEB is 6B, producing source **1,168B/339 x86**.

These opposite width deltas cancel across the pair; **the
aggregate byte length happens to agree with the original
2,335B but is NOT an exact source match**. Eight additional
entire normal VC7.1 partial-parent opacity grammar alternatives
(byte comparison order, const field reads, integer promotion
and equivalent bounds) did not correct native ordinal64;
some regressed the branch mnemonic.

The tracked bounded
[PE/COFF whole-parent verifier](../scripts/verify-third-fighter-signed-x87-f983.py)
cold-compiles TWO complete original-shaped normal VC7.1
partial giant fathers: F982 prior markers and F983 true
states, independently reading the pinned original whole
game executable. It checks both full 339-x86 inner cases,
**all 56 actual zero-addend typed original PE targets at
correct original x86 field ordinals**, preceding original
1F7, all **151 real afterRET local DIR32 labels and
522 nonfield DATA B**. It never reloc-masks wrong absolute
field positions shifted by a native CMP width mismatch.

| Entire original-shaped partial C++ father | Prior F982 | F983 real source |
| --- | ---: | ---: |
| Compiled source CODE B | 40,025 | **42,330** |
| Generated whole x86 | 10,979 | **11,653** |
| Original 1F8 source CODE/x86 | 15/2 marker | **1,167/339** |
| Original 1F9 source CODE/x86 | 15/2 marker | **1,168/339** |
| Wrong native mnemonics | not aligned | **0 in both** |
| Wrong native widths | not aligned | **1 each, ordinal64** |
| Wrong original GPR roles | not aligned | **174/168** |
| Genuine original typed PE targets | markers | **28+28** |
| Original afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Entire original 82KB callable exact | NO | **NO** |

The full C++/OBJ/PDB, original PE-backed 56-target receipt
and compiler transcripts remain in ignored
.analysis/f983-third-original-proof/. Eight bounded real
opacity controls and five alternative true X expression
versions are retained in ignored .analysis/f983-third-1f8/.

Reproduce only the two touched partial giant parents:

    scripts/repo-python scripts/verify-third-fighter-signed-x87-f983.py

**Zero newly accepted original whole CODE/functions; no
979-unit corpus-wide cold replay.**
