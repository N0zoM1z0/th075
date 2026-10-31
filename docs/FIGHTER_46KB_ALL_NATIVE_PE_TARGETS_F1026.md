# F1026 — Original 46KB Boss: all 1,341 physical PE targets verified

The SHA-pinned Japanese TH075 v1.11 complete original
fighter **005214B0** owns **46,755 callable CODE B /
13,230 original x86**, followed by **901 separately owned
afterRET switch DATA bytes**. The selected whole original-shaped
normal VC7.1 F901 source compiles to **46,754 CODE B /
13,230 x86**. It remains NONEXACT.

Earlier source reviews established the correct native
semantics and many case-local PE external targets, but did
not verify every physical call/global field over the
entire fighter.

The [F1026 full-native PE verifier](../scripts/verify-fighter-whole-46kb-pe-targets-f1026.py)
fresh-builds the actual complete F901 original-shaped
VC7.1 C++ source, decodes the entire original Japanese
PE from its pinned SHA, and maps every source COFF
external DIR32/REL32 site to the **actual original x86
instruction ordinal and field offset**. Each native
original target is calculated from genuine PE bytes,
not inferred solely from a source or log.

| Entire fighter evidence | Verified |
| --- | ---: |
| Physical native external PE/COFF call/global targets | **1,341/1,341** |
| Explicitly address-named original source symbols | **1,311/1,311** |
| Genuine original __ftol2 at 006406AC | **30/30** |
| Source CODE-local label fields | **11** |
| Original afterRET DIR32 case labels | **139/139** |
| Original afterRET nonfield literal DATA bytes | **345/345** |
| Distinct native original jump tables | **7** |
| Total emitted normal VC7.1 COFF entries | **1,491** |
| Original/source complete x86 instruction count | **13,230/13,230** |

For all seven real native jump tables, the complete
independent verifier checks the physical original
dense-list values, their equality partitions against
the generated COFF local label offsets, the actual
afterRET source data field positions, and the
345 genuine nonrelocation bytes. No case is truncated,
no internal state is credited separately and no shifted
COFF field is hidden.

The source still has **five original incorrect
instruction widths** at whole x86 ordinals
**2885, 2908, 8455, 8986 and 9130**. Some game
GPR roles and original whole-parent absolute/relative
PE/COFF physical offsets differ; a one-byte total
CODE shortfall does not imply only one wrong byte.
The correct external PE target proof does NOT
establish full original codegen equality.

Reproduce only this single affected complete 46KB
whole-parent C++ build and original PE audit:

    scripts/repo-python scripts/verify-fighter-whole-46kb-pe-targets-f1026.py

Native physical call/field records, actual jump
table receipts and normal VC7.1 C++/OBJ/PDB
are retained under ignored .analysis/f1026-whole-46kb-original-PE/
and .analysis/f1026-46kb-pe-audit/.

**No new exact complete original callable CODE B.
No all-979-unit cold replay.**
