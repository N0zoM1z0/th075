# F953 — Real 004AC040 CC/CD game state and preceding-case GPR phase

The pinned Japanese TH075 v1.11 whole authored giant
`004AC040` contains **82,796 original game CODE bytes /
22,721 x86**, plus **1,126 separate afterRET jump DATA**.
The currently authored natural VC7.1 parent is still PARTIAL;
it does not reproduce the full native 0x720 frame, saved
receiver at EBP-0x64 or many later genuine game actions.
The giant is **NONEXACT**.

Two full real original consecutive game-state bodies had still
been represented by 15-byte/two-instruction markers:

| Real action | Original PE interval | Entire native case interior |
| --- | --- | --- |
| 0xCC | **004B0852..004B0A05** | **435B /128 x86 /11 genuine PE external fields** |
| 0xCD | **004B0A05..004B0BB8** | **435B /128 x86 /11 genuine PE external fields** |

Both independent original natives implement collision/ground
motion, stage/frame virtual advancement and a **real
`00453C80(0x3C)`** projectile at the state transition.
The original native PE shows the projectile is issued
**BEFORE** writing its new motion values, so a prior
source sketch that moved that call outside the conditional
had ten wrong native mnemonic positions and was rejected.

The real original actor-specific transition is stage **3**
for CC and stage **2** for CD. After issuing the raw
X/Y projectile each source sets:

- **CC**: X = 0.0f, velocity = 20.0f, drag = 0.7f, then clears flag +0x3AC.
- **CD**: X = 10.0f, velocity = 15.0f, drag = 0.7f, then clears flag +0x3AC.

Both real original states check the native ground flag
and velocity against `0065782C`, call original
`00454BC0(3,4,0xFF)` when required, perform signed
short stage/frame counter updates, test the actual
`00657D14` float for auxiliary action 5, advance
the original virtual frame and terminate via a shared
parent epilogue. All native conditions and original
C++ field widths are preserved in the new natural source:

- [CC original source](../probes/FighterThirdBossCCF953.inc)
- [CD original source](../probes/FighterThirdBossCDF953.inc)

## Crucial actual register-allocation crossover

A truly important compiler behavior emerged.
The bounded [F953 original PE/VC7.1 verifier](../scripts/verify-third-fighter-cc-cd-f953.py)
generates and serially compiles **FOUR COMPLETE
original-shaped partial giant father C++ sources**,
not truncated fake per-case callables:

| Entire partial father variant | Whole source CODE | Original CC GPR errors | Original CD GPR errors |
| --- | ---: | ---: | ---: |
| Previous CC/CD markers | 20,397 B | Not aligned | Not aligned |
| Genuine CC only | 20,817 B | **77** | Not aligned |
| Genuine CD only | 20,817 B | Not aligned | **77** |
| **Genuine CC followed by genuine CD** | **21,237 B** | **77** | **0** |

Every source-backed real CC and CD emits the ORIGINAL
complete **435B/128-x86** geometry, with **0 wrong
mnemonic or width positions and all 11 actual typed
zero-addend PE external field targets checked
independently**. But the prior-case source affects
compiler register allocation in the following state:
the same CD C++ has **77 wrong GPR-role instructions
when preceded by a 15-B CC marker**, and **ZERO
wrong GPR-role instructions when the correct native
CC source is authored immediately before it**.
This demonstrates a genuine **CC→CD register-phase
dependency** in this third huge fighter, independently
consistent with the earlier cross-actor 0x58→0x59
loop-phase discovery. It does not establish a
historical complete fighter class.

The current partial father still saves `this` at
EBP-0x10 rather than original EBP-0x64. Its
absolute branch displacements, shared epilogue and
many other source offsets differ, so **even CD's
zero incorrect GPR roles does NOT make the
complete native function byte-exact**. The
same new whole-father build also independently
checks genuine preceding CF/D0 x86 and PE
targets, all **151 genuine afterRET local DIR32
case-label mappings** and **522 original
nonfield DATA bytes**.

Reproduce ONLY the four complete original-shaped
partial C++ fathers:

    scripts/repo-python scripts/verify-third-fighter-cc-cd-f953.py

The full complete C++/OBJ/PDB, original PE
target verification, compiler logs and JSON
receipt are preserved in ignored
`.analysis/f953-third-cc-cd-proof/`, with
the earlier raw control-flow trial in
`.analysis/f953-third-cc-cd/`.

**Neither switch case is independently accepted
as an original callable function. 0 newly
accepted native whole functions or CODE bytes;
NO 979-unit cold replay.**
