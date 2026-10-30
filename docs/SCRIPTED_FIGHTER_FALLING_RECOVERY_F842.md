# F842 — Three real 12C/12D/12E falling recovery states in the growing 46KB fighter

The SHA-pinned Japanese TH075 v1.11 original fighter at
005214B0 contains **46,755 callable CODE B /13,230 x86**
and 901 separately owned afterRET packed dispatch DATA
bytes. F841 reconstructed the preceding CC/CD/CE cases;
F842 adds the next three actual native falling/recovery
states to one affected whole VC7.1 C++ translation unit.

| Actual original state | Full original native interior | Typed original PE fields | Native action / animation parameters |
| --- | --- | ---: | --- |
| 12C | **207 B /59 x86** | 6 | Set action 0, prepare at stage 1, animation 0x1B |
| 12D | **219 B /61 x86** | 6 | Set action 0, prepare at stage 3, animation 0x1C; clear actual short +0xF00 |
| 12E | **207 B /59 x86** | 6 | Set action 2, prepare at stage 2, animation 0x1C |

These parameters come from the selected fighter's **physical
original PE**, not from F653's distinct actor 00543210.
That older source used stage 2/4/2 and animation 0x1B/
0x1D/0x1D. Copying those parameters would be an original-
game behavior error. The tracked natural C++ uses real
stage/frame and falling-flag checks, height subtraction at
00658058, ground x87 threshold at 0065782C, actual
00453E20/0040FA30/0040FAC0/00453D60 helper calls,
and the original zero of +0xF00 only for state 12D.

## Selected whole-parent physical proof

F842 first regenerates and independently verifies the
F841 native-backed giant parent, then freshly builds the
entire affected new normal VC7.1 C++ source. Generated
callable code grows from **21,322 B/5,793 x86**
to **21,910 B/5,966 x86**.

The verifier independently checks all three new entire
real original case extents, native x86 mnemonics, instruction
widths and relative locations, and all **18 physically
typed PE/COFF field locations, kinds, zero addends,
original native destinations and source symbols**.
Each of the complete 207/219/207-B native cases has
**only two nonrelocation byte differences** in the
authentic final JMP operand pointing at original whole
fighter epilogue 0052CB4F. They are explicitly NOT
ignored or accepted as exact callable game CODE.

The same newly compiled whole source independently
rechecks ELEVEN preceding full original C8/C9/CA/CB/
CC/CD/CE/CF/D0/D1/D2 cases with their native PE
fields and their genuine complete-parent epilogue
JMP negatives. All FIVE separately owned original
packed afterRET switch tables are physically verified
against the new COFF dense/sparse mappings.

The natural compiler context shifts again: the 46B/16-x86
common default/getter still has original saved-this
EBP-0x10, correct PE REL32 destinations and instruction
geometry, but **four real native nonrelocation GPR
operand bytes at offsets 10/12/16/19 differ**. The
prior shorter F841 default 34/34 source match therefore
MUST NOT be inherited as a claim about the larger parent.

Selected reproducible rerun:

    scripts/repo-python scripts/verify-scripted-fighter-falling-recovery-f842.py

Fresh source, pinned VC7.1 COFF/PDB, original PE
comparisons and verification receipt are retained
under ignored .analysis/f842-scripted-falling-recovery/.
The enclosing original 46,755-B callable giant remains
NONEXACT; no independent case/whole-function authored
CODE accepted, and no all-979-unit cold replay.
