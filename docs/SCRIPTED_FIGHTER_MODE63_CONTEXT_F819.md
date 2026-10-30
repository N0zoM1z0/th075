# F819 — The original fighter 0x63 mode action in the current, larger whole parent

The pinned Japanese TH075 1.11 original fighter at 005214B0
has **46,755 original callable CODE B /13,230 x86**, and
901 separately owned packed after-RET dispatch DATA bytes.
F817's current source, with full original early game actions and
resource state 0x62, emits 11,785 CODE B /3,069 x86 while still
missing most later gameplay and remaining NONEXACT.

F819 restores the next authentic physical second-switch action 0x63
at native original 00523C9D..00523E3D: **417 complete CODE B,
109 x86 and seven genuine PE/COFF call/global fields**.
The actual original mode-3 global at 006714B4, signed 0x2CD
activation flag, owner/opponent-stage fields, input-history
bytes at +0x32A indexed by +0x39D, and game transitions
to states 0x5F/0x31C are preserved using tracked real
F626 C++ rather than copying the original x86 encoding.

The tracked verifier regenerates and physically checks the F817
selected parent, then compiles ONE whole source parent with
the new F626 mode action. Generated source reaches
**12,187 callable CODE B /3,176 x86**, retains original
saved-this EBP-0x10, revalidates all selected previous
complete cases 0x5F/60/61/62 with their original real PE fields,
the first 30 F617 source-backed game cases and the entire
901B original after-RET switch DATA.

Unlike the *earlier, shorter* F626 research parent, the expanded
source no longer has exact 0x63 GPR roles. While the original and
source remain **417 B /109 x86 with all original instruction
mnemonics and all seven typed PE call/global symbols**, the
true original versus current source has instruction-width
differences at x86 ordinals **38 and 61** and **143
non-relocation machine-byte differences**. These are original
register/operand differences, never masked as relocations or
claimed exact. The F806 46B shared default remains
byte-different at genuine GPR offsets 10,12,16,19, while
its original PE call targets and saved receiver remain correct.

Targeted reproducer:

    scripts/repo-python scripts/verify-scripted-fighter-mode63-context-f819.py

Full C++, original PE/COFF verification and compiler object
are preserved in ignored .analysis/f819-scripted-mode63/.
The original callable game function is STILL NONEXACT:
zero independent subcase or authored whole-function CODE credit;
no mass cold replay of accepted units.
