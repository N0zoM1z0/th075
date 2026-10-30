# F760 — three original fighter CC/CD/CE state engines restore 1,264 physical CODE bytes

**Whole-original-parent game-source progress, not a complete-function byte-exact
adoption.** Native target is the pinned user-supplied Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The actual authored callable boss `00543210` is **58,294 native CODE
bytes plus 943 bytes of separately owned after-RET dispatch DATA**. Three
noncallable switch interiors have no independently accepted CODE credit.

## Original physical whole states — not cropped snippets

The full original PE gives three consecutive, genuinely distinct complete
handler extents:

| State | Original native PE interval | Whole original CODE | Original x86 | Real zero-addend PE/COFF fields | Real external parent-tail JMPs |
| --- | --- | ---: | ---: | ---: | ---: |
| `0xCC` | `00547A8B..00547C3E` | **435 B** | **128** | **11** | **2** |
| `0xCD` | `00547C3E..00547DF1` | **435 B** | **128** | **11** | **2** |
| `0xCE` | `00547DF1..00547F7B` | **394 B** | **115** | **9** | **2** |
| **Total** | | **1,264 B** | **371** | **31** | **6** |

The new naturally compiled source is
[`FighterComplexStageCC_CE_F760.inc`](../probes/FighterComplexStageCC_CE_F760.inc),
with one genuine C++ body per state from
[`FighterComplexStageCaseF760.inc`](../probes/FighterComplexStageCaseF760.inc).
The source reproduces the original ground `FUCOMPP/FCOMP` state setup,
`ConfigureStormAt454BC0(3,4,255)`, native state-0 reset, falling
velocity, bounce to action `0xA`, auxiliary stage check only in CC/CD,
actual signed 16-bit animation-frame progression and action `0x3C`
spawn through `00453C80`. The three original stage-2 positions are
`0.0f / +11.0f / −11.0f`, with source speeds
`21.0f / 16.0f / 16.0f` and actual `0.85f` drag.
No synthetic padding locals, guessed executable bytes, target patches,
conditional exact-only source bodies or intermediate fake returns.

### Corrected original control-flow branch

The first complete source trial achieved all **371 original x86 mnemonic
and size positions**, but had exactly one real nonrelocation byte wrong
in each case. At original `CC+0x192`, the `JL` branch displacement is
`0x11`, while the initially compiled candidate emitted `0x1B`.
The original `JL` bypasses only `S16(0x62)-=2`; the following genuine
`NativeVirtualFrameAdvance()` is invoked **regardless** of that
condition, once the animation frame advances. The first source had
incorrectly placed the virtual call inside the condition. Correcting
this actual game control flow naturally removes all **three**
remaining real operand differences, without forcing any bytes.

Now the freshly compiled **single entire parent** reproduces all
**1,264 original CODE bytes and 371 source instructions in matching
physical positions**, with **31/31 authentic COFF fields** at their
own original instructions, correct source symbol and PE target,
and **1,116/1,116 other nonrelocation/non-tail bytes identical**.
The **six original four-byte relative JMP displacement fields** to the
*external* whole boss shared continuation still differ, because the
enclosing entire boss is nonexact. These six mismatching fields are
excluded for *diagnosis only*; they are not credited to exact CODE.

## A second large win: the earlier eight-shot register phases

Adding the original CC/CD/CE gameplay after real C8–CB source changes
VC7.1's subsequent codegen and repairs the GPR phase regressed in F759.
In the **same newly compiled full parent**, all eight checked original
source-backed game interiors — `18A`, `18B`, `190`, `191`, `192`,
`194`, `195`, `2D0` — have native-complete opcode/width positions and
**zero differing bytes** outside their actual COFF fields and legitimate
external parent JMP displacement bytes. The true original `190` now
emits **276 B /75 x86/7 authentic COFF** and has **zero other machine
byte differences**; previously F759 had 40 real register differences
in that same case, despite already repairing its EBP scratch offset.
F759's measured `190/191/192` residuals **40/40/34** were not
permanent original-source truths; they were compiler-context effects.

This **does not** make the eight *internal cases* independently callable
source units, or establish byte identity of every other unsolved action.
Original `302` retains authentic current register-phase negatives.

## Reproducible complete parent, full after-RET data and honest state

Run only the one affected full-fighter VC7.1 C++ source, never an all-unit
cold replay:

```bash
scripts/repo-python scripts/verify-fighter-complex-stage-cc-ce-f760.py
```

The verifier recomposes prior tracked F759 source with the new three
cases, **fresh-compiles one ordinary complete giant** (`/Od /Ob0
/Gy /GR- /GX /GS /Zi`), and independently verifies the pinned whole
native original PE boundaries, every one of the 371 native x86
positions, 31 actual zero-addend field owners/callees and resolved
PE destinations, six legitimate shared-tail displacement negatives,
the previous C8–CB native full-case evidence, eight later complete
source-backed native cases, and the independent **943-byte after-RET
DATA** (156 genuine DIR32 labels and 319/319 original sparse bytes).

The complete new parent emits **58,173 CODE bytes** compared with
**58,294 original bytes**, leaving **121 native CODE bytes still
unrecovered** and other source contexts to audit. The whole boss is
**NONEXACT**, with **zero newly accepted authored callable CODE**;
formal ledger remains **970 / 864,961 original CODE bytes**. All
previously accepted exact units and origin evidence are unchanged.
Compiler evidence, full generated C++, COFF and JSON receipts remain
under ignored local `.analysis/f760-fighter-cc-ce/`; the new source
and strict verifier above are tracked for reproducibility.
