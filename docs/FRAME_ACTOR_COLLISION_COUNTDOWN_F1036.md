# F1036 — Native paired fighter collision countdown retained across eight exact frame functions

The pinned Japanese TH075 v1.11 original frame control has two
adjacent signed 16-bit actor fields at physical offsets **+0x3B8**
and **+0x3BA**, established by the complete real native update/actor
guard routines. `+0x3B8` is the active collision hold countdown;
`+0x3BA` receives the previous countdown before `+0x3B8` is
conditionally decremented. Both are actual, used fields, not padding.

The frame updater's two real actors at scene offsets +0x44/+0x48
copy the two counters independently; both `FrameActor::AdvanceGuardedState`
and `AdvancePosition` test the borrowed other actor's current +0x3B8
counter. Before this change, these references used identical raw
`FIELD(short, actor, absoluteOffset)` casts, with no source-visible
relationship between the adjacent native WORDs.

`FrameActorCollisionCountdownF1036` is now a *borrowed 4-byte window*
of these original two physically observed values. The caller computes
its receiver by adding the observed +0x3B8 base offset to the actual
actor pointer. The new structure is used only through this borrowed
pointer and is **not** assumed to be a complete actor class or
instantiated as an owning member. Static size/offset assertions protect
the signed two-WORD native boundary. This refactoring preserves the
original exact function's observable sequence and code generation.

All exact units in the **same affected `src/BattleFrame.cpp` object**
were cold-built once and re-compared in full, including the 859B
`BattleFrame::UpdateFrame` and 289B `FrameActor::AdvancePosition`.
The targeted source set was:

| Complete native unit | Accepted CODE B |
| --- | ---: |
| `battle-frame-update` | 859 |
| `battle-frame-present` | 16 |
| `battle-frame-resolve-round-end-mode` | 55 |
| `battle-frame-update-player-counters` | 179 |
| `frame-actor-advance-guarded-state` | 132 |
| `frame-actor-advance-position` | 289 |
| `frame-actor-check-horizontal-limits` | 133 |
| `frame-actor-choose-action` | 304 |

**8/8 entire original callables remain exact across one cold source
object, preserving 1,967/1,967 previously accepted CODE bytes.**
Replay each of these eight units, not the entire 979-unit corpus,
whenever the shared object source is further edited. No relocation
manifest or original byte was changed; no new native CODE credit was
claimed. This does not settle the remaining 25 nonexact functions.
