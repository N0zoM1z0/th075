# F616 — three complete original 88-byte constructor CODE bodies from natural C++

**Original pinned Japanese TH075 1.11 PE and newly compiled MSVC VC7.1
whole-function byte identity. Provenance UNKNOWN; no new authored exact
credit.** Executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Independent native PE function and typed destination evidence

| Complete original game-code function | Native whole CODE | Original x86 | Actual physical original typed relocations |
| --- | ---: | ---: | --- |
| `004251C0`, provisional polymorphic scene-with-member ctor | **34 B** | 13 | `DIR32` at `+0xC` to actual native vtable `00657B88`, `REL32` at `+0x17` to genuine member ctor `00417210` |
| `00458670`, provisional auxiliary base ctor | **23 B** | 10 | `DIR32` at `+0xC` to actual native vtable `0065904C` |
| `00458650`, provisional auxiliary derived ctor | **31 B** | 12 | `REL32` at `+0xB` to real native base ctor `00458670`, `DIR32` at `+0x14` to actual derived vtable `00659038` |
| **Three entire real functions** | **88 B** | **35** | **5 authentic original physical fields** |

These are the native **complete registered function boundaries**, not
an extracted interior switch branch or a shortened RET. At each
machine-code operand above, the verifier checks both the actual native
absolute DWORD or REL32 destination arithmetic and the generated
source COFF symbol/type/zero addend. After genuinely resolving those
five COFF fields to original addresses, both selected source families
are **88/88 linked actual original machine-code bytes identical**,
with every one of the 35 original instruction starts, sizes, mnemonics
and operand encodings reproduced. Original vtable pointer addresses
are genuine native PE observations; **the complete original vtable
contents and complete historical class layouts have not been proven**.

## Both genuine explicit and compiler-generated default constructors match

The real C++ alternative
[`NativeGameConstructorsF616.cpp`](../probes/NativeGameConstructorsF616.cpp)
defines three ordinary explicit empty constructor bodies. A separate
natural C++ source
[`NativeGameConstructorsImplicitF616.cpp`](../probes/NativeGameConstructorsImplicitF616.cpp)
has **no explicit constructor declarations/definitions** for the three
owning game objects: ordinary placement-new invocations cause the
pinned VC7.1 compiler to emit their actual implicit default special
members. Both source TUs use real virtual destructors, a genuinely
nontrivially constructed member at `this+4`, and a derived object
with its real nontrivial polymorphic base constructor. These are
meaningful C++ object/lifetime layouts, not forced registers, fake
locals or native byte grafts.

The two entirely separate ordinary MSVC VC7.1 `/Od /Ob0 /Gy /GR-
/GX- /GS /Zi` compiler outputs both reproduce **all three complete
original functions, in every machine-code byte after actual original
relocation resolution**. One implicit generated special-member COFF
symbol may omit a function-size auxiliary record. The verifier
requires the **complete original native function extent** in that
case rather than truncating to a convenient prefix or omitting
its relocation records.

## Original native call graph and the provenance limit

[`verify-native-game-constructors-f616.py`](../scripts/verify-native-game-constructors-f616.py)
independently decodes genuine direct CALL instructions from all
**4,351 registered original native function extents**:

- Scene ctor `004251C0`: **15 real direct calls from 15 currently
  authored game scene initializers**, including battle, title,
  opening, character select, replay and staff roll scene owners.
- Derived auxiliary ctor `00458650`: **2 real direct calls from
  currently authored game code**, including fighter initialization.
- Base auxiliary ctor `00458670`: **2 real direct calls**, one from
  the original derived ctor `00458650` (itself unclassified), and one
  from an authored `CharacterAuxObject` game initializer.

These original direct calls show that the three constructors are
**genuinely used by the game**, not synthetic dead probes. However,
a source-written constructor and a compiler-generated default
constructor have indistinguishable native machine code here, and
original authored *callers* do not establish whether the callees
are explicit developer functions or generated/lifecycle glue.
The original ownership rows remain `unknown`, disposition `review`
in `config/function-origins.csv`; the provisional class names are
**not historically established**, and no authored match unit or
config acceptance entry is added.

**F616 contributes 88 whole-original CODE bytes of rigorously
source-backed evidence, but ZERO new accepted authored whole
functions or authored byte coverage.** The original 95 unknown-origin
functions/3,420 bytes remain pending until independent class/source
provenance is established; the official 943 authored exact functions/
862,726 original CODE bytes are unchanged. Separate game callee
`00417210`, class vtable DATA, and compiler runtime are not
implicitly credited by these three exact source function bodies.
There was no game binary edit, no manual assembly, no all-unit
cold replay and no external Oracle acceptance claim.

## Reproduce by cold-compiling only the two changed source TUs

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-native-game-constructors-f616.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Both complete newly generated source COFF/PDBs, compiler logs, all
actual original PE linked-byte receipts and independently scanned
original native callers are under ignored
`.analysis/f616-native-constructors/verified/`. Earlier trial source
probes are preserved in `.analysis/f616-native-constructors/`.
