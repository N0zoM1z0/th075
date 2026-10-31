# F1021 — Ten complete original-frame 82KB loop grammar controls

The pinned Japanese TH075 v1.11 original fighter at 004AC040
is **82,796 callable CODE B /22,721 x86**, with
native frame0x720 and saved this at EBP−0x64.
After the genuine F1020 shared-ring-local correction,
the tracked [selected original-shaped source](../probes/FighterWhole004AC040F1020.cpp)
reproduces ALL these whole geometry values and all 22,721
native ordered mnemonic positions. But **12 native
instruction widths** and **6,958 original GPR operand
roles** still differ, so the entire callable is
NOT exact and earns no original CODE credit.

The first whole-fighter original GPR divergence is
x86 ordinal **2180, physical address004ADEFA**,
the first instruction of actual action0x59.
Its immediately preceding native action0x58,
physical 004ADD25..004ADEFA, is **469B/135 x86**,
and the following native 0x59 is **356B/95 x86**.
The selected strict real 0x58 ten-shot source is
already exactly positioned in all 469 original
mnemonic/width/GPR roles, but source action0x59
still has **19 wrong GPR-role instructions**.

Earlier F931 trials on another 58KB fighter and
F938 controls on a much smaller original-shaped
PARTIAL father found a postincrement-loop tradeoff.
F1021 DOES NOT assume that historical negative
remains valid. It independently replays the actual
pinned game target against TEN fresh serial full
82KB VC7.1 fathers with the now-correct native
frame and receiver.

The [bounded original PE verifier](../scripts/verify-third-fighter-native-loop-phase-f1021.py)
fresh-compiles complete original-shaped PARTIAL sources
while varying ONLY real ten-shot stage0x58 loop
and native field value-category grammar, and checks
the entire original source CODEx86, each actual
0x58/0x59 complete case interval, the physical
afterRET 151 original DIR32 local case labels and
522 original nonfield DATA bytes.

| Full VC7.1 source spelling | Whole original mnemonic errors | Whole width errors | Whole GPR-role errors | Native0x58 error M/W/G | Following0x59 GPR errors |
| --- | ---: | ---: | ---: | --- | ---: |
| Strict original for(burst=0;burst<10;++burst) | **0** | **12** | **6,958** | **0/0/0** | **19** |
| Genuine postincrement while(burst++<10) | 1 | 14 | 6,979 | 1/2/40 | **0** |
| Postincrement for equivalent | 1 | 14 | 6,979 | 1/2/40 | **0** |
| Hoisted real int burst local | **0** | **12** | **6,958** | **0/0/0** | **19** |
| Natural burst++ iteration for | **0** | **12** | **6,958** | **0/0/0** | **19** |
| Reversed genuine unsigned-free comparison | **0** | **12** | **6,958** | **0/0/0** | **19** |
| Explicit lexical scope around genuine for | **0** | **12** | **6,958** | **0/0/0** | **19** |
| Read-only genuine X/Y shot bit operands | **0** | **12** | **6,958** | **0/0/0** | **19** |
| Native stage1 actor+0x54 typed FLOAT view | 0 | 14 | 6,960 | 0/2/2 | **19** |
| Preincrement while(++burst<=10) | MANY | MANY | MANY | 67/60/68 | 19 |

The preincrement loop emits only 467B/134 x86
for action0x58 and the full source only
82,794B/22,720 x86, so the whole positional
statistics after its first omitted instruction
are not a meaningful single-instruction alignment.

**Conclusion:** the original postincrement spelling
can repair the subsequent 0x59 register phase,
but at the direct cost of a non-original 0x58
instruction and two nonnative widths; globally
it makes register-role agreement *worse* by 21.
Pure loop declaration scope, actual X/Y borrowed
value categories, or operand-order spelling do
not repair the native register-owner phase.
The strict selected source remains original-shaped,
and the whole giant is still NONEXACT.

This does NOT prove what the historical game's C++
was, nor rule out a different genuine owner lifetime
or a different preceding state. It does rule out
claiming complete CODE exactness via a nonnative
shortened loop or by accepting the inner 0x59 alone.
No artificial locals, fake padding, ASM, truncated
comparisons or relocation masking were introduced.

Reproduce ONLY the ten original-shaped entire father
builds (not the 979 accepted corpus functions):

    scripts/repo-python scripts/verify-third-fighter-native-loop-phase-f1021.py

Native PE original checks and all ten C++/OBJ/PDB
compiler receipts remain in ignored
.analysis/f1021-third-native-loop-proof/.
The preliminary independent four- and six-control
matrices are in .analysis/f1021-third-loop-phase/.

**No newly accepted original whole GAME callable
CODE B/functions; no mass cold replay.**
