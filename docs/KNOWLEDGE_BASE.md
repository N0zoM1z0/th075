# TH075 reconstruction knowledge index

Updated 2026-10-25 for resumed reconstruction, F152. The active 98%
authored-byte objective remains incomplete. Current state and continuation
instructions are in [RE_HANDOFF.md](RE_HANDOFF.md).

## Authoritative inputs and evidence

- Target: supplied Japanese th075.exe 1.11, SHA-256
  `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
  Archive identity is pinned; independent official provenance is not established.
- `config/functions.csv` holds provisional boundaries/source state;
  `function-origins.csv` holds ownership. Source presence, names, Ghidra types,
  successful compilation and byte equality are separate facts.
- `config/match-units.toml`, `matches.csv`, `exact-adoptions.json` retain
  complete cold-exact units/all actual relocations. Counts are 333 units,
  717,040 code bytes, 136 canonical objects and 211 accepted inputs.
- Reviewed authored coverage is 36.33%; conservative coverage is 36.27%.
  All 97 unknown origins/3,608 bytes and all pending code stay in the conservative
  denominator. Origin evidence through R268 is unchanged.
- CODE size determines goal credit; compare_size includes owned tables/remaps
  for full acceptance. Never crop owned data or change the metric.

## Current source work

**004AC040, R048 authored:** `.analysis/character-move-4ac040/f152/` contains
all 151 nondefault fragments, real prefix/default/common tail and the first
complete compiled `Preview.cpp` (SHA prefix24ea3a57). Whole comparison remains
82,796 code + 1,126 owned data = 83,922 bytes. The draft emits 84,234 bytes,
including 83,108 code bytes (+312), with 74,320 position differences after
resolving all 2,352 actual relocation fields. No source-presence or exact
credit. Preserve F148/F150/F151/F152 and `build/probes/F152Complete.obj`.

Compiler observations: the 0x720 frame, saved ESI, EBP-0x64 receiver and 377-byte
dispatch prefix structure agree. Six pointer tables retain their actual widths
and all four byte remaps agree. These do not establish original locals/profile.
The explicit diagnostic profile is pinned VC7.1 build3077, /Od /Ob0 /Gy /GR-
/GX- /GS /Zi /I src. One Windows `PlaySound` macro collision was removed at the
complete source include boundary; accepted headers remain unchanged. All actual
local COFF offsets remain actual, with no native-label rebasing. Full unmasked
comparison remains authoritative; per-entry diagnostics are investigation only.

Next frontier: state6 has the first genuine instruction-order differences in
two floating expressions, despite equal403-byte size. Native loads both receiver
addresses before the x87 operand; emitted code loads the x87 operand between
them. State88 is the first size delta (+12), including native DWORD field copying
versus emitted x87 copying. No natural source correction is established yet.
Copy F152 inputs into a fresh F153 before further changes.

F150 covers the actual mapped states 390..420, adding 12,684 native
investigation bytes (35,886 contiguous bytes with source in total). It retains
three explicit sites in each 400..405 volley, five explicit sites in each
406..410 fan, and both separate five-site branches in 418. The eight real
loops in 416/417/419/420 bring the source to eleven genuine loop counters.
Nested `RecordedRange455580::SelectRange` arguments use the accepted 139-byte
unit and native right-to-left argument evaluation; original names/layouts
remain provisional. This source audit checks call evaluation order, not emitted
CFG or bytes. Native constants at 006590AC and 00657F74 are 110.0f and 0.25f.
State 416 decrements F00 without initializing it in that entry; preserve this
observed order. No compilation, source-presence or exact credit is claimed.

F151 added 27 actual mapped entries 500..610, covering 24,106 more native
investigation bytes (59,992 contiguous bytes with source at that checkpoint). Its audit had 926
canonical named calls, seven unaccepted command calls, fifteen genuine loops
and eighteen float-to-short conversions. Native entry/body/CFG/table/ABI,
source call evaluation order and real exits were rechecked. A separate scalar
contract audit verifies all direct literal float/integer store widths, values
and order in the 27 new entries; it does not prove calculated expressions,
conditions, original declarations or emitted bytes.

- 500/501 use repeat bounds 1/3; 502/503 use 2/4. The latter multiply motion by
  double constants 0.25/0.1. 501 sets gravity after its auxiliary effect call.
- 504..506 fade by 30 and launch at zero; 507..509 fade by 20 and launch after
  the repeated phase-8 reset path. Preserve the six distinct tracked effects
  and the post-call transform/alpha stores in each entry.
- 594..596 decrement byte 366 before clearing motion. Only 594/595 retain the
  pre-advance 3B6/7C guard, and 598/599 have no sound call at their spawn site.
- 600/601 decrement the short timer only inside the pre-advance phase >4 guard.
  Their five computed angle stores differ; 602 retains the native five-angle
  sequence 10,5,0,5,10. Do not infer symmetric negative angles.
- 603/605 each contain 36 distinct calls with literal angles 0..350 by 10.
  604/606 each contain nine distinct calls with literal angles -28..28 by 7.
  604 decrements F00 before advancing; 605/606 do not. 607..610 have four real
  ten-iteration loops. 607/608 restore motion from short F00/F02 times 0.01f
  before resetting/incrementing those shorts; 609/610 have no such restore.

F152 adds the final20 entries700..796/22,380 native investigation bytes. All151
entry fragments now cover82,372 contiguous investigation bytes. The source
audit retains1,290 canonical named calls,21 pending named calls,41 float-to-short
conversions and24 real loop counters/25 loops. The full native function has
1,358 calls including six true slot-0 calls. The scalar audit checks direct
literal float/integer store width/value/order in all20 new entries, not computed
conditions or expressions. The audits are frozen precompilation/preacceptance
snapshots. Eleven pending sites now have independently exact bodies in the new
scalar helper units; ten pending sites remain (seven454BC0,two452B30,one483300).

- 700/701 preserve the duplicate F00 zero stores and angle-pair spawn sites.
  701 sets F14 and omits the F04 increment. 702/703 retain five distinct repeat
  phases and `(SelectRange(0,100)>200)`; do not simplify that observed test.
- 704..707 retain different repeat bounds and landing guards. 706 returns after
  its advance-completion spawn, unlike the neighboring entries. Opponent status
  copies remain word copies; full opponent/owner layouts remain unknown.
- 731 reuses one real counter in two actual360-degree loops, while the six
  post-fade tracked effect sites remain explicit. Preserve the independent
  phase18/19 and20/21 gravity/landing branches. 741/742 retain fresh signed
  global level reads; 742 has four separate level loops (12,20,30,40 iterations).
- 751/752 retain short motion snapshots scaled by100, temporary polar speed
  **100.0f**, five explicit spawn phases and restores scaled by0.01f. 751's first
  random angle subtracts70 and the following four subtract50; 752 subtracts70
  at all five sites. Their gravity constants differ (0.01f/0.02f).
- 761 retains four distinct random-rain sites with right-to-left nested random
  argument evaluation, repeated level reads and opponent transform/alpha writes.
  762's landing returns before advancing; 763 refreshes facing at phase9 and
  selects761 on completion. Do not merge the neighboring fade/launch policies.
- 770 has four separate level loops (10,12,15,20 iterations). Its landing path
  continues into advance. 771 retains signed random rotation, short snapshots,
  unknown483300 aim call and actual divisor0.017453288659453392f at00657828.
  795/796 retain their fade/resource calls; only796 writes byte3CF after reset19.

Pending contracts are fully exported in `pending-helper-native-contracts.json`.
Resource452B30 is an authored215-byte policy with mixed transitive callees, not
accepted. Unknown483300 forwards two float stack slots to483320 and returns ST0;
483320 widens to doubles for642240 and performs FST single before returning ST0.
The private float return declaration is a used-ABI hypothesis, not ownership or
proof of original precision. Both unknown origins remain unchanged.

The observed two-slot receiver prefix is supported by constructor 004C0832,
table006594A8, complete R050/R068 bodies and four actual character calls in
already-exact BattleFrame::UpdateFrame. It does not recover a complete owner.
The separate global draw-dispatcher call is not character evidence.

**0050A580:** the complete 92-entry draft remains pending in full. Preserve
source SHA prefix 80ca174b and active F145CanonicalViews plus the five older active
objects listed in the handoff. Required comparison 82,106; actual diagnostic
82,109 bytes / 26,719 differences/522 GPR differences, all 1,449 actual fields.
F146's bounded negative compiler controls did not establish a natural fix.

**New F152 accepted code:** `FighterMoveScalarHelpers` has two declaration-only
methods in one source/object:37-byte `SetNonnegativeWord` at00453E80 and35-byte
`BeginFadeParameters` at00454A70. A single canonical cold build replayed both
whole units,72/72 exact with no relocations. Both saveECX atEBP-4 and returnRET4.
The first tests the signed low word and returns without a store when negative,
otherwise writes word3B8. The second writes byteF0 at538 then argument byte539.
R103 origin roles/native bodies and all real exits remain independently checked;
literal aliases preserve the old names. Neither interface establishes a complete
owner. The large source still uses its frozen pending view; migrate declarations
only in the next complete revision and compare all actual relocations again.

**Earlier accepted code:** F146's 51-byte motion helper00453E20, unit
`fighter-motion-clear-00453e20`, cold51/51 exact. The R103 role and original
database title are preserved by literal alias. Four DWORD zero stores do not
establish original field declarations or a complete owner layout.

**Pending command declaration:** wrapper 454BC0 (61bytes, RET12) is R213
authored; setters 410FA0/410FE0 (22bytes each, RET4) are R239 authored. All
remain unaccepted. The wrapper forwards byte/DWORD values through pointer 480.
Historical functions.csv notes about unknown setters are superseded by the
existing origin ledger. Original identifiers/signedness remain provisional.

F149 stopped during read-only reconnaissance of390..402. No additional case
was authored. State392's nested phase 6/phase 4 tests and400..402's three
explicit spawn sites must be preserved from native evidence rather than
optimized away/replaced by an invented loop. The unused duplicate work copy
was removed; F148 retains that earlier source/native checkpoint.

## Historical investigations

The complete former knowledge base, including original section titles,
observations, unknowns and R/F histories through F148, is retained byte-for-byte
as [KNOWLEDGE_BASE_THROUGH_F148.md](history/KNOWLEDGE_BASE_THROUGH_F148.md).
The former long handoff is retained as
[RE_HANDOFF_THROUGH_F148.md](history/RE_HANDOFF_THROUGH_F148.md).
Historical relative links were written from docs/: resolve them there or
read the original documents with Git at fd82165. Archived active-goal and
next-task instructions are superseded by this index, handoff and AGENTS.md.

Use an original address/evidence identifier to locate historical facts, then
confirm against the unchanged target and ledgers. Private source/checkpoints
are local and are not included in a Git clone. **Preserve this workspace when
switching agents.** Shared tools and the private Ghidra project also remain
local and read-only as documented.
