# F553: action 8 from full native CODE of three huge fighter bosses

**Native-source/C++ compiler evidence only, not full-fighter exact CODE.**
Japanese TH075 1.11 is pinned to SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This extends [F551's actual action six/seven C++](FIGHTER_ACTIONSEVEN_NATIVE_CPP.md)
with **one complete additional action 8** in each of three original
43–61K-byte giant fighters. The physical first-switch DWORDs for native
cases **8 and 9** delimit the real complete action-eight CODE; every
original whole-giant CODE and full after-RET DATA hash is verified before
new natural C++ builds. Never truncate the huge function or count an inner
case as independent exactness.

## Original true behavior differs by fighter

For Reimu `0045DD70` and `005D73C0`, the complete original action 8 is
**362 CODE bytes /104 contiguous native x86 instructions**. It has the
original genuine actor state/threshold handling already established in
F548 action 6, but the real **three** changed source values are:

- signed frame byte `this+0x511` tested against **4**, not action-6's 3;
- native state callback `0040FAC0` receives **0xCE**, not 0xCC;
- float field `this+0x50` becomes **−4.0f**, not 0.0f.

**`0058AF60` is genuinely different.** The original action 8 has only
**352 bytes /102 instructions** because it **omits one `FLAG = 0` assignment**
after the float/stage initialization. The compiler probe reproduces that
shorter real branch by *not writing* this byte in its C++ source, rather
than injecting a manual jump or padding. The remaining native virtual
call uses physical `dword ptr [edx]`; for `005D73C0`, it uses `[eax]`.

## Independent VC7.1 source/COFF validation

[`verify-fighter-action-eight-natural-source.py`](../scripts/verify-fighter-action-eight-natural-source.py)
regenerates all C++ from existing *tracked and original-backed* native
F548/F551 source helpers, not ignored prior object binaries. Each probe
contains **three complete original-style actor actions 6, 7, 8** and
explicit *diagnostic-only* stores for other unimplemented actions.
The pinned MSVC 7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` compiler builds only
three affected small TUs, one after the other, and validates the
*entire* three original action spans and native jump-table DATA.

For **3/3 separately compiled C++ objects**:

- **934/934** native x86 GPR/x87/branch instruction roles agree for
  complete original actions 6, 7 and 8; all complete case byte lengths
  agree (**362/362/362** vs **362/362/352** in the exceptional role).
- **54/54 genuine typed COFF call/float reference roles** match the
  physical original instructions. Real vtable indirect-call register
  selection is preserved, with no manual ASM or copied executable bytes.
- All **422 original-style native switch DWORD COFF relocations**, the
  original repeated/default partitions, **1,323 byte-identical original
  sparse indexes** and **3,011 complete post-RET DATA-shape bytes** are
  preserved. No DATA is credited as CODE.

| Original whole fighter | Real action 8 CODE | Original flag clearing? | Native vtable invocation | All three cases' typed COFF fields | Genuine sparse index bytes |
| --- | ---: | --- | --- | ---: | ---: |
| `0x0045DD70` | 362 bytes / 104 instructions | Yes | `dword ptr [edx]` | 18 | 522 |
| `0x0058AF60` | 352 bytes / 102 instructions | No | `dword ptr [edx]` | 18 | 350 |
| `0x005D73C0` | 362 bytes / 104 instructions | Yes | `dword ptr [eax]` | 18 | 451 |

## Reproduce only changed source units

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-action-eight-natural-source.py --boss 0x0058AF60
# Or fresh-compile just all three new C++ prototypes:
scripts/repo-python scripts/verify-fighter-action-eight-natural-source.py
```

All original **3,248 interior CODE bytes** of the complete cases 6/7/8
remain part of **153,511 entirely nonexact original giant CODE bytes**.
Generated source/OBJ/PDB/JSON/compile logs are preserved under ignored
`.analysis/f553-action-eight-source/` and actual native-source negative
controls in `.analysis/f553-action-eight/`. No accepted partial/whole
function credit, all-unit cold replay, external Oracle receipt, invented
class owner layout or byte grafting.
