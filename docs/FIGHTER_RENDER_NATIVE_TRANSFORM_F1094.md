# F1094 — Native 36-byte fighter render transform and position borrows, two whole functions still exact

The pinned Japanese TH075 1.11 original has independently accepted
complete `FighterRender453F70::Render` at `00453F70` (**2,246 native
CODE B**) and `EffectPattern44E930::Render` at `0044E930` (**2,297
CODE B**), compiled in one `src/ActorEffectDrawing.cpp` translation
unit. Both remain exact under the complete native CODE and COFF checks.

## Physical original actor fields, not an invented owner

The original fighter's **X and Y position float pair** occupies
actor+0x44/+0x48. The new source uses the independently verified
borrowed `F1037_POSITION(this).xPosition/yPosition` for the actual
four game rendering and history writes/reads, while preserving
native camera-centering and true `AppendElement` pointer/argument order.
This is the same real physical view already established in
original accepted battle-frame functions, not a synthetic local.

Nine adjacent native actor transform floats form one *borrow-only*
**36-byte window at actor+0x1C..+0x3F**. The new
`FighterRenderTransformWindowF1094` names the physically used
fields: scale X/Y/Z (+0x1C/20/24), rotation X/Y/Z (+0x28/2C/30)
and origin/pivot X/Y/Z (+0x34/38/3C). These are actually passed
to the source's original `SpriteTransform::ScaleQuad` and
`RotateQuad` methods in the native argument order, with original
signed-facing scale and vertex adjustments intact. `sizeof` and
`offsetof` static constraints ensure the 36B extent and native
rotation/pivot offsets on pinned 32-bit VC7.1.

This view is **never allocated or embedded** as a guessed original
fighter class layout. It describes only existing observed scalar
storage, and the intervening +0x40 flag and +0x44 actual position
stay independently owned. Source preserves original pixel-shader,
quad-transform, model camera, active-frame, particle-history,
blend/filter and draw behavior. No artificial calls, stack pads,
forced registers or copied target machine bytes were introduced.

## Strict complete native replay

There were **two independent complete-object cold builds** using
the pinned original VC7.1 compiler profile: first replacing
actual fighter X/Y coordinate reads with the F1037 borrowed
view, then replacing all used transform float offsets with this
new 36B F1094 typed window. Both builds replayed **both complete
original callables**, including actual physical nonlocal COFF
relocation identities, rather than cropping a single render branch.

| Full original game callable | Original accepted CODE B | Cold result |
| --- | ---: | --- |
| `fighter-render-00453f70` | **2,246** | **exact** |
| `effect-render-pattern08-0044e930` | **2,297** | **exact** |
| **One affected complete source object** | **4,543** | **2/2 exact** |

Reproduce ONLY these two affected entire functions:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit fighter-render-00453f70 \
        --unit effect-render-pattern08-0044e930

These are **previously accepted 4,543 original native CODE B**,
not new exact coverage. Baseline original-shaped C++ and strict
cold-build receipts are retained under ignored
`.analysis/f1094-render-actor-position/` and standard replay output.
No all-979-function replay, modified original EXE or relaxed COFF
matching criteria.
