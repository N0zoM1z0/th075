# F572: actual 271-instruction CharacterObject fighter actions, plus seven leaves

**Original Japanese TH075 1.11 native-code source reconstruction evidence,
NOT an exact full original boss.** The pinned PE SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Original CharacterObject giant `004EBDA0` consists of **33,293 complete
native CODE bytes**, with 438 separately owned after-RET jump/index DATA
bytes. The entire original CODE SHA256, first compressed physical switch
and every physical case boundary are validated *before* compiling the
new candidate. Original nominal class names/true member prototypes
remain provisional: C++ borrowed interfaces are derived from thiscall
and original source operations, not asserted to be original class types.

## First seven real complete small action bodies

The first seven original actions `0x320..0x326` are genuinely **13
CODE bytes / 3 native x86 instructions apiece**. Each performs:

```cpp
case 0x320: ResetAt4F4170(); break;
// ... same genuine call statement, but distinct case block for 0x321..0x326
```

The actual original source has seven *different physical handler
addresses*, not seven aliases of one dense table slot. The pinned
VC7.1 /Od C++ emits each distinct `MOV ECX,[saved_this]`, real typed
`REL32` call to original `004F4170`, and `JMP` back to the entire
fighter's common exit, for **21/21 instructions, 91 original CODE
bytes and seven real COFF calls**. These are parts of the large
source function, NOT seven separate independent functions.

## Three genuinely large original game-action bodies

Immediately after these seven leaves, the next three original
physical compressed action IDs are `0x327`, `0x328` and `0x329`.
Each original **complete 271-instruction action body** is reproduced
by ordinary, readable C++ **inside the same generated switch**:

- Real parent actor `+0xE4` / signed state `+0x60` range gate,
  frame phase bound `+0x62 < 5` and genuine `0045B830` reset.
- Actual `for (int iteration=0; iteration<8; ++iteration)` emits
  the original eight effect-creation calls through the parent actor
  at native `00453A70`, with authentic 0x3E4/0x3E3 effect IDs.
- Native `+0xEFA` saturation/return and the actual FPU-derived
  `+0xD8/+0xDA` stage motion/velocity update, using the real
  floating constants at `006590B4`, `00659738` and `00659730`.
- Stage-0 motion updates, state effects (`0040FBB0`, `0040FB70`,
  `0040FB40`), a floating-point effect spawn at `00453A70`,
  `00453D40`, native action query `0040FA30`, and real early exit
  conditions for byte `+0x11`, stage `+0x62`, counter `+0xDC`.

The three source policies must **not** be collapsed into one shared
constant template. From original physical MOV and signed-short
increment instructions:

| Actual native action | Whole original CODE | Native x86 instructions | Initial +0xD8 | Initial +0xDA | Subsequent +0xD8 update | Real COFF fields |
| --- | ---: | ---: | ---: | ---: | --- | ---: |
| `0x327` | 998 B | 271 | −30 | 150 | +3 | 18 |
| `0x328` | 999 B | 271 | 70 | 150 | −2 | 18 |
| `0x329` | 999 B | 271 | −30 | 200 | +4 | 18 |

An important compiler-specific finding: normal
`F32(0x48) = F32(0x48) - F32(0x54)` produces the right x87
arithmetic but loads the saved actor receiver in a different source
order. The equally ordinary and type-valid expression
`F32(0x48) = *(&F32(0x48)) - *(&F32(0x54))` naturally makes VC7.1
emit the **original saved-owner loads before x87 `FLD`**, without
adding locals or any extra code bytes. Also the native actor effect
creation requires a genuine `char` argument on its computed-position
path: passing a promoted `int` instead produces an incorrect
`MOVSX` rather than the original byte `MOV AL`. Both source details
were determined by *compiling and comparing* natural C++, not
inserting original instructions or source padding.

## Fresh physical source/COFF and original case verification

Tracked source:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
Tracked full original-backed source verifier:
[`scripts/verify-characterobject-action-family-f572.py`](../scripts/verify-characterobject-action-family-f572.py).

The verifier cold-compiles **only this newly affected natural C++ TU**
under pinned MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. It then
independently reads the actual original PE, rather than trusting any
ignored experiment or prior report. It verifies every real physical
case boundary through original dense/sparse jump destination bytes,
then requires the *complete* source and original instruction lists to
agree on exact instruction sizes, **all real EAX/ECX/EDX allocations**,
x87 operands, signed-short field usage, true internal relative branch
targets and early exits. It never crops to a matching prefix.

Per every native case, all original direct calls and physical x87
global operands are also matched to a **real compiled COFF `REL32` or
`DIR32` field at the same instruction ordinal**, with the correct
original callee/global identity, source symbol and zero addend.
Only after independently verifying that physical field is a genuine
relocation does the grammar normalize the source object's zero
placeholder (`[0]`) to the authentic original global; no unverified
absolute operands are masked or treated as exact.

**Verification: 10/10 complete original actions, 834/834 x86
instructions, 3,087 native inner CODE bytes, and 61/61 true physical
COFF call/global fields.** The candidate further retains all
**60 physical jump-table `DIR32` COFF labels**, each zero-addend,
original repeated/default handler partitions, **198/198
byte-identical native sparse-index bytes with original SHA256**,
and **438 complete after-RET DATA-shape bytes**.

### Affected-only reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-action-family-f572.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The full native 271-instruction source comparisons, failed alternate
floating expression controls and early 7×13-byte native experiments
are preserved in ignored `.analysis/f572-characterobject-native-actions/`.
The fresh selected C++ OBJ/PDB, compiler log and summary are under
`.analysis/f572-native-action-family/`.

**Exactness boundary:** these 3,087 original inner CODE bytes are
*not independently exact functions*. The complete giant still has
**33,293 original CODE bytes that are unaccepted**, because the
remaining dozens of game-action bodies, full original actor/class
ownership and stack frame remain unreconstructed. There is no new
accepted whole or partial CODE/DATA, no all-unit cold replay,
and no external Factory/Oracle receipt.
