# F738 — two complete authored record-prefix policies canonically cold-exact

**NEW original whole-function exact CODE: 2 authored functions, 117 native
CODE bytes.** Pinned original is the user-supplied Japanese TH075 v1.11
`resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Both functions had independent authored provenance **before** this
C++ reconstruction: R211 for the conditional allocation/zeroing and
R210 for the explicit record prefix zero/flag policy. They are not
CRT/library functions or provenance-unknown compiler thunks.

## Original complete bounded PE and ordinary VC7.1 C++

| Original whole authored target | Entire original CODE/x86 | Genuine original behavior | Actual physical typed PE/COFF fields |
| --- | --- | --- | --- |
| `00458790` | **70 B /26 x86** | Clear original byte `this+0xC`; if `this+8` is null, scalar-allocate **36 B**, assign returned pointer, then **always** clear all 36 bytes, including when storage was reused | `REL32` offset `0x1C` to native scalar `operator new` `0064159D`; `REL32` `0x3B` to CRT `_memset` `00640490` |
| `00458880` | **47 B /18 x86** | Explicit `memset(this,0,16)`, set original `this+8` pointer to null, write byte one at `this+0xC`, return original `this` receiver | `REL32` offset `0x10` to CRT `_memset` `00640490` |
| **Total** | **117 original CODE B /44 x86** | Two distinct real authored 16-byte prefix ownership policies | **3 genuine physically typed fields** |

Tracked [`src/RecordPrefixPoliciesF738.cpp`](../src/RecordPrefixPoliciesF738.cpp)
reconstructs exactly these complete original game functions using
natural C++ and pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`.
The inferred 16-byte record has physically observed pointer at +8
and flag at +12; its other private fields and historical class name
remain unproved. No fake padding used to shape codegen.

Original `00458790` has **two genuinely used temporary stack slots**:
its `this` receiver is saved at `EBP−8` and the scalar allocation
result at `EBP−4`. The genuine source records and subsequently uses
the same returned pointer in member `+8`. VC7.1 emits the exact
original x86 prologue, branch, `operator new(36)`, pointer copy,
`memset(pointer,0,36)` and `RET`, including native actual physical
field positions, types and link targets. Original `00458880` has
one real `EBP−4` saved receiver and returns it intact; its
full 47-byte body matches after the actual physical CRT field.

### Critical native CFG correction from diagnostic to cold-exact

The first natural candidate for `00458790` put the 36-byte
`memset` **inside** the `if (!owned36At8)` conditional. It
compiled to the *same 70 bytes and same 26 ordered x86* and
had both correct source COFF fields, yet the canonical original
comparison found **69/70 bytes equal**. Its `JNE` byte had
target-relative displacement `0x29` instead of original **`0x16`**
at original whole-CODE offset `0x18`.

Re-reading the actual original native jump destination `004587BF`
proved that the branch skips **only the allocation** and joins
**before** the unconditional 36-byte `memset`. The code still
clears reused storage; the initial source condition therefore
had incorrect GAME semantics, not just an assembly formatting
difference. Moving the real `memset` after the `if` naturally
restored the actual original branch byte. There is no source
alignment directive, manual branch displacement or copy/paste
from the original executable.

## Actual per-unit cold replay, no global cold build

Both original callable functions are independently listed in
`config/match-units.toml` with their native PE target address,
complete 70/47 byte original size, source, COFF symbol, original
physical relocation offsets, types and exact callee targets. The
already archived R210/R211 origin decisions were preserved.
After correct native source was written, the canonical tool **cold
built ONE original-shaped normal C++ object** and replayed just
these two *new* exact units:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit record-prefix-reset-allocation-00458790 \
  --unit record-prefix-zero-flag-00458880
# Cold replay: 2/2 exact units across 1 object
```

The canonical comparator verified all **117 original CODE bytes,
all 3 physically typed real PE/COFF fields, and their real target
symbols/zero addends** with zero original/source differences.
No native CRT scalar-allocator or `_memset` callee CODE was credited
to either game function. All previously accepted 955 whole functions
remain preserved and were **not cold-replayed en masse**.

**Live accepted authored ledger after F738:** **957 complete
cold-exact functions/957 source-present/957 canonical units**,
**863,280 original CODE bytes** (**43.74%** of **1,973,704**
reviewed authored bytes; **43.66%** conservative with the 95
independently provenance-pending functions totaling 3,420 B).
The separate 22 large fighter bosses, 2,987-byte WinMain, 248-byte
Scene destructor and 171-byte ArchiveCatalog destructor remain
whole-function NONEXACT. The 98% goal remains incomplete.
