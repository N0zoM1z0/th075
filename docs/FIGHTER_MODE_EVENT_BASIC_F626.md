# F626 — original 109-instruction native action0x63 in five giant fighter controllers

**Attested Japanese TH075 1.11 PE → ordinary original-profile VC7.1
natural C++ inside selected whole giant `Advance()` translation units;
NO exact whole-giant function adoption.** Original executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Re-reading the actual 109-instruction original game grammar

F624 reconstructed an actual **118-instruction** native action0x63
in `00564BE0` and `005AEEC0`, including an additional follow-up
action gated by `this+0x370 + this[0x39D]`. That additional bonus
path is **not present at all** in the original `0x63` 109-instruction
cases for seven other fighter giants. Their real original native
control flow ends the `this+0x32A + this[0x39D] == 2` path immediately
after calling real game method `0040FAC0(0x31C)`. Copying F624's
bonus logic into those actors would invent a branch, a game call,
and nine original instructions.

The full native case otherwise retains the independently verified
original mode-global signed-byte test at `006714B4` and its real
short-circuit behavior:

```cpp
if (g_ModeAt006714B4 != 3 || signedByteAt2CD == 0) {
    // Check original state 2, owner+0x60 and set action0x5F.
} else {
    // Check native state byte +0x32A plus live +0x39D:
    // transition to 0x31C when 2 or 1, or to 0x5F when 0.
}
```

There is no byte patched from the original: source
[`FighterMode63BasicF626.inc`](../probes/FighterMode63BasicF626.inc)
expresses the actual original behavior with normal signed
member accesses, genuinely short-circuited C++ `if` expressions,
real `0x2E8` target receiver and indexed byte owner status. The
original native x86 `JNE` at ordinal2 jumps to ordinal7; ordinal6
jumps to ordinal27. The stage-two `0x31C` branch exits the native
case even if later conditions are true. The source leaves the
other actor-specific x86 case families unclaimed.

## Five strictly source-backed complete native case interiors

There are **seven** original giant fighters with the same 109-x86
structural source family, but *two* have a genuinely different
native GPR allocation phase from VC7.1's natural source in the
current enclosing whole function. An independent original PE →
selected source compilation verifies **only five** exact-register
original case0x63 subranges:

| Original enclosing huge fighter (all still NONEXACT) | Original 0x63 full native case CODE | Native GPR/x87/CFG roles | True physical typed original COFF fields |
| --- | ---: | ---: | ---: |
| `004AC040` | 417 B | **109/109** | **7** |
| `00486550` | 417 B | **109/109** | **7** |
| `00543210` | 417 B | **109/109** | **7** |
| `004D7E70` | 417 B | **109/109** | **7** |
| `005214B0` | 417 B | **109/109** | **7** |
| **F626 strict source proof** | **2,085 original inner CODE B** | **545** | **35** |

The original case0x63 is at the *last real* second packed-switch
dense index **25** (the slot 26 value is a common DEFAULT, not the
next original game handler). The full true original case ends at
the independently registered *next physical* original handler
**0x8C**. The compiled source is delimited using the actual next
C++ `0x8C` case's physical `DIR32` marker symbol and its instruction
literal `0x8D`, never by a guessed default handler or a cut-out
subrange. Every selected ordinary VC7.1 source emits **109 x86 /
417 actual source bytes**, with all native x86 instruction widths
and exact register/x87/CFG roles reproduced (after independently
resolving the genuine signed-byte `DIR32` global operand).

All seven actual original physical COFF positions per case are
individually checked: one `DIR32` mode-global `MOVSX` at original
x86 ordinal0 to **`006714B4`** and six original `REL32` game calls
at ordinals 22, 48, 71, 94 (four genuine `0040FAC0` transitions),
99 (`0040FA30` getter), and 107 (`0040FB40` auxiliary action).
Each source symbol, physical instruction ordinal, zero addend,
original PE absolute/relative target and complete case length is
verified without simply masking eight or more bytes as uncertain.

The strict original-backed
[`verify-fighter-mode63-basic-f626.py`](../scripts/verify-fighter-mode63-basic-f626.py)
**cold-compiles only the selected affected giant whole C++ source**
with pinned MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`.
For **each new whole-parent OBJ**, it rechecks all **30 previously
reconstructed original internal game case bodies** (through F614
0x58) and the *entire original physical after-RET* dense jump-table
COFF refs/sparse bytes and partition. Later `0x62` source remains
unmatched in some of these selected fighter owners and therefore
an honest original-action placeholder: the F622 `0x62` role proof
from other source contexts is **not** claimed to be simultaneous
with F626. No entire giant function becomes native byte exact.

## Explicit native register-phase and boundary negatives

Two original 109-instruction actors were also freshly compiled, but
remain genuinely **nonmatching** under this same source grammar:

| Original actor | Native 0x63 x86 / original CODE | Natural source | Actual native GPR/x87/CFG differences after verifying typed mode-global field |
| --- | --- | --- | ---: |
| `004F7130` | 109 x86 / **416 B** | 109 x86 /417 B | **67** |
| `0058AF60` | 109 x86 /417 B | 109 x86 /417 B | **67** |

The first has an additional real x86 size difference; the second
has distinct instruction-width differences despite equal total
native CODE. In particular, `0058AF60` has only **26** slots in the
second native packed table; its last real 0x63 is **slot24** and its
next physical handler is **0x89**, not generic slot25/0x8C.
The checker detects both of these real original layout distinctions
and preserves them in `--negative-actor` receipts rather than
claiming the 5 matching actor source is universal. A second
provisional verifier was also inspected for additional useful
native checks; it had the incorrect universal slot25/0x8C and an
incorrect original instruction ordinal assumption. Its original
source is archived in ignored `.analysis/f626-mode63-regular/`
after integrating the valid original-check ideas into the single
tracked verifier, to avoid diverging duplicate source of truth.

**F626 adds exactly five strict source-backed internal case bodies,
545 real native x86 roles, 2,085 original inner CODE bytes, and
35 typed PE/COFF fields**, without any new accepted complete authored
source unit. The studied original giant case total rises from
F598–F624's **341 cases /88,614 inner CODE bytes** to **346
original native inner case subranges /90,699 original inner CODE
bytes**. These are source compiler grammar findings, **not**
independently accepted complete original functions or proof that
all prior alternative case contexts are simultaneously exact.
Official authored whole-function acceptance stays at **943
complete exact functions /862,726 original CODE bytes**. No game
binary modification, manual ASM, synthetic EBP locals, external
Oracle acceptance or full all-unit cold replay.

## Reproduce only newly affected giant source TUs

```bash
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py --boss 0x004AC040
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py --boss 0x005214B0
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py --negative-actor 0x004F7130
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py --negative-actor 0x0058AF60
# Optional only the five newly affected giant original C++ TUs:
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Original native PE x86, each selected generated normal C++ full
giant, source COFF/PDB, compiler outputs, true native typed relocation
receipts and explicit negative actor controls are retained in ignored
`.analysis/f626-mode63-regular/verified/`. The initial independently
explored source/bytewidth candidates and the alternative verifier
were preserved under `.analysis/f626-mode63-regular/`.
