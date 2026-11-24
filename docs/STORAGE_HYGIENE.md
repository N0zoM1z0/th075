# TH075 storage policy

Preserve the inputs and contexts needed to continue reconstruction:

- The pinned `resources/th075.exe`, tracked title-screen/progress assets,
  `src/`, `probes/`, canonical `config/` ledgers and repository scripts.
- Shared `.tools/` installations, the TH075-specific Wine prefix and
  `ghidra-project/`. Shared tools may serve other repositories; do not trim
  them based only on TH075 usage.
- Useful `.analysis/` contexts: complete-parent baselines, original-PE
  observations, current Ghidra query results, layout tools, origin research
  and private runtime settings. Do not delete `.analysis/` wholesale.
- Concise current findings and failed approaches in `docs/`; the canonical
  ledgers and Git history retain accepted state and tracked-source history.

Repository scripts can rebuild the exact-unit objects, PDBs and replay
scratch in `build/`. Clear obsolete output while the compiler and debugger
are idle. Preserve response files and any staged objects still consumed by
an open experiment. The pending-origin scripts in
`.analysis/final-origin-review/` use inputs from `build/probes/`.

The `.analysis/` tree is mixed. Remove session-local trial variants after the
winning source change and useful negative results have been recorded. Remove
completed replay scratch when the canonical ledgers already contain the
accepted result, superseded snapshots recoverable from Git history, and
byte-identical duplicate diagnostics. Before deleting any other research
file, check whether it is the only retained original-PE observation or
compiler context for an unresolved parent. A document reference alone does
not justify retaining a disposable output, but a valuable research context
should not be discarded just to make the directory smaller.

Keep binaries, tools, Wine prefixes, analyzer databases, generated decompiles
and secrets out of Git. A fresh clone requires private inputs/runtime
separately. Exact acceptance still requires a cold build and complete strict
comparison of the affected unit, even when an older object exists.
