# F737 — two complete original 194/195 grounded eight-shot actions; authentic cross-case register phase gain

**New native-grounded natural C++ GAME source in the original full giant; the enclosing function remains NONEXACT.**
Target is the user-provided Japanese TH075 v1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The authored fighter at `00543210` consists of **58,294 original CODE B**
and **943 additional original post-RET switch DATA B**. Internal handlers
are not independent original functions and cannot be adopted as exact CODE.

## Entire original physical case source and original typed fields

| Actual original handler | Full native PE CODE interval | Original CODE/x86 | New full-parent VC7.1 CODE/x86 | Physical typed PE/COFF fields |
| --- | --- | ---: | ---: | ---: |
| `0x194` | `0054967C`–`005497CB` | **335 B/92 x86** | **329 B/92 x86** | **7/7** |
| `0x195` | `005497CB`–`0054991A` | **335 B/92 x86** | **329 B/92 x86** | **7/7** |
| **Both entire source-backed interiors** | | **670 B/184 original x86** | **658 B/184 original mnemonics** | **14/14** |

Tracked original-shaped normal C++ [`FighterEightGroundF737.inc`](../probes/FighterEightGroundF737.inc)
implements each whole native game action, preserving differences
between them: actual stage-zero `+0x7C=1`, Y speed `+0x54` damping by
`+0x5C`, original physical ground test of `(+0x48)+(+0x54)` against
`[0065782C]`, zeroing all three original speed/ground members,
original stage-four `PrepareActionAt453D40(0)` and actual velocity
`-4.0f/9.0f/0.65f`, original `+0x314` angle `0.0f` for 194 but
`-30.0f` for 195, `StartAnimationAt46D000(200)`, eight real
`0x324` projectile calls using signed direction coefficient **35**
or **27**, true original Y global `[00659A24]` or `[00659A20]`,
and genuine `GetNativeActionAt40FA30` completion to action **9**.
There is no inert stack field, cropped native body or raw x86 patch.

Fresh VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` compiled both
bodies in the **same entire original-shaped 58KB parent**. Each
source emits **exactly all 92 original ordered x86 mnemonics** and
all **7 physical native PE/COFF fields at their original x86 owner
ordinals**, matching real PE destination, source symbol, `REL32`
or `DIR32` kind and zero addend. Original x86 ordinals 20–23 and
the source match the authentic `FCOMP [0065782C]; FNSTSW AX;
TEST AH,0x41; JP` floating threshold predicate. They also match
all true signed-facing `IMUL` magnitudes, original calls and
case tail. Both whole cases have **zero normalized nonfield
GPR/CFG differences**. This is NOT byte-exact original CODE.

Each original case uses **two 6-byte deep EBP integer-to-x87
`MOV/FILD` instructions** at x86 ordinals 71/72; current source
uses two **3-byte** equivalents, accounting for all **6 missing
emitted CODE bytes per case**. The actual slots remain wrong:

| Original real slot | Original native 194/195 | Generated 194/195 |
| --- | --- | --- |
| Used eight-shot index | `EBP−0x1C/−0x20` | `EBP−0x14/−0x18` |
| Used signed facing-to-float scratch | `EBP−0x9C/−0xA0` | `EBP−0x6C/−0x70` |
| Saved `this` across the *whole* 58KB parent | `EBP−0x44` | **`EBP−0x3C`** |

All actual original and compiled scratch slots and two width
negatives are individually asserted. The deeper source this slot
arose naturally from used gameplay locals, not artificial filler;
there are still **two real DWORD stack slots** between compiler
and original this allocation, and the whole giant is NONEXACT.

## Major independently proven cross-case compiler-phase gain

F734 had recovered real source actions 190/191/192, but still
kept 194/195 as marker placeholders. Replacing them with two
actual complete grounded eight-shot actions adds two genuine
loop indices and two actual integer-to-x87 conversions in the
natural VC7.1 source. This *changes the native CODE geometry of
several previously recovered cases in the SAME newly built parent*:

| Original whole physical internal case(s) | Prior source context | New real 194/195 context |
| --- | --- | --- |
| **1F5**, original **538 B/149 x86/18 original fields** | 506 emitted B, 10 true x86 width differences, 71 GPR differences | **538 emitted B**, **all 149 native mnemonic AND instruction widths**, **0 normalized GPR differences**; original deep EBP values still wrong |
| **1FA/1FB/1FE/1FF** | 50/111/96/96 normalized GPR differences | **0/0/0/0** |
| **200/201** | 67/85 GPR differences | **0/0** |
| **2D0/2D1**, original 416B/120 each | 60/60 GPR differences | **0/0** |
| **2DD/2DE** | 80/0 GPR differences | **0/0** |
| **2EF** | 0 | **0**, still native-shaped in sampled full context |

In all **13 selected previous real native action interiors**,
`verify-fighter-eight-ground-f737.py` checks original full PE
case boundaries, entire 149/82/etc native x86 counts, generated
source physical size, every original physical typed COFF field
*count*, actual ordered mnemonics and zero normalized nonfield
GPR errors, with width equality for all cases except previously
nonexact `1F4`. Earlier `1F4` still has its **ten true 6B/2B or
6B/3B width differences**, and `1F5` matches width but retains
native-vs-source deep stack offsets. None of this establishes
complete byte-equality for any inner case or for the whole giant.
No historical 27-strict counts are inherited without fresh checks.

## Original full DATA and reproducibility

[`scripts/verify-fighter-eight-ground-f737.py`](../scripts/verify-fighter-eight-ground-f737.py)
regenerates the giant from all tracked source fragments, compiles
only **one original-shaped 58KB parent**, verifies the two new
complete native PE actions and their 14 typed fields, reruns the
three earlier entire 190/191/192 physical checks with the actual
new source scratch shift, verifies the 13 selected previous
original physical case contexts, and rechecks the complete **943-B
original after-RET dispatch DATA**. All **156 original/source
`DIR32` switch relocations** resolve to real instruction starts
in the original PE and current compiled parent, and all remaining
**319/319 original sparse bytes are identical**. Source DATA is
independent of original CODE credit.

The older F734 checker now accepts **optional** independently
attested following genuine 194 source and a genuine +8 byte
signed-int x87 scratch offset shift; the older source-context
default remains unchanged and is separately regression tested.

```bash
scripts/repo-python scripts/verify-fighter-eight-ground-f737.py
scripts/repo-python scripts/verify-fighter-eight-round-f734.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Actual compiled parent C++/OBJ/PDB, compiler logs and native PE/COFF
receipts are preserved in the ignored local
`.analysis/f737-fighter-eight-ground/`; tracked natural source and
portable complete original parent verifier are in Git.
**No new independent original whole function has been accepted**;
formal reviewed authored coverage remains **955 exact complete
functions /863,163 original CODE B (43.73%)**. No mass cold replay.
