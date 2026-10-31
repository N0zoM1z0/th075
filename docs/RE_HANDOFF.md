# TH075 — ACTIVE reconstruction agent handoff

**Verified snapshot: 2026-10-31, current F780 exact ledger; F865 complete five-case region and F864 Scene locals.**
This is the **short working queue**, not the chronological research log.
Original Japanese PE and the live configuration **always outrank historical
prose, old case-level exact labels, class names or inferred layouts**.
Old long F653–F753 handoff: [frozen, link-corrected archive](history/RE_HANDOFF_F653_THROUGH_F753_2026-10-30.md).
Older [F598–F652](history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md),
[F540–F596](history/RE_HANDOFF_F540_THROUGH_F596.md), and the
[historical knowledge base](KNOWLEDGE_BASE.md) preserve experiments.

## 1. Live original target and formal exactness

| Evidence / classification | Current live manifest value |
| --- | --- |
| User-supplied Japanese TH075 `resources/th075.exe` v1.11 | SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| Provisional original native candidate rows | **4,351** |
| Independently reviewed `origin=authored` candidates | **1,004** |
| Canonical accepted complete exact authored game functions | **979 functions / 979 exact units** |
| Accepted complete original CODE | **868,243 original CODE bytes** |
| Reviewed denominator | **1,973,704** native authored CODE B |
| Exact reviewed coverage | **43.99%** |
| Conservative coverage (includes pending origin bytes) | **43.91%** |
| Authored candidates still NOT exact | **25 authored functions remain nonexact** |
| 25 nonexact breakdown | **22 large original state advances**, **3 other original small/medium whole functions** |
| 22 large original native CODE not accepted | **1,102,055 CODE bytes** (separate after-RET DATA not credited) |
| 3 small/medium native CODE not accepted | **3,406 CODE bytes** |
| Independently origin-unknown candidates | **95 functions / 3,420 CODE bytes**, uncredited |

**Important correction:** the older **25 unfinished** figure only counted
rows flagged both `owner=authored` and `status=unclassified` in
`config/functions.csv` (22 large + WinMain/Scene/Archive). There were
**11 more** candidates whose `function-origins.csv` origin was already
reviewed as authored, but whose provisional `functions.csv` owner is still
blank at that historical checkpoint because they lacked accepted source.
F755 (`00407270`), F758 (`00407A50`), F760 (`00407B80`), F765 (`0040D790`), F766 (`0040D6B0`), F769 (`0040B110`), F770 (`0040B000`), F775 (`0040D2E0`), F776 (`0040CEF0`), F779 (`0040CA20`) and F780 (`0040C9A0`) accepted all eleven. The remaining three
small/medium functions were already separately owner-marked authored.
Do not credit them until complete independent cold exact matches.
Use **`config/function-origins.csv` for provenance** and
`config/matches.csv` / `config/match-units.toml` for whole CODE credit.
The **98% whole-authored-byte goal is NOT met**.

### Preflight (read-only, no mass rebuild)

```bash
git status --short --branch
git log -5 --oneline
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/audit-active-handoff.py
scripts/repo-python scripts/ghidra.py check
```

All dirty tracked/untracked work belongs to this one reconstruction worker;
inspect and continue it, do not skip/reset it. Run the hash-pinned original
`th075.exe`, **not** `th075c.exe`. Use `scripts/repo-python` and the pinned
VC7.1 compiler; compile probes serially under headless Wine. **Never run an
all-979-unit cold replay.** Only newly accepted or affected whole functions
need canonical `scripts/repo-python scripts/replay-exact-units.py --unit NAME`.
Source grammar/byte geometry of an *internal switch case* does **not**
earn credit for the still-NONEXACT enclosing whole callable function.

## 2. Large/giant whole functions — invest real effort here

**`0x00543210` / 58,294 original CODE B, plus 943 after-RET switch DATA B.**
The **current** whole-parent source includes F781's native shared
getter and is reproduced by
`scripts/repo-python scripts/verify-fighter-shared-getter-f781.py`
([F781 original physical proof](FIGHTER_EARLY_SHARED_GETTER_F781.md)).
F752's borrowed-position checker is *historical evidence only*
([F752 original source comparison](FIGHTER_BORROWED_POSITION_F752.md))
and does not generate this latest 58,293-B parent.

Current true native source positives in ONE complete VC7.1 parent:
original saved `this` **`EBP−0x44`** matches naturally from real
`059/060/061` game and ten-shot loop lifetimes. The formerly wrong
original `05D`/`05E` **337 B/101 x86/8 physical PE fields each**
now emit complete native `FLD ACTOR; FCOMP OPPONENT` thanks to
**both borrowed actor/opponent typed `+0x44` float members**. They have
zero mnemonic/width/normalized GPR differences and 301/305 original
nonfield bytes each; only **two shared-tail JMP displacement fields**
per case differ because the whole giant layout remains nonexact.
All **16/16 original PE/COFF relocations**, **27 other selected full
native action contexts**, and the whole **943-B DATA /156 real DIR32
jump labels /319 other native bytes** were rechecked in that parent.
See [F747–F749 original frame proof](FIGHTER_EARLY_RESOURCE_STACK_F747_F749.md)
and [F752 complete corrective comparison](FIGHTER_BORROWED_POSITION_F752.md).

**F759 historical full-parent correction (before F760):** the previously placeholder `C8–CB`
original actions now have **1,804 B/532 x86/54 genuinely typed COFF
fields** of original source-backed case geometry. All **1,540/1,540**
nonfield original bytes outside 54 relocation and 12 external parent-tail
JMP fields match; the 12 real tail displacements are NOT exact. Four
meaningful native `EBP−0x74/−0x78/−0x7C/−0x80` FILD temporaries
recover the missing 16B stack lifetime across downstream `18A/18B/190`
and later contexts. Native `190` is now **276 B/75 x86 versus 276
compiled B/75 x86**, but still has authentic GPR/CFG differences and
shared-tail nonexact bytes. The whole giant still emits **56,954**
versus **58,294 native CODE B**; `CC/CD/CE` remain placeholders
(435/435/394 native B). Reproduce only the affected entire parent:

```bash
scripts/repo-python scripts/verify-fighter-four-directional-c8-f759.py
```

[Full F759 native physical proof](FIGHTER_C8_CB_WHOLE_PARENT_F759.md).
No new independently exact whole original CODE was credited.

**F759 further historical whole-parent evidence:** original four C8–CB actions now
recovered as 1,804 real internal CODE B /532 original x86/54 authentic
PE fields, with 1,540 byte-identical other nonfield bytes and 12
real shared-parent JMP displacement differences. The extra genuine
source *also* restores nine downstream MOV/FILD EBP scratch pairs
(18A/18B, 190–195, 2D0, 302), including original 190 `EBP−0x90`.
The enclosing 58,294-B original remains NONEXACT: 56,954 emitted
CODE B, 1,340-B deficit; 943-B afterRET DATA remains separately
verified. [F759 physical full-parent evidence](FIGHTER_FOUR_DIRECTIONAL_NATIVE_F759.md),
`scripts/repo-python scripts/verify-fighter-four-directional-c8-f759.py`.

**F760 historical whole-parent result (before F762; supersedes F759 GPR negatives):**
three more real CC/CD/CE source actions reproduce 1,264 original CODE B,
371 original x86, 31 genuine PE/COFF fields, and 1,116/1,116
nonfield/non-tail bytes. Correcting the real unconditional virtual call
after the short stage-count conditional fixed three actual `JL` bytes.
Eight downstream source-backed actions 18A/18B/190/191/192/194/195/2D0
now have **zero mismatches outside actual COFF and parent-tail JMP**
including original 190 `276/276 B` and original GPR role. The full
58,294-B native boss emits 58,173 B, a remaining 121-B CODE deficit.
The original 943-B afterRET DATA is still independently verified;
whole game callable function remains NONEXACT.
[Original complete F760 evidence](FIGHTER_COMPLEX_STAGE_CC_CE_F760.md);
`scripts/repo-python scripts/verify-fighter-complex-stage-cc-ce-f760.py`.

**F762 historical full-parent correction (before F763):**
`05F` now has genuine native-shaped source **144 B/44 x86/3 fields**,
but its GPR phase remains NONEXACT. More importantly, original complete
`1F6/1F7/1F8` now emit **3,833 original CODE B /1,118 x86 /115
actual typed PE/COFF fields** with zero nonfield byte mismatches except
true still-nonmatching parent-shared JMP displacements. The original
`ContactAt454EE0` gate applies only to the first two side-edge
predicates, not the independent actor/opponent position comparisons.
Borrowed typed actor/opponent `+0x44` float lvalues restore real x87
FCOMP and the 1F8 native MOV/FLD order. The WHOLE 58,294-B boss emits
**58,277 B**, a remaining **17-B length deficit** plus genuine
register/other-code bytes; **not exact**. Original 943-B afterRET DATA
remains separately verified. [F762 entire native evidence](FIGHTER_TYPED_RETURN_CROSS_CASE_F762.md);
`scripts/repo-python scripts/verify-fighter-typed-returns-f762.py`.

**F763 historical full-parent result (before F764):** original 2DB now reproduces
**1,024 native CODE B, 290 x86 and 34 real PE/COFF fields**, with
zero other nonfield bytes outside the genuine shared-parent tail JMPs.
Original `actorX < sideEdge`, `abs(actorX−opponentX) < threshold`
and real actor/opponent float `+0x44` lvalues restore the correct
x87 TEST AH status flags and MOV/FLD register order. The formerly
extra 8 B/two x86 in 2DB have been removed naturally; the full
58,294-B boss candidate now emits **58,269 B**, 25-B deficit and
still NONEXACT. Original 2FA still emits 979 B vs native 971 B;
that is the next targeted x87/branch/GPR task. Original 943-B
afterRET switch DATA separately verified, no accepted CODE credit.
[Complete F763 native evidence](FIGHTER_APPROACH_NATIVE_F763.md);
`scripts/repo-python scripts/verify-fighter-approach-native-f763.py`.

**F764 historical original 2FA state research (before F767):** all six real floating
predicates/borrowed actor-opponent `+0x44` X member reads corrected
inside the same complete 58KB C++ parent. Actual native action 2FA
now emits **971 B/279 x86/31 genuine typed PE/COFF fields** and
has **zero original opcode or instruction-width differences**.
However **156 real GPR/operand nonfield bytes remain WRONG**; this
is NOT whole-case or whole-function exact. Recovered 2DB and
1F6/1F7/1F8 native source bodies stay strict (except parent-tail
JMPs), and original afterRET jump DATA remains 943 B/156 real
DIR32/319 sparse bytes. Whole original `00543210` now emits
**58,261/58,294 CODE B** (33-B deficit plus genuine wrong bytes);
zero new accepted CODE. [F764 original whole-case proof](FIGHTER_APPROACH_VOLLEY_NATIVE_F764.md);
`scripts/repo-python scripts/verify-fighter-approach-volley-native-f764.py`.

**F767 historical 2F9 physical source advance (before F768):** a real source correction of
borrowed opponent/actor X `+0x44` float members and read-only opponent Y
`+0x48`/actor Y lvalues restores all 381 original 2F9 mnemonics and
instruction widths within its entire 1,367 original CODE B and 34
original zero-addend PE/COFF fields. Eleven true whole-parent compiler
variants cut nonfield wrong bytes **265→249**, fixing all eight wrong
original 2F9 opcode positions without ASM/padding or target bytes. The
remaining 249 genuine register/operand bytes **are NOT exact**. The
whole 58,294-B fighter still compiles to 58,261 B, 2FA still has 156
real wrong operand bytes; true after-RET 943-B separate DATA reverified.
[F767 original PE and source proof](FIGHTER_STORM_ANGLE_TYPED_F767.md);
`scripts/repo-python scripts/verify-fighter-angle-storm-typed-f767.py`.

**F768 historical 2F8 integer-FPU source recovery (before F771):** actual C++ actor
`this+0x44` borrowed float member changes the real native actor-X
minus signed-direction×3 operation from nonnative `FLD/FISUB` to
original `MOVSX/IMUL/MOV/FILD/FSUBR`. In one newly compiled full
58KB parent, all **928 CODE B/252 native x86/23 PE fields** of 2F8
have exact original opcode and width positions; real nonfield
mismatching bytes fall **182→166**, with all five wrong x86 opcodes
eliminated. Those **166 operand bytes remain NONEXACT**. Same parent
rechecks F767 2F9 (249 wrong bytes), F764 2FA (156 wrong bytes),
and separate 943-B original afterRET DATA. The whole native function
still compiles 58,261/58,294 CODE B and is NOT exact.
[F768 full PE/COFF source proof](FIGHTER_STORM_VOLLEY_TYPED_F768.md);
`scripts/repo-python scripts/verify-fighter-storm-volley-typed-f768.py`.

**F771 historical 2FB whole-parent source result (before F777):** the original
`00550D97..0055101E` 647-B/181-x86/17-PE-field state now uses real
borrowed actor/opponent float `+0x44` X and opponent `+0x48` Y.
Eleven full 58KB VC7.1 source variants show all four wrong original
MOV/FLD instruction ordinals repaired and wrong real operand bytes
**119→111**, with 111 still explicitly **NONEXACT**. Previous full
2F8 166, 2F9 249 and 2FA 156 real operand-byte negatives remain;
the whole boss still emits 58,261 of original 58,294 CODE B and
943-B afterRET jump DATA remains independently correct. No case CODE
is accepted as an independent callable function. [F771 original
physical evidence](FIGHTER_GROUNDED_VOLLEY_TYPED_F771.md);
`scripts/repo-python scripts/verify-fighter-grounded-volley-typed-f771.py`.

**F777 historical 58KB register audit (before F778):**
Rebuilt the entire tracked F771 parent and independently confirmed its
real native `058` complete **469-B/135-x86/17-PE-field** case is
nonfield-exact outside legitimate external shared-tail JMPs, while
adjacent complete `059` has **19** actual wrong GPR operand bytes,
`060/061` **98/101**. Crucially *current-parent* native `063` is
**706 B/189 x86 /15 PE fields** but source emits **705 B/189 x86**:
real `CMP ...,0x96` ordinals **18/61/84** choose original
EDX/EAX/EDX (6/5/6 B) versus generated EAX/ECX/EAX (5/6/5 B).
Historical F626 `063` "strict" applies to a different old parent,
**not this one**. All **68** true PE/COFF source references in the
five native complete cases, plus original 943-B afterRET DATA, are
revalidated by
[`verify-fighter-current-register-phases-f777.py`](../scripts/verify-fighter-current-register-phases-f777.py).
Thirteen actual C++ 059 stage/float/short conversions and eight R015
`004EBDA0` typed-color/stage variants were negative; don't repeat
them without a new source hypothesis.
[Original physical evidence and negative bounds](FIGHTER_CURRENT_REGISTER_PHASE_AUDIT_F777.md).

**F778 historical full-parent default-handler repair (before F781):** independent
physical native dispatcher reading proves **239 original action IDs**
map to the real `00551598` shared default, not a source marker.
Its actual `0040FA30` state getter / `+0x70` compare / conditional
`0040FAC0(0)` transition is now normal whole-parent C++ with
**32 original CODE B, 10 native x86 and two genuine PE/COFF call
fields**; only four real EAX/ECX/EDX operand bytes in this guard
remain wrong. Recovered source **58,261→58,283 CODE B**, now only
**11 B/3 x86** shorter than original **58,294 B/16,471 x86**:
10 B of separately observed tail JMP/getter CODE plus one real
`0x63` CMP-width byte. "Near-exact-length" source controls that
route other cases through an extra getter were explicitly REJECTED
as nonnative control flow. Same fresh source verifies earlier
C8–CE/1F6–1F8/2DB/2F8–2FB and all 943 B/156 DIR32/319 sparse
nonfield original after-RET DATA. **Giant still NONEXACT, zero
whole-function CODE credit**. [F778 full native control-flow proof](FIGHTER_NATIVE_DEFAULT_F778.md),
`scripts/repo-python scripts/verify-fighter-native-default-f778.py`.

**F781 latest full-parent shared-getter recovery:** independently decoded
original native `005515BA` is the real **8-B getter call**, reached
by **exactly four direct physical JMPs** from action 0/2/4/5
(`00543462`, `005435EA`, `005436CD`, `005436DC`).
Those four source actions now use a shared post-switch getter entry,
while other normal breaks still return directly; the original default
guard retains its authentic short JMP over the getter. The whole
compiled 58KB parent now emits **58,293 of 58,294 CODE B** and
**16,471 of 16,471 original x86**, restoring the complete **46-B/16-x86
native suffix** with three genuine target-attested PE calls (default
`0040FA30/0040FAC0`, shared `0040FA30`). All four default GPR
bytes remain wrong and the **one real length byte deficit in 0x63**
persists, along with the original 059/060/061 GPR discrepancies.
The 943-B afterRET DATA and 68 native physical references across
058/059/060/061/063 are independently rechecked in the same parent.
**No entire 00543210 exact CODE credit.**
[Full F781 source/PE evidence](FIGHTER_EARLY_SHARED_GETTER_F781.md);
`scripts/repo-python scripts/verify-fighter-shared-getter-f781.py`.

**F782 targeted native 0x63 hypothesis rejection:** four actual
full F781 58KB VC7.1 compiled parents compared the original borrowed
expressions with typed opponent `+0x60`, actor `+0x39D`, and
both. Their **entire COFF CODE/DATA and all 1,863 typed relocation
shapes are identical**; real CMP width positions [18,61,84] remain
wrong, leaving original 0x63 706B vs generated 705B.
Simply adding typed borrowed views does not solve this GPR phase;
this is *negative evidence*, not exact credit.
[Reproducible F782 controls](FIGHTER_MODE63_BORROWED_VIEWS_F782.md);
`scripts/repo-python scripts/verify-fighter-mode63-borrowed-f782.py`.

**F790 renewed full 58KB boss native mode-63 control-flow study:**
seven full VC7.1 C++ parent rebuilds independently test
`150>stage`, signed-int conversion, negated comparison,
`<=149`, swapped short-circuit evaluation and genuine
boolean normalization against the pinned native PE.
The first three are codegen-identical to F781's still-nonexact
**58,293/58,294 CODE B**; the other variants either change
native Jcc semantics or produce a **712-B** instead of
706-B mode-63 case. Real CMP register-width ordinals
**18/61/84** remain unresolved; F790 rechecks original
mode-63 15 PE fields, 58/59/60/61 predecessor native
register negatives, the original 46-B common suffix and
all 943 native afterRET switch DATA in complete parents.
**Zero whole original fighter CODE credited.**
[Original native/VC7.1 evidence](FIGHTER_MODE63_CONTROLFLOW_F790.md);
`scripts/repo-python scripts/verify-fighter-mode63-controlflow-f790.py`.

**F792 renewed actual 0x59 356-B source-owner audit:** eight *whole*
58KB fighter recompilations tested a genuine borrowed typed
actor stage `+0x62`, typed velocity/drag `+0x54/+0x5C`,
stage and native x87 comparison order, and real position
assignment/short comparisons. In the fresh full parent,
all native **95/95 0x59 x86** and **16/16 physically
verified PE/COFF target fields** remain correctly positioned,
but **19 genuine GPR operand bytes** are still wrong; reversing
the actual position-add order regresses to **21**. Earlier
case 0x58 remains strictly native, and 0x60/0x61
still show 98/101 wrong GPR operand bytes. 943-B after-RET
DATA and original shared getter are rechecked. No split-case
or giant whole-function CODE credited.
[F792 full native register phase experiment](FIGHTER_BOUNCE_OWNER_PHASE_F792.md);
`scripts/repo-python scripts/verify-fighter-bounce-owner-phase-f792.py`.

