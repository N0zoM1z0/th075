# F560 — true precontact-stage action 8 of the entire `00543210` fighter giant

**Original Japanese TH075 v1.11 PE / actual native VC7.1 C++ experiment,
not accepted whole-fighter CODE exactness.** The original SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The 58,294-byte complete original `00543210` seven-switch fighter giant
is first verified against its entire original CODE SHA, all physical
first-switch case slots, all six other jump groups and **943 genuine
post-RET DATA bytes**. Then one real new C++ source prototype is freshly
compiled under pinned MSVC 7.1. Other source cases remain explicitly
diagnostic marker stores, **not** restored game code.

## Why action 8 requires a distinct source algorithm

The entire native physical action-8 body is bounded by the ninth/tenth
DWORD destinations of the original first 11-slot jump table:
**403 complete CODE bytes, exactly 117 decoded original x86 instructions**.
Unlike this same character's action 6 and 7 (115 instructions, 393 bytes
apiece), original action 8 moves its full **13-instruction auxiliary-stage
comparison and callback before the collision x87 branch**. The ordinary
C++ that generates the original instruction/control order is:

```cpp
if (S16(0x62) == 3 && POS54 < g_ExtraThresholdAt00657D14)
    SetAuxActionAt40FB40(4);
if (POS48 > g_ThresholdAt0065782C) {
    // Genuine previous contact x87 subtraction, threshold, state/reset,
    // including an early return from the enclosing whole fighter.
}
// Frame counters and stage updates remain original-native C++.
```

In the original action 6/7 source this callback occurs **after** the
collision branch. Both ordering variants have natural x87/COFF backing,
but cannot be treated as interchangeable source. Action 8 also tests
unsigned `this+0x511 == 4`, passes native `0xCE` to `0040FAC0`, and on
stage-three activation performs four original MOV stores in the order:

```cpp
POS = -7.0f;
FLAG = 0;
POS54 = 18.0f;
POS5C = 0.95f;
```

These are physical original float/byte immediate values at original
instruction ordinals 94, 96, 98, 100. The direct native original
`0040FB40(4)` call is observed at ordinal 42; original x87 contact
comparison follows at ordinals 43–45, not before that auxiliary call.
The original actor's virtual method call remains
`call dword ptr [edx]`. No full original type/vtable layout is claimed.

## Two independent new source generators validated the same real block

Two separate C++ source-generation/verification experiments were run,
each deriving the native case from the **original PE** rather than an
ignored C++ snapshot, each compiling one new affected VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` diagnostic TU:

- Tracked authoritative reproducer:
  [`scripts/verify-fighter-precontact-stage-action-eight.py`](../scripts/verify-fighter-precontact-stage-action-eight.py).
- Independently constructed full native/COFF verifier preserved (including
  its failed initial unsigned/negative-float parse and corrected source
  policy) under ignored
  `.analysis/f560-543210-action-eight/independent-f560-source-verifier-preserved.py`,
  with its own generated source/object/summary in
  `.analysis/f560-early-aux-action8-source/`.

Both recompiled and confirmed **the same native complete 115/115/117
instruction case sequence and 393/393/403-byte case geometry**, all
**24 genuine per-case physical typed COFF `REL32`/`DIR32` references**,
true per-fighter EAX/ECX/EDX register choices, x87 operand roles,
original conditional branch graph and source virtual call form.
They also independently checked **156 original-style physical switch
DWORD COFF references**, original repeated/default handler partitions,
**319 byte-identical original sparse index bytes** and the complete
**943 after-RET DATA-shape bytes**. Every original case span is bounded
by authentic native PE jump-table targets, not independently assumed.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-boss-family.py
# Only the new affected original-backed C++ probe, never full cold replay:
scripts/repo-python scripts/verify-fighter-precontact-stage-action-eight.py
```

**Important accounting:** all **1,189 original interior action 6/7/8
CODE bytes** are still part of the **unmatched complete 58,294-byte
fighter giant**; 943 after-RET DATA bytes belong to tables, not source
CODE. There is **zero new accepted exact function/CODE/DATA credit**,
no fabricated stack padding/byte grafting and no external Oracle receipt.
