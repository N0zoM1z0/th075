# F839 — Actor-specific 428B native CC fixes the historical virtual-call CFG

The original Japanese TH075 v1.11 native fighter
005214B0 owns 46,755 callable CODE B and 901
separate afterRET packed switch DATA B. The
real 0xCC case at 00525C24..00525DCF is
**428 complete interior CODE B/126 native x86/
10 true typed PE call/global fields**.

Earlier F649/F760 fragments belonged to
different fighters (435B or more). F839
independently reads the real selected actor
and reconstructs its natural source: original
x87 threshold comparison with FUCOMPP,
native ConfigureStormAt454BC0(3,4,0xFF),
16-bit stage/frame state at +0x62/+0x64,
collision reset 00453E20, aux state5,
stage3 sprite kind0x3C, actual native
flag at +0x3AC and the receiver's original
virtual vtable dispatch at slot zero.

Five whole-parent VC7.1 experiments expose
two substantive earlier source errors:

- The original x87 physical instruction
  order is FLD(this+0x48), FADD(this+0x54).
  A seemingly equivalent POS54+POS48
  expression produces wrong operand machine
  bytes even with the same 428B length.
- More importantly, the original test
  stage>=max conditionally subtracts two
  from stage, but then **unconditionally
  dispatches the virtual method through
  the vtable**, regardless of this test.
  The old source enclosed the virtual call
  inside the condition and emitted an
  objectively wrong Jcc destination byte.
  F839 fixes the original game CFG.

The actual stage3 flag clear belongs inside
the stage3 sprite block, not afterward.
Natural signed short prefix increments
reproduce both original MOV/ADD 16-bit
frame/stage sequences. The selected source
is now **428 B/126 x86**, with all
original instruction widths, mnemonics,
relative positions, GPR/x87 bytes and
10 genuine original PE references matching.
Only **four real nonrelocated machine
bytes** at CC offsets 186/187 and
424/425 differ; they are the two long
JMP operands targeting the still-unmatched
original enclosing giant epilogue.

F839 recompiles ONE entire affected
normal VC7.1 fighter parent from a fresh
reverification of F837. Its current
source emits **20,578 callable CODE B /
5,571 x86** (F837: 20,165/5,447).
All earlier complete C8/C9/CA/CB
and following CF/D0/D1/D2 original
cases, their original physical PE
fields and native non-JMP machine
bytes remain verified. The default
46B/16-x86 original getter remains
**34/34 identical nonrelocation bytes**
plus three authentic REL32 calls.
All five original packed 901B afterRET
dispatch DATA tables are also verified
in the new compiled whole function.

Selected targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-complex-cc-f839.py

Regenerated current C++, VC7.1 COFF/PDB,
alternative whole source experiments and
original PE comparisons are in ignored
.analysis/f839-scripted-stage-cc/.
The enclosing 46,755-B game function
remains NONEXACT. No split-case,
vtable call or packed DATA receives
independent accepted callable CODE.
No all-unit cold replay.
