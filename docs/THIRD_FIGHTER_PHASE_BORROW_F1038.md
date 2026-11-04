# F1038 — Real stage/frame WORD pair in the entire 82KB fighter parent

The pinned Japanese TH075 1.11 original `004AC040` is an independently
attributed, but **NONEXACT**, complete 82,796-byte/22,721-x86 fighter
`Advance`. The current selected normal-VC7.1 C++ source has the right
complete CODE length, x86 count and 0x720 frame but still disagrees with
the native original at **12 instruction widths and 6,958 GPR-role
positions**. Matching generated code or internal states must not be
credited as original callable exactness.

The original game already physically establishes the adjacent signed
short animation stage at actor **+0x62** and within-stage frame at
**+0x64**, and the borrowed type `FighterAnimationPhaseBorrowedF1024`
had been separately validated in other complete original authored
functions. Until now, the giant F1020 candidate still reintroduced
these same values in 34 local source positions via unrelated
`I16/S16` byte-offset casts.

F1038 changes **21 stage accesses and 13 frame accesses** in the
actual selected 82KB source to the shared borrowed `F1024_PHASE(this)`
fields. This exposes the original relation in action handlers 6,7,8,A
and their actual timers without inventing a class layout, changing
branch/control expressions, adding a dummy local, or forcing x86
registers. It is a real source-level semantic refinement of the
large boss function, not a new independent inner callable.

## Verification against the actual original and former full source

The tracked `verify-third-fighter-phase-borrow-f1038.py` reconstructs
the former untyped spelling from the tracked source, then compiles
**both complete 82KB parents** in ordinary pinned VC7.1 under Wine.
It independently reads the SHA-pinned original PE and checks every
original authored x86 mnemonic, width and GPR role, the authentic
whole frame/saved-receiver, the actual native 0x58/0x59 regions and
all **17 + 16 physically typed native external fields**, plus the
151 genuine afterRET DIR32 entries and 522 genuine nonrelocation
DATA bytes. It compares the *entire* emitted C++ functions, not just
the 34 changed expressions.

| Check | Former source | F1038 typed source |
| --- | ---: | ---: |
| Complete generated CODE bytes | 82,796 | **82,796** |
| Whole generated x86 | 22,721 | **22,721** |
| Native whole wrong mnemonic/width/GPR | 0 / 12 / 6,958 | **0 / 12 / 6,958** |
| Original 0x58 native wrong GPR | 0 | 0 |
| Original 0x59 native wrong GPR | 19 | 19 |
| AfterRET native physical table and literals | 151 DIR32 / 522B | **151 DIR32 / 522B** |
| Entire emitted CODE+DATA compare between sources | baseline | **bit-for-bit identical** |

The compiler renumbered **161 synthetic internal `$L...` labels**
when the borrowed type header was introduced. The verifier checks
that these are the *only* differences in all **2,352 COFF records**:
physical field offsets, kinds, addends, local target offsets, and
all external symbol names remain identical. This benign label-name
change is documented rather than claiming literal COFF symbol strings
remained equal. Original native exactness still has **zero new credit**.

Reproduce only this affected original-shaped 82KB parent (two cold
whole-parent source variants, not all 979 accepted callables):

    scripts/repo-python scripts/verify-third-fighter-phase-borrow-f1038.py

Generated COFF/PDB/logs and fresh original-byte proof remain under
ignored `.analysis/f1038-third-phase/`.

**Complete fighter remains NONEXACT; no target/manifest alteration,
no source-fragment acceptance, and no 979-unit cold replay.**
