# F545 — eleven full-size original fighter controllers: six natural C++ opening actions each

**Research and native compiler proof only, not exact reconstruction of any
whole giant fighter.** The pinned Japanese user-supplied `th075.exe`
1.11 SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The native-PE-only [22-boss fingerprint audit](FIGHTER_BOSS_FAMILY_DISPATCH.md)
and [complete F537 action-to-original-address lookup](FIGHTER_ACTION_CASE_RESOLUTION.md)
are checked for each original function. This advances the genuine natural
VC7.1 C++ work in [F541](FIGHTER_ACTIONZERO_FAMILY_CODEGEN.md) and
[F542](FIGHTER_ACTIONONE_FAMILY_CODEGEN.md) to **all six original opening
actions (0 through 5) of each of eleven separate huge multi-switch bosses**.

## Native original facts, no guessed case bounds

The seven *real* original DWORD case addresses in each first 11-slot switch
delimit exactly six distinct contiguous instruction ranges. For each of the
11 independent original fighter owners, original actions **0 and 2** have
**50 x86 instructions**, actions **1 and 3** have **60**, and actions
**4 and 5** have **3**: **226 real instructions per fighter**, or
**2,486 native instructions** across the eleven complete 28K–82K originals.
These six inner action ranges occupy **9,146 actual original CODE bytes**
(ten fighters ×814, one ×1,006), *inside* the **613,391 still-unmatched
whole original CODE bytes** of the eleven giant controllers. These 9,146
bytes are **not** independently compiled accepted functions and earn zero
CODE credit.

The first four cases implement the real signed +0x3AC flag/x87 +0x50
movement and reset logic; actions 1 and 3 also check actual native
`0040FA30` signed-short state against `this+0x70`, then call `0040FAC0`
with argument **2** for action 1 and **0** for action 3. Actions **4 and 5**
store *genuine, fighter-specific 32-bit float constants* into `this+0x50`
and take the actual common native exit, not a generic one-size-fits-all
speed assumption. The observed original values are:

| Original giant start | Native action 4 float | Native action 5 float |
| --- | ---: | ---: |
| `0x0045DD70` | 4.5 | -4.5 |
| `0x00486550` | 6 | -6 |
| `0x004AC040` | 6 | -6 |
| `0x004D7E70` | 6 | -6 |
| `0x004F7130` | 4 | -4 |
| `0x005214B0` | 3 | -3 |
| `0x00543210` | 6.5 | -6.5 |
| `0x00564BE0` | 4 | -4 |
| `0x0058AF60` | 4.5 | -4.5 |
| `0x005AEEC0` | 5.5 | -5.5 |
| `0x005D73C0` | 6 | -4.5 |

The original `0x005D73C0` is **deliberately asymmetric: +6.0 versus -4.5**.
This is verified from the original two real `MOV [owner+0x50], imm32`
instructions and independently regenerated as natural `POS = 6.0f` and
`POS = -4.5f`. Never impose symmetric left/right speeds by borrowing
another fighter's layout or assuming an earlier report was correct.

## Eleven independent fresh compiler-source experiments

`[verify-fighter-opening-actions-natural-source.py](../scripts/verify-fighter-opening-actions-natural-source.py)`
regenerates each native fighter's entire *switch dispatch topology* from
real original action IDs. It then writes **six genuine natural C++ source
cases**, using float literal values (never copied machine-code byte arrays
or inline assembly), and leaves the other cases as explicitly labeled
**diagnostic marker stores, not restored game code**. Each separate
translation unit is compiled serially under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`.

Across **11/11 new independently compiled probes**:

- **2,486 / 2,486** original complete-case instruction mnemonics and
  per-fighter actual EAX/ECX/EDX allocations, full x87 operand roles,
  branching, threshold constants and direct integer assignments agree
  after normalizing only the larger enclosing function's real EBP owner
  slot and unresolved diagnostic external references.
- **440 / 440 authentic physical case COFF call/global reference roles**
  agree. There are 9 each in cases 0 and 2, 11 each in cases 1 and 3;
  both direct float-store cases are truly relocation-free.
- The original full jump geometry retains **1,607 / 1,607 physical DWORD
  switch COFF relocation fields** plus all repeated/default target
  equivalence classes, and **4,502 / 4,502 byte-identical original sparse
  index bytes**. The whole original **10,930 post-RET DATA-shape bytes**
  are reproduced in the separately compiled C++ objects but not credited.

A real compiler-frame limitation remains: `00564BE0` stores its owner
at native `EBP-0x88`, outside disp8. The original six native actions
therefore occupy **1,006 bytes** while the small C++ source probe
emits **814**, with exactly the 192-byte difference explained by the
original 64 widened receiver loads across these cases (14/17/14/17/1/1).
This is verified original source-frame evidence; it is **not** adjusted
with arbitrary locals, padding, byte grafting or a fake return.

| Whole original boss | Six original CODE bytes (not accepted) | New C++ case CODE bytes | Authentic case COFF roles | Whole original table COFF fields | Original compressed bytes |
| --- | ---: | ---: | ---: | ---: | ---: |
| `0x0045DD70` | 814 | 814 | 40 | 142 | 522 |
| `0x00486550` | 814 | 814 | 40 | 163 | 412 |
| `0x004AC040` | 814 | 814 | 40 | 151 | 522 |
| `0x004D7E70` | 814 | 814 | 40 | 140 | 409 |
| `0x004F7130` | 814 | 814 | 40 | 141 | 411 |
| `0x005214B0` | 814 | 814 | 40 | 139 | 345 |
| `0x00543210` | 814 | 814 | 40 | 156 | 319 |
| `0x00564BE0` | 1,006 | 814 | 40 | 131 | 350 |
| `0x0058AF60` | 814 | 814 | 40 | 154 | 350 |
| `0x005AEEC0` | 814 | 814 | 40 | 164 | 411 |
| `0x005D73C0` | 814 | 814 | 40 | 126 | 451 |

## Reproduce with only affected probe builds

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-boss-family.py
# Independently read the original giant function and cold-compile only this source probe:
scripts/repo-python scripts/verify-fighter-opening-actions-natural-source.py --boss Reimu
# Or rebuild only the eleven new standalone source probes, serially:
scripts/repo-python scripts/verify-fighter-opening-actions-natural-source.py
```

Fresh `.cpp`, `.obj`, `.pdb`, compiler logs and original-comparison summary
are retained under ignored `.analysis/f545-opening-six-actions/`.
Existing accepted `src/`, `config/matches.csv`, `config/match-units.toml`,
`exact-adoptions.json` and historical tests are unchanged; no giant whole
source is claimed. This is material source-level work on **big functions**,
not a partial-byte match masquerading as whole-function exactness. There
is no new accepted function/byte credit, full all-unit cold replay, or
external Factory/Oracle receipt.