**F793 genuine predecessor-to-bounce native GPR phase test:**
ten entire 58KB parents changed real `0x58` game
ten-projectile loop signedness, increment, threshold
comparison, native position copy/float additions and
two-stage guard without fake locals. Eight source
variants retain exact **469B/135-x86 original 0x58
nonfield bytes** and still reproduce **19 wrong
0x59 GPR bytes**; unsigned loop changes one genuine
branch Jcc, swapping x87 add operands changes two
real 0x58 bytes, but **neither corrects 0x59**.
Original 17/16 0x58/0x59 physical call/global
references, entire 46-B shared getter and 943-B
afterRET DATA rechecked within the current parent.
Full 58,294-B giant remains nonexact.
[F793 predecessor native source experiment](FIGHTER_BURST_PREDECESSOR_PHASE_F793.md);
`scripts/repo-python scripts/verify-fighter-burst-predecessor-f793.py`.

**F801 full 0x63 action history / opponent pointer source hypothesis:**
eight complete 58KB VC7.1 parents independently modeled the
real `this+0x32A` signed action-history array,
`this+0x39D` index, `this+0x2E8` owner pointer
and opponent `+0x60` signed stage as typed
*borrowed* views. **All eight entire 59,236B
CODE+943B DATA objects and all 1,863 COFF
relocation shapes are bit-identical**. Original
0x63 **15 native PE fields** and 46B common getter
suffix were revalidated; original 706 B vs source
705 B and CMP register-width ordinals 18/61/84
remain genuine negatives. Full boss not exact;
no authored callable CODE credited.
[F801 physical native/typed-view proof](FIGHTER_BORROWED_ACTION_HISTORY_F801.md);
`scripts/repo-python scripts/verify-fighter-native-borrowed-action-f801.py`.

**F803 entire-parent default-guard GPR experiment:**
15 whole 58KB native-shaped VC7.1 sources varied
the true `00551598` fallback getter/stage
comparison and borrowed `+0x70` typing.
Nine emit **identical entire 59,236-B CODE+DATA
sections and all 1,863 COFF relocation shapes**,
retaining the genuine wrong native GPR operand
bytes at fallback offsets **10/12/16/19**.
Six alternatives move real branch/control
instructions, source bytes or reference counts
and cannot be accepted as native exact.
All original 46-B shared tail true PE calls
reverified, plus earlier 058/059/060/061/063
and 943B original afterRET table in baseline.
[F803 true original default guard study](FIGHTER_SHARED_DEFAULT_GRAMMAR_F803.md);
`scripts/repo-python scripts/verify-fighter-default-source-grammar-f803.py`.
No callable exact CODE.

**Next meaningful giant tasks:** resolve the real native `059` **19**
normalized nonfield GPR discrepancies and `060/061` **98/101**;
recheck *in the next newly compiled entire parent* (do not inherit
F737/F744 counts) and restore the remaining genuine deep x87 stack
lifetimes/earlier source actions. Recheck 0x63 CMP native
register widths [18,61,84] before attempting the last length byte. F759 had **40/40/34** real wrong register ordinals in 190/191/192,
but **F760 repairs all three to zero other nonfield differences** in the
new whole parent. This is a compiler-context/lifetime effect; full
boss CODE and parent-tail JMP layout remain nonexact.
Never invent unused EBP padding or isolate a case for byte credit.

**`0x004EBDA0` /33,293 original CODE B, plus 438 after-RET DATA B.**
Ordinary C++ currently emits original **33,293 B/8,789 x86
mnemonic and width positions**, with **682 native typed COFF fields**
and **30,866/31,003 matching native nonfield bytes**. **137 real
register/phase bytes** remain different across actual actions
`38D/38E/3E3`. The F705 real parent/source-lvalue controls and
older F690/F692 controls were NEGATIVE; do not promote this entire
function or keep repeating equivalent `*(&field)` tests.
Recheck only this native owner if you change it:

```bash
scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py
```

**F794 renewed second giant 004EBDA0 source-ownership review:**
ten fresh entire 33,293-B/8,789-x86 VC7.1 full-parent
builds tested actual typed red/green/blue/alpha
`+0x11..+0x14` member accesses, real stage-counter
updates, and stage-3 condition source order. Nine
preserve all original PE/x86 geometry but still have
**137 wrong register operand bytes**; reversing a
real short-circuit stage test worsens it to
**152**, including wrong original x86 Jcc widths
at ordinals 8042/8046. Crucially the verifier independently
checks *all 682 true original PE/COFF fields* and
the 438-B/60-pointer afterRET table for every whole
parent, not just register-normalized snippets. Giant remains
NONEXACT; zero new whole CODE credit.
[Complete native F794 evidence](CHARACTEROBJECT_COLOR_REGISTER_PHASE_F794.md);
`scripts/repo-python scripts/verify-characterobject-color-source-f794.py`.

**F800 33KB source lexical-scope hypothesis rejected by full PE:**
eleven independent whole `004EBDA0` VC7.1 compiles test actual
0x38B/0x38C/0x38D/0x38E/0x3E3/0x3E4 C++ lexical
braces, individually and combined. **All eleven complete
33,731-B source CODE+DATA sections are byte identical**,
with all **682 physical original PE/COFF fields**
independently verified. All retain the same **137 true
GPR/operand wrong bytes** in the final 33,293-B giant.
Simple case braces cannot fix register phases.
[F800 complete original-target source result](CHARACTEROBJECT_LEXICAL_SCOPE_F800.md);
`scripts/repo-python scripts/verify-characterobject-scope-phase-f800.py`.

**F802 whole CharacterObject 0x38D original relocation caveat:**
22 full 33KB VC7.1 source candidates test meaningful stage
comparison, actual float fade and stage-four multiplication/
color source syntax near first real wrong GPR at `004F344C`.
Only **17/22 candidates** maintain all **682 authentic
PE/COFF fields** at original positions/targets; all those
still have >=**137 actual native wrong CODE bytes**.
**Five compound-update candidates have wrong original
PE field destinations despite emitting 33,293 CODE B,
8,789 x86 and 682 *source* COFF records.**
Never use their candidate-masked mismatch count as exactness
evidence. [F802 full original PE/candidate comparison](CHARACTEROBJECT_STAGE4_RELOCATION_AUDIT_F802.md);
`scripts/repo-python scripts/verify-characterobject-stage4-grammar-f802.py`.

**F806 positive new 46KB fighter source in another entire boss:**
original `005214B0` native has **46B/16-x86 default
and shared-getter tail** `0052CB25..0052CB52`.
The four authentic early actions 0/2/4/5 JMP from
`00521709/00521891/00521974/00521983` to
original `0052CB47`. Current natural tracked C++
rebuild reproduces all 16 tail x86 identities
and **three physical PE calls** to
`0040FA30/0040FAC0/0040FA30`. Only
four real saved-this EBP bytes differ
(native `-0x10`, current incomplete source `-4`).
Rechecks the first **23 complete original action cases**,
all 80 independently typed second-switch fields,
139 original dense pointer labels, 345 sparse bytes
and 901 full afterRET DATA in one affected parent.
Source parent grows **6,830→6,868 CODE B**;
original complete giant is 46,755 B and
remains NONEXACT. No split-case callable credit.
[Actual F806 native shared-tail source](SCRIPTED_FIGHTER_SHARED_GETTER_F806.md);
`scripts/repo-python scripts/verify-scripted-fighter-native-shared-tail-f806.py`.

**F807 expanded the SAME 46KB scripted native fighter:**
current `005214B0` source now integrates the three
additional complete original motion actions
`0x46/0x47/0x48` (**374+310+310
native original inner B, 104+86+86 x86,
41 real typed COFF fields**) with F806's
four original shared getter exits and
real **46B/16-x86** fallback tail.
Previous 23 action bodies, actual 139 dense
jump pointers, 345 sparse bytes and complete
901B afterRET DATA rechecked **in the single
new source parent**. C++ output improves
**6,868→7,817 callable B** (1,650→1,920 x86).
Crucial context negative: adding these true
actions changes subsequent default GPR allocation:
four native wrong register bytes at suffix
offsets **10/12/16/19**, plus four honest
saved-this EBP wrong bytes **2/13/26/36**,
even though native tail control/16 x86/3 PE
calls remain exact in grammar. Do not carry
F806's old GPR phase into a newer parent.
[Original full F807 parent evidence](SCRIPTED_FIGHTER_EXPANDED_NATIVE_ACTIONS_F807.md);
`scripts/repo-python scripts/verify-scripted-fighter-extended-f807.py`.
Still NOT whole original 46,755-B exact.

**F808 new positive 46KB giant 0x49 landing/GPR recovery:**
fresh one-parent original `005214B0`
C++ integrates full native `0x49`
(**350 CODE B /99 x86/15 true PE fields**)
with all 26 previous complete source-backed
game actions and F806's 46-B/16-x86
default/shared getter. Source parent expands
**7,817→8,152 callable CODE B** and
**1,920→2,017 x86**, with true packed
901B afterRET DATA revalidated.
**Crucial physical improvement:** adding
the genuine preceding original `0x49`
naturally RESTORES the four real native
default-guard GPR bytes that were wrong
in F807, *without any register forcing*.
Only four original saved-this EBP displacement
bytes at suffix offsets 2/13/26/36
remain different (native `-0x10`,
incomplete source `-4`). The full
46,755-B giant is STILL NONEXACT;
no 350B subcase or tail credit.
[F808 actual native GPR restoration](SCRIPTED_FIGHTER_LANDING_RESTORES_GPR_F808.md);
`scripts/repo-python scripts/verify-scripted-fighter-landing-shared-f808.py`.

**F810 further positive new 46KB original scripted fighter `0x4A`:**
real full `005214B0` action `0x4A`
is **434 native B/119 x86/19 original
physically typed PE/COFF fields**,
original packed case bounds `00522DD6..00522F87`.
Incorporating F610's natural game bounce
source into F808's full-parent F806
shared-default C++ rebuilds **28 true
original actions** in one fresh
VC7.1 source object: CODE **8,152→8,571 B**,
x86 **2,017→2,134**. All 27 earlier
source-backed original cases, three
real default tail PE calls, four early
native getter JMPs, and full 901-B
afterRET switch DATA independently
verified. **The real 0x4A source rotates
default tail GPR allocation again**:
four genuine GPR operand bytes
`+10/+12/+16/+19` differ, plus four
actual saved-this EBP bytes
`+2/+13/+26/+36`; 46B/16-x86
tail control and PE field shape unchanged.
Do not inherit F808 GPR phase from its
shorter parent. Full 46,755B original
still NONEXACT, no original inner CODE credited.
[F810 full PE/VC7.1 proof](SCRIPTED_FIGHTER_BOUNCE_GPR_PHASE_F810.md);
`scripts/repo-python scripts/verify-scripted-fighter-bounce-shared-f810.py`.

**F811 further 46KB scripted giant source recovered real original `0x4C`:**
tracked original F613 0x4C game recovery
(**285 native B/74 x86/14 genuine typed
PE/COFF fields**) was integrated with
all prior 28 source-backed original
action cases and F806's true 46B
fallback/shared getter in a **single
freshly compiled source parent**.
Source CODE expands **8,571→8,841 B**,
x86 **2,134→2,206**; entire 901B
native afterRET packed switch table,
three real default PE calls and four
early original getter JMP positions
rechecked. **Third native-default
register-phase observed:** adding
real 0x4C rotates source GPR
roles from F810 EAX/ECX/EDX to
F811 ECX/EDX/EAX; original
default remains EDX/EAX/ECX.
Four genuine GPR bytes
`10/12/16/19` and four real
saved-this EBP bytes `2/13/26/36`
still differ, despite exact
46B/16-x86 local CFG/mnemonic/width.
Never transfer old parent GPR
claims into a new parent.
[Original complete source/PE F811 evidence](SCRIPTED_FIGHTER_RECOVERY_GPR_PHASE_F811.md);
`scripts/repo-python scripts/verify-scripted-fighter-recovery-shared-f811.py`.
Still NOT full native 46,755-B exact.

**F812 positive 46KB fighter ten-projectile source and frame lifetime:**
native action 0x58 at 005230A5 is 469 complete interior B/135 x86
with 17 true physical PE fields. One freshly built **30-action
whole C++ parent** preserves 29 prior original case bodies,
the 901B afterRET packed switch DATA and F806's 46-B shared
default/getter with three authentic PE calls and four true early
JMPs. Callable source CODE grows **8,841 to 9,295 B**,
x86 **2,206 to 2,339**. Real gameplay's ten-shot
loop introduces a used index and advances saved this
from EBP-4 to **EBP-8**, naturally restoring all native
default EDX/EAX/ECX GPR roles. Only four honest
EBP displacement bytes remain wrong in the tail
(native EBP-0x10, source EBP-8). The full
original 46,755-B game giant remains NONEXACT
and cannot receive subcase CODE credit.
[F812 native entire-parent proof](SCRIPTED_FIGHTER_TEN_BURST_FRAME_F812.md);
scripts/repo-python scripts/verify-scripted-fighter-ten-burst-shared-f812.py.

**F813 original scripted fighter action0x59 added with correct actor-specific stage:**
the pinned 005214B0 PE has a complete 0x59 at
0052327A..005233DD, **356B/95 x86/16
genuine physical typed PE/COFF fields**. Unlike
F752's different actor, THIS original uses
signed **stage==3** and auxiliary **action 3**.
The new tracked ordinary game source
rebuilds **9,636 callable CODE B/2,432 x86**
in ONE 46KB parent (F812: 9,295 B/2,339 x86),
preserving all previous **30 source-backed
original actions**, real 901-B packed switch
DATA, 46-B F806 shared tail, three real
PE calls and four actual early getter JMP
positions. Every original 0x59 x86 mnemonic
and width is exact, but **57 real case
nonrelocation GPR/EBP bytes remain wrong**,
and the newer default tail again has four
GPR plus four EBP wrong bytes. Never
transfer the F812 tail's register phase
to this larger source. Whole 46,755-B giant
remains NONEXACT, no subcase credit.
[F813 full original/source PE check](SCRIPTED_FIGHTER_STAGE3_BOUNCE_F813.md);
scripts/repo-python scripts/verify-scripted-fighter-stage3-bounce-f813.py.

**F814 real 0x5D/0x5E source-context evidence in the same scripted giant:**
adding F617's two genuine original **337B/101-x86/
8-PE-field** air-transition cases after F813's true
stage-3 0x59 yields one **10,280B/2,630-x86
full-parent C++ source** with 33 original action
bodies. Every original 0x59/5D/5E handler is
bounded by real packed jump targets; all 16
0x59 and 8+8 new typed PE fields, 30 prior
actions and 901B afterRET table rechecked.
But *both* 0x5D and 0x5E have **61 original
GPR/CFG role mismatches** in this new parent;
the old short-parent F617 strict 0x5E label
must not be carried forward. A second
full-parent source swapping the action59
getter comparison restores 0x5E GPRs but
breaks actual 0x59 x86 opcodes/widths at
ordinals 54–57 and inserts a NONNATIVE
POP ESI, changing the true 46B/16-x86
default to 47B/17-x86. This alternative is
**rejected**, not recorded as native exact.
Whole 46,755B game still nonexact.
[F814 original PE/source context](SCRIPTED_FIGHTER_AIR_CONTEXT_F814.md);
scripts/repo-python scripts/verify-scripted-fighter-air-context-f814.py.

**F815 selected original 46KB scripted fighter now includes face action 0x5F:**
real packed second-switch original 00523680..0052370F
has 144 native B/44 x86 and three genuine zero-addend
PE calls. Natural F620 facing source uses action
transitions **0 then 1**, real this/opponent +0x44
float comparisons, and native signed direction +0x66.
A newly compiled whole 005214B0 parent grows source
**10,280 to 10,409 CODE B**, x86 **2,630 to 2,672**;
earlier 32 native cases, full 901B separate packed
switch DATA and 46B shared getter rechecked.
The real 0x5F machine still differs in 13 genuine
saved-receiver EBP bytes (source -8 vs native -0x10),
plus two authentic parent-tail JMP displacement bytes.
[Complete original 0x5F physical source](SCRIPTED_FIGHTER_FACING_F815.md);
scripts/repo-python scripts/verify-scripted-fighter-facing-f815.py.
Full giant still NONEXACT; no split-case credit.

**F816 major positive native saved-this frame and default-tail recovery:**
the original 005214B0 fighter now includes *both* complete
0x60/0x61 resource-ten-volley cases, each **586 real CODE B /
169 x86 /11 physical original PE/COFF fields**.
Actual game loop indices EBP-8 and EBP-0xC naturally
restore the original saved this **EBP-0x10**. The source
grows 10,409 to **11,551 B/3,006 x86** with 33 earlier
physical original cases plus 901B afterRET packed DATA.
The ordinary 0x5F/60/61 native-correct direct function
exits reproduce actual parent epilogue CFG, all
x86 widths/roles and **3+11+11 authentic PE fields**.
Their only complete-case machine negatives are the
different-sized incomplete parent's original
external long-JMP rel32 displacements (two source
byte differences in 0x5F, four in each 0x60/61).
**Crucial: full native 46B/16-x86 F806 default/getter
now matches ALL 34/34 nonrelocation original PE
machine bytes, plus all three genuine physical PE
REL32 calls and four early shared getter JMPs.**
Whole 46,755B game still NONEXACT; no subcase or tail
credited callable CODE.
[F816 original entire-parent native physical proof](SCRIPTED_FIGHTER_RESOURCE_VOLLEYS_F816.md);
scripts/repo-python scripts/verify-scripted-fighter-resource-volley-f816.py.

**F817 next scripted original 46KB resource selector:**
real packed original 0x62 at 00523BA4 is **249B/65
x86/4 genuine PE/COFF game calls**. Fresh one-parent
source extends F816 to **11,785 CODE B /3,069 x86**,
still preserving original saved this EBP-0x10,
all previous 5F/60/61 complete native machine
geometry, three-plus-eleven-plus-eleven true
PE fields and entire 901B afterRET packed DATA.
Natural original 0x62 resource decisions choose
actions 0x5F, 0x5D or 0x5E.
The new native-shaped case retains **10 honest
GPR operand bytes** plus 2 external final JMP
bytes different, and its genuine preceding
C++ source ROTATES the later default GPRs
again, leaving **four true default-tail byte
negatives 10/12/16/19**. Saved-this frame
remains physically native EBP-0x10. Do not
inherit F816's 34/34 native default source
match from a shorter parent.
[F817 target PE/source proof](SCRIPTED_FIGHTER_RESOURCE_SELECTOR_F817.md);
scripts/repo-python scripts/verify-scripted-fighter-resource-selector-f817.py.
Entire 46,755B giant still NONEXACT, no case credit.

