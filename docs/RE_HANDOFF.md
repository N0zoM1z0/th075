# TH075 reconstruction handoff

The conservative authored-byte coverage exceeds 98%. All 22 character
fighter and object slot-1 `Advance` methods have accepted exact units.
The authored stage base constructor at `0x00449DE0` still needs a
canonical source unit and a cold exact replay.
[Advance source and replay index](GIANTS.md) · [Stage constructor evidence](ORIGIN_PENDING_REVIEW.md#r305--stage-base-constructor-follows-the-deleting-destructors)

Use the ledgers for live counts and provenance.

    scripts/repo-python scripts/report-reconstruction-status.py --summary

The target is the user-supplied Japanese TH075 v1.11 `resources/th075.exe`
with SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The publisher's Japanese 1.11 patch yields the same executable.
[Target cross-check](ORIGIN_PENDING_REVIEW.md#r300--publisher-patch-reproduces-the-pinned-executable)

## Windows x86 build

Run `scripts/repo-python scripts/build.py --library` to compile the
configured translation units and archive them as `build/program/th075.lib`.
`--program` also passes the objects to the VC7.1 linker using the Windows
CRT startup. Both paths use the serial, headless Factory Wine runtime.
Compiler, librarian and strict linker logs are under `build/program/`.

All 441 configured sources compile and archive. The strict executable link
stops at `LNK1120` with 1,049 unresolved externals. All fifteen scene
allocations in WinMain call their existing constructors through
`SceneBase`-derived types. The replay browser uses three VC7.1 deques
for filenames, file headers and secondary mode bytes. Its latest
cold replay covered 11 units across eight objects. The virtual table,
deleting destructor and exception cleanup also match.
The character selection
constructor and destructor use the same three texture-manager members.
Startup, capture, drawing, and cleanup share the frame texture owner.
Startup sequences share five state variables and the existing character
and stage loaders. Battle state, configuration bytes and the event worker's
wait value use shared definitions. Selection, snapshots
and the battle loader share six player byte pairs and two fighter pointers.
Scene setup and teardown use those same pointers. Replay capture,
snapshot fields, the name screen, path selection and playback limits use
the same owner as the four native deques. The replay append routine still
needs the VC7.1 iterator stack layout. Battle records and selection use
`GameProgress`, and rendering calls the existing `Fighter` methods.
Stage pack loading uses the embedded texture manager at `+0x18`, and
battle scene teardown uses the same manager's deleting destructor. Stage
base construction and the complete stage virtual tables remain open.
The frame entry forwards the native status and the score callers share
the progress object.

Menu and results text use the same 56-byte GDI font surface. Startup,
rendering and teardown use the same 120-byte text overlay.

Input callers share the two 72-byte mappings. Stream loading and playback
share the VC7.1 deque of 64-byte audio records. Sound bank lifetime,
archive loading and playback share the 20-byte DirectSound buffer owner.
Music callers share the playback and fade entries.

Camera initialization, update, snap, and rendering share state. Scene
and sequence callers share the camera override and snap entries. The music, options,
results, and window constructors share the D3D8 texture allocator.
Transition dispatch and frame capture share the presentation callback
API. Transition and opaque sprite drawing share the SDK-backed RECT
constructor. The frame capture callback still needs its constructor
binding reconciled with the native stack layout.
The loading and logo draw routines use the same transform and frame
completion methods. Their default quad constructor has the same local
layout constraint.
Texture pack I/O, bitmap directories, drawing, and teardown share the
manager's three typed vectors. The bitmap codec and entry lifetime use
the same 44-byte entry storage. WinMain and the manager use the same
graphics client, and the manager uses the native four-byte deque layout.
Scene constructors and the results cleanup now call the shared manager.
Drawing callers use the same texture-manager state methods for blend,
depth, filtering, shader mode, and color scaling. Ordinary and projected
quad drawing and texture-rectangle lookup also share the manager. The
default and four-float quad constructors use the same SDK-backed layout.
Archive reading and writing use the same index list. Catalog close and
the event worker use the same deques as their corresponding startup
and insertion paths.
Headless library consumers exercised both camera snap modes, the log,
cosine table, sound defaults, configuration save and load, event queue
insertion and signaling, archive registration, lookup, a write/read round
trip, and handle release,
and the four corners produced by the RECT constructor.
Use `build/program/link.log` and the relocation targets to find candidate
definitions. Batch related exact units with `--batch` to compile each
profile together. Startup resource bindings and transitive scene
dependencies remain open.
The graphics and DirectInput error strings and pixel shader are also
unresolved.
[Startup bindings and toolchain notes](KNOWLEDGE_BASE.md#windows-link)

## Origin review

The live `review` rows are in `config/function-origins.csv`. Every pending
byte counts toward the conservative denominator. The original 51-candidate
pass remains incomplete. The current evidence table gives the conflicting
whole-function or linked-interval comparisons for each open address.
[Pending origins and evidence](ORIGIN_PENDING_REVIEW.md#r288--remaining-origin-evidence)

- VC7.1 build 3077 warns about `/G-` when given `/Gy-`. Omit `/Gy` to
  test unpackaged ordinary code. With that profile, the full Scene,
  SpriteHistory, Actor and texture intervals match with both implicit and
  explicit lifetime definitions. The SpriteHistory, Actor and two texture
  decisions were reopened. The old R304, R306 and R307 comparisons remain
  useful for their original packaged profiles.
  [Corrected flag controls](ORIGIN_PENDING_REVIEW.md#r314--omitting-function-packaging-restores-the-native-scene-order)
- BG00a still distinguishes the explicit base constructor under the
  corrected flag control. Its implicit constructor occupies the native
  base deleting wrapper slot. The script sequence and Fighter frame copy
  decisions also retain their complete comparisons with `/Gy` omitted.
  [Copy controls](ORIGIN_PENDING_REVIEW.md#r317--the-implicit-sequence-and-frame-copy-matches-survive-without-function-packaging)
- The shipped and patch packages yielded no matching symbols. The PE's
  RSDS record names `東方萃夢想.pdb`, GUID
  `9306058f-6d68-4650-b80b-1e0d05dd1e18`, age 3. A matching PDB, original
  link map or original build input could distinguish several alternatives
  that already reproduce their whole intervals.
  [Symbol witness search](ORIGIN_PENDING_REVIEW.md#r313--uncalled-functions-retain-byte-equal-linked-alternatives)

The historical full authored-origin verifier reports ledger/name-alias
mismatches. R314–R316 rechecked the affected scopes and reproduced the
same baseline discrepancies. Target-required tracking passes. Use the
scoped comparison for a new origin decision.
[Workflow](RE_WORKFLOW.md)

## Resuming work

1. Read [AGENTS.md](../AGENTS.md) and inspect Git and the target preflight.
   Use the existing headless Ghidra project and serialize compiler builds.
2. For the stage constructor, start from the R305 and R314 complete
   comparisons and the existing background layout. Verify consumers if the
   layout or declarations change. Adopt a new unit only after
   `scripts/repo-python scripts/replay-exact-units.py --unit NAME` passes.
3. For origin review, look for observations that distinguish the remaining
   byte-equal alternatives. Keep the origin and exactness ledgers separate.
   Replay commands and their dependencies are in the linked evidence notes.
4. Commit verified checkpoints locally with `gpt-6.2-sol: ...`. Git history
   retains accepted checkpoints and the former giant research baselines.

`.analysis/final-origin-review/` contains the retained sources and
scripts for the latest comparisons. Their staged linker inputs and outputs
are under `build/probes/`. Exact-unit build products can be regenerated
from the manifest. Preserve the pinned PE, the
game-specific Wine prefix, the analyzer project and the shared tools.
[Storage policy](STORAGE_HYGIENE.md)
