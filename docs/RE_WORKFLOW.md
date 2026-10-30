# TH075 complete-function reconstruction workflow

**Current task:** continue both big/core functions and small leaves.
Do not use archived H184 no-active-goal instructions. Current priorities and
the handoff clean-state snapshot are in [RE_HANDOFF.md](RE_HANDOFF.md).
Historical documents and tentative Ghidra labels are **not proof**.

## 1. Start safely

Inspect Git and continue **all** pre-existing dirty work in scope.
The user explicitly reports **no other active sessions**. Inspect,
complete and commit pending source/config/evidence rather than avoiding it;
keep compiler builds serial and reuse existing private environments.

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/audit-active-handoff.py
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
and library/compiler origin evidence. The 95 origin-unknown functions remain
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
git diff --check
git status --short --branch
git add <reviewed-files>
git commit -m 'gpt-web: <specific verified work>'
```

Cold-replay only new or affected units, including dependents of changed shared
inputs. Run `scripts/ci.py` when changing exact-comparison, checkpoint,
byte-accounting, or test infrastructure. It needs no compiler builds. Routine
function acceptance and handoff need no additional suite; ordinary probes need
only their direct comparison.
Run a historical origin test only when its evidence or verifier is affected.
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

## 6. Keep evidence and save space **without losing it**

**F754 documented backlog correction:** the true author-origin backlog
was **36 complete unmatched authored functions** at F754 from
`config/function-origins.csv` (22 large + 14 small/medium); after F755, F758, F760, F765, F766, F769 and F770
the live queue is **29 (22 large + 7 small/medium)**, not the
25 `owner=authored` rows selected by the old active audit. The
[current handoff](RE_HANDOFF.md) contains the entire 7-function
small/medium queue, and the former 1,289-line F653–F753 handoff
is preserved [in frozen history](history/RE_HANDOFF_F653_THROUGH_F753_2026-10-30.md).
Use the updated `audit-active-handoff.py` to cross-check every address.

**F754 local storage recovery:** 1,931 generated old giant
f133–f166 `.asm/.cod/.log` traces were archived with independent
original-path SHA256s; net **86,614,259 bytes** saved. Original
source/COFF/PDB/JSON/current giant or exact units were not removed.
Restore only a needed original via `scripts/repo-python
scripts/archive-frozen-giant-traces.py --restore ORIGINAL_PATH` and
check the manifest with `--verify`. These tar+index files are
**local ignored evidence**, not present in a fresh Git clone.
See [STORAGE_HYGIENE.md](STORAGE_HYGIENE.md).

Preserve the pinned Japanese original PE, `.analysis/vc71-wine/` VC7.1
prefix, `ghidra-project/`, `.tools/`, all accepted source/config/manifest
and `build/matching/` objects, all original native/COFF/whole-function
evidence and meaningful negative C++ source experiments. **Never skip or
reset dirty work.** Repeated historical snapshots may be moved to
SHA256-verified, individually reversible archives; do not mistake old
ignored JSON backups for the frozen live adoption manifest.

On 2026-10-29, **135 old parent/adoption snapshots** (649,802,039 bytes)
were losslessly compacted to adjacent `.json.zst` archives (35,694,113
bytes), with SHA256 index under `.analysis/cache-archives/`. Restore one:

```bash
scripts/repo-python scripts/archive-historical-analysis.py --restore .analysis/f180-background-counters/parent-and-seed.json
```

A second **1,002 unprotected old probe PDBs** (71,393,280 bytes) were
losslessly archived to the SHA256-verified 2026-10-29 tar.gz batch; the
previous 2,031-PDB 2026-10-28 archive remains intact. Check the adjacent
per-file receipts before restoring. **All 15 H184-protected original
PDB/COFF pairs are still directly present and byte-verified; all
`build/probes/*.obj` are still present.** Only actual cold-replayed
new/changed units should ever rebuild. Full details and safe recovery:
[STORAGE_HYGIENE.md](STORAGE_HYGIENE.md). Another narrowly frozen,
original-SHA256-indexed **219 historical generated JSON diagnostics**
were compressed to four ignored tar.zst archives (≈244.66 MiB net
reclaimed); recover individual original scan/survey/whole-diagnostic
JSON paths via `scripts/repo-python scripts/archive-redundant-diagnostics.py
--restore .analysis/ORIGINAL_PATH.json` as documented there. The
historical F-series negative C++ sources and original boss
decompilations remain preserved.
