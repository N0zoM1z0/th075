# F745 — complete original GameProgress signed unlock-bit clear COLD EXACT

**NEW canonical exact complete authored game-function CODE:** original
`00416D50`, **111 original CODE bytes /39 native x86**, and **zero
physical PE/COFF relocation fields**. Pinned original is the user's
Japanese TH075 ver1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

The function had independently reviewed **R212 game-authored origin**
before F745 source reconstruction, supported by its complete target
boundary, explicit signed-range policy and the adjacent authored
GameProgress bitset operations. This is **not** an unknown-provenance
STL/compiler helper or a substring of a giant switch case.

## Entire original native function and actual game semantics

The original whole `00416D50..00416DBF` accepts a signed **16-bit
short selector**, saves the receiver at `EBP−4` and first guards
valid indices `0..320` inclusive. It then calculates `selected/32`
using actual MSVC VC7.1 signed arithmetic (`CDQ; AND EDX,0x1F;
ADD EAX,EDX; SAR EAX,5`) and `selected%32` using native signed
remainder bias (`AND ECX,0x8000001F; JNS; DEC; OR ECX,−32;
INC`). It builds an actual bit-clear mask with
`MOV EDX,1; SHL EDX,CL; OR ECX,−1; SUB ECX,EDX`, uses
`AND` on the existing source-owned bitset DWORD, and writes the
updated DWORD back through the same native `this+0x16A9C` array
at index `selected/32`. The function exits with the genuine
`RET 4` thiscall ABI; it has no calls and **no relocations**.

Tracked [`src/GameProgressClearUnlockF745.cpp`](../src/GameProgressClearUnlockF745.cpp)
uses only the original physically observed member-array offset and
normal C++:

```cpp
if (selected>320 || selected<0) {} else
    BITS[selected/32] &= (0xffffffffu - (1u << (selected%32)));
```

The type is a deliberately limited GameProgress receiver interface;
it does **not** assume a full historical GameProgress class layout.
The entire signed range guard ensures `selected % 32` is in `0..31`
on the reachable bit-clear path. The selected `1u << remainder`
and unsigned subtraction are **defined 32-bit arithmetic** even
for bit 31; they naturally produce the precise native mask and
original MSVC x86 operations, without the signed-overflow risk of
`1 << 31`. No inert local, asm, manual machine-byte patch or
truncated comparison is used.

## Independent alternative source controls

F745 also serially compiled **five complete original-shaped 111-B
whole-source candidates** under the pinned real VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` profile; generated source,
OBJ/PDB, compiler logs and original full bytes are kept under
ignored `.analysis/f745-progress-clear/unsigned-controls/`.

| Natural whole C++ mask expression | Native whole-function comparison |
| --- | --- |
| `-1 - (1 << signedRemainder)` (signed shift) | **111 B/39 x86, byte-exact**, but potential signed left-shift overflow for remainder 31 |
| `-1 - (1u << signedRemainder)` (unsigned shift) | **111 B/39 x86, byte-exact**, defined arithmetic |
| **`0xffffffffu - (1u << signedRemainder)` (chosen)** | **111 B/39 x86, byte-exact**, entirely defined unsigned mask |
| `~(1u << signedRemainder)` | **110 B/40 x86, NOT original** |
| `~(1 << signedRemainder)` | **110 B/40 x86, NOT original** and potentially undefined shift |

The apparently more direct complement variants produce a different
native machine-code shape. Exactness is not established by logical
bit-mask equivalence alone; the selected complete source has
**111/111 original nonfield machine-code bytes equal and zero
expected/actual COFF relocations**. Its original signed division,
remainder, range conditional branches, bit access, final `RET 4`
and full physical extent are all the pinned target's.

This is adjacent to, but independent from, the already accepted
R103-authored `GameProgressF394::SetUnlockBit` and
`GameProgressF394::TestUnlockBit` at original
`00416CE0` / `00416DC0`, which use the same physically observed
`+0x16A9C` bitset array. Those previously accepted exact units
are not reclassified, rewritten or cold-replayed by F745.

## Canonical one-function targeted cold replay

One new complete original match unit now records true target
`00416D50`, all 111 CODE bytes, original source and decorated
symbol, exact pinned VC7.1 flags and explicitly
`relocations = []`:

```bash
scripts/repo-python scripts/replay-exact-units.py \
 --unit game-progress-clear-unlock-bit-00416d50
# Cold replay: 1/1 exact units across 1 new object
```

The canonical comparator cold-builds this one new original-shaped
C++ object and verifies the **entire 111-byte original**; no old
964-unit cold replay, masked normalization, fabricated relocation,
original executable edit or extra callee CODE credit is involved.
The existing original R212 independent authored provenance remains
unchanged.

**Official original authored ledger after F745:** **965 canonical
exact whole game functions /965 source-present /965 units**,
**864,024 original CODE bytes**, **43.78% reviewed** of 1,973,704
original authored bytes (**43.70% conservative** with separate
3,420 provenance-pending bytes). The giant original 58KB fighter,
other 21 giants and three WinMain/Scene/Archive full ownership
functions remain NONEXACT; the 98% objective is unfinished.
