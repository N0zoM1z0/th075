# F934/F937 — Strict original 0x58 expression controls cannot repair the following 0x59 register phase

Pinned Japanese TH075 v1.11 entire authored game-fighter
00543210: **58,294 original callable CODE B / 16,471 x86**,
plus **943 separately owned original afterRET DATA B**
(156 actual relocated DIR32 table labels and 319
nonfield sparse map bytes). The F917 selected whole source
emits 58,293 B/16,471 x86, still NONEXACT.

Original action0x58 at 00544F34..00545109 owns
**469 B/135 x86/17 actual external PE/COFF fields**.
It contains the real ten-shot projectile loop, a
genuinely used integer counter, original x/y actor
bit-value parameters and the native spawn call.
Its original full opcode/mnemonic/width/GPR local
shape was already strict in F917. Original immediately
following action0x59 at 00545109..0054526D has
**356B/95x86/16 real PE target fields**, but
F917 source differs in **19 original GPR-role
instructions /19 real nonfield operand bytes**.

The independent cross-actor F931/F932 discovery showed
a different *real ten-shot loop source lowering* using
a 32-bit while-postincrement could repair **ALL** 0x59
register roles in TWO entire giant fighters. But it
breaks the previous native0x58 original initial JMP
and two widths. This F934/F937 study tests a
distinct hypothesis: is there an ordinary,
semantically meaningful source spelling of the
native for-loop and projectile arguments that
preserves the original 0x58 x86 while shifting
compiler register phase for 0x59?

## 49 complete original-shaped whole-father C++ compiler controls

F934 generated and compiled **49 entire 58KB normal
VC7.1 fathers**, not isolated case snippets. It
varied actual used signed int loop declaration,
C++ increment `++`, postfix, `+=`, assignment
of increment; true loop boundary comparisons;
genuine constant 10 in its natural literal and
cast forms; harmless source braces and scope;
real game SpawnDirected argument value-category
and native parameter types/bit values. Candidates
introducing extra comparisons or different loop
conditions are retained as *negative diagnostics*,
not accepted native original behavior.

Every source compiled successfully with pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`;
all retain **943B generated separate afterRET DATA**
and **1,863 complete-source COFF fields**. Forty-one
of 49 retain the original 16,471 x86 count and
58,293 whole CODE bytes; others genuinely add
instructions or change original control flow and
are NEVER cropped.

In **36 of the 49**, generated 0x58 retains
all **135 original positional mnemonic and
instruction-width roles AND all source GPR roles**
through the full physical action, without changing
its authentic 469-B extent. **All 36 of those
same-source 0x58-strict fathers STILL have the
original 19 GPR-role differences in the following
0x59.** Not one simultaneously fixes both.
The remaining experimental source grammars either
change original 0x58 opcode/width/register phase,
increase original code size or introduce non-native
instructions, and do not yield a complete accepted
original callable function.

## Independently reproducible original PE proof

The tracked
scripts/verify-fighter-strict-predecessor-controls-f937.py
reconstructs F917's *entire* 58KB current C++ parent
from tracked source generation, and compiles **seven
separate complete original-shaped 58KB fathers**.
Six are true native-original 0x58 strict variants,
and one real `<=9` comparison is a deliberately
nonstrict control. For each native-strict source,
the original-PE F777 verifier independently
checks **all 469 bytes/135 x86 positions, all
17 actual target-backed zero-addend physical
PE/COFF fields** and the real shared-exit tail
jump ownership.

All seven independently retain **19 wrong
GPR-role instructions and 19 wrong nonfield
original operand bytes in 0x59**, after
original-PE validation of **all 16 actual
0x59 external fields**. The 943 original
DATA bytes, **all 156 native DIR32 jump
labels and 319 sparse-map nonfield bytes**
are freshly validated in each parent, without
claiming code exactness.

    scripts/repo-python scripts/verify-fighter-strict-predecessor-controls-f937.py

Machine-local ignored research:
`.analysis/f934-fighter-both-adjacent-native/`
holds the full 49-source source/OBJ/PDB,
compiler logs and original x86 comparison
receipts. The seven portable full parent
receipts are in `.analysis/f937-strict-predecessor-controls/`.

**Inference limit:** changing ordinary for-loop
increment and the true projectile parameter lvalues
while retaining native 0x58 x86 is not sufficient
to repair the next case's register phase in these
compiled models. This does NOT disprove more
substantial correct original C++ source shapes.
The next useful aim is a genuine native predecessor
loop/control-flow/owner-lifetime grammar that
produces **both strict original 0x58 and correct
0x59 source registers in the SAME full father**.

**0 new accepted whole functions, 0 new original
CODE credit, no all-unit cold replay.**
