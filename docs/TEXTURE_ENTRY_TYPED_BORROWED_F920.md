# F920 — Recover five typed texture-entry fields in one entire 340B original native leaf

The pinned Japanese TH075 v1.11 native
`TexturePalette40C8C0::Refresh` at **0040C590** is one
independently accepted complete **340-byte / 125-instruction**
original game function with **eleven** physically mapped
original COFF call relocations.

## Read the original fields, not the unproven complete class

The source for this entire authored function already proves that
the entry at `TexturePalette40C8C0::this+8 -> At(index)`
has five meaningful directly accessed original fields:

| Original entry byte offset | Observed native type/usage |
| --- | --- |
| +0 | 8-bit value sent to `BitmapUpload::CopyTo` |
| +4 | Signed 32-bit metadata/width candidate, snapshotted into live local |
| +8 | Signed 32-bit metadata/height candidate, snapshotted into live local |
| +0x0C | Signed 32-bit other metadata, snapshotted into live local |
| +0x28 | 8-bit truth value selecting 256-pixel palette texture vs physical surface |

Names remain explanatory; metadata purpose is not independently
proven. Do not infer a complete or instantiable entry class
from these offsets. The original source `SpriteEntries40CA80::At`
interface remains a borrowed pointer-only view.

`src/TexturePalette40C590.cpp` now declares a
**borrowed partial `NativeSpriteEntryViewF920`**
whose five actual fields have explicitly checked original
physical offsets (0/4/8/12/0x28), with opaque occupied spans
between them. It replaces the old raw `ENTRY_INT` and
`ENTRY_BYTE` offset casts with actual typed field reads.
The constructor, sampler, lock/unlock, copy/upload and
release calls are unchanged, as are the native parameter
and Win32/D3D8 ABI types. No unknown layout is embedded
or allocated as a complete record.

## Full native VC7.1 comparisons and acceptance

A targeted compiler hypothesis matrix tested ten
complete original-shaped VC7.1 source versions:
baseline, five single-field conversions, both width/height,
all three metadata, both byte flags, and all five fields.
Each version compiled an entire 340-B callable function
under the pinned native per-unit flags and each retained
**340 full CODE bytes / 125 native x86 / 11 original call COFF
fields / zero nonrelocation byte differences**.

After adopting the full five-field view into the tracked
source, the canonical acceptance reran a cold build for
**only the affected entire function**, not the whole corpus:

    scripts/repo-python scripts/replay-exact-units.py \
      --unit texture-palette-refresh-0040c590

Result:

    texture-palette-refresh-0040c590: exact; 340 coverage bytes
    Cold replay: 1/1 exact units across 1 objects

The existing canonical manifest checks the eleven
actual PE callee targets, physical source COFF field offsets,
types, zero relocation addends and complete nonrelocation
whole-function equality. The newly typed view is a
source **semantic improvement** to **340 previously accepted
exact native CODE bytes**, not 340 newly counted CODE bytes.

Full one-unit cold replay receipt preserved locally:
`.analysis/f920-texture-entry-typed-cold/whole-340B.log`.
The ten complete compiled C++ candidates/OBJ/PDB, previous
native-PE comparison and research matrix remain in ignored
`.analysis/f920-texture-entry-typed/`.
No other accepted unit was cold-replayed; no whole boss
or afterRET DATA was credited.
