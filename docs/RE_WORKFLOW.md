# TH075 complete-function reconstruction workflow

**Current task:** continue both big/core functions and small leaves.
Do not use archived H184 no-active-goal instructions. Current priorities and
the handoff clean-state snapshot are in [RE_HANDOFF.md](RE_HANDOFF.md).
Historical documents and tentative Ghidra labels are **not proof**.

## 1. Start safely

Inspect Git, verify and continue all pre-existing dirty edits. The user
explicitly says no other session is active; never avoid or discard unfinished
work. Keep compiler builds serial and reuse the existing private environments.

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
and library/compiler origin evidence. The 97 origin-unknown functions remain
**uncredited**. A correct name or structural match does not prove authored
ownership.

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
use `/GX` where the native EH lifetime needs it. Names, scopes,
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

Update `config/functions.csv` (source/match state), then
`implemented.csv`, `matches.csv`, `reccmp-functions.csv`,
`known-symbols.csv`, `exact-adoptions.json`, the manifest
SHA256 in `tests/exact_checkpoint.py`, and the progress card.
Preserve original before/after ledger and origin entries and all
canonical source hashes. Do **not** count other callees, data,
CRT/SDK code, EH helpers, or functions with uncertain ownership.

## 5. Validate, commit and hand off

```bash
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/update-progress.py
scripts/repo-python scripts/ci.py
git diff --check
git status --short --branch
git add <reviewed-files>
git commit -m 'gpt-web: <specific verified work>'
```

Cold-replay only new or affected units, including dependents of changed shared
inputs. `scripts/ci.py` runs the small exact-comparison, checkpoint, and
byte-accounting suite without compiler builds. Run it at handoff or after
changing that infrastructure; ordinary probes need only their direct comparison.
Run a historical origin test only when its evidence or verifier is affected.
There is no requirement to run the full historical suite, add a Python test per
accepted function, or duplicate native bytes and source text in assertions.
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

## 6. Keep research evidence without clutter

Keep `.analysis/vc71-wine`, private Ghidra project, shared
`.tools`, accepted source/config/tests/manifest, original native
disassembly and best complete negative probes. Repeated failed
single-variable permutations can be compacted into a private
verified compressed source/log/results archive and a short result
summary; remove only **regenerable** probe objects. Do not delete
the H184 protected frozen objects or large-boss baselines.
The cleanups, active large targets and retention locations are
listed in [the handoff](RE_HANDOFF.md).
