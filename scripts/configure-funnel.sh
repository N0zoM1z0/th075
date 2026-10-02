#!/usr/bin/env bash
set -euo pipefail
repo_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
bridge="$repo_root/.tools/mcp_for_gptweb-ghidra"
export ENV_FILE="${ENV_FILE:-$bridge/.env}"
mkdir -p "$repo_root/.analysis/deployment"
# The upstream status output includes unrelated private endpoints. Retain it
# locally, while leaving existing Funnel handlers untouched.
umask 077
bash "$bridge/scripts/configure-funnel.sh" > "$repo_root/.analysis/deployment/funnel-setup.log" 2>&1
echo "TH075 Funnel route configured; deployment log is private."
