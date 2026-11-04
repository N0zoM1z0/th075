# F1119 — Original 0x38A, 1,035-byte twin fifteen-shot landing action and real 0065747C threshold

**Historical F1119 checkpoint:** the live source now adds [F1120 0x38B](CHARACTEROBJECT_NATIVE_38B_F1120.md), so the 72-case/73,516B source dimensions below are previous figures. Original 38A 226/226 native widths, GPR and 18/18 PE fields remain verified.

The SHA-pinned Japanese TH075 1.11 executable contains **one** authored original `CharacterObject::Advance` at `0050A580`, with **81,539 whole-original CODE bytes /17,435 native x86**, plus 567 real afterRET switch DATA bytes. F1119 reconstructs an additional genuinely independent game-state **interior**, `0x38A` at `0051BFE2..0051C3ED`, **1,035 original CODE B /226 x86**, in the one still-NONEXACT whole parent. This is not an independently accepted complete original callable.

The action checks actual signed parent +0x3A0 health, initializes the native stage/frame, signed +0x80, +0x7C, +0xD8, two scale floats, four opacity bytes and native X/Y velocity via real `0040FBB0`. Stages below six add original **00658348** to both scales and compare against native **0065747C**, individually clamping to 2.0f. Stages above five use native x87 `TEST AH,0x41; JP` to check next frame Y/velocity against original `0065782C`. On impact it zeroes velocity, calls parent `00453D40(11)`, invokes own `0040FAC0(0x385)`, spawns native **`0x347`**, then performs **two genuinely separate fifteen-iteration source loops** spawning original `0x33A` and `0x389`. It finishes the impact by invoking real parent `00453E60(5.0f)`.

The original parent-state-9 transition and own stage below six executes `0040FB40(ownStage+5)`, sets X velocity from genuine `00455580(0,30)+10`, initializes Y velocity to **−20.0f**, and moves signed-facing X and Y. Native `0040FA30` completion and own stage/frame-six reset invoke original `0040FB40(6/1)`.

A historical analogy with adjacent `0x384` supplied the first natural C++ structure but **not trustworthy global values**. That initial entire-parent VC7.1 C++ emitted all **226 correct native mnemonics, GPR roles and widths**, yet had original PE physical field mismatches at ordinal **59/67**: the source used `00657480` as the two scale-comparison globals. The *actual original 0x38A PE* loads **0065747C** at both ordinal fields. Correcting the genuinely observed C++ globals restores all true original PE targets; this difference also affects gameplay and cannot be dismissed as symbol renaming.

| Native original 0x38A evidence | Selected normal C++ |
| --- | ---: |
| Original full state interior CODE B | **1,035 /1,035 emitted** |
| Ordered native mnemonics | **226/226** |
| Original GPR roles | **226/226** |
| Original instruction-width positions | **226/226** |
| Physically correct external REL32/DIR32 fields | **18/18** |
| Non-relocated original scalar immediate positions | **49/49** |
| Two 15-shot loops | `0x33A` and `0x389`, native |

The tracked **one-parent**, not cropped-case, original PE verifier `scripts/verify-characterobject-current-recovered-f1068.py` cold builds only the affected original-shaped whole C++ and checks its original 92 afterRET DIR32 label-equivalence partitions, 199 sparse original bytes, and all recovered real game-case instruction positions, native GPR roles, true original physical PE destinations and scalar literals. It now checks **72 strict role-matched native game-case interiors**, **68,799 original native CODE B /14,763 original x86**, **14,763/14,763 mnemonic+GPR positions**, **1,137/1,137 physical original external fields** and **2,735 native scalar-immediate positions**. Seven genuinely source-authored cases remain **PROVISIONAL** for incorrect GPR phases.

Selected current C++ parent emits **73,516 CODE B /15,749 x86**; the original whole remains **81,539B /17,435 x86**, and branch distances and original stack owners are not yet restored. **Original entire game function NONEXACT; newly accepted complete original exact CODE = 0B.** All earlier 979 accepted whole exact functions remain separate.

Reproduce only the affected giant parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Real pinned original PE physical field measurements and normal VC7.1 OBJ/PDB plus rejected wrong-comparison-global source remain under ignored `.analysis/f1119-native38a/` and `.analysis/f1068-boss-live-all-native/`; no mass 979-unit replay.
