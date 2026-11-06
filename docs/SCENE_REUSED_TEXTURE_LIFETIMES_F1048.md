# F1048 — Texture/resource sequential union ownership does not restore the full original Scene destructor

**F1157 supersession:** the complete original virtual destructor is now
accepted cold exact using scalar deletion of the three native new-allocated
HUD objects. These earlier free-based negative sources remain preserved;
see [whole original F1157 proof](BATTLE_SCENE_TYPED_DELETE_EXACT_F1157.md).

The SHA-pinned Japanese TH075 v1.11 original independently authored
virtual Scene destructor at **0043B0B0** is one whole **248B /75 x86**
callable, including its real EH prologue, texture scalar deleting
receiver, three original CRT frees, native base virtual destructor
and unwind. The genuine original PE has **12 physical external
COFF fields**; the best current normal VC7.1 `/GX` source matches
**191/200 original nonrelocation bytes** but uses the wrong original
EBP lifetime slot allocation for texture/delete/three CRT-free values.

Earlier F882/F1015 tested true four-field owning aggregates and
member declaration order, but not an actual **sequential union**
where the texture receiver is first used and deleted, then one of
the three freed resource pointers reuses that same live stack field.
This is a meaningful C++ hypothesis: after the texture has been
deleted there is no overlapping semantic use of its pointer, and
all actual CRT frees still consume exactly the native observed
`+0x4C`, `+0x50`, `+0x54` resource values.

The tracked `verify-scene-reused-lifetime-f1048.py` builds **28
complete original-shaped natural VC7.1 `/Od /GX` destructors**
without fake locals, inert padding, altered deleting destructor
flags or copied target bytes:

- The unmodified 248B/75-x86 baseline.
- 27 independent genuine source owners combining each of three
  real freed resources with the formerly deleted texture in a union,
  placing that union in any of three struct member orders and
  declaring the actual object at function entry, before the game
  clock branch, or before the texture deletion.

The verifier independently checks the true original 248B/75-x86
callable, all twelve physical original target PE type/destination
fields and five native EBP roles. It freshly compiles each whole
function with the original pinned compiler profile, checks the
real EH/vtable/texture/delete/CRT-free/base-dtor symbol set and
compares the *entire* compiled function, not cropped snippets.

| Result | Source shape | Native judgement |
| --- | --- | --- |
| 248B /75 x86 /12 real refs | Baseline | **191/200** comparable bytes, NONEXACT |
| **254B /77 x86 /12 real refs** | All **27 actual union owners** | Extra actual MOV/temp instructions, wrong complete function extent |

All new variants still preserve the correct real external symbol
identity set. However, the original does **not** contain the extra
two instructions needed by VC7.1 to write/read this real union
member while preparing the texture deletion. Therefore even an
actually reused, truly live scalar lifetime cannot be accepted
as matching original 248B. Neither rearranging the three real
member declarations nor changing this genuine allocation site's
scope restores the original texture/delete EBP-0x14/-0x10 pair.
The new union code is **not** adopted as the original destructor.

Reproduce only these affected 28 whole Scene VC7.1 source compiles:

    scripts/repo-python scripts/verify-scene-reused-lifetime-f1048.py

Serial source/OBJ/PDB/compile logs and measured original-code
receipts remain under ignored `.analysis/f1048-scene-reused-owner/`.
No originally nonexact whole Scene destructor was promoted to exact,
no game bytes or other exact-unit manifests changed, and no 979-unit
full cold replay was performed.
