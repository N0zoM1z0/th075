# F1052 — Real 0x325 three-shot loop restores downstream GPR phase; 0x32F DWORD owner copy

**Historical F1052 ten-state checkpoint:** the live parent has since gained authentic native [0x337 and 0x345 states](CHARACTEROBJECT_NATIVE_337_345_F1054.md). The ten-state byte/role totals below remain valid *for those ten original cases*, but not as the current entire source coverage total.

The SHA-pinned Japanese TH075 v1.11 `CharacterObject::Advance` at
`0050A580` remains one independently authored **NONEXACT 81,539-byte /
17,435-x86** callable with 567 separate afterRET jump DATA bytes.
F1051 reconstructed native case `0x321` and restored the adjacent
`0x322` register phase, but later states had regressed GPR allocations
because their intervening C++ behavior was absent. F1052 actually
reconstructs two more original game actions:

- **0x325**: original `0050B654..0050B821`, **461B / 100 x86**,
  genuine parent action in `(49,150)`, own animation stage before 2,
  authentic three-shot `0x3E4` loop from the *parent* at original
  `00453A70`, special parent `+0xEFA` countdown/extra `0x3E3`
  projectile, and real actor motion/frame initialization. The
  actual stage-zero branch calls native parent `00453D40(0x17)`.
  All **seven native game CALLs** and their actual PE physical fields
  are preserved, including repeated calls to the same projectile API.
- **0x32F**: original `0050D097..0050D17A`, **227B / 50 x86**,
  actual parent action `0x133` and **DWORD bit-preserving X/Y copy**
  from parent to actor, real motion/reset and action completion.
  All **three actual original native call fields** are retained.

Both new C++ sources are real switch state cases in the ONE tracked
partial C++ parent. No additional standalone function is asserted.
Original game fields and native PE call targets were recovered from
fresh pinned PE x86, not inferred merely from old trial notes.

## Genuine cross-state discovery

The original three-shot 0x325 loop has a true used C++ `shot` index
with native loop initialization, increment and branch. Restoring it
makes the normal VC7.1 compiler recover the previously missing
register phase **across six later real game actions**; this could
not be reproduced by merely adding unrelated C++ locals or a
marker at that case.

`verify-characterobject-cross-state-phase-f1052.py` compiles **four
ENTIRE natural VC7.1 partial-parent sources**: both real new
states, 0x325 only, 0x32F only, and neither. It verifies the original
whole PE hash and genuine afterRET 92 DIR32 partition /199 sparse
literal bytes before comparing authentic case x86 ordinals.

| Real native game action | Former state-missing GPR roles | After true 0x325 |
| --- | ---: | ---: |
| `0x32B` | 13/39 | **39/39** |
| `0x32C` | 19/63 | **63/63** |
| `0x32D` | 14/50 | **50/50** |
| `0x32E` | 19/63 | **63/63** |
| `0x332` | 13/35 | **35/35** |
| `0x32F` (when present) | 14/50 (without 0x325) | **50/50** |

The control with only real 0x32F and an unrecovered 0x325 retains
the poor downstream GPR phase: the real **0x325 C++ loop/lifetime**, not
simply increasing source byte size or adding one real case, causes
the cross-state improvement.

With **both** new genuine actions, all ten recovered inner source
cases now reproduce **776/776 original x86 mnemonics and 776/776 GPR
roles**, plus **56/56 physical original PE external call/global
fields**. Every actual COFF field is resolved by original physical
instruction ordinal, kind, byte offset and native target from the
pinned original PE, not by a source label alone. The original 92
DIR32 entries and all 199 sparse-map DATA bytes still agree.

| Native whole versus partial normal source | Measured |
| --- | ---: |
| Original whole callable CODE / x86 | 81,539B / 17,435 |
| Current **partial** C++ callable CODE /x86 | **4,165B / 984** |
| Ten restored original state intervals | **3,597 original CODE B /776 x86** |
| Compiled selected ten inner states | **2,792B /776 x86** |
| Original x86 mnemonics and GPR roles in restored cases | **776/776** each |
| Original physical nonlocal PE fields in restored cases | **56/56** |
| Remaining real-original width discrepancies | native large EBP-0xAC/real scratch, and long/short case branches |
| Native original full callable exact? | **No** |
| Newly accepted exact authored CODE | **0B** |

The real complete original's original stack frame is `ESP 0x3A0`
with native saved receiver `EBP-0xAC`. The current short prototype
still uses `EBP-0xC`, and its genuine float-conversion scratch
windows are correspondingly shallower; some original near conditional
branches shrink to shorts. The native case CFG and genuine call
targets remain audited, but **machine widths/absolute relocation
sites remain nonexact**. Many other switch states are still marker
placeholders and the original function is far from whole exactness.

Bounded only-to-this-Boss reproducibility:

    scripts/repo-python scripts/verify-characterobject-multi-state-f1047.py
    scripts/repo-python scripts/verify-characterobject-cross-state-phase-f1052.py
    scripts/repo-python scripts/verify-characterobject-boss321-f1051.py

The first check fresh-compiles and verifies the one current original-
shaped partial parent; the second builds four whole-parent natural
C++ controls and checks their true GPR phases; the third independently
rechecks the complete previous 0x321 native game action. All source,
COFF/PDB and actual PE receipts remain under ignored `.analysis/f1047-*`,
`.analysis/f1051-*` and `.analysis/f1052-*`. No entire 979-unit cold
replay, byte patch, GPR-asm intervention or original game splitting.
