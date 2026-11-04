# F1108 — Two original 952B/206-x86 states 0x360 and 0x361; separate 0x365/0x366 projectile and complete native GPR phase

The SHA-pinned Japanese TH075 1.11 original contains ONE independently
authored `CharacterObject::Advance` at `0050A580`, **81,539 native
original CODE B /17,435 x86**, followed by 567 separately owned
original switch DATA bytes. F1108 replaces two formerly synthetic
marker handlers with **two physical original game-case interiors**.
This is genuine ordinary VC7.1 C++ inside the incomplete parent;
the two switch cases are NOT independent whole-game callables.

| Actual original native game action | Genuine PE interval | Original native CODE/x86 | Current whole-source case |
| --- | --- | ---: | ---: |
| `0x360` | **00516D10..005170C8** | **952 B /206** | **964 B /206** |
| `0x361` | **005170C8..00517480** | **952 B /206** | **964 B /206** |
| Both original distinct case interiors | — | **1,904 B /412** | **1,928 B /412** |

The original game handlers share all 206 ordered x86 mnemonics and
native instruction widths, but have distinct real GPR phases and
physical local scratch slots. They also produce **different game
projectiles**, a distinction that mnemonic/PE-call-only comparison
could miss: when the original action finishes, state `0x360` writes
parent+0x314 original angle bits, spawns projectile **`0x365`** via
real parent `00453A70`, then expires. `0x361` instead spawns native
**`0x366`**. Both preserve separate original jump table entries and
native immediate values; the same real source family is instantiated
for each with an actual independent C++ case and native literal.

## Reconstructed native game behavior

Each original state checks parent action `(0x31,0x96)` and own stage
below 2, expires via original `0045B830`, loops over precisely
**two `0x3E4` projectile calls**, and conditionally resets parent
+0xEFA and spawns an extra original `0x3E3` projectile. The genuine
initial `(stage,frame,d8)==(0,0,0)` resets motion using actual
`0040FBB0`, both scale floats to 1.0f, four alpha bytes to 0xFF,
collision status, signed countdown and +0xD8 timer to **15**. It
invokes real `0040FB70` with the **unaltered raw DWORD** actor+0xC8
angle and float timer.

Every frame it moves native signed-facing X and subtracts Y motion;
in stage 0 it invokes real `0040FB70` again, decrements +0xD8,
clamps its signed counter at zero, and increases original +0x30
angle by true float global **00657878**. It checks independently
verified native arena boundaries at X-right `00659424`, X-left
`006595EC`, Y-upper `006583B4` and Y-lower **also `006595EC`**.
On original `0040FA30` action completion it writes actor+0xC8
DWORD directly into parent+0x314, spawns `0x365` or `0x366`, and
calls `0045B830`.

An initial genuine C++ source emitted **207 x86** for each handler
instead of the actual original **206**, because it separated two
terminal `return` branches and generated an extra `JMP`. Restoring
the authentic shared return path, without modifying game effects,
produces exactly **206/206 ordered original native mnemonics and
206/206 original GPR operand roles** in **both** physical states.
All native original nonlocal call/global fields were checked against
the independent original PE at their *actual instruction ordinals*.

| Original PE evidence | `0x360` | `0x361` |
| --- | ---: | ---: |
| Original mnemonics, GPR roles | **206/206 each** | **206/206 each** |
| Exact original physical PE external fields | **15/15** | **15/15** |
| Correct original nonrelocated scalar immediates | **34/34** | **34/34** |
| Matching original instruction widths | 202/206 | 202/206 |
| Original spawned game action | **0x365** | **0x366** |

**Width debt is real and narrow:** original state `0x360` uses a
native loop counter at EBP-0x78, and `0x361` at EBP-0x7C. Current
original-shaped C++ keeps the actual loop counter at EBP-0x8C and
EBP-0x90, respectively; because these cross the signed-byte
addressing boundary, **four genuinely used counter MOV/CMP x86
instructions per case are 3 bytes too wide**. This is not masked
or claimed byte-exact. The actual source still has an incomplete
whole 81KB frame, and correct original local lifetime placement
remains a distinct research objective.

## Single current parent cold original-PE validation

The tracked `scripts/verify-characterobject-current-recovered-f1068.py`
**recompiles only this changed original-shaped whole partial C++
parent**, independently validates SHA of the entire original Japanese
81,539B CODE and 567B DATA, original **92 DIR32 jump-label equality
partitions** plus 199 native sparse index bytes, then checks every
recovered state by original mnemonic ordinal and GPR role, every
physical original REL32/DIR32 call/global field and every original
nonrelocated immediate value.

F1108 expands the strict role-matched original-state cohort from 55
to **57 genuine original interiors**, totaling **48,466 original
native CODE B /10,508 original x86**, with **10,508/10,508 native
mnemonic and GPR matches**, **803/803 actual original physical PE
fields** and **1,963 verified original scalar immediates**.
Another **seven game states** remain independently tracked as
PROVISIONAL due to native GPR-role debt; do not confuse those with
the 57 strict-role cases or new whole-function exact credit.

Selected whole current partial C++ emits **53,396 CODE B /11,524
x86** plus the authentic native 567B afterRET DATA, with saved this
at EBP-0x94 and `ESP 0x24C`, versus original complete 81KB game
EBP-0xAC, `ESP 0x3A0`, and **17,435 x86**. Original whole
callable remains **NONEXACT; no new original exact CODE bytes**.
The original 979 exact whole functions and accepted CODE are unchanged.

Reproduce this ONE affected large source only:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Original native field, normal VC7.1 C++/OBJ/PDB/compiler receipts,
and rejected extra-JMP source remain in ignored
`.analysis/f1108-native360361/` and `.analysis/f1068-boss-live-all-native/`.
No 979-unit replay, original EXE patch or synthetic register binding.
