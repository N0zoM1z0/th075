# F636 — complete native 0x9B/0x9C landing cases in all eleven fighter giants

**Pinned original Japanese TH075 1.11 PE, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.** Normal MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, newly compiled **whole fighter `Advance()` C++ translation units**. These are the real physically bounded original **inner action bodies**, not complete independent callable native functions. All enclosing fighter giants remain NONEXACT.

## Genuine original native case semantics and physical boundaries

The original physical giant handler sequence contains **distinct complete case `0x9B→0x9C` and case `0x9C→0x9E`**; original action code 0x9D does **not** create another separately bounded case between them. Both cases have the actual full F633-style native landing physics, but they have **their own original game states**: the source initializes live float member `this+0x50` to **−10.0f** or **−13.0f** respectively, and **both transition to native action 2** via the real method `0040FAC0` (unlike the earlier `0x97/0x98`, which transition to 0). This is independently read from the real native `MOV` immediate and final `PUSH`, not inferred from a shared source template.

The true original physics timer at `this+0x368` uses float global `0065747C`, checks original maximum global `006583B4` and caps at 1000f. The frame-zero source clears the real signed-short trajectory counter at `+0xF00` or native `005AEEC0 +0xEFC`, sets the genuine float position/vertical velocity and clears motion mode. Two actor-specific 75-instruction original versions **also clear `+0xF0A` in opposite source orders**: `0058AF60` BEFORE its trajectory counter, `00543210` AFTER the physics stores. Actual x87 original `FCOMP` and `FADD` compare/correct the ground threshold `0065782C/00658058`; `ContactAt454EE0`, signed byte `+0x3BE`, and genuine double `FMUL qword [006583E8]` store the reflected float at `+0x490`. The native `0040FA30` frame query and real `0040FAC0(2)` action setter conclude each case. Source shares the **same actual normal C++ body** [`FighterLandingTimerSiblingsF633.inc`](../probes/FighterLandingTimerSiblingsF633.inc), with **new original PE-derived F636 case/height/counter/reset/next-action macros**, avoiding duplicate or guessed gameplay behavior.

## Full native x86 roles and genuine physically typed PE/COFF fields

[`verify-fighter-landing-pair-f636.py`](../scripts/verify-fighter-landing-pair-f636.py) first independently decodes both complete original PE case boundaries, including the real following 0x9E, then checks each native 73/75-instruction x86 GPR/x87/CFG role and size, real initial float, action target, distinct short-reset order, and **nine true typed zero-addend physically PE-targeted COFF fields per complete case**. These include original float globals `0065747C`, `006583B4`, `0065782C` twice, `00658058`, genuine game contact `00454EE0`, **64-bit-double `FMUL [006583E8]`**, frame getter `0040FA30` and state setter `0040FAC0`. Native source symbols/types/field ordinals and target addresses are checked individually; no relocation-masked byte claim is taken as full original function exactness.

The native wide-frame owner `00564BE0` has **exactly 22 actual `EBP−0x88` receiver MOVs expanded three bytes each** in each original 342-byte case versus a natural 276-byte source case. Every other original compact case is 276 bytes/73 x86, or 288 bytes/75 x86 for the two extra short-reset owners.

| Original enclosing whole giant (all NONEXACT) | Two true original native cases | Real original CODE bytes | Native x86 roles strictly matched | Original typed COFF fields |
| --- | ---: | ---: | ---: | ---: |
| `005AEEC0`, real `+0xEFC` motion counter | 2 | 552 B | 146/146 | 18 |
| `00564BE0`, real wide `EBP−0x88` | 2 | **684 B** | 146/146 | 18 |
| `004AC040` | 2 | 552 B | 146/146 | 18 |
| `00486550` | 2 | 552 B | 146/146 | 18 |
| `00543210`, extra short AFTER | 2 | **576 B** | 150/150 | 18 |
| `004D7E70` | 2 | 552 B | 146/146 | 18 |
| `005214B0` | 2 | 552 B | 146/146 | 18 |
| `005D73C0`, real F627 138-x86 priority predecessor retained | 2 | 552 B | 146/146 | 18 |
| `004F7130`, preceding `0x91` remains nonstrict | 2 | 552 B | 146/146 | 18 |
| `0045DD70`, preceding special sprite `0x91` remains nonstrict | 2 | 552 B | 146/146 | 18 |
| `0058AF60`, extra short BEFORE, preceding `0x91` still nonstrict | 2 | **576 B** | 150/150 | 18 |
| **F636 strictly rebuilt original case interiors** | **22** | **6,252 B** | **1,614** | **198** |

Every newly compiled *whole giant source object* also **reverifies all three F633 strict `0x97/0x98/0x9A` cases**, original F631 0x96, F629 0x91 where originally role-strict, the three F628 jump-landing case bodies, the genuine native mode `0x63` when strict, the **30 earlier source-backed game cases** and complete separately owned after-RET original compressed jump DATA. The F628/F629/F631/F633 verifiers received **backward-compatible explicit bounded followup lengths** and real source marker `0x9E` support; their original default commands still pass. This is essential because the ordinary VC7.1 compiler can rotate GPR allocation when changing earlier case source even if a later case's text is unchanged.

**Nonstrict predecessor cases remain explicitly nonexact.** Native `004F7130` 78-x86 `0x91` still has 35 original GPR differences. Two native special projectile cases `0045DD70` and `0058AF60` 105-x86 `0x91` retain 55 native GPR-role differences each. The strict F636 case evidence does **not** adopt those preceding source failures, nor does it imply the entire enclosing giant matches.

## Accounting and bounded reproduction

F598–F635 prior source-backed case research recorded **423 genuine original strict internal case bodies /113,268 original native inner CODE bytes**. F636 adds **22 strict complete inner case bodies /6,252 original native inner CODE bytes /1,614 x86 roles /198 original typed fields**: cumulative **445 strictly source-backed original action interiors /119,520 original inner CODE bytes** across independently compiler-verified whole giant source objects. These are **NOT 445 accepted whole original functions** and **NOT newly accepted authored whole CODE bytes**. The official exact authored function registry still holds **943 complete functions /862,726 native CODE bytes (43.71% reviewed)**. The original 22 huge fighters and three other author-classified complete functions remain unmatched. No full all-unit cold replay, target executable modification, external Oracle acceptance or manual machine-code graft.

```bash
scripts/repo-python scripts/verify-fighter-landing-pair-f636.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-landing-pair-f636.py --boss 0x0058AF60
# Optional only the eleven affected whole C++ fighter translation units:
scripts/repo-python scripts/verify-fighter-landing-pair-f636.py
scripts/repo-python scripts/verify-fighter-landing-siblings-f633.py --boss 0x0058AF60
scripts/repo-python scripts/validate-tracking.py --require-target
```

The fresh actual original C++/COFF/PDB, normal VC7.1 compiler logs, original physical PE/source typed field receipts and initial independent native case comparisons remain under ignored `.analysis/f636-fighter-landing-pair-source/` and `.analysis/f636-landing-pair/`.
