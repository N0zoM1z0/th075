# The remaining giants

The unmatched authored functions are slot-1 `Advance` methods from
the fighter vtables. These are per-frame state machines with large
`switch (action)` bodies. All character-object advances have exact
replay units.
Use the live reconstruction report for the authored backlog and the
table below for complete source parents.

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
names `std::list<ObservedInputSnapshotF378>::front`. The layout change
cold-replayed all 81 affected exact units. The [complete object replay](#2026-11-24--youmus-object-advance-cold-replays-exactly)
now includes that call.

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
including all 938 relocation records at that checkpoint.

## Complete research parents

The table lists the complete parents and their recorded comparisons.
Instruction and width counts describe the nonexact builds. The exact
rows have complete replay units.

| Original | Character | Size | Parent | GPR debt | Widths | First GPR difference |
| --- | --- | ---: | --- | ---: | ---: | --- |
| 0045DD70 | Reimu fighter | 60,999 | `ReimuFighterAdvanceF1183.cpp` (cold exact) | 0 | 0 | — |
| 00476A40 | Reimu object | 50,915 | `ReimuObjectAdvance.cpp` (cold exact) | 0 | 0 | — |
| 00486550 | Marisa fighter | 50,735 | `MarisaFighterAdvance.cpp` (cold exact) | 0 | 0 | — |
| 0049C8F0 | Marisa object | 46,596 | `MarisaObjectAdvance.cpp` (cold exact) | 0 | 0 | — |
| 004AC040 | Sakuya fighter | 82,796 | `SakuyaFighterAdvanceF1020.cpp` (cold exact, `/GX`) | 0 | 0 | — |
| 005214B0 | Youmu fighter | 46,755 | `YoumuFighterAdvanceF1040.cpp` (cold exact) | 0 | 0 | — |
| 00543210 | Remilia fighter | 58,294 | `RemiliaFighterAdvanceF1041.cpp` (cold exact) | 0 | 0 | — |
| 00564BE0 | Yuyuko fighter | 61,872 | `YuyukoFighterAdvance.cpp` (cold exact) | 0 | 0 | — |
| 004CA6E0 | Sakuya object | 42,511 | `SakuyaObjectAdvanceF1222.cpp` (cold exact) | 0 | 0 | — |
| 004EBDA0 | Alice object | 33,293 | `CharacterObjectActionsF572.cpp` (exact replay) | 0 | 0 | — |
| 0050A580 | Patchouli object | 81,539 | `PatchouliObjectAdvanceF1044.cpp` (cold exact) | 0 | 0 | — |
| 00536400 | Youmu object | 39,999 | `YoumuObjectAdvanceF1211.cpp` (cold exact) | 0 | 0 | — |
| 0055AC80 | Remilia object | 28,432 | `CharacterObjectWhole0055AC80F1194.cpp` (cold exact) | 0 | 0 | — |
| 0057D580 | Yuyuko object | 43,845 | `YuyukoObjectAdvanceF1237.cpp` (cold exact) | 0 | 0 | — |
| 005A1600 | Yukari object | 43,599 | `YukariObjectAdvanceF1231.cpp` (cold exact) | 0 | 0 | — |
| 005C9CC0 | Suika object | 43,501 | `SuikaObjectAdvanceF1216.cpp` (cold exact) | 0 | 0 | — |
| 005EB520 | Meiling object | 34,434 | `MeilingObjectAdvanceF1207.cpp` (cold exact, no `/GS`) | 0 | 0 | — |

The flags are `/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes` unless noted.

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
three width differences). The complete natural-C++ source is now promoted to
`src/RemiliaFighterAdvanceF1041.cpp`, with the ledger marked `reconstructed`,
not `matching`; the native vtable at `0x00659A40` confirms slot 1 points to
`0x00543210`. Its three guarded dispatch tables/remaps are independently
verified. No giant exact credit was claimed.

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
16,833 differing bytes). The complete natural-C++ source is now promoted to
`src/YoumuFighterAdvanceF1040.cpp` and the ledger marks it `reconstructed`,
not `matching`; the native vtable at `0x006598D0` confirms slot 1 points to
`0x005214B0`. Its four guarded dispatch tables/remaps are independently
verified. All 85 exact units depending on the real fighter header cold-replayed
in three affected-only groups (36/36, 25/25, 24/24).

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

