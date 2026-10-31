# F903 — Native mode63 29 whole-fighter source grammars, physical PE shift and false 46,755B length

Pinned Japanese TH075 v1.11 original fighter at 005214B0:
46,755 complete callable CODE B /13,230 original x86,
plus five separate afterRET jump DATA tables (901 B).
Original mode63 inside that ONE callable fighter is
417 native inner CODE B/109 x86/7 real PE call/global fields.

F903 compiles **29 actual normal VC7.1 /Od entire
fighter sources**, changing only genuinely used
mode63 C++ expressions: typed borrowed owner+0x60
signed-short member and owner+0x48 views, direct/
const/reference accessor values, real actor stage,
signed key and mode flag aliases, signed comparisons
and equivalent short-circuit predicate spellings.
There are no inert stack locals or binary/ASM patches.

**27 complete current parents** remain 46,754B/13,230
x86 and emit exactly 417B/109x86 for mode63, but
the original 6B CMP ECX,0x96 at case ordinal38
emits 5B CMP EAX,0x96, and original 5B CMP EAX,0x96
at ordinal61 emits 6B CMP EDX,0x96. All seven
original PE call/global destinations are preserved,
but native physical ordinal48's real REL32 field
at case-relative +185 is shifted to source +184.
That shifted field must never be relocation-masked
at only the source offset to invent byte equality.

The other two source grammars preserve meaningful
game logic but change actual x86 instruction forms.
One rewrites stage>0 as stage>=1, which makes the
WHOLE selected compiler parent **46,755B**, exactly
the original whole LENGTH, yet the native mode63
case becomes NONNATIVE **418B instead of 417B**,
with changed original opcode/width positions.
This is positive evidence that whole-byte-count
equality can accidentally conceal a true case error.

The other rewrites key>0 to key>=1 and generates
46,758B whole parent and 421B mode63, with
additional original instruction mnemonic mismatches.
Neither candidate is exact or improves original
mode63 physical source attribution.

The tracked verifier independently reads the original
Japanese physical PE, checks the seven original
call/global field positions and real targets in
multiple selected whole VC7.1 OBJ files, and
requires the physically shifted ordinal48
REL32 source field. All 29 true source C++ variants
are compiled as complete game functions, not cut
case snippets.

Reproduce ONLY the affected whole fighter:

    scripts/repo-python scripts/verify-scripted-fighter-mode63-typed-f903.py

C++/VC7.1 COFF/PDB, compiler logs and strict PE
receipts are in ignored .analysis/f903-fighter-63-typed-conditions/.
Original whole 46,755B fighter remains NONEXACT,
no split-case or whole callable exact CODE credit,
no all-unit cold replay.
