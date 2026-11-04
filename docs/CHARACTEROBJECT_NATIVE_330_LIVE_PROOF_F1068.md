# F1068 — Real 960B action `0x330` and a live, full-parent original-PE verifier for 30 game states

**Historical F1068 checkpoint:** genuine [F1069 original `0x331`](CHARACTEROBJECT_NATIVE_331_F1069.md) has since been restored. The live verifier now audits **31** recovered states (not the earlier 30) with current parent geometry. Original 0x330 x87 JNP and all 16 physical PE fields remain correct; figures below describe this older bounded checkpoint.

The original pinned Japanese TH075 v1.11 game contains **one**
independently authored `CharacterObject::Advance` at `0050A580`:
**81,539 original CODE B /17,435 x86**, followed by authentic
**567 independently owned afterRET sparse-switch DATA bytes**.
The selected partial source is still **NONEXACT**; no interior case
is a separately authored original callable or new accepted CODE byte.

## Actually reconstruct native `0x330` from the PE, not a marker

Original `0x330` is the physical state at
**`0050D17A..0050D53A`: 960 native CODE bytes /209 x86**.
Previous partial C++ source only wrote a synthetic marker there.
`CharacterObjectBoss330F1068.inc` now implements genuine game C++:

- Native parent action in `(0x45,0x96)` and own animation stage `<3`
  gates real `0045B830` cleanup, **five-shot** loop of original
  `0x3E4` objects through the authentic parent `00453A70`, and
  conditional parent+0xEFA reset / extra `0x3E3` projectile.
- Original actor +0x7C hit status 6 increments a real +0x80 WORD and
  resets status before stage handling. On stage/frame `(0,0)`, it
  initializes native motion through `0040FBB0` with the **real
  32-bit float input 60.0f** (`0x42700000`), scale, opacity, action
  fields, vertical speed 26.5f, actual parent `00453D40(3)` and
  original spawned action `0x345`.
- Subsequent source advances real float Y and velocity, stage-1
  orientation, actual constants `00657878`, `0065747C` and
  `0065782C`, stage-2 vertical update, collision/action state,
  native `0040FB40(3)`, parent `00453D40(5)` and original completion
  `0040FA30` / `0045B830`, plus the authentic stage-2/frame-zero
  parent `00453D40(4)` and X speed `-20.0f`.

The actual helper's source declaration was clarified to reflect its
physically observed **floating middle motion argument**; earlier
states only supplied a literal zero there. This is a natural game
C++ source parameter, not a bitwise patch or synthetic GPR helper.
All 16 original physical nonlocal PE call/global fields of state
`0x330` remain at the authentic original x86 ordinals and resolve to
the independently read original PE targets.

### Important original x87 branch, not just matching mnemonics

Original game state ordinal 163 uses the real x87
`FCOMP [0065782C]`, then `FNSTSW AX`, `TEST AH,0x41`, **`JNP`**
condition. A first natural C++ `Y+velocity >= ground` emitted
`TEST AH,1; JNE`, and a second `Y+velocity > ground` emitted
`TEST AH,0x41; JNE`. Neither is the original control flow, despite
otherwise correct x87 float arithmetic and true-game logic.
The semantically precise source **`!(Y + velocity <= ground)`**
reproduces the genuine native `TEST AH,0x41; JNP` branch while
preserving C++ float *unordered* comparison behavior. There are no
manual assembly instructions, artificial locals, altered code bytes
or branch-patch relocations.

| Entire original game state `0x330` | Normal pinned VC7.1 result |
| --- | ---: |
| Actual original CODE/x86 | **960B /209** |
| Current source inner CODE/x86 | 764B /209 |
| Original ordered mnemonics and GPR roles | **209/209 each** |
| Original x86 instruction widths | 144/209 |
| Physical original PE call/global fields | **16/16** (11 calls, five globals) |
| Actual native float immediate | `0x42700000` (60.0f), verified |
| Original x87 test/branch | `TEST AH,0x41; JNP`, verified |

## New current-source verifier: do not depend on old checkpoint sizes

The tracked `verify-characterobject-current-recovered-f1068.py`
provides a *single bounded live validation* for **every one of the
30 currently recovered actual game-state interiors**, compiled as
**ONE entire original-shaped partial parent**, not thirty cropped
independent functions. It has a fixed list of genuine native
recovered action IDs and independently expected counts of physical
nonlocal fields so that silently dropping a real call cannot pass.
For each physical game action, it:

1. Reads the pinned Japanese original full **81,539B CODE** and SHA,
   original 17,435-x86 geometry, entire genuine 92-slot DIR32 jump
   equivalence partition and every original 199 sparse-map byte.
2. Freshly builds the entire selected tracked parent under pinned
   normal MSVC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, using the real
   original native case boundaries and corresponding generated
   source case labels, never assuming a case is separately callable.
3. Verifies **every ordered original opcode mnemonic and GPR role**,
   and each actual original PE external REL32/DIR32 operand by
   original instruction ordinal, physical field byte, typed target
   arithmetic and source symbol target identity. It also checks
   real `0x333/0x334/0x336` float immediates and the `0x330`
   original `60.0f`/`JNP` instruction grammar.
4. Reports the **original-size-versus-source-size** gap and rejects
   assigning new exact original function or byte credit. It does
   **not** run the 979-unit cold replay.

Latest verified live partial source:

| Property | Independent original | Selected C++ partial parent |
| --- | ---: | ---: |
| Entire callable CODE | **81,539B** | **18,564B** |
| Entire function x86 | **17,435** | **4,858** |
| AfterRET table | 92 DIR32 +199 map B | physical partitions and literals match |
| Reconstructed actual game cases | 30 interiors | 30 genuine C++ case bodies, others markers |
| Original interior native CODE /x86 covered by these cases | **21,961B /4,690** | 17,488B /4,690 |
| Original mnemonic/GPR roles in these interiors | **4,690/4,690** | matches |
| Physically correct original PE call/global fields | **362/362** | matches |
| Actual whole game callable byte-exact? | **No** | **No** |
| Newly accepted authored whole original bytes | **0B** | — |

The original entire native game frame remains `ESP 0x3A0`, original
saved receiver EBP-`0xAC`, versus present incomplete parent `ESP
0xEC` / EBP-`0x4C`, with many missing game states and real width/
branch discrepancies. The source-generated case interiors are
*not* byte-exact original callable CODE; the 979 previously exact
complete functions and 43.99% authored coverage remain unchanged.

Reproduce the **one affected whole game parent only**:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Optional focused current-source original proofs remain available for
`0x333/334/336`, `0x335`, `0x338/339`, `0x33A`, five large 402-x86
cases and the x87 Y operand-order grammar. All new normal C++/COFF/PDB,
compiler logs and original PE receipts are retained under ignored
`.analysis/f1068-boss-live-all-native/` and `.analysis/f1068-object330/`.
No manual registers, original PE modification, cropped-callable
credit, mass cold replay or falsely accepted new original CODE bytes.
