# F836 — Selected fighter 0xCA original 418B native case recovered in the whole parent

The original Japanese TH075 v1.11 005214B0 fighter contains
46,755 callable CODE B and five afterRET packed switch tables
occupying a separate 901B DATA region. The original 0xCA
case at 00525892..00525A33 is **418B/121 x86/11 physical
original PE/COFF calls/globals**. It is NOT the other-fighter
F759 439B/129-x86 0xCA state, despite the similar name.

Normal, source-backed VC7.1 C++ reconstructs actual 0xCA:
native ConfigureStorm(3,4,0xFF), stage/frame-zero
position and vertical velocity/drag reset, grounded
x87 threshold 0065782C, native action0xA exit,
actual conditionally reset action9, real stage2
position/speeds (10.0/5.0/0.6), native
signed-direction sprites 0x7D/0x7E at 00453C80
and PrepareActionAt453D60(31).

Four full-parent original source expression tests
were built, not isolated fake case functions. The
selected real expression preserves 418B/121 x86,
all native instruction mnemonics, widths, relative
positions, GPR bytes and 11 genuine PE field
locations/zero addends/targets. Its only
**four unrelocated byte differences** are
CA-relative offsets 203/204 and 414/415,
both the authentic original enclosing-giant
long-JMP relative operand pairs at x86
ordinals 56/120. Those remain wrong while
the generated parent is smaller than original.

A fresh compiled affected whole parent has
**19,684 callable CODE B /5,308 x86**,
versus F834's 19,281/5,189. The verifier
regenerates the previous C8 source from
target, then physically rechecks complete
C8 (657B/190 x86/17 PE fields), C9
(279B/86 x86/11 PE fields) and new CA,
plus all FIVE original packed 901B afterRET
switch tables from the current COFF object.
The 46B native shared getter keeps original
EBP-0x10 and three PE REL32 calls, but new CA
changes its source GPR phase: four true nonfield
bytes at offsets 10/12/16/19 are wrong.
Do not inherit the shorter F834 getter 34/34
byte result.

Reproduce only this giant's affected source:

    scripts/repo-python scripts/verify-scripted-fighter-fourway-ca-f836.py

Regenerated C++, original PE/COFF receipts,
and alternate source compiles are in ignored
.analysis/f836-scripted-fourway-ca/.
The enclosing original 46,755-B game function
remains NONEXACT. No independent case or
separate switch DATA callable CODE credit,
and no all-unit cold replay.
