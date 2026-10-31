# F880 — Three native sprite37 handlers and authentic 16-bit stage8 counter

The pinned original Japanese TH075 v1.11
resources/th075.exe fighter at 005214B0
owns 46,755 callable original CODE B
and five separately owned afterRET
packed switch tables of 901 DATA B.

Three complete independently bounded
native switch cases were reviewed:

| Original case | Whole original CODE B | x86 | PE fields |
| --- | ---: | ---: | ---: |
| 255 | 258 | 75 | 7 |
| 256 | 186 | 55 | 6 |
| 257 | 258 | 75 | 7 |

All original cases reset native
motion at stage0 and initialize
short +F00=0. All three check
the real native current-action
getter, setting action **9**
on observed +70 completion,
then fire sprite37 through
original 00453C80 at stage5,
using integer X+44, float
Y+48 plus original global657888,
and real facing byte+66.
They then prepare animation0x21
through 00453D60.

Original 255 and 257 also check
stage8/frame0 with SHORT+F00
less than 1; they genuinely
increment this 16-bit counter
and invoke native auxiliary6
at 0040FB40. The middle state
256 does NOT have this event.

The selected natural full-parent
C++ emits original 258/186/258
inner CODE B and 75/55/75 x86.
Real 16-bit prefix increment
naturally produces native
MOV r16 and ADD r16,1; a
dword-like assignment instead
generates MOVSX and loses a
real original CODE byte.
Five actual whole VC7.1
source variants compare
these native and false
16-bit expressions.

The original PE field offsets
are [26,78,102,146,167,177,249]
for 255 and 257 and the first
SIX positions for 256.
All twenty real physical
original game PE call/global
fields, types, zero addends
and actual destinations
are checked in the newly
compiled full VC7.1 parent.

One new complete original-shaped
source parent is **33,605
callable CODE B/9,452 x86**
(F879 32,948/9,253), with
all five original afterRET
packed 901B tables checked.
The same new source object
rechecks **54 earlier native
case interiors**, including
1FD original one-byte CMP
negative and 252/254 wrong
individual original PE field
positions, and the 46B
native getter's four real
GPR byte differences.

The new cases are NOT exact:
255/257 each have 48
genuine GPR operand byte
errors plus two original
whole-giant final JMP bytes;
256 retains 32 genuine GPR
plus two final JMP negatives.
The enclosing original
46,755B giant is still
NONEXACT. Do not accept
an internal case as whole
callable CODE.

Targeted original verification
only for this giant:

    scripts/repo-python scripts/verify-scripted-fighter-stage255-257-f880.py

Full VC7.1 C++/COFF/PDB,
source controls and physical
PE receipts remain under
ignored .analysis/f880-scripted-255-257/.
No mass cold replay.
