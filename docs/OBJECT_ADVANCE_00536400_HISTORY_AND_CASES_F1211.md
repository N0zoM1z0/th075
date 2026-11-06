# F1211 — native history relay and 22 actual states toward whole 00536400

F1212 continues the same body with native 801–811 and a freshly built
33-state checkpoint. Its [early-state evidence](OBJECT_ADVANCE_00536400_EARLY_STATES_F1212.md)
supersedes this dated checkpoint's selected object and current dimensions.

[`CharacterObjectActions00536400F1211.cpp`](../probes/CharacterObjectActions00536400F1211.cpp)
contains the original history-controlled path and 22 reviewed nondefault states
in one natural C++ body. Its [receiver/history views](../probes/ObjectAdvance536400F1211.hpp)
preserve the observed physical ABI without constructing or embedding incomplete
owners. **The body is unfinished: 44 native states remain unwritten.** Its
current default therefore also receives those unimplemented values. It is
compiler research, not an executable replacement or an accepted exact unit.
All **39,999 original CODE bytes remain pending**.

## Original evidence

R048 independently attributes original `00536400..0054003E` as authored.
The complete 39,999B /10,573-x86 CODE hash is
`823fc631fb60219c6751959fee28d40d0572f9243386e74dfde2a782f730d69c`.
The separately owned 467B DATA contains 67 dense entries and 199 sparse bytes;
its hash is
`2cff9415eed954b39c6d89393ac98ad2f80bd0aea3fc78f27b1c6cf721dc0f68`.
The actual default is `00540033`, epilogue `0054003B`; fourteen following
alignment bytes are excluded. All reads use the pinned Japanese target.

The existing F422 exact constructor at `00536360` is independently reread:
146B, hash `fb0d9bc7c1bb39886ec8ead8ce9d32310ec345b0ebd1a90a894727e5a9999cfe`.
It installs vtable `006599D4`, whose first two entries are `0045B880` animation
binding and this `00536400` callback. The five observed entries hash to
`22e32665db9ce799b9c79c1314431901f11c0b37bc43a1937880b55a8ed5e700`.
The new header describes only the first two virtual slots. Original nominal
names, complete owner layout and allocation extent remain separate unknowns.

A fresh attested, read-only Ghidra export was used as a hypothesis alongside
complete pinned native disassembly. No target bytes or database definitions
were changed. The ordinary 32B `00540220` list-front helper remains
R243-library/excluded; using its observed returned payload address adds no
helper source or CODE credit.

## History-controlled path, before the ordinary action switch

The native 742B /177-instruction prefix first applies the actual opponent and
owner freeze guards. For signed action values below 800, it then:

- Sets owner word `+F12`. Independent mode-1/mode-2 checks at owner `+39D`
  select owner scale `+9C` of 0.5/0.4, call the existing gauge helper with 5/7,
  and copy owner `+3B0` into `+F10`.
- If owner `+F10` or health `+3A0` has expired, restores scale 1, clears
  `+F10`, selects action 810 and exits.
- Otherwise clears current `+8A`, initializes the observed transform,
  scales, alpha 128, RGB 255 and flag `+10=82h`; a nonzero owner countdown
  exits before reading history.
- Reads the front record from owner `+FEC`. An action change restores current
  counter `+80` from record `+0E`; a stage change clears `+7C`. It selects
  the record's action/stage with frame zero, copies both coordinate DWORDs
  and the facing byte, then exits.

The borrowed 16B record window exposes short action/stage, two coordinate
DWORDs, a facing byte and short counter. Natural alignment supplies the byte
before `+0E`; no filler array is declared. The coordinate copies preserve
raw bits rather than converting the DWORD values numerically. Native behavior
contains no empty-list check, so the source adds none.

For actions at least 800, current countdown `+82` instead decrements and exits
when nonzero, then the original action switch is reached.

## Real loop and named-local stack recovery

State 912 has a native loop at `0053E5E7`: its used integer index occupies
**EBP-8**. The history record pointer occupies **EBP-4**, and saved-this is
**EBP-0xC**. Declaring the two genuinely used locals at function scope recovers
all three slots without a dummy local or padding. Declaring the history
pointer in its inner block instead swaps the two named slots; the earlier
failed object is retained.

The source preserves state 912's actual health guard, polar initialization,
hit transition, scale saturation and split condition: stage 2, owner action
752/stage 8 and y below 380. It clears `+74`, sets the burst count from
`RecordedRange(0,3)+3`, and uses the real loop to spawn effect 913 with the
owner's facing and independently randomized coordinates. It then continues
the original movement, bounds checks, stage-3 fade and frame advance. Clearing
`+74` before the burst does not become an invented early return.

