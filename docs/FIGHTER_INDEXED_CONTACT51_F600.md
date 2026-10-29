# F600 — native original indexed action 0x33, eleven giant Fighter switches

**New real game C++ source inside the large *nonexact* original fighters,
not eleven standalone functions or any officially accepted CODE.**
After F598 restored the isolated singleton `0x32`/50, this study
independently read the original Japanese TH075 1.11 PE's **next indexed
case `0x33`/51** in all eleven huge native `Advance()` implementations.
This case belongs to the **second physical sparse-index switch**,
not the preceding standalone `CMP state,0x32; JE` branch. The original
second table's first three literal sparse indices are `0,1,2`;
its first two real physical DWORD destinations independently bound
the complete case51 extent and the beginning of case52. No previous
PE hypothesis, generated diagnostic `.cpp` or guessed case size was
used as boundary authority.

## Original gameplay and source-code generation

Tracked natural C++ case
[`probes/FighterIndexedContact51F600.inc`](../probes/FighterIndexedContact51F600.inc)
uses the native state and geometry fields, the real signed byte
contact callback `00454EE0`, double projection `006583E8`, float
approach `00658058`, strict `<` / `>` original x87 status branches,
and native action receiver calls `0040FA30`, `0040FAC0`.
It differs from singleton `0x32` in a crucial original initialization:
**`this+0x50 = -9.0f`**, not `-8.0f`. The original native register
cycle rotates all three GPR roles at the next case boundary. Combining
the two natural cases in the *same entire* ordinary VC7.1
`Advance()` produces those actual rotated registers without hand
assembly, fake locals, synthetic padding or byte patching.

The original native case is **58 instructions** in every giant;
**ten** have **205 original CODE bytes** (the compiled case also has
205), and the wide-frame `00564BE0` original occupies **256 bytes**.
For that native actor, exactly 17 original saved-this `MOV` loads from
`EBP-0x88` widen by three bytes versus the 205-byte source case;
all other original individual instruction widths are identical.
All original/source **58 GPR registers, x87 operations, branch graph,
member offsets and immediate literals match** after normalizing the
real containing function's saved-this EBP slot and linker-resolved
addresses. For each case the **seven original `DIR32`/`REL32` fields**
are independently proved in the right native instruction, with exact
symbol, actual PE call/float destination, zero addend and kind.

## Independently recompiled all eleven original giant contexts

The targeted verifier
[`scripts/verify-fighter-indexed-contact51-f600.py`](../scripts/verify-fighter-indexed-contact51-f600.py)
regenerates the earlier natural C++ from original-backed
F564/F566/F567 creators, adds *both* tracked F598 and F600 cases,
then recompiles **only a selected fighter translation unit** (or the
exact eleven affected units if called without `--boss`). Every one
passes a fresh read of the entire original giant's pinned SHA,
the complete native after-RET table DATA, the 11 older real case0–10
x86 grammars, the entire original F598 singleton case50 again, the
new original indexed case51, and all source/original COFF table
DWORDs and literal sparse-index bytes. No temporary build error is
treated as positive proof.

| Original entire giant (still nonexact) | Native case51 location | Original/source case bytes | Original case x86 roles | Genuine case51 COFF fields |
| --- | --- | ---: | ---: | ---: |
| `0045DD70` | `0045E817` | 205/205 | 58/58 | 7 |
| `00486550` | `00487079` | 205/205 | 58/58 | 7 |
| `004AC040` | `004ACB39` | 205/205 | 58/58 | 7 |
| `004D7E70` | `004D8952` | 205/205 | 58/58 | 7 |
| `004F7130` | `004F7CAF` | 205/205 | 58/58 | 7 |
| `005214B0` | `00521EB9` | 205/205 | 58/58 | 7 |
| `00543210` | `00543D48` | 205/205 | 58/58 | 7 |
| `00564BE0` | `005659CE` | **256/205** | 58/58 | 7 |
| `0058AF60` | `0058BA33` | 205/205 | 58/58 | 7 |
| `005AEEC0` | `005AF9FB` | 205/205 | 58/58 | 7 |
| `005D73C0` | `005D7EA4` | 205/205 | 58/58 | 7 |

**New F600 case51 original interior:** **11 complete action blocks /
638 original instructions /2,306 original CODE bytes /77 actual typed
COFF fields**. With F567's 121 cases and F598's 11 additional
singletons, the eleven large still-unmatched functions now have
**143 source-backed original case subranges /8,111 original x86 roles
/29,141 original uncredited interior CODE bytes /944 typed physical
case fields**. The same full native switch DATA/coff fields are
checked, but **neither inner code nor after-RET data receives official
exact function credit**; F600 has not rebuilt the other original
indexed actions starting at 0x34 or the complete giant containing
frame. Exact authored ledger still **943 whole functions/862,726 CODE
bytes**, 22 original giant functions still unmatched.

### Strictly targeted reproduction

```bash
scripts/repo-python scripts/verify-target.py
# One ordinary 44K original giant; only its real source TU is compiled:
scripts/repo-python scripts/verify-fighter-indexed-contact51-f600.py --boss 0x004F7130
# One 61K wide-frame giant; precisely test original +51 native byte width:
scripts/repo-python scripts/verify-fighter-indexed-contact51-f600.py --boss 0x00564BE0
# Optional eleven affected source TUs, NOT 943 matching-unit cold replay:
scripts/repo-python scripts/verify-fighter-indexed-contact51-f600.py
```

Physical original PE and new COFF objects, compiler logs, generated
full source and per-boss JSON receipts are retained under ignored
`.analysis/f600-fighter-indexed-contact51/`. No external Oracle
receipt, no class-ownership promotion, no fake function splitting.