Ghidra labels the shared call in Yuyuko fighter actions `0`, `2`, `0x5D`
and `0x5E` as `Concurrency::details::ContextBase::ClearCancel`. Its
destination `0x00453E20` is the exact `Fighter::ClearMotionFields` leaf.
[Whole-function replay](#2026-11-24--yuyukos-fighter-advance-cold-replays-exactly)

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

Fighters 004D7E70 (Alice, 43,601 B), 004F7130
(Patchouli, 44,211 B), 0058AF60 (Yukari,
49,230 B), 005AEEC0 (Suika, 71,616 B) and 005D73C0 (Meiling, 43,282 B).
`config/fighter-boss-dispatch-fingerprints.json` has their extents and jump
tables. Each fighter shares its switch grammar with the others, so a new
parent starts from the closest complete one plus the native case bodies.

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

### 2026-11-22: promoted Sakuya, Patchouli, Youmu, Yuyuko, Meiling, Suika and Yukari object parents

The complete natural-C++ parents for the large Sakuya, Patchouli, Youmu, Yuyuko, Meiling, Suika and Yukari object state machines are now promoted from `probes/` into `src/`. Their ledger status is `reconstructed`, not `matching`; original function extents, source-origin classification and exactness are kept independent. The promotion does not claim a byte-exact replacement.

- `0x004CA6E0` — `src/SakuyaObjectAdvanceF1222.cpp`, 42,511 target CODE bytes. The focused VC7.1 frontier remains 0 mnemonic, 12 width and 447 GPR differences; first GPR difference `0x004CCBD7`. The 12 width differences are the action-500..503 comparisons in the adjacent object action blocks, where the same EAX/ECX/EDX register cycle changes the accumulator `cmp` encoding. A positive-outer-guard rewrite of action 809 regressed the frontier; keep the original natural predicate until a new allocation hypothesis exists.
- `0x0050A580` — `src/PatchouliObjectAdvanceF1044.cpp`, 81,539 target CODE bytes. The focused frontier remains 0 mnemonic, 5 width and 522 GPR differences; first GPR difference `0x00515C0E`, in Patchouli case `0x354`. The target/source difference is the same three-register cycle. A local `Fighter*` alias and three action/stage predicate orderings all regressed the instruction frontier; retain the original source form.

- `0x00536400` — `src/YoumuObjectAdvanceF1211.cpp`, 39,999 target CODE bytes, with its typed list-history declarations in `src/YoumuObjectHistoryF1211.hpp`. The focused frontier remains 0 mnemonic, 10 width and 913 GPR differences; first GPR difference `0x005392F8`. The 268-byte dispatch table at `0x0054003F` and 199-byte remap at `0x0054014B` were independently revalidated. The history-queue replay remains ordinary C++ and nonexact; no exactness credit is inferred.

- `0x0057D580` — `src/YuyukoObjectAdvanceF1237.cpp`, 43,845 target CODE bytes. The focused frontier is 0 mnemonic, 6 width and 914 GPR differences; first GPR difference `0x00583489` at the `case 838` entry. Condition-order, nested-if, and scoped owner/stage alias trials did not improve the register frontier; the current natural-C++ condition remains unchanged. The guarded dispatch has a 284-byte jump table at `0x005880C5` and a 198-byte remap at `0x005881E1`, both independently revalidated against the original PE. The old frontier entry had not been refreshed after commit `13c5871b` reordered the equivalent `case 838` short-circuit terms: the code section grew from 44,327 to 44,331 bytes, width debt fell from 28 to 6, and GPR debt changed from 897 to 914. The byte-offset ratchet is now re-based to that already-committed instruction shape; its 17,739 differing offsets reflect shifted instruction encodings, not an exactness claim.

- `0x005EB520` — `src/MeilingObjectAdvanceF1207.cpp`, 34,434 target CODE bytes. The focused frontier is 0 mnemonic, 6 width and 135 GPR differences; first GPR difference `0x005F3904`, all register differences in state 998. Its recorded VC7.1 profile intentionally omits `/GS`; do not silently add that flag. The guarded dispatch has a 244-byte table at `0x005F3BA2` and a 199-byte remap at `0x005F3C96`, both independently revalidated against the original PE.

- `0x005C9CC0` — `src/SuikaObjectAdvanceF1216.cpp`, 43,501 target CODE bytes. The focused frontier is 0 mnemonic, 1 width and 935 GPR differences; first GPR difference `0x005D2558`. The guarded dispatch has a 272-byte table at `0x005D46AD` and a 198-byte remap at `0x005D47BD`, both independently revalidated against the original PE.

- `0x005A1600` — `src/YukariObjectAdvanceF1231.cpp`, 43,599 target CODE bytes. The focused frontier is 0 mnemonic, 11 width and 613 GPR differences; first GPR difference `0x005A88A8`. The guarded dispatch has a 308-byte table at `0x005AC04F` and a 200-byte remap at `0x005AC183`, both independently revalidated against the original PE.

The COFF section extents include generated switch data and must not be mistaken for function padding. Sakuya's separately recorded guarded dispatch uses a 224-byte table at `0x004D4CEF` and a 198-byte remap at `0x004D4DCF`; Patchouli's uses a 368-byte table at `0x0051E403` and a 199-byte remap at `0x0051E573`; Youmu's uses a 268-byte table at `0x0054003F` and a 199-byte remap at `0x0054014B`; Yuyuko's uses a 284-byte table at `0x005880C5` and a 198-byte remap at `0x005881E1`; Meiling's uses a 244-byte table at `0x005F3BA2` and a 199-byte remap at `0x005F3C96`; Suika's uses a 272-byte table at `0x005D46AD` and a 198-byte remap at `0x005D47BD`; Yukari's uses a 308-byte table at `0x005AC04F` and a 200-byte remap at `0x005AC183`. All seven dispatch guards, complete tables and remaps were independently revalidated against the original PE. The extra COFF extent is not a license to extend the C++ body, add padding, or graft table bytes into source.

The parallel `SakuyaFighter::Advance()` frontier remains a separate 82,796-byte giant. Typed-short substitutions for its `F00/F02` counters and targeted `case 0x59` return/control-flow variants did not improve its 6,958-GPR / 12-width frontier. Keep the shared `FighterScriptedBounce59F813.inc` unchanged; the next step needs new register-allocation evidence, not another spelling-only edit. `/O1` and `/O2` compiler-profile trials changed thousands of mnemonics, so retain the locked `/Od` profile.

For Reimu fighter `0045DD70`, the first width difference at `004605C6` is `cmp eax,0x96` (target) versus `cmp edx,0x96` (source), a register-choice encoding-width change rather than a missing action. The priority-mode `case 0x63` is already present through `ReimuEarlyRecoveryStatesF1184.inc` and `FighterMode63PriorityF627.inc`. Changing that comparison to hexadecimal, constant-left, casts, or a raw short load did not change the focused frontier; keep the existing natural C++ handler until a new register-allocation hypothesis is available. After the latest source update, the focused frontier's recorded COFF object size was refreshed from 62,090 to 61,926 bytes; the original target extent remains 60,999 bytes.

## 2026-11-22: promoted fighter action-state sources

Four complete large fighter action-state bodies are now in `src/` as natural C++ reconstructions. Their `functions.csv` status is `reconstructed`, not `matching`; the independent `function-origins.csv` source-origin records remain unchanged, and no giant exact-match credit is inferred.

- `0x004AC040` — `src/SakuyaFighterAdvanceF1020.cpp`, full 82,796-byte native body. The focused frontier preserves the full extent and CFG. Current byte debt is 18,253 bytes, with 6,958 GPR operand positions and 12 instruction-width differences; first GPR divergence is `0x004ADEFA`.
- `0x0045DD70` — `src/ReimuFighterAdvanceF1183.cpp`, full 60,999-byte native body. The focused frontier preserves the full extent and switch/control-flow shape. The first GPR divergence is `0x0045FDA9`; the first width divergence is `0x004605C6`, after which linear instruction decoding loses alignment.
- `0x00543210` — `src/RemiliaFighterAdvanceF1041.cpp`, full 58,294-byte native body. The focused frontier remains 0 mnemonic, 3 width and 1,741 GPR differences; first GPR divergence `0x00545109`. Original vtable `0x00659A40` slot 1 points directly to `0x00543210`; all three guarded dispatch tables/remaps were independently verified.
- `0x005214B0` — `src/YoumuFighterAdvanceF1040.cpp`, full 46,755-byte native body. The focused frontier remains 0 mnemonic, 5 width and 2,736 GPR differences; first GPR divergence `0x0052327A`. Original vtable `0x006598D0` slot 1 points directly to `0x005214B0`; all four guarded dispatch tables/remaps were independently verified.

All four bodies are ordinary C++ composed from action-specific source fragments. No inline assembly, emitted bytes, padding, raw-code grafts, masks, or truncated comparisons were introduced. Their remaining compiler/codegen debt stays explicit and is the next reconstruction target.


### 2026-11-22: targeted fighter register-frontier and leaf replay batch

Meiling object `005EB520` remains at 0 mnemonic / 6 width / 135 GPR differences, all GPR differences confined to action state 998; the first is `005F3904`. Direct and explicit `this` member assignment, `Actor` base casts, address dereference, signed-byte casts, register pointer/value aliases, local reference aliases, and nested/reordered stage/frame guards were compiled under the pinned VC7.1 profile. None improved the frontier, so the committed natural-C++ state remains unchanged.

Sakuya fighter `004AC040` remains at 0 mnemonic / 12 width / 6,958 GPR differences. The first GPR mismatch `004ADEFA` is in action `0x59`. Plain/constant-left predicates, nested and goto control flow, local/register stage aliases, pointer/reference/volatile views, and later stage/frame predicate ordering were measured; none improved the whole-function frontier. Keep the existing `FighterScriptedBounce59F813.inc` source until a new allocation hypothesis has evidence.

Eight affected-only cold leaf replays were independently exact in this batch: `Actor::ResetPrimaryCounters` (52 B), `Actor::ResetSecondaryCounter` (43 B), `Actor::AdvanceNestedFrame` (142 B), `Actor::ResetTransform` (158 B), `Actor::SetPolarVelocity` (57 B), `Fighter::ClearMotionFields` (51 B), `Fighter::SetCameraShake` (25 B), and `CharacterObject::PlaySharedSound` (29 B). These are real game helpers called by the giant state machines; no STL/CRT helper or unreferenced no-op was promoted as game logic. No full cold replay was run.

## 2026-11-23 — Meiling action 998 inherits the scratch register cursor

VC7.1 starts the first `this` reload of action 998 at the EDX entry of
its scratch register search in the maintained build. Omitting only
`rotationZ += 1.0f;` from action 997 in a scratch copy changes the
action 998 entry to EAX and removes all 135 register and six instruction
width differences within 998. Action 998's source is identical in both
builds. The target executes the omitted update at `005F38C8–005F38D9`.

The deletion removes two receiver reloads. Its first register difference
in an instruction that survives the deletion is the sign extension of
`AdvanceNestedFrame`'s result at target `005F38E2`. The result moves
from EDX to EAX. The call still receives `this` in ECX and the two
action 997 exits still target the shared return. Omitting the whole of
997 also gives EAX, but makes 997 dispatch to the default. Omitting 996
instead gives ECX at 998. Explicit `this` qualification of both sides of
the facing assignment and appending the real
`Actor::ResetSecondaryCounter` definition to the translation unit each
reproduce the baseline code and relocation destinations. Pre- and
post-increment, reversed addition, subtracting negative one, and
returning immediately after the reset also keep the EDX entry.

The read-only Wine/GDB builds used the pinned `c2.dll` and the Meiling
frontier's `/Od /Ob0 /Gy /GR- /GX- /Zi` profile. They reproduced the
ordinary builds' whole sections and relocation records. The search at
`10775ACC` reads its starting pointer from `108A7D0C` via `10775443`.
The entries at `108A9738`, `108A973C` and `108A9740` correspond to
EAX, ECX and EDX. The store at `10776893` records the next position.
The two receiver reloads for the baseline rotation update advance the
cursor from `108A9738` through `108A973C` to `108A9740`. The
rotation omission removes exactly those two requests. The next request
in both builds is the sign extension at native `005F38E2`, which takes
the first candidate at its respective search position.

At the first reload in action 998, the baseline starts at `108A9740`
and takes EDX, advancing to `108A9738`. Both omissions start at
`108A9738` and take EAX, advancing to `108A973C`. The operands logged
at emission site `107B1490` tie these choices to the reload from
`[ebp-4]`. The search accepts the starting entry in each build.
The target's original compiler inputs remain unknown.

The full comparisons used the 34,877-byte target extent, including the
61 jump words and 199 remap bytes. Existing bindings resolved every
external call and the PE supplied the literal operands, whose bytes
were checked against the COFF literal symbols. The object supplied the
same-section relocation destinations.

| Build | CODE / full bytes | COFF relocations | Full byte differences | Action 998 |
| --- | ---: | ---: | ---: | --- |
| Maintained, explicit `this`, or visible reset | 34,436 / 34,879 | 806 | 876 | EDX, 135 register / 6 width differences |
| Omit action 997 | 34,032 / 34,471 | 800 | 1,817 | EAX, 0 register / 0 width differences |
| Omit the action 997 rotation update | 34,416 / 34,859 | 805 | 1,207 | EAX, 0 register / 0 width differences |

The byte totals include the unmatched end of the longer extent. In the
baseline the first byte difference is at `005EB547`, a jump displacement
to the shared return that moved by two bytes. Six CODE relocation
coordinates move, along with both table pointers' destinations. All 901
direct branches preserve their destination instructions, and all 199
actions preserve their destination blocks. The same edge and dispatch
checks pass in the rotation-omission build, with an identical remap and
11 moved CODE relocation coordinates after the omitted update. That
control has four register differences in the surviving tail of action
997, starting at `005F38E2`. The maintained C++ still performs the
rotation and the match ledger remains at its previous state.

Replay from the repository root with the scratch helpers in
`.analysis/meiling-allocator/` and the current
[Meiling source](../src/MeilingObjectAdvanceF1207.cpp). The positive
control removes the rotation update between the scale stores and the
frame-advance call in `case 997`. The local negative control replaces
`facing = owner->facing;` with `this->facing = this->owner->facing;`.

```bash
unset DISPLAY WAYLAND_DISPLAY
export WINEDLLOVERRIDES='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
scripts/repo-python .analysis/meiling-allocator/probe.py baseline explicit-this omit-997
scripts/repo-python .analysis/meiling-allocator/followup.py visible-reset omit-997-rotation
scripts/repo-python .analysis/meiling-allocator/audit.py baseline explicit-this visible-reset omit-997 omit-997-rotation
scripts/repo-python .analysis/meiling-allocator/trace-run.py baseline omit-997-rotation
```

Use the window between the last matching register request in 997 and
the first in 998 when evaluating a new whole-function candidate. A
source change must preserve the rotation store and both exits while
explaining how the compiler reaches the target EAX choice.

### Cross-check with Alice's eliminated stage test

Alice action `0x38D` supplies a same-compiler example of allocations
that change the register search without adding machine instructions.
The accepted source's empty stage-3 arm still gives a complete
33,731-byte match with 682 relocations. Removing only that arm keeps
the extent and relocation fields but introduces 137 differing bytes
starting at `004F344D`. The pinned read-only C2 trace shows two extra
requests in the accepted build between offsets `+0x76A6` and
`+0x76AC`. Their nodes have opcodes `0x1` and `0xC5`, the same
opcodes as the adjacent receiver reload and signed-word load. Neither
adds an instruction between the final scale store and the stage-4
test. The two requests move the starting candidate for that test from
ECX to EAX. Both traced objects agree with their ordinary builds.

Meiling's first cross-check reached EAX while keeping action 997's
rotation update. Both scratch versions store the actual frame advance result
in a signed `short reachedStage` and retain the completion check and
reset. Adding only the empty `else if (reachedStage == 0)` arm restores
the target register sequence and instruction widths in 998. Both
versions enlarge the frame from `0x210` to `0x214` and move `this`
from `[ebp-4]` to `[ebp-8]`. The extra word store already differs
at the earlier action, and both builds first differ in the prologue
at `005EB525`.

| Meiling control | CODE / full bytes | Full byte differences | Action 998 |
| --- | ---: | ---: | --- |
| Named short result | 34,447 / 34,890 | 24,827 | EDX, 135 register / 6 width differences |
| Named short result with an explicit zero-result arm | 34,445 / 34,888 | 24,820 | EAX, 0 register / 0 width differences |

All 806 relocation fields were applied in each comparison. Both remaps
match and all 199 actions retain their destination blocks, but 185
action entry offsets and the shared return offset move. Keeping the
result in an `int` removes the cursor effect of the zero-result arm.
Declaring the short `register` leaves its stack slot in place. Direct
`goto` and `return` exits in 997 give the baseline comparison. The
old baseline has 135 instruction-encoding differences when
instructions are aligned and corresponding branch and relocation fields
are accounted for. Every one is in action 998. The named-short pair's
trace shows one extra `0xC5` request from the zero-result arm. It moves
the cursor from EDX to EAX before the first reload in 998.

```bash
unset DISPLAY WAYLAND_DISPLAY
export WINEDLLOVERRIDES='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
scripts/repo-python .analysis/meiling-allocator/alice-control.py
scripts/repo-python .analysis/meiling-allocator/trace-run.py alice-stage3 alice-default
scripts/repo-python .analysis/meiling-allocator/playback-controls.py advance-short advance-short-playing
scripts/repo-python .analysis/meiling-allocator/whole-playback.py advance-short advance-short-playing
scripts/repo-python .analysis/meiling-allocator/trace-run.py advance-short advance-short-playing
```

### Meiling now cold-replays exactly

Action 997 checks whether the animation is still in range after handling
a completed animation. An in-progress stage continues on the next tick.
Expressing that path directly as `else if (animationStage < animationStageCount)`
lets VC7.1 reach EAX at `005F3904` with the target `0x210` stack
frame and `[ebp-4]` receiver slot. The rotation update, completion call,
reset, and two exits retain their original instructions and offsets.

The read-only trace of the accepted source shows four extra requests
after the completion comparison. Each stage operand contributes a
receiver reload and a signed-word load, with C2 opcodes `0x1` and
`0xC5`. Those requests advance the cursor from `108A9740` to
`108A9738` and leave no emitted instructions. The next request is the
reload at `005F3904`, which now selects EAX. The debugger build
reproduces the cold build's complete section and relocation records.

The canonical replay compares 34,877 bytes at `005EB520` with zero
differences, including every byte of the 244-byte jump table at
`005F3BA2` and the 199-byte remap at `005F3C96`. All 199 action
entry offsets, 901 direct branches, and 806 relocation offsets and
targets match. The unit credits the 34,434 bytes of authored code.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit meiling-object-advance-005eb520
scripts/repo-python .analysis/meiling-allocator/trace-run.py stage-exact
```

## 2026-11-24 — Suika's three startup joins cold-replay exactly

Actions 918, 928 and 929 initialize the transform on the first frame
of stage zero. Each now explicitly keeps the initialized transform on
later frames of that stage. The same condition
`animationStage == 0 && animationFrame != 0` restores the original
register choice at each join without emitting an extra instruction.
The stage-1 update and later motion and completion paths retain their
original effects and control flow.

Successive whole-function builds isolate the three joins under VC7.1
3077 with the recorded `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` profile.

| Explicit later startup frames | First differing register use | GPR differences | Complete relocated byte differences |
| --- | --- | ---: | ---: |
| Baseline | `005D2558` in 918 | 935 | 7,698 |
| 918 | `005D38D2` in 928 | 572 | 1,631 |
| 918 and 928 | `005D3B75` in 929 | 106 | 106 |
| 918, 928 and 929 | — | 0 | 0 |

The accepted unit cold-replays 43,971 bytes, including the 272-byte
jump table at `005D46AD`, the 198-byte remap at `005D47BD` and all
991 relocation fields. All 198 mapped action offsets and 1,001 direct
branch destinations match. The exact ledger credits 43,501 code bytes.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit suika-object-advance-005c9cc0
```

## 2026-11-24 — Sakuya's arena bounds check cold-replays exactly

Action 808 explicitly lets later frames of the startup stage proceed
to the same arena bounds check. The condition
`animationStage == 0 && animationFrame != 0` follows the movement
counter update. VC7.1 build 3077 emits no instructions for the empty
path and restores ECX at the receiver reload at `004CCBD7`. The
counter increment and four strict arena comparisons match their
original instructions, order and operand widths.

In the baseline, the first receiver reload for the bounds used EAX.
The resulting register difference carried through actions 809–811.
Writing the counter as a postfix increment gave the same baseline.
A separate empty test for equality at the right edge emitted two x87
loads and `fucompp`, adding ten code bytes. The later-startup
condition removes all 447 register and twelve width differences
in the complete function.

The cold replay compares 42,933 bytes with zero differences and
matches all 929 relocation fields. This covers 42,511 code bytes,
the 224-byte jump table at `004D4CEF` and the 198-byte remap at
`004D4DCF`. The full audit also checks all 198 action offsets and
1,014 direct branch destinations.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit sakuya-object-advance-004ca6e0
```

## 2026-11-24 — Patchouli's object Advance cold-replays exactly

Actions `0x357` and `0x3E5` now explicitly leave an unfinished
animation to continue when `animationStage < animationStageCount`.
VC7.1 emits the original completion checks and exits. The source
conditions restore the register choices at the following action
entries, `00515C0E` and `0051E215`. The completion calls, frame
updates and effect loops all retain their original bytes.

| Explicit in-progress paths | First differing register use | GPR differences | Complete relocated byte differences |
| --- | --- | ---: | ---: |
| Baseline | `00515C0E` in `0x358` | 522 | 26,719 |
| `0x357` | `0051E215` in `0x3E6` | 75 | 1,193 |
| `0x357` and `0x3E5` | — | 0 | 0 |

The original `0x357` exit skips frame progression while the owner is
delayed. Naming only that delay in an empty arm leaves the baseline
bytes unchanged. Checking the object's animation stage and count
reproduces the register choice in `0x358` while keeping the delay guard
and the completion cleanup.

The canonical replay compares 82,106 bytes, including the 368-byte
jump table at `0051E403` and the 199-byte remap at `0051E573`.
All 1,449 relocations, 199 action offsets and 1,834 direct branch
destinations match. The match ledger credits 81,539 code bytes.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit patchouli-object-advance-0050a580
```

## 2026-11-24 — Yukari's object Advance cold-replays exactly

Action 908 now explicitly lets an unfinished animation continue when
`animationStage < animationStageCount`. The VC7.1 build emits the original
movement, bounds checks and completion cleanup. At the following entry,
`005A88A8`, the first receiver reload uses ECX as in the target.
That change clears all 613 register differences across actions 909–917.
The eleven instruction-width differences also disappear, with the code
extent growing from 43,596 to the target 43,599 bytes.

The cold replay compares 44,107 bytes with zero differences, including
the 308-byte jump table at `005AC04F`, the 200-byte remap at `005AC183`,
and all 943 relocation fields. The complete audit checks all 200 action
offsets and 1,196 direct branch destinations. The match ledger credits
43,599 code bytes.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit yukari-object-advance-005a1600
```

## 2026-11-24 — Youmu's object Advance cold-replays exactly

Actions 829 and 906 switch to stage 14 when their owner reaches the
trigger stage. Explicitly expressing the path already at stage 14 or
later preserves the original stage change and return, followed by
the usual owner checks on the continuing path. VC7.1 emits the target
registers at both joins and removes the ten instruction-width differences.

| Explicit later-stage paths | First differing register use | GPR differences | Complete relocated byte differences |
| --- | --- | ---: | ---: |
| Baseline | `005392F8` in 829 | 913 | 26,729 |
| 829 | `0053DB86` in 906 | 472 | 9,470 |
| 829 and 906 | — | 0 | 0 |

The history-reader call at `005365FF` binds the typed
`std::list<ObservedInputSnapshotF378>::front` to `00540220`. The
emitted 32-byte member matches using its native begin and dereference
destinations. The emitted dependency bodies also match the addresses
recorded in the [R243 origin evidence](../config/character-list-front-origin-evidence.json).

The canonical replay compares 40,466 bytes with zero differences,
including all 938 relocation fields, the 268-byte jump table at
`0054003F` and the 199-byte remap at `0054014B`. The full audit
checks 199 action offsets and 967 direct branch destinations.
The match ledger credits 39,999 code bytes.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit youmu-object-advance-00536400
```

## 2026-11-24 — Yuyuko's object Advance cold-replays exactly

Yuyuko's object `Advance` at `0x0057D580` reproduces 43,845 CODE bytes,
the 284-byte jump table at `0x005880C5`, and the 198-byte remap table at
`0x005881E1`. The cold replay compares all 44,327 bytes with 1,043
relocations.

The first divergence was the stage-3 test after `AdvanceNestedFrame`
and `ClearFrameInfo` in action 837. Expressing the ongoing animation
path moved the first difference to the corresponding test in action
903 and restored all 198 dispatch offsets. A control that only tested
`animationStage < 3` at the same location loaded ECX where the target
loaded EAX and left seven instruction-width differences. The matching
completion path compares the two short animation fields.

After fixing both completion paths, the next divergence was inside
action 911. Its stage-3 hold between growth and fade follows the same
pattern as Alice's exact object action 909 at `0x004F344C`. Action
914 has the same growth and fade structure. Full builds changing one
path at a time produced these results:

| Source variant | GPR differences | Width differences | First GPR difference | Relocated byte differences |
| --- | ---: | ---: | --- | ---: |
| Parent at `c1739059` | 914 | 6 | `0x00583489` | 19,193 |
| Ongoing animation in 837 | 740 | 0 | `0x00585753` | 752 |
| Also in 903 | 619 | 0 | `0x00586A25` | 629 |
| Stage-3 hold in 911 | 379 | 0 | `0x00586EAC` | 385 |
| Also in 914 | 0 | 0 | — | 0 |

The local controls and complete comparison are in
`.analysis/yuyuko-object-advance/`. To repeat acceptance, run:

```sh
scripts/repo-python scripts/replay-exact-units.py --unit yuyuko-object-advance-0057d580
```

## 2026-11-24 — Remilia's fighter Advance cold-replays exactly

Remilia's fighter `Advance` at `0x00543210` matches all 58,294 CODE
bytes and the 943 bytes of owned dispatch data at `0x005515C6`.
The complete replay resolves 1,863 relocations and compares all seven
jump tables, three remap arrays, 380 dispatch entries, and 1,905
direct branch edges.

The first divergence was the receiver load at the entry to action
`0x59`. The preceding action `0x58` emits the same instructions when
its later stage-one frames are explicit, and VC7.1 then selects EAX
at the next action entry. A control for the stage before stage one at
the same source position selected ECX. The stage continuations in
`0x5E` and `0x61` correct the next two divergences. After those three
changes, the only remaining differences begin in `0x2F0`, at the
transition from reduced gravity to the descent test. An explicit
preparation phase with no speed update fixes that join and the
instructions through the shared epilogue.

| Cumulative source variant | GPR differences | Width differences | First GPR difference | Relocated byte differences |
| --- | ---: | ---: | --- | ---: |
| Parent at `33d81615` | 1,741 | 3 | `0x00545109` | 45,834 |
| Later stage-one frames in `0x58` | 1,722 | 3 | `0x00545517` | 45,815 |
| Later landing frames in `0x5E` | 1,495 | 2 | `0x005459E5` | 1,610 |
| Later launch frames in `0x61` | 1,203 | 0 | `0x0054F906` | 1,241 |
| Preparation stages in `0x2F0` | 0 | 0 | — | 0 |

The velocity operands in the two `0x58` contact-counter products retain
their parentheses. Removing them reversed the order of the memory operands
in both x87 products and moved their relocations by three bytes. The
complete section still had the same size, and the cold comparison
rejected it.

The local comparison log is
`.analysis/remilia-fighter-advance/whole-function-audit.log`. Replay the
accepted source with:

```sh
scripts/repo-python scripts/replay-exact-units.py --unit remilia-fighter-advance-00543210
```

## 2026-11-24 — Youmu's fighter Advance cold-replays exactly

Youmu's fighter `Advance` at `0x005214B0` matches 46,755 CODE bytes
and the 901 bytes of owned dispatch data starting at `0x0052CB53`.
The 47,656-byte comparison resolves 1,491 relocations and includes
seven jump tables, four remap arrays, 379 dispatch entries, and
1,522 direct branch edges.

The first divergence was the receiver reload at the entry to
action `0x59`. The later stage-one frames in `0x58` fix the same
cross-action join as in Remilia. The rebound and landing frame paths
in `0x59`, `0x5D` and `0x5E` move the first difference to the
completion check in `0x62`. The `0x5D` change temporarily increases
the total byte differences while moving the first divergence into
`0x5E`. Its counterpart in `0x5E` restores the rest of that case.

The input-idle path in `0x62` keeps the previous attack selection. The
ongoing animation path in `0x136` then restores the full size and all
dispatch offsets. The remaining join follows the ground-speed
clamp in `0x201`. Expressing the preparation stages there fixes the
rest of the function through the shared epilogue.

| Cumulative source variant | GPR differences | Width differences | First GPR difference | Relocated byte differences |
| --- | ---: | ---: | --- | ---: |
| Parent at `240ece09` | 2,736 | 5 | `0x0052327A` | 18,391 |
| Later stage-one frames in `0x58` | 2,717 | 5 | `0x005233DE` | 18,372 |
| Later rebound frames in `0x59` | 2,662 | 3 | `0x0052352F` | 18,241 |
| Later landing frames in `0x5D` | 2,867 | 6 | `0x00523688` | 35,637 |
| Later landing frames in `0x5E` | 2,595 | 5 | `0x00523C4E` | 18,250 |
| Idle attack inputs in `0x62` | 2,333 | 3 | `0x00526CDA` | 17,912 |
| Ongoing animation in `0x136` | 686 | 2 | `0x0052904F` | 886 |
| Preparation stages in `0x201` | 0 | 0 | — | 0 |

The local comparison log is
`.analysis/youmu-fighter-advance/whole-function-audit.log`. Replay the
accepted source with:

```sh
scripts/repo-python scripts/replay-exact-units.py --unit youmu-fighter-advance-005214b0
```

## 2026-11-24 — Reimu's fighter Advance cold-replays exactly

Reimu's fighter `Advance` at `0x0045DD70` matches 60,999 CODE bytes
and 1,090 bytes of dispatch data starting at `0x0046CBB7`. The
62,089-byte comparison includes six jump tables, four remap arrays,
and all 1,824 relocations. The unit uses the existing ledger name
`ReimuFighter::AdvanceActionStatesAt0045DD70`.

The first receiver reload differs at the entry to `0x59`. As in
Remilia and Youmu, the later stage-one frames in `0x58` restore it.
Writing the remaining rebound and landing continuations in `0x59`,
`0x5D`, `0x5E`, and `0x61` fixes the early sequence through the
priority-mode action `0x63`.

Pairing the actions by their native jump-table entries exposed eight
separate instruction-sequence differences in `0x258`–`0x25F`.
The original puts the projectile bodies under affirmative stage/frame
guards and resets only when the animation completes. Its two-shot
and six-shot fans write `field318 = 10.0f` for every projectile. The
source also retains the member-first x87 evaluation of the projectile
Y offset and the opening speed scale. Together these changes recover
the full 16,837-instruction layout.

The two matching launch continuations in `0x136` and `0x186` then
restore register allocation. The second aligns the remaining 5,783
register operands and the two instruction widths that were still
moving later action and relocation offsets.

| Cumulative source variant | GPR differences | Width differences | First GPR difference | Relocated byte differences |
| --- | ---: | ---: | --- | ---: |
| Early continuations and eight corrected special actions | 5,834 | 2 | `0x00463B59` | 6,282 |
| Later launch frames in `0x136` | 5,783 | 2 | `0x00463C80` | 6,231 |
| Later launch frames in `0x186` | 0 | 0 | — | 0 |

The local comparison log is
`.analysis/reimu-fighter-advance/whole-function-audit.log`. Replay the
accepted source with:

```sh
scripts/repo-python scripts/replay-exact-units.py --unit reimu-fighter-advance-0045dd70
```

## 2026-11-24 — Sakuya's fighter Advance cold-replays exactly

Sakuya's fighter `Advance` at `0x004AC040` matches all 82,796 CODE
bytes and 1,126 bytes of owned dispatch data at `0x004C03AC`.
The 83,922-byte comparison uses the recorded VC7.1 `/GX` profile
and includes six jump tables, four remap arrays, 543 dispatch
entries, and 2,352 relocations.

The first receiver reload differs at the entry to `0x59`. The
later stage-one frames in `0x58` restore it, as in the other
fighter parents. The rebound and landing continuations in `0x59`,
`0x5D`, `0x5E`, and `0x61` match the early sequence. The next
three joins respond to ongoing animation in `0xCA` and later
animation frames in `0xCB` and `0x130`.

The last three affected actions share a repeat limit of four.
Expressing the stage-eight path at that limit in `0x1F8`, `0x1F9`,
and `0x1FA` restores the stage-eleven tests and the later register
choices. Each of the first two changes moves the first difference
forward and increases the number of mismatched bytes relative to
the build before the three changes. The third restores all offsets.

| Cumulative source variant | GPR differences | Width differences | First GPR difference | Relocated byte differences |
| --- | ---: | ---: | --- | ---: |
| Parent at `b64e6109` | 6,958 | 12 | `0x004ADEFA` | 18,539 |
| Continuations through `0x61` | 6,555 | 10 | `0x004B0691` | 18,058 |
| Also `0xCA` and `0xCB` | 6,399 | 10 | `0x004B14C9` | 17,898 |
| Later frames in `0x130` | 348 | 2 | `0x004B5EDF` | 1,283 |
| Repeat limit in `0x1F8` | 3,340 | 8 | `0x004B636E` | 5,186 |
| Repeat limit in `0x1F9` | 3,198 | 8 | `0x004B67FE` | 13,714 |
| Repeat limit in `0x1FA` | 0 | 0 | — | 0 |

The local comparison log is
`.analysis/sakuya-fighter-advance/whole-function-audit.log`. Replay the
accepted source with:

```sh
scripts/repo-python scripts/replay-exact-units.py --unit sakuya-fighter-advance-004ac040
```


## 2026-11-24 — Reimu's object Advance cold-replays exactly

The native dispatch at `00476AEB` maps actions 800–998 to 66 distinct
entry blocks. Fifteen actions grouped in the partial parent have
separate native bodies. Splitting the groups recovered their differing
effect IDs, limits, and float scales. The entry also decrements
`field082` before returning during hit stop. The 134 remap aliases
share the animation-update default, including actions outside the table.

The VC7.1 `/FAcs` listing compares byte-for-byte with the normal object
and maps 59 jumps to their source statements. Explicit returns after
those statements restore the native direct jumps to the shared
epilogue. In 931 and 932, compound updates of the owner's signed
short at `+0xF24` retain its destination in ESI across `__ftol2`
and recover the original stack frame and saved registers.

The first register divergence in 913 appears after the stage-2 speed
update. Expressing the fade-stage speed hold aligns the movement, then
the active-contact path aligns the subsequent stage-reset guard. The
same pair of joins applies to 927–930 and 940. In 933, the later
startup frames retain the launch velocity. Finally, the in-progress
animation path in 997 restores ECX at the first reload in 998.

| Action 997 comparison | CODE / complete bytes | Relocated byte differences | Action 998 |
| --- | ---: | ---: | --- |
| In-progress animation | 50,915 / 51,378 | 0 | ECX at `00482E6F` |
| Omit only the in-progress arm | 50,912 / 51,375 | 1,203 | EAX at `00482E6F`, 142 register and 5 width differences |

Both builds resolve all 1,152 relocation fields and preserve the 1,273
direct branch destinations and 199 dispatch destinations by instruction.
The omission moves ten relocation fields and 134 action entry offsets.
The accepted cold replay compares the 264-byte table at `00483123`
and the 199-byte remap at `0048322B` along with the CODE extent.

```sh
scripts/repo-python scripts/replay-exact-units.py --unit reimu-object-advance-00476a40
scripts/repo-python .analysis/reimu-object-advance/continue-control.py
```


## 2026-11-24 — Marisa's object Advance cold-replays exactly

The native switch maps actions 800–998 to 75 action bodies and one
default. The cold comparison covers 46,596 CODE bytes, the 304-byte
jump table at `004A7EF4` and the 199-byte remap at `004A8024`. All
1,021 relocations, 1,044 direct branches and 199 action destinations
match.

The first three beam actions each emit 23 segments at fixed positions.
The 812 guard spawns 13 instances of effect `0x3E4` after the optional
counter effect. The assembled call counts resolve a missing call in
the decompiler listing. Action 814 keeps the original signed angle in
ESI across `RecordedRange(0, 40)`. Writing the live angle and random
offset in one expression reproduces that save, the `0x3FC` frame, and
the original epilogue. The member-first x87 loads preserve the
subtraction and comparison directions in each trajectory.

Actions 828–833 make six independent calls to `004A80F0` with the
object in ECX. The callee is now `MarisaObject::UpdateTrackingNode`
and uses the named fighter fields and the real effect-spawn method.
Its 3,935 bytes and 52 relocations match with the typed receiver.

```sh
scripts/repo-python scripts/replay-exact-units.py --unit marisa-object-advance-0049c8f0 --unit auxiliary-actor-update-004a80f0
```


## 2026-11-24 — Yuyuko's fighter Advance cold-replays exactly

`YuyukoFighter::Advance` at `0x00564BE0` covers 61,872 CODE bytes.
The complete extent through the last remap is 62,746 bytes, with
1,438 relocations, 1,575 direct branches and 131 jump words in seven
tables. The five remaps and six singleton comparisons resolve 131
explicit actions. The flat switch lowers to the original dispatch tree.
Actions 0, 2, 4 and 5 reach the nested-frame call at `0x00573D81`.

Two separate landing continuations in `0x5D` and `0x5E` restore the
entry registers at `0x0056762C` and `0x005677E5`. The completed-animation
and frame-zero launch paths in `0x60` and `0x61` share short internal
exits at `0x00567AE4` and `0x00567DBA`. Keeping the later launch frames
in `0x61` restores the EDX reload for `0x62` at `0x00567E3D`. Removing
the copied zero-input arm from `0x62` then restores the EAX result at
`0x00567F14`. This separates the previous action's register effect from
the local effect after the two directional inputs.

Removing only the launch continuation from the final source changes the
reload at `0x00567E3D` to ECX and moves 968 code relocation fields. The
full linked comparison reports 40,118 differing bytes, including the
one-byte size increase. The control is repeatable with
`scripts/repo-python .analysis/yuyuko-fighter-advance/continuation-control.py`
after the cold replay.

Action `0x303` needs three separate counters, each scoped to the pair of
20-shot loops for its countdown branch. Case-scope declaration
permutations leave the first and second counters transposed or move the
first counter past the disp8 limit. Scoping each to its countdown arm
restores `[ebp-0x7c]`, `[ebp-0x80]` and `[ebp-0x84]` and removes the
last 24 differing bytes. The original opponent resets in `0x2F9` and
`0x303`, signed input projections and x87 operand order are preserved.

    scripts/repo-python scripts/replay-exact-units.py --unit yuyuko-fighter-advance-00564be0


## 2026-11-24 — Marisa's fighter Advance cold-replays exactly

`MarisaFighter::Advance` at `0x00486550` covers 50,735 CODE bytes.
The 51,799-byte complete comparison includes 1,683 relocations, 1,645
direct branches, 163 jump words in seven tables, and four remaps. All
468 dispatch values, including the six singleton checks, resolve to the
original entries. Actions 0, 2, 4 and 5 use the shared nested-frame call
at `0x00492B73`.

The former nested-switch parent cold-builds 50,693 CODE bytes and puts
`this` at `[ebp-0x1c]`. One flat switch over the actual action member
restores the compiler's dispatch tree, `this` at `[ebp-0x18]` and the
switch temporary at `[ebp-0x1c]`. The double multiply in action `0x32`
removes a float temporary and recovers the `0x21c` frame. The source
keeps distinct cases for `0x2CE` through `0x2D1` and preserves the
original exits in `0xC8` and `0x130`. The x87 comparison at each
landing site determines whether contact includes equality. Action
`0x2C0` writes height 1600, and `0x2F8` and `0x2F9` reset to 920.

The impact and landing continuations in `0x58`, `0x59`, `0x5D` and
`0x5E` restore the entry phases through `0x5F`. The later launch
frames in `0x61` restore EAX at the entry of `0x62`. The firing paths
in `0x190` and `0x194` then recover the following two groups.
Within `0x208`, the stage-6 continuation before drift starts restores
EAX at `0x0048E364`. Combining the decay guard with a short-circuit
expression leaves EDX at that instruction. The empty floating-point
comparison for positive drift emits an extra comparison and adds
14 CODE bytes.

Removing only the action `0x2BF` firing continuation changes the first
reload at `0x004900AC` from EDX to ECX. It leaves the seven tables and
all relocation positions intact, with 808 instructions with differing registers
and 810 differing bytes through the end of the function. Restoring that
path yields zero differences. Run the two full comparisons with
`scripts/repo-python .analysis/marisa-fighter-advance/firing-control.py`
after cold replay.

    scripts/repo-python scripts/replay-exact-units.py --unit marisa-fighter-advance-00486550
