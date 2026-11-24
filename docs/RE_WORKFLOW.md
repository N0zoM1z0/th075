# TH075 complete-function reconstruction workflow

> Current workflow: follow the **Highest priority** section in `AGENTS.md`.
> Prefer affected exact comparisons and useful Markdown knowledge. Ordinary
> notes do not require full CI, native replay or document-hash/pin refreshes.
> Older broad validation instructions apply only when their impact is relevant.


Use the [current handoff](RE_HANDOFF.md) for live priorities.
[GIANTS.md](GIANTS.md) indexes the accepted per-character `Advance`
units and their archived research. The status report and canonical
ledgers give the current authored backlog and separate pending origins.

Write source against the shared classes (`Actor`, `Fighter`,
`<Char>Fighter`, `CharacterObject`): name a member once in the layout instead
of using raw offsets, and check a method's vtable slot before naming it.

## 1. Start safely

Inspect Git and continue **all** pre-existing dirty work in scope.
The user explicitly reports **no other active sessions**. Inspect,
complete and commit pending source/config/evidence rather than avoiding it;
keep compiler builds serial and reuse existing private environments.

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/ghidra.py check
```

Use only the pinned user-supplied Japanese `th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
`th075c.exe` is a different binary. Always call
`scripts/repo-python` for Python so the pinned Capstone decoder is verified.
Do not re-import the existing Ghidra project or reset unpushed Git progress.

## 2. Audit the **entire** native function

Pick a real authored candidate from `config/functions.csv`, then cross-check
its `config/function-origins.csv` classification against native control flow
and library/compiler origin evidence. Keep pending origins out of
authored credit until independent evidence supports a decision.

Example read-only Ghidra CLI operations:

```bash
scripts/repo-python scripts/ghidra.py query .analysis/function.txt function 0x00401020
scripts/repo-python scripts/ghidra.py query .analysis/disassembly.txt disassemble 100 0x00401020
scripts/repo-python scripts/ghidra.py query .analysis/callers.txt callers 0x00401020
scripts/repo-python scripts/ghidra.py query .analysis/xrefs.txt xrefs_to 30 0x00671210
scripts/repo-python scripts/ghidra.py decompile .analysis/hypothesis.c 0x00401020
```

The MCP bridge exposes `check`, `function`, `decompile`,
`disassemble`, `callers`, `callees`, `xrefs_to`, `xrefs_from`,
`list_functions` and `search_strings`. Do not substitute a
decompile for native evidence. Decode every instruction and verify
function start, last RET, INT3, independent exits, switch tables,
actual imported addresses, signedness, and conditional order.
For CODE credit, exclude owned tables after RET; for comparisons,
include their full comparison extent and all table relocations.

Large functions must be investigated as whole functions; do not
crop difficult code to claim partial exactness. Observe actual
field offsets but do not invent complete source class ownership.

## 3. Experiment with natural C++ and real VC7.1

Write a complete, meaningful source probe under the ignored
`.analysis/` tree. Use the pinned **VC7.1 build 3077** and
**headless, serialized** Wine sessions:

```bash
env -u DISPLAY -u WAYLAND_DISPLAY \
  WINEDLLOVERRIDES='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d' \
  WINEPREFIX="$PWD/.analysis/vc71-wine" \
  scripts/compile-probe.sh .analysis/probe.cpp build/probes/Probe.obj \
    /Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src

scripts/repo-python scripts/compare-coff-function.py \
  build/probes/Probe.obj 'MANGLED_SYMBOL' 0x00401020 CODE_SIZE --json
```

Compiler flags are **per-function evidence**, not a universal recipe:
use `/GX` where the native EH lifetime needs it. Omit `/Gy` when testing
ordinary code without function packaging. VC7.1 ignores `/Gy-` with
warning D4002 and honors any earlier `/Gy`. Inspect the COFF sections
before drawing conclusions from linked order. Names, scopes,
integer signedness, `<` versus `<=`, dimensional array indexing,
object temporaries, new/delete lifetimes and pointer expression order
can change VC7.1 bytes. Reproduce native behavior naturally; do not
manufacture matches using assembly, target-byte grafts, arbitrary
padding, fake locals, false ABI types, cropping or masking.

A `structural-exact` preview compares only non-relocated bytes;
it does **not** qualify as accepted exact source. Analyze every
COFF relocation field (offset, type, symbol and resolved native
destination), including EH and local jump-table fields.

## 4. Adopt only **cold-exact** complete code

After proving the correct source, add a unit to
`config/match-units.toml`: source, compiler profile, output object,
mangled function, complete native target CODE size, optional
post-RET comparison size, and **every actual relocation**.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME
```

This builds a fresh object before comparing every required CODE and
relocation byte. A prior `build/probes` preview is not fresh cold
proof. Adopt only a `result=exact`, with no difference and with
authored origin already supported independently.

Update `config/functions.csv`, the source and exact ledgers, and
the progress card for the affected unit. Keep historical receipts
in Git and revise a live origin if new evidence overturns it. Cold
replay verifies the current source and its owned bytes. Authored
CODE credit comes from the accepted extent and independent provenance.

## 5. Validate, commit and hand off

```bash
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/update-progress.py
git diff --check
git status --short --branch
git add <reviewed-files>
git commit -m '<session prefix>: <specific verified work>'
```

Cold-replay only new or affected units, including dependents of changed shared
inputs. Run `scripts/ci.py` when changing exact-comparison, checkpoint,
byte-accounting, or test infrastructure. It runs basic syntax, ledger/manifest
and whitespace checks without compiler builds.
Run relevant tool tests explicitly when their implementation changes. Routine
function acceptance and handoff need no additional suite; ordinary probes need
only their direct comparison.
Run `scripts/check-origins.py NAME` only when origin evidence or a verifier
is affected, and `scripts/check-frontier.py` after editing a giant research
parent.
Do not add a Python test per accepted function or duplicate native bytes and
source text in assertions; the canonical manifests and cold replay cover these.
Do not add allocation-failure, null-pointer, fault-injection or general robustness
tests during exact reconstruction. Reproduce original failure branches when
present, without adding new defensive behavior. Documentation-only edits need
`git diff --check`.

After meaningful progress,
commit promptly, then update the **concise** active
`docs/RE_HANDOFF.md` and retain detailed proof notes in
`docs/KNOWLEDGE_BASE.md`. Restore no old no-goal directives from
archival docs. Git commits are local checkpoints, **not external
Oracle acceptance**. Never claim an unavailable push succeeded.

## 6. Retain what helps reconstruction

Keep the original PE, shared toolchain, game-specific Wine prefix and Ghidra
project; current source, exact/origin ledgers and complete comparison scripts;
and short notes on current blockers, verified findings and useful failed ideas.
Keep an unresolved compiler context separately only when it is costly to recreate.

Historical archives, repeated diagnostics, old trial outputs and cleanup reports
may be deleted together with their references. A past document link is not a
retention requirement. Cleanup needs no new archive, receipt or audit report.
See [storage policy](STORAGE_HYGIENE.md).
