# F781 — Four native action exits converge on the real shared getter

**Full-parent source improvement; not an independently exact giant.**
The pinned Japanese TH075 v1.11 original `0x00543210` owns
58,294 callable CODE bytes plus 943 bytes of switch jump DATA after
RET. The tracked `scripts/verify-fighter-shared-getter-f781.py`
rebuilds *one entire* native-shaped VC7.1 parent, never truncating
its cases or invoking a corpus-wide cold replay.

## Original physical observations independently re-read

Native Capstone disassembly (confirmed against the original hash)
identifies **only these four** immediate JMPs entering original
`0x005515BA`:

| Native branch | Action | Original destination |
| --- | --- | --- |
| `0x00543462` | 0 | `0x005515BA` |
| `0x005435EA` | 2 | `0x005515BA` |
| `0x005436CD` | 4 | `0x005515BA` |
| `0x005436DC` | 5 | `0x005515BA` |

The shared block is exactly eight original bytes:
`MOV ECX,[EBP-0x44]` followed by the original call to
`0x0040FA30`; it immediately enters the four-byte epilogue at
`0x005515C2`. In contrast, the authentic shared default at
`0x00551598` has a 32-B get/compare/transition guard, then a
two-byte JMP at `0x005515B8` that skips the getter; other normal
case exits also return through the epilogue, **without** this call.
Previously tried near-length controls which ran the getter after
*every* switch case had the wrong native control flow and were rejected.

## Recovered C++ and compiler evidence

The four actual early case exits now use `goto native_shared_getter;`
with the `probes/FighterEarlySharedGetterTailF781.inc` expression:

```cpp
    return; // ordinary switch breaks go directly to the epilogue
native_shared_getter:
    GetNativeActionAt40FA30();
```

The common action getter is real source behavior, not an artificial
padding call. Source generation inherits F778's 239-aliased default
logic and the prior C8–CE/1F6–1F8/2DB/2F8–2FB native gameplay.
One full target-shaped VC7.1 build revalidates:

- All four source jumps at their *same function-relative* native
  locations, targeting only the generated shared getter.
- **46 original suffix bytes, 16 x86 instruction identities and sizes**,
  including three independently decoded physical CALL fields to
  `0x0040FA30`, `0x0040FAC0`, `0x0040FA30`.
- All **68 true PE/COFF fields** across the original 058/059/060/061/063
  complete case extents. Original action 058's 469-B strict nonfield
  interior is preserved, and 059/060/061 remain 19/98/101 genuine
  source-operand differences. Original 063 is 706 B versus 705 emitted
  and still has three native CMP register-width differences.
- The **943 original afterRET DATA bytes**, all 156 physical DIR32
  relocations and all 319 other native sparse-map bytes (not CODE).

The new whole-parent code size is **58,293 / 58,294 B** and the
complete source/native x86 counts are **16,471 / 16,471**. The one
remaining *length* byte is native 063 CMP-width phase, **not** a
license to crop or pad the original. The four genuine original
register differences in the default guard and many other physical
operand bytes remain; **no whole-function exact credit** is entered
into `config/matches.csv`. 979 previously accepted callable exact
units remain untouched.

To reproduce this one changed giant:

```bash
scripts/repo-python scripts/verify-fighter-shared-getter-f781.py
```
