# F1023 — Original 2BC/2BD/2BE GPR phase, 20 true full-father controls

This research uses the SHA-pinned Japanese TH075 v1.11
004AC040 original **82,796 CODE B /22,721 x86**
function, not one of the 58KB or 46KB fighter variants.
F1020 has already restored the normal VC7.1 whole
source to the actual **82,796 CODE B /22,721 x86**,
native saved-this EBP−0x64 and 0x720 frame. This
experiment therefore measures a true remaining
register-phase problem rather than a partial-frame artifact.

The physical original late states are contiguous:

| Original state | PE original CODE B/x86 | True original PE external targets | Wrong native GPR-role positions in current C++ |
| --- | ---: | ---: | ---: |
| 2BC | **755/199** | 15 | **128** |
| 2BD | **742/196** | 15 | **125** |
| 2BE | **1,607/471** | 50 | **125** |
| 2BF | **2,167/616** | 65 | **0** |

All current 2BC/2BE original mnemonic and x86 width
positions align. Original 2BD local ordinal133 is
still a real 5-byte ADD EAX,0xB4, whereas the C++
uses 6-byte ADD EDX,0xB4. Its correctly native
target-mnemonic count does not make that case exact.

Original 2BC and 2BD require their initial MOV/MOVSX
register chain EDX→EAX; the current original-shaped
C++ emits ECX→EDX. The following 2BE starts with
another one-register GPR role rotation; 2BF returns
to the real native phase and remains correct.

The [independent original PE verifier](../scripts/verify-third-fighter-stage-2bc-phase-f1023.py)
compiles **20 ENTIRE 82KB normal VC7.1 C++ fathers**,
varying only genuinely used original stage0/frame0
conditions and actual script field access, including
nested if, De Morgan, literal-first equality,
direct boolean checks, real redundant signed casts,
readonly and volatile borrowed signed-short views,
swapped pure conditions, original adjacent F00/F02
borrowed owner typing, real F00 initialization order,
and the original scoped guard. No fake locals,
register forcing, byte grafts or CROPPED case
comparison are allowed.

Every candidate has the original **82,796B/22,721 x86
count and native0x720 frame**, all original 151
afterRET DIR32 labels, **522 nonrelocation afterRET
bytes**, and all **145 physical original 2BC–2BF
typed PE external destination fields** independently
verified. The original 2BD width and the three-state
GPR phase remain wrong in all 20 sources:

| Verifier outcome | Number of complete parents |
| --- | ---: |
| Same 12 whole native width defects as F1020, 6,958 whole GPR errors | **19** |
| Four additional native widths due to reordered real F00 store, GPR unchanged | **1** |
| Any improvement to 2BC/2BD/2BE GPR errors | **0** |
| Any new accepted exact full original callable | **0** |

No alternate source is selected: the strict original
source's initializer order is preserved. These controls
rule out these 20 particular grammar ideas; they do not
establish that the genuine native C++ register phase is
unrecoverable. The next root-cause search should inspect
earlier emitted case/source allocation and original
source lifetime, without perturbing 2BF or the real
whole-function frame.

Reproduce only these 20 affected full-parent compiles:

    scripts/repo-python scripts/verify-third-fighter-stage-2bc-phase-f1023.py

All complete original-shaped C++/OBJ/PDB, logs, physical
PE-field checks and complete-father results are retained
under ignored .analysis/f1023-third-native-proof/
and .analysis/f1023-native-2bc-phase/.

**No new complete-original callable GAME CODE credit;
no 979-unit mass cold replay.**
