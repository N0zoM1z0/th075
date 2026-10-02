# Repository Python environment

TH075 follows TH10's `scripts/repo-python` convention. Every repository Python
command uses this entry point, including Web MCP Bash commands and Python
child processes. The private interpreter lives in `.tools/python`; activating
a virtual environment is unnecessary.

## Setup

Install Python 3.12, then run from the repository root:

```bash
scripts/bootstrap-python.sh
scripts/repo-python scripts/verify-python-env.py
```

If Python 3.12 is installed outside the shell's search path, supply it during
setup:

```bash
TH075_BOOTSTRAP_PYTHON=/path/to/python3.12 scripts/bootstrap-python.sh
```

The bootstrap creates the private environment and installs the version-pinned
dependency from `config/python-requirements.txt`. The wrapper checks Python
3.12, the environment location, Capstone 5.0.6, and four SHA-256 identities
covering its bindings and native decoder before each command. A missing or
mismatched environment causes an error with no interpreter fallback.

## Local and Web commands

Use the same commands locally and through the MCP `run_command` tool:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/ci.py
```

The deployed MCP service starts commands in the repository root. Its
`GHIDRA_COMMAND` is the absolute path to `scripts/repo-python`, so the
`ghidra_call` tool also uses this environment. Concrete MCP request examples
are in [the deployment guide](GHIDRA_MCP.md#web-command-entry-point).

The wrapper can be invoked by absolute path from any directory. Script paths
and file arguments remain relative to the caller's working directory; use
absolute paths for them when working outside the repository.

Python runs in isolated mode (`-I`), which excludes shell `PYTHONPATH`, user
site packages, and the current directory from import lookup. Repository
scripts that need sibling modules add their known script directory explicitly.
Build, comparison, tracking, Ghidra, progress, and CI child processes invoke
the wrapper by absolute path and preserve that isolation.

## Verification

```bash
scripts/repo-python scripts/ci.py
scripts/repo-python scripts/test-public-mcp.py
```

CI includes a regression that places a conflicting `json.py` on shell
`PYTHONPATH` and launches the progress/status chain from an unrelated
directory. The public test repeats it through Funnel, verifies the Python
and decoder identities, attests the Ghidra project, and cold-builds an exact
function comparison through Bash. Public requests use the existing private
URL without authentication; the test keeps that URL out of routine output.
