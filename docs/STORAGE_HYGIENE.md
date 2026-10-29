# TH075 local storage hygiene and lossless recovery

**Updated 2026-10-29, after F597 maintenance.** This is a storage
report and recovery recipe, **not** permission to remove original
PE/C++/COFF evidence or skip dirty work. Archives and per-file
SHA256 receipts are under **Git-ignored** `.analysis/cache-archives/`
(local to this worktree). Their **restoration tools and instructions
are tracked in Git**; new Git clones do not automatically receive
those local archives. Historical JSON/PDB batches and the new F597
legacy CI-log batch were archived separately without touching
source, original-function evidence, Wine or accepted build objects.

## What was compacted, with independently verified bytes

| Batch | Files safely archived | Original file bytes | Packed bytes | Storage reclaimed |
| --- | ---: | ---: | ---: | ---: |
| Old parent/adoption JSON snapshots, 2026-10-29 | **135** | **649,802,039** | **35,694,113** | **614,107,926** |
| Unprotected old compiler-probe PDBs, 2026-10-29 | **1,002** | **71,393,280** | **7,298,260** | **63,919,095** net including receipt |
| **Earlier JSON/PDB batches** | **1,137** | **721,195,319** | **42,992,373** | **≈ 647 MiB** after receipts/index overhead |
| **F597 old CI logs (F001–F300 only)** | **243** | **108,699,966** | **13,829,049** | **94,834,471 bytes net** after 36,446-byte receipt (**≈ 90.4 MiB**) |

The pre-existing **2026-10-28** verified PDB archive and its original
receipts are **still present** and were **not** removed or overwritten.
That earlier archive contains **2,031** older unprotected PDBs
(`.analysis/cache-archives/probe-pdb-unprotected-2026-10-28.tar.gz`).

Each of the **135** historical JSON files was compressed *individually* to
`original-name.json.zst`. The archive script first computed the real original
SHA256, decompressed the newly written archive in a fresh read, checked its
size and original SHA256, then wrote an **atomic durable archive receipt**
**before** removing the original plain JSON. For lossless recovery and audit,
`.analysis/cache-archives/snapshot-compaction-index.json` records original
path, original bytes, SHA256, compressed path, compressed bytes and compressed
SHA256. This manifest is intentionally local/ignored, just like its archives;
**a fresh Git clone does not automatically receive old local analyses**.

The PDB batch was archived using the same conservative procedure already
employed on 2026-10-28: complete tar.gz archive, then independently read back
**all 1,002 tar members and their per-file SHA256 hashes**, and only then
remove the old loose PDBs. The complete per-file receipt is
`.analysis/cache-archives/probe-pdb-unprotected-2026-10-29-receipt.json`.
The 2026-10-29 tar archive SHA256 is
`a67cfcc66dbb8ac2cc990fd95a962d6e3a9eb923b24603d23ed4ad91ab3c446d`.

## F597: verified recovery for redundant early CI logs

**Actual cleanup performed:** 243 frozen pre-F301 historical CI
**output logs** (`.analysis/fNNN-ci*.log` or
`.analysis/fNNN-*/ci*.log`) originally occupied **108,699,966
bytes**. They were bundled into the lossless local archive
`.analysis/cache-archives/legacy-ci-logs-pre-f301.tar.gz` of
**13,829,049 bytes**, with a **36,446-byte** per-file
SHA256/size/original-path receipt at
`.analysis/cache-archives/legacy-ci-logs-pre-f301-receipt.json`.
The verified archive SHA256 is
`72c3ff90479af3377bafaabb71ec1280e966eab598a301971aada122cf558b46`.
Net storage reclaimed **94,834,471 bytes (≈90.4 MiB)**.

The archiver **independently unpacked/read and SHA256-verified all
243 original tar members before deleting any loose file**, then
verified the entire tar again after removing the originals. We
also **successfully restored an individual historical file**
`.analysis/f179-ci.log` (**544,204 bytes**, SHA256
`b5026befd9ce6a04a93d5164466007eea9ee45df60c1c2273bc976ee9b868386`),
verified exact original bytes and returned that tested loose copy to
the archive after the smoke test. No historical evidence bytes were
lost; only loose duplicate representations were removed.

```bash
# Read-only plan: excludes F301+ fresh research, H184 protected work,
# the compiler, current Ghidra/source/probes and all COFF/PDB/JSON.
scripts/repo-python scripts/archive-legacy-ci-logs.py --plan

# Verify all 243 archived original members by size and SHA256:
scripts/repo-python scripts/archive-legacy-ci-logs.py --verify

# Restore one known file on demand (never overwrites changed bytes):
scripts/repo-python scripts/archive-legacy-ci-logs.py \
  --restore .analysis/f179-ci.log

# `--archive` was used once and deliberately refuses overwrite/re-run
# against an existing historical archive + signed receipt.
```

