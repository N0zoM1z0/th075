# F1143 — Original 0x389 stage guard excludes subsequent speed decay

This is an independently rechecked source correction inside the ONE
**nonexact** original 81,539-byte/17,435-x86 `CharacterObject::Advance`
function at `0050A580` in Japanese TH075 v1.11. It is NOT a new
complete exact callable.

The native `0x389` case `0051BB8B..0051BFE2` is **1,111 original CODE
bytes /238 x86**. Original `JG` at local ordinal **101**, when the
animation stage is greater than one, branches directly to **ordinal
161**. The earlier source placed signed velocity+0xD8 decrement by 15
and clamp to signed+0xDC *outside* its stage<=1 block. Its JG landed
at ordinal **146** instead, so it incorrectly decelerated even after
the animation entered later stages. The selected C++ moves the real
decrement/clamp into the stage<=1 block, after the native random
scale/0x33C projectile actions, while retaining original expression
order and exact native instruction grammar.

The current one-parent verifier `scripts/verify-characterobject-current-recovered-f1068.py`
recompiles only the whole partial giant C++ under pinned VC7.1 and
requires all **17,435 original ordered mnemonics**, all **1,834
original direct jump target ordinals** to be compared, and the actual
`0x389` JG source and original target **161**. Native `0x389` remains
**238/238 original mnemonics, GPR roles and widths**, original
physical PE external call/global positions and source scalar values.
The previous 14 known CFG target discrepancies are reduced to **13**;
these 13 are explicitly reported as unresolved correctness debt,
not waived as exact.

The live source still emits **81,560 bytes** against **81,539 original
whole CODE bytes**, and its frame/stack layout, eight other GPR-provisional
cases and two physical FUCOMPP field errors in `0x391` remain uncorrected.
**Whole original callable NONEXACT, newly accepted whole original CODE=0B.**
The 979 previously exact whole functions and their 868,243 accepted
bytes are unchanged.

Reproduce only the changed parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Do not use full-corpus cold replay. The original PE, rather than
historical prose, defines these branch target ordinals.
