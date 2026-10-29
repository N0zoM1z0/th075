# F691 — entire original 249-byte COM resource cleanup and singly linked list unlink

Pinned user-supplied Japanese TH075 1.11 `resources/th075.exe`,
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is a **complete original native PE machine-byte identical
function**, not a compiler-created excerpt or a separate part of a
giant. Actual original `config/function-origins.csv` remains
**`origin=unknown, disposition=review`**: current byte-perfect C++
source does not prove the author's historical type/SDK ownership.

## Full native original 249-byte function and actual source operations

| Whole real registered original native function | Complete original linked machine CODE | Entire genuine x86 | Physical original PE/COFF fields | Historical source owner |
| --- | ---: | ---: | ---: | --- |
| **`0061F125`–`0061F21E`** | **249/249 B** | **104/104** | **Five distinct zero-addend `DIR32`** | **UNKNOWN** |

The real native code receives `this` in ECX, uses authentic
`this+0x64/+0x68` COM handles and an actual resource object at
`this+4`, calling genuine virtual `__stdcall` callback at vtable
byte offset **`+0xE0`** twice. It then executes the genuine **eight-
element twin-resource release loop** over original live pointer
members `this+0x30..+0x4C` and `this+0x10..+0x2C`, invoking native
COM `__stdcall` vtable slot **`+8`** for nonnull pointers and
clearing each pointer to zero. It releases the additional native
members `this+0xC` and `this+4` through the same slot and clears
them to null. The native code conditionally invokes the authentic
double-argument import `00657048` for two `this+0x6C`
resource/handle pairs at actual offsets `+0xA8` and `+0x9C`, then
frees native pointer `+0x98` through imported `0065704C` and
releases native pointer `+0x6C` through imported `0065702C`.

Finally, the function removes **this exact object** from a real
singly linked global list at original PE **`0068E264`**, where
the actual next-pointer field of a linked node is at **`+0xAC`**.
Its original machine code uses `CMP [0068E264],EBP` with EBP=0,
`MOV EAX,0068E264`, traverses `LEA EAX,[ECX+0xAC]` until it
finds this receiver or reaches a null link, and writes the
successor pointer into that actual link. This last original loop
was critical to recovering the entire function exactness.

The ordinary C++ source
[`SDKNativeCOMManagerCleanupF691.cpp`](../probes/SDKNativeCOMManagerCleanupF691.cpp)
models only genuine observed resource pointer offsets, imported
function ABI signatures, explicit vtable callback slots and the
actual linked next-pointer offset. It does **not** create a fake
0xAC-byte local array or 57 meaningless C++ virtual methods to
reach COM slot `+0xE0`. The source's class/field names are
provisional native ABI grammar, not historical original class names.

## Why an independently tested natural list condition mattered

The first real-source build used natural typed source with
`if (*cursor) { while (*cursor!=this && next) ... }`. This recovered
**all first 87 native x86 instruction roles and their physical
geometry**, including the real COM handle and eight-element twin
release loops, but emitted **257/108** rather than original **249
bytes/104 instructions**: four extra list-loop instructions and
incorrect loop-head register ownership. Source methods
`Next()/NextPtr()` with pinned `/Ob0` produced extra calls and
larger code, so they were rejected.

The correct normal C++ declaration is a typed pointer-to-link and
the actually meaningful termination condition:

```cpp
SDKCOMManagerF691** cursor = &g_SDKCOMManagerHeadF691;
while (*cursor && *cursor != this)
    cursor = reinterpret_cast<SDKCOMManagerF691**>(
        reinterpret_cast<char*>(*cursor) + 0xAC);
if (*cursor)
    *cursor = *reinterpret_cast<SDKCOMManagerF691**>(
        reinterpret_cast<char*>(*cursor) + 0xAC);
```

This preserves the original list behavior and naturally lowers to
**all 104 original instructions**, including the `CMP [global],0`,
`LEA next`, `JNE`, and final `MOV [link],next` instructions.
**Five independent meaningful loop-condition/explicit-branch
variants** were compiled before finding the exact form; more
controls compared early null checks, do/for constructs and
address/read ordering. The selected pinned profile is normal
MSVC VC7.1 **`/O1 /Ob0 /Gy /GR- /GX- /GS /Zi`**. `/O2`
changes actual saved registers and native loop source geometry;
it is not interchangeable for this function.

## All five true original zero-addend native PE/COFF relocations

| Physical original source field offset | Field type | Original PE target | Genuine compiler symbol role |
| --- | --- | --- | --- |
| `+129` | `DIR32` | `00657048` | imported double-argument COM pair release |
| `+185` | `DIR32` | `0065704C` | imported `__stdcall` resource free |
| `+199` | `DIR32` | `0065702C` | imported `__stdcall` resource dispose |
| `+205` | `DIR32` | `0068E264` | original global list head read |
| `+210` | `DIR32` | `0068E264` | original global list head address |

[`verify-sdk-native-com-manager-cleanup-f691.py`](../scripts/verify-sdk-native-com-manager-cleanup-f691.py)
fresh-compiles **only this selected small source TU**, checks all
104 genuine original complete x86 mnemonics/widths/raw operands,
the actual COM slot and native loop/callback roles, independently
verifies every physical original source COFF `DIR32` symbol,
zero addend and original PE target, and compares **all 249
original linked machine CODE bytes** after linking only these
five genuine fields in a comparison bytearray. The original EXE
is never modified. A separate scan over all 4,351 registered
original native CODE function extents finds **one real direct
CALL** to this whole function; absence of other direct calls does
not exclude indirect use or identify original authorship.

The previous F595–F687 research cohort contained **84 distinct
complete source-backed but origin-UNKNOWN whole functions /
1,700 original CODE bytes**. F691 adds this substantial **249-byte
complete original**, giving **85 distinct whole original source-
backed UNKNOWN functions /1,949 genuine CODE bytes**. All 95
historical source-unknown candidates remain `unknown,review` and
uncredited. Official authored exact coverage remains **943
whole functions /862,726 original CODE bytes (43.71% reviewed)**;
no 22 giant parent exactness is asserted.

```bash
scripts/repo-python scripts/verify-sdk-native-com-manager-cleanup-f691.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Compiler CPP/OBJ/PDB, original target/COFF field receipts, original
direct-caller graph and source hash remain in ignored
`.analysis/f691-native-com-manager-cleanup/`. All meaningful
wrong C++ list/COM calls and selected native compiler controls
are preserved under ignored `.analysis/f691-com-cleanup-large/`.
No original EXE patch, fake dummy object layout/stack locals,
all-943-unit cold replay or external Oracle whole-function
acceptance was performed.
