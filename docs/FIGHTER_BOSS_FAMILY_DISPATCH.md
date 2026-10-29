# TH075: all 22 independently owned whole fighter action bosses, real after-RET DATA

**Status: original PE research, NOT reconstructed C++ and NOT exact CODE credit.** F537 extends this whole-function research with the independently decoded **original 7,152 action-ID → native-entry** mapping across all 22 bosses, including 64 isolated `JE` branches and 4,847 indexed inputs that reach shared defaults; see [F537 action-case resolution](FIGHTER_ACTION_CASE_RESOLUTION.md). This does not convert any original boss into exact C++.

This independently checks the *entire* original CODE stream for each of the
remaining 22 R-origin authored fighter controllers in the pinned Japanese
`resources/th075.exe` 1.11. The actual native PE SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The 22 full functions occupy **1,102,055 original authored CODE bytes**;
they are still pending. This is not 1,102,055 newly restored bytes.

The 22 are a natural structural split, independently read from their actual
original native x86, *not* inferred from arbitrary Ghidra class labels:
11 `CharacterObject::Advance`-family functions contain **one** native
indirect switch and a single compressed byte-index table; 11
`CharacterMove::Advance`/`ReimuFighter::AdvanceActionStates`-family
functions contain either **six** (two members) or **seven** (nine members)
independent native indexed jumps. These names are provisional abstractions
and do not prove original C++ source names, virtual owner layouts, or
interchangeable per-character jump targets.

## Verified whole original native CODE + after-RET physical DATA

| Native start | Complete CODE bytes | Native instructions | Real `call`s | Indexed jumps | DWORD slots | Sparse index bytes | Post-RET DATA bytes |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| `0045DD70` | 60,999 | 16,837 | 1,026 | 6 | 142 | 522 | 1,090 |
| `00476A40` | 50,915 | 13,357 | 603 | 1 | 66 | 199 | 463 |
| `00486550` | 50,735 | 14,260 | 981 | 7 | 163 | 412 | 1,064 |
| `0049C8F0` | 46,596 | 12,297 | 588 | 1 | 76 | 199 | 503 |
| `004AC040` | 82,796 | 22,721 | 1,361 | 6 | 151 | 522 | 1,126 |
| `004CA6E0` | 42,511 | 11,201 | 535 | 1 | 56 | 198 | 422 |
| `004D7E70` | 43,601 | 12,231 | 806 | 7 | 140 | 409 | 969 |
| `004EBDA0` | 33,293 | 8,789 | 432 | 1 | 60 | 198 | 438 |
| `004F7130` | 44,211 | 12,442 | 816 | 7 | 141 | 411 | 975 |
| `0050A580` | 81,539 | 17,435 | 846 | 1 | 92 | 199 | 567 |
| `005214B0` | 46,755 | 13,230 | 876 | 7 | 139 | 345 | 901 |
| `00536400` | 39,999 | 10,573 | 574 | 1 | 67 | 199 | 467 |
| `00543210` | 58,294 | 16,471 | 1,039 | 7 | 156 | 319 | 943 |
| `0055AC80` | 28,432 | 7,653 | 394 | 1 | 58 | 198 | 430 |
| `00564BE0` | 61,872 | 13,596 | 819 | 7 | 131 | 350 | 874 |
| `0057D580` | 43,845 | 11,694 | 601 | 1 | 71 | 198 | 482 |
| `0058AF60` | 49,230 | 13,788 | 919 | 7 | 154 | 350 | 966 |
| `005A1600` | 43,599 | 11,620 | 522 | 1 | 77 | 200 | 508 |
| `005AEEC0` | 71,616 | 19,482 | 1,282 | 7 | 164 | 411 | 1,067 |
| `005C9CC0` | 43,501 | 11,447 | 566 | 1 | 68 | 198 | 470 |
| `005D73C0` | 43,282 | 12,259 | 783 | 7 | 126 | 451 | 955 |
| `005EB520` | 34,434 | 9,378 | 492 | 1 | 61 | 199 | 443 |
| **Total** | **1,102,055** | **292,761** | **16,861** | **84** | **2,359** | **6,687** | **16,123** |

