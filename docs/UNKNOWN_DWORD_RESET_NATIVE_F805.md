# F805 — Complete native zero-store leaf 00454C00, historical owner UNKNOWN

**New complete source-generated original machine-code match;
not a proven historical authored game function.**

The user-supplied Japanese TH075 1.11 original PE has
a previously unclassified entire function
`00454C00..00454C17`, **24 complete native CODE B,
nine x86**, no physical PE/COFF relocation fields.
Original machine instructions save thiscall `ECX` at
`EBP-4`, reload it into `EAX`, and execute
`MOV DWORD PTR [EAX+0x47C],0` before `RET`.
Thus both the actual write width and target offset
are independently physically observed.

Fresh normal pinned VC7.1 compilation from
`probes/UnknownNativeDwordResetF805.cpp`
emits the **entire original 24/24 machine CODE B,
9/9 x86** with no relocation waiver. The borrowed
source view has only the true offset `+0x47C`;
it is **not** an instantiated/embedded historical
owner and does not claim the original class identity.

F805 separately compiles five *complete*
source-method alternatives using real dword/word/byte
data types. These source variants demonstrate
that byte equality does **not** establish
the nominal original field type:

| Natural C++ member/source | Whole source CODE | Original equality |
| --- | ---: | --- |
| `unsigned int statusAt47C = 0` | 24 B /9 x86 | **Full exact codegen** |
| `int statusAt47C = 0` | 24 B /9 x86 | **Full exact codegen** |
| `float statusAt47C = 0.0f` | 24 B /9 x86 | **Full exact codegen** |
| `short statusAt47C = 0` | 23 B /9 x86 | Not original |
| `unsigned char statusAt47C = 0` | 21 B /9 x86 | Not original |

The target PE supports a **32-bit zero assignment**,
but unsigned, signed or IEEE-754 float nominal
interpretations cannot be distinguished from this
code alone. Ghidra's original `xrefs_to` report
contains no direct target references, which
is not proof that no indirect/vtable caller exists.
The neighboring address `00454C20` belongs
to a separately independently authored game
function, but physical adjacency itself
does not establish the owner/provenance of
`00454C00`.

```bash
scripts/repo-python scripts/verify-unknown-native-dword-reset-f805.py
```

The tracked verifier independently verifies the original
function's `unknown/review` entry, complete native
CODE/x86 and zero original COFF relocations, and
cold-compiles all five selected whole method
source types. Generated research objects and
summary are retained in ignored
`.analysis/f805-native-borrowed-reset/`.
The original origin stays **unknown**:
no canonical authored exact unit or bytes credited,
no original PE patch, no all-unit cold replay.
