# TH075 — current agent handoff

**Maintained: 2026-10-29, after F589; this is the active handoff, not a research diary.** Start by checking the *live repository*; the figures below are a snapshot. The user requires serious work on **whole large boss functions and smaller leaves**, natural C++, independently checked original bytes, and immediate commits using `gpt-web: ...`. **All dirty changes belong to this one work session:** inspect, continue and finish them; never skip/reset/discard them. **Never run a full all-unit cold replay**—only the new or affected `--unit` entries.

## 1. Current authoritative state (not historical hypotheses)

| Item | Verified as of this handoff |
| --- | --- |
| Pinned original | user-supplied **Japanese** `resources/th075.exe` ver1.11; SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`; **never** localized `th075c.exe` |
| Whole exact C++ source | **943 functions / 943 exact units**, **862,726 original CODE bytes** |
| Reviewed original authored coverage | **43.71%** of **1,973,704** reviewed bytes; conservative **43.64%** with pending-origin bytes |
| Origin review | 4,351 provisional candidates; **1,004** origin-classified authored, **95** origin-pending, 3,420 origin-pending bytes |
| Current `owner=authored,status=unclassified` | **25 complete functions**: 22 large fighter bosses + 3 other originals below |
| Goal | **98% original authored bytes NOT attained**; local Git/Cold checks are **not** external Oracle receipts |

```bash
git status --short --branch
git log -5 --oneline
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/audit-active-handoff.py
scripts/repo-python scripts/ghidra.py check
```

**Trust, in this order:** the pinned original Japanese PE and its physical instructions, `config/function-origins.csv`, live `config/functions.csv`, whole physical COFF comparisons, *targeted* cold replay, `config/match-units.toml`, `config/exact-adoptions.json` and SHA-pinned source files. The provisional class/method names and decompiler locals are **not** authoritative original source declarations. Historical documents can be wrong; recheck against the PE. The complete 943-function accepted register is in `config/functions.csv`, not in this handoff.

## 2. Actual unresolved whole-function authored backlog

**The 22 giant fighter action/advance bosses are the principal coverage barrier.** All are separate, original authored function extents totaling **1,102,055 CODE bytes**; none has an accepted whole C++ source. Together they decode to **292,761 native x86 instructions, 16,861 calls and 84 physical indirect switch instructions**. Their **16,123 separate after-RET DATA bytes** (2,359 DWORD slots and 6,687 sparse index bytes) are *never CODE credit*. Follow [the full fighter cohort audit](FIGHTER_BOSS_FAMILY_DISPATCH.md), its frozen original manifest `config/fighter-boss-dispatch-fingerprints.json`, and read-only `scripts/repo-python scripts/verify-fighter-boss-family.py`. The 11 CharacterObject-family bosses each have one compressed switch; the 11 CharacterMove/Reimu-family bosses have 6–7. Four actual shared byte-index patterns occur, but **identical indices do not mean shared native destinations** and duplicate DWORD destinations are legitimate. For source work, inspect the verified whole [60,999-byte Reimu](REIMU_ACTION_BOSS_DISPATCH.md) and [82,796-byte CharacterMove](CHARACTER_MOVE_ACTION_DISPATCH.md) as starting points, not as “already restored” functions. **F537 has now independently resolved 7,152 original per-ID action entries across all 22 whole bosses (7,088 indexed, 64 singleton; 4,847 indexed inputs jump to each boss's native shared default).** See [the physical action/handler mapping](FIGHTER_ACTION_CASE_RESOLUTION.md) and the reproducible read-only `scripts/repo-python scripts/report-fighter-action-handlers.py --csv .analysis/f537-fighter-actions/whole-original-action-handlers.csv` (create its output directory first). This is a serious native whole-function dispatch milestone, but no giant has been C++ rebuilt or claimed exact. **F539 then established a real VC7.1 *natural single-switch* source generator for both 60,999-byte Reimu and 82,796-byte CharacterMove native dispatches: 66/66 x86 instruction grammars, exactly 325 bytes of dispatch geometry, all 522 sparse-index bytes, every 142/151 COFF DWORD slot and complete case-target equivalence partitions; see [the source-codegen experiment](FIGHTER_SWITCH_CODEGEN_RECONSTRUCTION.md) and `scripts/repo-python scripts/verify-fighter-natural-switch-probes.py`. This remains a *nonexact whole-boss* probe.** [F538 original action-zero audit](FIGHTER_ACTION_ZERO_NATIVE_LAYOUT.md) separately proves the same **50-instruction x87 case-zero sequence** inside all 11 multi-switch whole bosses (ten 180-byte cases, one 222-byte disp32 case), without claiming new exact CODE. Full original decompilation and meaningful probes live under `.analysis/f493-reimu-megaboss/`, `.analysis/f509-charactermove-megaboss/` and `.analysis/character-move-4ac040/`.

**F540 now verifies a genuine first giant-boss action-body C++ source hypothesis**:
[the 50-instruction action-zero native C++ proof](FIGHTER_ACTIONZERO_SOURCE_RECONSTRUCTION.md),
reproducible with `scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py`.
The 180-byte Reimu/CharacterMove case and all nine authentic call/data
references emerge from normal VC7.1 C++, and its instruction/branch/x87
structure generalizes to all eleven 180/222-byte original case-zero blocks.
All remain **parts of unmatched whole fighters, not independently exact units**. **F541 expands the natural action-zero source experiment to all 11 independently compiled multi-switch bosses**: each reproduces 50/50 original instruction and *per-fighter real register-choice* grammar and nine genuine case references, plus all 1,607 original-style DWORD table COFF fields, 4,502 identical sparse index bytes and 10,930 after-RET DATA-shape bytes. See [the eleven-fighter C++ codegen study](FIGHTER_ACTIONZERO_FAMILY_CODEGEN.md) and `scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py --boss 0x00486550`. No giant exact CODE credit. **F542 also reconstructs the full original 60-instruction action-1 native control/x87 case as natural C++ and compiles 11/11 fighter-specific switch probes.** All 11 have 60/60 native register/operand/branch grammars, 11/11 typed COFF references each, all 1,607 DWORD table fields and all 4,502 native sparse index bytes. Original case 1 is 212 bytes for ten fighters, 263 for EBP-0x88 due to 17 widened receiver loads. See [F542 action-one source/codegen evidence](FIGHTER_ACTIONONE_FAMILY_CODEGEN.md) and `scripts/repo-python scripts/verify-fighter-actionone-natural-source.py --boss Reimu`. Still zero full-boss exact CODE credit. **F545 now independently compiles all six opening actions (0..5) of each of the eleven multi-table fighter bosses**: 2,486/2,486 real original per-fighter register/branch/x87 instructions, 440 real case COFF roles, original table partitions and true individual action-4/5 float constants (notably 005D73C0 is +6.0/-4.5). Ten originals have 814 CODE bytes in these six cases; 00564BE0 has 1,006 due to 64 EBP-0x88 widened loads. See [the eleven-fighter six-case source proof](FIGHTER_OPENING_SIX_CASES_CODEGEN.md) and the new `scripts/repo-python scripts/verify-fighter-opening-actions-natural-source.py --boss 0x005D73C0`. No exact whole giant or split-case CODE credit. **F547 now adds the entire original 42-instruction action-9 C++ case across eleven newly compiled fighter-specific probes** (66 genuine typed case references, complete per-fighter sparse/index/table COFF partitions). `00543210` uniquely pushes `1` rather than `0` to `0040FB40`; six generated case-9 instances match exact original GPR allocation, five match native field/x87/control grammar but have different free-register assignments. Ten native cases have 144 CODE bytes; original `00564BE0` has 183 due to 13 wide receiver loads. See [F547 native C++ action-nine evidence](FIGHTER_ACTIONNINE_FAMILY_CODEGEN.md) and `scripts/repo-python scripts/verify-fighter-actionnine-natural-source.py --boss 0x00543210`. **No giant whole-function CODE credit.** **F548 now independently compiles a new complete 104-instruction, 362-byte native action-six C++ case in three whole giant original contexts** (`0045DD70`, `0058AF60`, `005D73C0`). It reproduces the 5-call native policy including the genuine virtual vtbl[0] method and 18 authentic typed COFF fields, 422 jump-table DWORD COFF refs and 1,323 original sparse bytes; each original character has distinct stage/float initialization. See [F548 action-six source audit](FIGHTER_ACTION_SIX_FAMILY_CODEGEN.md) and `scripts/repo-python scripts/verify-fighter-action-six-natural-source.py --boss 0x0058AF60`. The other eight case-six functions are different 96–125-instruction native families and remain for complete source investigation. **No giant exact CODE credit.** **F549 adds eleven separately compiled complete action-10 C++ cases**: 9 regular 31-instruction bodies and 2 genuine 20-instruction variants (the real EBP-0x88 fighter expands to 87 bytes). All 53 genuine case COFF call positions, 1,607 jump-table fields and per-character `0/2`, `3/2`, `0/1` state arguments are checked. Six actual GPR allocations match, five differ. See [F549 natural action-ten study](FIGHTER_ACTIONTEN_NATIVE_CPP.md) and `scripts/repo-python scripts/verify-fighter-actionten-natural-source.py --boss Reimu`. No full boss exact credit.

**F551 additionally reconstructs the entire 104-instruction action 7** within
three original giant fighters, while retaining independent action-6 source
verification. All **624/624** real two-case GPR/x87/control instructions and
**36/36** genuine call/global COFF references are verified under fresh
selected-only VC7.1 compilation. The original action-7 guard changes to 5,
callback to 0xCD, and per-role float position to 4.0f or 6.0f; the native
virtual calls remain exact in source shape. See [F551 action-six/seven family
source study](FIGHTER_ACTIONSEVEN_NATIVE_CPP.md) and
`scripts/repo-python scripts/verify-fighter-action-seven-natural-source.py
--boss 0x005D73C0`. **No whole giant or split-case CODE credit.**

**F553 additionally recovers actual original action 8** in three native
fighters through newly compiled natural C++. Reimu and `005D73C0` retain
104/104 native instructions; `0058AF60` has a *real* 102-instruction
variant omitting `FLAG = 0`, with 352 CODE bytes rather than 362. Each
character's C++ switch now independently validates complete actions
6, 7, 8: **934/934 per-fighter native instruction roles, 54 authentic
COFF references** plus full source-native switch-table layout. See
[F553 action-eight source proof](FIGHTER_ACTIONEIGHT_NATIVE_CPP.md) and
`scripts/repo-python scripts/verify-fighter-action-eight-natural-source.py
--boss 0x0058AF60`. No split/whole giant exact CODE credit.

**F556 independently reconstructs the harder 117-instruction/403-byte
action 6 and 7 original variants** inside `00486550` and CharacterMove
`004AC040` (82,796 original CODE bytes). Four original cases each compile
with full **117/117 original register/x87/branch instructions and 8/8 true
COFF call/global fields**, including a formerly absent guarded native
`0040FB40(5)` invocation and original float threshold `00657D14`.
The actual stage and float initializers differ between the fighters, and
CharacterMove's action 7 clears FLAG **before** float stores, unlike the
other original. Full description:
[F556 original 117-insn case source](FIGHTER_EXTRA_STAGE_SOURCE_F556.md);
targeted compiler command:
`scripts/repo-python scripts/verify-fighter-extra-stage-action-source.py --boss CharacterMove`.
**All 1,612 case bytes remain inside two whole unmatched giant functions**;
no split/whole CODE exactness credit.

**F557 adds two more entire 115-instruction original action-six/seven
source families** (`00543210`, `00564BE0`) with truly **no FLAG clear**.
Four new complete native C++ cases verify **460/460 original per-fighter
GPR/x87/branch instructions and 32/32 authentic COFF fields**, plus all
287 DWORD table slots and 669 original sparse bytes. The unusual 508-byte
source parent is explained by **37 wide native EBP-0x88 reloads + one
extra-long JL** per case, not padded C++. See
[F557 115-instruction source/codegen proof](FIGHTER_STAGE_NO_FLAG_F557.md)
and `scripts/repo-python scripts/verify-fighter-stage-no-flag-source.py
--boss 0x00564BE0`. These 1,802 native interior bytes are **not** full-
function exact CODE credit.

**F558 additionally reconstructs entire action 8** in both the 50,735-byte
`00486550` and 82,796-byte CharacterMove `004AC040` giants, while preserving
the earlier real action 6/7 C++ cases. Their complete original case sizes
are 403/403/362 bytes, with **676/676 actual native instruction roles**
and **44 genuine COFF fields** in the two newly compiled diagnostic source
objects. Critically `00486550` action 8 clears `FLAG` *between* position
and velocity initialization, whereas CharacterMove clears `FLAG` first.
See [F558 original action 8 study](FIGHTER_EXTRA_STAGE_EIGHT_F558.md) and
`scripts/repo-python scripts/verify-fighter-extra-stage-action-eight.py
--boss CharacterMove`. No full giant or independent case CODE credit.

**F559 additionally rechecks and reconstructs the complete native action
8** of the unusual wide-frame 61,872-byte fighter giant `00564BE0`,
while independently re-verifying its complete actions 6 and 7. Its new
102-instruction action-8 C++ source produces 352 bytes vs **458 native**;
exactly **34 long EBP-0x88 receiver reloads plus one long JL** account for
the native extra 106 bytes, with **no fake source padding**. The three
real action cases together have **332/332 original GPR/x87/branch roles,
22 genuine COFF call/float fields**, all original 131 DWORD jump slots
and 350 original sparse bytes. See
[F559 wide-frame action-eight native source proof](FIGHTER_WIDE_ACTION_EIGHT_F559.md)
and `scripts/repo-python scripts/verify-fighter-wide-action-eight-source.py`.
These 1,474 original inner bytes remain part of **unmatched whole giant
CODE** with zero independent/split-case exactness credit.

**F560 now reconstructs the full native action-8 source of giant
`00543210` (58,294 complete original CODE bytes)** in a newly compiled
VC7.1 C++ probe, retaining its action 6 and 7. Its real action-8
**117 instructions / 403 CODE bytes** place auxiliary stage-three
`0040FB40(4)` **before** contact/x87 comparison, then write native
-7.0f position, clear FLAG, and initialize 18.0f/0.95f motion on
transition. Two independent original-backed new source builds confirm
**347/347 full case x86 instruction roles, 24 true COFF fields, 156
physical switch DWORD fields and 319 byte-identical original sparse
bytes**. See [F560 full original action-eight case C++ study](FIGHTER_PRECONTACT_ACTION_EIGHT_F560.md)
and affected-only verifier
`scripts/repo-python scripts/verify-fighter-precontact-stage-action-eight.py`.
Its 1,189 inner original CODE bytes remain within **unmatched whole
giant source**; zero split/whole exact CODE credit.

**F562 separately reconstructs the full original action 6/7/8 C++
in the 43,601-byte fighter giant `004D7E70`**. Its three physical native
cases contain **102/115/102 x86 instructions and 352/393/352 CODE bytes**
respectively; only action 7 has the extra x87 stage condition and
`0040FB40(5)` callback. Newly compiled ordinary VC7.1 C++ matches all
**319 original GPR/x87/control instruction roles, 20 real COFF
call/constant fields**, the real action-6 `[eax]` versus action-7/8
`[edx]` virtual dispatch and all **140 native-style switch DWORD fields
and 409 exact original sparse indexes**. Actual role speed is 0.65f;
no source stage branch is fabricated in action 6/8. Reproducer:
`scripts/repo-python scripts/verify-fighter-split-stage-4d7e70.py`;
[F562 native original three-case source study](FIGHTER_SPLIT_STAGE_F562.md).
The **1,097 inner CODE bytes remain inside the nonexact giant**, not
independent exact function/CODE credit.

**F563 now reconstructs two previously unmodeled original
`FLAG > 0` secondary-motion giant-boss policies**, independently
within `004F7130` (44,211 original CODE) and `005AEEC0`
(71,616 original CODE). Six separate original action 6/7/8 cases are
fully modeled in normal C++, for **698/698 native real GPR/x87/branch
instruction roles**, **44 genuine COFF call/global fields**, real
fighter-specific two-stage motion constants, all **305** physical jump
DWORD fields and **822** exact sparse map bytes. Critically `004F7130`
performs a secondary override in both action 6/7 and clears `FLAG` only
at the end of the action-7 override, while `005AEEC0` overrides only
its action 6 and never clears FLAG in its three cases. See
[F563 native conditional-override source proof](FIGHTER_FLAG_OVERRIDE_SOURCE_F563.md)
and targeted reproducer
`scripts/repo-python scripts/verify-fighter-conditional-override-actions.py
--boss 0x004F7130`. The 2,440 original internal CODE bytes remain
inside **two unaccepted whole giant bosses**; zero split/whole exact
CODE credit.

**F564 integrates all eleven actual native actions 0..10 into one
newly compiled natural C++ Advance() function per whole original fighter**
for 004F7130 (44,211 CODE) and 005AEEC0 (71,616 CODE). Two fresh VC7.1
source builds verify **all 22 complete original action cases, 1,296 real
GPR/x87/branch/length instruction roles and 146 genuine typed COFF fields**
plus the full 305 physical switch DWORD fields, default/repeated
destinations, 822 exact sparse bytes and 2,042 after-RET DATA-shape
bytes. With real action6-8 source in the same function, action9/10
register allocation also reaches the native grammar. See
[F564 eleven-case integrated source study](FIGHTER_INTEGRATED_ELEVEN_CASES_F564.md)
and scripts/repo-python scripts/verify-fighter-integrated-opening-switch.py
--boss 0x004F7130. All 4,558 original inner CODE bytes remain inside
**two nonexact giant functions**, with later action cases/owner frame
not reconstructed and no whole/split CODE exact credit.

**F565 reconstructs the last previously unmodeled first-switch
fighter family, original 005214B0 (46,755 whole CODE bytes).**
Unlike the frame-update actor families it has 96/83/83 native action
6/7/8 x86 instructions, distinct signed stage >2 gated collision,
no final virtual frame-advance call and true 0040FB40(5/11/13)
versus 0040FAC0(9) character-state policy. One newly compiled
natural C++ source matches all **262 complete native instruction roles,
23/23 actual typed COFF call/global fields**, physical 139 switch
DWORD references and 345 original sparse-index bytes. See
[F565 distinct script-state source study](FIGHTER_SCRIPTED_STAGE_F565.md)
and scripts/repo-python scripts/verify-fighter-scripted-stage-actions.py.
These 911 inner CODE bytes remain in one entire **nonexact giant**,
with zero split/whole exact CODE credit.

**F566 now integrates all original actions 0..10 in ONE
freshly compiled natural C++ function for the unique 46,755-byte
scripted fighter giant 005214B0.** This moves beyond F565's
independent action6/7/8 source: all eleven original cases together
reproduce **550/550 physical native GPR/x87/branch/length instruction
roles, 73/73 genuine typed COFF reference fields**, all native 139
switch DWORD COFF slots and 345 byte-identical sparse index bytes,
with 901 separate after-RET DATA bytes. See
[F566 scripted fighter eleven-case source](FIGHTER_INTEGRATED_SCRIPTED_F566.md)
and scripts/repo-python scripts/verify-fighter-integrated-scripted-switch.py.
All 1,938 inner CODE bytes remain in the **nonexact** 46,755-byte
giant; later actions are diagnostic markers, not restored game source.
No whole/split exact CODE credit.

**F567 completes an original-backed integrated opening C++ source
experiment for all eleven giant multi-switch fighters**. The eight
previously unintegrated roles now each compile a separate single-
function VC7.1 Advance() containing the genuine first eleven native
game actions 0..10. Across all eleven (including previously verified
F564/F566): **121 original native game case subranges, 6,835 true
GPR/x87/branch x86 instruction roles and 790 actual typed COFF fields**
with all 1,607 native switch DWORD fields, 4,502 literal sparse index
bytes and separate 10,930 after-RET DATA-layout bytes. The unique
00564BE0 wide EBP-0x88 giant has 585 additional native byte lengths
from exactly 191 real wide loads and 3 long JL branches, not padding.
See [F567 all-eleven giant original action integration](FIGHTER_ALL_MULTISWITCH_INTEGRATION_F567.md)
and selected-only source verifier
scripts/repo-python scripts/verify-fighter-all-multiswitch-opening-cases.py
--boss 0x00564BE0. **All 613,391 whole giant CODE bytes remain
nonexact**, since the rest of the original game action cases and
real enclosing stack/owner lifetimes are still not source-complete.
All 24,529 inner-case original CODE bytes are diagnostic source
codegen only, zero split/whole exact CODE credit.

**F568 independently recompiled and audited the F567 eight giant
source contexts with a second original-backed COFF checker**, closing
a genuine physical relocation addend validation gap. All **571 actual
REL32/DIR32 case fields** in 88 native subranges, plus the **88 first
11-slot physical DWORD switch table refs**, have real zero COFF addends
and genuine original callee/global/source target identity. The
canonical F567 original-backed C++ verifier now explicitly rejects
nonzero addends; independent controls remain in the ignored research
directory, not a stale uncommitted duplicate. See
[F568 independent COFF addend control](FIGHTER_COFF_ADDEND_CONTROL_F568.md)
and targeted repro
scripts/repo-python scripts/verify-fighter-all-multiswitch-opening-cases.py
--boss 0x00564BE0. The eight complete giant CODE extents still are
NOT exact and receive zero additional CODE credit.

**F569 now reconstructs the real common pre-dispatch native C++
for ALL ELEVEN separate CharacterObject one-switch giants**, totaling
488,664 still-unmatched original CODE bytes. Fresh VC7.1 source
compiles reproduce each fighter's real 17-instruction two-part parent/owner
state guard logic, native 10-instruction cooldown decrement and
11-instruction compressed single-table dispatch. **11/11 original
guard/dispatch semantic paths**, 9/11 strict dispatch register
allocations, all **752 actual zero-addend COFF dense jump fields**,
2,185 identical native compressed byte indices and 5,193
after-RET DATA-layout bytes are verified. Actual 0050A580 wide
EBP-0xAC / -0xB0 stack slots widen six dispatcher loads by 18 bytes;
00536400 has extra original game logic preceding dispatch that
changes free registers. The 741 source action labels remain
**diagnostic-only marker stores**, not restored gameplay.
See [F569 one-switch source research](CHARACTEROBJECT_SINGLE_SWITCH_F569.md)
and targeted
scripts/repo-python scripts/verify-characterobject-single-switch-source.py
--boss 0x0050A580. The 488,664 original whole function CODE bytes
remain unmatched and receive zero new exact CODE/DATA credit.

**F570/F571 independently rechecked both near-exact smaller authored
destructor blockers**, not just the giant fighters: original 171-byte
ArchiveCatalog 0041CE50 and 248-byte SceneObject 0043B0B0.
Eighteen new VC7.1 archive lifetime/typed-pointer source variants
produced fourteen 177-byte bodies or four 171-byte bodies still only
108/115 or 102/115 comparable bytes. Ten new SceneObject source
variants (aggregate before texture delete, reversed fields and scoped/
named texture receivers) produced six 248-byte mismatches at 191/200
or 189/200 and four 251-/255-byte size mismatches. The original
three-way archive stack-slot permutation and texture/temp/three-heap
slot allocation are not yet solved. Preserve all negative artifacts
and treat neither function as exact.
[F570/F571 full local-lifetime study](DESTRUCTOR_LIFETIME_CONTROLS_F570_F571.md).
Zero accepted CODE/DATA and no all-unit replay.

**F572 newly reconstructs actual gameplay for the first TEN
native CharacterObject action bodies** inside the full 33,293-byte
one-switch giant `004EBDA0`, not just its F569 dispatch markers.
Seven genuine 13-byte/3-instruction leaf actions call native
`004F4170`; three different **complete 271-instruction** bodies
(`0x327`/`0x328`/`0x329`, 998/999/999 native CODE bytes) handle
8-effect spawning, the true `00453A70` parent effects API, x87 stage
motion and 13 real call/global symbols per body. A new *single*
pinned VC7.1 natural C++ TU reproduces **all 834 original x86
GPR/x87/branch/length instruction roles, 61 genuine typed COFF
call/global fields**, all 60 original jump DWORD COFF slots and
198 byte-identical compressed-map bytes. Source and affected-only
verifier:
[full F572 CharacterObject case-codegen study](CHARACTEROBJECT_FIRST_TEN_NATIVE_CASES_F572.md),
`probes/CharacterObjectActionsF572.cpp`,
`scripts/repo-python scripts/verify-characterobject-action-family-f572.py`.
These **3,087 original inner CODE bytes** remain part of the
**unmatched 33,293-byte whole fighter** with zero split/whole exact
CODE credit; the other game-action labels remain diagnostic markers.

**F573 adds the next actual complete `0x32A` action** in
33,293-byte CharacterObject giant `004EBDA0`, a **248-native
instruction / 932-byte original CODE** algorithm with six genuine
`FUCOMPP` floating equality checks, effect spawns, x87 motion and
state transition logic. One selected VC7.1 C++ source now models
**11 full real native cases, 1,082 physical original instruction
roles, 4,019 original inner CODE bytes and 80 authentic typed COFF
call/global fields**; all 60 physical DWORD switch fields and
198 compressed index bytes remain byte/authentic. Original action
`0x32A` has **exactly one two-instruction read-only MOV/FLD ordering
swap** in compiled source; the verifier independently proves that
single commutation, never credits its bytes as exact. Prior F572
10 actions still strictly reproduce their native machine order.
See [F573 six original x87 equality conditions](CHARACTEROBJECT_X87_ACTION32A_F573.md)
and `scripts/repo-python scripts/verify-characterobject-extended-action-f573.py`.
All **4,019 original inner CODE bytes remain inside the nonexact
whole 33,293-byte giant**, with zero whole/split exact CODE credit.

**F574 extends the same CharacterObject `004EBDA0` giant** with
complete real native action `0x32B` (112 x86 instructions /422 CODE
bytes) and `0x32C` (176/635), each reconstructed from original
stage/x87 motion and effect/collision C++ rather than case markers.
The first now strictly matches its entire original machine order;
the second has exactly one independently demonstrated adjacent
read-only MOV/FLD instruction-order swap, as already documented
for F573 action0x32A. One freshly compiled VC7.1 C++ function now
matches **all 13 original inner action bodies, 1,370 native x86
instruction roles, 102/102 real typed COFF fields**, 60 actual
native jump-table DWORDs, 198 original compressed bytes, and
438 separate after-RET DATA layout bytes. Source / local-only
reproducer:
[full F574 native-stage study](CHARACTEROBJECT_STAGE_CURVE_F574.md),
`probes/CharacterObjectActionsF572.cpp`, and
`scripts/repo-python scripts/verify-characterobject-following-actions-f574.py`.
**The 5,076 inner CODE bytes remain in the still unmatched
33,293-byte giant** and earn ZERO whole/split exact credit.

**F575 recovers complete original native CharacterObject `0x32D`
and `0x32E` fade-action C++** inside the same 33,293-byte fighter
giant `004EBDA0`: **66/229** and **70/282** original
x86-instruction/CODE-byte lengths, both strict native GPR/x87/CFG
order matches. The genuine original first action uses scale 0.4f
and float global 006583F8 plus conditional 20-byte alpha fade;
the second uses 0.5f, independent global 00659428 and
unconditional alpha decrement 10 after a `+0xD8==1` gate.
Original action0x32F maps to **default**, so actual 0x330 native
physical handler bounds the entire 0x32E case, not the next
numeric ID. The same newly compiled source now checks **15 full
native case bodies, 1,506 x86 roles and 113 true typed COFF
fields**, all 60 jump DWORD labels and 198 exact original sparse
bytes. Previous F573/F574 independent read-only MOV/FLD swaps
remain explicitly NONEXACT machine order; these two new actions
strictly match. Reproduce via
[F575 native fade C++ study](CHARACTEROBJECT_FADE_ACTIONS_F575.md)
and `scripts/repo-python scripts/verify-characterobject-fade-actions-f575.py`.
The **5,587 inner CODE bytes remain part of the still nonexact
33,293-byte giant**, not independent exact functions.

**F576 adds two more original large game-action bodies**, native
`0x330` and `0x331` inside the same `004EBDA0` CharacterObject
33,293-byte giant. Each whole native case has **274 instructions
and 1,003 CODE bytes**; a newly compiled natural C++ source emits
274 instructions /985 bytes because three real original native
integer-to-x87 temporary slots each use two disp32 instructions
(`6 × 3 = 18` extra native bytes per case). Native GPR/x87/branch
roles and all 16 genuine COFF refs in each case match; action331
uses original float global **00659090** where action330 uses
**006583FC**, verified by the original PE, not copied from templates.
The same newly compiled C++ now contains **17 real complete action
bodies: 2,054 original x86 instruction roles, 145 genuine typed COFF
fields and 7,593 native inner CODE bytes**, with 60 authentic
switch DWORD refs and 198 byte-identical compressed index bytes.
F573/F574's two earlier read-only MOV/FLD order exceptions remain
explicit, and both new actions have only explained stack encoding
width differences; no complete giant/source exactness credit.
See [F576 native fire-state source proof](CHARACTEROBJECT_FIRE_STATES_F576.md)
and `scripts/repo-python scripts/verify-characterobject-fire-actions-f576.py`.

**F577 newly reconstructs original native signed-byte direction
reversal action `0x332`** in the same CharacterObject giant `004EBDA0`
(33,293 complete original CODE bytes). The real physically bounded
`0x332` handler ends at `0x335`, since `0x333`/`0x334` are default
entries. Its full **279 native x86 instructions /1,019 CODE bytes**
are compiled into 279 instructions /1,013 bytes with the actual
stage-1 `S8(+0x66) = -S8(+0x66)` negation, native stage-zero
(+6.0f,+4.5f) motion and `0x322` effect-spawn ID. The only
length differences are native `EBP−0x9C` MOV/FILD operations
(+3 bytes each), never padded C++. A new one-TU C++ proof has
**18 real complete inner game-action bodies, 2,333 original x86
instruction roles, 161 true typed COFF fields and 8,612 actual
inner original CODE bytes**, plus all 60 native physical handler
COFF DWORD fields and 198 identical compressed index bytes.
Previous F573/F574 read-only instruction-order swaps remain
explicitly bounded. See
[F577 original direction-reversal source](CHARACTEROBJECT_DIRECTION_REVERSAL_F577.md)
and targeted verifier
`scripts/repo-python scripts/verify-characterobject-direction-reversal-f577.py`.
**The whole 33,293-byte original giant remains CODE nonexact**;
all inner CODE bytes are still part of that one unmatched whole
function and earn no independently exact coverage.

**F578 now reconstructs the whole original 269-instruction/
1,022-CODE-byte CharacterObject contact action `0x335`** inside
the still unmatched 33,293-byte giant `004EBDA0`, with actual
stage/saturation FX loop, native x87 movement, stage-ten collision
threshold 00657888 and stage-six float constant/member source order.
The new C++ compiler output has matching native instruction count,
GPR/x87/control operands and 17 true typed COFF fields; one genuine
adjacent independent read-only MOV/FLD pair at native indices 146/147
is explicitly documented as *not machine-order exact*. Crucially,
the newly added real source case shifts neighboring original action
`0x332`'s candidate temp from EBP−0x80 disp8 to EBP−0x84 disp32,
so its **279-instruction /1,019-byte native case length now matches
naturally without source padding**, while actual original EBP−0x9C
source bytes/whole giant remain nonexact.

In the *same newly compiled C++ function* F572–F578 now verify **19
real game-action bodies, 2,602 native instruction roles, 9,634 actual
internal original CODE bytes and 178 genuine typed COFF fields**,
plus all 60 native switch DWORD COFF destinations and 198 byte-identical
sparse-index bytes. The two earlier native read-only swaps remain and
only 36 real frame-width bytes across action 0x330/0x331 remain.
See [F578 native contact-stage study](CHARACTEROBJECT_CONTACT_STAGE_F578.md)
and `scripts/repo-python scripts/verify-characterobject-contact-stage-f578.py`.
**Full 33,293-byte giant still unmatched, zero split/whole CODE/DATA
exact credit.**

**F579 restores two additional complete native gameplay source
cases `0x338` and `0x339`** inside still-unmatched CharacterObject
giant `004EBDA0` (33,293 original whole CODE bytes). Native `0x338`
is a **130-instruction /478-byte** parent-effect spawn, native
00453E60 setup and 20-byte-color fade action; native `0x339` is
**80 instructions /309 bytes**, with genuine 1.3f scale and 40-step
color fade. Both newly selected C++ cases have **strict matching
native GPR/x87/control/individual byte-width grammar**, not just
unverified equivalence, and **9+6 genuine typed COFF fields**.
The same newly compiled C++ source now contains **21 actual
full original game-action bodies, 2,812 original x86 instruction
roles, 10,421 native inner CODE bytes, 193 genuine typed
COFF call/global fields**. Whole native jump DATA still matches
all 60 dense handler references and 198 original sparse index bytes.
Previously proven original 0x32A/0x32C/0x335 read-only source-order
swaps and 0x330/331 real EBP widened slots remain explicitly
bounded; 0x332 now naturally uses native disp32-width codegen.
See [F579 native fade/spawn study](CHARACTEROBJECT_FADE_SPAWNS_F579.md)
and targeted verifier
`scripts/repo-python scripts/verify-characterobject-fade-spawns-f579.py`.
The **10,421 original inner CODE bytes remain inside one
nonexact whole 33,293-byte giant**, not independent exact functions;
no full cold replay or fabricated coverage credit.

**F580 recovers FOUR more complete native CharacterObject action
bodies** in giant 004EBDA0: `0x33A` 66 x86/229 B, `0x33B`
84/301, `0x33C` 127/472, `0x33D` 127/472. All four are
**strict native x86 instruction/GPR/x87/branch/length matches**
in a new one-TU normal VC7.1 compile, with **31 genuine typed COFF
call/float fields** and no newly tolerated read-only swaps.
The native `0x33B` uses `TEST AH,5; JP`, which requires correct
`float < threshold` C++ semantics; `0x33D` first two parent
comparisons use 0x2C1 but **the third original compare uses 0x2BE**.
The same C++ now holds **25 complete actual original game-action
cases, 3,216 genuine x86 roles, 11,895 internal original CODE
bytes and 224 genuine typed COFF reference fields**, plus all 60
original native switch DWORD fields, 198 literal compressed index
bytes and 438 separate post-RET DATA bytes. F573/F574/F578's
three read-only MOV/FLD original-order exceptions and two deep
EBP-width actor cases remain explicitly bounded; the **33,293
whole original CODE bytes remain NONEXACT** with no standalone
case credit. See
[F580 four real original action source study](CHARACTEROBJECT_FOUR_ACTIONS_F580.md),
and run targeted
`scripts/repo-python scripts/verify-characterobject-four-next-actions-f580.py`.

**F581 adds TWO more strict original CharacterObject cases
`0x33E` and `0x33F`** inside original still-nonexact whole giant
`004EBDA0` (33,293 CODE bytes). The distinct native stage cases
are **127 x86 instructions/489 bytes** with original 00455580
scatter x87 globals `006578C0/006581E0/00659094`, and **101/381**
with distinct parent state `0x2C1` and original direction ×180.
Both newly compiled ordinary C++ source cases have **complete
matching original x86 GPR/x87/CFG/instruction byte widths and
10+6 real typed physical COFF fields**, no new order exceptions.
The same one-TU VC7.1 source now proves **27 complete real action
bodies, 3,444 native instruction roles, 12,765 native inner CODE
bytes and 240 genuine physical call/global COFF fields**, along
with all 60 original native dense handler COFF slots and 198 exact
sparse bytes. The original 33,293-byte giant remains NONEXACT;
no inner case is independently accepted CODE.

The SMALL 171-byte ArchiveCatalog destructor at `0041CE50` was also
independently retested with **14 new true POD/array/union/volatile
C++ filename ownership forms**. All fresh compiles retain 51
instructions/171 bytes but the original **108/115** nonfield byte
match/three-way EBP slot permutation persists, so ZERO new small
function exact credit. The negative source and COFF comparisons
are retained under `.analysis/f581-archive-expr-order/`.
See [F581 native parent scatter plus small destructor check](CHARACTEROBJECT_PARENT_SCATTER_F581.md),
and targeted source verifier
`scripts/repo-python scripts/verify-characterobject-parent-scatter-f581.py`.
No all-unit cold replay or external Oracle.

**F582 now reconstructs two more complete native CharacterObject
absolute-motion cases**, original `0x340` and `0x341` inside giant
`004EBDA0`. Each entire physical native case is **159 x86
instructions / 597 original CODE bytes**, with real parent direction
×90, original cdecl float `00412D90` and original FMUL 00659724,
contact threshold/velocity and two distinct 00453A70 effect IDs:
0x338+0x33A / 0x342+0x344, with native parent 00453D40(8/10).
Natural C++ parent and collision **real lvalue reference
expressions** reproduce exact original register/load/x87 branch
order, verified in alternative compiler experiments. **Both newly
compiled full source cases pass strict GPR/x87/branch/instruction
length geometry and 13+13 authentic typed zero-addend physical
COFF references**, no new source-order exceptions.

In the same one-TU VC7.1 diagnostic C++ source there are now
**29 complete original action bodies, 3,762 original native x86
instruction roles, 13,959 original inner CODE bytes and 266 genuine
typed COFF call/global references**, plus all original 60 dense
DWORD switch COFF fields and 198 exact compressed-index bytes.
The 33,293-byte *whole* giant is NONEXACT and these inner bodies
are never credited as exact standalone functions. See
[F582 full native absolute-motion source study](CHARACTEROBJECT_ABSOLUTE_MOTION_F582.md)
and targeted
`scripts/repo-python scripts/verify-characterobject-abs-motion-f582.py`.
No all-unit cold replay or Oracle receipt.

**F583 continues with THREE complete native CharacterObject
state/short-actor actions `0x342/0x343/0x344`** in the entire still
nonexact 33,293-CODE-byte giant `004EBDA0`. Genuine original
complete native x86 case footprints are **87/338**, **80/309** and
**66/229** (instructions/inner CODE bytes), respectively. Native
`0x342` invokes stage setup `00453E60(10f)` and real effect
`00453A70(0x343)`; `0x343` has distinct **1.7f float scales,
0065825C x87 global, signed stage>=0 and 20-step color fade**,
not copied `0x339` logic. `0x344` independently reproduces the
sprite 0x4E2/-75f original fade with global 006583FC. All three
new normal C++ sources reproduce the **strict original native
GPR/x87/control/instruction-width order** and **17 authentic
typed COFF call/global refs**.

The same newly compiled switch now verifies **32 physically true
original action bodies, 3,995 native x86 instruction roles, 14,835
native inner CODE bytes and 283 typed zero-addend COFF fields**,
plus all 60 physical DWORD jump slots and 198 identical native
compressed index bytes. Existing three read-only swap/EBP-depth
caveats remain; none new. See
[F583 original stage/fade case study](CHARACTEROBJECT_STATE_LEAVES_F583.md),
selected reproducer
`scripts/repo-python scripts/verify-characterobject-state-leaves-f583.py`.
**Whole 33,293-byte giant remains NONEXACT, zero independent split
or whole CODE credit.** No full cold replay or external Oracle.

**F584 independently retests the smaller 171-byte /51-instruction
nonvirtual ArchiveCatalog original destructor `0041CE50`**, not just
another giant switch. Twelve real VC7.1 `/GX-` C++ delete-expression
variants from an original-backed tracked baseline (cast,
lvalue-reference, alias, pointer-to-pointer, conditional) were
freshly compiled. **Ten still produce 171 bytes/51 instructions but
only 108/115 identical nonrelocation bytes** and retain the source
resource/destructor/filename EBP slots `−0x10/−0xC/−0x8` rather than
native **`−0xC/−0x8/−0x10`**; two conditional forms produce invalid
193/198-byte bodies. Original 51-instruction PE and all three saved
local differences were independently checked before compilation.
This excludes trivial source `delete` syntax as the original owner
lifetime solution; the function remains **NOT exact**. Full targeted
reproducer
`scripts/repo-python scripts/verify-archive-delete-expressions-f584.py`,
and [F584 whole-original destructor negative controls](ARCHIVE_DELETE_EXPRESSION_CONTROLS_F584.md).
The 943 existing exact functions and 862,726 accepted CODE bytes
remain unchanged. No all-unit cold replay, fabricated stack padding
or external Oracle acceptance.

**F585 reconstructs FIVE complete original native CharacterObject
trajectory and coordinate-sync actions `0x345..0x349`** inside
still-nonexact giant `004EBDA0` (33,293 entire original CODE bytes).
The three genuinely large trajectory actions are **286/1,144,
286/1,136, 289/1,153** (original x86 insns/CODE bytes) with
original angle ±180 wrapping, speed caps 140/+7, 120/+6,
200/+10 and real `006406AC` external `__ftol2` conversions.
Native `0x348` uniquely reverses its polar angles with two NEG
ops. The two distinct 111/436 native parent-sync cases call
`__ftol2` twice each and use real parent `+0xF0C/+0xF0E` state.
The first small probe rotated their EAX/ECX/EDX roles; *adding the
real giant action C++ source in the same switch* naturally recovered
correct registers and total complete byte lengths in all five cases,
without compiler padding or ASM.

New one-TU selected PE/COFF source proof has **five strict original
complete action x86/GPR/x87/CFG/byte-width cases**, **1,083 native
instruction roles, 4,305 original inner CODE bytes and 71 genuine
typed zero-addend COFF fields**. Across F572–F585 the one C++
switch now has **37 complete game actions, 5,078 original
instruction roles, 19,140 original internal CODE bytes and 354
real typed PE-grounded COFF records**, with all original 60 dense
jump slots, 198 literal compressed bytes and 438 native after-RET
DATA shape. Runtime `__ftol2` is external, not authored original.
See [F585 five real trajectory source cases](CHARACTEROBJECT_TRAJECTORY_F585.md)
and selected verifier
`scripts/repo-python scripts/verify-characterobject-five-trajectory-actions-f585.py`.
**Whole giant 33,293 CODE still NONEXACT; zero separate case or
whole exact credit.** No all-unit cold replay or Oracle.

**F586 newly restores original full CharacterObject actions
`0x34A` and `0x34B`** inside still-unmatched 33,293-byte giant
`004EBDA0`. The real former is **295 native x86 instructions/
1,093 CODE bytes**, with stage-zero 0065786C x87 contact,
0040FB40(1), original random(0,60), effect 0x323. The latter is
**278/1,012**, whose actual `0040FB70` caller passes two RAW
DWORD position fields `+0xC8/+0xCC` in native cdecl/thiscall
push order, not a float-to-integer conversion, and uses distinct
00657478 velocity decrement, random(0,15)-60 and effect 0x324.
Both newly compiled full case bodies match **strict native
GPR/x87/CFG/per-instruction byte-width geometry and all 18+17
genuine typed zero-addend original PE COFF fields**.

Critically, the added real source expands the *same enclosing*
C++ actor's saved x87 temporaries: the old native 0x331
(274/1,003) vs source 274/985 width gap of 18 real original
bytes shrinks to **274/997, only 6 bytes**. The new natural
source allocates actual temporaries `EBP−0x80/−0x84/−0x88`,
with only native ordinal97/98 disp32 vs source disp8; the other
four original `MOV/FILD` instructions now have identical sizes.
A new **strict original-PE slot verifier** preserves precisely
these two legitimate source contexts for native 0x331, without
relaxing registers, x87, CFG or introducing fake EBP padding.
The related source 0x332 temporary naturally moves from −0x84 to
−0x8C, retaining original machine-code width but not original
stack-slot identity. Across one new freshly compiled TU F572–F586
now prove **39 complete real game-action cases, 5,651 native x86
roles, 21,245 original internal CODE bytes, 389 authentic typed
COFF call/global fields**, 60 physical jump DWORD slots and
198 exact sparse bytes. Whole 33,293-byte fighter CODE remains
**NONEXACT**, no standalone inner case CODE or DATA credit.
See [F586 original 0x34A/34B and stack-frame evidence](CHARACTEROBJECT_LATE_STAGES_F586.md)
and targeted
`scripts/repo-python scripts/verify-characterobject-late-stage-actions-f586.py`.

**F587 now reconstructs the complete original 397-instruction /
1,529-CODE-byte CharacterObject four-way event action `0x34C`**
in original still-nonexact 33,293-CODE-byte giant `004EBDA0`.
It restores four *different* parent actor states `0x198/0x19A/
0x19C/0x19D`, original stage gating, native 8-effect loop, real
x87 position globals `006590A8/00658264` and complete signed
random transformations to four distinct native effect IDs
`0x322/0x323/0x324/0x325`, including separate real
`00455580/00453A70/00453D40` calls. One newly compiled VC7.1
source emits **all 397 original GPR/x87/CFG/per-instruction
width roles in exact order, with 25/25 genuine typed COFF
physical fields**, no new tolerated instruction-order difference.

Another *real compiler frame result*: the newly added giant action
naturally shifts earlier source action0x331's temporaries from
EBP−0x80/−0x84/−0x88 to **−0x84/−0x88/−0x8C**, so its
source length now **274/1,003 bytes**, identical to native original
274/1,003 rather than the prior F586 274/997. Its exact original
EBP slots remain different, so these are still **not byte-exact
original functions**; strict old source verifiers now distinguish
all three separately observed original/C++ temporary layouts.
Across F572–F587 one ordinary C++ function now verifies **40
real complete native game-action cases, 6,048 original x86
instruction roles, 22,774 original internal CODE bytes and
414 authentic typed PE COFF call/global refs**, all 60 original
switch DWORD fields and 198 exact compressed index bytes.
The whole 33,293-byte original is still NONEXACT with zero
independent inner CODE/DATA credit. See
[F587 complete four-state game action study](CHARACTEROBJECT_FOUR_WAY_EVENT_F587.md)
and run targeted
`scripts/repo-python scripts/verify-characterobject-four-way-event-f587.py`.
No full cold replay or external Oracle receipt.

**F588 newly reconstructs three MORE full original CharacterObject
stage actions `0x34D/0x34E/0x34F`** in the **still nonexact
33,293-CODE-byte giant `004EBDA0`**. Physically bounded complete
native cases are **190 instructions/697 bytes**, **163/603** and
**161/599**. Real `0x34D` preserves two raw DWORD motion field
copies (not incorrect FPU loads), native 5-effect parent loop,
contact effects 0x32B/0x32D and state0x33B. Real `0x34E` has
only a 4-effect parent loop, signed timer `>2` and no stage-zero
7C/80 stores; real `0x34F` has signed timer `>1`, its own
7C/80 stage0 stores and native direct reset callback. All three
**match complete original GPR/x87/branch/per-instruction width
source grammar, with 35 genuinely typed zero-addend original
PE COFF call/float fields**, no new tolerated swaps.

This is also the first ordinary natural source context where
previous native actions `0x330/0x331/0x332` have **literally
identical original Japanese EBP integer-to-FILD temporary operand
addresses**, not merely equal instruction lengths: 0x330 original
−0x84/−0x88/−0x8C, 0x331 −0x90/−0x94/−0x98, 0x332 −0x9C.
All are independently checked in source-only and original-PE
verifiers. No fake locals or machine-code byte grafts.

The SAME single-TU C++ now proves **43 real complete gameplay
cases, 6,562 original x86 instruction roles, 24,673 original
internal CODE bytes and 449 genuine typed physical call/global
COFF fields**, as well as all 60 native first-switch DWORD
handler fields and 198 identical sparse indexes (438 distinct
native after-RET DATA-layout bytes). Whole 33,293-byte boss
still **NONEXACT, zero separate case CODE/DATA exact credit**.
See [F588 three native stage cases plus original EBP source](CHARACTEROBJECT_THREE_NATIVE_STAGES_F588.md),
and targeted verifier
`scripts/repo-python scripts/verify-characterobject-three-late-actions-f588.py`.
No all-unit cold replay or external Oracle.

**F589 independently targets the SMALL complete 248-native-CODE-byte,
75-instruction original SceneObject virtual EH destructor `0043B0B0`**.
New tracked verifier freshly compiles **14 actual VC7.1 `/GX`
texture-delete C++ pointer/cast/reference source alternatives**.
All 11 ordinary equivalent resource-pointers reproduce the original
248-byte/75-instruction size and **12/12 original PE-typed physical
zero-addend COFF fields**, but **only 191/200 nonfield bytes**
because native texture temps at EBP−0x14/−0x10 and original
three resource frees at −0x18/−0x1C/−0x20 differ from C++
−0x20/−0x1C and −0x18/−0x14/−0x10. Three ternary controls
compile to invalid 267/272 whole CODE bytes. No fake padding,
byte-patching or incorrect source exact credit; original 248
function remains unaccepted. See
[F589 original scene texture-delete evidence](SCENE_TEXTURE_DELETE_CONTROLS_F589.md),
targeted whole-original verifier
`scripts/repo-python scripts/verify-scene-texture-delete-f589.py`.
The current 943 exact functions, 862,726 CODE bytes and all 22
still-nonexact original giant bodies remain unchanged. No cold
all-unit replay or external Factory/Oracle receipt.

**Three other authored functions remain nonexact (all require full CODE):**

| Original function / PE address | Size | Best meaningful current evidence / precise blocker |
| --- | ---: | --- |
| `GameApplication::RunAt00602A60` / `00602A60` | **2,987** | **654** original instructions, **123** calls, actual **0x278** frame and **15** scene switch cases. F528 complete native-like C++ `outer0-firsttmp1-while1.cpp` has **2,981 bytes /654 instructions /123 calls /0x278**, all **654/654 ordered x86 mnemonics** but only **224/654 identical complete operands+lengths**, so **not exact**. Most important true EBP locals: scene -0x184 vs candidate -0xC, pathname -0x180 vs -0x158, AppMode -0x3D vs -1, graphics -0x189 vs -0xD. Fix real C++ owner layout and lifetimes, not instruction counts or synthetic padding. See [full native WinMain audit](WINMAIN_ORIGINAL_CONTROL_FLOW.md), `scripts/repo-python scripts/verify-winmain-scene-dispatch.py`, `.analysis/f525-*` through `.analysis/f530-*`, `.analysis/f528-winmain-native-initial-scene/detailed-insn-alignment.tsv`. Original 60-byte after-RET scene table is DATA. |
| `SceneObject::ReleaseAt0043B0B0` / `0043B0B0` | **248** | Genuine virtual destructor with original EH and three owned heap frees. Full natural `/GX` C++ reaches **191/200** original nonrelocation bytes, but physical native texture/delete temporaries at EBP -0x14/-0x10 and actual heap pointers -0x18/-0x1C/-0x20 disagree with compiler allocation order. `.analysis/f215-battle-release/struct0.cpp`, `.analysis/f449-scene-texture-heap-release/`, `.analysis/f533-scene-native-separate-pointers/`. No 248-byte credit. |
| `ArchiveCatalog::Release` / `0041CE50` | **171** | Actually the **nonvirtual local RAII destructor** of the archive catalog, paired with `0041CE10`, as established from WinMain original call/receiver EBP -0x35. Genuine C++ destructor yields complete **171 bytes, 108/115** nonrelocation bytes (14 COFF fields), but physical resource/delete/filename locals at -0xC/-8/-0x10 differ from source -0x10/-0xC/-8. `.analysis/f343-archive-release/`, `.analysis/f531-archive-real-raii-destructor/` and `.analysis/f517-archive-true-name-record/`. Virtual destructor form is wrong (182 bytes). No 171-byte credit. |

**No other `owner=authored,status=unclassified` function is currently in the live ledger.** The **95 pending origins** are a separate provenance classification problem; do not silently count them as authored. The full original authored-byte goal remains distant, even though many smaller game bosses are already exact.

## 3. Important *already solved* functions: do not redo old “pending” experiments

| Previously disputed | Current correct result | Canonical source / batch |
| --- | --- | --- |
| Font Shift-JIS lead-byte range helper `0041CA30` | **77 whole CODE; 28 native instructions, 0 COFF relocations, 1/1 targeted cold exact**, four exact byte-boundary comparisons (0x81, 0xA0, 0xE0, 0xFF); sole native caller is already-exact authored `0041C9D0`. R183 originally kept authorship unknown; F555 re-reviewed probable game-local authored policy. No private original class identity, library/vendor provenance certainty or SDK table is invented | `src/FontLeadByteF555.cpp` / F555 |
| Combat-coordinate transform `00455770` | **111 full CODE, 29 instructions, 4 native DIR32; 1/1 cold exact**. Source uses genuine VC7.1 unparenthesized float lvalues; provisional owner has no observed direct callers. Distinct from all 22 large bosses and the 3 other nonexact originals | `src/CombatCoordinateViewF536.cpp` / F536 |
| GameProgress selected-record increment `00425130` | **92 CODE, 24 insns, no COFF fields, 1/1 cold exact**; actual native codegen requires **postfix** `SELECTED_COUNT++`, not prefix `++` | `src/GameProgressIncrementSelectedRecordF535.cpp` / F535 |
| NameEntry/Result rank labels `0042B110`, `00431890` | **169 + 169 CODE; 2/2 cold exact**; real 132-byte quad member in used local aggregate, separate glyph[8], real `/GS` | `src/NameEntryResultRankGlyphLabelsF516.cpp` / F516 |
| Replay filename glyph draw `0042C270` | **303 CODE, 1/1 cold exact**; correct prefix+132-byte quad aggregate and separate real glyph[8] | `src/ReplaySceneDrawSaveFilenameF514.cpp` / F514 |
| StaffRoll state/timing `00438C20` | **208 CODE, 1/1 cold exact**; real fighter/score branches *inside* outside-time-window guarded scope | `src/StaffRollSceneAdvanceF504.cpp` / F504 |
| Fighter and stage loading bosses `004183D0` and F407 fighter load | **3,765** and **3,232** original CODE already exact in F389/F407; do not double count | `src/BattleStageLoadBossF389.cpp`, `src/BattleCharacterLoadBossF407.cpp` |
| DataArchive writer/reader, replay finalizer, font rasterizer | 686/429, 375, 1,766 CODE **already exact** | F339/F338, F328, F319 |
| Original WinMain window callback `00603650` | **83 CODE already exact**, *not* the adjacent 2,987-byte WinMain | F468 |

Earlier F323/F424/F425/F450/F475/F478/F495/F503/F506/F510–F513/F521–F524 probes are **historical negative controls**. A statement such as “rank labels/Replay/StaffRoll/progress counter remain unclassified” in older research means **then**, not **now**. The chronological [KNOWLEDGE_BASE](KNOWLEDGE_BASE.md) and Git history retain those tests; current status comes exclusively from the live ledgers.

## 4. Required exact acceptance and commit procedure

1. Check `git status --short --branch` and **take ownership of all dirty work**. Verify Japanese original hash and authored origin for the complete function. Do not accept a plausible decompiler signature or a borrowed class size as proof of original layout.
2. Reconstruct the *whole* original natural C++ function including all return paths, genuine x87/scalar behavior, automatic object lifetimes and after-RET jump DATA bounds. Use ignored `.analysis/` for complete source hypotheses and pinned MSVC VC7.1 (`scripts/compile-probe.sh`; right `/GX` or `/GX-` profile), with `scripts/repo-python scripts/compare-coff-function.py ... --json` for diagnostics.
3. `structural-exact` alone is insufficient. Independently check **all** real physical COFF `REL32`/`DIR32` offsets, types, original PE destinations and object addends. Only whole original CODE counts; original jump DATA and external CRT/SDK/callee CODE never count.
4. Add affected units to `config/match-units.toml`, then cold replay **only** those units: `scripts/repo-python scripts/replay-exact-units.py --unit YOUR-NEW-UNIT` (multiple named `--unit` only when needed). **NEVER** launch an all-unit cold replay.
5. Only on `N/N exact`, update `config/functions.csv`, `implemented.csv`, `known-symbols.csv`, `reccmp-functions.csv`, `matches.csv`, `exact-adoptions.json`, the SHA256 in `tests/exact_checkpoint.py`, progress SVG via `scripts/repo-python scripts/update-progress.py`, README and this handoff. Use `scripts/repo-python scripts/validate-tracking.py --require-target`, `scripts/repo-python scripts/update-progress.py --check` and **light** `scripts/repo-python scripts/ci.py` (no whole-build cold replay). `git diff --check`; promptly `git commit -m 'gpt-web: ...'`; check tree again.

See [RE_WORKFLOW.md](RE_WORKFLOW.md), [BUILD_MATCHING.md](BUILD_MATCHING.md), root `AGENTS.md` and the original-only verification scripts for complete commands. A real and valuable research milestone can be documented and committed **without** dishonest CODE credit (e.g. F520 22-boss cohort).

## 5. Storage, protected artifacts and recovery

The active original PE, `src/`, `config/`, `tests/`, `.analysis/vc71-wine/` (about 1.3 GiB: actual VC7.1 environment), private `ghidra-project/`, `.tools/`, **all** `build/probes/*.obj`, `build/matching/` and the **15 H184 SHA256-protected PDB/COFF source pairs** are protected. Never reset/remove them to save space. Protected entries: `.analysis/h184-handoff/active-object-retention.json`. Keep the current **large-boss decompilations, negative C++ source and meaningful comparison results** in `.analysis/`, which is intentionally Git-ignored and not available on a fresh clone without local state.

Older, redundant parent/adoption **JSON snapshots** are now **individually SHA256-verified, losslessly archived** as adjacent `.json.zst`, indexed in `.analysis/cache-archives/snapshot-compaction-index.json`; they are *restorable*, not irrecoverably lost. Their historical registration scripts expected old commits anyway. To recover a specific old input or verify all archived evidence:

```bash
scripts/repo-python scripts/archive-historical-analysis.py --restore .analysis/f180-background-counters/parent-and-seed.json
scripts/repo-python scripts/archive-historical-analysis.py --verify
```

Old unprotected `/Zi` probe `.pdb` caches are retained in **independently hash-verified** archives `.analysis/cache-archives/probe-pdb-unprotected-2026-10-28.tar.gz` and `probe-pdb-unprotected-2026-10-29.tar.gz`, each with a per-file receipt. To restore **one** old PDB (no all-unit builds):

```bash
tar -xzf .analysis/cache-archives/probe-pdb-unprotected-2026-10-29.tar.gz -C . build/probes/FILE.pdb
```

Check the per-file SHA256 in the adjacent receipt. See [STORAGE_HYGIENE.md](STORAGE_HYGIENE.md) for exact storage savings, protected paths and recovery. **Do not delete original or generated matching COFF `.obj`, negative source, frozen manifest, native research or local tools.**

## 6. History and next agent orientation

Start from **§2** above, always work on at least one *whole* large boss alongside smaller outstanding code. Repeated brute-force variable renames, inert locals or cropped CODE are not progress. F555 completed a newly re-reviewed, whole 77-byte Shift-JIS byte-range helper (now 95 origins pending), preserving the historical R183 unknown-owner snapshot and its independent ordinary member alternative. F536 previously completed the 111-byte coordinate transform; F535 completed the 92-byte progress leaf; the meaningful smaller remaining are the **171/248-byte real destructors**. The 22 massive controllers dominate unaccepted authored CODE. Detailed older attempts are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md) and `git show 8da230b:docs/RE_HANDOFF.md` (the earlier verbose 338-line handoff), while the prior ancient handoff is explicitly archival `docs/RE_HANDOFF_HISTORY.md`. **Never treat a historical “pending” claim as live status.**

F538 adds [eleven independent native action-zero case bounds, 50-instruction signatures and 14 stack-reload observations](FIGHTER_ACTION_ZERO_NATIVE_LAYOUT.md). All 22 full fighter bosses remain nonexact pending complete natural C++ source, while F537 retains the original 7,152-entry action map.
