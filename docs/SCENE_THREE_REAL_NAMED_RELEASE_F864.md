# F864 — Full original Scene destructor with three actually used named resource pointers

The SHA-pinned Japanese TH075 1.11 Scene virtual destructor
at 0043B0B0 is **248 entire original CODE B/75 x86/
12 physically typed original PE fields**. Native
texture/deleting receiver use EBP-0x14/-0x10 and
the three real CRT-free argument temps use EBP
-0x18/-0x1C/-0x20. The present natural aggregate
source is only **191/200** original nonrelocation
bytes, with nine genuine EBP operand differences.

F864 tests **twelve complete normal pinned VC7.1
/Od /GX Scene destructors** using actual freed
scene members (+0x4C/+0x50/+0x54), preserving
their real resource free side effects, texture
scalar delete, exception frame, and base destructor.
Rather than renaming/relocating a three-field
aggregate, nine candidates use **three separate,
genuinely assigned and freed pointer locals**:
declarations before clock, before texture,
after texture, reverse/rotated names, register/
volatile storage, and local declarations with
true branch-specific initializers. Two further
variants use actual borrowed pointer references
or pointers to the freed original scene members.
No dummy stack padding or source byte patching.

Every original-sized candidate is checked against
all **248 original executable bytes, 75 native
x86 mnemonic/width pairs and 12 original physical
PE/COFF locations, kinds, zero addends and actual
resolved native call/global targets**.

| Real source design | Complete normal VC7.1 output | Real original native comparison |
| --- | --- | --- |
| Baseline three-field aggregate | **248B/75 x86/12 PE refs** | **191/200** original nonrelocation bytes |
| Nine true independent named pointer sources | **248B/75 x86/12 PE refs** each | **189/200**, 11 wrong real stack operand bytes |
| Actual branch pointer-reference/member-pointer aliases | **254B/78 x86/12 PE refs** each | Whole original CODE extent and x86 geometry wrong |

Crucially the true named local declaration order does
NOT reproduce the original texture/delete EBP-0x14/-0x10
slots: the compiler still places them at -0x20/-0x1C.
Although the three released resource temp slots now
differ from the aggregate source, they do not jointly
match original PE. Genuine C++ branch references/
member-address pointers add source instruction
lifetime and grow the entire destructor, so those
cannot be cropped into exact matches either.

This falsifies a plausible historical source-owner
hypothesis using full ORIGINAL game PE rather than
assuming older handoff documents are authoritative.
The independently callable authored Scene remains
NONEXACT. No 248B byte-match or authored exact
CODE credit is claimed.

Reproduce only the affected complete Scene function:

    scripts/repo-python scripts/verify-scene-three-named-release-f864.py

All twelve generated C++, VC7.1 OBJ/PDB,
full PE comparisons and strict JSON receipt
are under ignored
.analysis/f864-scene-named-release-slots/.
No mass cold replay.
