# F901 — Complete native 31B/31C, recovered 2F8 end and whole-fighter x86 width audit

Pinned Japanese TH075 v1.11 original executable:
the one callable fighter at 005214B0 owns
**46,755 original CODE bytes/13,230 x86 instructions**
and five separate packed afterRET switch DATA tables (901B).

After appending two genuinely original late cases to the
selected complete normal VC7.1 parent, the generated function
emits **46,754 CODE bytes/13,230 x86 instructions**, plus the
same 901B postRET DATA shape.

The full callable functions are NOT exact. All **13,230
original x86 MNEMONICS match by ordinal**, but exactly
FIVE genuine original instruction WIDTH positions still
differ in the current full source:

| Original case | Whole x86 ordinal | Native B | Current source B | Original operator |
| --- | ---: | ---: | ---: | --- |
| 0x63 | 2885 | 6 | 5 | CMP ECX,0x96 versus source CMP EAX |
| 0x63 | 2908 | 5 | 6 | CMP EAX,0x96 versus source CMP EDX |
| 0x1FD | 8455 | 6 | 5 | CMP ECX,0x95 versus source CMP EAX |
| 0x252 | 8986 | 3 | 2 | SUB DL,1 versus source SUB AL |
| 0x254 | 9130 | 2 | 3 | SUB AL,1 versus source SUB CL |

Those width differences net to one native CODE byte
absent, explaining the original 46,755 versus current
46,754. This does NOT mean only one machine-code
byte remains wrong: the source has authentic GPR
allocation differences. In the entire code,
1,352 source COFF relocation fields occur in
generated CODE; only **909 are at the identical
absolute original code field offsets**, while
**443 are shifted** relative to the corresponding
original instruction. Such fields cannot be
counted as original byte-exact relocation matches.

A new full-current-parent evidence audit checks
**79 earlier actual source-backed original game
case interiors** by each original physical
PE handler entry and matching native x86 ordinal
rather than freezing old GPR byte mismatches.
Across those intervals, **797/797 real physical PE
call/global DESTINATIONS match their C++ source symbols**;
424 source fields have shifted absolute positions
because of earlier machine-width phases. In
0x252 and 0x254 exactly six COFF fields each
also shift *within their own case*, twelve total.
No shifted field is masked to fake exact native CODE.
Original 1FD and 0x63 width/register issues
are retained as physical negatives.

## Newly reconstructed original late case interiors

Native 31B is **248 complete CODE B/74 x86/8 actual
physical PE fields** at 0052C952..0052CA49:
stage0 initializes actual short F00/dword7C,
real ResetAt453E20 and getter match;
stage4 invokes original 454A70(0), 452B30,
PrepareActionAt453D60(0x17) and sprite3E5
at 453A70. Stage8 genuinely increments short
F00 only below eight and invokes auxiliary6.

Native 31C is **219 complete CODE B/63 x86/7 actual
physical PE fields** at 0052CA4A..0052CB24:
stage12 uses original 454A70(0)/452B30/Prepare17;
stage15 increments a true short F00 below8,
invokes auxD and sets actual byte+3CF=1.
Its original last exit is already a GENUINE
TWO-byte SHORT JMP at original 0052CB23:
opcode EB 2A to native 0052CB4F. The selected
normal VC7.1 source generates the identical
short JMP; forcing a five-byte JMP would be
incorrect.

Both actual late cases reproduce the ENTIRE
original native inner CODE byte geometry,
with ALL **15 combined actual PE field positions,
types, zero addends and real original targets**.
They have ZERO nonrelocation byte differences,
INCLUDING their genuine original near/short
whole-giant epilogue JMP operands. They remain
switch interiors, not independent callable functions.

Adding those actual 467B original native state
interiors naturally restores the preceding
entire 2F8 to **1,151 B/316 x86/28 original
physical PE fields**, including the previously
nonnative final short-JMP width. Its current
complete inner source also has ZERO original
nonrelocation byte differences, with its natural
final five-byte long JMP restored.

Three independently compiled equal-sized full
C++ negative sources (wrong native 31B sprite,
wrong 31B trigger stage, and wrong 31C short
counter bound) are rejected by exactly one extra
genuine original nonrelocation operand byte
each, at case offsets +159, +93 and +171.

Current original shared 46B getter matches all
34 original nonrelocation bytes and all
three genuine physical PE calls. All five
original packed 901B postRET DATA tables
are physically reverified.

Reproduce ONLY this affected original fighter:

    scripts/repo-python scripts/verify-scripted-fighter-tail31b-31c-f901.py

Complete actual normal VC7.1 C++/COFF/PDB,
negative controls, opcode-width and PE target
receipts are in ignored .analysis/f901-fighter-31b/.
The original 46,755B whole callable function is
**NONEXACT**. No independent split-case exact
callable CODE credit and NO mass cold replay.
