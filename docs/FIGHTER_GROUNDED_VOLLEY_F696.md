# F696 — complete native fighter action 0x2FB in its original-shaped whole boss

**Source-backed but NONSTRICT original game CODE.** The target is the pinned
user-supplied Japanese TH075 v1.11 `th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This study does not accept an independent function or any whole-boss exact CODE.

The original authored fighter `00543210` owns a complete **58,294-byte CODE
parent** plus **943 separate after-RET switch DATA bytes**. Its original
physical action `0x2FB` occupies **`00550D97`–`0055101E` (647 bytes,
181 x86 instructions)**. Direct PE disassembly confirms all exits and the
following genuine `0x302` handler. The case configures storm state, sets
initial movement and gravity, checks ground contact, calculates the original
angle through `00483300`, launches kind `0x391`, and executes a genuine
indexed kind-`0x392` volley controlled by signed global `006714D0`.
It then handles completion and stage-13/18 transitions. This is normal C++
source, not copied machine code, stubbed loops or binary patching.

## Exact physical evidence vs remaining differences

| Original/compiled property | Fresh full-parent result |
| --- | --- |
| Whole original 2FB native case | 647 CODE B; 181 x86 |
| Source-generated real case | 635 CODE B; 181 x86 |
| Physical original PE/COFF fields | All **17/17** at the matching instruction ordinals, correct REL32/DIR32 type, zero addend and original symbol target |
| Native x86 mnemonic order | **177/181**; four actual MOV/FLD evaluation-order reversals at ordinals **64, 65, 75, 76** |
| Original EBP integer-to-x87 scratch | Genuine four six-byte original references at ordinals **69, 70, 97, 98** versus three-byte compiled references; original `EBP-0x1FC/-0x200`, source `EBP-0x7C/-0x80` |
| Actual normalized GPR/CFG operand differences | **109 positions**; first at ordinal **5**, not silently masked or claimed exact |
| Native receiver storage | Native `EBP-0x44`; new full TU C++ `EBP-0x18` (one store, **2,392** true reloads) |

These are real differences. The native 647 B is **not byte-exact**, despite
recovered behavior, full case extent, instruction count, and typed relocations.
The original parent remains whole NONEXACT and original function-level
accepted CODE credit remains **zero** from F696.

## Rebuild and context regression

The tracked source fragment [`FighterGroundedVolleyF696.inc`](../probes/FighterGroundedVolleyF696.inc)
is inserted into a freshly regenerated **complete** `00543210` source parent,
using the tracked preceding F651–F684 source contexts. Reproduce only the
one affected original parent, with pinned serial VC7.1 `/Od` compilation:

```bash
scripts/repo-python scripts/verify-fighter-grounded-volley-f696.py
```

The verifier independently reads the pinned original native PE and its actual
action boundaries; discovers the compiler-generated action in the full switch
rather than comparing an isolated fragment; checks all 17 physical original
relocation owners and authentic stack/mnemonic negatives; and authenticates the
**entire new source saved-`this` role** before presenting just that role to
older source-context verifiers. Every other EBP displacement remains real.
It also rechecks the previous **27 strict *nonterminal* internal case bodies**,
the actual earlier negative cases (`186`, `18A/B`, `258`, `2F0/2F1`, `2F8`,
`2F9`, `31B/31C`), and the **complete original 943-byte after-RET DATA**
inside the **same newly compiled whole parent**. This last property matters:
adding a real index loop for `2FB` changed the compiled saved `this` from
`EBP-0x14` (F684) to **`EBP-0x18`**, and moved F684's genuine integer-to-x87
source scratch by four bytes. Those shifts were read from the fresh COFF
object, not inferred from old documentation. The old `2F9` retains **236**
real GPR/x87-role mismatches, and terminal `31B` retains **43** in this new
full-parent context; no prior strict context is falsely merged into it.

A separate natural C++ lvalue-source variation using `*(&F32(...))` around
the angle operands was also freshly compiled against the entire parent. It
preserved the 181/635 original case geometry but did **not** correct the four
native MOV/FLD reorder positions; this is a documented negative, not a new
success. Ignored research files, real COFF objects, compiler output and
`summary.json` are preserved in `.analysis/f696-fighter-grounded-volley/`.

**Current result:** meaningful whole-context original source reconstruction
of an additional 647 native internal CODE bytes; **not** a new accepted
independently callable function, **not** 647 credited exact bytes and **not**
proof that the surrounding 58KB fighter is exact. Continue the authentic
source lifetime/stack-ownership investigation, not artificial stack padding,
all-slot normalizations, cropped comparisons or full 943-unit cold replay.
