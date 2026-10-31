# F900 — 25 complete original Archive destructor real resource/filename lifetime variants

Original pinned Japanese TH075 v1.11 independently authored
ArchiveCatalog destructor 0041CE50 is exactly
171 complete callable native CODE B/51 x86,
with 14 physically typed native PE call/global fields.
Original real EBP roles are index -4, resource -0xC,
scalar delete receiver -8, filename to free -0x10,
saved this -0x14 and deleting-result temp -0x18.

The natural source matches all 51 native instruction
mnemonics, sizes, physical PE call locations/types/targets,
but only 108 of 115 native nonrelocation machine bytes,
because the three actually used pointer temporaries
have the wrong EBP owner assignment.

F900 investigates new genuine original-source lifetime
models using NORMAL pinned VC7.1 /Od /GX- compilation:
one actual resource field or one actual filename field,
two-field resource/filename structs (both field orders,
declaration scopes and delete expressions), all six
orders of three actually used index/resource/filename
fields, genuinely reused union storage for a deleted
resource followed by CRT-freed filename, real
pointer-to-pointer list-entry plus filename owners, and
an actual index/filename pair with separately
used resource pointer. No source field is inert
and all variants call both native list At methods,
perform scalar delete and CRT free, and then
both original Clear methods.

| Complete source type | Whole generated CODE | Native PE result |
| --- | --- | --- |
| Direct native baseline | 171B/51 x86/14 refs | 108/115 native nonfield bytes, not exact |
| Filename-only real aggregate | 171B/51 x86/14 refs | 102/115 native nonfield bytes, worse |
| Remaining 23 actual live-owner variants | 177B/53 x86/14 refs | Extra genuine pointer-lifetime MOVs, wrong whole extent |

All 25 compile successfully and preserve the actual
14 original semantically grounded C++ call/global symbol
identities and original zero COFF addends. The TWO
original-extent sources are compared byte-for-byte over
the entire original 171B function with only the real
14 physically aligned original PE relocation fields
excluded after independent offset/type/destination
checking. Both 171B sources have correct original
51-instruction mnemonic/size geometry but wrong
real source temp slots. The 23 longer variants are
NOT cropped to 171B and no local stack slot coincidence
is counted as exact original CODE.

Original resource EBP-0xC, receiver EBP-8,
filename EBP-0x10 remain unresolved.
This entire independently callable original authored
function remains NONEXACT.

Targeted replay of ONLY the Archive whole destructor:

    scripts/repo-python scripts/verify-archive-grouped-live-owners-f900.py

All complete source C++ variants, normal VC7.1 COFF/PDB,
compiler logs and native original PE JSON receipts remain
under ignored .analysis/f900-archive-grouped-locals/.
No all-unit cold replay, no whole-function CODE credit.
