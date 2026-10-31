# F933 — Two real stage initialization grammars at native +0x0C/+0x10/+0x14

The SHA-pinned Japanese TH075 v1.11 PE has 36 previously
accepted whole authored stage constructors in two
independently compiled VC7.1 C++ translation units:
src/BackgroundLoadPairF376.cpp (2 complete native functions)
and src/BackgroundLoadFamilyF377.cpp (34 functions).

The original whole constructor bodies are 140–181 CODE bytes each,
with their own genuine base constructor/EH lifetime,
real stage vtables, stage-specific asset filenames, stage
resource-pack allocation/read, and actual camera initialization
where applicable. The original native store destinations at
receiver +0x0C/+0x10/+0x14 are shared, but the field values
and physical source *types* are NOT uniform.

Re-reading the actual complete source against independently
observed native stores reveals two meaningful grammars:

| Authentic source/native stage grammar | Constructors | Real original values |
| --- | ---: | --- |
| Three unsigned 32-bit zero-initialized words | 30 | +0x0C=0, +0x10=0, +0x14=0 |
| Three 32-bit floating stage parameters | 6 | +0x0C=640.0f, +0x10=100.0f, +0x14=100.0f |
| **Total independent whole native constructors** | **36** | **Two real value/type paths** |

The initial proposal to treat every stage's three values as
zeroed integer counters was rejected after actual source/native
inspection found the six floating initializer owners. The
shared [BackgroundStageStateF933.hpp](../src/BackgroundStageStateF933.hpp)
therefore defines **TWO explicitly different borrowed
12-byte typed field windows**, offset-local to genuine
receiver+0x0C: unsigned DWORD zero fields and float fields.
Both preserve the original 0,4,8 internal member offsets,
verified by pinned VC7.1 sizeof/offsetof compile-time assertions.

These views are never allocated or embedded as fake stage
owners and make NO historical claim that F376 and F377
were the same concrete original class. Unknown bytes
outside the observed three-field window are still unknown.
Both source files retain their native original base object
and stage-asset/camera/pack C++ operations. The offset-local
field windows replace only the six recurring physical
field-address casts and their F377 siblings, without
introducing pad members, assembly, byte grafts or false
object layout.

## Canonical affected-unit cold replay

Only the 36 affected whole stage constructors were rebuilt
serially under their original individual pinned per-unit
VC7.1 compiler profiles (2 resulting source OBJ files).
The canonical exact-unit checker revalidated each
entire original PE CODE range and **every configured real
physical PE/COFF relocation**. The 36 separate complete
functions total **5,531 original native CODE bytes**.

    scripts/repo-python scripts/replay-exact-units.py       --unit background-stage-load-bg00a-00449aa0       --unit background-stage-load-bg00b-00449e10       ... other 34 background-stage-load-bgXX units from these 2 sources

Full cold-build receipt in local ignored
.analysis/f933-stage-initial-fields/all-affected-36-cold.log:

    Cold replay: 36/36 exact units across 2 objects

A preliminary targeted four-function cold replay also passed.
No other original game functions were cold-replayed; in
particular no complete 979-unit or giant-function replay was run.

**These 5,531 bytes were already accepted exact before F933.**
This change improves actual source/field semantics while
retaining formal 979 whole exact functions and 868,243 bytes
in the native ledger. No new accepted original code credit.
