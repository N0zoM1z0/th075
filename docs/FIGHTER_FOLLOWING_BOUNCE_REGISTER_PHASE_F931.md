# F929–F931 — Preceding ten-shot loop controls the next giant fighter register phase

Original SHA-pinned Japanese TH075 v1.11, authored whole game fighter
00543210: **58,294 callable CODE bytes /16,471 native x86**, plus
**943 separately owned afterRET DATA bytes** (156 genuine
DIR32 table fields). The entire giant remains NONEXACT.

## Native original evidence, re-read from the PE

The real action 0x58 at original 00544F34..00545109
has **469 B /135 x86 /17 physical PE-targeted external fields**.
Its actual ten-shot projectile loop uses a native 32-bit
EBP-4 counter, initial loop jump, ADD EAX,1 and a comparison
to 10. The immediately following original action 0x59 at
00545109..0054526D has **356 B /95 x86 /16 actual PE fields**.

Native 0x59 begins MOV EAX,[EBP-44h]; MOVSX ECX,word
ptr [EAX+62h]; CMP ECX,1. The previous F917 complete father
instead assigned EDX/EAX and had **19 wrong register-role
instructions /19 original nonfield operand bytes** in 0x59.
The source was 356 B/95 x86 with the correct instruction
mnemonics and widths, so case-local spelling was not the
whole code-generation problem.

## Real source experiment: improvement and regression

F929 compiled **27 complete original-shaped 58KB VC7.1
fathers**, varying the genuine 0x58 ten-projectile loop
source: natural int/short, for/while/do-while, unsigned,
declaration scopes, C++ compound expressions, and
source value categories. F930 compiled **27 more complete
original-shaped fathers** with alternative actual loop
counter signedness, increment placement and control flow.
The native calls and real ten-shot game effect are retained.
There are no fake locals, manual register assignments,
assembler or copied original machine bytes.

One meaningful source-control result is ordinary C++:

    int burst=0;
    while (burst++<10) {
        SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
    }

It still invokes the genuine spawn call ten times. The dead
local loop counter is incremented a final time while checking
the exit, but that final local value has no subsequent consumer.
The emitted whole source remains **58,293 CODE B/16,471
x86/1,863 COFF fields/943 afterRET DATA B**.

Crucially, that source grammar shifts VC7.1 register allocation
in the *next* real state. All original 0x59 GPR roles align,
and after independently checking all sixteen real original
PE/C++ external fields and two genuine jumps into the
parent's common epilogue, zero nonfield operand bytes differ
in the entire original 356B/95-x86 state 0x59.

| Full fighter property | F917 selected strict 0x58 | F931 postincrement experiment |
| --- | ---: | ---: |
| Generated callable CODE B (native 58,294) | 58,293 | 58,293 |
| Whole x86 instructions (native 16,471) | 16,471 | 16,471 |
| Physical 0x58 size and instruction count | 469 B/135 | 469 B/135 |
| **0x58 wrong native mnemonics** | **0** | **1 (local 55)** |
| **0x58 wrong native instruction widths** | **0** | **2 (local 55,59)** |
| Physical 0x59 size and instruction count | 356 B/95 | 356 B/95 |
| **0x59 wrong GPR-role instructions** | **19** | **0** |
| **0x59 wrong nonfield/nonshared-tail operand bytes** | **19** | **0** |
| 0x58/0x59 verified native PE-targeted fields | 17+16 | 17+16 |
| Complete native parent exact | NO | NO |

The two source JMPs to the real giant-fighter shared
epilogue have independently verified target semantics,
but their machine displacements are NOT passed off
as exact bytes; this entire fighter still has one
CODE-byte length deficit and the three later native
mode63 CMP register-width mismatches.

The new control **regresses actual preceding action
0x58**, removing its original initial JMP instruction
and changing the original loop comparison register-width
geometry. It is NOT an acceptable whole function or
standalone exact case. Original strict 0x58 F917 remains
selected. The real new finding is that preceding
source loop topology can explain *all* next-case
register allocation and native operand differences.
The next goal is the genuine original source grammar
that restores **BOTH 0x58 and 0x59** at once.

## Bounded complete-source replay

Tracked original-PE/COFF verifier:
scripts/verify-fighter-following-bounce-registers-f931.py.
It regenerates the latest F917 source entirely from
tracked F781 and F917 inputs, then serially cold
compiles two whole VC7.1 fathers. For both, it rereads
the original native game PE, real action boundaries,
all 135+95 x86 ordinals, 33 physically target-checked
original PE/COFF fields, all real 0x59 nonfield bytes,
both actual shared tail jumps, four shared-getter
entry edges, and the entire 943-B afterRET jump DATA
including 156 original relocated local case labels.

    scripts/repo-python scripts/verify-fighter-following-bounce-registers-f931.py

The two whole generated source/OBJ/PDB/compiler logs
and verified JSON stay in machine-local ignored
.analysis/f931-following-bounce-registers/. The 54
genuine whole-father alternative sources and receipts
remain in ignored .analysis/f929-fighter58-scopes/
and .analysis/f930-native-58-loop-topology/.

**No accepted full giant, no newly accepted CODE,
no corpus-wide exact-unit cold replay.**
