# F788 — Complete original implicit composite copy construction and EH states

**Whole original codegen matched without resolving authorship.**
The original Japanese TH075 v1.11 source candidate
`004591E0..00459380` is a complete 417-byte /128-x86
instance copy constructor with six authentic PE/COFF fields.
Its independently reviewed `config/function-origins.csv` record
remains **unknown**. Neither a matching generated copy
constructor nor a typical STL caller establishes whether the
original program explicitly defined equivalent copy semantics.

## Recover the actual object-lifetime difference, not filler

F787 discovered the exact original 368-B copy-assignment at
`0045AAE0` using a natural 116B composite with two 16B
grouped POD sections (`0x00..0x0F` and `0x44..0x53`),
distinct primitive members and two physically borrowed 16B
nested sequence owners (`+0x54` and `+0x64`).

For copy *construction*, that initial C++ source emitted
**413B/127 x86**, not the original 417B/128 x86.
Independent original PE comparison identified one more actual
EH state transition at function-relative `+0x38`
(`MOV DWORD PTR [EBP-4],0`) immediately after copying the
first grouped 16B header. A second authentic VC7 state
transition at `+0x171` is byte-sized
(`MOV BYTE PTR [EBP-4],1`) after constructing the first
nested 16B owner; the successful second nested construction
returns the EH state to `-1` before epilogue.

The real source-level explanation is a **nontrivial destructor**
for the observed initial 16B composite header; the generated
implicit member copy remains a natural grouped 16B copy. One
declaration `~NativeCopyHeaderF787();`, without an artificial
constructor call, arbitrary slot or inline assembly, changes
the compiler-generated copy from 413B/127 x86 to the complete
**417B/128 x86** native function. Its original PE EH-handler
thunk at `0x00656273` follows the actual 10B
VC7 `MOV EAX,handlerData; JMP __CxxFrameHandler` pattern.

The companion source generated assignment **remains** complete
368B/118 x86, demonstrating that the genuine nontrivial
destructor affects copy-**construction** EH state, not the
memberwise assignment code.

## Full original relocation checks, no cropped comparisons

`scripts/verify-composite-implicit-constructor-f788.py`
freshly compiles **one affected ordinary VC7.1 C++ source** and
independently checks full actual COFF COMDAT section sizes,
all ordered original x86 instructions, all nonrelocation
machine bytes and every real PE relocation.

| Original function | Original/source native CODE | Nonrelocation bytes | Original PE fields |
| --- | --- | --- | --- |
| `004591E0` constructor | **417/417 B**, 128 x86 | **393/393** | 6 |
| `0045AAE0` assignment | **368/368 B**, 118 x86 | **360/360** | 2 |

Constructor relocations: `DIR32+0x06` native EH handler
`00656273`; `DIR32+0x0C/+0x14/+0x197` original FS
exception-list zero; `REL32+0x16D/+0x183` both resolve
to the independently identified library sequence copy
constructor `00459390`.
Assignment relocations: `REL32+0x151/+0x163`, both resolve
to the independently identified library sequence assignment
`0045AC50`. All fields have compiler addend zero.
No after-RET DATA is silently credited.

```bash
scripts/repo-python scripts/verify-composite-implicit-constructor-f788.py
scripts/repo-python scripts/verify-composite-implicit-assignment-f787.py
```

**The two original candidate origins remain UNKNOWN.** Strong
implicit-codegen evidence is not independent historical proof
that neither method was explicitly written in user C++. No
formal authored exact-unit credit, no change to
`config/function-origins.csv`, no all-979-unit cold replay,
no original target patching. The tracked source and verifier
regenerate both results; ignored compiled evidence and
summary are at `.analysis/f788-composite-implicit-ctor/`.
