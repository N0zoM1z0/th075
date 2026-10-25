# TH075 reconstruction knowledge index

Updated 2026-10-25 for resumed reconstruction, F155. The active 98%
authored-byte objective remains incomplete. Current state and continuation
instructions are in [RE_HANDOFF.md](RE_HANDOFF.md).

## Authoritative inputs and evidence

- Target: supplied Japanese th075.exe 1.11, SHA-256
  `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
  Archive identity is pinned; independent official provenance is not established.
- `config/functions.csv` holds provisional boundaries/source state;
  `function-origins.csv` holds ownership. Source presence, names, Ghidra types,
  successful compilation and byte equality are separate facts.
- `config/match-units.toml`, `matches.csv`, `exact-adoptions.json` retain
  complete cold-exact units/all actual relocations. Counts are 337 units,
  717,360 code bytes, 138 canonical objects and 215 accepted inputs.
- Reviewed authored coverage is 36.35%; conservative coverage is 36.28%.
  All 97 unknown origins/3,608 bytes and all pending code stay in the conservative
  denominator. Origin evidence through R268 is unchanged.
- CODE size determines goal credit; compare_size includes owned tables/remaps
  for full acceptance. Never crop owned data or change the metric.

## Current source work

**004AC040, R048 authored:** the authoritative complete source is now
`.analysis/character-move-4ac040/f155/`, SHA prefix97e045e6. All151 entries plus
the real prefix/default/shared tail compile as one body. Current whole diagnostic
emits exactly83,922 bytes (82,796 code +1,126 owned data), with18,539 differing
positions after replaying all2,352 actual relocation fields. Both code streams
have22,721 instructions. This remains unaccepted with no source-presence/exact
credit. F155 uses canonical command and resource headers with the same complete code.
Preserve active F155 and F154 caller/compiler-map objects, F153 resolved/window/counter objects and F152 object
listed in the handoff. The first F152 failure84,234/74,320 remains frozen.

The explicit profile remains pinned VC7.1 build3077, /Od /Ob0 /Gy /GR- /GX-
/GS /Zi /I src. Frame0x720, savedESI, EBP-0x64 receiver, six table widths and four
byte remaps agree. All actual local COFF offsets remain actual; whole comparison
uses no masks, crops, aliases or native-label rebasing. The separate colorless
instruction diagnostic discards eax/ecx/edx identity for investigation only.
It finds no remaining shape differences, which proves neither data flow nor
exactness. Seventy entries still have physical differences.

F153's bounded pointer views describe observed scalar windows, never a complete
owner or a proven original nominal subobject. They are not instantiated/embedded
to size an owner. No explicit padding, synthetic storage, arrays or inert locals
were added. Actual fields and compiler-supplied alignment only:

- At40: byte flag40 and float positions44/48. Compiler alignment occupies41..43;
  the original identities of those bytes remain unknown and are never accessed.
- At50: float50/54, observed raw DWORD58 and float5C. The independently exact
  motion-clear helper writes all four DWORDs; polar velocity and main arithmetic
  provide the used float accesses. Raw58's original declaration stays unknown.
- At94: the two observed launch floats94/98. Their direct copy now emits the
  native DWORD copy rather than an x87 round trip.
- At2F0: the independently copied36-byte transform record followed immediately
  by four float parameters314..320. Canonical fighter forwarders pass these
  actual pointers; the accepted spawner copies the complete transform and reads
  all four parameters. This corrects the ten parameter314 argument loads in
  states751/752. Opponent positions use the same observed position view.
- At10: reuse of the accepted36-byte transform record for alpha11/scalar30 did
  not change bytes, but keeps the already established field interface.

All96 discarded small counter results were checked against the native field
load, arithmetic and store widths, paired in field/sign/order within complete
entries. Native byte/word operations now use natural ++/-- instead of promoted
assignment arithmetic. State414 uses integer `0 - F02 * 4`, matching the actual
XOR-zero/SUB sequence before conversion. State771 uses `F04 += F06`, matching
the actual RHS-before-LHS loads and add into the LHS value. These source changes
add no artificial locals or ABI changes. The source transformation audit projects
all151 entries exactly to frozen F152 source through only recorded changes.

The first genuine byte divergence is now state89 at004ADEFB: native loads the
receiver intoEAX, emitted intoEDX. Earlier states6/88 are resolved. No fix for
the remaining register choices is established. Copy F155 to fresh F156 before
working further. Four whole-source negative controls have identical raw code
and actual relocation targets: offset-zero scalar member, accepted transform
view, prefix/postfix loop increment in88 and explicit/implicit float truth tests
in88. Do not rerun them without new evidence.

F154's frozen baseline compiler observation matches all13,951 explicit GPR
tokens to its full COFF. Actual counts:8,223 mapping/8,223 use/2,639 forced-binding events.
First target difference is token1352, actual mapping event737: current virtual
descriptor18681 maps toEDX withEAX next; native expectsEAX. These descriptor labels belong only to the frozen baseline header inputs.
Identical code after canonical-header migration does not infer its logical IDs.
The native original virtual identities/liveness are not established. Twenty-one latest-node-write
tuple exceptions stay explicit; memory base/index operands are outside this
token model. Do not treat descriptor IDs as extra source operations or pad source.

Five F154 controls emit exactly the same full code/actual fields:545 observed
word-window accesses, nested final guard in88, implicit snapshot conversions
in88, /G6 tuning and /GX exception handling. Two double-zero comparisons emit eight-byte constants in
place of native four-byte loads; their new constant destinations were left
unresolved and the candidate rejected. No such control is adopted as a fix.
The full debugger build retains the same raw code and all2,352 relocation fields.
Raw Rich observations give no function-specific or executable-wide profile.

F155's bounded debugger trace narrows the first current-source choice further.
Immediately before event737, busyEAX/ECX/EDX are all zero and virtual18681 is
absent from all three per-physical interference sets. Candidate head3 is selected
asEDX, then the cursor advances to1. Hardware watches record actual writes around
maps730..740; stopped PCs are after writes. The compiler exited normally with
8,223 maps/13,951 emissions. All56 logged emission values (1325..1380) agree with
the complete own COFF; this is not a new full-value trace. At ordinal1352 the
actual receiver load isEDX versus nativeEAX. Only the frozen pre-resource-migration
input bundle establishes those logical labels. Target original virtual state and
post-resource-migration labels remain unknown. No queue, tool file or target was
patched. The full83,922 bytes/all2,352 fields agree with F154.

Two further complete caller controls are closed: lifting the genuine i88
declaration to function scope and /Zc:forScope. Both retain raw code/actual
destinations and18,539 differences; the first merely renumbers29 local labels.
Do not repeat them without new evidence. F155's source audit projects all151
entries exactly to F154 by reversing only the two accepted resource declaration
renames; prefix/default/shared exits and real operations stay unchanged.

Read-only constructor context did not establish an access to4C, so no broader
position/motion view spanning that unknown field was introduced. R045
initialize4567B0 calls458650/458670, whose observed wrappers only install vtables;
both remain unknown. Existing ownership and all97 pending origins stay unchanged.

F150 covers the actual mapped states 390..420, adding 12,684 native
investigation bytes (35,886 contiguous bytes with source in total). It retains
three explicit sites in each 400..405 volley, five explicit sites in each
406..410 fan, and both separate five-site branches in 418. The eight real
loops in 416/417/419/420 bring the source to eleven genuine loop counters.
Nested `RecordedRange455580::SelectRange` arguments use the accepted 139-byte
unit and native right-to-left argument evaluation; original names/layouts
remain provisional. This source audit checks call evaluation order, not emitted
CFG or bytes. Native constants at 006590AC and 00657F74 are 110.0f and 0.25f.
State 416 decrements F00 without initializing it in that entry; preserve this
observed order. No compilation, source-presence or exact credit is claimed.

F151 added 27 actual mapped entries 500..610, covering 24,106 more native
investigation bytes (59,992 contiguous bytes with source at that checkpoint). Its audit had 926
canonical named calls, seven unaccepted command calls, fifteen genuine loops
and eighteen float-to-short conversions. Native entry/body/CFG/table/ABI,
source call evaluation order and real exits were rechecked. A separate scalar
contract audit verifies all direct literal float/integer store widths, values
and order in the 27 new entries; it does not prove calculated expressions,
conditions, original declarations or emitted bytes.

- 500/501 use repeat bounds 1/3; 502/503 use 2/4. The latter multiply motion by
  double constants 0.25/0.1. 501 sets gravity after its auxiliary effect call.
- 504..506 fade by 30 and launch at zero; 507..509 fade by 20 and launch after
  the repeated phase-8 reset path. Preserve the six distinct tracked effects
  and the post-call transform/alpha stores in each entry.
- 594..596 decrement byte 366 before clearing motion. Only 594/595 retain the
  pre-advance 3B6/7C guard, and 598/599 have no sound call at their spawn site.
- 600/601 decrement the short timer only inside the pre-advance phase >4 guard.
  Their five computed angle stores differ; 602 retains the native five-angle
  sequence 10,5,0,5,10. Do not infer symmetric negative angles.
- 603/605 each contain 36 distinct calls with literal angles 0..350 by 10.
  604/606 each contain nine distinct calls with literal angles -28..28 by 7.
  604 decrements F00 before advancing; 605/606 do not. 607..610 have four real
  ten-iteration loops. 607/608 restore motion from short F00/F02 times 0.01f
  before resetting/incrementing those shorts; 609/610 have no such restore.

F152 adds the final20 entries700..796/22,380 native investigation bytes. All151
entry fragments now cover82,372 contiguous investigation bytes. The source
audit retains1,290 canonical named calls,21 pending named calls,41 float-to-short
conversions and24 real loop counters/25 loops. The151 nondefault entries have
1,358 calls including six true slot-0 calls. F155 independently recounts1,361
whole-function calls: the default/shared tail adds three canonical calls at
004C0380/004C0398/004C03A2. The current whole count is1,313 canonical named,
41 CRT, six virtual and one pending named; the earlier1,290 canonical fragment
count excluded those same three. This corrects reporting, not code or credit. The scalar audit checks direct
literal float/integer store width/value/order in all20 new entries, not computed
conditions or expressions. The audits are frozen precompilation/preacceptance
snapshots. Eleven pending sites now have independently exact bodies in the new
scalar helper units; ten pending sites remain (seven454BC0,two452B30,one483300).

- 700/701 preserve the duplicate F00 zero stores and angle-pair spawn sites.
  701 sets F14 and omits the F04 increment. 702/703 retain five distinct repeat
  phases and `(SelectRange(0,100)>200)`; do not simplify that observed test.
- 704..707 retain different repeat bounds and landing guards. 706 returns after
  its advance-completion spawn, unlike the neighboring entries. Opponent status
  copies remain word copies; full opponent/owner layouts remain unknown.
- 731 reuses one real counter in two actual360-degree loops, while the six
  post-fade tracked effect sites remain explicit. Preserve the independent
  phase18/19 and20/21 gravity/landing branches. 741/742 retain fresh signed
  global level reads; 742 has four separate level loops (12,20,30,40 iterations).
- 751/752 retain short motion snapshots scaled by100, temporary polar speed
  **100.0f**, five explicit spawn phases and restores scaled by0.01f. 751's first
  random angle subtracts70 and the following four subtract50; 752 subtracts70
  at all five sites. Their gravity constants differ (0.01f/0.02f).
- 761 retains four distinct random-rain sites with right-to-left nested random
  argument evaluation, repeated level reads and opponent transform/alpha writes.
  762's landing returns before advancing; 763 refreshes facing at phase9 and
  selects761 on completion. Do not merge the neighboring fade/launch policies.
- 770 has four separate level loops (10,12,15,20 iterations). Its landing path
  continues into advance. 771 retains signed random rotation, short snapshots,
  unknown483300 aim call and actual divisor0.017453288659453392f at00657828.
  795/796 retain their fade/resource calls; only796 writes byte3CF after reset19.

F152 preacceptance contracts are exported in `pending-helper-native-contracts.json`.
Resource452B30 was an authored215-byte policy with mixed transitive callees,
then unaccepted; F155 acceptance is recorded below. Unknown483300 forwards two float stack slots to483320 and returns ST0;
483320 widens to doubles for642240 and performs FST single before returning ST0.
The private float return declaration is a used-ABI hypothesis, not ownership or
proof of original precision. Both unknown origins remain unchanged.

The observed two-slot receiver prefix is supported by constructor 004C0832,
table006594A8, complete R050/R068 bodies and four actual character calls in
already-exact BattleFrame::UpdateFrame. It does not recover a complete owner.
The separate global draw-dispatcher call is not character evidence.

**0050A580:** the complete 92-entry draft remains pending in full. Preserve
source SHA prefix 80ca174b and active F145CanonicalViews plus the five older active
objects listed in the handoff. Required comparison 82,106; actual diagnostic
82,109 bytes / 26,719 differences/522 GPR differences, all 1,449 actual fields.
F146's bounded negative compiler controls did not establish a natural fix.

**New F152 accepted code:** `FighterMoveScalarHelpers` has two declaration-only
methods in one source/object:37-byte `SetNonnegativeWord` at00453E80 and35-byte
`BeginFadeParameters` at00454A70. A single canonical cold build replayed both
whole units,72/72 exact with no relocations. Both saveECX atEBP-4 and returnRET4.
The first tests the signed low word and returns without a store when negative,
otherwise writes word3B8. The second writes byteF0 at538 then argument byte539.
R103 origin roles/native bodies and all real exits remain independently checked;
literal aliases preserve the old names. Neither interface establishes a complete
owner. F153 migrates the large source to the canonical scalar declaration at all
eleven sites; the complete whole comparison still fails and earns no credit.

**Earlier accepted code:** F146's 51-byte motion helper00453E20, unit
`fighter-motion-clear-00453e20`, cold51/51 exact. The R103 role and original
database title are preserved by literal alias. Four DWORD zero stores do not
establish original field declarations or a complete owner layout.

**F154 accepted command closure:**61-byte `SetCommandSelection` at454BC0
and22-byte setters410FA0/410FE0 passed one canonical cold build,105/105 complete
bytes exact. The wrapper stores a DWORD at47C, forwards the low-byte mode through
pointer480 to the byte10 setter, then forwards the DWORD color mask to the +0x14
DWORD setter. RET12/RET4, savedECX atEBP-4, all exits and both actual REL32 fields
are retained. R213/R239 original roles and independent created-owner/action/draw
contexts remain frozen, with literal aliases. Original names, signedness and
complete owner layouts stay provisional; neither receiver view is instantiated.
Historical R213 notes saying the setters are unknown were already superseded by
R239 and remain preserved as history. All97 unknown origins are unchanged.

The complete caller now uses the canonical header at all seven command call
sites. Its151 source entries, raw function bytes and all relocation destinations
are unchanged from F153; whole comparison still fails at18,539 positions. Only
At F154, three named pending-body sites remained: two resource452B30 and one unknown483300.
Neither unknown483300/483320 nor either large draft earns new exact credit.

**F155 accepted resource policy:**215-byte `SelectResourceParameters` at452B30
passed one canonical cold replay,215/215 complete bytes exact with all seven
actual fields. It clears word3A2, tests signed byte2CD/global6714B4, stores9999
at3A0, and copies selected DWORDs from3D0/400 to3A4/3A8 using signed byte39D.
Clock mode1 forwards selected byte384 to the actual6718F8 profile receiver.
The other path computes float36C*8800.0f/900.0f, converts to integer before
adding1201/narrowing to word3A0, then clears byte464. SavedECX atEBP-4/plainRET,
all four branches and nine following excluded INT3 bytes are retained. R109
full native/independent game context and historical name remain preserved.
The current header claims call contracts and external storage only, never an
owner size, array dimensions, original nominal type or word signedness.

The transitive counter454D00 remains R182 authored but unaccepted. Its complete
79-byte body sign-extends byte argument/bank16AC4, uses stride17F0 and base394,
increments a word and returnsRET4. Both complete natural pointer/unknown-bound
array-reference controls emit79 bytes with23 differences: their RHS computes
the bank before loading the argument index, while native loads the index first.
No fake bank structure, padding or array extent was added to force it. Those
sources/evidence remain private and gain no source/exact credit. The resource
policy's seven fields instead bind to independently retained native callee/data
contracts. Both large drafts and all97 unknown origins remain pending.

The two resource sites in the complete caller now use the canonical header.
Only the unknown483300 named site lacks a canonical body; both483300/483320
remain unknown. Full caller comparison stays83,922 bytes/18,539 differences,
all2,352 fields replayed, first byte004ADEFB. Receipts are the F155 source audit,
allocator-window correlation, resource unit proof and canonical replay.

F149 stopped during read-only reconnaissance of390..402. No additional case
was authored. State392's nested phase 6/phase 4 tests and400..402's three
explicit spawn sites must be preserved from native evidence rather than
optimized away/replaced by an invented loop. The unused duplicate work copy
was removed; F148 retains that earlier source/native checkpoint.

## Historical investigations

The complete former knowledge base, including original section titles,
observations, unknowns and R/F histories through F148, is retained byte-for-byte
as [KNOWLEDGE_BASE_THROUGH_F148.md](history/KNOWLEDGE_BASE_THROUGH_F148.md).
The former long handoff is retained as
[RE_HANDOFF_THROUGH_F148.md](history/RE_HANDOFF_THROUGH_F148.md).
Historical relative links were written from docs/: resolve them there or
read the original documents with Git at fd82165. Archived active-goal and
next-task instructions are superseded by this index, handoff and AGENTS.md.

Use an original address/evidence identifier to locate historical facts, then
confirm against the unchanged target and ledgers. Private source/checkpoints
are local and are not included in a Git clone. **Preserve this workspace when
switching agents.** Shared tools and the private Ghidra project also remain
local and read-only as documented.
