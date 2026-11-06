# F1157 — Complete 248-byte virtual BattleScene destructor cold exact

Original R054-authored `0043B0B0..0043B1A7` is now accepted as
`battle-scene-release-0043b0b0`: **248 CODE bytes /75 x86, all 12
physical COFF fields, zero differences after canonical cold replay**.
Its original SHA256 is
`bed175595f91c3b4aa9f48ff91be6793cf1c069400bf98f37658a29ae98aa0c9`.
The last RET is `0043B1A7`; following INT3 alignment is excluded.

## Actual allocated objects, rather than synthetic cleanup storage

The independently cold-exact constructor `0043AD10`, represented by
`BattleConstructorF196.cpp`, allocates the texture manager with ordinary
new, then a digit-atlas object at +0x4C and two combo-counter objects at
+0x50/+0x54. The latter three require no nontrivial destructor calls in
the native cleanup. The accepted destructor uses ordinary typed scalar
delete for each actual nonnull HUD pointer after the texture deletion.
The pointer-only views are never allocated or embedded and do not claim
complete historical HUD layouts.

The old candidate instead declared a three-pointer cleanup struct and
passed its fields to `free`. That source matched only 191/200 nonfield
bytes and rotated the real stack owners. Natural deletion now yields:

| Native used temporary | Original and cold C++ EBP |
| --- | ---: |
| Texture pointer | -0x14 |
| Texture scalar-delete receiver | -0x10 |
| Digit atlas deallocation argument | -0x18 |
| First combo deallocation argument | -0x1C |
| Second combo deallocation argument | -0x20 |

The three actual deallocation calls bind `??3@YAXPAX@Z` to original
`00640F15`. Its original thunk jumps to `00642A61`; `0064169D`, used
by other scalar/array deallocation bindings, first jumps to `00640F15`.
The shared runtime destination alone never proved a source-level `free`
call or justified named cleanup locals. Both the allocation context and
the complete compiler temporary/COFF evidence support the natural delete.

The original mode comparison followed by literal nonzero `4`, state-value
setter `00423C60`, texture deleting destructor `00425460`, native vtable
`00658334`, EH handler `00655B86`, virtual base destructor `00431F40`
and full EH unwind remain intact. No cleanup of a pointer absent from
the original, null/failure branch, fake local or manual stack layout was added.

## Canonical acceptance

    scripts/repo-python scripts/replay-exact-units.py --unit battle-scene-release-0043b0b0

`src/BattleSceneReleaseF1157.cpp` contains the one source body, compiled
with pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi`. The manifest binds
all 12 actual field positions/types/symbols/zero addends/destinations.
All 200 nonfield bytes and every relocated byte compare exact.

The unchanged R054 origin and historical before row remain in the adoption
manifest. No base, texture, CRT or EH helper earns duplicate CODE credit.
The canonical ledger is now **981 complete functions /868,662 original
CODE bytes**, with **23** authored originals still nonexact: 22 giant
and WinMain. Reviewed coverage is 44.01%, conservative coverage 43.94%;
the 98% objective remains incomplete.

The earlier F589/F1015/F1048 free-based negative sources remain preserved.
The new structural preview, normal source/COFF/PDB, canonical cold log,
complete replay receipt and adoption script are under ignored
`.analysis/f1157-scene-object-delete/`.
