# TH075 WinMain: whole 2,987-byte original dispatch and four genuine cleanup paths

**Status: original PE research only, NOT an exact C++ reconstruction.**
The R064-authored original `GameApplication::RunAt00602A60` remains
unaccepted. It is the actual complete game startup, event/message pump,
15-scene dispatcher and cleanup routine in the pinned user-supplied Japanese
`resources/th075.exe` v1.11. SHA256 target:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Full original executable function and case DATA boundaries

The original *entire* WinMain CODE is `00602A60..0060360A` inclusive,
**2,987 bytes / 654 decoded native x86 instructions**, SHA256
`780862e0f784ac2cbd16ed20eaff12c0da49a0c831ce4a9f56e85fc2edb3ffa0`.
Its single last `RET 0x10` ends exactly at **`0060360B`**. Native code uses
an observed `sub esp,0x278` stack frame; no guessed original complete
application/private scene type is claimed.

Original original-code switch at `0060304B` performs
`JMP DWORD PTR [ECX*4 + 0x0060360B]`. The owned **15 DWORD/60-byte**
post-RET table is at **`0060360B..00603646`**, original table SHA256
`840a0d5ad8c1d5ad0a26f5ff4beae4c657cb03640df58b0aa1b71abba243fe86`.
Exactly **nine `CC` alignment bytes** follow, through `0060364F`;
separately already F468-exact `GameApplication::WindowCallback` starts at
`00603650`. Neither table DATA nor the nine padding bytes are executable
CODE coverage.

Every table entry is a **different, original instruction-aligned jump
target within the original 2,987-byte CODE body**. Each entry starts
with an immediate native scene allocation size and a genuine call to
original `operator new` at `0064159D`, followed by its own original
new-result, failure-test, constructor and scene-owner assignment path.
The native compiler physically emits **case 4 first**, even though the
table is indexed in logical case order. These are independently audited
original sizes and actual native entrypoints:

| Scene case | CODE address | True `operator new` size |
| ---: | --- | ---: |
| 0 | `006030A5` | `0x11C` |
| 1 | `006030FB` | `0x10` |
| 2 | `0060314E` | `0x3C` |
| 3 | `006031A1` | `0xF4` |
| 4 | `00603052` | `0x10` |
| 5 | `006031F7` | `0x54` |
| 6 | `0060324A` | `0x4C` |
| 7 | `0060329D` | `0x120` |
| 8 | `006032F3` | `0xC` |
| 9 | `00603346` | `0x1C` |
| 10 | `00603399` | `0x124` |
| 11 | `006033EF` | `0x14` |
| 12 | `00603442` | `0x3E0` |
| 13 | `00603498` | `0x14` |
| 14 | `006034E8` | `0x1D0` |

## Four *independent* original owned resource destruction sequences

All three native startup failure branches (RegisterClassExA,
CreateWindowExA and CoInitialize) and the original normal shutdown branch
have **four genuine direct destructor calls in exactly this order**:

1. `00406650` — original shared sound client destructor
2. `00403BE0` — original input client destructor
3. `00401020` — original global graphics client destructor (**F454 already exact**)
4. `00423A90` — original application-mode client destructor

Their original first-call addresses are respectively `00602BC7`,
`00602C44`, `00602CB5` and `006035D6`. These are **four distinct
physical original call sequences**, not one logically shared cleanup
helper and not copied source. The original native writes independent
0-valued return locals and jumps to a shared final security-cookie and
`RET 0x10` epilogue. A naturally compiled source that factors all
four into one cleanup tail can be semantically close but byte-wrong.

## The real scene pointer, path buffer, state method and Windows pump

The original C++ game function initializes the active scene DWORD at
**EBP-0x184** to zero immediately after app-mode construction, and uses
a **260-byte** actual module-path buffer starting at EBP-0x180.
Ghidra's broad overlapping array labels are not reliable C++ field
definitions; these are independently observed original x86 locations.
An early and a later scene-policy update call the true original **thiscall
`00431F60`**, at native call sites **`00602F0E` and `00602F95`**,
passing the actual scene pointer as the `ECX` receiver and 16-bit
scene state on the stack. An older provisional C++ source incorrectly
modeled this as a free **cdecl** `SceneTranslateAt00431F60` and thus
emitted different parameter and caller-stack cleanup instructions.

The original message loop has exactly **one call** to each imported
Windows pump API within the whole native 2,987-byte function:
`PeekMessageA` at `00602F3A`, `GetMessageA` at `00602F4E`,
`TranslateMessage` at `00602F61`, and `DispatchMessageA` at
`00602F6B`. Their exact native IAT slots are `0065722C`, `00657228`,
`00657224` and `00657220`. The first PeekMessage decides between
native scene advancement and ordinary Windows message dispatch; the
Win32 callbacks, shared timer and scene state must still be reproduced
with the actual original control flow, not just matching game behavior.

