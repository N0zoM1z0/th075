# F1149 — Genuine typed scale member restores both 391 x87 load orders

Original Japanese `0x391` is a 1,259B/277-x86 interior of the ONE
NONEXACT complete `0050A580` callable, not an independent exact unit.
The previously unresolved two physical x87 load sequences now agree
with the original PE, using existing measured source types.

The original equality checks at local ordinals 110/111 and 158/159
load the native float constant at `0065747C` before actor scale +0x1C,
then execute `FUCOMPP`. The prior `*(&SELF_FIELD(float,0x1C))`
access loads actor scale first, swapping the physical global field
and four native GPR-role/width positions. Earlier raw-pointer,
qualifier and promotion experiments did not restore that order.

F1149 uses `F1094_TRANSFORM(this).scaleXAt1C` in both comparisons.
The existing `FighterRenderTransformWindowF1094.hpp` describes only
the measured +0x1C..+0x3F borrowed transform window; it introduces no
complete owner, allocation or fabricated local. Under pinned VC7.1
the direct member comparison emits the original constant-first order.
The reversed equality and address-borrowed member forms do not.
Three literal-constant controls also retain the wrong load order;
these negative source/COFF diagnostics are preserved.

The complete parent cold verification passed, including every original
direct branch target (1,834/1,834), all 17,435 ordered mnemonics and
the original afterRET table partitions/sparse bytes. The full 391
interior has 277/277 mnemonic, GPR-role and width positions, 29/29
physical PE external fields and 49 scalar positions checked. It is
now included in the strict native-interior cohort: 83 interiors,
76,519 original CODE bytes /16,367 x86, 1,275 physical PE fields and
3,013 original scalar positions.

The entire source remains 81,572 CODE bytes versus original 81,539.
Frame 0x3A4/saved-this EBP-0xDC and eight provisional GPR interiors
remain wrong. Accepted complete exact functions remain 979 /868,243
original CODE bytes: this change adds no whole-function exact credit.

Reproduce only the affected parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Six fresh complete source probes, compiler logs, COFF/native-load
diagnostics, before-source/COFF/receipt and final verifier output
are retained under ignored `.analysis/f1149-native391-literal/`.
