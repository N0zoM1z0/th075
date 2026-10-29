# F573 — six original FUCOMPP gates in entire 248-insn actor action32A

**Pinned Japanese TH075 v1.11 PE/native C++ source evidence, NOT
byte-exact whole giant.** Original PE SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This extends [F572's ten complete genuine CharacterObject game-action
cases](CHARACTEROBJECT_FIRST_TEN_NATIVE_CASES_F572.md) in original
33,293-byte entire fighter `004EBDA0` by one additional physically
bounded complete original action **`0x32A`**. The original source
later actions remain diagnostic marker stores; no original owner
nominal type or exact containing frame size is asserted.

## Original 248-instruction game algorithm

Original compressed jump map action `0x32A` through action `0x32B`
delimits exactly **932 original CODE bytes, 248 contiguous x86
instructions**, which our new natural C++ reproduces *in the same
source switch as the original F572 cases 0x320..0x329*.

- Original signed parent state `+0xE4 -> +0x60` is checked against
  **0x31 and 0x96**; if in range, call true native `0045B830`,
  use the actual five-iteration `for` effect spawn at `00453A70`
  (effect `0x3E4`), and conditionally spawn `0x3E3` when native
  parent `+0xEFA` exceeds 25.
- If not in the parent range, the native actor checks local `+0x7C`
  and signed stage/frame state at `+0x62/+0x64`, resets via the
  true `0040FBB0(0,0,0)` call, and performs **six independent,
  ordered floating-point equality tests** of state field
  `this+0xC8` against original globals `0065782C`, `0065747C`,
  `00657480`, `00657CF8`, `00657D14`, `00657874`. These select
  motion position/velocity pairs `(5,6)`, `(3,8)`, `(1,10)`,
  `(-5,6)`, `(-3,8)`, `(-1,10)`; they are independent `if`s,
  **not** one guessed `else if` or integer equality switch.
- The original performs x87 motion updates using actual signed
  direction byte `+0x66`, velocity at `+0x54`, float at `+0x50`
  and globals `00658058`/`00657CC0`. Under the native stage
  condition it emits **two original effect-spawn calls** for
  `0x32B` and `0x32D`, then original `00453D40(4)`, action switch
  `0040FAC0(0x33B)`, four zero motion stores, and a genuine early
  exit. Other paths use actual `0040FA30` and `0040FB40(1)`.

The C++ uses actual `if (*(&F32(0xC8)) == global)` source lvalue
semantics to reproduce all **six native `FLD original global; FLD
this+0xC8; FUCOMPP; FNSTSW AX; TEST AH,0x44; JP`** sequences.
The usual `if (F32(0xC8) == global)` emits the two `FLD` loads in
reverse order under VC7.1, even though the float comparison is
mathematically symmetric. Eleven independent ordinary C++ operand,
reference and volatile probes were compiled to establish this,
without copied target assembly or fabricated padding.

## One explicitly bounded nonidentical instruction ordering

The new source emits the **same 248 native instruction types and
per-instruction sizes** (932 total bytes) as the original, all true
register operands, six `FUCOMPP` comparisons and 19 authentic
call/global source references. However **the original is not
instruction-order or byte-exact**: its instructions 186 and 187
are respectively:

```
MOV EDX, [saved_this]
FLD DWORD PTR [ECX+0x48]
```

The natural C++ compiler emits exactly the reverse order of these
two instructions. They are **independent read-only operations**:
MOV only changes EDX, while FLD uses ECX and writes the x87 stack.
There is no branch, intervening write or COFF field. The tracked
verifier permits **only this explicitly verified commutation** and
requires all other 246 original action32A instructions, GPRs,
operands, sizes, x87 roles and branch targets to match exactly.
Additional natural C++ operand-order variants were compiled; none
removed this remaining two-instruction ordering mismatch without
introducing different errors. This is a source-semantic match, not
machine-order exactness or an accepted original function.

## Full original-PE/physical COFF validation

Updated tracked C++ source:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
New targeted verifier:
[`scripts/verify-characterobject-extended-action-f573.py`](../scripts/verify-characterobject-extended-action-f573.py).

The script freshly compiles **one affected ordinary VC7.1 source TU**
with `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, then rechecks the
original SHA-attested full 33,293-byte CODE and 438-byte after-RET
DATA geometry, the 60 real native dense handler DWORD slots,
original default/repeated partitions and 198 literal compressed
index bytes. It also independently reruns F572's *strict*
original/compiled comparisons for all ten prior actions (not
trusted merely because a previous compile passed).

Total of all 11 original-backed *inner* game-action bodies now:

| Native original action | Complete x86 instructions | Native CODE | Genuine typed COFF fields | Order check |
| --- | ---: | ---: | ---: | --- |
| `0x320..0x326` (7) | 21 | 91 B | 7 | Strict |
| `0x327..0x329` (3) | 813 | 2,996 B | 54 | Strict |
| `0x32A` (1) | 248 | 932 B | 19 | One proven read-only swap |
| **Total** | **1,082** | **4,019 B** | **80** | 10 strict cases + 1 limited equivalence |

All **80 actual physical `REL32`/`DIR32` call/float fields** have
real original-PE target identity, same instruction ordinal, type,
matching C++ external symbol and **zero addend**; no unverified
literal `[0]` placeholder is treated as original absolute data.
The full original switch has **60 zero-addend `DIR32` handler fields,
198/198 byte-identical sparse-index bytes and 438 after-RET DATA
layout bytes**. They are *DATA*, not extra CODE credit.

### Reproduce only affected C++ source

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-extended-action-f573.py
scripts/repo-python scripts/verify-characterobject-action-family-f572.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Original PE/case disassembly, 11 native C++ equality variants, pointer
expression negative controls and full compiled candidate logs are
preserved under ignored `.analysis/f572-characterobject-native-actions/`
and `.analysis/f573-x87-lvalue/`; fresh COFF/PDB/JSON receipts under
`.analysis/f573-characterobject-action32a/`. None of the **4,019
original inner CODE bytes** can be counted as an independently exact
function: the complete **33,293-byte giant is still unmatched**.
No accepted whole/split CODE/DATA coverage, full all-unit cold replay,
or external Factory/Oracle receipt.

## F574 follow-up: two more original action bodies

The same tracked normal C++ source has now independently recovered
complete native `0x32B` (112 original instructions /422 bytes)
and `0x32C` (176 original instructions /635 bytes) in addition to
F573's action `0x32A`. The F573 verifier still independently
recompiles and revalidates its original first eleven actions,
while [F574's extended checker](CHARACTEROBJECT_STAGE_CURVE_F574.md)
explicitly verifies 13 original inner cases and another separately
proven read-only original/source instruction swap in action32C.
All whole-fighter CODE remains nonexact.