## Full natural C++ experimental controls: no exact acceptance

All complete-function probes and logs are preserved under `.analysis/`.
They call original borrowed game methods and use real C++ constructor,
destructor, scene-pointer, Win32 and COM resources instead of fake
stack locals or assembly. Each item has **a complete WinMain body** and
true 15-case after-RET table generated by pinned VC7.1, but **none**
passes whole-function original CODE or physical relocation comparison:

- F455/F456 initially modeled globally shared destructor calls and scene
  allocation results; their full compiled CODE lengths were **2,831**
  and **2,951** bytes, with incomplete error resource lifetime.
- F473 replaced fake manual release with genuine four C++ RAII objects
  and three early failure paths: **3,022 CODE bytes / 650 instructions**,
  stack `0x274`. The compiler still merged error cleanup rather than
  reproducing original physically separate destructor branches.
- F480 introduced a genuinely used early scene pointer and assignments:
  **2,963 CODE bytes / 651 instructions**, stack `0x270`.
- F500 corrected the borrowed `00431F60` scene-state **thiscall ABI**,
  initialized the actual scene-state word before the initial call and
  reproduced unsigned high-bit branch semantics; the separate pointer
  and module-path source compiled to **2,974 CODE bytes / 653
  instructions**, still with stack `0x270`. Physically grouping its
  two *real* adjacent startup objects compiled a **3,109-byte**
  version and placed them at wrong stack addresses, showing that a
  plausible aggregate declaration is not proof of the original
  source variable allocation order. Adding a meaningful first-scene
  construction result temp produced **3,122 bytes** and stack `0x274`.
- F501 tried **12** different complete, meaningful Win32 message-pump
  layouts: a single `PeekMessageA` if/else branch with both natural
  orientations, and early `continue`, each with the actual MSG declared
  in one of four live scopes. These compile to **2,947–2,962 CODE
  bytes / 650 instructions**, stack `0x270` or `0x274`, all **nonexact**.
  Do not infer a native match merely because a source form eliminates
  a duplicate `PeekMessage` block or adjusts byte count.

**Nothing from the 2,987-byte WinMain boss, its 60-byte switch DATA or its
alignment padding is accepted or counted as reconstructed CODE.** Original
F468 `WindowCallback` is a separately exact function and is not counted
again. Next full-function work needs the physically correct local
resource-object placement, each original failure destructor chain,
scene 4 owner first-new lifetime, 15-case native switch order, message
pump CFG and native relocation destinations — not just a matching
aggregate code length.

### Re-run original evidence validation (read-only, no cold replay)

```bash
scripts/repo-python scripts/verify-winmain-scene-dispatch.py
```

The script verifies the target SHA, entire CODE SHA, all 654 original
instructions and RET 16, all fifteen exact native scene case allocations,
separately original table SHA, instruction-aligned case targets,
four independent destructor chains, real scene-pointer/path stack
addresses, actual two `00431F60` call sites, original imported message
pump call sites and nine trailing `CC` bytes. It does **not** build
reconstructed C++, cold replay units, modify the PE or credit WinMain.

## F523–F531: complete C++ original-ABI lifetime and control-flow recovery (NOT exact)

The previously recorded F500 source had several genuine **ABI and C++
lifetime errors**, independent of minor WinMain code length. Reexamining
the **whole original** 2,987-byte x86 function (including its early-failure
cleanup and original successful shutdown) revealed:

- The native function calls **`0041CF80` three times as cdecl** with
  **two pushed `const char*` arguments and caller `ADD ESP,8`** at
  offsets `+0x2C1`, `+0x2D3`, and `+0x2E5`. Historical F455/F500
  mistakenly declared that function a **thiscall `ArchiveCatalog::Open`**.
  These do not have the same native call ABI or stack shape.
- Actual distinct *automatic, locally constructed game objects*:
  `ArchiveCatalog` C++ constructor `0041CE10`, receiver **EBP-0x35**
  at original offset `+0x2AF`, with its **nonvirtual destructor**
  `0041CE50` at `+0xB6B/+0xB6E`; and game-data resources constructor
  `00417210`, receiver **EBP-0x36** at `+0x307`, with its destructor
  `00417430` at `+0xB63/+0xB66`. Source must use real object lifetime,
  not call borrowed `InitializeGameData`/`SaveGameData` as cdecl free
  helpers with wrong receiver/cleanup order.
- Original shared replay object at **`006718F8`** receives its two
  original **thiscall methods `00416B10` and `004169E0`**. Each original
  call is immediately preceded by `MOV ECX,006718F8`, at native
  offsets `+0x4B7/+0x4BC` and `+0xAEA/+0xAEF`; an earlier source
  mistakenly modeled those as no-receiver cdecl functions.
