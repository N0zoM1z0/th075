# F637 — eleven original complete 0x9E ground-boost case interiors in giant fighters

**Pinned Japanese TH075 1.11 original PE** (`resources/th075.exe`, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`). This is a genuine source-backed reconstruction of the **full native indexed 0x9E case interior** within each of eleven still-NONEXACT giant fighter `Advance()` functions, NOT eleven newly exact whole functions or independently credited match units. Ordinary pinned MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` is used for each complete selected whole-giant C++ source TU.

## Recovered real original semantics (including a material per-actor branch difference)

Each physical original native **action `0x9E→0x9F`** handler advances the `+0x368` timer by genuine float global `0065747C`, clamps it to 1000.0f above original maximum float `006583B4`, and at stage/frame zero sets true vertical position `+0x50 = −6.0f`, velocity `+0x54 = +8.0f`, deceleration `+0x5C = +0.75f`. Two original actors have an additional real `+0xF0A` short reset, with the exact opposite source order: `0058AF60` **BEFORE** position/velocity initialization; `00543210` **AFTER**. Most actors then test original position `+0x48` against the original ground float `0065782C`, subtract velocity drag, test `POS48+POS54 <= originalGround`, call real game `0040FAC0(0xA)`, clear `POS48`, and call real `00453E20` reset. Normal frame completion calls real `0040FA30` and `0040FAC0(9)`.

**Independent native PE disassembly revealed a genuine comparator distinction**: original `005D73C0` tests `POS48 > 0065782C`, using x87 `FCOMP; FNSTSW; TEST AH,0x41; JNE` to *skip* the below/equal branch, while the other **ten** native actors test `POS48 >= 0065782C`, using `TEST AH,1; JNE`. This is a real **equal-ground gameplay behavior difference**, not a meaningless alternative spelling or relocatable byte. The first normal-C++ source generated identical 66-instruction geometry/243 bytes and all eight correct typed COFF fields for `005D73C0` but had **one wrong x87 condition operand** at original ordinal31. The corrected natural C++ [`FighterGroundBoost9EF637.inc`](../probes/FighterGroundBoost9EF637.inc) uses a genuine actor-specific strict/non-strict condition and now exactly reproduces the physical original x86 roles in every fighter, without machine-byte patches or assembly.

## Real original x86 and zero-addend physical COFF proof

[`verify-fighter-ground-boost-f637.py`](../scripts/verify-fighter-ground-boost-f637.py) independently reads the pinned full original PE action `0x9E→0x9F` boundaries and each full original 66/68-instruction case, checks stage/frame initialization, actor-specific strict-above comparator, `+0xF0A` early/late original store, the double x87 ground checks, exact 0xA and 9 game actions, and physically typed zero-addend original PE/COFF targets at **eight original x86 ordinals**: 2 `FADD [0065747C]`, 7 `FCOMP [006583B4]`, 29/31 and 43/45 `FCOMP [0065782C]`, 49/51 `CALL 0040FAC0`, 53/55 `CALL 00453E20`, 56/58 `CALL 0040FA30`, and 64/66 `CALL 0040FAC0`. The two index shifts are real extra `+0xF0A` reset instructions, not skipped or masked source code. The actual original x86 full-register GPR/x87/CFG mnemonic/operand roles and instruction widths match the freshly compiled VC7.1 source. Original game callees/global PE addresses, COFF symbol identities, relocation types (`DIR32/REL32`) and zero addends are each checked at the true physical ordinal.

| Actual enclosing original giant, still NONEXACT | Original complete native 0x9E CODE | Real original native x86 roles | Physical original typed COFF refs |
| --- | ---: | ---: | ---: |
| `005AEEC0` | 243 B | **66/66** | 8 |
| `00564BE0` (wide original `EBP−0x88`) | **306 B** | **66/66** | 8 |
| `004AC040` | 243 B | **66/66** | 8 |
| `00486550` | 243 B | **66/66** | 8 |
| `00543210` (extra short AFTER initialization) | **255 B** | **68/68** | 8 |
| `004D7E70` | 243 B | **66/66** | 8 |
| `005214B0` | 243 B | **66/66** | 8 |
| `005D73C0` (**strict `>` ground comparator**) | 243 B | **66/66** | 8 |
| `004F7130` | 243 B | **66/66** | 8 |
| `0045DD70` | 243 B | **66/66** | 8 |
| `0058AF60` (extra short BEFORE initialization) | **255 B** | **68/68** | 8 |
| **F637 eleven full original inner cases** | **2,760 original native CODE bytes** | **730** | **88** |

The original wide-stack `00564BE0` source has **exactly 21 actual saved-this `MOV` receiver loads widened three bytes each** due to the real `EBP−0x88` frame slot: **306 native bytes versus 243 ordinary source bytes**, not synthetic stack padding. All other source instruction widths agree one-for-one with the original physical native case length.

Crucially, each selected new **whole giant source object** also rechecks both F636 original 9B/9C cases, all three F633 original 97/98/9A cases, F631 original 0x96, previously strict original 0x91 (preserving known real predecessor **35/55 GPR-role mismatches** in other owners), F628 three jump/landing cases, F624/F626/F627 original mode0x63 where previously strict, all **30 earlier F598–F614 native game-case grammar/COFF proofs**, and the **entire separately owned original after-RET sparse/dense switch DATA**. Earlier validators were extended with backward-compatible true 66/68-instruction following-case boundaries, preserving their original default checks. This is a source-backed whole parent build context; no standalone 66-instruction function or original after-RET jump DATA is falsely counted as newly exact.

## Truthful accounting and reproducibility

F598–F636 strict original case study: **445 case interiors/119,520 original internal CODE bytes**. F637 adds **11 complete original 0x9E case interiors /730 native x86 roles /2,760 original inner CODE bytes /88 true typed fields**. Current **bounded native interior source evidence** is therefore **456 strict original game-case subranges /122,280 original native inner CODE bytes**. These are NOT 456 accepted whole native authored functions, NOT 122,280 newly credited authored bytes, and NOT evidence that any enclosing fighter whole CODE is exact. Official accepted authored whole-function ledger remains **943 exact source functions /862,726 original CODE bytes (43.71% reviewed)**. All 22 unmatched giant original functions and three other authored whole functions remain NONEXACT. No 943-unit cold replay, patch to original EXE, fake local or external Oracle exact acceptance.

```bash
scripts/repo-python scripts/verify-fighter-ground-boost-f637.py --boss 0x005D73C0
scripts/repo-python scripts/verify-fighter-ground-boost-f637.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-ground-boost-f637.py --boss 0x0058AF60
# Optional ONLY the 11 affected entire-giant VC7.1 C++ TUs:
scripts/repo-python scripts/verify-fighter-ground-boost-f637.py
scripts/repo-python scripts/verify-fighter-landing-pair-f636.py --boss 0x005D73C0
scripts/repo-python scripts/validate-tracking.py --require-target
```

Initial whole-parent source and x86 experiments are retained under ignored `.analysis/f637-ground-boost/`; the strict newly built complete C++/COFF/PDBs, typed original PE/source field receipts and GPR/x87/CFG original case role summaries are under ignored `.analysis/f637-fighter-ground-boost-source/`.
