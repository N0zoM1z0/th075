# F916–F917 — Four real original giant x87 projectile offsets recovered

Pinned original Japanese TH075 v1.11, independently authored single
**00543210** whole fighter: **58,294 callable CODE B / 16,471
x86 instructions**, plus five separate 943 afterRET switch DATA
bytes (156 actual DIR32 fields and 319 nonfield DATA bytes).
It is **not an accepted exact whole function**.

## Independently read complete native PE, not a case-only comparator

F916 rebuilt the actual F781 latest whole normal VC7.1 source
and compared *every original whole x86 instruction in order*:

- F781 generated **58,293 callable CODE B / 16,471 x86**.
- Three original instructions have wrong widths, at whole ordinals
  **2934, 2977, 3000**, all within native action 0x63.
- The first GPR-role divergence is at **whole ordinal 2198,
  original 00545109, action 0x59**. The preceding 2,198
  original register-operand roles match, which does NOT prove
  earlier absolute physical PE fields or complete CODE exact.
- **Four original mnemonic differences**, all caused by source
  arithmetic at full x86 ordinals **11765, 11970, 12328,
  12528**, are genuine `FSUBR` (native) versus `FADD`
  (source). They occur across real native 0x2BF, 0x2C0,
  0x2C4 and 0x2C5 C++ burst actions.
- The same four actual original sequences use
  `IMUL facing,+20` or `IMUL facing,+46`; F781 source
  instead uses **negative** integer products and `FADD`.
  Those expressions can be algebraically equivalent but are
  **not original-codegen identical** or necessarily
  indistinguishable for all floating-point rounding/exception
  circumstances.

## Real source recovery, not byte grafting

Seventeen complete *58KB parent* source alternatives tried the
true X-coordinate arithmetic: typed/const/volatile actor memory,
integer promotion, cast syntax, operand order and meaningful
float-reference lvalues. All candidates use the real signed actor
facing at `this+0x66`, actual float world X at `this+0x44`,
and native projectile creation calls. No dummy locals, fake
returns, manual assembly, mode-specific source bodies or target
bytes are inserted. Some variants generate additional instructions
and are explicitly rejected.

**Two different real C++ representations recover the native:**

- `reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44
  - float(signedFacing * positiveDistance)`
- An explicit `float&` lvalue read for the same observed X,
  followed by subtraction of the positive signed facing product.

The first is the new selected source, using
[`FighterProjectileXViewF917.hpp`](../probes/FighterProjectileXViewF917.hpp).
This is only a **borrowed X-member tail view**:
the 0x44-byte prefix is independently observed occupied
storage, NOT a complete or instantiable fighter class.
It does not allocate a fake object.

## Fresh complete normal VC7.1 original comparison

Tracked reproducer:
[`verify-fighter-native-burst-x87-f917.py`](../scripts/verify-fighter-native-burst-x87-f917.py)
regenerates the complete F781 source from its tracked
chain, expands two relevant genuine action includes,
compiles **two entire** normal VC7.1 /GX- bosses serially,
and re-reads the original pinned game PE.

| Entire original-shaped fighter property | F781 predecessor | F917 borrowed typed X |
| --- | ---: | ---: |
| Generated whole callable CODE B | 58,293 | 58,293 |
| Whole original/source instructions | 16,471 / 16,471 | 16,471 / 16,471 |
| **Native-vs-source mnemonic differences** | **4** | **0** |
| Original-vs-source instruction widths wrong | 3 | 3 |
| Native six-instruction projectile chains, all actual bytes equal | 0/4 | **4/4** |
| Actual compiler COFF records | 1,863 | 1,863 |
| True original afterRET jump DATA / local DIR32 fields | 943 / 156 | 943 / 156 |

Across the two complete generated *unlinked* CODE sequences,
**exactly eight bytes change**: the four real positive signed
integer IMUL immediates and four genuine native `FSUBR`
opcode bytes. The corresponding **24 full original x86 instructions across
four separate six-instruction windows** now align in
correct x86 positions, including real operand GPR roles,
native EBP scratch slots, full 32-bit values and floating
operation order. All original/source COFF field records and
the 943B postRET DATA bytes are unchanged. The original
DATA table's full sparse mapping is reverified against the
source by the existing original-native F759 checker.

The exact whole giant still has its original three wrong
action0x63 widths, many actual register/operand differences,
and source fields shifted by the preceding width phase.
A 1-byte **total-length deficit does not measure the
remaining machine-byte differences**. Do not mask an
absolute relocation, crop actions into callable functions
or promote this code to the 979-unit exact ledger.

Targeted full-giant verifier, **not the 979-unit replay**:

    scripts/repo-python scripts/verify-fighter-native-burst-x87-f917.py

The complete regenerated C++, object/PDB, compiler transcript,
17 original-source trial outcomes and original-PE/native receipt
are retained under ignored
`.analysis/f917-twin-x87-whole/` and
`.analysis/f917-native-burst-x87-verified/`.
No new original callable CODE credit.
