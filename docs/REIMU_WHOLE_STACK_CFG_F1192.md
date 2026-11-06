# F1192 — Reimu complete source, native whole stack/CFG and PE targets

`probes/FighterWhole0045DD70F1183.cpp` now contains all original state
bodies and the real default/shared getter tail. Every marker reference is
removed from its complete transitive source inputs. This continues the same
F652/F1183 parent; it is not an older marker-only restart. The independently
R063-authored original **0045DD70 remains NONEXACT**.

| Complete original property | Pinned native PE | Fresh normal C++ parent |
| --- | ---: | ---: |
| Entire callable CODE | 60,999B | **61,000B (+1)** |
| Ordered x86 instructions | 16,837 | **16,837** |
| Actual frame allocation | 0x380 | **0x380** |
| Saved-this | EBP-0x34 | **EBP-0x34** |
| EBP instruction operand positions | 5,444 | **5,444/5,444** |
| Ordered instruction mnemonics | 16,837 | **all match** |
| Direct intra-function branch destinations | 1,684 | **all native target ordinals match** |
| Physical CODE field destinations | 1,682 | **all native instruction/field destinations match** |
| Dense DATA entry destinations | 142 | **all native instruction ordinals match** |
| Physical handler order, including default | 144 | **all preserved** |
| Owned after-RET DATA | 1,090B | **1,090B**, including 522 exact sparse bytes |
| GPR-role differences | — | **6,311 instruction positions** |
| Instruction-width differences | — | **5 positions** |
| Whole original exact acceptance | — | **NO** |

A whole-object diagnosis resolves every actual CODE COFF field, including
local switch-table bases and __ftol2, with **zero unknown references**.
All non-GPR operands agree, while stack displacements are additionally
checked without normalization. These native PE destinations do **not**
establish original relocation-offset equality: width debt shifts absolute
source offsets. Canonical whole cold replay is still required for future
acceptance; no exact unit or accepted byte is added here.

## The last six native states and genuine stack recovery

| Newly sourced state | Complete native interior CODE | Native x86 | External fields |
| --- | ---: | ---: | ---: |
| 2DB | 1,131 | 316 | 32 |
| 2EF | 1,042 | 283 | 27 |
| 303 | 969 | 261 | 25 |
| 304 | 560 | 144 | 10 |
| 31B | 257 | 76 | 9 |
| 31C | 749 | 208 | 21 |
| **Last six bodies** | **4,708** | **1,288** | **124** |

The source preserves 2DB's separate early/late airborne gravity, distinct
landing exit, three independent selector paths and RNG refresh after each
spawn. 2EF retains charge transforms, strict landing, ordered counter/frame/
stage gates, random opponent-relative warp, direction decision and signed
timer arithmetic. The 303/304/31C loops are actual native loops, not
unrolled or fabricated register seeds; 31B retains the observed effect flow.
Names and complete private-owner layouts remain provisional.

Ten genuinely used loop indices restore all missing named local storage.
Their natural integer-to-float expression values and the real owner-relative
warp spill reproduce the complete original **0x380 frame, saved-this slot
and all 5,444 EBP operand positions**, without filler, fake locals, assembly
or a second exact-only body. The previously short 2F9 return and all 20
historical 190/191 scratch-width differences now recover naturally.

Initial candidates had three x87 expression-order differences: opponent-X
plus warp spread, the subsequent direction comparison, and center-X motion.
Genuine lvalue spelling/borrowing recovers original FLD/FADD, address/load
order and FLD/FSUB rather than reversed operations. The final six states
have every mnemonic, width, non-GPR operand, stack operand, branch destination
and physical external target checked. GPR debt remains in four of them;
31B/31C additionally reproduce all GPR roles.

## Native shared getter and ordinary exits

Actual original JMPs **0045DF98, 0045E120, 0045E203 and 0045E212** from
states 0/2/4/5 alone reach shared getter **0046CBAA**. Other ordinary
switch exits reach the real epilogue at **0046CBB2**, while default performs
its getter/conditional primary-action reset and skips over the shared getter.

The label therefore belongs inside the switch after default's break. An
initial after-switch return label sends ordinary exits through the default
skip JMP instead of directly to the epilogue. The native-ordinal audit
rejects that same-length/same-count wrong CFG. The adopted ordinary C++
label scope restores **all 1,684** actual direct destinations, including
the early shared tail and every interior conditional/loop exit.

## Honest remaining exact debt and reproduction

The five wrong widths are the three EAX-specific CMP encodings in **63**
at native **004605C6 /004606E1 /0046073C**, and the AL-specific byte SUB
encodings in **252/254** at **00467D27 /00467F2F**. All are actual GPR
encoding differences; there is no remaining frame or instruction-count
shortfall to hide. The first GPR divergence is state **59** at **0045FDA9**,
whole ordinal 2,292: native EAX versus source EDX for the saved-this load.
Inspect that boundary and the preceding native 58 source/real helper views;
do not restart equivalent marker or frame-padding experiments.

All 90 newly restored F1183–F1192 interiors span **46,364 native CODE
bytes /12,800 x86 /1,190 external fields**. Those are source-recovery
observations inside one original function, not independent exact units.
All 60,999 pending original bytes remain in the conservative denominator.

Use the headless serial F1183 compiler command with output
`.analysis/f1192-reimu-final-states/native-scope.obj`. The retained local
`whole-audit.py` reads that object (or one explicitly passed as its argument)
and checks the entire native CODE, all 144 physical handler starts, ordered
branches/stack/PE fields and full owned DATA. Its JSON contains every remaining
GPR/width position. Original intervals, before/initial/corrected objects,
rejected source scopes, transitive-source SHA256 inventory and verified summary
remain in that ignored directory. This is scoped research evidence, not
canonical acceptance or a new per-function test suite.

Target/tracking, active handoff and `git diff --check` pass. Accepted sources,
headers, exact/origin ledgers and comparison infrastructure are unchanged.
No full CI, corpus replay or historical origin tests ran. Canonical coverage
remains **982 whole exact functions /871,649 CODE bytes**, 44.16% reviewed /
44.09% conservative, with all 22 authored giants still pending.
