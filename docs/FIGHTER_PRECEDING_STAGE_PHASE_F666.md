# F666 — four true original preceding fighter cases and a source-phase dependency

Pinned user-supplied Japanese TH075 ver1.11 `resources/th075.exe`,
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This report is a **strictly verified negative comparison**, not an
additional strict-match claim. It investigates original native fighter
parent `00543210` (58,294 whole CODE bytes and 943 separately owned
after-RET switch DATA bytes), which remains whole-NONEXACT. The goal
is to test whether reproducing previously placeholder-only *preceding*
real native cases preserves the separately verified F664 `0x200/0x201`
source grammar. The answer is **no**, in the newly tested compiler
context. We retain both actual normal VC7.1 C++ source contexts.

## New actual whole native case-source grammar, but NOT strict GPR/EBP matches

| True original action | Actual original physical PE CODE interval | Native original x86 | Original CODE bytes | Normal C++ compiled bytes | Authentic typed PE/COFF fields | Wrong nonfield GPR/CFG role ordinals |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| `0x1FA` | `0054B9F9`–`0054BB18` | 82 | 287 | **281** | 9 | 50 |
| `0x1FB` | `0054BB18`–`0054BD73` | 174 | 603 | 603 | 15 | 111 |
| `0x1FE` | `0054BD73`–`0054BF81` | 153 | 526 | 526 | 14 | 98 |
| `0x1FF` | `0054BF81`–`0054C18F` | 153 | 526 | 526 | 14 | 98 |
| **Four NEW nonstrict source grammars** | | **562** | **1,942** | **1,936** | **52** | **Not exact** |

The normal C++ fragments in
[`FighterPrecedingStageGrammarF666.inc`](../probes/FighterPrecedingStageGrammarF666.inc)
reproduce real original stage-zero fighter state reset, movement
flag/velocity, stage/frame transitions, x87 gravity, collision and
sprite calls with actual physical original `00453E20`, `0040FA30`,
`0040FAC0`, `0040FB40`, `00453D40`, `00453C80`, `00453A70` and
actual PE globals `00657874`, `00657CBC`, `0065747C`, `006583FC`,
`006581E0`, `00659A10`, `00657CF8`, `0065782C`. The source has **all
562 original case x86 instructions**, physical case end boundaries,
and **52 exact original typed `REL32`/`DIR32` reference ownership
positions**. These are real original case semantics and evidence,
not separate exact original functions.

In particular the original `0x1FA` x87 `FILD` temporary is stored at
genuine original `EBP−0x110`. Two original native instructions are
**six bytes wide**; the compiler source emits two **three-byte**
instructions at a shorter, physically different EBP scratch slot,
resulting in a 281-byte case versus the genuine original 287. There
are also genuine wrong general-register roles from x86 ordinal zero.
The other three cases reproduce all their instruction widths, but
not their original `EAX/ECX/EDX` allocation/cycles. All four are
**NONSTRICT**, and none earns source-backed strict interior credit.

## Crucial cross-case compiler phase experiment

F664, in the explicitly scoped complete C++ parent with original
preceding action **markers still serving as source placeholders**,
proved `0x200` and `0x201` strictly against their original native
102/126 x86 roles, 343/436 CODE bytes, and 8/9 genuine typed fields.
This remains a reproducible, context-scoped original inner-case
source proof, **not** proof of historical whole-function source.

F666 now replaces those four preceding physical action placeholders
with their new natural C++ case bodies and recompiles the **same
complete giant parent**. The subsequent actual `0x200/0x201` cases
still emit **102/126 original instruction counts, all 343/436
original CODE-byte widths and all 8/9 genuine PE/COFF fields**, but
their original GPR register roles no longer match: **67** and **85
real nonfield register-role ordinal mismatches**, starting at native
instruction zero. They **must not be counted strict in this altered
compiler context**. In other words, reconstructing more of the
parent changes VC7.1's local register-allocation phase; solving the
complete parent requires recovering still earlier true source/semantic
context and actual local ownership, not padding or relocation masks.

Original `0x1FA..0x201` together have **790 original x86 roles /
2,721 real original internal CODE bytes /69 physical typed
PE/COFF source fields**. Normal compiled C++ has 790 corresponding
instructions but 2,715 emitted bytes, and genuine nonfield GPR/EBP
differences. These six bodies have **zero additional strict source
credit in this alternative source context**, and no independent
whole-function acceptance. The earlier stable F664 selected-parent
case proof is intentionally retained separately. Do not silently
replace it with this negative variant, or use the two variant results
as if they described a single consistent historical parent.

## Strictly reproducible selected original full-parent comparison

[`verify-fighter-preceding-stage-controls-f666.py`](../scripts/verify-fighter-preceding-stage-controls-f666.py)
regenerates the real parent from original dispatch evidence, then
freshly compiles **only that giant** using pinned MSVC VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. It independently reads all six
actual original PE complete case intervals and authentic x86
instructions, checks **all 69 original typed PE/COFF targets** against
the corresponding source symbol/type/addend and physical compiled
instruction, asserts the two real original `0x1FA` wide EBP field
mismatches, and **refuses exactness** for every remaining case with
wrong GPR roles. It also rechecks all **17 earlier strict native
cases**, the separate 186/18A/18B EBP negative controls, and the
complete independently owned after-RET switch DATA in the **same
newly compiled full parent**. It is not a 943-unit cold replay.

```bash
# Context where natural original predecessor source changes register phase:
scripts/repo-python scripts/verify-fighter-preceding-stage-controls-f666.py
# Distinct earlier context where real 200/201 case interiors are strict:
scripts/repo-python scripts/verify-fighter-special-stage-f664.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Full cold CPP/OBJ/PDB, original native field/role receipts and compiler
log for this actual negative context remain under ignored
`.analysis/f666-fighter-preceding-controls/`. Formal authored exact
coverage stays **943 full functions /862,726 original CODE bytes**;
F598–F666 strict original fighter inner-case total stays **587 /
158,673 original CODE bytes**. No artificial locals, assembly,
original game binary patch, fabricated whole-exact credit or
full 943-unit cold replay was performed.
