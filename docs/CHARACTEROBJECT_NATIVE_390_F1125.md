# F1125 — Actual original 0x390: two polar velocity calls, atan2 and three-channel fade; 38F return width restored

**Historical F1125 checkpoint:** the current C++ parent also restores [F1128 original 0x392/0x393 and provisional 0x391](CHARACTEROBJECT_NATIVE_391_392_393_F1128.md), so 0x390 now has its original 212/212 **native instruction widths** including the 5B tail JMP. Earlier 211/212 widths and 77-case/76,322B partial-source dimensions below were true of F1125, not the later full-parent state.

Original SHA-pinned Japanese TH075 v1.11 contains ONE authored `CharacterObject::Advance` at `0050A580`: **81,539 original whole CODE B /17,435 native x86** and 567 separately owned afterRET switch DATA bytes. F1125 restores its actual physical native game-state interior **`0x390` at `0051CB4A..0051CF28`, 990 original CODE B /212 native x86** inside the still-NONEXACT one-switch C++ parent. It is not an independent original callable or newly accepted exact CODE.

Original 0x390 first checks parent+0x3A0 signed health, then at stage/frame zero resets motion through authentic `0040FBB0`, native collision countdown, status and signed +0xD8. It invokes real `0040FB70` with **unaltered actor+0xC8 DWORD angle** and a float `float(+0xD8)*006590B4 + 006592A4`, sets scale X/Y to 0.1f, alpha bytes to 0xFF, computes actual orientation+0x30 via real **`00483300` atan2(Yvelocity,Xvelocity)/00657828**. After incrementing signed +0xD8, own stages below two repeat the native `0040FB70` angle/motion call and grow actual X/Y scales through the real `0065747C` threshold and `006590B4` step.

On collision status nonzero in stage one, original `0040FB40(2)` resets scales to **4.0f**, zeroes both native velocities and exits. Otherwise it moves signed-facing X and subtracts Y speed, checks four truly native world bounds using X **0065925C/00659258** and Y **00657884/0065924C**, then for stages above one fades three unsigned alpha channels by 25 and both scales by real **00659454**. An underflow sets alpha zero and expires through original `0045B830`. The authentic `0040FA30` action-completion test also expires.

The first ordinary C++ source correctly emitted all **212 original native mnemonics and GPR roles**, but an unnecessary separate terminal `return` emitted a 213th JMP. Using the natural common completion return reproduces the original **212 x86** while retaining real gameplay. Its last original JMP is **5 bytes** to the giant's common tail; the incomplete selected whole C++ still emits a **2B** short JMP. This is explicitly tracked as **211/212 native width matches**, not falsely reported byte-exact; branch/stack geometry remains incomplete.

An important independent cross-state result: restoring original 0x390 increased the genuine following-code span enough that **previous original `0x38F` automatically changed its terminal JMP from wrong 2B to original 5B** without a synthetic branch or manual padding. The selected 0x38F now has all **32/32 original x86 instruction WIDTHS** matching, alongside its original 32 mnemonics/GPR and 3 physical PE external fields. That changes the previously documented F1123 checkpoint, which was historically correct at its own earlier source size.

| Genuine original 0x390 evidence | Selected whole C++ source |
| --- | ---: |
| Native original inner CODE B/x86 | **990B /212** |
| Generated partial C++ inner CODE B/x86 | **987B /212** |
| Original ordered mnemonics and GPR roles | **212/212 each** |
| Original native instruction widths | **211/212** (one terminal JMP) |
| Physically original PE REL32/DIR32 fields | **24/24** |
| Original nonrelocated scalar immediates | **33/33** |
| Original atan2 and both actual polar velocity calls | verified at original physical ordinals |

The tracked one-parent `scripts/verify-characterobject-current-recovered-f1068.py` cold compiles ONLY the current selected partial giant, SHA-checks entire original 81KB PE plus native **92 DIR32 postRET partitions and 199 sparse bytes**, and now verifies **77 strict original-GPR-shaped game-state interiors** spanning **71,674 original CODE B /15,376 native x86**, with **15,376/15,376 native mnemonic and GPR positions**, **1,192/1,192 original physical external PE fields** and **2,834 native scalar-immediate values**. Seven other source-backed original inner cases remain GPR-PROVISIONAL.

The incomplete normal C++ whole emits **76,322 CODE B /16,352 x86** versus the actual whole **81,539B /17,435 x86**; target original receiver/frame/branch ownership remains incomplete. **Original whole NONEXACT, newly accepted entire authored game CODE = 0B.** All prior 979 exact whole functions are unchanged.

Reproduce only this one changed partial parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Rejected extra-JMP variant and normal C++/COFF/PDB/native original PE comparison receipts retained under ignored `.analysis/f1125-native390/` and `.analysis/f1068-boss-live-all-native/`. No entire 979-unit cold replay.
