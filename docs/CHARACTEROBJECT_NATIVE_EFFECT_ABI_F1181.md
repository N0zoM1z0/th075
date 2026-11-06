# F1181 — Native effect/sound narrow-parameter views in the 81KB parent

The live `probes/CharacterObjectWhole0050A580F1044.cpp` now reconciles
seven C++ declarations, covering six actual native callees, with the
low-word/low-byte parameter views of already exact helper bodies.
One affected complete-parent cold compilation verifies **82,109/82,109
previous candidate CODE+DATA bytes unchanged**, all **1,449** physical
COFF offsets/kinds/addends/local destinations unchanged, and all **202**
changed decorated external symbols still bound to their actual native targets.
This is source-contract reconstruction, **not new whole-function exact credit**.

| Original callee | Reconciled source view | Independent existing exact source |
| --- | --- | --- |
| `0040FAC0` | `SetNativeActionAt0040FAC0(short)` | `GameLeafHelpers.cpp`, primary animation counters |
| `0045B860` | `NativeHitAt0045B860(short)` | `EffectServices.cpp`, shared sound |
| `00453D40` | `NativePrepareAt00453D40(short)` | `FighterEffectPolicies.cpp`, actor sound |
| `00453A70` | short effect /signed-char facing and layer; both coordinate views retained | `FighterEffectPolicies.cpp`, battle-effect forwarding |
| `00453C80` | short effect /signed-char facing and layer | `FighterEffectPolicies.cpp`, auxiliary-effect forwarding |
| `00453B50` | short effect /signed-char facing and layer /unsigned-byte link and mode | `FighterEffectPolicies.cpp`, tracked-effect forwarding |

The existing provisional method names are retained. These pointer-only
interfaces neither instantiate owners nor establish their private layouts.
An exact compatible callee source does not prove original C++ type spelling.
The native stack contract and complete caller emission remain authoritative.

## Raw float representation transport must remain explicit

The native parent forwards coordinate and angle representations with DWORD
MOV/PUSH sequences. Those four-byte stack slots are compatible with float
views in the helper bodies. That does **not** justify numerically converting
an integer representation to float, nor prove that a newly typed float
lvalue argument will reproduce the native caller.

A separate complete-parent experiment changed the coordinate/angle reads to
proper float views and used the existing helpers' float parameter views:
**90 lexical calls across 73 current include files** were examined, including
the includes expanded for several switch states. VC7.1 emitted **82,521 CODE
bytes /17,764 x86**, versus the selected **81,542/17,435**. Thus the genuine
float-argument lowering adds 979 bytes /329 instructions and does not match.
This negative source is retained in `.analysis/f1178-native-effect-abi/`;
it was **not** adopted. The live raw-coordinate overloads retain the actual
DWORD representation transfer. The accepted helper bodies are unchanged.

## Complete native proof and remaining debt

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

The affected-parent replay independently retains:

- all 17,435 original mnemonic positions, native frame 0x3A0 and saved-this
  EBP-0xAC, and all 5,717 native EBP operands;
- all 1,834 original direct branch destinations, all 92 dense-table native
  instruction destinations, all 199 sparse bytes and all 1,357 CODE fields;
- all 83 strict interiors /16,367 GPR positions and their 1,275 PE fields;
- **522 remaining wrong GPR positions and five wrong widths** in the same
  eight provisional interiors. The original full callable is **still NONEXACT**.

The direct CODE+DATA equality above compares the old and new **candidate**;
it must not be mistaken for equality to the original 81,539-byte function.
All native addresses are re-read from the pinned Japanese PE. The raw old
object, new cold proof, symbol transitions and full native summary are retained
under `.analysis/f1179-native-narrow-abi/` and
`.analysis/f1181-native-effect-abi/`.

Other bounded full-parent controls remain negative and are retained locally:
actual terminal switch exits, prefix/postfix counter update, comma grouping,
used void-call returns, direct float X copies, inline parent-action access,
and CPU/size profiles (`.analysis/f1172-*` through `.analysis/f1180-*`).
Plain float X copies emit the same native MOV sequence; passing float lvalues
as arguments is the distinct failing operation. `/G5`, `/G7` and `/Ot` preserve
the old debt; `/Os` changes whole geometry to 81,324 CODE bytes /18,105 x86
and is rejected. These observations narrow future work; none authorizes
fake register seeds, inert locals, ABI changes, assembly or cropped acceptance.

The canonical ledger stays **982 complete exact originals /871,649 CODE
bytes**. All 22 remaining authored originals are giants; all 95 unresolved
origins remain unknown. No exact unit, origin evidence, comparison/test
infrastructure or accepted source was changed, so no corpus cold replay,
full CI or historical origin-test rerun was required.
