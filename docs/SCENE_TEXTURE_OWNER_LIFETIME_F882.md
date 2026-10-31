# F882 — Real Scene texture-owner declaration exposes a native stack-slot tradeoff

The independently authored SHA-pinned Japanese TH075 v1.11
Scene virtual destructor at 0043B0B0 is **248 complete callable
original CODE B, 75 native x86, 12 actual physical PE fields**.

Original machine stack slots are:

| Actual native intermediate | Original EBP |
| --- | --- |
| Observed texture pointer from this+8 | -0x14 |
| Deleting texture receiver | -0x10 |
| CRT free argument from this+0x4C | -0x18 |
| CRT free argument from this+0x50 | -0x1C |
| CRT free argument from this+0x54 | -0x20 |

Prior three-field cleanup aggregate source naturally matches
all 75 x86 opcode/width positions and all 12 authentic native
PE field offsets/types/destinations. It still differs at
nine true nonrelocation stack operand bytes, with only
**191/200 real comparable original bytes equal**:
the scalar texture/delete receiver stack slots get
EBP -0x20/-0x1C and the actual resource frees get
-0x18/-0x14/-0x10.

## Seventeen complete normal VC7.1 source controls

Rather than merely changing the pointer names, F882
reconstructs the actually used texture pointer value
as a genuine local object, const/volatile/register
texture owner, reference to original texture member,
pointer to original texture member, or a member of
one actual four-field cleanup aggregate together
with all THREE genuinely freed resource pointers.

All seventeen complete virtual destructor sources
retain the native game clock conditional, real texture
scalar deletion, three independent conditional CRT
free operations and base destructor call, and use pinned
normal VC7.1 /Od /GX compilation. No fake or inert
locals, target edits, naked assembly or manual
register forcing are used.

| Source model | Complete emitted source CODE | Original native comparison |
| --- | --- | --- |
| Baseline and direct typed texture lvalue | **248B/75 x86/12 fields** | **191/200** native nonrelocation bytes; same nine true EBP negatives |
| Three genuinely initialized early texture locals | **251B/76 x86/12 fields** | Entire native length wrong |
| Ten scoped or four-field actual texture-owner models | **254B/77 x86/12 fields** | Entire native length wrong |
| Two genuine texture-reference/member-pointer models | **256B/78 x86/12 fields** | Entire native length wrong |

**A meaningful partial compiler breakthrough:** the complete
four-field cleanup aggregate with texture declared as its
second-to-last member naturally moves the original
texture-value store at x86 ordinal26 to **EBP-0x14**,
matching one required original physical native stack slot.
But the same normal source also emits additional actual
MOV/store instructions before scalar deletion, changes
the real delete receiver to **EBP-0x24** instead of -0x10
and extends the whole source to **254B/77 x86**.

Its original first six physical PE fields still occur at
[6,12,20,35,49,70], but the final six original fields at
[113,152,182,212,230,240] move in the generated source
to [119,158,188,218,236,246]. They are offset by SIX
full real executable bytes, not a permitted relocation
mask. Matching one isolated EBP slot cannot earn exact
whole-function credit.

The only two actual **248B/75-x86** variants are compared
byte-for-byte over all original CODE after masking ONLY
the 12 real original physical PE field bytes (already
independently checked for offset/type/target). Both are
still **191/200** native, with the same nine real stack
operand errors [94,97,100,103,111,176,179,206,209].
The independently authored 248B destructor remains NONEXACT.

Reproduce only this original small whole function:

    scripts/repo-python scripts/verify-scene-texture-ownership-f882.py

All 17 complete C++, VC7.1 OBJ/PDB, compiler logs
and original physical PE receipts remain in ignored
.analysis/f882-scene-texture-ownership/.
No original exact CODE added, no mass cold replay.
