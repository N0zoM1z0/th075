# F741 — two complete authored 116-byte nested-record lifetimes cold-exact

**New canonical original whole-game CODE: two functions, 261 original CODE
bytes.** The original is the user-supplied Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
These two functions were **independently authored before the present
reconstruction** by the target/source evidence R210 (construction
policy) and R209 (explicit clear-before-destruction policy). Original
private class names and all member semantics beyond the physically
observed bytes are provisional.

## Two entire native PE original functions and actual ordinary C++

| Original native entire callable function | Original CODE / native x86 | Genuine original member lifecycle | Physically typed COFF fields |
| --- | --- | --- | ---: |
| `004587E0` — nested record construction/explicit clear | **145 B /41 x86** | Construct real 16-B prefix, then two 16-B vector subobjects at `this+0x54/+0x64`; update native EH states **0,1,2**, `memset(this,0,116)`, explicitly call `Clear()` on both real vector members, write `this+8=0`, restore exception chain, return `this` | **10** |
| `004588E0` — nested record explicit clear/destruction | **116 B /32 x86** | Enter EH state **2**, explicitly clear vector `+0x54` then `+0x64`, destruct embedded vector members in reverse order `+0x64` then `+0x54` through native `004589F0`, finally destruct prefix through `004588B0`, restore exception chain and return | **9** |
| **Both complete authored functions** | **261 CODE B /73 native x86** | Three actually constructed and destructed RAII member objects | **19 authentic original PE/COFF fields** |

Tracked natural [`src/NestedRecordLifecycleF741.cpp`](../src/NestedRecordLifecycleF741.cpp)
uses a real `Prefix16F741` member, an actual 0x44-byte region of
additional original record storage between prefix and vectors, and
two real `Vector16F741` member objects. The 0x44-byte region is part
of the original **116 bytes reset by the actual `memset`** and is
needed for the original vector owner offsets; its historical private
member declarations are unknown. It is **not** an inert stack-frame
padding local or fabricated unused arithmetic variable. The member
constructors/destructors have normal nontrivial C++ lifetimes,
which cause VC7.1 to emit authentic EH cleanup without handwritten
instructions, forced local stack slots, assembly or conditional
per-build source bodies.

Under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi`, both whole
callable original functions generate **exactly all original 261
CODE bytes and 73 native x86 instruction positions**, including
original full prologues, `FS:[0]` chain handling, state changes,
original member-relative offsets, complete ordinary returns and
all **19 original typed physical `DIR32`/`REL32` fields**. Both
individual original x86 bodies have **185/185 equal unrelocated
native bytes**, plus all 19 actually relinked PE targets at their
physical original instruction offsets. Native `004587E0` originally
calls the already accepted 47-B prefix initializer at `00458880`;
that callee's original CODE is **not** counted a second time.
Native vector init `004589C0`, clear `00458A80`, automatic vector
destruction `004589F0` and prefix destruction `004588B0` are
observed physical external calls; no unknown short callee was
reclassified as authored.

## Additional independent EH-carrier audit

Since the original native bodies are C++ constructor/destructor
functions, merely matching their CODE does not demonstrate the
exception paths. We additionally opened the same just-compiled
VC7.1 object's actual COFF `.text$x` and `.xdata$x` carriers,
read the corresponding native PE sections, and compared their
**entire physically bounded** 40- and 52-byte contents:

| Main original function | Native 40-B cleanup/EH stub beginning | Native handler entry within stub | Native 52-B unwind data beginning |
| --- | --- | --- | --- |
| `004587E0` | `006561C0` | `006561DE` (+30) | `00669774` |
| `004588E0` | `006561F0` | `0065620E` (+30) | `006697A8` |

Each 40-B native EH stub contains **three real cleanup entry
points** with actual destructor call references, followed by the
`MOV EAX,<native unwind table>; JMP ___CxxFrameHandler` sequence.
Its **five genuine typed COFF fields** comprise three `REL32`
member-destructor calls, a local `DIR32` unwind-data pointer and
one `REL32` frame-handler call at native `006407B8`.
**20/20 unrelocated original bytes** of each complete 40-byte
stub agree with the corresponding compiled `.text$x` object.

Each 52-B unwind table contains **four genuine `DIR32` fields**
to the actual original cleanup start offsets (`stub+0`, `+8`,
`+19`) and its own original table data beginning. Every
**36/36 unrelocated original unwind DATA bytes** match the
compiled `.xdata$x`, including the native EH-state and C++ frame
header encoding. All **18 actual EH-carrier typed local/external
references** are also validated for original PE destinations,
not just symbol names. Combined, **112/112 nonfield bytes match
across two full 40-B stubs and two full 52-B unwind records**.
These carriers are separate C++ runtime/linker-owned instructions
and data and are **NOT double-credited** as new callable authored
game-function CODE. The additional read-only audit and its real
object/PE evidence remain locally under ignored
`.analysis/f741-nested-record/verify-carriers.py` and
`.analysis/f741-nested-record/eh-original-carrier-proof.json`.

## Canonical target-only cold replay and official accounting

Two new complete-function units in `config/match-units.toml`
record the true original `004587E0/004588E0` bounds, source,
compiler flags, decorated symbols, original EH-handler addresses,
actual member-call targets, and every real typed PE/COFF
relocation. The canonical matcher then freshly built **only one
new VC7.1 source object** and validated both entire functions:

```bash
scripts/repo-python scripts/replay-exact-units.py \
 --unit nested-record116-construct-clear-004587e0 \
 --unit nested-record116-clear-then-destroy-004588e0
# Cold replay: 2/2 exact units across 1 object
```

Only after actual successful canonical native comparisons were two
functions added to `config/functions.csv`, `config/matches.csv`,
`config/reccmp-functions.csv`, `config/implemented.csv`, and the
exact-unit graph. Their **R209/R210 independent author-origin
classification is unchanged**, as are all 961 previously accepted
exact units and the 95 provenance-unknown candidates. No entire
corpus cold replay was run.

**Official F741 accepted authored ledger:** **963 cold-exact entire
original game functions /963 source-present /963 configured units**,
**863,853 native original CODE bytes**, **43.77%** of the reviewed
1,973,704 original authored CODE B (**43.69% conservative** with
the separate 3,420 provenance-pending bytes). The 22 giant and
three WinMain/Scene/Archive complete functions remain NONEXACT;
the 98% authored goal is incomplete.
