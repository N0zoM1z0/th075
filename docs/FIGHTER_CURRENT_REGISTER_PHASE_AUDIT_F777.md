# F777 — original 00543210 whole-parent register-phase and action-63 width audit

**Revalidated original PE evidence, not another exact game function.**
The pinned original is Japanese TH075 v1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The independently authored complete `00543210` fighter is **58,294
native CODE bytes** and owns **943 separately accounted after-RET
packed switch DATA bytes**. Its newest F771 normal VC7.1 C++
whole-parent source emits **58,261 CODE B**, a **33-byte original
CODE deficit plus actual register/CFG byte differences**, not
an accepted callable game function.

## Independent per-action physical native PE findings

The tracked [F777 whole-parent verifier](../scripts/verify-fighter-current-register-phases-f777.py)
freshly compiles exactly one entire F771 original-shaped fighter with
the pinned VC7.1 compiler. It then independently rereads each
complete actual PE action interval and pairs original x86
*instruction ordinals* with actual COFF source owner ordinals.
This matters because an older F626 compiler context reported
five fighters, including `00543210`, as having a strict internal
`0x63` game action. That historical source result **must not**
be projected into this different, more complete F771 parent.

| Complete original internal action | Actual original PE interval | Original CODE B | Original x86 | Typed real PE/COFF fields | Current complete parent native result |
| --- | --- | ---: | ---: | ---: | --- |
| `0x58` | `00544F34..00545109` | 469 | 135 | 17 | Zero nonfield byte differences excluding true external parent-tail JMPs |
| `0x59` | `00545109..0054526D` | 356 | 95 | 16 | **19 real nonfield GPR/operand bytes wrong** |
| `0x60` | `0054559F..005457BC` | 541 | 154 | 10 | **98 real nonfield GPR/operand bytes wrong** |
| `0x61` | `005457BC..005459E5` | 553 | 158 | 10 | **101 real nonfield GPR/operand bytes wrong** |
| `0x63` | `00545ADE..00545DA0` | **706** | 189 | 15 | **705 emitted bytes**, 189 x86; three wrong x86 operand-width/register ordinals |
| **Physical original sample** | | **2,625** | **731** | **68** | Explicit positive and negative controls, zero new whole callable CODE credit |

All **68** real COFF source references in these five complete action
intervals were checked individually: genuine original PE field offset
via paired original/source x86 ordinal, `DIR32/REL32` kind, zero
addend, exact source decorated symbol, and independently decoded
original PE absolute/relative destination. `__ftol2` is independently
resolved to the actual PE native helper address, not a guessed
internal action call. Each native action is mapped from the actual
original packed switch entry and independently bounded by the next
real original handler, not a duplicated source label or arbitrary
cropped compiler fragment.

## The important stale strictness error in native action `0x63`

All **189 original and source x86 instructions** have the same
mnemonics at corresponding positions, but the three real comparisons
with owner `+0x60` and original constant **150 (`0x96`)** use
*distinct GPRs and instruction widths*:

| Native ordinal | Physical original PE x86 | Latest whole-parent C++ x86 |
| --- | --- | --- |
| **18** | `CMP EDX,0x96` — **6 B** | `CMP EAX,0x96` — **5 B** |
| **61** | `CMP EAX,0x96` — **5 B** | `CMP ECX,0x96` — **6 B** |
| **84** | `CMP EDX,0x96` — **6 B** | `CMP EAX,0x96` — **5 B** |

These three genuine original `CMP` register/width mismatches give the
observed **706-B native versus 705-B emitted** complete case.
They are not an artifact of PE/COFF relocations, and the other
native operand differences in that case are not masked or
silently declared exact. This invalidates any *unqualified* use
of historical F626 current-parent 'strictness' when discussing
F771. The old F626 evidence is retained as a statement about
its own older complete parent, not deleted or rewritten.

The immediately preceding original `0x58` is source- and
PE-nontail-byte-identical in this **same** parent (469 native B /
135 x86 /17 authentic fields), while `0x59` already has an
**EAX/ECX/EDX phase rotation** at native x86 ordinal 0.
Full original `0x5D` is again strict in the current context;
it is wrong to assume the rotated `0x59` phase carries unchanged
through all later actions. `0x60/0x61` again show real
cross-action GPR phase changes. The actual compiler context
must be checked separately for each real game action.

## Real source experiments, no fake local fixes

Thirteen new original-shaped entire VC7.1 C++ parent builds varied
**actually used** `0x59` stage comparisons, actor position/velocity
expression ownership, compound assignments, collision float lvalues,
and genuine signed-short conversion expressions, without artificial
register or stack padding. The original `0x59` source has a
**356-B/95-x86** full case but 19 wrong GPR operands. The
meaningful `velocity -= drag`, stage comparator reversal,
read-only global and typed-short casts did not improve the 19
bytes. Compound color fade increased actual wrong bytes to 22
and two original instruction widths differed. Read-only position
sum made 23 bytes wrong and two actual opcode differences;
reversing the stage-two guard increased wrong bytes to 34.
None is promoted as an exact source correction.

Separately, eight entire-parent borrowed typed actor stage/color
models in the **different** R015 giant `004EBDA0` (original
33,293 CODE B/8,789 x86/682 PE fields) were recompiled under
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`; all retained its exact
original instruction geometry but **137 true register-phase
nonfield wrong bytes** in `38D/38E/3E3`. These negative controls
remain under local `.analysis/f773-characterobject-typed-phase/`.
No claim that a type cast fixes the other giant is warranted.

## Selective reproduction and independent DATA ownership

```bash
scripts/repo-python scripts/verify-fighter-current-register-phases-f777.py
# F777 0x58: 469-B nontail exact
# 0x59: 19 wrong original bytes; 0x60: 98; 0x61: 101
# 0x63: original 706B vs 705 emitted; CMP ordinals [18,61,84]
# 68 original real PE fields verified; original afterRET 943B verified
```

This verifier compiles **only ONE affected entire 58KB C++ TU**,
reuses the F771 physical current-parent controls for other true
C8–CE/1F6–1F8/2DB/2F8–2FB native cases, and checks the original
**943-B after-RET DATA** with its **156 real DIR32 switch labels**
and **319/319 other actual sparse-map bytes**. This DATA is not
new original callable game CODE. The generated object/PDB,
original physical instruction evidence and receipt are under
ignored local `.analysis/f771-fighter-grounded-volley-whole/` and
`.analysis/f777-fighter-register-audit/`. The tracked verifier and
this document are sufficient to regenerate them.

**Nothing in F777 is accepted as whole-function exact.** The official
ledger remains **977 complete original authored functions and
868,036 original CODE bytes (43.98% reviewed)**. There remain 22
large and five smaller original-authored whole functions not exact.
No mass 977-unit cold replay, target executable modification,
original `0x63` fake-register patch, history deletion or partial
case CODE credit is involved.
