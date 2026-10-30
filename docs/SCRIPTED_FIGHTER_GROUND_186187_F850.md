# F850 — Real 186/187 ground states, original PE-complete but register nonexact

Pinned original Japanese TH075 v1.11 game fighter
005214B0 owns 46,755 callable native CODE B and 901
separate packed afterRET switch DATA B.

F850 reconstructs two current actor source-backed,
original physically bounded gameplay state interiors:

| Original action | Native complete interior | Physical PE fields | Real original behavior |
| --- | --- | ---: | --- |
| 186 | **250 B /74 x86** | 7 | Stage0 POS=12.5f, stage>0 subtract original global 00658058, stage3 animation0x1D and projectile0x341 |
| 187 | **214 B /61 x86** | 6 | Stage0 POS=12.5f, stage>0 subtract DIFFERENT actual global 00659090, stage3 animation0x1C, no projectile |

Both use genuine original stage/frame checks,
flag +0x3AC reset, floating ground threshold
0065782C, native action0 transition, real
00453E20/0040FA30/0040FAC0 and normal
00453D60 animation helper calls. The first
also sends sprite0x341 through genuine
00453A70 with observed coordinate bits and
facing byte. This is natural source code,
not synthetic register padding or disassembly
transcribed into inline ASM.

F850 first regenerates/physically checks the
previous F849 entire giant parent, then compiles
one fresh complete affected normal VC7.1 C++
translation unit. It now emits **23,997 callable
CODE B /6,595 x86**, versus F849's
23,563B/6,464 x86.

Both new cases have ALL original x86 mnemonics,
widths, exact instruction/PE field positions,
ten actual original global/call targets plus
three additional real PE calls, correct field
types and zero addends. **However, their source
is still nonexact**: genuine register allocation
differences exist in 47 nonrelocation source
bytes of case186 and 38 bytes of case187.
Two additional genuine bytes per case encode
the original enclosing complete-fighter
epilogue JMP displacement. They are NOT
masked as relocations or independently
accepted authored game CODE.

Adding these genuine game states does not
yet fix the earlier F849 0x136 stage5
GPR allocation: its 15 real register
operand negatives and two final JMP bytes
remain reverified in the newer parent.
The same full object checks 20 prior
C8-D2, 12C-12F, 130/131/133/134/135
original case extents/PE fields and all
five original packed afterRET jump tables
with 901 separately owned DATA bytes.

The original 46B/16-x86 default/getter
now again matches **34/34 genuine native
nonrelocation bytes** and all three
real PE REL32 calls, a separate positive
whole-parent compiler-context observation
that must NOT be promoted as an independent
game function.

Reproduce only the affected whole fighter:

    scripts/repo-python scripts/verify-scripted-fighter-ground-186187-f850.py

Full source, VC7.1 COFF/PDB, physical
original PE comparison and generation log
remain under ignored .analysis/f850-scripted-186187/.
The enclosing whole 46,755B original
fighter is NONEXACT. Zero new accepted
whole callable authored CODE, no mass
accepted-unit cold replay.
