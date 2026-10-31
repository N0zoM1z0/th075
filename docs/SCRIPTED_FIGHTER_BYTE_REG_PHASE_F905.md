# F905 — 54 complete native 252/254 real byte-decrement source models

Original pinned Japanese TH075 v1.11 whole fighter 005214B0:
46,755 native callable CODE B /13,230 x86,
and five separate postRET jump DATA tables (901B).

Original physical states 252,253,254 are respectively
**260/260/224 B, 72/72/63 x86, 6 actual PE fields each**.
Their actual native 8-bit decrement is a three-stage
register-allocation phase:
- 252: SUB DL,1 (3-byte instruction)
- 253: SUB CL,1 (3-byte instruction)
- 254: SUB AL,1 (2-byte instruction)

The current normal near-complete father emits
SUB AL/DL/CL, or **259/260/225 B**. These case
sizes sum to the SAME 744B as the three original
states, but real source 252 has SIX PE operand fields
one byte EARLIER than native, and 254 has SIX fields
one byte LATER. The aggregate width is not exact.

F905 builds **54 full, naturally generated normal
VC7.1 /Od fighter C++ variants**, changing only
real stage0 byte+366 decrement, truly used member
lvalue/reference, or the actual stage/action conditions.
This includes unsigned/signed prefix and postfix
operators, typed actor byte struct members, direct
borrowed pointer/index access, real used byte references,
compound subtraction, and equivalent original
C++ short-circuit condition spellings for 252/254
individually and together. No fake locals or register
patches are introduced.

Forty-six variants retain the original entire father
x86 count of 13,230, but **none recovers the native
SUB DL in 252 and SUB AL in 254**. Forty-three
retain 259/260/225-B natural case geometry; other
valid C++ forms change opcode grammar or case
width without restoring original actual case boundaries.
Four variants coincidentally emit a 46,755B
whole father but still have incorrect original
GPR operands and/or extra x86 instructions. They
are not whole-function exact.

The original PE is reread independently. For the
three selected baseline case sections the verifier
resolves all **18 original call/global field targets**,
types, zero COFF addends and the exact physical
difference between original and source field offsets,
including six -1B and six +1B relocated case fields.
Every complete full source variant keeps the normal
901B postRET tables, and any source with additional
real x86 is reported as a different COMPLETE parent
rather than being cropped to 72/63 instructions.

The real problem is full switch register-allocation
context, not an untested signedness of the decrement.

Reproduce only the affected full game father:

    scripts/repo-python scripts/verify-scripted-fighter-byte-decrement-f905.py

All 54 complete normal C++/VC7.1 OBJ/PDB and
original PE receipts remain in ignored
.analysis/f905-fighter-byte-decrement/.
Original 46,755B callable giant is NONEXACT;
no individual switch case exact CODE credit,
no all-unit cold replay.
