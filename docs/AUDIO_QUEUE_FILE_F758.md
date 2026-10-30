# F758 — original R016 audio file queue: 289-byte complete cold-exact reconstruction

**Accepted exact authored game CODE: one original whole function at
`00407A50..00407B70`, 289 bytes, 77 x86 instructions and 26 authentic
typed, zero-addend COFF fields.** Source:
[`AudioQueueFileF758.cpp`](../src/AudioQueueFileF758.cpp). The target is the
user-supplied Japanese TH075 v1.11 original PE (SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`).
Authored origin is independently established by R016; historical
AudioStream owner/method names remain provisional.

## Complete original game behavior

The original function is `cdecl`, with two incoming arguments (filename
and playback mode), a normal `RET`, and a **real MSVC `/GX` exception
chain** for the local audio record constructor/destructor.

- Construct one original **64-byte stack audio record** via `00409290`.
  Use the shared queue at `006713A0`: check size through `004094B0`
  and, if at least two entries are present, pop the last through `004096A0`.
- Use Win32 imported `CreateFileA` at `[00657130]` with genuine
  `GENERIC_READ`, `OPEN_EXISTING` and `FILE_ATTRIBUTE_NORMAL` flags.
  If the handle is not `INVALID_HANDLE_VALUE`, close it via imported
  `CloseHandle` at `[00657138]` and append the constructed record via
  `004095C0`.
- Select playback mode from the actual second argument: modes 0 and 1
  assign the actual DWORD at record **`+0x28`**; mode 2 assigns 1 and
  invokes actual `00408670` file loop-point parsing. Each mode accesses
  the shared record through the native `Back()` callee `004094F0`.
- Open the queued record through original `00408110` with the authentic
  `0x100000` argument. Always end the constructed record's lifetime
  with native `004092F0`, restoring the native `FS:[0]` chain.

No target-only fault handling, invented extra behavior, CRT/OS callee CODE
credit, after-RET DATA credit or duplicate compiler EH carrier credit was
added. The source defines only a minimally sufficient observed record
storage envelope; unknown private field semantics and whole registry
layouts are not claimed.

## Correcting a genuine earlier source hypothesis

An initial complete natural C++ candidate emitted **289 bytes, 77 x86 and
26 original relocation positions**, but matched only **177/185 native
nonrelocation bytes**. It had `sub esp,0x50`, record at `EBP−0x54`,
file handle at `EBP−0x58` and mode switch temporary at `EBP−0x5C`.
The native actually uses `sub esp,0x4C`, record **`EBP−0x54`**,
handle **`EBP−0x10`** and switch temporary **`EBP−0x58`**.

This was NOT solved by faking stack padding or changing the target.
The original local record was **64 bytes, not the previously assumed
68 bytes**. A real `HANDLE` declared in the outer function scope, with
the 64-byte record constructed in an inner lexical scope, naturally
causes VC7.1 to place all three source variables in the original slots.
Recompiling the entire source with these legitimate lifetimes yields
**185/185** original nonfield bytes.

We separately tested whole-function 64/68/72/76-byte storage envelopes,
outer and inner record lifetimes, handle const/volatile and other
meaningful lexical models. The source sizes and stack-slot outcomes
were directly decoded from each freshly built COFF object. Of note:
a 64-byte local record represented as a **BYTE array** triggered native
VC7.1 `/GS` stack-cookie instrumentation **absent from this original
function** (305 emitted bytes/28 fields). The accepted source uses an
opaque **DWORD-word storage envelope** of 64 bytes; this matches native
stack allocation and does **not** pretend to have proven the meaning
of the unreferenced record fields. It exposes the one physically used
playback-mode DWORD at original `+0x28`.

## Full original PE/COFF evidence

All 26 relocations have the precise original instruction-field offsets,
COFF types, zero addends, original source symbols and original PE
resolved destinations; they are listed individually under unit
`audio-stream-queue-file-00407a50` in
[`config/match-units.toml`](../config/match-units.toml).

| Actual original field offsets | Native PE destination | Type |
| --- | --- | --- |
| `+06` | `00654E0C` exception handler | DIR32 |
| `+0C,+14,+119` | `__except_list` / `FS:[0]` | DIR32 |
| `+1F,+10F` | `00409290` constructor; `004092F0` destructor | REL32 |
| `+2B,+3A,+7B,+9F,+B2,+C5,+DA,+F4` | `006713A0` shared queue | DIR32 |
| `+30,+3F,+80` | `004094B0` size, `004096A0` pop, `004095C0` append | REL32 |
| `+5B,+72` | `00657130` CreateFileA IAT, `00657138` CloseHandle IAT | DIR32 |
| `+A4,+B7,+CA,+DF,+F9` | `004094F0` queue back access | REL32 |
| `+E6,+100` | `00408670` loop point, `00408110` record open | REL32 |

The complete pinned original **289/289 CODE**, **77/77 x86** and
**26/26 physical relocations** were compared, not an internal fragment.
Canonical acceptance rebuilt only this newly authored unit:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit audio-stream-queue-file-00407a50
# audio-stream-queue-file-00407a50: exact; 289 coverage bytes
# Cold replay: 1/1 exact units across 1 objects
```

Official authored complete-function ledger after F758:
**970 exact / 864,961 original CODE bytes, 43.82% reviewed and
43.75% conservative**, with **22 still-unmatched giant originals
and 12 smaller originals**. The 98% authored-byte target remains
incomplete, and no all-unit cold replay was run.
