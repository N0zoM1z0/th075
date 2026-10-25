# TH075 reconstruction knowledge index

Updated 2026-10-25 for cleanup and agent handoff. The user cleared the active
goal. The 98% authored-byte objective remains incomplete. Current state and
successor instructions are in [RE_HANDOFF.md](RE_HANDOFF.md).

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

**004AC040, R048 authored:** `.analysis/character-move-4ac040/f148/` contains
80/151 uncompiled nondefault fragments, full native CFG/table/entry proof,
default/common tail and source/call/constant/ABI audits. Seventy-one entries
remain, starting with state 390 at 004B1C5B. Whole comparison is 82,796 code +
1,126 owned data = 83,922 bytes. No source-presence or exact credit. Keep F148
immutable; copy current inputs before writing F150.

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
was removed; F148 retains every current source/native file.

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
