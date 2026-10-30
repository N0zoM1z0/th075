# F760 — original R016 audio archive queue, complete 283-byte cold-exact reconstruction

**One independently reviewed authored entire game function `00407B80..00407C9A`
now byte-exact:** 283 native CODE bytes, 76 x86 machine instructions and
27 genuine physically typed zero-addend PE/COFF relocations. The pinned
original is the user's Japanese TH075 v1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This result is a complete callable function, unlike C8–CE internal fighter
cases; do not double-count its original library callees or EH support bytes.

## Actual original semantics, not an artificial ABI

The original `cdecl` function accepts a filename, playback mode and archive
name; it has `RET` and an authentic MSVC `/GX` `FS:[0]` exception frame.
The real audio vector is the shared owner at `006713A0`, and the queued
value is the **64-byte VC7.1 record** already established by original
file-queue `00407A50` (F758), with its used playback-mode DWORD at `+0x28`.
Natural source: [`AudioQueueArchiveF760.cpp`](../src/AudioQueueArchiveF760.cpp).

- Before the local record is constructed, check the shared vector size
  using actual `004094B0`, and pop back through `004096A0` when it is at
  least two entries. Then find the original archive context through the
  existing independently accepted `ResourceLookup::FindByName` at `0041CF00`
  using the **actual borrowed archive-name data at `006577AC`**, and seek
  the filename using the independently exact `0041D750` thiscall.
- Store its returned file handle at original `EBP−0x10`. If it is
  `INVALID_HANDLE_VALUE`, skip creation and return without a record
  destructor. The original compiler emits `PUSH filename; PUSH archive name;
  CALL resource lookup; ADD ESP,4; MOV ECX,EAX; CALL archive seek` as
  a *natural nested C++ call expression*; no incorrect callee ABI,
  manually manipulated stack or assembly is necessary.
- For valid handles, construct the real 64-byte local record at
  `EBP−0x54` through original `00409290`, set true MSVC EH state zero,
  and append it to the vector at `006713A0` using `004095C0`.
- Copy the real playback-mode argument into the original mode temporary
  at `EBP−0x58`. Modes 0/1/2 store 0/1/1 into the queued record's
  `+0x28` mode field, using actual Back at `004094F0`; mode 2 also calls
  `00408900` to read archive loop points with the filename and archive name.
  All three modes finally call original `00408390` on the last record
  with `(filename, 0x100000, archiveName)`.
- Terminate the real scope with record destructor `004092F0` and restore
  the original exception chain. Source does not instantiate a guessed
  full archive manager or alter Windows error semantics.

The original actor names, hidden record field meanings and full registry
layout remain provisional. Source declares only observed borrowed interfaces.
It shares the already proven native 16-DWORD record envelope and uses
no synthetic padding, fake return, `#ifdef` alternate implementation,
patches or original executable byte arrays.

## Original extent and complete physical COFF proof

The original native decoded body has **76 contiguous x86 instructions**
ending at the original `RET`, consuming **all 283 CODE bytes**; the
freshly emitted VC7.1 C++ object has identical whole-code length and
**175/175 nonrelocation bytes** equal to the original. All **27**
physical relocation fields have the original instruction owner offset,
`REL32` or `DIR32` type, zero-addend source COFF symbol and actual
original PE resolved destination. Representative actual destinations:

| Original game role | Original PE address |
| --- | --- |
| Native EH handler and `FS:[0]` saved chain | `00654E1E` and `__except_list` |
| Shared vector and Size/Pop/Push/Back | `006713A0`; `004094B0`, `004096A0`, `004095C0`, `004094F0` |
| Borrowed archive-name constant | `006577AC` |
| Independent actual archive lookup/seek | `0041CF00`, `0041D750` |
| Audio record constructor/destructor | `00409290`, `004092F0` |
| Archive loop points and stream opening | `00408900`, `00408390` |

All 27 individual typed symbol/PE/offset bindings are in
[`config/match-units.toml`](../config/match-units.toml) under unit
`audio-stream-queue-archive-entry-00407b80`. The only cold replay was
of **this newly affected complete unit**:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit audio-stream-queue-archive-entry-00407b80
# audio-stream-queue-archive-entry-00407b80: exact; 283 coverage bytes
# Cold replay: 1/1 exact units across 1 objects
```

Formal exact authored tally rises **970→971 whole functions**, and
**864,961→865,244 original CODE bytes** (**43.84%** reviewed,
**43.76%** conservative). This leaves **33 complete authored original
functions unmatched: 22 large and 11 small/medium (6,405 CODE bytes)**.
The 95 independently unresolved-origin functions remain uncredited.
No global cold replay was performed; the 98% goal remains unmet.
