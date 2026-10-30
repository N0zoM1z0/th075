# F708 — full original fighter 2BF/2C4 twin burst handlers in the real whole boss

**Meaningful native source reconstruction, not byte-exact.** Target is the
user-supplied Japanese TH075 1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original authored `00543210` owns **58,294 CODE bytes** plus **943
separate afterRET switch DATA bytes**. Neither internal action is a new
independently callable function; the giant remains **NONEXACT**.

## Two complete original physical native cases, real C++ and call graph

| Original native action | Physical original CODE | Original x86 | Native typed PE/COFF fields | New VC7.1 whole-parent C++ |
| --- | --- | ---: | ---: | --- |
| `0x2BF` | `0054D489`–`0054D64D` (452 B) | 131 | 16 | 452 B /131 x86 /16 fields |
| `0x2C4` | `0054DC0E`–`0054DDD2` (452 B) | 131 | 16 | 452 B /131 x86 /16 fields |
| **Both authentic native case interiors** | **904 original CODE B** | **262** | **32** | **904 generated CODE B /262 x86/32 typed original fields** |

Tracked source [`FighterTwinBurstF708.inc`](../probes/FighterTwinBurstF708.inc)
reconstructs both complete native cases with normal C++:

- Original stage-zero frame/control initialization, short frame counter,
  trajectory `00453E80(40)`, native `00453D60(23)` and preparations
  `00453D40(9)` or `(13)`; actual `this+0x36C` x87 subtraction.
- Native independent `00453C80` kind `0x73` and `0x74` projectile
  calls with signed facing × 20 and authentic float Y offset; each
  followed by a **seven-argument** game call `00453B50` kind `0x334`
  with real x/y, signed direction and three original flags.
- Actual completion check and `0040FAC0(0)` transition.
- Stage-12 two full native projectile calls per case: `0x328/0x33C`
  and `0x32B/0x33D` with directional × 65 conversion and original
  `[006591EC]` float Y. Importantly `2BF` performs
  `0046D000(500)` **after** those shots, while `2C4` runs
  `0046D000(750)` **before** its shots; original stage prep is
  10 vs 14. We did **not** make them artificial identical stubs.

All **32 physical original call/global PE locations** are checked
against the original program: actual x86 owner ordinal, original
native target, emitted VC7.1 source symbol, zero addend and correct
`REL32/DIR32` type. Each case's whole source emits **all 131 native
instruction widths** in original order, including all authentic
six-byte `MOV/FILD` integer-to-x87 scratch operands.

## Real source x87 improvement and remaining mismatch

The first meaningful source spelling of `X - float(dir * 20)` emitted
a `FLD [X]` followed by `FISUB [integer scratch]`, while the native
original does `MOVSX dir; IMUL dir, +20; MOV [EBP] ; FILD [EBP];
FSUBR [X]`. That native/source sequence differed in **five x86
mnemonic positions** in **each** complete 452-byte case.

A source-equivalent expression `float(dir * -20) + X` naturally makes
VC7.1 evaluate direction first: `MOVSX; IMUL; MOV [EBP]; FILD;
MOV this; FADD [X]`. The result retains **452 B/131 x86/16 source
fields**, but reduces the actual opcode-order mismatch to **only one
position (native `FSUBR` vs source `FADD` at x86 43)** in each case.
It also emits `IMUL -20` rather than genuine original `IMUL +20`.
Those are actual operand differences, **not** matching bytes. The
negative sign is arithmetically equivalent for the observed signed
byte facing range and does not add a synthetic float conversion
helper or unused locals. Seven whole-parent C++ arithmetic controls
were freshly compiled: three byte-width-identical forms retaining the
wrong `FLD/FISUB`, three additional `FCHS` or `NEG` forms with extra
opcodes, and the selected semantically real negative-multiplier
source with the better original x87 evaluation phase.

Original `2BF` conversion locals live at native
`EBP−0x154/−0x158/−0x15C`, but the source uses
`−0x8C/−0x90/−0x94`; `2C4` native scratch
`EBP−0x16C/−0x170/−0x174` becomes
`−0x98/−0x9C/−0xA0`. All twelve native/source
six-byte scratch operands are separately asserted: **no EBP bytes
are masked**. In the selected full parent, `2BF` also retains two
and `2C4` retains 66 other normalized original x86 operand/GPR
mismatches respectively. Both are **NONSTRICT**, not accepted exact.

## Whole-parent interaction: no false split-case acceptance

[`verify-fighter-twin-burst-f708.py`](../scripts/verify-fighter-twin-burst-f708.py)
regenerates one entire original-shaped giant TU from the tracked
F706 C++ context, inserts the **two** true source cases, compiles
only that selected whole parent using pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, and re-reads the pinned PE.
It checks **every full original 2BF/2C4 instruction, all 32
physical original fields, true x87/IMUL and EBP negatives**. It also
reruns the native shape of all five genuine `259–25D` original
source actions, later `2F8–302` handlers and **all 27 previously
context-strict nonterminal original bodies**, with the *entire
943-byte afterRET switch DATA* in this same newly compiled parent.
The source saves `this` at `EBP−0x28` (native `−0x44`); exactly
2,715 physical source MOV uses were independently authenticated.

The earlier F673 verifier now explicitly supports a source-backed
real following `2BF` instead of assuming its old placeholder, while
F696/F706 carry newly measured adjacent case boundaries. Existing
source contexts retain their older default expectations and were
regression tested separately. Generated CPP/OBJ/log, seven actual
alternative original-shaped compiler builds and the `summary.json`
are retained under **ignored** local
`.analysis/f708-fighter-twin-burst-native/`; the tracked portable
source and verifier are in `probes/` and `scripts/`.

```bash
scripts/repo-python scripts/verify-fighter-twin-burst-f708.py
scripts/repo-python scripts/verify-fighter-combined-native-storm-f706.py
```

No exact whole giant, no native CODE bytes patched, no fake stack
locals, no separate inner-case CODE credit, no all-943-unit cold
replay. Official full authored ledger remains **943 functions /
862,726 original CODE B (43.71% reviewed)**.
