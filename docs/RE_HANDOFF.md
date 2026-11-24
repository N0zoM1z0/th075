# TH075 reconstruction handoff

The conservative authored-byte coverage exceeds 98%. All 22 character
fighter and object slot-1 `Advance` methods have accepted exact units.
The stage base constructor at `0x00449DE0` has a 45-byte exact unit.
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
stops at `LNK1120` with 393 unresolved externals. The readonly data batch
resolved 57 symbols using literals already present in the source.
All 353 bytes of the new definitions match their native destinations,
and 21 comparison units across 19 objects cold-replay exactly.

The replay writer batch
resolved 24 symbols and cold-replayed 56 units across 44 objects. Battle
state appends through the shared replay object and its four VC7.1 deques.
A headless archive consumer wrote two records and verified the payload,
file offsets, count, and queue cleanup.

The scene cleanup and
quad batch resolved seven symbols and cold-replayed 29 units across 20
objects. Options, results and title share the texture manager type from
construction through destruction. The loading, logo, capture, rank and
replay filename callers use the shared quad constructors.

The container and
storage batch resolved seven symbols and cold-replayed 20 units across
16 objects. The HUD and status views share the typed frame vectors, and
the direction-bit writer uses the typed input deque. The character loader
uses the same ten-byte roster for reads and writes. The coordinate
outputs have zero-initialized storage.

The selection and math
batch resolved eight symbols and cold-replayed 123 units across 36 objects.
Selection uses the SDK long absolute-value overload, the round banner
uses `log10f`, and the collision wrapper uses `ceilf`. Suika's projectile
calls use the shared fighter effect entry.

The result-list batch
resolved 20 symbols and cold-replayed 151 units across 80 objects. Both
card loaders, list rendering, and scene teardown use the same deque of
owned card names. Startup and resource selection share the eleven name rows.
An archive-linked headless smoke exercised the defaults constructor and
checked that it initialized all eleven rows.
Patchouli's projectile calls use the shared fighter effect entry.

The auxiliary effect batch resolved 35 symbols and cold-replayed 487 units
across 255 objects.
Both spawn entries create the 148-byte auxiliary object. Its five virtual
slots match, and frame binding and peer spawning use the shared effect
owner. Advance, prune and teardown use the two native deques. Mirrored
node rendering calls the shared scale and rotation methods.

The battle resource batch resolved 67 symbols.
The battle and ending scenes share the typed fighter input update.
Stage texture load, draw and teardown use the same texture manager.
The HUD binds the digit atlas to its initialized tables. Startup, stage
loading, battle transitions and rendering share the static effect owner.
Its CRT stubs, container lifetimes, pattern loader and side dispatch match.
A headless library consumer initialized the digit tables, released both
effect queues and exercised pattern and texture-owner teardown.

The character-loader batch resolved 38 symbols.
The loader allocates the eleven concrete fighter types at the native sizes.
All twenty slots match for each fighter table. The complete loader, both
switch tables and the constructor cleanup records match.

The fighter lifetime batch resolved 72 symbols.
The two Actor base constructors and Fighter use shared member layouts.
Both Actor tables, the Fighter base table, and all eleven character
deleting destructors match. Youmu clears its owned lists and the other
ten character destructors use the compiler-generated base call. A
headless library consumer exercised frame and sequence construction,
vector copying, pose reset, and cleanup.
Script parsing, field access and cleanup share the nested deques.
A headless consumer of the static library exercised all three with a
synthetic script and verified that missing IDs return an empty count.
Fighter slot 7 constructs the eleven typed character objects, and all
five slots match for their base and derived object tables.
Character effects, command selection, and mode 5 input call the shared
fighter methods. Fighter resource loads use the existing script stream
methods. Stage drawing, fighter texture loads, and the static effect
resources use the shared texture manager. Battle and results share
the score and flow state. The title menu,
replay browser and audio reader have their original startup values.
Projected drawing and camera snap share the existing read-only values.
The round-field writer uses the same signed declaration as its callers.
All fifteen scene allocations in WinMain call their constructors through
`SceneBase`-derived types. The replay browser uses three VC7.1 deques
for filenames, file headers and secondary mode bytes. Its virtual table,
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
the same owner as the four native deques. The append routine uses the
same queues and clears them after writing each record. Battle records
and selection use `GameProgress`, and rendering calls the existing
`Fighter` methods.
Stage loading and teardown share the active stage pointer with frame
updates and rendering. All 36 stage classes use their native allocation
sizes and share the base camera and texture members. The six-slot
virtual tables, deleting destructors and constructor unwind records match.
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
API. Transition, frame capture and opaque sprite drawing share the
SDK-backed RECT constructor. The loading and logo draw routines use the
same default quad constructor, transform and frame completion methods.
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
2. Reconcile the sprite history draw and remaining quad constructors
   with their native stack layouts. The auxiliary object's mirrored
   node slot uses the default quad constructor at `0x0040D990`.
   The encoded card loaders and replay writer also have existing
   implementations with outstanding caller bindings.
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
