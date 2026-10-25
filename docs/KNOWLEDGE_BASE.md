# TH075 reconstruction knowledge index

Updated 2026-10-25 for resumed reconstruction, F151. The active 98%
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
  complete cold-exact units/all actual relocations. Counts remain 331 units,
  716,968 code bytes, 135 canonical objects and 209 accepted inputs.
- Reviewed authored coverage is 36.33%; conservative coverage is 36.26%.
  All 97 unknown origins/3,608 bytes and all pending code stay in the conservative
  denominator. Origin evidence through R268 is unchanged.
- CODE size determines goal credit; compare_size includes owned tables/remaps
  for full acceptance. Never crop owned data or change the metric.

## Current source work

**004AC040, R048 authored:** `.analysis/character-move-4ac040/f151/` contains
131/151 uncompiled nondefault fragments, full native CFG/table/entry proof,
default/common tail and source/call/constant/ABI audits. Twenty entries
remain, starting with state 700 at 004BAC11. Whole comparison is 82,796 code +
1,126 owned data = 83,922 bytes. No source-presence or exact credit. Keep F148
and F150 immutable; F151 copied the complete F150 input set before editing.

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

F151 adds 27 actual mapped entries 500..610, covering 24,106 more native
investigation bytes (59,992 contiguous bytes with source). There are now 926
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

The observed two-slot receiver prefix is supported by constructor 004C0832,
table006594A8, complete R050/R068 bodies and four actual character calls in
already-exact BattleFrame::UpdateFrame. It does not recover a complete owner.
The separate global draw-dispatcher call is not character evidence.

**0050A580:** the complete 92-entry draft remains pending in full. Preserve
source SHA prefix 80ca174b and active F145CanonicalViews plus the five older active
objects listed in the handoff. Required comparison 82,106; actual diagnostic
82,109 bytes / 26,719 differences/522 GPR differences, all 1,449 actual fields.
F146's bounded negative compiler controls did not establish a natural fix.

**Last new accepted code:** F146's 51-byte motion helper00453E20, unit
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
