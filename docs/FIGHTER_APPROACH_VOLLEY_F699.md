# F699 — restore full native fighter 2FA approach/volley handler inside complete boss

**SOURCE-BACKED, NOT BYTE-EXACT.** Target is the user-supplied Japanese
TH075 v1.11 `resources/th075.exe`, pinned SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original authored boss `00543210` remains a **58,294-byte whole CODE
function** with **943 distinct after-RET switch DATA bytes**. Its original
`0x2FA` action is a *physical internal handler*, **not** another function.

## Full original action and native C++ recovery

Pinned original whole-action extent is `005509CC`–`00550D97`, **971 CODE
bytes, 279 actual x86 instructions, 31 genuine typed zero-addend original
PE/COFF fields**. The direct original PE control-flow and 31 physical
field destinations were checked anew, rather than adopting an old source
hypothesis. The recovered normal C++ source in
[`FighterApproachVolleyF699.inc`](../probes/FighterApproachVolleyF699.inc)
models the original initial state and flag resets; early stage gravity,
ground/position contact, state-10 transition; stage-10–12 facing-dependent
horizontal correction; paired edge/parent position and facing checks;
action-completion counter and `2FB` transition; stage-3 absolute lateral
distance, randomized direction, original two type `0x7D`/`0x7E`
projectile calls, motion initialization; and stage-10 auxiliary action 8.
The original `00412D90` float absolute-value call and genuine
`00454EE0` contact calls are retained, rather than replaced by
approximate arithmetic or stubbed branch bodies. Source aliases and
sign-sensitive float comparisons are still **provisional** until exact
compiler evidence resolves every original predicate and lifetime.

The pinned `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` VC7.1 compiler builds
**one entire original-shaped giant parent** with true F681 `2F8`, true
F684 `2F9`, newly restored F699 `2FA`, and F696 `2FB` in their authentic
source order. Newly compiled **2FA emits 281 x86 /973 CODE B**, with all
**31 original PE/COFF fields matched in original physical instruction
order**, including exactly the correct call/global type, zero addend,
source symbol and independent native PE destination. Original native
2FA still contains **279 x86 /971 B**: the full action is **NONSTRICT**
and no whole-function exact CODE is accepted.

### Genuine native/compiler discrepancies, not suppressed

Native `2FA` x86 ordinals `129` and `141` compare a computed x87 value
directly against an actual `this` float memory field using `FCOMP`.
Our source compiler instead emits `FLD` plus `FCOMPP` at the
corresponding aligned positions `129/130` and `142/143`, adding two
x86 instructions and two bytes overall. It also differs at native
original branch opcodes `46`, `110`, `202` (`JP` instead of source
`JNE`), and has an original `FLD` operand-load ordering difference
around native ordinal `193`. The actual original saved receiver is
`EBP-0x44`; source `EBP-0x18` is separately authenticated. The
original stage-3 signed-side-to-x87 integer scratch at ordinal `229/230`
uses `EBP-0x1F8`, while source ordinals `231/232` use **`EBP-0x7C`**;
this real width/ownership discrepancy is **not masked**. The program
has no manual CODE graft, fake locals, injected padding or cropped
comparison.

**11 additional successfully compiled complete parent C++ controls**
varied actual float operand direction, explicit lvalue identity
expressions, sign-negated edge/ground conditions, read-only contact
arguments and native `fabs` expression ownership. None removed the
two extra x87 instructions or recovered whole exactness. A further
ground-predicate compiler attempt failed with a Wine transport reset;
that attempted source is **not a compiler negative or a verification
result** and is retained only for traceability. Its native behavior
must not be inferred from the failed run. Actual source, whole compiler
OBJ/PDB, logs and honest opcode matrices are preserved locally under
ignored `.analysis/f699-fighter-approach-volley/`.

## Full-parent context, dependent cases and acceptance boundary

This addition changes the following genuine `2FB` compiled geometry:
its source now emits **181 x86 /641 CODE B** rather than F696's
**181 x86 /635 B**, still compared with the original **647 B /
181 x86** and all **17 genuine physical PE/COFF fields**. The four
existing original-vs-source x87 order differences and 109 normalized
GPR/CFG differences remain. New source temporary scratch slots differ;
no previous F696 *source-context* result is silently reused.

[`verify-fighter-approach-volley-f699.py`](../scripts/verify-fighter-approach-volley-f699.py)
reads and decodes the original pinned PE, reconstructs the entire
source parent freshly, rechecks **all 31 native `2FA` PE/COFF fields
in order**, original/compiled opcode edits and original negative x87
and stack operands, then rechecks the downstream full `2FB` with its
**17 separate physical fields**. It passes an explicit parameter to
F684's native `2F9` verifier because its following branch is now a
real, source-backed `2FA`, no longer the previous placeholder.

In this **same newly compiled full parent**, the F696 regression
verifier rechecks the prior **27 strictly source-backed nonterminal
internal case bodies**, authentic previous negative controls (`186`,
`18A/B`, `258`, `2F0/2F1`, `2F8`, `2F9`, `31B/31C`), and the **entire
943-byte separate after-RET switch DATA**, with independently validated
real saved-this compiler slot and all **2,468 physical source MOV uses**.
Previously verified `2F9` still has 236 real GPR/x87-role differences;
`31B` still has 43 in this parent. Neither is promoted to strict.

Targeted reproduction of **only one** original-shaped giant parent:

```bash
scripts/repo-python scripts/verify-fighter-approach-volley-f699.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

**No cold replay of the other 943 accepted units, no new independent
original game function exact credit and no whole 58KB boss exactness.**
The authored whole-function ledger remains 943/862,726 CODE B.
