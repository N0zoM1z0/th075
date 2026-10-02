# Function reconstruction workflow

Select one bounded address from `config/functions.csv`. Attest the target and
Ghidra project before investigating complete disassembly, callers, callees,
global accesses, strings, and bounded decompilation.

```bash
python3 scripts/ghidra.py query .analysis/function.txt function 0x00401020
python3 scripts/ghidra.py query .analysis/disassembly.txt disassemble 100 0x00401020
python3 scripts/ghidra.py query .analysis/callers.txt callers 0x00401020
python3 scripts/ghidra.py query .analysis/xrefs.txt xrefs_to 30 0x00671210
python3 scripts/ghidra.py decompile .analysis/hypothesis.c 0x00401020
```

MCP's `ghidra_call` provides the same `check`, `decompile`, `function`,
`disassemble`, `callers`, `callees`, `xrefs_to`, `xrefs_from`, `list_functions`,
and `search_strings` operations. The bridge owns queuing, input bounds,
timeouts, and scratch cleanup; the workspace script owns target attestation.

Reconcile function boundaries against target bytes. Ghidra's candidate extent
can include tables, shared tails, or incorrect analysis. Classify authored,
compiler-generated, and library code separately. Except for the first reviewed
function, the initial candidates remain unknown/review.

Form an ABI and behavior hypothesis, then write a small natural C++ probe below
`.analysis/probes/`. Compiler flags must be explicit:

```bash
scripts/compile-probe.sh .analysis/probes/example.cpp build/probes/example.obj /Od /Zi
python3 scripts/compare-coff-function.py build/probes/example.obj SYMBOL ADDRESS SIZE --json
```

These flags illustrate invocation only. Diagnostic `structural-exact` excludes
relocation fields and cannot earn exact credit. Investigate every relocation's
symbol, type, offset, and target. Record the source, compiler profile, COFF
symbol, complete extent, and relocations in `config/match-units.toml`.

Accept a function only after:

```bash
python3 scripts/replay-exact-units.py --unit UNIT_NAME
```

This cold-builds the object and compares all configured bytes. Reports are
written below `.analysis/replay/`. Only an `exact` result can be entered into
`matches.csv` and the function ledger's matching state. Naming, source presence,
successful compilation, and exactness are separate facts.

Record target observations, compiler observations, inferences, and unknowns in
`KNOWLEDGE_BASE.md`. Update `RE_HANDOFF.md`, validate tracking, and run public CI.
Replay affected accepted units after changing shared declarations or flags.

Queries open an existing project read-only with analysis disabled and verify
six distributed `.text` samples. Sampling detects wrong projects and changes
at sampled locations; it does not prove the entire database is unchanged.
Never modify target bytes. `inventory` writes fresh candidates only below
`.analysis/inventory/`, preserving accepted ledgers.
