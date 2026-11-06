# F1237 — native-backed initial source for 0057D580

`probes/CharacterObjectActions0057D580F1237.cpp` writes **32 of 70** actual
nondefault states, the observed entry guards and default, in one C++ body.
It is an **incomplete, NONEXACT research parent**. Unwritten states currently
take its default; it is not an executable replacement. All **43,845 original
CODE bytes remain pending**. Neither an interior diagnostic nor a compatible
helper declaration earns new exact credit.

## Independent original inputs

The supplied Japanese TH075 1.11 executable retains SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Its identity is pinned to the user's archive. R048 independently attributes
0057D580 to authored object policy; source discovery does not supply ownership.

| Native observation | Complete original |
| --- | --- |
| CODE extent /instructions | 0057D580..005880C4; 43,845B /11,694 x86 |
| CODE SHA256 | `b312df96bc1add13a19d592dc61fb5d5a601d47eb8eb897b52392d59ca9c8543` |
| Frame /saved receiver /saved GPR | 0x378 /EBP-0x40 /ESI |
| Default /return epilogue | 005880B8 /005880C0, beginning with POP ESI |
| Owned dense /sparse DATA | 005880C5, 71 entries /005881E1, 198 bytes |
| Complete after-RET DATA | 482B; following nine alignment INT3 excluded |
| DATA SHA256 | `4031611d95cdf4503437a4feea0827a3ce0b3dfab7df95b392f0941583996192` |

The already accepted F422 constructor at 0057D4E0 is freshly read in full:
146B /35 x86, SHA256
`54c9d8cdceecc88a2756f0bcf9e89bf4c62034167663e1274aa1d05c150ea65b`.
It installs vtable 00659C88 and stores the owner at E4. The first five vtable
slots read back as 0045B880, **0057D580**, 0040FC70, 00410350, 00410A00.
These support the borrowed virtual slot-1 receiver declaration. No complete
owner layout is asserted or instantiated. The constructor is unchanged and
was not replayed. Read-only, analysis-disabled Ghidra attestation and the full
decompile are retained; the latter is a hypothesis aid, not pasted source.

## Written behavior and direct diagnostics

Written states are 800–810, 813–815, 818–819, 827–829, 832–833, 841–844,
846, 899, 912, 915 and995–997. Their native physical intervals total
**18,692B /4,965 instructions**. They are not independent acceptance units.

800–802 preserve three distinct original entries and their real reward loops,
0.2f polar acceleration and phase-dependent fade. 813/818/819 instead use two
reward effects, 0.1f acceleration and the 960 height bound. 803/832/833 preserve
the parent-action gates, distinct 0.9f/0.75f decay, velocity integration and
phase retry policy. 804/806 retain separate spawn packets, random ordering,
counter changes, fade thresholds and sound timing. Actual constants correct
807's following Y offset to 110, 814's to 125, 841's to 40 and 806's X-scale
increment to 0.8f.

808 preserves the initial opponent-relative angle with +/-20 clamp, moving
trail, hit-triggered immediate return, eight-effect loop and owner count.
843 changes the clamp to +/-40, reverses the two native service calls and
spawns 842. 810/842 retain different 15/21 phase thresholds, cancellation,
owner/opponent counters and 2/5 angle retry thresholds. Native 842 promotes
two short decrements to integer before truncation; explicit assignment
reproduces its MOVSX/DWORD subtraction, while 810 keeps word decrements.
The native X-addition and final x87 comparison order are recovered naturally
by operand order in the source. 899 and995–997 retain their distinct owner,
follow/fade, health and return behavior, including 997's reset value9.

The selected fresh parent emits **18,839 CODE B /5,012 x86**, frame **0x13C**,
receiver **EBP-0x24**. All 32 written regions have the original instruction
counts, mnemonic sequences and diagnostic operand shapes, including actual
constant bits, field offsets, direct callees and local branch target ordinals.
These comparisons normalize scratch GPRs and unfinished negative stack slots;
raw GPR/EBP/width differences are also retained. This is **not byte equality**.
The original frame, ESI save, complete dispatch and remaining behavior are
still absent. The prefix records its missing PUSH ESI rather than hiding it.

Eight genuine, used source loop indices are now present. Original native
initializations, updates, comparisons and uses identify fifteen slots above
the receiver. The other seven correspond to **812, 816, 817, 822, 825, 830,
834**. Continue those real branches; do not add storage to imitate the frame.

## Reproduction and retained evidence

Seven serial headless VC7.1 builds cover initial, early, controllers, reviewed,
combat, combat-order and late-combat stages. Profile:
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`.
Only this new research translation unit was compiled. Existing accepted
inputs and every other research parent remain unchanged.

`.analysis/f1237-object-57d580-recovery/` retains all native function/state
disassemblies, original constructor/vtable reads, Ghidra output/log, donor
and internal-variant comparisons, all immutable CPP/HPP stages, listings,
build logs, source diagnostics, `selected-native-evidence.json`,
`native-named-index-slots.json` and `verified-summary.json`. Actual OBJ/PDB
files are under `build/probes/f1237-object-57d580/`; private OBJ symlinks
reference them. Current selected stage is **late-combat**.

Selected CPP SHA256:
`370abfb547a4327eded5e0b997f14169d47b5056082e52ba631fe0ad31a916b0`.
Selected OBJ SHA256:
`37a00c17f72922c6a6197b96df503eadaf19378b30c815a661e11edc75891344`.
Private `diagnose-source.py STEM` is diagnostic only. No canonical unit or
ledger is changed. Full native comparison and affected-unit canonical cold
replay remain required after all states and remaining machine differences
are recovered. No full CI, corpus replay, origin retest or new test was run.

The preceding 005A1600 call-contract review also preserves fresh complete
native helper reads under `.analysis/f1237-object-5a1600-call-boundary/`.
No evidence justifies an ABI change there; its F1236 parent remains intact.
