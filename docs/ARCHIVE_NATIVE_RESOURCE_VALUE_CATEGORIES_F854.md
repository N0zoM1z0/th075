# F854 — Actual Archive delete receiver value categories against complete 171B native destructor

The SHA-pinned original Japanese TH075 1.11 nonvirtual
ArchiveCatalog destructor at 0041CE50 has **171 entire
callable CODE B /51 x86 /14 real original PE fields**.
Original game physical stack roles are index EBP-4,
resource pointer EBP-0xC, actual scalar-delete receiver
EBP-8, filename freed through CRT EBP-0x10, saved this
EBP-0x14. Ordinary source returns the same whole native
size, opcode/mnemonic widths and original call fields,
but assigns the three pointer slots -0x10/-0xC/-8 and
matches only **108/115** native nonrelocation bytes.

F854 compiles **sixteen complete original-shaped pinned
VC7.1 /Od /GX-** C++ resource value-category variants.
Every value introduced is actually used by the original
delete operation or taken from the actual resource array:
named resource pointers, const/volatile/register source
pointer variables, true pointer/reference aliases to
the actual array slot, pointer-to-pointer resource array
entry, and explicit cast-bound delete expressions.
All candidates still delete genuine original list resources,
free actual filenames, and clear both original arrays,
without fabricated locals or native EXE byte changes.

| Real source value category | Whole generated compiler CODE/x86 | Physical original result |
| --- | --- | --- |
| Direct original delete, explicit value lvalue/const-ref cast expression, parenthesized dereference | **4 × 171 B /51 x86 /14 PE fields** | Byte-identical compiled CODE, **108/115** nonrelocation original bytes |
| Ten named owning value, pointer-to-pointer, register, volatile and direct/reference-alias variants | **10 × 177 B /53 x86 /14 source COFF fields** | Original whole length wrong; extra genuine copy-lifetime instructions |
| Pointer-to-pointer plus named used value | **183 B /55 x86** | Original whole length/frame wrong |
| Real resource pointer plus truly used const-reference receiver | **185 B /56 x86** | Original whole length/frame wrong |

All sixteen candidate COFF objects have the SAME semantic
call/global symbol identity and 14 original code-generation
reference categories, but **only equal-length candidates**
are compared as complete PE-native functions with original
field positions/destinations. All four original-sized cases
are validated against all 14 original native PE field
offsets, kinds, zero addends and resolved actual game targets;
none may hide a wrong stack operand as a relocation.

An important code-generation distinction is now demonstrated:
a direct cast expression to a borrowed pointer reference
generates exactly the same 171-byte source code as direct
delete, so it cannot fix the native original EBP permutation.
Actually introducing a named reference or value *does*
change compiler temp ownership, but also emits 6–14
additional CODE bytes (2–5 x86 instructions), without
matching the original 171B entire function.
There is no legitimate basis to truncate those candidates
or claim the three native temp slots were recovered.

This narrows the remaining authored small-function problem
to the original historical owner/result lifetime model,
not superficial deletion pointer type or declaration of
an independently used alias.

Targeted reproduction (this whole destructor only):

    scripts/repo-python scripts/verify-archive-real-delete-value-f854.py

All original-shaped source TUs, VC7.1 COFF/PDB,
full physical PE comparisons and experiment receipts
are stored in ignored .analysis/f854-archive-real-delete-values/.
Original Archive 171B still NONEXACT, zero new accepted
whole callable CODE. No mass cold replay.