**F819 additional real original case0x63 in the same 46KB giant:**
fresh full source integrates F626's 00523C9D native original
**417-B/109-x86/7-true-PE-field** mode state with existing
0x5F/60/61/62 full native geometry and original 901-B packed
DATA. Generated whole-parent callable CODE grows **11,785
to 12,187 B** (x86 3,069 to 3,176); saved this remains
native EBP-0x10. But original 0x63 is NOT register-exact
in this newer larger source: two actual x86 widths at
ordinals 38/61, plus a source COFF relocation at
x86 ordinal 48 shifted one byte versus the real
native PE operand. The historical 143 source-mask
diagnostic is NOT physical exactness evidence;
under a safe union of original and source PE
fields **142/388 comparable nonfield B differ**.
F626 short-parent source equality cannot be inherited.
Default suffix has four authentic remaining GPR bytes.
[F819 whole 0x63 PE-backed context](SCRIPTED_FIGHTER_MODE63_CONTEXT_F819.md);
scripts/repo-python scripts/verify-scripted-fighter-mode63-context-f819.py.
Enclosing 46,755B function still NONEXACT.

**F820 three more complete real 46KB scripted fighter original landings:**
native 8C/8F/90 each has **289 whole interior B /80 x86 /
8 true physical PE fields** (867 real case B /240 x86 /
24 game-call/float targets). One new pinned VC7.1 whole
parent builds **13,009 callable CODE B/3,410 x86**,
up from F819 12,187B/3,176 x86, with all early
source-backed states, original 901B afterRET DATA and
default tail checked. Earlier short-parent F628 zero
GPR mismatches do NOT transfer: each case in the
longer whole source has **55 honest nonrelocation byte
differences**, including true enclosing epilogue JMP.
A separate native-field audit CORRECTED F819's
0x63 source-COFF relocation at x86 ordinal48: source
field is physically **one byte earlier** than original
PE, so historical 143 source-mask mismatch B is
diagnostic only, not target exactness; safe union
of native/source fields leaves **142/388** wrong.
[F820 current whole PE/source proof](SCRIPTED_FIGHTER_LANDINGS_F820.md);
scripts/repo-python scripts/verify-scripted-fighter-landing-trio-f820.py.
No callable exact giant or case credit.

**F821 additional physical native 0x91 original arc/gameplay in same giant:**
authentic 005214B0 original action0x91 is **288 full
interior CODE B/78 x86/12 physically typed PE call,
float and __ftol2 references**. Source now
rebuilds **13,282 callable B/3,486 x86** in
a single growing whole parent, with all three
prior 8C/8F/90 landing states, earlier
0x63 native PE field shift, EBP-0x10 receiver
and 901B original postRET packed DATA checked.
This wider source has **37 original nonfield
byte negatives** in case91, despite native
opcode/width and all 12 PE field positions.
Default still has four actual GPR bytes wrong.
Short-parent F629 strict claim does not transfer.
[F821 pinned original arc91 source](SCRIPTED_FIGHTER_ARC91_F821.md);
scripts/repo-python scripts/verify-scripted-fighter-arc91-context-f821.py.
No original giant callable exact credit.

**F822 major complete original fighter timed-landings source advance:**
one fresh 005214B0 VC7.1 parent now emits **14,326
callable B/3,770 x86** and includes four more
complete original gameplay cases 0x96/97/98/9A.
Each is **276 native CODE B/73 x86/9 true PE
references**, for 1,104 newly sourced internal B
and 36 genuine native fields. Each source now
matches ALL original x86 mnemonics, widths,
register roles, native PE field positions/targets
and nonrelocation bytes except precisely **two
authentic encompassing-giant final JMP bytes**
per case. Original saved this EBP-0x10 and
901B afterRET packed DATA retained. Earlier
0x91/8C/8F/90/0x63 physically rechecked;
their documented native operand differences
and shifted mode63 COFF field still apply.
These cases are not callable independent
whole original functions and gain zero
accepted authored exact CODE.
[F822 four full native cases](SCRIPTED_FIGHTER_TIMED_LANDINGS_F822.md);
scripts/repo-python scripts/verify-scripted-fighter-timed-landings-f822.py.

**F823 two more complete native 46KB fighter timer cases:**
original 9B and 9C are each **276 native B/73 x86/9
actual typed PE references**, with real -10/-13 float
heights and original action2 transitions. One affected
freshly compiled whole parent is **14,848 callable
B/3,912 x86**, up from F822 14,326B/3,770 x86.
All **six** 96/97/98/9A/9B/9C native timer cases
have correct opcode/width/GPR and **54 original
PE fields**; only two genuine full-giant epilogue
JMP operand bytes (272/273) differ in each case,
not accepted as exact CODE. Previous 91, 8C/8F/90,
actual 0x63 shifted COFF field, and 901B afterRET
DATA independently checked.
[F823 physical whole-parent proof](SCRIPTED_FIGHTER_LANDING_PAIR_F823.md);
scripts/repo-python scripts/verify-scripted-fighter-landing-pair-f823.py.
Whole 46,755B fighter still NONEXACT.

**F824 whole 46KB fighter original 0x9E ground boost integrated:**
original physical 00524939 complete **243 native
inner CODE B/66 x86/8 real typed PE fields**,
natural >= ground-approach and action A/9.
Fresh one-parent VC7.1 output expands
**14,848 to 15,076 callable B**, x86
**3,912 to 3,976**. Exact native 0x9E
opcode/width/GPR and all eight real PE field
positions/targets; only four honest
external whole-giant epilogue JMP operand
bytes 202/203 and 239/240 differ,
not accepted. All six earlier original
timers, actual 91/8C/8F/90 states, 0x63
shifted PE field and 901B separate
afterRET DATA freshly checked.
[F824 complete original PE/source](SCRIPTED_FIGHTER_GROUND_BOOST_F824.md);
scripts/repo-python scripts/verify-scripted-fighter-ground-boost-f824.py.
Original 46,755B giant still NONEXACT.

**F825 three further 9F/A0/A1 original timed landings:**
native each **276 inner CODE B/73 x86/9
physical PE/COFF fields**, with actual
-9/-10/-13 initial float height and action0.
One newly compiled 005214B0 whole parent
now **15,859 callable B/4,189 x86**,
up from F824 15,076B/3,976 x86.
All NINE preceding/current original
96/97/98/9A/9B/9C/9F/A0/A1 timer bodies
have genuine native x86 mnemonic/width/GPR
and 81 original PE fields; each has ONLY
two authentic enclosing-parent final JMP
operand bytes (272/273) wrong, never
accepted as callable exact. Original 9E
ground boost and current default GPR phase
also checked, 901B switch DATA unchanged.
[F825 native original-source proof](SCRIPTED_FIGHTER_LAST_TIMERS_F825.md);
scripts/repo-python scripts/verify-scripted-fighter-last-timers-f825.py.
Whole 46,755-B giant still NONEXACT.

**F826 genuine 0xA3/A4/A5 COUNTER-FREE fighter landings:**
three complete original **264 native B/71 x86/9
genuine PE fields** per case; crucially these
states omit the prior family short +0xF00
counter clear. Real native initial ground
heights -9/-10/-13 and action2 continue.
New entire affected C++ parent **16,606
callable B/4,396 x86**, up from F825
15,859B/4,189 x86, retains the earlier
nine original timer cases, native 0x9E,
901B afterRET packed DATA and native
EBP-0x10 frame. Every new case has
identical native opcode/width/GPR and true
original PE references, with ONLY two
actual enclosing-giant final JMP operand
byte negatives (260/261) each.
[F826 original complete native source](SCRIPTED_FIGHTER_NO_COUNTER_F826.md);
scripts/repo-python scripts/verify-scripted-fighter-no-counter-landings-f826.py.
Still NONEXACT whole 46,755B giant, zero split-case credit.

**F827 new 46KB giant native sprite and full default-tail recovery:**
the same 005214B0 fighter now contains both
real A7/A8 projectile cases, each **350 native
inner B/97 x86/12 genuine physical PE fields**.
Native source uses real sprite 0x38, signed
direction*30, true +0xF00 cooldown,
real StartAnimation/Spawn, projectile
fall x87 and next states 0/2.
One whole VC7.1 parent now builds
**17,276 callable B/4,586 x86**,
up from F826 16,606/4,396.
A7/A8 source opcodes/GPR/widths and 24
real PE call/global fields match; ONLY
two authentic parent-final long-JMP
displacement bytes (346/347) differ
per case, no split exact credit.
Previous 3 A3/A4/A5, 9 timers,
9E and full original 901B packed
DATA rechecked. **Major positive GPR:
46B/16-x86 native F806 default/getter
is again 34/34 nonrelocation machine
bytes IDENTICAL plus three true original
REL32 PE fields**, restoring actual
EBP-0x10 and EDX/EAX/ECX naturally from
genuine preceding original sprite logic.
[F827 original whole-parent/source proof](SCRIPTED_FIGHTER_PROJECTILES_F827.md);
scripts/repo-python scripts/verify-scripted-fighter-projectiles-f827.py.
Original full 46,755B still NONEXACT.

**F829 B4/B5 real original restart cases in the 46KB fighter:**
each complete **215 native B/60 x86/8 physically
typed original PE fields**, original initial
heights +8/-8 and auxiliary motion 8/10.
Fresh one-parent VC7.1 source becomes
**17,676 callable B/4,702 x86**,
up from F827 17,276/4,586.
All real native instruction opcodes/GPR/widths
and 16 physical call/global targets verified.
Precisely **three real whole-giant epilogue
JMPs per case** remain two-byte-displaced
at case offsets 169/170, 206/207, 211/212;
these are not masked as exact CODE.
Earlier A7/A8 PE-backed projectile source
and full F806 46B shared default with
**34/34 identical unrelocated native
machine bytes plus three authentic PE
calls** remain verified. Original 901B
switch DATA separately owned.
[F829 original full-parent native proof](SCRIPTED_FIGHTER_MOTION_RESTART_F829.md);
scripts/repo-python scripts/verify-scripted-fighter-motion-restart-f829.py.
Whole original 46,755B still NONEXACT.

**F830 genuine next native 005214B0 fighter action 0xD0:**
whole original **195 inner CODE B/60 x86/
6 original PE/COFF fields** now in fresh
**17,856-B/4,760-x86** selected parent.
Real signed-facing flip, x87 FUCOMPP,
ground drag and auxiliary state are reproduced.
Only four real physical nonrelocation bytes
at +154/+155/+191/+192 differ, encoding two
enclosing original game epilogue JMP targets.
Earlier B4/B5 original cases, all 16 PE
refs and 901B original afterRET DATA rechecked.
The newly restored original D0 C++ rotates
default getter GPR phase back to four
nonrelocated byte differences +10/+12/+16/+19.
Do not inherit F829 default tail equality
in this longer parent. Whole 46,755B remains
NONEXACT, no inner-case CODE credited.
[F830 native PE/source proof](SCRIPTED_FIGHTER_REFLECT_D0_F830.md);
scripts/repo-python scripts/verify-scripted-fighter-reflect-d0-f830.py.

**F831 original native 0xCF fall/ground state in SAME 46KB fighter:**
actual 005260D6 complete **114 native inner B/30
x86/4 physically typed original PE fields** added.
Whole C++ parent now emits **17,955 callable B/4,788
x86** versus F830 17,856/4,760. All CF native
opcode widths and original PE call/global targets
verified, but 20 actual nonrelocation case GPR/JMP
operand bytes differ in this source. The TRUE
earlier CF C++ changes following native D0
register allocation again: D0 now has **39
honest nonfield byte mismatches**, not F830's
four shorter-parent bytes. Prior B4/B5 source
and original 901B switch DATA checked.
**The complete 46B/16-x86 default/getter
recovers 34/34 original nonrelocation
machine bytes plus all three authentic
PE REL32 calls naturally from actual
preceding game C++**, never forced GPRs.
[F831 native selected whole source](SCRIPTED_FIGHTER_FALL_CF_F831.md);
scripts/repo-python scripts/verify-scripted-fighter-fall-cf-f831.py.
46,755B enclosing function still NONEXACT,
zero independent case/suffix CODE credit.

**F832 next two true original 46KB scripted fighter resource shots D1/D2:**
original complete D1 **199 inner B/59 x86/8 typed PE
fields**, D2 **251B/74 x86/10 genuine fields**,
now in one freshly compiled **18,375-B/4,917-x86**
whole parent, up from F831 17,955B/4,788 x86.
Actual source is ACTOR-SPECIFIC: signed
resource decay **6** rather than F651's
other-fighter 3; D2 scales original horizontal/
vertical speeds and calls PrepareActionAt453D60
**BEFORE** native sprite 0x3E6 emission,
not F652's other-fighter post-spawn order.
All 18 original PE call/global field positions,
types and true native targets verified from
physical source rather than inherited field ordinals.
Native full opcode/width geometry agrees, but
32 and 46 actual D1/D2 nonrelocation register/
parent-JMP byte negatives remain. Previous
CF/D0 physical source with real PE fields,
901B afterRET DATA and 46B shared tail
rechecked; later default 4 honest GPR bytes
still wrong. Enclosing 46,755B remains
NONEXACT with zero new whole-function credit.
[F832 actor-specific native PE proof](SCRIPTED_FIGHTER_RESOURCE_SHOTS_F832.md);
scripts/repo-python scripts/verify-scripted-fighter-resource-shots-f832.py.

**F833 selected original scripted 0xC9 storm projectile source:**
actual native 0052577B whole **279B/86 x86/
11 physically typed original PE fields**
joins the same 005214B0 actor-specific
giant C++ parent, now **18,639 callable
B/5,001 x86** from F832 18,375/4,917.
Original storm 00454BC0(3,4,0xFF),
two signed-direction 0x7D/0x7E native
projectiles, float X at this+0x44,
Y global 00658268 and original height
recovery are ordinary C++ source.
A genuinely borrowed UNINSTANTIATED X
view reproduces all physical 86 x86
mnemonics and widths; direct raw X or
Y alias alternatives change real x87
codegen. All 11 original call/global
PE fields verified; **47 honest native
nonrelocation GPR/parent-JMP bytes
still differ** in this incomplete parent.
Prior CF/D0/D1/D2 physical source, 901B
packed DATA and shared default checked.
The preceding 657B C8 remains missing;
do not copy C9's GPR phase as exact.
[F833 original target PE/source proof](SCRIPTED_FIGHTER_FOURWAY_C9_F833.md);
scripts/repo-python scripts/verify-scripted-fighter-fourway-c9-f833.py.
Original 46,755B giant still NONEXACT.

**F834 major original 46KB fighter native C8 FULL 657B source and downstream recovery:**
actual original 005254EA 0xC8 **657 complete interior
B/190 x86/17 genuine typed PE fields**, source-grown
normal VC7.1 entire fighter now **19,281 callable
B/5,189 x86** versus F833 18,639/5,001.
Full real storm/facing/projectile/short-counter gameplay
is natural C++ with seven direct native parent exits.
The actual prefix **++S16(0xF00)** recovers native
MOV CX/ADD CX,1 (F834 alternative assignment/compound
produce 656B wrong width and misplaced following PE
fields). All 190 physical x86 mnemonics/widths/GPR
and 17 source PE fields now match; **ONLY seven real
enclosing parent JMP two-byte pairs** differ in C8.
More importantly, restoring real preceding C8 NATURALLY
fixes all prior GPR source negatives in five later
complete native cases C9 (279B/86x86/11 refs),
CF (114B/30/4), D0 (195B/60/6),
D1 (199B/59/8), D2 (251B/74/10):
all their original non-PE machine bytes now agree
except TRUE encompassing final epilogue long-JMP
operand pairs. Full F806 46B/16-x86 shared getter
remains **34/34 original nonrelocation machine
bytes plus three true PE REL32 calls**.
**All FIVE genuine 901B afterRET packed jump
tables were physically revalidated**, not merely
their length. Entire 46,755B original STILL
NONEXACT, zero formally accepted inner-case/suffix
or DATA CODE.
[F834 physical whole native recovery](SCRIPTED_FIGHTER_FULL_C8_F834.md);
scripts/repo-python scripts/verify-scripted-fighter-fourway-c8-f834.py.

**F836 full native 0xCA source added to original 005214B0 giant:**
pinned original 00525892..00525A33 is **418 inner CODE
B/121 x86/11 true physically typed PE fields**,
not another fighter's 439B F759 case. Selected
normal whole VC7.1 parent now **19,684 callable
CODE B/5,308 x86**, up from F834 19,281/5,189.
Original x87 grounded tests, real stage2 native
sprites and two direct enclosing-parent action
exits are natural C++. Native original opcode,
width, GPR and PE target fields are exact; only
FOUR honest original whole-giant epilogue
JMP operand bytes (+203/204,+414/415) differ.
Preceding C8/C9 original full native sources
and all FIVE 901B packed switch DATA tables
freshly rechecked. Original default 46B
source GPR phase rotates again: four true
nonrelocation byte negatives +10/12/16/19,
saved-this EBP-0x10 and 3 PE calls correct.
[F836 native selected whole-parent proof](SCRIPTED_FIGHTER_FOURWAY_CA_F836.md);
scripts/repo-python scripts/verify-scripted-fighter-fourway-ca-f836.py.
Whole giant NONEXACT; no split-case credit.

**F837 native fighter CB completes fourway series AND downstream register recovery:**
pinned original 005214B0 CB is **496 original inner
CODE B/141 x86/12 true PE call/global fields**
(not the other-fighter F759 445B case). Original
counter reset first, 16-bit ++short native
MOV DX/ADD DX,1, authentic borrowed X+0x44
projectile and all physical field targets
are normal C++. One new entire selected
VC7.1 parent **20,165 callable CODE B/5,447 x86**
(previous F836 19,684/5,308). Only four
original enclosing-parent JMP bytes at
CB +214/215 and +492/493 remain wrong.
TRUE preceding CB source ALSO recovers all
later CF/D0/D1/D2 GPR bytes naturally:
C8/C9/CA/CB/CF/D0/D1/D2 now each differ
ONLY at genuine encompassing-giant final
long-JMP displacement operands. Complete
46B/16-x86 original F806 default tail
**34/34 native nonrelocation bytes**
plus 3 real PE call fields recovered,
and all FIVE 901B afterRET native packed
jump tables verified.
[F837 selected whole-original PE proof](SCRIPTED_FIGHTER_FOURWAY_CB_F837.md);
scripts/repo-python scripts/verify-scripted-fighter-fourway-cb-f837.py.
Whole 46,755B giant STILL NONEXACT.

**F839 actor-specific original CC repaired beyond historical source:**
native original 00525C24..00525DCF
**428 complete inner B/126 x86/10
true PE call/global fields** now in
full new **20,578 callable B/5,571-x86**
source parent. Unlike other actor F649,
native 0xCC requires x87 order POS48
then POS54, real flag clear INSIDE
stage3 and **unconditional vtable
method call** AFTER conditional
stage decrement. Prior source
incorrectly guarded that virtual
call and had actual wrong Jcc.
Natural tracked C++ now matches all
native CC opcode/width/GPR/x87/
PE bytes except exactly TWO
full-giant epilogue long JMP
displacement byte pairs +186/187,
+424/425. All preceding C8-CB and
following CF-D2 physical source
cases and five original 901B
afterRET tables remain verified;
default 46B 34/34 native
nonrelocation plus three PE calls.
[F839 selected original CFG proof](SCRIPTED_FIGHTER_COMPLEX_CC_F839.md);
scripts/repo-python scripts/verify-scripted-fighter-complex-cc-f839.py.
Whole 46,755B still NONEXACT.

