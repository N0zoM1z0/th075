# F1013 — Two genuine final fighter actions 31B/31C and native 303 JMP recovery

The pinned Japanese TH075 v1.11 original fighter at 004AC040
has **82,796 callable CODE B /22,721 x86** and
1,126 separate afterRET jump-table DATA B. The
[tracked original-shaped normal VC7.1 C++](../probes/FighterWhole004AC040F1013.cpp)
is an incomplete PARTIAL parent, not whole-game original exact:
native saved receiver EBP−0x64, frame0x720, unimplemented
actions and physical entire-father relocations still differ.

Independent original physical PE decoding shows only two true
late fighter actions beyond 303, and a separate common default
state; don't invent action implementations for 304..31A:

| Real original action | Physical PE interval | Native case CODE/x86 | Typed original PE fields |
| --- | --- | ---: | ---: |
| 31B | 004C01A1..004C02A2 | **257 B/76 x86** | **9** |
| 31C | 004C02A2..004C037D | **219 B/63 x86** | **7** |
| Both | contiguous | **476 B/139 x86** | **16** |

Both original states set signed short F00=0 and int+0x7C=1
then call ResetAt453E20 at stage0/frame0, handle native
0040FA30 animation completion through 0040FAC0(0), and
invoke **00454A70(0)**, **00452B30()** and
00453D60(0x17) at their genuine state-specific stage
(stage5 for 31B, stage16 for 31C). Original 31B then
emits the actual 0x3E5 projectile with RAW 32-bit actor X,
float Y+real global **00657888**, original signed facing
and layer1. At stage11/frame0 with F00<8, 31B increments
F00 and invokes auxiliary action9.

Original 31C at stage21/frame0 with F00<8 increments F00,
invokes auxiliary action19 and writes BYTE **actor+0x3CF=1**.
No arbitrary action0 or dummy projectile was added to the
31C source. All call parameters, byte/short widths and
side effect ordering come from the real original PE.

The
[ordinary C++ cases](../probes/FighterThirdBossFinal31B31CF1013.inc)
in a COMPLETE original-shaped PARTIAL parent source naturally
reproduce **all 139 native ordered mnemonics, widths and
GPR operand roles** with **16 actual original PE external
targets**, no register forcing, ASM, fake locals or target
bytes. Both case interiors have the exact native
257+219 original sizes despite the still-unmatched whole father.

**Preceding-case positive effect:** restoring 31B/31C
causes real original303's final shared-parent-tail JMP
to compile to the native five-byte near encoding rather than
the previous two-byte short. The native303 source now has
**1,014 B/267 x86 with zero mnemonic, width or GPR-role
differences** and retains its 29 real physical PE fields.
The earlier native302 source is also unregressed.

The bounded
[original PE verifier](../scripts/verify-third-fighter-final31b31c-f1013.py)
freshly compiles TWO ENTIRE normal VC7.1 original-shaped
PARTIAL 82KB fathers, F1012 old real 303 plus markers
versus F1013 with two authentic final actions. It checks
all 139 case instructions, **all 16 original typed zero-addend
PE/COFF destinations**, prior real 302/303 source,
all **151 original afterRET DIR32 local case labels and
522 native nonfield DATA bytes**.

| Entire original-shaped PARTIAL father | F1012 prior | F1013 real |
| --- | ---: | ---: |
| Generated partial CODE B | 72,252 | **72,707** |
| Generated partial x86 | 19,803 | **19,938** |
| Real 31B source B/x86 | 12/2 marker | **257/76** |
| Real 31C source B/x86 | 12/2 marker | **219/63** |
| Wrong original case mnemonic/width/GPR | n/a | **0/0/0 both** |
| Original physical case PE targets | markers | **9+7** |
| Prior303 original width/GPR errors | 1/0 | **0/0** |
| Compiler PARTIAL source frame | 0x584 | **0x584** |
| Entire original 82KB callable exact | NO | **NO** |

The real common default at 004C037D and final shared
epilogue at 004C03A7 are separately owned original code,
not 31C case bytes. The whole father still has different
native EBP offsets and many missing game action sources.
Never award independently exact callable GAME CODE for
an inner state.

Reproduce only these two affected complete PARTIAL builds:

    scripts/repo-python scripts/verify-third-fighter-final31b31c-f1013.py

Private native PE receipts and normal VC7.1 C++/OBJ/PDB
compiler logs under .analysis/f1013-third-native-proof/
and .analysis/f1013-third-final/ are retained.

**No new accepted whole original callable function/CODE.
No all-979-unit cold replay.**
