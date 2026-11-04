# F1064 — Four-shot original 0x335 gameplay and its real 676B native case

The pinned Japanese TH075 1.11 original game contains **one**
`CharacterObject::Advance` at `0050A580` with **81,539 original
callable CODE B /17,435 native x86**, plus 567 separately owned
original afterRET switch DATA bytes. The C++ source is a still
**NONEXACT, partial original-shaped whole-parent probe** with many
unrecovered marker handlers. No original switch case is an independently
callable exact game function, regardless of local mnemonic matching.

Independent fresh Japanese PE disassembly gives original state
`0x335` at **0050E274..0050E518**, **676 original CODE B /149
actual native x86**, previously only a synthetic marker. Its real
C++ gameplay was reconstructed into the *same* current parent:

- Four original x87 arena-bound comparisons of real actor X/Y at
  +0x44/+0x48 against the four physical original float globals
  `0065925C/00659258/006583B4/00658374`. The genuine invalid
  branch calls `0045B830` and returns.
- For original parent action in **(0x31,0x96)** and the owned actor's
  animation stage below 7, calls real `0045B830`, emits a genuine
  **four-shot** loop of original `0x3E4` objects through parent
  `00453A70` and conditionally resets its original +0xEFA timer
  and emits original `0x3E3`.
- Tests authentic +0x7C actor status 5 and performs the real cleanup;
  in stage/frame (0,0) calls native `0040FBB0`, initializes actual
  action WORD +0x80, current +0x7C, two scale floats and four opacity
  bytes, and sets actual borrowed +0x50/+0x54 motion to 10/5.
- Advances original signed-facing X and native Y motion, then calls
  real `0040FA30` getter and potential `0045B830` completion.

No dummy stack allocation, inline assembler, patched target instruction
bytes, fabricated sprite actions or forced GPR variables were used.
The original four bounds, real loop, physical owner pointer and
native helper calls are represented by actual C++ game control flow.

## Independent native PE proof of a whole-compiled partial parent

Tracked `verify-characterobject-native-335-f1064.py` compiles the
**entire** partial C++ parent with the original pinned VC7.1 flags.
It SHA-checks the entire original **81,539B** CODE extent and all
original 567B afterRET DATA, verifies the actual original **92-entry
DIR32** jump equality partition and **199 literal sparse-map bytes**,
then uses the original `0x335` sparse lookup and physical native
handler endpoints. Every actual source COFF nonlocal relocation is
matched against the real original x86 instruction ordinal, PE field
byte address, typed REL32 call or DIR32 float field and genuine PE-
derived destination, not just a source function name.

| Genuine original `0x335` | Selected C++ source |
| --- | ---: |
| Original native CODE /x86 | 676B /149 |
| Natural compiled interior CODE /x86 | 536B /149 |
| Original ordered x86 mnemonic matches | **149/149** |
| Original GPR-role matches | **57/149** |
| Original x86 width matches | **103/149** |
| Original physically correct call/global fields | **12/12** (8 REL32/4 DIR32) |
| Following six real neighboring states' original GPR roles | **all preserved** |

The original giant uses native `ESP 0x3A0` frame and saved receiver
`EBP-0xAC`. The current incomplete partial-parent source uses
`ESP 0xC4`, saved receiver `EBP-0x3C` and a shallower genuine
four-shot loop temporary. The physical stack-width and native
conditional branch geometry therefore remain different. Crucially,
**92 of 149 GPR roles are still wrong** in this source case.
The preceding `0x333` and `0x334` are both still marker-only despite
original game bodies of about 1.2KB and 249 x86 each; restoring
their *actual* original behavior is a next research opportunity to
investigate this GPR phase. It is not proven that those states alone
will repair the current register allocation.

Restoring the real `0x335` does **not** break original GPR roles in
following `0x337/338/339/33A/33B/345` whole-source cases, or any of
the other previously recovered original case mnemonic streams.
The one affected C++ parent and its actual original PE targets were
recompiled and measured by F1064, F1062, F1059, F1057, F1055,
F1051 and F1047 scoped verification, without any all-exact unit replay.

**Current selected partial source:** **14,970 generated CODE B /3,910
x86**, plus original afterRET 567 DATA B. It now represents **26
original native game-state interiors**, totaling **17,430 original
state CODE B /3,734 original x86 mnemonic ordinals**, with
**3,734/3,734 correct ordered x86 mnemonics** and **3,642/3,734
correct native GPR roles** (all 92 role mismatches are 0x335), and
**304/304 independently original physically correct external PE
call/global fields**. The source's emitted restored interior case
CODE B total **13,834B**, not 17,430 original bytes, because
native original wide stack and branch instruction widths remain
nonexact. The genuine original 81KB full callable still contains
numerous unimplemented original states and **earns zero new whole
exact CODE credit** from this work.

Reproduce only this affected full partial boss source and adjacent
original-native checks, not the 979-unit exact corpus:

    scripts/repo-python scripts/verify-characterobject-native-335-f1064.py
    scripts/repo-python scripts/verify-characterobject-native-338-339-f1062.py
    scripts/repo-python scripts/verify-characterobject-five-long-actions-f1057.py
    scripts/repo-python scripts/verify-characterobject-multi-state-f1047.py

Complete ordinary VC7.1 C++/COFF/PDB/compiler logs and real original
PE receipt retained under ignored `.analysis/f1064-original-335-proof/`.
The initial natural C++ trial is under `.analysis/f1064-object335/`.
No byte patch, original executable mutation, separate inner callable
promotion, register forcing or all-979-function cold replay.
