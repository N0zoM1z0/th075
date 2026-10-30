# F706 — actual five-case source restores 2F9's complete native x86 widths

**New full-parent compiler result, not whole-boss or inner-case exact credit.**
Target is original user-supplied Japanese TH075 v1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The authored whole fighter `00543210` owns **58,294 CODE bytes** plus
**943 separately owned after-RET switch DATA bytes**. Many native action
cases outside the selected source cohort remain represented by source
placeholders; compiling a whole switch parent is **not** a complete
reconstruction of all 58,294 original CODE bytes.

## Genuine original C++ source integration, rather than fake stack padding

F672 had separately reconstructed five genuine `259/25A/25B/25C/25D`
source action bodies, but their original native positions were not
integrated with the later F701 real `2F8/2F9/2FA/2FB/302` source
context. F706 builds **one newly combined normal C++ parent** containing
all of them, plus the older actual F651–F681 game actions. It does not
insert a single artificial local: additional compiler frame occupancy
comes from eight actual kind-321/322 barrage shots and four original
one-shot actions with real integer-to-float intermediates.

The original five cases are physically independent internal subranges,
not separately callable game functions:

| Original native action | Original CODE / x86 | New emitted CODE / x86 | Native typed fields | Difference from F672's separate source context |
| --- | --- | --- | ---: | --- |
| `0x259` | 733 B /210 | 685 B /210 | 20/20 | 16 original wide EBP scratch instructions still shorten |
| `0x25A` | 198 B /60 | 192 B /60 | 6/6 | 2 original wide scratch operands still shorten |
| `0x25B` | 198 B /60 | 192 B /60 | 6/6 | 2 original wide scratch operands still shorten |
| `0x25C` | 170 B /52 | **170 B /52** | 5/5 | Now both native integer-to-x87 scratch instructions have their genuine original 6-byte widths, despite wrong EBP location |
| `0x25D` | 170 B /52 | **170 B /52** | 5/5 | Same meaningful wide-operand restoration as 25C |
| **Five real game actions** | **1,469 B /434** | **1,409 B /434** | **42/42** | 12 extra compiler bytes correctly restore original scratch *widths* over the earlier 1,397-B context |

All 434 native opcode positions and all 42 *original physical* typed
PE/COFF references are independently checked with source symbol,
actual original target, zero addend, `DIR32/REL32` type and instruction
ordinal. Apart from original-vs-source EBP conversion scratch slots,
normalized native GPR/x87/CFG roles are the same in all five cases;
all **24 true original raw EBP scratch operands** are still deliberately
checked and remain not byte-exact. This is useful genuine source
recovery, **not five newly accepted exact functions**.

## More valuable cross-case finding: complete original 2F9 width geometry

Adding these five *actual* cases changes the C++ compiler's stack-frame
allocation and source register phases in several **previously written**
substantial original cases. The whole compiled parent uses real saved
`this` at **`EBP−0x28`**, not native **`EBP−0x44`**, and has one
attested save plus **2,642 actual source receiver reload MOVs**.
All other real EBP slots are independently checked, not blanket
normalized.

| Later original action | Physical original | Fresh combined-parent C++ | Honest remaining negatives |
| --- | --- | --- | --- |
| `0x2F8` | 928 B /252 x86 /23 fields | **928 B /252 x86 /23 fields** | Real x87 evaluation order and five actual operand-width/role differences; NONSTRICT |
| **`0x2F9`** | **1,367 B /381 x86 /34 fields** | **1,367 B /381 x86 /34 fields** | **Every original x86 instruction width is now restored**. Eight authentic MOV/FLD float-evaluation reorders and 236 real nonfield GPR/x87 roles remain NONSTRICT |
| `0x2FA` | 971 B /279 x86 /31 fields | 979 B /281 x86 /31 fields | Two extra source FLD/FCOMPP instructions and real GPR/EBP differences |
| `0x2FB` | 647 B /181 x86 /17 fields | 647 B /181 x86 /17 fields | Four original MOV/FLD order differences; true source stack slots and GPR differ |
| `0x302` | 935 B /261 x86 /28 fields | **935 B /261 x86 /28 fields** | All original x86 mnemonic/width positions and fields; 136 real nonfield GPR/CFG operand differences remain |

The most important result is the full native **`2F9` width restoration**.
F701's earlier whole source compiled `2F9` at only **1,331 bytes**,
with 12 original wide `MOV/FILD/FIMUL` operand-width negatives. The
F706 parent now generates **all 1,367 genuine original bytes of
instruction *length***, including the 16 source scratch ordinals
`78/79,94/95,124/125,151/152,167/168,197/198,273/274,330/331`.
The compiler uses genuine six-byte EBP operands at `−0x9C` through
`−0xB8`; native uses **different** `−0x1D8` through `−0x1F4`.
Correct length and all 34 physical typed fields do **not** imply
byte-exactness or correct original source owner declaration.

## Reproduce the same-context evidence

[`verify-fighter-combined-native-storm-f706.py`](../scripts/verify-fighter-combined-native-storm-f706.py)
regenerates the full parent **from tracked, natural C++ source**, cold
compiles **only that original-shaped fighter** with pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, rereads the pinned original PE,
compares all five full 259–25D cases and their real scratch/fields,
checks the five later original action extents and physical references,
authenticates every source receiver MOV, and rechecks the previous
**27 context-strict nonterminal internal bodies**, honest old negative
cases, and the **entire original 943-byte after-RET switch DATA** in
this very same newly built parent. Existing F671/F673/F681/F684/F696
helpers accept independently authenticated *new genuine neighbor
source* boundaries and actual compiler scratch widths; their old
source-context defaults are preserved.

```bash
scripts/repo-python scripts/verify-fighter-combined-native-storm-f706.py
scripts/repo-python scripts/verify-fighter-four-tier-volley-f701.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Only research-generated C++/OBJ/PDB/log/JSON is under ignored
`.analysis/f706-fighter-combined-native-case-context/`; the tracked
portable source fragment inputs and targeted verifier are in `probes/`
and `scripts/`. No entire original boss source is accepted, no masking
of real GPR or EBP bytes, no original executable modifications, and
**no mass 943-unit cold replay**. Formal accepted authored whole-function
coverage stays **943 functions /862,726 original CODE bytes (43.71%)**.
