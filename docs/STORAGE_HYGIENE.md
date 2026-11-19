# TH075 storage policy

Keep what is needed to continue reconstruction:

- Inputs: the pinned original resources/th075.exe, shared toolchain,
  game-specific .tools/wine/ prefix and ghidra-project/.
  .analysis/vc71-wine is a compatibility symlink to the same TH075 prefix.
- Current results: src/, active research sources in probes/, canonical
  exact/origin ledgers and evidence in config/, and scripts that cold-build
  and compare complete functions, owned extents and relocations.
- Useful knowledge: the live handoff, GIANTS.md, verified findings and failed
  approaches worth avoiding. Keep notes concise.
- Unresolved compiler contexts that would be costly to recreate: retain the
  selected parent and the relevant source snapshots, target observations and
  settings needed to investigate it.

The contents of build/ are disposable compiler outputs: COFF objects, PDBs,
origin/layout probes, matching intermediates and replay scratch. They are not
canonical evidence; scripts recreate the directories and outputs. Clear them
when no build or debugger is using them. Do not preserve old build products
merely because a document once linked to them.

The .analysis/ tree is mixed. Preserve current giant baselines, original-PE
observations, layout-tools, current Ghidra query context and private runtime
configuration. Remove superseded logs, batch lists, duplicate trial objects
and completed replay scratch when their findings have been summarized in
Markdown or the canonical ledgers. A document reference alone does not justify
retaining a file.

Shared .tools/ installations serve other repositories too; do not trim them
based only on TH075 usage. Preserve the game-specific Wine prefix and Ghidra
project. Keep binaries, tools, Wine prefixes, analyzer databases and generated
decompiles out of Git.

A fresh clone needs the private inputs/runtime separately. Exact acceptance
requires the affected unit's cold build and complete strict comparison, even
when an older object still exists. No deletion receipt or cleanup report is
required.
