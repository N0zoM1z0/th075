# F1069 — Original 852B action `0x331` and its three actual parent-Y offsets

**Historical F1069 checkpoint:** the live partial parent has since gained genuine original [F1071 `0x323/0x324` gameplay](CHARACTEROBJECT_NATIVE_323_324_F1071.md), correcting `0x325` GPR phase. The live verifier now audits 33 real states and current source geometry; numbers below are for this earlier 31-state source snapshot. The original F1069 PE fields and 331 gameplay still verify.

The independently authored Japanese TH075 1.11 original
`CharacterObject::Advance` at `0050A580` is ONE **81,539 original
CODE B /17,435-x86** callable, followed by separately owned
**567 afterRET switch DATA B**. Its current original-shaped C++ is
partial and **NONEXACT**: inner switch states are not separate
independently authored exact original function credit.

Original action `0x331` at **`0050D53A..0050D88E`** is **852
original CODE B /185 real x86** and previously emitted only a
synthetic diagnostic marker. F1069 re-reads the actual original PE,
then restores native gameplay into the **entire** tracked one-switch
normal MSVC7.1 C++ parent rather than an isolated byte sketch.

This game state copies the parent-facing byte to the actor+0x66.
Three **separate original parent-action ranges** control position:

- Original parent `(0x95,0x9A)` at own stage 0 uses native
  `float(facing * 57)` added to parent X+0x44 and adds true
  float `00659138` to the parent Y+0x48.
- Parent `(0x99,0x9E)` at own stage 0 uses the same authentic
  facing-dependent X but different original Y float `00658264`.
- Parent action exactly `0x9E` and own stage 0 uses the original
  Y offset at `00657888`.

Source preserves the actual **parent Y first** x87 operand order by
borrowing `*(&F1037_POSITION(PARENT).yPosition)` before the global
float, not swapping operands in an algebraically equivalent source.
When parent action is outside `[0x96,0x9E]` at own stage 0, the
original sets real auxiliary action 1 and clears the parent+0xF0A
WORD. At the real initial `(stage, frame, +0xD8)==(0,0,0)`, the
actor initializes native `0040FBB0`, both scale floats to 1.0f,
all four opacity bytes to 0xFF, float +0x2C to the authentic
**50.0f bit pattern 0x42480000**, and +0xD8 to 1. It subsequently
advances true +0x30 float using original `00657480`, lowers alpha
by 30 after stage zero, reads native `0040FA30`, expires through
`0045B830` or sets stage-1/frame-zero auxiliary action zero through
`0040FB40`.

## Original physical PE evidence

The new state was actually compiled inside the **full current
partial one-switch C++ parent** under pinned ordinary VC7.1. The
independent original PE was read for **the entire 81,539B** original
and all 92 original DIR32 switch label equivalence partitions and
199 actual sparse-index bytes. It was compared at each actual
`0x331` original instruction ordinal and all nine physical nonlocal
call/global PE fields were resolved from the native executable, not
assumed from source symbol spelling.

| Genuine original 0x331 | Actual verified source |
| --- | ---: |
| Native CODE/x86 | **852B /185** |
| Selected natural C++ inner CODE/x86 | 661B /185 |
| Original matching mnemonic ordinals | **185/185** |
| Original matching GPR operand roles | **185/185** |
| Original matching instruction widths | **122/185** |
| Actual native nonlocal PE targets | **9/9** (four calls +five globals) |
| Parent Y globals at original ordinals | 32, 62, 87; correctly typed |
| Native float +0x2C immediate | `0x42480000`, verified |

The first source compile already matched all 185 x86 mnemonic and
register-role positions, all nine original PE field types, offsets
and destinations and original native float immediate. **These are
not whole-function byte exactness.** The original 81KB owner still
has `ESP 0x3A0` and saved receiver EBP-0xAC, whereas the selected
partial C++ emits `ESP 0xF8`, EBP-0x4C saved receiver, and many other
original cases remain unimplemented marker handlers.

F1069 also extends the tracked original-PE live verifier
`scripts/verify-characterobject-current-recovered-f1068.py` so it
rebuilds **only the current one changed whole partial parent**, and
independently checks **all 31 recovered game-state interiors**:
**22,813 original native state CODE B /4,875 original x86**,
**4,875/4,875 original mnemonic and GPR-role matches**,
**371/371 physically authentic original PE nonlocal fields**,
92 DIR32 case labels and 199 sparse-map bytes. The selected partial
function currently emits **19,232 CODE B /5,041 x86**, including
18,171 compiled C++ CODE B corresponding to the recovered interior
cases. It does not represent all 81KB of original game code.

Reproduce **only this one affected whole parent**, not the
979 accepted exact-function corpus:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Normal C++/COFF/PDB/compiler and actual original PE receipts remain
under ignored `.analysis/f1069-object331/` and
`.analysis/f1068-boss-live-all-native/`.
**Newly accepted exact whole original GAME CODE = 0B.**
