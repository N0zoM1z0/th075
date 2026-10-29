# F596 — restore three byte-exact original MOV-before-FLD collision evaluations in the 33K CharacterObject boss

**Original Japanese TH075 v1.11 PE / newly compiled ordinary pinned
MSVC VC7.1 C++, not accepted exact whole CODE.** Native executable
SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

F593 reconstructed the *entire* `004EBDA0` giant into a normal C++
`Advance()` with the correct **33,293 native CODE bytes**, **8,789
native x86 instruction boundaries and widths**, **438 separate
after-RET switch DATA bytes**, **622 CODE +60 DATA =682 physical
zero-addend typed original PE/COFF fields**, and every real game
case represented. It still had **155 native nonrelocation byte
differences** of 31,003 comparable CODE+DATA bytes. Exactly three
separate read-only `MOV`/`FLD` instruction pairs were reversed in the
source; the other differences belonged to three real nonexact
GPR-allocation cases `0x38D`, `0x38E`, `0x3E3`.

## The original native C++ evaluation-order reconstruction

This round corrects **three different game-action C++ expressions
in the *same whole* enclosing switch**, and does not add synthetic
stack variables, ASM, patches, fake game behaviors, or short
standalone function credit.

| Entire true original action within the 33K function | Original entire native x86 instructions | Actual native inner CODE bytes | Original game case-local `MOV`/`FLD` ordinals | Entire function ordinals |
| --- | ---: | ---: | --- | --- |
| **`0x32A`** | 248 | 932 B | **186/187** | **1062/1063** |
| **`0x32C`** | 176 | 635 B | **114/115** | **1350/1351** |
| **`0x335`** | 269 | 1,022 B | **146/147** | **2521/2522** |

The genuine Japanese original instructions always first preload a
second game-object register with `MOV`, and only *then* read the
first object's float using `FLD`:

```text
Original 0x32A: MOV EDX,[EBP−0x40]; FLD DWORD PTR [ECX+0x48]
Original 0x32C: MOV EAX,[EBP−0x40]; FLD DWORD PTR [EDX+0x48]
Original 0x335: MOV EDX,[EBP−0x40]; FLD DWORD PTR [ECX+0x48]
```

F593's former ordinary expressions `F32(+0x48) + F32(+0x54)`
and `F32(+0x48) − F32(+0x54)` instead emitted the `FLD` before
the independent register `MOV`. Although those *read-only*
operations were semantically independent and source-order
swapping did not change the game calculation, their bytes
were not the original machine code.

F596 rewrites **only those three original conditional float
expressions**, using normal member lvalues:

```cpp
// In real original cases 0x32A and 0x32C:
*(&F32(0x48)) + *(&F32(0x54)) <= gCompareAt0065782C

// In real original case 0x335:
*(&F32(0x48)) - *(&F32(0x54)) <= gCollisionAt00657888
```

On a newly compiled selected VC7.1 C++ TU, these natural source
expressions **recover the literal original three-byte machine
instructions in both positions of all three pairs**. All six
machine instructions are byte-identical with the pinned original
PE, not merely semantically equivalent or accepted after a
source-normalization waiver. The complete C++ cases 0x32A,
0x32C and 0x335 are now strictly original GPR/x87/relative-CFG
order- and individual-width identical with complete non-COFF
machine-byte agreement, plus physical original PE/COFF fields.

## Whole boss improvement directly verified on all original bytes

| Entire native property of `004EBDA0` and its after-RET DATA | F593 source | **F596 source** |
| --- | ---: | ---: |
| Whole CODE | 33,293 B | **33,293 B** |
| Original x86 instruction positions, same native offsets/widths | 8,789 | **8,789** |
| x86 mnemonics at identical original physical ordinal | 8,783 | **8,789** |
| Physical original CODE plus jump DATA relocations | 682 | **682** |
| Original sparse after-RET compressed indexes byte-identical | 198 B | **198 B** |
| Native non-relocation CODE+DATA bytes comparable | 31,003 | **31,003** |
| Native non-relocation bytes identical | 30,848 | **30,866** |
| Still-different original non-relocation bytes | 155 | **137** |
| Original differing instruction entries | 139 | **133** |
| Native/source remaining reordered `MOV`/`FLD` pairs | 3 | **0** |

F596 improves **18 actual native machine-code bytes** (six
three-byte instructions) *without changing total function size,
x86 branch distances or external call/global source references*.
The complete original PE/COFF object comparator returns
`mismatch` rather than `structural-exact` because **137
nonrelocation bytes over 133 original instruction positions**
still differ. Those are cyclic EAX/ECX/EDX source allocations
in original actions `0x38D`, `0x38E` and the first 31 instructions
of `0x3E3`, with respectively **45, 64, 24 native register role
mismatches**. They are real outstanding reconstruction work.

The previous **56 native full-case source structures**, 8,300
original x86 instruction roles and 31,374 original inner CODE
bytes remain source-verified. This is not 56 independently exact
functions, and the entire 33,293-byte boss remains NONEXACT.
The official accepted authored ledger stays **943 whole exact
functions /862,726 original CODE bytes**, unchanged.

## Strict original-pe-backed reproducer and historical verifier update

The new tracked source is
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
Strict F596 verifier:
[`scripts/verify-characterobject-native-collision-order-f596.py`](../scripts/verify-characterobject-native-collision-order-f596.py).

It rereads the pinned executable, freshly compiles **ONE selected
normal VC7.1 TU** under `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
through F593's whole-original case verifier, checks the original
**8,789 instructions and all 682 true typed zero-addend COFF
source fields**, requires *every* original `MOV`/`FLD` x86
byte in the six locations to be precisely equal, and additionally
checks the complete three native game-action GPR/x87/CFG/source
grammars and all nonrelocation CODE bytes within those cases.
It then requires the specifically measured **30,866/31,003**
whole-original byte comparison and exactly **137** remaining
nonfield byte differences. No arbitrary source-offset mismatch
or untrusted family swap is waived.

Historical F573–F583 original-backed source verifiers remain
functional: their read-pair checks now accept **either** the
previous exact, physically proven read-only pair permutation
**or** the newly byte-identical F596 source order, each
strictly verified by actual original PE instructions and GPR
operands. Summaries no longer automatically claim there is a
source-order difference when current normal source has none.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py
scripts/repo-python scripts/verify-characterobject-five-complex-actions-f592.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Compilation/COFF/whole-original byte proofs are preserved under
ignored `.analysis/f596-characterobject-native-collision-source/`
and `.analysis/f593-characterobject-whole-source/`; native-only
original disassembly, C++ source variants and full comparison
logs are retained under `.analysis/f596-fpu-evaluation/`.
**Zero full cold replay; zero external Oracle; whole giant still
NOT exact.** Continue real original GPR context reconstruction
rather than injecting register-patched bytes or artificial locals.
