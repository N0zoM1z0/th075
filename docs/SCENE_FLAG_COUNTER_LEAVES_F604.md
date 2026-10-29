# F604 — two complete native 24- and 31-byte game-state leaf source shapes

**Genuine original Japanese TH075 1.11 whole-function byte identity,
not accepted authored source provenance.** Original `resources/th075.exe`
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This work supplements F602/F603's complete internal actions inside
all eleven still-nonexact giant fighter bosses; small native leaves
must be investigated seriously as *whole functions*, but original
source ownership cannot be guessed from a matching source alternative.

## Recheck the native PE: two distinct original functions

| Original PE entire function | Original native extent | Actual source semantics | Native COFF fields |
| --- | --- | --- | ---: |
| `00454C00` | **24 CODE bytes /9 x86 instructions** | Set the original receiver's 32-bit member `this+0x47C` to zero | **0** |
| `00454F70` | **31 CODE bytes /15 x86 instructions** | Read pointer at `this+0x74`, then unsigned 32-bit flags `+0x3C`; return whether `(flags & 0x20) > 0` | **0** |

The complete original register, stack prologue/epilogue, instruction
boundaries and return ABI are included. Neither has an external call
or a real relocation field; the operands are literal member offsets,
not patchable COFF placeholders. No original owner/class name or
full object layout can be inferred from these observations alone.

## Why the unsigned comparison operator is significant

Tracked [`SceneFlagAndCounterLeavesF604.cpp`](../probes/SceneFlagAndCounterLeavesF604.cpp)
uses natural typed C++ member access, not assembly or copied bytes.
The original **31-byte** native condition has these exact six
instructions after the two nested field loads:

```asm
mov edx, dword ptr [ecx+0x3c]
and edx, 0x20
xor eax, eax
cmp eax, edx
sbb eax, eax
neg eax
```

Under pinned MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, a
real unsigned `> 0` expression naturally reproduces all six and
**31/31 original bytes**. By contrast the mathematically equivalent
`!= 0` C++ expression emits an entirely different 29-byte/14-x86
sequence based on `NEG/SBB/NEG`, **not the original**. Signed `>0`
likewise emits a different `SETG` control and fails 31-byte matching.
A named intermediate pointer also changes the original stack layout
and gives 39 bytes; the true source shape needs one nested typed
pointer expression, not an invented EBP temporary. This distinction
was established by actual separate compiler builds, not by trusting
an old pseudocode `bool` label.

`00454C00` separately compiles to **24/24 original bytes** from
one ordinary `this+0x47C` field-clear expression. The independent
pinned original-backed
[`verify-scene-flag-counter-leaves-f604.py`](../scripts/verify-scene-flag-counter-leaves-f604.py)
cold-compiles **only one positive source translation unit** and checks
both full original extents, all 24 original instruction boundaries
(9 + 15), all machine-code bytes, and the true absence of COFF
relocations. An optional independently compiled 29-byte `!=0`
negative control protects the predicate-typing discovery.

## Source class/owner provenance is still unknown

The two reconstructed observation classes are intentionally distinct:
there is **no evidence that the original two methods share one
original complete game type**. The original Ghidra provisional
function boundaries and `unknown`/`review` origin classifications
are rechecked, not promoted.

A fresh scan of **all 4,351 registered complete original native
functions** found **zero literal direct CALL instructions targeting
either address**. A separate scan of the actual executable file found
zero literal DWORD pointers equal to either native address. These are
only limits of discovered explicit references: **they do not prove
unreachable code**, exclude indirect/computed calls or reveal a source
provider. They are insufficient to classify either leaf as authored
or library/compiler generated.

**F604: 55 source-backed whole-original CODE bytes (24+31), 24
complete native x86 instructions, zero original COFF fields, but
ZERO additional accepted authored whole functions/CODE bytes.** No
source, match, origin, or exact-match registry entries were changed.
The existing verified authored ledger remains **943 complete exact
functions, 862,726 original CODE bytes**.

## Remaining authored destructor blocker cross-check

Independent genuine C++ experiments continued on the whole original
`0041CE50` nonvirtual ArchiveCatalog destructor, not just on these
small leaves. Original 171 CODE bytes /51 x86/14 PE/COFF fields
require original EBP temporaries `−0xC/−0x8/−0x10` (resource,
delete receiver and filename), but the natural `/GX-` C++ source
allocates `−0x10/−0xC/−0x8`. Fresh trials included
register/const/restrict declarations, real pointer alignment, true
named array lvalues and original-equivalent conditional expressions.
`register`, const and four-byte alignment keep 171/51 but retain
**108/115** original nonrelocation byte equality, while
8/16-byte aligned pointers and conditional branches change the
complete native size; no whole-function exact claim is possible.
Full source variants, fresh COFF/PDB, compiler transcripts and
original whole-function comparisons are preserved in ignored
`.analysis/f604-archive-compiler-local-layout/`. This is a genuine
negative constraint, not a fabricated stack-padding solution.

## Targeted reproducibility (no full all-unit replay)

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-scene-flag-counter-leaves-f604.py --negative-predicate
scripts/repo-python scripts/validate-tracking.py --require-target
```

The new two native positive whole-function receipts, full original
caller audit, and optional one negative C++ source/object live in
ignored `.analysis/f604-game-leaves-source/`. No user executable was
modified, no external Oracle acceptance or all-unit cold replay ran.
