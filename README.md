# 東方萃夢想 ～ Immaterial and Missing Power

<p align="center">
  <img src="resources/title-screen.png" width="640" alt="User-supplied TH075 title screen">
</p>

<p align="center">
  <img src="resources/progress.svg" alt="TH075 function reconstruction progress">
</p>

This project currently covers **function-level source reconstruction and byte
comparison**, using the Bash + Ghidra MCP workflow from TH095.

The target is the user-supplied Japanese `th075.exe`, which reports `ver1.11`:

| Property | Pinned value |
| --- | --- |
| File size | 2,576,384 bytes |
| SHA-256 | `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| MD5 | `21bcb855a39f2170195811e6ad292f18` |
| Image base | `0x00400000` |
| Entry point | `0x0064232C` |
| `.text` virtual extent | `0x00401000..0x00656F0E` |

This pins the supplied sample; its official distribution provenance has not
been independently corroborated. The localized `th075c.exe` has a different
identity and cannot substitute for the target.

The current checkpoint has **515 exact functions / 760,721 code bytes** from
4,351 provisional candidates. Reviewed authored coverage is 38.55%; conservative
coverage, including all 3,608 pending bytes, is **38.48%**. The objective of
98% authored bytes exact remains incomplete. At R268, 1,002 authored, 2,671
library and 581 compiler-generated candidates are classified; 97 remain unknown.
Unknown origins receive no exact credit. Candidate count does not establish
ownership, and original names and complete object layouts remain provisional.
Never construct or embed partial reconstructed owners.

On 2026-10-27 the user resumed reconstruction of both large/core functions
and small helpers. F184 cold-replayed two complete input policies: title menu
input (228 bytes/19 relocation fields) and replay menu input (310 bytes/27
fields). Both are recorded as exact in the current canonical ledgers, without
claiming the full original scene layouts. In F185 the 1,273-byte title-scene `Advance` core state machine was also
cold-replayed exact with its separate 40-byte owned jump table and all 76
actual relocations. No code-size credit is taken for the owned table.
In F186, another large menu state machine, `OptionsScene::AdvanceAt00428F00`
(951 code bytes), passed full canonical cold replay along with its 28-byte
owned seven-way jump table and all 70 COFF relocations. The first /Od
natural-source attempt emitted a 982-byte comparison extent, exposing a real
compiler type/operation distinction; a natural conditional toggle reproduced
the complete native 979-byte comparison.
F187 added 339 exact bytes for `GameConfig::SaveIni`, the configuration
file-writer reached from the options menu. The Win32 file operations, all
eleven writes, literal filename and 27 relocation fields were independently
checked, with a separate canonical cold-build.
F188 cold-reconstructed the options scene's text-resource update and its
complete VC7.1 exception-aware new/delete path (563 CODE bytes, 28-byte
owned switch table, 34 actual relocations). The font instance is represented
by an observed 56-byte ephemeral allocation carrier: complete source-level
member semantics and original class identity are **not** established.
F192 additionally cold-accepted only the independently authored 31-byte
scene-base cleanup destructor. The matching 34-byte paired constructor is
kept **uncredited** because its authored-versus-generated origin remains
unresolved (R108); a structural compiler preview alone does not prove
authorship.
F190 cold-reconstructed the 604-byte graphics default-state controller and
all 45 COFF relocation fields, including the original SDK D3D8 render/texture
state sequence, D3DX shader assembly and pixel shader constant setup. An
initial 603-byte variant was rejected before the native early-return branch
was restored. F189 was an unaccepted native analysis of the battle initializer;
F196 supersedes it with a complete 922-byte cold-replayed natural constructor,
without claiming the original nominal owner layouts.
F191 independently cold-replayed the complete 860-byte music-room selected
detail renderer, including its two texture updates, GDI glyph lifetimes,
signed-index bounds and 25 COFF fields. Only the function earns new authored
byte credit; the original complete music-scene/glyph object layouts and text
buffer declaration remain unproven.
F193 independently cold-reconstructed the complete 531-byte game-global
defaults initializer, including 71 actual relocation fields, 11 character
name copies, initial option/key mappings and the existing config.ini loader.
The paired scene-base constructor remains origin-unknown and uncredited.
F194 cold-reconstructed the complete 339-byte config.ini reader called
by F193 with all 27 import/data fields. Multiple genuine local-name/order
controls proved that correct code size alone does not ensure correct stack
references; the adopted natural-source read counter restores native EBP
assignments. No credits were granted for borrowed settings storage.
F195 cold-reconstructed the entire 358-byte global cleanup, retaining
virtual destruction of three borrowed game objects, three generated scalar
deleting destructor call targets, audio playback clearing and reference-count
gating without fabricating complete original owner layouts.
F196 independently cold-reconstructed the entire 922-byte
`BattleScene::Initialize` boss constructor, including all 40 actual
relocations, native /GX five-state exception frame, original
80/1/20/20-byte subobject allocations, and scene state initialization.
The physical allocation carriers are supported by real constructor
offsets; original nominal classes, unknown texture root word, vector
element types, compiler EH helper bytes and the base constructor's
R108 authored/generated ownership remain unproved/uncredited.
F197 independently repeated that base/texture-constructor structural
evidence in the 435-byte TitleScene initializer, with all 18 real
relocations and the two-state native EH policy cold exact. Original
class names and texture container element identities remain unknown.
F198 cold-reconstructed both authored TextureManager initialization
(177 bytes, five-state EH) and resource-slot allocation (128 bytes,
one-state EH). The real 80-byte member-construction order and 44-byte
meaningful temporary slot reproduced native VC7.1 code; all 20 actual
fields cold-replayed without masks or guessed external ownership.
F199 cold-reconstructed the full 434-byte texture-manager destructor,
including both resource vectors, repeated COM Release and all 23 native
relocation fields. The original code stores one COM reference count, and
capturing that real API return restores the exact native stack frame.
F201 additionally cold-reconstructed 904 bytes of the original game-state
snapshot writer, with all 131 relocations and four mode-specific paths,
after independently auditing and preserving its pending worktree edits.
Both routines were separately cold-replayed before adoption.
F202 cold-reconstructed the 880-byte game-state snapshot restoration,
independently replaying all 129 actual data/callee fields and full branches
against the original 904-byte F201 save path. The original complete record
class/storage layout is still unknown. An extra untracked alternative source
was investigated and preserved byte-for-byte privately without granting
duplicate credit.
F203 cold-reconstructed the whole 671-byte game progress selection
policy and both adjacent native five-entry switch tables (40 bytes).
All 711 compared bytes and 56 actual fields, including ten local
jump-table targets, matched. The original bitwise accumulator evaluation
order was established through rejected compound-assignment controls.
F204 cold-reconstructed the 318-byte music track selector from its actual
WAV path cases, audio queue and progress tracking, all 22 relocation fields.
A 132-byte buffer probe had the wrong stack offsets; 128 bytes reproduces
the observed 0x88 stack frame. F205 added the exact 27-byte transition
fade policy with one real call relocation. Neither unit assumes complete
original audio/record owners or counts imported data/code.
The 98% target is still incomplete.
See the [current reconstruction handoff](docs/RE_HANDOFF.md); the preceding H184
handoff is preserved there as historical context.

Private source/evidence stays local: preserve this workspace when
switching agents. Use the existing Ghidra wrapper and local tools without REA.
Every operation must remain headless. Commit subjects must use
`gpt-web: ...`; frequent commits and pushes remain authorized. Cold-replay
only new or affected units and keep compiler builds serial.

Full documents through F183 are preserved byte-for-byte in the
[recent handoff archive](docs/history/RE_HANDOFF_THROUGH_F183.md) and
[recent knowledge archive](docs/history/KNOWLEDGE_BASE_THROUGH_F183.md).
Their goal-state and next-task commands are historical; use the current handoff.

Complete documents through F148 are preserved in the
[handoff history](docs/history/RE_HANDOFF_THROUGH_F148.md) and
[knowledge history](docs/history/KNOWLEDGE_BASE_THROUGH_F148.md). Earlier
origin/reconstruction checkpoints remain in the
[older handoff archive](docs/RE_HANDOFF_HISTORY.md) and
[origin review journal](docs/ORIGIN_REVIEW.md). Start with the
[current handoff](docs/RE_HANDOFF.md) for accepted units, all active drafts,
local retention requirements and validation commands.

## Getting started

Use `scripts/repo-python` for repository Python commands and Web MCP Bash
requests. Bootstrap the isolated Python 3.12 environment with
`scripts/bootstrap-python.sh`; Capstone 5.0.6 bindings and its native decoder
are hash-checked before every invocation. No activation is needed.
Build, comparison, Ghidra, and CI scripts use this entry point for their Python
child processes as well, preserving the same isolated environment throughout.

Private symlinks currently reuse TH095's installed tool binaries. TH075 has
its own bridge checkout, Ghidra project, and output directories. Recreate the
tool environment with:

```bash
scripts/bootstrap-tools.sh /path/to/th095
scripts/repo-python scripts/import-target.py /path/to/th075.exe
```

`import-target.py` also accepts an executable path and imports only the pinned
hash. Game files are ignored by Git. Run `scripts/repo-python scripts/ghidra.py import` only
to create a new project and initial candidate ledgers. For the existing project,
use `check` instead of importing again.

Start each reconstruction session with:

```bash
scripts/repo-python scripts/check-tools.py
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/ghidra.py check
```

Cold-build and replay the first accepted function:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit graphics-resource-client-constructor
```

