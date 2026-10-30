# F722 — restore original 2C0/2C1 and true 2BF→2C0→2C1→2C4 game source order

**Meaningful original-native C++ source recovery and verified compiler
register-phase improvement; NOT a new byte-exact whole function.**
Target: user-supplied Japanese TH075 1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original authored fighter `00543210` owns **58,294 original CODE
bytes** with **943 independently owned after-RET DATA bytes**. All
these cases are physically internal handlers, not independent
original game functions; no new CODE is credited until the enclosing
whole original function is exact.

## Original machine code and complete normal C++ behavior

| Entire native physical handler | Original native PE interval | Native full CODE / x86 | Current full-parent VC7.1 CODE / x86 | Original zero-addend typed PE/COFF references |
| --- | --- | --- | --- | --- |
| `0x2C0` | `0054D64D`–`0054D93E` | **753 B /218 x86** | **753 B /218 x86** | **21/21** |
| `0x2C1` | `0054D93E`–`0054DC0E` | **720 B /214 x86** | **720 B /214 x86** | **20/20** |
| **New source-backed original interiors** | | **1,473 B /432 x86** | **1,473 B /432 x86** | **41/41** |

The tracked normal C++
[`FighterEarlyPairF722.inc`](../probes/FighterEarlyPairF722.inc)
implements both entire handlers, not a partially recovered branch:

**2C0:** actual original stage-zero game state/byte/motion reset;
stage 16–24 X/y deceleration and original `[00659090]` and
`[00657CF8]` floor clamp; real collision auxiliary 25 and shared
reset; native completion check, frame counter reset; stage-one
attack with *real* member `+0x36C` subtraction, original
`InitTrajectory(40)`, `PrepareAction(23)` and kind `0x73`
projectile with directional angle×46 and native Y offset
`[0065826C]`; stage-seven raw-X/raw-Y `0x3C` shot and original
`StartAnimation(500)`; real stage 7–14 kind `0x329` float projectile;
stage 15 repeated auxiliary 11 with authentic short counter; and
stage-25 auxiliary 23.

**2C1:** distinct original stage-zero reset, trajectory and kind
`0x74` mixed-coordinate projectile followed by actual
`+0x36C` subtraction; stage 4–10 velocity Y decrease by
`[00659A10]`, zero clamp, stages 11–13 Y gravity and native
floor contact auxiliary 14; actual stage-five trajectory
initialization 5.0f; frame completion reset; stage-four 15.0f/
0.85f Y speed/drag; stage-five real kind `0x32A` float projectile,
raw coordinate kind `0x340` projectile, `StartAnimation(500)` and
original action preparation 12; authentic stage-eight and
stage-eleven auxiliary loops and stage-fourteen terminal action.

Each newly reconstructed complete action has **every original x86
instruction width** and every original **physically typed PE/COFF
`REL32`/`DIR32` reference** matched to its actual native PE
destination and authentic source symbol at the native x86 ordinal.
`2C1` has **214/214 identical native mnemonics and zero normalized
nonfield GPR/CFG mismatches**. `2C0` has **217/218 native opcode
mnemonics**, with the only opcode difference at native x86 ordinal
117 (`FSUBR` original, `FADD` compiler); two real normalized
nonfield differences are that operation and the corresponding
signed integer multiplier at ordinal 113.

## Actual x87-expression reduction: 5 wrong opcode positions → 1

The baseline natural source `X−float(direction×46)` produced
native-incompatible `FLD X`, integer scratch and `FISUB` phases,
with **five non-native opcodes and five operand-width mismatches**
in the complete 753-byte handler. F722 serially compiled **nine
complete original-shaped VC7.1 boss parents** using meaningful
C++ grammar controls: source-original X minus float, negated
subtraction, signed negative-angle followed by X addition, X plus
negative-int cast, implicit float conversion, actual read-only X
lvalue, volatile X operand and related signed direction forms.

Using the *algebraically equivalent, genuinely executed*
`float(direction×−46)+X` changes the order to original-native
`MOVSX; IMUL; MOV [EBP]; FILD; MOV this;` and preserves all
**753 native instruction bytes of *length***. This reduces original
x87 opcode differences from five to **one**. It does **not** make
the case byte-exact: original native uses **`IMUL +46` and `FSUBR`**,
while the generated source uses **`IMUL −46` and `FADD`**.
Both original native signed-direction float scratch owners remain
**different**: native EBP `−0x160/−0x164` versus source
`−0x98/−0x9C`; `2C1` native `−0x168` versus source `−0xA0`.
All six genuinely wide `MOV/FILD` EBP operands are asserted
individually. The enclosing native saves `this` at `EBP−0x44`,
whereas the current VC7.1 giant saves it at `EBP−0x28`.

