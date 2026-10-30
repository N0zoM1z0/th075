# F702–F704 — whole native WinMain real-used local/object lifetime controls

**Physically verified negative C++ reconstruction evidence; no exact credit.**
Original user-supplied Japanese TH075 1.11 executable SHA-256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The actual authored game startup `00602A60` is a complete **2,987-byte
CODE /654-x86** function followed by its independently owned **60-byte
(15-DWORD) scene switch DATA table**. The original first seven live
resource/object constructor and location operands were re-read from the
original target PE; native frame `SUB ESP,0x278` and `RET 0x10` remain
separately bounded and are not guessed from historical documentation.
The actual native active scene pointer at `EBP−0x184` and adjacent
module-path buffer at `EBP−0x180` are real stack locations, not mere
names inferred from a decompiler.

## Goal: reproduce *real* source object lifetime placement, not fabricated locals

Earlier F615 had compiled 30 whole original-shaped VC7.1 startup
variants; a real scene/path aggregate combined with `MSG` and event
lifetime produced a scene at `−0x178` and path at `−0x174`, **12
bytes short of the native offsets**. The
real native `scene/path` pair is `−0x184/−0x180`. We independently
revisited this hypothesis rather than accepting old prose or
re-running the previous 30-candidate generator indiscriminately.

F702–F704 compiled **37 new complete, nontrivial WinMain C++ source
variants** using the pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
original-profile compiler. Each retains genuine `AppMode`, graphics,
input, sound, archive, game-data and scene owner lifetimes; native
15-scene switch with real scene constructor calls, the whole Win32
message pump and the early failure and normal cleanup paths. **Every
newly moved/grouped member is actually assigned and used** by the
source; there are no inert stack fillers, fake aggregate members,
raw x86 grafts or hidden modifications to the executable.

| New whole-source hypothesis | Distinct VC7.1 compiles | Original-size source result |
| --- | ---: | --- |
| F702: move genuinely used `HWND main`, ready-event `HANDLE`, two window dimensions, real directory-end pointer and `WNDCLASSEXA` declaration to earlier lexical lifetimes in previously tested scene/path+`MSG` context | **12** | All **3,002 or 3,026 CODE B /654 x86 /173 generated COFF fields /60 afterRET DATA B**, nonexact |
| F703: put genuinely used `HWND main`, ready-event handle, window dimensions and directory-end pointer in the *real scene/path aggregate*, with the source API call inputs and actual writes preserved | **12** | All **3,002 or 3,026 B /654 x86 /173 COFF fields /60 DATA B**, nonexact |
| F704: place genuinely used native `MSG`, `WNDCLASSEXA` and/or `HWND`/event/directory-end values as members of the *same actual source aggregate*, including alternative member orderings | **13** | All **3,002 or 3,026 B /654 x86 /173 COFF fields /60 DATA B**, nonexact |
| **Total** | **37** | **0** exact 2,987-byte complete original functions |

Every compiled source still has the original **654 ordered x86
mnemonics**, and its VC7.1 function owns a separate **60-byte
post-RET scene-table layout**. Its **173 physical compiler COFF
records are SOURCE generation evidence only**: they do **not**
prove that each original PE target relocation or any complete
original game function is byte-exact. The original target has 123
native CALL instructions, which cannot be counted as 123 separate
accepted functions. The whole source CODE is always 15 or 39 B
**longer** than the original, with at most **627/654 identical
instruction widths** in this matrix, and substantial real EBP
object ownership differences remain.

## Important new actual stack negative: `EBP−0x180` is not enough

The best grouped source classes in this new matrix sometimes move the
actual used `currentScene` aggregate owner to **`EBP−0x180`**, with
`path` starting at **`EBP−0x17C`**, still **four bytes short** of
original `EBP−0x184/−0x180`. This occurs, for example, with a real
`main` and directory-end pointer in the aggregate (F703) or real
`MSG`+`main`+event/`WNDCLASSEXA` combinations (F704). They still
emit **3,002 B/654 x86**, with only **619/654** original instruction
widths equal, **not** 2,987 native CODE bytes. Adding yet more
existing POD declarations or moving their real source lifetimes
can leave both scene/path slots unchanged or move them *closer to
`EBP`*, contrary to the naive expectation that every new declaration
reserves another four EBP bytes. The original VC7.1 local allocator
cannot be inferred solely from declaration order.

F615 had independently obtained the **single real native pathname
location `EBP−0x180`** using a different source context, but its
scene pointer remained `−0xC` and entire CODE shrank to 2,930 B;
that also is **not** an acceptable entire WinMain reconstruction.
The new F702–F704 negatives exclude the straightforward hypothesis
that only earlier declarations of real `HWND`/event/dimensions or
embedding those already used POD fields into a scene/path owner will
simultaneously recover native module-path and scene pointer roles.
They do **not** prove any historical nominal class size or original
source type, and do **not** exclude a genuine larger object lifetime
or constructor/destructor ABI that has not yet been recovered.

All new source versions, complete generated COFF/PDB objects and
compiler transcripts, executable targeted research scripts and
per-variant summary JSON are preserved **locally** (Git-ignored) at
`.analysis/f702-winmain-real-startup-scene-lifetimes/`,
`.analysis/f703-winmain-real-aggregate-fields/` and
`.analysis/f704-winmain-message-context/`. They are not claimed to
be stored in Git or accessible from a fresh clone. A selected old
F615 baseline and original target scene dispatch can be independently
rechecked with:

```bash
scripts/repo-python scripts/verify-winmain-scene-dispatch.py
scripts/repo-python scripts/verify-winmain-local-layout-f615.py --case baseline
# New explicitly bounded matrix (only complete WinMain TUs):
scripts/repo-python .analysis/f703-winmain-real-aggregate-fields/research.py
```

No whole-author exact credit; **943 accepted authored whole functions /
862,726 original CODE B (43.71% reviewed)** remains the truth. The
original 2,987-byte WinMain is still a separate authored NONEXACT
function, and no mass 943-unit cold replay, original EXE patch or
external exactness claim was made.
