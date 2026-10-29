# F549 — real action 10, eleven independent natural VC7.1 fighter switch probes

**Complete original-PE evidence and natural C++ codegen, not a whole-fighter
function exact match.** The pinned Japanese TH075 v1.11 SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The entire original CODE SHA256 and owned native after-RET switch DATA are
verified *before every selected source compile*. The first switch's physical
**eleventh DWORD entry** begins action 10; the independently verified
**action `0x32` singleton entry** marks its end. This is a whole contiguous
case inside each 28K–82K original giant, **not** a separate function.

## New original game-state behavior

Original action 10 has two genuine whole-native control-flow families:

- In **nine** fighters, the original first checks signed shorts at
  receiver `+0x62/+0x64`; when both are zero it invokes the native
  `00453D60(30)` *thiscall*. It then invokes `00453E20` reset, reads the
  original signed state via `0040FA30`, compares it with receiver `+0x70`,
  and checks the original DWORD at receiver `+0x4E0`. Depending on its
  zero/nonzero state, it invokes `0040FAC0` with the fighter-specific
  two-case argument. This is **31 whole instructions / 101 original CODE
  bytes** per regular boss.
- In **two** fighters (`005214B0` and `00564BE0`) the first-state guard
  and `00453D60(30)` call are genuinely **absent**. These are **20 original
  instructions** each. `005214B0` has **69 native CODE bytes** and
  `00564BE0` has **87** because six real receiver reloads at `EBP-0x88`
  widen to disp32 (six extra three-byte displacements).

The actual native low/high state arguments vary by character and are **not
one shared sequence**: three fighters use **0/2**, three use **3/2**, and
five use **0/1**. The source generator decodes *actual original `PUSH`
instructions*, validates the whole native call ordering, and emits ordinary
`if` expressions rather than transferring machine bytes.

## Independent whole-context compiler checks

Each selected probe regenerates real actions 0..5 and 9 from their previous
native-verified C++ sources; it adds a natural C++ action 10 while retaining
explicit test-only marker stores for all other unimplemented actions. All
source TUs compile under the pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` profile, serially. The checker independently
reads every whole original fighter and the entire native jump DATA, then
compares the entire case control flow from the authentic case-10 DWORD entry
to the native independently branched case-`0x32` start.

Across **11/11** separately compiled C++ candidates:

- **319/319** complete native case instruction mnemonics and the actual
  member-access, branch-target and source-level condition roles agree after
  normalizing enclosing-frame EBP slots and volatile GPR choices with true
  thiscall/receiver dataflow checks. **Only 6/11** also have precisely the
  original GPR allocation; **5/11 differ** and are not register-/byte-exact.
- **53/53 real typed `REL32` COFF call fields** are present at the correct
  physical case instruction sites and target the authentic original methods.
- All **1,607 original-style COFF DWORD jump references**, repeated-case
  and default partitions, **4,502 byte-identical original sparse-index
  DATA bytes** and **10,930 after-RET DATA-shape bytes** are validated.
  None is accepted CODE/DATA credit.

| Whole original boss | Real case 10 bytes | Original calls | Native `453D60(30)`? | Native low / high arguments | GPR allocation exact? |
| --- | ---: | ---: | --- | --- | --- |
| `0x0045DD70` | 101 | 5 | Yes | 0 / 2 | Yes |
| `0x00486550` | 101 | 5 | Yes | 3 / 2 | No (dataflow checked) |
| `0x004AC040` | 101 | 5 | Yes | 0 / 1 | Yes |
| `0x004D7E70` | 101 | 5 | Yes | 0 / 1 | No (dataflow checked) |
| `0x004F7130` | 101 | 5 | Yes | 0 / 1 | No (dataflow checked) |
| `0x005214B0` | 69 | 4 | No | 0 / 1 | Yes |
| `0x00543210` | 101 | 5 | Yes | 3 / 2 | No (dataflow checked) |
| `0x00564BE0` | 87 | 4 | No | 0 / 1 | Yes |
| `0x0058AF60` | 101 | 5 | Yes | 0 / 2 | Yes |
| `0x005AEEC0` | 101 | 5 | Yes | 3 / 2 | No (dataflow checked) |
| `0x005D73C0` | 101 | 5 | Yes | 0 / 2 | Yes |

## Targeted reproduction, no full cold replay

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-actionten-natural-source.py --boss Reimu
# All eleven newly affected natural C++ probe translation units only:
scripts/repo-python scripts/verify-fighter-actionten-natural-source.py
```

Fresh C++/OBJ/PDB/COFF evidence is retained under ignored
`.analysis/f549-action-ten-source/`. The source uses the tracked reusable
F547 `source_nine_for` helper, **not an ignored old source snapshot**, so it
is reproducible from original PE and previously verified tracked C++
generators. The actual **1,065 original interior action-10 CODE bytes**
remain within **613,391 unmatched whole giant CODE bytes**; there is no
new exact function, partial/whole accepted CODE or DATA, external Oracle
receipt, pasted ASM, or all-unit cold replay.
