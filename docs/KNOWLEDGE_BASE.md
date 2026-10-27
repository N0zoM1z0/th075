# TH075 reconstruction knowledge index

Updated 2026-10-27: the user resumed reconstruction. F184 added two
canonical cold-exact input policies (+538 CODE bytes / 46 relocation fields);
F185 added the 1,273-byte title core state machine plus an owned 40-byte
switch table and 76 relocation fields, all cold exact.
F186 added a separate 951-byte options scene controller, seven-case owned
28-byte switch table and 70 relocations, also fully cold exact.
F187 added the 339-byte Win32 config writer and its 27 actual fields with
independent canonical cold comparison.
F188 adds the options text-resource update with 563 CODE bytes, seven-case
owned table, 34 fields, and natural EH/new/delete path, all cold exact.
The original H184 handoff was historical and is superseded by the current
request. Earlier experiments and names remain hypotheses until tested.
See the current [handoff](RE_HANDOFF.md) for current status.

## Authoritative state

- Supplied Japanese th075.exe 1.11, SHA-256
  `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
  Archive identity is pinned; official distribution provenance is uncorroborated.
- **499 exact functions/units, 753,102 CODE bytes, 171 canonical objects,
  276 accepted source-header inputs.** Reviewed coverage is 38.16%; conservative
  coverage is 38.09%, including all 97 unknown origins/3,608 pending bytes.
- Ownership, source presence, names, Ghidra types, compilation and reproducible
  exactness remain distinct. Read ledgers and relevant origin evidence before
  relying on any classification or provisional boundary.
- CODE size determines credit; comparisons also include owned tables/remaps.
  Only full canonical cold replay earns credit. Preserve evidence through R268
  and every pending byte in the conservative denominator.
- Original names and complete layouts remain provisional. Never instantiate or
  embed partial owners. The known complete 132-byte packet and SDK RECT16 may
  be instantiated; borrowed scene/drawing/manager views may not.

## Recent reproducible observations

F179..F183 added 16 exact units/9,888 CODE bytes across five pushed commits.
Each new unit passed full native extent/CFG/field review and canonical cold
comparison. Only new units were rebuilt. Each cohort passed 3,612 CI tests;
old canonical inputs, origins and protected evidence stayed unchanged.

| Cohort | Accepted result | Useful observation |
| --- | --- | --- |
| F179 | Background 435A70, 6,404 bytes/235 fields | Genuine two-side tint array and borrowed float windows reproduce native stack/x87/call behavior. |
| F180 | Eleven callbacks, 463 bytes/2 fields | Keep signed counters, strict 2500.0 versus inclusive 15360.0 double thresholds, reverse 3840 wrap and separate 72-frame cycle. |
| F181 | Timed sprite 451A00, 446 bytes/18 fields | cameraX bucket9 to cameraHorizontal bucket12 fixes real X allocation; the old same-bucket control stays closed. |
| F182 | Two name-entry policies, 1,486 bytes/76 fields | Keep actual 72-byte player spacing, signed repeat/modulo6, short INC/DEC, bounds/reset and extra shared toggle. |
| F183 | Title rendering 43A7A0, 1,089 bytes/26 fields | Measured real-local names yield packet-88/RECT-98/index-9C; retain ten stripe/item transforms and native color packing. |

F179's observed float windows cover 0x98..0xBC and 0xCC..0xDC without guessed padding or
owner instances. Member expression treatment changes while actual field widths,
operations and ABI remain. R163 sine 40D940 stays unknown; its existing
float(float)/ST0 view was unchanged. F181 adds no local, scope, type, layout,
precision or ABI workaround; CodeView and complete comparison verify the slots.

Every emitted readonly section and all definitions were checked where used.
No helper/data credit was added. D3DCOLOR masks express actual color semantics;
they are never comparison masks. Source patterns or mapped names alone prove
neither ownership nor exactness.

## F184: cold-accepted input policies

| Function | Native/emitted bytes | Returns / branches | Fields | Differences |
| --- | --- | --- | --- | --- |
| R043 43ABF0 title input | 228 / 228 | 1 / 9 | 19 | 0 |
| R053 429DC0 replay/shared input | 310 / 310 | 1 / 16 | 27 | 0 |

Both full extents have plain RET, no tables and verified alignment; all 18 calls
reuse canonical input/window helpers. Two separate pointer-only synthetic scene
views were compiled anew and registered with all 46 real relocation fields.
The canonical cold replay of both complete extents passed with zero differences.
Keep DWORD versus byte stores, independent direction checks, confirm/cancel,
Escape counter and actual chord placement. Reuse the existing mappings/counts.

The frozen original H184 preview source/object and resumption seed remain
historical evidence and were not reclassified as cold-built canonical objects.
The distinct F184 public source and one fresh canonical object are accepted;
full layouts/names remain unknown.

## F185: title-scene state-machine exactness

The independently measured target 0043A270 has 1,273 CODE bytes and an
immediately following 40-byte owned ten-case switch table. The entire
1,313-byte extent (76 relocation fields, including 11 local jump-table
references) cold-replays byte-for-byte from natural VC7.1 C++, using a genuine
single shared loop-local index and signed attract-mode state. Complete loop,
dispatch, exit and timed attract branches were retained; no cropped table,
comparison mask, padding, fabricated returns, assembly, or fake owner
instantiation was introduced. Native code SHA256:
`f528f379b927bad808eaa0703fa48c798fb8998bbae44ca9a2c96264215928a7`.
Owned table SHA256:
`01b9780b16a3176977d6c14d930d0eb42e860439a880b82435248b8459770254`.

Before success, the natural first probe was 1,312 bytes total (1272 CODE +
40 data) and mismatched the signed flag and time-branch layout. Its retained
variants record the alternative and allow independent replication. Inverting
the terminal time condition into a true attract-mode block reproduced the
native long `jbe` to the tail; changing the attribute to signed matched native
`movsx`. Reversing the ten-item alpha conditional matched the target's
separate highlighted-item store and decay/clear branches. A private duplicate
unit alias was identified and removed after verifying exact equivalence to
the registered unit, restoring exact unit↔ledger 1:1 correspondence and a
new automated check. Full owner layout, names and some global semantic roles
remain conjectural.

## F186: options-scene control-flow and volume policy

R066 00428F00 is 951 CODE bytes with the exact following 28-byte owned switch
table. Native body SHA256
`21e698c0f26cbca4c23286883c7de9a04cf91b1825c1090dfa320b09956f75fa`;
switch table SHA256
`f84e9f643843fc0db5c9ce2278848b8224a99bb915d32538e7d99646afd4f124`.
Independent x86 decoding yielded 269 complete instructions and one plain
RET. VC7.1 cold-compiles the full 979-byte comparison extent, zero byte
differences after all 70 actual relocations (eight local switch labels) are
replayed and verified.

The first valid source probe using `!g_Flag` generated a 982-byte comparison
block and three 8-bit SBB/INC pairs; the target used 32-bit SBB/INC.
`flag = 1 - (flag != 0)` generated 1001 bytes, while both
`static_cast<unsigned int>(flag == 0)` and the natural
`flag = flag ? 0 : 1` yielded zero structural differences across their
complete 979-byte blocks. The last expression was adopted because it retains
simple semantics without a cast chosen to force codegen. Full relocation
replay and canonical cold build then yielded exact, not merely a masked
structural match.

The signed two-axis input, signed-short menu index and sample timer,
modulo-four display selection, three toggles, signed volume adjustments,
explicit audio/stream refreshes, options materialization dependency
00429F00, configuration write helper 00419450, fade and 0x2202/9 returns
were preserved. The referenced callee 00429F00 has independent complexity and
no source/exact credit yet. No owner layout, source class identity, data
ownership or ABI beyond this method is inferred.

## F187: Win32 configuration writer with authentic stack slots

R052 00419450's full 339-byte native body has 116 Capstone-decoded
instructions and plain RET followed by alignment. The natural Win32
`CreateFileA("config.ini")`/`SetFilePointer`/eleven `WriteFile`/
`CloseHandle` sequence cold-compiles exact after all 27 physical DIR32
relocations. The filename literal at 00657A70 in the pinned target is the
exact ASCII `config.ini\0`; it is a source string, not newly credited target
data. All 80-byte bulk settings and ten 1-byte fields are written in the
original observed order, including the single setting explicitly set to 1
*after* writing its persisted value. Original full storage owner is unknown.

The first 339-byte probe with `HANDLE file` declared before `DWORD written`
failed 26 nonrelocation comparisons, entirely due to swapped real EBP slots.
The reversed natural declaration order keeps 339 bytes and matches all
register/stack references. The final namespace shares the already canonical
F186 `OptionsSettingsF186::SaveConfiguration` call target 00419450; F186
was neither edited nor unnecessarily rebuilt. No IAT, literal, or global data
bytes were added to authored-code credit. The native CODE SHA256 is
`4d1027f88999c9085d95ab8c24338439ad7fb2eaf122ac8b6c9f60065fa2d940`.

## F188: EH-backed options font/texture pipeline

The independent native `0x00429F00` body is 563 CODE bytes (137 complete
x86 instructions) and its immediately following switch table is 28 bytes.
Source `src/OptionsSelectionF188.cpp` cold-replays **all 591 bytes** and all
34 COFF fields, including one same-section table pointer plus seven local
case labels. Code SHA256:
`65e7c664f6846ac95a8085eeb2bba5eab32f5ad2c272cb3d2dfa049ad8e2d759`.
Table SHA256:
`3bab5fa7d3230c10ba3afdd6140cc4ddd35837b701713cbff1d0156ffe9a64b2`.

Pinned VC7.1 `/GX` (not `/GX-`) reproduces the native EH frame, cookie and
original allocation/cleanup shape. Native evidence independently anchors
`operator new(0x38)`, the constructor and destructor targets, a
D3D8 `IDirect3DTexture8::LockRect`/UnlockRect pair, a font setup/rasterizer
pair, and the original seven message strings. All 34 actual relocations were
replayed. The EH handler at `0x006558BD` and cleanup code at `0x006558AF`
were inspected as dependencies but earn no separate exact byte credit.

Controls show the 512-byte nominal buffer variant displaces meaningful
stack slots by eight bytes; natural 500/504-byte variants both recreate the
same stack shape, so the precise original declaration length is unknown.
The original function sign-extends the option index; an explicit signed
comparison changes MOVZX to the observed MOVSX without changing the F186
caller ABI. The offset-check typedef control changes VC7 local-label symbol
numbers without changing body semantics; it was not promoted. The ephemeral
56-byte glyph object has physically reviewed total size and supported access
offsets, but one +0x18 word is unobserved and the original class layout and
semantics remain provisional. Do not reuse that allocation carrier elsewhere
or claim a complete original font owner. No manual EH bytes, assembly,
comparison masks, fabricated returns, cropped tables, or other code/data
credits were introduced.

## Retained failures and method boundaries

Retain 14 frozen prior objects plus F184, all 14 F157 probes, both F159 traces
and 40 protected groups. Full 004AC040, 0050A580 and 0055AC80 drafts still fail
complete comparison. Their detailed closed controls remain in the archives and
private receipts; read them before another scope/profile/type/name experiment.
The old F176 440-byte probe stays negative evidence even though F181 accepts
the same native function through another complete 446-byte object.

R103 camera 453EB0 remains unaccepted. R231 unread camera stores, R065 445A00's
write-only local and R054 455B30's 28-byte clear need supported source-purpose
explanations; no unused locals, arrays or padding. Options switches need owned-
table comparison. The 43AD10 EH constructor needs real allocation/layout/lifetime
evidence; no pasted EH bytes or invented complete owners.

## Cleanup and historical evidence

Wine lowercases PDB names. Compare paths case-insensitively before treating a
PDB as unpaired or unprotected. H184 losslessly archived 480 old unpaired PDBs,
checked every full member hash, then removed their original outputs. Live object
companions, all objects, sources, profiles and evidence remain. The local archive
manifest permits restoring any individual original path. No frozen origin or
evidence file changed.

The complete former documents are preserved **byte-for-byte** in
[knowledge through F183](history/KNOWLEDGE_BASE_THROUGH_F183.md) and
[handoff through F183](history/RE_HANDOFF_THROUGH_F183.md). Original titles,
filenames, strings, observations and unknowns remain. Archived goal-state and
next-task commands are historical; current user instructions, AGENTS.md and the
handoff govern. Historical relative links were written from docs/. Earlier
[F148 knowledge](history/KNOWLEDGE_BASE_THROUGH_F148.md),
[F148 handoff](history/RE_HANDOFF_THROUGH_F148.md) and origin histories are unchanged.

**Preserve this workspace when switching agents.** Private artifacts, target and
project are not in a Git clone. Preserve shared tools and private service/auth
settings. Stay headless, use scripts/repo-python and the existing Ghidra wrapper
without REA, cold-replay only new/affected units and keep compilers serial.
