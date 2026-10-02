#!/usr/bin/env bash
set -euo pipefail

repo_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
msvc_root=${TH075_MSVC71_ROOT:-"$repo_root/.tools/msvc710"}

if [[ $# -lt 3 ]]; then
  echo "usage: $0 SOURCE OUTPUT.obj MSVC_FLAG..." >&2
  echo "flags are mandatory because the original compile profile is not yet proven" >&2
  exit 2
fi

source_path=$1
output_path=$2
shift 2
compiler="$msvc_root/Vc7/bin/cl.exe"

if [[ ! -f "$compiler" ]]; then
  echo "missing pinned VC7.1 compiler; run scripts/bootstrap-tools.sh" >&2
  exit 1
fi
if [[ ! -f "$source_path" ]]; then
  echo "missing probe source: $source_path" >&2
  exit 1
fi

# A compiler path alone is insufficient: keep probes on the locked binary.
"$repo_root/scripts/repo-python" - "$repo_root/config/tools.lock.toml" "$compiler" <<'PY'
import hashlib
from pathlib import Path
import sys
import tomllib
with open(sys.argv[1], 'rb') as stream:
    locked = tomllib.load(stream)['msvc71']
directory = Path(sys.argv[2]).parent
for filename, key in [('cl.exe', 'compiler_sha256'), ('c1.dll', 'c_frontend_sha256'),
                      ('c1xx.dll', 'cpp_frontend_sha256'), ('c2.dll', 'optimizer_sha256'),
                      ('mspdb71.dll', 'pdb_backend_sha256')]:
    if hashlib.sha256((directory / filename).read_bytes()).hexdigest() != locked[key]:
        raise SystemExit('compiler component identity mismatch: ' + filename)
PY

mkdir -p "$(dirname -- "$output_path")"
# Serialize VC7/Wine invocations across CLI and simultaneous public Bash calls.
mkdir -p "$repo_root/.analysis/locks"
exec {compile_lock}>"$repo_root/.analysis/locks/compiler.lock"
flock "$compile_lock"
source_win=$(WINEDEBUG=-all winepath -w "$(realpath "$source_path")")
output_win=$(WINEDEBUG=-all winepath -w "$(realpath -m "$output_path")")
pdb_path="${output_path%.*}.pdb"
pdb_win=$(WINEDEBUG=-all winepath -w "$(realpath -m "$pdb_path")")
vc_include=$(WINEDEBUG=-all winepath -w "$msvc_root/Vc7/include")
sdk_include=$(WINEDEBUG=-all winepath -w "$msvc_root/Vc7/PlatformSDK/Include")
vc_lib=$(WINEDEBUG=-all winepath -w "$msvc_root/Vc7/lib")
sdk_lib=$(WINEDEBUG=-all winepath -w "$msvc_root/Vc7/PlatformSDK/Lib")

WINEDEBUG=-all \
INCLUDE="$vc_include;$sdk_include" \
LIB="$vc_lib;$sdk_lib" \
nice -n 15 wine "$compiler" /nologo /c "$@" "$source_win" "/Fo$output_win" "/Fd$pdb_win"
