# F559 — original 458-byte action 8 inside the 61,872-byte wide-frame giant

**Complete original-case native C++ codegen evidence, NOT an exact full
fighter/source function.** The original Japanese TH075 1.11 executable is
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The independent whole-original 61,872-byte fighter controller begins at
`00564BE0` and contains seven original code switch groups and **874 bytes
of distinct after-RET switch DATA**. Its SHA256 and physical original jump
and sparse bytes are checked by the original-only F537 full-function
verifier before attempting any C++ compilation. This extends the earlier
[115-instruction no-flag C++ cases](FIGHTER_STAGE_NO_FLAG_F557.md).

## What the original action 8 actually does

The physical first-switch ninth and tenth native DWORD destinations
delimit exactly **458 original CODE bytes / 102 native instructions**:
**it is an entire original action case, not a new independently exact
function.** It tests the original unsigned `this+0x511` byte state
against **4**, invokes the native state setter with **0xCE**, and
conditionally resets the motion on x87 collision. It advances signed-short
frame counters, writes the actual stage-two motion initialization
`this+0x50 = -4.0f`, `this+0x54 = 12.0f`, `this+0x5C = 0.4f`, and issues
the genuine `call dword ptr [edx]` actor vtable operation. Unlike this
fighter's native action 6 and 7, **action 8 does not contain a separate
auxiliary-stage float callback**; none of its 102 original instructions
writes `FLAG = 0` after stage initialization. Both omissions are recorded
as original game behavior, not guesses from another fighter's source.

The natural source is derived from a real, previously verified
104-instruction case-six C++ expression, but it removes the actual
native-absent flag assignment and changes **only the original-backed
state test, callback argument and float position**. Its action 6 and 7
source is regenerated through tracked F557 source helpers. All unrelated
switch cases are **test-only marker stores**, not reconstructed original
behavior.

## Why 458 native bytes versus 352 newly compiled C++ bytes?

The isolated VC7.1 source probe emits **352 bytes / 102 instructions**
for action 8. The *entire original* source case has the same exact 102
instruction/branch/x87/member/register grammar, but its much larger native
controller saves the receiver pointer at **EBP-0x88**, outside the compact
8-bit stack displacement range. The original contains **34 physical
receiver reloads** whose disp32 operands are **3 bytes wider** than those
in the small source probe. Additionally, the real original case contains
one **near `JL` rather than short `JL`**, adding **4 bytes**. The
original-to-probe size gap is therefore
`(34 × 3) + 4 = 106 bytes`, and `352 + 106 = 458`. This is verified
instruction by instruction; there is **no source padding, assembly or
machine-byte copying**.

## Real compiler/COFF evidence across *all three* native actions

[`scripts/verify-fighter-wide-action-eight-source.py`](../scripts/verify-fighter-wide-action-eight-source.py)
reads the entire native original, regenerates one C++ prototype containing
three actual original action bodies, and fresh-compiles **only that one
new translation unit** under pinned MSVC 7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`:

- Whole action **6 and 7**: two original **508-byte /115-instruction**
  cases, each compared against a separate **393-byte /115-instruction**
  native C++ candidate (the original width expansion is
  `37 × 3 + 4 = 115` bytes in each case).
- New whole action **8**: one original **458-byte /102-instruction**
  case, versus the **352-byte /102-instruction** candidate (the width
  expansion is `34 × 3 + 4 = 106` bytes).
- Across these three: **332/332 original register/x87/control-flow
  instruction roles**, **22/22 genuine typed `REL32`/`DIR32` physical
  case COFF fields**, the original virtual-call receiver/register form,
  all **131 original-style physical DWORD jump-table COFF references**,
  default/repeated-target partitions and **350/350 byte-identical native
  sparse-index bytes**. The whole **874-byte original after-RET DATA
  layout** is separately checked, *never accepted as CODE*.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-boss-family.py
# One new/affected natural C++ TU only; not an all-unit cold replay:
scripts/repo-python scripts/verify-fighter-wide-action-eight-source.py
```

Fresh source/COFF/PDB/JSON and compiler logs are saved under ignored
`.analysis/f559-wide-action8-source/`; native experimental source and
byte-displacement comparisons are retained under
`.analysis/f559-wide-case-eight/`. The genuine original **1,474 CODE
bytes within these three cases are still part of an unmatched 61,872-byte
giant original**. No partial-function or full-fighter exact CODE credit,
no full all-unit cold replay and no external Factory/Oracle receipt.
