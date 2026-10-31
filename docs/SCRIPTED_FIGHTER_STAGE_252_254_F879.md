# F879 — Three native byte-decrement game states and false aggregate CODE length

Pinned Japanese TH075 1.11 original fighter at 005214B0
owns 46,755 callable CODE B and 901 separate afterRET DATA B.
The real original states 252 at 005290D2, 253 at 005291D6
and 254 at 005292DA are THREE independent dispatch entries,
not independently callable leaf functions:

| Original state | Whole native CODE B | x86 | PE fields |
| --- | ---: | ---: | ---: |
| 252 | 260 | 72 | 6 |
| 253 | 260 | 72 | 6 |
| 254 | 224 | 63 | 6 |
| Total | 744 | 207 | 18 |

All three decrement original BYTE this+0x366 at stage0,
reset native motion and use stage5 sprite0x37 through
00453C80, real X+0x44, float Y+0x48 plus actual
global00657888, PrepareActionAt453D60(0x21)
and clear original owner this+0x2E8 -> short+0xEFA.
Only original 252/253 check actual short+0x3B6==0
and dword+0x7C==1 and write short+0x3B0=1000.
Original 254 has no such condition.

Ordinary C++ byte re-assignment and compound subtraction
instead emit MOVZX r32 and nonnative arithmetic. Real
C++ prefix/postfix 8-bit decrement restores MOV r8,
SUB r8,1 and MOV r8 memory grammar. But the CURRENT
incomplete giant's register phase is still wrong:

| State | Original native SUB | Current VC7.1 SUB | Whole generated case |
| --- | --- | --- | --- |
| 252 | DL,1 (3B) | AL,1 (2B) | 259B / 72x86 |
| 253 | CL,1 (3B) | DL,1 (3B) | 260B / 72x86 |
| 254 | AL,1 (2B) | CL,1 (3B) | 225B / 63x86 |

TEN legitimate used C++ decrement variants were compiled
in the complete fighter, including signed/unsigned prefix/
postfix, compound and actually borrowed reference operands.
Equivalent byte operations preserve register phase; named
references change the whole frame and cannot be cropped.

**Crucial misleading aggregate length:** source 259+260+225
equals **744 B**, exactly like original 260+260+224, but
the full original 252/254 case lengths differ by -1/+1.
Consequently ALL six true original physical PE relocation
locations for 252 are one byte later than source; ALL six
true original physical PE relocations in 254 are one byte
earlier. Matching aggregate code length is NOT exact source.

Current source 253 has full 260B/72-x86 original grammar
and all six physically correct PE call/global targets,
but still differs at 47 genuine GPR operand bytes
plus two original enclosing giant epilogue JMP bytes
(+256/+257). No internal case earns exact CODE credit.

One affected full normal VC7.1 fighter now emits
**32,948 callable CODE B/9,253 x86**, up from
F878 32,249/9,052. The tracked verifier checks
original distinct entry boundaries, all eighteen
true original PE target destinations and their
shifted native-vs-current operand locations,
the prior 51 complete source-backed game cases,
all five native 901B packed afterRET tables
and common getter's four authentic GPR byte errors.
Original 46,755B giant remains NONEXACT.

Reproduce ONLY this original giant:

    scripts/repo-python scripts/verify-scripted-fighter-stage-252-254-f879.py

Generated full C++, VC7.1 COFF/PDB, ten source
controls and original pinned-PE evidence remain under
ignored .analysis/f879-scripted-triple252/.
No original binary modification, padding, ASM or
all-unit cold replay.
