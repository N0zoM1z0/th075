# F886 — Real original 2BE float-to-short C++ helpers and raw-integer Y sprite

Pinned original Japanese TH075 v1.11 fighter at
005214B0 owns 46,755 callable CODE B and five
separately owned packed afterRET switch DATA
tables totaling 901 B. Physical original
case2BE at 00529E8E..0052A05A is **461
entire native CODE B/136 x86/15 genuine
typed original PE fields**.

The natural VC7.1 C++ restores actual stage0
Reset and +0x80=6, action-completion check,
stage+0x64==0 counter reset, stage2 animation
0x28 and Prepare0x17, native correction
float+0x36C minus original global00657888,
sprite0x73 with true signed-facing*64
FILD then FSUBR actor X and floating
Y+0x48 plus global00659470.

Two genuine C++ conversions of the actually
read float X+0x44/Y+0x48 into signed short
values stored at +0xF00/+0xF02 produce
TWO native VC7.1 runtime helper calls:
source symbol **__ftol2**, physically resolved
in the original PE to **0046406AC** (0x6406AC).
These are NOT injected opcode sequences
or ABI-swapped substitute helpers.

The next sprite0x33C through native 00453B50
uses actor integer X+0x44 and a TRUE
**raw integer Y+0x48**, not the float-Y formal
used in preceding 2BD. Stage10 triggers
native animation0046D000(0x1F4) and
PrepareActionAt453D40(6), while stage11
invokes InitTrajectoryAt453E60(5.0f)
and raw sprite0x7F through 00453C80.

A false but plausible copied 2BD method
signature with floating third argument
promotes raw Y to float. The compiler
then emits one extra real FILD/FSTP
sequence: whole inner case becomes
**464B/137 x86** rather than the
original 461B/136-x86. F886
compiles both complete C++ parents
and rejects that false positive.

One selected full pinned VC7.1 parent
generates **36,061 callable CODE B/
10,165 x86** (F885 35,615/10,031).
Every 2BE original 136 instruction
mnemonic, width and relative offset
now matches. All 15 true physical
original PE operands at case offsets
[60,68,92,154,164,179,209,255,
266,287,337,373,383,419,452]
have genuine relocated original
destinations, zero source addends
and compatible real C++ symbol
roles, including both original
0x6406AC conversion helper calls.

The original inner case remains
NONEXACT, with **48 genuine
GPR operand byte differences
and two enclosing giant final
JMP byte differences** at
case-relative +457/+458.

The same new whole source COFF
physically rechecks **61 prior
original PE-backed state cases**,
including entire 2BC and 2BD,
1FD one-byte CMP defect,
252/254 physical relocation
shifts, and 259 correct
sparse physical boundary.
All five original 901B packed
afterRET tables and native
46B common getter four
honest GPR errors are verified.

Targeted verifier:

    scripts/repo-python scripts/verify-scripted-fighter-stage2be-f886.py

Complete normal C++, VC7.1 OBJ/PDB,
positive/negative whole-source
controls and strict native PE
JSON receipts are in ignored
.analysis/f886-scripted-stage2be/.
Original 46,755B full fighter
remains NONEXACT; no inner-case
or afterRET DATA gets accepted
whole callable exact CODE.
No full corpus cold replay.
