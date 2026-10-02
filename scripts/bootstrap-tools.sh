#!/usr/bin/env bash
set -euo pipefail
repo_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
"$repo_root/scripts/bootstrap-python.sh"
reference_root=$(realpath -- "${1:-$repo_root/../../th095-reconstruction/th095}")
mkdir -p "$repo_root/.tools"

# Reuse only installed tool binaries. Target, ledgers, analysis projects, bridge
# checkout, configuration, and build products belong to this workspace.
for tool in ghidra jdk msvc710; do
  expected=$(realpath -- "$reference_root/.tools/$tool")
  destination="$repo_root/.tools/$tool"
  if [[ -e "$destination" || -L "$destination" ]]; then
    [[ $(realpath -- "$destination") == "$expected" ]] || {
      echo "refusing to replace existing tool: $destination" >&2
      exit 1
    }
  else
    ln -s -- "$expected" "$destination"
  fi
done

bridge="$repo_root/.tools/mcp_for_gptweb-ghidra"
bridge_commit=$("$repo_root/scripts/repo-python" - "$repo_root/config/tools.lock.toml" <<'PY'
import sys, tomllib
with open(sys.argv[1], 'rb') as stream:
    print(tomllib.load(stream)['bash_ghidra_mcp']['commit'])
PY
)
if [[ ! -e "$bridge" ]]; then
  git clone --local --no-hardlinks -- "$reference_root/.tools/mcp_for_gptweb-ghidra" "$bridge"
  git -C "$bridge" checkout --detach "$bridge_commit"
fi
[[ $(git -C "$bridge" rev-parse HEAD) == "$bridge_commit" ]] || {
  echo "MCP bridge commit differs from config/tools.lock.toml" >&2
  exit 1
}
[[ -z $(git -C "$bridge" status --porcelain --untracked-files=no) ]] || {
  echo "MCP bridge has modified tracked files; refusing dependency/build changes" >&2
  exit 1
}
"$repo_root/scripts/repo-python" - "$repo_root" <<'PY'
import hashlib
from pathlib import Path
import sys, tomllib
root = Path(sys.argv[1])
with (root/'config/tools.lock.toml').open('rb') as stream:
    locked = tomllib.load(stream)['msvc71']
for name, key in [('cl.exe', 'compiler_sha256'), ('link.exe', 'linker_sha256'),
                  ('c1.dll', 'c_frontend_sha256'), ('c1xx.dll', 'cpp_frontend_sha256'),
                  ('c2.dll', 'optimizer_sha256'), ('mspdb71.dll', 'pdb_backend_sha256')]:
    digest = hashlib.sha256((root/'.tools/msvc710/Vc7/bin'/name).read_bytes()).hexdigest()
    if digest != locked[key]:
        raise SystemExit('tool identity mismatch: ' + name)
print('Locked compiler/linker identities OK')
PY
cd -- "$bridge"
npm ci --ignore-scripts
npm run typecheck
npm test
npm run build
