# F1138 — Typed 358 genuine original phase/gauge accesses in complete nonexact 81KB CharacterObject C++ without changing CODE, DATA or physical COFF fields

The pinned Japanese TH075 1.11 original contains ONE independently authored `CharacterObject::Advance` at `0050A580`, **81,539 original callable CODE B /17,435 native x86** and 567 genuine afterRET switch DATA B. The tracked original-shaped C++ currently emits **81,560 CODE B /17,435 x86** and the native-shaped **567 afterRET DATA B**, but the entire original callable is STILL NONEXACT: the source has incorrect original saved-receiver stack slot, GPR role debt, several x87 field load orders and branch widths. This change is a substantive native memory-layout reconstruction, **not** acceptance of any new whole exact original bytes.

## Real fighter animation and meter fields

The original independent exact fighter-frame/animation sources establish **two adjacent signed short WORDs at +0x62/+0x64**, for native actor animation stage and frame. The original exact gauge/score sources establish signed 16-bit fighter meter and cooldown WORDs at +0x3B0 and +0x3B6 in the genuine 10-byte borrowed F980 window. F1138 uses those same previously full-original-exact source identities in **72 actually included game action source files** of the selected 81KB native-shaped Boss:

| Original native field | Typed physical source lvalue | Actual original-shaped source accesses |
| --- | --- | ---: |
| Actor +0x62 signed stage | `F1024_PHASE(this).stageAt62` | **240** |
| Actor +0x64 signed frame | `F1024_PHASE(this).frameAt64` | **108** |
| Grandparent fighter +0x3B0/+0x3B6 signed meter/cooldown | `F980_GAUGE(PARENT_GRANDPARENT).meterAt3B0/cooldownAt3B6` | **10** |
| **Actual changed source reads and writes** | **72 genuine included C++ case files** | **358** |

`src/FighterAnimationPhaseBorrowedF1024.hpp` and `src/FighterGaugeBorrowedF980.hpp` are existing narrow exact-evidenced, size/offset-checked borrowed windows, not guessed complete owner classes. Source remains real pointer-valued fighter objects with original signed comparisons and updates, including every stage-zero conditional, native animator transition and original 3E4 hit-meter policy. No type fields are fabricated or silently zero-filled, no compiler locals are forced and the native pinned executable remains untouched.

## Whole CURRENT C++ image: actual 82,127 bytes and 1,449 physically identical relocations

First, before modifying any actual C++ case, the complete selected parent OBJ was copied under ignored `.analysis/f1138-boss-native-windows/baseline-whole.obj`. The full selected 81KB parent was then freshly compiled after **all** true source borrows under pinned normal VC7.1, and `scripts/verify-characterobject-current-recovered-f1068.py` re-read the original entire Japanese game PE and verified all **82 strict original case interior** mnemonics/GPR, all **1,246/1,246 original physical external PE fields**, 2,964 original nonrelocated scalar positions, 92 native afterRET DIR32 label-equivalence classes and 199 native sparse bytes.

An independent whole-object-to-whole-object comparison of selected **before vs after** confirmed:

| Genuine actual compiled evidence | Result |
| --- | ---: |
| Emitted complete partial C++ CODE + afterRET DATA | **82,127 /82,127 bytes identical** |
| Real original-shaped partial C++ body CODE /x86 | **81,560 B /17,435** unchanged |
| Physical COFF position, relocation type, native addend, local symbol target offset | **1,449/1,449 unchanged** |
| Original jump/sparse DATA byte-for-byte | **567/567 identical** |
| C++ internal compiler `$L` symbolic LABEL NAME renumbering | **94 names changed**; original positions and local offsets did not |
| New independently accepted *whole original* exact CODE | **0B** |

The 94 changed `$L` *names* are genuine VC7.1 symbol-table changes caused by introducing additional struct declarations. They are not physical CODE/DATA or relocation-offset changes; they also mean this does **not** pass a hypothetical strict COFF exact replay for the original whole function. This distinction matters: the independent original PE still has **81,539 CODE B and `ESP 0x3A0` / saved this EBP-`0xAC`**, versus the incomplete selected **81,560 CODE B and `ESP 0x3A4` / saved this EBP-`0xDC`**. Do not call matching previous C++ CODE bytes exact with the original game.

Reproduce **only the affected whole native-shaped Boss parent**:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

The full 82,127B pre-borrow selected OBJ and 72 original included case source snapshots, compiler logs and original PE receipts remain under ignored `.analysis/f1138-boss-native-windows/` and `.analysis/f1068-boss-live-all-native/`. No all-979-unit replay or target game executable modification.
