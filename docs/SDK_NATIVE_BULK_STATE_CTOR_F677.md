# F677 — exact entire original 104-byte optimized native bulk-state constructor

Pinned user-supplied Japanese TH075 v1.11 `resources/th075.exe` SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The registered original native function is `0060B728`–`0060B790`:
**104 entire original machine CODE bytes /34 original x86
instructions**. Its historical SDK or author-written C++ owner
remains **UNKNOWN**. The following is a complete, independently
compiled, PE-linked machine-byte identity, not source-authorship
attribution or an accepted authored match unit.

## Original whole native semantic program

The real original PE entry receives `this` in ECX, saves ESI and
EDI, sets one original vftable pointer at `0065D3C0`, stores
`+4=1`, initializes the observed native state fields
`+8,+0x20,+0x24,+0x28,+0x2C,+0x34,+0x30=0`, and executes a genuine
**two-trip pair-of-members loop**: `LEA EAX,[this+0x40]`,
`MOV [EAX−8],ESI`, `MOV [EAX],ESI`, `ADD EAX,4`, `DEC ECX`, `JNE`.
It then performs authentic compiler-optimized **bulk zeroing**:
`XOR EAX,EAX`, `MOV ECX,0x104`, `LEA EDI,[this+0x50]`,
`REP STOSD`. That represents the exact original **260 DWORD /
1,040-byte (`0x410`) zeroing region at `+0x50..+0x460`**.
It next initializes the observed tail state offsets
`+0x460,+0x470,+0x48C,+0x490,+0x468`, restores EDI/ESI,
returns `this` through EAX, and terminates with a native `RET`.
No artificial object-size padding or invented stack locals is needed.

The normal C++ source
[`SDKNativeBulkStateCtorF677.cpp`](../probes/SDKNativeBulkStateCtorF677.cpp)
expresses only these actual native member offsets, the genuine
2-element loop and a standard `memset(this+0x50,0,0x410)`.
**Fresh pinned MSVC VC7.1 `/O1 /Oi /Ob0 /Gy /GR- /GX- /GS /Zi`**
reproduces **all 34 original x86 instructions and 104 complete CODE
bytes**, with exactly **one** genuine source COFF zero-addend
`DIR32` field at function offset `+10` to compiler-generated
`??_7SDKProbeE@@6B@`. Transiently linking only that physical
compiler field to the independently read true PE vftable
`0065D3C0` makes **all 104/104 original machine CODE bytes
identical**, including the original loop, `REP STOSD`, and epilogue.
The original executable is never patched.

## Why this exact source grammar, not an arbitrary fill

F677 independently compiled **15 combinations** of five meaningful
normal C++ array/zeroing grammars and `/O1`, `/O2` and `/O1 /Oi`
profiles, retaining all source, compiler logs and diagnostic COFFs
under ignored `.analysis/f677-native-sdk-state/`. Only the
**two-element source loop plus actual full 0x410-byte `memset`,
compiled with `/O1 /Oi`**, gave exactly original 104 bytes and
34 original x86 roles. A plain two-element loop and 0x104-element
C++ loop produced 104 B/34 x86 under `/O1`, but still differed in
original native compiler operand roles; `/O2` and other variants
changed the native original loop and/or bulk clearing geometry.
No fake unused variables, arbitrary struct padding, hand-coded x86,
or original machine displacement copying was used to force equality.
The provisional SDK C++ class name/virtual declaration is only the
minimum source grammar for the genuine original vftable field,
not evidence for the historical complete object layout or owner.

[`verify-sdk-native-bulk-state-ctor-f677.py`](../scripts/verify-sdk-native-bulk-state-ctor-f677.py)
compiles only this small source TU, requires the complete original
registered PE function boundary and all 34 original x86 roles,
the exact original 2-trip source zeroing loop, original ECX count
`0x104` and `REP STOSD`, the physical original `DIR32` type,
compiler source vftable symbol and zero addend, and **all 104
linked original machine bytes**. Independently scanning all 4,351
registered original native CODE functions gives one actual direct
caller from the currently `library`-classified original
`00605107`, native `CALL 0060B728` at `00605139`.
That classification does not prove this function's historical
source owner or exclude other indirect callers.

Every source-origin candidate classification remains unchanged:
**95 original provenance-unknown** functions still require
attribution. F595–F675 previously had **75 distinct original whole
source-backed origin-unknown functions /1,405 native CODE bytes**;
F677 raises the fully uncredited source evidence to **76 complete
original functions /1,509 original CODE bytes**, with **zero
new authored acceptance**. Official whole-authored exact coverage
remains **943 whole functions /862,726 original CODE bytes
(43.71% reviewed)**. The giant fighter's separate F676 case-interior
source progress remains uncredited as well.

```bash
scripts/repo-python scripts/verify-sdk-native-bulk-state-ctor-f677.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Actual new VC7.1 optimized OBJ/PDB, compiler log, native PE direct
caller graph, original PE-vftable whole-byte receipt and source hash
are preserved under ignored `.analysis/f677-native-sdk-bulk-ctor/`.
No 943-unit full cold replay, artificial padding, original EXE patch
or external Oracle whole-function acceptance was performed.
