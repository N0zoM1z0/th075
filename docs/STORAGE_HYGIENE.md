# TH075 local storage hygiene and lossless recovery

**Updated 2026-10-31, F908 safe Git maintenance / Python bytecode cleanup,
after F907 reversible probe-binary compaction.**
This is a storage report and **lossless local recovery recipe**, NOT
permission to remove original PE, C++/COFF research evidence, active
work, matching objects, or unrecognized dirty changes. The archives,
SHA256 receipts and index files under Git-ignored
`.analysis/cache-archives/` are **machine-local and NOT in Git**;
this checkout must preserve them, or back them up independently before
moving/cleaning the worktree. The restore/verify tooling and these
instructions ARE tracked, but a fresh clone will not contain the
archives. Historical F597 and older JSON/PDB/CI archives are still
available and independently restorable.

## F908: normal Git-object maintenance and disposable Python bytecode cache

After the F907 SHA256 archive and committed recovery tool, a normal
**git gc --prune=2.weeks.ago** was executed with a standard two-week
retention horizon, no reflog reset, force-prune, branch rewrite or
history rewriting. **git fsck --connectivity-only --no-progress**
exited successfully (reporting only ordinary dangling blobs).
All live Git refs, history and unpushed commits remained intact.

| Generated local cache | Before | After | Reclaimed |
| --- | ---: | ---: | ---: |
| .git/ standard object storage | 140,288,349 B | 23,731,416 B | **116,556,933 B** |
| scripts/tests Python bytecode | 583 generated pyc files | removed, regenerate on demand | **12,665,361 file bytes** |

Only generated Python **.pyc/.pyo** files were removed from
scripts/__pycache__ and tests/__pycache__ after confirming neither
contains source or other data. They regenerate automatically when
later verification imports them. No actual authored Python source,
unit test, original PE, native research or compiler object was removed
by this small bytecode-cache cleanup. Filesystem directory accounting
may differ slightly from the exact file byte totals.

**Combined F907 archive + F908 maintenance net measured recovery:**
**349,427,978 bytes (333.24 MiB)**, including the F907 archive
and its original-path SHA256 receipt. This changes NO original
reconstruction exact credit or native artifact provenance.
Do not run git gc concurrently with a separate Git writer. Current
work is single-worker; a future worker should inspect Git status and
preserve all dirty edits first.

---

## F907: 4,712 regenerable VC7.1 OBJ/PDB files losslessly archived

The 2026-10-31 executed cleanup selected **only** loose Git-ignored
research binaries under .analysis/f650-* through .analysis/f906-*,
with filename extensions OBJ or PDB. The latest selected giant object
.analysis/f901-fighter-31b/Boss005214B0-F901-whole.obj was **excluded**.
All original game/source files, original native PE, normal VC7.1/Wine,
H184 protected objects, Ghidra, accepted build/matching, generated C++
and all JSON research receipts remain untouched.

| Actual archived source evidence | Measured value |
| --- | ---: |
| Regenerable complete source-probe OBJ/PDB files | **4,712** |
| All original loose file bytes, verified before removal | **267,798,945 B** |
| New local compressed archive | **46,739,344 B** |
| Original-path/size/SHA256 JSON receipt | **853,917 B** |
| **Net disk reclaimed (including the receipt)** | **220,205,684 B (210.00 MiB)** |

New SHA256-verified, **machine-local and NOT in Git**:

- .analysis/cache-archives/f650-f906-regenerable-obj-pdb-2026-10-31.tar.gz
- .analysis/cache-archives/f650-f906-regenerable-obj-pdb-2026-10-31-receipt.json

Archive file SHA256:
8a1902225b45854f9c6c7810071b97b6ecd4f04c3013a126b1bc7f9a3661c982.
Every original member was hashed on disk, packed, **stream-verified
against its original SHA256 while the loose copy remained intact**, and
all original files were rechecked again before unlinking. The archive
was then independently verified after deletion. A real original
F900 baseline OBJ was restored to its exact old path, its SHA256
checked independently, and the identical restored duplicate was
safely re-compacted, leaving the original compressed evidence intact.

F907 tracking/recovery script (preserved in Git):

    scripts/repo-python scripts/archive-recent-probe-objects-f907.py --family binaries --plan
    scripts/repo-python scripts/archive-recent-probe-objects-f907.py --family binaries --verify
    scripts/repo-python scripts/archive-recent-probe-objects-f907.py --family binaries --restore .analysis/f900-archive-grouped-locals/baseline.obj
    scripts/repo-python scripts/archive-recent-probe-objects-f907.py --family binaries --recompact-restored .analysis/f900-archive-grouped-locals/baseline.obj

