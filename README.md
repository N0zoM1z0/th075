# 東方萃夢想 ～ Immaterial and Missing Power

<p align="center"><img src="resources/title-screen.png" width="640" alt="User-supplied TH075 title screen"></p>
<p align="center"><img src="resources/progress.svg" alt="Function reconstruction progress"></p>

**TH075 Japanese v1.11 original x86 complete-function reconstruction** in
ordinary C++, using the actual pinned VC7.1 compiler and comparing full native
PE CODE plus genuine physical COFF relocations. **This is not a complete
playable game or an officially verified distribution rebuild.**

## Current verified snapshot (2026-10-30, F776 exact ledger; F754 maintenance)

| Property | Verified value |
| --- | --- |
| Original | User-supplied Japanese `resources/th075.exe` (v1.11) |
| Size / image base | 2,576,384 bytes / `0x00400000` |
| SHA-256 | `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| MD5 | `21bcb855a39f2170195811e6ad292f18` |
| Provisional native candidates | **4,351** |
| Independently origin-reviewed authored candidates | **1,004** |
| Source-present / whole-byte-exact units | **979 / 979** |
| Accepted original CODE | **868,243** bytes |
| Reviewed authored coverage | **43.99%** of **1,973,704** original bytes |
| Conservative authored coverage | **43.91%**, including **3,420** provenance-pending bytes |
| **Authored not exact** | **25** total: **22** large original state advances (**1,102,055 CODE B**) and **3** small/medium functions (**3,406 CODE B**) |
| Independently unknown origin | **95** candidates; **3,420** CODE B uncredited |

**The 98% authored-byte objective is NOT achieved.** The old claim that
only **25** authored functions remained is incomplete: it counted only
`config/functions.csv.owner=authored` pending rows and missed **11**
other independently authored original candidates. F755, F758, F760, F765, F766, F769, F770, F775, F776, F779 and F780 have now accepted all eleven
of those 11, leaving **0** nonexact; their provenance was already recorded
in `config/function-origins.csv`. The remaining three original non-giant authored functions are independently tracked and still nonexact. The original PE, independent
origin ledger, canonical full-function match records and live status
scripts are more authoritative than historical F-series prose.

Read [the short **current agent handoff**](docs/RE_HANDOFF.md) for the
full 27-function original-authored backlog, native source checkpoints
and targeted compiler commands. The previous 1,289-line handoff is
preserved [as a frozen F653–F753 historical archive](docs/history/RE_HANDOFF_F653_THROUGH_F753_2026-10-30.md),
with all local links updated. The [chronological knowledge base](docs/KNOWLEDGE_BASE.md)
is historical experimental evidence, **not** an active status ledger.

## Work on both large and small original functions

The **22 large whole original state-advance functions** are not accepted
whole exact. The most developed `00543210` fighter has 58,294 native CODE B
and separate 943-B after-RET dispatch DATA; ordinary real C++ restores the
native `this` stack frame `EBP−0x44`, and recent F752 restores original
`05D/05E` direct floating-point `FCOMP` grammar. Nonetheless the whole
function's shared tail and other original GPR/EBP geometry still differ.
Use the [F752 physical evidence](docs/FIGHTER_BORROWED_POSITION_F752.md)
and the new [F759 original four-case whole-parent proof](docs/FIGHTER_C8_CB_WHOLE_PARENT_F759.md),
**not** truncated standalone case credit. F759 naturally restores four real
`C8–CB` native action bodies (1,804 CODE B/532 x86/54 true COFF fields),
fixing the previous 16-byte x87 scratch shift in many downstream actions.
The complete 58KB parent still has **1,340 missing CODE bytes** and is
**not** an accepted exact unit. The `004EBDA0` 33,293-B original state-advance still has 137
real nonfield register-phase byte differences despite correct whole
opcode widths and 682 real typed fields.

New full-parent fighter research [F759](docs/FIGHTER_FOUR_DIRECTIONAL_NATIVE_F759.md)
recovers four complete original C8–CB actions (1,804 original internal
CODE B/532 x86/54 genuine typed relocations), and nine authentic
downstream integer-to-x87 EBP slots. This does **not** credit partial
case CODE: full `00543210` still has a 1,340-B whole-CODE deficit.

The new [F760 whole-parent physical proof](docs/FIGHTER_COMPLEX_STAGE_CC_CE_F760.md)
recovers three more original `CC/CD/CE` actions (1,264 CODE B /371 x86
/31 physical COFF fields); all nonfield bytes outside legitimate parent-tail
JMP displacements match. Eight downstream cases, including `190`, now
match their original nonfield/COFF physical layouts as well. The whole
`00543210` boss still emits only **58,173/58,294 original CODE B**
and remains NONEXACT.

New original entire-parent [F762](docs/FIGHTER_TYPED_RETURN_CROSS_CASE_F762.md)
restores **3,833 native CODE B /1,118 x86 /115 genuine PE/COFF
fields** of full 1F6/1F7/1F8 internal actions, fixing the original
Contact guard and both float member operands. The whole 58KB boss
currently emits 58,277/58,294 B but remains NONEXACT, with **zero
new official accepted whole CODE credit**.

New [F763 full-parent fighter 2DB proof](docs/FIGHTER_APPROACH_NATIVE_F763.md)
recovers another complete original **1,024 CODE B/290 x86/34 PE/COFF
fields** by correcting true floating-point threshold predicates and
borrowed actor X ordering. Whole fighter is still NONEXACT, currently
58,269/58,294 CODE B and uncredited until the entire parent matches.

New complete-parent [F764 fighter 2FA result](docs/FIGHTER_APPROACH_VOLLEY_NATIVE_F764.md)
restores the original **971-B/279-x86/31-COFF opcode geometry** through
six genuine float/comparison corrections. **156 original nonfield GPR
bytes still differ**, and whole `00543210` remains NONEXACT at
58,261/58,294 native CODE B; no partial case is credited.

New whole original R011 SpriteDrawing `0040D790` is **171-B/52-x86/6-field
selected cold exact** after reconstructing real nested RECT lifetimes,
with physical original 147/147 nonrelocated bytes.
[F765 complete PE/COFF proof](docs/SPRITE_OPAQUE_NATIVE_F765.md).

New sibling R011 SpriteDrawing mirrored draw `0040D6B0` is also
**212-B/66-x86/6-PE/COFF-field complete cold exact**, recovering the
real `flip & 1` horizontal RECT reversal with correct VC7.1 lifetime.
[F766 complete original proof](docs/SPRITE_OPAQUE_MIRRORED_F766.md).

The newest full-giant [F767 2F9 angle restoration](docs/FIGHTER_STORM_ANGLE_TYPED_F767.md)
recovers **all 381 original x86 mnemonic/width positions** across
1,367 native CODE B/34 genuine fields and reduces wrong original
nonfield bytes 265→249 using real borrowed actor/opponent X/Y source.
Whole boss still NONEXACT; no internal-case CODE credited.

Further [F768 full original fighter 2F8 research](docs/FIGHTER_STORM_VOLLEY_TYPED_F768.md)
restores all native **928-B/252-x86/23-PE-field opcode/width** positions
through the real integer-first `FILD; FSUBR actorX` source.
Wrong original nonfield operands fall 182→166, still NONEXACT.
The whole giant remains incomplete and no split-case bytes are credited.

A new [F769 original texture slot lifetime](docs/TEXTURE_MANAGER_SLOTS_NATIVE_F769.md)
is **184 native CODE B/56 x86/8 original PE fields cold exact**.
Correcting the physical used VC7 element record from 40 to **44 bytes**
restores the true EH frame and all native offsets without fake locals.

New [F770 original complete shared-texture allocator](docs/TEXTURE_MANAGER_SHARED_NATIVE_F770.md)
**261-B/79-x86/11-PE-field cold exact** restores real third vector
zero and loop index lifetimes `EBP−0x44`/`−0x10`, not dummy locals.

The new [F771 complete fighter 2FB source investigation](docs/FIGHTER_GROUNDED_VOLLEY_TYPED_F771.md)
restores all native **647-B/181-x86/17-PE-field opcode/width** positions
by using the authentic borrowed opponent/actor X and opponent Y float
members. Its real register-byte differences decrease 119→111, but the
entire 58KB boss remains NONEXACT and no case bytes are credited.

New complete original [F775 SpriteDrawing scaled/rotated render](docs/SPRITE_SCALED_NATIVE_F775.md)
is **970-B/257-x86/14-PE-field selected cold exact**, after correcting
true nested quad/RECT lifetimes and three native x87 expression orders.

The paired [F776 original variant sprite function](docs/SPRITE_VARIANT_NATIVE_F776.md)
is **994-B/269-x86/15-native-PE-field whole cold exact**, with the
true x87 JP branch and original ordinary C++ quad rotation path.

The newest [F777 current 58KB fighter register audit](docs/FIGHTER_CURRENT_REGISTER_PHASE_AUDIT_F777.md)
rechecked five **complete original case intervals /68 genuine PE
fields** in one full VC7.1 parent. `0x58` remains native nonfield
strict, but `0x59/0x60/0x61` have 19/98/101 real register bytes
wrong and current `0x63` is **706 original B vs 705 emitted**.
Old F626 strict claims belong to an earlier whole-source context,
not the current giant. No new callable CODE is accepted from F777.

A further [F778 whole-fighter native default reconstruction](docs/FIGHTER_NATIVE_DEFAULT_F778.md)
corrects real game behavior for **239 original switch action IDs**,
recovering a **32-B/10-x86** native conditional action reset.
This reduces the complete `00543210` source shortfall from 33 to
**11 original CODE B**, but four genuine default GPR bytes and
other whole-game registers remain NONEXACT; no split-case credit.

The **5 unmatched small/medium authored originals** include SpriteDrawing
(2), and WinMain/Scene/Archive (3).
They are fully enumerated in the [active handoff](docs/RE_HANDOFF.md).
For example `0040CA20` has real 92-B/34-x86 projected-quad source but
still differs in the original used local-copy stack frame; do not call
that source exact. Recently accepted complete original AudioStream
constructor `004071C0` is already **161-B cold exact** with its 18
real COFF fields and separately verified EH handler/unwind data,
which is not double-counted ([F753](docs/AUDIO_STREAM_CLIENT_ACQUIRE_F753.md)).
The paired audio client release/destructor `00407270` is now **292-B
whole-function cold exact**, with 24 authentic physical relocations
([F755](docs/AUDIO_STREAM_CLIENT_RELEASE_F755.md)). The original
`00407A50` audio file queue is now **289-B/77-x86/26-reloc cold exact**
([F758](docs/AUDIO_QUEUE_FILE_F758.md)). The adjacent archive-entry
audio queue `00407B80` is now **283-B/76-x86/27-COFF cold exact**
([F760](docs/AUDIO_QUEUE_ARCHIVE_ENTRY_F760.md)).

## Begin a safe reconstruction session

Read [AGENTS.md](AGENTS.md), [the reconstruction workflow](docs/RE_WORKFLOW.md)
and [the active handoff](docs/RE_HANDOFF.md). Inspect **all** dirty
tracked and ignored research first: one worker owns the worktree.
Use only the pinned original `th075.exe`, **not** `th075c.exe`;
compile serially with pinned VC7.1. Do **not** run an all-unit cold
replay; rerun only the newly added or affected complete source unit.

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/audit-active-handoff.py
scripts/repo-python scripts/ghidra.py check

# An accepted new/affected complete game function ONLY:
scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME
```

Each accepted whole function must preserve complete original control flow,
true native ABI, all COFF relocation owners and independent authored
provenance. Valid compiler source has **no** fake locals, alignment hacks,
assembly patches, truncated game bodies or guessed origin attribution.
Historical original class names and whole object layouts remain provisional.
Commit verified substantial progress locally as **`gpt-web: ...`**;
no push is assumed.

## Storage, historical evidence and recovery

Previous generated diagnostic archives are **ignored and local**, not
stored in Git. Their contents are original-SHA256-verifiable and can be
restored individually. The latest maintenance archived **1,931 old
f133–f166 generated giant ASM/COD/LOG traces**, reclaiming
**86,614,259 bytes** without deleting original source, JSON receipts,
COFF objects, compiler environment, Ghidra project or accepted units.
See [storage hygiene and exact restoration commands](docs/STORAGE_HYGIENE.md)
and `scripts/archive-frozen-giant-traces.py`. **Never delete the locally
ignored archives** without a verified independent replacement backup.
