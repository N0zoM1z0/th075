# F1060 — Physical native Combo HUD 16B window: four full game callables exact

Pinned Japanese TH075 1.11 original `ComboCounterF173` has a real
native 59B complete constructor at `0043D490` and a separate 154B
complete `UpdateComboCounter` at `0043D4D0`. Source had unrelated
raw offset casts for values which original native MOV and x87
instructions demonstrate form a single contiguous **16-byte borrowed
window starting at the HUD object+4**, with physical fields:

| Original owner offset | Physical observed value | Source window field |
| --- | --- | --- |
| `+0x04` | native 16-bit signed combo count | `countAt04` |
| `+0x06` | native 16-bit signed damage/score | `damageAt06` |
| `+0x08` | native 16-bit signed extra ratio | `ratioAt08` |
| `+0x0A` | native unsigned opacity byte | `opacityAt0A` |
| `+0x0B` | native signed side byte | `sideAt0B` |
| `+0x0C` | native 16-bit signed hold timer | `holdAt0C` |
| `+0x0E` | native 16-bit signed animation phase | `phaseAt0E` |
| `+0x10` | native 32-bit float vertical position | `verticalAt10` |

The real HUD texture pointer at native object+0x00 is *outside*
the borrowed view and remains a genuine separate owner field. The
`ComboHudWindowF1060` is never allocated, embedded as a proposed
original class prefix or used to invent a historical full owner
layout; source simply borrows the actual physically present fields
through the observed `+4` offset. Compile-time `sizeof` / `offsetof`
assertions enforce the true 16-byte window boundaries and alpha/side
byte overlap boundary. The original class's actual 32-bit architecture
and signedness are preserved.

The new source replaces the constructor and updater's genuine repeated
casts by ordinary member reads/writes of this view. It preserves the
native `CameraSineAt0040D940` call and its original float scaling,
native comparison/branch order, game-visible counter and opacity
behavior. It adds no synthetic runtime calls, fake locals, patched
machine code, additional original game functions or speculative
texture ownership.

## Strict pinned VC7.1 native evidence

The one affected `src/RoundEndHudF173.cpp` translation unit was
cold-compiled under the real original VC7.1 matching flags, then
all **four** of that unit's complete original game callables and
physical COFF relocations independently compared to pinned TH075:

| Complete native whole function | Previously accepted CODE B | Cold exact |
| --- | ---: | --- |
| `battle-enter-round-end-0043cdb0` | 599 | exact |
| `progress-increment-mode-counter-0043d360` | 66 | exact |
| `hud-combo-constructor-0043d490` | 59 | exact |
| `hud-update-combo-counter-0043d4d0` | 154 | exact |
| **All affected original callables** | **878** | **4/4 exact** |

Reproduce only the one affected object, not all 979 native exact units:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-enter-round-end-0043cdb0 \
        --unit progress-increment-mode-counter-0043d360 \
        --unit hud-combo-constructor-0043d490 \
        --unit hud-update-combo-counter-0043d4d0

**No new credited original exact CODE bytes or new exact whole
functions** were added; the already-accepted 878B remain byte-exact
with strict COFF identities. No mass cold replay or original PE edits.
