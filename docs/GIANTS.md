# The 20 remaining giants

All 20 currently unmatched authored functions are slot-1 `Advance` methods
from 11 fighter and nine character-object vtables: per-frame state machines
with large `switch (action)` bodies, 34–83 KB each. Thirteen parents have a
complete research source in `probes/`: Alice object `004EBDA0` and Remilia
object `0055AC80` are now exact, leaving 11 complete but nonexact parents.
The other nine remaining functions have no complete parent yet.

Measure a parent with

    scripts/repo-python scripts/measure-giant.py [ADDRESS ...]

It cold-builds the parent with its recorded flags and compares its
`Advance` with the original instruction by instruction: mnemonic and width
differences, and positions whose general-purpose registers differ ("GPR
debt"), with the first such position. It is a diagnostic only. A giant
becomes exact only through a complete replay unit in `config/match-units.toml`.

`config/frontiers.toml` lists the parents (source, flags, symbol, original
extent and its SHA-256) with the byte offsets that still differ after
relocation fields are masked. After editing a parent, run

    scripts/repo-python scripts/check-frontier.py [NAME ...]

It fails if the body size changes or a byte that matched now differs.
Record an improvement with `--update NAME` and commit the file with the
source change.

The Youmu object parent now reads the native `std::list` front through
`YoumuFighter::historyQueue` (+0xFEC), the same list appended and pruned by
its exact 1,008-byte auxiliary writer. The original 0xFF8 allocation and
VC7.1's 12-byte list establish the shared owner/member layout. The entire
40,464-byte research COFF body is unchanged, with all 938 relocations retaining
their positions, types, addends and local targets; the front-call symbol now
names `std::list<ObservedInputSnapshotF378>::front`. This remains a NONEXACT
giant. Its 81 affected exact units cold-replayed 81/81.

The shared 0x54-byte effect manager now owns four `std::deque<Actor*>`
instances rather than borrowed raw/void-pointer views. The complete
constructor, destructor, cleanup, spawn and bind functions retain their
exact full bodies; their 58 header-dependent units replayed 58/58. Its 24
code/EH/data sections and 46 relocations verify against the unchanged PE with
fresh 3/3 owner cold-replay receipts. This supplies a typed implementation
for the fighter/object effects used by the large Advance state machines.

The effect manager's frame advance (296 bytes) and both render dispatch
methods (166/207 bytes) are now methods of the same
`EffectManagerLifetimeF161` object that constructs, owns, spawns and clears
its four `std::deque<Actor*>` members. They cold-replay 3/3 with their entire
original bytes and relocation destinations; the temporary owner view classes
and headers are gone. This restores a single native C++ owner for fighter and
object state-machine effect calls without changing the outstanding giant
register-allocation frontiers.

The already-exact 31,352-byte `CharacterAuxObject::Advance` auxiliary
boss now uses direct C++ short assignments in 16 random/decay paths instead
of redundant explicit narrowing casts. The complete 31,777-byte COFF section
and all 913 relocations still pass cold exact replay (1/1).

Youmu's shared 16-byte history record now uses ordinary named members,
with no alternative union aliases or object-side overlay typedef. The
1,008-byte snapshot writer and all 81 affected exact units cold-replay; the
whole 40,464-byte object `Advance` parent remains byte-for-byte identical,
including all 938 relocation records. Its nonexact register frontier remains.

## Complete research parents

The table lists all 13 complete parents. Meiling, Yuyuko, Yukari and Suika
were remeasured on 2026-11-20; the other rows retain their 2026-11-19
measurements. Instruction, width and register counts are diagnostic measures,
not byte equality; mnemonic/width drift can accompany a register-allocation
change.

| Original | Character | Size | Parent | GPR debt | Widths | First GPR difference |
| --- | --- | ---: | --- | ---: | ---: | --- |
| 0045DD70 | Reimu fighter | 60,999 | `FighterWhole0045DD70F1183.cpp` | 6,311 | 5 | 0045FDA9 (#2292) |
| 004AC040 | Sakuya fighter | 82,796 | `FighterWhole004AC040F1020.cpp` (`/GX`) | 6,958 | 12 | 004ADEFA (#2180) |
| 005214B0 | Youmu fighter | 46,755 | `FighterWhole005214B0F1040.cpp` | 2,736 | 5 | 0052327A (#2103) |
| 00543210 | Remilia fighter | 58,294 | `FighterWhole00543210F1041.cpp` | 1,741 | 3 | 00545109 (#2198) |
| 004CA6E0 | Sakuya object | 42,511 | `SakuyaObjectAdvanceF1222.cpp` | 447 | 12 | 004CCBD7 (#2526) |
| 004EBDA0 | Alice object | 33,293 | `CharacterObjectActionsF572.cpp` (exact replay) | 0 | 0 | — |
| 0050A580 | Patchouli object | 81,539 | `PatchouliObjectAdvanceF1044.cpp` | 522 | 5 | 00515C0E (#10128) |
| 00536400 | Youmu object | 39,999 | `CharacterObjectActions00536400F1211.cpp` | 913 | 10 | 005392F8 (#3223) |
| 0055AC80 | Remilia object | 28,432 | `CharacterObjectWhole0055AC80F1194.cpp` (cold exact) | 0 | 0 | — |
| 0057D580 | Yuyuko object | 43,845 | `CharacterObjectActions0057D580F1237.cpp` | 914 | 6 | 00583489 (#6565) |
| 005A1600 | Yukari object | 43,599 | `CharacterObjectActions005A1600F1231.cpp` | 613 | 11 | 005A88A8 (#7965) |
| 005C9CC0 | Suika object | 43,501 | `CharacterObjectActions005C9CC0F1216.cpp` | 935 | 1 | 005D2558 (#9213) |
| 005EB520 | Meiling object | 34,434 | `CharacterObjectWhole005EB520F1207.cpp` (no `/GS`) | 135 | 6 | 005F3904 (#9200) |

The flags are `/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes` unless noted.

Marisa fighter `Advance` (`0x00486550`, 50,735 CODE bytes) now has a
tracked, natural-C++ partial parent probe. It derives from the real
`MarisaFighter`, uses named inherited `Actor`/`Fighter` fields and methods,
and contains 158 recovered action-state bodies. Recent batches added states
`0x46`–`0x4C`, `0x58`, `0x5D`–`0x62`, `0x8F`/`0x90`, `0x97`–`0xA8`,
`0xC8`–`0xD2`, `0x12C`–`0x136`, `0x186`–`0x18B`, `0x190`–`0x1A3`,
`0x1F4`/`0x1F5`,
`0x208`/`0x20A`–`0x20E`, `0x252`–`0x25D`, `0x270`–`0x271`,
`0x2BC`–`0x2D1`, and the late `0x2E5`–`0x2F9` / `0x31B`–`0x31C`
resource tails. The latest three nested handler bodies (`0x12C`, `0x1F4`,
`0x2C2`) add 1,147 original bytes. A follow-up machine-code audit corrected
38 landing comparisons from inclusive `<= 0` to strict `< 0` where the
original x87 `FCOMP`/status-word `JP` branch requires it, while retaining the
separate inclusive stage-exit guards in `0x133` and `0x189`. It also fixed
`0x2F9`'s 50-unit opponent spacing and 870-unit reset height. The probe and its Marisa-specific
counter fragments contain no raw offset casts, ASM, padding, or synthetic
marker cases. The expanded source covers all 141 unique top-level Ghidra
action labels and all 158 explicit in-parent handler groups; the shared
default handler is retained as a real default path. This inventory is
repeatable with `scripts/validate-marisa-advance-cases.py`. VC7.1 compiles it
to 51,920 CODE bytes / 14,840 instructions; the original is 50,735 bytes /
14,260 instructions. This remains deliberately NONEXACT and is not entered
into the complete-parent frontier: the 1,185-byte / 580-instruction code
generation difference is real and unaccepted. The 468-value original
dispatch map and its 153 unique handler addresses remain the authority for
further case work.
Three shared fighter fragments required a context-sensitive terminator:
ground boost 0x9E, landing siblings 0xA3-0xA5, and motion restart 0xB4/0xB5.
Their original top-level fighter parents correctly use switch-break exits,
but Marisa's partial parent nests them inside a sparse switch followed by
switchDefault. Each fragment now accepts a local exit macro defaulting to
break; Marisa explicitly selects return for its nested uses. This preserves
the existing complete Reimu/Sakuya/Remilia parent source semantics while
preventing Marisa from falling through to an extra frame advance. Rebuilt
complete-parent measurements are unchanged: Reimu 60,999/62,090 bytes and
6,311 GPR/5 width differences; Sakuya 82,796/83,922 bytes and 6,958/12;
Remilia 58,294/59,236 bytes and 1,741/3. Marisa's partial parent compiles and
the source-coverage validator remains 141/141 labels and 158/158 handlers.

Marisa action 0x62's resource selector, the 0xA7/0xA8 projectile-launch
pair, and the 0x97/0x98/0x9A-0xA1 landing-timer siblings now return after
their native nested-frame/counter update. Their three former breaks entered
the partial default handler despite the original Ghidra cases returning.
The per-fragment validator now checks these terminal edges too.

The same original-return audit fixed four more Marisa state fragments:
scripted bounce 0x59, recovery 0x4C, jump landings 0x8F/0x90, and landing
timer 0x96. Their six old switch breaks now return on the native contact,
counter-completion, or timer-update paths. The validator now enforces these
per-fragment terminal edges as well.

The remaining early trajectory handlers 0x46, 0x49, 0x4A and 0x58 now
also preserve their original return paths. Their 15 switch breaks covered
the stage-threshold exits, landing/contact transitions, bounce redirect,
and stage-one resource follow-up branches; the original decompilation returns
from each of those paths. All 15 now return from the parent rather than
falling into the partial switchDefault frame handler. The Marisa validator
guards the per-fragment exit counts, and the full partial parent still
compiles with all action/handler coverage intact.

Marisa trajectory follow-ups 0x47/0x48 now preserve six additional native
returns. The original handlers return after their stage-3 early reset, after
the ground-contact transition into action 0x61, and after the ordinary nested
frame/secondary-counter update. Replacing the partial parent's six switch
breaks prevents these paths from reaching switchDefault and advancing another
frame. The validator checks all six exits; the partial parent compiles and
retains complete source-label/handler coverage.

Marisa's resource volleys 0x60/0x61 also had four incorrect switch breaks.
The original handlers return both when the stage-3 ground boundary is hit
and after the ordinary nested-frame/volley-counter update. The partial parent
now returns on those four paths instead of entering switchDefault and
advancing another frame. The Marisa validator guards all four exits, and the
parent still compiles with full source-label/handler coverage.

The same nested-switch return audit now covers Marisa actions 0x5D-0x5F
and 0x91. Original Ghidra control flow confirms seven terminal exits in the
early-bounce/facing group and three in the arc-trajectory action. Their old
break statements fell through to the partial parent's common default frame
handler; all ten now return directly, matching the original transition,
landing, and frame-completion paths. The validator guards these exit counts,
and the full Marisa partial parent compiles with all 141/141 top-level labels
and 158/158 explicit in-parent handlers still covered. This remains a
semantic correction to the partial parent, not whole-function exactness.

Marisa's eleven contact actions 0x33-0x41 in F600 now preserve the native
return edges instead of breaking out of the partial parent's nested action
switch. Ghidra's original parent has no switch breaks in these eleven cases:
each ordinary contact path returns after AdvanceNestedFrame/ResetPrimaryCounters,
and the 0x35/0x3B/0x41 repeat paths return after their stage-7 counter update.
The old 14 breaks fell through to switchDefault and could advance the frame a
second time. All 14 terminal exits are now returns; the Marisa validator
guards this structure along with action 0x63. The complete partial parent
recompiles and still covers 141/141 top-level labels and 158/158 explicit
in-parent handler addresses. This is a runtime-semantic correction, not a
whole-function exactness claim.

The BG02a/BG02b/BG02c load constructors now use the same native
NativeBackgroundBaseF479 layout as their destructor views. Each has a real
SpriteQuad40CA80 member at +0x6C and the preceding +0x68 word; the base
TextureManager at +0x18 and the three stage words at +0x0C..+0x14 are direct
members. TextureManagerF198 now owns its unformatted-slot allocation,
archive load/default and blend methods instead of three independent
call-only receiver aliases. The three BG02 constructors and the three
TextureManager helpers replay exact (6/6); the remaining stage constructors
still need their individual derived layouts recovered.

The BG02a/BG02b/BG02c 60-byte blend methods now access the original
embedded TextureManager member directly. BackgroundStage's native base
layout is represented as its virtual base header, +0x04 camera-reset state,
the three stage-specific words at +0x0C..+0x14, and the 80-byte
TextureManager at +0x18. The constructor at 00449DE0 and destructor at
00449D40 independently establish the same embedded object lifetime; the
80-byte TextureManager layout is also asserted by its own constructor and
destructor views. The three blend bodies and the 65-byte SetBlendMode leaf
remain structurally exact. Unknown camera-state words and historical class
spelling remain provisional; this does not claim a complete stage owner.

The 162-byte BattlePointerQueues::ReleaseEntries leaf now exposes its two
side lists as named adjacent NativePointerListF337 members instead of
reinterpret-casting this+0 and this+0x14 at each use. The observed 20-byte
list view is backed by std::deque<void*>: VC7.1 confirms sizeof 0x14, the
native Size helper reads +0x10, and At returns void** for the pointers that
the owner frees. The two-member receiver prefix is checked as 0x28 bytes;
the unknown remainder of its original owner and allocator/lifetime details
remain unclaimed. The focused 005F7140 replay is still byte-exact, including
all eight original COFF relocations.

The linked-effect transform copy is now expressed through one native
36-byte TransformRecordF136 packet shared by the Fighter and Actor layouts.
Fighter+0x2F0 exposes it as effectTransformRecord; Actor+0x10 exposes it as
transformRecord. EffectManagerLifetimeF161::Spawn no longer manufactures an
Actor+0x10 pointer with raw byte arithmetic, and both fighter tracked-effect
forwarders pass the named packet. The VC7.1 compiler still emits the original
nine-DWORD REP MOVSD copy: the full 282-byte Spawn body and all three
relocations replay exact. Actor/Fighter layout assertions retain sizes 0xC4
and 0xF10, and five focused units (Spawn, both tracked-effect forwarders,
their shared Fighter forwarder, and ResetTransform) replay 5/5 exact. The
Sakuya object parent and Actor rendering consumer also compile against the
overlaid declarations. No full cold replay was run.

Marisa fighter partial parent action 0x63 now preserves all five native
terminal paths as returns, including the ordinary nested-frame completion
after its three conditional mode-3 transitions and one mode-not-3 transition.
terminal transitions as return statements. The partial parent places this
case inside a nested sparse switch(actionSnapshot) followed by the shared
switchDefault frame path; the previous break statements exited only that
inner switch and incorrectly advanced the common frame after a transition.
The original action has three mode-3 transitions and one mode-not-3 transition
that return immediately. The focused parent compile succeeds, and
validate-marisa-advance-cases.py still reports all 141/141 top-level labels
and 158/158 explicit in-parent handler addresses covered. The validator now
guards the four-return/one-break structure. This is a semantic correction to
the partial natural-C++ parent, not a whole-function exactness claim.

Patchouli object's 81,539-byte giant now calls native typed C++
helpers in place of its last random/angle/sound alias methods:
`PatchouliObject::RecordedRange` for 37 compiled native calls,
`Actor::SetPolarVelocity` for 19 calls (including exact float-bit
argument recovery), and `PatchouliObject::PlaySharedSound` for two.
Whole 82,109-byte COFF bodies preserve all 1,449 relocation positions/
types, zero nonrelocation byte changes and its unchanged nonexact
24,643-byte frontier. All 24 `CharacterObject.hpp`-affected exact
units cold-replayed successfully.

Patchouli action `0x34B` was audited against its x87 branch, not just the
Ghidra pseudocode. The target uses `FCOMP` / `FNSTSW` / `TEST AH,0x41` / `JNE`;
that condition also takes the movement path for unordered values. The existing
natural-C++ `if (y > bound) ClearFrameInfo(); else move;` emits the matching
condition. A positive `y <= bound` rewrite changed the body to 82,110 bytes
and displaced many matching offsets; `!(y <= bound)` kept the size but added
a new differing byte. Both candidates were rejected, and the source remains
unchanged. The targeted animation-progress and ClearFrameInfo leaves replay
exact (2/2).

Patchouli object `0050A580` now defines `PatchouliObject::Advance` on its
actual vtable class. The parent preserves its complete 81,539 CODE bytes,
with 522 GPR and five width differences. Thirty-two parent sound calls
and seven camera-shake calls use the existing Fighter/EffectServices
interfaces. Six additional Patchouli source spawn sites (seven compiled calls, as one
state is included twice) now use `Fighter::SpawnBattleEffect` with native
float arguments. Both complete 82,109-byte function objects have all 1,449
relocation offsets/types identical and no differing nonrelocation bytes.
The remaining 71 source sites use original DWORD bit transport and are
intentionally not converted into numeric float casts.
A full conversion of those 71 raw source sites to direct float calls failed:
the COFF body increased by 32 bytes and added two `__ftol2` relocations.
The raw conversion was rejected, while the seven separately verified
float-argument calls were retained.
All 24 header-affected exact functions cold-replayed. A subsequent
Patchouli whole-function compiler comparison converted 24 more source
spawn sites across nine case files from unsigned coordinate-bit overloads
to the native `Fighter::SpawnBattleEffect` float API with ordinary `x, y`
field arguments. The compiled 82,109-byte body and all 1,449 relocation
positions/types were unchanged, with zero nonrelocation-byte differences.
A second batch converted 19 further source spawn sites across 12 case
files. Both batches preserve the entire 82,109-byte function object,
all 1,449 relocation offsets/types and every nonrelocation code byte.
A final 27 raw-coordinate spawn sites and both auxiliary/tracked
spawn sites have now also moved onto `Fighter` members, leaving just
one unresolved 0046D000 cross-character gauge-timer call behind the
borrowed interface. The final whole-function VC7.1 object remains
82,109 bytes with all 1,449 relocation positions/types preserved
and no nonrelocation-byte differences. This is natural-source recovery,
not new exact giant credit.

Sakuya object `004CA6E0` now defines `SakuyaObject::Advance` directly.
The original 42,511 CODE bytes are still nonexact (447 GPR-role and
12 width differences). Of its 929 COFF relocation records, 52 effect
spawns, 22 sounds and 13 tracked spawns now bind to the real
`Fighter`/`SakuyaFighter` interfaces. The parent body size, every
relocation offset/type and every nonrelocation instruction byte remained
unchanged; 24 header-affected exact units cold-replayed.

Remilia object `0055AC80` defines `RemiliaObject::Advance` on its real
class. Twenty-four random-range, 25 effect-spawn, seven sound and two
shared-sound call sites use typed C++ members instead of borrowed receiver
aliases. The earlier 28,868-byte research draft retained 726 GPR-role and
six instruction-width differences. The later F1194 state-flow reconstruction
uses a natural non-initial-frame preservation branch and now cold-replays the
complete 28,432-byte native CODE body exact. Its 232-byte guarded jump table
and 198-byte remap are also independently compared in the 28,862-byte extent;
all 696 physical relocations resolve to original destinations. The tables are
comparison data, not additional authored CODE coverage.

Remilia fighter `00543210` now directly defines `RemiliaFighter::Advance`
under the native character class, rather than a research-only subclass.
Four observed projectile X sources use `Actor::x` instead of a borrowed
+0x44 field view. The 59,236-byte before/after COFF bodies have all
1,863 relocation offsets/types and every nonrelocation byte unchanged.
All 98 fighter-header-affected exact units cold-replayed (36/36, 31/31,
31/31). The original 58,294 CODE bytes remain NONEXACT (1,741 GPR-role,
three width differences). No giant exact credit was claimed.

Remilia fighter `00543210` now defines `RemiliaFighter::Advance` on
its actual class instead of an artificial research subclass. Four
projectile expressions now use the inherited `Actor::x` rather than
borrowed +0x44 views. Original and modified VC7.1 parent objects both
contain 59,236 bytes and 1,863 relocations; all relocation positions/types
and every nonrelocation byte are unchanged. Its 58,294 native CODE bytes
remain NONEXACT with 1,741 GPR-role and three width differences (40,569
frontier differing bytes); all 98 affected exact units were cold-replayed
in three groups (36, 31, 31). No new whole-giant exact credit.

The 00454BC0 action-command selection interface is now the real
`Fighter::SetCommandSelection(int,unsigned char,unsigned int)` in Reimu,
Sakuya, Youmu and Remilia giant state machines (7 / 7 / 4 / 17 native
calls). This also removes speculative per-character `int,int,int`
prototypes: the actual VC7.1 code, COFF body sizes and all relocation
offsets/types are unchanged. The 132 affected exact units cold replayed
in three affected-only groups (44/44 each), and no giant exactness is
claimed.

The original camera-shake leaf at `00453E60` now belongs to the real
`Fighter::SetCameraShake(float)` API rather than a borrowed receiver class.
The native leaf remains structural-exact (25-byte full body, one relocation).
Four complete fighter and five object giant research parents now call it
from 72 compiled sites (51 fighter + 21 object), retaining each entire
COFF body size, relocation offsets/types and every nonrelocation byte.
All nine complete native giant frontiers remain NONEXACT but nonregressing.
An affected-only replay of 103 directly related exact units was 103/103
across three batches (36/34/33); the full 449-unit Fighter.hpp header
fanout was intentionally not cold-replayed.

Four fighter giant research parents now call shared, verified Fighter
helpers instead of provisional class-specific aliases: 122 native
`CheckHorizontalLimits` calls (00454EE0), 29 `SetNonnegativeWord`
(00453E80), nine `BeginFadeParameters` (00454A70), nine
`SelectResourceParameters` (00452B30), and six `SpawnAuxEffect`
(00453C80) calls. Their original 62,090 / 83,922 / 47,655 / 59,236
byte COFF bodies and all 1,824 / 2,352 / 1,491 / 1,863 relocation
offsets/types are preserved, with zero changes outside relocation
fields; four nonexact native frontiers are not worsened. All 132 affected
exact units cold-replayed locally in three groups of 44/44 (not a full
repository replay).

The Sakuya fighter 004AC040 source now calls the real Fighter effect
APIs at 270 compiled sites: 153 `SpawnBattleEffect`, 104 seven-argument
`Fighter::SpawnTrackedEffect`, and 13 `SpawnAuxEffect` calls. The two
whole 83,922-byte VC7.1 COFF bodies contain the same 2,352 relocation
positions/types and zero differences outside relocations. No new
independent giant exactness is claimed; native frontier remains nonexact.

Sakuya fighter `004AC040` (82,796 original CODE bytes) now directly
defines `SakuyaFighter::Advance`, rather than an artificial derived
research receiver. Sixteen included state files use the actual
`x`/`opponent->x` field instead of borrowed +0x44 views, and the
opponent transform resets through the native `Actor::ResetTransform`.
The full 83,922-byte VC7.1 object is byte-identical outside all
2,352 unchanged relocation positions/types; its 6,958 GPR-role and
12 width differences remain nonexact (18,253 differing frontier bytes).
All 98 affected exact units cold-replayed across three groups (36/36,
31/31, 31/31). No giant exact credit was claimed.

Youmu fighter `005214B0` now directly defines `YoumuFighter::Advance`
on the native fighter class. Thirteen source state files use actual
`x`/`opponent->x` fields in place of a temporary +0x44 owner view, and
15 opponent state resets now call `Actor::ResetPrimaryCounters`.
The two 47,655-byte whole COFF bodies have identical nonrelocation bytes
and all 1,491 relocation offsets/types; its 46,755-byte original CODE
remains nonexact (2,736 GPR-role and five width differences, frontier
16,833 differing bytes). All 85 exact units depending on the real fighter
header cold-replayed in three affected-only groups (36/36, 25/25, 24/24).

The Reimu fighter, Alice object and Meiling object research parents now
directly define `ReimuFighter::Advance`, `AliceObject::Advance`, and
`MeilingObject::Advance`, rather than artificial derived classes. Alice's 33,293-byte parent uses real `owner` and
`owner->opponent` fields (including named Fighter/AliceFighter members) in
place of raw offset macros, while preserving all 575 outstanding differing
bytes in its nonexact ratchet and its first register discrepancy at
`004F344C`. The change also cold-replayed all 24 exact functions affected
by `CharacterObject.hpp`. Native-call helper aliases retain provisional ABI
spelling until the target call signatures have been fully reconciled. The Meiling parent also calls
`Fighter::SpawnBattleEffect` directly through `owner` at all 93 effect-spawn
sites; its 34,434-byte frontier remains 985 differing bytes with 135 GPR
and six instruction-width mismatches in the late state machine. All 24
header-affected exact units cold-replayed.

Youmu object `00536400` now defines `YoumuObject::Advance` with its
16-byte recorded-action history entries read from the typed owner list. 108 effect spawns, eight shared sounds, eight owner sounds, two
auxiliary and two tracked effect calls use the real Fighter APIs. The
seven gauge-timer calls to 0046D000 retain a provisional receiver ABI
pending cross-character ownership proof. Both complete 40,464-byte
COFF bodies preserve all 938 relocation offsets/types and every
nonrelocation byte. The original 39,999 CODE bytes remain NONEXACT
(913 GPR-role, ten width differences); 24/24 header-affected exact
units replayed successfully.

The Youmu fighter's R049 auxiliary writer and R243 object-history reader
now share `YoumuFighter::historyQueue`, an actual final C++ member at +0xFEC.
The source uses the 12-byte VC7.1 `std::list<ObservedInputSnapshotF378>`
layout and its 16-byte record; the independently observed Youmu allocation
ends at +0xFF8. The constructor's automatic member construction calls the
original 00531C00, and `ResetRound` calls the standard list `clear` at
00531CE0 without a synthetic subcomponent or raw offset cast. The snapshot
writer and object giant use direct member access. The complete constructor,
reset, writer and all header-dependent exact units cold-replayed 81/81.
The 40,464-byte object COFF, its 938 relocation positions/types/addends/
destinations and all code bytes remain identical. The 39,999-byte object
giant remains NONEXACT at 913 GPR / ten widths; actual source names and
unobserved list-node details remain provisional.

Three more complete object bosses now use direct declared member types in
place of redundant reference reinterpretations: Youmu and Yuyuko assign the
signed-char `facing` member directly from `owner->facing` (one and two sites),
and Suika writes zero directly to the declared unsigned-short `owner->fieldF06`.
Their full 40,464 / 44,331 / 43,972-byte COFF bodies remain byte-identical,
with all 938 / 1,043 / 991 relocation positions/types unchanged. The native
frontiers remain nonexact at 913/10, 914/6 and 935/1 GPR/width differences;
no giant exactness is claimed.

Suika object `005C9CC0` now defines `SuikaObject::Advance` on the
real CharacterObject hierarchy, with 64 effect spawns, 13 sounds,
three shared sounds and five camera shakes using the verified native
Fighter/EffectServices contracts. The two complete 43,972-byte COFF
objects have all 991 relocation positions/types and every nonrelocation
byte unchanged. The native 43,501 CODE bytes remain nonexact (935 GPR
roles, one width); 24/24 header-affected exact units replayed.

Yukari object `005A1600` is now the native `YukariObject::Advance`
class member, with 52 effect spawns, 16 sounds, two auxiliary effects
and three camera shakes expressed via `Fighter` and existing verified
camera interfaces. The complete 44,104-byte COFF object has all 943
relocation positions/types unchanged and zero nonrelocation-byte
regressions. Its original 43,599 CODE bytes remain nonexact (613 GPR,
11 width differences), and all 24 header-affected exact units replayed.

Nine complete object giant `Advance` parents now inherit the same
`CharacterObject::PlaySharedSound(short)` method instead of duplicating
a speculative sound declaration in each character class: Sakuya 2,
Alice 2, Patchouli 2, Youmu 4, Remilia 2, Yuyuko 2, Yukari 2, Suika 2,
Meiling 2 (20 actual compiled COFF call relocations). All nine full VC7.1
object sizes, relocation locations/types and nonrelocation bytes are
identical to their pre-refactor outputs, and all nine native frontiers
remain nonexact without regression. The 28 exact units affected by the
shared `CharacterObject` header replayed 28/28; no giant exact credit.

The native 0045B860 sound-bank forwarding method has also moved from
a fake `EffectSound45B860` receiver into the common
`CharacterObject::PlaySharedSound(short)` class. Its complete 29-byte
body and two game-owned relocations remain cold exact, with 28/28
header-affected exact units replayed. The object giant callers will
next shed their duplicate per-character sound declarations.

The original 0045B850 shared, parameter-discarding no-op was also
recovered as a real 13-byte `CharacterObject` member with a genuine
VC7.1 thiscall `RET 4`: original PE direct calls are observed in Yuyuko
(3), Yukari (4) and Suika (4) object giant Advances. The complete
three giant COFF outputs keep all original relocation positions/types
and nonrelocation bytes; the independently complete 13-byte leaf
cold-replays exact and adds one conservative exact unit. This is a
native function, not ASM, a filler stub or a claim of original naming.

Yuyuko fighter `00564BE0` has a natural-C++ partial `Advance` parent in
`probes/YuyukoFighterAdvancePartial.cpp`. Its 62,043-byte VC7.1 body now also
covers the common horizontal-recovery groups `0x8F..0x90`, `0x96..0x98`,
`0x9A..0x9E`, `0x9F..0xA1`, `0xA3..0xA5`, `0xA7..0xA8`, and `0xB4..0xB5`.
The source keeps the individual initial velocities, gauge accumulation,
landing transitions, timer/effect side effects and action-specific counter
resets. The missing direct boundary handlers `0x12C`, `0x186` and `0x1F4` are
now explicit C++ bodies, preserving their motion decay, launch/effect, timer,
sound and counter transitions. Direct boundary `0x2BC` is already present as
decimal `case 700`, including the 48-effect burst. The dispatch comparisons now
include the original singleton boundaries; eight affected shared leaf units
replay 8/8 exact. Action `0x19E` now includes the previously missing stage-3 five-angle,
three-layer barrage (`0x320..0x322`), its 300-frame timer/sound, velocity capture
and restoration; seven affected leaf units replay exact. Actions `0x60` and `0x61` now have separate natural-C++ handlers with
their original input-test grouping, effect burst, landing transition and
velocity follow-up. Actions `0x8F` and `0x90` also retain separate handlers
for their original horizontal-recovery state machines. The gauge-drift groups
`0x96..0x98`, `0x9F..0xA1`, and `0x9A..0x9C` are likewise split into separate
per-action handlers, retaining their individual velocities and counter targets.
The `0xA3..0xA5`, `0xA7..0xA8`, and `0xB4..0xB5` movement actions now also
retain separate C++ bodies for their distinct launch velocities and reset paths.
Actions `0x252`, `0x253`, and `0x254` are separate as well; the spirit-recovery
gate is restricted to `0x252/0x253` as in the target control flow. Effect
actions `0x259`, `0x25A`, `0x25F`, `0x260`, `0x261`, and `0x262` now retain
separate per-action handlers, including the original `0x25A` sound/gauge order.
Low actions `1` and `3` also have separate handlers for their distinct
primary-counter destinations. The `0x91` impact recovery, `200`, `0xC9..0xD0` command-driven movement and
rebound actions, and action `400`'s repeated five-effect barrage are represented. Action 0x91's two 0x006406AC calls are __ftol2 float-to-short conversions
of the projected velocity components; the unsupported extra PlaySharedSound
call has been removed, and the shared-sound inventory now matches the target.
All 125 original switch case labels across the seven ranges have explicit
natural-C++ handlers, along with six singleton boundaries (0x32, 0x8C,
0x12C, 0x186, 0x1F4, 0x2BC): 131 distinct action values total. The
single flat source switch naturally compiles into the target's seven-range
dispatch tree. The `0x303` fan has three independent countdown branches with paired
20-shot loops and now reuses three loop-counter locals in the original
`local_80`/`local_84`/`local_88` pairs. The `0x2F9` fan contains only the original
repeat-level `0x38C` radial and `0x38D` random-position bursts; the misplaced
`0x394..0x396` fan volley and countdown reset were removed from `0x2F9` because
they are exclusively part of `0x303`. All ten random samples in the remaining
`0x2F9` pattern call the exact `Actor::RecordedRange` leaf at `0x00455580`.
The 139-byte random-range leaf cold-replays exact. Removing the misplaced
0x303 volley reduced the VC7.1 body from 63,161 to 62,416 bytes, direct
non-relocation differences from 53,477 to 52,265, and the stack frame from
0x348 to 0x31C. Restoring all 27 field490 products to the target's
double-precision fmul QWORD [0x6583E8] instead of narrowing the constant to
float reduced the body to 62,254 bytes and direct differences to 51,620, with
a 0x2B0 frame. Restoring action 0x192's missing effect-800 X offset,
separating action 0x2E4's stage-7/stage-8 emissions, and normalizing all
signed-facing offsets brought the body to 62,271 bytes (+399), 51,948 direct
differences and a 0x2B8 frame. The latest shared-scratch source reduced that to 62,060 bytes (+188),
51,937 direct differences and a 0x224 frame. Removing the unsupported action-0x91
shared-sound call reduced the current body again to 62,043 bytes (+171), with
51,920 direct differences and the same 0x224 frame. Fifteen targeted related leaf units replay 15/15 exact, and the five
animation/reset/motion/camera leaves
directly affected by the 0x91 correction replay 5/5 exact. An explicit nested
seven-switch rewrite was tested and rejected: 62,204 bytes, 52,560 direct
differences and a 0x240 frame. The flat switch already lowers into the
target's seven-range dispatch tree. The parent remains partial with unresolved
common/default control flow and code-generation differences, not an exact
function.
This is a partial reconstruction, not a whole-function exactness claim.

For Yuyuko fighter actions `0`, `2`, `0x5D`, and `0x5E`, Ghidra prints the
stale `Concurrency::details::ContextBase::ClearCancel` label, but the original
PE call target is `0x00453E20`, the exact `Fighter::ClearMotionFields` leaf.
The current source call is correct; no separate cancel helper is implied.
A duplicated 5D/5E source-body experiment added 357 bytes without improving
the direct object comparison, so the compact shared C++ arm is retained.
The first Yuyuko object GPR mismatch at `0x00583489` remains a register
allocation difference at the stage-3 test. A later `0x838` branch group was
also found to have a source-order mismatch: the original tests `field080 == 0`
and the 611/612 exclusions before the owner-stage/action group. Reordering
the equivalent short-circuit terms to that original order restores the full
11,694-instruction control-flow shape through the function epilogue; the
remaining four-byte body-size delta and register allocation differences are
still under investigation. No whole-function exactness is claimed.

Yuyuko object `0057D580` now defines `YuyukoObject::Advance`, with
66 effect spawns, eight sounds and four camera-shake calls moved from
borrowed owner declarations to shared game interfaces. Both 44,331-byte
research bodies have exactly 1,043 relocation positions/types and zero
nonrelocation byte differences. At that earlier checkpoint, its 43,845
original CODE bytes remained nonexact (914 GPR-role differences and six widths); all 24 affected
exact units cold-replayed. Other parents retain their historical names.


Alice's 33,293-byte parent and its exact 855-byte projectile-behavior
leaf now pass genuine `float` values into the shared
`AngleAt00483300(float,float)` math helper, replacing their two distinct
raw integer-bit call signatures. Both complete COFF functions retain
all body bytes outside relocation fields and all 682/22 original
relocation positions/types. Targeted cold replay of the 855-byte leaf
and the separately exact 13-byte CharacterObject hook passed 2/2;
Alice's full parent still has 133 unresolved GPR-role differences.
Twelve further natural-C++ trials at the first discrepancy `004F344C`
(changes to fade lvalues, redundant float casts, scopes, labels and
condition spelling) yielded no improvement; two regressed native byte
or size matches, and all trial modifications were discarded.

Alice's seven `0x320`–`0x326` actions now call the real 855-byte
`AliceObject::AdvanceProjectileBehavior()` at `004F4170` rather than a
speculative reset method. This independently exact leaf includes two
real `Fighter::SpawnBattleEffect` calls instead of borrowed owner methods.
Original and revised leaf COFF contain identical 855-byte code bodies,
22 identical relocation positions/types and no nonrelocation changes.
The Alice 33,731-byte giant COFF likewise preserves all 682 relocation
locations/types and every nonrelocation byte while renaming its seven
real calls; 24/24 affected exact units cold-replayed. The giant's native
register-role debt remains unchanged and NONEXACT.

Alice's seven projectile action states (`0x320`–`0x326`) now call the
complete, separately exact 855-byte helper at `004F4170` as
`AliceObject::AdvanceProjectileBehavior()`. Its two native effect spawns
use `Fighter::SpawnBattleEffect`, eliminating the bogus projectile owner
receiver. Both entire COFF bodies (33,731 and 855 bytes) keep every
nonrelocation byte unchanged and all 682/22 relocation positions/types;
24/24 exact header-affected functions, including the leaf, cold-replayed.
The giant itself is still nonexact.

Nine object research giants now inherit the native recorded-random-range
method from `Actor`, rather than carrying their own duplicate declarations.
The nine complete COFF bodies — Alice, Patchouli, Youmu, Sakuya, Yuyuko,
Yukari, Suika, Remilia and Meiling — retain every relocation offset/type,
identical object sizes and zero nonrelocation-byte changes. Their complete
compiled code uses 414 calls to inherited `Actor::RecordedRange`. The
139-byte shared leaf remains cold-replay exact; 24 object-related and
105 selected Fighter/Actor-dependent exact units were replayed locally,
all passing. None of the nonexact giant frontiers were changed.

Four complete fighter giant parents now use `Actor::RecordedRange`
for another 169 actual compiled range calls: Reimu 29, Sakuya 97,
Youmu 16, Remilia 27. Their 62,090 / 83,922 / 47,655 / 59,236-byte
COFF bodies preserve every original relocation position/type and every
nonrelocation byte. The former character-specific range method aliases
were removed from their headers; all 132 affected exact units passed
local cold replay in three groups of 44/44. Native giant GPR/width
debt remains nonexact.

A second typed-coordinate migration restored the 00453A70 mixed X-bit /
Y-float projectile variant: 81 source-level calls now pass the actual
`float x` / `opponent->x` directly to `Fighter::SpawnBattleEffect` rather
than transporting them through fake integer-reference signatures.
The four complete fighter parent COFF bodies retain their original
62,090 / 83,922 / 47,655 / 59,236-byte lengths, all relocation positions
and types and every nonrelocation code byte. There are 92 actual renamed
native spawn relocations (Reimu 15, Sakuya 59, Youmu 10, Remilia 8).
All 132 header-affected exact units replayed locally in three groups of
44; native fighter giant exactness is not claimed.

Across four complete fighter giant parents, the `00453A70`
integer-bit projectile-position aliases now become 62 natural C++
`Fighter::SpawnBattleEffect(effect, x, y, ...)` calls across 39 original
case/parent files (Reimu 13, Sakuya 10, Youmu 26 and Remilia 21 actual
COFF call relocations, 70 total). `x` and `y` are genuine float fields,
with native zero written `0.0f` instead of integer-bit masquerading.
All full VC7.1 COFF bodies retain their 62,090 / 83,922 / 47,655 /
59,236-byte extents, original relocation offsets/types and every
nonrelocation byte. Header-affected exact cold replay passed 132/132
in three bounded 44-unit groups. Native giant exactness is not claimed.

The remaining 00453A70 float-X/raw-Y call aliases are now gone from
Reimu, Youmu and Remilia. Nineteen native COFF call relocations now name
the exact inherited Fighter::SpawnBattleEffect(short,float,float,
signed char,signed char) API; raw y and opponent->y bit references
become actual float fields, while Remilia's 0x41F00000 / 0xC1F00000 /
0x42480000 / 0xC2480000 values are expressed as +30.0f / -30.0f /
+50.0f / -50.0f. All three complete COFF bodies and all relocation
positions/types remain unchanged outside the renamed symbols. The
127 affected exact units replayed 127/127 in three bounded groups.

Three more fighter giants now inherit the exact shared 00453B50/00453C80
effect APIs: Reimu routes 29 native call relocations, Sakuya 25 and
Youmu 66 through Fighter::SpawnTrackedEffect / Fighter::SpawnAuxEffect.
Their original per-character ABI aliases are removed, and raw/mixed
integer-reference coordinate arguments become genuine float fields.
All three complete COFF bodies retain their original 62,090 / 83,922 /
47,655-byte extents, all 1,824 / 2,352 / 1,491 relocation positions and
types, and every nonrelocation byte. The 127 exact units affected by
the three shared fighter headers cold-replayed 127/127 in bounded
43/42/42 groups. All three giant frontiers remain explicitly nonexact.

Remilia's full 58 KB fighter giant now routes all 49 00453B50/00453C80
calls through the real inherited `Fighter::SpawnTrackedEffect` (3) and
`Fighter::SpawnAuxEffect` (46). Sixteen original case-fragment files and
the parent source now use float coordinates, not integer-reference
bit transport; four speculative per-character helper declarations were
removed. The full 59,236-byte COFF retains all 1,863 relocation
positions/types and every nonrelocation byte; all 98 exact units
impacted by the Remilia fighter header cold-replayed 98/98 in bounded
36/31/31 groups. The 58 KB giant remains nonexact.

The Reimu, Sakuya and Youmu fighter giants now also use their actual
inherited `Fighter::SpawnTrackedEffect(short,float,float,...)` and
`Fighter::SpawnAuxEffect(short,float,float,...)` interfaces in place of
94 source-level per-character 00453B50/00453C80 aliases across 57
case-fragment files. This yields 120 native call relocations in the
three full COFF parents (29 Reimu, 25 Sakuya, 66 Youmu); all three
retain their original 62,090 / 83,922 / 47,655-byte section extents,
relocation positions/types and every nonrelocation byte. 127 header-
affected exact units cold-replayed 127/127 in bounded 43/42/42 groups.
All three large fighter frontiers remain nonexact.

Four native fighter parents now use the same inherited 00455580
`Actor::RecordedRange(int,int)` rather than per-character range aliases:
Reimu 29, Sakuya 97, Youmu 16 and Remilia 27 (169 native COFF call
relocation names). All four whole parent objects retain their previous
62,090 / 83,922 / 47,655 / 59,236-byte extents, their 1,824 / 2,352 /
1,491 / 1,863 relocation positions/types and every nonrelocation byte.
All 132 exact units affected by the four fighter headers cold-replayed
in three bounded groups of 44/44. The giant native frontiers remain
nonexact and are not credited as new matched functions.

Eight native object giant parents now invoke the inherited
`Actor::RecordedRange` instead of eight per-character speculative method
symbols: Sakuya 75, Alice 15, Youmu 49, Remilia 24, Yuyuko 67,
Yukari 17, Suika 73 and Meiling 57 (377 full COFF call relocations).
All eight original complete function object sizes and each relocation
offset/type are identical before and after the change; every
nonrelocation code byte is unchanged. The eight nonexact native
frontiers are not claimed exact. All 25 header-affected existing exact
functions, including the 13-byte CharacterObject no-op and 855-byte
Alice projectile helper, cold replayed exactly.

The independently exact native recorded-range policy at 00455580 is
now a common `Actor::RecordedRange(int,int)` method instead of an
artificial standalone receiver. Its complete 139-byte COFF shape, all
11 relocation targets and signed replay/record sampling behaviour
cold-replay exact. This is an inferred native shared calling contract;
the eight object giant source call sites will adopt it in a later
verified step, without recrediting the existing leaf.

The Alice action source also removes four more integer-reference casts
around known float members: fighter `field318/field31C`, object `x/y`,
including a native zero assignment. They are now direct float-to-float
C++ assignments; the full 33,731-byte COFF, all 682 relocation offsets/
types and every nonrelocation byte remain unchanged.

Alice's 33 KB source now also uses real float assignments for all
32 zeroed rotation components and both float-to-float velocity copies,
not `reinterpret_cast<int&>` bit-punning. The complete VC7.1 COFF remains
33,731 bytes with all 682 relocation positions/types and zero
nonrelocation-byte differences. This is a source-semantic cleanup only;
the 133-position GPR debt remains and the giant is still nonexact.

Alice's complete object `Advance` now also passes its native signed-char
`facing` member directly to the declared
`Fighter::SpawnBattleEffect(short,float,float,signed char,signed char)`
interface at all nine effect sites. The previous unsigned-char reference
reinterpretations were redundant type punning: `Actor::facing` is already a
`signed char`. The full 33,731-byte VC7.1 COFF retains all 682 relocation
positions/types and every nonrelocation byte (0 differences); the
33,293-byte giant frontier remains NONEXACT with 133 GPR-role differences.

Alice's hit-confirm path also increments the opponent's declared signed-char
`Fighter::field366` directly. Its old `reinterpret_cast<unsigned char&>`
was unnecessary: the branch first bounds the value below two, and the
natural signed-char increment produces the same complete object code.
The 33,731-byte COFF still has all 682 relocation positions/types and zero
nonrelocation-byte differences; the 33,293-byte boss remains NONEXACT.

Alice's 33 KB `Advance` now also uses direct C++ lvalues in place of 118
redundant address-of/dereference identity expressions (`*(&member)`). The
recovery covers repeated Y/velocity updates, X/Y projectile motion, owner and
opponent coordinates, animation-distance fields and global float constants.
Each expression family was compiled independently before combining them;
the final natural source compiles to the identical 33,731-byte COFF body,
all 682 relocation positions/types and zero changed bytes. The two remaining
`field0CC` and `field0D0` identity pairs were tested separately and together
before inclusion. This is source-semantic/readability progress only: the
33,293-byte giant still has 133 GPR-role mismatches, first at `0x004F344C`.
The separate-if form was retained; nested else/else-if, goto, switch, stage
aliases and register-local trials did not improve the native join.

Alice object also recovers the actual `0040FB70` polar-velocity ABI
and shared range/sound calls: 19 `Actor::SetPolarVelocity` (including
three previously encoded as raw `int` float-bit transports), 15
`AliceObject::RecordedRange`, and two `AliceObject::PlaySharedSound`
call relocations. The complete 33,731-byte COFF and all 682 relocation
positions/types were preserved with zero nonrelocation differences.
The original 33,293-byte native frontier remains NONEXACT (133 GPR
mismatches, zero width mismatches); 24 impacted exact units cold replayed.

Alice object `004EBDA0` Alice action 0x38D terminal fade now expresses its switch-tail exit as
an early return rather than a break that exits the function's only
switch. The source explicitly clears the final color channel and frame
before returning; this is semantically equivalent to the original
switch-tail break and emits exactly the same 33,731-byte COFF body,
682 relocation offsets/types and zero nonrelocation-byte differences.
It does not reduce the remaining 133 GPR mismatches or claim exactness.

now also dispatches through truthful inherited
Actor/CharacterObject C++ calls rather than speculative `AliceObject` helper
names: 93 `ClearFrameInfo`, 66 `ResetSecondaryCounter`, 56
`AdvanceNestedFrame`, 52 `ResetTransform` and seven
`ResetPrimaryCounters` call relocations (274 total). Full 33,731-byte
COFF output preserves all 682 original relocation positions/types with
zero nonrelocation-byte differences. Its 33,293-byte native frontier is
unchanged (133 GPR-role, no width mismatches), and the 24 exact units
depending on `CharacterObject.hpp` cold-replayed successfully.

At Yuyuko's first register-role discrepancy (`00583489`, case 837), the
native path returning from `AdvanceNestedFrame`/`ClearFrameInfo` joins the
next animation-stage test with the scratch-register rotation one position
ahead of the VC7.1 parent. Ten natural-C++ variations were cold-compiled:
braces, swapped comparison, double negation, qualified calls, explicit
`this`, nested stage tests, swapped constants, grouped conditions,
postincrement and assignment-form increment. None improved the whole
function without regressions. The swapped comparison added a byte to the
object and 788 new differing positions; assignment-form increment
shortened it a byte but introduced 838 newly differing positions. Neither
is a valid improvement. Preserve case 837 and investigate how this join's
register state was selected in the original compile.

The shared 00453E20 motion clear is now the exact `Fighter::ClearMotionFields`
leaf (51 native CODE bytes, using `velocityX`, `velocityY`, `field058`
and `field05C`). Across Reimu/Sakuya/Youmu/Remilia fighter research
parents, 410 source-level `ResetAt453E20` aliases became this inherited
natural member call, covering 494 authentic compiled call relocations
(105, 139, 115 and 135 respectively). All four pre/post COFF objects
retain their original 62,090/83,922/47,655/59,236-byte sizes, their
1,824/2,352/1,491/1,863 relocation offsets and types, and every
nonrelocation byte. The four whole-function giant frontiers are still
nonexact, with zero newly regressed bytes. Only the 132 directly
header-affected exact units were cold-replayed (44/44 in each of three
groups), all exact. No ASM, padding, fake locals or giant exact credit.

The native Actor action-reset helper `0040FAC0` is now called by its
real inherited `Actor::ResetPrimaryCounters(short)` name across the
four complete fighter giants: 511 source calls in 256 state/parent files
expand to 705 native COFF calls (169 Reimu, 177 Sakuya, 181 Youmu,
178 Remilia). Each full research COFF object retained its exact size,
all relocation offsets/types and every nonrelocation byte; all
132 header-affected exact units passed affected-only cold replay in
three groups of 44. This is a type/ownership and natural source
recovery, not additional giant exact coverage.

The native 00453A70 ordinary effect constructor is now invoked as
`Fighter::SpawnBattleEffect(short,float,float,signed char,signed char)`
throughout the Reimu, Youmu, and Remilia fighter giants as well as Sakuya.
Reimu's raw `int`-signature float argument alias rewrites preserve the
real IEEE-754 float data directly; whole-function COFF audits verified
133 Reimu, 20 Youmu and 69 Remilia compiled native spawns (222 total)
renamed to the shared API. All body sizes, relocation offsets/types and
nonrelocation bytes remained unchanged. All 127 currently header-affected
exact units passed targeted cold replay in 43/42/42-unit groups; the
nonexact giant frontiers remain unchanged.

A further float-ABI recovery in Sakuya and Remilia fighter parents
changed 12 compiled call sites to the true inherited
`Actor::SetPolarVelocity(float,float)` at 0040FB70. Ten Sakuya sites had
previously used `reinterpret_cast<int&>(field314)` to pass a float's
raw bits through a fake integer signature; using the natural float member
produced the same VC7.1 output. The full 83,922-byte Sakuya and
59,236-byte Remilia COFF bodies preserved all 2,352 and 1,863
relocation offsets/types with zero nonrelocation-byte differences.
All 104 affected exact units cold-replayed in three groups (36/34/34).
These remain nonexact giant research parents.

The common actor transform endpoints have also been recovered within
the four fighter giants: native `0040FBB0` is now the inherited
`Actor::ResetTransform(float,float,float)` with correct floating-point
arguments, and `0040FC50` is `Actor::ClearTransformFlag()`.
The rewritten state fragments account for 45 native call relocation
renames in aggregate, with all four complete VC7.1 object sizes,
relocation offsets/types and nonrelocation bytes unchanged from the
pre-migration parents. All 132 header-affected exact units passed local
cold replay in three 44-unit groups. Giant exactness remains unresolved.

The shared Actor animation-stage reset `0040FB40` now appears as
`Actor::ResetSecondaryCounter(short)` throughout four complete fighter
state machines, replacing 351 textual `SetAuxActionAt40FB40` aliases.
Their whole VC7.1 COFF bodies preserve all original sizes, relocation
offsets/types and nonrelocation bytes; 462 compiled reset-call relocation
symbols now point to the inherited Actor method (113 Reimu, 137 Sakuya,
68 Youmu, 144 Remilia). All 132 source-header-affected exact units
cold-replayed in three groups (44/44 each); no giant exact credit is
claimed.

The shared Actor action reset `0040FAC0` is now called as the real
inherited `Actor::ResetPrimaryCounters(short)` in four complete fighter
state machines. 511 textual `SetNativeActionAt40FAC0` aliases across
256 parent/case files correspond to 705 actual COFF relocations (169 Reimu,
177 Sakuya, 181 Youmu, 178 Remilia). For every full parent, VC7.1 COFF
body size, relocation positions/types and every nonrelocation code byte
are unchanged against the immediate pre-migration state. All 132 affected
exact units cold-replayed in three 44-unit groups. The giants remain
nonexact against the PE; no exact credit is claimed.

The shared Actor helper `0040FA30`, which advances an animation frame,
is now called as inherited `Actor::AdvanceNestedFrame()` rather than the
misleading `GetNativeActionAt40FA30` in all four fighter research giants.
382 textual alias calls across 252 source files become 552 actual COFF call
relocations (135 Reimu, 143 Sakuya, 135 Youmu, 139 Remilia). Pre/post
whole-function COFF sizes, relocation offsets/types and nonrelocation
bytes are unchanged. All 132 header-affected exact units cold replayed
in three affected-only groups (44/44 each). The giant parents remain
NONEXACT against original PE bytes.

The 00453D60 shared sound endpoint is likewise now the natural
`Fighter::PlaySharedSound(short)` inherited method: 147 textual aliases
across 93 source files became 192 native calls (55 Reimu, 45 Sakuya,
50 Youmu, 42 Remilia). Whole function pre/post COFF sizes and all
relocation offsets/types were unchanged, with zero nonrelocation
byte differences. All 132 affected exact units cold-replayed 44/44
in each of three targeted groups. Research giants remain nonexact.

The native 00453D40 per-fighter sound endpoint is also now called by its
real `Fighter::PlaySound(short)` name in all four complete fighter research
parents. This changes 199 textual call sites (257 compiled COFF relocations:
77 Reimu, 80 Sakuya, 42 Youmu, 58 Remilia). Before/after whole-object
compilation preserved respectively 62,090 / 83,922 / 47,655 / 59,236 bytes,
all 1,824 / 2,352 / 1,491 / 1,863 relocation positions/types and every
nonrelocation byte. The 132 header-affected exact units were cold-replayed
44/44 + 44/44 + 44/44. The giant parents themselves remain NONEXACT.

A later four-fighter migration replaced 410 text occurrences of the
misleading `ResetAt453E20` alias with the real inherited
`Fighter::ClearMotionFields`. These case fragments expand to 494 native
COFF call relocations across Reimu (105), Sakuya (139), Youmu (115),
and Remilia (135). All four full research object sizes stayed at
62,090 / 83,922 / 47,655 / 59,236 bytes, their 1,824 / 2,352 /
1,491 / 1,863 relocation offsets/types unchanged, and nonrelocation
code bytes identical. All 132 header-affected exact units cold replayed
in three local groups of 44/44, not full replay. This is meaningful
natural C++ call recovery; the giant parents remain NONEXACT.

The 0046D000 shared gauge-timer caller cleanup is also complete in the
four full fighter research parents: 52 Reimu, 44 Sakuya, 14 Youmu, and
28 Remilia compiled call sites (138 total) now use the inherited natural
`Fighter::UpdateGaugeTimer` member rather than the misleading
`StartAnimationAt46D000` alias. For each complete fighter COFF object,
pre/post output length, every relocation offset/type and all
nonrelocation bytes are identical (respectively 62,090/1,824,
83,922/2,352, 47,655/1,491, and 59,236/1,863 bytes/relocations).
All four whole-function native frontiers remained nonregressing, with no
new exact giant credit. This preserves the original 0046D000 shared
implementation and removes fake per-character helper declarations.

The previously borrowed `0046D000` cross-character gauge-timer call
is now the common `Fighter::UpdateGaugeTimer`. Youmu/Patchouli/Remilia
object research parents use the real owner method; the shared 126-byte
callee itself remains cold-replay exact and all touched giant frontiers
are unchanged. This is source/interface recovery, not giant exact credit.

## Without a complete parent

Objects 00476A40 (Reimu, 50,915 B) and 0049C8F0 (Marisa, 46,596 B); fighters
00486550 (Marisa, 50,735 B), 004D7E70 (Alice, 43,601 B), 004F7130
(Patchouli, 44,211 B), 00564BE0 (Yuyuko, 61,872 B), 0058AF60 (Yukari,
49,230 B), 005AEEC0 (Suika, 71,616 B) and 005D73C0 (Meiling, 43,282 B).
`config/fighter-boss-dispatch-fingerprints.json` has their extents and jump
tables. Each fighter shares its switch grammar with the others, so a new
parent starts from the closest complete one plus the native case bodies.

Yuyuko fighter `00564BE0` now has a 62,043-byte natural-C++ partial parent in
`probes/YuyukoFighterAdvancePartial.cpp`. It covers the low movement actions,
the observed `0x32..0x41` horizontal-drift cases, `0x46..0x4A` bounce/landing
states, `0x4C`, `0x58..0x59`, `0x5D..0x63` recovery/input follow-ups, selected
`0x12D..0x136` special-move phases, `0x187..0x18B`, `0x191..0x192`, `0x194`,
`0x196..0x198`, `0x19A`, `0x19C`, `0x19E`, `0x1A0` repeated resource/effect bursts,
action `700`'s 48-effect stage burst, knockout/continue transitions
`0x1F5` and `0x252..0x256`, resource/impact states `599..600`,
`0x259..0x25A`, `0x25F..0x265`, and `0x2BD..0x2C3` radial/impact
patterns, difficulty-scaled `0x2DA` radial phases, manual-motion state `0x2DB`,
`0x2E4` multi-phase effects, difficulty-scaled `0x2EE..0x2EF`, `0x2F8`
recovery and the randomized polar/radial fan `0x2F9`, `0x302..0x303`,
`0x31B..0x31C`, `0x8F..0x90`, `0x91`, `0x96..0x98`, `0x9A..0x9E`,
`0x9F..0xA1`, `0xA3..0xA5`, `0xA7..0xA8`, `0xB4..0xB5`, `200`,
`0xC9..0xD0`, `400`, and `0x8C`; the original function is 61,872 bytes.
All 125 original switch labels plus six singleton boundaries have natural-C++
handlers (131 distinct action values); common/default flow and code-generation
differences remain. Action 0x91 now preserves both __ftol2 velocity conversions
and no longer emits the unsupported shared sound. The current VC7.1 body is
62,043 bytes versus the 61,872-byte target (+171), with 51,920 direct
non-relocation byte differences and a 0x224 stack frame; this is an active
partial reconstruction, not whole-function exactness. The
13 exact Yuyuko translation units affected by its `YuyukoFighter.hpp` slot
declaration cold-replay 13/13 exact.

## Why the register debt exists

At `/Od` VC7.1 reloads `this` for every member access and rotates the
scratch register eax → ecx → edx → eax from one load to the next. The
rotation carries across statements and through ordinary joins. Each giant's
debt is this rotation shifted by one or two steps from a single point
onwards, so one cause explains thousands of positions.

The shift starts at a join where the original takes the register state of
the **first** conditional jump into it instead of the fall-through state
(`.analysis/layout-tools/anomalies.py` lists such joins in an original).
Two shapes occur at the first-debt points:

- `if (animationStage < 3) { scaleX = … + g; scaleY = … + g; }` followed by
  `if (animationStage == 4)` (Alice 004F344C, Yuyuko 00586A25);
- `if (animationStage == 0 && animationFrame == 0) { …colours = 255…;
  velocityX = 0; velocityY = 0; }` followed by `if (animationStage == 1)`
  (Remilia object 0055F711, Suika 005D2558, Remilia fighter 0054F906).

The same shapes appear many times in every giant and behave normally
elsewhere (Remilia's object has nine such velocity-reset joins and only one
is anomalous). None of our builds produces such a join. These did not
change the state and are ruled out:

- spelling: `else`, extra braces, `goto`, `do {} while (0)`, comma
  expressions, inverted tests, nesting `if (A) { if (B) … }` instead of
  `A && B`, a one-pass `while`/`for` with `break`, line breaks, and placing
  the code inside a `switch` case;
- flags: `/Z7`, `/RTC1`, `/Oy-` and `/GX`. `/ZI` restarts the rotation at
  every statement but changes thousands of other instructions;
- compiling two giants in one translation unit;
- the join is never a jump-table target, and no shared instruction, label,
  call or `this`-reload count marks the anomalous positions.

Meiling object `005EB520`: 22 additional natural-C++ variants at the
`997`/`998` boundary at `005F3904` (condition polarity, guard/else,
scope, comparison order and facing assignment forms) did not reduce
whole-function differences. A plain `facing = owner->facing` produces
identical native bytes and is retained as the more natural C++ source.
A separate whole-function source cleanup removes four redundant
`static_cast<double>(0.02f)` promotions and two explicit `static_cast<short>`
wrappers around float-to-short assignments. The 34,879-byte COFF body remains
byte-identical; all 806 relocation positions/types/addends/local target
offsets remain identical (only compiler-generated local label names rotate).
The giant frontier is unchanged at 985 differing bytes, 135 GPR positions,
six width deltas and first divergence `005F3904`. The `float` cast before
`owner->field3A0 / field0D8` remains necessary to avoid integer division.
Youmu object `00536400` also drops 13 redundant `static_cast<short>`
wrappers around float expressions, angle results and float-to-short member
assignments. The complete 40,464-byte COFF body and all 938 relocation
positions/types/addends/local targets remain identical. Its giant frontier
is unchanged at 913 GPR positions, ten width differences and first
`005392F8`; no exact giant credit is claimed.

Per-parent attempts that failed, kept so they are not repeated: loop-update,
return, condition and index rewrites in 005A1600; swapping 0057D580's
state-837 equality operands (reads the limit before the frame-progress call,
1,122 GPR); compound-update, bound, `/G7`, comma and indexed-expression
variants in 004CA6E0; chaining, DWORD/array/member/guard and `/Op` variants
in 0055AC80; typed float arguments in 0050A580 (raw DWORD transport of
coordinates and angles is required; typed arguments add 329 instructions).
The deleted per-checkpoint notes with full details remain in Git:
`git show 430a06a4:docs/<NOTE>.md` (list them with
`git ls-tree --name-only 430a06a4 docs/`).

Seven further natural-C++ source experiments at the Alice object join at
`004F344C` (inverse comparison, operand swap, compound assignment, empty
`else`, inverse `else`, explicit boolean, and conditional expression) did
not improve the native byte frontier. The inverse `else`, compound
assignment, and explicit boolean forms introduced new width/instruction
debt. The remaining lead is a construct that makes the join take the
first-jump register state without changing its other instructions.

The common Fighter +0xEFA field is now correctly declared short, not
unsigned short: five object giants and the exact 855-byte character
projectile leaf were all using signed 16-bit comparisons/increments.
Their 99 speculative reinterpret_cast<short&> accesses are now direct
typed member operations. Sakuya, Youmu, Remilia, Yuyuko and Yukari
complete COFF bodies (42,937 / 40,464 / 28,868 / 44,331 / 44,104 bytes)
retain all 929 / 938 / 696 / 1,043 / 943 relocation positions/types
and every nonrelocation byte. The exact projectile leaf remains
byte-for-byte matching. All 450 header-affected exact units cold-replayed
450/450 in 13 bounded batches; no giant exactness is claimed.

Sakuya's 42.5 KB object boss now uses ordinary C++ float copies for 31 same-type transfers among x/y, scale, rotation and Fighter field314. The full 42,937-byte COFF remains identical, all 929 relocation positions/types are unchanged, and there are zero nonrelocation-byte differences. The giant remains nonexact.

Four more object giants now use their declared native C++ scalar types
instead of integer-reference disguises: Sakuya, Youmu and Yukari replace
97 same-type float copies (1/36/60), while Remilia replaces 93 unsigned
references to Actor::field07C with direct signed int state access. All
four complete COFF bodies (42,937 / 40,464 / 44,104 / 28,868 bytes), all
929 / 938 / 943 / 696 relocation positions/types and every nonrelocation
byte remain unchanged. All four frontiers remain explicitly nonexact.

SuikaObject::Advance also replaces 22 unsigned-int-reference aliases between declared float fields (scale, owner/opponent coordinates, velocity and fighter transform angle) with direct float assignments. The complete 43,972-byte COFF, all 991 relocation positions/types and every nonrelocation byte remain unchanged; the boss stays nonexact.
A further whole-function pass removes 18 redundant `static_cast<short>`
wrappers from Suika's short-member assignments, including angle results and
float/coordinate truncations. The full 43,972-byte COFF body and all 991
relocation positions/types/addends/local targets remain identical. Its
frontier stays at 935 GPR positions, one width difference and first
`005D2558`; no exact giant credit is claimed.
Yukari object `005A1600` removes six redundant `static_cast<short>` wrappers
from float-angle and coordinate assignments to short fields. The complete
44,104-byte COFF body and all 943 relocation positions/types/addends/local
targets remain identical. Its frontier remains 613 GPR positions, 11 width
differences and first `005A88A8`.
Yuyuko object `0057D580` removes two redundant `static_cast<short>` wrappers
around float-angle results assigned to `field0D8`. Its complete 44,331-byte
COFF body and all 1,043 relocation positions/types/addends/local targets
remain identical. Its frontier remains 914 GPR positions, six width
differences and first `00583489`.

Reimu fighter motion now uses the real float types for the reaction-velocity pair: FighterFrameInfo +0x2C/+0x30 and Actor +0x94/+0x98 are floats, not unsigned integer bit buckets. The 0x46 trajectory now performs ordinary float negation/addition, combat reaction scales the float fields directly, and Fighter initialization writes float zeroes. The full 62,090-byte Reimu fighter COFF remains identical with all 1,824 relocation offsets/types and zero nonrelocation-byte differences. All 462 exact units affected by the shared Actor header cold-replayed 462/462 in 16 bounded batches; the 855-byte projectile Advance remains exact.

YoumuObject's borrowed history record now types its +0x04/+0x08 position fields as floats (xAt04 / yAt08) and assigns them directly to the object's float coordinates. The complete 40,464-byte boss COFF, all 938 relocation offsets/types and every nonrelocation byte remain identical; the view is still non-owning and no exactness credit is claimed.

The signed Fighter::fieldEFA cleanup is now complete across the remaining large callers: Meiling, Suika and Alice object giants replace 87 reinterpret_cast<short&> uses, while Reimu and Remilia fighter fragments replace four opponent-field casts. These 91 sites now use direct short member access and increment. The five complete COFF bodies (34,879 / 43,972 / 33,731 / 62,090 / 59,236 bytes), all 806 / 991 / 682 / 1,824 / 1,863 relocation offsets/types, and every nonrelocation byte remain unchanged. No exact unit depends on these boss-only fragments; all five giant frontiers remain nonexact.
A second `fieldEFA` pass removes 61 more signed-short reference aliases from
29 shared boss-state fragments. The five complete consumers—Patchouli object
Advance plus Reimu, Sakuya, Youmu and Remilia fighter Advance—were rebuilt
against the pre-change sources: every COFF byte and every relocation
position/type/addend/local target remains identical. Their frontiers are
unchanged (Patchouli 24,643 differing bytes; Reimu 42,551; Sakuya 18,253;
Youmu 16,833; Remilia 40,569); none is promoted to exact.

`Fighter::fieldEFE` is now a signed `short`, matching the two complete Meiling
and Patchouli stage renderers' explicit signed-word timer operations. Removing
all six `reinterpret_cast<short&>` views preserves both complete 1,606-byte
COFF bodies and all 40 relocations in each. The 21 relevant initialization /
reset units plus the two renderers replayed 23/23 exact.


Sakuya object 004CA6E0 was revisited on 2026-11-19 at the 809/810 action
gate. Positive and negative OR predicates, grouped comparisons, nested
guards, switch breaks, explicit owner qualification, local register
aliases, and goto-based forms were measured against the whole parent.
The best transient form reduced GPR-role differences from 447 to 328,
but emitted a 42,939-byte section instead of the required 42,937 bytes
and failed the frontier size check. Other forms regressed or returned to
the original 447/12 result. Every experiment was discarded; the tracked
source remains at its committed 42,937-byte baseline. Do not repeat these
syntax-only variants without new target evidence.
A separate natural-C++ cleanup removes five redundant `static_cast<short>`
wrappers around `AngleAt00483300` float results assigned to short fields.
The complete 42,937-byte COFF body remains byte-identical and all 929
relocation positions/types/addends/local targets remain identical. The
Sakuya giant frontier remains 447 GPR positions and 12 width differences;
no boss exactness is claimed.

The shared angle leaf `AngleAt00483300` is now natural C++ and exact as a
21-byte authored game function. Sixteen independently authored caller
functions make 211 original direct calls to it, including Alice and Meiling
`Advance` parents. Its source calls the VC7.1 `atan2f` inline overload; the
37-byte worker at `00483320` is separately recorded as VC71CRT library code,
with its `_atan2` callee already independently classified. This closes the
small game wrapper without claiming the header worker or CRT math body as
game-authored bytes. The two other float math wrapper pairs remain under R163
review because their complete SDK/ordinary alternatives are still ambiguous.

## 2026-11-19 — Meiling state 997/998 register frontier

The detailed target/object instruction comparison for `MeilingObject::Advance`
(`0x005EB520`, state values 997/998) narrows the remaining mismatch to the
switch-state entry at `0x005F3904`:

- Through the two exits at `0x005F38FA` and `0x005F38FF`, the target and object
  use the same GPRs; the final `ResetSecondaryCounter` call loads `this` into
  `ECX` in both builds.
- At `0x005F3904`, the target begins the state-998 body with
  `mov eax, [ebp-4]`, while the object begins with `mov edx, [ebp-4]`.
  The source-level facing copy is already the direct natural assignment
  `facing = owner->facing`; changing its cast or owner alias is not the
  remaining explanation.
- The six instruction-width deltas later in state 998 are the x86 accumulator
  encoding consequence of that register rotation: the target uses the shorter
  `cmp eax, imm32` encoding where the object uses a non-`EAX` register, and in
  two comparisons the rotation is reversed (`ECX` versus `EAX`). They are not
  six independent source-width defects.
- A source-order swap of the independent `case 997` and `case 998` blocks was
  tested and rejected: VC7.1 emitted the blocks in the swapped order, losing
  the target's native layout. The existing direct-facing, owner-alias,
  typed-owner, case-997 polarity/else-shape, and state-998 return variants
  remain rejected; do not repeat them without a new hypothesis.

Keep this as a compiler/register-allocation frontier, not a reason to add
inline assembly, padding, or synthetic instructions. Continue with natural
C++ control-flow and object-model hypotheses only.

Three shared math leaves now have complete natural C++ game wrappers in
`src/MathFloatHelpers.cpp`: angle (`00483300`, 21 bytes), absolute value
(`00412D90`, 17 bytes), and magnitude (`00428D20`, 17 bytes). They are
called from 16/30/3 independently authored game functions respectively
(211/68/6 direct call sites). The angle's 37-byte `atan2f` worker is
separately classified VC71CRT library code; the `fabsf` and `sqrtf` workers
remain unknown under R163 and are not credited. The three wrappers have
focused exact native replay; this does not change the still-nonexact Alice
or Meiling giant frontiers.

Alice object `004EBDA0` removes 59 additional redundant numeric conversions
across its complete `Advance` state machine: signed facing/velocity products,
short-to-float call arguments and expressions already promoted by float
operands now use ordinary C++ conversions. The full 33,731-byte COFF body
remains byte-identical, all 682 relocation records remain identical, and the
frontier guard remains at 575 differing bytes / 133 GPR positions / zero
width differences. This is natural-source cleanup only; Alice's giant is
still NONEXACT and its first GPR divergence remains `0x004F344C`.

A second Alice object pass removes 34 more explicit `float` casts where the
surrounding float operand or float destination already performs the same
conversion: the eight float/double scale updates, direct `RecordedRange`
results, signed-facing products, and the short/char and short/float mixed
expressions. Each family was compiled alone before combining. Eight casts
around `RecordedRange(...) +/- integer` were deliberately retained: without
the cast the subtraction happens in integer arithmetic before assignment,
which changes the original COFF. The accepted natural source keeps the full
33,731-byte function body and all 682 relocation offsets/types/addends and
local destinations identical. The frontier remains 575 differing bytes,
133 GPR positions and zero width mismatches; no giant exactness is claimed.
A third Alice source pass removes 13 redundant `static_cast<short>`
wrappers around expressions assigned to short members, plus one redundant
float conversion on a double-multiplier result assigned to `scaleY`. The full
33,731-byte COFF body and all 682 relocation positions/types/addends/local
targets remain identical. The frontier stays at 575 differing bytes, 133 GPR
positions and zero width differences; the float conversions before integer
`RecordedRange` subtraction and before `owner->field3A0 / field0D8` remain
because they change arithmetic semantics.
A further Alice cleanup removes eight `static_cast<float>` wrappers around
`RecordedRange` integer results assigned to float members. The `0..4` range
minus two wrapper was tested separately and retained because its removal
changes code generation. With only the eight byte-neutral wrappers removed,
the complete 33,731-byte COFF body and all 682 relocation positions/types/
addends/local targets remain identical; the 575-byte / 133-GPR / zero-width
frontier remains unchanged.

Reimu fighter `0045DD70` removes two redundant `static_cast<short>` wrappers
around float projection results assigned to short script counters. The full
62,090-byte COFF body and all 1,824 relocation positions/types/addends/local
targets remain identical. The frontier remains 6,311 GPR positions and five
width differences; this is natural-source cleanup, not exact giant credit.

The shared Fighter script words at `+0xF00/+0xF02` are signed `short`, not
`unsigned short`: the native Reimu and third-boss state machines repeatedly
compare them as signed values, increment/decrement them as signed counters,
and consume their sign-extended values in trajectory reconstruction. The
source now declares the actual signed type and replaces 813
`reinterpret_cast<signed short&>` aliases across 140 source/include files with
direct member access. A follow-up removes 29 redundant `static_cast<short>`
wrappers from assignments to those now-correctly-typed fields.

All four complete fighter `Advance` parents preserve their entire COFF bodies
and relocation maps: Reimu 62,090 bytes / 1,824 relocations; Sakuya 83,922 /
2,352; Youmu 47,655 / 1,491; Remilia 59,236 / 1,863. Relocation positions,
types, addends and local targets are unchanged. A further signed-counter
cleanup removes 16 redundant `static_cast<int>` promotions inside float
expressions and 18 redundant `static_cast<float>` wrappers whose surrounding
float arithmetic already performs the conversion. All four complete parent
bodies and relocation maps were rebuilt again and remain byte-identical.
types, addends and local targets are unchanged. Their existing frontiers also
remain unchanged (6,311/5, 6,958/12, 2,736/5 and 1,741/3 GPR/width debt
respectively); no giant exactness is claimed. The 12 affected exact units
covering character action dispatch and all fighter reset-round entry points
were cold-replayed selectively and passed 12/12.
The Youmu parent also drops six explicit `static_cast<signed short>`
wrappers in three shared scripted-state fragments. The complete 47,655-byte
COFF body and all 1,491 relocation positions/types/addends/local targets
remain identical after this additional cleanup.

A further signed-counter pass removes 16 redundant `static_cast<int>` staging
conversions before float use in five bounce/resource-volley fragments, plus
two redundant `static_cast<float>` conversions in the random-volley fragment.
The signed short fields now undergo the ordinary C++ integral-to-float
promotion directly. All four complete fighter `Advance` bodies and their
relocation maps remain byte-identical (62,090/1,824; 83,922/2,352;
47,655/1,491; 59,236/1,863), with all four frontiers unchanged.

A related reset/initialization cleanup removes 58 `reinterpret_cast<unsigned
short&>` aliases around already-signed Fighter members (`sequenceTimer`,
`fieldF04`, `fieldF0A`, `fieldF0C`, `fieldF0E`) when those members are set to
zero. All writes now use the declared `short` members directly. The 20 exact
initialization/reset/dispatch units covering the changed source files were
replayed selectively and passed 20/20; no broad cold replay was run.

`Fighter::fieldEF8` at `+0xEF8` is an unsigned 16-bit animation timer, not
a signed short. `Fighter::UpdateCounters` increments it continuously, while
Marisa's chain renderer and the battle HUD consume its unsigned phase/modulo
value. The field is now declared `unsigned short`; all five explicit
`reinterpret_cast<unsigned short&>` reads were replaced by direct member
access. The affected exact units (counter update, base reset, Sakuya reset,
Marisa chain render and battle HUD render) replayed 5/5.

A second reset-field pass removes another 38 `unsigned short&` reinterpret
aliases from zero assignments to already-signed members: `aiWaitTimer`,
`aiStep`, `aiCardTimer`, `field6FA`, `field6FC`, Suika's `fieldF28/fieldF2A`
and Yuyuko's `fieldF10`. These members now use their declared `short` types
directly. The same 20 initialization/reset exact units were replayed again
and passed 20/20. No `reinterpret_cast<unsigned short&>` aliases remain in
tracked `src/` or `probes/` sources.
`Fighter::field478` at `+0x478` is a signed 16-bit texture-slot count. The
native `LoadResources` body uses `movsx` before passing it to `AllocateSlots`;
the member is now `short` and the call passes it directly, removing the last
`reinterpret_cast<short&>` member view in tracked source. The complete
1,186-byte `Fighter::LoadResources` body and all 63 relocations remain
identical. Its exact unit and all eleven character initialization units
replayed 12/12.
`Fighter::field6F8` at `+0x6F8` is a signed byte. Both complete stage
renderers load it with native `movsx` before comparing the stage-render gate;
the shared member is now `signed char` and both explicit signed-byte
reinterpret views are gone. Meiling and Patchouli retain their complete
1,606-byte COFF bodies and all 40 relocations each; the two exact renderer
units replayed 2/2.
The Mode 5 option bytes at `+0x52C/+0x52D/+0x52E/+0x530/+0x531` are
also signed bytes, matching the signed loads and the already-signed Mode 5
direction view. Their five `Fighter` members are now `signed char`; 39
`reinterpret_cast<signed char&>` views across pause/debug, options, render,
battle-state and frame-action code become direct member access. All seven
affected exact functions (pause menu, debug keys, Mode 5 options/render,
state advance, frame-action selection and base reset) replayed 7/7 with
complete bodies and relocations unchanged.
`BattleScene::field118` at `+0x118` is a signed menu-selection byte: pause
navigation increments/decrements it and explicitly wraps negative values.
The member is now `signed char`; 33 signed-byte reinterpret views in pause,
Mode 5 options/render and end-overlay rendering are direct accesses. The
nine affected exact functions (pause menu/debug, end overlay, Mode 5 options
and render, battle-state advance, scene construction, pause shortcut and
frame-action selection) replayed 9/9 with complete bodies and relocations
unchanged.
The character-selection arrays `chosenCharacter` / `alternateCharacter` at
`+0xE0/+0xE2` are signed bytes, not unsigned bytes. The selection controller
uses negative decrement and wrap checks; the two arrays are now `signed char`
and 70 `reinterpret_cast<signed char&>` views plus 29 redundant explicit
signed casts across controller/card/background/options code are gone. All six
exact selection update, card render, background render, options render,
subselection and reset functions replayed 6/6 with their complete COFF bodies
and relocation maps unchanged.
`Fighter::field713` at `+0x713` is a signed character-sequence state byte.
The result-scene target uses `movsx` for its `>= 8` and `== 10` state tests;
the shared member is now `signed char`, and the two result-scene signed-byte
reinterpret views are direct member accesses. Both complete 11KB character
sequence giants (Alice 11,354 bytes / 375 relocations; Yuyuko 11,428 bytes /
365 relocations), the 1,561-byte result update and all eleven fighter
initializers remain byte-identical; all 14 exact units replayed 14/14.
`Fighter::field3CF` at `+0x3CF` is the unsigned continuation/status byte
immediately following the one-byte F992 outcome union at `+0x3CE`. The shared
member is now `unsigned char`; 17 signed/unsigned reference aliases across
`BattleStateMachine` and nine shared fighter fragments now use direct access.
The complete Reimu/Sakuya/Youmu/Remilia fighter parents (62,090 / 83,922 /
47,655 / 59,236 bytes; 1,824 / 2,352 / 1,491 / 1,863 relocations) remain
byte-identical, and the affected exact battle-state function replayed 1/1.
`Fighter::field3CE` (+0x3CE) is now the one-byte `FighterOutcomeByteF992`
union, with explicit signed and unsigned views. This replaces 17 signed-byte
reinterpret-reference views and all 18 uses of the old two-byte `F992_OUTCOME`
borrowed-window macro with direct member access; the adjacent `field3CF`
remains its own unsigned byte. The old pointer-arithmetic overlay type and
macro are removed. All 56 exact functions across battle-state, hit handling,
KO/round-end processing and fighter reset (six translation units) replayed
56/56 with complete function bytes and relocation maps unchanged.
A further 45 unsigned-byte reference casts were removed from writes to
members already declared `signed char`: the eleven character `field532`
initializers, BattleScene `field018` state writes, Meiling `sequencePhase`,
Fighter `field484/field3AD/noticeState`, and ResultScene `field00C`. This
covers the 3,797-byte Meiling stage configuration, hit/pause/KO/round-end
paths, notice helpers and all eleven fighter constructors. All 38 exact
functions across the 20 touched translation units replayed 38/38 with
complete COFF bodies and relocation maps unchanged.
The replay-record append cursor at `+0x116` remains a signed byte and now
increments directly, without an unsigned-reference alias. The complete
1,252-byte `ReplayRecords::AppendRecord` body and all 50 relocations remain
identical (exact replay 1/1).
Four Youmu stage-two fragments now assign the opaque Actor color channels
as unsigned `0xFF` values directly instead of reinterpreting each channel as
`signed char` and storing `-1`. All 20 aliases are gone. The full 47,655-byte
Youmu `Advance` body and all 1,491 relocations remain identical; its frontier
stays at 16,833 differing bytes, with no regression.
Six more unsigned-byte aliases were removed from already-typed argument
and state accesses: two round-winner writes, the signed-byte round-record
field (with an explicit value conversion), the projectile direction argument
and both notice-render step arguments. The affected round-end, record-field,
character auxiliary and notice-render functions replayed 11/11 exactly.
Forty-one `reinterpret_cast<char&>` aliases of the already-signed `facing`
byte were removed from 21 shared Reimu attack/state fragments and the Youmu
owner-wave fragment. Both complete Reimu and Youmu `Advance` bodies (62,090
and 47,655 bytes; 1,824 and 1,491 relocations) remain byte-identical, and
both nonexact frontiers remain unchanged at 42,551 / 16,833 differing bytes.
Twenty further unsigned-byte aliases were removed from five large fighter
parents: ten zero writes to signed `field3AC`, seven byte decrements of signed
`field366`, and three owner-facing copies. The Reimu/Sakuya/Youmu/Remilia
fighter advances and PatchouliObject advance (62,090 / 83,922 / 47,655 /
59,236 / 82,109 bytes; 1,824 / 2,352 / 1,491 / 1,863 / 1,449 relocations)
all remain byte-identical. Their frontier drift remains unchanged at 42,551,
18,253, 16,833, 40,569 and 24,643 bytes respectively.
The notice gate `Fighter::noticeFirst` at `+0x6E8` is a signed byte; its
native render test sign-extends the value. The member is now `signed char`,
with the complete 1,637-byte render and 1,151-byte base-reset functions still
identical. Four signed-byte aliases that only wrote zero to the unsigned
`field39C` flag and the redundant signed view in the overlay timeline switch
were also removed. The four affected exact functions replayed 4/4.
Selection input history now tests the four signed storage counters with
explicit `static_cast<unsigned int>` value conversions rather than
reinterpret-cast references. Eight aliases across the two selection/update
functions were removed; both complete functions replayed 2/2 exactly.
Forty float-to-float bit-reference assignments were replaced by ordinary
member assignments throughout the large PatchouliObject action family:
owner position copies, projectile velocity/angle copies, and paired scale
copies. Seven more float bit aliases in the shared CharacterProjectile and
CharacterObject constructor were replaced with direct float assignments.
The complete 82,109-byte PatchouliObject `Advance` and all 1,449 relocations
remain identical; its frontier stays at 24,643 differing bytes. Both affected
exact leaf functions replayed 2/2.
The paired third-boss arc no longer wraps its already-`float` `velocityX`
member in ten redundant `reinterpret_cast<const float&>` expressions. The
complete 83,922-byte Sakuya `Advance` body and all 2,352 relocations remain
identical; its frontier stays at 18,253 differing bytes.
Twelve remaining `int&` bit overlays on float members were replaced with
native float assignments: six zero resets of Reimu's `field490` pair, two
rotation resets, two owner-X copies and a Y zero in Youmu's scripted states.
The pause effect's positive `field10C = 3600` write is now direct as well.
All eight affected `ProgressPauseF174` functions replayed 8/8, and the full
Reimu/Sakuya/Youmu/Remilia fighter `Advance` bodies and relocation maps remain
identical.
`BattleScene::field010` (+0x010) is now a signed `int` timeline-frame
counter, matching its per-frame increment and signed rectangle-offset math.
Seventeen `reinterpret_cast<int&>` views in the frame and overlay-timeline
paths are gone. Eleven additional `int&` overlays around positive writes to
the existing unsigned `BattleScene::field00C` timer were removed in pause,
KO and round-end transitions; the timer's unsigned storage is preserved. All
22 exact functions across seven battle/scene translation units replayed
22/22, including the 3,459-byte overlay timeline and 4,764-byte battle state
machine. The four fighter giant bodies and relocation maps remain identical.
Battle collision response now copies `field08C`/`field090` as their actual
float members instead of viewing the float lvalues as `unsigned long&`.
`Actor::SaveCollisionFields` likewise snapshots `savedX`/`savedY` through
ordinary float assignments. This preserves the original 32-bit representations
for the finite world coordinates while expressing the observed Actor layout
with its native C++ types. All three exact collision functions (975-byte
hitbox resolution, 897-byte body contact, and 118-byte collision snapshot)
replayed 3/3 with complete bodies and relocation maps unchanged.
The battle scene constructor's two zero writes to float `field08C` are now
`0.0f` assignments instead of integer-word aliases; its complete 922-byte
constructor and all 40 relocations remain identical (replay 1/1).
The score word is stored as signed `int`, while the global score ceilings
are unsigned 32-bit values. The three unsigned-reference aliases in the
battle state machine and knockout settlement were redundant for comparisons
because the usual arithmetic conversions already preserve the unsigned
comparison; the settlement add now spells out the unsigned 32-bit sum before
storing back to the signed score member. The continue/debug score reset is a
normal direct member assignment. All eight exact functions across the three
state/KO/pause translation units replayed 8/8, including the 4,824-byte
`BattleScene::AdvanceState` and 1,150-byte knockout resolver.
The queue policy and static lifetime paths now consume that same typed
segmented storage: `ClearFourQueues` and `IsPrimaryInputQueueEmpty` use direct
queue members, while the static constructor/destructor expose the file handle,
record header, offset table, and four queue members at their native offsets.
The destructor now uses the typed `HANDLE` field and compiler-managed
reverse-order member destruction. All four queue-policy/constructor/destructor
functions replayed 4/4 exact (67 / 35 / 132 / 161 bytes respectively).
The replay reader `ReplayRecords::LoadRecord` (+0x413AC0) now shares the
same `ReplayRecordsLayoutF219` and queue storage declarations. It uses the
actual file-path array, ten-entry record-offset table, typed serialized
header, and four queue members directly; the `AT`/`LIST` pointer-arithmetic
macros are gone. Its complete 792-byte body and all 29 relocations remain
identical. The append and load functions replayed 2/2 exact.
`ReplayRecords::AppendRecord` (+0x413DE0) now has a typed owner view instead
of a `FIELD` macro and raw `this+offset` queue casts. The ten file-offset
slots at `+0x11C`, serialized 16-byte header at `+0x144`, and four queue
members at `+0x154/+0x168/+0x17C/+0x190` are explicit members. The queues are
20-byte segmented circular collections (block map, block count, first index,
size); their 8-byte iterators hold owner plus logical index and dereference
through 16-element blocks. The complete 1,252-byte append function and all
50 relocations remain identical; exact replay passed 1/1.
The four-byte Actor overlay at `+0x080` now names the auxiliary-object
angle as `field080Angle`, while preserving the ordinary actor's adjacent
signed `field080`/`field082` hit-stop words in an anonymous union. The four
float-reference aliases in `CharacterAuxObject::Advance` are direct typed
member accesses. Its complete 31,777-byte body and all 913 relocations remain
identical; the exact 31,352-byte function coverage replayed 1/1.
The shared Fighter card/knockout countdowns `field3A4` (+0x3A4) and
`field3A8` (+0x3A8) are now signed `int` members. The native update subtracts
from them, checks negative underflow and clamps to zero; knockout settlement
also consumes the signed `field3A4` value as a record count/score. Sixteen
`reinterpret_cast<int&>` views were removed across the timer, knockout, battle
state and status-render paths. All 45 exact functions across six translation
units replayed 45/45, and all four complete fighter `Advance` bodies and
relocation maps remain identical.
The Actor/Fighter pointer views were made explicit without changing their
32-bit slots. `Fighter::field534` now has renderer and secondary-texture
union views; `stageDrawing` keeps its multi-renderer `void*` view plus the
F286 stage-texture view. The load-stage/load-resources paths now use the typed
members directly. The redundant pointer-reference aliases in fighter overlay
rendering, command selection, damage-flash predicates and opponent-gauge byte
offset access were removed. All ten exact functions across six translation
units replayed 10/10, including the 1,186-byte `Fighter::LoadResources`,
1,081-byte `BattleScene::RenderDamageFlash`, 753-byte opponent-gauge update
and 374-byte stage-resource loader.
The third-boss state words `Fighter::fieldF06` (+0xF06) and `fieldF08`
(+0xF08) are now signed 16-bit members. Their native uses include negative
arc increments, signed cadence countdowns, signed trajectory values and
signed comparisons; they were incorrectly modeled as unsigned and accessed
through 36 `reinterpret_cast<signed short&>` aliases. All eight third-boss
fragments now use the actual members directly. The complete 83,922-byte
Sakuya `Advance` body and all 2,352 relocations remain identical; all 46 exact
functions across eleven reset/shared-action translation units replayed 46/46.
The four fighter giant bodies remain identical and Sakuya's frontier remains
at 18,253 differing bytes.
The input counters `inputA`/`inputB`/`inputC` and `inputD` no longer use
reference reinterpretation to force unsigned comparisons. The existing
32-bit signed storage of A/B/C is preserved, but the intended unsigned tests
now use value `static_cast`s; `inputD` uses its already-declared unsigned
value directly or an explicit value conversion where the native expression
requires the signed bit pattern. This removes the aliasing references without
changing the Fighter layout. All 29 exact functions across fifteen affected
translation units replayed 29/29, and the complete Reimu/Sakuya/Youmu/Remilia
`Advance` bodies and relocation maps remained identical. Their existing
frontier drift counts remain 42,551 / 18,253 / 16,833 / 40,569 bytes.
The name-entry `field120` byte at `+0x120` is likewise signed: the parallel
sprite-name view already declares it `signed char`, and the editor uses its
sign-extended value to calculate the active record offset. The update view now
uses `signed char` directly, removing its last signed-byte reinterpret cast;
the complete 541-byte `NameEntryScene::UpdatePlayer` body and all 11
relocations remain identical (exact replay 1/1).


## 2026-11-20 — Alice object first-join register debt eliminated

The Alice object `Advance` join at `0x004F344C` now uses the original
VC7.1 register rotation. The `animationStage < 3` scale-growth branch has an
explicit, empty `else if (animationStage == 3)` arm: stage 3 is a real no-op
for this scale update, and expressing that state explicitly changes the
compiler's join predecessor state without adding instructions. This is
ordinary C++ control flow, not padding or a synthetic instruction sequence.

Focused VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` measurement now reports
8,789/9,009 target/object instructions, zero mnemonic differences, zero
instruction-width differences and zero GPR operand differences. The
byte-frontier ratchet fell from 575 to 438 bytes; its remaining range is
exactly the object suffix after the 33,293-byte CODE extent, not a code
mismatch. That 438-byte suffix consists of the two separately reviewed
original switch tables: 240 bytes at `0x004F3FAD` and 198 bytes at
`0x004F409D`; both target SHA-256 values in
`config/authored-origin-switches.csv` match the object bytes. Across the
complete 33,731-byte code-plus-table object extent, every non-relocation byte
matches the target. All 682 COFF relocation destinations also resolve:
62 local targets and 620 external references (64 distinct symbols) agree
with the original local offsets and known function/global/runtime addresses.

The exact replay unit `alice-object-advance-004ebda0` now accepts this whole
parent. Its `size = 33,293` credits only authored CODE, while
`compare_size = 33,731` also compares the two separately owned switch tables;
the 438 table bytes are never counted as authored CODE. The canonical
`matches.csv` and `functions.csv` ledgers now record 100.00% matching. Alice is
removed from `frontiers.toml`; Meiling is the next active giant frontier.

## 2026-11-20 — Meiling/Sakuya register-frontier recheck

Meiling `005EB520` still has 135 GPR-role and six width differences, with the
first mismatch at `005F3904` in action 998. The mismatches are a consistent
EAX/ECX/EDX rotation through that state's body; the six width changes are
associated with the different accumulator/register forms of its integer
comparisons. Explicit `this`, base/derived owner casts, volatile lvalues,
owner-pointer aliases, and register locals did not alter the native register
rotation. All probes were discarded; the complete source remains unchanged.

Sakuya `004CA6E0` was also rechecked at its actual first GPR mismatch,
`004CCBD7` in the action-800 bounds guard (not the later 809/810 gate). The
target reloads the receiver through ECX/EDX/EAX/ECX for the four float-bound
comparisons, while the current object uses EAX/ECX/EDX/EAX. Ten equivalent
predicate order/grouping/negation/qualification variants retained the same
447 GPR and 12 width differences; nested forms expanded the body and were
rejected. The earlier 809/810 transient 328-GPR form remains rejected because
its section was two bytes too large. No source change or exactness credit.

Patchouli action `0x356` was checked against its own Ghidra switch arm rather
than nearby disassembly. That arm's effect loop is `local_6c < 8`; the separate
`0x0A` loop at `00515C73` belongs to a different control-flow block and must
not be attributed to this action. The source remains eight iterations. The
brief ten-iteration probe was reverted and receives no semantic or exactness
credit. The parent remains at 522 GPR-role and five width differences, with
first mismatch `00515C0E`.

The Patchouli first GPR divergence `00515C0E` is the entry of action
`0x358` (source fragment `CharacterObjectBoss358F1101.inc`), not action
`0x356`. Its following `cmp [ebp-0x6c], 0x0A` at `00515C73` is the ten-effect
loop already present in the `0x358` source. Action `0x356` is the separate
preceding switch arm and correctly retains its eight-effect loop. Five
predicate-order/inclusive-bound forms and several local-owner aliases were
compiled against the whole parent for `0x358`; none produced an acceptable
improvement. The stage-first condition reduces a raw zipped GPR count but
reorders the native tests and adds instruction/width differences; mnemonic-
aligned comparison confirms it does not solve the register rotation. Further
isolated variants using register pointers, references, `short`/`long` temporaries
and explicit `goto` guards also worsened the whole-object frontier. All
experiments were discarded; both case sources remain unchanged.


## 2026-11-20 — Yuyuko state-838 source-order frontier

The complete Yuyuko object parent `0057D580` now expresses state 838's
independent owner-action and stage tests in a different natural-C++ order.
The `animationStage == 0` / owner-action 611–613 arm is evaluated first;
the `owner->action != 611 && field080 == 0 && owner->action != 612` arm
comes second. The predicates are Boolean-equivalent and read only ordinary
fields, so this changes VC7.1's register/code layout without changing game
behavior or introducing assembly, padding or machine-code literals.

The COFF section shrank from 44,331 to 44,327 bytes. The byte frontier fell
from 17,739 to 1,697 differences: 16,120 formerly differing bytes now
match, with 78 previously matching offsets displaced. All 198 switch-table
entries for actions 800–997 now resolve to the same relative state-entry
offsets as the original.

The current instruction diagnostic is 23 mnemonic, 28 width and 897 GPR
differences, with the first GPR mismatch at `00583489` (#6565). This is a
nonexact whole-function frontier. The next useful investigation is the
surrounding state-837/838 join at that address; do not treat the first
mismatch as necessarily belonging to the state-838 entry itself.


Yukari object `005A1600` action `900` remains at its committed baseline. A
speculative stage-2 proximity gate was rejected after checking the original
case-900 decompile and target code: that action has no 100-unit distance test
or `0045B850(8)` transition. Do not reintroduce that trial without new target
evidence; the Yukari object remains a separate partial reconstruction.

### Latest Yuyuko source follow-up

Action 0x192 restores its original 50-unit facing-dependent X offset for
effect 800. Action 0x2E4 retains separate stage-7 and stage-8 0x388 emissions.
Facing-based X offsets now preserve signed-char integer multiplication
before conversion to float. The current VC7.1 body is 62,271 bytes versus the
61,872-byte target (+399), with 51,948 direct non-relocation byte differences
and a 0x2B8 frame. Relative to the prior double-contact-scale checkpoint
(62,254 bytes, 51,620 direct differences, 0x2B0 frame), these source-level
semantic corrections add 17 body bytes, 328 direct differences and 8 frame
bytes; this is not a whole-function exactness claim. Fifteen targeted
animation, movement, range, reset, battle/aux-effect, sound, gauge, camera
and word-helper leaf units replay 15/15 exact. A natural-C++ seven-range/
switch dispatch rewrite was compiled but not retained because VC7.1 created
per-switch temporary slots and a larger frame than the current flat-switch
baseline.

### 2026-11-22: Sakuya object Advance 004CA6E0 — action-808 register frontier

A fresh target disassembly around the first register mismatch at `004CCBD7` clarifies the earlier shorthand that called this the “action-800 bounds guard”: the mismatching block is the later `case 808` in `SakuyaObjectAdvanceF1222.cpp`. `case 800` is a distinct block and uses the 1400/-160 horizontal bounds; action 808 uses 2000/-1000 horizontal bounds and 1000/-160 vertical bounds. The PE constants at `006583D8`, `006595E0`, `006583B4`, and `006595EC` decode to those four values.

The current object-advance frontier remains 42,511 bytes, with no mnemonic mismatches, 12 width differences, and 447 register-operand mismatches (441 instructions). Those register mismatches are confined to the `004CC000` and `004CD000` blocks and form the same three-register cycle: target EAX maps to source EDX, target ECX to source EAX, and target EDX to source ECX. The first occurrence is the action-808 bounds guard at `004CCBD7`.

A target-shaped four-guard `goto` formulation was tested for action 808: four conditional branches to one out-of-bounds label, followed by an unconditional jump over the cleanup block to the in-bounds body. It cold-compiled to the same 447-register / 12-width frontier as the original `||` expression. Earlier condition-order, grouping, negation, qualification, and owner-alias experiments likewise did not improve this frontier. Do not repeat those syntax-only variants; the next useful step needs new evidence about live-register allocation at the action-808 block. No assembly, byte graft, padding, or fabricated locals were introduced.

The action-808 source now names the four read-only arena bounds as `extern const float` references to `006583D8` (2000), `006595E0` (-1000), `006583B4` (1000), and `006595EC` (-160), matching the actual PE data reads instead of embedding equal-valued literals. The separate action-800 1400/-160 guard is unchanged. The focused frontier remains 447 GPR / 12 width differences: this is a source/data-identity correction, not an exactness claim. Constant-left, ternary, member-alias, and break/return rewrites were also measured without improving the register cycle.

### 2026-11-22: promoted Sakuya and Patchouli object parents

The complete natural-C++ parents for both large object state machines are now promoted from `probes/` into `src/`. Their ledger status is `reconstructed`, not `matching`; original function extents, source-origin classification and exactness are kept independent. The promotion does not claim a byte-exact replacement.

- `0x004CA6E0` — `src/SakuyaObjectAdvanceF1222.cpp`, 42,511 target CODE bytes. The focused VC7.1 frontier remains 0 mnemonic, 12 width and 447 GPR differences; first GPR difference `0x004CCBD7`. The 12 width differences are the action-500..503 comparisons in the adjacent object action blocks, where the same EAX/ECX/EDX register cycle changes the accumulator `cmp` encoding. A positive-outer-guard rewrite of action 809 regressed the frontier; keep the original natural predicate until a new allocation hypothesis exists.
- `0x0050A580` — `src/PatchouliObjectAdvanceF1044.cpp`, 81,539 target CODE bytes. The focused frontier remains 0 mnemonic, 5 width and 522 GPR differences; first GPR difference `0x00515C0E`, in Patchouli case `0x354`. The target/source difference is the same three-register cycle. A local `Fighter*` alias and three action/stage predicate orderings all regressed the instruction frontier; retain the original source form.

The COFF section extents include generated switch data and must not be mistaken for function padding. Sakuya's separately recorded guarded dispatch uses a 224-byte table at `0x004D4CEF` and a 198-byte remap at `0x004D4DCF`; Patchouli's uses a 368-byte table at `0x0051E403` and a 199-byte remap at `0x0051E573`. Both dispatch guards, complete tables and remaps were independently revalidated against the original PE. The extra COFF extent is not a license to extend the C++ body, add padding, or graft table bytes into source.

The parallel `SakuyaFighter::Advance()` frontier remains a separate 82,796-byte giant. Typed-short substitutions for its `F00/F02` counters and targeted `case 0x59` return/control-flow variants did not improve its 6,958-GPR / 12-width frontier. Keep the shared `FighterScriptedBounce59F813.inc` unchanged; the next step needs new register-allocation evidence, not another spelling-only edit. `/O1` and `/O2` compiler-profile trials changed thousands of mnemonics, so retain the locked `/Od` profile.

For Reimu fighter `0045DD70`, the first width difference at `004605C6` is `cmp eax,0x96` (target) versus `cmp edx,0x96` (source), a register-choice encoding-width change rather than a missing action. The priority-mode `case 0x63` is already present through `ReimuEarlyRecoveryStatesF1184.inc` and `FighterMode63PriorityF627.inc`. Changing that comparison to hexadecimal, constant-left, casts, or a raw short load did not change the focused frontier; keep the existing natural C++ handler until a new register-allocation hypothesis is available. After the latest source update, the focused frontier's recorded COFF object size was refreshed from 62,090 to 61,926 bytes; the original target extent remains 60,999 bytes.

## 2026-11-22: promoted fighter action-state sources

Two complete large fighter action-state bodies have moved from research-only probes into `src/` as natural C++ reconstructions. Their `functions.csv` status is `reconstructed`, not `matching`; `function-origins.csv` remains independently unclassified and no authored/exact origin credit is inferred.

- `0x004AC040` — `src/SakuyaFighterAdvanceF1020.cpp`, full 82,796-byte native body. The focused frontier preserves the full extent and CFG. Current byte debt is 18,253 bytes, with 6,958 GPR operand positions and 12 instruction-width differences; first GPR divergence is `0x004ADEFA`.
- `0x0045DD70` — `src/ReimuFighterAdvanceF1183.cpp`, full 60,999-byte native body. The focused frontier preserves the full extent and switch/control-flow shape. The first GPR divergence is `0x0045FDA9`; the first width divergence is `0x004605C6`, after which linear instruction decoding loses alignment.

Both bodies are ordinary C++ composed from action-specific source fragments. No inline assembly, emitted bytes, padding, raw-code grafts, masks, or truncated comparisons were introduced. Their remaining compiler/codegen debt stays explicit and is the next reconstruction target.
