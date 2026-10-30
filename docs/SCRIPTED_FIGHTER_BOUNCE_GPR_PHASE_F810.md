# F810 — Whole 46KB scripted fighter: genuine 0x4A bounce source rotates default GPR phase again

**Positive original-action source integration, not full giant exactness.**
The hash-pinned Japanese TH075 v1.11 original
`005214B0` fighter owns **46,755 complete callable CODE
B** plus **901 separate afterRET packed switch DATA B**.
F808's current original-backed source restored actual actions
0..10, 0x32, 0x33–0x41, 0x46–0x49 and the F806
46-B shared default/getter tail in one C++ parent,
producing 8,152 source CODE B /2,017 x86.
After adding the *real* action `0x49` the original
tail GPR roles had naturally aligned again; only
four honest saved-this EBP displacements still differed.

F810 adds the **next genuine native action `0x4A`** to the
*same* incomplete but growing original-shaped parent.
Its original second-switch dense slots 15/16 bound
`00522DD6..00522F87` as **434 native CODE B,
119 complete x86, 19 original typed PE/COFF fields**;
the following original action is `0x4C` — no
synthetic independent `0x4B` handler is introduced.

The actual stage/trajectory logic includes original
32-bit raw velocity bit-copy, real 0.8f drag
and signed `+0xF00/+0xF02` short counters,
the authentic stage-3/stage-4/late-stage-7
transitions, ground-contact bounce scaling through
genuine native `00657F74`, real contact probe
`00454EE0`, paired float-to-short conversion,
and true game state/motion callbacks. The
source is tracked natural C++ from
`probes/FighterTrajectoryBounce4AF610.inc`,
not original x86 byte grafting or forced registers.

## Fresh full-parent validation

`scripts/verify-scripted-fighter-bounce-shared-f810.py`:
1. Regenerates **only selected `005214B0`** full C++
   from F610's tracked original source and strictly
   verifies all **28** original action source bodies
   including 0x4A's native **434B/119-x86/19
   independently typed PE fields**.
2. Restores F806's native four early action0/2/4/5
   shared-getter branches, real 32B default handler
   and entire **46B/16-x86** fallback/getter suffix.
3. Recompiles the **whole affected parent** with
   pinned VC7.1 and re-verifies all **27 previous
   complete original action bodies**, true packed
   switch destinations, all **901B afterRET DATA**,
   the default suffix's three physically
   zero-addend PE calls to
   `0040FA30/0040FAC0/0040FA30`, and the four
   genuine early JMPs and their source/native
   relative positions.

The growing compiled parent now emits
**8,571 source CODE B /2,134 x86**,
up from F808's **8,152 B /2,017 x86**.
The original whole native 46,755-B function
remains far larger, so no internal case
counts as accepted independent callable CODE.

## Genuine non-monotonic MSVC register allocation

Integrating true earlier 0x4A source changes
the later default guard's compiler allocation:
the register-phase alignment seen in F808
does not hold in F810. The full 46B suffix
retains authentic original x86 opcode
**mnemonics, sizes, relative locations and CFG**,
but four **actual GPR operand bytes** again
differ at suffix-relative offsets `10/12/16/19`:

| Native original | Newly compiled parent |
| --- | --- |
| `MOVSX EDX,AX` | `MOVSX EAX,AX` |
| `MOV EAX,[EBP-10h]` | `MOV ECX,[EBP-4]` |
| `MOVSX ECX,[EAX+70h]` | `MOVSX EDX,[ECX+70h]` |
| `CMP EDX,ECX` | `CMP EAX,EDX` |

Four other authentic saved-this EBP bytes at
offsets `2/13/26/36` still differ due to
the incomplete parent's genuine `EBP-4`
stack layout versus native `EBP-0x10`.
None of these eight nonrelocated machine
bytes are ignored or claimed exact.
F807→F808→F810 is a concrete, independently
reproduced example of naturally rotating
VC7.1 GPR phases as actual preceding
gameplay cases are reconstructed. This
is not a license to hard-code x86 registers.

Targeted reproduction, *not* all-979-unit replay:

```bash
scripts/repo-python scripts/verify-scripted-fighter-bounce-shared-f810.py
```

New full source/COFF and original PE comparison
evidence reside under ignored
`.analysis/f810-scripted-bounce/`.
**No whole original fighter exact credit and
no split-case or jump DATA CODE credit**.
