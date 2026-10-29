# TH075 local storage hygiene and lossless recovery

**Updated 2026-10-29.** This is a storage report and recovery recipe, **not**
a license to remove original PE/C++/COFF evidence or skip dirty work. The
only tracked change required for the snapshot compaction was the reversible
`scripts/archive-historical-analysis.py` helper; actual historical archives
and receipts live under **Git-ignored** `.analysis/` (local to this worktree).

## What was compacted, with independently verified bytes

| Batch | Files safely archived | Original file bytes | Packed bytes | Storage reclaimed |
| --- | ---: | ---: | ---: | ---: |
| Old parent/adoption JSON snapshots, 2026-10-29 | **135** | **649,802,039** | **35,694,113** | **614,107,926** |
| Unprotected old compiler-probe PDBs, 2026-10-29 | **1,002** | **71,393,280** | **7,298,260** | **63,919,095** net including receipt |
| **This cleanup** | **1,137** | **721,195,319** | **42,992,373** | **≈ 647 MiB** after receipts/index overhead |

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