**Do not rerun --archive while the archive and receipt exist.** It
refuses replacement. If an older source experiment needs its original
OBJ/PDB at the old location, restore only that SHA256-verified file.
Recompiling a source after cleanup can generate a different OBJ or
PDB at an archived path; verification preserves that new loose copy,
and restoration/recompaction refuses to overwrite or delete modified
research. A fresh Git clone contains the script, NOT the local
archive or receipt; back them up before cleaning/moving the worktree.
No native original exact function byte credit changed.

---

## Earlier F754 cleanup: 1,931 SHA256-recoverable frozen giant ASM/COD/LOG files

**Actual executed archive:** frozen generated text traces from original
historical investigations in only two allowlisted local directories:
`.analysis/character-move-4ac040/f133..f166/` and
`.analysis/object-action-50a580/f133..f166/`. The tracked
[`archive-frozen-giant-traces.py`](../scripts/archive-frozen-giant-traces.py)
selects **only** `.asm`, `.cod`, `.log` in these original historical
subtrees, which were already frozen before the current F752 giant
and F753 accepted whole-source work. No active F500+ experiment
outside the allowlist was considered for removal.

| Frozen generated trace family | SHA256-archived original files | Original bytes |
| --- | ---: | ---: |
| Historical native/emitted `.asm` disassembly and relocation dumps | **1,683** | **81,600,754** |
| Historical compiler `.cod` emitted native listing | **12** | **6,065,146** |
| Frozen experiment `.log` output | **236** | **2,665,732** |
| **Original total** | **1,931** | **90,331,632 B (86.15 MiB)** |

The archive was **3,373,146 bytes** (3.22 MiB), and the machine-local
per-file SHA256/path/size receipt is **344,227 bytes**. The exact
**net reclaimed space including this receipt is 86,614,259 bytes
(82.60 MiB)**, before incidental filesystem allocation effects.
The two old giant historical directory footprints decreased from
approximately **144 MiB +50 MiB** to **75 MiB +28 MiB**. The
`.analysis/cache-archives/` store grew as expected from roughly
57 MiB to 61 MiB. The remaining roughly **1.3 GiB
`.analysis/vc71-wine/` original compiler prefix MUST remain**.

The new local ignored archive/receipt are:

- `.analysis/cache-archives/historical-f133-f166-giant-traces.tar.zst`
- `.analysis/cache-archives/historical-f133-f166-giant-traces-index.json`

**Every 1,931 original member was SHA256 hashed, packed, then
independently streamed out of the actual newly written archive and
verified against the full original bytes/length BEFORE removing ANY
loose file**. All original source loose files were individually
rehashed just before unlinking; the full tar.zst archive was
independently re-verified AFTER deletion. One actual original
1,595,692-byte F154 `.cod` file was restored at its historical
path, validated against original SHA256, and successfully
re-compacted only when its bytes matched. There were **zero
changed or accidentally overwritten originals** in the final
verification. The local tar/index are **not in Git**; keep them
when cloning, transferring or further reducing worktree storage.

```bash
# Read-only: no eligible loose frozen .asm/.cod/.log should remain
scripts/repo-python scripts/archive-frozen-giant-traces.py --plan
# Independently verify every archived original and original per-path SHA256
scripts/repo-python scripts/archive-frozen-giant-traces.py --verify
# Rehydrate an exact original file needed by an older research script
scripts/repo-python scripts/archive-frozen-giant-traces.py \
  --restore .analysis/character-move-4ac040/f154/BaselineMapTrace.cod
# After examination, remove ONLY the byte-identical restored duplicate
scripts/repo-python scripts/archive-frozen-giant-traces.py \
  --recompact-restored .analysis/character-move-4ac040/f154/BaselineMapTrace.cod
```

`--archive` refuses overwrite of existing archive/index; `--restore`
refuses to replace newly generated or changed loose originals; and
`--recompact-restored` refuses deletion unless it independently
verifies the loose original has exactly its archived SHA256.
Old research scripts that read archived loose `.asm/.cod/.log`
need to restore only those files first. **The full original target
EXE, current source, every ignored C++/INC/HPP, OBJ/PDB, JSON
research receipt, H184 best objects, the Ghidra project, Wine,
accepted `build/matching/`, and current F7xx boss experiments
were never removed.** Never count these storage savings as
new native exact CODE.

---

## Historical F694 cleanup: 1,760 generated files preserved, ≈127.75 MiB net reclaimed

