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

A clean build compiled all 441 translation units and linked a Windows
PE32 executable with an empty linker log. All 16 affected match units
passed complete comparisons on the freshly compiled objects. The linked
image matched all 47 supplied data ranges, and all 237 code references
resolved to the corresponding symbols.

The audio client and event-service destructors now bind the shared
`TerminateThread` import. Both units cold-replayed over their full extents,
and a strict relink used the refreshed objects.
[Import evidence](KNOWLEDGE_BASE.md#windows-link)

The ordinary and reverse-order Windows links both ran from the title
through character selection and back to title before exiting under
isolated Xvfb. Both layouts also loaded and rendered the first battle
with the installation's `replay/` directory staged. The command-history
matcher now uses the native iterator subtraction, and both layouts
completed 60 battle updates after the fix. The PI notes record which
symbols moved. With linker reference elimination disabled, both layouts
also verified all configured unit extents, 80 vtables and the C++
initializer array. Separate console probes round-tripped the same
configuration in both object orders.
[Windows position independence](POSITION_INDEPENDENCE.md)

The Japanese 1.11 reference and the normal executable both played the
same Coolier Youmu versus Marisa recording and returned to the replay
browser. The test added 12 zero bytes to expand the downloaded file's
header from `0x30` to `0x3C`. The record and its four input streams
were byte-identical. The battle phase, both positions, actions, and
health values agreed at all nine checkpoints through update 240.
Both runs used isolated Xvfb sessions. The local logs and checkpoint CSV
are under `build/program/external-replay/`.
[Coolier replay](https://coolier.net/th_up4/index.php?id=6736)

Four more Coolier recordings tested the normal link against the Japanese
1.11 executable. All four pairs returned to the replay browser at the
same update. The suite covered 28,417 battle updates per executable.
All 544 observations at battle entry, hit handlers and replay exit
agreed on the update counter, phase, timer, and both fighters' positions,
actions, animation state, health, spirit, and scores. The test adapted
only the replay headers as above. The local fixture hashes, traces and
comparison report are under `build/program/replay-suite/`.
[Coolier replay pack](https://coolier.net/th_up4/index.php?id=6739)

Earlier executable link work and compiler findings are indexed in the
[knowledge base](KNOWLEDGE_BASE.md#windows-link).

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
