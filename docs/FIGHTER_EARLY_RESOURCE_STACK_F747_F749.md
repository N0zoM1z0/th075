# F747–F749 — authentic early fighter actions naturally restore the whole giant saved `this` frame

**Significant source-backed 58KB GIANT progress, NOT whole-game byte-exact.**
Pinned target: user-provided Japanese TH075 v1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Original authored `00543210` consists of **58,294 original CODE B**
and **943 separately owned after-RET dispatch DATA B**. Original
switch-case interiors are not independently callable authored functions;
none of their CODE earns formal exact coverage until the *whole giant*
is genuinely exact.

## Six complete, physically bounded, newly source-backed original actions

| Original native action | Full PE original interval | Original complete CODE /x86 | Fresh full-parent VC7.1 source | Original physical typed COFF fields | Original-vs-source real GPR errors |
| --- | --- | ---: | ---: | ---: | ---: |
| `0x059` | `00545109`–`0054526D` | **356 B /95 x86** | **356 B /95 x86**, same mnemonic+width | **16/16** | **19** |
| `0x05D` | `0054526D`–`005453BE` | **337 B /101 x86** | **341 B /103 x86**, two real extra x87 operations | **8/8** | **46** |
| `0x05E` | `005453BE`–`0054550F` | **337 B /101 x86** | **341 B /103 x86**, two real extra x87 operations | **8/8** | **46** |
| `0x060` | `0054559F`–`005457BC` | **541 B /154 x86** | **541 B /154 x86**, same mnemonic+width | **10/10** | **98** |
| `0x061` | `005457BC`–`005459E5` | **553 B /158 x86** | **553 B /158 x86**, same mnemonic+width | **10/10** | **101** |
| `0x062` | `005459E5`–`00545ADE` | **249 B /65 x86** | **249 B /65 x86**, same mnemonic+width | **4/4** | **0** |
| **Six source-backed original internal cases** | | **2,373 native B** | **2,381 emitted B**, all meaningful C++ | **56 real native fields** | Not whole-function exact |

Tracked normal C++ bodies:
[`FighterEarlyBounceF747.inc`](../probes/FighterEarlyBounceF747.inc),
[`FighterResourceTenVolleyF748.inc`](../probes/FighterResourceTenVolleyF748.inc),
[`FighterResourceSelectorF749.inc`](../probes/FighterResourceSelectorF749.inc).
All are compiled together in **ONE complete original-shaped 58KB
VC7.1 fighter parent**, under pinned flags
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and all previously restored real
fighter gameplay. No artificial unused stack locals, manual emitted
instructions, binary patches, handcrafted relocation fields or
isolated-case compiler tricks.

### Original real game behavior recovered

The original `059` restores angular motion after stage one, advances
`+0x30` by original `[00657858]`, changes vertical speed, uses a real
`FCOMP [0065782C]` ground condition, converts X/Y velocity to signed
short `+0xF00/+0xF02` through original `[00657888]` and two real
`__ftol2` calls, resets motion/ground, switches to original
`0x61`, calls authentic trajectory and subaction methods, and
relaunches actual X/Y speed using native `[006590BC]`/`[00658044]`
float globals and `SetMotionStateAt40FBB0(0,95.0f,0)`.

The sister `05D/05E` actions share real stage-under-eight gravity,
native ground `FCOMP [0065782C]` and aux-eight reset, original
completion action `0` or `1` depending the signed stock at
`this+0x4E0`, two independent facing comparisons against original
opponent member `OWNER+0x44`, stage-three vertical speed **8.0f**,
horizontal speed **+15.5f/−15.5f**, drag **0.75f**, and stage-eight
auxiliary **6**. Their signed facing writes to actual byte `+0x66`
are live game state, not synthetic register controls.

The genuinely substantial `060/061` original actions evaluate facing
sign × native `+0x4DC` and **four unsigned resource guards** at
`+0x4E8/+0x4EC/+0x4F0/+0x4F4`, select signed short flag `+0xF00`
as **1 or 2**, and at stage-zero/frame-zero execute real
**ten-iteration `0x3E4` projectile loops** with actual distinct used
C++ integer loop variables. If native signed `+0xEFA>25`, they reset
this real counter and spawn one additional **`0x3E3`** projectile.
The two cases use different original gravity stages (`060` stage 3;
`061` stage >3 and <5) and grounded auxiliary actions **4/5**.
On completion they select real action `0x62` or `0x63` from actual
`+0x3CF`, or restore original signed-short `+0xF00/+0xF02`
velocity through the same original `[006590B8]` x87 float scaling,
with true Y negation performed on the integer before `FILD` and
real drag **2.0f**.

Finally `062` genuinely rechecks the same facing/resource sign,
then on original completion first sets action **`0x5F`** and selects
native `0x5D`/`0x5E` when the real signed flag is 1/2. This
naturally produces the complete original **249 B/65 x86/4 authentic
PE/COFF source fields** with **zero normalized GPR differences** in
the same full parent. No inner-case bytes receive separate credit.

## Major natural compiler lifetime/frame positive

The latest F744 entire parent still saved `this` at **`EBP−0x3C`**,
versus the actual original native frame **`EBP−0x44`**.
Inserting the **true** early game cases 059/05D/05E and, especially,
the real used ten-shot loop variables and integer-to-x87 speed
conversions in 060/061 naturally moves the saved receiver to
**`EBP−0x44`**, the *real original whole 58KB parent slot*.
This does **not** mean all other code or stack lives are exact:

