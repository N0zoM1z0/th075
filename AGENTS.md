# TH075 function reconstruction rules

## Highest priority: lightweight exact reconstruction and useful knowledge

These are the user's current workflow requirements. They override older
instructions that mandate broad CI, repeated preflights, document/source-pin
refreshes, per-checkpoint audits or extra workflow machinery. Preserve the
actual exactness, target identity, natural-source and state-isolation rules.

- Prioritize exact reconstruction and reusable knowledge. Use the shortest
  useful loop: inspect relevant state, analyze/edit, compile and compare the
  affected scope, retain useful learning, and create a coherent checkpoint.
- Use existing repository scripts and composable Bash. Add only the smallest
  change needed for an observed problem. Do not introduce a framework, schema,
  registry, state machine, generalized validator, test family or reporting
  process merely to make a local reconstruction task look more engineered.
- Documentation, knowledge and handoff edits require no compiler, analyzer,
  full CI, cold replay or receipt refresh. Inspect the diff. Check syntax only
  for machine-readable inputs actually changed.
- Source changes need the complete affected exact comparison, including its
  owned extents and relocations. Recheck known consumers of changed shared
  inputs. Tool changes need relevant positive/negative cases and a bounded
  real smoke. Run a broad suite only for an explicit request or a demonstrated
  impact that cannot be narrowed; state that reason first.
- Do not add tests or live freshness gates for prose hashes, prompt wording,
  progress totals, handoff source-SHA tables or ordinary source spelling.
  Bind exact evidence to executable inputs and relevant verification settings.
  Keep Git metadata as provenance. A document genuinely consumed by a build
  remains a build input. Never edit historical receipts to manufacture a pass.
  Do not pin SHA-256s of tracked sources, verifier scripts or canonical ledgers
  in tests or verifiers: exactness is the cold replay, origin evidence is the
  target-byte check, and Git records history. Hashes of the target PE and of
  frozen evidence JSON are fine.
- Plain Markdown is sufficient for knowledge: record the finding, applicable
  target/compiler/scope, evidence links, useful failed attempts and open
  questions. No mandatory JSON conversion, promotion workflow or test per note.
  Search relevant sections; do not read an entire large knowledge journal.
- Write documentation and knowledge in natural, fluent English. Lead with the
  concrete finding and connect the evidence and next action clearly. Remove
  filler, circular restatements, repeated conclusions and unnecessary jargon.
  Do not add defensive-claim boilerplate. State a real uncertainty or scope
  limit once when it changes a decision; do not repeat disclaimers about what
  a note does not prove, certify or authorize. Prefer a small useful note over
  an exhaustive report that is difficult to read.
- Keep handoff focused on current work, evidence references, blockers and the
  next useful action. Generate progress from canonical ledgers; avoid manual
  duplicate counts, recurring full reports and unrelated documentation chores.
- Preserve dirty/untracked work, targets, current research contexts, game-specific
  Wine prefixes and analyzer projects. Exactness still requires a complete strict
  comparison; knowledge and successful commands alone confer no exact credit.


Current scope is TH075 exact function reconstruction, including both
large/core functions and small helpers. Treat prior
documents, working hypotheses, and historical exact labels as testable leads,
not proof. Inspect dirty edits and continue unfinished investigations within the
assigned scope. The user reports **no other active sessions**: all dirty source,
config and local evidence is ours to inspect, preserve, finish and commit.
Never skip, reset or label it as another session's responsibility.
Commit substantial verified progress promptly with the session's requested prefix.
The 98% authored-byte objective remains incomplete; do not declare completion
without a verified build.

