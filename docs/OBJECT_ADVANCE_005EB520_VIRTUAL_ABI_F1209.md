# F1209 — original 005EB520 virtual callback and F1208 compiler controls

The complete [34KB research source](../probes/CharacterObjectWhole005EB520F1207.cpp)
now declares its actual **virtual slot 1**, preceded by the observed animation
binding slot 0. This replaces the F061 call-only nonvirtual declaration with
an independently supported virtual interface. It is still a borrowed prefix;
no complete object layout, original nominal class spelling or allocation size
is asserted. The complete callable remains NONEXACT: **135 GPR /six width
differences**, with zero new accepted CODE.

## Native object, vtable and dispatch evidence

Fresh original PE reads and the existing read-only Ghidra wrapper establish:

- `005EB490` is the already exact F422 134B character-object constructor.
  Its instruction at `005EB4A2` stores `0065A04C` into the object's first DWORD.
  The body hash remains
  `4c0f0b5110662281a5c781a8548d59612fddfe55674e7d3e01b7f5c54be9f303`.
- Ghidra independently reports `005EB4A2 -> 0065A04C` and
  `0065A050 -> 005EB520`; no names, types, bytes or boundaries are written.
- Existing exact `0045BDB0` advances four effect deques. At `0045BE22` it
  loads the object's vptr, retains the object in ECX, and at `0045BE27`
  calls `[edx+4]`. This is a no-explicit-argument slot-1 dispatch, independently
  consistent with the existing exact F137 `AdvancingEffectF137` interface.

The original table contains these five observed entries:

| Slot | PE field | Native body | Existing source/evidence |
| --- | --- | --- | --- |
| 0 | 0065A04C | 0045B880 | F139 animation binding, exact 149B |
| 1 | 0065A050 | 005EB520 | Current complete 34KB nonexact parent |
| 2 | 0065A054 | 0040FC70 | F129 camera-relative node rendering, exact |
| 3 | 0065A058 | 00410350 | F129 node rendering, exact |
| 4 | 0065A05C | 00410A00 | F437 mirrored node rendering, exact |

The 20 table bytes hash to
`e2808aae77e8183224e9ef929d67da6dcd4751a0d3648b00f34cd5b4a3f32805`.
The source describes only the first two slots, which suffice to place this
body correctly. Its emitted member symbol is now
`?AdvanceAction@ObjectActor5EB520Draft@@UAEXXZ`.

The constructor chain is independently reread as
`005EB490 -> 0045B760 -> 00458650 -> 00458670`. The last two remain
origin-unknown; no origin is promoted from this relationship. The chain
initializes vptrs and sparse fields, and does not establish all intervening
member types. No padding array or fabricated leading layout is introduced.

## Complete source preservation

Only this research translation unit is affected. Fresh serial headless VC7.1
builds retain the F061 profile `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
The virtual declaration preserves all 34,879 emitted CODE+DATA bytes and all
806 physical relocation shapes/destinations. There are 63 compiler-local
label renames; external bindings are unchanged. The full native audit still
checks 9,378 instructions, frame 0x210 /this EBP-4, all 3,170 EBP positions,
901 direct targets, 745 CODE fields, 61 dense targets and 199 sparse bytes.
The independent F061 physical binder also checks actual constant payloads
and PE permissions. The six wrong widths still leave CODE two bytes too long.

Selected evidence is `.analysis/f1209-object-5eb520-virtual-abi/`: fresh
`tracked.obj`, `whole-audit.py`, whole audit JSON, physical-binding receipt,
`verified-summary.json`, `native-virtual-facet.json`, complete constructor-chain
receipt and native dispatch disassembly. F1208's Ghidra entry/vtable xrefs and
native constructor reads remain in its directory. The old F1207 source/object
and its nonvirtual symbol remain preserved as historical research.

## F1208 — bounded full-parent negatives, no source adoption

Eight fresh complete candidates preserve every CODE+DATA byte and physical
binding shape, leaving the same 135 GPR /six widths:

- A contiguous native action/stage/frame/direction window at +60.
- A scope around the genuine state-997 body.
- `/Z7` instead of `/Zi`.
- Sequencing the direction copy with its following first-frame condition.
- Removing the `else` after state 997's real early-return guard.
- Intrinsic `memcpy` of the genuine single direction byte.
- Writing twice the parent-health ratio with the constant first.
- Returning the genuine void reset call directly from its exit branch.

Two other complete candidates are rejected on independently checked shape:
double-precision state-997 ratios replace each native FIDIV with FILD/FDIVP,
producing 34,440B /9,380 x86. Moving `default` before state 998 physically
moves its code and emits 34,439B /9,378 x86. No ordinal-zipped whole GPR audit
is claimed for either changed ordering/count.

All changed nonfixed GPR roles in 998 follow the cyclic EAX->EDX,
ECX->EAX, EDX->ECX correspondence, including low-byte forms; AX returned by
the frame helper is fixed. This is an observed correspondence, not proof of
the compiler's internal allocation algorithm or whole-function equality.
The broader bounded inventory of 9,285 CPP paths produces no additional
selected whole parent; its name/size heuristics do not prove absence.

F1208 retains all ten sources/objects/logs, whole audits, shape reports,
`control-summary.json`, `998-register-correspondence.json` and inventory JSONs
under `.analysis/f1208-object-5eb520-native-phase/`. Do not repeat these controls
without new native/compiler evidence. F1209 changes no accepted input, origin,
source/match ledger or comparison infrastructure; all 34,434 original CODE
bytes remain pending. No full CI, corpus replay, origin retest or new
per-function test is required or run.
