# F922 — Share the original sprite-entry flag view across two complete exact functions

The pinned Japanese TH075 v1.11 original executable independently
confirms that the same borrowed entry address returned by the
`SpriteEntries40CA80::At(index)` call owns an 8-bit
palette flag at **entry+0x28**. In original `0040C590`, the
native `MOVZX ECX,byte ptr [EAX+28h]` is at 0040C602.
The separate original `0040C8C0` performs that same
read at **0040C912**, including the identical 0x28
displacement and the real original return/branch semantics.

This reconciles the two real typed source interfaces rather than
presuming historical C++ owner declarations. F920 had recovered
five fields under a **borrowed, incomplete** `NativeSpriteEntryViewF920`
in one original 340B function. F922 moves that precise
offset-checked partial view to
[`src/TextureEntryBorrowedF922.hpp`](../src/TextureEntryBorrowedF922.hpp)
and shares its **actual byte field `paletteFlagAt28`**
with the independent `SpriteTextures40CA80::GetTexture`
original source. No full record layout, constructor or
unknown metadata meaning is invented; the incomplete view is
never allocated/embedded. All existing actual 340B palette
loads at offsets 0/4/8/12/0x28 remain in one shared type.

The original 0040C8C0 total is **162 callable CODE bytes /
53 x86 / 11 physical original COFF fields**. It checks the
real original global cached texture index and refreshes the
cached palette branch when needed. Changing the field expression
does not alter that observable behavior or invent a helper call.

Only the two actually changed translation units were cold-built
serially with their **own original per-unit pinned VC7.1
profiles**, then compared to whole original callable CODE
and all actual PE relocation offsets, types, addends and
destinations:

| Entire original function | Whole native CODE | Canonical replay |
| --- | ---: | --- |
| TexturePalette40C8C0::Refresh 0040C590 | 340 B | exact |
| SpriteTextures40CA80::GetTexture 0040C8C0 | 162 B | exact |
| **Two affected original units** | **502 B** | **2/2 exact** |

The reproducible scope is:

    scripts/repo-python scripts/replay-exact-units.py \
      --unit texture-palette-refresh-0040c590 \
      --unit texture-resolve-0040c8c0

Actual fresh compiler/PE receipt:
`.analysis/f922-shared-native-texture-entry/cold-both.log`
(ignored local machine research). These are **502
previously accepted**, not newly accepted, native CODE
bytes. No other units or all-unit cold replay were run.