Every entry is the **whole original function**, decoded with the pinned
Capstone x86 decoder, ending at its independently verified *single*
original `RET` boundary. Each full original CODE SHA256 is frozen in
`config/fighter-boss-dispatch-fingerprints.json`. Its post-RET DATA consists
of actual original DWORD jump tables and dense/sparse 8-bit index maps;
**no post-RET DATA is counted as authored CODE**, and the original `CC`
padding before the next separately identified function is also excluded.

The `scripts/verify-fighter-boss-family.py` verifier validates 22 independent
whole-CODE original SHAs, 292,761 instruction boundaries, call counts,
84 actual in-CODE indirect JMP instructions, all frozen DWORD-table addresses,
lengths, contents, SHA256 digests, the original sparse map addresses and
bytewise SHAs, all 2,359 physical DWORD targets against the original
instruction boundaries, the combined contiguous after-RET DATA fingerprints
and all 22 CC alignment regions. Where a later C++ reconstruction becomes
accepted, this research-only verifier remains applicable.

## Native cross-character shared maps: four verified equivalence classes

Physically identical *sparse byte maps* were found at **different original PE
addresses**, and each equivalence class is independently verified against
its actual original byte stream, not inferred from similar function names:

| Map length | Copies | Original native SHA256 | Character function starts, in address order |
| ---: | ---: | --- | --- |
| 49 | 8 | `8f5c9622c9e01faae1a5f158935e3342837c189bde690936e98cc5821dfbf978` | `00486550`, `004AC040`, `004D7E70`, `004F7130`, `005214B0`, `00543210`, `00564BE0`, `005AEEC0` |
| 68 | 8 | `a5a34134b8e8e16d03f131a259adb2621cc4cf6499be28366ab35d452f1f48f6` | `0045DD70`, `00486550`, `004AC040`, `004D7E70`, `004F7130`, `005214B0`, `00543210`, `005D73C0` |
| 49 | 3 | `924429b5c10b434d789b073c634207abb2c0d31243bb71bf07d921c6879f7d1b` | `0045DD70`, `0058AF60`, `005D73C0` |
| 66 | 2 | `81ce3687d81ad083b2f8b59274c419414389a9a70730df3d9174d92608567dbf` | `00564BE0`, `005AEEC0` |

The two different 49-byte patterns are **not equivalent**. Even when sparse
indices are identical, corresponding original DWORD destination arrays are
*per-character native CODE addresses* and must not be copied as shared C++
code or recredited. An earlier original-target research assumption that
all physical DWORD slots must have distinct destinations was **incorrect**:
the original PE contains different slots that legitimately converge on
one actual shared default/epilogue instruction. The verifier tests the
validity of **each physical target**, preserving duplicates faithfully.

The original `CharacterObject`-family single switches have their own
**198–200-byte** sparse maps, with no byte-identical whole map found among
the 11 original functions; this argues against blindly imposing one
per-character C++ action set. Original `CharacterMove` early guards
and action-ID group cutoffs vary across fighters. See detailed whole native
examples `docs/REIMU_ACTION_BOSS_DISPATCH.md` (R063 60,999-byte boss)
and `docs/CHARACTER_MOVE_ACTION_DISPATCH.md` (R048 82,796-byte boss).
The actual shared byte maps are useful tests for *future complete natural C++
action dispatch*, not proof that a common source body can be reused unchanged.

## Reproduce, without any build or cold replay

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-boss-family.py
scripts/repo-python scripts/verify-reimu-action-dispatch.py
scripts/repo-python scripts/verify-character-move-dispatch.py
```

The private `.analysis/f520-fighter-boss-family/survey.py`, `catalog.json`
and `survey.log` are preserved exploratory evidence. These must not replace
the tracked independent SHA-frozen verifier/manifest. Work remaining is the
**complete 28K–82K C++ action/state/bullet/float logic within each whole
boss**, not just original switch tables or tiny helpers. **No source present,
no exact credit, no original DLL/CRT/borrowed callee credit, no target patches,
no fabricated local stack padding or assembly, and no full cold replay**.
