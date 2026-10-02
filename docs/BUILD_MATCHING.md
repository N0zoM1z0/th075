# Compiler and function comparison setup

TH075 currently reconstructs functions into native i386 COFF objects. It does
not yet have a whole-program link graph or playable reconstructed executable.
The linker is installed and attested; function acceptance uses the compiler
and complete relocation-aware COFF comparison.

## Unified repository Python

Use `scripts/repo-python` for every repository Python command, including Web
MCP `run_command` requests. It runs the ignored `.tools/python` environment in
isolated mode, checks Python 3.12, and verifies Capstone 5.0.6's Python binding,
x86 binding/constants, and native library against four SHA-256 pins. It never
falls back to conda, a system decoder, PYTHONPATH, or user site-packages.
The installed patch version is currently 3.12.3; the supported interpreter
contract is the 3.12 series. Decoder bytes are pinned independently.

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

On this machine, the native tool installations are shared read-only symlinks
to TH095. Recreate those links and the independent bridge with:

```bash
scripts/bootstrap-tools.sh /path/to/th095
```

That helper requires an already installed TH095 tool tree. It does not install
or modify a shared compiler. The C/C++ frontends, optimizer, and PDB backend are also hash-pinned and
checked before compilation. Their installed files were compared with the
locked compiler repository commit. The compiler repository revision and tool archive
URLs/hashes are recorded in `config/tools.lock.toml`; downloaded binaries are
private operator inputs. Install Wine, winepath, Git, curl, Node/npm, and flock
before native work. The current bridge uses Node 22.19.0. The current exact
workflow does not require objdiff or reccmp executables; their reference pins
are retained as optional diagnostics.

TH105 is a useful engine reference, but its VC8/LTCG and D3D9 configuration is
not the TH075 compiler profile. TH075's accepted functions reproduce with VC7.1
and the per-unit profiles recorded in `config/match-units.toml`.

## Compile and accept

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/build.py --check
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

Replay clears each object's previous output and compiles each shared source
object once, serially, with its explicit unit profile. `compile-probe.sh` also
holds a compiler lock across Wine invocation/path conversion, so CLI and
public Bash compilations cannot launch VC7 concurrently. Keep the entire
reconstruction session single-writer; this compiler lock does not authorize
parallel source or ledger mutations.

Object/PDB outputs belong to `build/`; tool files and the Python environment
are ignored. Source and unit manifests belong to Git. Every relocation is
replayed, including switch dispatch/table labels. Same-section destinations
must agree with the freshly built COFF symbol offsets. A size mismatch or
unreviewed relocation prevents exact acceptance.

Public invocation uses the same entry point:

```bash
scripts/repo-python scripts/public-mcp-client.py <<'JSON'
{"name":"run_command","arguments":{"command":"scripts/repo-python scripts/replay-exact-units.py","timeout_ms":120000}}
JSON
```

The Ghidra bridge's private environment sets `GHIDRA_COMMAND` to the absolute
path of `scripts/repo-python`. Bash commands must explicitly use the wrapper;
the generic shell tool remains available for other authorized repository work.

Final gates are `scripts/repo-python scripts/ci.py`,
`scripts/repo-python scripts/update-progress.py --check`, and
`git diff --check`. These public checks need neither the game nor private tools
beyond the repository Python environment.
