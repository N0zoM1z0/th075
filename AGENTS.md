# TH075 function reconstruction rules

Current scope is TH075 function reconstruction, restarted by the user on
2026-10-27. Address both large/core functions and small helpers. Treat prior
documents, working hypotheses, and historical exact labels as testable leads,
not proof. Preserve and investigate any dirty edits; there is no other agent.
Commit substantial verified progress promptly, with subjects `gpt-web: ...`.
The former H184 handoff's no-active-goal instruction is historical and is
superseded by the current request. The earlier 98% authored-byte objective
remains incomplete; do not declare completion without a verified build.

Use the existing Ghidra wrapper and local tools; do not use REA.
Preserve all accepted exact units and origin evidence through R268. The 97
unresolved origins remain unknown; they do not block reconstruction of
independently reviewed authored functions. Include all pending bytes in the conservative goal denominator.
Start with the concise live handoff at `docs/RE_HANDOFF.md` (F228 as
of 2026-10-28); the old verbose snapshot lives in Git history at
`ca81d72:docs/RE_HANDOFF.md`. The knowledge base and origin journals
retain detailed old experiments and must not override current evidence.
Use the current cohort in `docs/RE_HANDOFF.md`. The user reiterated on
2026-10-28: **only cold-replay changed/affected units**, never run an all-unit
cold replay. Do not rebuild other accepted units without dependency changes. Keep
compiler builds serial and periodically remove only obsolete reproducible
outputs, preserving evidence, manifests, sources, inputs and shared tools.
Write repository documentation, comments, and handoffs in English. Preserve
original titles, filenames, and target strings where they are evidence.
Use the latest user-required commit subject format `gpt-web: ...` (2026-10-27).
Use `scripts/repo-python` for repository Python commands, including public
MCP Bash requests. It checks the private environment and hash-pinned decoder;
do not replace it with a shell-dependent Python or silent fallback.

## Target and preflight

Use only the supplied Japanese `th075.exe`, self-reporting version 1.11:
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Its identity is pinned to the user's archive, not independently corroborated
against an official distribution. Never substitute `th075c.exe`.

Before changing reconstruction state, read `docs/RE_HANDOFF.md`,
`docs/RE_WORKFLOW.md`, `docs/KNOWLEDGE_BASE.md`, and relevant source. Inspect
`git status`, then run from the repository root:

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

## Tools and working state

- The user required every operation to be headless on 2026-10-25. Never open
  host GUI windows. Unset `DISPLAY` and `WAYLAND_DISPLAY` for Wine/debugger
  processes and disable Wine graphical drivers for those processes; use CLI
  logs, batch debugging and the existing headless Ghidra wrapper. Preserve
  shared tool installations and the existing private service settings.

- On 2026-10-04 the user waived public MCP acceptance. Use local investigation
  and final verification while preserving complete evidence and cold builds.

- Use `scripts/ghidra.py` or `.tools/mcp_for_gptweb-ghidra` for Ghidra access.
  Every operation verifies the target, program identity, mapping samples, and
  attestation marker. Queries additionally require their own completion marker.
- Queries open the project read-only with analysis disabled. Never patch target
  bytes. Accepted database names/types/boundaries must be mirrored into ledgers
  and read back before relying on a database write.
- `inventory` exports to `.analysis/inventory/`; it does not overwrite accepted
  ledgers. Initial `import` is only for a new project and initial empty ledgers.
- The wrapper lock serializes CLI and bridge access to the private TH075
  project. Use one writable reconstruction session and serial compiler builds;
  do not delegate matching. Keep `config/claims.csv` header-only.
- The pinned VC7.1 probe compiler is build 3077. TH075's Rich header contains
  multiple historical builds; do not infer one executable-wide compiler profile.
  Flags are explicit per unit, including flags that are merely reproducibility
  settings rather than distinguishable target facts.
- `.tools/ghidra`, `.tools/jdk`, and `.tools/msvc710` currently refer to shared
  installations from TH095. Treat these shared tool installations as read-only.
  TH075 has its own bridge checkout, target, configuration, project, and outputs.
- The user explicitly selected no authentication for the existing private
  Funnel URL. Preserve that setting and the fixed random path. Keep the actual
  URL out of tracked files, documentation, routine logs, and process arguments.
- Keep private hypotheses/logs in `.analysis/`, objects in `build/`, and the
  private Ghidra project in `ghidra-project/`. Never commit game executables/data,
  archives, analysis databases, downloaded tools, generated decompiles, or secrets.
- Update the knowledge base and handoff after a bounded accepted function. Replay
  affected units after changing headers, ABI declarations, flags, or relocations.
  Run `scripts/repo-python scripts/ci.py` and `git diff --check` before handoff.
