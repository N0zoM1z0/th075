# F613 — genuine complete native recovery action0x4C inside eleven fighter giants

**Pinned Japanese TH075 1.11 original executable against ordinary VC7.1 C++
source, not an independent exact whole-function adoption.** Target SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This extends F598–F611's genuinely source-compiled *whole giant* fighter
`Advance()` C++ probes beyond the recovered original action0x4A. The
real second compressed native switch maps action **0x4C** to packed
dense index **16**; the next independent source case is **0x58** at
index **17**. Original codes 0x4B/0x4D..0x57 do **not** establish
additional independent original function or action bodies, and the
complete original after-RET packed jump DATA is separately owned.

## Original native behavior and a corrected actual C++ branch

Every original fighter has the same **74 native x86 instructions** and
14 genuine typed PE/COFF call/float fields for this action. Ten
physical original cases are **285 bytes**. Fighter `00564BE0` has
real `EBP−0x88` stack receiver loads, expanding exactly **25 genuine
receiver MOV instructions by 3 bytes each**: 360 original bytes.
The original `005AEEC0` uses its native signed-short trajectory base
at **`+0xEFC`**; the other ten use **`+0xF00`**.

Actual original PE instructions 0–13 guard a one-time initialization:
if the signed-short counter is zero, increment it and call the true
thiscall game method `0040FBB0` with integer/float/integer arguments
`(0,95.0f,0)` in the real C++ ABI and original stack push order.
The initial intuitive source incorrectly enclosed a further member
angle advance in that initialization block; its source still emitted
**74/74 native-like instructions and 285 original-style bytes**, but
its `JNE` at native ordinal 3 wrongly skipped to **case ordinal 19**.
The actual original `JNE` goes to **ordinal 14**: regardless of
whether the once-only initialization has run, it advances live float
`this+0x30` by the true original float global `00657878` **on every
frame**. Moving that ordinary C++ expression *outside* the guard
restores the exact original native branch target and GPR/x87/CFG
instruction sequence, without asm, byte grafting or fake locals.

After this unconditional angle advance, the real original source
subtracts horizontal/vertical motion `this+0x5C` from `+0x54`, tests
contact against actual float global `0065782C`, and invokes game action
preparation `00453D60(0x16)`. On ground contact, two original `FMUL`
references to float `00657888` and two genuine CRT `__ftol2`
`REL32` calls to `006406AC` convert independent float velocities
into the original adjacent signed-short trajectory slots. The source
then calls true native game reset `00453E20`, clears `+0x48`, sets
action `0x61` via `0040FAC0`, clears angle `+0x30`, starts trajectory
`00453E60(2.0f)` and invokes the separate real method `0040FC50`
without introducing an invented cdecl cleanup. On ordinary frame
completion, the real getter `0040FA30` is compared to `+0x70` and,
when equal, calls auxiliary transition `0040FB40(0)`.

Tracked natural game C++ source:
[`FighterTrajectoryRecovery4CF613.inc`](../probes/FighterTrajectoryRecovery4CF613.inc).
Its two previously provisional borrowed method names encode the
actual original **thiscall ABI**, not a claim about historical C++
class symbols or object layout.

## Eleven complete original PE/COFF and earlier source-context proofs

The selected original-backed
[`verify-fighter-trajectory-recovery-f613.py`](../scripts/verify-fighter-trajectory-recovery-f613.py)
independently reads each original native 0x4C and 0x58 complete
handler boundary from the **real original packed PE jump DATA**, checks
all 74 original instruction starts, sizes, register, x87 and CFG
roles, and all **14 typed physical zero-addend `REL32`/`DIR32` source
COFF fields** against their actual original game/CRT/global target
addresses. The verifier asserts the actual native `JNE` at ordinal 3
lands at ordinal **14**, preventing regression to a falsely scoped
source expression. It also distinguishes 285-byte compact source from
real 360-byte wide-EBP original x86 byte widths.

Every selected fighter's **entire C++ source translation unit** is
freshly compiled with pinned MSVC VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, not reused from ignored experiments.
On that *same new OBJ*, the verifier repeats the strict F610 or F611
original PE-backed checks of all **28 earlier source-backed game
cases** (including original 0x4A bounce/double-spawn) and the entire
original separately owned after-RET packed jump DATA. Source
comparison does not treat cases as standalone independently callable
functions or counted exact CODE.

| Original enclosing whole fighter (all NONEXACT) | Native 0x4C CODE | Original x86 | Physically typed native PE/COFF fields |
| --- | ---: | ---: | ---: |
| `0045DD70` | 285 B | 74 | 14 |
| `0058AF60` | 285 B | 74 | 14 |
| `005D73C0` | 285 B | 74 | 14 |
| `00486550` | 285 B | 74 | 14 |
| `004AC040` | 285 B | 74 | 14 |
| `00543210` | 285 B | 74 | 14 |
| `00564BE0` | **360 B** | 74 | 14 |
| `004D7E70` | 285 B | 74 | 14 |
| `004F7130` | 285 B | 74 | 14 |
| `005AEEC0` | 285 B | 74 | 14 |
| `005214B0` | 285 B | 74 | 14 |
| **F613 new original game *interiors*** | **3,210 B** | **814** | **154** |

With previous F598–F611 source observations, the eleven giant
fighting functions now contain **319 source-backed true internal
original action cases /79,377 original interior CODE bytes**.
These are **NOT 319 accepted independently exact functions** and
not 79,377 newly accepted authored whole CODE bytes. All 11 containing
giants plus the other 11 original giants and three authored whole
small functions remain unmatched. Official complete authored exact
coverage remains **943 complete functions /862,726 native CODE bytes**;
there has been no all-unit cold replay, external Oracle receipt or
game executable patching.

## Targeted rebuilds only

```bash
scripts/repo-python scripts/verify-fighter-trajectory-recovery-f613.py --boss 0x004F7130
scripts/repo-python scripts/verify-fighter-trajectory-recovery-f613.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-trajectory-recovery-f613.py --boss 0x005AEEC0
scripts/repo-python scripts/verify-fighter-trajectory-recovery-f613.py --boss 0x0058AF60
# Optional only the eleven newly affected giant probes, never 943 cold replays:
scripts/repo-python scripts/verify-fighter-trajectory-recovery-f613.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Generated original-backed source/COFF/PDB and original native PE
case/typed-field proof receipts are in ignored
`.analysis/f613-fighter-recovery-source/`. The preliminary one-case
branch-scope experiment is under `.analysis/f613-recovery-trials/`.
