# F582 — two full 159-instruction CharacterObject absolute-motion action states

**Pinned original Japanese TH075 1.11 PE vs freshly built ordinary MSVC7.1
C++ source evidence, not byte-exact whole-function acceptance.** The original
executables SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
F582 adds real native `0x340` and `0x341` game-state source bodies to the
same one-function ordinary C++ `Advance()` source built in F572–F581, within
entire original giant `004EBDA0` (33,293 native CODE bytes, still nonexact).
The real original full CODE attestation and separate compressed jump DATA
are rechecked before compilation. Unrestored later cases remain explicitly
diagnostic marker stores, not claimed gameplay source.

## Two whole native 159-insn, 597-byte actions, not independent leaves

The true original first sparse jump table physically bounds two distinct
complete bodies, *both* **159 x86 instructions / 597 original CODE bytes**.
They share parent and actor motion source, but have different native
handler arguments:

- Native stage-zero `S16(+0x62/+0x64)==0` calls actual
  `0040FBB0(0,0,0)` and updates `+0x7C/+0x80` state. It constructs
  a real float displacement using signed **parent direction byte ×90**
  (`IMUL`, `FILD`), adds parent `+0x44`, subtracts parent child's
  `+0x44`, then calls the actual existing original *cdecl float*
  `00412D90` absolute-value routine. It `FMUL`s native float global
  **`00659724`** and stores actor `+0x50`; the genuine native
  comparison `FCOMP 00657D14; TEST AH,5; JP` clamps it to 4.0f.
  Then actor velocity becomes 20.0f, scale 1.0f and color FF.
- Each tick subtracts true float global **`00657480`** from velocity
  `+0x54`, updates `+0x44` by the signed direction and speed,
  and advances `+0x48` using the actual x87 field operands. For
  signed stage `<2`, its stage motion increases `+0x30` using
  global **`00657CC0`**, then compares the true sum of actor `+0x48`
  and `+0x54` against native float global **`0065782C`**.
- On native contact, the **`0x340` case** invokes actual original
  parent `00453A70` effect IDs **0x338 and 0x33A**, then parent
  `00453D40(8)`; the **`0x341` case** instead spawns **0x342 and
  0x344** and invokes parent **`00453D40(10)`**. Both call native
  `0040FAC0(0x33B)`, zero the actual four actor motion fields and
  leave through the original common exit.
- If contact is not reached, the real current-action query
  `0040FA30` conditionally invokes state callback `0040FB40(1)`.

The original C++ ABI helper at `00412D90` is consistent with the
existing independently reconstructed caller signature
`float __cdecl AbsFloatAt00412D90(float)`. This is validated by the
*physical* `REL32` at native ordinal 39, the preceding x87 FSTP
argument, and the subsequent original x87 return value, not assumed
from old documentation alone.

## Actual normal C++ expression order mattered

A naive signed-direction expression compiled the parent `+0x44`
pointer load **after** its integer-to-FPU conversion, unlike the true
native ordinal 25–32 register/operand order. The natural C++ expression
`*(&PF32(+0x44)) + static_cast<float>(PS8(+0x66)*90)`
preloads the actual parent reference before the signed direction FILD,
matching original `MOV ECX,[parent]`, `MOVSX`, `IMUL`, `FILD`, `FADD`.

Similarly, naive collision C++ `F32(+0x48) + F32(+0x54)` generated
`FLD` before its independent receiver reload. Writing the genuine
lvalues `*(&F32(+0x48)) + *(&F32(+0x54))` makes the native
`MOV EAX; MOV ECX; FLD [EAX+0x48]; FADD [ECX+0x54]` order occur
naturally. **13 real alternate C++ compiler experiments** included
volatile, reversed operands, double casts, const references and
comparisons; only real original-codegen order was selected, without
artificial locals, manual ASM, stack padding or original byte grafts.

The new source passes strict original machine grammar for **both**
complete actions: 159/159 authentic x86 registers, FPU semantics,
actual per-instruction lengths, branch graph and true physical
`REL32`/`DIR32` call/global fields. There are **13 genuine zero-addend
COFF references per action**, including real `00412D90` and float
globals `00659724`, `00657D14`, `00657480`, `00657CC0` and
`0065782C`. No newly tolerated instruction-order exception exists.

## Entire one-switch source and correct whole-giant accounting

The tracked original-backed targeted verifier
[`scripts/verify-characterobject-abs-motion-f582.py`](../scripts/verify-characterobject-abs-motion-f582.py)
freshly compiles only ONE affected normal MSVC7.1 C++ source translation
unit from [`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
with `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, then compares all
**29 complete native real action cases** and their actual original
PE-bounded CODE, typed COFF call/globals and whole switch DATA.

| Actual complete game-action cases within one nonexact giant | Original x86 instructions | Original internal CODE bytes (no independent exact credit) | Genuine typed COFF fields | New-source proof |
| --- | ---: | ---: | ---: | --- |
| 27 previous real actions through `0x33F` | 3,444 | 12,765 B | 240 | Previous exceptions retained |
| New `0x340` | **159** | **597 B** | **13** | **Strict original order** |
| New `0x341` | **159** | **597 B** | **13** | **Strict original order** |
| **Total 29 native real action bodies** | **3,762** | **13,959 B** | **266** | Whole giant still nonexact |

The entire original physical jump table retains all **60 real
zero-addend COFF DWORD handler fields**, duplicate/default-partition
identity, **198 byte-identical compressed index bytes** and the
separate **438 native after-RET DATA bytes**. Prior original F573/
F574/F578 three bounded read-only source-order differences and
F576's authentic +18/+18 wider EBP temporary encodings remain
explicit; neither new case adds an exception.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-abs-motion-f582.py
# Scope-safe older source regression in same newly expanded switch:
scripts/repo-python scripts/verify-characterobject-parent-scatter-f581.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

New source/COFF/PDB and case summary live under ignored
`.analysis/f582-characterobject-abs-motion-source/` and native
full instruction alignments/negative C++ trials under
`.analysis/f582-characterobject-native-actions/`. The **13,959
native internal CODE bytes remain inside the wholly nonexact
33,293-byte original giant**; these are not 29 separately accepted
functions. No accepted split/whole CODE or DATA credit, no full
all-unit cold replay and no external Oracle receipt.

## F583 follow-up: original state and fade actions 0x342..0x344

The same natural VC7.1 source now contains three more genuine complete
original game actions `0x342` 87/338, `0x343` 80/309 and `0x344`
66/229 (x86 instructions / inner CODE bytes). They have strict native
GPR/x87/branch/width grammar and their actual original physical
COFF refs. F582's existing original-backed source verifier still
rechecks its prior 29 whole case bodies; [F583's original state
study](CHARACTEROBJECT_STATE_LEAVES_F583.md) independently verifies
all 32 without new read-only swaps. Whole boss CODE still nonexact.
