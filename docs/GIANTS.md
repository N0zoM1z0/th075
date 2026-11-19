# The 22 remaining giants

Every authored function that is not yet exact is the slot-1 `Advance` of one
of the 11 fighter or 11 character-object vtables: the per-frame state machine,
one big `switch (action)`, 28–83 KB each. Thirteen have a complete research
parent in `probes/` that compiles to the original instruction sequence apart
from register choice. The other nine have no complete parent yet.

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

## Complete research parents (measured 2026-11-19)

All thirteen have the original instruction count, frame, stack slots, branch
targets and mnemonics. What remains is register choice and the few
instruction widths that follow from it.

| Original | Character | Size | Parent | GPR debt | Widths | First GPR difference |
| --- | --- | ---: | --- | ---: | ---: | --- |
| 0045DD70 | Reimu fighter | 60,999 | `FighterWhole0045DD70F1183.cpp` | 6,311 | 5 | 0045FDA9 (#2292) |
| 004AC040 | Sakuya fighter | 82,796 | `FighterWhole004AC040F1020.cpp` (`/GX`) | 6,958 | 12 | 004ADEFA (#2180) |
| 005214B0 | Youmu fighter | 46,755 | `FighterWhole005214B0F1040.cpp` | 2,736 | 5 | 0052327A (#2103) |
| 00543210 | Remilia fighter | 58,294 | `FighterWhole00543210F1041.cpp` | 1,741 | 3 | 00545109 (#2198) |
| 004CA6E0 | Sakuya object | 42,511 | `CharacterObjectActions004CA6E0F1222.cpp` | 447 | 12 | 004CCBD7 (#2526) |
| 004EBDA0 | Alice object | 33,293 | `CharacterObjectActionsF572.cpp` | 133 | 0 | 004F344C (#8076) |
| 0050A580 | Patchouli object | 81,539 | `CharacterObjectWhole0050A580F1044.cpp` | 522 | 5 | 00515C0E (#10128) |
| 00536400 | Youmu object | 39,999 | `CharacterObjectActions00536400F1211.cpp` | 913 | 10 | 005392F8 (#3223) |
| 0055AC80 | Remilia object | 28,432 | `CharacterObjectWhole0055AC80F1194.cpp` | 726 | 6 | 0055F711 (#5225) |
| 0057D580 | Yuyuko object | 43,845 | `CharacterObjectActions0057D580F1237.cpp` | 914 | 6 | 00583489 (#6565) |
| 005A1600 | Yukari object | 43,599 | `CharacterObjectActions005A1600F1231.cpp` | 613 | 11 | 005A88A8 (#7965) |
| 005C9CC0 | Suika object | 43,501 | `CharacterObjectActions005C9CC0F1216.cpp` | 935 | 1 | 005D2558 (#9213) |
| 005EB520 | Meiling object | 34,434 | `CharacterObjectWhole005EB520F1207.cpp` (no `/GS`) | 135 | 6 | 005F3904 (#9200) |

The flags are `/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes` unless noted.
Patchouli object's 81,539-byte giant now calls native typed C++
helpers in place of its last random/angle/sound alias methods:
`PatchouliObject::RecordedRange` for 37 compiled native calls,
`Actor::SetPolarVelocity` for 19 calls (including exact float-bit
argument recovery), and `PatchouliObject::PlaySharedSound` for two.
Whole 82,109-byte COFF bodies preserve all 1,449 relocation positions/
types, zero nonrelocation byte changes and its unchanged nonexact
24,643-byte frontier. All 24 `CharacterObject.hpp`-affected exact
units cold-replayed successfully.

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

Remilia object `0055AC80` now defines `RemiliaObject::Advance` on its
real class. Twenty-four random-range, 25 effect-spawn, seven sound and
two shared-sound call sites now use typed C++ members instead of borrowed
receiver aliases. The full 28,868-byte COFF body, all 696 relocation
offsets/types and every nonrelocation byte remain unchanged. This does
not resolve its 726 GPR-role and six instruction-width differences;
all 24 affected exact units cold-replayed successfully.

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
16-byte recorded-action history entries preserved as a bounded borrowed
view. 108 effect spawns, eight shared sounds, eight owner sounds, two
auxiliary and two tracked effect calls use the real Fighter APIs. The
seven gauge-timer calls to 0046D000 retain a provisional receiver ABI
pending cross-character ownership proof. Both complete 40,464-byte
COFF bodies preserve all 938 relocation offsets/types and every
nonrelocation byte. The original 39,999 CODE bytes remain NONEXACT
(913 GPR-role, ten width differences); 24/24 header-affected exact
units replayed successfully.

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

Yuyuko object `0057D580` now defines `YuyukoObject::Advance`, with
66 effect spawns, eight sounds and four camera-shake calls moved from
borrowed owner declarations to shared game interfaces. Both 44,331-byte
research bodies have exactly 1,043 relocation positions/types and zero
nonrelocation byte differences. The 43,845 original CODE bytes remain
nonexact (914 GPR-role differences and six widths); all 24 affected
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

Reimu fighter motion now uses the real float types for the reaction-velocity pair: FighterFrameInfo +0x2C/+0x30 and Actor +0x94/+0x98 are floats, not unsigned integer bit buckets. The 0x46 trajectory now performs ordinary float negation/addition, combat reaction scales the float fields directly, and Fighter initialization writes float zeroes. The full 62,090-byte Reimu fighter COFF remains identical with all 1,824 relocation offsets/types and zero nonrelocation-byte differences. All 462 exact units affected by the shared Actor header cold-replayed 462/462 in 16 bounded batches; the 855-byte projectile Advance remains exact.

YoumuObject's borrowed history record now types its +0x04/+0x08 position fields as floats (xAt04 / yAt08) and assigns them directly to the object's float coordinates. The complete 40,464-byte boss COFF, all 938 relocation offsets/types and every nonrelocation byte remain identical; the view is still non-owning and no exactness credit is claimed.

The signed Fighter::fieldEFA cleanup is now complete across the remaining large callers: Meiling, Suika and Alice object giants replace 87 reinterpret_cast<short&> uses, while Reimu and Remilia fighter fragments replace four opponent-field casts. These 91 sites now use direct short member access and increment. The five complete COFF bodies (34,879 / 43,972 / 33,731 / 62,090 / 59,236 bytes), all 806 / 991 / 682 / 1,824 / 1,863 relocation offsets/types, and every nonrelocation byte remain unchanged. No exact unit depends on these boss-only fragments; all five giant frontiers remain nonexact.


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
