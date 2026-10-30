# F838 — Original Scene destructor declaration placement and release field order

Pinned Japanese TH075 1.11 original virtual Scene destructor
0043B0B0 is **248 callable CODE B /75 x86 /12 actual PE/COFF
fields**. Original five temp slots are texture/delete
EBP-0x14/-0x10, and the three truly released resource
pointers EBP-0x18/-0x1C/-0x20. Earlier natural cleanup
aggregate C++ emitted all native opcode/width/PE
symbols but only **191/200 original nonrelocation
bytes** because texture/delete occupied EBP-0x20/-0x1C.

F838 tests eight complete, behavior-preserving pinned
VC7.1 /GX normal C++ source variants, varying:
the real three-pointer cleanup value aggregate's
declaration before the clock, texture deletion,
or even the function's first statement, its
actual release inner scope, and three meaningful
permutations of real resource member declaration
order. All source still conditionally deletes
the original texture and frees actual three
resource values, in the same game call order.
No inert local, incorrect ABI, target patch or
assembly was used.

| Genuine source declaration experiment | Full generated original-shaped source | Physical original CODE |
| --- | --- | --- |
| Baseline and four earlier declaration/inner scope placements | **248B/75-x86/12 PE fields** | **191/200** original nonrelocation bytes |
| Three permutations of actual released-pointer member fields | **248B/75-x86/12 PE fields** | **189/200**, worse |

For all eight full source objects, the verifier checks the
actual 248 native bytes, all 75 x86 instruction mnemonics
and exact instruction widths, plus **all twelve original
PE field offsets, relocation types, zero addends and native
target destinations**. It compares the remaining original
200 nonrelocation byte positions without masking any
GPR/stack bytes.

No candidate recovers the original shallow texture/delete
slots. Its three freed-pointer member roles can move
with true member declaration order, but none gives
the original texture/delete and all three freed slots
simultaneously. Therefore moving the actual
aggregate declaration earlier does not explain the
original five-slot allocation order.

Targeted reproduction only:

    scripts/repo-python scripts/verify-scene-release-declaration-f838.py

Complete sources, pinned VC7.1 COFF/PDB and original
PE comparison evidence reside in ignored
.analysis/f838-scene-declaration-placement/.
Original 248B Scene remains NONEXACT, zero accepted
authored whole CODE and no mass cold replay.
