# TH075 — CURRENT reconstruction agent handoff

**Maintained 2026-10-30, after F664; earlier frozen handoffs are archived.**
This is the **active queue and verified ledger snapshot**. Old F-series
milestone descriptions are *not current status*: the long previous
[F598–F652 handoff was archived intact](history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md),
with its Markdown links adjusted for its new directory. The older
[F540–F596 narrative](history/RE_HANDOFF_F540_THROUGH_F596.md) and
[chronological knowledge base](KNOWLEDGE_BASE.md) are evidence, not a
reason to undo later exact adoptions. Original pinned native PE and
**live manifests outrank every historical sentence**.

## 1. Live truth, targets, immediate preflight

| Item | Authoritative snapshot; recheck live manifests on every new session |
| --- | --- |
| Original game | User-supplied Japanese TH075 ver1.11 `resources/th075.exe`, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`; **never** localized `th075c.exe` |
| Exact authored whole functions | **943 functions / 943 exact units**, **862,726 original CODE bytes** |
| Reviewed authored bytes | **43.71%** of **1,973,704** original CODE bytes; conservatively **43.64%** with unknown origins included |
| Provisional ledger | **4,351** candidate original functions; **95** still origin-unknown with 3,420 CODE bytes; these have **no authored credit** |
| Unfinished author-owned functions | **25 complete functions**: **22 large fighter bosses**, **1,102,055 CODE bytes** of original whole CODE, plus **three** other whole functions (2,987 B, 248 B, 171 B) |
| Separated after-RET giant switch DATA | **16,123 bytes** across the 22 giants; DATA is not authored CODE credit |
| Goal | 98% authored CODE coverage is **not** achieved; no external Oracle acceptance for new work |

```bash
git status --short --branch
git log -6 --oneline
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/audit-active-handoff.py
scripts/repo-python scripts/ghidra.py check
```

Inspect **all** existing dirty work: the user reports there are no other
worker sessions. Continue it; never skip/reset unrecognized changes or
assume another agent owns them. Use real original PE evidence, pinned
VC7.1, natural C++ and serial headless compilation. Every substantial
verified improvement must be committed as `gpt-web: ...`. **Never cold
replay all 943 exact units**; replay only newly accepted or affected
units and their dependencies. No manual machine-code patches, fake
locals or fabricated class layouts to force a match.

## 2. The main giant `004EBDA0`: solve remaining true native registers

Native `CharacterObject::Advance`-like whole original is **33,293 CODE
bytes + 438 separately owned after-RET DATA bytes**, 8,789 original x86
instructions. Normal VC7.1 C++ source
[`CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
reproduces **8,789/8,789 x86 mnemonic order, starts and widths**, all
**682 genuine typed PE/COFF fields** (622 CODE + 60 DATA) and all 198
compressed switch-index bytes. Current original whole comparison is
**30,866/31,003 nonrelocation bytes**, with **137 truly mismatched
nonrelocation bytes across 133 x86 instructions**: the whole function
is **NONEXACT**, no entire CODE acceptance.

The actual differences are **compiler register ownership/cycles**, not
missing instructions: native `0x38D` has 45 GPR role differences (from
ordinal 91, `004F344C`); `0x38E` has 64 (cycle persists from 38D),
and `0x3E3` has 24 (only first ~30 ordinals). F596 corrected prior
x87 collision ordering; later F635 25 meaningful whole-function C++
type/ownership trials **did not** resolve 137 bytes. Read
[the F596 physical original native evidence](CHARACTEROBJECT_NATIVE_COLLISION_ORDER_F596.md),
[F635 controlled negative C++ alternatives](CHARACTEROBJECT_TYPED_MEMBER_CONTROLS_F635.md)
and native target, rather than trusting older F593 figures such as
“155 remaining bytes”. F659 independently recompiled 14 new
stage-3/stage-4 C++ grammar hypotheses against the **entire**
original 33KB function: 12 remained **137 wrong nonfield bytes**,
and two `+=` variants regressed to **141 plus native x87 geometry
errors**. [New F659/F660 original source negatives](GIANT_REGISTER_AND_ARCHIVE_LIFETIME_NEGATIVES_F659_F660.md).
Focus on real source scope/lifetime and original register phase,
not additional fake fields.

```bash
scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py
# A *single* F635 rejected grammar control (not a whole-corpus replay):
scripts/repo-python scripts/verify-characterobject-typed-member-f635.py --case 38d-zero-velocity-as-bits
```

## 3. The other giant fighter functions: actual case gains vs whole exactness

