# F575 — recover actual CharacterObject fade actions 0x32D/0x32E

**Pinned Japanese TH075 1.11 PE and actual MSVC 7.1 C++ codegen,
not exact whole-fighter source.** Original executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original complete fighter `004EBDA0` is 33,293 CODE bytes;
after its own `RET` are 438 distinct native jump/index DATA bytes.
F575 extends the same tracked readable
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
from F572/F573/F574 with **two more complete native game-action cases**.
Both real branch bodies are independently bounded by original
physical Japanese PE case-handler addresses, never arbitrary source
or byte-match prefixes.

## Original action 0x32D: two-stage float fade and short timer

Native physical **66 x86 instructions / 229 CODE bytes** implement
real C++ semantics:

- On original `S16(0x62)==0 && S16(0x64)==0`, call genuine
  `0040FBB0(0,0,0)` and initialize two actor alpha/scale fields
  `this+0x1C/+0x20` to **0.4f**, set color bytes `+0x11..+0x14`
  to 0xFF, native sprite index `S16(+0x1A)=0x4E2` and
  motion offset `this+0x28=-75.0f`.
- Every tick, add **the real float global 006583F8** separately
  into each +0x1C/+0x20 field using native x87 FLD/FADD/FSTP.
- When stage `S16(+0x62)>1`, reduce the actual unsigned byte
  `U8(+0x11)` by 20 only when it is **greater than 20**;
  otherwise call true original `0045B830` and exit.
- Independently query actual current state `0040FA30` and call
  `0045B830` when it equals signed stage owner `+0x70`.

All **66 original EAX/ECX/EDX, x87, branch and byte-width roles**
strictly match natural C++. There are **6 genuine original physical
`REL32`/`DIR32` call and float-global COFF fields**.

## Original action 0x32E: gated fade with distinct global and timer

The separate native **70-instruction / 282-byte complete** action
only initializes when stage/frame state are both zero **AND**
`S16(+0xD8)==1`; it then zeroes `+0xD8`, calls
`0040FBB0(0,0,0)`, initializes `+0x1C/+0x20=0.5f`, zeros
native velocity/motion counters, sets original 0xFF color bytes
and native owner state.

Every frame it adds float global **00659428** into both
+0x1C/+0x20 and **unconditionally** subtracts 10 from byte
+0x11, before querying `0040FA30` and conditionally resetting
with `0045B830`. This differs from action32D's conditional
stage-two fade and its entirely different global.
The generated VC7.1 C++ strictly matches all **70/70 original
GPR/x87/CFG instruction types, exact widths and order**, and
**5/5 authentic zero-addend typed COFF call/float fields**.

**Critical native dispatch caveat:** original action ID **0x32F
maps to the default handler**, so the end of the complete 0x32E
CODE body must be obtained from the **next actual handler, 0x330**.
The new validator explicitly uses this independently native
physical target instead of incorrectly truncating its original
case to the default handler or conflating the two source labels.

## Cumulative native source and physical COFF validation

Tracked source-aware verifier:
[`scripts/verify-characterobject-fade-actions-f575.py`](../scripts/verify-characterobject-fade-actions-f575.py)

The fresh verifier uses only **ONE affected native VC7.1 C++
translation unit** with `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and
independently rechecks original whole PE CODE/hash, original dense
60-slot table, physical default/destination partitions, all real
selected case boundaries and **198 exact original sparse index
bytes**. It separately verifies all previous genuine F572/F573/F574
cases, not trusting previous saved compiler objects.

| Complete original action family | X86 instructions | Original inner CODE | Typed COFF fields | Physical source order |
| --- | ---: | ---: | ---: | --- |
| 0x320–0x326 (seven simple leaves) | 21 | 91 B | 7 | Strict |
| 0x327–0x329 (three 271-insn bosses) | 813 | 2,996 B | 54 | Strict |
| 0x32A (six floating equality gates) | 248 | 932 B | 19 | 1 independent read-only MOV/FLD swap |
| 0x32B (integer-FPU stage curve) | 112 | 422 B | 9 | Strict |
| 0x32C (collision/effects) | 176 | 635 B | 13 | 1 independent read-only MOV/FLD swap |
| **0x32D and 0x32E (new fade cases)** | **136** | **511 B** | **11** | **Strict** |
| **Total** | **1,506** | **5,587 B** | **113** | 13 strict, 2 documented swaps |

All **113/113 authentic case COFF `REL32`/`DIR32` fields** have
original PE callee/global identity, native x86 instruction ordinal,
true candidate symbol and zero addend. All **60 physical native
jump-table DWORD COFF labels**, true repeated/default partitions,
**198 byte-identical compressed original index bytes** and 438
independent after-RET DATA-shape bytes are verified.

### Targeted reproduction — no all-unit cold replay

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-fade-actions-f575.py
# Freshly recheck all earlier first-ten/eleven/thirteen C++ cases:
scripts/repo-python scripts/verify-characterobject-following-actions-f574.py
scripts/repo-python scripts/verify-characterobject-extended-action-f573.py
scripts/repo-python scripts/verify-characterobject-action-family-f572.py
```

Original source disassemblies, native actor stage values and negative
initial boundary experiments remain under ignored
`.analysis/f575-characterobject-fade/`. New COFF/OBJ/PDB/compiler
and physical case summary stay under
`.analysis/f575-characterobject-fade-source/`.

These **5,587 original inner CODE bytes are still included in the
33,293-byte entire original giant, which is NOT exact**. The original
C++ class layout and still-unimplemented later actions remain unknown.
Zero accepted whole/split-function CODE/DATA credit, no fake padding,
no all-unit replay and no external Factory/Oracle receipt.