The 2026-10-30 actual on-disk inventory identified only TWO narrowly
allowlisted classes of old **reproducible compiler and test outputs**.
[`archive-redundant-native-research.py`](../scripts/archive-redundant-native-research.py)
archived all originals with their complete original path/byte size/SHA256,
then re-read and verified EVERY tar member against EVERY still-present
original file **before removing even one**. Both archives were then
verified again from storage after deletion. Exact one-file
`--restore` and `--recompact-restored` smoke tests succeeded for both
classes; no source/OBJ/game CODE was lost.

| Original generated-file cohort | Files | Original bytes | Compressed tar bytes | Net reclaimed INCLUDING receipt |
| --- | ---: | ---: | ---: | ---: |
| F500–F649 research compiler PDB (excluding key F593/F596 parent proofs) | 1,457 | 82,939,904 | 2,023,441 | **80,648,648 B** |
| Root R001–R259 repeated historical CI output logs (excluding R260+ checkpoint/acceptance logs) | 303 | 60,857,730 | 7,509,018 | **53,304,224 B** |
| **Total** | **1,760** | **143,797,634** | **9,532,459** | **133,952,872 B (127.75 MiB)** |

The locally ignored `.analysis/` tree changed from about
**2,231,088 KiB to 2,105,496 KiB** on this filesystem. This is
filesystem allocation accounting; the exact **133,952,872-byte**
net saving is based on original file sizes minus new archives and
per-file receipt sizes. PDBs/CI logs remain **byte-for-byte
recoverable** from the two SHA256-authenticated `.tar.gz` files and
receipts in `.analysis/cache-archives/`. A routine historical script
may require restoring a missing old PDB or CI log before execution.

```bash
# No changes: show remaining eligible loose files (normally zero)
scripts/repo-python scripts/archive-redundant-native-research.py --family pdb --plan
scripts/repo-python scripts/archive-redundant-native-research.py --family logs --plan
# Independently verify EVERY original archived file by its SHA256
scripts/repo-python scripts/archive-redundant-native-research.py --family pdb --verify
scripts/repo-python scripts/archive-redundant-native-research.py --family logs --verify
# Restore one actual F609 compiled debug file only if needed
scripts/repo-python scripts/archive-redundant-native-research.py \
  --family pdb --restore .analysis/f609-archive-source-types/release-double-address.pdb
# After inspecting it, remove only that SHA256-unchanged duplicate
scripts/repo-python scripts/archive-redundant-native-research.py \
  --family pdb --recompact-restored .analysis/f609-archive-source-types/release-double-address.pdb
# Example of original historical R142 CI log recovery
scripts/repo-python scripts/archive-redundant-native-research.py \
  --family logs --restore .analysis/r142-ci.log
```

**A regenerated historical PDB is NOT an archive checksum failure.**
After re-running an older VC7.1 source control, a former F500–F649
`.pdb` may reappear at an archived path with a *different* SHA256.
`--verify` still verifies every archived original member and reports
that changed loose copy without modifying it. **Neither `--restore`
nor `--recompact-restored` overwrites/deletes that regenerated file.**
We exercised these refusal cases using an explicit temporary
synthetic smoke output, then reverified the original stored tar
members. During original archival, all loose original hashes are
strictly checked **before** unlinking any file. If a newly generated
PDB appears, `--plan` may list it; `--archive` refuses to overwrite
the already authenticated tar/receipt. Never force-delete newly
regenerated research data simply to repeat an earlier compaction.

**Not touched:** original pinned `th075.exe`; Wine/VC7.1 prefix;
Ghidra project; H184's **15** original protected PDB/object pairs
(**all 30 SHA256s rechecked**); all accepted `build/matching/` and
`build/probes/*.obj`; all active F650+ PDBs; R260–R268
checkpoint logs; every native C++/ASM/INC/source/COFF OBJ, original
native trace, original JSON research receipt, decompilation and
case/source-negative experiment; Git history and dirty changes.
The original SOURCE provenance of uncredited SDK-like functions and
the authored whole-function exact ledger remain unchanged.

---

## Earlier 2026-10-29 storage campaigns (historical measurements)

## Standard Git object maintenance after the documentation/archive commits

After the complete old-handoff narrative had been preserved and the
reconstruction/storage scripts committed, a **standard Git GC** was run
with the normal **two-week prune horizon**:

```bash
git gc --prune=2.weeks.ago
git fsck --connectivity-only --no-progress
git status --short --branch
```

