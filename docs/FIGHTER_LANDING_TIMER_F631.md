# F631 — eleven complete original action0x96 landing-timer case interiors in giant fighters

**Pinned original Japanese TH075 1.11** `resources/th075.exe`, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`. All eleven containing fighter `Advance()` giants remain **NONEXACT**: these are complete **internal switch-case** sources, not independently callable exact authored functions or accepted match units.

## Original timer, floating-point and native case0x96 behavior

Each original complete native action `0x96` is physically bounded by the next registered native handler `0x97`. The actual source first adds original float global `0065747C` to `this+0x368`, and when the resulting float exceeds original global `006583B4` clamps `+0x368` to **1000.0f**. The x87 `FLD/FADD`, `FCOMP`, `FNSTSW`, `TEST AH,0x41` and conditional jump widths match the pinned native source roles. At stage/frame zero the actor clears its original 16-bit trajectory member (`+0xF00` in ten fighter owners or `+0xEFC` in `005AEEC0`), initializes `+0x50 = −9.0f`, `+0x54=0.0f` and clears `+0x7C`.

**Two original actors have genuine extra short `this+0xF0A=0` instructions but in opposite order:** `0058AF60` clears **`+0xF0A` before** the trajectory member and physics members; `00543210` clears **`+0xF0A` after** those members. This is not a harmless textual detail: the initial shared source generated the right 75-instruction count and 288-byte extent but five incorrect ordered register/member instructions in `0058AF60`. The natural C++ source now derives and preserves each authentic original native order rather than imposing a universal initializer.

The following ground behavior checks `this+0x50` against genuine global float `0065782C`, adds original float `00658058` only on the strict below-threshold path, clamps to zero only on the strict above-threshold path, and uses original game `00454EE0` contact and signed byte `this+0x3BE` to compute the rebound `this+0x490` with **native double-precision `FMUL qword ptr [006583E8]`**. Frame completion checks real game method `0040FA30` and calls action setter `0040FAC0(0)` when equal to the actor's signed-short `+0x70`. Tracked natural C++: [`FighterLandingTimer96F631.inc`](../probes/FighterLandingTimer96F631.inc).

## Original whole-case x86 and typed physical PE/COFF verification

[`verify-fighter-landing-timer96-f631.py`](../scripts/verify-fighter-landing-timer96-f631.py) fresh-compiles **only the selected affected original-shaped whole giant C++ TU** under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, rereads the complete original PE case `0x96→0x97`, verifies the real original 73/75 x86 ordinal roles/operand widths/CFG, the actor-specific source counter and true extra initialization order, then compares **nine true zero-addend physical typed PE/COFF fields** at their authentic x86 ordinal and original global/callee destination: `2 FADD [0065747C]`; `7 FCOMP [006583B4]`; `31/33 FCOMP [0065782C]`; `37/39 FADD [00658058]`; `42/44 FCOMP [0065782C]`; `49/51 CALL 00454EE0`; `59/61 FMUL qword [006583E8]`; `63/65 CALL 0040FA30`; `71/73 CALL 0040FAC0`. Offsets advance by two native instructions for the two authentic extra-short owners, not by a guessed byte displacement.

| Original enclosing fighter (each still NONEXACT) | Entire real 0x96 interior CODE | Original GPR/x87/CFG x86 roles | Real PE/COFF fields |
| --- | ---: | ---: | ---: |
| `005AEEC0` (native `+0xEFC` counter) | 276 B | 73/73 | 9 |
| `00564BE0` (wide original EBP frame) | **342 B** | 73/73 | 9 |
| `004AC040` | 276 B | 73/73 | 9 |
| `00486550` | 276 B | 73/73 | 9 |
| `00543210` (extra `+0xF0A` **after** trajectory init) | **288 B** | 75/75 | 9 |
| `004D7E70` | 276 B | 73/73 | 9 |
| `005214B0` | 276 B | 73/73 | 9 |
| `005D73C0` (priority-native predecessor source retained) | 276 B | 73/73 | 9 |
| `004F7130` (nonexact predecessor0x91) | 276 B | 73/73 | 9 |
| `0045DD70` (nonexact 105-x86 special predecessor0x91) | 276 B | 73/73 | 9 |
| `0058AF60` (extra `+0xF0A` **before** trajectory init) | **288 B** | 75/75 | 9 |
| **F631: eleven entire real native case0x96 interiors** | **3,126 B** | **807** | **99** |

Original wide-frame `00564BE0` has precisely **22 genuine receiver MOVs widening three bytes each** because the original whole giant stores its `this` receiver at `EBP−0x88`: native 342 bytes versus 276 natural-compiler source bytes. This is a measured native instruction-geometry difference, not synthetic stack padding.

## Rechecking preceding giant source context, including true negative branches

Every new source OBJ is independently verified for the **previous three F628 native landing cases `0x8C/0x8F/0x90`, the real original packed mode case0x63 when previously strict, 30 earlier F598–F614 source-backed game case bodies and the entire separately owned after-RET packed jump DATA**. The F628/F629 strict verifiers gained backward-compatible explicit lengths for a newly reconstructed following action0x96, rather than depending on stale `0x91` or `0x96` source markers; their own default reproduction commands still pass.

Eight owners also retain **previous complete original action0x91 78/78 GPR/x87/CFG roles and 12 actual PE/COFF targets** in each new full-giant source object. The other three source contexts are **explicitly nonexact on their predecessor**:

- `004F7130`'s native 78-x86 action0x91 still differs in **35 genuine GPR/CFG roles** even though this newly rebuilt action0x96 itself is 73/73 strictly matched. Its previous F628 8C/8F/90 also remain genuinely nonstrict.
- `0045DD70` and `0058AF60` have authentically different **105-x86/373-byte** previous action0x91 with a **real one-shot `+0xF0C` guarded projectile spawn**. Native game sprite kind is **`0x3B7` or `0x3E7`**, respectively; both actual original action0x91 calls pass **side 1**, a fact independently checked at real native `PUSH` ordinal30 and not borrowed from the earlier action0x46 sprite side. Tracked ordinary C++ negative experiment [`FighterArcSpawn91F630.inc`](../probes/FighterArcSpawn91F630.inc) reproduces all **105/105 native instruction counts, 373 whole inner CODE byte widths and 13 actual PE/COFF field symbols/ordinals/targets** in both new whole-giant sources, but each still has **55 native register/CFG-role mismatches**. Their preceding 8C/8F/90 cases likewise remain nonstrict. These two 105-x86 predecessors are **NOT** added to F629 or F631 strict case counts.

This matters: the original native physical `0x96` source may be completely role-identical **even when another actual adjacent source case is not**. No partial function acceptance, relocation masking, fake locals or universal fighter class layout is inferred from that observation.

## Accounting and reproducibility

F598–F629 had studied **379 strictly source-backed original internal game case bodies /100,764 original native interior CODE bytes**. F631 adds **11** complete strict native interiors/3,126 original bytes, bringing the bounded record to **390 strictly source-backed case interiors /103,890 original native interior CODE bytes**. This is **not 390 accepted complete authored native functions**, and none of the eleven containing giant fighters is entirely byte-exact. The official original authored whole-function ledger remains **943 exact functions /862,726 original CODE bytes (43.71% reviewed)**, with 22 giant original functions and three other authored whole functions still nonexact. No full 943-unit cold replay, target binary modification, original byte graft, unchecked source-origin promotion or external Oracle exact acceptance.

```bash
scripts/repo-python scripts/verify-fighter-landing-timer96-f631.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-landing-timer96-f631.py --boss 0x0058AF60
scripts/repo-python scripts/verify-fighter-landing-timer96-f631.py --boss 0x004F7130
# Optional only eleven new affected giant C++ TUs, never 943 cold replays:
scripts/repo-python scripts/verify-fighter-landing-timer96-f631.py
scripts/repo-python scripts/verify-fighter-arc91-f629.py --boss 0x005AEEC0
scripts/repo-python scripts/verify-fighter-jump-landings-f628.py --boss 0x005AEEC0
```

Fresh normal VC7.1 full C++/COFF/PDB, real original PE-targeted physical field receipts, 11 strict case0x96 role records and native predecessor negatives remain under ignored `.analysis/f631-fighter-landing-timer-source/`. Initial natural VC7.1 source order/flag comparisons and special predecessor context trials are retained under `.analysis/f631-landing-timer-trials/` and `.analysis/f630-arc-spawn-trials/`.
