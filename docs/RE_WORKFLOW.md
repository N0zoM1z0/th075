# Function reconstruction workflow

Select one bounded address from `config/functions.csv`. Attest the target and
Ghidra project before investigating complete disassembly, callers, callees,
global accesses, strings, and bounded decompilation.

```bash
scripts/repo-python scripts/ghidra.py query .analysis/function.txt function 0x00401020
scripts/repo-python scripts/ghidra.py query .analysis/disassembly.txt disassemble 100 0x00401020
scripts/repo-python scripts/ghidra.py query .analysis/callers.txt callers 0x00401020
scripts/repo-python scripts/ghidra.py query .analysis/xrefs.txt xrefs_to 30 0x00671210
scripts/repo-python scripts/ghidra.py decompile .analysis/hypothesis.c 0x00401020
```

MCP's `ghidra_call` provides the same `check`, `decompile`, `function`,
`disassemble`, `callers`, `callees`, `xrefs_to`, `xrefs_from`, `list_functions`,
and `search_strings` operations. The bridge owns queuing, input bounds,
timeouts, and scratch cleanup; the workspace script owns target attestation.

Reconcile function boundaries against target bytes. Ghidra's candidate extent
can include tables, shared tails, or incorrect analysis. Classify authored,
compiler-generated, and library code separately. Consult `function-origins.csv`
and `ORIGIN_REVIEW.md` for the current reviewed set; an imported name is not
origin evidence. Record a durable origin batch before attempting exact credit.

After exact batches F008 and F009, the user resumed origin review on
2026-10-03. Preserve the 60-function exact baseline while reviewing bounded
candidate cohorts. R108 resolved one explicit destructor and retained five
complete explicit/implicit lifetime ambiguities. R109 resolved thirteen game
policies and exposed the six-callee R110 cohort recorded in `RE_HANDOFF.md`.
R110 resolved those dependencies through complete source-typed game loops;
R111 resolved complete erase graphs, related wrappers and necessary helpers.
The current bounded cohort is recorded in the handoff.
Scanner output is only a shortlist: accept each origin only after a durable
verifier freezes its complete extent, body, control flow and independent
ownership context. Run investigation and final acceptance locally. On
2026-10-04 the user waived public MCP acceptance to accelerate continued origin
review. Preserve complete evidence, necessary cold builds and required local
checks.
Recorded name aliases preserve earlier origin roles after exact reconstruction
renames a function; a matching ledger state does not invalidate its origin.
`report-reconstruction-status.py --summary` continues to report the incomplete
origin milestone and uses a provisional authored denominator while any origin
remains pending.

Form an ABI and behavior hypothesis, then write a small natural C++ probe below
`.analysis/probes/`. Compiler flags must be explicit:

```bash
scripts/compile-probe.sh .analysis/probes/example.cpp build/probes/example.obj /Od /Zi
scripts/repo-python scripts/compare-coff-function.py build/probes/example.obj SYMBOL ADDRESS SIZE --json
```

These flags illustrate invocation only. Diagnostic `structural-exact` excludes
relocation fields and cannot earn exact credit. Investigate every relocation's
symbol, type, offset, and target. Record the source, compiler profile, COFF
symbol, complete extent, and relocations in `config/match-units.toml`.

Accept a function only after:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME
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