The 22 original giant CODE owners remain authored NONEXACT. The main
case-source subcohort has **11 real multi-switch giant fighters**,
with real per-actor native differences and a full afterRET sparse/
dense dispatch shape. F598–F664 compiler-backed original research
proves **587 strict original *internal action case bodies* /
158,673 original native internal CODE bytes**. These do **NOT** mean
587 additional independently callable exact functions or credited
whole function bytes; each parent remains nonexact. Case interior
source must always be compiled in the **fresh complete original
parent C++ translation unit** and its preceding cases + entire jump
DATA rechecked. [Full original dispatch fingerprint JSON](../config/fighter-boss-dispatch-fingerprints.json),
[original fighter family dispatch](FIGHTER_BOSS_FAMILY_DISPATCH.md).

**Latest strict path:** native `00543210` has **19 strictly matched
native case interiors /1,437 genuine x86 /4,971 original internal
CODE bytes /132 real typed PE/COFF fields**, in one newly compiled
entire parent. F664 newly adds **two full original `0x200/0x201`
case interiors** (**228 native x86 /779 original bytes /17 genuine
physical original PE/COFF fields**) and rechecks all prior cases
and after-RET DATA in the same new source object.
[Newest F664 authentic native proof](FIGHTER_SPECIAL_STAGE_F664.md).
Earlier F657 added **three original full `0x187/0x188/0x189` native case
interiors** (**212 x86/767 original B/19 original physical fields**),
including authentic 0.6f falling states and the stage7/9 collision
and auxiliary action behavior. Its preceding real case `0x186` is
**NONSTRICT despite all 82 x86 and 8 typed fields**: two true original
`EBP−0x84` int-to-float scratch refs compile at `EBP−0x20`, for
**284 compiler bytes versus 290 original case bytes**. We additionally
check raw EBP roles independently, rather than trusting the broad
historical register-slot normalizer. Do not promote or pad `0x186`.
[Newest F657 original proof](FIGHTER_MOTION_CONTINUATION_F657.md).

The **14 consecutive strict earlier native cases** are `CF/D0/D1/D2/
12C/12D/12E/12F/130/131/133/134/135/136` (997 original x86/
3,425 original B/96 real typed fields). F656 last added five of
these (434 x86/1,484 B/36 fields), preserving the full after-RET
dispatch. `0x132` is the same actual default handler as `0x50`, not
a separately owned native case. [Earlier F656 original proof](FIGHTER_LATE_STAGES_F656.md).
F654 added `12F/130`, F653 added `12C/12D/12E`, F651/F652 added
D1/D2 and CF/D0 were earlier strict. F661 additionally reconstructs
native **18A/18B complete source-backed case C++ interiors**
(**170 genuine x86, 615 original CODE B, 13 real PE/COFF fields**),
but both remain **NONSTRICT**: their original meaningful x87 scratch
EBP−0x88/−0x8C occurs at compiler EBP−0x24/−0x28, shortening each
case by six bytes. All 17 previous strictly backed cases and whole
after-RET DATA are rechecked in the **same new C++ parent**.
[Latest 18A/18B source and authentic native negative proof](FIGHTER_MOTION_SHOTS_F661.md).
The original 58K whole parent is still NONEXACT; `D2→12C`
has no separate D3 physical handler.
The native original D2 float drag occurs **outside** stage-zero
initialization, essential for CFG and x87 role order. Eight other
D1/D2 owner versions still have **28 or 42–52 genuine register/CFG
role differences**; native `005AEEC0` and `00564BE0` have no separate
D1/D2 handlers. Do not copy this actor-specific victory to all 11.
[Selected strict full giant and field proof](FIGHTER_RESOURCE_SHOTS_F651_F652.md).

**Latest difficult negative:** true native case `0xCC` inside giant
`005AEEC0` has **128 x86/435 B** and original wide `00564BE0`
**126 x86/542 B**. Normal C++ reconstructs entire case x86 starts,
mnemonics and widths and all **11 true typed PE/COFF call/global
fields per case** (39 real wide saved EBP−0x88 receiver MOVs in the
wide owner) but **80/78 original non-field GPR/CFG role mismatches**
remain. This is a **NEGATIVE, not two strict cases**. The real
collision constant is **`0xFF`**, not `-1`; native 16-bit stage
increments use prefix `++I16`; native sprite x/y are raw DWORD
bit-pattern pushes. The source's raw parameter ABI is a provisional
**compiler grammar probe**, not proof of historical C++ declaration.
Of 22 attempted C++ variants, **20 compiled whole giant parents and
two postfix-increment variants failed with genuine VC7.1 C2105**.
[Full F649 source/PE negative study](FIGHTER_COMPLEX_STAGE_CC_F649.md).
F646 `0xD0` remains nonstrict in other original actors due to
35/36 GPR register-phase differences and/or preceding-case context;
[the selective F646/F647 strict proof](FIGHTER_FALL_REFLECT_F646_F647.md)
explicitly distinguishes the 3 strict parent contexts.

