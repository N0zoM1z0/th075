# F675 — four entire original optimized SDK state constructors (source origin UNKNOWN)

Pinned user-supplied Japanese TH075 version 1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
These are **four independently registered, fully source-backed original
native function extents**, not four newly identified game-authored
functions. All original `function-origins.csv` rows remain
`origin=unknown,disposition=review`. Their historical SDK owner,
virtual method names and original complete class layouts are
**not** established by matching these constructor machine bytes.

## Complete original native PE CODE versus fresh original VC7.1 C++

| Original whole function | Real complete original CODE | Original x86 | Original vftable PE target | Physical `DIR32` source field | Observed real member operations |
| --- | ---: | ---: | --- | --- | --- |
| `00608F7B` | **27/27 B** | 8 | `0065D348` | function +6 | `+4=1`; `+8,+0x48,+0x4C=0` |
| `00609AA4` | **30/30 B** | 9 | `0065D374` | function +6 | `+4=1`; `+8,+0xC,+0x10,+0x14=0` |
| `00609F58` | **39/39 B** | 12 | `0065D39C` | function +6 | `+4=1`; `+8,+0x20,+0x24,+0x28,+0x2C,+0x30,+0x38=0` |
| `006200DA` | **24/24 B** | 6 | `0065DE1C` | function +12 | `AND DWORD [+0xC],0`; `AND DWORD [+8],0`; `+4=1` |
| **Four distinct entire originals** | **120/120 B** | **35** | | **4** | No original historical class-name claim |

Tracked ordinary source
[`SDKNativeStateConstructorsF675.cpp`](../probes/SDKNativeStateConstructorsF675.cpp)
declares four separate virtual-bearing receiver classes with real,
observed member offsets and naturally expressed assignments. The only
non-byte-identical information in the cold compiler COFF is its genuine
unlinked **zero-addend `DIR32` vftable symbol**. Replacing precisely
that one compiler relocation operand with the independently verified
original PE vftable target produces a **complete exact native CODE
match** in each original registered function, including the original
last `RET`, all register roles, every original instruction width, and
all 120 linked machine bytes. The comparison operates on an in-memory
copy; no original game EXE is patched.

The native original SDK routines use an *optimized* VC7.1 profile;
**`/O1 /Ob0 /Gy /GR- /GX- /GS /Zi`** reproduces all four.
`/O2` also matches the first three, but not the fourth's original
full native instruction sequence: `006200DA` relies on authentic
`AND DWORD [member],0` operations, whereas `/O2` lowers them to
`XOR` plus `MOV`. Ordinary `/Od` emits an entirely different
stack-frame-laden routine, and is **not** the historical profile for
these optimized SDK-like functions. These compiler controls were
actually tested rather than guessed from earlier handoffs.

[`verify-sdk-native-state-constructors-f675.py`](../scripts/verify-sdk-native-state-constructors-f675.py)
rebuilds only this small source TU with the real pinned VC7.1,
requires each original PE registered full function boundary,
all 35 original native x86 roles and instruction starts, the one
physical original zero-addend `DIR32` COFF field per native function,
its genuine source vtable symbol and original PE target, and **all
120 original linked machine CODE bytes**. It also independently
scans all 4,351 registered original function CODE extents for direct
`CALL`s. The four originals have **1/1/1/3 genuine direct caller
instructions**, none currently classified as game-authored; this
does **not** prove vendor authorship or exclude indirect uses.

The earlier F595–F670 distinct source-backed complete historical
origin-unknown cohort comprised **71 originals /1,285 original CODE
bytes**. F675 adds **four new functions /120 bytes** for a total of
**75 independent whole originals /1,405 original CODE bytes**, all
uncredited while **95 historical source-origin-unknown** candidates
remain pending. Formal accepted authored exact totals are unchanged:
**943 entire functions /862,726 original CODE bytes (43.71%
reviewed)**. These whole SDK-like function matches are independent
of the 58K fighter boss's still-uncredited internal-case progress.

```bash
scripts/repo-python scripts/verify-sdk-native-state-constructors-f675.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Cold COFF/PDB, compiler transcript, each original PE-linked byte
proof, native original direct-caller graph and source hash are saved
under ignored `.analysis/f675-sdk-native-state-source/`.
No full 943-unit cold replay, artificial stack padding, manual native
code graft, original EXE modification or external Oracle whole-function
acceptance was performed.
