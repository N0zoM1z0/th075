# F664 — two strictly reconstructed complete original native cases in giant 00543210

Pinned user-supplied Japanese TH075 v1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This report addresses **native cases 0x200 and 0x201 in the actual original
58,294-CODE-byte giant fighter `00543210`**, plus its 943 separately
owned after-RET switch DATA bytes. The **entire giant is still NONEXACT**.
Only these complete physical original *internal case bodies* are strictly
source-backed, not independently callable whole original functions.

## Original physical bounds and source-backed native CODE

| Genuine original case | Actual original native CODE extent | Native x86 instructions | Strict original inner CODE B | Genuine typed PE/COFF fields |
| --- | --- | ---: | ---: | ---: |
| `0x200` | `0054C18F`–`0054C2E6` | 102 | **343** | 8 |
| `0x201` | `0054C2E6`–`0054C49A` | 126 | **436** | 9 |
| **New strict original native complete interiors** | | **228** | **779** | **17** |

Both genuine original action cases reset the fighter's movement and animation
control state at stage and frame zero (`+0x62/+0x64`), set real short
`+0x80=1`, zero real DWORD `+0x7C`, signed flag `+0x3AC`, and real short
`+0xF00`. At stage greater than seven they subtract the actual native
single-precision original PE float **`00659240`** from horizontal motion
at `+0x50`, clamp it to zero on the original strict-less-than-zero x87
condition (`0065782C`, with `FNSTSW AX; TEST AH,5; JP`), and at stage
seven with control DWORD `+0x7C==2` invoke the real `0040FB40(8)` and
set horizontal motion to 10.0f. They transition through authentic
`0040FA30` and `0040FAC0(0)` at the animation boundary.

At stage five, frame zero, both cases call original `00453D40(7)` then
spawn a **kind 0x3C** projectile through the physical original
`00453C80`, passing actual `+0x44/+0x48` position as raw DWORD bit
arguments and the signed side byte at `+0x66`. This raw-argument
C++ method declaration is a *provisional native ABI compiler probe*;
its original historical C++ signature is not independently known.
At stages seven and eight (frame zero) the original writes 50.0f and
10.0f to `+0x50` in order. Native `0x201` adds a real additional
stage-eleven one-shot branch: only when the signed short `+0xF00==0`
does it increment the counter as a native **16-bit** value, invoke
`0040FB40(2)`, zero `+0x7C` and set `+0x80` to one. This real
additional branch accounts for 93 more native CODE bytes than `0x200`.

## Actual whole-giant VC7.1 source and strict original PE/COFF proof

The ordinary original-backed C++ fragment
[`FighterSpecialStageF664.inc`](../probes/FighterSpecialStageF664.inc)
is included in a regenerated *complete parent C++ translation unit*,
not compiled as a detached function or a copied assembly blob.
[`verify-fighter-special-stage-f664.py`](../scripts/verify-fighter-special-stage-f664.py)
freshly compiles **only the selected entire giant** with pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. The verifier independently decodes
the **full real original physical CODE intervals**, including their
actual next physical case boundaries, genuine common native shared exit
`005515C2`, instruction counts, sizes and branch targets. It validates
all 17 actual PE-targeted source fields: original x86 ordinal, physical
original destination, real typed COFF `REL32` call or `DIR32` float
symbol, zero addend, and exact ownership in each whole native case.
Only physically authenticated *unlinked* floating-global fields may be
normalized; every other GPR/x87/CFG register operand and instruction
width must agree. An additional **raw EBP stack operand** pass permits
only the known original receiver at EBP−0x44 to compile at EBP−8;
no other original local displacements may be changed or suppressed.

Critically the same new full-parent compiler object is used to reverify
all preceding **17 strict original fighter case interiors**
`CF/D0/D1/D2/12C/12D/12E/12F/130/131/133/134/135/136/187/188/189`,
all preceding true native parent switch conditions, and the **complete
943-byte independently owned after-RET switch DATA**. The real nonexact
scratch cases `0x186`, `0x18A`, and `0x18B` remain explicitly negative
controls and are *not* included in strict credit. Neither is the
historical `0x132` shared default handler miscounted as a new physical
native case.

The selected entire giant now has **19 strictly source-backed genuine
internal cases /1,437 original x86 /4,971 original internal CODE bytes /
132 authentic PE/COFF fields**; these are not one uninterrupted run
because of other nonexact original cases. Across F598–F664 the
research-only strict original fighter *internal case* cohort increases
to **587 cases /158,673 original internal CODE bytes**. **Zero new
independently whole-function exact authored CODE** is accepted, the
22 original fighter giants remain whole-NONEXACT, and the official
whole-authored exact numerator stays **943 functions /862,726 original
CODE bytes (43.71% reviewed)**.

## Targeted reproduction

```bash
scripts/repo-python scripts/verify-fighter-special-stage-f664.py
scripts/repo-python scripts/verify-fighter-motion-shots-f661.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Newly compiled original giant CPP/COFF/PDB, compiler log and authentic
original physical PE/COFF field receipts are preserved under ignored
`.analysis/f664-fighter-special-stage/`. No machine-code graft,
original executable modification, fake locals, full 943-unit cold
replay, or external Oracle whole-function acceptance was used.
