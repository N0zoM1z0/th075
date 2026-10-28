# Original 82,796-byte CharacterMove action boss: six real switch tables

**Evidence state: original Japanese TH075 PE, NOT an accepted C++ reconstruction.**
The original R048-authored `CharacterMove::AdvanceAt004AC040` is still an
unclassified source-missing function in `config/functions.csv`. The actual
pinned user-supplied Japanese `resources/th075.exe` ver1.11 SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
All numbers below have been independently checked against original PE bytes
using the read-only verifier `scripts/verify-character-move-dispatch.py`.

## Whole original CODE, not an extracted switch fragment

- Original complete CODE extent: **`004AC040..004C03AB` inclusive**;
  exactly **82,796 original authored CODE bytes**, SHA256
  `4dced8c8583edf4b8234505793e28732e19af2adb311d0d39a755f0036e59cfc`.
- Actual full Capstone x86 stream: **22,721 original instructions**,
  **1,361 call instructions**, one final `RET` ending at `004C03AC`.
  The real stack allocation is `0x720`, `this` is stored at EBP-0x64,
  and the signed short action ID at this+0x60 is sign-extended to
  native EBP-0x68. These are physical x86 observations, not assumed
  full class types or C++ source locals.
- Original early guards independently test the signed short at
  this+0x82 and the signed short at `(*(this+0x2E8))+0x3BA` and bypass
  the action dispatcher when nonzero. Original singleton IDs **0x32,
  0x8C, 0x12C, 0x186 and 0x254** are handled separately from six
  indexed-dispatch action spans.
- Whole original decompilation, retained under
  `.analysis/f509-charactermove-megaboss/original-native.c`, is 6,631
  lines / 309,980 bytes, with six `switch(iVar4)` constructs and
  **146 explicitly rendered `case` labels**: 11 + 26 + 31 + 9 + 35 + 34.
  Ghidra's names and casts are hypotheses; PE instruction bytes and
  conditional branches are the source of the facts stated here.

## Contiguous, verified original post-RET switch DATA

Each switch has an actual **indirect `JMP DWORD PTR` instruction in CODE**
and a corresponding DWORD destination table in the original PE *after*
its final `RET`. Four switches also use sparse one-byte indirection maps.
The mapping/table bounds are **not** inferred from Ghidra `case` counts;
all original data bytes and every jump destination have been checked.

| Action input IDs | Original indirect JMP | DWORD table address | DWORD entries | Sparse byte-map address | Sparse bytes |
| --- | --- | --- | ---: | --- | ---: |
| `0x000..0x00A` | `004AC09B` | `004C03AC` | 11 | none | 0 |
| `0x033..0x063` | `004AC0D5` | `004C03D8` | 27 | `004C0444` | 49 |
| `0x08F..0x0D2` | `004AC112` | `004C0475` | 32 | `004C04F5` | 68 |
| `0x12D..0x136` | `004AC148` | `004C0539` | 10 | none | 0 |
| `0x187..0x253` | `004AC188` | `004C0561` | 36 | `004C05F1` | 205 |
| `0x255..0x31C` | `004AC1B2` | `004C06BE` | 35 | `004C074A` | 200 |

The six original dense tables have **151 physical DWORD slots = 604 DATA
bytes**, and their four original sparse index maps have lengths
**49 + 68 + 205 + 200 = 522 DATA bytes**, totaling **1,126
contiguous owned post-RET DATA bytes** at `004C03AC..004C0811`
(inclusive). SHA256 of the *whole* 1,126 bytes:
`bd3fbb666cc78c750efbf154d066c8087cb36225fd34593994240e77ed392377`.
Exactly **14 `CC` alignment bytes** occupy `004C0812..004C081F`;
the next separate original function begins at `004C0820`.
**None of these 1,126 DATA bytes or 14 CC padding bytes is CODE credit.**

All 151 original DWORD slots have individually verified native instruction-
aligned destinations *inside* the original 82,796-byte CODE. Exactly
**147 different native case target addresses** occur; repeated target
addresses reflect original shared defaults, not corrupted data. All 522
sparse indexes are strictly smaller than the corresponding original
DWORD table size and enumerate each legal table index at least once.
The read-only verifier checks original SHA256 for all six individual
DWORD tables, all four sparse byte-index maps, the full CODE and the
whole post-RET DATA area, in addition to the final 14 padding bytes.

## Cross-boss native codegen evidence: Reimu versus CharacterMove

The independent, still-unaccepted original R063 Reimu
`ReimuFighter::AdvanceActionStatesAt0045DD70` has 60,999 whole CODE
bytes and six analogous physical switch tables, as recorded and verified
in `docs/REIMU_ACTION_BOSS_DISPATCH.md`. These are **not the same
function or class**; `CharacterMove` here is separately R048 authored.

Both explicitly test the signed short action ID at this+0x60 and early
state guards at +0x82 and through +0x2E8/+0x3BA, then divide state
space into similar spans. Critically, **the entire original 68-byte
`0x08F..0x0D2` sparse index map is byte-identical** in the two original
PE locations `004C04F5` (CharacterMove) and `0046CCFC` (Reimu), SHA256
`a5a34134b8e8e16d03f131a259adb2621cc4cf6499be28366ab35d452f1f48f6`.
The corresponding DWORD tables contain different native code addresses;
thus this is reliable evidence of a **shared switch-lowering/action-ID
partition**, not permission to reuse Reimu's targets or type layouts.
The later ranges are genuinely different: Reimu switches at
`0x187..0x25A` and `0x25C..0x31C`, while CharacterMove splits at
`0x187..0x253` and `0x255..0x31C` with an explicitly separated
`0x254` state. The native dense table slot counts are also distinct.

Frequent original direct-call targets (not extra CODE credited) include
`00453A70` (222 calls), `0040FAC0` (177), `0040FA30` (143),
`00453E20` (139), `0040FB40` (137), `00453B50` (114),
`00455580` (97), `00453D40` (80), `00453D60` (45) and
`0046D000` (44). These 1,361 original call sites and numerous x87
float/timer/action branches must be faithfully modeled in an **entire
function** before claiming exact C++ or authored CODE credit. Do not
splice native jump bytes or accept partial switches.

### Reproduce the original PE evidence, without compiler or cold replay

```bash
scripts/repo-python scripts/verify-character-move-dispatch.py
scripts/repo-python scripts/verify-reimu-action-dispatch.py
```

The CharacterMove verification script validates pinned PE identity,
full function SHA, all 22,721 decoded x86 instructions and final RET,
all six indirect-JMP operands and their exact dense/sparse contents,
151 real instruction-aligned targets, whole post-RET SHA, final CC
padding and the shared Reimu 68-byte index map. This is a fully
read-only original-target research milestone: **0 newly matched
CharacterMove CODE bytes, 0 DATA bytes accepted, no all-unit cold replay**.
