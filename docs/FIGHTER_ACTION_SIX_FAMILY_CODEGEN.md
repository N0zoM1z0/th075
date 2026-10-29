# F548 — genuine 104-instruction action-six source within three giant fighter bosses

**Whole original fighter CODE analyzed; natural source/VC7.1 compiler evidence
inside an incomplete giant function, NOT an exact accepted source unit.** The
source original is the user-supplied Japanese TH075 v1.11 `th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This extends the native-backed multi-switch action 0..5 source reconstruction
[F545](FIGHTER_OPENING_SIX_CASES_CODEGEN.md) to three original fighter-specific
**action-six** handlers, selected by identical complete original 104-instruction
behavioral and native member/reference families. The other eight large
fighters have genuinely different action-six control paths (96–125
instructions), **not** automatically treated as restored by this C++ body.

## Entire original action-six C++ behavior, including a real virtual call

The native first indexed switch's **seventh and eighth physical DWORD
handler addresses** bound each full original action-six CODE stream.
All three are **362 original CODE bytes and exactly 104 native x86
instructions** inside separate 43K–61K whole fighters. The original
control flow uses real signed short fields at receiver +0x62/+0x64/+0x70/+0x72,
unsigned mode +0x511, signed byte flag +0x3AC, and float motion fields
+0x48/+0x50/+0x54/+0x5C. It directly invokes true original `0040FAC0`
twice and `00453E20` twice, references the actual global threshold
`0065782C` twice, and finally invokes the **real owner vtable[0]** via
an observed `CALL DWORD PTR [EAX/EDX]`. These are five actual native calls,
not invented semantic names or separate functions. The C++ model uses
an actual `virtual void NativeVirtualFrameAdvance()` declaration to obtain
the original `this` vtable call, not an inline assembly/vptr-byte patch.

A startup state condition can immediately select action `0xCC` and return.
A native no-flag initial state resets the fighter. When the x87 position at
+0x48 crosses the real threshold, the source advances +0x54 by -(+0x5C),
tests the updated position sum and if appropriate sets action 10,
clears +0x48, resets and **returns from the entire fighter**. Otherwise
it genuinely increments the native signed-short frame counter +0x64; on
its limit at +0x72, it resets the frame, increments stage +0x62, sets the
original fighter-specific float values at stage 2 or 4, then rolls back
stage by 2 if past +0x70 before its real virtual-frame callback. These
conditions were recovered from the original instructions, not a Ghidra
local-variable name or copied original case bytes.

## Fighter-specific source values, not copied across characters

| Whole giant original | Full native fighter CODE (still unaccepted) | Stage reset threshold | Float +0x54 | Float +0x5C | Native vtbl[0] dispatch |
| --- | ---: | ---: | ---: | ---: | --- |
| `0x0045DD70` | 60,999 | 2 | `12.5f` | `0.55f` | `dword ptr [edx]` |
| `0x0058AF60` | 49,230 | 4 | `12.5f` | `0.55f` | `dword ptr [edx]` |
| `0x005D73C0` | 43,282 | 2 | `14.0f` | `0.7f` | `dword ptr [eax]` |

In particular `0058AF60` resets at stage **4** rather than **2**;
`005D73C0` writes **14.0f / 0.7f** rather than Reimu's
**12.5f / 0.55f**. All floats arise from actual physical native
`MOV DWORD PTR [owner+field], imm32` and are expressed as ordinary
round-trip-correct C++ float literals. There are no copied machine-code
arrays, fabricated frame locals, artificial padding or cropped exact claims.

## Three fresh compiler probes and precise limitations

The reproducible
[`verify-fighter-action-six-natural-source.py`](../scripts/verify-fighter-action-six-natural-source.py)
first authenticates each **entire original giant CODE** and all post-RET
switch tables using existing PE-bound verifiers. It then regenerates a
natural C++ single-switch source with the real six F545 opening cases
and this full source action six. All other actions remain explicitly
nonoriginal diagnostic marker cases. It compiles exactly the selected
small source translation units, **serially** under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` (never all 942 accepted cold units).

All **3/3** fresh objects reproduce, for their own original giant:

- **104/104 actual complete x86 instruction mnemonics, lengths, real
  EAX/ECX/EDX allocations, signed member offsets, x87 stack operation
  sequence and real internal branch graph**. Only the original parent
  receiver EBP slot, external absolute target relocations and the
  enclosing function's return destination are normalized, with these
  fields checked separately where physical COFF relocations are present.
- **6/6 authentic original typed physical COFF fields per case**, or
  **18/18 across three**: four native direct `REL32` call destinations
  and two native global `DIR32` x87 operand references in each case.
  The 104-instruction final indirect `vtable[0]` call is independently
  checked in both real native and generated C++ (no COFF relocation).
- The entire compiler-emitted first-switch/post-RET layout retains all
  **422 original-style DWORD jump-table COFF references**, the true
  original repeated-target/default equivalence partitions, **1,323
  byte-identical sparse action-map index bytes**, and the whole 3,011
  original post-RET DATA byte *shape*. None of those DATA bytes is
  accepted authored CODE credit.

Even though each isolated candidate case matches the **original 362-byte
length**, the small C++ translation unit stores its borrowed receiver at
`EBP-4` instead of the original whole fighter's real EBP-0x34 or
EBP-0x2C. External call targets and after-RET label locations also differ.
**This is source/compiler structural evidence, not a 362-byte exact
match for a separate function and not a replacement for any complete
43K–61K boss reconstruction.** All 1,086 original action-six CODE
bytes remain parts of the 153,511 as-yet-unaccepted whole fighter CODE
bytes; complete big function source is still necessary to earn credit.

## Reproduce without all-unit cold replay

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-boss-family.py
# One original whole boss plus one freshly compiled relevant source probe:
scripts/repo-python scripts/verify-fighter-action-six-natural-source.py --boss 0x0058AF60
# Or exactly the three separate action-six original/source comparisons:
scripts/repo-python scripts/verify-fighter-action-six-natural-source.py
```

Ignored generated `.cpp`, `.obj`, `.pdb`, compiler logs and native
comparison summaries are retained under `.analysis/f548-action-six-source/`.
Original disassemblies and negative source probes remain under
`.analysis/f548-action-six/`. No accepted `functions.csv`, original
C++ owner-layout proof, exact match manifest or external Oracle receipt
was added; no all-unit cold replay was launched.
