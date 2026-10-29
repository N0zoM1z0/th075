# F654 — native two-stage falling finish and ground-contact projectile in 00543210

New strict inner case source from the original supplied Japanese TH075
version 1.11 `th075.exe` (SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`).
The original giant fighter `00543210` still owns **58,294 entire CODE
bytes plus 943 separately owned after-RET switch DATA bytes**; it is
not whole-function exact. The pinned normal MSVC VC7.1 source probe
uses `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and a single newly compiled
full giant C++ parent. It does not use hand-copied target code bytes.

## Independent original PE bounds and new native case results

| Native real action | Original whole physical case interval | Native x86 instructions | Original inner CODE | Original typed PE/COFF fields |
| --- | --- | ---: | ---: | ---: |
| `0x12F` | `005484EB`–`0054860B` | 82 | 288 B | 8 |
| `0x130` | `0054860B`–`00548710` | 79 | 261 B | 6 |
| **New strictly backed full inner cases** | | **161** | **549 B** | **14** |

At action `0x12F`, native stage/frame-zero initialization matches
F653's real reset and flag writes. Its signed positive flag gates a
**0.6f** subtract from actual velocity `+0x50` only for stage below
4, and for stage over 3, it applies a separate global **0.9f**
subtraction unconditionally, clamping only the actual velocity to
zero on the native strict-less-than-float comparison. The two *distinct*
original PE constants are at `00658058` and `00659240`. On original
stage 4, frame 0, it sets velocity to 25.0f and calls real
`00453D60(0x1D)` animation preparation. On action completion, it
transitions through original `0040FAC0(2)`.

At action `0x130`, the original first computes genuine x87
`F32(+0x54) -= F32(+0x5C)`; if original y plus vertical velocity
reaches the floor (`<=` native float at `0065782C`), it changes to
original action 10 and clears the original y/acceleration/velocity
members `+0x48/+0x5C/+0x54`, exiting directly through the real
shared giant epilogue. Otherwise it initializes stage/frame-zero
state, transitions to action 9 at the original action boundary, and
at stage 3/frame 0 prepares animation `0x1D` and spawns kind
`0x339` through genuine `00453A70`. The sprite call's raw x/y
DWORD argument representation is **a provisional compiler/ABI
probe**, not proof of the original historical function declaration.

All original **eight** typed physical source fields in `12F` are
`00453E20` (REL32), `00658058` (DIR32), `0065782C` (DIR32),
`00659240` (DIR32), `0065782C` (DIR32), `0040FA30` (REL32),
`0040FAC0` (REL32), `00453D60` (REL32); native `130` has **six**
real fields: `0065782C` (DIR32), `0040FAC0` (REL32), `0040FA30`
(REL32), `0040FAC0` (REL32), `00453D60` (REL32), `00453A70`
(REL32). The compiler's two `12F` x87 `FSUB` absolute operands
are zero while unlinked, but **each genuine PE target, relocation
type, zero addend and COFF symbol is checked**; only those independently
proved global float fields are normalized. Every other original
GPR/x87 operand, x86 width and CFG branch ordinal matches.

Original physical handlers are contiguous `0x12F→0x130→0x131`,
not separate invented helper functions. The ordinary C++ source
[`FighterFallingFinishF654.inc`](../probes/FighterFallingFinishF654.inc)
contains both cases. Reproducer
[`verify-fighter-falling-finish-f654.py`](../scripts/verify-fighter-falling-finish-f654.py)
regenerates the **entire native fighter parent C++** from original
fingerprints, compiles it fresh using the pinned compiler, and checks
all old strict **CF/D0/D1/D2/12C/12D/12E** cases against the **same
new full-parent object**, including the full independent after-RET
compressed switch DATA. Earlier F653 and F651 standalone verification
remain valid.

Nine consecutive native inner cases now reproduce **563 original x86
instructions /1,941 original CODE bytes /60 real typed PE/COFF
fields** inside this giant, with no independent whole-function CODE
credit. Across F598–F654 the strict whole-interior counter reaches
**577 native action cases /155,643 internal CODE bytes**, still
uncredited. **943 complete authored functions /862,726 CODE bytes
remain accepted**; none of the 22 original whole giants is exact.

```bash
scripts/repo-python scripts/verify-fighter-falling-finish-f654.py
scripts/repo-python scripts/verify-fighter-falling-recovery-f653.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The actual cold-generated parent CPP/COFF/PDB, logs and native field
summary are in ignored `.analysis/f654-fighter-falling-finish/`.
There was no full 943-unit cold replay, original-EXE patch, fabricated
C++ local, or Oracle claim of exact whole-function acceptance.
