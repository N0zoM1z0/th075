# F638 — four complete original game-facing constructors, two independent natural C++ origins

**Pinned Japanese TH075 1.11 original PE**, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`, and genuine MSVC VC7.1 normal `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Unlike unfinished giant fighter **cases**, all four addresses below are **distinct complete physically registered original native functions** and every original native CODE byte is reproduced by two different ordinary C++ source styles. However, their historical source origins remain **UNKNOWN**; complete original machine-byte identity **does not** establish authored-vs-compiler-generated source or justify acceptance in the authored exact ledger.

## Authentic original PE and natural C++ class construction

The first pair is a genuine two-level C++ constructor chain. Real original complete `00458670` first sets the original base's virtual table DWORD **`0065904C`** and returns its receiver; complete native `00458650` calls real original base constructor **`00458670`**, then overwrites the same receiver's virtual table with its derived table **`00659038`**, and returns the true receiver. Distinct original complete `004251C0` sets a different real virtual table DWORD **`00657B88`**, then constructs the genuine first member at `this+4` using original callee **`00417210`**. Real original `00411C10` has no virtual table: it constructs the genuine nontrivial member at `this+4` via actual original callee **`0040D990`** and returns `this`. The actual native class names, complete class layouts and whether original constructors were user-defined are not derived from these tiny complete code bodies.

| Original registered entire game-facing function | Complete original CODE | Native x86 count | Typed original PE/COFF fields | Real original references |
| --- | ---: | ---: | ---: | --- |
| `00458670` polymorphic base constructor | **23/23 whole CODE bytes** | 10/10 | 1 | `DIR32 +0xC → vtable 0065904C` |
| `00458650` polymorphic derived constructor | **31/31 whole CODE bytes** | 12/12 | 2 | `REL32 +0xB → base 00458670`; `DIR32 +0x14 → vtable 00659038` |
| `004251C0` polymorphic game scene-like owner constructor | **34/34 whole CODE bytes** | 13/13 | 2 | `DIR32 +0xC → vtable 00657B88`; `REL32 +0x17 → member constructor 00417210` |
| `00411C10` nonvirtual owner/member constructor | **25/25 whole CODE bytes** | 11/11 | 1 | `REL32 +0xE → member constructor 0040D990` |
| **Four distinct complete original functions** | **113/113 true whole native CODE bytes** | **46/46 x86** | **6 true PE/COFF fields** | All independently real and fully linked |

Tracked genuine C++ [explicit empty constructors](../probes/GameInheritanceAndMemberConstructorsF638.cpp) use normal `BaseF638`, derived `DerivedF638 : public BaseF638`, a virtual scene-like owner with a nontrivial first `TextureMemberF638`, and a nonvirtual sprite-like owner with one real four-byte prefix and nontrivial `SpriteMemberF638`. A **separate, independently compiled C++ TU** [with NO owner constructor declarations](../probes/GameInheritanceAndMemberConstructorsImplicitF638.cpp) uses ordinary placement-new to instantiate the four types, forcing VC7.1 to produce **implicit compiler-generated default special members**. Both compiler profiles emit the same **23/31/34/25 native whole function sizes, 10/12/13/11 x86 roles and the same six physically typed zero-addend original source COFF symbols**. No artificial saved frame locals, ASM, byte graft or forced unusual compiler profile is required.

## Full native linked-byte comparison and independently observed game call graph

[`verify-game-inheritance-constructors-f638.py`](../scripts/verify-game-inheritance-constructors-f638.py) cold-compiles **only the two relevant source TUs**, then independently retrieves each complete original function's physically owned CODE extent and original native call/vtable field bytes. For **each of the eight mode × function source comparisons** it checks every true source relocation offset, typed `DIR32/REL32`, genuine VC7.1 symbol name, actual original target address and zero addend, fixes only the physical PE-owned fields using their **real original native destinations**, and demands **all full machine CODE bytes equal** (no truncation or blanket relocation masking). Implicit compiler-generated constructor COFF symbols lack the explicit-function auxiliary definition record, so the source verifier uses the **independently established original full native function size** while also enforcing whole x86 count, physical original reference count and full linked original bytes, as supported by the repository COFF reader.

The verifier independently decodes real direct x86 `CALL` instructions across all **4,351 registered original native function CODE extents**, excluding separately owned after-RET DATA. This confirms:

| Native ctor | Actual native direct CALLs | Direct CALL instructions from currently authored original game functions | Evidence |
| --- | ---: | ---: | --- |
| `00458670` | **2** | 1 | Real derived `00458650` call and an original CharacterAuxObject initialization caller |
| `00458650` | **2** | 2 | FighterState/BattleObject initialization paths |
| `004251C0` | **15** | 15 | Game scene/resource loading and initialization paths |
| `00411C10` | **1** | 1 | SpriteSequence element append path |

The native functions are **clearly used by the game**, but an original game-authored caller does not decide if the callee's constructor was explicitly written or implicitly generated by VC7.1. The explicit and implicit whole-source alternatives are **machine-code indistinguishable**, even though their C++ authorship histories are different. Existing original `config/function-origins.csv` entries for all four remain `unknown` with `review` disposition, and no class's full virtual table or layout is claimed from a vtable *pointer* write alone.

**F638 adds four completely original-byte-source-backed, origin-unknown whole functions /113 native CODE bytes /46 authentic x86 /6 physical PE/COFF refs, but ZERO newly accepted authored exact match units or credited authored CODE bytes.** With prior F616/F618 four whole origin-unknown native constructors (133 original bytes) and F634 three tiny exact leaves (41 bytes), the independent origin-unknown complete-source study now includes **11 distinct fully original-byte-backed whole functions /287 original native CODE bytes**, all **uncredited pending provenance**. F637's 11 large fighter 0x9E case interiors are a separate bounded study and not independently callable functions. Official accepted authored whole-exact coverage remains **943 functions /862,726 native CODE bytes (43.71% reviewed)**. No all-unit cold replay, original game executable modification or external Oracle exact acceptance.

```bash
scripts/repo-python scripts/verify-game-inheritance-constructors-f638.py
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Fresh explicit/implicit C++/COFF/PDB objects, original native full linked byte receipts and real game direct-CALL graph are under ignored `.analysis/f638-game-inheritance-constructors-verified/`; initial independent compiler experiments remain under `.analysis/f638-game-constructors/`.
