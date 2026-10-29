# F614 — full original native burst action0x58 in eleven fighter giants

**Pinned Japanese TH075 1.11 native PE, ordinary original-profile VC7.1
C++ source and strict physical COFF proof. Entire giant original
functions remain NONEXACT.** Target SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This follows F613's native action0x4C recovery in all eleven large
fighters, continuing the *real same giant function* indexed second
switch. The next original nondefault complete native handler is
**0x58** at packed-after-RET jump table dense index **17**, immediately
followed by handler **0x59** at slot **18**; original action codes
0x4D..0x57 must not be hallucinated as separately callable original
functions, or as independently matched action bodies.

## Exact original PE action semantics versus natural C++

The ordinary original `0x58` initializes live motion on stage/frame
zero: negate `+0x94` into float `+0x50`, copy the **raw DWORD** from
`+0x98` into `+0x54`, set drag at `+0x5C = 0.8f`, and reset `+0x7C`.
On actual ground contact against real float global `0065782C`, it
converts two independent float motion components to the two adjacent
**signed-short** native trajectory values at `+0xF00/+0xF02`, except
for the genuine actor `005AEEC0`, which uses `+0xEFC/+0xEFE`.
Both conversion calls go to real CRT `__ftol2` at `006406AC` using
native float scaling global `00657888`. It resets actor state, clears
vertical displacement, sets original next action to `0x59`, initializes
trajectory with **3.0f** (not F602's 2.0f) and prepares action `0x16`.

The native full body then has a real VC7.1 **signed `int` loop counter
at `EBP−4`**:

```cpp
for (int burst=0; burst<10; ++burst)
    SpawnDirectedAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
```

All original per-iteration `MOV/ADD/MOV`, loop `CMP 10/JGE`, call
arguments and loop-back branch match exactly in the natural C++.
It separately tests the actual signed short `+0xEFA` against **25**,
clears it only when `>25`, and invokes the native `0x3E3` projectile
spawn. That event is conditional and not a fake eleventh loop
iteration. On the non-contact continuation, original frame-state
query `0040FA30` may send `stage-1` via `0040FB40`. A final
stage-one/frame-zero branch uses two separate genuine native
`FLD global; FLD member; FUCOMPP/FNSTSW/TEST AH,0x44` sequences to
select auxiliary state 3 or 2, preserving the real source
`*(&POS)==g_ThresholdAt0065782C` lvalue evaluation order and both
actual switch-case `break`s.

The two real special fighter originals `0045DD70` and `0058AF60`
add **19 x86 instructions /70 original CODE bytes**: after the
frame-1 condition, a separate real signed-short **`+0xF0C`
one-shot** guard optionally calls game projectile creation
`00453A70` for **`0x3B7`, side 1** or **`0x3E7`, side 0**,
respectively. The actual signed byte direction at `+0x66`, real
`+0x44/+0x48` positions and receiver `ECX` thiscall are preserved.
Their preceding 10-projectile and `+0xEFA` bonus-spawn behavior is
independently unchanged; these are not F613's recovery state.

Tracked normal C++ source:
[`FighterTrajectoryBurst58F614.inc`](../probes/FighterTrajectoryBurst58F614.inc).
The source has no original machine-code grafting, inline assembly,
register forcing or fake stack locals. A preliminary compiler probe
initially showed only 135 instructions even for the two special
fighter cases due to a **test harness bug**, where semicolon-separated
Python statements after a single-line `if` accidentally retained
`F614_STAGE1_SPAWN=0`. Inspecting the newly built source caught this;
the experimental harness was corrected, **both special original
154-instruction cases separately rebuilt**, and only then accepted
under the strict F614 original native PE verification. This is an
important example of distrusting old hypothesis/tool logs until the
actual live generated source and compiler proof have been checked.

## Original physical native case and 17/18 typed PE/COFF fields

[`verify-fighter-trajectory-burst-f614.py`](../scripts/verify-fighter-trajectory-burst-f614.py)
independently decodes the original physical 0x58/0x59 complete case
extent, the true sparse-to-dense jump table and 10-shot loop/bonus
conditions, the original x87 operand roles and all real physical
typed `DIR32`/`REL32` PE/COFF destinations. For the two original
`FLD` global operands (native x86 ordinals 113/120, or 132/139 in
the real 154-instruction variants), source's unlinked `FLD [0]`
operand is normalized **only after** verifying the true exact
`DIR32` field position, zero addend, original absolute destination
`0065782C` and source symbol. All other GPR/x87/CFG roles and the
actual original byte widths are individually checked.

Every selected whole fighter source is freshly compiled with pinned
MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. All **29 earlier real
original game cases**, including F610/F611 0x4A and F613 0x4C, and
complete separately owned physical after-RET packed jump DATA are
also rechecked on *the same fresh OBJ*. The original `00564BE0`
case has exactly **37 wider native EBP−0x88 receiver MOVs (37×3=111
additional bytes)**; no synthetic frame padding or width relaxation
is accepted for other owners.

| Whole original fighter still NONEXACT | Native complete 0x58 CODE | Original x86 | Actual typed physical COFF |
| --- | ---: | ---: | ---: |
| `0045DD70` | 539 B | 154 | 18 |
| `0058AF60` | 539 B | 154 | 18 |
| `005D73C0` | 469 B | 135 | 17 |
| `00486550` | 469 B | 135 | 17 |
| `004AC040` | 469 B | 135 | 17 |
| `00543210` | 469 B | 135 | 17 |
| `00564BE0` | **580 B** | 135 | 17 |
| `004D7E70` | 469 B | 135 | 17 |
| `004F7130` | 469 B | 135 | 17 |
| `005AEEC0` | 469 B | 135 | 17 |
| `005214B0` | 469 B | 135 | 17 |
| **F614: eleven genuine complete *case interiors*** | **5,410 B** | **1,523** | **189** |

F598–F613 had studied 319 original complete internal case bodies /
79,377 original native inner CODE bytes. **F614 brings this to 330
original internal game-case bodies /84,787 native inner CODE bytes**.
These interior cases are **not 330 independent callable complete
functions** and no such fragment is accepted as original exact
whole authored CODE. All eleven enclosing fighters and the other
original giant owners remain NONEXACT; official accepted
whole-authored ledger remains **943 functions/862,726 original CODE
bytes**. There is no full 943-unit cold replay, target modification,
manual ASM or external Oracle acceptance receipt.

## Rebuild only an affected original fighter giant source TU

```bash
scripts/repo-python scripts/verify-fighter-trajectory-burst-f614.py --boss 0x004F7130
scripts/repo-python scripts/verify-fighter-trajectory-burst-f614.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-trajectory-burst-f614.py --boss 0x0045DD70
scripts/repo-python scripts/verify-fighter-trajectory-burst-f614.py --boss 0x0058AF60
# Optional only the eleven affected C++ giant source probes:
scripts/repo-python scripts/verify-fighter-trajectory-burst-f614.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Fresh actual original game-backed compiler objects, x86/typed-field
receipts and full source compiler logs are in ignored
`.analysis/f614-fighter-burst-source/`, with the experimental
harness/corrected initial attempts in `.analysis/f614-burst-trials/`.