```bash
# NEW complete selected giant: 200/201 strict, 17 prior strict, three negative:
scripts/repo-python scripts/verify-fighter-special-stage-f664.py
# Earlier selected giant, nonstrict 18A/18B and 17 older strict cases:
scripts/repo-python scripts/verify-fighter-motion-shots-f661.py
# Earlier three strict cases and true original 186 negative:
scripts/repo-python scripts/verify-fighter-motion-continuation-f657.py
# Prior 14 strictly verified real physical native cases:
scripts/repo-python scripts/verify-fighter-late-stages-f656.py
# Prior nine-case native fighter proof still reproducible:
scripts/repo-python scripts/verify-fighter-falling-finish-f654.py
# Previous seven-case original native proof remains independently reproducible:
scripts/repo-python scripts/verify-fighter-falling-recovery-f653.py
# Earlier 4-case historical proof remains independently reproducible:
scripts/repo-python scripts/verify-fighter-resource-shots-f651.py
# Confirm both native whole-case CC negative controls, not acceptance:
scripts/repo-python scripts/verify-fighter-complex-stage-cc-f649.py
# Previous wide-EBP actor strictly rechecked in its own whole source TU:
scripts/repo-python scripts/verify-fighter-motion-restart-f645.py --boss 0x00564BE0
```

**All 22 giant original CODE extents** (none accepted whole; sizes
come from live `config/functions.csv`):

| Native address | CODE bytes | Native address | CODE bytes |
| --- | ---: | --- | ---: |
| `0045DD70` | 60,999 | `00476A40` | 50,915 |
| `00486550` | 50,735 | `0049C8F0` | 46,596 |
| `004AC040` | 82,796 | `004CA6E0` | 42,511 |
| `004D7E70` | 43,601 | `004EBDA0` | 33,293 |
| `004F7130` | 44,211 | `0050A580` | 81,539 |
| `005214B0` | 46,755 | `00536400` | 39,999 |
| `00543210` | 58,294 | `0055AC80` | 28,432 |
| `00564BE0` | 61,872 | `0057D580` | 43,845 |
| `0058AF60` | 49,230 | `005A1600` | 43,599 |
| `005AEEC0` | 71,616 | `005C9CC0` | 43,501 |
| `005D73C0` | 43,282 | `005EB520` | 34,434 |

## 4. The three other NONEXACT authored whole original functions

| Original full native function | Original whole CODE extent | Real remaining blocker and best direct source/PE evidence |
| --- | ---: | --- |
| `00602A60`, GameApplication::Run-like giant WinMain | **2,987 B**, 654 native x86, 123 calls, 60 separate afterRET DATA bytes | F528 C++ produced 2,981 B/654 x86 but wrong real EBP local ownership; F615 30 other complete native C++ source trials failed. [Real WinMain original CFG](WINMAIN_ORIGINAL_CONTROL_FLOW.md), [F615 true local lifetime negatives](WINMAIN_LOCAL_OBJECT_LAYOUT_F615.md). |
| `0043B0B0`, scene/resource virtual destructor | **248 B**, 75 native x86, 12 PE/COFF refs | Normal VC7.1 **`/GX`** source matches **191/200 nonrelocation bytes**, not full CODE, because five original EBP local slot owners differ; F612/F632 many scope/type variants failed. [Actual source/PE lifetime](SCENE_DESTRUCTOR_POINTER_TYPES_F612.md), [F632 honest negative controls](DESTRUCTOR_FREE_ASSIGNMENT_F632.md). |
| `0041CE50`, ArchiveCatalog nonvirtual destructor | **171 B**, 51 native x86, 14 PE/COFF refs | Normal **`/GX-`** C++ matches **108/115 nonrelocation bytes**, not full CODE; original filename, resource-delete and index temporaries have wrong EBP slots. F609 19 type/scope probes and later F643 14 used-variable lifetime controls failed; F660's seven additional genuine early filename-lifetime C++ forms yield 108/115 or regress to 102/115, no correct EBP slots. [F609 originals](ARCHIVE_DESTRUCTOR_SOURCE_TYPES_F609.md), [F660 new negatives](GIANT_REGISTER_AND_ARCHIVE_LIFETIME_NEGATIVES_F659_F660.md). |

```bash
# Cold-compile ONLY one unchanged tiny author's negative control:
scripts/repo-python scripts/verify-destructor-free-assignment-f632.py --case archive-ptr-in-free-arg
scripts/repo-python scripts/verify-destructor-free-assignment-f632.py --case scene-three-assignment-args
```

