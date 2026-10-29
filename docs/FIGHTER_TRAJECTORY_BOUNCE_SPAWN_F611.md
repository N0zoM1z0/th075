# F611 — original double-spawn bounce action0x4A in the final two fighter giants

**Real pinned Japanese TH075 1.11 PE, ordinary VC7.1 source, complete
native case x86 and PE/COFF evidence; both enclosing game functions
remain NONEXACT.** Executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
F610 recovered native action0x4A as 119 x86 /434 or wide 556 inner CODE
bytes for nine original regular fighter giants. F611 independently
reconstructs both complete *other* action0x4A native subranges in
`0045DD70` and `0058AF60`: **165 original x86 instructions, 589
original CODE bytes, and 21 true PE/COFF typed fields per fighter**.
Their exact physical boundaries are real native second-switch packed
dense DWORD slots 15 (0x4A) and 16 (0x4C), not partial code cutouts;
after-RET table DATA is still separately owned.

## Two genuine original one-shot projectile paths

Compared with the ordinary F610 bounce action, each special native
case has **46 additional real machine instructions /155 original
inner CODE bytes**. The extra logic is not padding or a compiler
prologue variant:

- At original stage `+0x62 == 1`, frame `+0x64 == 0`, and signed-short
  one-shot flag `+0xF0C == 0`, set the flag to 1 and spawn the original
  projectile using real five-argument game `thiscall` `00453A70`.
- Independently after `ContactAt454EE0()` and x87 comparison of
  float `+0x50` with native global `006590C0`, the original bounce
  branch checks **the same +0xF0C one-shot flag again**, conditionally
  generates the original projectile and only then changes native action
  to `0x4C`, scales the negated position using float `00657F74`, sets
  15.0f/0.5f motion and invokes the genuine trajectory/game helpers.

Actual original projectile kind/side differs between fighter parents:
`0045DD70` uses **`0x3B7`, side 1, stage1/aux2/late5**;
`0058AF60` uses **`0x3E7`, side 0, stage2/aux3/late5**.
Both paths pass the original signed byte at `+0x66`, real 32-bit
coordinates `+0x44/+0x48` and actual `this` receiver. This real ABI
is verified from original `PUSH`/`MOV` order and typed source COFF
positions, not guessed from old class documentation.

The remainder retains the genuine native bounce reflection and
post-bounce x87 ground test, plus **two real CRT `__ftol2` calls** to
`006406AC` to store the adjacent signed short trajectory values
`+0xF00/+0xF02`. Unlike most regular F610 cases, these two original
fighters prepare action `0x16` **after** their landing trajectory
initialization, not before the float-to-short conversions. Their
original 0x49 landing predecessors have a single projectile branch;
F611 correctly reproduces **two** guarded projectile sites on 0x4A.

## Full original native action source and strict targeted verifier

Tracked natural C++ source:
[`FighterTrajectoryBounceSpawn4AF611.inc`](../probes/FighterTrajectoryBounceSpawn4AF611.inc).
The source uses original-backed real lvalues and typed C++ control flow
rather than ASM, fabricated temps, fake locals or raw machine byte
patches. It compiles with pinned MSVC VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, with only the selected whole giant
translation unit built freshly for each proof.

[`verify-fighter-trajectory-bounce-spawn-f611.py`](../scripts/verify-fighter-trajectory-bounce-spawn-f611.py)
reads complete original PE function bounds/165 x86, verifies the two
`0xF0C` writes, actual stage and projectile IDs, the native register
and x87 instruction roles and all original instruction byte widths.
It reads both native projectile `00453A70` calls plus **19 other
actual physical native targets**, checks the full source object has
exactly 21 matching zero-addend `REL32`/`DIR32` physical COFF fields
at the correct instruction ordinals with the correct symbols. It
also independently reruns the earlier strict F598/F600/F603/F606/F608
checks on **all previous 27 original native game case bodies**, and
checks the complete real separately owned after-RET switch DATA in the
same newly built original whole-parent C++ object.

| Original whole giant, still nonexact | Native entire case0x4A | Original x86 roles | Original typed COFF targets |
| --- | ---: | ---: | ---: |
| `0045DD70` | **589 B** | **165** | **21** |
| `0058AF60` | **589 B** | **165** | **21** |
| **F611 total** | **1,178 original inner CODE B** | **330** | **42** |

With F610, **all 11 real native action0x4A subranges** are now
source-backed: **1,401 original x86 roles /5,206 internal original
CODE bytes /213 physical typed PE/COFF targets**. Cumulatively since
F598 the selected giant original research now covers **308 internal
game case subranges /76,167 original native CODE bytes**, all still
embedded in eleven entire *nonexact* fighter `Advance()` functions.
These are NOT 308 newly accepted full functions or 76,167 added exact
whole-function bytes. The official ledger is unchanged at **943
complete exact authored functions /862,726 native CODE bytes**; the
other authored giant and three small whole functions remain incomplete.
No all-unit cold replay, executable patch or external Oracle receipt.

## Selected local reproduction (never all-unit cold replay)

```bash
scripts/repo-python scripts/verify-fighter-trajectory-bounce-spawn-f611.py --boss 0x0045DD70
scripts/repo-python scripts/verify-fighter-trajectory-bounce-spawn-f611.py --boss 0x0058AF60
scripts/repo-python scripts/verify-fighter-trajectory-bounce-spawn-f611.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

New normal compiler objects and all actual original native case/COFF
receipts are under ignored `.analysis/f611-fighter-bounce-source/`;
source variant trials and per-instruction evidence are in
`.analysis/f611-bounce-spawn/`.
