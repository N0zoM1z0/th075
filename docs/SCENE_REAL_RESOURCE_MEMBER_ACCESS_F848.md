# F848 — Scene destructor: real resource-member access and VC7.1 forced-inline negatives

The SHA-pinned original Japanese TH075 1.11 Scene virtual
destructor at 0043B0B0 has **248 complete original
CODE B /75 x86 /12 physical PE/COFF fields**.
The real original temporary stack roles are
texture EBP-0x14, scalar delete receiver EBP-0x10,
and three CRT free arguments EBP-0x18/-0x1C/-0x20.
The current normal cleanup aggregate emits
texture/delete EBP-0x20/-0x1C and free arguments
EBP-0x18/-0x14/-0x10, leaving nine genuine
native nonrelocation operand byte mismatches.

F848 compiles ten complete normal pinned VC7.1
/Od /Ob0 /Gy /GR- /GX /GS /Zi
destructor C++ alternatives using the original
three *actually freed* source pointers, normal
conditional texture scalar delete, exception
frame and original base virtual destructor.
It tests both natural aggregate field access
and named member helper methods (which really
read/write the actual freed values), without
adding dummy locals or changing the original
call side effects.

| Actual real-value source model | Full compiled Scene | Physical native result |
| --- | --- | --- |
| Baseline; register or volatile cleanup aggregate; through aggregate address; C++ pointer-to-member | 5 × **248B/75 x86/12 PE fields** | All still **191/200** native nonrelocation bytes |
| One or three actual named setter/getter methods marked __forceinline | **253/254/263/266/281B**, 76/77/78/81/84 x86, 13–18 source COFF fields | Wrong entire original extent; helper calls remain under /Ob0 |

All five equal-size candidates are independently compared
against the *entire* native 248B executable function,
including all **12 original physical PE/COFF field
offsets, kinds, zero addends and actual target
destinations**, original exception-handling geometry
and all five native stack operands.
All emit the same nine non-PE EBP-byte differences.

Important toolchain observation: in this pinned
normal /Ob0 build, declaring a genuine access
helper __forceinline does **not** make its
callsites match the original direct pointer access.
The source compiler generates additional actual
member calls and linked COFF records, with
an incorrect original whole-function length.
No 253–281B source candidate is cropped or
byte-masked into a false 248B exact result.

These full original-target experiments rule out
trivial volatile/register qualifiers, equivalent
C++ member-pointer syntax and straightforward
accessor function refactoring as explanations
for the native reversed five-temporary allocation.
The original historical object/value lifetime is
still unknown and the authored destructor NONEXACT.

Selected local reproduction (only the Scene unit):

    scripts/repo-python scripts/verify-scene-actual-access-f848.py

Generated source, VC7.1 compiler COFF/PDB,
target PE checks and original byte receipts
are preserved in ignored
.analysis/f848-scene-real-owner-access/.
No accepted independently callable exact CODE
and no all-unit cold replay.
