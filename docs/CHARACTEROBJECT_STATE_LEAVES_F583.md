# F583 — three complete native state leaf/actor actions 0x342–0x344

**Japanese TH075 v1.11 original entire-PE / new ordinary MSVC VC7.1
C++ source evidence, NOT exact original whole boss.** Original PE
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The entire original CharacterObject boss `004EBDA0` has **33,293 CODE
bytes**, and **438 distinct original after-RET switch DATA bytes**.
Its whole original CODE hash, real physical sparse table and full
physical case boundaries are verified before each selected C++ compile.

## True action `0x342`: staged effect spawn, 87 x86 instructions /338 CODE bytes

The original native source checks signed stage `+0x62/+0x64` both zero,
clears signed state counter `+0xD8`, calls genuine native
`0040FBB0(0,0,0)`, sets real `+0x80=1`, `+0x7C=0`, float position
`+0x54/+0x50=0.0f`, scale `+0x1C/+0x20=1.0f`, color FF and zero
position offsets `+0x28/+0x2C/+0x30`. It invokes the real parent
`00453E60(10.0f)` helper.

The native `+0x7C==6` branch independently clears that counter and
increments the *signed short* at `+0x80`; stage **3/frame 0** emits
the real native `00453A70` parent effect **`0x343`**, using original
actor positions and **signed direction byte +0x66**, then native
`0040FA30` action-state checking/reset `0045B830`.
An independently freshly compiled normal C++ source matches all
**87 original x86 instructions /338 native CODE bytes**, GPR/x87
control semantics and exact per-instruction widths. **5 real typed
COFF call/global references** are verified, including true stage
setup and effect spawn at original instruction ordinal 76.

## True action `0x343`: 1.7f stage scales, 80 x86 /309 CODE bytes

This is a *different physical handler* from earlier action `0x339`,
not an alias despite similar source control flow. The actual native
stage0 writes signed counter +0xD8=0 and calls `0040FBB0`,
sets **both float scales to 1.7f** (native bits `0x3FD9999A`),
resets stage/position fields and sets four color bytes FF.
Its two separate x87 scale additions use **native float global
`0065825C`**, NOT the `00659428` used by the older 1.3f action.
The native signed stage test is `S16(+0x62) > -1` and the
unsigned color fade is **20**, unlike the older action's
`stage >1` and 40-step fade. When the fade byte is too small,
this case sets the opacity to zero, calls real `0045B830` and
exits early; native current-action query `0040FA30` may reset.

Fresh ordinary C++ source matches all **80 authentic x86 instructions
and 309 native byte widths**, and both physical float global
`DIR32` references at original ordinals 43 and 48, with **6 total
original typed COFF fields**. No read-only order exception is used.

## True action `0x344`: independent 66-instruction /229-byte fade

Direct original PE comparison finds the full native gameplay matches
source shape and constants of previously reconstructed action `0x33A`:
`0040FBB0(0,0,0)` state reset, 1.0f scale, native sprite short
`+0x1A=0x4E2`, float offset `+0x28=-75.0f`, two original x87
`FADD` references to **`006583FC`**, native 20-step unsigned color
fade only if strict `>20` and native reset/action-query callbacks.
**This is a separate original physical 66-instruction/229-byte
handler**, not an invented alias. New natural C++ emits all original
66 GPR/x87/branch instruction roles and exactly 229 CODE bytes,
with **6 genuine zero-addend COFF fields** verified at their original
native instruction positions.

## Single-TU native source and entire original function accounting

Source:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
Original-backed targeted verifier:
[`scripts/verify-characterobject-state-leaves-f583.py`](../scripts/verify-characterobject-state-leaves-f583.py).
The verifier compiles only ONE affected normal C++ TU under pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, then rereads original PE
case boundaries and checks all 32 actual complete nondefault game
actions (the five original shared-default IDs are explicitly
excluded). Every real x86 register/x87/branch role, complete original
case length, genuine physically present `REL32`/`DIR32` native
call/global source field and zero addend is required. No old ignored
object is trusted as the proof.

| Real whole native gameplay cases in one nonexact giant | Original x86 instruction roles | Original internal CODE (uncredited) | Typed physical COFF |
| --- | ---: | ---: | ---: |
| Prior F572–F582 29 true cases | 3,762 | 13,959 B | 266 |
| New `0x342` stage-effect source | **87** | **338 B** | **5** |
| New `0x343` 1.7f float fade | **80** | **309 B** | **6** |
| New `0x344` native sprite fade | **66** | **229 B** | **6** |
| **Total 32 complete original game actions** | **3,995** | **14,835 B** | **283** |

All **60 original physical zero-addend dense switch DWORD handler
COFF references**, original default/repeated destination equivalence,
**198 byte-identical original sparse-index bytes**, and the **438
separate native after-RET DATA-layout bytes** remain verified.
Three previously documented independent read-only MOV/FLD swaps in
F573/F574/F578 and two authentic original EBP disp32 width
differences in `0x330/0x331` remain explicitly unaccepted. **None
of the three new action cases requires a swap or widened operand
exception.** The next real unimplemented case `0x345` remains a
clearly marked diagnostic source store.

### Reproduce only the newly affected C++ code

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-state-leaves-f583.py
scripts/repo-python scripts/verify-characterobject-abs-motion-f582.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Freshly compiled selected OBJ/PDB, real PE/COFF source JSON and
compiler logs are preserved in ignored
`.analysis/f583-characterobject-state-leaves-source/`, with initial
independent original disassembly and source compiler controls under
`.analysis/f583-characterobject-state-leaves/`. The entire
**33,293 original giant CODE bytes remain NONEXACT**; the 14,835
inner original case bytes are not 32 independent exact functions.
No fabricated local stack frame, original assembly graft, all-unit
cold replay or external Factory/Oracle acceptance receipt.

## F585 follow-up: complete trajectory source cases

The same normal C++ source now implements original complete
`0x345`, `0x346`, `0x347`, `0x348` and `0x349` native game actions.
The original first case is 286 instructions/1,144 CODE bytes;
`0x347` and `0x348` are independently original-backed 286/1,136
and 289/1,153 big trajectory states. The two 111/436 cases
reproduce authentic parent short sync and external `__ftol2` calls.
After the large real source cases were added, original GPR register
allocation in the two short cases also emerged naturally.
F583 still verifies all 32 earlier actions under the same new TU;
[F585 five-trajectory study](CHARACTEROBJECT_TRAJECTORY_F585.md)
checks all 37, retaining entire original 33K giant NONEXACT.
