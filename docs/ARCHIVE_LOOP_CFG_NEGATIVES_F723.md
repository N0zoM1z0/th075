# F723 — whole 171-byte ArchiveCatalog original loop CFG source controls

**Twelve fresh original-native VC7.1 source controls, no exact adoption.**
Target: user-supplied Japanese TH075 v1.11 `resources/th075.exe`,
pinned SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Original physical evidence, not a guessed abstract loop

The entire authored nonvirtual original `0041CE50` destructor has
**171 CODE B /51 authentic x86**. It decrements its shared refcount
`[0068BE04]`, then performs original indexed borrowed resource
`delete`, indexed filename CRT `_free` at original `0064169D`, and
both original global list `Clear` calls. The original physical loop
is not just an unspecified traversal: native x86 ordinals **8–16**
are `MOV [EBP−4],0`, immediate `JMP` to the original size check,
original index-increment block `MOV/ADD/MOV`, `MOV ECX,0068BE1C;
CALL 0041DD50`, then `CMP [EBP−4],EAX; JAE` with the body after it.
The original has **14 physical typed PE/COFF fields**. Its true
resource/delete-receiver/name pointer owner stores at native ordinals
22, 24 and 38 are **`EBP−0xC`, `−0x8`, `−0x10`**, whereas the
selected ordinary C++ produces **`−0x10`, `−0xC`, `−0x8`**.
This has exactly seven actual nonrelocation mismatching bytes at
whole-function offsets `0x4F,0x52,0x55,0x58,0x60,0x84,0x87`:
**108/115** original comparable bytes equal; the whole function
remains **NONEXACT**.

## New original-source hypothesis: real loop control-flow shape

F709/F710 and F719 already varied used pointer type, declaration
position, resource aggregate ownership and scoped source lifetimes.
F723 independently investigates whether the actual original C++
source used a normal `for`, a standalone `while`, or an explicit
unsigned loop guard with `break`/`continue`, rather than relying
on historical assumptions about its original syntax. All twelve
full translation units preserve the *actual* resource `delete`,
filename `free`, unsigned indexed names `Size()` and both original
post-loop container `Clear` operations. No dummy locals or target
machine bytes were injected. Source forms with different
termination behavior for unusual changing `Size()` values are
**diagnostic negative models**, not accepted native semantics.

| Whole VC7.1 C++ loop model | Variants | Entire compiled original-shaped destructor | Original PE comparison |
| --- | ---: | --- | --- |
| `for` postfix increment, `+=1`, or `index=index+1` | **3** | **171 B/51 x86/14 source COFF** | **108/115** native nonrelocation B, original EBP rotation still wrong |
| Semantically reversed unsigned comparison `Size()>index` | **1** | **171 B/51 x86/14 fields** | **106/115** nonfield B, only 50/51 original x86 mnemonic/width positions correct |
| `for (;;++index)` with explicit `index>=Size()` or `Size()<=index` guard and `break` | **2** | **173 B/52 x86/14 fields** | Original physical opcode/layout changes; not 171 native B |
| Used unsigned-index `while (index<Size())`, postincrement and reversed comparison | **3** | **169 B/50 x86/14 fields** | Original `JMP` before first condition not reproduced; no native whole geometry |
| Infinite `while` with `break` before real body | **1** | **180 B/54 x86/14 fields** | Different original control flow |
| Infinite `do/while` with real early `break` | **1** | **178 B/53 x86/14 fields** | Different original control flow |
| Empty-condition `for` with actual conditional body and `continue` | **1** | **173 B/52 x86/14 fields** | Different original control flow |
| **Total** | **12 complete original-profile source TUs** | | **0** whole original native exact |

The three conventional `for` increments are genuine source-level
compiler equivalents, and none fixes the native three-way EBP
allocation. The reversed comparator even changes original native
comparison opcode/field width placement. Crucially, the natural
`while` source *shortens* the complete caller to **169/50** and
explicit first-iteration `break` *lengthens* it to **173/52**;
this is physical evidence that the original 171/51 layout is
naturally consistent with a conventional source `for`. The missing
original byte-match therefore concerns native compiler-generated
resource/filename temporary lifetime, not a missing loop macro or
invented unconditional condition. No whole native exact credit.

## Reproduce, preserving complete PE/COFF evidence

The portable tracked
[`verify-archive-loop-structure-f723.py`](../scripts/verify-archive-loop-structure-f723.py)
reads the pinned original whole 171-B/51-x86 target and the actual
native three EBP stores. Its default behavior compiles **one entire
small destructor C++ TU** with pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`; `--case` selects one original
loop grammar; `--all` compiles **only these twelve affected whole
small source TUs**, never the 943 accepted exact units. The 171-B
candidates use the canonical whole-original relocation-aware PE
comparator to check all **14 original typed physical fields** and
actual 108/115 or 106/115 byte negatives. For non-171-byte source
cases, generated real native x86 and COFF counts are compared and
the original whole mismatch is preserved — never cropped to 171 B.

```bash
scripts/repo-python scripts/verify-archive-loop-structure-f723.py --case for-postincrement
scripts/repo-python scripts/verify-archive-loop-structure-f723.py --all
scripts/repo-python scripts/verify-archive-source-types-f609.py --case release-scope-delete
```

Actual private compiler source, OBJ/PDB, diagnostics and native PE
comparison are kept in Git-ignored local
`.analysis/f723-archive-loop-control/` and its `verified/`
subdirectory. The tracked selected verifier reproduces the negative
in a clean reconstruction worktree with the required native target
and compiler. No target EXE modification, false authored origin,
unverified exact acceptance or mass cold replay. The formal whole
function ledger remains **943 exact authored functions, 862,726
original CODE bytes (43.71% reviewed)**.
