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
python3 - "$repo_root/config/tools.lock.toml" "$compiler" <<'PY'
import hashlib
from pathlib import Path
import sys
import tomllib
with open(sys.argv[1], 'rb') as stream:
    expected = tomllib.load(stream)['msvc71']['compiler_sha256']
actual = hashlib.sha256(Path(sys.argv[2]).read_bytes()).hexdigest()
if actual != expected:
    raise SystemExit('compiler identity mismatch: ' + actual)
PY

mkdir -p "$(dirname -- "$output_path")"
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