- Original first scene allocation saves its **actually used constructor
  return pointer** in EBP-0x19C at `+0x48B`, then copies it to the
  real active-scene local **EBP-0x184** at `+0x491/+0x497`. This is
  a meaningful source-level `Scene4* firstConstructedScene = new Scene4;
  currentScene = firstConstructedScene;`, not a stack-padding variable.
- Original `sceneState` first assigns the real 16-bit state `0x2004`
  at **EBP-0x3C**, then calls genuine scene thiscall `00431F60` and
  stores its 16-bit return. The native outer event loop retains a real
  **constant-true condition** at `+0x4C1/+0x4C6/+0x4C8`:
  `MOV ECX,1; TEST ECX,ECX; JE end`. With this VC7.1 compiler,
  natural `while (1)` emits those instructions, whereas natural
  `for(;;)` does not.
- Original three initial failures each execute the four authentic
  reverse-order local resource destructors **in the early branch**.
  Explicit failure-first `if (RegisterClassExA(...) == 0) return 0;`
  and equivalents for window creation and COM initialization produce
  the correct 16 native compiler-generated resource destructor calls
  spread among four original paths. Nesting success-only conditions
  misplaces entire destructor regions.
- A natural single `PeekMessageA` if/else-driven event pump is closer to
  the actual original 654-insn ordered sequence than a pair of nested
  `while` conditions: no extra call to imported Win32 APIs is allowed.

**Full-function C++ evidence with pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`**
(the independent original function is still **2,987 CODE bytes /654
instructions /123 calls /0x278 stack**):

| Probe | Complete generated CODE | x86 instructions | Original mnemonic-order matches | Real stack allocation |
| --- | ---: | ---: | ---: | --- |
| F500 old scene-ABI corrected source | 2,974 | 653 | 592/654 for original pre-correction F480; later first 86-instruction block correct | 0x270 |
| F525, all three genuine failures early-return | 2,962 | 650 | **626/654** | 0x270 |
| F526, flat single `PeekMessageA` | 2,949 | 647 | **639/654** | 0x270 |
| F527, correct archive/game-data/replay ABIs and RAII | 2,962 | 651 | **649/654** | 0x274 |
| F528, first-scene constructor temp + true `while(1)` + no extra delete guard | **2,981** | **654** | **654/654** | **0x278** |
| F528, same with extra redundant scene-deletion condition | 2,987 | **656** | 654/654 (two extra) | 0x278 |
| F529, sixteen authentic POD declaration-scope alternatives | 2,933–2,981 | 654 | 654/654 | 0x278–0x27C |
| F530, actually used scene/path/HWND aggregate hypothesis | 3,113 | 654 | 654/654 | 0x278–0x27C |

The *strongest F528 source is not exact* despite all **654/654 ordered
x86 mnemonics**, all **123 original `call` instructions**, the exact
native stack allocation and original fifteen-case switch. The original
complete function is still **six CODE bytes longer**. An independent
instruction-by-instruction operand/size audit at
`.analysis/f528-winmain-native-initial-scene/detailed-insn-alignment.tsv`
shows only **224/654 source instructions have both original operand and
instruction length**, with 430 actual operand/length differences,
including 200 physical EBP-local differences and many outstanding
relocation/branch displacements. This is **not** structural-exact or
an accepted full-function reconstruction, and even an equal 2,987-byte
candidate with 656 instructions cannot be accepted.

Critical real EBP layout still to recover, without fictitious pads:
original **application-mode object EBP-0x3D** (source currently -1),
**graphics client EBP-0x189** (source -0xD), **input EBP-0x62** and
**sound EBP-0x61** (source -0x15/-0x16), **active scene EBP-0x184**
(source -0xC), **module path EBP-0x180** (source -0x158), and **main
window EBP-0x188** (source elsewhere). Original `WNDCLASSEXA`, real
`MSG` local, scene-state word and the original startup/shutdown locals
must occupy their genuine physical locations without changing source
semantics. F529 moving only used POD declaration lines before app-mode
construction did not fix those slots. F530 grouping existing HWND,
scene pointer and path into one C++ aggregate produced **3,113 bytes**
and wrong physical offsets; native field adjacency alone therefore
**does not prove** an original C++ aggregate. Both source hypotheses
remain preserved privately and uncredited.

The now-expanded read-only
`scripts/repo-python scripts/verify-winmain-scene-dispatch.py` also
**independently checks the original PE** for two constructor/destructor
pairs, three genuine archive cdecl stack-cleanup calls, two real replay
instance call receivers, the first scene-return local, the 16-bit state
local and the actual `while(1)` guard in addition to all 15 original
scene jump-table allocations and four independent failure/success cleanup
paths. No compiler probe alters the pinned original executable; no
partial CODE, jump DATA or borrowed callee is credited, no assembly,
fake local, offset mask or all-unit cold replay is used.
