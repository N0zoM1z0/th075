# TH075 storage policy

Keep what is needed to continue reconstruction:

- Inputs: the pinned original `resources/th075.exe`, shared toolchain,
  game-specific `.analysis/vc71-wine/` prefix and `ghidra-project/`.
- Current results: `src/`, active research sources in `probes/`, canonical
  exact/origin ledgers in `config/`, and scripts that cold-build and compare
  complete functions, owned extents and relocations.
- Useful knowledge: current blockers, verified findings and failed approaches
  worth avoiding. Keep notes concise and start from [the handoff](RE_HANDOFF.md).
- Unresolved compiler contexts that would be costly to recreate: retain only
  the selected parent and relevant inputs/settings needed to investigate it.

Historical archives, duplicate evidence, old trial outputs, generated build
products and cleanup reports may be deleted when no longer useful. Remove
obsolete references at the same time. A document link is not a reason to keep
an artifact. No replacement archive, deletion receipt or cleanup report is needed.

Preserve unfinished work and private runtime settings. Keep binaries, tools,
Wine prefixes and analyzer databases out of Git. A fresh clone needs the private
inputs/runtime separately. Exact acceptance requires the affected unit's cold
build and complete strict comparison, even when an older object still exists.
