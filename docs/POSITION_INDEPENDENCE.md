# Position independence in the Windows x86 build

Code and data in the TH075 build should be able to move within the PE
at link time. The linker resolves each reference to its symbol and keeps
the COFF addend for member access. This follows ReC98's definition based
on symbolic references to program data. TH08 tests the same property by
reversing the object order in a second link.
[ReC98 FAQ](https://github.com/nmlgc/rec98.nmlgc.net/blob/master/faq.html)

## Reordered link

The VC7.1 linker used the same 442 COFF inputs in reverse order, including
the supplied read-only data object. The library order and link flags stayed
the same. The experiment has its own response file, executable and map.
The ordinary build remains under `build/program/`.
Both layouts use image base `0x00400000`. Reordering tests internal link
placement at that base.

| Symbol | Ordinary link | Reordered link |
| --- | --- | --- |
| `WinMain` | `0x005A4010` | `0x004488B0` |
| `TitleScene::Render` | `0x005A3BC0` | `0x004494A0` |
| `SoundBank::~SoundBank` | `0x004217F0` | `0x005CC830` |
| `g_GameMainWindowAt00671608` | `0x00627AB0` | `0x006422B4` |
| `g_OptionsMessage0` | `0x00614230` | `0x00611200` |

For each layout, 55,325 relocation fields agreed with the linked symbol
or same-section COFF offset and the stored addend. The check covered 3,669
fields in owned data beyond the function bodies, and all 237 references
to the supplied read-only object. Another 372 fields resolved to local
data without public map entries. Their destinations contained the
corresponding COFF strings or zero-initialized texture cache fields.
All 140 groups of duplicated float literals held the expected values
in read-only storage in both layouts.

The 80-byte keyboard configuration keeps both 40-byte bindings in one
array. Configuration load and save use its base, and input initialization
uses addends of 0 and 40. The keyboard configuration, the two input
mappings and the 3,600-float cosine table own disjoint ranges in each
map. Reordering separated the input mappings from the cosine table
that immediately followed them in the ordinary link.

The original PE import directory confirmed 838 named IAT references.
This caught the audio shutdown import at `0x00657134`. The audio and
event destructors both call `TerminateThread` there. Both units passed
complete cold comparisons after the binding was corrected.
[Import evidence](KNOWLEDGE_BASE.md#windows-link)

An instruction scan of all 1,023 configured code extents found two
unrelocated immediates inside the original image's address ranges. Both
are audio loop lengths or endpoints in `AudioRecord408110.cpp`.

## Runtime check

The Japanese 1.11 executable and both reconstructed layouts used the same
three local archives, with a fresh Wine prefix and isolated Xvfb display
per run. ALSA discarded audio through a null PCM endpoint. With the default
keyboard bindings, Q advanced to character selection, W returned to title,
and Escape selected and confirmed exit. The batch debugger recorded both
title renders, character selection, audio destruction and process exit
for all three runs.

The initial staging omitted the installation's `replay/` directory.
After character confirmation, replay capture tried to create
`replay/replay.tmp` and opened an error dialog. With a writable
`replay/` directory in each run, the original and both reconstructed
layouts loaded the characters and stage and returned from the first
`BattleScene::Render` call.

The first update initially failed in the command-history matcher in both
reconstructed layouts. The native call uses iterator subtraction to
start before the end of the deque. After correcting the source and
checking the three VC7.1 iterator helpers, the original and both
layouts completed 60 consecutive `BattleScene::Update` calls.
[Iterator evidence](KNOWLEDGE_BASE.md#windows-link)

The relocation audit covered 961 unit bodies. Of these, 957 had their
original object owners in both maps. Four matched other map entries
with the same instruction body and compatible relocation operands. The
other 62 configured units had no matching body in linked code after
masking the COFF relocation fields. A whole-image PI claim also requires
evidence for library and startup code outside the configured units.

Local evidence is under `build/program/xvfb-runtime.6WNFjB/`. The
`pi-reordered/` subdirectory has both-layout relocation checks. The
menu and first-battle directories hold the debugger traces.
The `reference-battle-updates/` and `*-battle-updates-fixed/`
directories record the 60-update checks.
