# F598 — native singleton action 0x32 in all eleven huge Fighter controllers

**New natural VC7.1 C++ reconstruction of genuine big-function interior
logic, not any whole-fighter exact CODE adoption.** We independently
rechecked the original Japanese TH075 1.11 `resources/th075.exe` (SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`),
all **eleven whole original giant CODE SHA256 values**, the real singleton
`CMP / JE` action **50 / `0x32`** branches, the physical next indexed
switch handler at action `0x33`, and the complete original after-RET
jump-table DATA before compiling source. Old F564/F566/F567 hypotheses
were treated as compiler-generation inputs to be reverified, **not
accepted** as proof of this action's code.

## The complete original singleton C++ source

A new tracked, readable C++ switch case lives in
[`probes/FighterSingletonContactF598.inc`](../probes/FighterSingletonContactF598.inc).
The true original full native block has **58 x86 instructions** and
**seven** physical native call/global address references. Its actual
behavior, verified at every native instruction ordinal:

1. Only when both signed stage `this+0x62` and signed frame
   `this+0x64` are zero, initialize position `this+0x50=-8.0f`,
   second position `this+0x54=0.0f` and counter `this+0x7C=0`.
2. When position is **strictly `<`** native float `0065782C`, add
   original native float `00658058`. Clamp position to zero **only when
   the new value is strictly `>`** `0065782C`. This **`<` / `>` pair**
   was derived from physical native `TEST AH,5; JP` and
   `TEST AH,0x41; JNE`; mistaken `>`/`>=` guesses compiled to the
   same number of instructions but used *different x87 status branches*.
3. Invoke original receiver call **`00454EE0`**, sign-extend its byte
   return and require its nonzero result together with signed byte
   `this+0x3BE` nonzero. Then multiply `this+0x50` by original
   **`double`** global `006583E8` and store the resulting float in
   `this+0x490`. This is the real **`FLD/F MUL qword/FSTP`** ordering,
   not a fabricated one-float multiply.
4. Compare original signed-short receiver call **`0040FA30`** with
   signed short `this+0x70`; when equal, invoke genuine receiver
   **`0040FAC0(0)`** before returning to the actual *whole fighter*
   shared exit.

`00454EE0` is a provisional name derived from its original call
address and signed byte return; the complete game class declaration
is not claimed. The source has no inline assembly, original-byte
embedding, fake frame padding, manual opcode patch or partial return.

## Eleven independent complete-case original/source comparisons

[`scripts/verify-fighter-singleton-contact-f598.py`](../scripts/verify-fighter-singleton-contact-f598.py)
recreates the original eleven opening actions 0–10 **from the
PE-backed generators** used for F564, F566, F567 (F564's historical
top-level generator is freshly rerun for its selected fighters).
It adds action 50 to the *same* real natural C++ `Advance()` switch,
then compiles only that selected source TU using the pinned MSVC VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` profile. The original **seven**
physical case references must occur in the right x86 instructions,
with correct COFF `REL32`/`DIR32` types, actual C++ symbol/destination
identity and **zero addends**, not just masked bytes.

| Entire original giant (still unmatched) | Original case0x32 CODE | Original case x86 | Typed real COFF fields | Previous 11 case x86 roles preserved |
| --- | ---: | ---: | ---: | ---: |
| `0045DD70` | 205 B | 58 | 7 | 611 |
| `0058AF60` | 205 B | 58 | 7 | 609 |
| `005D73C0` | 205 B | 58 | 7 | 611 |
| `00486550` | 205 B | 58 | 7 | 637 |
| `004AC040` | 205 B | 58 | 7 | 637 |
| `00543210` | 205 B | 58 | 7 | 646 |
| `00564BE0` | **256 B** | 58 | 7 | 620 |
| `004D7E70` | 205 B | 58 | 7 | 618 |
| `004F7130` | 205 B | 58 | 7 | 655 |
| `005AEEC0` | 205 B | 58 | 7 | 641 |
| `005214B0` | 205 B | 58 | 7 | 550 |

Original `00564BE0` uses **EBP-0x88** instead of a narrow source
owner slot. Exactly **17 real receiver `MOV` loads ×3 additional
encoding bytes** explain the entire original **256–205=51 byte**
difference. No other x86 instruction changes length; all **58/58**
register, operand, float/status, internal branch destination and
call roles still match. For the other ten original fighters, all
**205/205 compiled-original case sizes and 58 individual instruction
lengths** agree, after normalizing the enclosing giant's genuine
receiver slot and linker-resolved call/global addresses. This is
not byte-exact original CODE because the receiver EBP slots differ.

**Aggregate NEW source-backed native interior evidence:**
**11 complete original cases / 638 instructions / 2,306 original CODE
bytes / 77 typed original physical fields**. These are subranges,
not separate executable functions. Combining with F567's original
121 interior cases gives **132 source-backed case subranges, 7,473
original x86 roles, 26,835 original interior CODE bytes and 867 typed
COFF fields** across the eleven large unmatched originals. All
**1,607 full seven-switch DWORD COFF fields**, **4,502 literal
sparse-index bytes** and **10,930 after-RET DATA shape bytes** are
still verified; the new source preserves the original eleven earlier
cases' register/control roles. *None* of these interior bytes or DATA
is independently counted by the exact ledger.

### Targeted reproduction only

```bash
scripts/repo-python scripts/verify-target.py
# One previously incomplete 44K giant, no whole-unit replay:
scripts/repo-python scripts/verify-fighter-singleton-contact-f598.py --boss 0x004F7130
# One wide 61K original, validates 17 widened original EBP loads:
scripts/repo-python scripts/verify-fighter-singleton-contact-f598.py --boss 0x00564BE0
# Optional only the eleven affected natural C++ TUs (NOT 943 cold replay units):
scripts/repo-python scripts/verify-fighter-singleton-contact-f598.py
```

All eleven freshly compiled `.cpp`/`.obj`/`.pdb`, selected F564
baseline control logs and JSON metrics are preserved in ignored
`.analysis/f598-fighter-singleton/` and can be regenerated with
**only the named source builds**. No full function has become exact,
no `functions.csv`/`match-units.toml` acceptance changed and there
is no external Oracle receipt.

## Concurrent small-function and difficult-boss negative source controls

The entire giant `004EBDA0` was separately inspected at original
first divergent `004F344C` (case38D ordinal91): its real native
`MOV EAX,[EBP-0x40]` rotates to source `MOV ECX,[EBP-0x40]` and
persists into 38E and the first31 instructions of 3E3. **Six new
normal C++ expression/control variants** were compiled independently
in `.analysis/f598-native-register-investigation/`; five preserve
33,293 bytes/8,789 x86 and the *same* **137 residual nonrelocation
bytes**. A genuine inverted condition/else source instead has
33,295 bytes/8,790 instructions. **None solves original exactness**.
The earlier F596 solution to the three MOV/FLD swaps was not changed.

The complete small `0041CE50` destructor was also recompared against
six new original-backed filename/`free` declaration/expression
variants (one plus five in `.analysis/f598-archive-declaration/`).
Direct `free(*At(index))` or cast/parenthesized equivalents **do**
place the two native resource deletion temporaries at EBP-0xC and
-0x8, but they emit only **165 bytes/49 instructions** instead of
native **171 bytes/51** and omit the actual named filename load/store.
Keeping a meaningful `char*` or `void*` filename local restores
171/51 but reverts to the incorrect source slots EBP-0x10/-0xC/-0x8
and **108/115** nonfield bytes. An actual filename reference gets
**102/115**. These are *failed whole-function controls*, not 171-byte
exactness. This identifies a compiler local-lifetime tradeoff worth
further investigation, not a fabricated EBP-slot fix.

**Current official acceptance stays 943 whole authored exact functions
/862,726 CODE bytes;** no full all-unit cold replay was run.
