# F1028 — All 2,191 physical PE external targets in original 82KB fighter

Pinned original Japanese TH075 v1.11 fighter 004AC040:
**82,796 complete callable CODE B /22,721 original x86**,
plus 1,126 separately owned afterRET jump-table DATA bytes.
F1020's real shared 2DB ring counter recovered the same
entire normal VC7.1 source CODE size, x86 count, original
0x720 frame and saved receiver EBP−0x64. The whole game
function is STILL NONEXACT.

The
[bounded independent full-native verifier](../scripts/verify-third-fighter-whole-82kb-pe-targets-f1028.py)
freshly builds the selected genuine F1020 entire original-shaped
82KB C++ parent under pinned normal VC7.1, decodes the
actual SHA-pinned Japanese PE, and maps every source
nonlocal REL32/DIR32 entry to its actual native
x86 INSTRUCTION ORDINAL and PHYSICAL OPERAND FIELD OFFSET.
It computes the original native PE destination from the
original machine bytes at that site, not from source-side
symbol names or relaxed relocation masking.

| Entire 82KB fighter evidence | Strict native verification |
| --- | ---: |
| Nonlocal original PE call/global targets | **2,191/2,191** |
| Real source symbols with explicit original address | **2,150/2,150** |
| Native __ftol2 helper calls 006406AC | **41/41** |
| Original CODE-local switch/case fields | **10** |
| Original afterRET switch DIR32 fields | **151/151** |
| Native afterRET nonfield DATA bytes | **522/522** |
| Total pinned normal compiler COFF fields | **2,352** |
| Original/source entire CODE size | **82,796/82,796 B** |
| Original/source entire x86 count | **22,721/22,721** |
| Original/source saved receiver | **EBP−0x64 both** |
| Original/source stack frame | **0x720 both** |
| Wrong original mnemonic ordinals | **0** |

The verification independently checks equality partitions
of all 151 original jump target labels (not just their
count), all 522 original literal nonfield bytes, and
the original opcode positions of every nonlocal global
or function target.

**Remaining mismatches are real:** twelve x86
instruction width positions still differ, while their
signed byte deltas cancel. Across the entire original
fighter **6,958 GPR operand-role instruction positions**
do not match; many physical whole-parent COFF field
positions and relative jump displacements therefore also
differ. The native 2BE three-case register phase
and native 0x58/0x59 predecessor phase remain known
obstacles. Matching 2,191 external PE destinations and
the whole frame does NOT make a complete original
callable byte-exact.

Reproduce this ONE affected full-parent compilation:

    scripts/repo-python scripts/verify-third-fighter-whole-82kb-pe-targets-f1028.py

All 2,191 original physical PE target receipts,
original-source OBJ/PDB and compiler logs remain in
ignored .analysis/f1028-original-82kb-whole-PE/
and .analysis/f1028-82kb-pe-audit/.

**No new exact complete original callable CODE B/functions;
no 979-unit mass cold replay.**
