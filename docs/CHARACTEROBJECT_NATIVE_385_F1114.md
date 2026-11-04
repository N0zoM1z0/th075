# F1114 — Original 0x385 random scale and stage-3 retry: 557B/114 x86, all native widths and PE fields

**Historical F1114 checkpoint:** current one-parent source additionally recovers [F1115 original 0x386](CHARACTEROBJECT_NATIVE_386_F1115.md). Native 385 114/114 widths and 10/10 real PE destinations remain verified; the 67-case/69,031B partial parent dimensions below are the earlier snapshot.

Pinned Japanese TH075 1.11 has ONE original 81,539-byte `CharacterObject::Advance` at `0050A580` with 17,435 x86 and genuine 567B afterRET sparse-switch DATA. This change reconstructs physical native action **`0x385` at `0051AFF0..0051B21D`, 557 original CODE B /114 native x86**, as a real inner C++ case. It is **not an independently exact original callable**.

Original `0x385` checks signed parent+0x3A0 loss, expires via `0045B830`, increments signed +0x80 countdown when collision/status+0x7C==6 and clears the status, and at initial stage/frame (0,0) performs real `0040FBB0` motion reset, sets signed +0x80 to 1, +0xD8 zero, X/Y scale to **1.0f/2.0f**, all four alpha bytes 0xFF and orientation+0x30 **15.0f**.

At stage **2**, the game reads `RandomBoundaryAt00455580(0,6)`, converts it through native signed `FILD`, multiplies by the **real 006590B4 global**, adds **00659094**, stores X scale, then derives Y scale from genuine X scale plus **0065747C**. Stage **above 2** independently multiplies X scale by native **00659240**. On animation completion `0040FA30` it expires with `0045B830`; at stage 3/frame zero, signed +0xD8 retries up to **9** using real `0040FB40(2)`, otherwise sets final scale to **1.8f/1.0f**.

The entire current original-shaped one-switch C++ parent was freshly compiled under pinned normal VC7.1 and its 0x385 interval was independently compared with the original Japanese executable by physical native x86 ordinal, COFF field offset, relocation kind and original PE-calculated target, plus nonrelocated scalar immediates.

| Real original 0x385 property | Actual result |
| --- | ---: |
| Original inner CODE B and generated C++ inner CODE B | **557 /557** |
| Original x86 mnemonics | **114/114** |
| Original GPR roles | **114/114** |
| Original instruction widths | **114/114** |
| Original physical PE external call/global fields | **10/10** |
| Native nonrelocated scalar-immediate values | **26/26** |

The live giant `scripts/verify-characterobject-current-recovered-f1068.py` now checks **67 strict source-authored original inner cases** representing **64,239 native original CODE B /13,777 original x86**; all **13,777 mnemonic/GPR positions**, **1,042 original physical PE fields**, **2,539 scalar-immediate positions**, 92 true afterRET DIR32 label partitions and 199 native sparse-map bytes match the original. Another seven source-backed original cases remain provisional due to GPR lifetime debt.

Current partial C++ emits **69,031 CODE B /14,773 x86** versus full original **81,539B /17,435 x86**. The source still has different real stack/frame/branch geometry and missing game states; **whole original callable NONEXACT, zero newly accepted exact original CODE bytes**.

Reproduce only the affected whole partial game source:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Normal VC7.1 C++/COFF/PDB, original PE field and native scalar receipts are stored under ignored `.analysis/f1114-native385/` and `.analysis/f1068-boss-live-all-native/`; no mass exact-unit cold replay.
