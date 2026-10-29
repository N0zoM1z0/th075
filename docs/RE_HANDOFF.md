# TH075 — CURRENT reconstruction agent handoff

**Maintained 2026-10-30, after F691; earlier frozen handoffs are archived.**
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
dense dispatch shape. F598–F681 compiler-backed original research
proves **597 context-strict original *internal action case bodies* /
162,036 original native internal CODE bytes**. These do **NOT** mean
597 additional independently callable exact functions or credited
whole function bytes; each parent remains nonexact. Case interior
source must always be compiled in the **fresh complete original
parent C++ translation unit** and its preceding cases + entire jump
DATA rechecked. [Full original dispatch fingerprint JSON](../config/fighter-boss-dispatch-fingerprints.json),
[original fighter family dispatch](FIGHTER_BOSS_FAMILY_DISPATCH.md).

**Latest strict path:** native `00543210` has **29 source-context
strict original native case bodies /2,409 genuine x86 /8,334
original internal CODE bytes /222 real typed fields** in a **fresh
complete original-shaped VC7.1 C++ parent**. F681 newly makes
physical terminal `0x31B` strict (**74 x86/248 native B/8 genuine
REL32 call fields**), and the adjacent 31C remains strict
(**63 x86/219 B/7 real fields**) in the same parent. This works
only when BOTH genuine 2F0/2F1 and new **2F8 storm-loop natural
C++ source** are present: isolated 31B previously had 43 GPR
errors and disturbed 31C by 36. True original `2F8` has
**252 native x86/928 original CODE B/23 physical fields**; its
source emits 904 B and retains actual GPR/x87 and genuine EBP
loop/scratch differences, so remains **NONSTRICT**.

The new parent has a real source `this` save at `EBP−0xC` instead
of earlier source `−8`, because the original 2F8's real loop index
occupies compiler `−8` (original physical native index `−0x24`).
F681 independently authenticates the **sole** saved-this store,
all its 2,243 compiler reloads, original `EBP−0x44` saved receiver,
and **only then** presents this role to older verifier helpers.
All other EBP locals/widths remain independently checked; no blind
stack-local offset mask. All previous **28 context-strict native
cases**, genuine 186/18A/18B/258 negative controls and complete
separate **943-byte afterRET switch DATA** remain verified in the
**same new full-parent compile**. No original entire giant is exact.
[F681 original PE/source/receiver-role proof](FIGHTER_STORM_TERMINAL_F681.md).
**Separate F684 full-parent context:** real native action `2F9`
(**381 original x86 /1,367 whole inner CODE B/34 physical PE/COFF
fields**) now has normal C++ for the authentic two kind0x391/392
loop volleys and `00483300`/`__ftol2` angle conversions. It emits
**1,319 B, NONSTRICT** due to 16 authentic wide integer-to-float
EBP local positions (original −0x1D8..−0x1F4, compiled
−0x58..−0x74), eight x87 load/move reorderings and 236 genuine
GPR/x87 register-role discrepancies. That newly compiled full
parent still rechecks 27 previous strict nonterminal cases and
whole afterRET DATA, but real terminal 31B/31C now have 43/36
GPR phase differences. This does **not** invalidate F681's
separately verified context-strict terminal proofs.
[F684 true original 2F9 negative study](FIGHTER_ANGLE_STORM_F684.md).
F676 earlier made 31C strict when 2F0/2F1 were restored; F674
correctly found 31C NONSTRICT in its older different parent context.
[Prior F676 source context proof](FIGHTER_CLOUD_BURST_F676.md).

