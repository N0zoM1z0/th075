# F967 — Real signed profile selector bytes shared by six additional original source objects

The pinned Japanese TH075 v1.11 original executable
independently demonstrates two **signed 8-bit**
selection fields at receiver **this+0x16AC4** and
**this+0x16AC5**. F954 already reconstructed this
actual two-byte borrowed view in the progress/selection
and battle-pause sources, but six other entire original
game source translation units still used unrelated
raw signed-char reinterpret_casts.

The source now consistently reuses the already
strict-size/offset-checked
[`ProgressSelectionKeysF954.hpp`](../src/ProgressSelectionKeysF954.hpp)
without instantiating or reconstructing the complete
historical giant profile object. Independently
disassembled original physical PE instructions
show actual `MOVSX BYTE PTR [receiver+16AC4h/16AC5h]`
in each relevant original native function:

- **ProgressRecordLeavesF213**: original 109-B
  RaiseSelectedValue and 90-B IncrementSelectedRecordCount,
  both using original signed character `0x17F0`
  and difficulty `0x5FC` record selection.
- **GameProgressIncrementSelectedRecordF535**:
  complete original 92-B record count function
  using the genuinely required **postfix**
  `selectedCount++`, not an equivalently valued
  prefix or double-assignment that would regress
  real VC7.1 GPR evaluation order.
- **KnockoutProgressF172**: four complete small
  card-record flag/counter/value leaves
  (40–79 B) use the true signed fighter index.
  The full **1,150-B ResolveKnockout** source
  remains otherwise unchanged and is cold-replayed
  because it shares its changed object.
- **ProfileSelection454D00**: complete original
  79-B selected word counter leaf.
- **ProfileSelectionLoadWorkingF403**: original
  85-B `memcpy` 8-byte restore, which is the
  reverse data direction of the previously
  accepted F274 `memcpy` record store.
- **SinglePlayerOptions438670**: original 53-B
  progress card value read and **596-B** parent
  options rendering function in the same object.
  The renderer's behavior and source are untouched.

Source grammar, actual signedness, native
offsets, originally correct postfix evaluation,
real record strides, call ABIs and external
COFF symbols are preserved. No fabricated
class padding or stack locals, no assembly
or native-byte patching.

## Exact affected units only

After **4/4** representative full-original native
cold pilot builds passed (including the 1,150-B
knockout and 85-B memcpy restore), the canonical
per-unit replay was run ONLY on the complete
original units whose `source` is one of the
**six modified C++ translation units**. The
actual pinned VC7.1 compiler regenerated all
source objects and checked each entire callable
game CODE range, every PE/COFF relocation
offset/type/symbol/addend/destination and all
nonrelocation instruction bytes.

| Changed original source | Complete accepted units | Native accepted CODE B |
| --- | ---: | ---: |
| ProgressRecordLeavesF213.cpp | 2 | 199 |
| GameProgressIncrementSelectedRecordF535.cpp | 1 | 92 |
| KnockoutProgressF172.cpp | 5 | 1,356 |
| ProfileSelection454D00.cpp | 1 | 79 |
| ProfileSelectionLoadWorkingF403.cpp | 1 | 85 |
| SinglePlayerOptions438670.cpp | 2 | 649 |
| **Total** | **12/12 exact** | **2,460 B** |

Canonical native receipt:

    Cold replay: 12/12 exact units across 6 objects

The exact list of 12 unit IDs is obtained from the
six matching `source` values in
`config/match-units.toml`; the target-original
proof transcript is preserved in ignored
`.analysis/f967-record-keys/all-12-cold.log`.
No other 979-unit cold replay was run.

**All 2,460 bytes were ALREADY accepted whole callable
game CODE before F967. These are source semantics
and genuine native field ownership improvements,
not newly credited exact CODE or functions.**
