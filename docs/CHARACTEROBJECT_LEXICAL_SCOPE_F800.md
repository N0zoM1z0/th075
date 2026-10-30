# F800 — Complete CharacterObject case-scope source cannot repair the native register phase

The real user-supplied Japanese TH075 1.11 PE contains an authored
whole character state advance at `004EBDA0`, with **33,293 native
CODE bytes**, **8,789 x86 instructions**, and **438 bytes of independent
after-RET switch DATA**. F596's current normal VC7.1 source has
**137 genuine non-relocation machine-byte differences** in action
`0x38D/0x38E/0x3E3`; all source instruction positions, mnemonics
and widths otherwise reproduce the original.

## F800 independently tests switch-case lexical scope

Eleven *complete original-shaped* VC7.1 source builds change only
real C++ lexical braces surrounding the 0x38B, 0x38C, 0x38D, 0x38E,
0x3E3 and 0x3E4 switch-case bodies. The variants include independent
braces, adjacent pairs, and combined 0x38B–0x38E ranges. Every
case's actual logic, fields, native-call lifetimes and switch
fall-through semantics are retained. Removing superfluous braces is a
natural C++ source test, not an artificial padding instruction.

**All eleven entire generated COFF function byte arrays are
identical**, including all **33,293 CODE + 438 afterRET DATA bytes**.
All 682 actual typed PE/COFF relocation identities also agree
(offset, kind, addend, locally resolved original label position or
external symbol). This is strictly stronger than simply getting an
equal number of wrong bytes.

The tracked verifier re-reads the actual target PE and independently
resolves every original relocation and jump-table target via F593's
physical target checker, including 622 CODE records and 60 table
records, rather than trusting Ghidra names or a previous byte mask.
Original and source both emit 8,789 complete x86 instruction
positions; each retains **137 actual wrong nonfield GPR bytes**,
beginning at original PE `004F344C`. Complete original
0x38D/0x38E/0x3E3 remains nonexact.

Reproduce without replaying the accepted corpus:

```bash
scripts/repo-python scripts/verify-characterobject-scope-phase-f800.py
```

Sources, compiler output and a physical comparison summary are
regenerated under `.analysis/f800-character-scope/`. This
eliminates lexical-brace-only source hypotheses for the currently
unmatched register phases, **not** genuine semantic lifetime
differences from earlier game logic. No whole original callable
function, subcase or jump DATA is accepted as new exact CODE.
