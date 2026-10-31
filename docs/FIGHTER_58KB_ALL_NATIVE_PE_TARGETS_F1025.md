# F1025 — Native 58KB fighter: all 1,697 external physical PE targets verified

The pinned Japanese TH075 v1.11 executable original
**00543210** is a single complete callable
**58,294 CODE B /16,471 x86**, followed by separately
owned **943 afterRET DATA B** (156 actual local DIR32 case
labels and 319 nonfield DATA bytes). It is not an accepted
exact whole original function.

The F917 selected complete original-shaped normal VC7.1
fighter source emits **58,293 CODE B /16,471 x86**.
Prior native-target verifiers proved four genuine x87 signed
projectile chains and actual jump-table targets, but did not
independently audit all of the whole giant's nonlocal COFF
call/global target destinations.

The [F1025 native PE verifier](../scripts/verify-fighter-whole-58kb-pe-targets-f1025.py)
freshly cold-builds BOTH complete F781/F917 original-shaped
58KB source variants through the selected normal VC7.1
compiler, reads the original SHA-pinned Japanese PE
independently, maps source COFF fields to genuine original
x86 **instruction ordinals and the actual original field
position inside each instruction**, and decodes every native
REL32 or DIR32 destination. No shifted field is masked,
and no partial or internal case is falsely considered a
whole native callable.

Across each entire compiled fighter:

| Original native evidence | Exact verified |
| --- | ---: |
| Physical nonlocal native PE/COFF targets | **1,697/1,697** |
| Those with explicit address encoded in source symbol names | **1,676/1,676** |
| Native __ftol2 target 006406AC | **21/21** |
| Actual CODE-local case label fields | **10** |
| Original afterRET case DIR32 fields | **156/156** |
| Original afterRET nonfield DATA B | **319/319** |
| Total normal compiled COFF fields | **1,863** |
| Original/source complete x86 instruction count | **16,471/16,471** |

The verifier invokes the independent F759 original sparse
switch-table proof, including every physical dense target,
actual sparse table partition and literal bytes. It does
not infer original global addresses from matching symbol
names alone: it decodes the true native PE operand values
and independently compares them to original explicitly
address-typed C++ declarations, or the actual __ftol2
native conversion entry.

The signed-X F917 C++ also retains the genuine native
four positive-IMUL/FSUBR signed-float subtractions.
Its whole original mnemonic sequence now matches
**16,471/16,471**, but still has original 0x63
instruction-width differences at whole ordinals
**2934, 2977, 3000** and **1,741 wrong positional GPR
operand roles**. The saved this and actual 0x218
compiler frame are native-aligned, but the source lacks
one genuine original CODE byte and whole physical
COFF absolute sites and jump displacements differ
because of the width/register allocation problems.

Reproduce only these TWO affected complete original-shaped
58KB parent compilations and original PE field checks:

    scripts/repo-python scripts/verify-fighter-whole-58kb-pe-targets-f1025.py

Original x86/COFF full target records and native audit
receipts are preserved under ignored
.analysis/f1025-original-58kb-pe/ and
.analysis/f1025-58kb-pe-target-audit/.
The canonical F917 whole-actor C++/OBJ/PDB compiler
evidence remains under .analysis/f917-native-burst-x87-verified/.

**Zero newly accepted complete game callable CODE bytes.
No corpus-wide 979-unit cold replay.**
