# F812 — Native ten-burst action naturally restores default GPRs and advances the fighter stack frame

The pinned Japanese TH075 v1.11 original whole fighter 005214B0
contains **46,755 callable CODE bytes, 13,230 x86 instructions**
and **901 separately owned post-RET packed switch DATA bytes**.
F811's previous incomplete source emitted 8,841 CODE B/2,206 x86
with 29 real original action bodies and the F806 native shared tail.

F812 re-reads F614's real second-switch 0x58/0x59 physical handler
boundaries and regenerates the entire **469-B/135-x86** action 0x58
with **17 actual PE/COFF call and float fields**. Its original game
behavior includes actual trajectory setup, native integer conversions,
two float comparisons, ten real projectile spawn calls of kind 0x3E4,
the +0xEFA bonus-projectile counter and the conditional 0x3E3 spawn.
The loop counter is truly used by gameplay, not dummy stack padding.

The targeted verifier scripts/verify-scripted-fighter-ten-burst-shared-f812.py
first regenerates and checks the selected F614 source, including the
29 preceding original action bodies, then compiles one whole updated
VC7.1 parent with the true F806 shared getter and default.
It again verifies the complete original 0x58 x86 and typed PE fields,
all prior actions, all 901 original post-RET DATA bytes, all three
authentic default REL32 calls, and the four actual early JMP entries.

| Whole-parent source | Previous F811 | New F812 | Actual original |
| --- | ---: | ---: | ---: |
| Callable CODE bytes | 8,841 | **9,295** | 46,755 |
| Callable x86 instructions | 2,206 | **2,339** | 13,230 |
| Separate after-RET DATA | 901 | **901** | 901 |

**New genuine frame-lifetime result:** the actual ten-projectile
source loop introduces a used local index and moves saved receiver
from EBP-4 to **EBP-8**. This naturally also reproduces the original
default's exact EDX/EAX/ECX GPR roles, with no manually forced
registers. The 46-byte/16-x86 original default/getter tail now
has **only four remaining real nonrelocated EBP-byte differences**
at offsets 2, 13, 26, 36: native EBP-0x10 versus current EBP-8.
All tail mnemonics, sizes, control flow and real native PE calls agree.
These four are *not* relocs and must not be masked.

The source still has many placeholder states, so the entire original
46,755-B callable game function is **NONEXACT**; no 469-B internal
subcase or jump DATA is credited as independent callable CODE.

To reproduce only the affected original source parent:

    scripts/repo-python scripts/verify-scripted-fighter-ten-burst-shared-f812.py

The whole source C++, COFF/PDB and physical comparison receipts remain
in ignored .analysis/f812-scripted-burst/. No all-unit cold replay.
