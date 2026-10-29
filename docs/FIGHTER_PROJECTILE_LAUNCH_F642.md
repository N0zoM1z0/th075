# F642 — complete native 97-x86 A7/A8 sprite-launch cases in eleven giant fighters

Pinned original Japanese TH075 1.11 PE `resources/th075.exe`, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`. Ordinary pinned MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` source compiled **in each selected entire giant fighter `Advance()` C++ TU**. These are genuinely physically bounded original *internal action cases* and remain **UNcredited**: the containing eleven whole giants and the remaining authored unmatched functions are still nonexact.

## Source behavior observed in the original PE

Original action `0xA7→0xA8` and `0xA8→0xB4` are **two distinct complete 97-instruction x86 cases per giant**, not two independent callable functions. They advance native animation timer `this+0x368` via float `0065747C`, clamp against original `006583B4`, then on stage/frame zero call native `0046D000(0xFA)` animation trigger and `00453D60(0x2C)` preparation, and initialize a **signed-short cooldown to `0xB4`** at `this+0xF00` or actual `005AEEC0 +0xEFC`. Native `00453C80` then emits sprite kind **`0x38`**, side **1**, orientation signed from `this+0x66` and genuine x/y floats calculated as **`this+0x44 + 30*int8(direction)`** and **`this+0x48 + float global 00657888`**. The original source uses a true signed `IMUL 0x1E`, `FILD` from a real stack temporary, `FADD` and two original stack-floating `FSTP` arguments; it does **not** convert a character direction using an arbitrary float cast or fake saved register.

When actual vertical position `this+0x50` is below original global ground `0065782C`, the native source adds real `00658058` and conditionally clamps to zero if it crosses the original boundary. The source computes `this+0x490 = -signed_short(cooldown) * float global 006590B4` via the **second real signed integer-to-x87 `FILD`**, then decrements the 16-bit cooldown by **10** only while positive. It queries actual frame state `0040FA30` and calls genuine action setter `0040FAC0(0)` for `0xA7`, **`0040FAC0(2)` for `0xA8`**. The tracked natural source is [`FighterProjectileLaunchF642.inc`](../probes/FighterProjectileLaunchF642.inc).

## Re-tested hypotheses, x87 source operand order, real stack widths

The first ordinary-C++ trial already emitted **97/97 original instruction counts, correct complete compact 350-byte size and all 12 true PE-targeted source COFF fields**. However, its y-position C++ expression `POS48 + g_ContactProjectionAt00657888` made VC7.1 produce `FLD dword [GLOBAL]` followed by `FADD dword [this+0x48]`, whereas real original x86 ordinal34 is `FLD dword [this+0x48]` and ordinal35 is `FADD dword [GLOBAL]`. The result is the same ordinary floating sum but **two wrong original physical instruction operand roles and one −3/+3 opcode width pair** per case. Simply swapping expression operands, applying casts, volatile, comma-operator or aliasing did not reliably repair the compiler x87 operand order.

**Nineteen actual normal-C++ source expression trials**, each compiled as the *whole original giant C++ parent TU* and compared to both entire original physical 97-x86 cases, proved the genuine member expression **`F32(0x48) + g_ContactProjectionAt00657888`** instead emits the exact original `FLD member; FADD global` pair. Both A7/A8 cases now reproduce **all 97/97 physical original GPR/x87/CFG roles, true byte extents, and 12/12 COFF target fields** per actor without machine-byte grafts. The first nine or so earlier F598–F614 source cases are not used as shortcuts: the new parent object rechecks all previous **30** native game-case proofs and the complete separately owned after-RET jump DATA.

Two original compiler frame layouts independently prove why instruction counts alone are not evidence of full original-byte correctness:

- **`004AC040`** has a normal-sized receiver frame but original signed integer→float temporary locals at greater-than-127-byte EBP offsets: x86 ordinals **41/42 and 72/73** are two genuine `MOV temp`/`FILD temp` pairs widened by **3 bytes per instruction**. Thus its complete original A7/A8 case is **362 native bytes** versus 350 bytes in the natural source reference, with all 97 x86 operand roles preserved.
- **`00564BE0`** has a real saved `this` pointer at `EBP−0x88`. Exactly **27** original receiver MOVs widen by +3 bytes each, **four** real signed integer scratch `MOV/FILD` accesses also widen +3 bytes, and original near `JNE` at x86 ordinal **16** expands **four additional bytes**. Consequently each genuine 97-x86 case is **447 native bytes**, a physical **+97-byte** difference from the normal 350-byte VC7.1 source. Treating all 31 widened operands as saved receiver MOVs was independently falsified by the actual native PE; this distinction is enforced by the tracked verifier.

