# F591 — complete native CharacterObject parent-guarded fade and spawn actions

**Pinned Japanese TH075 v1.11 PE and freshly compiled ordinary MSVC7.1
natural C++ source proof, NOT accepted whole-function exact CODE.** The
original PE SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The still-nonexact complete CharacterObject boss `004EBDA0` owns
**33,293 original CODE bytes** and **438 distinct post-RET original
switch DATA bytes**. F591 adds three real complete nondefault
physical game cases to the same natural C++ `Advance()` as F572–F590.
Unimplemented later actions remain explicitly diagnostic marker
stores, not reconstructed behavior.

## Original physical handlers, not inferred short leaves

| Native original case | Entire x86 instructions | Original internal CODE (uncredited) | True typed PE-grounded COFF records |
| --- | ---: | ---: | ---: |
| **`0x385`** | **138** | **511 B** | **10** |
| **`0x386`** | **84** | **330 B** | **7** |
| **`0x387`** | **74** | **262 B** | **7** |
| **New F591 total** | **296** | **1,103 B** | **24** |

Every case starts with the independently native-attested parent actor
`P16(+0x3A0)>0` guard and otherwise immediately invokes original
`0045B830` reset. They do **not** share the same fade policy:

- `0x385` initializes signed timer `+0xD8`, stage counters, position,
  **0.75f** x/y scales and white opacity, calls parent
  `00453E60(5.0f)`, then genuinely spawns effect **`0x387`**.
  Subsequent `+0x7C==6` increments `S16(+0x80)`, and two separate
  x87 additions use original global **`00659724`**. Signed stage
  `>1` fades color byte `+0x11` by **40**. Original stage2/frame0
  creates a **different effect `0x386`**, and the independent
  `0040FA30` state query can reset the actor.
- `0x386` starts with similar **0.75f** scale and state reset,
  and both original x87 scale additions also use native
  **`00659724`**. **Unlike `0x385`, the unsigned 20-step color
  fade is unconditional every frame**; there is NO original
  `S16(+0x62)>1` guard. A first plausible C++ draft inherited
  that guard and incorrectly compiled to 88 instructions /342
  bytes, with four spurious instruction roles. Rereading the
  complete native source removed the unjustified guard. Ordinary
  C++ then matches **84/330** and all seven actual COFF fields.
- `0x387` has distinct 0.75f scales, sprite short
  `+0x1A=0x4E2`, **−75.0f** offset and separate original float
  global **`006583F8`** used by both x87 additions. Signed stage
  `>1` triggers fade by **20** only when unsigned opacity is
  strictly greater than 20, not greater-or-equal. Its original
  reset path does **not** invent a zero-opacity store.

The natural VC7.1 source emits all original x86 opcodes and GPR
allocations, x87 operand grammar, relative branch structure and
complete instruction widths for all **296 newly verified native
roles**. No new independent read-only MOV/FLD reordering or fake
padding is tolerated.

## Genuine PE/COFF proof and entire giant accounting

Tracked source:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
New original-backed verifier:
[`scripts/verify-characterobject-stage-fades-f591.py`](../scripts/verify-characterobject-stage-fades-f591.py).

The verifier rereads the **entire pinned Japanese original PE**, its
actual native first-switch case boundaries and compressed DATA,
then fresh-compiles only **ONE affected ordinary VC7.1 TU** under
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. It rechecks the 46 prior
complete original game-action cases and all their real fields,
then independently verifies each of the three newly restored
entire cases. It requires every genuine `REL32`/`DIR32` call/global
COFF field at the **original native instruction ordinal**, with
correct original PE destination, symbol/type and zero addend:
10 physical fields for `0x385`, 7 for `0x386`, 7 for `0x387`.

The complete source also reproduces all **60 physical native
zero-addend switch handler DWORD COFF fields**, original
shared-default/repeated partitions, **198 literal byte-identical
sparse index bytes** and **438 distinct post-RET DATA bytes**.

| Authentically whole original game actions in one unfinished giant | Original x86 roles | Original inner CODE, no independent exact credit | Genuine typed PE COFF records |
| --- | ---: | ---: | ---: |
| Previous F572–F590: 46 original cases | 6,813 | 25,588 B | 474 |
| F591: 3 genuine whole cases | **296** | **1,103 B** | **24** |
| **Total 49 original real action bodies** | **7,109** | **26,691 B** | **498** |

### Affected-only reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-stage-fades-f591.py
scripts/repo-python scripts/verify-characterobject-guarded-stages-f590.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Original full x86 disassembly, individual source controls and native
comparison files live in ignored `.analysis/f591-characterobject-next/`;
new compiled source/OBJ/PDB, PE-grounded typed COFF records and
summary live under `.analysis/f591-characterobject-stage-fades-source/`.
The **entire 33,293-byte original giant remains NONEXACT**;
its 26,691 authentic internal original CODE bytes are not 49
independently exact functions. No split/whole CODE or DATA credit,
no full all-unit cold replay, no external Factory/Oracle receipt.
