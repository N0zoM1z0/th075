# F1051 — Authentic 1,048B action `0x321` restores following `0x322` GPR phase

The pinned Japanese TH075 v1.11 original CharacterObject::Advance at
`0050A580` remains one NONEXACT **81,539 CODE B / 17,435 x86** callable
with 567 separate afterRET DATA bytes. F1051 reconstructs its genuine
complete **action `0x321` at `0050A80F..0050AC27` (1,048 native CODE B,
229 actual x86 instructions)** as normal gameplay C++ in the tracked
complete one-switch parent prototype. This is a real former marker
replacement, not a new independently callable function.

The original case's natural behavior was derived again from original
PE instructions instead of assuming historic notes were correct:

- Guard parent at actor+`0xE4` for real native action `0x2BC` and exit
  through actual `0045B830` otherwise.
- In animation stage/frame `(0,0)`, call `0040FBB0`, initialize genuine
  16-bit action/timer counters, scaling, opacity and two independent
  floating motion fields.
- Advance both scales by native `00658348` only before stage 6, with
  original float compare against `0065747C` and native `2.0f` clamp.
- Upon authentic stage-6 ground contact, zero real motion components,
  call the actual parent `00453D40(11)` and own `0040FAC0(0x322)`,
  emit native projectiles `0x347`, `0x7F` and a **20-shot loop** of
  `0x33A`, then parent `00453E60(10.0f)`.
- For parent stage 9 and own stage before 6, compute facing-aware
  relative X using the real parent+`0x2E8` target X, divide by
  `006590C4`, clamp against `00658290`, set native Y motion -24,
  and select a true auxiliary action.
- Advance X/Y movement and finish through the actual `0040FA30` and
  `0040FB40` game calls.

## Entire original and source comparison

A first ordinary VC7.1 whole-parent compile emitted 230 x86 with
191/229 original mnemonics. Reconstructing actual float operand order
from the native PE and using the already independently verified
`F1037_POSITION`/`F1037_MOTION` borrowed physical X/Y views fixes the
compiler's misplaced `MOV/FLD` instructions and floating expression
order, removing the extra instruction. The selected tracked C++ now
compiles action `0x321` to **813B / 229 x86**, with **229/229 exact
original mnemonic and GPR-role sequences**, no manual assembly,
padding locals, fake ABI or byte grafts.

The tracked `verify-characterobject-boss321-f1051.py` cold-builds the
**whole current 81KB *partial* source prototype**, freshly reads and
SHA-checks the actual entire original 81KB CODE and original afterRET
DATA, resolves all **19/19 genuine native original nonlocal PE field
targets at their authentic instruction ordinal**, including **12
original call fields and seven true float globals**. It validates the
source's 92 jump-entry equality partitions and all 199 original
sparse-map bytes, then checks the adjacent native `0x322` sequence.

| Authentic original | Source with complete 0x321 |
| --- | ---: |
| Native `0x321` size / x86 | 1,048B / 229 |
| Source `0x321` size / x86 | **813B / 229** |
| Native original mnemonic/GPR roles | **229/229 and 229/229** |
| Native instruction widths matching | **152/229** |
| Native original physical external targets | **19/19** |
| Following original `0x322` GPR role matching | **56/56** (was 18/56) |
| Current full partial prototype | **3,649B / 838 x86**, not original 81KB |

The original still has wide saved receiver at EBP-`0xAC`, full
`ESP 0x3A0` frame, real local source objects and external source
positions not present in the short prototype. All 77 width differences
in 0x321 correspond to measured actual x86 sizes, and **the native
whole callable is not byte-exact**.

**Important cross-case result:** restoring the true 0x321 gameplay
also changes the compiler's GPR allocation for some later marker-
preceded states. `0x322` improves from 18/56 to **56/56** roles;
`0x32B/0x32C/0x32D/0x32E/0x332` register roles regress in this
incomplete parent, although all their authentic opcode mnemonics
and physical call destinations remain verified. F1051's whole-parent
verifier records these *regressions* explicitly. They must be addressed
through genuine intervening game actions (`0x323`..`0x32A`), not by
reverting the now-correct complete `0x321` or forcing registers.

Reproduce only the affected current big-function source:

    scripts/repo-python scripts/verify-characterobject-boss321-f1051.py
    scripts/repo-python scripts/verify-characterobject-multi-state-f1047.py

Both build the one affected C++ original-shaped partial whole parent,
not the 979 accepted units. Native original PE and complete source
compiler/COFF/PDB receipts are retained under ignored
`.analysis/f1051-object321-proof/` and `.analysis/f1047-object-multistate/`.
No authored exact-byte acceptance or artificial switch-case callable
credit was claimed.
