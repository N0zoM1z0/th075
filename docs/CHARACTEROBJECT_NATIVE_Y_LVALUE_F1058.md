# F1058 — The real 657888 Y-add original x87 operand is a typed lvalue

The pinned Japanese TH075 1.11 independently authored
CharacterObject::Advance at `0050A580` is **one** unaccepted original
81,539-byte/17,435-x86 game callable, with 567 separate afterRET
sparse-switch DATA bytes. Earlier F1057 correctly reconstructed
five authentic 1,908-byte/402-x86 **inner** action handlers and their
original 33 nonlocal call/global targets. A source's entire native
mnemonic count alone did not make its physical relocations exact.

The original Japanese PE uses the following real native instruction
ordinals in each of `0x33B`, `0x33D`, `0x33F`, `0x341`, `0x343`:

- Ordinal 261: load the actual *grandparent/target actor* at native
  parent+0x2E8, addressed through the genuine real parent at this+0xE4.
- Ordinal 262: **`FLD dword ptr [target + 0x48]`**, the borrowed target Y.
- Ordinal 263: **`FADD dword ptr [0x00657888]`**, the original real
  global vertical offset.
- Ordinals 277/278: repeat this **actual ordered** Y and global
  addition for the second original condition and its native branch.

These are not arbitrary FPU instruction reorderings. The original
`FADD` operand is an independently actual **original PE DIR32 field**
located in the instruction at ordinal 263 (and 278). A misleading
ordinary C++ `F1037_POSITION(PARENT_GRANDPARENT).yPosition + global`
source compiles under pinned MSVC7.1 /Od with the **same original 402
x86 mnemonic sequence**, but its native-looking `FLD` operand at
ordinal 262 is the *global*, followed by `FADD [targetY]` at 263.
That gives **31/33** original PE target fields per long action, and
is genuinely wrong even though the source/game-real-number equation
seems equivalent and the overall emitted CODE length is unchanged.

## Twelve entire real C++ source alternatives

The new tracked `verify-characterobject-long-y-grammars-f1058.py`
compiles **12 distinct ENTIRE current original-shaped partial boss
parents** with the pinned normal VC7.1 compiler profile. The trial
only varies two genuinely used Y+global source expressions in the
large natural game body and preserves every actual game call, stage,
branch, original physical switch identity, and all other game states.
No ASM, injected padding, register-binding pragmas, fake value locals
or copied PE bytes are used.

For **all twelve whole-source objects**, full generated partial CODE
is **12,836 bytes /3,325 x86**, and each of the five original native
long state intervals has **402/402 original mnemonics**. All 33
actual C++ external symbol fields in each case are mapped back to
its *real native instruction ordinal* and field byte offset and
resolved from independently read actual original PE bytes.

| Natural native C++ source grammar | Original physical PE fields per state | Authentic Y global field ordinals |
| --- | ---: | --- |
| Selected typed borrowed Y with actual `*(&lvalue)` identity | **33/33** | **152, 263, 278** |
| Direct borrowed float pointer dereference | **33/33** | **152, 263, 278** |
| Const float pointer dereference | **33/33** | **152, 263, 278** |
| Reverse addition using a direct pointer field | **33/33** | **152, 263, 278** |
| Old unadorned typed member + global | **31/33** | **152, 262, 277** |
| Direct typed-member dereference and six other natural spellings | **31/33** | **152, 262, 277** |

The original 152 global field is in a different, preceding trajectory
expression, and is correctly located even by the negative candidate.
The **two genuine erroneous original PE fields** are at ordinal
262/277, where the source's global relocation would refer to an
instruction which in the actual original PE is `FLD [targetY]`.
They cannot be made exact by ignoring or masking relocation offsets.

The selected source retains the independently proven `F1037_POSITION`
actual borrowed actor+0x44/+0x48 member view and makes its true
parent Y field **an explicitly dereferenced actual lvalue**. This
makes the ordinary VC7.1 C++ backend emit the original `FLD targetY`
then `FADD [00657888]` order, improving matching native **GPR roles
from 131 to 133 of 402** and original instruction width matches by
four per original 402-instruction case. It simultaneously preserves
all **165/165 genuine original PE external targets** across the five
independently original 1,908-byte long handler extents.

The other source variants remain negative controls retained under
ignored `.analysis/f1058-long-y-grammar/` as full C++/COFF/PDB and
measured actual Japanese PE receipts. The selected F1057 source and
entire-one-Boss native verifier remain tracked separately. F1058
is evidence of **a real source-codegen correction**, not newly
accepted exact whole callable original game CODE.

Reproduce only these affected full partial-parent grammar controls:

    scripts/repo-python scripts/verify-characterobject-long-y-grammars-f1058.py
    scripts/repo-python scripts/verify-characterobject-five-long-actions-f1057.py

**Original complete 81KB callable still NONEXACT; no 979-function
corpus replay, changed original EXE, or invented separate case credit.**
