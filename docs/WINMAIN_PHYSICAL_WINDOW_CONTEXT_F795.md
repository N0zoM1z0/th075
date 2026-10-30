# F795 — Original WinMain graphics/window/scene/path stack adjacency and 26 source controls

**Complete native original 2,987-byte startup source research, not a
byte-exact whole-function acceptance.** The original target is the
pinned Japanese TH075 v1.11 `resources/th075.exe`; its real
`00602A60..0060360B` authored WinMain contains **2,987 CODE B,
654 x86 and 123 original CALL instructions**, followed by a
**separate 60-B native jump table** for 15 actual scene
constructors. The source-driven full WinMain retains the real
window, graphics/input/sound, archive, scene and cleanup
lifetimes. No entire game function is cropped.

## Independent original native PE stack evidence

The original compiler allocates four *actually used* native
WinMain objects in immediate physical sequence:

| Actual original meaning | Machine-code proof | Original location |
| --- | --- | --- |
| Graphics resource client | `00401000` constructor receiver | `EBP-0x189` |
| Created window HWND | `CreateWindowExA` return store at `00602C28` | `EBP-0x188` |
| Current scene pointer | original zero initialization at `00602A7C` | `EBP-0x184` |
| Module-path 260B buffer | original `GetModuleFileNameA` address at `00602AA6` | `EBP-0x180` |

The original WinMain also initializes EventService from
`EBP-0x3D`, Input client from `EBP-0x62`,
Sound client from `EBP-0x61`, and actual 48-byte
`WNDCLASSEXA` from `EBP-0x30`.
This is **observed stack adjacency**, not evidence that the
historical source necessarily declared one composite type.
A source-level grouping must preserve real construction/call
ordering, not merely position a copied value at the same offset.

## 26 independent complete pinned VC7.1 hypotheses

The tracked
`scripts/verify-winmain-native-used-group-f795.py`
builds **26 genuine complete WinMain C++ variants**, all
using their actual original runtime values: live `HWND`
main, `HANDLE` readyEvent, `MSG`, `WNDCLASSEXA`,
directory-end pointer, and window width/height. No blank
padding fields, invented persistent owners, or unused
frame locals are introduced.

Twelve alternatives add previously missing *combinations*
of genuinely used members to the existing scene/path
view; twelve reorder the actual scene/path/window/class
members, and two check whether source-compatible
one-byte struct packing can account for the difference.
Every variant still emits 654 original-position x86
**mnemonics**, 173 compiler-COFF fields and a separate
60-B postRET scene table, but that **does not mean
all original instruction widths/fields/byte addresses
match**.

| Genuine source experiment | Whole source CODE | Original-width x86 matches | Actual scene/path positions |
| --- | ---: | ---: | --- |
| Best 4+ member grouping (window, main, ready, directory) | 3,002 B | 619 /654 | `EBP-0x180/-0x17C` |
| Grouped scene/path + main/window ordinary order | 3,002 B | 619 /654 | `EBP-0x180/-0x17C` |
| Reorder main before scene/path | 3,026 B | 627 /654 | `EBP-0x17C/-0x178` |
| Reordered window/main/path/scene | 2,993 B | 590 /654 | `EBP-0x48/-0x14C` |
| Relevant packed-one field controls | identical to unpacked | no new original matches | unchanged source EBP |

The original native current scene and path require
`EBP-0x184/-0x180` with 2,987 CODE bytes;
**none** of the twenty-six full source variants
matches those roles, and the 2,993-B almost-right
length control has far *worse* real x86 widths and
completely incorrect scene/path positions.
A pleasing total byte count must not be confused
with a complete original function match.

The verifier independently rechecks the original
physical CALL and receiver fields, native original
WinMain `RET 0x10`, actual 15 scene-table PE
destinations, the 654 original instruction count and
all described stack ordinals. Source COFF records are
reported explicitly as **diagnostic source fields**:
their total count of 173 is not proof that all native
original PE relocation offsets and call targets match,
because the enclosing WinMain is not byte exact.

Reproduce only the affected full startup function
from tracked source:

```bash
scripts/repo-python scripts/verify-winmain-native-used-group-f795.py
```

The 26 complete alternative C++ files and private
COFF/PDB/JSON diagnostics remain in the preserved
ignored folder `.analysis/f795-winmain-grouped-runtime/`.
No historical complete private class size or original
field-order declaration is asserted. **WinMain still
NONEXACT, zero original authored CODE added; no full
979-unit cold replay.**
