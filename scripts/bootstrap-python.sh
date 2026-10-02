#!/usr/bin/env bash
set -euo pipefail
repo_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)
bootstrap_python=${TH075_BOOTSTRAP_PYTHON:-$(command -v python3.12 || command -v python3)}
"$bootstrap_python" -I -c 'import sys; assert sys.version_info[:2] == (3, 12), "Python 3.12 required; set TH075_BOOTSTRAP_PYTHON"'
mkdir -p "$repo_root/.tools"
repo_python="$repo_root/.tools/python/bin/python"
if [[ ! -x "$repo_python" ]]; then
  if command -v uv >/dev/null; then
    uv venv --python "$bootstrap_python" "$repo_root/.tools/python"
  else
    "$bootstrap_python" -I -m venv "$repo_root/.tools/python"
  fi
fi
if command -v uv >/dev/null; then
  uv pip install --python "$repo_python" --no-deps --only-binary :all: -r "$repo_root/config/python-requirements.txt"
else
  "$repo_python" -I -m pip install --disable-pip-version-check --no-deps --only-binary :all: -r "$repo_root/config/python-requirements.txt"
fi
"$repo_python" -I "$repo_root/scripts/verify-python-env.py"
