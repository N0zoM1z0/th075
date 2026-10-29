# F595 — small complete original 40-byte field-setter C++ exact, but provenance still UNKNOWN

**Original Japanese TH075 v1.11 PE, not an approved authored exact function.**
Executable SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

F595 explicitly investigates a SMALL pending leaf as well as the
previous F593 entire **33,293-byte large CharacterObject boss**.
The original complete `004135F0` native function is **40 whole CODE
bytes / 16 x86 instructions / three stack parameters / `RET 0xC`**.
It writes three actual receiver fields in native instruction order:

| Actual native receiver + offset | C++ parameter | Original instruction |
| --- | --- | --- |
| `+0x24` | First unsigned/signed byte (parameter 1, EBP+8) | `MOV byte ptr [eax+0x24],cl` |
| `+0x1C` | Second DWORD (EBP+0xC) | `MOV dword ptr [edx+0x1C],eax` |
| `+0x20` | Third DWORD (EBP+0x10) | `MOV dword ptr [ecx+0x20],edx` |

This includes the complete original prologue, saved-this local,
EAX/ECX/EDX register assignment, receiver writes and real `RET 0xC`;
**no external calls, no original physical COFF fields and no assumed
missing secondary function body**. New ordinary C++
[`probes/NativeFieldSetterOriginPendingF595.cpp`](../probes/NativeFieldSetterOriginPendingF595.cpp)
compiles under pinned MSVC VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` to **byte-for-byte identical
40/40 machine code**, not merely semantically equivalent assembly.
The independently original-backed `compare-coff-function.py` gives
**`structural-exact`, 40/40 nonrelocation bytes, zero typed fields**.
The machine byte identity is a strong source-shape proof but is
**NOT** proof that the function was authored in the game itself.

## Independent original owner and caller audit

Original native function `004135F0` has **no direct `CALL` reference
from the 4,351 currently registered whole-function native boundaries**,
and a fresh scan of the entire pinned executable file finds **zero
literal 4-byte pointer references** to `004135F0`. This limits
discovered ownership; it **does not prove unreachable code**, because
indirect/computed calls, unregistered functions, toolchain linkage
and inlined/metadata references are still possible. Its original
class declaration, creation context and author/vendor ownership
remain unresolved, as earlier evidence already suspected. Do
not infer original source ownership from three raw field offsets.

The same independently extracted native direct-call graph has two
useful peer controls, **neither** of which by itself settles authored
origin:

- `00449DE0`: a separate 45-byte native constructor installing
  physical `0065844C` vtable and calling observed `00412620`
  and `0040AD80` subobject constructors. It has **36 genuine
  native direct callers, all 36 previously exact authored
  `BackgroundStage::LoadBGxx` loaders**. The original vtable
  begins with physical deleting destructor **`00449D60`**, followed
  by **five `00641E19` pure-virtual-call slots**. This is strong
  C++ *background base-class usage* evidence, but explicit original
  user-authored constructor versus compiler-generated implicit
  constructor remains ambiguous. The original R108 `unknown`
  classification is not silently changed.
- `004588B0`: a different 43-byte conditional resource pointer
  destructor using native `free` at `00640F15`. It has **six
  actual direct call sites**: one exact authored
  `Effects::LoadPatternCatalog`, one origin-unclassified neighboring
  cleanup routine and four recorded STL/deleting-destructor
  contexts. This mixed source graph also does **not** justify
  promoting ordinary compiler-generated resource cleanup to an
  independently authored game function.

The exact source shape of `004135F0` therefore remains a **pending
provenance result**. Both `config/function-origins.csv` and
`config/functions.csv` are deliberately unchanged. All three
of these small original addresses remain `unknown`/`review`.
F595 contributes **zero new accepted authored functions and zero
accepted CODE bytes**; the live official ledger is still
**943 exact whole functions /862,726 CODE bytes**.

## Reproduce only this 40-byte small leaf, not the all-unit suite

Tracked original-backed verifier:
[`scripts/verify-native-pending-fieldsetter-f595.py`](../scripts/verify-native-pending-fieldsetter-f595.py).
It freshly reads original PE bytes, decodes all 16 native
instructions and true no-reloc structure, compiles just one
new VC7.1 source TU, independently compares the whole original
40-byte function both as raw machine code and with the original
COFF comparator, rechecks the three unknown origin ledger rows
and audits the 4,351 recorded original call boundaries/peer
vtable without changing the ledger.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-native-pending-fieldsetter-f595.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Fresh source/OBJ/PDB/compiler log, typed 40/40 whole original
comparison, original direct-caller records and the summary are
saved under ignored `.analysis/f595-small-origin-source/`.
Independent raw source/C++ disassembly remains at
`.analysis/f595-leaf-cold-controls/`; original call graph inspection
is preserved under `.analysis/f595-leaf-origin-audit/`.
No all-unit cold replay, no external Factory/Oracle acceptance,
no invented class ownership and **no promoted exact game CODE**.
