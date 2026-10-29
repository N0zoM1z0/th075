# F538 — whole native action-zero case across all eleven multi-switch bosses

**Original-Japanese TH075 v1.11 evidence only, NOT matched whole C++ or
partial CODE credit.** This extends, without duplicating, [F537's full
7,152-entry fighter action table](FIGHTER_ACTION_CASE_RESOLUTION.md).
The original PE is pinned to SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
All eleven entire 43K–83K multi-switch controller bodies are validated
against their independent full native CODE hashes before their contained
case-zero bodies are read. No source compiler or replay is invoked.

## Physically complete action-zero case boundaries

The *first two independently verified original DWORD destinations* of each
multi-switch boss's eleven-slot, zero-based first table delimit the entire
original action-zero case, not a guessed snippet up to the first branch.
Original bytes are then freshly decoded to contiguous x86 instructions.
Every one of these eleven real cases has **50 instructions** with an identical
complete mnemonic sequence, **18 x87-related instructions**, **three real
calls to `00453E20`**, **14 genuine owner-pointer reloads** and native
member observations `+0x3AC` (signed byte flag) and `+0x50` (float).
All eleven refer to original x87 globals `0065782C`, `00657478`,
`00658050`; these are physical operand observations, not a proved
whole owner layout or equivalent per-character behavior.

| Complete original boss | Native case-0 start | Case-0 end (exclusive) | Native CODE | Receiver EBP slot | Case SHA256 |
| --- | --- | --- | ---: | --- | --- |
| `0x0045DD70` | `0x0045DEE9` | `0x0045DF9D` | 180 | `EBP-0x34` | `1a8a683ca581a3bc6461625deac676a38044261e95d9d4735a1e062b06e8680e` |
| `0x00486550` | `0x004866F9` | `0x004867AD` | 180 | `EBP-0x18` | `e1dc74f9f1d403e861c62446e9527114b2502346ff852d84de40f17b83cee615` |
| `0x004AC040` | `0x004AC1B9` | `0x004AC26D` | 180 | `EBP-0x64` | `204706336d8e2a69cd5538c0be7ab502cd953242ce134b375456a724c538b78c` |
| `0x004D7E70` | `0x004D8019` | `0x004D80CD` | 180 | `EBP-0x34` | `7bebc91f7d34337f137e6ffdfaeb32eb08aff64c32afea3bad5680d4907997c8` |
| `0x004F7130` | `0x004F72D9` | `0x004F738D` | 180 | `EBP-0x1C` | `55c09336673f19b9539e0e05baf0ddbe8d021f51c0423d67643e740bbbf5c71a` |
| `0x005214B0` | `0x0052165A` | `0x0052170E` | 180 | `EBP-0x10` | `afd4dd487ee2b9927fdefe6a639186d396ec2b857dc9460a18ec763f4b6b1a0d` |
| `0x00543210` | `0x005433B3` | `0x00543467` | 180 | `EBP-0x44` | `f18f87d2e8884fa2043dea35ab2f6d47e982ae22fca21ba4b735962f4258ff20` |
| `0x00564BE0` | `0x00564E10` | `0x00564EEE` | 222 | `EBP-0x88` | `e083dc658d7aaa38432a104306f71d2a18df14a41f47e267511c0c1bf95b6536` |
| `0x0058AF60` | `0x0058B10F` | `0x0058B1C3` | 180 | `EBP-0x2C` | `b4dfaec443a47bbeb00b9a46c5c2d36fbc1cded1f65a14f16832dcaefd3c71c1` |
| `0x005AEEC0` | `0x005AF069` | `0x005AF11D` | 180 | `EBP-0x38` | `2d3448d527bc9675c0e199410138fb7015df395e7c4284c1a5f2b9b9a0348869` |
| `0x005D73C0` | `0x005D7576` | `0x005D762A` | 180 | `EBP-0x2C` | `af75dba6493174b017f1dd6e710c82c08157a9a1327d050f40413ebadde5ae9c` |

The exceptional `0x00564BE0` controller emits **222** bytes rather than
180 for the *same 50 native instruction mnemonics*. Its observed receiver
local is at **EBP-0x88**, requiring a disp32 addressing form instead of
normal disp8. Exactly 14 original receiver reloads each gain three
machine-code bytes: `14 × 3 = 42`. This explains the size discrepancy
without inventing source padding or assuming the branch is functionally
different. All other ten owner slots are representable with disp8.
The branch extents belong to **still-unmatched giant originals**: do not
register them as independent 180/222-byte reconstructed functions or
credit them as accepted CODE.

## F540 natural C++ source follow-up

The original 50-instruction body has now been modeled as genuine VC7.1 C++
with signed flag, float position, float threshold/step, *double* rise,
branch-sensitive `<`/`>`, and three authentic thiscall sites. Fresh targeted
probes reproduce **50/50 instruction graphs and 9/9 original physical
call/global relocation roles**, directly for Reimu and CharacterMove and
normalized against all eleven complete original cases. See
[F540 native action-zero C++ reconstruction](FIGHTER_ACTIONZERO_SOURCE_RECONSTRUCTION.md).
No whole boss exact CODE is claimed.

## Next native-to-C++ attack surface

For the full 60,999-byte Reimu function at `0x0045DD70`, original action
zero occupies `0x0045DEE9..0x0045DF9C`; the complete 82,796-byte
CharacterMove controller at `0x004AC040` has its own action zero at
`0x004AC1B9..0x004AC26C`. Both branch to original `00453E20` three times
and use the same x87 member/global layout, but their relative jump
operands, true owner stack locations and entire function bodies differ.
The next natural C++ probe should reproduce the original signed-byte
state guard, both native x87 threshold comparisons and their ordering,
position delta, and three genuine reset/callback call sites *in the
context of the complete boss*. Matching this internal 50-instruction
signature alone is diagnostic; only exact full native CODE plus all
physical COFF references and owned jump DATA earns acceptance.

## Reproduce using the original PE

```bash
scripts/repo-python scripts/verify-fighter-boss-family.py
scripts/repo-python scripts/report-fighter-action-handlers.py --json > .analysis/f537-fighter-actions/whole-action-index.json
scripts/repo-python scripts/report-fighter-action-handlers.py --boss 0x00564BE0
```

The second command now verifies all eleven complete action-zero blocks,
their SHA256, original instruction sequence, calls, real stack slots and
encoding widths while retaining F537's exact generated 7,152-line action
index checksum unchanged:
`3a265d8d4c44fe0672fb8f8184bce18775d36a80ad4707134ed5b3ccc6e08b08`.
This is **new original code-generation knowledge**, not exact-source
progress or an external Oracle receipt. No full cold replay was run.
