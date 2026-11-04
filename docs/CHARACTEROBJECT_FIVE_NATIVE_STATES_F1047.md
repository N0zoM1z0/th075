# F1046–F1047 — Five authentic game states in the 81KB CharacterObject Boss

This work continues original Japanese TH075 v1.11 single-switch
`CharacterObject::Advance` at **0050A580**: 81,539 original CODE bytes
and 17,435 x86 instructions, followed by 567 independently owned
sparse jump-table DATA bytes. The full original callable is still
**NONEXACT**; its C++ prototype still has many marked, unimplemented
game states. Previous F1045 recovered the actual `0x320` source;
F1047 now adds **four further real full state bodies** in their
natural original control flow, not independent callable functions:

- `0x322` at **0050AC27..0050AD46**: the original `+0x7C`
  state 5/6 transition, real reset/motion initialization, alpha,
  gain and native action calls. Source uses the genuine signed-short
  animation stage/frame and real `+0x30` float, not a marker write.
- `0x32B` at **0050CCC3..0050CD7A**: actual stage-zero motion,
  facing/opacity setup and native action completion with `2.0f`
  scaling.
- `0x32D` at **0050CE97..0050CF7A**: copies native parent
  coordinates only under the authentic action `0x12D`, initializes
  scale/opacity and dispatches the genuine action completion.
  Crucially, the original copies the two coordinates with raw
  **32-bit MOVs**. C++ float assignment incorrectly generated
  `FLD/FSTP`; two `unsigned int` bit-preserving member copies
  recovered all native **50/50 mnemonics and 50/50 GPR roles**.
- `0x332` at **0050D88E..0050D929**: authentic stage-zero
  animation/motion reset, float scale, opacity, and native
  completion callback. After restoring the prior `0x32D` DWORD
  behavior, the subsequent whole-source register phase also
  recovered all **35/35** native GPR roles.

Independent later full-native controls confirmed that, for the `0x32B`, `0x32D` and `0x332` sources, **every remaining width mismatch is exactly a three-byte `EBP-0xAC` versus `EBP-4` saved-receiver displacement**. There are 14, 17 and 12 such native/partial-frame width differences respectively. The tracked multi-state verifier now asserts this physical fact rather than merely counting wrong widths.

The original whole 81KB function remains much larger than this
partial prototype. The chosen original game action-to-physical-
handler mapping is not invented from source order: `F1047`
independently reads its pinned original PE, confirms the complete
native CODE SHA-256, every real 92-entry DIR32 jump-table equivalence
partition and all 199 original sparse-map bytes, and cold-builds
**the one affected complete current source prototype** with pinned
normal VC7.1.

| Native original action | Native CODE/x86 | Generated inner CODE/x86 | Matching mnemonic | Matching GPR | Genuine PE refs |
| --- | ---: | ---: | ---: | ---: | ---: |
| `0x320` | 439B / 91 | 335B / 91 | 91/91 | 91/91 | 6/6 |
| `0x322` | 287B / 56 | 216B / 56 | 56/56 | 18/56 | 4/4 |
| `0x32B` | 183B / 39 | 141B / 39 | 39/39 | 39/39 | 3/3 |
| `0x32D` | 227B / 50 | 176B / 50 | 50/50 | 50/50 | 3/3 |
| `0x332` | 155B / 35 | 119B / 35 | 35/35 | 35/35 | 3/3 |
| **Five real game cases** | **1,291B / 271** | **987B / 271** | **271/271** | **233/271** | **19/19** |

All physical native PE field types/targets were independently decoded
at their original instruction ordinal and field offset. Every source
symbol's recorded `AtXXXXXXXX` identity and zero COFF addend matches
that physical original target; no address was assumed merely from a
C++ name. The native original case `0x322` still has a different GPR
phase because the preceding `0x321` is **not** reconstructed and is
still a synthetic marker in this whole source. The compiler's original
wide `EBP-0xAC` saved receiver and `0x3A0` real frame are also missing
from the partial 2,435B/489-x86 emitted callable; the remaining
instruction **width** mismatches in all five cases are real and
cannot be covered by truncating or relocation masking.

The source keeps the real original `0x320` from F1045, adds actual
`0x322`, `0x32B`, `0x32D` and `0x332` as separate readable case
fragments in the ONE large function's switch, and leaves other actions
explicitly unimplemented. The complete afterRET original DATA layout
remains 92 DIR32 + 199 non-field bytes. The earlier 32-variant
`0x320` C++ grammar verifier was also replayed against this updated
partial parent, preserving the selected **91/91** native mnemonics
and roles instead of silently treating the former smaller source as
current.

Run only the two affected source-research checks:

    scripts/repo-python scripts/verify-characterobject-multi-state-f1047.py
    scripts/repo-python scripts/verify-characterobject-boss320-f1044.py

Source, COFF/PDB, compiler logs and original-native receipts are
retained under ignored `.analysis/f1047-object-multistate/` and
`.analysis/f1044-object320-grammars/`. No byte arrays or assembler
were introduced into source; no game target was patched; no truncated
case was counted as a separately exact original function. **Zero new
accepted original CODE bytes; whole 81KB callable remains nonexact.**
No 979-unit corpus replay was run.
