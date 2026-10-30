# F769 — original R017 texture slot allocation, complete 184-byte cold exact

**One newly accepted independently R017-authored complete original game
function** at `0040B110..0040B1C7`, in the pinned Japanese TH075
v1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The actual original callable function is **184 CODE bytes /56 x86
instructions /8 genuine typed zero-addend PE/COFF relocation fields**.
A selected fresh VC7.1 one-unit cold replay verifies **1/1 exact**.
Source: [`src/TextureSlotsF769.cpp`](../src/TextureSlotsF769.cpp).

## Original native game ownership and policy

This real `thiscall` takes a slot count and an unsigned-byte texture
mode. It constructs a stack-local 44-byte texture record with native
constructor `0040D8C0`, maintains genuine Microsoft VC7 `/GX`
`FS:[0]` exception state and destroys it with native `0040D8E0`.
The original saved receiver is **`EBP−0x40`** with real
`SUB ESP,0x34`, the actual used local record starts at
**`EBP−0x38`** and the later used DWORD zero at **`EBP−0x3C`**.
These are machine-observed original positions, not guessed C++ class
fields or unreferenced fake padding.

The function assigns incoming mode to original owner byte
`this+0x4C` and performs all four genuine ordered native comparisons:
`mode != 0`, `mode != 0x10`, `mode == 0x18`, `mode != 0x20`.
If all conditions hold it normalizes original `0x18` to `0x10`.
Although some conditions are logically redundant, the VC7.1
nonoptimized original *actually emits them*, so the source does not
replace the observed branch with an unproven historical convenience.

The original first vector at `this+8` receives
`Assign(count, constructedElement)` through genuine VC7 vendor
callee **`0040DDA0`**. A second vector at `this+0x18` receives
`Assign(count, zeroDWORD)` through `0040DF20`. Constructor,
exception-state transitions, assignments, native destructor and
exception-list restoration occur in their actual original order.
The two vector assign callees are independently vendor/STL-classified
in the origin ledger and are **not** new game-authored CODE credit.
The historical name or entire original private texture manager and
44-byte element layouts remain **provisional**.

## Corrected used object size from actual PE bytes

The first meaningful normal C++ probe used a 40-byte element, which
produced the right **184-byte instruction extent and eight COFF
fields** but matched only **137/152 nonrelocated original bytes**.
These fifteen differences are authentic stack-frame and local-access
operands: source frame `SUB ESP,0x30` and saved receiver at
`EBP−0x3C` versus native `SUB ESP,0x34`, `EBP−0x40`.
The original actually requires a **44-byte** constructed member
rather than the provisional 40-byte envelope.

Using a real 11-DWORD (44-byte) physically observed local (not an
unused filler) lets VC7.1 place the ctor/dtor object, receiver,
second vector's zero element and EH state in the native slots.
The same ordinary C++ source now emits **all 184 original CODE
bytes and 56 native x86**, and precisely **152/152 original
nonrelocation bytes**. No target-code insertion, manual assembly,
artificial stack gaps or split-case comparison was used.

## Complete typed PE/COFF and selective acceptance

The selected canonical unit
`texture-manager-allocate-slots-native-0040b110` records these
eight real original physical relocation field offsets:

| Original CODE offset | Original type | Native PE resolved target |
| --- | --- | --- |
| `+06` | DIR32 | `00654F36` original compiler EH handler |
| `+0C`, `+14` | DIR32 | `__except_list` / `FS:[0]` |
| `+22` | REL32 | `0040D8C0` used texture element ctor |
| `+7B` | REL32 | `0040DDA0` first vector assign |
| `+95` | REL32 | `0040DF20` second vector assign |
| `+A4` | REL32 | `0040D8E0` used element destructor |
| `+AE` | DIR32 | `__except_list` restoration |

Every original PE field's offset, type, zero addend, decorated COFF
source symbol and resolved original PE target was independently
checked. The native EH carrier/VC7 library CODE is not separately
counted as new game-authored bytes.

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit texture-manager-allocate-slots-native-0040b110
# texture-manager-allocate-slots-native-0040b110: exact; 184 coverage bytes
# Cold replay: 1/1 exact units across 1 objects
```

The official authored complete-function ledger now has **974 exact
functions /865,811 original game CODE bytes**, reviewed **43.87%**,
conservative **43.79%**, and **30 still-unmatched original-authored
whole functions**: 22 large giants and 8 small/medium originals
(5,838 native CODE bytes). The goal of 98% whole-authored-byte
coverage remains unmet. No unrelated accepted unit or all-unit cold
replay was run; historical files and unrelated work were preserved.