## More significant new finding: restore native physical case sequence

Earlier whole-parent F708 source grouped `2BF` and `2C4` together
and retained `2C0` and `2C1` as source placeholders *after both*.
The authentic original PE orders them
**`2BF → 2C0 → 2C1 → 2C4`**. Old generated sibling-case order was
thus **not trustworthy** as a compiler/register-phase model.

[`verify-fighter-native-order-f722.py`](../scripts/verify-fighter-native-order-f722.py)
reuses the actual tracked F708 C++ bodies for `2BF` and `2C4`
without modifying their earlier independent reproductions, splits
those genuinely used bodies at their true original case boundary,
then inserts the complete new F722 `2C0/2C1` source *between* them.
It generates and compiles **one freshly built entire original-shaped
58KB giant parent**. The new source order accounts for three
additional actually used signed integer-to-x87 scratch objects;
no fake stack padding or registers are inserted.

The resulting original-target comparisons show a natural **positive
compiler phase change** in already source-backed cases:

| Physically original action | Previous selected-parent normalized nonfield GPR/CFG discrepancies | New original-source-ordered parent |
| --- | ---: | ---: |
| `2BF` | 2 | 2 |
| `2C4` | **66** | **2** |
| `2DB` | 236 | 235 |
| `2DC` | 95 | 80 |
| `2DD` | **80** | **0** |
| `2DE` | 0 | 0 |
| `2DF` / `2E5` | 0 / 0 | 0 / 0 |
| `2EF` — original full 788B/224 x86/20 fields | 0 strict | **0 strict** |
| `2F0` / `2F1` | 147 / 170 | 147 / 170 |

The genuine source order reduces `2C4` by **64 GPR discrepancies**
and restores `2DD` by **80 GPR discrepancies**. That is real
cross-case original machine-code evidence, not a higher accepted
whole-function percentage. Other cases' EBP scratch offsets widen
by three real four-byte slots, moving native x87 source location
closer in some operands but never actually matching the original
native `−0x44` saved receiver or much deeper native scratch frame.
All changed contexts are checked separately; earlier original
source-context receipts remain valid for their **old** compiler
parents, not for this new one.

## Full-parent regression and honest acceptance boundary

The F722 verifier uses the original PE to recheck **both complete
2C0/2C1 handlers**, all 41 actual typed physical fields, true
case order and six EBP operands. In the **same new entire parent**,
it also verifies old real `2BF/2C4`, `2D0/2D1`, `2DB/2DC`,
`2DD/2DE`, `2DF/2E5`, five source-backed 259–25D cases,
late `2F8/2F9/2FA/2FB/302`, **all 27 still-context-strict earlier
original nonterminal actions** (including `2EF`) and the **entire
separate 943-byte original after-RET DATA**. `2F0/2F1` continue
to have 147/170 honest original nonfield GPR mismatches; `2C0`
continues to have the true `IMUL/FSUBR` native-vs-source difference.

Affected prior selected verifiers F708/F711/F714/F718/F720 now
accept **optional, independently verified new physical case-start
indices and real source scratch shifts**, while their existing
old-context defaults remain unchanged and are re-run. Thus
adding native code cannot be misreported as a source-context strict
match using a previous compiled object's stack slots.

```bash
scripts/repo-python scripts/verify-fighter-native-order-f722.py
scripts/repo-python scripts/verify-fighter-late-storm-f720-f721.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Actual generated C++/OBJ/PDB, original PE/COFF proof and nine
complete-parent source variants are retained in ignored local
`.analysis/f722-fighter-early-pair/`. Portable meaningful C++
fragment and complete original-parent verifier are tracked in Git.
No original EXE edits, invented fake locals, separate inner-case
CODE acceptance or 943-unit cold replay. **Formal accepted whole
authored functions remain 943 and 862,726 original CODE bytes
(43.71% reviewed)**; the enclosing fighter is still NONEXACT.