**F840 selected original 0xCD complete native source:**
physical original 00525DD0 is **387 native
inner CODE B/113 x86/8 true original PE fields**
rather than F760 other-fighter 435B CD. Real
stage3 POS=11.0, vertical velocity=17.5,
drag=0.8, native 16-bit ++, float
POS48+POS54 and UNCONDITIONAL virtual
callback after conditional stage subtract
now normal C++. New entire VC7.1 parent
**20,950 callable CODE B/5,682 x86**,
from F839 20,578/5,571. All genuine
original CD opcode/width/GPR/x87/PE
fields match except TWO actual original
whole-giant epilogue relative JMP
operand pairs (+186/187, +383/384).
Earlier complete CC, C8-CB and CF-D2
physical original PE cases rechecked,
46B shared default 34/34 native
nonrelocation bytes + 3 original
PE REL32 calls, and all FIVE original
901B packed afterRET tables verified.
[F840 current actor CD PE proof](SCRIPTED_FIGHTER_COMPLEX_CD_F840.md);
scripts/repo-python scripts/verify-scripted-fighter-complex-cd-f840.py.
Original enclosing 46,755B still NONEXACT.

**F841 completes three genuine selected actor CC/CD/CE cases:**
original CE 00525F53 is **387 full native
inner B/113 x86/8 original physical PE
fields**, with real stage3 POS **-11.0f**,
speed17.5f, drag0.8f, 16-bit native
counter increments and unconditional
vtable method callback. One selected
full normal VC7.1 source now **21,322
callable CODE B/5,793 x86**, up
from F840 20,950/5,682.
All native CE GPR/x87/opcode/width/PE
bytes match except two true enclosing
original giant epilogue JMP pairs
(+186/187,+383/384). All three CC/CD/CE,
preceding C8-CB and following CF-D2
original complete case PE geometry
reverified, plus F806 46B default
34/34 native nonrelocation bytes
and all five original 901B
afterRET packed tables.
[F841 actual original CE PE proof](SCRIPTED_FIGHTER_COMPLEX_CE_F841.md);
scripts/repo-python scripts/verify-scripted-fighter-complex-ce-f841.py.
The full 46,755B fighter still NONEXACT.

**F842 three original 12C/12D/12E falling-recovery game cases in 46KB fighter:**
selected physical original complete states are **207/219/207
native inner B**, **59/61/59 x86**, SIX typed
PE fields each. Original actor-only prepare
frame stages **1/3/2**, animation **1B/1C/1C**
and +0xF00 short reset ONLY in 12D were
independently read from original Japanese
PE, not other actor F653 values 2/4/2,
1B/1D/1D. One new whole parent is
**21,910 callable CODE B/5,966 x86**,
up from F841 21,322/5,793. All three
new complete cases match native opcode/
width/GPR and 18 physical PE references;
only TWO actual entire-fighter epilogue
long-JMP operand bytes differ per case.
All ELEVEN preceding genuine C8-D2
native whole-case sources and all five
901B afterRET packed jump DATA tables
reverified. The new source context rotates
the 46B shared getter to FOUR actual
unrelocated GPR byte mismatches at
10/12/16/19; do not inherit F841
shorter-parent default equality.
[F842 original entire PE source](SCRIPTED_FIGHTER_FALLING_RECOVERY_F842.md);
scripts/repo-python scripts/verify-scripted-fighter-falling-recovery-f842.py.
Whole native 46,755B STILL NONEXACT, no
independent inner-case callable CODE credit.

**F843 actual original selected actor 12F after four falling states:**
physical game 00526646 full **207 native inner B/
59 x86/six true PE field targets**, NOT
other actor F654's 288B/82 x86.
Actor original native prepares animation
0x1B at stage1, transitions state2,
no +0xF00 clear. One entire selected
VC7.1 fighter now **22,102 callable
source CODE B/6,023 x86** (F842
21,910/5,966). Complete original
12C/12D/12E/12F each physical
PE field, x86 width/GPR and previous
eleven C8-D2 complete original cases
all rechecked in new object.
New 12F only real original complete
game parent final JMP relative
two-byte operand difference +203/204.
All five original 901B packed
afterRET jump DATA tables rechecked.
Common default 46B still has
four real GPR byte negatives,
no whole-game exact code credit.
[F843 original physical PE proof](SCRIPTED_FIGHTER_FALLING_12F_F843.md);
scripts/repo-python scripts/verify-scripted-fighter-falling-12f-f843.py.

**F844 genuine next native 130 ground/animation state in original 46KB fighter:**
selected original at 00526715 is **202
native interior CODE B/58 x86/five physical
PE call/global fields**, NOT F654 other
actor's 261B source. Authentic x87 sum
POS48+POS54, native grounded position/
velocity/drag zero ORDER, original action9
and prepare animation 0x1C at stage3
now normal C++. Fresh selected whole
VC7.1 parent emits **22,289 callable
B/6,079 x86**, up from F843
22,102B/6,023 x86. All original 130
opcode/width/GPR and true PE locations
match except TWO full giant-epilogue
long-JMP two-byte operand pairs
(130 +84/85, +198/199).
All four earlier genuine 12C..12F
cases, ELEVEN real C8..D2 source
cases and ALL FIVE 901B afterRET
packed native tables rechecked.
The true 46B default retains four
honest GPR nonfield bytes wrong
at 10/12/16/19; original whole
46,755B still NONEXACT with no
split case callable CODE credit.
[F844 current selected original PE proof](SCRIPTED_FIGHTER_GROUNDED_130_F844.md);
scripts/repo-python scripts/verify-scripted-fighter-grounded-130-f844.py.

**F844 original fighter 0x130 complete grounded-recovery case:**
the actual pinned game at 00526715 has **202
whole inner CODE B/58 x86/5 native PE references**,
now in one fresh **22,289 callable B/6,079 x86**
selected giant parent (F843 22,102/6,023).
Native x87 operand order POS48+POS54, actual
three motion resets, stage3 animation1C
and two entire-parent direct returns
naturally reconstruct all original x86
mnemonics/widths/GPR and real PE fields,
with only two true original giant epilogue
JMP operand byte pairs +84/+85,+198/+199
different. Earlier 12C-12F and ELEVEN
C8-D2 original complete cases rechecked
with true physical PE fields. All five
901B original afterRET jump tables remain
correct. The 46B default/getter has four
actual GPR byte negatives +10/+12/+16/+19,
not accepted whole CODE.
[F844 physical selected source](SCRIPTED_FIGHTER_GROUNDED_130_F844.md);
scripts/repo-python scripts/verify-scripted-fighter-grounded-130-f844.py.
Complete 46,755-B fighter remains NONEXACT.

**F845 true original 0x131 grounded state in the growing fighter:**
the native physical handler 005267DF..005268A8
has **202 complete original interior B/58 x86/5
typed real PE fields**, and genuine stage3
animation **0x1D** (unlike prior 0x130 0x1C).
The next distinct physical action is 0x133
at 005268A9; default 0x132 maps the
shared getter and cannot bound 0x131.
One full selected VC7.1 C++ parent
**22,476 callable B/6,135 x86**, up
from F844 22,289/6,079. All 0x131
native register/x87 and PE bytes match
except two real parent-epilogue JMP
operand pairs +84/+85,+198/+199.
All prior 0x130, four 12C-12F and
eleven C8-D2 original PE cases and all
five 901B native jump tables checked.
Common default 46B has four honest
GPR byte negatives in the new context.
[F845 selected original PE proof](SCRIPTED_FIGHTER_GROUNDED_131_F845.md);
scripts/repo-python scripts/verify-scripted-fighter-grounded-131-f845.py.
Whole 46,755B native original still NONEXACT.

**F846 actual 0x133 original fighter side-step restores native getter GPR:**
physical original 005268A9 0x133 case is
**270 whole interior B/78 native x86/six PE
fields**. At stage8 it multiplies signed
facing by **70**, FILDs that integer then
FADDs the true float X at this+0x44,
not reversed x87 arithmetic. One updated
full VC7.1 parent **22,731 callable B/
6,211 x86**, versus F845 22,476/6,135.
Native 0x133 opcodes/width/GPR/PE-field
positions and targets all match; only
two real complete-giant epilogue long-JMP
operand bytes at +266/+267 differ.
All 17 prior 0x130/0x131/12C-12F/C8-D2
whole native source cases and all FIVE
901B packed jump tables freshly rechecked.
Genuine preceding 0x133 naturally
restores F806 shared getter **34/34
real original nonrelocation bytes** plus
three physical original PE REL32 fields.
[F846 native selected source](SCRIPTED_FIGHTER_SIDESTEP_133_F846.md);
scripts/repo-python scripts/verify-scripted-fighter-sidestep-133-f846.py.
Enclosing 46,755B game function STILL
NONEXACT, no standalone case/suffix credit.

**F847 authentic fighter 134/135 original projectile cases:**
both game interiors are **278 whole native
CODE B/82 x86/seven true original PE
fields each**, sprite 0x334 at stage4 and
sprite 0x339 at stage7, native prepare
animation1D at stages5 and7 respectively.
Fresh selected VC7.1 whole fighter is
**23,257 callable B/6,371 x86**
(previous F846 22,731/6,211).
Every native x86 width/GPR and 14 real
PE call/global fields match except
two genuine full-giant final JMP
operand bytes +274/275 per case.
All 18 preceding whole original C8-D2/
12C-12F/130/131/133 source cases and
five packed original 901B jump tables
rechecked in the new COFF. Original
46B shared getter remains **34/34
native nonrelocation bytes** plus
three original PE REL32 calls.
[F847 current actor game PE proof](SCRIPTED_FIGHTER_PROJECTILES_134135_F847.md);
scripts/repo-python scripts/verify-scripted-fighter-projectile-134135-f847.py.
Whole 46,755B still NONEXACT; no
independent inner case CODE credit.

**F849 new selected native 0x136 ground physics and HONEST GPR negatives:**
original actual native 00526BE3 0x136
is **321 whole interior CODE B/95 x86/
10 true original PE fields**. Native stage>2
ground drag and 0065747C extra correction,
stage5 sprite0x33A and animation1D are
normal current source, one complete
VC7.1 selected parent now **23,563
callable B/6,464 x86** (F847
23,257/6,371). All original case
mnemonics/widths and ten physical PE
target offsets/types match. BUT 15 true
register operand bytes within the
late sprite/prepare portion (starting
at native ordinal70 ECX vs source EAX)
and two enclosing-parent epilogue
JMP operand bytes +317/+318 still
DIFFER. Ten meaningful C++ syntax/
condition/float controls do not recover
that GPR phase. Previous 20 complete
native original C8-D2/12C-12F/130/131/
133/134/135 source cases and all FIVE
901B afterRET packed tables rechecked.
Current 46B default has FOUR honest
GPR operand negatives +10/12/16/19.
[F849 physical original/negative proof](SCRIPTED_FIGHTER_GROUND_PHYSICS_136_F849.md);
scripts/repo-python scripts/verify-scripted-fighter-physics-136-f849.py.
Whole original 46,755B still NONEXACT,
zero inner case or callable exact CODE.

**F850 two actual 0x186/0x187 grounded native states:**
selected original 186 **250 inner B/74 x86/7 PE
fields**, 187 **214B/61 x86/6 PE fields**;
distinct real original ground correction
globals 00658058 vs 00659090, stage3
animation1D with sprite341 vs 1C without
sprite. New entire normal VC7.1 parent
**23,997 callable B/6,595 x86**, up
from F849 23,563/6,464. Original
opcodes/x86 widths and all 13 physical
PE fields/true targets match, but
genuine source GPR byte differences
of **47/38** plus 2 whole-game
epilogue JMP bytes PER case still
apply. Earlier original 136 GPR
negatives retained: no false exact
credit. Twenty prior complete
native cases and all five original
901B packed afterRET DATA tables
reverified. F806 46B common getter
again **34/34 native nonrelocation
bytes** plus three original PE calls.
[F850 true original PE and GPR negatives](SCRIPTED_FIGHTER_GROUND_186187_F850.md);
scripts/repo-python scripts/verify-scripted-fighter-ground-186187-f850.py.
Complete 46,755B original giant NONEXACT.

**F851 genuine selected fighter 0x188 ground/recovery source:**
original 00526EF4 complete **214 native
inner CODE B/61 x86/six genuine typed
PE fields**, original +12.5f height,
gravity00659090, action2, stage2
prepare animation1D. New ONE full
VC7.1 parent **24,196 callable
CODE B/6,654 x86** from F850
23,997/6,595. All original x86
mnemonics/widths and all six PE
call/global targets match, BUT 38
honest native GPR operand bytes plus
two actual encompassing giant final
JMP operand bytes remain DIFFERENT.
Earlier original 136 and 186/187
register negatives retained; 20 prior
original whole interior cases and
all FIVE 901B packed afterRET jump
tables rechecked. Native common
getter 46B has four real unmasked
GPR operand bytes wrong 10/12/16/19.
[F851 real actor original PE proof](SCRIPTED_FIGHTER_GROUND_188_F851.md);
scripts/repo-python scripts/verify-scripted-fighter-ground-188-f851.py.
Full original 46,755B NONEXACT.

**F852 original 0x189 x87 bounce state in same growing fighter:**
real original 00526FCA is **381 complete
native inner B/107 x86/11 actual physical
typed PE call/global fields**. Source uses
genuine original FUCOMPP global-vs-member
equality, x87 float POS48+POS54<ground,
actual 00657478 velocity multiplier,
auxiliary state7 and native stage3
POS15/velocity8.5/drag0.85. One new
whole VC7.1 source now **24,562 callable
B/6,759-x86**, from F851 24,196/
6,654. All 107 native opcode widths,
instruction positions and eleven real
physical PE target fields match, BUT
**68 genuine original non-PE GPR bytes**
and two entire giant epilogue relative
JMP operand bytes +377/+378 still
differ. Seven real source expressions
were independently compiled; not
all math-equivalent float spellings
preserve original x87 branch machine
code. Previous native 136/186/187/188
GPR negatives and 20 earlier complete
PE-backed cases, all FIVE packed 901B
afterRET tables rechecked. The common
46B getter again **34/34 actual original
nonrelocation bytes** plus three PE
calls. Whole 46,755B NONEXACT, no
standalone-case exact credit.
[F852 selected original PE proof](SCRIPTED_FIGHTER_BOUNCE_189_F852.md);
scripts/repo-python scripts/verify-scripted-fighter-bounce-189-f852.py.

**F853 real fighter 18A original float Y lvalue/PE widths:**
selected original 18A complete **250 native inner
B/71 x86/six physically typed PE fields**.
Original float Y must FLD this+0x48 first,
then FADD float global0065929C; source
bare POS48+global reversed 3B/6B x87
widths, real lvalue (*(&POS48))+global
restores native width/order. One selected
full VC7.1 parent now **24,797 callable
CODE B/6,828 x86** from F852
24,562/6,759. All x86 source widths
and six genuine original PE targets match,
BUT **45 native GPR byte operands**
and two true enclosing-giant final
JMP operand bytes +246/+247 remain
honestly WRONG. Prior 136/186-189
GPR negatives, 20 earlier complete
original source cases, five packed
901B afterRET jump tables checked.
Current common getter 46B has four
actual nonfield GPR byte negatives.
[F853 original Y-lvalue PE proof](SCRIPTED_FIGHTER_FLOATSHOT_18A_F853.md);
scripts/repo-python scripts/verify-scripted-fighter-floatshot-18a-f853.py.
Whole original 46,755B fighter remains NONEXACT.

**F855 actual original 18B native short-counter and float volley:**
selected game action 00527241 is **353 complete
native inner B/99 x86/seven true physical
PE call/global fields**. Stage7 genuine
short++ auxiliary state6, stage6 float
sprite0x328 signed-facing*128 SHL/FILD
and lvalue Y this+0x48 then
FADD original global00658400
are natural C++. New entire affected
VC7.1 fighter source **25,135 callable
B/6,925 x86**, up from F853
24,797/6,828. ALL original case
opcode/width and native PE fields
match but **71 honest GPR machine
operand bytes**, including native
AX versus source DX short increment
and native EAX vs source EDX SHL,
plus two real enclosing original
whole-fighter final JMP operand
bytes +349/+350 remain WRONG.
All six preceding GPR-negative
136/186..18A complete native
cases and 20 earlier source-backed
original cases and all five 901B
packed jump DATA tables rechecked.
Default getter 46B has four honest
non-PE GPR byte negatives.
[F855 selected native PE proof](SCRIPTED_FIGHTER_VOLLEY_18B_F855.md);
scripts/repo-python scripts/verify-scripted-fighter-volley-18b-f855.py.
Whole 46,755B giant STILL NONEXACT.

**F856 original fighter 0x190 stage3 sprite/animation sources:**
the genuine original 005273A2 handler is
**217 complete original inner B/64 x86/
6 actual physical native PE CALL fields**.
At stage3 source sets +0x314 float1,
emits original sprite0x320 at 00453A70,
STARTS native animation0xFA via
0046D000 THEN prepares action0 via
00453D40. Source with those calls
reversed retains similar CODE geometry
but has WRONG original PE destinations
and is rejected. At stage4 source sets
+0x7C=1. New one-parent VC7.1 whole
source **25,337 callable CODE B/
6,987 x86** versus F855 25,135/
6,925. All 64 native opcode/widths
and 6 physical PE calls align, BUT
39 authentic GPR operand bytes and
2 original encompassing giant final
JMP operand bytes +213/+214 still
differ. All 27 preceding original
PE-backed C8..18B whole source cases
and all FIVE 901B packed native
afterRET jump tables reverified.
Original 46B common getter now
34/34 native nonrelocation bytes
plus three true PE calls naturally
from whole C++ compiler context.
[F856 actor-specific PE proof](SCRIPTED_FIGHTER_STAGE_190_F856.md);
scripts/repo-python scripts/verify-scripted-fighter-stage-190-f856.py.
Whole 46,755B original remains
NONEXACT; no exact CODE adoption.

**F857 selected original 191 native float projectile case:**
original 0052747B is **166 native
complete inner B/53 x86/five
true typed PE call/global fields**.
Stage5 genuine sprite321 with
signed facing*100 FILD then
FADD X+0x44, and Y FLD
member+0x48 before native
FADD float global00659298,
followed by real Prepare0
and action0 source. One
whole new normal VC7.1
parent **25,488 callable CODE
B/7,038 x86** (F856
25,337/6,987). All native
original opcode/width and
five physical PE fields match,
BUT **29 real source GPR bytes**
plus two full-giant final
JMP operand bytes +162/+163
remain different. Eight
preceding genuine 136/186..190
GPR-negative complete cases
and twenty earlier original
source cases and ALL FIVE
native 901B packed tables
rechecked. Original 46B
shared getter stays **34/34
native nonrelocation bytes**
plus three authentic PE
calls. Whole 46,755B
original NONEXACT, zero
new whole-callable credit.
[F857 original PE evidence](SCRIPTED_FIGHTER_FLOATSHOT_191_F857.md);
scripts/repo-python scripts/verify-scripted-fighter-floatshot-191-f857.py.

