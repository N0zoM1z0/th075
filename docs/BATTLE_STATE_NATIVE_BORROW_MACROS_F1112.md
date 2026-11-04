# F1112 — BattleFrame 4,764B whole original exact, 27 native fighter life/round/position accesses with unchanged COFF `$L` ownership

The Japanese TH075 v1.11 target contains one independently accepted **4,764B complete** `BattleFrame::AdvanceState` (`battle-frame-advance-state`) original callable. F1112 types **27 actually used original actor accesses**, leaving the complete original logic, native CODE bytes, all physical COFF relocations and switch-table labels **bit-for-bit exact**.

The observed real signed WORDs at fighter+`0x324`/`0x326` hold current/recoverable life. They are independently corroborated by the complete original F999 leaf cohort. The pair at actor+`0x368`/`0x36C` is two physically adjacent original `float` round-recovery motion values, and actor+`0x44`/`0x48` contains actual physical position X/Y corroborated by the F1037 whole native fighter movement functions. In this complete source object, F1112 replaces **20 real life WORD accesses**, **5 round float pair accesses**, and **2 actor position float accesses**, totalling **27 distinct used source occurrences**. Do not assume the offsets prove a complete fighter owner layout.

The source uses narrow named `F1112_LIFE_CURRENT`, `F1112_LIFE_RECOVERABLE`, `F1112_ROUND_FIRST/SECOND`, and `F1112_ACTOR_X/Y` macros defined in the original translation unit. This is deliberate: all are actual typed original pointer dereferences of existing receivers, not synthetic runtime calls or extra locals. Six declarations only, followed by matching `#undef`; no newly embedded struct layout.

## Why the first real typed-struct refactor was rejected

The original selected complete source was strict **1/1 exact** before F1112. A first real compilation introduced borrowed C++ struct headers and the same actual field accesses. The entire emitted function remained 4,764 native CODE B/1,170 ordered x86 mnemonics, with every original physical field position/kind unchanged, but the *actual original VC7.1 COFF `$L` local symbols* for the switch table changed. Strict original COFF comparison correctly failed, regardless of identical code bytes. Five separate full-source tests isolated the cause: **even including the independently verified F999, F1037 or F1112 struct header without using any new field changes VC7.1 local symbol numbering**. The fully unchanged original source compiled with original symbol names. The macro-only field borrowing avoids introducing new struct declarations into this TU and restores every original `$L` label exactly. These were genuine compiler experiments; no local-symbol acceptance mask, fabricated padding, manual renumbering or `DIFFBUILD` conditional source was used.

## Whole 4,764B native strict cold replay

After trying the borrowed header and rejecting its COFF mismatch, compiling the selected *whole* source with the narrow in-TU macros and then adding matching macro undefinitions both yielded:

    scripts/repo-python scripts/replay-exact-units.py --unit battle-frame-advance-state

**1/1 complete original game callable exact, 4,764/4,764 previously accepted CODE B retained.** Original machine CODE, actual nonlocal relocations, local `$L` symbol identities, true 60B afterRET table and native target SHA are unchanged. The failed full C++/OBJ/probe experiments and original accepted source are preserved under ignored `.analysis/f1112-state-machine/`; there was no 979-unit replay or mutation of the Japanese target EXE. This is real maintainability/layout reconstruction, **zero new accepted whole original CODE bytes**.
