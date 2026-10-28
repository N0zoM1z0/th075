# ReimuFighter's original 60,999-byte action boss: verified dispatch layout

**State:** original PE research only. **Not** a reconstructed exact C++ function, no
CODE coverage adopted for this boss. These are independently verified facts about
the pinned Japanese `resources/th075.exe` v1.11 (SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`).
The provisional R063 name is `ReimuFighter::AdvanceActionStatesAt0045DD70`.

## Complete native function boundary and entry guards

- The entire real original CODE occupies **0x0045DD70..0x0046CBB6** inclusive,
  exactly **60,999 bytes**, original PE SHA256
  `b78fa89a709b1cbbafdf4310c6fd81dd68369a9fa528a1852a64bb105ee93bc2`.
- The complete Capstone x86 stream contains **16,837 instructions**, **1,026
  call instructions** and **one final `RET`** ending at `0x0046CBB7`.
  Original stack reservation is `0x380` and `this` is stored at EBP-0x34;
  these are physical x86 facts, not guesses about the original source class.
- The first early-exit guard tests the **signed 16-bit** state at this+0x82;
  another tests the signed short at `(*(this+0x2E8))+0x3BA`. A nonzero value
  on either path bypasses action handling. The action ID for dispatch is a
  signed short at **this+0x60**, sign-extended into a genuine DWORD at EBP-0x38.
- The native front-end differentiates independent state values **0x32, 0x8C,
  0x12C, 0x186 and 0x25B** separately from the six table-dispatched spans.

## Six *physical*, independently validated jump tables and compressed indexes

| Action-state input span | Indirect x86 JMP | Actual dense DWORD table | DWORD slots | Sparse byte-index table | Bytes of index DATA |
| --- | --- | --- | ---: | --- | ---: |
| `0x000..0x00A` | `0045DDCB` | `0046CBB7` | 11 | none | 0 |
| `0x033..0x063` | `0045DE05` | `0046CBE3` | 26 | `0046CC4B` | 49 |
| `0x08F..0x0D2` | `0045DE42` | `0046CC7C` | 32 | `0046CCFC` | 68 |
| `0x12D..0x136` | `0045DE78` | `0046CD40` | 10 | none | 0 |
| `0x187..0x25A` | `0045DEB8` | `0046CD68` | 32 | `0046CDE8` | 212 |
| `0x25C..0x31C` | `0045DEE2` | `0046CEBC` | 31 | `0046CF38` | 193 |

These are **142 original DWORD slots** (568 bytes) and **522 original
compressed byte-index slots**, precisely **1,090 contiguous DATA bytes**.
The tables start *immediately after* the CODE's final RET at `0x0046CBB7`
and end at `0x0046CFF8`. Exactly **seven `0xCC` alignment bytes** then
follow to the next native function's entry at `0x0046D000`.

All **142 physical DWORD destinations** were checked directly from original
PE bytes; **every destination starts an original decoded x86 instruction
within the 60,999-byte function**. There are **139 different destination
addresses**; duplicate targets are real shared defaults, not bad provenance.
All 522 byte-index values are less than their respective dense table sizes,
all used indexes are represented, and each table, compressed map and the
entire owned post-RET area has an independently verified SHA256.

The original Ghidra rendering of the **same** original function has six
`switch(iVar5)` statements with **138 explicit `case` labels**: 11, 25,
31, 10, 31 and 30 by span. The compressed tables also contain true default
entries; do not confuse the label count, 139 unique jump targets and
142 physical jump-table slots. The five separated equality states above
remain outside the indexed dispatch groups.

## Real computational scale and next exactness requirements

The original entire boss has 1,026 physical call instructions. Frequently
used *original call destinations* include `0040FAC0` (169 references),
`00453A70` (164), `0040FA30` (135), `0040FB40` (113), `00453E20`
(105), `00453D40` (77), `00453D60` (55) and `0046D000` (52).
These are **call occurrences**, not authored CODE credited for the callees.
The six dispatch groups need native MSVC7.1 C++ switch lowering with their
exact compact jump-word and byte-map layouts; the five singled-out states,
physical local `EBP-0x38`, real float x87 pipelines, original secondary
action timers and resource/FX callees must then be reproduced across the
**entire** 60,999-byte function before any exact match or credit is claimed.

The full provisional native Ghidra text (5,393 lines / 238,909 bytes) is
retained in `.analysis/f493-reimu-megaboss/original-native.c`, along with
the PE-backed verifier output. Its C-like names and casts are hypotheses;
**original PE instructions, addresses and relocation evidence are the authority**.

### Reproduce the original evidence without cold replay

```bash
scripts/repo-python scripts/verify-reimu-action-dispatch.py
scripts/repo-python scripts/ghidra.py decompile \
    .analysis/f493-reimu-megaboss/original-native.c 0x0045DD70
```

The first command checks the pinned target, the **entire original CODE
SHA256**, instruction count/RET, all six jump instruction operands,
every jump-slot boundary, every destination's *instruction boundary*, all
sparse indexes, exact whole DATA digest and final padding. The script
reads but never alters the executable. It does **not** build or cold replay
any source unit. There is currently no full exact C++ Reimu function and
no external Oracle result; the 1,090 table DATA bytes are **not CODE credit**.
