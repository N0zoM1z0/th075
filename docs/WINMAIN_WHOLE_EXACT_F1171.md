# F1171 — Complete original WinMain cold exact

The independently R113-authored `00602A60..0060360A` is accepted as
`game-application-run-00602a60`: **2,987 CODE bytes /654 x86 instructions**,
plus its complete **60-byte /15-entry after-RET scene table**. All **3,047
compared bytes and 173 physical relocation fields** match after canonical
cold compilation of `src/WinMainF1171.cpp`. Only 2,987 CODE bytes receive
coverage. Ownership evidence and the 95 unknown origins are unchanged.

The original CODE SHA256 is
`780862e0f784ac2cbd16ed20eaff12c0da49a0c831ce4a9f56e85fc2edb3ffa0`;
table SHA256 is
`840a0d5ad8c1d5ad0a26f5ff4beae4c657cb03640df58b0aa1b71abba243fe86`.
The final `RET 0x10` ends at `0060360B`; table DATA occupies
`0060360B..00603646`. Nine INT3 alignment bytes precede the already
accepted callback at `00603650`. Neither padding nor callback is credited.

## Actual source lifetime and local ordering

The selected F911 source already had all 654 native mnemonics **and GPR
roles**, but nine wrong widths, frame 0x274 and incorrect stack owners.
F914 recovered some pointer slots while losing other native widths.
Those historical probes remain unchanged; their dimensions are historical.

Three artificial success-path nesting scopes in the old probe are removed.
Window/message/path locals, the archive catalog and game-data resource
client have their real observed lifetimes in one function scope. Ordinary
meaningful variable names and the declaration of `MSG msg` after the sound
client recover VC7.1's native local ordering. A separate compiler-only
calibration confirmed name-bucket/reverse-declaration ordering; this does
**not** recover original identifier spellings. No unused local or altered
buffer capacity was introduced: the real path remains `char path[260]`.

A remaining distinction was a **used construction value**, rather than a
named pointer hoisted into the function's named-local pool:

    currentSceneOwner = static_cast<GameScenesF1171* const&>(new Scene4F1171);

This ordinary C++ const-reference conversion materializes the base pointer
value for the full expression and transfers it to the actual scene owner.
It is used at startup and in all fifteen switch cases. VC7.1 now allocates
the initial construction value at EBP-0x19C, its raw allocation at -0x1A0,
then delete receivers at -0x1A4/-0x1A8 and case construction/raw-allocation
pairs from -0x1AC/-0x1B0 onward. The original 0x278 frame, every native EBP
operand, all GPR roles/widths and direct branch bytes match. Named pointer,
object-reference, named pointer-reference and inlined factory alternatives
were negative controls, retained locally rather than adopted.

The scene base's real +4 count-lifetime subobject and +8 first-derived-field
boundary are independently witnessed by the accepted base/scene constructors.
The fifteen complete allocation carriers use the **actual native allocation
extents**, checked at all sixteen new sites and paired with the fifteen
already exact original constructors. Their opaque private storage represents
that allocated extent; it adds no local/frame filler and asserts no recovered
private field semantics. These are scoped allocation carriers, not permission
to instantiate or embed a partial borrowed owner interface elsewhere.

## Every relocation is bound to its actual destination

The full field review separates independent evidence:

| Binding evidence | Physical fields |
| --- | ---: |
| Preserved exact compiler/CRT bindings | 18 |
| Independently accepted constructors/methods | 44 |
| Actual PE import descriptors and IAT names | 28 |
| Existing R006/R129 vendor-runtime origin evidence | 2 |
| Actual address-named external data/functions | 65 |
| Live same-section COFF labels /original numeric scene table | 16 |
| **Total** | **173** |

Thirteen stale address suffixes in the old probe are corrected. Its reused
`g_LogOKAt0065A21C` also hid **eight distinct original string addresses**:
`0065A210`, `0065A230`, `0065A250`, `0065A270`, `0065A28C`, `0065A2A8`,
`0065A2C8`, `0065A2E4`. The accepted source preserves them separately,
with a single destination for each external source symbol. Native strings,
including the original Japanese title, are read back from the pinned PE.
The scene table retains numeric indices 0–14 and physical case order
4,0,1,2,3,5–14. Local-label destinations follow the newly built object;
a fixed relocation binding cannot conceal a moved case.

## Acceptance and remaining work

    scripts/repo-python scripts/replay-exact-units.py --unit game-application-run-00602a60

Result: **1/1 exact across one freshly compiled object**, with all 2,355
nonfield bytes and 692 relocation-field bytes compared, including table DATA.
No full CI, full-corpus cold replay or new per-function test was needed.
The canonical manifests retain the R113 before/after row, source hash,
explicit profile and every relocation. Local sources, compiler calibration,
negative controls, native string/IAT/constructor review, preview, adoption
script and cold-replay receipt remain in ignored `.analysis/f1159-*` through
`.analysis/f1171-winmain-whole-exact/`.

Current ledger: **982 complete exact functions /871,649 original CODE bytes**,
**44.16%** reviewed authored coverage and **44.09%** conservative coverage.
All **22 remaining authored whole functions are giants**, totaling
1,102,055 CODE bytes; no independently authored smaller whole function
remains. The 98% goal is incomplete. In particular, `0050A580` still has
522 GPR-role and five width differences; its current parent and verifier
are unchanged by this acceptance.
