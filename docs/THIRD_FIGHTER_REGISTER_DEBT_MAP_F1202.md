# F1201–F1202 — whole 004AC040 register debt and bounded negative controls

The selected source remains the F1200 complete
[`F1020 parent`](../probes/FighterWhole004AC040F1020.cpp): 82,796 CODE
bytes /22,721 x86, native frame 0x720 and saved-this EBP-0x64. Its complete
direct CFG, non-GPR/EBP operands, CODE destinations and owned DATA remain
verified. **No candidate source is adopted and no exact credit is added.**

Six fresh serial whole-parent controls exclude additional explanations for
the remaining register phase. A new native dispatch analysis attributes
every current GPR/width difference to its actual physical handler interval,
providing a broader work queue than the first 19 differing instructions.

## Native dispatch and complete debt attribution

The supplied Japanese original is unchanged, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The complete original function CODE hash is independently checked as
`4dced8c8583edf4b8234505793e28732e19af2adb311d0d39a755f0036e59cfc`.

The local diagnostic interprets only the original dispatch instructions
004AC07E..004AC1B8: stack selector moves, signed/unsigned comparisons,
subtractions, sparse-byte lookups and dense jumps. It enumerates the full
65,536-value signed-short selector domain, following native branch targets
and reading table bytes directly from the pinned PE. This is static analysis;
it does not run, patch or substitute the target executable.

The result has **152 distinct native entry destinations**. Independently
reading all six original dense tables yields 147 distinct destinations;
the remaining five are the native direct-comparison midpoint handlers:

| Action | Native direct destination |
| --- | --- |
| 32 | 004ACA6C |
| 8C | 004AE9DA |
| 12C | 004B1039 |
| 186 | 004B1C5B |
| 254 | 004B7825 |

Every dispatch destination is a decoded original instruction boundary.
Together with the dispatcher, shared getter and epilogue, the **155 physical
intervals cover all 22,721 native instructions**, and their debt sums are
exactly the current **6,958 GPR positions /12 widths**. These are internal
physical attribution intervals, not independently callable exact units.

| Original interval | Native start | Native x86 | Current GPR differences | Width differences |
| --- | --- | ---: | ---: | ---: |
| 25B | 004B84BA | 957 | 577 | 0 |
| 25D | 004B973A | 749 | 477 | 0 |
| 1FB | 004B6824 | 346 | 180 | 1 |
| 1FC | 004B6CCD | 346 | 180 | 1 |
| 1FD | 004B7175 | 346 | 180 | 0 |
| 1F8 | 004B5A75 | 339 | 174 | 1 |
| 1A2 | 004B450B | 309 | 171 | 0 |
| 1F9 | 004B5F05 | 339 | 168 | 1 |
| 25C | 004B9327 | 271 | 162 | 0 |
| 25E | 004BA229 | 236 | 153 | 0 |
| 258 | 004B7BB0 | 212 | 137 | 0 |
| 259 | 004B7EF2 | 212 | 137 | 3 |
| First divergent interval 59 | 004ADEFA | 95 | 19 | 0 |

The two largest intervals account for 1,054 remaining GPR differences.
Their real 36-call source bodies are already present; preserve them rather
than replacing them with loops or markers. The complete map, including the
first difference in each interval, is retained locally for further work.

## Six complete-parent controls

All compiles use pinned VC7.1 and the selected explicit profile
`/Od /Ob0 /Gy /GR- /GX /GS /Zi /I src /I probes`; only the tuning control
adds `/G7`. The complete audit compares every native instruction, branch,
EBP operand, CODE destination and owned table after each compile.

| Meaningful source/profile hypothesis | Complete observed result | Decision |
| --- | --- | --- |
| 58 landing/nonlanding `if/else` instead of an early switch break | Same length/count and GPR debt; one native direct target regresses | Reject |
| `/G7` tuning | Entire CODE+DATA and all 2,352 COFF records identical | No profile change |
| 59 uses 0.0f /40.0f /100.0f literals instead of external data names | All CODE+DATA bytes identical; ten COFF symbol-name changes with unchanged field geometry and offsets | No adoption |
| 58's four actual native epilogue exits use `return` | Entire CODE+DATA and COFF identical | No adoption |
| 259's discarded signed-short counter operations use postfix syntax | Entire CODE+DATA and COFF identical | No adoption |
| 259 uses `+=1` /`-=1` for those counters | 82,794 CODE B /22,721 x86, two wrong mnemonics and fourteen wrong widths; GPR debt unchanged | Reject |

The `if/else` control redirects original 004ADE68's jump through the final
58 continuation (whole ordinal 2,179), instead of directly to the native
epilogue (22,717). Matching instruction counts conceal this error. The
`return` control changes only four existing genuine function exits; it
introduces no fake return, unreachable branch or extra operation.

The three tested constant values are independently reread from original
0065782C, 00657858 and 00657888. They lie in nonwritable `.rdata`, whose
section characteristics are 0x40000040. Literal spelling does not repair
the allocation phase. The compound counter candidate likewise preserves
the same 6,958 differing GPR ordinals but changes actual instruction forms;
it must not be accepted on its shorter total length.

Earlier F1021, F906, F792/F793, F1023 and F1029 negative controls were
consulted before these experiments. Do not rerun their old matrices or
these six new controls without a new evidence-based reason.

## Local evidence and validation scope

`.analysis/f1201-82kb-first-register/` preserves the original source/object,
four complete candidate sources/objects/logs/audit JSONs,
`native-state-debt.py`, `native-state-debt.json`, `constant-sections.json`,
`literal-symbol-changes.json`, `whole-audit.py`, `make-receipt.py` and
`verified-summary.json` with recursive source/artifact SHA256 values.
The two 259 controls and full audits are preserved separately in
`.analysis/f1202-third-short-counter-phase/`.

The selected current object stays
`.analysis/f1200-82kb-native-cfg/tracked.obj`. No accepted source, interface,
manifest, origin, comparison infrastructure or progress accounting changed.
Preflight target/tracking/handoff/Ghidra checks pass; documentation gets
whitespace and active-handoff checks. No full CI, corpus replay, historical
origin test or new per-function test is added. All 22 authored giants and
95 unknown origins remain pending as before.
