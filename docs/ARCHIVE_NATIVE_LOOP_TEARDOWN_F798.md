# F798 — ArchiveCatalog native loop resource and delete-receiver ownership

**Whole original authored function research; no new exact CODE credit.**

The pinned Japanese TH075 1.11 original authored
`ArchiveCatalog` destructor at `0x0041CE50` owns
**171 complete CODE bytes, 51 x86 instructions, and
14 actual PE/COFF relocation fields**.
Fresh independent original native disassembly establishes
the following five EBP positions:

| Real physical role | Original native EBP slot |
| --- | --- |
| Saved destructor `this` | `-0x14` |
| Loop index | `-0x04` |
| Resource value returned by the original list | `-0x0C` |
| Actual scalar-delete receiver | `-0x08` |
| Name passed to CRT `free` | `-0x10` |

The ordinary standalone-variable source emits the
**correct 171 B /51 x86**, with **108/115 original
nonrelocated bytes matching** and all 14 original
PE source calls, but three real resource/delete/name
stack locations differ. They may not be ignored
as relocation fields or accepted on matching length
alone.

## Nine new complete actual source controls

`scripts/verify-archive-loop-teardown-f798.py`
freshly compiles nine whole `/Od /GX-` VC7.1
Archive destructor source variants. Every local field
represents a **real source value that is read/written
by the original work**: loop index, resource pointer,
actual delete receiver or filename. No dummy padding,
inert members, manual x86 or original-binary grafts.

A two-field loop context joining index and filename,
with each source field actually used, produces:
- Index-first: complete **171 B /51 x86**,
  but only **102/115** original nonrelocation bytes
  matching; wrong native index and filename slots.
- Filename-first: complete **171 B /51 x86**,
  retains **108/115** byte matches, but real
  resource/delete receiver still have incorrect EBP
  ownership. Both full-length alternatives preserve
  **14/14 original physical PE relocation targets,
  kinds, offsets and zero addends**.

A meaningful four-member loop context with actual
filename, resource, explicit delete receiver and
index reveals a stronger **stack allocation lead**.
With members ordered `filename/resource/deleteReceiver/index`,
the compiler stores the first resource returned by
`ArchiveResources::At` at **EBP−0x0C**,
its explicitly used delete receiver at **EBP−0x08**,
the filename at **EBP−0x10** and the loop index
at **EBP−0x04**, exactly the four observed native
non-saved semantic offsets.

**But this is not complete native source.** The
same actual compiler, with this explicit copy
lifetime, generates *four additional MOV instructions*
after assigning the receiver, to prepare another
real delete temporary; total source becomes
**183 B /55 x86**, the frame
`sub esp,0x20` and saved `this EBP−0x1C`.
The native instead has **171 B /51 x86**,
`sub esp,0x18` and saved `this EBP−0x14`.
Rewriting explicit `delete` as an assignment
within `delete (receiver=resource)` preserves
the same nonnative extra instructions; changing
real member order likewise fails.

Thus the true remaining challenge is not just
*which four physical values live together* but
which original C++ value category and delete
expression naturally **avoid the compiler's
second pointer-copy lifetime**. All alternatives
remain nonexact. The verification does not truncate
183B to 171B or count its near-native EBP values
as formally matched functions.

To rerun only the affected whole function:

```bash
scripts/repo-python scripts/verify-archive-loop-teardown-f798.py
```

The tracked verifier checks native original 171B
boundaries, authentic real EBP instruction ordinals
and 14 original PE fields for all same-sized
variants. For size-mismatching variants, it records
actual complete 183B COFF and all source reference
identities *without claiming original PE relocation
positions remain equal*. Generated sources, compiler
objects and results are preserved under ignored
`.analysis/f798-archive-teardown-scratch/`.
No all-979-unit cold replay, target-byte mutation
or accepted authored exact CODE credit was made.
