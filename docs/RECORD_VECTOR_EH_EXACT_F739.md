# F739 — four original complete authored record EH constructors/destructors cold-exact

**NEW canonical authored complete-game CODE: four functions /312 native
CODE bytes.** The pinned user-provided Japanese TH075 ver1.11 executable
is `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The previously reviewed original provenance is **R211** (`00458960`),
**R212** (`005F7F20`), and **R256** (both separate record destructors).
All four were authored independently of this reconstruction; their
original class names and private full layouts are provisional.

## Original complete native CODE and meaningful normal VC7.1 source

| Complete original authored function | Native whole CODE / x86 | Actual native member lifetime and fields | Physical target-defined COFF fields |
| --- | ---: | --- | ---: |
| `00458960`, 20-byte record constructor | **93 B /25 x86** | Construct embedded vector at `+0` via `00458AA0`, save native EH state 0, explicitly clear vector via `00458B50`, write two 16-bit zeros at `+0x10/+0x12`, restore EH and return `this` | **6** |
| `004586C0`, 20-byte record destructor | **72 B /20 x86** | With EH state 0 call real vector `Clear` `00458B50`, set final EH state -1 and automatically destruct embedded vector via `00458AD0` | **6** |
| `005F7F20`, 16-byte container constructor | **75 B /21 x86** | Construct embedded vector through `005F7F70`, save real EH state 0, explicitly clear via `005F8020`, restore EH chain and return `this` | **6** |
| `005F7ED0`, 16-byte container destructor | **72 B /20 x86** | Explicit vector clear `005F8020` followed by automatic vector destruction `005F7FA0`, with original EH state cleanup | **6** |
| **Four native whole functions** | **312 CODE B /86 x86** | Two genuinely used embedded RAII vector members | **24 typed original PE/COFF** |

Tracked ordinary [`src/RecordVectorLifetimesF739.cpp`](../src/RecordVectorLifetimesF739.cpp)
models each actual vector subobject as a real embedded C++ member,
not a proxy with an inert pad or artificial return path. The
compiler naturally invokes its default constructor and destructor;
the authored constructor/destructor body calls its real `Clear()`.
Only the two native 16-byte vector storage extents and two real
trailing 16-bit zeroed words (for the 20-byte class) are needed.
The original historical class names remain unknown and no complete
vendor/private layout is claimed.

Pinned MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` produces all
**312 original native CODE bytes, all 86 ordered x86 instructions,
and all 24 original physical typed PE fields**. Each native
function's exact EH prologue includes `PUSH −1`, original
`PUSH EH handler`, true `FS:[0]` chain installation, saved `this`
`EBP−0x10`, the actual state 0/−1 writes to `EBP−4`, original
member call order, FS-chain restoration and full original `RET`.
There is no missing constructor branch, partial-body acceptance
or stitched native instruction data.

## Extra independent full native EH carrier audit (beyond body CODE)

A structural CODE match alone is insufficient for a truthful
exception-lifetime story, so the original PE's **four associated
MSVC EH handler and unwind DATA carriers** were independently
read and compared to the *same* compiled VC7.1 COFF object:

| Native function | Original 18-B EH stub start (native handler at start+8) | Original associated 36-B `.xdata` start |
| --- | --- | --- |
| `00458960` ctor | `00656220` (handler `00656228`) | `006697DC` (table pointer `006697E4`) |
| `004586C0` dtor | `006561A0` (handler `006561A8`) | `00669750` (table pointer `00669758`) |
| `005F7F20` ctor | `006566D0` (handler `006566D8`) | `0066A08C` (table pointer `0066A094`) |
| `005F7ED0` dtor | `006566B0` (handler `006566B8`) | `0066A068` (table pointer `0066A070`) |

The source COFF has four real 18-byte `.text$x` carrier sections,
each with exactly **three** correctly typed original relocation
positions: `REL32` at +4 to its original embedded vector destructor
(`00458AD0` or `005F7FA0`), `DIR32` at +9 to the correct actual
EH table start+8, and `REL32` at +14 to the independently observed
native `___CxxFrameHandler` `006407B8`. All **6/6 nonrelocation
bytes** of every 18-byte original EH stub match the same COFF
section.

The paired four true 36-byte `.xdata$x` sections carry **two**
real typed `DIR32` positions apiece: +4 points to that handler's
original cleanup stub start, +16 points to the actual beginning
of its own 36-byte unwind data. Every source/PE table has
**28/28 matching nonrelocation bytes** (including the native
`FFFFFFFF` state and `0x19930520` record encoding). Thus across
all four carriers, **136/136 nonrelocation EH stub+DATA bytes
match**, and all **20 real EH carrier typed references** have
the correct original native destination roles. These ancillary
carriers are independently owned code/data and are **not added
again to authored whole-function CODE coverage**. This is an
additional check beyond the canonical four main-function matches;
it does not silently assume that matching EH *names* establishes
identical original external unwind structure.

## Official targeted cold-build acceptance

Four new distinct matching units record the full original
functions, their unique original native EH handler pointer,
`__except_list` entries, vector calls, PE targets, COFF symbol,
relocation kind, physical original offsets and original complete
CODE sizes. The canonical compiler freshly built only **one
C++ source object**, then independently replayed exactly these
four original whole game functions:

```bash
scripts/repo-python scripts/replay-exact-units.py \
 --unit record20-clear-and-zero-construct-00458960 \
 --unit record20-clear-then-destroy-004586c0 \
 --unit record16-construct-clear-005f7f20 \
 --unit record16-clear-then-destroy-005f7ed0
# Cold replay: 4/4 exact units across 1 object
```

The extra carrier inspection used the actual compiled object,
original pinned native PE and the real `.text$x` / `.xdata$x`
section and COFF records; the complete compiler output and
research evidence remain under ignored local
`.analysis/f739-record-eh/`. Original R211/R212/R256 provenance
and all older 957 matched units were preserved; no all-unit cold
replay, synthetic EBP locals, machine-byte graft, invented caller
or re-credit for vector/CRT callee CODE.

**Current formal authored original ledger after F739:** **961
cold-exact entire source-present game functions /961 exact units**,
**863,592 original CODE bytes**, **43.75%** of reviewed original
1,973,704 CODE B and **43.68% conservative** including 3,420 B
with unresolved provenance. All 22 giant fighters and the three
WinMain/Scene/Archive complete functions remain NONEXACT, so the
98% goal is not yet met.
