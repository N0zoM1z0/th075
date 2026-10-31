# F951 — Third 82KB Fighter: real original CB gameplay, 131 x86 and eleven true PE targets

The SHA-pinned Japanese TH075 v1.11 original fighter
at **004AC040** has **82,796 callable game CODE B /
22,721 x86**, plus **1,126 separately owned afterRET
DATA B**. Its normal VC7.1 C++ reconstruction remains
a partial source and the entire original fighter is
**NONEXACT**.

The independently decoded original game action
**0xCB** is physically **004B0680..004B0852**,
**466 original native CODE B /131 x86 /11 real
PE-targeted call/global fields**. The previous
natural partial parent had only a 15-B/2-x86
original-shaped placeholder there. F951 replaces
it with actual gameplay C++ at
[`FighterThirdBossFourWayCBF951.inc`](../probes/FighterThirdBossFourWayCBF951.inc).

The original source controls are grounded in its own
physical x86, NOT copied from another fighter's CB:
`00454BC0(3,4,0xFF)` storm setup; stage0/frame0
reset of the genuine signed-short +0xF00 counter,
movement X/vertical velocity/drag fields at +0x50,
+0x54,+0x5C; real ground collision with +0x48,
the threshold float **0065782C**, original
`0040FAC0(0xA)` landing exit, and frame completion
`0040FA30` followed by `0040FAC0(9)`.
At stage3/frame0 the native original sets
X=−11.0f, vertical speed=5.0f and drag=0.6f,
then fires two original `00453C80` bullets
(kind **0x7D/0x7E**) with genuine signed opposite
facing, X based on **facing×68 + actual float
this+0x44**, and Y **this+0x48 +
original global 00658400**, followed by real
`00453D60(31)`.

The bounded
[`verify-third-fighter-fourway-cb-f951.py`](../scripts/verify-third-fighter-fourway-cb-f951.py)
regenerates two *entire original-shaped partial
fathers* (old CB marker vs new CB), serially
compiles both with pinned original normal VC7.1
flags, reads the original hash-attested PE,
resolves all **eleven** typed zero-addend
original PE/COFF call/global target addresses
at their true native instruction ordinals,
and rechecks preceding original C8/C9/CA,
the 151 original afterRET DIR32 local-label
records and all 522 nonfield DATA bytes.
No cropped per-case fake callable function
is compiled.

| Whole partial original-shaped source | Before: CB marker | F951: CB natural C++ |
| --- | ---: | ---: |
| Compiled complete partial father CODE B | 19,958 | **20,397** |
| Compiled whole partial x86 instructions | 5,365 | **5,494** |
| Original CB source CODE B /x86 | 15 /2 | **454 /131** |
| Native original CB CODE B /x86 | 466 /131 | **466 /131** |
| Original CB wrong x86 mnemonics | Not comparable | **0** |
| Original CB wrong GPR-role instructions | Not comparable | **79** |
| Original CB wrong x86 widths | Not comparable | **4** |
| Real original typed PE call/global targets checked | 0 | **11/11** |
| Native afterRET labels/nonfield bytes | 151/522 | **151/522** |
| Complete original game fighter exact | NO | **NO** |

The missing **12 actual original CODE bytes** come
from two separate signed-facing integer-to-x87
temporary lifetimes. The original physical PE
uses two pairs of **6-byte** long-EBP accesses:

- Original CB ordinals **96/97**:
  `MOV [EBP−0x9C],EAX; FILD [EBP−0x9C]`.
  The partial father uses EBP−0x48, giving 3-byte
  instructions instead.
- Original CB ordinals **118/119**:
  `MOV [EBP−0xA0],EAX; FILD [EBP−0xA0]`.
  The partial father uses EBP−0x4C and emits two
  more 3-byte instructions.

The original entire fighter has **0x720 bytes of
stack frame** and a genuine receiver saved at
EBP−0x64; the current 20KB partial C++ source
has neither lifetime/owner layout and assigns
many different GPRs. In particular, **79 native
GPR roles remain wrong**, unlike the previous
C9 or CA source; this is an important negative,
not something relocation masking can conceal.
Do not fabricate filler locals or graft native
bytes to force long accesses. The prior
[F950 CA](THIRD_FIGHTER_FOURWAY_CA_F950.md)
still has two original width differences, and
[F948 C8](THIRD_FIGHTER_FOURWAY_C8_F948.md)
three; [F949 C9](THIRD_FIGHTER_FOURWAY_C9_F949.md)
continues to have all 158 native positional
mnemonic/width/GPR roles matched.

Reproduce *only* the two affected partial parent
source compiles:

    scripts/repo-python scripts/verify-third-fighter-fourway-cb-f951.py

Full original-shaped C++ sources, compiled OBJ/PDB,
native PE verification receipt and compiler logs
are in ignored `.analysis/f951-third-native-CB/`,
with preliminary native x86 experiments in
`.analysis/f951-third-cb-native/`.

**No new accepted original whole callable function
or CODE byte; no all-979-unit cold replay; no
original EXE or tracking ledger mutation.**
