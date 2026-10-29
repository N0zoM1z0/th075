# F585 — five complete original CharacterObject trajectory/game-action bodies

**Original Japanese TH075 1.11 PE and fresh pinned VC7.1 C++ source
verification, NOT accepted exact whole giant CODE.** The executable
SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

The entire original actor giant at `004EBDA0` is **33,293 CODE bytes**
plus separately owned **438 after-RET sparse switch DATA bytes**.
F585 directly rereads its pinned entire original native source,
checks the true physical sparse handler entries for all five new
cases, builds ONE complete normal C++ `Advance()` containing every
previous F572–F583 action source plus these new game actions, and
independently checks each original case's real `REL32`/`DIR32`
physical typed COFF call/global references and original target.
The other later action labels are diagnostic marker stores, NOT
original gameplay. Original nominal class type, real EBP local
lifetime and the other action bodies are still outstanding.

## Three genuine ~1.1 KB x87 and angle-based trajectory cases

The actual native `0x345`, `0x347`, `0x348` are independently
physical 286/286/289-instruction game-state bodies. Each performs
signed stage-zero transform initialization, then at stage `>5`
x87 object motion and four original independent float boundary
conditions against globals **`00659248`, `0065930C`, `00658E80`**,
resetting via native `0045B830` on invalid position.

Earlier stages implement a real float `00657CBC` motion update,
parent mode `+0xF12` transition and native `0040FB40` callbacks,
angle source **`P16(0xF10)-180` plus F32(+0xC8)** with
**actual `__ftol2` at `006406AC`**, signed angle wrap
`+180/-180` with 360-degree adjustment, `0040FB70` velocity,
and two more true float-to-long `__ftol2` conversions when
computing `F32(+0x44/+0x48)` from parent `+0xF0C/+0xF0E`
coordinates, facing byte and own velocity. The true signed
`+0xDA` speed increases until a role-dependent native cap:

| Original action | Native x86 instructions | Native original inner CODE | Real stage speed cap / increment | Native angle/velocity change | Typed PE COFF fields |
| --- | ---: | ---: | --- | --- | ---: |
| **0x345** | 286 | 1,144 B | **140 / +7** | Forward | **19** |
| **0x347** | 286 | 1,136 B | **120 / +6** | Forward | **19** |
| **0x348** | 289 | 1,153 B | **200 / +10** | Signed angle reversal | **19** |

The original `0x348` has two otherwise absent **`NEG`** x86 ops,
with a genuine `ADD EAX,180` at the first native polar call. Its
C++ uses `-S16(+0xD8)+180` for the first and `-S16(+0xD8)`
for the second `0040FB70` polar call. These are real independent
native behaviors, not a shared constant-only clone. Each source
compiles into exactly the native complete original mnemonic,
**EAX/ECX/EDX assignment**, x87/control-branch target graph and
per-instruction byte widths, not merely the original total length.

## Two separate 111-instruction parent coordinate synchronization cases

Native `0x346` and `0x349` both have **111 whole original x86
instructions /436 internal CODE bytes**, but they are separate
physical original switch handlers, not default aliases. They
initialize transform and color, clear signed parent short
`+0xF10` and set original movement speed 25.0f. During native
stages `<2` they decrement parent `+0xF10` by 3, call original
CRT **`__ftol2` twice** after loading actor float positions,
storing the converted signed shorts into true parent `+0xF0C`
and `+0xF0E` fields, subtract real global `0065747C` and clamp
against actual threshold `0065782C`. They advance actor motion
using the signed facing byte, query real `0040FA30`, reset via
`0045B830`, and write parent `+0xF12` state 0,1,2 on the
original specific frame transitions.