**Separate F672 original source context:** all five original native
`259/25A/25B/25C/25D` bodies (434 whole x86 /1,469 native CODE B /
42 real zero-addend typed PE fields) now have natural C++ complete
case grammar. Genuine x87 multiplication/load order and original eight-
shot + four single-shot behavior match, but **24 actual original EBP
integer-to-float scratch operands/widths differ**, so all five are
**NONSTRICT**. That alternative full parent rechecks 25 preceding
strict cases and keeps 2BC strict, plus all original afterRET DATA.
[Full F672 source/real EBP negative](FIGHTER_EIGHT_SHOT_AND_FOLLOW_F672.md).
F674's selected strict 2EF source context uses 259–25D placeholders;
F666 independently proved that combining source contexts can change
later register allocation. Never merge these as if a whole 58K
parent were exact.
**F671 next difficult original:** complete physical action258
(**134 authentic x86 /502 real original inner CODE B /12 physical
typed PE/COFF fields**) has a newly compiled ordinary C++
four-projectile source that matches all GPR/x87/CFG roles, 12
real targets and every original source call, but is **NONSTRICT**:
eight true original x87 conversion scratch EBP−0x114/−0x118/−0x11C/
−0x120 operands compile at −0x2C/−0x30/−0x34/−0x38, shortening
source 502→478 B. No fake local padding or strict credit;
all 25 earlier strict cases and afterRET DATA remain correct in
this **same freshly compiled whole parent**.
[Newest F671 complex original negative](FIGHTER_FOUR_SHOT_BARRAGE_F671.md).
F664 earlier added 200/201 (228 x86/779 B/17 fields), and F668
added 252/253/254; no enclosing whole giant is exact.
**Critical F666 context warning:** a second freshly compiled whole-giant
source variant restores *four earlier original* `1FA/1FB/1FE/1FF`
case C++ grammars (562 original x86/1,942 native CODE B/52 real
fields). They remain NONSTRICT from genuine GPR/EBP mismatches. Their
insertion also changes the same following `200/201` register phases
by 67/85 wrong original nonfield GPR roles, despite maintaining all
physical instruction counts, bytes and typed fields. The F664
strict inner-case proof applies **only to its explicitly verified
original-shaped but still partly placeholder parent context**, not a
fully restored historical parent. [F666 controlled full-native
negative and register-cycle proof](FIGHTER_PRECEDING_STAGE_PHASE_F666.md).
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
# NEW alternative full parent: real 2F9 x87/storm-source negative and true terminal GPR regressions:
scripts/repo-python scripts/verify-fighter-angle-storm-f684.py
# Prior complete selected giant: real 2F8 storm negative and strictly matched 31B+31C:
scripts/repo-python scripts/verify-fighter-storm-terminal-f681.py
# Prior 2F0/2F1 negative source and context-strict 31C:
scripts/repo-python scripts/verify-fighter-cloud-burst-f676.py
# Earlier alternate giant: five native 259..25D source/EBP negatives and strict 2BC:
scripts/repo-python scripts/verify-fighter-eight-shot-and-follow-f672.py
# Context-scoped strict 2EF cloud-rain and real 31C negative:
scripts/repo-python scripts/verify-fighter-cloud-rain-f674.py
# Earlier whole giant: strict original full 2BC ground wave:
scripts/repo-python scripts/verify-fighter-ground-wave-f673.py
# Previous full parent: 258 four-shot source, honest EBP negative:
scripts/repo-python scripts/verify-fighter-four-shot-barrage-f671.py
# Previous strict 255/256/257 and 22 preceding case bodies:
scripts/repo-python scripts/verify-fighter-post-counter-f669.py
# Prior selected whole giant: strict 252/253/254 and 19 preceding cases:
scripts/repo-python scripts/verify-fighter-counter-special-f668.py
# Separate alternate whole giant: four native predecessors and GPR-phase negative:
scripts/repo-python scripts/verify-fighter-preceding-stage-controls-f666.py
# Separate selected full-giant parent with strict 200/201 source context:
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
| `0041CE50`, ArchiveCatalog nonvirtual destructor | **171 B**, 51 native x86, 14 PE/COFF refs | Normal **`/GX-`** C++ matches **108/115 nonrelocation bytes**, not full CODE; original filename, resource-delete and index temporaries have wrong EBP slots. F609 19 type/scope probes and later F643 14 used-variable lifetime controls failed; F660's seven additional early filename-lifetime C++ forms yield 108/115 or regress to 102/115. New F682/F683 tested **39 further complete actual original C++ source hypotheses**: 21 resource-named/reference forms emit 177/53 rather than 171/51, one resource cast stays 108/115, 14 genuine filename type/register forms remain 108/115, two filename references regress to 102/115 and one VC7.1 `__restrict` grammar fails. The original EBP resource/delete/filename assignment cycle remains unresolved. [F682/F683 new full-target negative evidence](ARCHIVE_RESOURCE_FILENAME_LIFETIMES_F682_F683.md), [F609 originals](ARCHIVE_DESTRUCTOR_SOURCE_TYPES_F609.md), [F660 earlier negatives](GIANT_REGISTER_AND_ARCHIVE_LIFETIME_NEGATIVES_F659_F660.md). |

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

F595 + F616–F691 research now source-backs **85 distinct
historical origin-unknown entire native functions /1,949 genuine
original CODE bytes**. New F691 proves a substantial whole
**249-byte `0061F125` COM manager cleanup and linked-list unlink**
function from ordinary pinned VC7.1 `/O1` C++: **104 entire original
x86, 249/249 complete linked CODE bytes, five true zero-addend
`DIR32` PE/COFF fields**, authentic two COM `+0xE0` handle calls,
eight-element twin resource release loop using virtual `+8`, three
original imported stdcall targets, and real linked global head
`0068E264` with actual per-node link at `+0xAC`. A natural C++
`while (*cursor && *cursor != this)` list termination restores the
original final seventeen instructions and exact full 249-byte
native extent; earlier semantic but wrong compiler branch forms
emitted 253–257 bytes. Original historical author remains
**unknown**, all 95 origin-unknown entries retain `unknown,review`.
[New F691 entire native source and complete PE/COFF proof](SDK_NATIVE_COM_MANAGER_CLEANUP_F691.md).
F687 earlier proved two complete native COM owner virtual destructors
(122 CODE B/49 x86/five genuine typed fields);
[earlier F687 evidence](SDK_NATIVE_COM_OWNER_DESTRUCTORS_F687.md).
F688 independently isolated source-exception-layout negatives for
original 73-byte `0061A453` derived destructor;
[F688 EH negative](SDK_EH_DERIVED_DESTRUCTOR_NEGATIVE_F688.md).
This cohort earns **zero accepted game-authored whole-function CODE**.

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
scripts/repo-python scripts/verify-sdk-native-com-manager-cleanup-f691.py
scripts/repo-python scripts/verify-sdk-native-com-owner-destructors-f687.py
scripts/repo-python scripts/verify-sdk-native-vtable-destructor-f686.py
scripts/repo-python scripts/verify-sdk-native-helper-leaves-f680.py
scripts/repo-python scripts/verify-sdk-native-bulk-state-ctor-f677.py
scripts/repo-python scripts/verify-sdk-native-state-constructors-f675.py
scripts/repo-python scripts/verify-game-native-scoped-lifetime-f670.py
scripts/repo-python scripts/verify-game-native-forwarder-leaves-f665.py
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
