# F949 — Third original Fighter 004AC040 action C9 fully matches 158 native x86 roles

Pinned Japanese TH075 v1.11 entire fighter at **004AC040**:
**82,796 original game callable CODE B /22,721 x86**,
with separately owned **1,126 original afterRET
jump-table DATA B**. Source is still a partially
reconstructed whole native C++ parent, not an
accepted exact full 82KB function.

The original next handler **0xC9** has authentic
physical interval **004B02B9..004B04CC**,
**531 original CODE bytes /158 x86 /13 real
source PE-targeted external fields**. The preceding
real action C8 is a different, already independently
source-backed F948 149-x86 body with three genuine
width differences because the partial parent has
the wrong native frame and 32-bit x87 scratch slots.

## Actor-specific original C9, not a transplanted other-fighter case

Original complete native x86 proves:

- Original `00454BC0(3,4,0xFF)` storm configuration.
- Distinct signed-short `this+0x62/+0x64` stage/frame
  gates at stage **0,2,4,6**; stage 0 calls actual
  reset `00453E20`, stage2 initially sets X=0,
  stage4 initially sets X=−10.0f.
- Real air-ground test: `this+0x48>0065782C`,
  signed stage **3<stage<6**, subtract actual
  `+0x5C` from `+0x54`, on landing clear
  movement/ground frame and call original
  aux action **6**.
- Native `0040FA30` frame completion transitions
  with `0040FAC0(0)`, independent stage2/frame0
  set X=−50.0f.
- At stage4/frame0, real `+0x54=4.0f`,
  `+0x5C=0.6f`, `+0x50=−30.0f` and **two
  actual `00453C80` shots** of kinds 0x7D/0x7E
  using real source raw `this+0x44` bits,
  **negated signed facing**, native Y `this+0x48`
  plus global **00657888**, and actual
  prepare call `00453D60(31)`.
- True stage6/frame0 exit calls auxiliary action **5**.

The original game C9 is not the same as the
different 58KB original Fighter C9, which uses
different gates and movement constants. The new
tracked ordinary C++ source is
[`FighterThirdBossFourWayC9F949.inc`](../probes/FighterThirdBossFourWayC9F949.inc).
It preserves real values and call ordering
without fake stack locals, forced registers
or manual original instruction bytes.

## Whole partial VC7.1 parent and original-target proof

[`verify-third-fighter-fourway-c9-f949.py`](../scripts/verify-third-fighter-fourway-c9-f949.py)
regenerates the prior complete original-shaped
partial father with existing F938–F948 real
C++ handlers, then fresh compiles TWO entire
normal VC7.1 father source units: the original
C9 two-instruction marker versus new authentic
natural C9. Native physical case boundaries
come exclusively from original afterRET
DIR32 source-label relocations, **not**
generated-stub x86 ordinal guesses.

| Complete *partial* father feature | Old marker | New F949 |
| --- | ---: | ---: |
| Whole generated source CODE B | 19,027 | **19,543** |
| Whole generated source x86 | 5,088 | **5,244** |
| Source real C9 CODE B / x86 | 15B/2 | **531B/158** |
| **C9 wrong original mnemonics** | Unaligned | **0** |
| **C9 wrong original widths** | Unaligned | **0** |
| **C9 wrong original GPR-role instructions** | Unaligned | **0** |
| Real original C9 typed PE targets checked | Placeholder | **13/13** |
| Original separate afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Entire 82KB original exact | NO | **NO** |

The C8 source remains **529B/149 x86 versus
original 539B/149 x86**, preserving the
three honest non-native x86 widths at
local ordinals 106/121/122. Its fifteen
PE/global targets are also checked in the
same two fresh whole-partial-parent sources,
not assumed exact due to similar C9. The
real original save-this stack EBP−0x64
versus partial-source EBP−0x10 is still
unrecovered and changes actual original
machine operands even where GPR role
assignments line up.

Reproduce only the affected whole C++ source:

    scripts/repo-python scripts/verify-third-fighter-fourway-c9-f949.py

The complete compiled source/OBJ/PDB, VC7.1
transcripts and original target-PE verified
receipt are kept machine-locally under ignored
`.analysis/f949-third-real-C9/` with
original exploratory trials under
`.analysis/f949-third-c9-native/`.

**Internal case geometry is source-backed,
not a new independently callable function.
No newly accepted original game CODE, no
all-979 cold replay, no original PE changes.**
