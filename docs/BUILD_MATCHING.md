# Compiler and function comparison setup

VC7.1 compiles the reconstructed sources into i386 COFF objects.
`scripts/repo-python scripts/build.py --program` links them into a Windows
executable using a read-only data object from the supplied Japanese v1.11 PE.
Function acceptance uses a separate cold build and complete relocation-aware
COFF comparison. [Build and runtime evidence](RE_HANDOFF.md#windows-x86-build)

## Unified repository Python

Use `scripts/repo-python` for every repository Python command, including Web
MCP `run_command` requests. It runs the ignored `.tools/python` environment in
isolated mode, checks Python 3.12, and verifies Capstone 5.0.6's Python binding,
x86 binding/constants, and native library against four SHA-256 pins. It never
falls back to conda, a system decoder, PYTHONPATH, or user site-packages.
The Python 3.12 patch version can vary. Decoder bytes are pinned independently.

```bash
scripts/bootstrap-python.sh
scripts/repo-python scripts/verify-python-env.py
scripts/repo-python scripts/check-tools.py
```

Bootstrap needs Python 3.12 and either `uv` or the standard venv/pip tools.
`TH075_BOOTSTRAP_PYTHON=/path/to/python3.12` selects the creation interpreter.
No environment activation is required. The decoder wheel is installed from
the configured Python package index, then its actual binding/library files are
verified. Linux x86_64 is the pinned native-decoder platform. Repository checks
on GitHub also bootstrap and use this environment.

Python scripts also launch their Python children through the absolute
`scripts/repo-python` path. Reusing `sys.executable` alone would lose isolated
mode: a child could then import a shell's `PYTHONPATH` even though its parent
ignored it. A regression invokes the progress/status chain from an unrelated
directory with a conflicting `json` module on `PYTHONPATH`; both processes
must ignore that module. The public MCP smoke test runs the same regression.

This follows TH10's verified `repo-python` routing idea, with a single private
virtual environment for TH075. Capstone provides bounded disassembly; the
canonical byte comparator itself uses Python's standard library and PE bytes.

## Locked native tools

| Tool | Selected version | Identity / use |
| --- | --- | --- |
| VC7.1 compiler | 13.10.3077 | SHA-256 in `config/tools.lock.toml`; checked before each compilation |
| VC7.1 linker | 7.10.3077 | SHA-256 and executable version banner checked by `check-tools.py` |
| Platform SDK | Installed VC7 SDK | Win32, D3D8, D3DX8, DirectInput headers; emission verified by cold replay |
| Ghidra | 12.1.3 | Separate TH075 project; executable identity and mapped samples attested per request |
| Temurin JDK | 21.0.12.1+1 | Headless Ghidra runtime |
| Bash + Ghidra bridge | Commit `60e18377b558fb62451230a393cd6a37f947a3f9` | Independent TH075 checkout/build |

Use [the shared Factory runtime](SHARED_TOOLS.md) for Ghidra, JDK, Wine and
winepath. The matching and program builds select the read-only VC7.1
installation through `.tools/msvc710` or `TH075_MSVC71_ROOT`. They check
the compiler, C/C++ frontends, optimizer and PDB backend against
`config/tools.lock.toml`. That file also records the compiler repository
revision and tool archive identities. The MCP bridge is a separate checkout
for TH075. The objdiff and reccmp pins are available for optional diagnostics.

TH105 is a useful engine reference, but its VC8/LTCG and D3D9 configuration is
not the TH075 compiler profile. TH075's accepted functions reproduce with VC7.1
and the per-unit profiles recorded in `config/match-units.toml`.

## Compile and accept

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/build.py --check
scripts/repo-python scripts/replay-exact-units.py --unit text-overlay-set-raster-parameters-004135f0
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

Select the new or affected units. For several affected translation units,
pass `--batch` with repeated `--unit` flags to group compilations by profile.
Replay cold-compiles each shared source object once, serially, with its
explicit unit profile. `compile-probe.sh` also
holds a compiler lock across Wine invocation/path conversion, so CLI and
public Bash compilations cannot launch VC7 concurrently. Keep the entire
reconstruction session single-writer; this compiler lock does not authorize
parallel source or ledger mutations.

Object/PDB outputs belong to `build/`; tool files and the Python environment
are ignored. Source and unit manifests belong to Git. Every relocation is
replayed, including switch dispatch/table labels. Same-section destinations
must agree with the freshly built COFF symbol offsets. A size mismatch or
unreviewed relocation prevents exact acceptance.

The effect lifecycle source also owns exception handlers and unwind data
outside the callable bodies. Replay its three current authored units with:

```bash
env -u DISPLAY -u WAYLAND_DISPLAY WINEDLLOVERRIDES='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d' \
  scripts/repo-python scripts/replay-exact-units.py --batch --unit effect-initialize-four-deques-0045b920 --unit effect-destroy-owned-effects-0045b9b0 --unit effect-bind-fighter-0045ba10
```

The historical 24-section check in `verify-effect-lifecycle-exact.py`
belongs to the `Actor*` deque object at `5faf8087`. The current source
uses `CharacterObject*` and emits different COMDAT names. The three
authored bodies and their relocations still match the pinned game.

Public invocation uses the same entry point:

```bash
scripts/repo-python scripts/public-mcp-client.py <<'JSON'
{"name":"run_command","arguments":{"command":"scripts/repo-python scripts/replay-exact-units.py --unit text-overlay-set-raster-parameters-004135f0","timeout_ms":120000}}
JSON
```

The Ghidra bridge's private environment sets `GHIDRA_COMMAND` to the absolute
path of `scripts/repo-python`. Bash commands must explicitly use the wrapper;
the generic shell tool remains available for other authorized repository work.

Function acceptance needs target/tracking checks, cold replay of new or affected
units, and `git diff --check`. Run
`scripts/repo-python scripts/ci.py` only when changing exact-comparison,
checkpoint, byte-accounting, or test infrastructure. Its public checks need
neither the game nor private tools beyond the repository Python environment.
