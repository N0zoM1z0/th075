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
