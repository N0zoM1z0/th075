# Shared Factory tools

Ghidra, JDK and the Wine executable are provided by the common Factory
installation. This repository's compiler and Ghidra frontends use that runtime.
The local launcher works without Factory MCP or a network connection:

```bash
./scripts/shared_runtime.py --describe ghidra
./scripts/shared_runtime.py java -- -version
./scripts/shared_runtime.py --describe wine
./scripts/shared_runtime.py wine -- cmd /c ver
./scripts/shared_runtime.py winepath -- -w "$PWD/build/probe.obj"
```

Use the existing repository Ghidra script for its target checks and project
lock. Direct headless arguments can also be passed with
`./scripts/shared_runtime.py ghidra -- ...`. Keep the original locked tool
version; moving the installation does not authorize changing tool hashes.

The ignored `.tools/shared-runtimes.json` chooses the installed versions,
repository-owned Wine prefix and architecture. `.tools/ghidra`, `.tools/jdk`
and `.tools/factory-runtime.py` are local selectors. Factory's provisioner
refreshes them if its checkout moves. Do not copy a complete installation into
this repository or borrow another game's prefix/project. Consult Factory
`docs/shared-runtimes.md` for provisioning and sandbox mounts.

Java home, temporary files, settings and caches stay below this repository's
`.analysis/factory-runtime/ghidra`. The existing analyzer project, compiler
profile, target and exactness evidence stay here too. Wine's normal prefix is
selected from this repository's configuration, independently of an ambient
`WINEPREFIX`. An explicit local probe prefix can be selected with
`./scripts/shared_runtime.py --prefix .analysis/probe-prefix wine -- ...`.
External prefixes must be the exact legacy path configured for this game.
Do not use the operator's global Wine prefix. Factory rejects prefixes already
owned by another repository and serializes Wine launches within this game.
Use existing headless/Xvfb compiler wrappers where required. Historical
verifier recipes naming system Wine retain the same shared binary and their
recorded game-specific prefix/profile.

TH075 currently uses the 32-bit `.tools/wine` prefix. The legacy
`.analysis/vc71-wine` path links to it, so older local recipes use the same
TH075 state. Other games keep their own writable prefixes.

The private MCP bridge runs from `dist/` with production dependencies only.
Use its locked `npm ci --omit=dev --ignore-scripts` installation for runtime;
install development dependencies again only when rebuilding or testing the bridge.

Read-only source access to other registered games remains available through
Factory for cross-reference. Shared tools do not grant writes to their mutable
state. Ordinary analysis and source browsing do not require a full replay.
