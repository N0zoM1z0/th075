# F755 — original 00407270 audio client destructor, complete cold-exact source

**Accepted: one independently R015-authored entire game function, 292 CODE bytes,
82 original x86 instructions and 24 genuine zero-addend typed COFF relocation
fields.** The attested target is the user-supplied Japanese TH075 v1.11 PE,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This follows the original 004071C0 AudioStream constructor accepted at F753.
Neither the historical `AudioStream::ReleaseClient` name nor the full private
AudioStream layout has been independently established.

## Recovered original lifetime and ABI

The full original at `00407270..00407393` is a member destructor-like
`thiscall` (`RET`) with MSVC `/GX` frame and `FS:[0]` unwind cleanup. Its
native `this+0` member has the **16-byte VC7 vector storage**, consistent
with original constructor `004071C0` and the vector ctor/dtor/size/index
callees at `00409350`, `00409380`, `004093A0` and `00409430`.

Natural source in [`src/AudioStreamReleaseF755.cpp`](../src/AudioStreamReleaseF755.cpp)
performs the observed game policies in native order:

1. Decrement shared client count `[00671388]`; only on the last client,
   set the worker termination byte `[0067138E]` to zero, wait on worker
   handle `[00671398]`, close shared handles `[00671394]` and `[00671398]`,
   clear both handles, and invoke original `00409740` with the global
   resource at `006713A0`. Independent R077 identifies the callee as
   **VC7 deque destructor/library code**, not separately authored game CODE.
2. For each element in the native vector, if its COM buffer pointer is not
   null, call `IDirectSoundBuffer8::Stop` through vtable `+0x48`, then
   `Release` through vtable `+8`, then set the same slot to null. The
   native source calls `At(index)` **four times**; they are not collapsed
   into one cached pointer in the native CODE.
3. Call the actual vector clear (`00409490`), followed by the native
   embedded vector destructor (`00409380`) via normal C++ member lifetime,
   and restore the original MSVC exception list on return.

The native shared-client destructor's own code is **not** the VC7 or Windows
callee implementations. We credit its original 292-byte authored policy only.
The source declares a borrowed global view rather than instantiating or
pretending to know the complete original audio collection type.

## Target-independent source constraints, failures and correction

The first complete `/Od /Ob0 /Gy /GR- /GX /GS /Zi` probe emitted
292 bytes/82 x86 with 24 physical COFF fields, but matched only
**185/196** original nonrelocation bytes. Assigning two COM element
values into explicit source local pointers altered actual VC7.1 stack-slot
and register lifetimes at 11 machine bytes. Calling `At(index)->Stop()`
and `At(index)->Release()` directly instead reproduces the original
compiler-generated temporaries **without extra artificial locals**.

Changing the borrowed global `00409740` interface to an explicit C++
`~GlobalAudioBuffersF755()` invocation is also a useful *negative* control:
it emitted **294 bytes**, even though prior R077 analysis supports the
callee's STL destructor role. Consequently the accepted source uses a
meaningfully named borrowed global cleanup method, and the historical
exact full global object type remains **unproven**. No fake destructor,
post-RET padding, assembly, target-byte insertion or code cropping was used.

## Whole original PE/COFF exact evidence

Original and freshly generated source each contain **292 CODE bytes / 82 x86
instructions**. The native original independently provides 24 physical
relocations, not inferred solely from a decompile:

| Original CODE offsets | Kind | Original PE target / role |
| --- | --- | --- |
| `+06` | DIR32 | `00654DFA` native compiler EH handler pointer |
| `+0C,+14,+11C` | DIR32 | `__except_list` / `FS:[0]` source fields |
| `+26,+2E` | DIR32 | `00671388` refcount |
| `+36` | DIR32 | `0067138E` running flag |
| `+3F,+58,+6F` | DIR32 | `00671398` worker handle |
| `+46` | DIR32 | `00657134` WaitForSingleObject IAT |
| `+4C,+65` | DIR32 | `00671394` other handle |
| `+53,+5F` | DIR32 | `00657138` CloseHandle IAT |
| `+78` | DIR32 | `006713A0` global collection |
| `+7D` | REL32 | `00409740` VC7 deque destructor |
| `+97` | REL32 | `004093A0` vector Size |
| `+A8,+B9,+D6,+F3` | REL32 | `00409430` vector indexed element |
| `+103` | REL32 | `00409490` vector Clear |
| `+112` | REL32 | `00409380` vector destructor |

For **all 24**, the native original PE absolute/relative destination,
typed COFF relocation symbol, offset and zero addend were checked against
the new compiler object, not copied from an old checkpoint. All **196/196
nonrelocated original bytes** are identical, and the full comparison
including physical relocation ownership is **exact**.

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit audio-stream-client-release-00407270
# audio-stream-client-release-00407270: exact; 292 coverage bytes
# Cold replay: 1/1 exact units across 1 objects.
```

No all-unit replay was run. Associated separate exception support carriers
were not counted again as authored game CODE, and no independent EH carrier
exactness claim is made here. This raises canonical whole original authored
coverage from **968 to 969 functions** and from **864,380 to 864,672
original CODE bytes**, reviewed **43.81%**, conservative **43.73%**;
original-authored pending is now **35** whole functions (**22 giants + 13
non-giants**). The 98% goal is still incomplete.
