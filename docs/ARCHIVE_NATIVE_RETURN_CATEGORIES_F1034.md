# F1034 — The native ArchiveCatalog destructor does not depend on At() value-category declarations

**F1155 supersession:** this original whole destructor is now accepted cold
exact with array deletion of registered names, paired with the original
`new char[]`. These earlier free-based negative sources remain preserved;
see [complete F1155 proof](ARCHIVE_CATALOG_ARRAY_DELETE_EXACT_F1155.md).

The original pinned Japanese TH075 1.11 independently authored
`0041CE50` ArchiveCatalog nonvirtual destructor is one **171-byte / 51-x86**
complete callable. The original PE contains 14 real physical external
call/global relocation fields. Its three actually used pointer values
occupy **resource at EBP-0x0C**, **deleting receiver at EBP-0x08** and
**filename for CRT free at EBP-0x10**. The closest normal VC7.1 C++ emits
exactly 171B/51 x86 and preserves all 14 physical fields, but cyclically
rotates these locals to EBP-0x10, EBP-0x0C and EBP-0x08.

The existing F900/F936 lifetime and loop-expression experiments did not
establish whether source declarations of the two list `At(index)` return
value categories controlled the original local storage. F1034 tests
that specific uncertainty with **11 freshly compiled entire ordinary
VC7.1 `/GX-` destructors** and the original compiler profile.

Both genuinely used list interfaces were independently declared as
`T** At(index)`, `T*& At(index)`, or `T* const* At(index)`; actual delete
and filename expressions were updated to respect the reference forms.
Nine full-source combinations generated the same **171B/51 x86,
14 physically identical external relocation fields, and 108/115
native nonrelocation bytes**. The original three pointer stack slots
remained wrong in every one. Two natural variants that passed the
filename directly to CRT `free` generated **165B/49 x86** and are not
whole-original matches; the real named local cannot be silently removed.

The verifier reads the pinned original PE, independently checks each
of its 14 physical typed targets, then compares the entire resulting
function only when its original full CODE/ordinal and COFF geometry
match. It never truncates an overlong/short function or counts one
internal fragment. The original destructor remains **NONEXACT**.

Reproduce the bounded 11 whole-function compiles:

    scripts/repo-python scripts/verify-archive-return-categories-f1034.py

All generated C++/COFF/PDB compiler logs and results are retained in
`.analysis/f1034-archive-return-categories/`, including the per-byte
mismatch set. The selected source, relocation manifest and ownership
ledger remain unchanged. The next meaningful research direction is
a genuine different resource/filename receiver lifetime or nested
source-level value owner, not merely `At`'s value-category syntax.

**Zero new exact callable CODE bytes. No all-function cold replay.**
