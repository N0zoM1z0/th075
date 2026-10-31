# F919 — Three original short animation counters as a real contiguous tail view

**Target:** pinned Japanese TH075 v1.11 executable. Three
previously **fully accepted byte-exact callable** animation
functions use the same original 16-bit signed counter words at
receiver+0x60, receiver+0x62, receiver+0x64.

The original physical x86 was freshly read, *not* inferred
from the old source implementation:

| Entire original callable native function | Original CODE | Genuine observed operations |
| --- | ---: | --- |
| `0040FAC0` | 52 B | Zero frame+0x64, zero secondary+0x62, write primary+0x60, virtual callback |
| `0040FB00` | 56 B | Write third+0x64, second+0x62, first+0x60, virtual callback |
| `0040FB40` | 43 B | Zero frame+0x64, write secondary+0x62, virtual callback |
| **Three real original functions** | **151 B** | Independent complete x86 bodies |

The original virtual `AnimationState` class has other unknown
fields and is NOT a complete recoverable owner. The
tracked `src/GameLeafHelpers.cpp` now borrows a
separate **six-byte window** at actual offset +0x60,
with three adjacent signed short fields
`primaryAction`, `secondaryAction`, `animationFrame`.
The 6-byte size is checked by the original VC7.1 compiler;
the view is never instantiated or embedded as a fabricated
complete object. The three unchanged original method
signatures, ordering, virtual dispatch and side effects are
preserved; no fake locals, manual assembly or target bytes.

All three affected original callable functions were **freshly
cold-built under the pinned per-unit VC7.1 profiles** and
canonical replay checked each entire original 52/56/43-byte
native extent. The results were:

    animation-reset-primary-counters: exact; 52 coverage bytes
    animation-set-three-counters: exact; 56 coverage bytes
    animation-reset-secondary-counter: exact; 43 coverage bytes
    Cold replay: 3/3 exact units across 1 objects

The evidence is retained locally in
`.analysis/f919-animation-typed-counters/affected-3-cold-replay.log`.
The other six functions from this source file are untouched,
as are the existing exact units' compiler options, ABI,
manifest and relocation mappings. **151 already-accepted
native CODE bytes remain exact, not 151 newly claimed bytes**.
No full 979-unit replay.
