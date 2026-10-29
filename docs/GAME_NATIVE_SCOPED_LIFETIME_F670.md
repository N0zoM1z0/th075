# F670 — complete original 00423B20 scoped-object lifetime source grammar

This is a complete original native function reconstruction with
**historical source origin still UNKNOWN**, not a new accepted authored
function. The original target is the supplied Japanese TH075 v1.11
`resources/th075.exe`, pinned SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original registered native extent is `00423B20`–`00423B3A`:
**26 complete CODE bytes /11 genuine x86 instructions**.

## Authentic original ABI and natural C++ lifetime

The original whole native code creates a stack-addressed temporary
at **EBP−1**, pushes the real constructor argument `16`, calls the
genuine original constructor `004239F0`, then calls the actual
original destructor `00423A90` on the same temporary address. It
restores ESP/EBP and returns as a full ordinary CDECL function; it
does not contain a partial outer-function snippet or an invented
extra epilogue. The actual distinct original `CALL` fields are:

| Native physical field | Real PE callee | Original source field type |
| --- | --- | --- |
| `00423B2A` (function `+10`) | `004239F0` | Zero-addend `REL32`, constructor |
| `00423B32` (function `+18`) | `00423A90` | Zero-addend `REL32`, destructor |

Tracked ordinary source
[`GameNativeScopedLifetimeF670.cpp`](../probes/GameNativeScopedLifetimeF670.cpp)
expresses the same native lifetime as a complete function containing
one C++ local object with a declared nontrivial single-argument
constructor and destructor. MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX-
/GS /Zi` genuinely compiles it into the same **26 native machine
CODE bytes after linking only the two authenticated REL32 fields**.
There are no fake locals, padding arrays, machine-code grafts,
embedded original relocations, handwritten assembly, or compiler
flag changes to force a prefix match. The class spelling is only a
*provisional compiler grammar*. An empty C++ class occupies at least
one byte, but a full original object layout and historical source
class name are not proven by EBP−1.

[`verify-game-native-scoped-lifetime-f670.py`](../scripts/verify-game-native-scoped-lifetime-f670.py)
cold-builds only this one tiny source TU. It independently decodes
the real entire original 26-byte PE function and new compiler COFF,
requires all **11 whole original x86 positions, sizes, and mnemonic
forms**, the genuine two native EBP−1 `LEA` sites, real 16 argument,
and each complete original `CALL` destination, source COFF symbol,
type, zero addend and linked displacement. It then compares **all
26 original PE CODE bytes** byte-for-byte. The actual registered
original direct-CALL scan of the 4,351 whole CODE extents found **zero
direct callers** of this function; indirect, init-time, or otherwise
unregistered uses are not ruled out. Neither this fact nor the
compiler grammar determines original source authorship.

The original `function-origins.csv` entry remains
**`origin=unknown, disposition=review`**, like the other 94 pending
origin candidates. Prior F595–F665 source-backed whole origin-unknown
cohort contained **70 distinct complete originals /1,259 native
CODE bytes**; F670 adds one new independent source-backed complete
native function **26/26 bytes**, bringing this uncredited research
cohort to **71 originals /1,285 CODE bytes**. Official accepted
whole game-authored exact coverage remains **943 functions /
862,726 original CODE bytes (43.71% reviewed)**.

```bash
scripts/repo-python scripts/verify-game-native-scoped-lifetime-f670.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Newly generated COFF/PDB, compiler log, real original PE caller scan
and full linked machine-byte proof are retained in ignored
`.analysis/f670-native-scoped-lifetime/`. No all-unit cold replay,
original EXE modification or external Oracle whole-function
acceptance was claimed.
