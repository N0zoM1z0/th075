# 東方萃夢想 ～ Immaterial and Missing Power

<p align="center"><img src="resources/title-screen.png" width="640" alt="User-supplied TH075 title screen"></p>
<p align="center"><img src="resources/progress.svg" alt="Function reconstruction progress"></p>

This repository reconstructs **TH075 (ver1.11) functions in natural C++**, comparing
complete VC7.1-compiled x86 code and all physical COFF relocations against a
user-supplied executable. It is **not yet a complete game rebuild**.

## Pinned target and progress

| Property | Value |
| --- | --- |
| Target | Japanese `th075.exe` (ver1.11), supplied by the user |
| Size / image base | 2,576,384 bytes / `0x00400000` |
| SHA-256 | `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| MD5 | `21bcb855a39f2170195811e6ad292f18` |
| Source-present / exact functions | **967 / 967** |
| Accepted CODE bytes | **864,219** |
| Reviewed authored coverage | **43.79%** of 1,973,704 reviewed bytes |
| Conservative coverage | **43.71%**, with 3,420 origin-pending bytes included |
| Unresolved origins | **95** of 4,351 provisional function candidates |

**The 98% authored-byte goal is incomplete.** Function labels and C++ owner
types are provisional; machine-code matches alone do not prove an entire
original class layout. The target's official distribution provenance has not
been independently verified; do not substitute a localized `th075c.exe`.

These live snapshot counts were rechecked after **F750** (2026-10-30); the F694 storage cleanup and F689–F693 negative-evidence audit do **not** add accepted CODE.
The **live** sources of truth, not any dated prose milestone, are `config/functions.csv`,
`config/function-origins.csv`, and `config/match-units.toml`.
Refresh using `scripts/repo-python scripts/report-reconstruction-status.py --summary`.

The original authored backlog is **25 whole functions**: **22 large fighter
bosses** totaling **1,102,055 uncredited CODE bytes** (plus 16,123 distinct
after-RET switch DATA bytes), the 2,987-byte WinMain, 248-byte battle scene
destructor and 171-byte archive catalog destructor. **No giant is currently
accepted whole exact.** The 95 origin-unknown candidates are a separate
classification issue and cannot be silently counted as game-authored CODE.

The new [F735 authored six-leaf adoption](docs/THIN_AUTHORED_FORWARDERS_F735.md)
adds **six canonical cold-exact complete game functions (135 native CODE B)**,
with six authentic original call relocations checked and only the two
affected C++ objects freshly replayed. Existing exact units and
large-boss nonexact source remain intact.

The [F736 authored six-more-leaf adoption](docs/SMALL_AUTHORED_ORIGINAL_LEAVES_F736.md)
adds another **six original-authored entire cold-exact functions (302
native CODE bytes)** using just three newly compiled source objects.
Combined with F735, this turn recovered twelve new cold-exact
complete original functions (**437 authentic CODE bytes**), while
all older accepted units and nonexact giant source remain intact.

The new [F738 record-prefix original functions](docs/RECORD_PREFIX_WHOLE_EXACT_F738.md)
add **two more native exact complete authored functions, 117 original
CODE bytes**, with real original branch semantics checked and just
one fresh pinned VC7.1 source object cold-replayed. Latest giant
F737 source and its nonexact deep stack differences remain intact.

The [F739 native record-vector EH lifetime adoption](docs/RECORD_VECTOR_EH_EXACT_F739.md)
adds **four more entire canonical cold-exact game functions (312 native
CODE bytes)** under actual VC7.1 exception-handling member lifetime,
with four associated original EH stub and unwind data carriers
separately verified but not double-credited. New F739 units were
cold replayed from one source object without rebuilding all prior units.

The [F741 exact nested-record lifecycle](docs/NESTED_RECORD_WHOLE_EH_F741.md)
adds two more entire R209/R210 original-authored cold-exact
functions (**261 native CODE B**). Both external 40-byte EH stubs
and 52-byte unwind data records also match their original native
PE field ownership, but are not counted again as callable CODE.
New F741 replay rebuilt just one source object, not all earlier units.

The [F742 60-byte InputMapping initializer](docs/INPUT_MAPPING_INIT_NATIVE_F742.md)
is another pre-reviewed original-authored complete game-function
cold exact match. It adds one true native 60-byte body and three
physical original CALL relocs from only one VC7.1 source object;
the other 963 existing exact units were not cold-replayed.

The new [F745 exact native progress bit-clear function](docs/GAME_PROGRESS_CLEAR_UNLOCK_F745.md)
adds another original R212-authored **111-byte complete COLD-exact
function**, preserving native signed division/modulo, defined unsigned
masking and all 39 x86 instructions. Only the newly affected VC7.1
object was rebuilt; the older 964 accepted units remain untouched.

The [F746 BG05b native timer policy](docs/BACKGROUND_BG05B_TIMER_F746.md)
adds one canonical whole 94-byte R212-authored function, 32 original
x86 instructions and no relocation fields; only the new affected
source object was cold-replayed. The previously accepted exact units
and nonexact giant parent code remain unchanged.

The [F750 complete authored CharacterAux frame-refresh function](docs/CHARACTER_AUX_FRAME_SELECTION_F750.md)
adds another real original 101-B source and four genuine nested STL
callee fields via one new canonical cold-exact unit, without
recounting any library callee CODE. Only the new affected source
object was rebuilt and cold replayed.

### Latest verified giant research and complete small-function evidence

The one native giant `004EBDA0` now compiles from ordinary VC7.1 C++ into
the same **33,293 bytes of CODE, 8,789 x86 instructions in identical order,
and 438 after-RET DATA-layout bytes**. All **682 physical typed PE COFF
fields** and 198 original sparse-index bytes are independently checked.
Following F596's genuine C++ evaluation-order corrections, **30,866/31,003
nonrelocation bytes match**; **137 bytes in three register-allocation case
bodies remain wrong**. This is outstanding, **not a fully byte-exact
33K function**. Reproduce via
`scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py`.
F659's 14 additional whole-giant C++ condition/lifetime variants did
not reduce the genuine 137-byte register cycle; two `+=` alternatives
actually changed native x87 geometry. F690/F692 later compiled **28
more entire 33KB C++ variants**; none improved whole exactness, and
seven altered the actual x87 instruction geometry. F689 separately
tested ten complete Scene destructor variants; none resolved the EBP
slots and one deliberately artificial unused-aggregate form is
invalid for reconstruction.
[Current original 28+10 negative matrix](docs/CHARACTEROBJECT_SCENE_PHASE_NEGATIVES_F689_F693.md),
[prior F659/F660 evidence](docs/GIANT_REGISTER_AND_ARCHIVE_LIFETIME_NEGATIVES_F659_F660.md).

**F598–F681's 597 context-strict source-backed fighter *internal
case bodies* (162,036 original native CODE bytes) remain uncredited**:
none of their enclosing giant `Advance()` functions is fully exact.
F681 adds a **new strict full native terminal case `0x31B`** (74 x86,
248 original inner CODE B, 8 real typed call fields), while the
previously strict adjoining terminal `0x31C` (63 x86/219 B/7 fields)
remains exact in the **SAME fresh whole selected `00543210` parent**.
The real **`0x2F8` 928-byte/252-x86/23-field storm loop** C++ source
is newly recovered but remains **NONSTRICT** from genuine x87,
integer-loop EBP and GPR differences (904 emitted B). The actual
compiler receiver-save moved to **EBP−0xC** due the *real* source
loop index; a fresh verifier independently authenticates every
real `this` reload before comparison, without hiding its real
local/scratch differences. F678's earlier 31B-only trial had 43
GPR errors and regressed 31C by 36; restoring **both 2F8 and 31B**
removes their genuine terminal GPR errors. All previous 28 strict
case interiors, four EBP-negative cases and complete after-RET
DATA were rechecked in the new parent.
The selected giant now has **29 context-strict original native
cases /2,409 x86/8,334 real inner CODE B/222 typed PE/COFF fields**.
It remains whole-NONEXACT. [F681 actual saved-this and full-parent
native proof](docs/FIGHTER_STORM_TERMINAL_F681.md).
A **separate F684 full-parent source context** newly recovers the
entire original complex `0x2F9` angle/volley handler (**381 genuine
x86/1,367 original CODE B/34 physical typed fields**); normal C++
reproduces the original two projectile loops and `__ftol2` angle
conversion, but emits **1,319 B** with 16 real wide stack differences,
eight x87 evaluation-order positions and 236 wrong GPR/x87 roles:
**NONSTRICT**. The upstream source also makes previously strict
terminal 31B/31C **43/36 GPR roles nonexact in this other parent**,
while 27 preceding nonterminal strict cases and entire afterRET DATA
remain verified. Preserve both honest source contexts.
[F684 entire 2F9 native/source/real EBP negative](docs/FIGHTER_ANGLE_STORM_F684.md).
F676 previously added two large NONSTRICT 2F0/2F1 source bodies
(616 x86/2,146 B/65 typed fields) and made 31C context-strict.
F674 previously strictly proved `2EF` (224 x86/788 B/20 fields).
New F672 separately reconstructs **five entire genuine native
`0x259..0x25D` source cases** (434 x86/1,469 original CODE B/
42 real PE/COFF fields) in a selected full parent, with all 26
prior context-strict case interiors and separate after-RET data
rechecked. They remain deliberately **NONSTRICT** because 24 genuine
integer-to-float EBP local operands/widths differ from original.
[Full F672 original source and EBP-negative proof](docs/FIGHTER_EIGHT_SHOT_AND_FOLLOW_F672.md).
F673 earlier added the separate large `0x2BC` ground-wave case
(208 x86/692 original B/20 real fields).
F671 goes on to reconstruct the **much larger native `0x258`
502-byte, 134-x86, four-projectile case** with all 12 physical
original PE/COFF fields, but explicitly remains **NONSTRICT**:
eight original `MOV/FILD` stack temporary operands at EBP−0x114
through −0x120 compile at EBP−0x2C through −0x38, emitting
478 instead of 502 CODE bytes. The same fresh giant parent
preserves all 25 earlier strict case interiors and full after-RET
DATA. [Full complex F671 source/EBP negative proof](docs/FIGHTER_FOUR_SHOT_BARRAGE_F671.md).
The older F666 register-phase context dependency remains relevant.
A new **F666 preceding-source context control** subsequently added
normal C++ for four actual earlier actions `1FA/1FB/1FE/1FF` and
independently proved all **562 original x86 roles /1,942 original
internal CODE bytes /52 typed fields**, but their native GPR/EBP
roles remain NONSTRICT. Critically this source insertion also shifts
original GPR roles in formerly strict `200/201`; their F664 proof is
**context-dependent**, not a single exact historical whole parent.
[Full original negative phase-control evidence](docs/FIGHTER_PRECEDING_STAGE_PHASE_F666.md).
No fake local padding or partial whole-function CODE credit.
Native complex `0xCC` in `005AEEC0`
and `00564BE0` still has **80/78 genuine wrong GPR/CFG roles**
despite matching x86 count and all 11 real PE/COFF fields; **do not
promote** it to exact just because the case body geometry matches.

Separately, **whole-function** VC7.1 C++ probes now reproduce
**85 distinct historical origin-unknown complete original functions /
1,949 original native CODE bytes**, all uncredited pending actual
source ownership. New F691 completely reconstructs a substantial
original **249-byte COM resource cleanup / singly linked manager
unlink function `0061F125`**, proving **249/249 authentic linked CODE
bytes /104 whole x86 /five true zero-addend DIR32 import/global
fields** from ordinary pinned VC7.1 `/O1` C++. Its two native
stdcall COM slots, eight-element twin resource release loop and
actual global linked-list unlink are fully machine-byte identical;
original class/author provenance remains UNKNOWN.
[F691 full native COM manager source proof](docs/SDK_NATIVE_COM_MANAGER_CLEANUP_F691.md).
F687 earlier recovered two 58/64-byte original COM virtual owner
destructors, 122 linked native CODE bytes/49 x86/five typed fields.
[F687 earlier whole native proof](docs/SDK_NATIVE_COM_OWNER_DESTRUCTORS_F687.md).
All previously accepted 111-byte mapping transform `00455770`,
77-byte Shift-JIS classifier `0041CA30`, Replay render, StaffRoll,
rank-label and selected-progress functions stay accepted exact.
Do not revive their superseded negative experiments.

For the actual unresolved work, start with the
[short current agent handoff](docs/RE_HANDOFF.md); the full *former* [F598–F652 active-handoff research narrative](docs/history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md)
and still older [F540–F596 chronology](docs/history/RE_HANDOFF_F540_THROUGH_F596.md)
preserve the original experimental detail without cluttering the first
screen. Both are **frozen historical sources, not the live backlog**. Git commits preserve local checkpoints; they are
**not external Oracle acceptance**.

## Begin a new reconstruction session

**Read [the current agent handoff](docs/RE_HANDOFF.md) first.** It lists current
unresolved large functions, the latest accepted units, private research to
retain and the next experiments. Then follow
[AGENTS.md](AGENTS.md), [the reconstruction workflow](docs/RE_WORKFLOW.md)
and the [source-backed knowledge base](docs/KNOWLEDGE_BASE.md).

Inspect **all dirty work** before editing; do not discard it because an
earlier agent left it. Address both large/core functions and small helpers,
recheck old hypotheses against native instructions, and promptly commit
substantial accepted progress using `gpt-web: ...` subjects.
Preserve and continue all pre-existing dirty work; the user reports no other active reconstruction session.

From the repository root:

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/audit-active-handoff.py
scripts/repo-python scripts/ghidra.py check
```

