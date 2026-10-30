# F829 — Original native B4/B5 motion restart cases with three real epilogue exits

The pinned TH075 1.11 Japanese original 005214B0 fighter
has 46,755 callable CODE B, 13,230 x86 instructions
and 901 separately owned after-RET packed switch DATA B.
F827's last growing parent reconstructed the original A7/A8
sprite states and regenerated the authentic 46B shared
default/getter with all 34/34 native unrelocated bytes equal.

F829 adds the next two genuine whole interior game states:

| Native action | Actual original interval | Original CODE/x86 | PE fields |
| --- | --- | --- | --- |
| B4 | 0052533C..00525412 | 215 B /60 x86 | 8 |
| B5 | 00525413..005254E9 | 215 B /60 x86 | 8 |

Both natural C++ motion-restart actions perform genuine
stage/frame initialization, reset game state through
00453E20 and 0040FC50, set original signed heights
+8f/-8f, initial velocity 12.5f/0.75f, real x87
ground comparisons and stage transitions, and
original auxiliary states **8 (B4) /10 (B5)**.
All values were rechecked independently in the
physical original PE by F645, not copied from
another actor or a decompiler.

The native physical original has THREE direct
function-epilogue exits within each state:
JMPs at x86 ordinals 47, 58 and 59, all
targeting original enclosing epilogue 0052CB4F.
In the encompassing void function, normal C++
return is equivalent to the original branch target,
while generic switch-case break routes through
an extra internal default exit. Tracked
probes/FighterScriptedMotionRestartF829.inc
uses the real direct return grammar.

## Full source physical verification

F829 regenerates and verifies the selected F827
parent, then builds one new entire VC7.1 source
with the two native motion cases. The growing
source becomes **17,676 callable B/4,702 x86**
(previously 17,276 B/4,586 x86). Each new 215B
case has **all 60 original x86 instruction
mnemonics, sizes, operand registers, relative
positions and eight physically checked zero-addend
PE call/global targets**. There are only
**six real nonrelocation byte mismatches per
whole case** at offsets 169/170, 206/207,
211/212, all belonging to the three original
enclosing-giant epilogue long JMP operands.
They are not relocation bytes and are not
accepted as independently exact CODE.

Both previously sourced A7/A8 states remain
350B/97-x86 with their 12 original typed PE
fields each and two actual parent-epilogue
JMP byte differences. The complete 46B/16-x86
native default/getter tail STILL has
**34/34 native nonrelocation bytes equal**
plus all three genuine native PE REL32 calls,
saved-this EBP-0x10 and real GPR roles.
The complete original after-RET 901B
packed dispatch DATA remains separately owned.

Run only the newly affected whole fighter:

    scripts/repo-python scripts/verify-scripted-fighter-motion-restart-f829.py

Generated C++, VC7.1 COFF/PDB, comparison logs
and physical original PE evidence remain
in ignored .analysis/f829-scripted-motion-restart/.
The original 46,755B giant is STILL NONEXACT,
with many other source states incomplete.
No split-case or whole authored exact CODE
accepted; no 979-unit cold replay.
