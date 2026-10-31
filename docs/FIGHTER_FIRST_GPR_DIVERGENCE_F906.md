# F906 — First current-parent fighter register divergence is native action 0x59

The pinned Japanese TH075 v1.11 original fighter
005214B0 is **46,755 callable CODE bytes / 13,230
x86 instructions**. Its current ordinary VC7.1 source
is **46,754 B / 13,230 x86**, with five known original
instruction-width differences and shifted PE field
positions. The whole function is **NONEXACT**.

Full-function x86 ordinal comparison independently
pinpoints the **first GPR operand difference** at
**whole ordinal 2103, original PE address 0052327A**,
the beginning of original state 0x59. The preceding
2,103 original x86 instructions have matching
source register-operand roles. This *does not* imply
the preceding region's relocations or entire CODE
are byte-exact.

Original 0x59 is **356 complete inner CODE B /
95 x86 /16 actual typed PE fields**, including
genuine __ftol2 calls to original 006406AC.
The tracked verifier resolves all sixteen real PE
call/global destinations and confirms identical
opcode mnemonics and widths in the selected parent.
Nevertheless this state has **19 incorrect GPR operand
roles** and the entire current parent has **2,736
incorrect GPR-role instruction operands**.

F906 builds **33 complete current-fighter normal
VC7.1 /Od source variants** using only actual original
game fields and stage3 floating expressions: read
lvalues, native stage/frame conditions, signed short
conversion to float, original getter, real movement
operators, contact arithmetic and legitimate float
reference ownership. No fake locals or hardcoded
register assembly are introduced.

Of these, 29 still compile to 13,230 whole x86
instructions, and **none reduces the 19 wrong
state-0x59 GPR roles or 2,736 whole-parent GPR
differences**. Other genuinely used source changes
introduce additional x86 and are not cropped to
fit the original 95-instruction case.

This establishes where further register-allocation
investigation should begin; earlier mode63 or
252/254 source grammar cannot be assumed to
account for all remaining native mismatch.

Reproduce only this affected whole fighter:

    scripts/repo-python scripts/verify-scripted-fighter-first-gpr-f906.py

Complete alternative C++, VC7.1 COFF/PDB,
compiler logs and physical PE receipts remain
in ignored .analysis/f906-fighter-first-gpr/.
No independently accepted exact callable CODE
and no mass cold replay.
