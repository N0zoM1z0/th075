# F759 — original fighter C8–CB C++ restores 1,804 physical case bytes in 58KB giant

**Positive original-target whole-parent compiler evidence, NOT newly accepted
whole-function CODE.** Target: pinned user-supplied Japanese TH075 v1.11
`th075.exe`, SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The entire independently authored giant callable `00543210` still spans
**58,294 original CODE bytes** plus **943 separately owned after-RET
switch DATA bytes**. It is **not yet exact**. The four switch cases below
are not independently callable functions, so their reconstructed interiors
receive **zero new official exact CODE credit**.

## Origin of the missing 16-byte physical stack lifetime

The previous complete fighter source retained four literal placeholder
actions `0xC8`, `0xC9`, `0xCA`, `0xCB` rather than original gameplay.
Earlier F734/F752 observations of `0x190`'s 276-byte native state showed
a 266-byte source body: one genuine conditional jump lacked four bytes,
and one actual integer-to-FPU MOV/FILD pair used `EBP−0x80` rather
than original **`EBP−0x90`**, losing three bytes per instruction.
F756 and F757 tried semantic C++ source grammar changes in other
contexts, including six full-parent original eight-shot loop lifetime
models; all were negative.

An independent census of the true original native source shows the real
source of the **16-byte deficit is upstream**, not the 8-shot loop:
original `C8` owns integer conversion temporary `EBP−0x74`, `C9`
owns `−0x78`, `CA` owns `−0x7C`, and `CB` owns `−0x80`. These are
**four meaningful game floating-point computations**, each requiring
one authentic compiler scratch DWORD. All four were missing from the
placeholder source. The following original `18A/18B/190` used
`−0x88/−0x8C/−0x90`, whereas the previous generated full parent
used `−0x78/−0x7C/−0x80` — exactly four missing DWORDs. This is
physical native PE evidence, not a recommendation to add fake locals.

## Four original complete gameplay case bodies, one real parent

[`probes/FighterFourDirectionalC8F759.inc`](../probes/FighterFourDirectionalC8F759.inc)
contains **normal C++** for the original four actions, emitted as
one include inside the **entire original source-shaped fighter switch**.
The real policies include original `00454BC0` startup (its third
argument is **255**, not `-1`), frame-zero initialization,
position/velocity and signed threshold collision, authentic scene/aux
transitions, and real facing-dependent `00453C80` projectile spawns
and `00453D60` preparation. The reverse-facing pair `C9/CB` uses the
independently observed borrowed typed position `this+0x44`, producing
native `FILD integer; FSUBR position` instead of the wrong early
`FLD position; FISUB integer` grammar. The C8 action transition's
two true native `break` exits also restore the actual 5-byte parent
JMP rather than a nonnative 2-byte intermediate branch.

| Original action | Entire native CODE | Native x86 | Authentic PE/COFF fields | External parent-tail JMPs |
| --- | ---: | ---: | ---: | ---: |
| `C8` / `0054737F` | 496 B | 145 | 16 | 5 |
| `C9` / `0054756F` | 424 B | 127 | 14 | 3 |
| `CA` / `00547717` | 439 B | 129 | 12 | 2 |
| `CB` / `005478CE` | 445 B | 131 | 12 | 2 |
| **Complete four-case interiors** | **1,804 B** | **532** | **54** | **12** |

Each case emits **identical native instruction count, widths, mnemonic
sequence and genuine register/operand machine bytes** except for the
properly identified *external parent* jump displacements and real
COFF target fields. For all **54** physical typed fields, the
original native PE bytes independently decode to the *same actual
PE destinations* as the C++ decorated COFF symbol identities, with
correct operand offset, REL32/DIR32 kind and zero addend. The source
is measured against the **whole native case**, never a truncated
favorable subrange. Exactly **1,540/1,540** other native nonfield bytes
are byte-identical, while the **12 original 4-byte shared-tail jump
displacement fields are still different** because the entire parent
layout is incomplete. Masking those differences is for **diagnosis
only** and is **not** accepted game CODE matching or `structural-exact`
credit.

The real four scratch slots propagate downstream naturally. Selected
entire native action contexts `18A,18B,190,191,192,194,195,2D0,302`
now all have their authentic integer-source MOV and x87 FILD **EBP
stack-slot operands** restored in the freshly compiled full parent.
Specifically `190` now emits **276 B / 75 x86** like its original,
not the former 266-byte source; it is **still nonexact in actual
register bytes and parent-tail destinations**. This does not imply
those downstream whole case interiors are all machine-byte exact.

## Real entire parent, switch DATA and revalidation

The source generator composes all *tracked* earlier ordinary fighter
C++ fragments (including F752 genuine borrowed actor/opponent
position owners), replaces all four literal placeholders and
**fresh-compiles only the affected full 58KB giant TU** with pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` under headless serial Wine.
It then reads the original Japanese PE again and decodes every native
case instruction, resolved COFF field and original external branch.
The native **943-byte after-RET dispatch DATA** is checked independently:
**156 real DIR32 COFF entries** point to actual original and source
instruction boundaries, and the remaining **319/319 original sparse
index bytes** match. None of this DATA counts as callable game CODE.

```bash
scripts/repo-python scripts/verify-fighter-four-directional-c8-f759.py
# F759 four original complete interior cases: 1804 B / 532 x86 /
# 54 physical PE/COFF references, 1540 genuinely matching
# nonfield bytes and 12 not-yet-exact full-parent exits
# Selected original giant compile only. No all-unit cold replay.
```

F759's single full-parent source emits **56,954 CODE bytes**, while
original `00543210` has **58,294 CODE bytes**: **1,340 bytes still
missing** in the incomplete original giant reconstruction, in
addition to genuinely different GPR/CFG bytes and shared-tail
relocations. The next three source placeholders (`CC`, `CD`, `CE`)
have independently bounded original CODE extents **435, 435 and
394 bytes** respectively. Reconstructing them as meaningful
original actions is a promising next task, but those totals cannot
be treated as a proof that this giant will then match: other native
register phases and branch destinations still need physical proof.

The separate 33KB original `004EBDA0` boss was also freshly checked
in F756 at **33,293 CODE / 8,789 original x86 / 682 COFF refs**;
its remaining **137 actual nonfield bytes** in actions
`38D/38E/3E3` are not solved by equivalent source-only branch/fade
syntax rewrites. No massive 970-unit replay or premature whole-giant
promotion occurred. The official authored whole-function ledger stays
**970 exact / 864,961 CODE bytes** (43.82% reviewed, 43.75%
conservative, 34 complete authored functions pending).
