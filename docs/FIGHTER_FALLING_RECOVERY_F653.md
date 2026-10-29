# F653 — strict native falling-recovery stages 0x12C/0x12D/0x12E in giant 00543210

Pinned original supplied Japanese TH075 ver1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Selected native giant `00543210` still contains **58,294 original CODE bytes**
and **943 separate after-RET switch DATA bytes** and is **NOT whole-exact**.
All evidence here comes from newly compiling that complete original parent
C++ probe under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, not from
simply comparing fragments in isolation or trusting an earlier COFF object.

## True original physical native cases

| Original action | Physical original native CODE interval | Whole case x86 | Original CODE bytes | Genuine physical PE/COFF fields |
| --- | --- | ---: | ---: | ---: |
| `0x12C` | `00548272`–`00548341` | 59 | 207 | 6 |
| `0x12D` | `00548341`–`0054841C` | 61 | 219 | 6 |
| `0x12E` | `0054841C`–`005484EB` | 59 | 207 | 6 |
| **New strict contiguous original case interiors** | | **179** | **633** | **18** |

All three cases initialize state word `+0x80` to 1 and zero `+0x7C`
when native stage/frame shorts `+0x62/+0x64` are zero, calling real
reset `00453E20` first only when signed character flag `+0x3AC` is
zero. While that flag is positive, they subtract original global
single-precision float `00658058` from velocity `+0x50` and zero the
velocity/flag only when the result is strictly **less** than genuine
global float `0065782C`. This emits the original `FLD/FSUB`, `FCOMP`,
`FNSTSW AX; TEST AH,5; JP` x87/branch sequence, not an invented
non-equivalent `<=` test. They compare real action `0040FA30` against
native short `+0x70`. Matching triggers action 0 (`0x12C/0x12D`) or
2 (`0x12E`) through genuine `0040FAC0`. Action `0x12D` *also clears*
short `+0xF00`. For stage 2, frame 0, `0x12C` prepares animation
`0x1B` while `0x12E` prepares `0x1D`; `0x12D` prepares `0x1D` at
stage **4**, frame 0. All three exit through the same actual original
shared fighter epilogue at `005515C2`.

For **each case**, the six independent real original PE-targeted fields
are `00453E20` (REL32 reset), `00658058` (DIR32 subtract float),
`0065782C` (DIR32 compare float), `0040FA30` (REL32 action query),
`0040FAC0` (REL32 action setter), and `00453D60` (REL32 animation
prepare). In the unlinked fresh compiler object, absolute float
operands contain zero pending a real DIR32 relocation. Only after
verifying **each** ordinal, exact target, type, zero addend, and source
COFF symbol are those two global fields normalized for the comparison;
all GPR register roles, x87 instruction forms, widths and jump/CFG
roles must match the full native cases. No COFF-relocation mismatch is
masked to obtain a convenient `structural-exact` result.

The actual F653 native C++ source is the shared ordinary-C++
[`FighterFallingRecoveryF653.inc`](../probes/FighterFallingRecoveryF653.inc),
included with the three original action/state parameters, in one
parent source TU. [`verify-fighter-falling-recovery-f653.py`](../scripts/verify-fighter-falling-recovery-f653.py)
regenerates the giant source from native dispatch evidence (not from
ignored historic compiler outputs), cold-builds **only** this giant,
checks the full original bounds of the three new cases and typed
fields, and reuses the strict F651/F652 proof for the immediately
preceding CF/D0/D1/D2 plus earlier native cases and the full after-RET
switch DATA, against the **same new** COFF object. Real original
`0x12F` is checked as the next physical handler; no invented handler
or internal case gets independent whole-function acceptance.

Together the seven **consecutive strict original** CF/D0/D1/D2/12C/12D/12E
case interiors cover **402 true x86 roles, 1,392 original inner CODE
bytes and 46 physical typed PE/COFF fields** in this selected giant,
but **zero new exact independently callable functions**. Across all
F598–F653 giant research, **575 strict internal native case bodies /
155,094 source-backed internal original CODE bytes** remain separate
from the unchanged official whole-function exact ledger:
**943 whole authored functions /862,726 original CODE bytes**.
None of the 22 giants is accepted whole.

## Targeted reproduction

```bash
scripts/repo-python scripts/verify-fighter-falling-recovery-f653.py
# Also test the retained earlier standalone F651 source path after verifier refactor:
scripts/repo-python scripts/verify-fighter-resource-shots-f651.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The newly compiled whole-parent CPP/COFF/PDB, compiler log and original
native case/field summary are under ignored
`.analysis/f653-fighter-falling-recovery/`. Do not commit or delete
those private generated artifacts. Neither a 943-unit cold replay nor
an external Oracle acceptance was performed.
