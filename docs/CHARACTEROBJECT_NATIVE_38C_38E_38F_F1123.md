# F1121–F1123 — Three real original 0x38C/0x38E/0x38F states; 797 native B/175 x86 and 15 actual PE fields

**Historical F1123 checkpoint:** the [F1125 native 0x390](CHARACTEROBJECT_NATIVE_390_F1125.md) now extends the current parent and makes the earlier 38F 2-byte short terminal JMP into the actual original **5-byte long JMP** (32/32 widths). The source widths 38F 151B and 76-state/75,344B numbers below describe the earlier F1123 snapshot, not current geometry.

The SHA-pinned Japanese TH075 1.11 original has ONE authored `CharacterObject::Advance` at `0050A580`: **81,539 whole CODE B /17,435 x86**, followed by 567 genuine afterRET switch DATA bytes. F1121–F1123 restore three separate original switch-state interiors in the SAME incomplete normal pinned VC7.1 whole-parent C++ source, not independently accepted exact original functions.

| Physical original state | Real PE interval | Original native CODE/x86 | Current source CODE/x86 | Matching mnemonic/GPR roles | Actual original PE fields |
| --- | --- | ---: | ---: | ---: | ---: |
| `0x38C` | `0051C82D..0051C91E` | **241B /52** | **241B /52** | **52/52 each** | **4/4** |
| `0x38E` | `0051C91E..0051CAB0` | **402B /91** | **402B /91** | **91/91 each** | **8/8** |
| `0x38F` | `0051CAB0..0051CB4A` | **154B /32** | **151B /32** | **32/32 each** | **3/3** |
| **Three native interiors** | — | **797B /175** | **794B /175** | **175/175 each** | **15/15** |

**Original 0x38C** resets motion via actual `0040FBB0`, initializes both native scale floats to 1.0f and all four alpha bytes to 0xFF, X speed to 6.0f, then **adds the real global `00659090`** to X velocity, moves facing-relative actor X and expires on original `0040FA30` completion. Its first ordinary C++ source emitted all 52 native mnemonics but wrongly loaded `00659090` first; original PE requires native ordinal **28 `FLD [actor+0x50]`**, ordinal **29 `FADD [00659090]`**. A real borrowed X-motion lvalue fixes native x87 operand order and physical PE field offset, with **52/52 original widths**.

**Original 0x38E** checks native signed parent+0x3A0, resets own signed +0xD8 and copies actor+0xC8 DWORD angle **bitwise** into original actor+0x50 motion (not float-converted). Stage 1/frame 0 spawns real **`0x38F`** via native `00453A70`. It tests two real actor X boundaries **00659424/0065924C**, moves facing-relative X, then uses original `0040FA30` completion and compares the signed retry count against the actual difficulty byte `006714D0 * 8 + 10` (native `LEA [EDX*8+0xA]`) before incrementing and switching to `0040FB40(1)`. The first source emitted an extra machine JMP from a redundant separate `return`; retaining the actual common return restores **91/91 original widths** and 8/8 PE fields.

**Original 0x38F** checks actual signed parent+0x3A0, initializes its +0xD8 WORD, +0x80 countdown and +0x7C status at native (stage,frame)=(0,0), then checks `0040FA30` and expires with real `0045B830`. All **32 ordered mnemonics/GPR roles, 3 actual external PE fields and 3 scalar immediate values** match the original. **One authentic original width remains different**: native original final JMP at ordinal 31 uses 5 bytes to the shared 81KB tail, while the incomplete selected C++ emits a 2-byte short JMP. Do not misreport this as complete original exactness; restoring later original states may change the branch span naturally.

Actual native evidence for the three state interiors was reread from the full SHA-pinned Japanese original PE, matched to physical VC7.1 COFF relocation kind/field offset/destination and ordinary original-shaped C++ x86 instruction ordinals, without a loose symbol-only acceptance or assembler. In total **21/21 original scalar immediate values** are independently checked.

The current one-parent `scripts/verify-characterobject-current-recovered-f1068.py` cold-builds ONLY the affected partial giant C++ and verifies the real original entire 81KB PE, original **92 DIR32 postRET target-equivalence partitions** and **199 sparse original bytes**, and now covers **76 strict original-GPR-shaped game interiors**, **70,684 original CODE B /15,164 native x86**, **15,164/15,164 original mnemonics and GPR roles**, **1,168/1,168 physically original PE call/global fields**, **2,801 original scalar immediate positions**. Seven other genuinely authored source cases remain separately **PROVISIONAL** for GPR-role debt.

The incomplete normal C++ parent emits **75,344 CODE B /16,142 x86**, original entire game remains **81,539B /17,435 x86** with different native stack owners and branch displacements. **Original whole callable still NONEXACT; newly accepted whole original CODE B=0**, 979 existing accepted whole exact functions untouched.

Reproduce only this one original-shaped parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Complete normal VC7.1 source/OBJ/PDB compiler experiments and rejected wrong-x87/extra-return source are preserved under ignored `.analysis/f1123-native38cef/` and `.analysis/f1068-boss-live-all-native/`, no 979-unit mass replay.
