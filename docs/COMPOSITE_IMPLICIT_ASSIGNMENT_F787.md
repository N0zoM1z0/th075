# F787 — Complete native 0045AAE0 composite assignment source evidence

**Exact machine-code reconstruction for a provenance-unknown candidate,
not a formally accepted authored game function.** The original
user-supplied Japanese v1.11 TH075 PE has a complete 368-byte /
118-instruction original method at `0045AAE0..0045AC4F`.
The original `config/function-origins.csv` independently labels its
ownership **unknown**. Its three native callers include
compiler/STL vector copy machinery, but a matching generated source
does not resolve whether the historical method was explicitly authored.

Fresh VC7.1 C++ source `probes/CompositeImplicitAssignmentF787.cpp`
defines a provisional 116-byte composite with two genuine 16-byte POD
blocks at offsets `0x00` and `0x44`, individually observed scalar
fields between them, and two borrowed 16-byte nested sequence owners
at `+0x54` and `+0x64`. A natural, compiler-*implicit*
`CompositeValueF787::operator=` emits the original complete
**368-byte / 118-x86** COMDAT with no hand-written target instructions.
The targeted checker verifies the *actual* independent COFF section
extent (not a truncated comparison!), **all 360 of 360
non-relocation native bytes** and both physical four-byte REL32
fields at offsets `0x151` and `0x163`.
They each resolve from the original PE to `0x0045AC50`,
already independently classified as library-owned
`std::vector::operator=`. No helper CODE is credited again.

The first 16-byte block restores a native four-DWORD grouped copy;
the second block restores a distinct 16-byte grouped copy at
`+0x44`. Treating those fields as 4 or 6 independent scalar
members previously emitted 382–400 B, which was **not** an exact
original function. Grouping both observed regions naturally
restores the full 368 bytes. Historical class spelling, authored
versus compiler-implicit provenance, and the complete private
nested sequence types remain unresolved.

Reproduce one source compile and *complete* original PE/COFF review:

```bash
scripts/repo-python scripts/verify-composite-implicit-assignment-f787.py
```

No `matches.csv`, `implemented.csv`, origin, or full-unit ledger
changes are made. **Official authored CODE coverage is unchanged**.
The generated source, COFF and diagnostic are retained in the
local research directory. The adjacent 417-B copy constructor
receives independent follow-up.
