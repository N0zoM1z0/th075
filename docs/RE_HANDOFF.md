# Current function reconstruction handoff

Updated 2026-10-02. Scope is function reconstruction; the user explicitly
deferred subsequent phases. Write documentation and handoffs in English.

- Target: supplied Japanese `th075.exe`, reporting version 1.11, SHA-256
  `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
  Official distribution provenance is uncorroborated. Do not substitute the
  localized executable.
- Initial analysis completed in the separate TH075 Ghidra 12.1.3 project.
  There are 4,351 candidates, with one mapped, one source-present, and one
  complete exact function covering 27 bytes. The other 4,350 origins remain
  unclassified. Candidate count is not authored function count; regenerate
  statistics from the ledgers.
- Accepted F001: the reference-count constructor at `0x00401000`; see
  `KNOWLEDGE_BASE.md`. Its name and complete owner layout remain provisional.
  Both DIR32 relocations have been verified.
- Private symlinks reuse TH095 tool installations. The bridge checkout,
  target, project, configuration, and build products are independent. Bridge
  pin and machine configuration template live below `config/`.
- Ghidra queries require attestation and operation completion markers. CLI
  and bridge requests share a project lock. `inventory` exports only below
  `.analysis/inventory/`, preserving accepted ledgers.
- The public repository is `https://github.com/N0zoM1z0/th075`, on `main`.
  Commit subjects use `gpt-6.1-sol: ...`. Reference source files and protected
  working-tree files were not changed.
- The enabled `th075-ghidra-bash-mcp.service` listens on `127.0.0.1:8775` and
  is published through a dedicated Tailscale Funnel path on HTTPS 443.
  The user explicitly requested no authentication. Its fixed random path
  lives only in the private `.tools/mcp_for_gptweb-ghidra/.env` (mode 600);
  no Bearer token is configured or needed.
- Public HTTP smoke testing passed 13 checks through a global IPv4 ingress,
  including no-auth access, unrelated-path rejection, two-tool discovery, Bash verification, Ghidra
  check/query/decompile, failure rejection, scratch cleanup, and cold exact
  replay. All six earlier Funnel handlers were preserved. The service is
  enabled and user lingering is active. See `GHIDRA_MCP.md`.
  Public initialization and Bash workspace verification also passed after
  restarting the service, using the unchanged private URL without authentication.

Next bounded address: paired cleanup at `0x00401020..0x0040110E`, 239 bytes.
Review interface types, shared pointers, and loop bounds before writing a
natural source probe. The target saves one Release result into a local slot;
the reason is unknown. Do not invent an inert local merely to force emission.
This function has no source-presence or exact credit yet.

```bash
git status --short
python3 scripts/verify-target.py
python3 scripts/validate-tracking.py --require-target
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/ghidra.py check
python3 scripts/replay-exact-units.py --unit graphics-resource-client-constructor
python3 scripts/ci.py
python3 scripts/test-public-mcp.py
```
