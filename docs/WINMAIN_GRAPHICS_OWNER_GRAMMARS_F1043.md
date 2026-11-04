# F1043 — The original WinMain graphics receiver is not restored by embedding a RAII client in the scene/path context

The pinned Japanese TH075 v1.11 original independently authored
WinMain is one complete **2,987-byte / 654 x86** callable at
`00602A60`, plus 60 **separate afterRET DATA** bytes. The normal
F911 original-shaped source remains **NONEXACT**: 2,984 compiled
bytes / 654 ordered original mnemonic instructions, with 9
instruction-width disagreements and wrong original C++ stack owners.
In the real native entry path the `currentScene` pointer is zeroed
before the independent Graphics client constructor, and Graphics
uses native EBP−0x189 adjacent to the HWND at EBP−0x188.

One plausible but unverified historical C++ layout was a real
`NativeStartupScenePathF500` automatic object containing the
Graphics client as a member alongside the actual HWND/current scene,
module path, window class, event and state fields. That arrangement
would move the Graphics object from the earlier synthetic stack
location and might explain the native adjacency. F1043 tested
**20 complete normal C++ member-owning sources**, plus the former
F911 complete baseline, under pinned VC7.1 `/GX-`.

The trials used a real `GraphicsClientF455 graphics` member at one
of five natural member locations (before HWND, after HWND, after
current scene, after module path, after window class). They varied
both genuinely used initial scene-pointer initialization forms
(member initializer versus constructor body), and ordinary versus
explicit inlining of the genuine owner constructor. In each variant
Graphics is still genuinely constructed and destroyed, Input and
Sound clients retain their real local lifetimes, and all 16 scene
allocation paths and original game logic remain in source. No
inert padding locals or fake unused members were introduced.

All 21 full-function sources compile. The independent original PE
and native source-COFF audit gives:

| Full source | Generated CODE | Generated x86 | COFF records | Original ctor/dtor symbol set |
| --- | ---: | ---: | ---: | --- |
| F911 stand-alone Graphics baseline | 2,984B | **654** | 173 | present |
| **All 20 owner-member trials** | **2,989B** | **653** | 173 | **wrong** |
| Pinned original WinMain | **2,987B** | **654** | real physical fields | real independent Graphics calls |

The absolute failure is **not** a one-byte padding or stack distance
issue. With a nontrivial `GraphicsClient` member, VC7.1 emits a
separate **context constructor and destructor**, replacing the
real original native Graphics client constructor/destructor call
symbols. The target original has direct client calls; this layout
contradicts the physical source ABI and destroys original entire
instruction geometry. An explicit `__forceinline` decoration on the
context constructor does not restore native codegen under this
pinned compiler and flag profile. A 2,989-byte generated body
is not a closer original whole-function reconstruction than a
2,984-byte source with the correct 654 original instruction sequence.

The tracked verifier reconstructs all actual whole sources and
compares original WinMain CODE, original jump-table ordinal mapping
where physically meaningful, full COFF symbol identity and compiler
frame/slot observations. It rejects the failed source shapes rather
than counting raw length or number of relocations as exactness:

    scripts/repo-python scripts/verify-winmain-graphics-owner-grammar-f1043.py

All generated C++, OBJ/PDB, compile logs and comparative receipts
remain under ignored `.analysis/f1043-winmain-graphics-owner/`.
Continue investigating genuine standalone Graphics/scene/path
lifetimes and the real first-scene pointer placement; do not adopt
a context-member RAII source merely to force graphics near HWND.

**No original whole WinMain match, no new CODE credit, and no full
979-unit cold replay.**
