# TH075 function reconstruction rules

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
Preserve all accepted exact units and origin evidence through R268. The 97
unresolved origins remain unknown; they do not block reconstruction of
independently reviewed authored functions. Include all pending bytes in the conservative goal denominator.
Start with the live cohort in `docs/RE_HANDOFF.md`; historical experiments
must not override current evidence. **Only cold-replay new/affected units**,
never all units. Keep compiler builds serial. Remove only obsolete reproducible
outputs, preserving evidence, manifests, sources, inputs and shared tools.
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
- Names may remain provisional even when emitted bytes match. A partial class
  interface does not establish the complete object layout; do not instantiate or
  embed an incomplete reconstructed owner.

## Validation scope

Focus on complete-function exact reconstruction. Do not add allocation-failure,
null-pointer, fault-injection, or general robustness tests for each function.
Preserve any such branches actually present in the target; do not add defensive
behavior absent from the original.

Acceptance needs target/tracking checks and cold replay of only new or affected
units. Do not add per-function Python tests, duplicate native-byte or source-text
assertions, or hard-coded progress counts; use the canonical manifests and replay.
Run `scripts/ci.py` when changing exact-comparison, checkpoint, byte-accounting,
or test infrastructure. Routine function acceptance and handoff do not require
that suite or historical origin tests. Run an origin test only when its evidence
or verifier changes. Documentation-only changes need `git diff --check`.

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
- Keep private hypotheses/logs in `.analysis/`, objects in `build/`, and the
  private Ghidra project in `ghidra-project/`. A lossless SHA256-verified
  archive of regenerable historical probe `.pdb` files is under
  `.analysis/cache-archives/` with an inventory and restoration steps.
  Protect H184 frozen objects/PDBs, original native and best whole-boss
  probes, `build/matching/`, `.analysis/vc71-wine/` and the Ghidra project.
  Never commit game executables/data,
  archives, analysis databases, downloaded tools, generated decompiles, or secrets.
- Update the knowledge base and handoff after a bounded accepted function. Replay
  affected units after changing headers, ABI declarations, flags, or relocations.
  Follow the validation scope above and run `git diff --check` before handoff.
