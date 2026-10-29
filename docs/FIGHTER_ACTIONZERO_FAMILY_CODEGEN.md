# F541 — eleven independent natural VC7.1 C++ action-zero/whole-switch probes

**Complete original functions analyzed, but none accepted as exact C++.** This
extends the prior [F540 two-fighter C++ case-zero proof](FIGHTER_ACTIONZERO_SOURCE_RECONSTRUCTION.md)
by *compiling each of the eleven native multi-switch fighters independently*,
using its **own** original action-ID partition and natural C++ source case
instead of normalizing away another fighter's general-purpose registers.
Original input is only the pinned Japanese `th075.exe` version 1.11,
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
All **eleven entire original CODE SHA256 extents** are verified first;
these whole giant functions contain **613,391 original CODE bytes** which
are still completely unmatched. Source names and borrowed receiver type
are provisional; test-marker branches in other actions are **not restored
source**.

## Source and compiler evidence

One genuine original-like action-zero C++ case is placed in each ordinary
`switch (I16(0x60))`, selecting explicitly native nondefault and isolated
case IDs from [F537's complete 7,152-entry physical action map](FIGHTER_ACTION_CASE_RESOLUTION.md).
The action-zero case models a signed byte at receiver +0x3AC, a float at
+0x50, and two separate x87 threshold guards with the original mutation,
three reset calls, an original float subtraction and an original **double**
addition. The real original C++ labels and complete receiver layouts are
**not** assumed.

All **eleven small standalone generated translation units** are freshly
compiled, serially, under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`; this is **not** the 942-unit
cold replay and does not pretend to compile any 28–82K complete fighter body.
The verifier independently checks for **each fighter**:

- all **50/50 actual original action-zero instruction mnemonics, per-fighter
  EAX/ECX/EDX register selection, member offsets, x87 operands, comparison
  and conditional branch graph**, normalizing only the independently
  measured receiver EBP slot, external relocation fields and case exit;
- all **9 authentic physical case call/constant COFF reference roles**, with
  three `00453E20` thiscalls and six actual original float/double globals;
- **each native six- or seven-way switch group** in its natural C++ object,
  all **1,607 original-style physical DWORD table COFF references**,
  all default and repeated-target equivalence partitions, and **4,502
  byte-for-byte original compressed index bytes**;
- all **10,930 after-RET DATA bytes of original layout**, including every
  original sparse-index map. This is *data-shape/codegen evidence*, **not**
  data or CODE accepted into the exactness ledger.

The one exceptional original boss at `00564BE0` has a native `EBP-0x88`
receiver requiring fourteen disp32 loads and therefore **222** original
case bytes rather than the probe's **180**. The instruction/reg/branch
structure is nonetheless fully validated; **no fake locals or padding**
are added to the C++ experiment to force a byte count.

## Individual fresh compiled witnesses

| Original whole boss start | Complete original CODE (unaccepted) | Explicit test cases | Original `JMP`s | Original case 0 / generated | COFF table fields | Identical sparse index bytes | After-RET DATA shape |
| --- | ---: | ---: | ---: | --- | ---: | ---: | ---: |
| `0x0045DD70` | 60,999 | 143 | 6 | 180 / 180 bytes | 142 | 522 | 1090 |
| `0x00486550` | 50,735 | 158 | 7 | 180 / 180 bytes | 163 | 412 | 1064 |
| `0x004AC040` | 82,796 | 151 | 6 | 180 / 180 bytes | 151 | 522 | 1126 |
| `0x004D7E70` | 43,601 | 131 | 7 | 180 / 180 bytes | 140 | 409 | 969 |
| `0x004F7130` | 44,211 | 133 | 7 | 180 / 180 bytes | 141 | 411 | 975 |
| `0x005214B0` | 46,755 | 140 | 7 | 180 / 180 bytes | 139 | 345 | 901 |
| `0x00543210` | 58,294 | 147 | 7 | 180 / 180 bytes | 156 | 319 | 943 |
| `0x00564BE0` | 61,872 | 131 | 7 | 222 / 180 bytes | 131 | 350 | 874 |
| `0x0058AF60` | 49,230 | 146 | 7 | 180 / 180 bytes | 154 | 350 | 966 |
| `0x005AEEC0` | 71,616 | 158 | 7 | 180 / 180 bytes | 164 | 411 | 1067 |
| `0x005D73C0` | 43,282 | 126 | 7 | 180 / 180 bytes | 126 | 451 | 955 |

## Reproduce, without replaying any existing exact units

```bash
scripts/repo-python scripts/verify-fighter-boss-family.py
# Fresh serial compile and individual native/COFF comparisons for these 11 TUs:
scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py
# Narrower recheck of just one original affected fighter:
scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py --boss 0x00486550
```

Fresh generated `.cpp`, `.obj`, `.pdb`, compiler logs and summary are kept
under ignored `.analysis/f540-natural-actionzero-source/` for later
source continuation. The verifier checks the original full function before
reading its inner case, never grafts machine bytes, uses no target assembly,
never crops CODE to claim an exact unit, and never runs the all-unit replay.

**Important limitation:** this is a major C++ code-generation constraint for
**full** 43–82K fighter reconstruction, not an exact restoration of any
one giant fighter. No new `config/matches.csv`, `match-units.toml` or
`functions.csv` credit arises: the register remains **942 whole-function
cold-exact units / 862,649 accepted authored CODE bytes**. Completion
requires all other actions, natural owner lifetimes, complete native CODE
and all original COFF references to match through affected-only cold replay.
