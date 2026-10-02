# Current function reconstruction handoff

Updated 2026-10-02. Scope is function reconstruction; the user explicitly
deferred subsequent phases. Write documentation and handoffs in English.

- Target: supplied Japanese `th075.exe`, reporting version 1.11, SHA-256
  `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
  Official distribution provenance is uncorroborated. Do not substitute the
  localized executable.
- Initial analysis completed in the separate TH075 Ghidra 12.1.3 project.
  There are 4,351 candidates, with 24 mapped, 24 source-present, and 24
  complete exact functions covering 2,987 bytes. The other 4,327 origins remain
  unclassified. Candidate count is not authored function count; regenerate
  statistics from the ledgers.
- Accepted F002: 22 shared graphics-state/frame functions plus the input error
  wrapper, adding 2,960 bytes. Complete jump tables and all 228 new relocations
  are included. Public MCP cold replay passed 24/24 units across three objects.
  See `KNOWLEDGE_BASE.md` for boundaries, ABI evidence, and unresolved names.
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
- Public HTTP smoke testing passed 14 checks through a global IPv4 ingress,
  including no-auth access, unrelated-path rejection, two-tool discovery,
  pinned Python/decoder verification, Bash verification, Ghidra
  check/query/decompile, failure rejection, scratch cleanup, and cold exact
  replay. All six earlier Funnel handlers were preserved. The service is
  enabled and user lingering is active. See `GHIDRA_MCP.md`.
  Public initialization and Bash workspace verification also passed after
  restarting the service, using the unchanged private URL without authentication.

Use `scripts/repo-python` for every Python command. The private Python 3.12
environment and Capstone 5.0.6 binding/native hashes are checked on each call.
The deployed Ghidra command uses this entry point; the endpoint and no-auth
settings stayed fixed. Public smoke testing passed after service restart.

The compiler/linker hashes and executable banners are checked by
`scripts/check-tools.py`; the SDK supplies D3D8/D3DX8 and DirectInput headers.
CLI and public Bash compiler calls share a compiler lock. The installed tools
remain shared read-only binaries; TH075 owns all objects and debug outputs.
TH105 was reviewed as an engine-structure reference: it uses VC8/LTCG and
D3D9, so retain TH075's proven VC7.1/D3D8 profile. See `REFERENCE_PROJECTS.md`
and `BUILD_MATCHING.md`.

Next bounded options: complete the resource lifetime family, or investigate
small input helpers before the larger drawing bodies at `0x004029F0` onward.
Deferred paired cleanup at `0x00401020..0x0040110E`, 239 bytes.
Review interface types, shared pointers, and loop bounds before writing a
natural source probe. The target saves one Release result into a local slot;
the reason is unknown. Do not invent an inert local merely to force emission.
This function has no source-presence or exact credit yet.

```bash
git status --short
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/check-tools.py
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/ci.py
scripts/repo-python scripts/test-public-mcp.py
```