## Written states and complete comparison limits

The written states are 800, 817, 820–827, 833, 838, 840, 841, 844, 912,
990, 991, 995, 996, 997 and 998. Their original physical intervals total
7,460B /1,977 x86, in addition to the prefix. **These are interior research
extents, not independently credited functions or exact bytes.**

Four native intervals correspond to existing complete-parent source under
explicit GPR/stack elision: 817/998 from the current 81KB parent and 995/996
from the complete 34KB parent. Field/scalar candidates 990/991 require actual
review: owner `+F2A` becomes `+F14`, and 991 uses divisor **75**, threshold
**150**, rather than the donor's 45/120. State 800's real short increment and
native exit, plus the original fade/continuation order in 840/841, were also
reconciled against the native instructions. No decompiler body or target
instruction array is pasted into the source.

| Whole-function property | Original | Current unfinished source |
| --- | ---: | ---: |
| CODE /x86 | 39,999B /10,573 | 8,101B /2,159 |
| Frame | 0x2A0 | 0x74, still wrong |
| Saved-this /history pointer /burst index | EBP-0xC /-4 /-8 | All three recovered |
| Nondefault states | 66 | 22 written, 44 unwritten |
| Dense entries /sparse bytes | 67 /199 | 23 /199 |
| Whole callable exact | — | **No** |

Fresh serial headless VC7.1 builds use the diagnostic per-unit profile
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`. The source listing and
actual COFF table entries independently agree on all written case entries
and the default. Every written interval and the prefix agree in mnemonic
sequence and the diagnostic operand shape, including actual helper targets,
field offsets, conditional destinations and actual COFF constant payload bits.
That diagnostic **elides GPR roles and negative stack displacements**; it does
not establish physical equality, original constant relocation destinations or
an accepted source comparison.

The prefix additionally has **zero raw GPR and EBP-operand differences**;
its one width difference is the incomplete frame allocation. State 800's
215 instructions have zero raw GPR, EBP or width differences. Many other
written states retain real GPR/stack/width differences in this incomplete
context. Function-wide physical relocations and unmasked equality must be
reviewed after all missing game logic is present. No canonical unit is added
and no acceptance replay is claimed.

## F1210 investigation retained without adoption

The existing complete 34KB `005EB520` parent remains unchanged. Replacing its
two state-997 integer conversion temporaries with used named health locals
keeps the instruction count but wrongly moves saved-this to EBP-0xC, creates
3,162 EBP mismatches and retains all 135 GPR differences. That candidate is
rejected; it does not justify adding inert locals.

A refined positive-witness scan covers eleven existing native methods and
records 1,987 direct saved-this member accesses, correctly invalidating full
register aliases after partial-register writes. It does not provide a `+0C`
witness within that bounded scope, so a complete leading object layout is
still unproved. No arbitrary member or padding is introduced to bridge it.
The initial weaker scan is retained but superseded by the refined receipt.

A method-body inventory found only placeholder-bearing candidates among its
543 records for the other fourteen giants. Its corrected `-v2` receipt counts
actual `g_FighterProbeMarker` stores; the old word-only `marker` count was
insufficient. Name/size/brace heuristics still do not prove that all possible
complete source is absent. All existing complete live parents are preserved.

## Evidence and continuation

`.analysis/f1211-object-536400-recovery/` retains full pinned native exports,
Ghidra export/log, owner/vtable/history inputs, bounded family-homology
receipts, original and corrected source snapshots, every fresh OBJ/PDB/log/
listing, `diagnose-source.py`, and selected **`current.obj`** /`current.asm`,
`current-source-diagnostic.json` and `verified-summary.json` with hashes.
F1210's temporary experiment, refined witness tool/JSON and corrected method
inventory remain under `.analysis/f1210-object-5eb520-native-temporaries/`.

Continue the missing states from the original native intervals, particularly
801–811 and the remaining 900-series behavior. The selected receipt lists all
44 missing values. Keep the two real locals, the complete history path and
all already reviewed state behavior; add no marker bodies to force the dense
table or artificial temporaries to force the frame. Finish the entire callable
before registering a match unit. All original CODE remains in the denominator;
origins and accepted inputs are unchanged. Only changed research translation units were
built; no full CI, corpus replay, origin retest or per-function test is added.