This was **not** `git gc --prune=now`, a force-delete of the reflog, a
Git history rewrite or a manual removal of `.git/objects`. It retained
all live refs, recent committed history and reflog entries; Git fsck
exited successfully, reporting only five ordinary dangling blobs that
were **not assumed to be accepted function sources**. Actual Git
storage shrank from **413,241,344 bytes to 23,572,480 bytes**, a
**389,668,864-byte (≈371.62 MiB) saving**; all 7,023 loose objects
were safely packed/maintained by Git, with 13,527 packed objects in
two packs afterward. Never run aggressive pruning or remove reflogs
simply to recreate this one-time saving.

**Historical 2026-10-29 campaign savings (not including F694):** **646,211,818 bytes
(≈616.28 MiB)** across the reversible 219-diagnostic archive
(**256,542,954 bytes net, including the receipt**) and the standard
Git storage maintenance (**389,668,864 bytes**). The checkout's **historical 2026-10-29** measured on-disk size was **2,754,048,000 bytes** (about
2.6 GiB), including required VC7.1/Wine, original native evidence,
Ghidra, accepted match objects and exact manifests.

## Earlier cleanup: 219 frozen redundant JSON diagnostics (post F652)

The four original *read-only historical* diagnostic sets below were
archived losslessly under ignored `.analysis/cache-archives/` using
[`scripts/archive-redundant-diagnostics.py`](../scripts/archive-redundant-diagnostics.py).
**All 219 original SHA256 checks were compared to the actual decompressed
tar members before any loose file was removed**; a durable 42,513-byte
per-path original-size and SHA256 index was written before deletion.
The four archived batches were independently read and verified **again
from storage after deletion**. A one-file restore and exact re-compaction
was successfully smoke-tested for **each of the four groups**.

| Historical diagnostic family (generated JSON only) | Originals | Plain bytes | Compressed bytes |
| --- | ---: | ---: | ---: |
| Old origin `r###-triage` / `before-acceptance` scans, **not** live `latest.json` | 95 | 77,534,232 | 1,129,548 |
| Repeated legacy `object-action-50a580/f###/*-whole-diagnostic.json` | 48 | 40,133,010 | 354,274 |
| Repeated legacy `character-move-4ac040/f###/*-whole-diagnostic.json` | 37 | 48,510,031 | 740,271 |
| Large `r###-*.json` historical R-series survey outputs (≤R270, original >1 MB) | 39 | 96,292,020 | 3,659,733 |
| **Total verified** | **219** | **262,469,293** | **5,883,826** |

Actual storage recovered: **256,542,954 bytes (244.66 MiB)** **after
including the original per-file archive-index bytes**, excluding a few
small directory-entry differences. This is storage *reclamation*,
**not reconstruction progress**. The original snapshots remain byte-for-byte
recoverable with their original relative path and SHA256. Current game source,
compiler profiles, original PE, Ghidra project, Ghidra decompilations,
`build/matching/`, original native COFF/OBJ/PDB, `vc71-wine/`, current
`.analysis/origin-scan/latest.json`, all F5xx–F652 whole giant and small-leaf
C++ research and every exact adoption were left intact. In particular,
we removed only selected **repeated old generated JSON diagnostics** from
the protected `character-move-4ac040/` area; no underlying native source,
ASM, entire-game diagnostic trace or compiler object there was discarded.

```bash
# Read-only discovery before any future archive:
scripts/repo-python scripts/archive-redundant-diagnostics.py --plan
# Independently stream-verify all 219 original member SHA256s:
scripts/repo-python scripts/archive-redundant-diagnostics.py --verify
# Recover a particular ORIGINAL ignored JSON file at its exact old path:
scripts/repo-python scripts/archive-redundant-diagnostics.py \
  --restore .analysis/character-move-4ac040/f156/secondary-int-caller-whole-diagnostic.json
# Once reviewed, reclaim that exact restored copy only after SHA256 verification:
scripts/repo-python scripts/archive-redundant-diagnostics.py \
  --recompact-restored .analysis/character-move-4ac040/f156/secondary-int-caller-whole-diagnostic.json
```

The four `.tar.zst` archives and `frozen-repeated-diagnostics-index.json`
are **intentionally ignored and local to this checkout**. They are **not**
part of a Git commit, Git clone, remote backup, or an external acceptance
receipt. Never delete a local archive without a verified replacement
backup if the corresponding ignored history is still needed. Older
one-off scripts reading an archived `*-whole-diagnostic.json` or
`r###-triage.json` must explicitly restore it first; do not mistake
a missing loose copy for an absent/failed original experiment.

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
`.analysis/f509-charactermove-megaboss/`, then-current F593/F596
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
