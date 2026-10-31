# F973 — Typed borrowed effect dispatch fields, eight original whole functions exact

The pinned Japanese TH075 v1.11 game
EXE independently proves actual original
fighter fields accessed by **two distinct
original effect forwarding source objects**.
They agree on a 32-bit effect queue/spawner
pointer physically at receiver **+0x2EC**.
The original player also passes the
**+0x2F0** address as a tracking/transform
pointer when linked tracking is enabled,
and the real **+0x314** address as a
float effect parameter. Source code
does not establish the complete historical
fighter, queue or transform object layout.

The new [bounded borrowed C++ field view](../src/FighterEffectBorrowedFieldsF973.hpp)
models only a **4-byte native
queue pointer** and physically
adjacent first tracking/transform
byte at +0x2F0; another independent
one-float borrowed view starts at
+0x314. The first original byte at
+0x2F0 may be part of a larger
unrecovered transform region.
C++ struct tail alignment/padding
does NOT imply original known
storage past that byte. No view
is allocated or embedded in a
complete actor class.

The effect queue's actual C++ call
interface is different in the two
source files, but both are concrete
ordinary C++ pointer-only interfaces:
[effect forwarders](../src/FighterEffectPolicies.cpp)
use `BattleEffectQueueF135*`,
while [tracked effect helpers](../src/FighterTrackedEffectsF169.cpp)
use `BattleEffectSpawnerF136*`.
The borrowed template changes only
the real queue pointee type, preserving
native 32-bit pointer ABI, field
address and indirect member calls.
The original `+0x314` address
is passed as a genuine pointer to
the same existing float; no temporary
copies, fake register-spill locals
or new original argument values
are introduced.

VC7.1 **cannot compile a dependent
template `offsetof` typedef**,
as independently observed in an
initial cold pilot. That unsupported
assertion was corrected rather
than changing the native source
or compiler profile: the view
checks original pointer width and
the canonical whole function
cold replay validates actual
+0x2EC/+0x2F0/+0x314 operand
locations and complete PE/COFF
relocation identity for each
affected original callable function.

## Canonical cold replay of affected functions only

Two selected entire-function pilots
completed **2/2 exact**. The canonical
per-unit cold replay then rebuilt
**every whole callable function whose
`source` is one of the TWO modified
translation units** under its own
original pinned VC7.1 compiler
profile, checking entire native
CODE ranges and all physical
PE/COFF source symbols,
relocation offsets/types/addends
and resolved game targets.

| Changed real source object | Whole original functions | Original CODE |
| --- | ---: | ---: |
| FighterEffectPolicies.cpp | 6 | **449 B** |
| FighterTrackedEffectsF169.cpp | 2 | **281 B** |
| **Total affected native originals** | **8/8 exact** | **730 B** |

Actual canonical transcript:

    Cold replay: 8/8 exact units across 2 objects

The eight affected unit names are
exactly the current
`config/match-units.toml` sources
listed above, and the private
source/object/PE receipt is under
ignored `.analysis/f973-fighter-effect/all-eight-cold.log`.

**All 730 original bytes were already
accepted exact** before the source
type improvement. This is native
field ownership reconstruction,
not new original CODE coverage.
No 979-unit corpus cold replay.
