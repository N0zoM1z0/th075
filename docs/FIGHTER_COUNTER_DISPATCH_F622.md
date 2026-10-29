# F622 — original unsigned collision counter OR in native action0x62, two strict giant cases

**Actual pinned Japanese TH075 1.11 PE, ordinary MSVC VC7.1 natural C++
inside whole original-shaped giant `Advance()` translation units.**
The original target SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Neither the complete giant parent nor an independent game function is
accepted exact by an internal switch case reconstruction.

## Original native control-flow discovery: four-way unsigned OR, not AND

The physical original second packed switch maps action `0x62` to a
real jump-table DWORD, followed by `0x63` at the next dense slot.
Independently decoding the actual PE complete case exposes two
nearly identical collision guards: one if the **signed** direction byte
at `this+0x66` multiplied by the signed 32-bit component at `+0x4DC`
is **positive**, another if that product is **negative**.
For either sign, the original tests four distinct **unsigned**
32-bit status fields `this+0x4E8`, `+0x4EC`, `+0x4F0`, `+0x4F4`.
The true native x86 conditional edges at ordinals 8/11/14 are `JA`
**directly into** the 16-bit counter assignment at ordinal 18/19.
The final original ordinal17 `JBE` **skips that assignment**
if the fourth field is zero. The second mirrored set of native
ordinals 28/31/34/37 behaves identically.

Therefore the authentic game condition is:

```cpp
if (statusE8 > 0 || statusEC > 0 || statusF0 > 0 || statusF4 > 0)
    motionCounter = directionProduct > 0 ? 1 : 2;
```

These snippets explain the physical native behavior; the actual
tracked [natural C++ case source](../probes/FighterCounterDispatch62F622.inc)
contains the two explicit original sign paths, **no helper-based
abbreviation**, and real typed unsigned member accesses. An initial
plausible reverse-engineering attempt instead required the first
three fields to be zero and only the fourth positive. That source
compiled to the same **65 native-shaped x86 instructions, 249 bytes,
and four authentic COFF targets**, but the original `JA` edges were
wrong (`JNE` to ordinal20 rather than `JA` into ordinal18), proving
that instruction-count and relocation-count equality do NOT ensure
faithful control flow. The PE evidence forced the semantic correction.

After setting signed-short counter 1 or 2 at the original owner slot,
the genuine native frame state query `0040FA30` compares to `+0x70`.
If equal it calls real action transition `0040FAC0` with `0x5F`, then
conditionally with `0x5D` or `0x5E` for counter 1 or 2. This gives
**four true physical `REL32` fields**, at original x86 ordinals
41,49,56,63, to actual game callees `0040FA30` and `0040FAC0`
(three calls). All actual original target addresses, instruction
positions, source COFF symbol identities and zero addends are checked.

## Two strict original native case bodies and genuine register-phase negatives

The real original game fighters have different surrounding source
contexts. A fresh ordinary VC7.1 C++ `Advance()` compile makes the
complete original case0x62 **65/65 exact GPR/x87/CFG role matches**
for exactly two actors:

| Whole original giant, still NONEXACT | Original full case0x62 CODE | Original native x86 roles | Actual typed COFF fields | Native source owner |
| --- | ---: | ---: | ---: | --- |
| `00564BE0` | **312 B** | **65/65** | **4** | `+0xF00`, 21 authentic widened `EBP−0x88` receiver MOV loads |
| `005AEEC0` | **249 B** | **65/65** | **4** | **`+0xEFC`** signed-short action counter |
| **F622 strict internal source study** | **561 original bytes** | **130** | **8** | **Zero new whole-function credit** |

These strict results were compiled in their actual whole-source
fighter probes with the later, currently nonexact switch cases left
as honest placeholders, not in artificial standalone little helper
functions. The same original game-source semantics, also cold-built
as negative controls, still have a **40 native register/CFG-role
mismatch** in original fighter `0045DD70`, despite correct
65/65 x86 counts and 249-byte widths, and a **10-role mismatch**
in actor `004AC040`, whose original has a genuinely different
**25-instruction/87-byte** case without either collision-flag guard.
Neither of these negative source bodies is called an exact case.
Other actors' register phases also remain unresolved.

Every selected source is freshly compiled using pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. The verifier **also** reruns
native PE/COFF strict source checks for all **30 previously verified
internal fighter case bodies** and the original complete separately
owned after-RET packed jump DATA on that *same newly compiled OBJ*.
The generated source's 65/65 original instruction positions, correct
wide versus compact physical x86 widths and all four real typed
call relocations are then individually rechecked against the original
native `th075.exe`.

## Corrected the old shared switch-dispatch verifier, not weakened it

The prior general-case function
[`verify-fighter-actionzero-natural-source.py`](../scripts/verify-fighter-actionzero-natural-source.py)
had incorrectly assumed **every `JA` in the entire fighter function**
is a switch-bound/default guard. The genuine action0x62 introduces
six later native `JA` branches that have nothing to do with dispatch.
The old assumption rejected the otherwise correct original source
with a false "unsigned default guards" error.

F622 precisely constrains the dispatch guard search to the region
**before the last indexed `JMP dword ptr [...]`**, where all original
switch-table dispatches actually reside, and preserves both the
original number of indexed switches and the requirement that all
*real switch guards* share the same original default destination.
The complete physical after-RET table layout, dense label COFF fields,
sparse bytes and partitions are **still checked unchanged**.
Targeted regression replays of the original 50-instruction action-zero
and the F614 full ten-projectile original case on the same relevant
fighter owners pass after this correction. The generic acceptance
infrastructure and canonical exact match-unit ledger are untouched.

## Accounting and reproduction

Previously F598–F620 strictly source-backed **337 original internal
case bodies /87,046 native interior CODE bytes** across the giant
research. F622 adds precisely **two** whole original 65-instruction
case interiors /561 original native CODE bytes /130 x86 roles /
8 physical typed PE/COFF calls, making **339 strict internal game
case bodies /87,607 original interior CODE bytes**. These are
**not 339 separately accepted complete original functions**.
All eleven enclosing fighter giants and the other original giant
functions remain nonexact, the official authored exact ledger remains
**943 complete functions /862,726 original CODE bytes**, and no
all-unit cold replay, target executable patch, invented ABI,
relocation masking, or external Oracle acceptance was performed.

```bash
scripts/repo-python scripts/verify-fighter-counter-dispatch-f622.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-counter-dispatch-f622.py --boss 0x005AEEC0
scripts/repo-python scripts/verify-fighter-counter-dispatch-f622.py --negative-actor 0x0045DD70
scripts/repo-python scripts/verify-fighter-counter-dispatch-f622.py --negative-actor 0x004AC040
# Only the two affected exact-grammar giant sources:
scripts/repo-python scripts/verify-fighter-counter-dispatch-f622.py
scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py --boss 0x005AEEC0
scripts/repo-python scripts/verify-fighter-trajectory-burst-f614.py --boss 0x00564BE0
```

The whole newly compiled normal C++ probes, physical COFF/PDBs,
original native jump edges, complete-source typed target receipts,
and negative experiments are in ignored `.analysis/f622-counter-dispatch/`.
The separate genuine 40+ F621 source-expression experiments for the
still-unmatched `0x5D` register cycle are preserved in ignored
`.analysis/f621-giant-5d-phase/` and are not claimed strict matches.