Replay only new or affected units during normal work; a complete replay is
available with `scripts/repo-python scripts/replay-exact-units.py` when required.
See [toolchain and matching details](docs/BUILD_MATCHING.md).
Run public checks with `scripts/repo-python scripts/ci.py`; these do not require the game
executable or private Ghidra project.

## Bash + Ghidra MCP

`.tools/mcp_for_gptweb-ghidra` is pinned to TH095's `ghidra-bash` bridge commit
`60e18377b558fb62451230a393cd6a37f947a3f9`. It exposes only `run_command` and
`ghidra_call`. Every Ghidra request passes through this repository's
`scripts/ghidra.py`.

The deployed user service uses its own fixed private Funnel URL on HTTPS 443,
loopback port 8775, and **no authentication**. Requests do not need an
Authorization header. The random path is stored in the ignored
`.tools/mcp_for_gptweb-ghidra/.env` with mode 600, not in repository documents.
Keep that file stable across restarts. The example is for a new deployment.

Operate and test the existing service with:

```bash
systemctl --user status th075-ghidra-bash-mcp.service --no-pager
systemctl --user restart th075-ghidra-bash-mcp.service
scripts/repo-python scripts/test-public-mcp.py
```

Public tests passed through a global IPv4 Funnel ingress with TLS validation,
including access without authentication, both tools, Ghidra attestation/decompilation, failed
request handling, scratch cleanup, and a cold exact function replay. The
service is enabled, user lingering is active, and all six existing Funnel
handlers were preserved. See [deployment details](docs/GHIDRA_MCP.md).

