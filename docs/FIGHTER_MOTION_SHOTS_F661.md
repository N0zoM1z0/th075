# F661 — original full-parent C++ source for native 0x18A/0x18B, still NONSTRICT

Pinned original Japanese TH075 ver1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original parent is giant fighter `Advance()` at `00543210`:
**58,294 original entire CODE bytes, plus 943 separately owned after-RET
switch DATA bytes**. It remains NONEXACT. These two newly recovered
normal C++ inner cases are *not independently callable original functions*,
and their real compiler scratch slots prevent strict interior acceptance.

## Two whole physical native interiors — true original C++ grammar evidence

| Actual original native case | Original real PE interval | Original entire x86 | Original internal CODE | Real original PE/COFF fields | New normal C++ compiled size | Status |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `0x18A` | `005490FD`–`005491FD` | 71 | 256 B | 6 | 250 B | **NONSTRICT** |
| `0x18B` | `005491FD`–`00549364` | 99 | 359 B | 7 | 353 B | **NONSTRICT** |
| **Both source-backed original whole case bodies** | | **170** | **615 B** | **13** | **603 B** | Zero strict/whole-function credit |

Actual original `0x18A` initializes signed stage/frame-zero member
state and 15.0f horizontal velocity, clears native short `+0xF00`,
then applies the unconditionally-per-frame original float subtraction
at `00658058`, native strict-below-zero velocity/flag clamp, and
original action `0040FA30` / `0040FAC0(0)` transition. At real stage
5/frame 0, it calls original `00453A70` with projectile kind `0x327`,
**signed direction `+0x66` multiplied by 151** for x offset and
original float global `0065929C` for y offset. Genuine source uses
ordinary `float(signed_direction*151)+F32(+0x44)` and
`F32(+0x48)+original_global` expressions; it does not embed machine
bytes or patch the PE.

Original `0x18B` starts from 10.0f, applies native velocity decay only
for signed stage greater than 6, and transitions to original action
2 on completion. At stage 7/frame zero it only increments the genuine
signed short `+0xF00` if below 2, invokes actual auxiliary action 6
via `0040FB40`, and resets the original two stage control fields.
At stage 6/frame zero, the real kind `0x328` spawn computes x using
signed direction times **128 (native `SHL ... ,7`)** and y using
original PE float `00658400`. All native control-flow ordinal roles,
real calls and x87 operations are represented in the normal C++.

## Why these are honestly NONSTRICT

The original `0x18A` physical x86 ordinals **61/62** perform `MOV
[EBP−0x88],reg; FILD [EBP−0x88]`, while the newly compiled full
parent uses meaningful temporary **`EBP−0x24`**, with both x86 widths
three bytes shorter. Original `0x18B` has the same mismatch at real
native ordinals **89/90**: original `EBP−0x8C`, compiled `EBP−0x28`.
Thus native **256/359 B** versus compiled **250/353 B**, respectively,
with four genuine register-independent CODE operand/width differences.
This resembles the earlier native `0x186` scratch allocation blocker
but is independently proved from the actual PE. **None** is allowed
into the strict source-backed case count, accepted match-unit ledger,
or authored whole-function coverage. Filling these EBP gaps with
unused/fake locals or masking their displacements would be invalid.

The tracked source [`FighterMotionShotsF661.inc`](../probes/FighterMotionShotsF661.inc)
is naturally included into the **new entire fighter C++ translation
unit**, generated independently from the original dispatch catalog by
[`verify-fighter-motion-shots-f661.py`](../scripts/verify-fighter-motion-shots-f661.py).
It compiles only this selected giant using pinned original VC7.1 `/Od
/Ob0 /Gy /GR- /GX- /GS /Zi` and validates original **71/99 whole-case
x86, all 13 true typed PE/COFF source fields, 13 independent original
PE call/float destinations**, full case geometry and physical EBP
scratch references. Every genuine `REL32`/`DIR32` field is checked
for original native target, COFF symbol, zero addend and physical
ownership; only these proven fields can be normalized while comparing
non-field GPR/x87/CFG roles.

Crucially, the older F598 normalizer erases all EBP slot offsets.
The new F661 verifier also independently compares **raw physical
EBP operands**, only allowing the already authenticated saved-this
slot `EBP−0x44` in the original to be `EBP−8` in this incomplete
compiler parent. It demands exactly the four nonmatching scratch
ordinals above, and no other local-role mismatches.

The same fresh parent proves all preceding **17 native strict case
interiors** `CF/D0/D1/D2/12C/12D/12E/12F/130/131/133/134/135/136/
187/188/189`, plus actual earlier original fighter cases and all
separately owned after-RET dispatch DATA, remain strict; earlier
nonexact `0x186` is separately rechecked as nonexact. Across all
F598–F661 original fighter research, the **strict** cohort remains
**585 /157,894 internal original CODE bytes**; 18A/18B add **zero**
to that cohort and none of the 22 giant parent functions is exact.
Formal whole authored total remains **943/862,726 CODE bytes**.

```bash
scripts/repo-python scripts/verify-fighter-motion-shots-f661.py
scripts/repo-python scripts/verify-fighter-motion-continuation-f657.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Complete newly compiled giant C++/COFF/PDB, actual PE field receipts,
logs and source code snapshots remain in ignored
`.analysis/f661-fighter-motion-shots/`. This work did not run all 943
cold exact units, patch game code, or claim external Oracle acceptance.