Do not declare these full functions exact from matching x86 count,
byte length, COFF-field count, a Ghidra decompile or a temporarily
relocation-masked comparison. **Acceptance requires a complete
original CODE extent including the true epilogue and every original
relocation, and a fresh selected-unit cold replay**.

## 5. Small leaves: whole-byte source evidence ≠ authored attribution

F595 + F616–F658 source experiments now prove **66 distinct
historical origin-unknown complete native function bodies /1,183
original entire machine CODE bytes**. The newest F658 adds **19
complete original 5/8/11/14/16-byte native leaves /181 genuine
CODE bytes /111 x86 instructions**, all directly original-byte
identical without relocation masks, through one small natural C++
VC7.1 TU. Their owners remain `unknown,review`, as do all **95
historical provenance-unknown candidates**. This research earns **zero
accepted authored whole-function CODE**. [Full new native whole-leaf
source and caller proof](GAME_UNATTRIBUTED_SIMPLE_LEAVES_F658.md).

Latest F655 seven **entire original registered native leaves**
(`004138D0`, `004169D0`, `0041F7F0`, `00540280`, `00441FD0`,
`0045B630`, `00409490`) now match **73/73 original linked CODE bytes,
43 entire x86, one physical original REL32** in only one newly compiled
small C++ TU. The native `00409490` wrapper's actual `00409860` callee,
its one real authored caller among three, and all seven true original
PE direct-call graphs are independently checked, but historical source
ownership remains UNKNOWN. [Full native leaf and caller proof](GAME_UNATTRIBUTED_LEAVES_F655.md).
Earlier F650 proves two other true whole leaves `004170B0` (27 bytes,
virtual `__stdcall`) and `004588B0` (43 bytes, conditional CRT free).
[Earlier genuine original F650 proof](GAME_COM_VIRTUAL_RELEASE_F650.md).

```bash
scripts/repo-python scripts/verify-game-unattributed-simple-leaves-f658.py
scripts/repo-python scripts/verify-game-unattributed-leaves-f655.py
scripts/repo-python scripts/verify-game-virtual-release-f650.py
scripts/repo-python scripts/verify-game-float-math-adapters-f644.py
```

**Avoid double-counting** whole origin-unknown functions already
recovered in F595, F616, F618 and later experiments. Never change
`function-origins.csv` or credit a named wrapper based only on the
compiler byte match, a real game call, or a plausible C++ signature.

## 6. Safe workflow, local storage and historical evidence

- Acceptance manifests in `config/match-units.toml` and
  `config/matches.csv` record **whole cold-exact original CODE**;
  `config/functions.csv` and `config/function-origins.csv` define
  native extents and authorship. For *new or affected* accepted units,
  use **`scripts/repo-python scripts/replay-exact-units.py --unit NAME`**;
  never cold replay the full 943-unit registry.
- Keep selected compiler commands serial/headless. With Wine unset
  `DISPLAY`/`WAYLAND_DISPLAY`, set the existing `.analysis/vc71-wine`
  prefix and disable graphical drivers. `scripts/repo-python` is
  required for Python and the hash-pinned x86 decoder. No external
  web, target modification or synthetic assembly is required.
- Historical F598–F652 detail is preserved at
  [the frozen full old handoff](history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md),
  and earlier F540–F596 at
  [the earlier frozen handoff](history/RE_HANDOFF_F540_THROUGH_F596.md).
  See [full ongoing chronological research](KNOWLEDGE_BASE.md),
  [work protocol](RE_WORKFLOW.md) and [native origin review](ORIGIN_PENDING_REVIEW.md).
- A **reversible per-file SHA256-indexed archive of 219 frozen,
  repetitive historical diagnostic JSON snapshots** has reclaimed
  about **244.66 MiB** (including manifest). Standard two-week-horizon
  `git gc` also safely repacked Git objects, reclaiming **≈371.62 MiB**:
  combined **≈616.28 MiB** saved. This checkout stores
  private `.tar.zst` archives and receipt under ignored
  `.analysis/cache-archives/`. The live original PE, `vc71-wine`,
  Ghidra project, current research, native/source/COFF/PDB probes,
  accepted objects and original decompilations are **retained**.
  `scripts/repo-python scripts/archive-redundant-diagnostics.py --verify`
  checks all original members; use its `--restore PATH` if a frozen
  old experiment expects an absent plain JSON path. Full recovery
  procedures: [STORAGE_HYGIENE.md](STORAGE_HYGIENE.md).
- After each substantial result: verify original PE/selected compiler
  object, `validate-tracking.py --require-target`,
  `audit-active-handoff.py`, `update-progress.py --check`,
  `git diff --check`, inspect **all** changes and commit
  **`gpt-web: <specific verified progress>`**. Do not lose ignored
  original evidence, including negative C++ hypotheses.