This cleanup **does not** cover the original PE, `.analysis/vc71-wine/`,
`.analysis/f493-reimu-megaboss/`,
`.analysis/f509-charactermove-megaboss/`, current F593/F596
whole-boss proof or F595 small-leaf evidence, `ghidra-project/`,
`build/matching/`, **any** probe `.obj` or `.pdb`, historical
PDB archives, original native JSON, decompilations, active Git
dirty files or any F301+ CI log. Do not confuse compressing an
old test run's duplicate stdout with deleting a native testcase.

## Restoring a historical JSON snapshot

The compressed files remain **next to their former paths**; when an old
one-off `.analysis/f1xx-*.py` program expects the uncompressed JSON, restore
its exact original bytes first. These old scripts are historical and may also
require a matching old `parent_commit` to be runnable.

```bash
# Confirm hashes for ALL 135 local archived historical snapshots:
scripts/repo-python scripts/archive-historical-analysis.py --verify

# Restore one specific historical snapshot with SHA256 verification:
scripts/repo-python scripts/archive-historical-analysis.py \
  --restore .analysis/f180-background-counters/parent-and-seed.json

# Inspect it normally, and recompact it if no longer needed:
scripts/repo-python scripts/archive-historical-analysis.py --archive --family seed

# Future read-only disk audit (does not delete anything):
scripts/repo-python scripts/archive-historical-analysis.py
```

The script deliberately compresses **only** historically frozen
**pre-F185** `parent-and-seed.json`, the exact H184
`resumption-seed.json`, and pre-F185 `fNNN-adoption-parent.json` snapshots
under ignored `.analysis/`. A **new in-progress F185+** parent snapshot
is not eligible for automatic compaction even if its basename matches. It does
**not** operate on current `config/exact-adoptions.json`, C++ source,
original PE, current `config/fighter-boss-dispatch-fingerprints.json`,
compiler environments, native decompilation or active negative probes.
If compression is interrupted, the script preserves an unmatched `.partial`
file and the original for inspection instead of silently overwriting data.

## Restoring an old PDB

```bash
# Restore ONE historical cache entry if actual debug info is needed:
tar -xzf .analysis/cache-archives/probe-pdb-unprotected-2026-10-29.tar.gz \
  -C . build/probes/FILE.pdb

# For an older PDB from the previous verified batch:
tar -xzf .analysis/cache-archives/probe-pdb-unprotected-2026-10-28.tar.gz \
  -C . build/probes/FILE.pdb
```

**Only restore a path actually listed** in the corresponding JSON receipt,
and compare the extracted file to the receipt's per-file original SHA256.
No `build/probes/*.obj` was deleted; current `build/matching/` objects/PDBs
and the accepted units stay available, so no full cold rebuild is needed.

## Never remove these dependencies and evidence

- `resources/th075.exe` **pinned Japanese** original and `ghidra-project/`
  original analysis. The PE itself is ignored, but is essential evidence.
- The **1.3 GiB** `.analysis/vc71-wine/` prefix containing the actual
  VC7.1 toolchain and Win32 runtime; `.tools/` bundled Python and Ghidra
  helpers. Deleting them would break target compiler verification.
- All tracked `src/`, `config/`, `scripts/`, `tests/`, `docs/` source and
  immutable exact adoption manifest hashes, plus accepted
  `build/matching/` and **all** COFF `build/probes/*.obj`.
- The **15 H184 protected PDBs and matching COFF source/objects**, listed
  with exact hashes at `.analysis/h184-handoff/active-object-retention.json`.
  All **15** protected PDB and COFF object SHA256s were **rechecked and
  unchanged** after this cleanup.
- The original gigantic Reimu/CharacterMove Ghidra decompilations,
  `.analysis/f493-reimu-megaboss/`, `.analysis/f509-charactermove-megaboss/`,
  `.analysis/character-move-4ac040/`, original PE-backed proofs,
  F528 whole WinMain source and meaningful negative C++/COFF probes.

The historical JSON backups are compressed **losslessly**, not discarded;
old PDBs are bundled and separately recoverable. Do not hide or abandon
new dirty work. Before another deletion, calculate exact sizes, confirm
that a file is redundant/regenerable or restore-tested, and keep a verified
recoverable copy when it may contain reconstruction evidence.
