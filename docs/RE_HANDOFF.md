# TH075 — active reconstruction handoff

**Maintained 2026-10-29 after F599.** This is the **only current task list**.
The [F540–F596 research chronology](history/RE_HANDOFF_F540_THROUGH_F596.md),
[knowledge base](KNOWLEDGE_BASE.md), and older F-series studies are
**historical evidence**, not statements of current progress. Independently
re-read original PE, current Git/files and manifests; old hypotheses
may be wrong. User requests substantive work on **both whole giant boss
functions and small leaves**, immediate `gpt-web: ...` commits, continuing
*every* dirty edit (the user reports no other active session), and **NO
full all-unit cold replay**; only compile/replay affected units.

## 1. Live source-of-truth and exact accounting

| Item | Verified live snapshot (recheck with commands below) |
| --- | --- |
| Original target | User-provided **Japanese** TH075 1.11 `resources/th075.exe` SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`; do not use localized `th075c.exe` |
| Whole exact source | **943 functions / 943 exact units**, **862,726 original CODE bytes** |
| Reviewed authored coverage | **43.71%** of **1,973,704** reviewed bytes; conservative **43.64%** including pending origins |
| Provisional native candidates | 4,351; 1,004 origin-classified authored, **95 unknown** comprising 3,420 original bytes |
| Unmatched authored | **25 complete functions**: **22 large fighter bosses** totaling **1,102,055 CODE bytes**, and 3 smaller complete originals below |
| Goal | 98% authored-byte coverage **not achieved**. No external Oracle acceptance receipt |

```bash
git status --short --branch
git log -5 --oneline
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/audit-active-handoff.py
```

**Authority order:** actual original pinned PE + physical full function
and x86/relocation boundaries; `config/function-origins.csv` and
`config/functions.csv`; accepted `config/match-units.toml` and cold
replay; then *provisional* C++ names, documentation and decompiler
hypotheses. `structural-exact` without verified provenance is not
accepted authored CODE. A complete boss **case is not its own exact
function**; after-RET jump DATA is not CODE.

## 2. Main large-boss task: original `004EBDA0`

The `CharacterObject::Advance`-like whole native function has
**33,293 CODE bytes, 8,789 complete x86 instructions**, and
**438 separately owned after-RET DATA bytes**. Its tracked normal
C++ source is `probes/CharacterObjectActionsF572.cpp` (provisional
class names, not exact original declarations). Under genuine pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` it now reproduces **all
8,789 original instruction start offsets, opcode widths and mnemonic
order**, complete native CODE length and compressed table layout.

**Latest original-PE verified F596, NOT F593's historical state:**

| Whole original CODE + DATA comparison | Current F596 |
| --- | ---: |
| CODE / after-RET DATA | **33,293 B / 438 B** |
| Original native x86 instructions / ordered mnemonics | **8,789 / 8,789** |
| Actual typed zero-addend PE/COFF fields | **622 CODE + 60 DATA = 682** |
| Original literal compressed switch index bytes | **198 / 198 identical** |
| Whole non-relocation bytes identical | **30,866 / 31,003** |
| Remaining non-relocation byte differences | **137** across 133 x86 instructions |
| Historical 3 independent `MOV`/`FLD` swaps | **ZERO remain** since F596 |
| Strictly source-grammar verified original *case subranges* | **56 cases**, 8,300 original x86 roles, 31,374 original *internal*, **uncredited** CODE bytes, 586 genuine typed case fields |

All **137** wrong nonrelocation bytes are linked to three remaining
compiler-register cycles; **whole giant remains NONEXACT**:

| Native case | Native complete role/size (not credited exact) | Different original GPR-role operands | Useful next evidence |
| --- | --- | ---: | --- |
| `0x38D` | 155 instructions /570 B | **45**, starting at case ordinal **91** (`004F344C`) | Native registers rotate after stage4 fade; source `F32(+0x1C)`/byte fade lexical scope suspected but **23 F594 + 6 F598 natural variants failed** |
| `0x38E` | 87 /348 B | **64** | Register rotation persists across source case boundary; compare original owner/view, not isolated fake register assignments |
| `0x3E3` | 200 /812 B | **24**, all in ordinals 0–30 | The same cycle disappears at ordinal31; investigate genuine enclosing scope and last-case compiler context |

Three previously disputed collision cases **`0x32A/0x32C/0x335`**
are now strictly native x86/byte-order equal in source after
natural C++ lvalues (`*(&F32(0x48)) ± *(&F32(0x54))`). Do not
reintroduce the old F573/F574/F578 expected swapped instruction
orders. Distinct last actions `0x3E4` (261 instructions /1,126 B)
and `0x3E5` (96 /396 B) are source-grammar strict but the
**whole function is still nonexact**.

Reproduce **only this one affected compilation**:

