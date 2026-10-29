# F600 — eleven further original contact actions in eleven fighter bosses

**Pinned Japanese TH075 1.11, real native PE + cold compiler original-
case codegen evidence; NO whole-fighter acceptance.** Original target
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
F598 had reconstructed action `0x32`, after the original opening
`0x00..0x0A`, in the eleven *still unfinished* 44–82K fighter
controllers. F600 continues the actual second indexed switch **in the
same native `Advance()` function**, rather than recognizing a small
case by itself as an independently callable complete function.

## Independent original PE: the eleven actual case boundaries

The original consecutive *nondefault* native action sequence is
`0x33`, `0x34`, `0x35`, `0x38`, `0x39`, `0x3A`, `0x3B`, `0x3E`,
`0x3F`, `0x40`, `0x41`, followed by `0x46` in the native second
compressed jump table. `0x36/0x37`, `0x3C/0x3D` and
`0x42..0x45` are not additional authored bodies and must not be
counted or emitted with invented behavior. Crucially, the real
second table's dense COFF slots **are not indexed by
`(action − 0x33)`**. They enumerate these distinct nondefault
handlers, followed by other actions and their shared default.
An initial diagnostic using literal case-number indexing wrongly
spanned multiple cases; this was corrected against all original
PE jump-target DWORDs before any acceptance of case roles.

Eight cases (`0x33/34/38/39/3A/3E/3F/40`) each contain **58 actual
x86 instructions, 205 native CODE bytes and 7 physical original
call/float COFF fields**; three (`0x35/3B/41`) each have **79
original x86 instructions, 295 CODE bytes and 8 genuine fields**.
One fighter `00564BE0` has an original EBP-0x88 stack frame; that
expands each short case to **256 bytes** (17 native receiver reads
wider by three bytes) and each stage-counter case to **367 bytes**
(24 wider receiver loads). Unlike a different C++ method, these
changes are original owner stack widths and have been verified at
every x86 instruction boundary. No fake local/frame padding was added.

## Reconstructed natural game C++ and three genuinely different groups

[`FighterAdditionalContactF600.inc`](../probes/FighterAdditionalContactF600.inc)
contains all **eleven ordinary complete C++ switch case bodies** with
original state, stage and member-offset behavior, included within the
existing fighter `Advance()` skeleton. Each init at signed stage
`+0x62 == 0` and frame `+0x64 == 0` sets position `+0x50` to
`−8.0f`, `−9.0f`, `−12.0f` or `−15.0f` as actually observed, clears
`+0x54` and the 32-bit `+0x7C` counter. In the three `−15.0f`
cases, it **also clears the owner-specific signed-short stage
counter**, absent from the others.

The actual original x87 code performs a strictly `<` compare against
the float at `0065782C`, adds real float `00658058`, then clamps to
zero only on a strictly `>` second compare. For a nonzero returned
signed byte from real thiscall `00454EE0` and nonzero actual byte
`+0x3BE`, it multiplies position by the original **double** at
`006583E8`, storing float at `+0x490`. Every case calls native
frame query `0040FA30` and compares its signed-short result to
`+0x70`. The normal group transitions to action **0**; the
`0x3E/3F/40` group transitions to action **2**. These are native
`PUSH 0` versus `PUSH 2`, not interchangeable compiler patterns.

The three genuine final cases `0x35/3B/41` transition to action 0,
clear the counter on that path and leave the case; otherwise when
stage is **exactly 7** and the counter is `<1`, they increment that
short and invoke native `SetAuxActionAt40FB40(1)`. Native original
`005AEEC0` uses counter **`+0xEFC`**, while the other ten use
**`+0xF00`**. The offset is selected per original actor via a
named C++ preprocessor constant, not via an invented game structure
or ABI split. Correctness is checked independently against all
three native counter accesses and all eleven original functions.

Each ordinary C++ case preserves the complete native GPR/x87/CFG
instruction order, **not merely its mnemonic sequence**. The
verifier checks the **seven/eight original physical COFF calls and
global values per case**, including register argument order and
actual destination. Original `00454EE0`, `0040FA30`,
`0040FAC0`, `0040FB40`, floats `0065782C`, `00658058` and
**qword** `006583E8` are all direct native-PE observations.

## Eleven complete affected source compilations

Only each *selected* affected giant-source translation unit is
compiled from fresh original-backed F564/F566/F567 C++ generators
and the two tracked F598/F600 case inserts. Original PE rows and
actual after-RET compressed switch tables are independently read
and revalidated. Existing original opening 11 cases and F598
`0x32` x86 role matches remain intact **in the same new object**.

| Whole original fighter (NONEXACT) | New complete native case roles | New original inner CODE bytes, uncredited | Typed native fields | Native stage counter |
| --- | ---: | ---: | ---: | --- |
| `0045DD70` | 701 | 2,525 | 80 | `+0xF00` |
| `0058AF60` | 701 | 2,525 | 80 | `+0xF00` |
| `005D73C0` | 701 | 2,525 | 80 | `+0xF00` |
| `00486550` | 701 | 2,525 | 80 | `+0xF00` |
| `004AC040` | 701 | 2,525 | 80 | `+0xF00` |
| `00543210` | 701 | 2,525 | 80 | `+0xF00` |
| `00564BE0` | 701 | **3,149** | 80 | `+0xF00` |
| `004D7E70` | 701 | 2,525 | 80 | `+0xF00` |
| `004F7130` | 701 | 2,525 | 80 | `+0xF00` |
| `005AEEC0` | 701 | 2,525 | 80 | **`+0xEFC`** |
| `005214B0` | 701 | 2,525 | 80 | `+0xF00` |
| **Total: 121 native case bodies** | **7,711 roles** | **28,399 native internal CODE bytes** | **880** | |

Across F598 and F600, **23 genuine case bodies per fighter**
(the earlier eleven action0..10, action50, eleven new second-switch
actions) have now been source-compiled with original x86-role proofs:
**253 internal native action bodies /55,234 original inner CODE bytes**
are studied and preserved, *not 253 new independent original
functions* and *not added authored exact bytes*. All the physical
after-RET COFF jump DWORDs, index DATA and original separate
ownership remain intact.

The other real case states beginning `0x46` are still represented by
explicit diagnostic placeholders and all eleven whole fighter CODE
bodies remain **nonexact**; no credit is claimed for any of these
28,399 original interior bytes or the associated jump DATA.
This is source coverage research only, not a whole-build or external
Oracle receipt. The official 943 exact authored functions/862,726
original CODE bytes and 95 pending origins are unchanged.

## Targeted reproduction

```bash
scripts/repo-python scripts/verify-fighter-additional-contact-f600.py --boss 0x004F7130
# The sole wide-frame original:
scripts/repo-python scripts/verify-fighter-additional-contact-f600.py --boss 0x00564BE0
# The different original counter owner:
scripts/repo-python scripts/verify-fighter-additional-contact-f600.py --boss 0x005AEEC0
# Rebuild only the eleven *affected giant probes*, not 943 exact units:
scripts/repo-python scripts/verify-fighter-additional-contact-f600.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Every compiled per-fighter object/source, native x86/case role, typed
COFF/target and preserved table proof is under ignored
`.analysis/f600-fighter-contact-source/`. No target patching, manual
register assignment, assembly, synthetic stack padding, truncated
whole-function acceptance or all-unit cold replay occurred.
