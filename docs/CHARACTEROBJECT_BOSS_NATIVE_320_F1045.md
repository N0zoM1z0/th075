# F1044–F1045 — Recover the actual native action 0x320 in the 81KB CharacterObject whole-source prototype

The SHA-pinned Japanese TH075 v1.11 original `CharacterObject::Advance`
at **0050A580** is a single authored **81,539-byte / 17,435-x86**
callable with an additional **567 afterRET switch-DATA bytes**.
Its one original physical compressed action dispatch has 92 genuine
DIR32 entries plus a separately owned 199-byte sparse-index map.
The existing F569 complete-parent *source prototype* reproduces the
real parent/owner guard, cooldown and sparse dispatch, but had only
marker stores in its game-action handlers. The actual 81KB body
remains mostly unimplemented and is **not exact**.

F1044 re-read this original from the PE and directly reconstructed
its first genuine action, `0x320`, at physical **0050A658..0050A80F**:
**439 original CODE bytes and 91 actual native x86 instructions**.
This is part of the *one* original 81KB callable — it is not a
separately callable or independently accepted function.

The genuine recovered logic includes:

- A real parent at receiver `+0xE4`; an original two-stage test of the
  parent's WORD `+0x60 == 0x2BC` and stage WORD `+0x62 > 12`, calling
  `0045B830` on expiration and returning;
- Signed fighter-facing BYTE `+0x66`, original positive 66 multiplier,
  true parent X FLOAT at `+0x44`, own X assignment and the original
  x87 signed integer-to-float conversion;
- True stage/frame WORD initialization gate at actor `+0x62/+0x64`,
  genuine motion setup `0040FBB0`, actual action/timer and effect
  fields `+0x80`, `+0x7C`, `+0xD8`, scale/color fields, and motion
  float `+0x54 = 10.0f`;
- Real Y-position update from float `+0x48/+0x54`, the exact original
  global gravity at `0065747C`, native ground check at `0065782C`,
  the actual getter `0040FA30` and auxiliary state setter `0040FB40`.

These are C++ operations reconstructed from the original PE, not a
machine-byte copy or an assembler implementation. The tracked
`probes/CharacterObjectWhole0050A580F1044.cpp` is the *one-switch
source prototype*; its tracked
`CharacterObjectBoss320NativeF1045.inc` now holds the real selected
case. The initial complete natural source control is retained in
`CharacterObjectBoss320F1044.inc` for independently repeatable
source-grammar experiments. Other unimplemented handlers remain
explicit marker stores and retain **zero game CODE credit**.

## Native source-expression recovery, not register forcing

The actual pinned normal VC7.1 original-shaped one-switch parent was
compiled with **33 distinct genuine 0x320 game source grammars**.
The first direct source emitted all 91 corresponding instructions but
only **84/91 original instruction mnemonics** and 83/91 native GPR
roles. The missing mnemonic positions were source evaluation orders
at true parent-X arithmetic and subsequent Y-coordinate movement.

Using two independently evidenced signed-float actor windows from
`FrameActorMotionPairsF1037.hpp` — position (`+0x44/+0x48`) and
motion (`+0x50/+0x54`) — and expressing the parent's real X before
the facing integer conversion restores the original x87 operation
order. The selected C++ emits:

| Native action 0x320 comparison | Original | Selected F1045 generated |
| --- | ---: | ---: |
| Actual original case CODE / emitted source case | 439 B | 335 B |
| Full case x86 instruction count | 91 | **91** |
| Matching original instruction mnemonics | 91 | **91/91** |
| Matching original native GPR roles | 91 | **91/91** |
| Matching original instruction widths | 91 | **57/91** |
| Actual external call/global fields | 6 | **6 matching targets and native ordinals** |

Six physical original PE targets independently checked (their real
REL32/DIR32 type and original instruction ordinal are retained):
`0045B830`, `0040FBB0`, `0065747C`, `0065782C`, `0040FA30`,
`0040FB40`. All original native call/global destinations come from
original PE bytes, not merely the source `AtHEX` function names.

**Important:** the 34 still-mismatched instruction widths represent
real saved receiver EBP displacement differences, because the
incomplete source prototype only emits a **0xC frame**, not the
original whole fighter's native **0x3A0 frame**. The original
`0x320` bytes are **not exact**. No fake locals, manual stack frame,
assembly, byte graft or cropped comparison was introduced to make
these width differences disappear. Source-generated 1,843B/317-x86
CODE versus original 81,539B/17,435-x86 is an explicit measure of
the remaining unfinished whole function, NOT successful exactness.

The complete prototype's 567 afterRET DATA shape is preserved; all
**92/92** source native jump-target equality partitions and
**199/199** original literal sparse-index bytes were rechecked.
Its full C++ object emits 191 total COFF records, including 92
actual switch DIR32 and the six recovered original game fields.

## Reproduction and next native work

`verify-characterobject-boss320-f1044.py` always reads the pinned
81KB original PE and independently verifies the complete native
original hash, authentic action extent/91 instruction boundaries,
all six actual external destinations, generated source x86/GPR
roles, original case ordinal COFF identity and native switch DATA.
It builds full one-switch prototype variants, never disjoint cropped
case functions. The tracked final source is compiled a second time,
and its entire emitted CODE+DATA and COFF list match the best
independently generated experiment exactly.

    scripts/repo-python scripts/verify-characterobject-boss320-f1044.py

Fresh source, COFF, PDB, logs, native comparisons and field receipts
are under ignored `.analysis/f1044-object320-grammars/` and
`.analysis/f1044-object-320/`. The historical F569 marker-only
source and its original PE proof remain intact.

**Remaining work:** recover the original whole 0x3A0 frame by genuinely
reconstructing further native game actions (especially `0x321`), not
by inventing unused frame members. The 81KB whole source remains
nonexact; new accepted authored CODE bytes = **zero**. No 979-unit
mass replay was run.