An important compiler-context observation: in a small isolated
C++ probe containing just the two 111-insn cases, VC7.1 generated
correct **111 instructions/436 bytes each**, but rotated their
EAX/ECX/EDX ownership roles versus original PE. After including
real ~1.1 KB `0x345`, then further *real* `0x347/0x348` source
in the **same containing `switch`**, VC7.1 naturally used the
original exact register assignments for **all five cases**.
No artificial local, patched stack slot, ASM or target machine
byte graft was used to force this context-sensitive behavior.

## Typed original PE/physical COFF and complete case boundaries

Tracked normal C++ source:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
Original-backed fresh one-TU verifier:
[`scripts/verify-characterobject-five-trajectory-actions-f585.py`](../scripts/verify-characterobject-five-trajectory-actions-f585.py).

The verifier first reuses F583's original-backed source check,
**fresh-compiling the same ONE normal VC7.1 TU under
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`**, and rechecking the
previous 32 original full game-action cases. It then independently
reads all five new entire original handler ranges directly from
the physical pinned PE DWORD/byte compressed switch, requires
complete original and new instruction counts, exact byte widths,
true GPR/x87 operands, original internal branch graph and
**all 71 genuine native physical call/global COFF records**.

Each native `CALL` and x87 absolute float operand must be matched
to a real physical `REL32` or `DIR32` source-object record at
**the exact original instruction ordinal**, with native PE target
identity, expected symbol, relocation type and **zero addend**.
In particular, the original runtime `006406AC` calls are
**verified as `__ftol2` external CRT calls**, never counted as
reconstructed game-owned CODE. The actual native calls to
`0040FBB0`, `0040FB70`, `0040FA30`, `0040FB40` and
`0045B830` are separately checked at their real physical sites.

| Whole original native cases within same incomplete giant | Native original x86 instruction roles | Original inner CODE (unaccepted) | Real typed physical COFF fields |
| --- | ---: | ---: | ---: |
| F572–F583: 32 earlier complete cases | 3,995 | 14,835 B | 283 |
| **F585: five genuine complete cases** | **1,083** | **4,305 B** | **71** |
| **Total 37 complete action bodies** | **5,078** | **19,140 B** | **354** |

The full after-RET source also reproduces **all 60 physical
original zero-addend `DIR32` jump-label COFF fields**, genuine
repeated/default-target partitions, **198 byte-identical original
compressed index bytes**, and separate **438 native after-RET
DATA-layout bytes**. Existing F573/F574/F578 bounded read-only
MOV/FLD x86 source-order swaps and two F576 original deep EBP
width differences remain explicitly nonexact; **no new source-order
exception** is introduced in these five cases.

### Reproduce only this affected native-profile C++ TU

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-five-trajectory-actions-f585.py
# Check previous original case-family independently after expansion:
scripts/repo-python scripts/verify-characterobject-state-leaves-f583.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The newly compiled single-TU COFF/PDB, compiler log and summary
are preserved under ignored `.analysis/f585-characterobject-five-native-source/`;
real 286/111/286/289/111-instruction original disassemblies,
source probes and GPR-rotation negative controls remain under
`.analysis/f585-characterobject-native/`.
The **entire 33,293-byte original giant is still NONEXACT**;
its 19,140 original inner CODE bytes are not 37 independently exact
functions and none can be adopted as standalone original CODE.
No new accepted whole/split CODE or DATA, no all-unit cold replay,
no external Factory/Oracle acceptance receipt.

## F586 follow-up: two additional large native stage actions

The same ordinary C++ switch now additionally implements original
full `0x34A` (295 original x86 instructions /1,093 CODE bytes)
and `0x34B` (278/1,012), requiring exact original native
x87 contact and raw two-DWORD argument semantics at `0040FB70`.
The F585 source verifier still independently checks its original
37 real case bodies under the larger new TU; F586 checks all 39,
including the improved genuine 0x331 native/temp width gap
18→6 bytes. See [F586 complete late-stage original source proof](CHARACTEROBJECT_LATE_STAGES_F586.md).
The whole original 33,293-byte fighter still is not CODE exact.