**F858 selected 192 actor-native state4 sprite and genuine different sibling values:**
original 00527521 complete **217 game interior
B/64 x86/six physical PE REL32 calls**.
Unlike native190, current192 transitions
**state2**, emits sprite320 at **stage4**,
writes +0x314 float **3.0f**, prepares
animationFA then action0, sets +0x7C
at **stage5**. Fresh normal VC7.1
whole C++ parent **25,690 callable
CODE B/7,100 x86** (F857 25,488/
7,038), matching all original source
opcode/width and six native PE calls,
BUT 39 genuine GPR operand bytes and
two full-giant final JMP operands
+213/+214 remain different. Nine
previous GPR-affected and twenty
earlier source-backed original cases
and five native 901B packed tables
rechecked. Current 46B default
has four real GPR byte negatives.
[F858 selected native source](SCRIPTED_FIGHTER_STAGE_192_F858.md);
scripts/repo-python scripts/verify-scripted-fighter-stage-192-f858.py.
The original 46,755B giant stays
NONEXACT, no independent case credit.

**F859 selected native fighter 0x194 ground case fixes historical sibling assumption:**
actual original 005275FA..00527722 is **297 full
native inner CODE B/86 x86/7 PE fields**.
Copying 0x192 ResetAt453E20 into 194
was WRONG and emitted 298B/88 x86/
8 refs; original 194 stage zero does
NOT reset. Authentic C++ instead has
POS54-POS5C, x87 inclusive ground
landing action0xA plus actual
POS48/POS5C/POS54 stores, action9,
stage5 float2.0 at +0x314 with
sprite320/animationFA/prep0,
then stage6 +0x7C=1. Selected
full VC7.1 parent **25,972
callable CODE B/7,184 x86**
(up from F858 25,690/7,100).
All 86 native mnemonics/widths
and seven true PE fields agree.
**55 genuine GPR operand bytes**
plus four complete giant epilogue
JMP operand bytes remain DIFFERENT,
not accepted exact. All 30 earlier
complete native PE-backed source
cases and five 901B afterRET
packed jump DATA tables rechecked.
Common getter current 4 true
nonfield GPR byte negatives.
[F859 real original PE proof](SCRIPTED_FIGHTER_GROUND_194_F859.md);
scripts/repo-python scripts/verify-scripted-fighter-ground-194-f859.py.
Whole original 46,755B NONEXACT.

**F860 selected native 196 full float shot and original CALL order:**
physical 00527723..005277E9 case 196 is
**199 original inner CODE B/60 x86/
seven actual typed PE call/global fields**.
At real stage3 the actor PREPARES 3
through 00453D40, THEN launches
sprite353 via native 00453A70 with
signed facing*100 FILD/FADD X+44
and member Y+48 FLD then FADD
global006581DC, FINALLY starts
animationC8 through 0046D000.
Full normal VC7.1 parent now
**26,156 callable CODE B/7,242
x86** (F859 25,972/7,184).
All original 196 x86 opcode/width
and seven PE field destinations
match, but **31 honest GPR bytes**
plus two real original enclosing
giant final JMP bytes +195/+196
remain WRONG. Earlier 31
PE-backed source game cases,
all five original 901B afterRET
packed tables and current 46B
common getter four honest GPR
byte negatives rechecked.
[F860 selected native physical proof](SCRIPTED_FIGHTER_STAGE_196_F860.md);
scripts/repo-python scripts/verify-scripted-fighter-stage-196-f860.py.
Whole original 46,755B giant NONEXACT.

**F861 actual selected 0x198 physical case in original giant:**
CORRECTION: native 5277EA..527BBD
980B is FIVE separately addressed
switch cases 198/19A/19C/19E/1A0,
NOT one 980B action. Actual
0x198 is **199 entire native inner
B/60 x86/seven true PE fields**,
stage4 state2 Prepare3 then
sprite351 signed facing*90,
Y global00659460 then native
animationC8. One full normal
VC7.1 fighter now **26,340
callable CODE B/7,300 x86**,
from F860 26,156/7,242.
All native original opcode/width
and seven PE call/global targets
match, with 31 honest original
GPR bytes plus two entire-fighter
final JMP operand bytes +195/196
DIFFERENT. Twelve preceding
GPR-phase cases, twenty earlier
source-backed native game cases,
all five 901B packed DATA tables
and common 46B getter again
**34/34 original nonrelocation
bytes +3 real PE calls** checked.
[F861 target physical proof](SCRIPTED_FIGHTER_STAGE_198_F861.md);
scripts/repo-python scripts/verify-scripted-fighter-stage-198-f861.py.
Original 46,755B remains NONEXACT.

**F862 actual native 19A full 302B plus rejected false register-prefix exactness:**
selected original 005278B1 is **302 complete
native inner B/86 x86/eight true physical
PE fields**, starts directly with
POS54-POS5C drag, original ground
action0xA, stage5 sprite352
facing*60 and Y global00658268,
then animationC8, Prepare3,
POS=-5/velocity12/drag0.65,
stage6 +0x7C=1. Normal whole
VC7.1 parent **26,627 callable
B/7,384 x86**. All original
mnemonics/widths/PE fields match,
but **51 true GPR operand bytes
plus four enclosing-giant JMP
operand bytes remain wrong**.
CRITICAL false positive: adding a
NONNATIVE stage0 Reset creates
**332B/96 x86/9 original-shaped
COFF fields**, but its LAST
302B/86 x86 deceptively matches
native GPRs except original giant
JMP. The verifier physically
rejects that complete-source extent
and one extra native call;
never crop an inner case.
Previous 33 whole native-backed
game cases and five original 901B
packed afterRET tables rechecked,
getter 46B four true GPR
negatives retained.
[F862 full physical false-positive proof](SCRIPTED_FIGHTER_STAGE_19A_F862.md);
scripts/repo-python scripts/verify-scripted-fighter-stage-19a-f862.py.
Original 46,755B giant still NONEXACT.

**F863 two authentic separate 0x19C/0x19E native states inside big fighter:**
original game cases physical
005279DF and 00527A59 each
**122 entire inner B/35 x86/three
real PE calls**, stage0 setup
and true Reset, getter/action0
plus stage4 state +0x7C=1.
One fresh entire VC7.1 fighter
**26,841 callable CODE B/7,450
x86** (F862 26,627/7,384).
All native 35 mnemonic/width
and three actual PE call
field positions/targets match
in EACH state; **22 genuine
GPR bytes plus two full-game
epilogue long JMP bytes**
+118/+119 per case remain
NONEXACT. Previous 34
physical original source-backed
whole cases, common 46B getter
**34/34 nonrelocation bytes**
plus three native PE calls,
and all FIVE original 901B
afterRET packed DATA tables
rechecked. These are giant
interiors, NOT two credited
independent leaf functions.
[F863 selected original PE proof](SCRIPTED_FIGHTER_SHORT_19C_19E_F863.md);
scripts/repo-python scripts/verify-scripted-fighter-short-19c19e-f863.py.
Complete original 46,755B giant
still NONEXACT.

**F865 actual 1A0 native float +0x54 member-first operand/PE field recovery:**
real original 00527AD3 complete
**235 inner CODE B/67 x86/five
physical native PE fields**. Source
scales POS+0x50 and POS54+0x54
by real global00658348.
Bare POS54*global emits reversed
6B FLD global/3B FMUL member,
moving the second physical
native DIR32 field +70 to +67.
TRUE C++ left-lvalue
(*(&POS54))*global emits
original FLD member (3B)
and FMUL global (6B), restoring
all real PE field offsets
[52,70,94,169,193].
One new full VC7.1 parent
**27,061 callable CODE B/
7,515 x86** (F863
26,841/7,450). Every original
source opcode/width and true
PE field matches; **49 real
GPR bytes** plus two original
whole-giant JMP bytes 231/232
differ. Previous 36 original
native source-backed cases,
all five original 901B
afterRET jump tables and
46B common getter with four
honest GPR negative bytes
physically rechecked.
[F865 original x87/PE proof](SCRIPTED_FIGHTER_SUSTAIN_1A0_F865.md);
scripts/repo-python scripts/verify-scripted-fighter-sustain-1a0-f865.py.
Whole 46,755B giant NONEXACT.

**F865 completes all FIVE separately bounded original states in 980B native switch region:**
physical original 198/19A/19C/19E/1A0
are 199/302/122/122/235 inner B,
NOT one 980B case. New real 1A0
at 00527AD3 has **235 native B/
67 x86/5 genuine original PE fields**,
two actual x87 scaled speed/velocity
groups using float multiplier 00658348.
Original stage-zero MUST
include BOTH float multipliers:
native JNE ordinals3/7 target
ordinal22 AFTER the two
multiply/store groups. Earlier
alternate tracked F865 source
had put them outside and branched
to ordinal12 instead, introducing
**two genuine JNE byte errors
+10/+21** even at the same
235B/67-x86/five-PE-field extent.
Fixed and now compiled as a
negative control, never exact.
Natural real POS54 LEFT LVALUE
restores original FLD member then
FMUL global width/order; bare
POS54*global reverses the second
group's machine widths. Original
grounded POS/POS54/POS48 store
order, stage>3 drag and action9
native source integrated. One
fresh selected whole VC7.1 father
**27,061 callable CODE B/7,515 x86**
(previous F863 26,841/7,450).
All original 1A0 opcode/width
and five PE call/global targets
align, BUT **49 honest GPR operand
bytes plus two encompassing original
giant final JMP bytes +231/+232**
still DIFFER. All 5 independently
addressed cases in 980B, 36 older
native whole-case source records and
all FIVE original 901B packed
afterRET DATA tables rechecked.
Common 46B original getter has
four current GPR byte negatives.
[F865 complete physical case proof](SCRIPTED_FIGHTER_GROUND_SCALE_1A0_F865.md);
scripts/repo-python scripts/verify-scripted-fighter-ground-scale-1a0-f865.py.
Original whole 46,755B fighter
STILL NONEXACT, no inner case
or separate DATA exact credit.

**F866 current actor original 1F4 complete double-projectile and 8-bit facing:**
the native whole interior 00527BBE..
00527D7D is **448 CODE B/136 x86/
14 genuine original PE fields**.
Real stage0 reset and flag clear,
x87 height damping, landing early
auxD, TWO separately checked
stage4 branches with sprite338
then Prepare1/POS8/speed9.5/
drag0.65 and sprite7F via
00453C80, stage13 auxB
all source restored.
A fourth INT method parameter
incorrectly produces **449B**
and ordinal113 MOVSX byte->int
(4B), while a genuine fourth
CHAR-equivalent parameter emits
original MOV byte->byte (3B):
**448B/136 x86 and all 14
physical PE fields** now match
opcodes/widths/call targets.
One complete VC7.1 source parent
**27,494 callable CODE B/
7,649 x86** (F865 27,061/
7,515). Still **82 actual GPR
byte negatives** and four real
complete-giant final JMP operand
negatives +219/+220,+444/+445.
All 37 previous native PE-backed
game cases, authentic 1A0 stage0
branch scope and five original 901B
packed afterRET DATA tables
rechecked. 46B common getter
still has four true GPR negatives.
[F866 real native PE proof](SCRIPTED_FIGHTER_DOUBLE_PROJECTILE_1F4_F866.md);
scripts/repo-python scripts/verify-scripted-fighter-doubleprojectile-1f4-f866.py.
Original 46,755B giant STILL
NONEXACT, no split-case exact CODE.

**F867 true original 1F5 628B six-stage projectile case:**
actual game 00527D7E..00527FF1
**628 native inner CODE B/195 x86/
17 physically typed native PE fields**.
Original stage0 Reset and float
height drop use global006583FC
then **distinct floor global
00657480**, NOT common threshold
0065782C. Native early ground
Reset/aux18 and game return,
stage1 sprite7F with POS9.5,
stage2 sprite33B/Prepare1,
stage13 sprite338/Prepare1,
stage14 counter reset,
stage15 POS10/speed15/drag0.65
and second sprite7F, stage24
auxiliary0x16 all recovered.
Real narrow 8-bit facing on
00453C80 avoids nonnative
MOVSX. Selected full VC7.1
fighter now **28,107 callable
CODE B/7,842 x86**
(F866 27,494/7,649).
All original case opcodes/
widths and 17 physical original
PE call/global target fields
agree, but **124 genuine GPR
operand bytes** and four
entire-fighter final JMP
operand bytes 219/220 and
624/625 remain WRONG.
All 38 previous real native
case interiors, five 901B
afterRET packed DATA tables
and common 46B getter
**34/34 real original
nonrelocation bytes plus
three correct PE calls**
rechecked. Entire original
46,755B NONEXACT.
[F867 full original PE source](SCRIPTED_FIGHTER_STAGED_1F5_F867.md);
scripts/repo-python scripts/verify-scripted-fighter-staged-1f5-f867.py.

**F868 native actor original 1F6 special byte511 stage guard and mixed XY shot:**
actual 00527FF2..00528165
is **372 native inner CODE B/
111 x86/12 original physical
typed PE call/global fields**.
Native special stage>7 and
stage<11 and **unsigned
byte +0x511 == 20** branches
to action1F7, Reset and
original game effect455B30,
then real complete-parent
early return. Stage5 POS14
emits original sprite80
via 00453C80 with signed
facing*100 FILD float X
and raw integer Y+48,
plus sprite336 via 00453A70
and Prepare2 at 00453D40.
One full selected VC7.1
C++ parent **28,464 callable
CODE B/7,951 x86**
(F867 28,107/7,842).
All original opcode/width/
PE field locations and
targets match, but **64
honest native GPR byte
negatives** and four
complete-fighter final JMP
operand negatives +197/+198
and +368/+369 remain.
All 39 earlier native
game case interiors,
all five original 901B
packed afterRET tables,
and native 46B getter
**34/34 original
nonrelocation bytes plus
three correct PE calls**
physically reverified.
[F868 native game case proof](SCRIPTED_FIGHTER_CONDITIONAL_1F6_F868.md);
scripts/repo-python scripts/verify-scripted-fighter-conditional-1f6-f868.py.
Whole 46,755B original giant
still NONEXACT, zero accepted
independent case CODE.

**F869 native fighter 1F7 stage4–6 special transition and original sprite337:**
selected game 00528166..00528298 has **307 complete
native inner B/90 x86/11 physically typed PE fields**.
Original stage>3 and stage<7 and unsigned
byte+0x511==0x14 triggers action1F8, Reset
and real 00455B30 effect then whole-giant
early return; stage3 sprite337 and Prepare3
are separate game logic. New full VC7.1
source **28,756 callable CODE B/8,039 x86**
(F868 28,464/7,951); every original
opcode/width and 11 physical PE calls/globals
align. BUT 50 genuine GPR operand bytes
and four actual enclosing fighter JMP
operand bytes +197/+198 and +303/+304
remain NONEXACT. All 40 preceding whole
native-backed cases, all five original 901B
afterRET packed tables and native common
getter four GPR negatives are rechecked
in the same new parent.
[F869 original action proof](SCRIPTED_FIGHTER_CONDITIONAL_1F7_F869.md);
scripts/repo-python scripts/verify-scripted-fighter-conditional-1f7-f869.py.
The original 46,755B giant remains NONEXACT;
zero independent inner case exact CODE credit.

**F870 actual 1F8 original FUCOMPP global-first and 15 typed PE fields:**
the original 00528299..0052846D case has
**469 complete native inner CODE B/
143 x86/15 PE global/call fields**.
Important opposite x87 grammar:
native equality must **FLD global
0065782C (6B), then FLD member+48
(3B), FUCOMPP**. Bare source
POS48==global is correct HERE;
a borrowed-left-lvalue reverses
widths and shifts true PE offsets.
Ground fall global00658058 and
native early Reset/auxF, stage3
POS8/speed12/drag0.8 + raw
sprite7F, stage7 sprite335/
Prepare4, stage15 auxE all
integrated. New full VC7.1
source **29,210 callable CODE
B/8,180 x86** (F869 28,756/
8,039), all x86 source grammar
and 15 original PE locations/
kinds/real targets verified,
but **84 genuine GPR bytes**
and four real enclosing-giant
final JMP operand bytes 240/241,
465/466 remain nonexact. All
41 earlier physical native
case sources and five original
901B packed afterRET tables
rechecked. Native 46B getter
again 34/34 nonfield bytes
plus three original PE calls.
[F870 original x87 evidence](SCRIPTED_FIGHTER_NESTED_FUCOMPP_1F8_F870.md);
scripts/repo-python scripts/verify-scripted-fighter-bounce-1f8-f870.py.
Whole original 46,755B still
NONEXACT, no split-case credit.

**F872 original fighter 1F9/1FA pair: two true float stage2 volley states with real FILD scratch:**
each native original independently
**227 complete inner CODE B/65 x86/
seven physical PE fields**.
Stage2 and real +0x7C==3
launches sprite32 with facing*50
versus *36, native Y globals
006598BC versus 00659310,
owner pointer+2E8 -> short
+0x82=0x1E, action1FB
versus1FC. Actual VC7.1
compiler naturally allocates
**FILD scratch EBP-0x70
and -0x74** in the same
entire parent, no fake locals.
One new normal VC7.1 whole
**29,634 callable CODE B/
8,306 x86** (F870 29,210/
8,180). Both entire native
opcodes/widths and all 14
true original PE fields match,
BUT EACH retains **35 real
GPR operand bytes and four
giant final JMP operand bytes**
+186/+187,+223/+224.
All 42 preceding original
PE-backed source states,
all five 901B packed
afterRET jump DATA tables
and native getter **34/34
original nonrelocation bytes**
plus three PE calls verified.
[F872 real original PE evidence](SCRIPTED_FIGHTER_FLOAT_VOLLEY_PAIR_1F9_1FA_F872.md);
scripts/repo-python scripts/verify-scripted-fighter-float-volley-pair-f872.py.
Whole 46,755B original NONEXACT,
no internal case exact credit.

**F873 two original 1FB/1FC physics-first recovery game states:**
original native 00528634/00528731
are TWO distinct complete
**253 inner B/70 x86/six
physical PE fields** EACH.
True motion POS+50 height
test and global00658350
subtraction happen BEFORE
stage0 ResetAt453E20 and
counter/FLAG initialization.
Stage6 repeats owner counters
then separately sets POS15.0f.
Incorrect stage0-before-physics
source retains 253B/70x86 but
destroys actual original branch
mnemonics/widths. New one
selected whole VC7.1 parent
**30,110 callable CODE B/
8,442 x86** (F872 29,634/
8,306). Each case matches
every original opcode/width
and six true native PE offsets/
targets, but has **46 actual
GPR operand bytes** plus two
original giant-final JMP bytes
+249/+250 different. All
44 earlier original
source-backed game cases
and all five original
901B packed afterRET
jump DATA tables plus common
getter native 34/34
nonrelocation bytes+3 PE
calls rechecked.
[F873 original native CFG evidence](SCRIPTED_FIGHTER_RECOVERY_PAIR_1FB_1FC_F873.md);
scripts/repo-python scripts/verify-scripted-fighter-recovery-pair-f873.py.
Whole original 46,755B
still NONEXACT, zero
split-case exact CODE.

