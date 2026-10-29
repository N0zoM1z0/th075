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
| Source-present / exact functions | **943 / 943** |
| Accepted CODE bytes | **862,726** |
| Reviewed authored coverage | **43.71%** of 1,973,704 reviewed bytes |
| Conservative coverage | **43.64%**, with 3,420 origin-pending bytes included |
| Unresolved origins | **95** of 4,351 provisional function candidates |

**The 98% authored-byte goal is incomplete.** Function labels and C++ owner
types are provisional; machine-code matches alone do not prove an entire
original class layout. The target's official distribution provenance has not
been independently verified; do not substitute a localized `th075c.exe`.

These counts are the verified snapshot after **F555** (2026-10-29).
The full, constantly changing register of accepted units is
`config/functions.csv` and `config/match-units.toml`, **not** a long
manual list of batch IDs. For live counts run
`scripts/repo-python scripts/report-reconstruction-status.py --summary`.
Exactly **25** currently `owner=authored,status=unclassified` functions
remain: **22** original 28K–82K fighter action bosses, the **2,987-byte**
WinMain, **248-byte** SceneObject destructor and **171-byte** archive
nonvirtual destructor. The 111-byte coordinate mapping transform `00455770` is cold exact (F536), as is the separate 77-byte font Shift-JIS lead-byte classifier `0041CA30` (F555). The original owner names remain provisional. The old 303-byte Replay renderer, two 169-byte
rank labels, 208-byte StaffRoll and 92-byte progress counter are all
**already cold exact**; do not retry historical pending experiments.
The 22-boss original-only verifier records **1,102,055 uncredited CODE
bytes** and 16,123 uncredited post-RET switch DATA bytes. F537 also
[resolves 7,152 original action-ID entries](docs/FIGHTER_ACTION_CASE_RESOLUTION.md) and [F539 reproduces two natural giant switch-dispatch codegen shapes](docs/FIGHTER_SWITCH_CODEGEN_RECONSTRUCTION.md) and [F540/F541 recover and independently compile native action-zero C++ codegen across all eleven multi-switch giants](docs/FIGHTER_ACTIONZERO_FAMILY_CODEGEN.md)
and [F542 validates action-one C++ against eleven whole-giant originals](docs/FIGHTER_ACTIONONE_FAMILY_CODEGEN.md) and [F545 reproduces six real opening actions per multi-switch fighter](docs/FIGHTER_OPENING_SIX_CASES_CODEGEN.md) and [F547 recovers the full native 42-instruction action-nine source behavior](docs/FIGHTER_ACTIONNINE_FAMILY_CODEGEN.md) and [F548 compiles full 104-instruction action-six behavior for three giant fighters](docs/FIGHTER_ACTION_SIX_FAMILY_CODEGEN.md) and [F549 verifies separate 31-/20-instruction action-ten source families](docs/FIGHTER_ACTIONTEN_NATIVE_CPP.md) and [F551 completes action seven for three giant fighter bodies](docs/FIGHTER_ACTIONSEVEN_NATIVE_CPP.md) and [F553 restores role-specific action-eight C++ (including the missing flag-clear)](docs/FIGHTER_ACTIONEIGHT_NATIVE_CPP.md) and [F556 recovers complete 117-instruction extra-stage action 6/7 C++ in CharacterMove and a second giant](docs/FIGHTER_EXTRA_STAGE_SOURCE_F556.md) and [F557 verifies the 115-instruction no-flag stage variants (including a real 508-byte wide-stack case)](docs/FIGHTER_STAGE_NO_FLAG_F557.md) and [F558 verifies a third true action in CharacterMove and its 117-instruction sibling](docs/FIGHTER_EXTRA_STAGE_EIGHT_F558.md) and [F559 reproduces the native 458-byte wide-stack action-eight case in another giant](docs/FIGHTER_WIDE_ACTION_EIGHT_F559.md) and [F560 reconstructs precontact auxiliary action-eight logic in a 58K fighter boss](docs/FIGHTER_PRECONTACT_ACTION_EIGHT_F560.md) and [F562 models three true stage/motion actions in a separate 43K fighter boss](docs/FIGHTER_SPLIT_STAGE_F562.md) and [F563 reconstructs positive-FLAG secondary-motion cases across two additional giant fighter bosses](docs/FIGHTER_FLAG_OVERRIDE_SOURCE_F563.md) and [F564 integrates eleven real action cases into each whole fighter C++ switch](docs/FIGHTER_INTEGRATED_ELEVEN_CASES_F564.md) and [F565 recovers a distinct 96/83/83 native scripted-action family in another giant](docs/FIGHTER_SCRIPTED_STAGE_F565.md) and [F566 integrates all eleven original actions into the scripted giant C++ source](docs/FIGHTER_INTEGRATED_SCRIPTED_F566.md) and [F567 integrates real opening actions across all eleven multi-switch giant fighters](docs/FIGHTER_ALL_MULTISWITCH_INTEGRATION_F567.md) and [F569 reconstructs the original parent guards and compressed-dispatch source for eleven CharacterObject giants](docs/CHARACTEROBJECT_SINGLE_SWITCH_F569.md) and [F570/F571 audit genuine destructor local/object lifetimes without false exact credit](docs/DESTRUCTOR_LIFETIME_CONTROLS_F570_F571.md) and [F572 reconstructs ten genuine CharacterObject action bodies including three complete 271-instruction game policies](docs/CHARACTEROBJECT_FIRST_TEN_NATIVE_CASES_F572.md) and [F573 reconstructs a further complete 248-instruction CharacterObject x87 action with an explicitly verified read-only instruction swap](docs/CHARACTEROBJECT_X87_ACTION32A_F573.md) and [F574 reconstructs native FPU stage curve and collision effects in two more complete CharacterObject action bodies](docs/CHARACTEROBJECT_STAGE_CURVE_F574.md) and [F575 recovers two strict original CharacterObject fade actions with correct default-handler bounds](docs/CHARACTEROBJECT_FADE_ACTIONS_F575.md) and [F576 reconstructs two 274-instruction fire-state actions with native deep-frame spill widths explicitly explained](docs/CHARACTEROBJECT_FIRE_STATES_F576.md) and [F577 recovers the next complete 279-instruction CharacterObject direction reversal and original stack-width proof](docs/CHARACTEROBJECT_DIRECTION_REVERSAL_F577.md) and [F578 restores a further complete 269-instruction CharacterObject contact action and naturally eliminates an earlier six-byte source-frame width gap](docs/CHARACTEROBJECT_CONTACT_STAGE_F578.md) and [F579 recovers two more strictly matching native CharacterObject effect/fade action bodies](docs/CHARACTEROBJECT_FADE_SPAWNS_F579.md) and [F580 reconstructs four more fully matching native CharacterObject game-action bodies](docs/CHARACTEROBJECT_FOUR_ACTIONS_F580.md) through native switch tables and singleton branches; **no giant boss
is C++ exact yet**. See the [active handoff](docs/RE_HANDOFF.md), not outdated chronological notes.
Local Git commits preserve checkpoints; they are **not external Oracle
verification receipts**.

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
| [Historical handoffs](docs/history/RE_HANDOFF_THROUGH_F183.md) | Superseded records; not the current task list |
| [Storage protection and recovery](docs/STORAGE_HYGIENE.md) | SHA256-verified archive/restore of historical JSON snapshots and regenerable probe PDBs; protect Wine, original PE, COFF objects and current source |

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
