# Shared Factory tools

Ghidra, JDK and the Wine executable are provided by the common Factory
installation. This repository's compiler and Ghidra frontends use that runtime.
The local launcher works without Factory MCP or a network connection:

```bash
scripts/repo-python scripts/shared_runtime.py --describe ghidra
scripts/repo-python scripts/shared_runtime.py java -- -version
scripts/repo-python scripts/shared_runtime.py --describe wine
env -u DISPLAY -u WAYLAND_DISPLAY WINEDLLOVERRIDES='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d' \
  scripts/repo-python scripts/shared_runtime.py wine -- cmd /c ver
```

Use the existing repository Ghidra script for its target checks and project
lock. Direct headless arguments can also be passed with
`scripts/repo-python scripts/shared_runtime.py ghidra -- ...`. Keep the
locked tool version and hashes when moving the installation.

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
`scripts/repo-python scripts/shared_runtime.py --prefix .analysis/probe-prefix wine -- ...`
with the same headless Wine environment as above.
External prefixes must be the exact legacy path configured for this game.
Do not use the operator's global Wine prefix. Factory rejects prefixes already
owned by another repository and serializes Wine launches within this game.
The matching and program build frontends unset both display variables and
disable Wine's graphical drivers. Runtime replay checks have used a separate,
isolated Xvfb display for Direct3D.

TH075 currently uses the 32-bit `.tools/wine` prefix. The legacy
`.analysis/vc71-wine` path links to it, so older local recipes use the same
TH075 state. Other games keep their own writable prefixes.

The private MCP bridge runs from `dist/` with production dependencies only.
Use its locked `npm ci --omit=dev --ignore-scripts` installation for runtime;
install development dependencies again only when rebuilding or testing the bridge.

Read-only source access to other registered games remains available through
Factory for cross-reference. Shared tools do not grant writes to their mutable
state. Ordinary analysis and source browsing do not require a full replay.

## Wine setup for a standalone build

On a fresh TH075 clone, install 32-bit-capable Wine and bootstrap the
repository Python environment as shown in [Play on Windows](../README.md#play-on-windows).
The following commands attach the public Factory launcher and select a
dedicated TH075 prefix. Run them once from the TH075 checkout. If your
checkout is already provisioned, use its existing runtime configuration.

```bash
(
  set -eu
  test ! -e .tools/shared-runtimes.json
  factory="$PWD/../touhou-reconstruction-factory"
  if [ ! -d "$factory/.git" ]; then
    git clone https://github.com/N0zoM1z0/touhou-reconstruction-factory.git "$factory"
    git -C "$factory" checkout --detach 1a060dbd8de80b8afb0818615c0627dc019ae471
  fi

  wine_bin="$factory/.factory/shared-tools/wine/bin"
  mkdir -p "$wine_bin" .tools/factory-bin
  for tool in wine winepath wineserver; do
    test -x "/usr/bin/$tool"
    if [ ! -x "$wine_bin/$tool" ]; then
      ln -s "/usr/bin/$tool" "$wine_bin/$tool"
    fi
  done
  ln -s "$(realpath "$factory/runtime/run.py")" .tools/factory-runtime.py

  cat > .tools/factory-bin/launch <<'EOF'
#!/usr/bin/env bash
set -euo pipefail
repo_root=$(cd -- "$(dirname -- "$0")/../.." && pwd)
exec "$repo_root/scripts/repo-python" "$repo_root/scripts/shared_runtime.py" "${0##*/}" -- "$@"
EOF
  chmod +x .tools/factory-bin/launch
  ln -s launch .tools/factory-bin/wine
  ln -s launch .tools/factory-bin/winepath

  printf '{"schema_version":1,"repository_id":"th075","owner_token":"%s","wine_prefix":".tools/wine","wine_arch":"win32"}\n' \
    "$(cat /proc/sys/kernel/random/uuid)" > .tools/shared-runtimes.json
  scripts/repo-python scripts/shared_runtime.py --describe wine
)
```

This setup supports program builds and exact replay. For headless Ghidra
queries, provision the locked Ghidra and JDK installations through Factory.
[Factory provisioning](https://github.com/N0zoM1z0/touhou-reconstruction-factory/blob/main/docs/shared-runtimes.md)
