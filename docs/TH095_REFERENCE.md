# TH095 reference investigation: function reconstruction

Reference: `/home/pentester/coding/codex_ida/th095-reconstruction/th095`.
The investigation covered `AGENTS.md`, README, the reconstruction workflow,
Ghidra attestation contract, compiler probes, COFF comparison, tracking
validation, and `.tools/mcp_for_gptweb-ghidra` source and tests.

## Reused methodology

| Layer | TH095 implementation | TH075 adaptation |
| --- | --- | --- |
| Target identity | `target.toml`, `verify-target.py` | Independent TH075 hashes, PE mapping, and entry point |
| Ghidra analysis | `ghidra.py`, four Java helpers | Separate TH075 project, attested on every request |
| GPT-web transport | Bash + read-only headless Ghidra HTTP MCP | Separate checkout pinned to the same bridge commit |
| Function inventory | Separate boundary and origin ledgers | 4,351 initial candidates, unknown/review by default |
| Source presence | Mapping and implemented ledgers | No automatic exact credit from decompilation or compilation |
| Compiler probes | Explicit VC7.1 flags | Same build 3077 probe compiler, profiles validated per function |
| Exact comparison | Complete COFF extents and explicit relocations | Cold rebuild and complete replay, with input digests |
| Session records | Knowledge base and short handoff | Independent F001 evidence and next bounded address |

The bridge is a transport layer. `run_command` executes Bash in the configured
workspace; `ghidra_call` serializes requests to the workspace attestation
script. It does not connect to a separate live Ghidra GUI MCP service. This
Bash + Ghidra MCP workflow uses attested headless operations.

## Bring-up adjustments

TH075's sample, initial analysis, and working state are independent of TH095;
only installed tool binaries are shared. Subsequent inventory exports go to
private scratch rather than overwriting reviewed names and boundaries. CLI and
bridge requests share a project lock, and logs stay below TH075 scratch.

Ghidra headless may return exit code zero after a post-script exception.
Queries, decompilation, and inventory export therefore require their own
completion markers in addition to target attestation. Missing functions and
failed decompilation reject the request rather than accepting partial output.

TH095's historical exact/normal source splits and assembly exceptions were not
carried over. TH075 match units use one source body, without a
`TH075_MATCH_EXACT` build macro.

## TH075-local observations

The supplied `th075.exe` reports version 1.11. The localized `th075c.exe` adds a
`.topo0` section and has a different identity. The Japanese target's `.text`
virtual size is 2,449,167 bytes, approximately four times TH095's.

Its PE linker version is 7.10. The Rich header contains predominantly build
3077 records, alongside several historical builds and build 4035 records.
This supports beginning with VC7.1 probes; it does not establish one compiler
version or profile for every function.

TH095 game classes, engine layouts, addresses, names, and exact-match results
are not TH075 evidence. Only its investigation and comparison workflow was
adapted; no TH095 game source was copied.
