# F925 — One observed 44-byte element and +0x4C mode in two whole texture allocators

The pinned Japanese TH075 v1.11 original has two independently
reviewed authored **whole callable game functions**:
`0040B000` shared-texture allocation, **261 B/79 x86/11
physical PE relocation fields**, and `0040B110` texture slot
allocation, **184 B/56 x86/8 physical PE fields**.

Independent original native x86, not a remembered class definition,
shows both real functions initialize/read a **BYTE** field
`this+0x4C`:

- `0040B033` and `0040B143` store the actual caller-supplied mode.
- The corresponding generated/native predicates repeatedly load
  the same signedness-neutral 8-bit mode, including the mode-0x18
  check and assignment of 0x10.
- Both methods construct and release one original witnessed
  **44-byte value** through the original texture-element
  ctor/dtor. Its internal 11-word contents have NOT been
  independently attributed to historically named fields.

Previously `TextureSharedF770.cpp` and
`TextureSlotsF769.cpp` had parallel copies of the same
`NativeTextureElementF769` class declaration with a
separate size assertion each, and each read mode through
a raw independent byte-offset cast.

The shared borrowed header
[`src/TextureManagerBorrowedF925.hpp`](../src/TextureManagerBorrowedF925.hpp)
reconciles them into a single genuinely used 44-byte
original value declaration and a separate **borrowed
receiver window** describing only the observed 8-bit
mode at offset +0x4C. This avoids inventing a complete
historical TextureManager layout. Both original code
paths still call the same real vector Assign, At,
graphics Create16BitTexture, constructor and
destructor targets. The borrowed mode view is not
allocated or embedded as a complete owner.

After this real source change the canonical checker
cold-built and compared ONLY the two changed complete
original units under their respective pinned compiler
profiles, including every physical original
zero-addend PE/COFF field:

| Original complete native function | Original CODE | Canonical whole replay |
| --- | ---: | --- |
| AllocateSharedTextures at 0040B000 | 261 B | exact |
| AllocateTextureSlots at 0040B110 | 184 B | exact |
| **Only affected original functions** | **445 B** | **2/2 exact** |

Reproduce:

    scripts/repo-python scripts/replay-exact-units.py \
      --unit texture-manager-allocate-shared-native-0040b000 \
      --unit texture-manager-allocate-slots-native-0040b110

The actual cold compiler/native original PE receipt is retained
under ignored
`.analysis/f925-texture-shared-type/two-whole-cold-replays.log`.
The resulting **445 native bytes were already accepted**
exact before F925; there is **no new whole exact function credit,
no altered source symbols/matched PE records**, and no
979-unit cold replay.
