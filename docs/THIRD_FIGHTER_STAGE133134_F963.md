# F963 — Third fighter authentic 133 and 134, 798 original native bytes and 19 PE targets

The SHA-pinned Japanese TH075 v1.11 original
`004AC040` giant is **82,796 complete callable
CODE B /22,721 x86**, with **1,126 separately
owned original afterRET jump DATA B**. The
tracked [cumulative C++ father](../probes/FighterWhole004AC040F963.cpp)
still implements only some original cases and
has a different saved-`this` EBP/stack lifetime,
so it is **NOT an exact whole original fighter**.

Re-reading the original PE independently, the
two real game-state boundaries are:

| Original handler | Physical executable interval | Original entire case CODE | External PE targets |
| --- | --- | ---: | ---: |
| **0x133** | **004B1593..004B16AD** | **282 B /84 x86** | **7** |
| **0x134** | **004B16AD..004B18B1** | **516 B /152 x86** | **12** |
| Combined native inner cases | contiguous | **798 B /236 x86** | **19** |

These ARE NOT the other actor's historical
F846/F847 states, which have different native
lengths, projectile kinds and stage transitions.

## Original actor gameplay source

The new [ordinary real 0x133/0x134 C++](../probes/FighterThirdBossStage133134F963.inc)
has the genuine native stage/frame-zero
fall initialization, positive signed fall-flag
ground motion using original **00658058**,
physical threshold **0065782C**, animation
frame completion and 16-bit +0xF00 state
reset in the real **0x133**. Its stage4/frame0
performs original `00453D60(0x1C)`; separate
stage3/frame0 fires a REAL seven-argument
`00453B50` projectile kind **0x324** with
actor raw X/Y bits, signed facing, and actual
trailing 1,0,1 arguments.

The original **0x134** is structurally
different, with stage0 motion initialization
and the actual `00657478` position drop.
It tests real `00657480` velocity stop
and the actual ground float, clamps motion
to 2.0f only when BOTH native thresholds
pass, and executes the original signed
stage LESS THAN **14** landing branch.
The native collision resets actual
movement and calls `0040FB40(0xE)`.
On stage2/frame0 it writes X=12.5f,
vertical velocity=8.5f and drag=0.65f.
Stage7/frame0 fires `00453B50(0x336)`
and independently prepares `00453D60(0x1D)`.
Stage14/frame0 passes the true signed
stage minus two to the auxiliary action.

This original PE-decoded C++ uses genuine
live game member values and call ordering,
not inert pad locals, manually forced
registers or copied native instruction
bytes. The borrowed actor fields do not
establish a complete historical class.

## Entire partial-parent normal VC7.1 and PE audit

The tracked
[`verify-third-fighter-stage133134-f963.py`](../scripts/verify-third-fighter-stage133134-f963.py)
serially compiles TWO **entire original-shaped
partial 82KB fighter C++ parents** (tracked
F962 with two markers versus tracked F963
with both real cases). It independently
rereads the SHA-pinned original full
82,796-B game function and native physical
case boundaries, checks all original
84+152 x86 ordinal mnemonics and widths,
all **19 actual typed zero-addend PE/COFF
target addresses**, and the preceding
native 131 (202B/58x86/5 external fields).

Both full parent outputs additionally
preserve the original **151 physically
owned DIR32 afterRET switch labels and
522 original nonfield DATA bytes**.
Original native PE call/global destinations
are not masked or inferred from stub
instruction indices.

| Whole *partial* original-shaped parent | F962 old markers | F963 natural cases |
| --- | ---: | ---: |
| Emitted partial whole C++ CODE B | 22,896 | **23,664** |
| Whole source x86 | 6,247 | **6,479** |
| 0x133 emitted CODE B/x86 | 15/2 | **282/84** |
| 0x134 emitted CODE B/x86 | 15/2 | **516/152** |
| Original positional mnemonic differences | n/a | **0 in both** |
| Original positional x86 width differences | n/a | **0 in both** |
| **Original 0x133 GPR-role errors** | n/a | **53** |
| **Original 0x134 GPR-role errors** | n/a | **98** |
| Original 133+134 PE target fields checked | stubs | **19/19** |
| Original afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Entire original 82KB game function exact | NO | **NO** |

Importantly, the earlier actor-specific native
131 is still 202B/58x86 with zero wrong
mnemonics and widths, but **36 wrong GPR roles**;
the new 133 and 134 do not conceal or repair
that debt. Native original receiver ownership
lives at EBP−0x64 and full original frame
0x720; the still-incomplete partial parent
has different physical operands even where
mnemonics and instruction widths match.

Reproduce only these two complete C++ parents:

    scripts/repo-python scripts/verify-third-fighter-stage133134-f963.py

Full compiler source/OBJ/PDB, target-PE
verifications and logs remain under ignored
`.analysis/f963-third-original-stage-proof/`,
with initial experiments under
`.analysis/f963-third-133-134/`.

**Zero newly accepted original whole
callable game functions or CODE B;
no all-979-unit cold replay.**