**F874 genuine original 1FD/1FE borrowed owner and actual CFG fix:**
original game 1FD **386B/107 x86/
nine true PE fields** and 1FE
**392B/107 x86/nine PE fields**
access real this+2E8 actor. 1FD
sets owner action66 BEFORE Reset;
1FE resets owner THEN action66.
Owner floatY equality with
global0065782C and stage<50/
>149 must have one combined
condition: native ordinal100
JLE targets **status=0 ordinal104**.
Previous nested-if source wrongly
skipped status reset for in-range
owner stage, despite same length.
This game semantic bug is fixed
and original CFG x86 targets asserted.
A new entire VC7.1 parent emits
**30,860 CODE B/8,652 x86**
(F873 30,110/8,442). Original
1FE now matches all 392 native
B/107-x86 widths and nine fields,
but **66 true GPR +4 giant
final-JMP bytes** still differ.
Original 1FD source remains
**385B vs native 386B**:
VC7.1 CMP EAX,149=5B,
native CMP ECX,149=6B at
ordinal99. All nine genuine
physical original PE fields and
real CFG are correct but **NO
original 1FD exact credit**.
All previous 46 native case
source interiors and five
901B packed DATA tables
rechecked, common getter four
authentic GPR operand negatives.
[F874 original owner PE/CFG proof](SCRIPTED_FIGHTER_BORROWED_OWNER_1FD_1FE_F874.md);
scripts/repo-python scripts/verify-scripted-fighter-owner-dual-f874.py.
Whole 46,755B original still NONEXACT.

**F875 real original 1FF stage1..6 borrowed owner and five native FILD temp slots:**
original 00528B34..00528D48
**533 complete game inner CODE B/
149 x86/nine typed real PE calls**.
Stage1..5 owner pointer+2E8
action64, facing multipliers
74/40/36/33/32, float X+44
stored into owner+44, then
stage6 owner action35.
Natural VC7.1 x87 scratch
**EBP-0x88/-0x8C/-0x90/
-0x94/-0x98** for five
FILD integer intermediates,
all original PE call targets/
offsets and x86 width/order.
New full parent **31,378
callable CODE B/8,799 x86**
(F874 30,860/8,652).
1FF still **109 native
GPR byte errors** plus two
real original giant final
JMP bytes +529/+530.
All 46 previous original
case PE sources, 1FE full
392B and 1FD still-one-byte
CMP ECX-vs-EAX negative,
five original 901B packed
afterRET DATA tables
reverified. Common getter
retains four honest GPR
operand byte differences.
[F875 native owner stage proof](SCRIPTED_FIGHTER_OWNER_STAGES_1FF_F875.md);
scripts/repo-python scripts/verify-scripted-fighter-owner-stages-1ff-f875.py.
Whole original 46,755B remains NONEXACT.

**F877 original fighter 200 six-stage owner wave and real FILD/FSUBR grammar:**
original case200 at 00528D4D
**634 native inner B/177 x86/
10 real typed PE call fields**.
Stages0..5 associate owner+2E8
action64 and update owner+44
via facing multipliers 74/
46/23/13/-6/26, with six
naturally allocated FILD
temp slots **EBP-0x9C/
-A0/-A4/-A8/-AC/-B0**.
Stage4 also physically
copies facing byte to owner+66.
At stage5 naive F32(44)-float
(facing*26) produces wrong
VC7.1 FISUB, despite same
634B/177-x86/10 PE ref counts.
True observed borrowed actor
X LEFT LVALUE produces original
FILD integer then FSUBR
member+44 (3B), exact native
x87 opcode/width grammar;
wrong version is freshly
compiled and rejected.
New complete VC7.1 parent
**31,997 callable CODE B/
8,974 x86** (F875 31,378/
8,799), all 10 native PE
targets and complete case
opcode/width positions verified.
**131 true GPR operand bytes**
plus four enclosing-giant JMP
operand bytes +95/+96,+630/+631
remain nonexact. All 49 earlier
native case sources including
1FD 1B CMP negative and
all five original packed 901B
switch DATA tables checked;
shared getter four genuine
GPR negatives retained.
[F877 original x87 and PE proof](SCRIPTED_FIGHTER_OWNER_WAVE_200_F877.md);
scripts/repo-python scripts/verify-scripted-fighter-owner-wave-200-f877.py.
Whole original 46,755B giant NONEXACT.

**F878 actual original game 201 two independent stage5 tests and native gravity-global negative:**
original 00528FC7..005290D1
is **267 complete inner CODE B/
80 x86/eight physical PE fields**.
True stage0 Reset/FLAG and
height ground global0065782C
with actual drop **00658350**;
stage5 first sprite336/Prepare2,
then independent second guard
sets POS30.0f.
One normal full VC7.1 parent
**32,249 callable CODE B/
9,052 x86** (F877 31,997/
8,974), original 201
opcode/width/PE fields all
match. Wrong but relocatable
global00657478 has SAME
267B/80x86 and nonfield bytes,
but DIFFERENT real physical
PE DIR32 destination, and is
explicitly rejected by full
negative source control.
Merging two stage5 conditions
produces nonnative full source
parent **32,226B/9,044x86**.
Selected source still **49
true GPR operand bytes and
two enclosing giant JMP
operand bytes +263/+264**
WRONG. All 50 earlier
physical original game cases,
including 1FD one-byte
CMP negative, and all five
901B packed afterRET tables
rechecked. Getter four
authentic GPR byte negatives.
[F878 original PE/false global evidence](SCRIPTED_FIGHTER_STAGE_201_F878.md);
scripts/repo-python scripts/verify-scripted-fighter-stage-201-f878.py.
Full 46,755B giant NONEXACT,
zero new accepted callable CODE.

**F879 actual native 252/253/254 original byte-decrement and false 744B aggregate equality:**
original three separate inner cases
**260/260/224 CODE B, 72/72/63x86,
six physical PE fields EACH**.
Real stage0 BYTE+0x366 decrement,
stage5 sprite37 with native float
Y global00657888 and owner+EFA
reset. Original 252/253 additionally
check +3B6/+7C and set+3B0=1000;
254 does NOT. Bare unsigned byte
assignment emits wrong MOVZX r32,
native prefix decrement produces
MOV/SUB r8, but current VC7.1 GPR
phase AL/DL/CL differs from original
DL/CL/AL. Source complete cases
**259/260/225 B**, exactly
744B total LIKE original
260+260+224, but source
PE operand fields in 252/254
are shifted -1/+1; these full
cases are NOT exact!
Only current 253 260B/72x86
has all six original PE offsets
aligned, still 47 authentic GPR
and two giant JMP byte negatives.
New whole generated source
**32,948 CODE B/9,253x86**
(F878 32,249/9,052).
Prior 51 native game cases,
all five original 901B afterRET
tables and getter four actual
GPR operand byte errors checked.
[F879 original PE proof](SCRIPTED_FIGHTER_STAGE_252_254_F879.md);
scripts/repo-python scripts/verify-scripted-fighter-stage-252-254-f879.py.
Original 46,755B giant NONEXACT,
no split-case credit.

**F880 real original native 255/256/257 action9 sprite37 states:**
three original bounded cases
**258/186/258 complete inner
CODE B, 75/55/75 native x86,
7/6/7 physical PE fields**.
True stage0 Reset/+F00=0,
getter action9, stage5
float Y sprite37 real
global657888, Prepare21.
255 and 257 also have
stage8/frame0 SHORT+F00<1,
original native MOV/ADD
r16 plus auxiliary action6;
256 has NO stage8.
Wrong 32-bit assignment
emits nonnative MOVSX and
one fewer CODE B in both
real 16-bit states.
New selected whole
VC7.1 fighter **33,605
callable CODE B/9,452 x86**
(F879 32,948/9,253).
All three opcode/width
and 20 genuine physical
original PE fields align,
but GPR/final whole giant
JMP operand bytes differ.
Previously 54 native
game case sources including
1FD CMP 1B negative and
252/254 field shifts,
all five original 901B
afterRET packed tables
and common getter four
GPR bytes rechecked.
[F880 real PE case evidence](SCRIPTED_FIGHTER_STAGE255_257_F880.md);
scripts/repo-python scripts/verify-scripted-fighter-stage255-257-f880.py.
Entire original 46,755B
fighter still NONEXACT,
zero split-case CODE credit.

**F881 actual original fighter action258 mixed float-X/raw-Y projectile:**
original 00529678..00529745
has **206 complete game inner
CODE B/60 native x86/six real
physical PE REL32 fields**.
Stage0 true Reset/state1,
stage2 native sprite340
at 00453A70 with signed
facing*80 FILD EBP-0xB4
plus float actor X, but
raw integer Y+48 and
narrow char facing argument.
Then real 0046D000(0xFA)
and Prepare5 at00453D40.
Int formal is INCORRECT:
whole native source case
207B MOVSX versus original
206B byte MOV. One full
new VC7.1 parent **33,796
callable CODE B/9,510 x86**
(F880 33,605/9,452);
all 60 opcode/width and
six original PE call fields
physically restored.
**34 real GPR plus two
whole-giant JMP byte
negatives** remain.
All preceding 57 original
game states including 1FD
1B CMP and 252/254 PE
offset shifts, five packed
901B afterRET tables and
native getter four real
GPR errors rechecked.
[F881 physical mixed-coordinate proof](SCRIPTED_FIGHTER_FLOATX_258_F881.md);
scripts/repo-python scripts/verify-scripted-fighter-floatx-258-f881.py.
Whole 46,755B giant remains
NONEXACT; no split-case CODE.

**F883 IMPORTANT corrected actual original handler259 physical boundary:**
numeric successor 25A
points to native common
DEFAULT at 0052CB25,
so numeric subtraction
incorrectly makes 259
appear **13,279B**.
The next real PHYSICAL
original handler is
**action2BC at 00529814**,
therefore actual
259 starts 00529746,
ends 00529813 and
owns only **206 native
inner B/60 x86/six
physically typed PE calls**.
This is an inner switch
interval, NOT a new
callable whole function.
Native state2 sprite34D,
real FILD EBP-0xB8 floatX/
raw integer Y, then
0046D000(0x1F4),
Prepare5 and giant
shared exit recovered.
One complete VC7.1 parent
**33,987 CODE B/9,568 x86**
(F881 33,796/9,510),
all six actual PE fields/
opcode widths match.
**34 authentic GPR bytes**
plus two original
enclosing giant JMP bytes
still nonexact. All 58
preceding source-backed
native case interiors and
five original 901B packed
afterRET jump DATA
tables verified. Native
getter retains four true
GPR byte negatives.
[F883 physical native handler boundary evidence](SCRIPTED_FIGHTER_PHYSICAL_259_F883.md);
scripts/repo-python scripts/verify-scripted-fighter-physical259-f883.py.
Entire original 46,755B
giant remains NONEXACT.

**F884 MAJOR native giant 2BC full 803B complicated staged handler:**
original physical game 2BC
00529814..00529B36 is
**803 complete native inner
CODE B/228 x86/22 physical
PE call/global fields**.
Real stage>8 **DOUBLE qword**
gravity global657D00,
stage7/9 opposite float
motion, actual once-only
SHORT F00 increment and
seven-arg sprite346 via
native 453B50, stage5
0x36C correction and
sprite73 via FILD EBP-BC
then genuine FSUBR
actor floatX, stage7/8
two FLOAT motion parameters
at 40FBB0, stage8 floatX
sprite80 FILD EBP-C0
and original animation1F4.
One newly compiled entire
VC7.1 parent **34,775
callable CODE B/9,794x86**
(F883 33,987/9,568).
All 228 original opcode/
width positions and all
22 actual PE types/targets
verified. Two independently
compiled WRONG full sources
(equal-length FISUB instead
of FSUBR, or short-counter
wrong 802B) are REJECTED.
**142 real GPR bytes and
two original whole-giant
JMP bytes +799/+800**
remain nonexact.
All 59 preceding original
native game states incl 1FD
CMP negative, 252/254 one-byte
PE shifts and corrected
259 physical boundary, all
five 901B packed afterRET
tables and getter four
honest GPR errors rechecked.
[F884 803B original PE proof](SCRIPTED_FIGHTER_NATIVE_COMPLEX_2BC_F884.md);
scripts/repo-python scripts/verify-scripted-fighter-stage2bc-f884.py.
Entire original 46,755B giant
still NONEXACT, zero
split-case CODE credit.

**F885 original 2BD complete 855B associated-owner early exit and native FILD:**
actual original 00529B37..00529E8D
is **855 inner CODE B/239 x86/
24 physical original PE fields**.
Native 2BD differs from 2BC:
one-shot first sprite346 THEN
PrepareD, action2C2/Reset,
copy borrowed owner+2E8 X to
current X and EARLY enclosing
giant return. Stage5 original
Prepare17 BEFORE float+36C
correction, sprite74 (not73),
FILD EBP-0xC4 then FSUBR.
Stage7 PrepareB, stage8
height30 and FILD EBP-0xC8
sprite80, second real enclosing
giant return. New complete
VC7.1 parent **35,615 callable
CODE B/10,031 x86** (F884
34,775B/9,794 x86). Every
original 239 mnemonic/width
and 24 genuine PE fields/
targets fully checked; still
**149 real GPR operand bytes
and four giant final JMP bytes**
+382/+383,+851/+852 wrong.
All 60 preceding original
physical native game cases,
five packed 901B afterRET
tables and 46B getter honest
GPR negatives revalidated.
[F885 original 2BD PE proof](SCRIPTED_FIGHTER_NATIVE_STAGE_2BD_F885.md);
scripts/repo-python scripts/verify-scripted-fighter-stage2bd-f885.py.
Whole original 46,755B
fighter still NONEXACT.

**F886 real original 2BE native float->SHORT helper and integer-Y sprite:**
native 00529E8E..0052A05A
**461 complete inner CODE B/
136x86/15 genuine physical
original PE call/global fields**.
State0 Reset and +80=6,
stage2 correction/floatX
sprite73 then TWO genuine
(float -> signed short)
C++ __ftol2 conversions
that resolve to original
helper **006406AC** in
both real native PE calls,
writing +F00/+F02.
Subsequent sprite33C
through 453B50 uses
RAW integer Y, unlike
earlier 2BD floating Y;
false float method formal
adds FILD/FSTP and produces
**464B/137-x86** nonnative
case, independently compiled.
Stage10 native animation1F4
and Prepare6, stage11
InitTrajectory5 and raw7F.
Current full VC7.1
source **36,061 callable
CODE B/10,165 x86**
(F885 35,615/10,031).
All original 136 instruction
opcodes/widths and 15
original physical PE fields
matched. 48 true GPR
operand bytes plus two
original giant final JMP
byte offsets +457/+458
remain nonexact.
All 61 previous actual
original game case interiors,
all five packed 901B
afterRET tables and
common getter four genuine
GPR negatives rechecked.
[F886 true original source](SCRIPTED_FIGHTER_NATIVE_STAGE_2BE_F886.md);
scripts/repo-python scripts/verify-scripted-fighter-stage2be-f886.py.
Original 46,755B giant
still NONEXACT.

**F887 native original 2BF high-quality whole-inner game source:**
original 0052A05B..0052A233
**473B/138x86/15 true PE fields**.
Stage0 writes actual short+80
**0x63 THEN 1**, stage2
sprite74 and33D, two real
__ftol2 -> original006406AC;
stage10 Prepare7, stage11
trajectory10.0f. One current
normal VC7.1 whole fighter
emits **36,519 callable
CODE B/10,301x86** (F886
36,061/10,165). 2BF has
ZERO original nonrelocation
GPR/stack wrong bytes:
ONLY **TWO enclosing giant
epilogue JMP field bytes**
+469/+470 differ, original
far tail0052CB4F. All 15
physical original PE fields
and all 138 native opcode/
width/relative positions
verified. Wrong omission
of first short80 store
produces nonnative geometry.
All 62 previous original
case interiors, five packed
901B afterRET tables and
46B getter true GPR negative
rechecked. STILL NO
independent exact credit:
whole original 46,755B
callable fighter NONEXACT.
[F887 actual original physical PE proof](SCRIPTED_FIGHTER_NATIVE_2BF_F887.md);
scripts/repo-python scripts/verify-scripted-fighter-2bf-f887.py.

**F888 corrected native 2C0/2C1 sprite345 original condition and whole getter GPR breakthrough:**
2C0 native **288B/85x86/
11 PE fields**, 2C1
**276B/81x86/11 PE fields**.
Both stage1 Prepare28/17,
2C0 Prepare8 sprite73,
2C1 Prepare9 sprite74.
Original sprite345 is
INSIDE actual current-action
matching if; previous
same-length C++ unguarded
sprite bug had wrong JNE
target +228/+204, now
corrected and separately
full-parent negative-tested.
2C0 stage>10 stores +F10
outside action condition;
2C1 stores +F10 INSIDE.
New complete normal VC7.1
source **37,053 callable
CODE B/10,463 x86**
(F887 36,519/10,301),
all native mnemonic/width,
22 actual PE field
destinations and source
case-local branches match.
ONLY enclosing-giant
final JMP +284/+285 and
+272/+273 differ.
IMPORTANT previously four
GPR wrong common getter
bytes (10/12/16/19)
now NATURALLY disappear
in expanded whole parent:
native 46B getter
**34/34 original nonfield
B** match, three native
PE call operands verified.
Previous 63 original game
cases plus five 901B
packed switch DATA tables
rechecked. STILL original
entire 46,755B parent
NONEXACT.
[F888 original PE proof](SCRIPTED_FIGHTER_NATIVE_2C0_2C1_F888.md);
scripts/repo-python scripts/verify-scripted-fighter-2c0-2c1-f888.py.

**F890 major original 2C2 FULL 2,274B native stage/multi-shot recovery:**
real original 0052A468..0052AD49
has **2,274 complete inner CODE B/
608 x86/50 physically typed PE
field operands**, and EIGHT real
F00 phases0..7 containing actual
sprite34A/329 paired shot cases,
true owner float X/Y and 13 x87
FILD scratch EBP -D4..-104. Native
stage8 one-shot is INSIDE outer
stage<9/frame0 branch, not outside:
wrong yet same-size full source
has native Jcc operand byte errors
+334/+335,+349/+350. Real owner
float X evaluated BEFORE integer
facing multiplication required.
One new complete normal VC7.1
parent **39,312 callable CODE B/
11,069 x86** (F888 37,053/
10,463) physically reproduces
all 608 original x86 opcode/
width positions, ALL FIFTY
physical PE original offsets/
types/real targets and **ONLY
FOUR genuine enclosing parent
far epilogue JMP wrong bytes**
+175/+176,+2270/+2271, with
zero other register/branch
errors. Wrong nesting and
wrong actual source operand
evaluation controls both
compiled as full normal parents
and rejected. All 65 previous
original game-state interiors,
five native 901B packed switch
DATA tables, native shared
getter 34/34 nonfield plus
3 actual PE calls verified.
[F890 2274B physical original PE proof](SCRIPTED_FIGHTER_FULL_NATIVE_2C2_F890.md);
scripts/repo-python scripts/verify-scripted-fighter-full2c2-f890.py.
Whole original 46,755B
still NONEXACT, no internal
case callable CODE credit.

**F891 original 2C3 independent game-state interior and getter phase sensitivity:**
original 0052AD4A..0052AD8E
**69 native inner CODE B/
20 x86/four real PE calls**.
True Reset, getter animation
completion and actual
dword this+4E0 zero test
chooses SetAction0 vs1.
Correct normal VC7.1
source has ZERO original
local branch/GPR wrong B,
only two enclosing giant
JMP operand bytes +65/+66.
Two whole normal source
controls invert conditional
or access wrong field+4DC:
equal 69B/20x86 but
genuinely wrong original
operand B, rejected.
New whole parent **39,366
callable CODE B/11,087x86**
(F890 39,312/11,069).
IMPORTANT expanding source
with native short case2C3
AGAIN rotates VC7.1
common getter GPR phase:
F890 getter 34/34
original nonfield B;
F891 getter **30/34**
with original four
GPR wrong bytes
+10/+12/+16/+19.
All 66 previous actual
native state interiors,
five 901B packed afterRET
tables and three getter
original PE calls verified.
[F891 original native proof](SCRIPTED_FIGHTER_NATIVE_2C3_F891.md);
scripts/repo-python scripts/verify-scripted-fighter-transition2c3-f891.py.
Whole 46,755B original
remains NONEXACT.