```bash
scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py
# Or inspect the underlying whole-original full COFF comparison:
scripts/repo-python scripts/verify-characterobject-whole-geometry-f593.py
```

Primary current results: [F596 collision-order and 137-byte residual](CHARACTEROBJECT_NATIVE_COLLISION_ORDER_F596.md),
[F593 whole CODE+DATA methodology and previous 155-byte baseline](CHARACTEROBJECT_WHOLE_GEOMETRY_F593.md),
`docs/CHARACTEROBJECT_COMPLEX_AIM_F592.md`. Fresh compiler and whole
PE/COFF receipts under ignored `.analysis/f593-characterobject-whole-source/`
and `.analysis/f596-characterobject-native-collision-source/`.

## 3. Other large original fighter bosses — do not only fix leaves

**22 large fighter bosses** together contain **1,102,055 CODE bytes**
plus **16,123 separate after-RET switch DATA bytes**. `004EBDA0`
is only one; **21 other whole giants remain nonexact**, including
Reimu `0045DD70`, CharacterMove `004AC040` (82,796 B), and
other 28–82K native bodies. Their native dispatches, GPR/x87
case families and table partitions have been partially decoded;
**do not conflate a locally strict case C++ probe with an accepted
complete original function**.

Read `config/fighter-boss-dispatch-fingerprints.json`,
[FIGHTER_BOSS_FAMILY_DISPATCH.md](FIGHTER_BOSS_FAMILY_DISPATCH.md),
[FIGHTER_ACTION_CASE_RESOLUTION.md](FIGHTER_ACTION_CASE_RESOLUTION.md),
and [FIGHTER_OPENING_SIX_CASES_CODEGEN.md](FIGHTER_OPENING_SIX_CASES_CODEGEN.md).
**F598, newly original-backed 12th action inside all eleven multi-switch
fighter giants:** native isolated action **0x32/50** now compiles as real
natural C++ in the same `Advance()` function as the earlier 11 original
actions, rather than a diagnostic marker. The 11 whole-case codegen
comparisons prove **638 original x86 instruction roles /2,306 internal
CODE bytes /77 true typed native COFF fields**; the one `00564BE0`
wide-frame case requires 17 physical EBP-0x88 receiver loads
(**256 native vs 205 source CODE bytes**). All earlier 121 native
case grammars and 1,607 physical jump DWORD fields/4,502 original
sparse bytes remain verified. Together **132 inner cases /26,835
original CODE bytes** are source-backed but **NO entire giant CODE
byte-exact acceptance or split-case credit**. Later actions beginning
`0x33` and their parent frame/switch lifetime remain undone.
[F598 PE+VC7.1 11-fighter contact singleton](FIGHTER_SINGLETON_CONTACT_F598.md),
tracked real C++ [case source](../probes/FighterSingletonContactF598.inc).

Use only a *selected* fighter original and source compilation, for example:

```bash
scripts/repo-python scripts/verify-fighter-singleton-contact-f598.py --boss 0x004F7130
scripts/repo-python scripts/verify-fighter-singleton-contact-f598.py --boss 0x00564BE0
```

Never run a full 943-unit cold replay.

## 4. Other three unmatched authored *whole* functions

| Original | Size / native structure | Precise remaining blocker, best source evidence |
| --- | --- | --- |
| **`00602A60`** `GameApplication::Run` | **2,987 B; 654 original x86, 123 calls**, original 0x278 frame | F528 best normal C++ source emits 2,981 B /654 x86 but wrong native EBP owner local slots; inspect `.analysis/f528-winmain-native-initial-scene/`, [WinMain whole CFG](WINMAIN_ORIGINAL_CONTROL_FLOW.md). The original scene switch's 60 after-RET bytes are DATA |
| **`0043B0B0`** battle scene destructor | **248 B /75 x86 /12 original COFF fields** | True VC7.1 `/GX` ordinary C++ has **191/200** non-COFF bytes; nine different literal EBP temp slots for texture delete and three resource frees. [F589 native destructor probes](SCENE_TEXTURE_DELETE_CONTROLS_F589.md). No 248-byte exact credit |
| **`0041CE50`** archive catalog nonvirtual destructor | **171 B /51 x86 /14 real COFF fields** | Natural `/GX-` C++ has **108/115** nonrelocation bytes; original delete/filename temporary locals use different EBP ownership. F598 confirms direct filename `free` fixes the **resource** stack slots but incorrectly drops 2 native instructions (165 rather than 171 B); meaningful local filename source restores 171 B but shifts slots back. [F584 native archive delete experiments](ARCHIVE_DELETE_EXPRESSION_CONTROLS_F584.md) and [F598 small C++ negatives](FIGHTER_SINGLETON_CONTACT_F598.md). No 171-byte exact credit |

