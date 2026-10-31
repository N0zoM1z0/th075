# F954 — Two native adjacent signed selection indices, eleven whole functions exact

The original pinned Japanese TH075 v1.11 executable independently
shows TWO physically adjacent **signed 8-bit selection fields**
at game-profile receiver `this+0x16AC4` and `this+0x16AC5`.
They are not assumed to be a complete original profile-owner class.

Three complete small source functions in
`src/ProgressSelectionF274.cpp` prove these offsets and
original **MOVSX signed-byte** behavior independently:

| Original complete game function | Original whole CODE |
| --- | ---: |
| SetSelection at 0041A1A0 | **37 B**, actual byte writes at +0x16AC4/5 |
| GetSelectedRecordAddress at 0041A240 | **48 B**, two signed MOVSX byte reads |
| StoreWorkingEightBytes at 00416E20 | **84 B**, two signed MOVSX reads |

The selection controls in `src/ProgressPauseF174.cpp`
independently read the SAME native signed values,
using the original fighter record stride `0x17F0`
and difficulty stride `0x5FC`: native 00441FEA,
0044201A, 004451DA/ED, 0044521A/2D,
0044525A/6D and 0044529A/AD. These include
two complete original 44-byte read leaves,
two 55-byte writes and two 50-byte gets.
The two source translation units also contain
two larger existing exact pause/input policies,
which are preserved unchanged in semantics.

The new [`ProgressSelectionKeysF954.hpp`](../src/ProgressSelectionKeysF954.hpp)
models ONLY this **borrowed two-byte native
receiver tail window**, with signed fields and
compile-time 2-byte size and second-field-offset
assertions. It is never embedded, allocated or
treated as a reconstructed original profile
class; native matrix payload fields remain
unknown. Both source files now use one actual
typed field access instead of independent
raw-pointer signed-char displacement casts.
No fake padding, asm, machine-byte grafting,
or unproven complete object layout was added.

**Canonical cold replay was limited to all eleven
whole original functions actually affected by
the two changed source files**:

    scripts/repo-python scripts/replay-exact-units.py \
      --unit progress-records-set-selection-0041a1a0 \
      --unit progress-records-selected-address-0041a240 \
      --unit profile-selection-store-working-eight-00416e20 \
      --unit progress-read-selected-word268-00441fe0 \
      --unit progress-read-selected-word394-00442010 \
      --unit progress-set-selected-value8-004451d0 \
      --unit progress-set-selected-value12-00445210 \
      --unit progress-get-selected-value8-00445250 \
      --unit progress-get-selected-value12-00445290 \
      --unit battle-poll-pause-shortcut-004456f0 \
      --unit battle-update-player-effects-00445830

Result: **11/11 entire callable original native functions
exact across TWO freshly compiled source objects,
1,238 original CODE bytes**. Every original PE/
COFF target, relocation kind/addend/symbol and
complete nonrelocated callable instruction byte
still matches. A preliminary 2/2 cold pilot also
passed. Local ignored build evidence:
`.analysis/f954-progress-selection-keys/all-11-cold.log`.

These **1,238 original game CODE bytes were previously
accepted exact**; this is an independently verified
source semantic/type improvement, NOT new coverage.
No 979-unit cold replay, no target modification.
