# F657 — three more native 00543210 cases and honest 0x186 scratch negative

Original Japanese TH075 ver1.11 pinned `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is original **giant fighter** `00543210`, **58,294 complete original
CODE bytes plus 943 separately owned after-RET switch DATA bytes**,
which remains **whole-NONEXACT**. Real source is ordinary C++ compiled
in a **new full parent TU** under pinned VC7.1 `/Od /Ob0 /Gy /GR-
/GX- /GS /Zi`. No new original whole-function authored CODE credit.

## Actual original physical native handlers and outcomes

| Real physical native case | Original physical CODE range | Original x86 | Native CODE | Genuine original PE/COFF fields | New strict? |
| --- | --- | ---: | ---: | ---: | --- |
| `0x186` | `00548CDC`–`00548DFE` | 82 | 290 B | 8 | **No**, 2 EBP scratch operands wrong |
| `0x187` | `00548DFE`–`00548EB3` | 50 | 181 B | 5 | **Yes** |
| `0x188` | `00548EB3`–`00548F68` | 50 | 181 B | 5 | **Yes** |
| `0x189` | `00548F68`–`005490FD` | 112 | 405 B | 9 | **Yes** |
| **New STRICT cases only** | | **212** | **767 B** | **19** | **Three** |

Cases `0x187` and `0x188` initialize the actual original native
stage-0 state words `+0x80=1/+0x7C=0`, call `00453E20` only if the
signed flag `+0x3AC` is zero and initialize member float `+0x50`
to **10.0f** and **15.0f**, respectively. For signed stage `+0x62
> 0` they subtract genuine original float `00658058` and clamp the
float velocity and signed flag after the original strict-below-zero
x87 `FCOMP; FNSTSW AX; TEST AH,5; JP` sequence. On completion
`0040FA30()==I16(+0x70)` they transition through original `0040FAC0`
to action **0** or **2**, respectively. Each real complete native
case contains five typed fields (reset, two floats, query/set calls).

Original `0x189` separately clears flag `+0x3AC`, sets native stage
words and vertical values at stage/frame zero, then applies its own
positive-velocity subtraction through **another genuine original
float global at `006578C0`**, with real x87 `TEST AH,0x41` branch.
While original y `+0x48` is positive and stage is **7 or 8**, it
integrates vertical speed `+0x54 -= +0x5C`, and on reaching ground
zeros all affected members and frame and invokes real auxiliary
`0040FB40(9)`, exiting immediately via the shared original giant
exit. Later, the original stage 7 sets vertical speed **9.0f** and
acceleration **0.9f**; stage 9 with positive y invokes the real
auxiliary method with `stage-2`. All **112 native x86 instructions,
405 original inner CODE bytes and nine true PE/COFF fields** match
ordinary C++ in the new parent, including x87/CFG ordering.

## Difficult native 0x186: explicitly negative, not a fake acceptance

Real `0x186` contains an original stage-5 trajectory method
`00453E60(2.0f)` and genuine projectile `00453A70` for sprite
kind `0x325`, with float y offset `00658290` and side-derived
x based on signed `+0x66 * 0xAA`. Natural C++ reproduces **all 82
original native x86 mnemonics and original 8 actual COFF fields**.
But the target has real integer-to-float temporary `MOV [EBP−0x84],EDX;
FILD [EBP−0x84]`; the new partial full-parent C++ probe instead
emits `EBP−0x20` at native x86 ordinals **72 and 73**. Both generated
instructions are three bytes shorter, so the source case is **284 B
against 290 real original CODE B**. These are true compiler
frame/temporary-lifetime differences, not relocation operands.
Do not count this case strict, invent a fake local or byte graft to
force the original EBP slot. The historical type declaration of
`SpawnFloatXYAt453A70` is provisional compiler grammar, not known
source ownership. Its near-complete native geometry/negative result
is retained for subsequent original parent-scope reconstruction.

Crucially, the old F598 helper's `normalized()` erases **all EBP
slot offsets** to compare register roles. This result's new verifier
also performs an independent **raw physical EBP operand comparison**,
normalizing only the already proved saved-receiver slot `-0x44` to
generated `-8`. It therefore requires precisely these two nonexact
`0x186` scratch ordinals and requires **zero** raw local-role
differences in the three accepted `0x187/0x188/0x189` cases. All
original 8+5+5+9 PE fields are individually cross-checked against
the compiler's real typed `REL32`/`DIR32` field source symbol, zero
addend and genuine native PE call/float target. Only independently
proved absolute float globals may be normalized as unlinked fields.

The ordinary C++ source fragment is
[`FighterMotionContinuationF657.inc`](../probes/FighterMotionContinuationF657.inc).
[`verify-fighter-motion-continuation-f657.py`](../scripts/verify-fighter-motion-continuation-f657.py)
regenerates the full original selected giant source from native
fingerprints, cold-compiles the **one** parent source TU and also
rechecks all prior **14 strict** native cases `CF/D0/D1/D2/12C/
12D/12E/12F/130/131/133/134/135/136`, and the complete original
after-RET jump DATA, against this **same new** compiler object.

This brings the original giant to **17 source-backed strict native
case interiors /1,209 original x86 roles /4,192 original internal
CODE bytes /115 real typed PE/COFF fields**. The 17 do **not** form
one uninterrupted strict sequence because the physical `0x186`
remains nonstrict between `0x136` and `0x187`.
Across F598–F657, **585 strictly reconstructed original native
inner case bodies /157,894 original CODE bytes** remain uncredited
until enclosing giant whole-function exactness. Formal authored exact
count still **943 complete original functions /862,726 CODE bytes**
(43.71% reviewed). No change to the 95 origin-unknown classifications.

```bash
scripts/repo-python scripts/verify-fighter-motion-continuation-f657.py
scripts/repo-python scripts/verify-fighter-late-stages-f656.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Native target observations, new giant CPP/COFF/PDB, compiler logs and
source comparison receipts are preserved under ignored
`.analysis/f657-fighter-motion-continuation/`, including the original
nonstrict `0x186`. No full 943-unit cold replay, manual target patch,
artificial stack-local padding or external Oracle whole-function
acceptance was used.
