# F938 — Third giant Fighter 004AC040: real state 0x59 replaces a placeholder

Original SHA-pinned Japanese TH075 v1.11 native function
**004AC040** spans **82,796 complete callable CODE B / 22,721 x86**,
plus **1,126 separate afterRET jump DATA B**. This is a third,
independently authored giant—not the 58KB 00543210 or 46KB 005214B0.
**The entire 82KB native function remains NONEXACT** and the current
whole natural C++ is structurally incomplete: many following
native cases are still explicit C++ placeholders.

The previous genuine F652 whole-parent draft had the real
ten-projectile action 0x58, but its **next original action
0x59 was just a 15-byte /2-instruction marker**. The
original PE independently identifies its real consecutive
state interiors:

| Physical original action | True game address | Original CODE and instructions |
| --- | --- | --- |
| 0x58 | 004ADD25..004ADEFA | **469 B /135 x86** |
| **0x59** | **004ADEFA..004AE05E** | **356 B /95 x86** |

The original 004AC040 state 0x59 has genuine *stage 3*
entry, current +0x30 random-offset accumulation,
float motion +0x54−+0x5C, native threshold +0x48/+0x54,
two signed-short F00/F02 conversions via real
`__ftol2`, true original reset/action/motion calls,
and its stage-3/frame-0 secondary branch. This is
distinct from 00543210's **stage >1** entry.
The original complete actor receiver is at **EBP−0x64**
at this position, not the current incomplete draft's EBP−8.

The tracked original-shaped whole-source fixture
[`FighterWhole004AC040F938.cpp`](../probes/FighterWhole004AC040F938.cpp)
reuses the already independently reconstructed natural
C++ body in `FighterScriptedBounce59F813.inc`, now
confirmed against this third original physical game actor.
This is **an actual source replacement**, not merely
a test of a potential source spelling; the former
0x59 marker is gone from the tracked selected giant
fixture. No arbitrary dummy locals, manual assembler
or byte grafts are used.

The tracked [F938 verifier](../scripts/verify-third-fighter-real-bounce-f938.py)
fresh-compiles THREE complete original-shaped VC7.1
whole parents: previous F652 0x59 marker source,
new tracked real body, and a third real preceding
ten-shot postincrement-loop C++ source control.
For all three, it independently rereads the original
PE and maps **actual original afterRET jump-table
physical case VAs to the source DIR32 relocated labels**,
never assuming placeholder ordinal offsets represent
original handler identities.

| Entire compiled original-shaped parent | Prior placeholder | F938 native body | F938 postincrement control |
| --- | ---: | ---: | ---: |
| Generated callable CODE B | 15,972 | **16,312** | 16,312 |
| Generated source x86 | 4,187 | **4,280** | 4,280 |
| Real state 0x58 native mnemonics/widths/GPR wrong | 0/0/0 | **0/0/0** | 1/2/40 |
| Real 0x59 generated CODE B /x86 | 15/2 | **356/95** | 356/95 |
| Real 0x59 native opcode/width differences | Not aligned | **0/0** | **0/0** |
| Real 0x59 native GPR-role differences | Not aligned | **19** | **0** |
| State 0x59 original PE target-checked COFF fields | Not real | **16/16** | **16/16** |
| Original-shaped afterRET DATA | 1,126 B | **1,126 B** | 1,126 B |
| Actual local DIR32 source/table labels | 151 | 151 | 151 |
| Original afterRET nonfield data bytes matching | 522/522 | **522/522** | 522/522 |

**Source note:** The 82KB native original has 22,721 x86,
but F938's still-partial giant C++ emits only **4,280 x86**,
so the entire parent is NOT byte-, instruction- or
relocation-equivalent to the game executable. The 19
GPR differences within the new genuine action and the
source/native receiver EBP difference remain. Two state
0x59 body widths being identical does not prove whole
code or exact independent callable function.

The third experiment reproduces F931/F932's surprising
cross-actor source-lowering fact: changing the preceding
native-strict 32-bit for loop into natural 32-bit
`while (burst++<10)` gives **0/95 wrong GPR
roles in the next true 0x59**, but LOSES native
strict 0x58 by 1 mnemonic, 2 widths and 40 GPR-role
instructions. The F938 tracked real-body/strict
predecessor source remains selected; the diagnostic
while alternative is NOT adopted.

Targeted reproducible verifier (not a full cold replay):

    scripts/repo-python scripts/verify-third-fighter-real-bounce-f938.py

Three complete compiled C++/OBJ/PDB, source logs and
SHA-pinned original PE-backed results are retained
in ignored `.analysis/f938-third-original-bounce-proof/`.
Earlier preliminary experiments under
`.analysis/f938-4ac040-native59/` remain untouched.

**No accepted new whole-game CODE or original case-only
byte credit. No 979-unit all-unit replay.**
