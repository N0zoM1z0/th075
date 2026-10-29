# F629 — original 78-instruction native action0x91 in eight giant fighter owners

**Pinned Japanese TH075 1.11 `th075.exe` (SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`).** This work is original-backed *complete interior action-case source grammar* in the enclosing VC7.1 fighter `Advance()` translation units, **not acceptance of eight whole native fighter functions**. The exact-unit ledger remains unchanged.

## Actual original game source and floating-point semantics

The complete original second/third indexed case0x91 is bounded by the **next physical native action0x96**, not a guessed number of instructions or a synthetic split function. Eight of the eleven original fighter giant owners contain a genuine **78-instruction** version. At frame/stage zero the original sets `this+0x50 = -10.0f`, `+0x54 = 14.0f`, `+0x5C = 0.5f` and clears the 32-bit `+0x7C`. The true actor-specific original stage is 1, 2 or 3; an x87 `FCOMP dword [00657480]; FNSTSW AX; TEST AH,5; JP` path conditionally enters the original early auxiliary state 2–4. Actual ordinary C++ `POS54 < g_StopThresholdAt00657480` reproduces the original x87/CFG roles, not arbitrary sign/branch ordering.

The next path subtracts drag, compares `POS54 + POS48` against real float `0065782C`, and uses **two independent true CRT `__ftol2` calls at `006406AC`**, each after its own `FMUL dword [00657888]`, to store actual adjacent native signed short trajectory slots. Most owners store `+0xF00/+0xF02`; **`005AEEC0` actually stores `+0xEFC/+0xEFE`**. It then calls original `00453E20` reset, clears vertical position, sends action `0x61` to `0040FAC0`, initializes 2.0f trajectory via `00453E60`, or on normal frame completion uses true `0040FA30`/`0040FB40` auxiliary transition. Unlike the previously recovered action0x4C, this source has no action preparation or motion reset. The natural C++ is tracked in [`FighterArcTrajectory91F629.inc`](../probes/FighterArcTrajectory91F629.inc).

## Eight independent entire-parent compilation proofs

[`verify-fighter-arc91-f629.py`](../scripts/verify-fighter-arc91-f629.py) compiles only the selected original-shaped whole giant VC7.1 C++ TU under `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. It decodes the actual complete original PE handler0x91→handler0x96, checks all 78 physical original x86 instruction starts, widths, GPR/x87/CFG roles, original initial constants and actor-specific stage/counter, and **twelve genuine typed zero-addend source COFF fields** against the exact original game/CRT/global address at each ordinal:

`22` stop float `00657480`; `28` auxiliary call `0040FB40`; `40` ground float `0065782C`; `46` and `52` projection float `00657888`; `47` and `53` CRT `__ftol2 006406AC`; `57` reset `00453E20`; `62` game action `0040FAC0`; `65` trajectory initialization `00453E60`; `68` frame getter `0040FA30`; `76` auxiliary transition `0040FB40`.

On each **same new OBJ**, the verifier also rechecks the three complete native F628 landing actions 0x8C/0x8F/0x90 (each eight typed PE targets), the already strict native 0x63 source including the 138-instruction priority owner `005D73C0`, all **30 earlier F598–F614 real source-backed game-case bodies**, and the entire separately owned native after-RET dense/sparse jump DATA. The F628 verifier was extended with a **backward-compatible explicit 78/105-instruction later-case boundary option**, preserving its original default behavior and full prior source comparisons. It now bounds F628's earlier cases by the *actual emitted* following action0x91 when that source is present, not a stale placeholder at a different address.

| Enclosing original fighter (all still NONEXACT) | Actual original 0x91 CODE | Original x86 roles | Native typed PE/COFF |
| --- | ---: | ---: | ---: |
| `005AEEC0` | 288 B | 78/78 | 12 |
| `00564BE0` — wide original EBP `−0x88` | **363 B** | 78/78 | 12 |
| `004AC040` | 288 B | 78/78 | 12 |
| `00486550` | 288 B | 78/78 | 12 |
| `00543210` | 288 B | 78/78 | 12 |
| `004D7E70` | 288 B | 78/78 | 12 |
| `005214B0` | 288 B | 78/78 | 12 |
| `005D73C0` — 138-x86 priority predecessor retained | 288 B | 78/78 | 12 |
| **F629 source-backed complete inner cases** | **2,379 B** | **624** | **96** |

The wide `00564BE0` original case is **75 bytes larger** than the normal VC7.1 288-byte case because 25 actual receiver `MOV` loads use the genuine larger `EBP−0x88` source frame; all 25 x86 widths and all other physical ordinal widths are checked. Original fighter `004F7130` is a **negative control**, not a success: it compiles the same 78/288 source geometry with all twelve real target COFF fields but still has **35 original GPR/CFG operand-role differences**, and its three preceding 8C/8F/90 original cases each have 51 role differences. It receives zero strict interior case credit. The other two original fighters `0045DD70` and `0058AF60` have genuine **105-x86/373-byte action0x91** with an extra real guarded projectile spawn; F629 deliberately does **not** reuse this 78-x86 grammar or claim those cases.

Cumulative strict interior research after F628's 371 original cases /98,385 original inner CODE bytes is **379 original complete interior case bodies /100,764 native inner CODE bytes**. These are *not* 379 accepted whole functions or accepted whole authored bytes. The pinned 943 whole authored exact functions /862,726 original CODE bytes (43.71% reviewed) remain unchanged, and all 22 giant original functions plus three other authored complete functions remain nonexact. No full 943-unit cold replay, target executable patch, manual assembly, synthetic stack padding or external Oracle receipt.

```bash
scripts/repo-python scripts/verify-fighter-arc91-f629.py --boss 0x005AEEC0
scripts/repo-python scripts/verify-fighter-arc91-f629.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-arc91-f629.py --negative-actor
# Optional only the eight affected newly compiled whole giant translation units:
scripts/repo-python scripts/verify-fighter-arc91-f629.py
scripts/repo-python scripts/verify-fighter-jump-landings-f628.py --boss 0x005AEEC0
```

The new C++/COFF/PDB, original physical PE fields, strictly verified receipts and native negative compiler records are retained in ignored `.analysis/f629-fighter-arc-source/`; the first independent ordinal/role trials are under `.analysis/f629-arc-trials/`.