Use the existing Ghidra wrapper and local tools; do not use REA.
Preserve **all** accepted exact units and origin evidence, including
the historical R268 checkpoint and every later verified adoption. The 95
unresolved origins remain unknown; they do not block reconstruction of
independently reviewed authored functions. Include all pending bytes in the conservative goal denominator.
For the still-unmatched authored backlog, count provenance via
`config/function-origins.csv` (currently 22 = 22 giant + 0
small/medium), not by assuming every unknown candidate is authored.
The 11 independently authored, formerly owner-blank copy/audio/sprite
candidates have now all been accepted in F755–F780. Remaining origin-
unknown candidates require independent attribution; an exact source-
generated machine function does not itself prove authored ownership.
Start with the live cohort in `docs/RE_HANDOFF.md` and `docs/GIANTS.md`;
historical experiments must not override current evidence. The 22 remaining
authored functions are the slot-1 `Advance` methods of the 11 fighter and 11
object vtables. Thirteen have complete but nonexact research parents in
`probes/`; measure one with `scripts/repo-python scripts/measure-giant.py
ADDRESS`. Never count partial switch states as whole-function exact. Matching
branch destinations or external PE targets does not prove relocation offsets
or byte equality.
Never restart at obsolete F938 marker-only giant source. **Only cold-replay new/affected units**,
never all units. Keep compiler builds serial. Remove obsolete outputs, duplicate
evidence and historical archives; retain current source, canonical ledgers,
inputs, shared tools and useful findings.
Write repository documentation, comments, and handoffs in English. Preserve
original titles, filenames, and target strings where they are evidence.
Use `gpt-web: ...` for reconstruction commits unless the user specifies another prefix.
Use `scripts/repo-python` for repository Python commands, including public
MCP Bash requests. It checks the private environment and hash-pinned decoder;
do not replace it with a shell-dependent Python or silent fallback.

## Target and preflight

Use only the supplied Japanese `th075.exe`, self-reporting version 1.11:
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Its identity is pinned to the user's archive, not independently corroborated
against an official distribution. Never substitute `th075c.exe`.

