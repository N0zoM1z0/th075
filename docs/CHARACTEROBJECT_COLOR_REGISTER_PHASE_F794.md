# F794 — Real four-channel color and state-lifetime experiments in the 33KB boss

**Complete native original PE-backed source research, not an exact
whole-function acceptance.** The pinned Japanese TH075 v1.11
`0x004EBDA0` character state advance owns **33,293 native
CODE B /8,789 x86** and **438 independently owned post-RET
switch DATA bytes**. The best selected ordinary VC7.1 source
matches all 8,789 native x86 instruction positions and
mnemonics, and **30,866 /31,003 comparable bytes**
across complete CODE+DATA, but **137 actual GPR operand
machine bytes** differ in real actions `0x38D/0x38E/0x3E3`.
Those are not relocation bytes and are not allowed to be
masked away.

F794 audits the very first failing native `0x38D`
action, not an isolated toy function. A genuine borrowed
`BorrowedCharacterColorF794` view identifies physically
observed actor four-byte color channels `+0x11..+0x14`.
It is never instantiated as an invented complete historical
owner. The source tests whether actual writable color and
stage-object lifetimes, instead of `U8(offset)` macro
spelling, can affect the VC7.1 register allocator.

Ten **complete** 33,731-B original-shaped source TUs were
recompiled in serial. Nine physically meaningful
variants preserve original **33,293 CODE B, all 8,789
x86 opcode/width positions, 682 genuine PE/COFF fields,
all 438 after-RET DATA bytes, and exactly 137 wrong
native nonfield bytes**. They test:

- complete typed red/green/blue/alpha member assignments;
- const-lvalue read of the actual red-channel threshold;
- original `20<=red` versus `red>=20` comparison;
- actual stage-counter postincrement versus preincrement;
- state-stage six check with reversed operands;
- explicit unsigned-byte color fade subtractions;
- observed stage-zero writable member lvalues;
- one originally existing color member in a borrowed typed view.

The tenth variant swaps the *real* stage-three
`S16(0x62)==3` and `S16(0x64)==0`
short-circuit order. Although its parent still emits
**33,293 native-shaped CODE B/8,789 x86 and all 682
original PE/COFF relocations**, it has nonnative
mnemonic/width ordinals **8042/8046** and worsens
physical wrong nonrelocated bytes to **152**. A
same-sized source is not exact if genuine branch
instructions change.

The tracked
`scripts/verify-characterobject-color-source-f794.py`
independently re-reads the true PE, cold-compiles
only these ten full parent candidates, and runs
`physical_all_COFF` against the **original 622
CODE plus 60 real post-RET DATA fields** for
*every candidate*: all native referenced destinations,
COFF kinds, addends and 60 actual dense/sparse
switch handler identities must agree, not only the
nonrelocation byte totals. No accepted unit is
replayed en masse.

```bash
scripts/repo-python scripts/verify-characterobject-color-source-f794.py
```

All generated original source versions and objective
comparison receipts are stored locally in ignored
`.analysis/f794-character-color-owner/`. This
does not change the reviewed authored provenance,
`config/matches.csv`, any whole-function exact
adoption or the official progress count.
