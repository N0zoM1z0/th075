# Bash + Ghidra MCP deployment

The TH075 deployment follows TH095's user-systemd and Tailscale Funnel setup.
It has an independent bridge checkout, environment, unit, fixed public path,
and private Ghidra project.

| Setting | Value or location |
| --- | --- |
| User service | `th075-ghidra-bash-mcp.service` |
| Loopback listener | `127.0.0.1:8775` |
| Public transport | Tailscale Funnel, HTTPS 443, dedicated fixed path |
| Authentication | None; no Authorization header required |
| Private environment | `.tools/mcp_for_gptweb-ghidra/.env`, mode 600 |
| Service environment link | `~/.config/th075-ghidra-bash-mcp.env` |
| Unit source | `ops/th075-ghidra-bash-mcp.service` |
| Bridge version | `ghidra-bash`, commit `60e18377b558fb62451230a393cd6a37f947a3f9` |
| Tools | `run_command`, `ghidra_call` |

Clients POST Streamable HTTP MCP requests directly to the fixed private URL,
without authentication or an Authorization header. The exact URL is recorded
only in the private `.env` and `.analysis/deployment/public-smoke.json` receipt.
No Bearer token is configured. Actual endpoint paths are excluded from
repository documentation and routine test output.

The service is enabled and user lingering is already active. The WSL
distribution must be running for the Linux service to be reachable. The
`MCP_PATH` remains stable across service restarts; preserve the existing
`.env` rather than replacing it with the example.

## Service operations

```bash
systemctl --user status th075-ghidra-bash-mcp.service --no-pager
systemctl --user restart th075-ghidra-bash-mcp.service
systemctl --user is-active th075-ghidra-bash-mcp.service
systemctl --user is-enabled th075-ghidra-bash-mcp.service
```

The systemd unit loads `.env` through its dedicated environment link. Node does
not load this file itself. Installed tool binaries remain shared read-only;
all analysis state and build products belong to TH075.
The Ghidra command is the absolute path to `scripts/repo-python`; Bash Python
commands also use this wrapper. See [the Python/toolchain setup](BUILD_MATCHING.md).

## Funnel routing

```bash
scripts/configure-funnel.sh
```

The wrapper calls the pinned bridge's `configure-funnel.sh`, using
`tailscale funnel --bg --https=443 --set-path=...`. Because Tailscale strips the
mount prefix, the loopback proxy target includes the same `MCP_PATH`.
Only the TH075 handler is added; the six existing handlers are preserved.

Funnel setup output is retained privately at
`.analysis/deployment/funnel-setup.log`, since full status output contains
unrelated private endpoint paths.

## Public validation

```bash
scripts/repo-python scripts/test-public-mcp.py
```

The test resolves the hostname through Google public DNS, selects a global
IPv4 ingress, and uses `curl --resolve` with `--noproxy '*'`. TLS certificate
verification stays enabled. This avoids accidentally testing only a MagicDNS
tailnet address or loopback listener.

The latest no-auth public run passed 15 checks:

- Requests without an Authorization header return HTTP 200.
- An unrelated URL returns HTTP 404.
- MCP initialization negotiates a supported protocol.
- Tool discovery exposes exactly `run_command` and `ghidra_call`.
- Public Bash verifies the TH075 workspace and target hash.
- Public Bash uses the repository Python and four hash-pinned Capstone files.
- Nested Python calls ignore shell `PYTHONPATH`, including from another directory.
- Public Ghidra attests the independent project.
- A bounded function query reports the expected 27-byte extent.
- A bounded decompile returns the expected target function.
- Missing-function decompilation returns a tool error.
- Public Bash cold-builds and exactly replays the first function.
- GET returns HTTP 405 for the stateless POST endpoint without authentication.
- Bridge call scratch is cleaned up.
- Existing Funnel handlers remain unchanged.

After restarting the user service, public initialization and Bash workspace
verification uses the same private URL without authentication.

Every test request omits Authorization. Curl reads the private URL through
stdin configuration instead of process arguments. Temporary headers and
response files are removed; the private receipt records the URL and results.

Local bridge validation also passed type checking, all 55 bridge tests, and
the TypeScript build. The public function-workflow checks passed 18 regression
tests without depending on a game executable or private database.

## Web command entry point

Use `scripts/repo-python scripts/NAME.py ...` in public `run_command`
requests. The same pinned environment is used by Ghidra's workspace wrapper.
A complete 39-unit replay (eight cold objects, 6,810 bytes) also passed through
public Bash after the environment migration. The smoke test exercises failure
handling as well as successful reads and compilation.

For local reproduction without exposing the private endpoint in arguments:

```bash
scripts/repo-python scripts/public-mcp-client.py <<'JSON'
{"name":"ghidra_call","arguments":{"operation":"check"}}
JSON
```

The helper loads the private endpoint locally and uses verified public IPv4
HTTPS ingress. Keep the full endpoint out of tracked examples and receipts.
