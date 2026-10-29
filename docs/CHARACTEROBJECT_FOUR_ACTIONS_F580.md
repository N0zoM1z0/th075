# F580 — original action 0x33A through 0x33D: four whole CharacterObject game-state cases

**Japanese TH075 v1.11 original-PE / pinned MSVC 7.1 C++ source evidence,
not accepted exact whole giant CODE.** Pinned Japanese PE SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
F580 extends the very same real-action C++ `Advance()` source used in
F572–F579 for original CharacterObject boss `004EBDA0` (**33,293 original
whole CODE bytes**, still nonexact). The original entire boss CODE SHA,
all physical compressed index tables and each complete original case
boundary are independently verified BEFORE one new selected VC7.1
compile. Unknown later game actions still have diagnostic-only marker
stores; original actor class layout and complete local stack lifetime
are not asserted as known.

## Four genuine native actor game actions, not four 13-byte leaves

The original first compressed jump table physically bounds four more
complete native action handlers, and the selected natural C++ emits
**all their true register/x87/branch instruction roles, complete
individual instruction lengths, and whole CODE extents**, with no
new read-only machine-order swaps:

| Original action | Complete native x86 instructions | Original inner CODE (uncredited) | Genuine typed COFF call/global fields | Physical grammar |
| --- | ---: | ---: | ---: | --- |
| **0x33A** | **66** | **229 B** | **6** | **Strict** |
| **0x33B** | **84** | **301 B** | **11** | **Strict** |
| **0x33C** | **127** | **472 B** | **7** | **Strict** |
| **0x33D** | **127** | **472 B** | **7** | **Strict** |
| New source this round | **404** | **1,474 B** | **31** | Four full case sources |

### 0x33A — native source fade, not simply a copied 0x32D body

Stage zero calls native `0040FBB0(0,0,0)` and initializes real
float scales `+0x1C/+0x20` to 1.0f, color bytes to FF, sprite
short `+0x1A` to 0x4E2 and float offset `+0x28` to −75.0f.
On every tick the scales increment using native float global
**`006583FC`**, not the `006583F8` global of previously recovered
0x32D. It performs the native signed stage >1 fade of color byte
`+0x11` by 20 only while **strictly greater** than 20, then true
`0045B830` reset or original `0040FA30` action query. One fresh C++
source emits the original entire 66 instructions / 229 bytes with
all six genuine typed COFF fields.

### 0x33B — signed direction, genuine x87 random motion and comparison

The actual 84-instruction native body initializes state under
`+0x62/+0x64==0`, performs `0040FBB0(0,0,0)`, sets scales to 1.0f
and RGBA bytes to FF. It calls native `00455580(0,45)`, converts
the result with **`FILD`**, subtracts real float global
**`00659728`**, adds float global **`006581DC`**, uses native `FCHS`
and passes the resulting genuine float argument plus 18.0f to
actual `0040FB70`. It updates signed `+0x66` motion, velocity using
**`00659454`**, and another x87 field using **`00657CBC`**.
Its native float position collision check uses real global
**`0065912C`**, `FCOMP`, `FNSTSW AX`, `TEST AH,5` and **`JP`**.
A native C++ expression `if (F32(+0x48) < gMaxPositionAt0065912C)`
reproduces precisely that instruction grammar; a superficially
similar `!(F32(+0x48) <= threshold)` incorrectly generated
`TEST AH,0x41; JNP`. Twelve genuinely distinct VC7.1 C++ relational
forms were compiled and checked, rather than assuming that
mathematical inequalities always lower to the same x87 flags.

### 0x33C/0x33D — two independent 127-instruction parent-state policies

Both full native cases begin with a parent state check, genuine
integer direction-byte ×65 via `IMUL/FILD`, a parent `+0x44`
position contribution and original global **`006590AC`** into
member `+0x48`, followed by stage gating, signed `+0xD8` state
transitions, `0040FBB0` reset, x87 scale fade using double
`00659730` and float `006583FC`, native `0045B830` reset and
`0040FA30`/`0040FB40(1)` callback. Their natural C++ source
contains the actual gameplay, never a marker substituted for it.

Critically, the original **0x33D is not an exact constant clone**
of 0x33C: its first and second parent state compares use **0x2C1**,
but its THIRD compare (instruction ordinal 34) uses **0x2BE**.
The original 0x33C uses 0x2BE at all three. This was established
by directly rereading original Japanese PE instructions, not a
previous assumption. Ordinary source lvalue
`*(&PF32(+0x44)) + static_cast<float>(S8(+0x66)*65)` also
naturally produces the original early parent pointer load before
signed-direction integer-to-FPU operations. An alternative naive
expression loaded parent *after* `FILD`, despite yielding the same
numerical arithmetic. Twelve natural C++ operand/lifetime variants
were compiled and compared, with no inline ASM or artificial stack
padding to manufacture an exact machine-code prefix.

## Original physical COFF verification and cumulative accounting

Tracked normal C++:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
New original-backed verifier:
[`scripts/verify-characterobject-four-next-actions-f580.py`](../scripts/verify-characterobject-four-next-actions-f580.py).
This newly compiles only **ONE affected normal VC7.1 translation unit**
(`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`), independently rereads all native
original case boundaries/entire CODE, compares the complete original
GPR/x87/branch grammar, and checks every real `REL32`/`DIR32` source
relocation at the actual original instruction ordinal, with correct
original PE callee/global, C++ symbol, physical type and zero addend.
It further checks entire first-switch post-RET DATA (all 60 physical
COFF DWORD handler slots, authentic duplicate/default partitions,
198 original compressed index bytes and distinct 438 DATA-shape bytes).

| Original game-action source in same function | Whole original x86 instruction roles | Inner native CODE (NOT independently exact) | Genuine typed COFF fields |
| --- | ---: | ---: | ---: |
| F572–F579: 21 previously proved full native game bodies | 2,812 | 10,421 B | 193 |
| **F580: new four complete action cases** | **404** | **1,474 B** | **31** |
| **Total 25 complete source cases** | **3,216** | **11,895 B** | **224** |

The three existing F573/F574/F578 independent adjacent MOV/FLD
read-only instruction-order differences are still **clearly
nonidentical source machine order**, and authentic original deep EBP
widths for actions 0x330/0x331 still add 18 source-codegen bytes
each. **No new difference** is introduced in F580's four new
complete cases. Under the richer normal C++ source, neighboring
0x332 continues to compile with the authentic 1,019-byte native
instruction widths (though original full-frame slot addresses are
still different). No partial inner CODE byte is accepted as an
independently exact function and no after-RET DATA is counted as CODE.

### Selected-only reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-four-next-actions-f580.py
# Recheck older case sources in the larger same C++ switch:
scripts/repo-python scripts/verify-characterobject-fade-spawns-f579.py
scripts/repo-python scripts/verify-characterobject-contact-stage-f578.py
```

The new source/OBJ/PDB, compiler logs and genuine PE/COFF summary
are retained under ignored `.analysis/f580-characterobject-four-source/`.
Original disassemblies, actual 0x33D third-compare correction, negative
x87 relational expression controls and parent-pointer order source
experiments remain under `.analysis/f580-characterobject-actions/`.
The **11,895 original internal CODE bytes still belong to the
nonexact 33,293-byte *whole* boss**; this is neither 25 standalone
exact functions nor a split original CODE credit. No all-unit cold
replay and no external Factory/Oracle acceptance receipt.
