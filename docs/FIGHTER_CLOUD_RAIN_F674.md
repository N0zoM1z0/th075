# F674 — strict entire 788-byte cloud-rain case 0x2EF with real native terminal context

Pinned user-supplied Japanese TH075 v1.11 `resources/th075.exe` SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original native selected giant fighter `00543210` owns **58,294
CODE bytes plus 943 independently owned after-RET switch DATA bytes**
and is **whole-NONEXACT**. This report proves one new *entire physical
inner native case* by original GPR/x87/CFG/width and all real PE/COFF
fields, plus a deliberately NONSTRICT real terminal-case source
needed for correct original long-distance shared-epilogue codegen.
Neither case is a new independently exact whole game function.

## Entire original 0x2EF physical native stage, 788 original CODE B

| Genuine original native action | Actual original physical interval | Whole native x86 instructions | Real original inner CODE bytes | Physical typed PE/COFF fields | Proof result |
| --- | --- | ---: | ---: | ---: | --- |
| `0x2EF` | `0054F55F`–`0054F873` | **224** | **788** | **20** | **Strict, within selected whole-parent context** |
| Real following terminal `0x31C` | `005514BD`–`00551598` | 63 | 219 | 7 | **NONSTRICT: 36 real nonfield register-role differences** |

The authentic source
[`FighterCloudRainF674.inc`](../probes/FighterCloudRainF674.inc)
models a complex original fighter stage: at stage/frame zero it clears
three genuine 16-bit counters `+0xF00/+0xF02/+0xF04`, sets DWORD
`+0x7C=1` and calls original `00453E20`. During stages 4–10 it
subtracts the original gravity float at `0065785C` from vertical
member `+0x54`, clamping with true original strict-below-zero x87
`FCOMP/TEST AH,5/JP`. During stages 5–7 it increments two *different*
short counters `+0xF02/+0xF04`, and at threshold
`100−signed_global_006714D0*20` clears one counter, prepares animation
`00453D40(16)` and emits **two original kind 0x389/0x38A shots**.
Their X arguments are the native DWORD at `+0x44`; their float Y
uses typed `+0x48` plus the original PE global `006591E4`, with
signed direction byte `+0x66` and argument one.

During stages 11–13 it subtracts actual acceleration `+0x5C` and
calls original auxiliary action 14 on zero/negative ground
contact. At native animation completion it calls actual
`0040FAC0(0)`, followed by a real two-argument native random-bound
method `00455580(60,100)`, then subtracts the signed byte original
`006714D0*20` and stores the result as an actual 16-bit member
`+0x516`. At stage 4/frame zero it sets native 16.5f velocity,
0.15f acceleration, and prepares animation 21; stage 5/frame zero
spawns original kind `0x38B`. Stages 8 and 11 conditionally trigger
auxiliary actions 5/8 only when the genuine 16-bit `+0xF00` counter
is below 25, incrementing the native short each time. The emitted
normal VC7.1 source preserves every original branch/short-counter
and real native x87 instruction width and register role.

## Authentic physical PE fields and original far-exit JMP

The original complete 2EF source owns **20 genuine zero-addend
PE-targeted compiler fields**, individually checked by instruction
ordinal, native target, `REL32`/`DIR32` type and C++ COFF symbol. The
real original PE destinations include `00453E20`, original float
globals `0065785C`/`0065782C`/`006591E4`, signed byte global
`006714D0` (two *real* typed `DIR32` `MOVSX` operands, not float
masks), actual `00453D40`, two `00453A70` shot calls, original
`0040FB40`, `0040FA30` and `0040FAC0`, native `00455580`, and a
third `00453A70` shot call. Only the independently proven unlinked
absolute byte/float globals may be normalized; all other original
GPR, x87 and branch roles are directly required. Raw EBP operand
comparison permits only the original saved `this` at `EBP−0x44`
becoming compiler `EBP−8`, never other local/stack slots.

The initial ordinary C++ 2EF source compiled all **224 native x86
instructions** and all original 20 PE/COFF fields, but emitted
**785 bytes**, because the last shared-exit `JMP` was only two bytes
instead of the original **five**. This was genuine source-layout
context, not a missing GPR instruction or a reason to add padding.

The second new source fragment
[`FighterTerminalCounterF674.inc`](../probes/FighterTerminalCounterF674.inc)
implements a **real original later physical native action `0x31C`**:
63 authentic x86 positions, **219 actual native CODE bytes, seven
real typed REL32 calls** to original reset, action query/set, two
native subactions, animation and auxiliary action. This actual stage
and its original native counter/scene semantics naturally place the
shared epilogue sufficiently far away that the compiler emits the
**correct original five-byte 2EF `JMP`**, restoring a complete
**788-byte native 2EF case**, with all 224 register/branch/size roles
exactly aligned. The terminal `31C` source itself remains **NONSTRICT**
from **36 independently observed real GPR register-role differences**;
it is not accepted or cited as a strict whole native case. Compiling
only a fake `NOP`/padding block in place of this real code would be
unacceptable.

## Selected whole-parent proof and context warning

[`verify-fighter-cloud-rain-f674.py`](../scripts/verify-fighter-cloud-rain-f674.py)
regenerates the whole selected parent from original physical dispatch
and tracked C++ fragments, cold-compiles **only that one complete
fighter giant** under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`,
and strictly checks original 2EF complete native PE physical bounds,
224 entire instruction roles and widths, all 20 actual fields, raw
EBP slots, and actual five-byte shared-exit jump. It separately
verifies the full original source/typed fields of the 31C terminal
and refuses exactness on its real 36 register-role differences.
The **same newly compiled original-shaped parent object** also
rechecks **all 26 previous context-strict native case interiors**
(including F673's original large 2BC ground-wave case), all true
186/18A/18B/258 native scratch-slot negatives, and the full
independently owned after-RET compressed switch DATA.

The selected giant now contains **27 context-strict original native
case interiors /2,272 authentic x86 /7,867 real original inner CODE
bytes /207 genuine typed PE/COFF fields**. The prior F666 caveat
still applies: replacing other original source placeholders can
change VC7.1's later register allocation, so this is a bounded
source-context case proof, not whole-parent historical exactness.
Across F598–F674 research, **595 original native inner case bodies /
161,569 original CODE bytes** are strictly source-backed in their
respective selected complete-parent contexts, but remain
**uncredited**. Formal whole-authored exact stays **943 functions /
862,726 original CODE bytes (43.71% reviewed)**; none of 22 giant
parent functions is whole exact.

```bash
scripts/repo-python scripts/verify-fighter-cloud-rain-f674.py
scripts/repo-python scripts/verify-fighter-ground-wave-f673.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Reproducible full-parent CPP/COFF/PDB, compiler logs, complete
original native field receipts and negative terminal evidence are
under ignored `.analysis/f674-fighter-cloud-rain/`. No machine-code
graft, fabricated local padding, original EXE patch, all-unit cold
replay or external Oracle whole-function acceptance was performed.