**F892 original game 2DB native 556B borrowed-owner distance and guarded random:**
physical 0052AD8F..0052AFBA
**556 native complete inner
CODE B/162x86/13 true PE
call/global fields**.
Stage2..9 actual distance
Abs412D90 of ownerX-
actorX with BOTH genuine
borrowed float X lvalues
evaluated in native order,
then aux10/early entire
giant return. Current
action completion guards
BOTH SetAction0 and actual
random30..60 via 455580
and short+516 store; an
unguarded source wrongly
changed actual JNE target
even with same CODE size.
Stage10 once-only shortF00,
stage15 real sprite80 floatX
FILD EBP-0x108 plus
sprite336 integer coords,
stage16 height17.5.
Current entire VC7.1
fighter **39,907 callable
CODE B/11,247x86**
(F891 39,366/11,087);
all original 162
opcode/width positions
and 13 true PE fields
physically match.
**ZERO genuine GPR/internal
Jcc wrong B**, only four
original enclosing full
giant JMP displacement B
+166/+167,+552/+553
still differ. Two false
whole source versions
(genuine x87 operand order,
wrong random conditional)
compiled/rejected. All
67 earlier original game
interiors, five 901B
packed afterRET DATA
tables and shared getter
34/34 nonfield verified.
[F892 physical original native PE proof](SCRIPTED_FIGHTER_NATIVE_STAGE_2DB_F892.md);
scripts/repo-python scripts/verify-scripted-fighter-stage2db-f892.py.
Whole original 46,755B
giant NONEXACT, no
split case CODE credit.

**F893 original 2DC real native 660B ground-contact complex stage:**
original 0052AFBB..0052B24E
**660 complete native inner
CODE B/188 x86/17 physical
PE call/global fields**.
True stage2 sprite33B
height10, stage13
sprite338, two actual
ground threshold x87
branches. Native contact
POS48+POS54 **<=**
ground0065782C calls
aux24, clears height/
speed/position, then
RETURNS through entire
giant epilogue. Getter
action0 and actual random
0..30 +516 assignment
are INSIDE match guard,
stage13 once-only shortF00
aux2, stage15 height12.5/
speed15, stage24 aux22.
One new normal VC7.1
full fighter **40,552
callable CODE B/11,433 x86**
(F892 39,907/11,247).
All original opcode/width
positions and 17 actual
physical PE destinations
match, ZERO GPR/local
branch errors, only
**four real original far
giant JMP operand bytes**
+427/+428,+656/+657
differ. Three same-size
FALSE game source controls
(strict ground<, outside
random and sprite33A)
independently compiled
and rejected by original
PE bytes. All 68 previous
actual native case sources,
five packed 901B afterRET
tables and shared getter
34/34 original nonfield
bytes rechecked.
[F893 original physical PE proof](SCRIPTED_FIGHTER_NATIVE_STAGE_2DC_F893.md);
scripts/repo-python scripts/verify-scripted-fighter-stage2dc-f893.py.
Whole original 46,755B
fighter remains NONEXACT.

**F894 original fighter 2DD PHYSICAL bound and 455580 real EAX return:**
numeric successor 2DE is
DEFAULT 0052CB25, falsely
implying **6358B 2DD**;
real next PHYSICAL native
2E4 starts 0052B466,
so actual 2DD is
**0052B24F..0052B465,
535 inner CODE B/153x86/
14 true physical PE fields**.
Stage3 actual int-return
RandomBoundary455580(0,6)
writes FULL 32-bit EAX
into native FILD temporary
**EBP-0x10C**, adds
float global006592A0
to height, uses sprite7F
and speed16; stage18
sprite335/Prepare4,
stage26 aux24. Stage>Y
contact native <= ground
with float00659090 and
aux26/whole giant exit.
Wrong borrowed SHORT return
instead emits MOVSX and
**538B/154x86** nonnative
entire inner case, verified.
New one full VC7.1 parent
**41,072 callable CODE B/
11,584x86** (F893
40,552/11,433), native
535B/153x86/14 PE fields
all correct and only FOUR
whole giant far-JMP bytes
+246/+247,+531/+532
different, zero inner GPR
or branch errors.
Previous 69 original
game-state interiors,
five packed 901B afterRET
DATA tables and shared
getter four genuine
GPR errors verified.
[F894 true original PE physical source](SCRIPTED_FIGHTER_PHYSICAL_2DD_F894.md);
scripts/repo-python scripts/verify-scripted-fighter-physical2dd-f894.py.
Original whole 46,755B
fighter still NONEXACT.

**F896 original 2E5/2E6 paired real random game states:**
each native **374 complete
CODE B/102 x86/12
real PE call/global fields**,
physical 2E5 at 52B5FF,
2E6 at 52B775.
Current action getter match
random455580(0,100) writes
F00; if dword+7C=0 sets
action0 and random(60,120)
short516 then whole exit;
otherwise real F00<30
2E5->2E6 or 2E6->2E5,
F00<60 ->2E7, else
->2E8. Stage2 (2E5)
or stage3 (2E6)
height15 sprite38E.
Current whole normal VC7.1
fighter **42,184
callable CODE B/11,896
x86** (F895 41,466/
11,696). Every native
case opcode/width and
all 24 original physical
PE fields/targets checked.
Both states ZERO true
GPR/inner Jcc wrong B,
only TEN original
enclosing father far-JMP
operand B each. Three
same-sized FALSE source
families recompiled and
rejected. All 71 previous
original native cases,
five packed 901B tables
and getter real four
GPR wrong B rechecked.
[F896 original game source PE proof](SCRIPTED_FIGHTER_PAIRED_2E5_2E6_F896.md);
scripts/repo-python scripts/verify-scripted-fighter-pair2e5-2e6-f896.py.
Entire original 46,755B
callable fighter NONEXACT.

**F895 actual original 2E4 full 409B native PE proof:**
real 0052B466..0052B5FE
**409 original inner
CODE B/114x86/11
typed physical PE fields**.
True float borrowed
ownerX-thisX Abs412D90
strict < global6591F4
chooses random455580
0..4 + action2E4
and early whole return.
Getter completion protects
random30..60 +516,
stage10 shortF00<2/aux2.
Fresh source parent F895
41,466 CODE B/11,696
x86, only 4 actual far
giant JMP byte differences,
3 whole false controls
compile/reject. New shared
scripts/verify-scripted-fighter-context-f895.py
rechecks 70+ original
cases in one current
COFF parent, 1FD and
252/254 true negatives,
901B original packed
DATA and common getter.
[F895 original 2E4 PE receipt](SCRIPTED_FIGHTER_PHYSICAL_2E4_F895.md).

**F897 original 2E7..2EA FOUR native 555B/167-x86 barrage cases:**
original physical 2E7 at
52B8EB, 2E8 at52BB16,
2E9 at52BD41, 2EA at
52BF6C; next PHYSICAL
case after 2EA is 2F0
at52C197, NOT numeric
2EB default. EACH native
**555 CODE B/167 x86/
15 real typed PE fields**,
four genuinely used FILD
EBP slots -110/-114/
-118/-11C, native stage3
facing*65 float sprite3E,
stage2 two real __ftol2
calls original6406AC
and sprite33D, stage9
sprite38B in 2E7/2E8
but sprite38C in
2E9/2EA, stage11
trajectory10/raw7F.
F897 one complete parent
**44,353 source CODE B/
12,556 x86** from F896
42,184/11,896.
2E7/2E8/2E9 full native
555B exact opcode/widths
apart from original far
giant JMP operand bytes.
**2EA current selected
source has NONNATIVE
last short 2B JMP vs
original 5B**: total
552B/167 x86, 15 PE
fields before it correct.
Do NOT mask missing three
bytes or claim exact.
Adding real original next
2F0 naturally makes 2EA
five-byte JMP; requires
separate actual verification.
All 73 previous native
case sources and 901B
packed DATA tables,
getter true PE refs
rechecked. Original
46755B fighter still
NONEXACT, no internal
case exact acceptance.
[F897 native PE proof](SCRIPTED_FIGHTER_FOUR_2E7_2EA_F897.md);
scripts/repo-python scripts/verify-scripted-fighter-four2e7-2ea-f897.py.

**F898 real original 2F0 full 828B staged float/double movement:**
native 0052C197..0052C4D2
**828 inner CODE B/
229x86/19 actual
physical typed PE
call/global fields**.
Stage<6 short F02 ++
and native facing*40
FILD EBP-0x120
sprite3E, stage>10
original DOUBLE qword
gravity657D00,
stage7/9 float motion
at +1C/+20, stage8
native sprite38D,
CloudOpponent signed
byte*30+240, real
float,float,int motion
and sprite80 signed
facing*150 FILD
EBP-0x124, stage7
negative motion and
four byte flags.
One complete normal
VC7.1 father **45,169
callable CODE B/12,783
x86** (F897 44,353/
12,556). Source 2F0
still only **825B**:
original last 5B far
JMP relaxed to 2B
short in this context,
three missing native
bytes NEVER credited.
All 19 original PE
fields and 228 earlier
x86 opcode/width pairs
match. Adding native
2F0 naturally RESTORES
previous final 2EA
from F897 nonnative
552B short-JMP to
original full **555B**,
so ALL four 2E7..2EA
now 555B/167x86
each with only original
far giant JMP operand
negatives. Two false
full C++ controls compile
and reject wrong source
facing multiplier/sprite.
73 previous original
state interiors, five
packed 901B DATA tables
and native getter PE
phase rechecked.
[F898 physical original game evidence](SCRIPTED_FIGHTER_NATIVE_2F0_F898.md);
scripts/repo-python scripts/verify-scripted-fighter-stage2f0-f898.py.
Full original 46,755B
fighter still NONEXACT.

**F899 actual original 2F8 complete handler geometry:**
original 0052C4D3
**1,151 native CODE B /
316 x86/28 real typed
PE fields**. Current whole
VC7.1 source **46,308
callable CODE B/13,097
x86**; all native PE
fields, opcodes and first
315 instruction widths
restored. Last source
JMP still short 2B vs
native 5B: source
1,148B, three absent
original bytes NOT masked
or credited. Actual
intermediate x87 stack
slots -128/-12C/-130/
-134/-138 confirmed.
Adding true 2F8 naturally
restores preceding 2F0
to original **828B/
229x86/19 fields**.
Two same-size false
source controls compiled
and rejected; previous
78 original native game
case interiors, five
packed 901B afterRET
DATA tables and common
getter 34/34 nonfield
rechecked. Whole original
46,755B giant NONEXACT.
[F899 original physical evidence](SCRIPTED_FIGHTER_NATIVE_2F8_F899.md);
scripts/repo-python scripts/verify-scripted-fighter-stage2f8-f899.py.

The other **20 large original state-advance functions** also remain
unmatched, including the 82,796-B `004AC040`, 81,539-B `0050A580`
and 60,999-B `0045DD70`. Their complete original extents and origin
classification are in `config/functions.csv` and
`config/function-origins.csv`. Preserve real native per-case source
research without calling it accepted whole CODE. [Giant dispatch
map](../config/fighter-boss-dispatch-fingerprints.json) is a
physical-data lead, not provenance proof.

## 3. All 3 additional nonexact original small/medium functions

These are **authored by `function-origins.csv`** but not canonically
matched (most have blank provisional `functions.csv` owner). This is
the complete **3,406-B** non-giant backlog, NOT just the three
frequently researched ownership functions:

| Native original entire function | CODE | Next evidence/source lead |
| --- | ---: | --- |
| `0x0041CE50` ArchiveCatalog destructor | 171 B | Best native 108/115 nonfield bytes, still seven genuine owner/CFG differences; [F697/F698 negatives](ARCHIVE_AGGREGATE_AND_REFERENCE_NEGATIVES_F697_F698.md) |
| `0x0043B0B0` Scene destructor | 248 B | Best 191/200 native nonfield bytes; used texture owner/stack layout unresolved; [F700](SCENE_TEXTURE_OWNER_LIFETIMES_F700.md) |
| `0x00602A60` WinMain | 2,987 B | Original saved local scene/path frame differs; [F702–F704](WINMAIN_USED_OBJECT_CONTEXT_NEGATIVES_F702_F704.md) |

**F795 original complete WinMain 00602A60 native stack-owner result:**
independently decoded **four adjacent real native live
objects**: graphics client `EBP−0x189`, created
window HWND `EBP−0x188`, current scene pointer
`EBP−0x184`, 260-B module path `EBP−0x180`.
The original 2,987-B/654-x86 startup/15-scene TABLE
is rechecked. Twenty-six normal VC7.1 *whole*
WinMain variants place actual used HWND, ready HANDLE,
MSG, WNDCLASS, directory-end and metrics into
different meaningful scene/path groups.
Best still `3,002` B (619 original instruction
widths) and scene/path `−0x180/−0x17C`;
a superficially closer 2,993-B source has only
590/654 original widths and badly misplaced scene.
**No full WinMain exact CODE or source class
layout claimed.** [F795 physical PE/source evidence](WINMAIN_PHYSICAL_WINDOW_CONTEXT_F795.md);
`scripts/repo-python scripts/verify-winmain-native-used-group-f795.py`.

**F798 original ArchiveCatalog 171B native teardown stack recovery:**
nine whole source builds with *actually used* loop
index/filename and resource/delete receiver
groupings. Two-field used contexts remain 171B/51
x86 with 102 or 108 of 115 native nonfield B
and all **14 authentic PE/COFF field destinations**
but wrong live EBP lifetimes. A genuine four-member
`filename/resource/deleteReceiver/index` context
restores exactly the original **-0x10/-0x0C/-0x08/-0x04**
semantic stack slots, an important compiler allocator
lead, yet it generates **four extra MOV instructions**,
**183B/55 x86 instead of native 171B/51 x86**, and
the frame/saved `this` are wrong. Direct/inline
delete assignment source grammar both negative.
**Not exact**, no truncated/cropped credit.
[F798 original whole-function evidence](ARCHIVE_NATIVE_LOOP_TEARDOWN_F798.md);
`scripts/repo-python scripts/verify-archive-loop-teardown-f798.py`.

**F809 new physical lifetime constraint for authored Scene 0043B0B0:**
nine fresh **whole 248-B virtual/EH destructor**
compiles check the real two texture-delete temporary
slots and three CRT-free argument slots. The genuine
three-pointer aggregate/array remains **191/200**
original nonfield bytes and preserves all 12 original
physical PE refs but reverses the stack ownership.
Replacing each saved CRT-free argument by direct
`free(this+field)` naturally **recovers the exact
native texture/delete `EBP-0x14/-0x10` slots**
but generates **230 B/69 x86**, omitting precisely
six real native stored/free-parameter instructions
(18 B). Separately named/volatile/union locals
restore **248 B/75 x86** but regress to
**189/200** original nonfield bytes.
An aligned real aggregate produces a non-native
271-B stack-aligned EH prologue. None is
whole-function exact; do not mask moved
PE fields in the wrong-size controls.
[F809 complete Scene original/VC7 lifetime proof](SCENE_NATIVE_FREE_TEMP_LIFETIMES_F809.md);
`scripts/repo-python scripts/verify-scene-release-lifetimes-f809.py`.

**F818 novel Scene 0043B0B0 typed resource-owner review:**
seven selected complete pinned VC7.1 authored
Scene destructor builds verify the real texture
+0x08 and free pointers +0x4C/+0x50/+0x54
through one OBSERVED-only borrowed typed
view, NEVER instantiating it as the original
unknown historical class. Inline texture-only,
free-only and combined typed views produce
byte-identical **complete 248B/75-x86
COFF functions** and all 12 identical
real original PE relocation records,
still **191/200 original nonfield
bytes** (nine actual stack slots wrong).
An actually used local borrowed pointer
or reference instead produces a
**254B/77-x86** nonnative destructor
and moves the saved-this frame to EBP-0x28.
Typed object access itself does not recover
the native five-slot lifetime; no early
whole-function exact claim or relocs masked.
[F818 entire Scene physical source](SCENE_COMPLETE_BORROWED_OWNER_F818.md);
scripts/repo-python scripts/verify-scene-borrowed-owner-f818.py.

The R011 ordinary-quad `0040C9A0` is now **115-B/37-x86/4-PE-field
whole cold exact** ([F780](SPRITE_ORDINARY_QUAD_NATIVE_F780.md)).
Two original calls prime/capture a texture pointer and real VC7 vector
size at stack `EBP−8`/`EBP−4`; the 132-B quad at `EBP−0x8C`
is copied before the final textured draw. The native 140-B grouped
scratch view matches the complete original 115 CODE bytes with all
four true physical REL32 fields; original historical C++ class layout
is not claimed. No double credit for the VC7 STL size() helper.
The R011 projected-quad `0040CA20` is now **92-B/34-x86/2-PE-field
whole cold exact** ([F779](SPRITE_PROJECTED_QUAD_NATIVE_F779.md)).
The observed 132-B quad needs explicit 4-B alignment, yielding real
`EBP−0x84` copy and `EBP−0x88` saved owner, with no invented frame padding.
It is no longer pending.
The R011 SpriteDrawing mode variant `0040CEF0` is now **994-B/269-x86/15-field whole cold exact**,
with original base-delegation and true rotated/unrotated `JP` branch
([F776](SPRITE_VARIANT_NATIVE_F776.md)); no longer pending.
The R011 scaled/rotated sprite `0040D2E0` is now **970-B/257-x86/14-field whole cold exact**,
with actual 132-B quad/RECT lifetimes and native x87 evaluation order
([F775](SPRITE_SCALED_NATIVE_F775.md)). It is no longer pending.
The R011 mirrored SpriteDrawing `0040D6B0` is now **212-B/66-x86/6-field complete cold exact**
with 188/188 authentic nonfield bytes and real mirrored RECT branch
([F766](SPRITE_OPAQUE_MIRRORED_F766.md)); no longer pending.
The R017 shared-texture allocator `0040B000` is **261-B/79-x86/11-PE-field whole cold exact**,
with original vector zero and loop index lexical lifetimes
([F770](TEXTURE_MANAGER_SHARED_NATIVE_F770.md)). It is no longer pending.
The R017 texture slot allocator `0040B110` is now **184-B/56-x86/8-PE-field cold exact**,
with genuine 44-B native VC7 used element lifetime
([F769](TEXTURE_MANAGER_SLOTS_NATIVE_F769.md)). It is no longer pending.
The R011 SpriteDrawing opaque draw `0040D790` is now **171-B/52-x86/6-field whole cold exact**,
with 147/147 authentic nonfield bytes and real native RECT lifetimes
([F765](SPRITE_OPAQUE_NATIVE_F765.md)); no longer in the pending queue.
The R016 audio archive-entry queue `00407B80` is now **283-B/76-x86/27-COFF cold exact**
([F760](AUDIO_QUEUE_ARCHIVE_ENTRY_F760.md)), with original valid-handle
conditional 64-byte record lifetime. It is no longer on the pending queue.
The R016 audio file-queue `00407A50` is now **289-B/77-x86/26-reloc cold exact**
([F758](AUDIO_QUEUE_FILE_F758.md)); its recovered 64-B native record
corrects the previously guessed 68-B lifetime and is no longer pending.
The paired R015 audio-client destructor `00407270` is now **292-B/82-x86/24-reloc cold exact**
([F755](AUDIO_STREAM_CLIENT_RELEASE_F755.md)); it is no longer pending.
Latest accepted R015 audio-client constructor `004071C0` is already
**161 B cold-exact** ([F753](AUDIO_STREAM_CLIENT_ACQUIRE_F753.md));
do not relist it as pending. Do not recredit its native STL/CRT/OS
callee code. Similarly the previous F750 CharacterAux 101-B
nested collection wrapper is already accepted exact.

