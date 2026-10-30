# F790 — Whole-parent native mode-63 stage and outer-control source limits

**Original PE/VC7.1 compiler evidence; complete fighter remains nonexact.**

The pinned Japanese TH075 v1.11 original fighter
`0x00543210` has **58,294 callable CODE bytes, 16,471
x86 instructions and 943 independently owned post-RET switch
DATA bytes**. The best F781 natural giant source emits 58,293
callable CODE bytes /16,471 instructions. Its independently
reviewed original action `0x63` occupies
`00545ADE..00545DA0`: **706 B /189 x86 /15 real
PE/COFF fields**; the emitted source still has 705 B /189
x86 and the exact same ordered mnemonics, but many real GPR
operands are incorrect.

Fresh native physical checks isolate three code-size-affecting
comparisons against 150 (the observed owner stage limit):

| Original case ordinal | Original target PE | Whole VC7.1 source |
| --- | --- | --- |
| 18 | `CMP EDX,0x96`, 6 B | `CMP EAX,0x96`, 5 B |
| 61 | `CMP EAX,0x96`, 5 B | `CMP ECX,0x96`, 6 B |
| 84 | `CMP EDX,0x96`, 6 B | `CMP EAX,0x96`, 5 B |

They explain the final **one-byte CODE length shortfall**,
but are not the only remaining byte differences, so simply
restoring the whole function length would not establish exactness.

## Seven fresh complete 58KB parent compiles

The tracked `scripts/verify-fighter-mode63-controlflow-f790.py`
regenerates the F781 whole fighter, injects one original-shaped
normal C++ source expression per variant and compiles **the
entire affected giant** using pinned VC7.1 in serial:

| Ordinary C++ hypothesis | Whole emitted CODE B | Physical original action 0x63 |
| --- | ---: | --- |
| Current stage comparison/control | 58,293 | 705 B; wrong CMP widths 18/61/84 |
| Equivalent reversed `150 > stage` | 58,293 | Same wrong widths |
| Explicit signed-int conversion | 58,293 | Same wrong widths |
| Negated `!(stage >= 150)` | 58,293 | Same wrong widths |
| Different boundary `stage <= 149` | 58,293 | Changed native conditional mnemonics at 19/39/62/85 |
| Reversed short-circuit test ordering | 58,293 | Different initial branch grammar, mnemonics at 0/1/2/3/5/6 |
| `static_cast<bool>(flag)` in control | 58,300 | 712-B altered case; wrong x86 geometry |

Every selected parent has **1,863 actual compiler COFF field
records** and 943 B of after-RET switch DATA; altered cases are
never cropped. Baseline and the three compiler-equivalent stage
expressions each independently revalidate *all fifteen native
mode-63 original PE/COFF fields*. Baseline additionally checks
the real F781 **four-entry common getter**, the complete original
**46-B shared suffix**, all 68 native physical fields of the
five early cases `0x58/0x59/0x60/0x61/0x63` and the genuine
943B DATA including **156 original DIR32 switch labels and
319/319 nonfield sparse-map bytes**.

Other physically checked early-case nonrelocation operand
differences remain `0x59:19`, `0x60:98`,
`0x61:101` (the adjacent 469B 0x58 case remains
nonfield-exact outside true external shared-tail JMPs).
These are measured **in the F790 freshly compiled complete
parent**, not inherited from old F626 assumptions.

The ordinary stage-control and borrowed-type hypotheses are
therefore either compiler-identical to the nonexact source
or introduce new, objectively wrong original x86 geometry.
Do **not** patch GPR bytes, reinterpret an original stage
predicate's limit, add unused locals, or claim exact credit.

Targeted rerun:

```bash
scripts/repo-python scripts/verify-fighter-mode63-controlflow-f790.py
```

Generated original-shaped whole C++, OBJ/PDB, native comparison
JSON and logs are retained in local ignored
`.analysis/f790-fighter-mode63-controls/` for later source
phase exploration. No all-979-unit replay and **zero new
formally accepted whole-boss CODE**. The independently reviewed
authored origin of the entire boss remains unchanged.
