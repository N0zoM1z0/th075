# F627 — genuine priority-bonus action0x63 in one 138-instruction fighter giant

**Pinned original Japanese TH075 1.11 PE; real complete native action
case source inside one enormous fighter C++ `Advance()` owner; entire
giant still NONEXACT.** Original target executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Original priority bonus is a separate early-exit path

F624's native `00564BE0`/`005AEEC0` action0x63 original cases
were **118 x86** with an optional bonus *after* a `0x31C`
transition. F626's five regular owners had **109 native x86** with
no bonus at all. Independently decoding the original `005D73C0`
(and `0045DD70`) reveals a **third genuine native grammar**:
**138 complete original x86 instructions** with a *priority* bonus
branch that occurs **before** the ordinary action0x31C path.

The original common first condition remains the physical two-edge
short circuit `mode_byte_at_006714B4 != 3 || this+0x2CD == 0`.
Within its second (mode==3, member!=0) branch, native x86 ordinals
27–55 first test real stage `+0x62 > 1`, live signed `+0x39D >0`,
and target owner `+0x2E8` stage short `+0x60 < 150`.
It then probes **two separate original signed bytes** in this order:

```cpp
this->signedByte[0x370 + this->signedByte[0x39D]] == 5 &&
this->signedByte[0x32A + this->signedByte[0x39D]] == 2
```

On success the real game state method `0040FAC0` receives **0x303**
and the original giant switch exits. If this priority path fails,
there is still a second, **separate full guard** of stage, live byte,
owner stage and `+0x32A == 2`; on success it sends ordinary action
**0x31C** and exits. Later `+0x32A == 1` and `== 0` cases, their
`0x31C` and `0x5F` transitions and byte `+0x3CF` updates, plus the
actual native `0040FA30` frame getter and `0040FB40(2)` exit,
retain their own original C++ guards and native order.

It is **not equivalent** to F624's optional bonus checked after
already transitioning to 0x31C, nor to F626's no-bonus condition.
Tracked genuinely different natural source
[`FighterMode63PriorityF627.inc`](../probes/FighterMode63PriorityF627.inc)
faithfully represents those independent game control paths without
machine-code byte copies or synthetic compiler locals.

## Strict one-actor success, one explicit real negative

Both original actors' real second packed sparse tables have **49
entries but only 26 dense slots**: the last actual `0x63` action
is native compressed **slot24**, while dense slot25 is common
DEFAULT (not the original physical end of game action0x63).
The independently registered next real original CODE handler is
`0x8C`. The verifier reads the pinned original PE physical addresses,
then bounds the generated real 0x63 C++ case using the *following*
`0x8C` source marker and its typed physical COFF field, never
using the shared default handler or trimming trailing x86.

| Whole enclosing original giant, still NONEXACT | Native entire real 0x63 CODE | Original x86 roles | True physically typed PE/COFF fields | Actual original GPR/CFG source differences |
| --- | ---: | ---: | ---: | ---: |
| `005D73C0` **strict** | **534 B** | **138/138** | **8** | **0** |
| `0045DD70` **explicit negative** | **533 B** | 138 x86 vs 138 C++ | 8 | **87**, after physically verifying and normalizing mode-global DIR32 |

The two source-code candidates produce the same nominal **534
C++ bytes/138 instructions**, but the original `0045DD70` genuinely
has **533 native bytes** and different register allocation. This
negative is not accepted simply because all physical relocation
fields are correct or the instruction count is identical.

The original eight typed PE/COFF fields are the signed-byte mode
`DIR32` at native x86 ordinal0 to **`006714B4`**, five actual
`REL32` calls to native action setter `0040FAC0` at ordinals
22, 54, 77, 100 and 123, native frame getter `0040FA30` at
128, and native aux setter `0040FB40` at 136. For all fields the
original PE target address, source COFF symbol identity, physical
instruction ordinal, type and zero relocation addend are checked
before comparing all remaining GPR/x87/CFG source roles. The only
normalized operand in strict shape analysis is the explicitly
verified original global `DIR32` field at ordinal0.

Tracked strict original-PE verifier:
[`verify-fighter-mode63-priority-f627.py`](../scripts/verify-fighter-mode63-priority-f627.py).
It fresh-compiles exactly one selected original-shaped giant C++
translation unit under pinned MSVC VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, confirms true physical
compressed case boundary and all 138 native x86 instruction
roles/widths, and re-runs original F614 verification of the
**30 earlier source-backed original action bodies** plus full
original separately owned after-RET dense/sparse switch DATA in
the *same* newly built OBJ. Later action0x62 and previously
unmatched predecessor source cases remain honest incomplete
placeholders in this source context. This does not imply all
case proofs in different source contexts simultaneously match.

**F627 adds exactly ONE strictly source-backed original inner game
case /138 real native x86 roles /534 original internal CODE bytes /
8 original physical typed COFF references.** The bounded giant
source study rises from F598–F626's **346 original internal cases /
90,699 original native CODE bytes** to **347 native internal case
subranges /91,233 original native CODE bytes**. These case fragments
are **not** 347 independently accepted game functions, and neither
entire fighter boss is byte-exact. Official accepted whole authored
coverage remains **943 exact functions /862,726 original CODE bytes**.
No manual assembly, bogus stack locals, original game target edits,
full all-unit cold replay or external Oracle acceptance.

## Selected reproduction only

```bash
scripts/repo-python scripts/verify-fighter-mode63-priority-f627.py
scripts/repo-python scripts/verify-fighter-mode63-priority-f627.py --negative-actor
scripts/repo-python scripts/validate-tracking.py --require-target
```

Full original PE case receipt, genuine newly compiled giant source
C++ and COFF/PDB, actual typed global/call addresses and explicit
negative original register-phase data are preserved in ignored
`.analysis/f627-mode63-priority/verified/`. Native source
experiments also remain in `.analysis/f627-mode63-priority/`.
