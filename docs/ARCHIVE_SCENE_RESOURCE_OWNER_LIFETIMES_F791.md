# F791 — Whole native Archive/Scene resource-teardown lifetime controls

**Original PE/VC7.1 evidence, not exact authored function acceptance.**
TH075 Japanese v1.11 original `th075.exe` identity was rechecked
against the supplied SHA256; only selected C++ source variants for
the affected functions are compiled, not a 979-unit cold replay.

## What original target machine code actually requires

The complete independently authored Archive destructor
`0041CE50` is 171 CODE bytes /51 x86 and has **14
physical original target relocations**. The actual native used
stack roles are three different 4-byte slots:

| Value | Observed original EBP slot |
| --- | --- |
| resource value copied from the list | `-0x0C` |
| scalar-delete receiver | `-0x08` |
| filename passed to `free()` | `-0x10` |

The longstanding natural separate-local source emits instead
`-0x10/-0x0C/-0x08` and is not exact despite matching 108/115
nonrelocated bytes. Prior trivial casts and one-field aggregates
had left this distinction unsolved.

F791 tests five semantically used grouped local teardown
contexts: three independent field orders for a *three-member*
resource/receiver/filename record, and two orders of a
*two-member* resource/filename record with genuine native
delete temporaries. Every field is assigned from an original
resource or actually passed to deletion/free; there are no
dummy locals or blank padding. However all three-member
variants emit **183 B /55 x86**, and both two-member
variants emit **177 B /53 x86**, each with 14 original-shaped
COFF reference fields; none is the 171-B original function.
An attractive source-level grouping is not proof of native
object layout or lifetime order.

The separate complete authored Scene destructor
`0043B0B0` is 248 CODE bytes /75 x86, with 12 physical
typed original PE fields. The actual texture scalar-delete
temporaries live at `EBP-0x14/-0x10` and three actual
conditional CRT `free` arguments at
`EBP-0x18/-0x1C/-0x20`.
The current 248-B/75-x86 C++ source still assigns
different true EBP owners, not allowed to be masked out.

Five whole VC7.1 scene variants independently test the
actual three freed-pointer field orders (four meaningful
representatives) and moving the declaration of their used
grouped owner **before texture deletion**. They all retain
248 complete CODE bytes /75 x86, all twelve genuine
original PE/COFF relocation offsets/kinds/zero addends
and physical original destinations. Three have **191/200**
non-relocation bytes equal; two alternate freed-owner
orders *regress* to **189/200**. Thus moving a genuine
source owner declaration or permuting real resource members
is not by itself the solution to the authentic five-slot
compiler allocation.

## Reproducible, fully bounded verification

```bash
scripts/repo-python scripts/verify-resource-teardown-ownership-f791.py
```

The verifier independently decodes both complete original
machine functions, checks native EBP slot ordinals, emits
ten **whole** natural C++ destructor alternatives using
the pinned VC7.1 profile (`/GX-` Archive and real
`/GX` Scene virtual destructor), and verifies that the
compiled COFF sections remain complete and untruncated.
Scene equal-size variants are also independently compared
against every actual PE relocation target; no target bytes,
vendor-owned helper CODE or artificial machine instructions
are inserted.

The 171-B Archive and 248-B Scene remain **formally
NONEXACT authored whole functions**, with zero new
native game CODE credited. Generated C++, OBJ, PDB,
compiler transcripts and machine results remain in ignored
local `.analysis/f791-resource-teardown-owners/`, with
tracked source regeneration from the original verified
`probes/ArchiveCatalogNativeLifetimeF584.cpp` and
`probes/BattleSceneTextureDeleteF589.cpp`.
