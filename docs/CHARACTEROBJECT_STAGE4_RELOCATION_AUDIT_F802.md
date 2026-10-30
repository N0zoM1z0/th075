# F802 — Original 33KB CharacterObject stage-four source and PE relocation audit

**No whole authored game function accepted.** The pinned Japanese
TH075 v1.11 PE has a complete authored CharacterObject
`0x004EBDA0` native function with **33,293 CODE B,
8,789 x86**, plus **438 separate after-RET jump DATA B**.
The selected whole-source VC7.1 baseline has matching
native instruction lengths, positions and all **682 physically
attested PE/COFF relocation fields**, but still **137
real wrong nonfield bytes** across native `0x38D/0x38E/0x3E3`
GPR phases.

F802 compiles **22 complete original-shaped VC7.1 C++
parents** instead of cropping `0x38D` into a toy function.
All real calls and source code are retained. Candidates
test semantics-preserving variants near the *first*
register-phase failure at native `004F344C`:
stage `<3` versus reversed/negated/<=2,
stage equality 4 with reversed/negated/cast operands,
individually borrowed `F32(0x1C/0x20)`
float fades, global constant reference expressions,
compound-addition grammar, swapped real independent
float update order, natural float scale `*= / =*`
expressions, and real unsigned-color threshold grammar.

## Independent physical results

| Whole source class | Result against original PE |
| --- | --- |
| **17** variants with genuine complete original physical relocation mappings | Each still has **at least 137 wrong original nonfield bytes** |
| **5** plausible compound-update variants | **Incorrect original PE relocations despite the same total function size and 682 compiler COFF references** |

The five incorrectly relocated candidates are
`left-fade-compound`, `right-fade-compound`,
`stage4-multiply-compound`, `stage4-combined-refs`
and `stage4-all-mix`. Their float instruction
widths change, moving authentic PE global-field offsets;
a naïve byte comparator masking the candidate's
relocations can report numbers such as `140` even though
the source reference no longer binds to the original
global at the same PE field. Those diagnostic mismatch
counts **must not** be treated as accepted comparable
original machine bytes.

For each candidate the verifier independently invokes the
native PE relocation checker from F593, resolving **all 622
CODE plus 60 after-RET jump table fields**, with original
physical source target addresses, zero addends, kinds,
internal handler offsets and external decorated symbols.
A false binding is rejected even if the entire emitted
CODE+DATA happens to be 33,731 B and the x86 count is 8,789.
The native source baseline preserves **30,866/31,003**
comparable bytes with 137 genuine mismatches, not
near-exact callable CODE.

Reproduce **only these affected giant source variants**:

```bash
scripts/repo-python scripts/verify-characterobject-stage4-grammar-f802.py
```

Output sources, compiler logs/COFF objects, and physical
original PE result summary are retained under
`.analysis/f802-character-stage4-grammar/`. This is
a source-grammar/relocation *negative* study, not
a mask waiver, complete owner-layout claim, original
binary patch or all-unit cold replay. No new
authored exact functions or bytes are credited.
