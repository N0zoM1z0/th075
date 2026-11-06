# F1227 — complete original 004CA6E0 source and whole native audit

The [single natural C++ body](../probes/CharacterObjectActions004CA6E0F1222.cpp)
now contains **all55 actual nondefault states**, adding901/903–911 to F1226.
It is **complete but NONEXACT**. All **42,511 original CODE bytes remain
pending**; no interior state, helper, table or symbol receives new exact
credit. Independent R048 origin, full extent and exact constructor/vtable
witness remain in [F1222](OBJECT_ADVANCE_004CA6E0_INITIAL_STATES_F1222.md).

## Complete pinned-original and fresh compiler evidence

| Checked complete-function property | Original PE | Selected fresh VC7.1 |
| --- | ---: | ---: |
| Entire callable CODE | 42,511B | **42,515B (+4B)** |
| Entire native x86 instructions | 11,201 | **11,201** |
| Frame / saved-this / ESI | 0x288 / EBP-4 / saved | **All agree** |
| EBP operand positions | 3,717 | **All agree** |
| Mnemonic / non-GPR operand differences | — | **Zero / zero** |
| Direct native branch targets | 1,014 | **All instruction ordinals agree** |
| CODE reference destinations | 873 | **All agree at native instruction fields** |
| Owned after-RET DATA | 422B | **422B** |
| Dense destination ordinals / sparse bytes | 56 /198 | **All agree** |
| Remaining wrong GPR roles / instruction widths | — | **447 /12** |
| Whole callable canonical cold acceptance | — | **NO** |

The entire original CODE is004CA6E0..004D4CEE, SHA256
`48f9d74fce27081274d2dbc00a89dd230eda628f05fb2371a3997f9490b118f5`.
Owned DATA SHA256 is
`7eadd1c24331f86d00f46e22c9392d2776cdb4167e6159e58c822c255d38b218`.
Eleven subsequent INT3 bytes remain excluded alignment. The dense entries
include default004D4CE2; the common epilogue starts at **004D4CEA, POP ESI**.
All boundaries, switch partitions and scalar remap bytes remain native-derived.

Completing the actual later expressions naturally restores frame0x288 and
every anonymous temporary position. The only named stack value is the real
receiver; no inert local, padding or forced register/stack binding is added.
Reference destinations agreeing does not certify original COFF offsets: wrong
GPR widths still shift later physical fields. No relocation mask or cropped
interval is used for acceptance.

## Recovered final native behavior

901 has an actual **owner health==0** guard; unlike the other later guards,
negative values are not included. It preserves the D8-gated initialization,
separate angle calls/owner transform writes without tracked creation, state6
hit-count restoration, hit reset6, bounds/bounce and phase5/7 repetitions.
903 reuses the reviewed803 flight structure only after replacing its actual
guard with owner health<=0 and checking the entire205-instruction interval.

904/905 preserve separate initial speed policy, their nonzero-hit alpha128
branch before alpha255, D8 clamp5, phase1 movement and hit-qualified effects.
The original one-/two-reflection limits and strict positive-angle tests remain.
904 starts speed15 and writes speed4 after each successful reflection;905
does neither. Original reflected angle tests remain independent. Native hit
reset2 returns before bounds/advance, and later bounce/fall paths remain.

906 preserves8A reset, independent random DA/D8 values, initial and per-tick
polar calls, actual speed scale0.01f, and initial velocity reset after angle
calculation. Its counter update is **`DC += 5 + D8`**: this naturally emits the
original D8-before-DC reads and exact LEA base/index roles. Explicit assignment
had swapped field reads, and reordered explicit addition left one LEA role
wrong; the compound form fixes that remaining isolated difference.

907/908 remain separately emitted identical states. Their acceleration is
`D8 * 0.01 + 0.05f + velocityX`. The double0.01 multiplication widens the
float0.05f addend, generating the actual QWORD **0.05000000074505806** bits;
it is not replaced with double0.05 or a precision-grafted literal. Both retain
native hit resets, distinct1320/-40 X bounds, wrapping fade and phase reset.
909 retains tracked813 creation, full owner transforms and phase repetition.
910 preserves the signed difficulty-byte repeat limit, effect909 parameters,
reset-before-increment order and actual immediate return. 911 preserves its
three difficulty-limited reflections, then polar/angle, tracked813 and812
packets in native order, with state2/4/6 hit resets and later bounce behavior.

All new literals are independently checked against actual PE bits and actual
COFF payloads. Existing receiver/helper views remain borrowed; no helper or
global owner is defined or independently credited, and95 unknown origins stay
unchanged. Names remain provisional independently of machine-code recovery.

## Precisely bounded remaining whole-function debt

| State | Wrong GPR positions | Wrong instruction widths |
| --- | ---: | ---: |
| 808 | 32 | 0 |
| 809 | 117 | 8 |
| 810 | 117 | 4 |
| 811 | 181 | 0 |

The prefix, every other state, original frame and all3,717 EBP operands have
zero raw GPR/EBP/width debt. First difference: **004CCBD7**, whole ordinal
**2,526**, after808's D8 increment: native loads ECX, source EAX. All twelve
width differences are accumulator-versus-other-register immediate comparisons
in809/810; the first is **004CCCBE /whole2,594**. F1224's postfix increment
control is already byte-identical negative evidence and must not be repeated.
No remaining source shape or allocator cause is asserted without new proof.

## Reproduction and retained evidence

Selected serial headless pinned VC7.1 profile:
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`.
`.analysis/f1227-object-4ca6e0-complete/` retains before CPP/HPP, initial and
reviewed complete source/header/object/listing/build-log stages, selected
immutable **compound-counter.cpp/hpp**, **compound-counter.obj/asm**, both
selected diagnostic JSONs and `verified-summary.json`. Local `whole-audit.py
[OBJ]` compares all native instructions, direct targets, reference destinations
and owned DATA; the source diagnostic separately reads actual COFF literals.
Original native/constant/callee/exit evidence remains in F1222/F1226. Earlier
stages and all ten previous complete parents remain preserved.

Continue the register debt in this complete body. Only zero-difference
canonical affected-unit cold replay can accept the whole function. No accepted
input, origin/tracking ledger or canonical infrastructure change, full CI,
corpus replay, origin retest or per-function test is introduced.
