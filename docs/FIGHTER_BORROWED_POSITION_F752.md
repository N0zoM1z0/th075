# F752 — genuine borrowed actor/opponent position members restore original 05D/05E x87 FCOMP grammar

**Substantive exact-geometry C++ source recovery in the complete original
58KB fighter, but still NOT whole-game-function byte exact.** The pinned
original is the user-provided Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The *authored callable function* begins at `00543210`, comprises **58,294
original CODE bytes** and owns another **943 original after-RET switch
DATA bytes**. Its internal action cases `05D/05E` are NOT separately
callable authored original functions; source-correct interiors alone
cannot earn any formal exact game CODE.

## Independent full original physical case evidence

| Original whole physical inner action | Complete original native interval | Previous full-parent C++ F749 | New full-parent C++ F752 | True original PE/COFF fields |
| --- | --- | --- | --- | ---: |
| `0x05D` | `0054526D..005453BE` | **341 B /103 x86**, 2 nonnative x87 loads | **337 B /101 original x86** | **8/8**, all original physical owner ordinals |
| `0x05E` | `005453BE..0054550F` | **341 B /103 x86**, 2 nonnative x87 loads | **337 B /101 original x86** | **8/8**, all original physical owner ordinals |
| **Both** | | 682 generated B/206 x86 | **674 generated B/202 native x86** | **16/16 typed relocations** |

The older [`FighterEarlyBounceF747.inc`](../probes/FighterEarlyBounceF747.inc)
expressed each true game-facing comparison through generic raw
`float*` pointer arithmetic, such as
`F32(0x44) > *reinterpret_cast<float*>(OWNER+0x44)`. The physical
original x86 comparison at native ordinals **59 and 69** is:

```asm
MOV   EAX, [EDX+0x2E8]   ; borrowed opponent pointer
MOV   ECX, [EBP-0x44]    ; real native fighter this
FLD   DWORD PTR [ECX+0x44]
FCOMP DWORD PTR [EAX+0x44]
FNSTSW AX
TEST  AH,0x41
JNE   original_skip
```

(The second independent comparison tests `AH,5` and branches `JP`.)
The raw pointer C++ source instead generated an extra `FLD` for the
opponent and a `FCOMPP`, producing **103** actual source x86 for
101 original x86. Earlier F747 explored eight genuinely compiled
whole-parent raw lvalue/const/volatile/reversal hypotheses; those
did not restore the native x87 grammar.

### Correcting an overgeneralized earlier hypothesis

The issue was not a required artificial x87 instruction or an
unreachable internal jump. The original code accesses two **real
float data members at native offset `+0x44`**. New tracked
[`FighterEarlyBounceTypedF752.inc`](../probes/FighterEarlyBounceTypedF752.inc)
expresses the actual observed borrowed actor and opponent positions
as C++ object member lvalues, with a **non-instantiated borrowed
view** (`FighterBorrowedXViewF752`) containing only the 68 bytes
preceding the observed X and a float `xAt44`. This is a structural
*view* of already existing game object memory: no fake used or
unused stack variable, original-class identity claim, fabricated
allocation, padding instruction, ASM, hand-patched relocations or
original executable byte copying. The critical source comparison is:

```cpp
if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44 >
    reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44)
    *reinterpret_cast<signed char*>(RAW+0x66) = -1;
```

Both comparator directions and both original cases use the same
actual typed actor/opponent member access, and compiler output
naturally switches from two x87 loads/`FCOMPP` to **`FLD ACTOR;
FCOMP OPPONENT`** with exact original ordered native mnemonics,
widths, GPR roles, `FNSTSW` and flag handling. The original
signed resource and stage/game-state semantics and true member
writes remain unchanged.

### Genuine strict machine-code geometry, explicit whole-game negatives

In a newly compiled ONE complete original-shaped 58KB VC7.1 parent,
each native original physical case has all **101 original x86
opcode and width positions**, the correct complete **337-byte
body**, **zero normalized GPR/CFG differences**, and all **8
physical original typed PE/COFF fields** at their **true native
x86 owning instructions** with matching decorated source symbols,
`REL32`/`DIR32`, real native PE targets and zero addends. Both
case intervals have their real `this` saved at **`EBP−0x44`**,
not the older wrong `−0x3C`.

A separate comparison of complete native physical 337-byte source
bodies finds **301/305 identical nonrelocation native bytes per
case**. The only four nonfield byte differences occur at **CODE
relative offsets `+103,+104,+333,+334`**. These are the
significant displacement bytes in the two legitimate `JMP`s
from the case to the whole giant's original **shared native
continuation `005515C2`**. Both newly compiled source jumps
instead target the same *actual decoded source giant tail*
`0xD78A` in its own still-NONEXACT larger function layout.
No source/PE branch target was invented, and those differences
**MUST NOT** be masked as accepted original whole-function CODE.
The original entire 58KB game source is still not byte-exact.

### Real independent whole-parent regression proof

[`scripts/verify-fighter-borrowed-position-f752.py`](../scripts/verify-fighter-borrowed-position-f752.py)
recreates and serially compiles one entire original-shaped fighter
using all tracked normal C++ source fragments from F728 through
F749. It substitutes only the new true member-typed source for
the previous F747 early cases, rereads native complete physical
boundaries and source COFF fields through the pinned original PE,
and checks original `05D/05E` mnemonics, widths, native direct
`FCOMP` at 59/69, native GPR roles, all 16 typed original fields,
and exactly the four **honest shared-tail branch displacement
negative bytes** per case.

It also independently verifies the other four original early
`059/060/061/062` sources, true original `EBP−0x44` saved
receiver and their already proven genuine loop/x87 scratch
slots; then checks **27 previously source-backed physically
bounded original action interiors**, zero normalized GPR errors
in this freshly generated parent, and retains the `190` original
**276-B versus 266-B** width negative. The complete independent
**943-B original after-RET switch DATA** is also compared,
including all **156 physical original/source DIR32 jump-table
entries** to real decoded x86 instruction starts and all other
**319/319 original sparse bytes** identical. No jump-table DATA
is credited as game CODE. The previous independent F749 verifier
retains its original raw-pointer negative context and defaults.

```bash
scripts/repo-python scripts/verify-fighter-borrowed-position-f752.py
scripts/repo-python scripts/verify-fighter-early-resource-f749.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Seven whole-parent C++ semantic hypotheses (baseline plus six
new genuine actor/opponent observed member-view and array-index
variants) were serially compiled; their actual C++/OBJ/PDB,
compiler logs, pinned PE source controls and results are retained
under ignored `.analysis/f752-fighter-native-borrowed-position/`.
Only **both** actor and opponent typed borrowed members restored
the complete original FCOMP mnemonic order; one-sided typing
alone was insufficient, despite some recovering 337B size.

**Official ledger remains 967 canonical exact complete authored
functions /864,219 original CODE B (43.79% reviewed)**.
No truncation, standalone internal case exactness, unchanged giant
whole-function credit, mass 967-unit cold replay or modified
original PE. The 98% objective remains incomplete.
