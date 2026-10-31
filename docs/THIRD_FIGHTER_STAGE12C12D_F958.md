# F958 — First tracked cumulative third-fighter parent, plus native 12C/12D

Pinned original Japanese TH075 v1.11 Fighter **004AC040**
contains 82,796 original callable CODE B/22,721 x86
plus 1,126 separate afterRET jump DATA B. The new
[tracked cumulative whole-parent C++ source](../probes/FighterWhole004AC040F958.cpp)
collects the authentic native C++ action bodies reconstructed
through F955, rather than requiring the ignored previous
full compiler experiment to reconstruct the latest source.
It is still **partial** and NONEXACT: remaining source
markers and the original 0x720 stack frame/saved-this
EBP−0x64 are not yet restored.

The additional genuine original actions have the
following independently decoded native PE ranges:

| Original case | Real original native interval | Complete original CODE | Verified external PE fields |
| --- | --- | ---: | ---: |
| **12C** | **004B1039..004B1108** | **207B /59 x86** | **6** |
| **12D** | **004B1108..004B11E3** | **219B /61 x86** | **6** |
| **Both internal handlers** | contiguous | **426B /120 x86** | **12** |

The original game semantics use stage/frame-zero initial
ResetAt453E20 guarded by the observed signed fall flag,
then set signed short +0x80=1 and zero the true 32-bit
+0x7C field. While original flag +0x3AC is positive,
subtract real float **00658058** from movement +0x50
and clamp at original float threshold **0065782C**
while clearing the signed flag. Both actors call
GetNativeActionAt40FA30 and SetNativeActionAt40FAC0(0)
on genuine frame completion. The later phase-specific
action differs:

- **12C:** signed short stage3/frame0 calls
  PrepareActionAt453D60(0x1B).
- **12D:** clears the real signed short +0xF00
  before checking stage4/frame0 and invoking
  PrepareActionAt453D60(0x1C).

The C++ is tracked in the common
[`FighterThirdBossStage12C12DF958.inc`](../probes/FighterThirdBossStage12C12DF958.inc)
within the actual cumulative parent. This is source
representing original gameplay, not a separate compiled
fake function or original-byte graft.

## Important original jump-table boundary correction

Native **12C has no independent DIR32 afterRET table
entry**. A candidate whole-function checker must NOT
invent one. The original real preceding D2 starts at
004B0F3E and has **251B/74 x86**. Its native exit is
exactly the start of the genuine 12C at **004B1039**.
The next real case 12D starts at **004B1108**, and
does have a genuine native table label. F958 derives
the 12C source boundary from the **verified 251-B
D2 code terminus** and the mapped 12D successor;
both native and source must be exactly 207B/59 x86
between these physical boundaries.

The tracked
[`verify-third-fighter-stage12c12d-f958.py`](../scripts/verify-third-fighter-stage12c12d-f958.py)
freshly compiles TWO entire original-shaped
normal VC7.1 partial 82KB giant fathers:
both previous markers vs both real cases
in the new tracked master. It independently
reads the SHA-pinned native PE, authentic
D2 terminus, original 12C/12D complete
native x86 and all **12 actual original
PE i386 target addresses**, zero-addend
COFF fields, all **151 actual afterRET
DIR32 local case labels** and the
**522 original nonfield DATA bytes**.

| Whole *partial* native-shaped source | Before F958 | F958 selected |
| --- | ---: | ---: |
| Emitted partial whole CODE B | 21,616 | **22,012** |
| Emitted whole partial source x86 | 5,859 | **5,975** |
| Original 12C source bytes/x86 | 15/2 | **207/59** |
| Original 12D source bytes/x86 | 15/2 | **219/61** |
| Both original native mnemonic/width/GPR-role wrong | n/a | **0/0/0** |
| Actual original native PE fields validated | markers | **6+6** |
| Original afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Entire original 82,796-B game fighter exact | NO | **NO** |

The new tracked whole parent emits **exactly the same
generated CODE+afterRET bytes and physical relocation
positions, types and local target offsets** as the
independently authored and compiled ignored trial
with both bodies expanded inline. Source-file
rewrapping does rename some VC7.1 internal `$L`
labels, so original string-symbol/label identity
is **not** assumed equal merely from byte equality.
It changes no actual native PE target claim and
earns no whole-source exact credit.

Reproduce without rebuilding unrelated 979 units:

    scripts/repo-python scripts/verify-third-fighter-stage12c12d-f958.py

Original-shaped full C++ source, OBJ/PDB, compile logs
and target-PE backed receipt are in ignored
`.analysis/f958-third-source-proof/` and the
earlier complete-source control in
`.analysis/f958-third-stage12c/`.

**0 newly accepted whole callable original functions,
0 original CODE bytes credited; no all-unit cold replay.**