Unknown provenance is **separate** from these authored nonexact
functions. F595 produced **40/40 byte-identical native C++** for
`004135F0` but it is **origin UNKNOWN**, zero registered direct
callers and no literal DWORD pointers; do not count in official
exact ledger. `00449DE0` has 36 original exact background-loader
callers yet implicit-vs-explicit constructor ambiguity; also
unknown. `004588B0` has six mixed vendor/game callers.
See [F595 original native small-function provenance](SMALL_ORIGIN_UNKNOWN_FIELDSETTER_F595.md)
and historical [origin review](ORIGIN_PENDING_REVIEW.md).

**F599: two large, complete, original-PE-byte-identical natural C++
copy members now source-backed, but original provenance still UNKNOWN.**
`0045AAE0` / 368 B /118 x86 and `004591E0` /417 B /128 x86
are generated *implicitly* from one genuinely used 116-byte C++ record
with nontrivial member lifetimes. Their complete **785/785 original CODE
bytes, 753/753 non-relocation bytes and 8/8 real physical typed COFF
destinations** are identical after true relocation linking. The first
nontrivial member destructor and VC7.1 `/GX` frame reproduce both native
exception-state writes; `/GX-` is a negative control. The actual owner
and developer's implicit-vs-explicit syntax remain unproved, so **do not
count 785 source-backed bytes as newly accepted authored CODE**.
An independent original direct-call scan over all 4,351 registered
functions now finds **three distinct library-classified direct callers
for each**, without proving the original member owner or author.
[Complete F599 original source/ownership evidence](RECORD116_IMPLICIT_COPY_ORIGIN_F599.md),
[actual natural C++](../probes/Record116ImplicitCopyF599.cpp) and one
selected cold compile plus optional EH negative:

```bash
scripts/repo-python scripts/verify-record116-implicit-copies-f599.py --with-negative-gxoff
```

## 5. Required workflow and data acceptance

1. Inspect dirty Git changes immediately and **continue all of them**;
   this is a single working session. Reread the actual original PE
   instead of assuming any report, proposed class or previous probe
   is correct. Never skip giant bosses to do only easy leaves.
2. Keep genuine source C++ in tracked `src/` or `probes/`, original
   results/negative controls in ignored `.analysis/`, and preserve
   `resources/th075.exe`, `ghidra-project/`, shared VC7.1/Wine,
   `build/matching/`, all probe COFF objects and immutable adoption
   receipts. **Do not overwrite/delete meaningful dirty work.**
3. Compile **only the affected translation unit** under pinned
   headless VC7.1. For exact authored code, run **only**
   `scripts/repo-python scripts/replay-exact-units.py --unit UNIT_ID`;
   never omit `--unit`. Verify actual complete function CODE and
   every typed physical relocation; never grant CODE to an inner
   switch action or compiler/runtime helper.
4. Commit actual progress promptly with `gpt-web: ...`. Run
   `scripts/repo-python scripts/validate-tracking.py --require-target`,
   `scripts/repo-python scripts/audit-active-handoff.py`,
   `scripts/repo-python scripts/update-progress.py --check`,
   `git diff --check`. Run the *light* `scripts/ci.py` if changing
   verification/ledger infrastructure. No all-unit cold replay.

## 6. Storage protection, recovery and historical navigation

[Storage protection and recovery](STORAGE_HYGIENE.md) is binding.
`.analysis/vc71-wine/` (about **1.3 GiB**) is a working compiler
**dependency**, not old cache. Keep Ghidra project, original PE,
source, manifests, accepted match objects, native JSON evidence and
significant negative controls. Only remove demonstrably redundant
**reproducible** outputs after hash-verified *lossless* archival and
record restoration instructions in `STORAGE_HYGIENE.md`; keep archive
receipts. Old historical JSON/PDB snapshots were previously compressed.
F597 additionally archived **243 redundant pre-F301 CI output logs**
losslessly (108,699,966 original bytes → 13,829,049-byte tar plus
36,446-byte SHA256 receipt; **≈90.4 MiB saved**). Restore any one
with the exact command below; `--verify` rereads all member hashes:

```bash
scripts/repo-python scripts/archive-legacy-ci-logs.py --verify
scripts/repo-python scripts/archive-legacy-ci-logs.py --restore .analysis/f179-ci.log
``` Current F301+ experimental logs and all source/objects,
original PE, Ghidra, `.analysis/vc71-wine` and H184 protected
artifacts are unchanged.

The former 977-line active handoff was archived **losslessly as
tracked English source evidence**:
[Historical F540–F596 handoff](history/RE_HANDOFF_F540_THROUGH_F596.md).
The detailed 10K-line [knowledge base](KNOWLEDGE_BASE.md),
[older handoffs](RE_HANDOFF_HISTORY.md),
[reconstruction workflow](RE_WORKFLOW.md), and
[AGENTS.md](../AGENTS.md) remain searchable but older factual
snapshots must not override live native/tracking evidence.
