# F669 — strict native fighter action 0x255/0x256/0x257 in complete 00543210 parent

Target is pinned original user-supplied Japanese TH075 version 1.11
`resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
All evidence comes from newly compiling **one complete selected fighter
C++ translation unit** under the pinned original VC7.1 `/Od /Ob0
/Gy /GR- /GX- /GS /Zi` profile and independently reading actual
original PE instruction/field intervals. The **entire original 58,294
CODE-byte giant** `00543210` and its 943 separately owned after-RET
switch DATA bytes remain **whole-NONEXACT**. These are three genuine
new strict **internal case bodies**, not independently callable original
whole functions or adopted authored CODE.

## Complete original native physical intervals

| Original action | Real native entire PE case extent | Native original x86 | Original complete inner CODE | Genuine original typed fields |
| --- | --- | ---: | ---: | ---: |
| `0x255` | `0054C782`–`0054C87A` | 72 | **248 B** | 6 |
| `0x256` | `0054C87A`–`0054C92A` | 52 | **176 B** | 5 |
| `0x257` | `0054C92A`–`0054CA22` | 72 | **248 B** | 6 |
| **New strict contiguous original inner cases** | | **196** | **672 B** | **17** |

All three cases naturally reset their original signed stage/frame-zero
state using genuine `00453E20`, set native word `+0x80=1` and clear
original DWORD `+0x7C`, byte `+0x3AC` and short `+0xF00`. Unlike
the preceding 0x252–0x254 cases, these actions do **not** decrement
native byte `+0x366` or invoke animation `00453D60(0x21)` at the shot
stage. Instead they transition via `0040FA30` and `0040FAC0(9)`
on completion, and spawn resource `0x37` through real `00453C80`
at native stage 5/frame 0, with raw x DWORD `+0x44`, true float y
`+0x48 + original global 00657888`, signed direction at `+0x66`
and integer argument 1. Native 0x255 and 0x257 have an additional
genuine stage-8/frame-zero guard `I16(+0xF00)<1`: increment the
original **16-bit short** and invoke actual `0040FB40(6)`.
Original 0x256 is the physically shorter stage without this guard.

The ordinary C++ source
[`FighterPostCounterF669.inc`](../probes/FighterPostCounterF669.inc)
uses an identity lvalue `(*(&POS48)) + g_ContactProjectionAt00657888`
for the native float y argument, preserving original **`FLD` member
before `FADD` original global** x87 source order. Its
`SpawnMixedAt453C80(int,int,float,char,int)` declaration is explicitly
an *ABI proxy* for native argument push order, not a proven historical
method/class signature. No fake locals, asm, instruction bytes or
manual displacements occur in the C++ source.

## Full-parent proof; true relocation targets and all earlier stages

[`verify-fighter-post-counter-f669.py`](../scripts/verify-fighter-post-counter-f669.py)
regenerates the parent from genuine original native dispatch records,
cold-builds **only that selected giant** and checks complete native
case bounds, the real shared exit `005515C2`, all instruction starts,
counts, widths, full GPR/x87/branch grammar, and exact original
physical PE-targeted calls/global float. The original field counts
are **6, 5, 6**. Genuine `REL32` call targets are
`00453E20`, `0040FA30`, `0040FAC0`, `00453C80` and (only in
0x255/0x257) `0040FB40`; the real `DIR32` float operand is
`00657888`. All compiler COFF source symbols/types and zero addends
are independently checked at the actual original instruction
ordinals, including the unequal conditional tail ownership. Only
authenticated unlinked float relocations may be normalized. A separate
raw physical EBP check permits only the *known* saved receiver
`EBP−0x44` becoming compiler `EBP−8`, not any other original local.

The **same new full-parent object** is also rechecked for the
**previous 22 strict native original cases**, the genuine original
0x186/18A/18B EBP-negative cases, and the complete separately owned
after-RET 943-byte switch DATA. It physically ends the third new
case at the **original next real 0x258 handler**, not a cropped or
invented source-function boundary.

Together F668+F669 reconstruct **six consecutive actual 0x252–0x257
whole native case interiors /403 original x86 /1,416 original
internal CODE bytes /35 typed PE/COFF fields**. The selected whole
fighter `00543210` now contains **25 source-backed context-strict
inner cases /1,840 original x86 /6,387 native internal CODE bytes /
167 genuine typed fields**. All enclosing giants remain NONEXACT;
F666's demonstration that adding earlier real C++ cases changes
subsequent register allocation also remains applicable. Across
F598–F669 the research-only strict source-backed fighter interior
cohort is **593 /160,089 uncredited original CODE bytes** in their
verified selected parent contexts. The official whole-authored exact
ledger remains **943 complete functions /862,726 CODE bytes (43.71%
reviewed)**, with **zero new independently whole-exact game functions**.

```bash
scripts/repo-python scripts/verify-fighter-post-counter-f669.py
scripts/repo-python scripts/verify-fighter-counter-special-f668.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Newly generated entire parent CPP/COFF/PDB, compiler logs, original
physical native x86 and verified field receipts are preserved under
ignored `.analysis/f669-fighter-post-counter/`. No original EXE
modification, fake stack variables, all-unit cold replay or
external Oracle acceptance was performed.