**F789 source-origin counterexample:** two separately explicit
user-defined normal C++ copy methods also reproduce *exactly*
the original 417B/128-x86 + 368B/118-x86 full machine code
and **all 8 authentic PE/COFF fields**. F787/F788's
compiler-implicit implementations independently reproduce the
same whole source geometry. This **proves provenance ambiguity
from byte evidence**; neither original candidate should be
prematurely reclassified as authored or excluded.
[Independent full explicit-source comparison](COMPOSITE_COPY_PROVENANCE_AMBIGUITY_F789.md);
`scripts/repo-python scripts/verify-composite-source-ambiguity-f789.py`.

**F788 whole original 417B implicit composite copy constructor
with genuine EH:** source probe `CompositeImplicitAssignmentF787.cpp`
also reproduces independently reviewed unknown-origin
`004591E0` **417/417 CODE B**, **128 original x86**,
393/393 nonrelocation bytes and **all six** PE fields
(including native `00656273` handler and two true
`00459390` library-owned nested constructor calls).
The actual first 16B header's **nontrivial destructor** creates
native EH state 0 at source +38h; first nested construction
sets byte-sized state 1 at +171h. It simultaneously preserves
F787's entire 368-B assignment match. Both remain
**provenance unknown**, no formal authored CODE credit.
[Complete F788 native constructor/EH proof](COMPOSITE_IMPLICIT_CONSTRUCTOR_F788.md);
`scripts/repo-python scripts/verify-composite-implicit-constructor-f788.py`.

**F787 original unknown-origin composite assignment source recovery:**
original `0045AAE0` /368 CODE B /118 native x86 has an entire
VC7.1 compiler-implicit C++ assignment source with all 360/360
nonrelocation CODE bytes and both real `0045AC50` nested
sequence calls at true offsets `151/163`; actual COFF section
extent is independently checked (not cropped).
The natural provisional 116B composite has genuinely observed
16B POD blocks at `+0x00/+0x44` and nested values at
`+0x54/+0x64`. **Provenance stays UNKNOWN**: equivalent
codegen from an explicit historical assignment remains possible.
Not accepted or credited to authored bytes.
[Full F787 physical evidence](COMPOSITE_IMPLICIT_ASSIGNMENT_F787.md);
`scripts/repo-python scripts/verify-composite-implicit-assignment-f787.py`.

**F791 reviewed entire authored Archive and Scene teardown owners:**
selected real 3-member and 2-member resource/filename grouped
locals for `0041CE50` (original 171B/51 x86) still emit
**183B/55 x86 or 177B/53 x86** under VC7.1.
Real used freed-pointer aggregate field order and lexical
timing for `0043B0B0` (original 248B/75 x86) preserve
all **12** genuine original physical PE/COFF refs but
match only **191/200** nonfield bytes best (some
permutations 189/200). Original resource/delete/filename
and texture/free stack slots have been independently decoded,
not normalized away. Ten newly reproduced *whole* targeted
C++ controls are nonexact; no authored credit.
[F791 original native teardown owner controls](ARCHIVE_SCENE_RESOURCE_OWNER_LIFETIMES_F791.md);
`scripts/repo-python scripts/verify-resource-teardown-ownership-f791.py`.

**F799 new *complete* source matching but origin-unknown leaf CODE:**
original `004135F0` writes exactly three real observed values at
`this+0x24/+0x1C/+0x20`, **40 original CODE B/16 x86**;
original `00454F70` follows a borrowed pointer `this+0x74` to
mask `+0x3C`, returning boolean bit `0x20` by native
`XOR/CMP/SBB/NEG`, **31 CODE B/15 x86**. Natural
VC7.1 C++ precisely reproduces **71/71 complete unrelocated native
CODE bytes**, zero original relocations. A semantically
equivalent `!=0` getter emits 29B/14 x86 and is rejected.
Both original `function-origins.csv` entries remain
**unknown/review**, so no formal authored exact credit.
[F799 original whole-leaf source proof](UNKNOWN_OWNER_FIELD_LEAVES_F799.md);
`scripts/repo-python scripts/verify-unknown-owner-field-leaves-f799.py`.

**F805 complete 24-B previously unknown native source match:**
original `00454C00` has 9 complete x86,
zero original PE/COFF fields and a real
`MOV DWORD PTR [this+0x47C],0` followed
by plain thiscall `RET`. Natural VC7.1 C++
`probes/UnknownNativeDwordResetF805.cpp`
emits **24/24 target CODE B**; independent
int/unsigned/float zero stores are codegen-identical,
while a short/byte store produces 23/21 B.
The original class/field nominal type and
historical authored-vs-library ownership remain
**unknown/review**, so no authored exact credit.
[F805 complete native PE evidence](UNKNOWN_DWORD_RESET_NATIVE_F805.md);
`scripts/repo-python scripts/verify-unknown-native-dword-reset-f805.py`.

**F818 Scene actual borrowed owner-fields original PE negative proof:**
seven whole original 0043B0B0 normal VC7.1 destructor builds
check typed texture +8 and three genuine CRT-free pointers
+0x4C/+0x50/+0x54. Direct typed views produce identical
248-B/75-x86/12-PE-field source COFF to raw accesses
and still 191/200 original nonfield B, with nine actual
EBP stack differences. A named *used* reference/pointer
produces nonnative 254 B/77 x86 and deeper saved this.
No original historical owner invented or accepted CODE.
[F818 native Scene whole-source result](SCENE_BORROWED_OWNER_FIELDS_F818.md);
scripts/repo-python scripts/verify-scene-borrowed-owner-f818.py.

**F828 complete Archive destructor register/volatile/const local controls:**
15 full original 0041CE50 **171B/51 x86/14 real PE
field** source compiles test actually used index and
filename storage qualifiers, genuine equivalent 32-bit
type and unsigned loop expression grammar. Thirteen
variants produce identical whole VC7.1 CODE/COFF
to baseline, still **108/115 native nonfield B**:
real resource pointer EBP-0xC, scalar-delete
receiver EBP-8, filename EBP-0x10 remain
misallocated as source -0x10/-0xC/-8.
Two reversed unsigned comparison variants
worsen to **106/115** despite same full
length and real PE field targets. Modern
__restrict is unsupported in pinned MSVC7.1
(C4235). No source fake layout/ABI, no
authored whole exact credit.
[F828 real PE/source result](ARCHIVE_USED_STORAGE_CLASS_F828.md);
scripts/repo-python scripts/verify-archive-storage-class-f828.py.

**F835 new complete ArchiveCatalog native lexical-scope negative:**
15 whole original 0041CE50 /Od /GX- builds test real
delete/free nested scopes and filename lifetime.
Thirteen original-sized 171B/51-x86 C++ variants
produce bit-identical whole CODE and 14 source
PE/COFF fields, but still only **108/115 real
native nonrelocation bytes**. Declaring the used
filename before the loop worsens to **102/115**,
while an actually used filename const-reference
emits **179B/54 x86**, not original geometry.
All 14 true PE fields/targets checked in each
size-correct source. No fake slots or formally
accepted authored exact CODE.
[F835 complete original PE evidence](ARCHIVE_LEXICAL_SCOPES_F835.md);
scripts/repo-python scripts/verify-archive-lexical-scopes-f835.py.

**F838 original Scene 248B destructor whole-owner declaration negative:**
eight genuine original 75-x86/12-PE-field
VC7.1 /GX destructor variants test
placing the actual three freed-pointer
aggregate BEFORE clock/texture/deletion
and meaningful resource member orders.
All eight compile as original full
**248B/75 x86**, all 12 real original
PE targets physically verified. Five
real declaration positions reproduce
same CODE and **191/200 original
nonfield byte matches**; three member
field order permutations worsen to
**189/200**. None restores original
texture EBP-0x14/deleting receiver
EBP-0x10 and three deeper CRT-free
slots together. No fabricated locals
or accepted whole authored CODE.
[F838 whole physical Scene proof](SCENE_RELEASE_DECLARATION_F838.md);
scripts/repo-python scripts/verify-scene-release-declaration-f838.py.

**F848 original Scene full 248B genuine owner-access controls:**
ten complete /Od /Ob0 /GX native-shaped
Scene destructors test actual three released
pointer values via normal vs volatile/register
aggregate, borrowed pointer-to-member,
and __forceinline setters/getters.
Five original-size **248B/75 x86/12 real
physical PE field** source variants still
match only **191/200** genuine nonrelocation
bytes (native texture/delete temp slots
EBP-0x14/-0x10 not reproduced).
Actual inline getters/setters under /Ob0
instead produce **253/254/263/266/281 B**
and extra COFF calls: physically wrong
whole original function lengths. No fake
padding, source cropping or accepted exact
authored whole CODE.
[F848 native Scene PE/source proof](SCENE_REAL_RESOURCE_MEMBER_ACCESS_F848.md);
scripts/repo-python scripts/verify-scene-actual-access-f848.py.

**F854 complete original 171B Archive delete/resource owner categories:**
sixteen freshly compiled whole /Od /GX-
resource delete C++ value categories
test actual owned pointer, const/volatile/
register pointer, true pointer-reference
alias, pointer-to-pointer entry, and
delete cast expression. Four variants
emit **byte-identical complete 171B/
51 x86/14 real original PE fields**;
each remains **108/115 native original
nonrelocation bytes** (resource, receiver,
filename EBP slots wrong). Ten
actually named resource/reference source
variants emit **177B/53 x86**, others
183B/55 and 185B/56, nonnative
entire function extent. All sixteen
retain original resource/delete/filename
semantic call symbol identities; only
original-sized ones earn a native 14-field
physical comparison, NONE exact.
[F854 original Archive value category proof](ARCHIVE_NATIVE_RESOURCE_VALUE_CATEGORIES_F854.md);
scripts/repo-python scripts/verify-archive-real-delete-value-f854.py.

**F864 original 248B Scene destructor actual named free-pointer controls:**
twelve complete pinned VC7.1 /Od /GX
destructor source tests use real
separately named +0x4C/+0x50/+0x54
free pointers, declarations before/
after texture/clock, rotated orders,
register/volatile and branch-scoped
actual initialized locals. Ten
original-size **248B/75-x86/
12 physical PE-field** whole
sources all retain original
call targets/opcode widths,
but NINE named models worsen
native nonfield matches to
**189/200** from aggregate
baseline **191/200**.
Two true branch pointer-reference
models emit **254B/78 x86**,
not the original whole extent.
Texture/delete EBP remains
-0x20/-0x1C vs native
-0x14/-0x10. No fabricated
locals or whole exact credit.
[F864 native Scene named pointer proof](SCENE_THREE_REAL_NAMED_POINTERS_F864.md);
scripts/repo-python scripts/verify-scene-three-named-release-f864.py.

**F864 real independent Scene destructor's actual three named CRT-free locals:**
twelve complete original 248B Scene
normal VC7.1 /Od /GX source controls
test **three separate genuinely used
freed-pointer locals** (+4C/+50/+54),
declaration order/before clock/texture/
branch, register/volatile, plus actual
pointer references/member address sources.
Ten emit full **248B/75 x86/12 genuine
physical original PE fields**; original
three-field aggregate matches 191/200
nonrelocation bytes, NINE separately
named real-value C++ alternatives
worsen to **189/200**. Two real
borrowed branch aliases emit
**254B/78 x86/12 refs** and fail
the original full extent. Texture/
delete original EBP -0x14/-0x10
remain wrong, no fabricated locals,
no newly credited whole exact CODE.
[F864 original Scene physical control](SCENE_THREE_REAL_NAMED_RELEASE_F864.md);
scripts/repo-python scripts/verify-scene-three-named-release-f864.py.

**F871 independent ORIGINAL PE static xref audit of 3 fully source-matched but UNKNOWN-origin leaves:**
native 004135F0 **40B/16 x86**,
00454C00 **24B/9 x86**,
00454F70 **31B/15 x86**
all still exact normal VC7.1
complete original game machine
codegen after targeted compile.
Raw original 2,449,408-B .text
EVERY-byte E8/E9 rel32 target
scan and ALL five original PE
section byte searches for any
absolute VA pointer found
**ZERO direct E8 calls, E9 JMP
or absolute VA occurrences**
for ALL THREE. The SAME scan
finds >500 real calls each
to known original 0040FA30,
0040FAC0 and 00453E20 as
positive controls. Absence
of static xrefs does NOT
prove no computed indirect
or runtime caller, nor
historical authored origin.
All three remain mandatory
unknown/review; no formal
whole authored exact CODE
or origin adoption claimed.
[F871 pinned PE static caller evidence](UNKNOWN_LEAF_STATIC_PE_CALLER_AUDIT_F871.md);
scripts/repo-python scripts/audit-unknown-leaf-native-xrefs-f871.py.
No full cold replay.

**F876 independently authored Archive full 171B destructor, real C++ helper return-value boundaries:**
TEN full ordinary/forceinline/
template return-of-real-pointer
variants compiled with pinned
VC7.1 /Od /Ob0 /GX-.
Original **171B/51x86/14
physical native PE fields**
baseline still only **108/115**
original nonrelocation bytes.
Four genuine inline single
getter sources instead emit
**167B/50x86/13 COFF refs**:
real At() call is moved OUT
of destructor to helper; both
helpers 163B/49x86/12 refs,
template pointer wrappers
178B/53x86/15 or
185B/55x86/16 refs.
These meaningful C++ helper
sources preserve actual resource
delete, filename CRT free and
both container clear operations,
but none is the full original
native destructor call graph
or CODE extent. Zero accepted
new authored exact CODE.
[F876 whole Archive original PE audit](ARCHIVE_INLINE_RETURN_BOUNDARIES_F876.md);
scripts/repo-python scripts/verify-archive-inline-return-boundaries-f876.py.

**F882 real independent Scene 248B destructor: texture owner local vs true PE fields:**
17 new COMPLETE normal pinned
VC7.1 /Od /GX sources with
actually used texture pointer
locals, const/volatile and
references, four-field cleanup
aggregate containing original
texture and all 3 real CRT
free pointers. Original
native **248B/75 x86/
12 physical PE fields**.
Two genuine 248B/75
source variants still
**191/200 native nonfield**
with 9 real EBP byte errors.
3 early texture owner locals
generate 251B/76x86,
TEN scoped/four-field
owner sources 254B/77x86,
two references 256B/78x86.
Notably four-field actual
texture SECOND-LAST recovers
native ordinal26 texture
store **EBP-0x14**,
BUT delete receiver becomes
-0x24, 2 extra MOV, whole
254B/77x86 and last six
original PE fields shift +6:
this is NOT whole exact.
All genuine CRT free and
texture delete effects are
preserved; no fake locals
or cropped PE match.
[F882 full Scene native tradeoff](SCENE_TEXTURE_OWNER_LIFETIME_F882.md);
scripts/repo-python scripts/verify-scene-texture-ownership-f882.py.
Original Scene still NONEXACT.

**F889 independent authored small Scene destructor: 29 whole real free-parameter ownership models:**
normal VC7.1 /Od /GX
original 0043B0B0
248B/75x86/12 physical
PE fields. Twenty-eight
true *used* mixed 1+2
or 2+1 cleanup member
and named pointer ownership
C++ forms across four
declaration timings,
register and pointer
volatile variants tested.
ALL 29 full sources compile
to correct 248B/75x86/
12 physical PE field
offsets/callee targets.
But ALL mixed versions
yield only **189/200**
original nonrelocation
bytes, baseline 3-field
aggregate **191/200**.
Texture/delete temp slots
remain -20/-1C instead
of native -14/-10,
and first CRT free gets
two additional genuinely
wrong stack bytes.
Thus mixed live cleanup
ownership hypothesis is
DISPROVEN, no whole exact
Scene function or CODE.
[F889 whole small original PE experiments](SCENE_MIXED_REAL_FREE_POINTER_OWNERS_F889.md);
scripts/repo-python scripts/verify-scene-mixed-owner-slots-f889.py.

**F900 independently authored small Archive destructor 25 complete real live-owner experiments:**
original 0041CE50
**171 native complete
CODE B/51x86/14 real
original PE call fields**.
The native EBP resource,
delete receiver, filename
slots require -C/-8/-10.
Full pinned VC7.1 /Od
/GX- source trial:
25 real resource+filename
pair/triple/union/entry
and live index ownership
layouts, with real delete,
filename CRT free, both
list At/Clear preserved.
23 genuinely grouped
owner sources generate
**177B/53x86**, NOT
original whole function;
one 171B/51x86 filename
member variant matches
only 102/115 native
nonrelocation bytes,
worse than baseline
**108/115**. All preserve
14 actual game call
symbol identities; two
171B candidates' original
14 PE field positions,
types, zero addends,
destinations verified.
No truncation or exact
whole CODE credit.
[F900 complete original Archive evidence](ARCHIVE_REAL_GROUPED_LIFETIMES_F900.md);
scripts/repo-python scripts/verify-archive-grouped-live-owners-f900.py.

## 4. Attribution, validation, research and storage

- **Original authored ≠ compiler/library ≠ unknown**. The 95 unknown
  candidates have 3,420 uncredited CODE bytes; e.g. fully byte-exact
  but origin-unknown `0061F125` remains UNACCEPTED. A plausible name,
  `Ghidra` function boundary or exact source alone cannot change this.
- **Accepted whole-function CODE** requires the entire original PE
  boundary, natural C++ under the actual VC7.1 flags, every zero-addend
  COFF relocation, independent authored origin and targeted cold replay.
  Separate after-RET jump DATA and MSVC EH carrier code/data are never
  double-counted as game CODE. Use `AGENTS.md` and [workflow](RE_WORKFLOW.md).
- **Research files**: keep original native/COFF evidence, negative C++
  grammar controls, `build/matching/`, H184 protected probes, full
  `.analysis/vc71-wine/`, Ghidra and all original files. The history
  archives are **local/ignored**, not Git assets.
- **Space-efficient recovery**: archived frozen f133–f166 giant `.asm/.cod/.log`
  traces and older JSON/PDB/log batches are documented in
  [storage hygiene](STORAGE_HYGIENE.md). Rehydrate an actual old
  original trace with `scripts/repo-python
  scripts/archive-frozen-giant-traces.py --restore ORIGINAL_PATH`;
  independently verify its SHA256 before relying on it. Do not
  delete archive files because they are absent from Git.
- **Required end-of-turn**: verify target/affected native source,
  `validate-tracking.py --require-target`,
  `audit-active-handoff.py`, `update-progress.py --check` when the
  count changes, `git diff --check`, inspect dirty changes and
  commit substantive results using **`gpt-web: ...`**.
  Local Git commits are not remote Oracle acceptance; **do not push**.
