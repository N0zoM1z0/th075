# F688 — genuine original SDK derived destructor EH source, nonexact controls

Pinned user-supplied Japanese TH075 version 1.11 `resources/th075.exe`,
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is a **targeted negative** native whole-function reconstruction
study, not a new accepted exact function, and original
`0061A453` still has unknown historical source attribution.

## Actual complete original PE program and EH ownership

The true registered `0061A453` complete original is **73 whole CODE
bytes /23 authentic x86 instructions**, with actual MSVC EH frame
prologue `MOV EAX,0x00656B2C; CALL 006425A4`. It saves the native
receiver in ESI and at original local `EBP−0x10`, sets the real
original vtable `0065DACC`, and initializes original EH cleanup
state at `EBP−4`. It calls actual resource cleanup `00619172`,
checks pointer at `this+0x106C`, conditionally calls true CRT free
`00640F15`, then sets the EH cleanup state to `−1`, calls the
**independently completely reconstructed 19-byte base native
virtual destructor `0061535A`** (F686), restores `FS:[0]` from
original `EBP−0xC`, and returns through the authentic `LEAVE; RET`.
The SEH frame, vtable and physical original call fields cannot be
cropped or excluded to claim a short exact function.

## Real pinned VC7.1 normal C++ compiler source experiments

The original target's likely C++ semantics were tested with a
minimal virtual derived class inheriting a nontrivial virtual
base destructor, genuinely performing the observed `00619172`
cleanup, conditional `free` at member `+0x106C`, and implicit
base destructor. Both original-like base/derived class names are
provisional; the source does **not** invent 0x106C bytes of actual
struct padding. Its raw member pointer offset is a native PE
observation.

| Selected ordinary C++ source grammar, genuinely cold compiled | VC7.1 flags | Generated complete CODE /x86 | Result against original 73/23 |
| --- | --- | --- | --- |
| Ordinary derived virtual destructor with meaningful cleanup/free/base destructor | `/O1 /GX` or `/O1 /GX-` | **39 B/13 x86** | **NONEXACT**: no required original EH prologue; base destructor is a tailcall |
| Same original semantic destructor | `/O2 /GX` | **41 B/13 x86** | **NONEXACT**: wrong resource stack cleanup, no original EH |
| Same semantic destructor | `/Od /GX` | **65 B/21 x86** | **NONEXACT**: different ordinary EBP prologue, no original EH |
| Destructor **function-try-block**, implicit or explicit catch/rethrow, and typed catch | `/O1 /GX` and `/O1 /EHsc` | **83 B/30 x86** (each) | **NONEXACT**: real EH prologue appears but distinct EBX/EDI/ESI ownership and catch-state code |
| Ordinary destructor with meaningful **body-level try/catch** | `/O1 /GX` and `/O1 /EHsc` | **69 B/22 x86** | **NONEXACT**: real EH prologue appears but has extra `PUSH ECX`, wrong EBP-this ownership/cleanup state |

The initial set covers **four profiles** of one genuinely inherited
resource lifetime source; a second controlled set contains **eight
further whole-function C++ function-try-block/exception-mode
experiments**. The user-supplied PE original is still **73 B/23
x86**: neither the 39/41/65 ordinary forms nor the 69/83 EH
forms match its full native function. In particular, source-level
C++ `try` statements alone cannot be taken as proof of the
specific historical MSVC EH state-owner and constructor/destructor
lifetime layout.

All complete C++ sources, original/native instruction comparisons,
compiler logs, COFF/PDB outputs and actual negative receipts are
preserved under ignored `.analysis/f688-eh-derived-dtor/`.
No original game EXE modification, fake filler local, manual
machine-code graft or whole 943-unit cold replay was performed.
No new accepted game-authored whole-function CODE bytes, nor any
new source-UNKNOWN complete exact match, is claimed. Original
provenance candidates remain **95 unknown**; the separate accepted
authored ledger remains **943 functions /862,726 CODE bytes**.

The next useful investigation is the actual original **MSVC EH
unwind table at `00656B2C`**, the specific base-subobject state
lifetime, and the original `EBP−0x10` saved derived receiver.
Those real native owners must be explained by meaningful C++ source
rather than arbitrary exception-handler declarations or inserted
padding before accepting the entire 73-byte original.
