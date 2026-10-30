# TH075 — ACTIVE reconstruction agent handoff

**Verified snapshot: 2026-10-31, current F780 exact ledger; F827 giant and F828 authored Archive research.**
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
