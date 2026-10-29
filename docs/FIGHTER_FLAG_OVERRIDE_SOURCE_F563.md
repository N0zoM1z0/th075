# F563 — two full-original fighter giants: real positive-FLAG secondary motion

**Native Japanese TH075 v1.11 source/code-generation evidence only, not
whole-fighter exact CODE.** Original pinned SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This independent investigation decodes and hashes two *entire* authored
fighter-control originals: `004F7130` (**44,211 CODE bytes**) and
`005AEEC0` (**71,616 CODE bytes**), **115,827 complete unaccepted CODE
bytes** in total. Their full original physical jump tables and after-RET
sparse index DATA (975 and 1,067 bytes respectively) are validated
before compiling any candidate. A source-level action subrange must NOT
be registered as an independent original exact function.

## What was missing from the previous fighter source models

These roles have a true **two-stage motion initializer**: after the
normal stage-2 position/velocity/speed assignments, original native C++
tests signed `FLAG > 0`, and if true overwrites those three fields with
**fighter-specific secondary motion**. This is verified by physical
original `MOVSX [owner+0x3AC]`, `TEST`, `JLE` and six original
`MOV` source/destination instructions in each conditional branch.
It is *not* the same as always applying an extra move or copying a
common character's motion constants.

For the entire 44,211-byte `004F7130` original:

- Native action **6** (125 x86 instructions / 441 CODE bytes): the stage-2
  base motion is `(0.0f, 13.0f, 0.4f)`; if `FLAG > 0`, replace it with
  `(2.0f, 10.0f, 0.25f)`. Do **not** clear FLAG in this branch.
- Native action **7** (127 instructions / 451 bytes): base motion is
  `(3.0f, 13.0f, 0.4f)`; if `FLAG > 0`, change it to
  `(4.5f, 10.0f, 0.25f)` and **only then** clear FLAG. This
  conditional additional assignment accounts for two more native
  instructions than action 6.
- Native action **8** (104 instructions / 362 bytes): use real
  `(-4.0f, 13.0f, 0.4f)` initial motion, and clear FLAG **between**
  the position and velocity stores, not after all three floats.

The 71,616-byte `005AEEC0` original is **different**:

- Native action **6** (125 instructions / 441 bytes): base
  `(0.0f, 16.0f, 0.75f)`, overridden by `FLAG > 0` to
  `(3.0f, 15.0f, 1.25f)`; no FLAG clear.
- Native action **7** (115 instructions / 393 bytes): only normal
  `(8.0f, 16.0f, 0.75f)` initialization with the genuine
  `0040FB40(5)` stage/x87 auxiliary call. No second motion override.
- Native action **8** (102 instructions / 352 bytes): only
  `(-8.0f, 16.0f, 0.75f)` and no FLAG clear, nor auxiliary-stage
  call. These 102 instructions are *not* the 104-instruction case from
  `004F7130`.

Each native action 6/7 includes the earlier original signed-short
stage-four and float threshold `00657D14` check, with the real
`0040FB40(5)` conditional auxiliary callback. All six retain genuine
actor `call dword ptr [edx]` final virtual dispatch and true x87
collision/reset/control behavior.

## Whole-native, affected-only C++ and COFF verification

The tracked reproducer
[`scripts/verify-fighter-conditional-override-actions.py`](../scripts/verify-fighter-conditional-override-actions.py)
re-reads the original *complete* fighter CODE and physical after-RET
switch tables using the independent native F537 inventory, derives and
checks real motion float bit patterns and source action structure, and
**fresh-compiles one normal C++ switch prototype per selected original
fighter** under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. These source units implement the
**complete original internal action 6, 7, 8 cases**; all other cases
stay diagnostic-only test marker stores, **not** restored original
body logic.

Across **2/2** new independent native C++ probes:

- All six complete internal action bodies, **698/698 original x86
  instruction mnemonics and actual per-role EAX/ECX/EDX registers,
  x87 operand roles, conditional branch graph, member accesses and
  instruction lengths** match their compiled C++ source case-by-case.
- **44/44 authentic typed physical COFF `REL32`/`DIR32`
  call/global fields** match the original's exact case instruction
  ordinal, field type and source symbol; 8/8 for each case 6/7 and
  6/6 for each case 8. Real actor virtual call registers are separately
  checked, not invented relocation targets.
- **305 real native-style physical DWORD switch COFF references**,
  all original repeated/default destination partitions,
  **822/822 literal original sparse index bytes**, and both complete
  original after-RET DATA extents (**2,042 total bytes**) agree.
  All of these table bytes are DATA, not new CODE credit.

| Whole original fighter | Case 6 | Case 7 | Case 8 | Genuine case COFF fields | All switch DWORD refs | Original sparse bytes |
| --- | --- | --- | --- | ---: | ---: | ---: |
| `0x004F7130` | 125 instructions / 441 B | 127 instructions / 451 B | 104 instructions / 362 B | 22 | 141 | 411 |
| `0x005AEEC0` | 125 instructions / 441 B | 115 instructions / 393 B | 102 instructions / 352 B | 22 | 164 | 411 |

## Reproduce, without all-unit replay

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-boss-family.py
# Only the one newly affected original-specific small TU:
scripts/repo-python scripts/verify-fighter-conditional-override-actions.py --boss 0x004F7130
# Or exactly the two newly affected C++ probe TUs, serially:
scripts/repo-python scripts/verify-fighter-conditional-override-actions.py
```

Fresh sources, COFF objects/PDB/compiler logs and full PE-checked case
summaries are under ignored `.analysis/f563-conditional-override-source/`;
independent original instruction and source probes remain under
`.analysis/f563-125-127-fighter/`. Original native complete case CODE
bytes total **2,440**, but remain inside the **115,827 bytes of still
entirely nonexact giant functions**. There is *zero* new accepted exact
CODE/DATA, no partial function credits, no artificial padding, no
all-unit cold replay and no external Factory/Oracle receipt.
