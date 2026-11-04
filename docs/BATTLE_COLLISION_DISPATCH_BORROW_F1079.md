# F1079 — Restore native attack timer, collision-frame flags and borrowed bounds in three exact dispatch functions

The pinned Japanese TH075 v1.11 independently authored original
`BattleCollisionDispatch.cpp` translation unit owns three already
byte-exact complete game callables: **975B `ResolveAttackHitboxes`,
897B `ResolveBodyContact` and 118B `SaveCollisionFields`**.
Together they represent **1,990 previously accepted original CODE
bytes**. The goal here was to improve physically observed native
field and owner relationships in the actual C++ source **without
regressing their strict original byte/COFF identity**.

## Verified native borrowed values, not invented historical owners

- The attacking actor has an actual signed **16-bit action-associated
  WORD at +0x80**, which guards collision eligibility and is
  decremented after relevant true body-contact outcomes. The source
  now uses the independently verified
  `F1027_TIMERS(actor).wordAt80` borrowed window, rather than
  separate raw `FIELD(short, actor, 0x80)` reads and writes.
  This does not invent additional actor members.
- The real attack/defense **collision frame** is reached from the
  fighter's actual **+0xAC pointer**. Native bit masks **0x400000
  and 0x80** operate on that *frame's* unsigned 32-bit +0x40 flags;
  defender's masks **0x2000/0x800/0x1000** are the *frame's*
  unsigned 32-bit +0x3C flags. Source now names these narrow
  separately owned `F1079_ATTACK_FLAGS` and `F1079_DEFENSE_FLAGS`
  references. They are **not** directly stored at the actor+0x3C
  or actor+0x40 offsets.
- When original `ResolveBodyContact` finds a real impact, it
  computes its coordinates from the battle collision owner's
  **four physically adjacent signed 32-bit bounds at +0x34,
  +0x38, +0x3C and +0x40**. The source now represents this as the
  genuine **borrowed Win32 `RECT`**
  `F1079_BOUNDS(this).left/right/top/bottom`, not an additional
  owned rectangle pointer or guessed complete battle class.

This is ordinary C++ on actual observed native object fields.
No new dummy locals, compiler register bindings, inline assembler,
relocation masks, original EXE edits or fabricated game helper calls
were introduced. Existing actual collision hitbox loops, guard
states, body-contact and impact-handling paths remain intact.

## Strict original whole-function verification

The affected `BattleCollisionDispatch.cpp` object was cold built
once with the pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
profile. The original native Japanese PE and all exact units were
checked **as complete callables** with their actual physical COFF
relocation identities, not by comparing cropped snippets:

| Independently authored original function | Original CODE B | Result |
| --- | ---: | --- |
| `battle-collision-resolve-attack-hitboxes` | 975 | exact |
| `battle-collision-resolve-body-contact` | 897 | exact |
| `collision-actor-save-collision-fields` | 118 | exact |
| **One affected native object** | **1,990** | **3/3 exact** |

Reproduce only this affected original source object:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-collision-resolve-attack-hitboxes \
        --unit battle-collision-resolve-body-contact \
        --unit collision-actor-save-collision-fields

This is **source semantic improvement preserving prior exact CODE**.
No new exact original function or newly credited original GAME CODE
bytes were accepted, and no full 979-unit cold replay was run.