| Actual original used stack resource | Original native EBP | Fresh entire-parent VC7.1 EBP | Evidence |
| --- | --- | --- | --- |
| Saved `this` in entire 58KB parent | **−0x44** | **−0x44** | Real prologue `MOV [EBP−0x44],ECX` |
| Action 059 original two signed-int-to-x87 velocity scratch locals | **−0x4C/−0x50** | **−0x4C/−0x50** | Native/source `MOV/FILD` original x86 74/75 and 82/83 |
| Action 060 actual ten-shot index | **−0x8** | **−0x8** | Native/source true used loop initialization and comparison x86 48/53 |
| Action 060 actual two signed-x87 speed locals | **−0x54/−0x58** | **−0x54/−0x58** | Original/native `MOV/FILD` x86 138/139 and 146/147 |
| Action 061 actual ten-shot index | **−0xC** | **−0xC** | Native/source ten-shot loop x86 48/53 |
| Action 061 actual signed-x87 speed locals | **−0x5C/−0x60** | **−0x5C/−0x60** | Original/native `MOV/FILD` x86 142/143 and 150/151 |

All the real temporary operand widths and offsets are asserted
**in the same freshly compiled entire parent**. This is a
natural original-source-lifetime result rather than fake stack
padding or a source-local artificial EBP override. Later original
source actions can still allocate scratch at wrong deeper offsets.

The new parent also rechecks **27 other previously source-backed,
physically bounded original fighter actions** (190 through 2EF),
with **zero normalized nonfield GPR/CFG discrepancies** across
these specifically tested current-parent contexts. Most of these
have original-sized x86 opcode/width geometry and matching
true source COFF-field counts, but `190` still has **three true
native-vs-source instruction width differences, 276 original B
vs 266 emitted B**. Their deep x87 EBP locations remain
independently nonexact and none is adopted as a whole game function.

## Honest original x87 negatives: 05D/05E still do NOT match

Even in this naturally correct saved receiver frame, the
`05D/05E` source still emits **341 B/103 x86 each** against
original **337 B/101 x86**. Original face-to-opponent
comparisons at native x86 **59 and 69** use direct
`FLD [actor+0x44]; FCOMP [opponent+0x44]` (plus real `FNSTSW`
branch), but the current semantically meaningful C++ loads both
floats and performs `FCOMPP`. This creates exactly **two extra
`FLD/FCOMPP` grammar instructions**, and the final original typed
call field shifts in source from native ordinal **99 to 101**.
All eight true native target symbols/types/zero addends per case
are nonetheless independently checked at their physically valid
current source owner instructions; **matching a field count is
not physical original ordinal equality** for these nonexact cases.

F747 compiled **eight complete giant C++ source grammar models**
testing genuinely used float left/right member lvalues, const,
volatile and reversed-expression comparisons. These controls
failed to produce the native direct two-operand `FCOMP` structure
without violating original semantics or whole-parent compiler
grammar; their real complete C++/OBJ/PDB/log and original comparison
receipts are preserved in ignored
`.analysis/f747-fighter-early-pair/compare-grammar/`.
The `059` multiplication was separately corrected from the
compiler's initial reversed `FLD GLOBAL; FMUL ACTOR` to the
native original **`FLD ACTOR; FMUL GLOBAL`** at x86 30/31 by a
genuinely used `*(&POS54)` actor member expression, preserving
both physical native `DIR32` global targets. These improvements
are genuine C++ grammar evidence, not proof of historical class names.

The `060` and `061` original entire cases have **all 154/158
mnemonic and WIDTH positions** and every true original ten-shot
loop/scratch position, but still have respectively **98 and 101
real normalized nonfield GPR/CFG operand differences**. The
`059` case also retains **19** such differences; 05D/05E
retain **46 each**. The whole 58KB game function remains
NONEXACT despite frame-layout improvements.

## Portable verifier, original physical PE and full 943-B DATA

[`scripts/verify-fighter-early-resource-f749.py`](../scripts/verify-fighter-early-resource-f749.py)
rebuilds exactly **one entire original-shaped 58KB C++ fighter**
under native pinned VC7.1, rereads original PE physical 059/05D/
05E/060/061/062 complete original bounds and all **56 real typed
native PE/COFF fields**, checks actual native source symbols,
relocation types/addends and owning instruction, and enforces
positive original EBP receiver/scratch/loop positions **and** the
remaining GPR/x87 negative counts. It additionally rereads the
27 selected earlier complete original internal case contexts.

Independently, in the same newly compiled parent, it verifies the
entire **943 original after-RET switch DATA bytes**: **156 physical
native/source `DIR32` jump table entries** each target a real
native or source decoded x86 instruction boundary, and all
**319/319 other original dispatch bytes** are byte-identical.
These are table DATA, not accepted whole game CODE. Existing
F744 and F737 historical source-context verifier defaults stay
reproducible and are separately regression checked.

```bash
scripts/repo-python scripts/verify-fighter-early-resource-f749.py
scripts/repo-python scripts/verify-fighter-double-repeat-f744.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Tracked full natural C++ action sources and selected-parent PE
validator are portable; the complete freshly generated source,
OBJ/PDB and source/target physical original comparison receipt
remain locally under ignored `.analysis/f749-fighter-resource-selector/`.
**Zero new exact whole game CODE** is credited by this giant study.
The formal authored exact ledger stays **966 complete functions /
864,118 original CODE bytes (43.78% reviewed)**; all 22 giant
original functions and 3 other complete authored WinMain/Scene/
Archive functions remain whole-function NONEXACT. No all-unit
cold replay or original EXE modification.
