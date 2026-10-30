# F742 — 60-byte authored InputMapping complete initializer COLD EXACT

**New canonical whole original authored game-function exact CODE:
`00406DB0`, 60 original CODE bytes, 24 real x86 instructions and three
physical typed PE/COFF references.** Target is the user's original
Japanese TH075 ver1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The R015 independently reviewed authored origin was already documented
before this reconstruction. This is the **complete original callable
function**, not an internal switch case, historical name assertion,
compiler/library thunk or duplicate credit for its callees.

## Actual original native extent and game semantics

The original physical `00406DB0..00406DEC` entire function has the
real `PUSH EBP; MOV EBP,ESP; PUSH ECX` thiscall prologue, saves the
receiver at `EBP−4`, calls actual `InputResourceClient` constructor
`00403B90` with **unadjusted ECX**, and performs two distinct
original CRT zeroing operations in this **specific sequence**:

1. `memset(this+0x2C,0,0x1C)` — clear **28 actual original bytes**
   beginning at physical receiver offset +44.
2. `memset(this+4,0,0x28)` — clear **40 actual original bytes**
   beginning at physical receiver offset +4.

The original function then returns `this` in EAX, restoring EBP and
emitting a regular `RET`. The two memsets are not interchangeable
for exact codegen and their original unsigned size and member
address arithmetic are independently observable.

Tracked natural [`src/InputMappingInitializeF742.cpp`](../src/InputMappingInitializeF742.cpp)
defines one original-shaped ordinary `InputMappingF742` derived from
the *actually called* InputResourceClient interface. Since the shared
`InputResourceClient` C++ header is deliberately a count-only
interface and does **not** claim the complete original base layout,
the derived source includes **four actual native object-storage
bytes** preceding the two physically observed cleared ranges.
This models the original member boundary at +4; it is **object
storage, not a fabricated stack-frame local or compiler padding
instruction**. The exact historical private class declaration,
contents of those four bytes and the original method name remain
unknown. The output source has the genuine native member clear
extents and ABI, not fabricated logic.

The pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` emits
**exactly 60 original CODE bytes and 24 ordered x86 positions**,
including exact return. Original **48/48 nonrelocation bytes**
agree, plus all **three actual physical `REL32` COFF fields**:

| Original function CODE offset | Source symbol | Original absolute PE target |
| ---: | --- | --- |
| `+0x0B` | `??0InputResourceClient@@QAE@XZ` | `00403B90` |
| `+0x1B` | `_memset` | `00640490` |
| `+0x2E` | `_memset` | `00640490` |

The native original has the same physical CALL-owning x86 ordinals,
`REL32` kind and zero COFF addend. Calling the native original
InputResourceClient and CRT memset does **not** re-credit those
callee CODE bytes to the new 60-B wrapper.

## Reproducible targeted acceptance

One new unit with the actual original target, source and all physical
typed fields is recorded in `config/match-units.toml`:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit input-mapping-initialize-00406db0
# Cold replay: 1/1 exact units across 1 object
```

The canonical test cold builds just **one affected original-shaped
C++ object**, then compares the entire function, all real typed
relocations and native byte positions; all previous 963 accepted
units remain untouched and are **not cold-replayed**.
The entire original original/source PE comparison, source object,
compile transcript and original layout trial remain under ignored
`.analysis/f742-input-mapping-init/`. Independent original authored
origin `R015` and all other provenance classifications are unchanged.

**Formal authored ledger following F742:** **964 cold-exact complete
functions /964 source-present /964 canonical units**, **863,913
original CODE bytes**, **43.77% reviewed** of 1,973,704 and
**43.70% conservative** including the separate 3,420 bytes pending
origin proof. No giant or the WinMain/Scene/Archive original complete
function has been falsely promoted; the 98% goal remains incomplete.