At session start, read `docs/RE_HANDOFF.md` and `docs/RE_WORKFLOW.md`;
consult relevant `docs/KNOWLEDGE_BASE.md` entries and source. Before changing
reconstruction state, inspect `git status` and run from the repository root:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/ghidra.py check
```

## Function evidence and acceptance

- `config/functions.csv` contains provisional boundaries. Reconcile the full
  control flow, exits, switch tables, shared tails, and alignment before accepting
  an extent. Never truncate comparison to obtain a convenient match.
- `config/function-origins.csv` separates authored, compiler, library, and unknown
  ownership. Ghidra auto-analysis proves none of these classifications.
- `config/reccmp-functions.csv` records address/name mappings;
  `config/implemented.csv` records source presence only.
- `config/match-units.toml` records the exact source, COFF symbol, target extent,
  compiler flags, and every relocation. `config/matches.csv` accepts only a
  reproducible complete comparison with zero differences.
- Acceptance requires `scripts/repo-python scripts/replay-exact-units.py --unit NAME`.
  This cold-builds the object before comparing it. Direct comparison of an old
  object is diagnostic, not new acceptance evidence.
- A diagnostic `structural-exact` result excludes relocation fields and cannot
  earn exact credit. Never use mapped names, decompiles, or successful compilation
  as exact evidence.
- Keep target observations, compiler observations, inferences, and unknowns
  explicit. TH095 supplies methodology, not TH075 layouts or function meanings.
- Preserve truthful x86 ABI and natural C++ source. Do not paste decompiler
  output or target byte arrays into source. Do not add fake returns, inert locals,
  arbitrary padding, ABI misdeclarations, or assembly to force a comparison.
- Use one source body. Do not introduce `DIFFBUILD` or `TH075_MATCH_EXACT`
  conditional bodies/layouts. TH095's historical source splits and narrowly
  authorized assembly exceptions are not inherited here.
- Names may remain provisional even when emitted bytes match.
- Declare object layouts as shared named classes (for example one `Fighter`
  layout reused by every fighter method) with named members, and `unknownNNN[]`
  byte arrays for regions nobody has observed yet. Such gap members document the
  layout; they are not padding to force a comparison. Do not use raw
  `FIELD(type, offset)` / `reinterpret_cast<T*>((char*)this + 0xNNN)` access in
  new or edited source: name the member once in the shared layout instead.
  A layout whose total size is unproven must never be constructed, embedded by
  value or used with `sizeof`; access it only through the real `this` or a
  pointer the original code holds.

## Validation scope

Focus on complete-function exact reconstruction. Do not add allocation-failure,
null-pointer, fault-injection, or general robustness tests for each function.
Preserve any such branches actually present in the target; do not add defensive
behavior absent from the original.

Acceptance needs target/tracking checks and cold replay of only new or affected
units. Do not add per-function Python tests, duplicate native-byte or source-text
assertions, or hard-coded progress counts; use the canonical manifests and replay.
Run `scripts/ci.py` and the unit tests (`scripts/repo-python -m unittest
discover -s tests`, a few seconds) when changing exact-comparison, checkpoint,
byte-accounting or other shared tooling. Run `scripts/check-origins.py NAME`
when origin evidence or a verifier changes, and `scripts/check-frontier.py`
after editing a giant research parent. Routine function acceptance and handoff
need none of these. Documentation-only changes need `git diff --check`.

## Tools and working state

- Keep every operation headless. Unset `DISPLAY` and `WAYLAND_DISPLAY` for Wine/debugger
  processes and disable Wine graphical drivers for those processes; use CLI
  logs, batch debugging and the existing headless Ghidra wrapper. Preserve
  shared tool installations and the existing private service settings.

- Public MCP acceptance is not required; use local evidence and cold builds.
- Use `scripts/ghidra.py` or `.tools/mcp_for_gptweb-ghidra` for Ghidra access.
- Queries open the project read-only with analysis disabled. Never patch target
  bytes. Accepted database names/types/boundaries must be mirrored into ledgers
  and read back before relying on a database write.
  Do not re-import the existing project.
- The wrapper lock serializes CLI and bridge access to the private TH075
  project. Use one writable reconstruction session and serial compiler builds;
  do not delegate matching. Keep `config/claims.csv` header-only.
- Use pinned VC7.1 build 3077 with explicit per-unit flags; do not infer one
  executable-wide compiler profile.
- Shared `.tools/ghidra`, `.tools/jdk`, and `.tools/msvc710` installations are read-only.
- Preserve the existing private Funnel URL, fixed path and no-auth setting.
  Keep the URL out of tracked files, routine logs and process arguments.
- Keep private research in `.analysis/`, objects in `build/`, and the private
  Ghidra project in `ghidra-project/`. Preserve the original PE, shared tools,
  game-specific Wine prefix, current sources, exact/origin ledgers, complete
  comparison scripts and current unresolved compiler contexts that are costly
  to recreate. A document reference alone does not justify retaining a file.
- Delete historical archives, duplicate diagnostics, obsolete trial outputs
  and cleanup reports when they no longer help current reconstruction. Remove
  their documentation references too. No replacement archive, deletion receipt
  or cleanup audit is required. Record useful conclusions and failed approaches
  briefly in Markdown; exact credit comes from a reproducible complete comparison.
- Default `scripts/ci.py` checks syntax, tracking/build manifests and whitespace.
  Keep compiler replay and targeted tool tests explicit and scoped to the change.
  Documentation edits need only diff review and `git diff --check`.
- Never commit game executables/data, archives, analysis databases, downloaded
  tools, generated decompiles or secrets.
- Update the knowledge base and handoff after a bounded accepted function. Replay
  affected units after changing headers, ABI declarations, flags, or relocations.
  Follow the validation scope above and run `git diff --check` before handoff.

## Shared Factory runtime

Follow [the shared tools instructions](docs/SHARED_TOOLS.md). Ghidra/JDK and
Wine executables are shared through Factory; repository scripts also work
without MCP. Use `scripts/shared_runtime.py` and the existing compiler/analysis
frontends. Keep this game's prefix, analyzer project, Java home/cache, target
and compiler profile isolated. Do not install duplicate tools or inherit
another game's `WINEPREFIX`. This shared-runtime procedure supersedes older
per-repository installation instructions; pinned versions/hashes still apply.
