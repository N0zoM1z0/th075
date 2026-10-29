# F556: full 117-instruction actor action 6/7 C++ inside two giant fighters

**Original Japanese TH075 1.11 native-PE codegen research, NOT a whole-boss
function exact CODE adoption.** Target SHA256 remains
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The complete 50,735-byte original `00486550` and **82,796-byte** original
CharacterMove `004AC040` are independently SHA-verified, including their
complete 6/7-way physical switch tables and after-RET DATA before every
freshly compiled, original-specific source probe. Their **133,531 whole
native CODE bytes remain nonexact**, with no split-case adoption.

## Recovering two 403-byte complete game-action variants

The original first switch's genuine seventh/eighth/ninth `DWORD` targets
bound action **6 and 7** without assuming an arbitrary function length.
Each complete original action is **403 CODE bytes and 117 x86 instructions**,
where the earlier Reimu/F548 controllers had only 362/104. The extra
**13 instructions/41 bytes** implement a game-state-specific bonus check:

```cpp
if (S16(0x62) == 4 && POS54 < g_ExtraThresholdAt00657D14)
    SetAuxActionAt40FB40(5);
```

This is a **real original `FCOMP`** against native global `00657D14`,
followed by `TEST AH,5; JP`, and a genuine `0040FB40(5)` thiscall. The
original `S16(0x62)` stage compare, float member, call target and PUSH
argument are all reread from the original PE. Normal C++ produces the
same instruction/register/branch geometry under the pinned VC7.1 profile.

**Two significant fighter-specific differences are real:**

- Fighter `00486550` transitions to stage **4** and initializes
  `this+0x54` to **16.0f**, `this+0x5C` to **0.75f**.
- CharacterMove `004AC040` transitions to stage **2** with **15.0f**
  and **0.7f** respectively. In its **action 7**, the original C++ must
  clear `FLAG` **before** setting position **5.0f**, velocity and speed;
  the other fighter clears `FLAG` after these three assignments. A uniform
  source-order template gives a false register/instruction match.

Both action 7 cases correctly test the native `this+0x511` byte against
**5** and pass **0xCD** to the native first-state callback, instead of
case 6's **3** and **0xCC**. Actual frame counter increments, native
`00453E20` resets, contact x87 arithmetic and virtual `dword ptr [edx]`
method invocation remain in normal C++. The source does not copy assembly
or original machine bytes.

## Independent affected-only compiler/COFF proof

[`scripts/verify-fighter-extra-stage-action-source.py`](../scripts/verify-fighter-extra-stage-action-source.py)
reconstructs each **entire 117-instruction native block** and generates
one natural C++ switch per original. It reuses only tracked native-backed
opening/switch source generators, with test-only placeholder stores for
all unrelated unfinished cases; original class ownership remains provisional.
Only the **one or two requested small source translation units** compile
using the pinned MSVC 7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` flags.

Across both independently compiled fighter C++ objects:

- **4/4 whole internal cases** are precisely **403/403 native-size bytes**,
  **468/468 true original GPR/x87/branch/operand instruction roles**;
  the emitted bytes still differ in larger original function receiver EBP
  slots and external call relocation operands.
- **32/32 genuine physical COFF call/float reference fields** have the
  correct source symbol, field type and original native instruction ordinal.
  Every case includes eight authentic typed fields: six from the earlier
  core and the two *new* extra-stage DIR32/REL32 fields.
- **314 correct original-style switch `DWORD` COFF destinations** and their
  duplicate/default target partitions, **934 literal original compressed
  index bytes** and all **2,190 after-RET DATA-shape bytes** are checked.
  No separate switch DATA is credited as CODE.

| Whole original fighter | Two native case CODE sizes | Game stage | Native position/speed floats | Action-7 flag ordering | Original switch DWORD COFF | Sparse index bytes |
| --- | --- | ---: | --- | --- | ---: | ---: |
| `0x00486550` | 403 / 403 B | 4 | `16.0f` / `0.75f` | After floats | 163 | 412 |
| `0x004AC040` | 403 / 403 B | 2 | `15.0f` / `0.7f` | Before floats | 151 | 522 |

## Reproduce just these affected probes

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-extra-stage-action-source.py --boss CharacterMove
# Rebuild exactly the two newly affected natural C++ objects, not all 943 exact units:
scripts/repo-python scripts/verify-fighter-extra-stage-action-source.py
```

Generated source/COFF/PDB/compiler logs/summary remain in ignored
`.analysis/f556-extra-stage-source/`; native original reverse-engineering
and negative source controls remain in `.analysis/f556-117-action6/`.
The actual **1,612 original interior CODE bytes** remain parts of two
**unmatched entire giant originals**; no 403-byte function exists in the
original outside those parents. This work grants **zero** exact CODE/DATA
credit, no full all-unit cold replay and no external Oracle receipt.
