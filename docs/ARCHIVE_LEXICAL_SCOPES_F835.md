# F835 — Real lexical deletion/free scopes do not restore the original Archive stack

The SHA-256-pinned Japanese TH075 1.11 original authored
nonvirtual ArchiveCatalog destructor at 0041CE50 owns
**171 callable CODE B /51 x86 /14 physical PE/COFF
fields**. Its native compiler stack has index EBP-4,
resource EBP-0xC, delete receiver EBP-8, filename EBP-0x10
and saved this EBP-0x14. Existing ordinary source has
resource/delete/filename EBP-0x10/-0xC/-8, so only
**108/115 original comparable nonrelocation bytes**
are equal despite all native call/global PE fields matching.

F835 compiles **15 complete, meaningful pinned VC7.1 /Od
/GX- C++ source variants**, changing only lexical scopes
of actual resource deletion and name release: shared/nested
braces, split delete/free blocks, genuine filename declaration
before delete or before the loop, and a genuinely used
const-reference to the released filename. No fake local
padding, arbitrary ABI changes, target byte edits or
partial-function truncation.

| Genuine original-source scope experiment | Full compiler CODE | Original PE nonfield result |
| --- | --- | --- |
| 13 distinct nested/adjacent scope or declaration variants | **171 B /51 x86**, byte-identical compiler CODE and all 14 source COFF fields | **108/115** |
| Real filename declared before loop | **171 B /51 x86** | **102/115** (index and filename stack slots swap, worse) |
| Actual used const-reference alias for filename | **179 B /54 x86** | Wrong complete original extent, not byte-comparable |

The tracked verifier independently reads the original pinned
171B game function and checks its actual six native
prologue/stack operand roles. Every correctly sized
source is compared as a **whole function** using the
native PE/COFF comparator, including **all 14 true
physical original relocation field positions, kinds,
zero addends and resolved actual game targets**.
It also checks that 13 variants generate byte-identical
complete source CODE and COFF relocation records,
not merely equivalent reported counts.

The real reference-alias variant correctly uses the
original filename value, but generates three additional
x86 instructions and a nonnative full frame. None of
these source-only candidates can be adopted.

These results rule out a trivial brace/lexical declaration
scope explanation for original pointer-owner EBP
allocation. The remaining task requires an evidence-
supported original resource/delete receiver value
category, not a fabricated local.

Reproduce ONLY this affected original whole destructor:

    scripts/repo-python scripts/verify-archive-lexical-scopes-f835.py

Source variants, VC7.1 COFF/PDB, compiler logs and original
physical PE proof receipts are retained in ignored
.analysis/f835-archive-lexical-scope/.
**Original 171B authored destructor still NONEXACT;
zero new independently accepted whole CODE, no mass cold replay.**
