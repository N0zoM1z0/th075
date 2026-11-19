# Floating math-overload origin probe (2026-11-19)

**Status: research source only; provenance `review`, no authored/exact coverage.**
The natural C++ code is `probes/MathFloatOverloadProbes483300.cpp`.
It models the two-stage `float` overload chains used by many original
TH075 fighter/object state machines. It contains no assembly, padding,
dead code, or target byte literals.

Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi /I src` reproduces each
complete original body using normal C++ float->double promotion and
float result narrowing. Each body contains exactly one physical COFF
REL32 field, at the original instruction offset:

| Native | Bytes | Physical REL32 | Target call | Result |
| --- | ---: | ---: | --- | --- |
| 00483300 | 21 | +0x0C | 00483320 float atan2 worker | 17/17 comparable bytes |
| 00483320 | 37 | +0x17 | CRT `_atan2` at 00642240 | 33/33 comparable bytes |
| 00412D90 | 17 | +0x08 | 00412DB0 float fabs worker | 13/13 comparable bytes |
| 00412DB0 | 28 | +0x0E | CRT `_fabs` at 006418CD | 24/24 comparable bytes |
| 00428D20 | 17 | +0x08 | 00428D40 float sqrt worker | 13/13 comparable bytes |
| 00428D40 | 28 | +0x0E | CRT `_sqrt` at 00641E54 | 24/24 comparable bytes |

Original-PE disassembly of all 13 giant parent extents finds 161 direct
calls to 00483300 across 11 giants, 19 calls to 00412D90 across seven,
and three to 00428D20 across two. Those original call counts establish
usage, **not** the authored origin of these wrappers. The workers call
CRT math imports, and generic C++ overload generation is an ordinary
alternative explanation. The original source owner is unknown: retain
`review` in `config/function-origins.csv`, **do not** promote these six
bodies into `match-units.toml`/`matches.csv` or claim additional authored
exact bytes on the strength of structural equality alone.

Reproduce the body comparisons with:

```sh
scripts/compile-probe.sh probes/MathFloatOverloadProbes483300.cpp build/probes/MathFloatOverloadProbes483300.obj /Od /Ob0 /Gy /GR- /GX- /Zi /I src
scripts/repo-python scripts/compare-coff-function.py build/probes/MathFloatOverloadProbes483300.obj '?FloatAtanOuter483300@@YAMMM@Z' 0x00483300 21 --json
scripts/repo-python scripts/compare-coff-function.py build/probes/MathFloatOverloadProbes483300.obj '?FloatAtanInner483320@@YAMMM@Z' 0x00483320 37 --json
```

Use the analogous `FloatAbsOuter412D90`, `FloatAbsInner412DB0`,
`FloatSqrtOuter428D20`, and `FloatSqrtInner428D40` COFF symbol names
for the other four extents. Any future origin classification needs
separate evidence of game authorship rather than this code-generation
match alone.