## Documentation and references

See the [function workflow](docs/RE_WORKFLOW.md),
[TH095 reference investigation](docs/TH095_REFERENCE.md),
[accepted evidence](docs/KNOWLEDGE_BASE.md), and
[current handoff](docs/RE_HANDOFF.md).

The [TH095 reconstruction](https://github.com/N0zoM1z0/th095) supplies the
Bash + Ghidra bridge and VC7.1 comparison workflow. The
[TH08 reconstruction](https://github.com/N0zoM1z0/th08) supplies additional
function-matching patterns. The
[TH105 reconstruction](https://github.com/N0zoM1z0/th105) provides a related
engine reference for rendering, input, and ownership investigations.
See the [reference comparison](docs/REFERENCE_PROJECTS.md).
Their source and engine layouts are supporting
references; acceptance depends on the pinned TH075 target.

Regenerate the progress card with `scripts/repo-python scripts/update-progress.py` after
updating the ledgers. The function-count bar includes all provisional candidates;
the authored-byte bar uses only the reviewed authored slice and stays marked
provisional until all origins are reviewed.

## License

Repository code and documentation are available under the [MIT license](LICENSE).
The game and the supplied title-screen artwork retain their original copyrights.
No game executable, game data archive, downloaded toolchain, analysis database,
or private MCP endpoint is distributed here.