## Full original case, COFF and enclosing-giant source verification

[`verify-fighter-projectile-launch-f642.py`](../scripts/verify-fighter-projectile-launch-f642.py) independently reads both original physical handler boundaries per actor, compares **all 97 original x86 widths, mnemonics, GPR/x87/CFG roles** and actor-specific local/cooldown offsets and native next-action, then checks every original **zero-addend physically typed `DIR32/REL32`** record against original x86 ordinal, VC7.1 source symbol and real PE target. **Twelve original reference ordinals per A7/A8**: animation delta `2` (`0065747C`), max `7` (`006583B4`), start animation `23` (`0046D000`), prep `26` (`00453D60`), y-offset float `35` (`00657888`), spawn call `49` (`00453C80`), ground `52/63` (`0065782C`), ground correction `58` (`00658058`), signed bounce scaling `74` (`006590B4`), frame query `87` (`0040FA30`) and state setter `95` (`0040FAC0`). Only the actual physical typed relocation operand is resolved; no GPR, x87 or CFG difference is ignored.

| Enclosing original fighter giant (all still NONEXACT) | Original two real case CODE bytes | Full real original x86 roles | Actual original typed PE/COFF fields |
| --- | ---: | ---: | ---: |
| `005AEEC0`, original signed-short `+0xEFC` | 700 B | 194/194 | 24 |
| `00564BE0`, true wide receiver/scratch/near jump | **894 B** | 194/194 | 24 |
| `004AC040`, true wide signed-int scratch EBP locals | **724 B** | 194/194 | 24 |
| `00486550`, `00543210`, `004D7E70`, `005214B0` | 4 × 700 B | 776/776 | 96 |
| `005D73C0`, `004F7130`, `0045DD70`, `0058AF60` | 4 × 700 B | 776/776 | 96 |
| **F642 strict original case interiors** | **7,918 original native CODE bytes** | **2,134** | **264** |

All eleven affected entire giant C++ sources are freshly rebuilt, and the **same new OBJ** then independently rechecks F641 A3/A4/A5, F639 9F/A0/A1, F637 9E with its genuine strict-vs-inclusive comparator, F636 9B/9C, F633 97/98/9A, F631 96, F629/F630 91 with known honest earlier register-phase negatives, F628 initial three native landings, mode63 when strict, the earlier 30 source-backed native game cases and **all original after-RET packed sparse/dense switch DATA**. Older selected verification scripts accept the actual following A7/A8 source spans *backward-compatibly* and still pass their original default commands. This is not exactness of any enclosing fighter whole-function CODE.

### Accounting and reproducible selected builds

F598–F641 research had **522 strictly source-backed original native game case interiors /140,487 original internal CODE bytes**. F642 adds **22 complete native case interiors /2,134 genuine x86 operand roles /7,918 original internal CODE bytes /264 actual original COFF fields**: the bounded strict case-source record becomes **544 original native case interiors /148,405 original internal CODE bytes**. These are **not 544 independently accepted authored whole functions** and no authored exact match unit was added. The formal authored exact whole-function ledger remains **943 exact complete functions /862,726 original CODE bytes (43.71% reviewed)**. No 943-unit cold replay, target executable modification, fake locals, ASM or external Oracle receipt.

```bash
scripts/repo-python scripts/verify-fighter-projectile-launch-f642.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-projectile-launch-f642.py --boss 0x004AC040
# Optional ONLY the eleven original affected whole giant C++ TUs:
scripts/repo-python scripts/verify-fighter-projectile-launch-f642.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

All actual normal VC7.1 new whole-fighter C++ source, COFF/PDB compiler evidence and original case/typed field receipts are retained in ignored `.analysis/f642-projectile-launch-verified/`. The independent **19 expression compiler alternatives** and real original x87 order diagnosis are retained under `.analysis/f642-projectile-launch/`.
