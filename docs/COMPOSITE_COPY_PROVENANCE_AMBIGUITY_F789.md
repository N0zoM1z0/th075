# F789 — Both historical explicit and compiler-implicit sources generate exact native copy CODE

**Original origin classification remains UNKNOWN, by independent
positive counterexamples rather than by default assumption.**

Original whole methods:
- `004591E0..00459380`: complete 417B/128 native x86,
  six typed physical PE fields including original EH handler.
- `0045AAE0..0045AC4F`: complete 368B/118 native x86,
  two authentic nested-sequence assignment calls.

F787/F788 showed that a truly *compiler-synthesized* copy
constructor and assignment operator for a provisional 116B
composite can reproduce these two full original functions
exactly, including all 785 native CODE bytes outside the
independently relocated 32 field bytes.

That still did not prove historical ownership. F789 therefore
generated **two separate, explicitly user-defined natural C++
methods** implementing exactly the observed 116B object-member
semantics:

- `CompositeValueF787::operator=(const CompositeValueF787&)`
  explicitly assigns its initial 16B POD block, the observed
  individual word/dword/byte fields, its separate 16B POD block
  at offset `+0x44` and the two nested sequence owners.
- `CompositeValueF787(const CompositeValueF787&)`
  explicitly initializes the exact same members in native
  order, including the first 16B member's nontrivial destructor
  that requires original copy-construction EH state.
  It is normal member initialization, **not** a fabricated EH
  instruction or a target-byte body.

One complete VC7.1 pinned compiler build per explicit method
gives the *same original physical machine code* as the two
entire compiler-implicit methods:

| Original | Explicit source | Original-machine nonfield | Native actual fields |
| --- | ---: | ---: | ---: |
| `004591E0` | 417B / 128 x86 | **393/393** | **6/6** |
| `0045AAE0` | 368B / 118 x86 | **360/360** | **2/2** |

The tracked verifier proves that **no generated COFF function
section was truncated**, checks the physical original target
identity, all original PE/COFF offsets/kinds/zero addends,
the native call destinations, and the complete nonrelocation
machine bytes. Source methods and objects are regenerable
under the ignored research folder.

```bash
scripts/repo-python scripts/verify-composite-source-ambiguity-f789.py
```

These are **positive provenance counterexamples**: codegen
alone cannot decide whether the original historical copy
constructor/assignment were explicitly user-authored or
compiler-implicit. Neither game-authored nor excluded/compiler
attribution can be conclusively established. Leave both
`config/function-origins.csv` records as `unknown`; the
official 979 accepted whole game functions and 868,243 CODE B
remain unchanged. Do not mask relocation fields for accepted
CODE credit or replay all units.