Use the hash-checked `scripts/repo-python` wrapper, not arbitrary system
Python. For a new installation see `scripts/bootstrap-python.sh` and
`scripts/bootstrap-tools.sh`; **do not re-import or overwrite the
already initialized target/Ghidra project**.

## Complete-function matching

Full source and all relocations for each accepted function are registered
in `config/match-units.toml`. Reconstruct the genuine function, including
all exits and owned jump tables. `structural-exact` excludes relocation
fields and is **only diagnostic**. Acceptance requires an independent
pinned-compiler cold replay:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME
scripts/repo-python scripts/validate-tracking.py --require-target
git diff --check
```

For probes, use VC7.1 build 3077 with explicit per-unit flags, serialized
headless Wine processes and the existing tools. Do not manufacture byte
matches with copied target bytes, assembly, arbitrary padding, masks or
unproved owner layouts. Do not count external data or runtime helper bytes.
Keep the 95 unresolved origin candidates uncredited.

Keep validation focused on exact reconstruction: `scripts/ci.py` runs the small
comparison/checkpoint/byte-accounting suite without compiling accepted units.
Run it when that infrastructure or its tests change. Cold-replay only new or
affected units; routine acceptance and handoff need no additional suite.
Do not add a test file per function, duplicate source-text assertions, or
allocation-failure/null-pointer tests. Do not run the full historical suite.
Historical origin tests remain available for changes to
their evidence or verifiers. See [the workflow](docs/RE_WORKFLOW.md).

## Finding information

| Resource | Purpose |
| --- | --- |
| [Current handoff](docs/RE_HANDOFF.md) | Live status and next practical tasks |
| [Reconstruction workflow](docs/RE_WORKFLOW.md) | Step-by-step native analysis, VC7.1 matching, acceptance |
| [Knowledge base](docs/KNOWLEDGE_BASE.md) | Detailed F-series proofs, rejected attempts and limitations |
| [Build and matching guide](docs/BUILD_MATCHING.md) | Compiler profiles, COFF and cold-replay mechanics |
| [Ghidra MCP guide](docs/GHIDRA_MCP.md) | Headless project/bridge operation |
| [Origin review](docs/ORIGIN_PENDING_REVIEW.md) | 95 currently unclassified origins (R263 historical matrix) |
| [Frozen F598–F652 detailed handoff](docs/history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md) | Full old 1,500-line evidence narrative; **not** current backlog |
| [Historical detailed F540–F596 handoff](docs/history/RE_HANDOFF_F540_THROUGH_F596.md) | All previous milestone notes; **not** current backlog |
| [Earlier handoffs](docs/history/RE_HANDOFF_THROUGH_F183.md) | Older archived experiments |
| [Storage protection and recovery](docs/STORAGE_HYGIENE.md) | **F694: 1,760 older compiler PDB/CI logs preserved in two SHA256-indexed local archives; 133,952,872 bytes (127.75 MiB) net reclaimed**, with verified one-file restoration. Earlier 2026-10-29 lossless JSON/CI/PDB archives and Git GC are separately documented. **Private archives are ignored: do not discard them when moving the checkout.** Current source, original PE, VC7.1/Wine, Ghidra, H184 protected objects and accepted COFF artifacts were retained. |

The pre-cleanup verbose F223 handoff and README are also recoverable from
Git commit `ca81d72`; older origin work is retained under `docs/history/`,
`docs/RE_HANDOFF_HISTORY.md` and `docs/ORIGIN_REVIEW.md`. Private native
analysis, experiments and build objects are ignored by Git and must remain in
the **same workspace** when changing agents. Protect the `.analysis/vc71-wine`
tool environment, shared `.tools` installations and `ghidra-project`.

## Copyright and license

Repository code and documentation use the [MIT license](LICENSE).
The game, its data and supplied artwork retain their original rights. No
game executable, protected analysis database, downloaded toolchain or private
MCP endpoint is distributed with this repository.
