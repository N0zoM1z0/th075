# F1133 — Entire 81KB original game action instruction count recovered by implementing the authentic default-case call

The SHA-pinned Japanese TH075 v1.11 original `CharacterObject::Advance` is ONE independently authored 81,539-byte /17,435-native-x86 callable at `0050A580`, followed by 567 genuine afterRET jump/sparse DATA bytes. The current incomplete original-shaped pinned ordinary VC7.1 C++ previously generated **81,559 callable CODE B /17,434 x86** because the original source's `default:` branch had been represented by an artificial `g_FighterProbeMarker=0` diagnostic global store.

A fresh native complete-function ordinal/92-switch-target audit demonstrated that the *true* original default handler, physically beginning at `0051E3F4`, consists of these five native instructions: `MOV ECX,[EBP-0xAC]`, **`CALL 0040FA30`**, `MOV ESP,EBP`, `POP EBP`, `RET`. It does **not** write any marker. The actual call to `GetNativeActionAt0040FA30()` has independently pinned original physical REL32 target `0040FA30` in the real original terminal branch. The C++ source now calls this genuine existing game method and discards its result as in the original machine code, and removes the unused synthetic external marker declaration.

The live `scripts/verify-characterobject-current-recovered-f1068.py` recompiles **only the affected entire partial 81KB C++ parent**, then checks the true original SHA, original 92 afterRET DIR32 jump target equivalence classes and all 199 native sparse literal bytes. It now independently requires the original **five entire terminal machine instructions**, their native mnemonic and GPR-role order, and the source COFF external REL32 physical byte position, kind, zero addend and real original 0040FA30 target. The previous fake global-store source is rejected, as it was missing the actual native call and one x86 instruction. This is a genuine gameplay/control-flow correction, not an instruction-padding trick.

| Entire original game source result | Actual verified evidence |
| --- | ---: |
| Original entire native callable CODE B/x86 | **81,539 /17,435** |
| Previous selected incomplete C++ CODE B/x86 | 81,559 /17,434 |
| **Current selected incomplete C++ CODE B/x86** | **81,560 /17,435** |
| Authentic original terminal `MOV/CALL/MOV/POP/RET` | **5/5 mnemonic + GPR positions** |
| Actual physical original `0040FA30` default call | **1/1 REL32 target/field/kind** |
| Real original sparse DATA 567B, 92 DIR32 label equalities, 199 literal bytes | **unchanged, verified** |
| Strict previously reconstructed native game case interiors | **82, 75,260 original CODE B /16,090 native x86** |
| Physical original external PE fields inside those 82 cases | **1,246/1,246** |
| Original nonrelocated scalar immediate positions | **2,964** |

**This is NOT whole callable exactness.** The current original-shaped whole C++ emits **21 bytes more than the original** despite matching its entire **17,435 native x86 instruction count**. Native original ESP is `0x3A0` with saved this at `EBP-0xAC`; selected C++ uses `ESP 0x3A4` and saved this at `EBP-0xDC`. Native original branch distances, temporary stack slots, several `FUCOMPP` x87 physical PE operands (in 0x391), and 0x3E6 GPR roles remain incorrect; eight other native case interiors remain GPR-provisional. The original callable remains **NONEXACT, zero newly accepted complete original authored CODE bytes**; 979 existing accepted whole exact functions unchanged.

Reproduce only the affected parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Original independently read complete native PE physical/default evidence, prior synthetic-marker C++ baseline and fresh full VC7.1 OBJ/PDB receipts are retained in ignored `.analysis/f1133-default-native/` and `.analysis/f1068-boss-live-all-native/`. No fake locals, code-byte patch, wrong-alias relocation acceptance or 979-function mass replay.
