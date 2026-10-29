# F542 — natural VC7.1 fighter action-one source across all eleven multi-switch bosses

**Original-CODE-derived and independently freshly compiled C++ research, not a
completed giant function or exact CODE adoption.** The original Japanese
TH075 v1.11 `th075.exe` SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This extends [F541's eleven original action-zero C++ compilations](FIGHTER_ACTIONZERO_FAMILY_CODEGEN.md)
to an **additional genuine, complete action-one case** inside each of the
same eleven independent fighter-control mega-functions. It is deliberately
built using each fighter's **own** full physical native action-ID mapping;
no Reimu switch or DWORD handler addresses are copied into another fighter.

## Entire original action 1 and native source behavior

Each original first switch's **second and third DWORD handler addresses**
physically delimit the whole action-one code; it is never guessed by stopping
at an inner `JMP` or taking a cropped portion of a whole function. The original
code's **60 x86 instructions** are contiguous and include 5 genuine calls,
18 x87-related operations, 17 receiver-pointer reloads and **11 genuine
call/constant relocation roles**. The original action-one case repeats the
real signed-byte/float threshold and reset behavior of action zero, and
then runs the following distinct gameplay condition:

```cpp
if (GetNativeActionAt40FA30() == I16(0x70))
    SetNativeActionAt40FAC0(2);
```

`GetNativeActionAt40FA30` is a native `thiscall` returning signed 16-bit
`AX` (extended to ECX); the receiver's actual `+0x70` signed-short member
is independently loaded and compared. If equal, value 2 is pushed to the
real `0040FAC0` thiscall. These names are **provisional**: the exact observed
callee addresses, `RET` behavior, and instruction operands are factual;
full original class ownership and all remaining actions are not established.

## Eleven affected-only compiler experiments and original proof

The executable verifier
[`scripts/verify-fighter-actionone-natural-source.py`](../scripts/verify-fighter-actionone-natural-source.py)
loads each fighter's *entire original* 28–82K CODE SHA256 plus all its physical
post-RET DATA before generating its C++ hypothesis and compiling just that
fighter's small probe translation unit with pinned MSVC 7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` under headless Wine. Each generated source
retains the previous real **action-zero** case, adds the **real action-one**
case above and uses explicitly marked diagnostic stores for all other
nondefault switch cases. It does not reconstruct or claim the full fighter.

Every one of **11/11** independently compiled cases matches all **60/60
actual original instruction mnemonics, real EAX/ECX/EDX register allocations,
member accesses, x87 operations and relative branch graph**, with the
original true receiver EBP slot treated as the larger unmatched enclosing
function's layout, not fabricated for the probe. **121/121 typed native
COFF roles** agree across these cases: per fighter three real `00453E20`
reset calls, one `0040FA30` state read, one `0040FAC0` state update and six
real original x87 globals. Entire switch data also retains **1,607/1,607
physical DWORD COFF table fields**, per-fighter default/handler equivalence
partitions and **4,502/4,502 original sparse-index bytes**, plus **10,930
real after-RET DATA-shape bytes**. These bytes are not credited as authorship.

The special original `00564BE0` case has **263** CODE bytes, not the 212
bytes of natural small probes: its receiver pointer is at genuine
`EBP-0x88`, making exactly **17** receiver reloads use disp32 instead of
disp8 (`17 × 3 = 51` extra bytes). This is a *real native whole-boss frame
constraint* and is not patched through fake locals or target ASM.

| Whole original boss start | CODE in original giant (not exact) | Original action-one bytes | Natural probe bytes | Real case refs | Whole native jump DWORD fields | Original sparse bytes |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| `0x0045DD70` | 60,999 | 212 | 212 | 11 | 142 | 522 |
| `0x00486550` | 50,735 | 212 | 212 | 11 | 163 | 412 |
| `0x004AC040` | 82,796 | 212 | 212 | 11 | 151 | 522 |
| `0x004D7E70` | 43,601 | 212 | 212 | 11 | 140 | 409 |
| `0x004F7130` | 44,211 | 212 | 212 | 11 | 141 | 411 |
| `0x005214B0` | 46,755 | 212 | 212 | 11 | 139 | 345 |
| `0x00543210` | 58,294 | 212 | 212 | 11 | 156 | 319 |
| `0x00564BE0` | 61,872 | 263 | 212 | 11 | 131 | 350 |
| `0x0058AF60` | 49,230 | 212 | 212 | 11 | 154 | 350 |
| `0x005AEEC0` | 71,616 | 212 | 212 | 11 | 164 | 411 |
| `0x005D73C0` | 43,282 | 212 | 212 | 11 | 126 | 451 |

## Targeted reproduction (no historical cold replay)

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-boss-family.py
scripts/repo-python scripts/verify-fighter-actionone-natural-source.py --boss Reimu
# Or serially recompile only the eleven new C++ diagnostic units:
scripts/repo-python scripts/verify-fighter-actionone-natural-source.py
```

`--boss 0x00486550` selects one 7-table fighter. Sources, freshly built
COFF objects and native comparison summaries are retained under ignored
`.analysis/f542-action-one-natural-source/`; the original PE, protected
prior probes, match manifests and other source are untouched.

**Acceptance status:** the parent eleven giant functions together contain
613,391 uncredited original CODE bytes, and this confirms concrete natural
C++ case/control-flow evidence *inside* them. No partial action handler is an
independent function. The entire 22-boss group remains without a single
full-function C++ exact match. There is **no new CODE/DATA exactness credit**,
no all-unit cold replay and no external Oracle verification receipt.
