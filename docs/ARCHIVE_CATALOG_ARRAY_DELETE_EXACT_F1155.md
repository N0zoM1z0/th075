# F1155 — Complete 171-byte ArchiveCatalog destructor cold exact

The independently R053-authored original `0041CE50..0041CEFA` is now
accepted as `archive-catalog-release-0041ce50`: **171 CODE bytes,
51 x86 instructions, all 14 physical PE/COFF fields, zero differences**.
Only this new unit was cold-replayed. The origin decision is unchanged.

Original whole CODE SHA256:
`558f79a85d376b77e258f05eb4bd8020d61b14bf893eaa9cd06d060ed0174975`.
The final RET is at `0041CEFA`; the following five bytes are INT3
alignment, not part of this callable. There is no owned afterRET table.

## Correct allocation pairing resolves the pointer-slot rotation

The earlier source used a named filename pointer followed by CRT `free`.
It matched all 51 mnemonics/widths and 14 field positions, but only
108/115 nonfield bytes. VC7.1 allocated filename at EBP-8, the scalar
delete receiver at -0xC and resource at -0x10, rotating the native roles.
Many historical lifetime and syntax controls retained that false premise.

The already cold-exact registration function `0041CF80`, represented in
`ArchiveOpenRegisterF353.cpp`, allocates names using `new char[strlen+1]`.
The accepted native call target `0064169D` is also bound to both scalar
and array deallocation operators elsewhere in the exact manifest; its
address alone never established that the original source called `free`.

The correct natural source is:

    delete *g_ArchiveResourcesAt0068BE08.At(index);
    delete[] *g_ArchiveNamesAt0068BE1C.At(index);

With the standard `<new>` declaration, the second call emits the genuine
array-delete symbol `??_V@YAXPAX@Z`, resolving to `0064169D`. All 115
nonfield bytes match. The actual compiler temporaries now naturally use
resource EBP-0xC, scalar deleting receiver -8 and filename -0x10. Frame
0x18, unsigned index -4, saved-this -0x14 and deleting-result temp -0x18
also agree. No fake local, forced offset, assembly or operand mask exists.

The source preserves the decremented shared use-count guard, indexed
resource/name order, real scalar deleting destructor `0041D8C0`, both
native list Clear operations and the original failure behavior. Borrowed
interfaces do not establish complete historical class layouts or names.
No resource, container, CRT or compiler callee code receives duplicate credit.

## Canonical acceptance

    scripts/repo-python scripts/replay-exact-units.py --unit archive-catalog-release-0041ce50

The canonical source is `src/ArchiveCatalogReleaseF1155.cpp`. The match
unit records all physical offsets, decorated symbols, zero addends and
native destinations. The acceptance ledgers and frozen adoption manifest
preserve the original before row and unchanged independent R053 origin.

Result: **980 complete exact functions /868,414 original CODE bytes**;
24 attributed whole functions remain nonexact (22 giant and two smaller).
Reviewed authored coverage is 44.00%; conservative coverage is 43.92%.
The 98% goal remains incomplete. Original probes, structural preview,
cold-build log, full replay receipt and adoption script are retained under
ignored `.analysis/f1155-archive-array-delete/`.

Historical F584/F900/F936/F1034/F1078 negative results remain true for
their recorded free-based sources; they do not describe this accepted body.
