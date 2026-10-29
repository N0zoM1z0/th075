# F608 — complete real 118-instruction action0x49 in two special giant fighters

**Pinned original Japanese TH075 1.11 native PE to ordinary VC7.1 C++;
whole fighter functions remain nonexact.** Original target SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
F607 source-reconstructed native indexed action0x49 in the nine ordinary
fighter giants (99 x86 /350 bytes, or wide 441). The two remaining giant
originals `0045DD70` and `0058AF60` have genuinely different **118-x86,
420-byte** action0x49 bodies. The full native CODE extents are bounded by
physical native compressed second-switch dense DWORDs 14 and 15 for
action0x49 and 0x4A; the after-RET table DATA remains separately owned.

## Original extra behavior and complete native C++ reconstruction

On stage/frame zero, both originals negate `this+0x94` to `+0x50`,
copy the **raw 32-bit** velocity word `+0x98` to `+0x54`, store 0.8f
drag and clear `+0x7C`. They test actual ground contact using float
`0065782C`, convert two x87 float velocities into the genuine signed
shorts at `+0xF00`/`+0xF02` using **two** real CRT `__ftol2` calls,
then call original `00453E20`, `0040FAC0`, `00453E60` and `00453D60`
in their native order. The following real receiver-frame query
`0040FA30` can dispatch `stage-1` via `0040FB40`.

**Unlike F607's nine normal cases**, the original stage-one/frame-zero
branch then tests an independent signed-short `+0xF0C` one-shot flag.
When zero, the original sets this flag to one and spawns a projectile
with actual game `thiscall` `00453A70`, real `+0x44/+0x48` coordinates
and `+0x66` byte direction. The two original policies are:

| Full original containing giant | Whole real action0x49 | x86 roles | Physically typed COFF | Actual projectile |
| --- | ---: | ---: | ---: | --- |
| `0045DD70` | **420 native bytes** | **118** | **16** | `0x3B7`, side 1 |
| `0058AF60` | **420 native bytes** | **118** | **16** | `0x3E7`, side 0 |
| **F608** | **840 original internal bytes** | **236** | **32** | |

After the real spawn guard, the same two original
`FLD global; FLD member; FUCOMPP; FNSTSW; TEST AH,0x44` tests
select auxiliary action 3 or 2, preserving the original x87 equality
rather than replacing it with a deceptively similar `FCOMP` or other
floating-point predicate. The genuine original field at `0065782C`
appears twice as a typed `DIR32` in the ordinary C++ COFF object;
its unlinked immediate is allowed to differ **only after** verifying
both physical field positions, exact symbol/type/addend and original
native destination.

Tracked natural C++ source
[`FighterTrajectoryLandingSpawnF608.inc`](../probes/FighterTrajectoryLandingSpawnF608.inc)
uses a real nested stage-one frame-one-shot block and a source-level
member lvalue for `*(&POS) == original global`, with separate `break`
statements on both native auxiliary branches. The genuine 19 new
instructions/70 bytes over F607 are the real guard and 5-argument
`SpawnDirectedAt453A70` call, not invented padding, machine-byte graft
or a false whole-function cutout.

The targeted original-PE verifier
[`verify-fighter-trajectory-landing-spawn-f608.py`](../scripts/verify-fighter-trajectory-landing-spawn-f608.py)
independently rereads the original 118-x86/420-byte native extent,
the one-shot projectile flag and original call ABI, and all **16** typed
PE/COFF `REL32`/`DIR32` call/global fields at their true x86 ordinals.
It cold-compiles only the selected original fighter whole C++ source
with pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Each compiled object
is **also** checked for its previous 23 first/contact game actions,
original 131-instruction 0x46 with its stage-one spawn, both previous
0x47/0x48 variants and the complete real after-RET switch table.

Together with F607 this reconstructs **all eleven actual original
0x49 internal action bodies**: **1,127 original x86 roles, 4,081
original internal native CODE bytes, 167 actual typed COFF fields**.
The F598–F608 cumulative bounded source study covers **297 genuine
native internal cases /70,961 original internal CODE bytes**, **not
297 separately callable complete functions or exact units**. All
11 entire fighter parents and the other 11 unmatched giants remain
NONEXACT; officially accepted authored code is unchanged at
**943 exact complete functions /862,726 CODE bytes**. There is no
all-unit cold replay or external Oracle acceptance.

## Reproduce exactly one or these two affected source compilations

```bash
scripts/repo-python scripts/verify-fighter-trajectory-landing-spawn-f608.py --boss 0x0045DD70
scripts/repo-python scripts/verify-fighter-trajectory-landing-spawn-f608.py --boss 0x0058AF60
scripts/repo-python scripts/verify-fighter-trajectory-landing-spawn-f608.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Original-backed compiler sources, COFF objects, PDBs, x86 and true
relocation receipts are in ignored `.analysis/f608-fighter-landing-source/`.
Earlier source-expression trials are under `.analysis/f608-landing-spawn/`.
