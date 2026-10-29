# F641 — original 71-instruction counter-free landing actions A3/A4/A5 in eleven giant fighters

**Pinned Japanese TH075 1.11 PE**, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`. Natural MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` **whole giant fighter `Advance()` C++ source translation units**. The entire original giant functions remain **NONEXACT**; native physically bounded **case interiors** are not separate accepted original authored whole-function match units.

## Original physical boundaries and recovered source behavior

The pinned original PE independently bounds action `0xA3→0xA4`, `0xA4→0xA5`, and `0xA5→0xA7` as **three distinct complete physical game-action cases** inside each huge fighter. There is no independent physical original `0xA6` handler between them. Each has **71 original x86 instructions** across **all eleven fighters**. Their original stage/frame-zero initial vertical positions are respectively **−9.0f / −10.0f / −13.0f**; all three genuine case endings transition to **action 2** via the real game method `0040FAC0`.

These are **not** the same native 73/75-instruction case bodies as previous F633/F639 landing actions. The real original A3/A4/A5 case has **no initialization of the signed-short trajectory counter** `+0xF00` (or `005AEEC0 +0xEFC`), and even the two original actors `00543210` and `0058AF60` have **no** `+0xF0A` extra-short initialization. The original source performs its authentic stage/frame-zero `+0x50` position, `+0x54` velocity and `+0x7C` mode writes **without these two extra native instructions**. Taking the earlier F633 natural C++ source [`FighterLandingTimerSiblingsF633.inc`](../probes/FighterLandingTimerSiblingsF633.inc) unchanged would produce extra actual machine instructions and incorrect original case boundaries; the new [`FighterLandingNoCounterF641.inc`](../probes/FighterLandingNoCounterF641.inc) removes only the behavior absent from the actual pinned original PE and retains the genuine x87/CFG game logic.

The source still updates genuine float timer `this+0x368` using original float global `0065747C`, compares to maximum `006583B4` and caps at 1000f; checks and corrects original ground boundary using `0065782C`/`00658058`; calls real `00454EE0` contact, tests signed `this+0x3BE`, computes the authentic **double-precision `FMUL qword [006583E8]`** reflection to `this+0x490`, then checks original `0040FA30` frame state and calls native `0040FAC0(2)`. The native C++ stage/position/target values are extracted from the real original case x86, not inferred from other fighters.

## Native 71-x86 whole case geometry and typed call/global PE fields

[`verify-fighter-no-counter-landings-f641.py`](../scripts/verify-fighter-no-counter-landings-f641.py) rereads every actual original physical A3/A4/A5 next-handler boundary, the real original whole x86 starts/widths/GPR/x87/CFG operand roles, original signed float height and final native action 2, and ensures there is **no hidden short-counter zeroing**. Each original physical case contains **nine genuine typed, zero-addend PE-targeted `DIR32/REL32` call/global fields**: original `FADD [0065747C]`, `FCOMP [006583B4]`, `FCOMP [0065782C]` twice, `FADD [00658058]`, genuine game `CALL 00454EE0`, `FMUL qword [006583E8]`, actual frame getter `0040FA30` and state setter `0040FAC0`. Their C++ source COFF symbols, original PE targets, field types and exact native x86 ordinal are checked one by one, **not blanket relocation-masked**.

The original wide owner `00564BE0` has exactly **21 physical saved-this `EBP−0x88` MOV receiver accesses widened three bytes each** per case, so the original whole inner CODE is **327 bytes**, not the normal **264 bytes**. The ordinary source naturally emits the correct 71 x86 roles and the original 21 genuine width differences; it never artificially pads a stack frame or rewrites an instruction.

| Actual original enclosing fighter, still NONEXACT | Three distinct original inner case bodies | Original native inner CODE | Native x86 role matches | True physical COFF fields |
| --- | ---: | ---: | ---: | ---: |
| `005AEEC0`, `004AC040`, `00486550`, `00543210`, `004D7E70`, `005214B0` | 18 | 6 × 792 B | 1,278/1,278 | 162 |
| `005D73C0`, `004F7130`, `0045DD70`, `0058AF60` | 12 | 4 × 792 B | 852/852 | 108 |
| `00564BE0`, real wide EBP receiver | 3 | **981 B** | 213/213 | 27 |
| **F641 all original giant source TUs** | **33** | **8,901 original inner CODE B** | **2,343** | **297** |

Each **newly compiled whole giant C++ source object** also revalidates previous F639 real original `0x9F/0xA0/0xA1` cases, F637 ground boost action0x9E including its genuine strict-vs-inclusive floating comparison difference, F636 `0x9B/0x9C`, F633 `0x97/0x98/0x9A`, F631 `0x96`, native source-backed 0x91 where strict, F628 initial three jump-landing actions, genuine mode0x63 where strict, the **30 previously restored original game case grammar/COFF proofs**, and the **entire separately owned original after-RET compressed jump DATA**. The actual earlier original 0x91 35/55-register-role negatives remain unresolved; newly strict later actions cannot promote them.

The previous selected native verifiers have been extended **backward-compatibly** with independently bounded 213-x86 A3/A4/A5 source intervals and real next-case marker action0xA7. Their normal earlier verification commands still work, and no all-unit cold replay was performed.

## Accounting, remaining work and bounded reproduction

F598–F639 bounded original strict game case source study contained **489 distinct complete original native case interiors /131,586 original native inner CODE bytes**. F641 adds **33** more true inner cases /**8,901 original native inner CODE bytes** /2,343 original native x86 roles/297 true physical typed COFF fields. The new total is **522 strictly source-backed original native game case interiors /140,487 original internal CODE bytes**. These are NOT 522 independent accepted whole authored functions or newly accepted authored bytes. All eleven enclosing giant originals and the other authored huge functions remain wholly nonexact. Official exact authored whole-function ledger remains **943 complete functions /862,726 original CODE bytes (43.71% reviewed)**, with 22 original giants and three other authored complete functions still nonexact. No original executable patch, external Oracle acceptance, artificial dead locals or 943-unit cold replay.

```bash
scripts/repo-python scripts/verify-fighter-no-counter-landings-f641.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-no-counter-landings-f641.py --boss 0x0058AF60
# Optional ONLY the eleven affected whole fighter source translation units:
scripts/repo-python scripts/verify-fighter-no-counter-landings-f641.py
scripts/repo-python scripts/verify-fighter-last-landings-f639.py --boss 0x0058AF60
```

The full normal VC7.1 C++/COFF/PDB sources and objects, compiler logs, native original case/PE field receipts and selected source-regression proofs are retained under ignored `.analysis/f641-fighter-no-counter-landings-source/`; native first compiler grammar experiments are under ignored `.analysis/f641-landings-no-counter/`.
