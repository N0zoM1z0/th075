# TH075 reconstruction handoff

Every function currently classified as independently authored has accepted
exact coverage. That includes all 22 character fighter and object slot-1
`Advance` methods and the 45-byte stage base constructor at `0x00449DE0`.
[Advance source and replay index](GIANTS.md) · [Stage constructor evidence](ORIGIN_PENDING_REVIEW.md#r305--stage-base-constructor-follows-the-deleting-destructors)

Use the ledgers for live counts and provenance.

    scripts/repo-python scripts/report-reconstruction-status.py --summary

The target is the user-supplied Japanese TH075 v1.11 `resources/th075.exe`
with SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The publisher's Japanese 1.11 patch yields the same executable.
[Target cross-check](ORIGIN_PENDING_REVIEW.md#r300--publisher-patch-reproduces-the-pinned-executable)

## Semantic reconstruction

The [source map](../README.md#where-to-start) leads to shared battle,
input, replay, resource and renderer layouts. The [Advance index](GIANTS.md)
links to each playable fighter and object. The [knowledge base](KNOWLEDGE_BASE.md#layout-facts)
records the source evidence for names and native field layouts.

The shared-field review recovered the sprite history retention count, signed
vertical acceleration, body separation and opponent motion contributions,
and the conditional-hit count and combo window. The accepted comparisons
cover all affected units.
[Shared motion and conditional hits](KNOWLEDGE_BASE.md#shared-motion-and-conditional-hits)

The reviewed action-local slots in `CharacterObject` and
`CharacterAuxObject` can carry different values after a state transition.
Further naming should follow their producers and consumers in each action.
Keep the native action order and function extent when adding source navigation.

## Windows x86 build

Run `scripts/repo-python scripts/build.py --program` to build
`build/program/th075.exe` and its linker map. `--library` builds only the
COFF archive. Both paths compile serially with VC7.1 and use the headless
Factory Wine runtime. Compiler, librarian and linker logs are under
`build/program/`.

The link supplies 59 external names from 47 read-only data addresses in
the pinned Japanese PE. The build takes the float, double and
null-terminated string values from that supplied image and includes a
data-only COFF object in the archive and link. Names for the same address
share one object offset.

The normal and reversed retained links after the first semantic pass both
checked all configured units, 56,374 linked relocations, 80 vtables and
ten initializer pointers. Headless probes round-tripped five replay
files and the 90-byte playtest config byte for byte.
[Position independence](POSITION_INDEPENDENCE.md) · [Link evidence](KNOWLEDGE_BASE.md#windows-link)

The pre-semantic Windows build and the Japanese 1.11 original completed
four Coolier recordings with matching results at all 544 checkpoints
over 28,417 battle updates per executable. The playback fixture expands
the file header from `0x30` to `0x3C` with twelve zero bytes. The local
fixture hashes, logs and comparison are under `build/program/replay-suite/`.
[Coolier replay pack](https://coolier.net/th_up4/index.php?id=6739)

### Local 1P playtest

The local overlay in `build/program/playtest/1p-no-damage.patch` protects
the first fighter's health and recoverable health from hits, guard chip,
opponent gauge attacks, and Yuyuko's drain. It applies to staged copies
of four translation units. The playtest uses VC7.1 objects and a native
Windows link. The console probe checked both players' health and healing.
Use the normal executable for reference replay comparisons.

The playtest directory has its own 90-byte `config.ini`. The built-in 1P
bindings use Q to confirm and Y/N for menu movement. The playtest file
maps 1P to the arrow keys, Z/X/C/A and F11, and 2P to G/J/Y/N, Q/W/E/D
and F12. The native Windows console probe loaded the file with the game's
configuration reader and checked all 18 scan codes with the input mapper.

After the keyboard configuration was installed, the user reported playing
Arcade versus CPU for an extended session on Windows with the 1P no-damage
build and said it felt good to play. This was a manual playtest.

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
2. For origin review, look for observations that distinguish the remaining
   byte-equal alternatives. Replay commands and their dependencies are in
   the linked evidence notes.
3. Commit verified checkpoints locally with `gpt-6.2-sol: ...`. Git history
   retains accepted checkpoints and the former giant research baselines.

`.analysis/final-origin-review/` contains the retained sources and
scripts for the latest comparisons. Their staged linker inputs and outputs
are under `build/probes/`. Exact-unit build products can be regenerated
from the manifest. Preserve the pinned PE, the
game-specific Wine prefix, the analyzer project and the shared tools.
[Storage policy](STORAGE_HYGIENE.md)
