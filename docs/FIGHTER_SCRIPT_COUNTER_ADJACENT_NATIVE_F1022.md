# F1022 — Genuine adjacent fighter script WORD counters, 46/46 complete cold exact

The SHA-pinned Japanese TH075 v1.11 original game
independently confirms TWO adjacent native actor
**16-bit WORD fields at +0xF00 and +0xF02**.
They are separate real script counters, not a
guessed complete fighter structure. Eleven independently
authored complete per-character original reset functions
physically issue MOV WORD accesses to both fields at
these exact owner-relative offsets. Corresponding full
original fighter case code uses the same pair.

The [four-byte borrowed counter window](../src/FighterScriptCounterWindowF1022.hpp)
holds exactly two unsigned short fields. Compile-time
sizeof=4 and second offsetof=2 establish the ABI;
the macro F1022_SCRIPT(actor) only borrows actor+0xF00,
never allocates or asserts the original complete
game fighter layout. Zero-initialization is identical
at machine-code and native memory-width level.

The new source view is used in **11 real C++ translation
units**: base/derived Sakuya actions, and independently
authored Marisa, Reimu, Youmu, Alice, Patchouli,
Remilia, Yuyuko, Yukari, Suika and Meiling
round-reset functions. All real 16-bit cleanup
operations, call order, GPR roles, other script
word owners and actual compiler local symbol
identities remain unchanged.

An initial canonical native exact cold replay
selected five independent reset-source objects:
**5/5 whole original functions exact**. Then the
complete affected 11-object set, including the
otherwise unrelated 35 additional virtual action
functions generated in the same C++ object, was
rebuilt with the canonical VC7.1 compiler and
independent strict pinned original PE/COFF comparator:

| Original affected source group | Original exact whole callables | PREVIOUSLY accepted CODE B |
| --- | ---: | ---: |
| FighterVirtualActionsF159.cpp | **36/36** | **1,957** |
| Ten per-character reset files | **10/10** | **2,815** |
| **All 11 changed native source objects** | **46/46** | **4,772** |

Canonical complete exact receipt:

    Cold replay: 46/46 exact units across 11 objects

This is true unchanged native full-callable x86 bytes,
physical external PE fields and compiler-local COFF
identity, not just equivalent behavior. We did not
change original function extents, accepted matching
metadata or add any whole-original CODE credit.

Source-independent proof of the 11 physical WORD
writes, five-function initial replay and all 46
complete normal VC7.1 replay receipts are under
ignored .analysis/f1022-script-pair/.

**No newly accepted whole original callable CODE B.
No 979-unit mass cold replay.**
