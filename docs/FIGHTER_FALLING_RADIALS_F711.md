# F711 — source-backed complete original falling radial cases 2D0/2D1

**Substantial real fighter C++ reconstruction, NOT whole-function byte-exact.**
Target: original user-supplied Japanese TH075 1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Whole authored fighter `00543210` remains **58,294 CODE B** with
**943 separately owned after-RET switch DATA bytes**. The following
are physically complete *internal actions*, not separately callable
whole original game functions and not accepted whole-function credits.

## Full original native PE evidence and meaningful C++

| Physical original native action | Native CODE interval | Native CODE / x86 | Whole-parent source CODE / x86 | Physical typed original PE/COFF fields |
| --- | --- | ---: | ---: | ---: |
| `0x2D0` | `0054E111`–`0054E2B1` | **416 B /120** | **416 B /120** | **15/15** |
| `0x2D1` | `0054E2B1`–`0054E451` | **416 B /120** | **416 B /120** | **15/15** |
| **Both distinct original cases** | | **832 B/240 x86** | **832 B/240 x86** | **30/30** |

The new tracked normal C++
[`FighterFallingRadialsF711.inc`](../probes/FighterFallingRadialsF711.inc)
recovers authentic original gameplay, not just code-shape markers:

- Both original `00454BC0` storm setup calls (`0xFF0000` for `2D0`
  vs `0xFF` for `2D1`), stage-zero initialization of physical
  motion-X and short+`0xF00`, and original stage gates.
- Real positive-height condition (`this+0x48 > 0065782C`) and
  stage counter `<7` or `<6` respectively, actual Y-velocity
  decrement by native `[00658290]`, ground-crossing x87 comparison,
  original reset and auxiliary action `7` or `6`.
- Distinct completion policy that calls `0040FAC0(0)` and returns
  from the original action without running the subsequent attack.
- Genuine stage `4` vs `3` launch, real `RandomBoundaryAt455580(0,15)`
  and native float `FILD` for horizontal velocity. `2D0` adds global
  `[006592A4]`; `2D1` uses global `[00659A0C] - float(random)`,
  retaining the original physical x87 `FADD`/`FSUBR` distinction.
- Two native `00453C80` projectiles `0x7D` and `0x7E`, correct
  direction × 80 float-X, original `this+0x48 + [00658268]`
  member-first `FLD/FADD`, direction, and flag. Actual trajectory
  members+`0x54=40.0f`, +`0x5C=6.0f`, and native final
  `00453D60(31)` call are represented in both actions.

Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, with actual
C++ embedded in **one complete original-shaped `00543210` parent**,
generates the exact original **120 x86 mnemonic and instruction-width
positions** for each of the two independently bounded actions. All
**30 physical original typed PE/COFF fields** match the genuine
native instruction ordinal, real original target address, `REL32` or
`DIR32` type, zero addend and source symbol, including the random
float globals and both `0x7D/0x7E` spawn calls. No artificial stack
padding, manually forced x86 or cropped comparison is used.

## Crucial negative: source GPR/EBP and genuine earlier strict regression

These cases **remain NONSTRICT**. Each has **60 real normalized
nonfield GPR/CFG operand mismatches** despite exact 416-byte x86
geometry and all original typed relocation fields.
Original meaningful random conversion temporaries use real native
`2D0` `EBP−0x184/−0x188` and `2D1` `−0x18C/−0x190`;
the new compiled original-shaped giant instead allocates these
at `−0xA4/−0xA8` and `−0xAC/−0xB0`. All eight individual real
six-byte `MOV/FILD` scratch instructions are checked, **not
blanket-normalized**; the native original saved `this` is
`EBP−0x44`, compiler-saved `this` is `EBP−0x28`.

More importantly, inserting this additional genuine source into the
real giant changes VC7.1's downstream register-allocation phase.
**It is NOT correct to reuse F708's 27 context-strict action count
in this source context.** All previous earlier **26** strict
nonterminal native cases remain strict, but native `2EF` (788 B,
224 x86, 20 genuine physical fields) now has **144 real nonfield
GPR/x87 operand mismatches** even though every instruction start,
width and mnemonic is still native-shaped. The following native
`2F0` (1,169 B/342 x86/42 fields) has **175** genuine nonfield
GPR differences, and native `2F1` (977 B/274 x86/23 fields) has
**170**. These real regression counts are separately attested,
not accepted as strict, and original EBP receiver slots are still
validated physically. The downstream actual `2F8` (928 B),
`2F9` (1,367 B), `2FA` (source 979 B), `2FB` (647 B),
`302` (935 B) and terminal `31B/31C` continue to have their
independently rechecked native source/PE geometry and known actual
nonstrict cases.

The observed register-phase effect is not simple cumulative code
length: F711 independently compiled the actual *whole parent*
with only `2D0`, only `2D1`, and with both. Either real new case
alone causes **88** authentic 2EF GPR differences; both together
cause **144**. The whole source-parent PE fields and original
2EF 788-byte mnemonic/width geometry remain intact. Seven
meaningful alternative natural C++ expression/control-flow variants
were also freshly compiled against the **entire parent**:
reversed random-sum source operands; equivalent subtraction with
negation; reversed frame-gate evaluation; member `*(&float)`
read-only lvalues; reversed stage constant tests; `-=` for real
gravitational velocity; and used velocity read-only lvalues.
None restored original 2EF GPR allocation. Five alternatives retained
both 416-B/120-x86 original action geometry; the other two changed
real original codegen opcode order/width and are rejected even
when their total size matched. All genuine alternatives have their
actual CPP, OBJ, compiler transcript and native difference receipt
locally under ignored `.analysis/f711-fighter-two-falling-radials/`.

## Bounded original-game verification and reproducibility

[`verify-fighter-falling-radials-f711.py`](../scripts/verify-fighter-falling-radials-f711.py)
regenerates the **whole original-shaped fighter parent**, inserts
real `2D0` and `2D1` normal C++ alongside original-backed F672,
F706 and F708 actions, cold compiles **just that one parent**, and
re-reads every relevant original native PE extent and physical
COFF field. It requires both complete 416-B actions and all 30
zero-addend original relocation owners, independently proves their
real EBP offset negatives, verifies previous twin-burst `2BF/2C4`
and five `259–25D` handlers, and rechecks later full-native
`2F8–302` cases, the **26 earlier truly strict internal action
bodies**, and the **entire independent 943-B after-RET switch DATA**.

The older F674/F676/F696 checker defaults still require their
original strict/negative source contexts. The F711 verifier instead
passes explicit, independently measured `144/175/170` real native
nonfield GPR regressions; it never relaxes all source mismatches or
claims they are cosmetic. Authentic original `EBP−0x44` receiver
identity is checked against the new compiler frame. The F706
checker now allows a separately authenticated *earlier* native
storm prologue without confusing it with physical `2F9/2FB/302`.

```bash
scripts/repo-python scripts/verify-fighter-falling-radials-f711.py
scripts/repo-python scripts/verify-fighter-twin-burst-f708.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

No accepted whole fighter CODE, no independently creditable
internal-case function, no EXE patch, no fake locals or 943-unit
cold replay. Official authored complete-function exact ledger is
still **943 functions /862,726 CODE bytes (43.71% reviewed)**.
