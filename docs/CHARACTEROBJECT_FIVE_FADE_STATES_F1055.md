# F1055 — Five original fade actions, real x87 order, downstream 0x345 GPR restoration

Pinned Japanese TH075 v1.11 has one independently authored
CharacterObject `Advance` at `0050A580`: **81,539 original callable
CODE B /17,435 x86**, plus **567 separate afterRET DATA B**. This
single giant remains NONEXACT. The source still has unreconstructed
marker states and a small generated stack frame; do **not** claim
separately callable CODE for its switch case interiors.

Independently reading the actual original native PE found five
physically different game fade handlers, each **252 native CODE B /
57 x86 /five genuine physical COFF call/global targets**:

| Native action | Actual Japanese PE interval |
| --- | --- |
| `0x33C` | `0050F9CE..0050FACA` |
| `0x33E` | `0051023E..0051033A` |
| `0x340` | `00510AAE..00510BAA` |
| `0x342` | `0051131E..0051141A` |
| `0x344` | `00511B8E..00511C8A` |

Each genuine original case initializes three real motion arguments
through `0040FBB0` on animation stage/frame `(0,0)`, sets both real
actor scale floats `+0x1C`/`+0x20` to 1.0 and four opacity bytes
`+0x11..+0x14` to `0xFF`, scales both floats by the original native
`006598A4` multiplier, lowers one actually unsigned alpha byte by 20
with a clamp to zero, and uses original `0040FA30` getter and
`0045B830` completion handler. The five physical cases are emitted
separately from the one original-shaped switch; a shared C++ include
only expresses the repeated original logic. No switch labels or
independent callable prototypes are invented.

## Original physical x87 versus apparently equivalent C++

An initial genuine whole-parent C++ experiment using the natural
`SELF_FIELD(float,0x1C) *= g_...` expression emitted the original
57 instructions but loaded the float **global first** and then
multiplied by the receiver field. The genuine original PE instead
emits `FLD [actor+0x1C]` then `FMUL [006598A4]` (and similarly for
+0x20). These differ in x87 operation/load order even when the
real-number formula is algebraically the same. The original-width
physical PE fields and x87 instructions cannot be silently called
equal.

Writing the actual multiplication as the **explicit original
left-hand field value first** `SELF_FIELD(float,0x1C) =
SELF_FIELD(float,0x1C) * g_...` restores the authentic `FLD`/`FMUL`
operand roles. The selected C++ has genuine gameplay, no padding,
manual assembly, forced registers, separate case objects or target
byte grafting.

`verify-characterobject-five-fades-f1055.py` freshly compiles the
**entire one-switch parent** under pinned ordinary VC7.1, reads the
original **whole** 81KB code and the original afterRET 567B data from
the verified PE, checks all 92 native DIR32 case-label equivalence
partitions and 199 original literal sparse indices, and independently
maps all 25 external source COFF fields at original x86 instruction
ordinal and field byte position to the actual PE call/global target.
It measures complete 57-instruction native case extents, not cropped
functions.

| Game state | Native mnemonic | Native instruction widths | Native GPR roles | Physical PE fields |
| --- | ---: | ---: | ---: | ---: |
| `0x33C` | 57/57 | 37/57 | 17/57 | 5/5 |
| `0x33E` | 57/57 | 37/57 | **57/57** | 5/5 |
| `0x340` | 57/57 | 37/57 | 17/57 | 5/5 |
| `0x342` | 57/57 | 37/57 | 17/57 | 5/5 |
| `0x344` | 57/57 | 37/57 | **57/57** | 5/5 |
| **Five real original fade state interiors** | **285/285** | 185/285 | 165/285 | **25/25** |

The remaining 20 width errors per fade source are exactly the
original giant `EBP-0xAC` actor receiver versus the incomplete
partial-parent `EBP-0xC`, **3 bytes each**. The current source
emits **192B** for each 252B native original case; it is not a
machine-byte exact original state.

Restoring these five real fade phases also changes the compiler's
following action `0x345` GPR allocation from **13/35 to 35/35**.
Earlier `0x33C/0x340/0x342` register differences persist, likely
because their interleaved 1,908B original game action handlers
(`0x33B/0x33D/0x33F/0x341/0x343`) are still synthetic markers.
They are not “fixed” with fake local values.

The complete tracked **partial** parent now compiles to
**5,258 CODE B /1,325 x86** with original-shape 567B afterRET DATA.
Across **17 recovered native game state interiors**, it has
**5,167 original native CODE B /1,131 original x86** represented by
**3,990 emitted inner C++ CODE B**. All **1,131/1,131 original
mnemonics** and **87/87 physical original external targets** are
verified, but only **1,011/1,131 original GPR roles** match.
The true whole original 81KB remains unaccepted and not exact.

Bounded only-to-this-parent reproduction:

    scripts/repo-python scripts/verify-characterobject-five-fades-f1055.py
    scripts/repo-python scripts/verify-characterobject-multi-state-f1047.py

A historical five-case compound-operator negative `.inc` and
both complete VC7.1 compile logs/OBJ/PDB are under ignored
`.analysis/f1055-object-fade/`. Current full-original PE receipts
and normal generated parent are under `.analysis/f1055-five-fade-native/`.
No full 979-unit cold replay or newly accepted original bytes.
