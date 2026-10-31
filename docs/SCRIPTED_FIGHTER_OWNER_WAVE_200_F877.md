# F877 — Original 200 six-stage owner wave and native FILD/FSUBR repair

The pinned Japanese TH075 v1.11 original fighter
at 005214B0 owns 46,755 callable game CODE B
plus five separately owned packed switch DATA
tables of 901 B. Original state200 at
00528D4D..00528FC6 is **634 complete
native inner B/177 x86/10 physical
original PE REL32 call fields**.

The selected normal C++ source performs genuine stage0
Reset/counters and returns directly to the
enclosing fighter epilogue when native
GetNativeActionAt40FA30 equals observed +0x70.
It then performs SIX separate stage0..5
borrowed-owner actions0x64 (real owner at
this+0x2E8), assigns float X to owner+0x44,
and at stage6 sets owner action0x35.

| Original stage | Signed facing multiplier | Genuine FILD stack |
| --- | ---: | --- |
| 0 | 74 | EBP-0x9C |
| 1 | 46 | EBP-0xA0 |
| 2 | 23 | EBP-0xA4 |
| 3 | 13 | EBP-0xA8 |
| 4 | -6 | EBP-0xAC |
| 5 | 26 with native reverse subtraction | EBP-0xB0 |

At stage4 the original also copies the actual
facing byte this+0x66 to the associated
owner's +0x66. Its original GPR carrier is
DL; the incomplete source may use CL but
the authentic three-byte MOV instruction
width/real field destination are verified.

## Genuine final x87 code-generation discovery

The last stage's original semantics are:
ownerX = actorX - float(signedFacing*26).

The naive C++ F32(0x44)-float(facing*26) tells
the pinned VC7.1 compiler to load actorX and
perform an integer-memory FISUB. This is NOT
the native code, even though the entire
generated inner case remains 634B/177 x86
and has the same 10 PE fields.

The meaningful, actually read borrowed
actor X lvalue from previously observed
this+0x44 instead naturally generates
the physical original instruction grammar:

    IMUL signedFacing, 26
    MOV [EBP-0xB0], scaledFacing
    FILD [EBP-0xB0]
    FSUBR [actor+0x44]
    FSTP [owner+0x44]

The tracked verifier **independently compiles
the correct and wrong full parents**, confirms
the wrong code's misleading equal case length
and genuine FISUB rather than native FSUBR,
and validates the complete actual game source.

The selected new whole normal VC7.1 parent
is **31,997 callable CODE B/8,974 x86**
(F875 31,378B/8,799 x86). All 177
original 200 mnemonic/size/position pairs,
all six genuine FILD EBP positions, and
10 physical PE call offsets
[26,66,90,133,212,291,370,449,546,625],
types, zero addends, source callee identities
and real native game destinations are correct.

The original 200 source remains **NONEXACT**:
131 true register operand byte differences
and two enclosing fighter epilogue JMP
operand pairs at case offsets +95/+96
and +630/+631 remain.

The new same whole parent physically rechecks
all 49 preceding original game case interiors
(46 earlier plus 1FD/1FE/1FF), actual typed
PE fields and honest negative registers.
Original 1FD remains one CMP byte shorter
in the compiler source (385B vs native386B);
1FE remains complete 392B source geometry.
All five original 901B packed afterRET
tables are reverified. Common 46B getter
still contains four GPR negatives at
10/12/16/19 and three correct original
PE call target fields.

Reproduce only this affected giant:

    scripts/repo-python scripts/verify-scripted-fighter-owner-wave-200-f877.py

Current full C++, VC7.1 OBJ/PDB, positive
and negative original float-source controls
and native physical PE receipts live in
ignored .analysis/f877-scripted-owner-wave200/.
The original 46,755B whole giant is still
NONEXACT, no split-case callable exact
CODE credit, no mass cold replay.
