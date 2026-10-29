# F551: complete native action 7 and previously recovered action 6 in three giants

**Original Japanese TH075 1.11 native CODE and freshly compiled natural
C++ code-generation evidence, not whole-fighter exactness.** The original
SHA256 remains `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Before each selected compile, the verifier hashes and decodes the **entire
original 43–61K fighter function**, all after-RET switch DATA, and the
physical first-switch DWORD targets for cases 6, 7 and 8. This extends
[F548's original action-six C++](FIGHTER_ACTION_SIX_FAMILY_CODEGEN.md).

For the three original action-7 cases, *each complete source-level case* is
**362 original CODE bytes, 104 contiguous native x86 instructions**. The
original native case-six and case-seven instruction/branch graphs are
identical except for **exactly three semantic source differences**:

- Actual `U8(0x511)` state guard is **5**, rather than action 6's **3**.
- Actual state transition callback `0040FAC0` is given **0xCD** rather
  than **0xCC**.
- The genuine float store to receiver `+0x50` is **4.0f** for Reimu
  `0045DD70` and fighter `0058AF60`, but **6.0f** for `005D73C0`.

The sources do **not** paste original instruction bytes; the three values
are independently read from real `CMP`, `PUSH` and `MOV` instructions.
Their genuine signed-short stage, native frame increments, x87 arithmetic,
original physical virtual `dword ptr [edx]`/`[eax]` call and other branch
conditions remain natural C++ with the independently verified per-fighter
actor/float conditions from action 6.

## Fresh affected-only compiler and full original validation

Every role receives its own regenerated natural C++ `switch` source from
tracked, original-backed F548 helpers; it contains **two genuinely modeled
complete action cases** (6 and 7) and test-only marker stores for other
unreconstructed actions. The pinned MSVC 7.1 `/Od /Ob0 /Gy /GR- /GX-
/GS /Zi` toolchain compiles each new source. Both cases are then checked
at their *entire physical original case spans*, not clipped to a matching
prefix.

Across **3/3 independent compiled fighter probes**:

- **624/624 native instructions across cases 6 and 7** have matching
  per-fighter EAX/ECX/EDX member use, actual x87 operands, complete
  branch-control structure, and the original virtual-call register form.
- **36/36 actual typed `REL32`/`DIR32` native COFF case reference roles**
  match (six real original call/global relocations per case).
- All **422 physical original-style DWORD switch-table COFF references**,
  original repeated/default handler partitions, **1,323 byte-identical
  sparse-index bytes** and **3,011 after-RET DATA-shape bytes** are retained.
  These are not accepted CODE/DATA credit.

| Whole original fighter | Two original cases | Original action-7 position | Original action-7 virtual call | Whole switch COFF refs | Original sparse bytes |
| --- | ---: | --- | --- | ---: | ---: |
| `0x0045DD70` | 724 CODE bytes / 208 instructions | `4.0f` | `dword ptr [edx]` | 142 | 522 |
| `0x0058AF60` | 724 CODE bytes / 208 instructions | `4.0f` | `dword ptr [edx]` | 154 | 350 |
| `0x005D73C0` | 724 CODE bytes / 208 instructions | `6.0f` | `dword ptr [eax]` | 126 | 451 |

## Targeted reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-action-seven-natural-source.py --boss Reimu
# Or fresh compile only the three newly affected natural C++ TUs:
scripts/repo-python scripts/verify-fighter-action-seven-natural-source.py
```

The real original complete giant source remains **153,511 unmatched CODE
bytes** across these three original fighters. The **2,172 original interior
case CODE bytes** are not standalone functions and earn **zero exact coverage**.
Probe source/object/compiler outputs remain under ignored
`.analysis/f551-action-seven-source/`, negative/reverse-engineering controls
under `.analysis/f551-action-seven/`. No target assembly copied, fake
padding/return, all-unit cold replay or external Oracle receipt.
