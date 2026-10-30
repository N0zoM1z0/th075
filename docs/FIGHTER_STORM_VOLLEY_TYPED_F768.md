# F768 — actual fighter 2F8 integer-to-x87 FILD/FSUBR source ordering restored

**Complete original game-state research inside one still-NONEXACT
58KB fighter parent.** The pinned original is Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The independently authored `00543210` entire callable function is
**58,294 native CODE bytes**, with **943 separate after-RET switch
DATA bytes**. The genuine internal `0x2F8` complete case is
`005500D5..00550475`, exactly **928 native CODE bytes, 252 x86
instructions and 23 physically typed zero-addend PE/COFF fields**.
As this is an internal case, none of these 928 bytes can be credited
as an independently byte-exact game function.

## Native x87 mismatch was a real C++ expression-order defect

F681/F706 game source already implemented the original early two
counters, stage-2 signed directional projectile 0x40, the real
stage-6 0x391/0x392 barrage loop, 006714D0 cloud-dependent counter,
actual action completion, animation stage changes, and genuine
`00453A70`, `00453C80`, `00453D40`, `00454BC0` calls. With the
recent F767 complete fighter context, this source emitted
**928 B/252 x86 and all 23 real PE fields**, but **five physical
native x86 opcode ordinals 39–44 were in the wrong evaluation order**.
The native original is not a simple `FLD actorX; FISUB scratch`:

```asm
MOVSX  EAX, BYTE PTR [actor+66h]
IMUL   EAX, EAX, 3
MOV    [EBP-1C8h], EAX
FILD   DWORD PTR [EBP-1C8h]
FSUBR  DWORD PTR [actor+44h]
```

This computes actor X minus `float(direction*3)` with **integer-first
x87 evaluation**. A raw C++ cast of X caused VC7.1 to evaluate the
actor float first and emit `FLD` before integer multiplication,
then `FISUB`, which is not the actual original instruction sequence.

The physical actor `+0x44` float member is independently established
by earlier F752/F762 original source; using this *real borrowed typed
member* in the expression allows VC7.1 to generate the original
`MOVSX/IMUL/MOV/FILD/FSUBR` instructions naturally. The new
[`FighterStormVolleyTypedF768.inc`](../probes/FighterStormVolleyTypedF768.inc)
contains no synthetic temp/padding, byte patches or handwritten ASM.

Eleven freshly compiled **entire 58KB original-shaped VC7.1 C++
source alternatives** tested the genuine actor-X lvalue, observed
float member, const-qualified member, actual signed-facing source,
32-bit cast and parentheses. A plain parenthesized arithmetic form
introduced an extra incorrect two-byte x87 operation and was rejected.
The genuine actor X lvalue/borrowed field restores **all 252 original
ordered x86 mnemonics and widths** and reduces actual native
nonfield/parent-nontail wrong bytes from **182 to 166**, repairing
all five wrong opcode positions. The 166 remaining EAX/ECX/EDX/EBP
machine-byte differences are *not* normalized away or called exact.

## Fresh selected complete parent verification and honest negatives

The tracked [`verify-fighter-storm-volley-typed-f768.py`](../scripts/verify-fighter-storm-volley-typed-f768.py)
regenerates all the actual F759–F767 C++ fighter source, substitutes
this original 2F8 source, then compiles **ONLY one affected entire
VC7.1 parent TU** under `/Od /Ob0 /Gy /GR- /GX /GS /Zi`.
It rereads the independent original PE and verifies all original
2F8 boundaries, **928 whole native CODE B/252 native x86**, the
**23 original physical DIR32/REL32 fields** with authentic offsets,
zero addends, source COFF decorated symbol owners and original PE
target destinations. It rejects any wrong physical x86 opcode/width,
and explicitly asserts **166 genuine nonfield wrong bytes** plus
unmatched external full-parent relative JMP displacement bytes.

In this same newly compiled parent the previous F767 complete 2F9
**1,367-B/381-x86/34-ref** native opcode proof remains intact (249
wrong operand bytes), and F764 complete 2FA **971-B/279-x86/31-ref**
still has 156 wrong GPR operand bytes. Previous C8–CE,
1F6/1F7/1F8, 2DB full-case original source and the independent
**943-B after-RET original jump DATA** (156 authentic DIR32 labels,
319/319 other original sparse-map bytes) also pass their own checks.
This confirms the source is genuinely composed in one entire parent,
not separately compiled favorable inner case snippets.

```bash
scripts/repo-python scripts/verify-fighter-storm-volley-typed-f768.py
# 2F8 entire native 928B/252 x86/23 PE fields; no opcode/width errors
# 166 actual wrong operand bytes remain (was 182)
# 2F9 still 249 bad, 2FA still 156 bad; all remain NONEXACT
```

The complete fighter still emits **58,261 of 58,294** native CODE B,
so the parent has a **33-B whole-CODE deficit** *plus* genuine other
register and shared-tail CFG differences. Neither the full 2F8
case nor the original callable giant earns new exact authored CODE
credit. Official accepted ledger remains **973 complete game
functions /865,627 original CODE bytes**, 43.86% reviewed.
No all-973-unit cold replay, target EXE edits, invented locals,
CRT/SDK callee double-credit or unknown-origin promotions were made.
Full compiled CPP/COFF/PDB, native comparison and trial logs remain
in ignored `.analysis/f768-fighter-2f8-order/` and
`.analysis/f768-fighter-storm-whole/`.
