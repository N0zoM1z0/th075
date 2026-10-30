# F782 — Borrowed stage-view controls in the 58KB fighter

**Reproducible negative evidence; no new callable exact CODE credited.**

The original Japanese TH075 v1.11 `00543210` fighter is 58,294
native CODE bytes and 16,471 x86 instructions. The latest F781
complete VC7.1 parent emits 58,293 bytes and 16,471 x86,
plus 943 separate after-RET switch DATA bytes. The original
action `0x63` occupies `00545ADE..00545DA0` (706B / 189 x86);
the generated source emits 705B / 189 x86.

Independent native observations locate three wrong GPR encoding widths:

| Native x86 ordinal | Original PE | Current complete parent |
| --- | --- | --- |
| 18 | `CMP EDX,0x96` (6B) | `CMP EAX,0x96` (5B) |
| 61 | `CMP EAX,0x96` (5B) | `CMP ECX,0x96` (6B) |
| 84 | `CMP EDX,0x96` (6B) | `CMP EAX,0x96` (5B) |

The real borrowed opponent stage is observed at `+0x60`;
the real borrowed actor flag at `+0x39D`. These fields do not
prove a complete original class layout. Four **entire** 58KB
whole-parent builds were compiled serially using pinned VC7.1:

1. Original pointer-only expressions.
2. Opponent `+0x60` via a source-compatible typed borrowed view.
3. Actor `+0x39D` via a source-compatible typed borrowed view.
4. Both typed borrowed views simultaneously.

All four generated **full COFF function CODE/DATA bytes are identical**.
All **1,863 physical COFF relocation shapes** (offset, kind,
addend, linked destination / local offset) are unchanged; compiler
local label spellings may differ. All still have three wrong
CMP register-width ordinals `[18,61,84]` and the same 705B
generated 0x63 / 58,293B generated parent sizes.

Therefore typed views alone do not correct the original register
phase, and these variants must not be called exact. The old
F626 0x63 strictness came from a different compiler parent.
A genuine improvement requires regenerating and checking the full
current fighter function and its actual PE/COFF relocations.

Targeted rerun (does not cold replay any accepted-unit corpus):

```bash
scripts/repo-python scripts/verify-fighter-mode63-borrowed-f782.py
```

Ignored research C++/OBJ/PDB and verified JSON are retained under
`.analysis/f782-fighter-mode63/`.
