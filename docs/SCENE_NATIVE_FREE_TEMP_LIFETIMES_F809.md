# F809 — Original Scene texture-delete temporaries versus actual three CRT-free parameters

**Reproducible whole authored 248-B Scene destructor investigation,
not a canonical accepted byte-exact function.**

The independently pinned Japanese TH075 1.11 PE owns an authored
virtual destructor at `0043B0B0..0043B1A7`, **248 native CODE
bytes/75 x86**, using genuine VC7.1 exception-handling syntax
and **12 physically verified original PE/COFF references**.
Its work includes the original scene-vtable replacement, game
clock state update, conditional texture scalar delete, three
conditional CRT `free()` calls and base virtual destructor;
all source variants preserve those original effects in that order.

Independent original PE decoding reveals **five different actually
used EBP pointer temporary slots**:

| Native machine instruction ordinal | Physical value | Original slot |
| ---: | --- | --- |
| 26 | texture pointer returned from `this+0x08` | `EBP-0x14` |
| 28 | scalar-delete receiver | `EBP-0x10` |
| 42 | first CRT-free argument, `this+0x4C` | `EBP-0x18` |
| 52 | second CRT-free argument, `this+0x50` | `EBP-0x1C` |
| 62 | third CRT-free argument, `this+0x54` | `EBP-0x20` |

The current complete 248-B/75-x86 natural source with a
genuine three-pointer local aggregate emits the same instruction
geometry and **191/200 actual original non-relocation bytes**,
but allocates texture/delete temporaries at `-0x20/-0x1C`
and freed parameters at `-0x18/-0x14/-0x10`.
All nine wrong native nonfield bytes are authentic stack slot operands.
The compiler-produced COFF source fields cannot hide these mismatches.

## A precise native allocation tradeoff

F809 builds **nine whole** pinned VC7.1 `/GX` source alternatives:

- Source baseline; nested texture deletion; and a meaningful
  three-pointer array view. These remain 248 B/75 x86,
  with all 12 actual original PE relocation positions,
  kinds and destinations, but still **191/200** native bytes.
- Three separately used pointer locals (normal, volatile, and
  a borrowed pointer/bit union), plus reversed declaration order.
  Each remains **248 B/75 x86/12 original fields**, but has
  **189/200** authentic nonfield byte matches; the resulting
  source frees have incorrect EBP roles.
- Three *direct* `free(FIELD(void*,offset))` argument expressions,
  still guarded by their original independent non-null tests.
  This variant genuinely **recovers the first two original
  texture/deleting-receiver stack slots `-0x14/-0x10`**,
  but emits only **230 B/69 x86**, because the original
  three named CRT-free parameter storage/reload pairs
  (six real instructions, 18 bytes) are no longer present.
  Source COFF has 12 fields, but their physical offsets
  are different from the 248-B native function: do NOT
  mask them to pretend the short source is exact.
- Source-compatible 8-byte alignment for the actually
  used cleanup pointer aggregate instead triggers a
  non-native stack realignment prologue and emits
  **271 B/85 x86**, not the original exception frame.

This establishes **two independent original physical requirements**:
the texture/delete pointer values must occupy the shallow
two slots, *and* the three actual CRT-free arguments must
survive as independently stored values in deeper slots
without changing call and EH instruction count.
Simply inlining `free()`, naming the values, changing
cv qualification, adding lexical braces, or aligning
the natural aggregate does not satisfy both at once.

The tracked verifier independently reopens the original
PE and verifies the native complete 248-B/75-x86 extent
and each source candidate's entire COFF section.
For same-size source candidates it explicitly checks **all
twelve physical original PE relocation offsets/kinds/zero
addends and true destinations**, not just the number of
candidate COFF fields. It never truncates the 230/271-B
negative controls to 248 B.

```bash
scripts/repo-python scripts/verify-scene-release-lifetimes-f809.py
```

Generated C++, OBJ/PDB, logs and reproducible diagnostics are
retained locally under ignored
`.analysis/f809-scene-released-lifetimes/`.
All original historical source owner names and the complete
private object layout remain provisional; the 248-B authored
whole function is **NONEXACT**, with **zero newly accepted
whole-game CODE bytes or independent functions**.
No full accepted-unit cold replay was run.
