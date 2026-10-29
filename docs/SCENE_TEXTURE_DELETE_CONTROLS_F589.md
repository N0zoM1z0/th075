# F589 — original 248-byte SceneObject virtual destructor texture-delete source experiment

**Pinned Japanese TH075 v1.11 original PE, fresh VC7.1 `/GX` C++
source controls, and complete original 248-byte native CODE/COFF
comparison. No accepted exact function.** Original PE SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

The genuine original SceneObject resource-release virtual destructor
at **`0043B0B0`** is a *whole 248-native-CODE-byte, 75-x86-instruction*
function. It installs a real compiler EH handler, writes the original
scene vtable, inspects `0066C238`, calls real game state setter
`00423C60`, conditionally performs native texture scalar delete
`00425460`, frees three separate owned pointers at receiver
`+0x4C/+0x50/+0x54` with original CRT **`00640F15`** and finally
invokes the actual base virtual destructor `00431F40` and restores
its registered FS exception handler. This is a nontrivial real
native destructor, not a standalone guessed `free()` leaf.

## Re-read complete original PE, not compiler-equivalence assumptions

The tracked original-backed
[`scripts/verify-scene-texture-delete-f589.py`](../scripts/verify-scene-texture-delete-f589.py)
independently rereads the entire native 248 bytes and requires
**75 instructions**, the actual original EH stack frame
`SUB ESP,0x1C`, real native texture/delete/three-free calls and
these **physically attested EBP temporary locations**:

| Original instruction ordinal | Real native pointer/temporary | Real original EBP slot | Best natural C++ slot |
| --- | --- | --- | --- |
| **26** | Texture resource read | `−0x14` | `−0x20` |
| **28** | Texture scalar-delete receiver | `−0x10` | `−0x1C` |
| **42** | First CRT-free resource | `−0x18` | `−0x18` |
| **52** | Second CRT-free resource | `−0x1C` | `−0x14` |
| **62** | Third CRT-free resource | `−0x20` | `−0x10` |

The current normal C++ source has exactly the **same 248 native
CODE bytes of extent and 75 x86 instruction count**, but the
nonrelocation comparison is still only **191/200 whole-function
bytes**. The nine differing bytes are literal EBP displacement
bytes at these source locations. We do not replace those bytes or
pad the frame to pass an exactness check.

The physical original function contains **12 genuine source COFF
`REL32`/`DIR32` records**, and this new verifier independently
compares ALL twelve to actual original target PE values and zero
addends: original EH handler `00655B86`, three FS exception-list
fields, vtable `00658334`, frame clock global `0066C238`, state
setter `00423C60`, texture scalar deletion `00425460`, three
separate CRT frees **`00640F15`** and base virtual destructor
`00431F40`. Nonrelocation differences are not mistaken for COFF
fields or accepted original exact bytes.

## 14 actual C++ texture-delete-source experiments

The new tracked nonexact C++ input
[`probes/BattleSceneTextureDeleteF589.cpp`](../probes/BattleSceneTextureDeleteF589.cpp)
uses the original member/control behavior without claiming an
unproven original class size. F589 freshly compiles **14
independent natural C++ expressions** for its texture delete:

- Parenthesized pointers, `static_cast`, `reinterpret_cast`,
  C-style cast, `const_cast` and pointer-to-pointer dereference;
- Lvalue-reference and const-reference ownership, `&*` pointer
  identity, a class pointer-constant alias and direct byte-offset
  member-pointer access;
- Two constant ternary expressions and one `sizeof`-guarded ternary
  are intentional compiler-control alternatives, not fabricated
  original game behavior.

Every single variant is freshly compiled under the genuinely
**exception-enabled** pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX /GS /Zi` profile and compared to the
**entire 248-byte original PE/COFF function**. Using `/GX-` would
have changed EH behavior and would not be an original-shaped probe.

| Real compiled controls | Variants | Full native C++ output | Original whole-function result |
| --- | ---: | --- | --- |
| Type/reference/alias/identity source expressions | **11** | **248 B /75 instructions** each | **191/200 original nonfield bytes; all five wrong/right EBP locals unchanged; 12/12 authentic COFF fields** |
| Constant conditional expressions | **3** | **267 B /81 instructions or 272 B /82 instructions** | Original total CODE size fails; not candidates |
| **Total** | **14** | Genuine pinned VC7.1 C++ builds | **0 whole exact** |

The smaller 171-byte ArchiveCatalog destructor was independently
rechecked in F584 with twelve more natural `delete` casts/aliases:
it has a *different* original local-slot permutation, yet also
remains nonexact. These original EH source facts argue against
assuming a superficial `delete` cast or global pointer alias will
recover the real SceneObject lifetime layout. **Future work needs
a true original lexical owner/lifetime or class member arrangement
capable of making VC7.1 allocate the native five physical local
slots in their observed order**, not arbitrary filler variables,
explicit assembly, or target CODE grafts.

### Only selected affected C++ builds, no cold all-unit replay

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-scene-texture-delete-f589.py --case static_cast
# Or the 14-case bounded negative source experiment matrix:
scripts/repo-python scripts/verify-scene-texture-delete-f589.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

All newly compiled per-variant source, OBJ/PDB, full PE/COFF
comparison JSON and stdout compiler logs are preserved under
ignored `.analysis/f589-scene-texture-source/`. Initial physical
original x86 comparisons and all fourteen independently compiled
variants remain in `.analysis/f589-scene-texture-expression/`.
No accepted source file for `0043B0B0` was falsely promoted to
exact, no original after-RET/EH DATA credit was invented and no
full all-unit cold replay or external Factory/Oracle receipt
occurred. The canonical **943 exact whole functions and 862,726
accepted original CODE bytes remain unchanged**.
