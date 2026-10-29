# F581 — authentic CharacterObject parent-scatter actions 0x33E and 0x33F

**Original Japanese TH075 1.11 native PE and pinned VC7.1 natural C++
source proof; the original whole 33,293-byte fighter remains nonexact.**
Original PE SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

The real original compressed case-handler addresses physically bound
`0x33E` and `0x33F` as two separate genuine action bodies inside
original one-switch giant `004EBDA0`. F581 extends the very same
one-function C++ `Advance()` from F572–F580, without a copied compiler
snippet, ASM, original target machine-byte graft, or fabricated
padding. Unknown later actions remain diagnostic-only markers.

## Entire real original game state `0x33E`: 127 instructions, 489 bytes

The native source has two genuine parent checks of signed owner
`+0xE4/+0x60 == 0x2BE`; on the first it sets actor `+0x44`
position from parent `+0x44` plus **signed direction byte times 140**
via real integer `IMUL/FILD/FADD`. It updates actor `+0x48` from
parent `+0x48` plus original global `006590AC`.
When the parent state differs and signed stage `+0x62 < 7`, it issues
real `0040FB40(7)` and exits. Stage/frame-zero initializes native
`+0x80`, `+0x7C`, then only if `S16(+0xD8) != 1` performs the actual
`0040FBB0(0,0,0)` reset, float scales `+0x1C/+0x20=1.5f`,
color FF, and signed timer `+0x80=10`.

At stage 6, the original calls `00455580(0,4)`, subtracts 2,
`FILD`s the true temporary, **FMULs original float global `006578C0`**
and **FADDs `006581E0`**, then stores scale `+0x20`. Stage 7
applies the separate original **`FMUL 00659094`**; current action
`0040FA30` conditionally resets via `0045B830`, while a
stage7/frame0/`+0xD8 < 10` transition issues `0040FB40(6)`, zeros
`+0x7C`, then increments signed `+0xD8`.

The newly compiled normal C++ reproduces all **127 original x86
register/x87/branch/byte-width instruction roles and all 489 native
case CODE bytes** under strict original machine-order grammar, with
**10 genuine zero-addend physical COFF fields** at the exact native
instruction positions.

## Entire different state `0x33F`: 101 instructions, 381 bytes

The parent-state check instead requires `+0x60 == 0x2C1`, and the
native directional movement uses **signed direction ×180**, not
×140. Outside that state and with native stage `<17`, it invokes
**`0040FB40(17)`**. The stage-zero initializer sets actual
`+0x7C=0`, calls `0040FBB0(0,0,0)`, initializes scale fields to
**2.0f/1.5f** (different from 0x33E), native signed timer to zero,
color FF and owner signed `+0x80=25`. A real `0040FA30` state query
may reset. On signed stage 13/frame 0 with signed timer `<2`, it
calls native `0040FB40(6)` and increments the actual timer.

The source reproduces **101 original x86 instructions /381 bytes
in native order**, with **6 physical true COFF call/global refs**.
It is not an alias of 0x33E and no `0x33E` random scatter action is
invented in the `0x33F` C++ branch.

## Entire original case and physical source/COFF verification

Tracked source:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
F581 original-backed fresh-compiler checker:
[`scripts/verify-characterobject-parent-scatter-f581.py`](../scripts/verify-characterobject-parent-scatter-f581.py).

The checker hashes/reads the **entire pinned original giant CODE** and
complete sparse switch DATA, then compiles **ONE newly affected
ordinary VC7.1 translation unit** with
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Every original game-action case
is bounded by the real Japanese PE physical dense/sparse switch
handlers, not assumed continuous case IDs. It validates the full
native x86 instruction count, all real EAX/ECX/EDX/x87 control/branch
roles, complete per-instruction lengths, and genuine typed COFF
`REL32`/`DIR32` call/global targets, source symbols, original
instruction ordinals and zero relocation addends.

| Real whole original action group | x86 original instruction roles | Real internal CODE (not independent exact credit) | Actual typed COFF call/global fields | Machine-order status |
| --- | ---: | ---: | ---: | --- |
| Previous 25 original cases F572–F580 | 3,216 | 11,895 B | 224 | Three previously bounded read-only swaps, two EBP width differences |
| New `0x33E` | **127** | **489 B** | **10** | **Strict** |
| New `0x33F` | **101** | **381 B** | **6** | **Strict** |
| **Total 27 real action bodies** | **3,444** | **12,765 B** | **240** | Whole original 33K source still unmatched |

All 60 physical zero-addend original switch DWORD COFF slots, correct
original repeated/default handler partitions, **198 byte-identical
native sparse index bytes** and **438 distinct after-RET DATA bytes**
are revalidated. The 3 prior F573/F574/F578 read-only MOV/FLD order
swaps remain explicit; two original deep EBP cases 0x330/0x331
still have 18 native extra bytes each. No new machine-order
exception in 0x33E/0x33F. These 12,765 inner original CODE bytes
are **not 27 independently exact original functions** and remain
part of the nonexact whole 33,293-byte giant.

### Selected-only, no cold all-unit replay

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-parent-scatter-f581.py
scripts/repo-python scripts/verify-characterobject-four-next-actions-f580.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

New compiler/COFF/PDB and original case JSON summaries are retained
under ignored `.analysis/f581-characterobject-scatter-source/`;
native complete instruction disassemblies and source trial controls
are preserved under `.analysis/f581-characterobject-more-actions/`.

## Concurrent small original function check (not accepted exact)

The separate original nonvirtual ArchiveCatalog destructor at
`0041CE50` is still **171 whole native CODE bytes /51 x86
instructions**. A fresh matrix of **14 meaningful natural C++
filename-lifetime variants** (true POD record, union, 1-element
pointer array, `void*`, volatile pointer, unsigned byte pointer and
scoped/outer declarations) was recompiled in the correct pinned
VC7.1 `/GX-` profile. **14/14 compile to 171 bytes /51 instructions,
but all remain at only 108/115 comparable nonrelocation bytes**.
Each preserves the same wrong three-way local variable-slot
allocation compared with the original real resource-delete temps
and filename slot. The physical original 171-byte function and all
relocation fields are NOT accepted as exact; none of the 14 variants
is used as fake padding. All source/object/log/JSON evidence remains
under ignored `.analysis/f581-archive-expr-order/`.

**This F581 study changes no accepted whole CODE or DATA, has no
full all-unit cold replay and has no external Oracle receipt.**

## F582 follow-up: native absolute-motion action 0x340 and 0x341

The same ordinary VC7.1 switch source has gained two genuinely
reconstructed **159-instruction/597-byte** original action bodies,
including real original cdecl float absolute-value `00412D90`,
parent direction and distinct effects 0x338/0x33A vs 0x342/0x344.
The F581 targeted source verifier remains scoped to its prior 27
native actions; [F582 source evidence](CHARACTEROBJECT_ABSOLUTE_MOTION_F582.md)
checks all 29 complete real action bodies with strict physical COFF
fields and no extra read-only ordering exceptions. Whole giant CODE
remains nonexact.
