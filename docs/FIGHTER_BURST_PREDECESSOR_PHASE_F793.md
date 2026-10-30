# F793 — Ten native 0x58 predecessor controls cannot repair adjacent 0x59 GPR phase

**Complete-fighter physical source study, not an exact full 58KB original.**
The pinned Japanese TH075 v1.11 original includes
`00543210` 58,294 native callable CODE B plus 943
separate afterRET DATA B, and the selected natural F781
source still emits 58,293 B. This study specifically tests
the hypothesis that the previous **whole** `0x58`
action's C++ spelling might change the register-phase seed
at the first instruction of the following `0x59` action,
even while reproducing the previous case's original x86
bytes.

The source of original action `0x58` occupies
`00544F34..00545109`, **469 native CODE B,
135 x86, 17 physical PE/COFF typed references**.
The following actual original action `0x59`
occupies `00545109..0054526D`, **356 B,
95 x86 and 16 authentic physical fields**.
Native 0x58 is currently nonfield-exact outside genuine
shared-parent continuation jumps, whereas 0x59 has exactly
**19 actual GPR-operand machine-byte differences**.

Ten freshly compiled **whole 58KB VC7.1 parents** varied
genuine source behavior without creating dummy padding or
source-only inert locals:
- native ten-projectile loop postincrement versus preincrement;
- actually used unsigned counter (which changes a genuine
  signed-vs-unsigned branch opcode);
- reverse threshold-25 and floating position comparisons;
- reverse the original two real x87 position-add operands;
- observe actual position bit copy through typed `unsigned`
  members rather than signed integer aliases;
- use the genuine `0.8f` motion member through a real
  borrowed lvalue;
- reverse loop-limit comparison `10 > burst`;
- express the two-stage real guard by De Morgan equivalence.

Each compiled full parent retains **58,293 CODE B /
16,471 x86 and 1,863 actual COFF fields**.
For the eight native-nonfield-byte-preserving controls,
the preceding 0x58 remains complete 469B and
nonfield-exact; the following 0x59 still differs by
**exactly 19 physical GPR bytes**.
The unsigned loop changes the *real original* x86
mnemonic at 0x58 ordinal 60 (wrong Jcc), and reversing
float add order makes two real 0x58 bytes wrong; yet neither
change fixes a single 0x59 phase byte. These negative results
show that changing a superficial predecessor expression
cannot be assumed to reset the next native case register
phase.

The verifier independently reviews the complete 0x58
and 0x59 source CODE extents and every authentic **17+16
original PE/COFF reference** under native original
relocation kinds/destinations for valid-form controls.
The intentionally wrong unsigned-loop branch remains
clearly labeled a negative, not a byte-exact match.
The original full 46-B F781 shared getter suffix,
remaining 0x60/0x61/0x63 native code controls,
all 943 afterRET DATA bytes, all 156 native jump-table
labels and 319 nonfield index bytes are rechecked
in the baseline *whole parent*. No original byte
grafting, masked nonrelocation differences, isolated
case acceptance or full accepted-unit cold replay.

Reproduce just the affected fighter:

```bash
scripts/repo-python scripts/verify-fighter-burst-predecessor-f793.py
```

Sources, objects and result receipt remain under local
ignored `.analysis/f793-fighter58-predecessor/`.
The original complete fighter still is **NONEXACT**
and earns zero formal callable CODE credit.
