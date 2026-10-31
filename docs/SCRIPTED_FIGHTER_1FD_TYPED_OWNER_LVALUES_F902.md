# F902 — Fourteen complete VC7.1 owner-status C++ source alternatives for original 1FD

Original pinned Japanese TH075 v1.11 fighter 005214B0
is a 46,755B callable whole function with 13,230 native
x86 instructions and five separate packed 901B afterRET
switch DATA tables. In the current full source F901,
normal VC7.1 emits 46,754B/13,230 x86. Exactly FIVE
original instruction-width defects remain.

The original stage handler 1FD at 0052882E is
**386 native CODE B/107 x86/9 true original PE
call/data fields**. Its second owner-stage upper
bound must emit original six-byte
CMP ECX,0x95 (native ordinal99, whole ordinal8455).
Current source naturally generates five-byte
CMP EAX,0x95, preserving the other 106 original
mnemonics and native game semantics, but leaving
one complete native code byte absent.

Fourteen full normal VC7.1 /Od actual source variants
test a genuinely different hypothesis from previous
condition-ordering studies: real borrowed actor+0x2E8
owner field+0x60 may be an accessed typed signed short
member rather than an untyped char* offset.

The tested live-value sources include:
- A real typed struct with float Y+0x48 and signed
  short owner status+0x60, with both and single-branch
  owner-status reads, typed float Y and owner+0x60
  lvalues
- const signed short pointer views, const references,
  static-cast signed short values, direct owner dword
  offset and unsigned byte-pointer typed arithmetic
- A real used owner-status pointer cached for both
  comparisons inside the actual stage branch
- A real used signed-short owner field reference
  reused across both comparisons

Twelve entire parent sources remain EXACTLY
**46,754B/13,230 x86**, with native-sized
1FD source **385B/107 x86/9 PE fields** and
the same 5B wrong CMP EAX. Every one of those
twelve preserves and independently verifies ALL
NINE original physical 1FD PE field offsets,
REL32/DIR32 types, zero source addends,
actual original target addresses, and all 107
original instruction mnemonics. These still
fail complete 386B original native extent.

Two actually used local owner-pointer/reference
sources really generate additional code: entire
selected parents become **46,760B/13,231 x86**
or **46,761B/13,232 x86**. They fail original
whole-function geometry and cannot be cropped
to the original 107 instructions. The verifier
deliberately does NOT report a truncated case
match or count these as repaired 1FD.

Therefore simply recovering the actual owner
short+0x60 member layout or introducing a live
owner alias does not fix the real physical
1FD CMP ECX register-allocation phase. Future
work must continue investigating original
expression and full-switch compiler context,
not hand-authored register assignments or
false standalone case acceptance.

Reproduce ONLY the affected whole original
fighter source variants:

    scripts/repo-python scripts/verify-scripted-fighter-owner-lvalues-1fd-f902.py

All fourteen complete VC7.1 C++, OBJ/PDB,
compiler logs and original PE receipts remain
in ignored .analysis/f902-fighter-1fd-owner-lvalues/.
The whole 46,755B original fighter remains
NONEXACT. No new accepted whole callable CODE,
no all-unit cold replay.
