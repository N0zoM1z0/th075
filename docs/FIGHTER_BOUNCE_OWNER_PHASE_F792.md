# F792 — Real 0x59 bounce source owner/register phase, eight full fighter builds

**Native provenance-verified giant source study; NOT exact whole CODE.**
Original user-supplied Japanese TH075 v1.11 has a *single*
58,294-B/16,471-x86 fighter function at `0x00543210` plus
943 after-RET switch DATA bytes. The current fully reproduced
F781 ordinary VC7.1 parent still emits 58,293 B/16,471
x86, without falsely crediting any internal case as callable CODE.

The true complete original interior action `0x59` at
`00545109..0054526D` has 356 CODE B, 95 x86, and
16 independently typed actual PE/COFF relocation fields.
A fresh comparison of the *entire* source parent confirms
the original branch/instruction order and every x86 width,
yet the first 25 machine instructions contain **19
physically wrong GPR-operand bytes** (EAX/ECX/EDX rotation);
all 16 real source references retain original PE addresses.

Eight separate whole-parent normal C++ builds try independent
source hypotheses that do real game work:
- original baseline;
- reversed stage comparison `1 < stage`;
- reversed floating comparison;
- addition of real current position/velocity in swapped order;
- borrowed physically typed `+0x62` actor stage;
- borrowed physically typed `+0x54/+0x5C` velocity/drag;
- actual writable float `+0x30` lvalue expression;
- genuine signed-short/int guard conversion.

Each compiled entire 58,293-B/16,471-x86 parent contains the
356-B/95-x86 complete case and all 16 independently verified
native PE reference fields. Seven still differ in **19
real unmasked nonfield GPR operand bytes**; swapping the
float add operands regresses to **21**, despite still matching
every mnemonic and instruction width. The original 0x58
preceding complete 469-B case remains nonfield-exact outside
genuine shared-parent jumps; actual 0x60 and 0x61
still have 98 and 101 wrong native GPR operand bytes
respectively. Original 943-B post-RET DATA, 156 native
DIR32 labels, 319/319 sparse-map original bytes and
the true 46-B shared getter suffix are rechecked
inside the freshly built baseline parent.

Only the affected complete fighter was compiled (eight variants)
and independently compared to the original PE. No fake
locals/returns, target patches, split-case clipping, ABI
misdeclarations, or full accepted-unit corpus replay.

Reproduce the whole-source original comparison with:

```bash
scripts/repo-python scripts/verify-fighter-bounce-owner-phase-f792.py
```

New source/probe objects and physical comparison summary are
under ignored `.analysis/f792-fighter59/`. Actual
source and historical owner name are still provisional;
the 58KB whole original remains NONEXACT and formally
credited CODE stays unchanged.
