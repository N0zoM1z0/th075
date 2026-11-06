# F1148 — All 1,834 original direct branch targets recovered

The one original 81,539B/17,435-x86 `0050A580` callable remains
NONEXACT. Its ordinary complete C++ now reproduces every original
direct intra-function branch destination by whole-instruction ordinal.
The live verifier requires zero differences, retaining the independently
SHA-verified original PE as the reference.

| Case / branch ordinal | Original destination | Previous destination | Recovered behavior |
| --- | ---: | ---: | --- |
| 35D /13, 17 | 49 | 44 | Increment signed +0xD8 only during stage 1/frame 0, after spawning 0x330 |
| 35E /155 | 308 | 323 | Stage<=0 skips homing but still performs the final polar velocity update |
| 391 /124, 130 | 136 | 153 | The left-bound reflection check is independent of the right-bound reflection check |

For 391, both directional checks remain within the original scale-equality
and difficulty>1 guard. A failed positive-X-velocity or right-bound condition
now reaches the negative-X-velocity/left-bound check, rather than skipping
reflection entirely. No helper, padding, fake local or machine-byte patch
was introduced.

Cold verification of only the affected whole parent passed. All 17,435
ordered original mnemonics, 1,834 direct jump destinations, 92 afterRET
DIR32 target partitions and 199 sparse bytes were checked. The 82 strict
interiors retain 16,090 mnemonic/GPR positions, 1,246 physical external
PE fields and 2,964 scalar immediate positions. Eight PE-verified
interiors remain GPR-provisional. The separate 391 still has two reversed
x87 constant-load fields and four associated GPR-role differences.

The selected whole source emits 81,572 CODE bytes (+33 versus original),
still with wrong 0x3A4 frame and saved-this EBP-0xDC instead of original
0x3A0/EBP-0xAC. Restoring the longer stage/frame guard branch adds four
bytes naturally. Original whole-function exact credit remains zero;
the accepted 979 units and 868,243 original CODE bytes are unchanged.

Reproduce only this parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Previous 35D/35E/391 source, before-COFF and receipts, native disassembly,
the intermediate two-debt summary and final zero-debt verifier log are
retained under ignored `.analysis/f1148-native-35d35e-cfg/`.
