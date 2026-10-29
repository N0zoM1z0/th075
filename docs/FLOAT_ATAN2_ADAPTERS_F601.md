# F601 — complete native 21- and 37-byte float atan2 adapters from ordinary VC7.1 C++

**Original Japanese TH075 1.11 native CODE and genuine pinned compiler
comparison; original provenance remains UNKNOWN, not credited authored
CODE.** Original executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Re-read the actual complete PE before accepting a source hypothesis

The two original formerly unclassified native functions make an ordinary
float-to-double C math path, not an independently recovered fighter
formula or an automatically game-authored trigonometry implementation:

| Whole original native function | x86 instructions | CODE bytes | Real typed COFF operand | Original callee |
| --- | ---: | ---: | --- | --- |
| `00483300` | 10 | 21 | `REL32` at `+0xC` | `00483320` float wrapper worker |
| `00483320` | 15 | 37 | `REL32` at `+0x17` | `00642240` actual VC7.1 CRT `_atan2` |

The 37-byte body reads the two caller-stack **float** arguments,
widens each to the real 8-byte **double** stack ABI, calls the CRT
`_atan2`, pops 16 argument bytes, and stores its floating-point return
to a 4-byte EBP local. The 21-byte forwarding body pushes the two
original raw DWORD argument values in the authentic order, calls its
worker and adjusts its own 8 argument bytes. Both complete original
prologues, epilogues, returns, intermediate stack writes and caller
cleanup are included. No external CRT code is mistaken for either
function's own CODE.

## Genuine C++ source and two fully linked whole-function comparisons

Tracked [`FloatAtan2AdaptersF601.cpp`](../probes/FloatAtan2AdaptersF601.cpp)
uses ordinary cdecl float calls with a declared `double atan2(double,
double)` CRT interface, naturally built using original-profile VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. The cold compiler emits exactly
**21 + 37 = 58** own CODE bytes with **10 + 15 = 25** correct x86
instruction roles and physical boundaries. Its two real `REL32`
COFF fields have the exact expected offsets, target symbol identities,
and **zero addends**. The original PE proves actual call destinations
`00483320` and `00642240` independently. After resolving both fields,
**each complete reconstructed CODE byte** is identical to the original:
17/17 and 33/33 non-COFF bytes respectively, plus both genuine typed
four-byte call fields (58/58 final linked bytes). No assembly, copied
native bytes, inert stack locals, fake ABI, truncated comparison or
source-only masked acceptance was used.

[`verify-float-atan2-adapters-f601.py`](../scripts/verify-float-atan2-adapters-f601.py)
reads original PE CODE and source COFF afresh, verifies the complete
instruction count/width/offset/mnemonic geometry, independently
resolves the actual native call destinations, checks all 58 linked
bytes, verifies original ownership records are still unknown and
that `_atan2` is a library implementation.

## Original full caller graph does not establish authored origin

To check whether the wrappers really participate in gameplay, the
verifier decodes real `CALL` instructions in **all 4,351 registered
native function extents**, not just old Ghidra XREF names. The first
wrapper at `00483300` has **211 original native direct calls from
16 distinct game-author-classified fighter functions**, including
both still-unmatched giant CharacterObject/fighter owners and exact
character action methods. The second wrapper `00483320` has **one
original direct caller** from `00483300`. Their observed `cdecl` ABI
and runtime dependency are therefore well supported by real original
machine instructions.

However, a direct call from authored game code does **not** prove
whether the C++ float forwarding adaptation was handwritten by the
game developer or instantiated/borrowed from a compiler/SDK overload.
The nearby original `00412D90/00412DB0` and `00428D20/00428D40`
math pairs have documented independently byte-equal ordinary and
SDK alternatives (prior R163), and exactly the same ownership
ambiguity can exist here. Do **not** relabel these two functions as
authored merely to improve coverage. Both remain `unknown` with
`review` disposition in `config/function-origins.csv`; all function,
match and acceptance ledgers remain untouched.

**F601 adds 58 source-backed whole-original bytes and strong native
caller evidence, but zero new credited authored CODE bytes and zero
accepted authored exact functions.** Its authentic CRT `_atan2`
callee, adjacent math helpers, other original callers and full
out-of-line vendor runtime remain separate owners.

## Independent destructor-local negative controls from the same round

This round also investigated *both* of the remaining much harder
nonexact authored destructors using only selected pinned compiler
translation units and complete original comparisons. Those source
hypotheses were rejected, not silently marked exact:

- `0041CE50` (171 original bytes / 51 x86 / 14 true COFF fields):
  pointer/reference-return member interfaces, actual typed pointer
  lvalues and natural `delete`, then `free` comma sequencing all
  preserve VC7.1's wrong -0x10/-0xC/-0x8 local ownership and at best
  **108/115** equal original non-COFF bytes. Removing meaningful
  filename storage shrinks the source to **165/49**, not original
  **171/51**. Some reference-local forms are worse at 102/115.
- `0043B0B0` (248 original bytes / 75 x86 / 12 true COFF fields):
  meaningful aggregate free-resource declaration scopes, reversed
  member field order and natural separated locals retain the native
  control-flow/instruction shape, but produce **191/200** or
  **189/200** equal original non-COFF bytes, not the real native
  texture and three CRT free temporary slots. Reordering fields
  only permutes the later free slots; it does not repair the two
  native texture-delete temporary positions.

The complete individual source, full original compare JSON, compiled
COFF/PDB and negative result matrix are preserved in ignored
`.analysis/f601-archive-reference/`, `.analysis/f601-archive-sequenced/`
and `.analysis/f601-scene-lifetime/`. These provide reproducible
negative evidence rather than speculative stack-padding proposals.

## Minimal reproduction (only the new small translation unit)

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-float-atan2-adapters-f601.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The compiler object, logs and native call-site/relocation receipt are
under ignored `.analysis/f601-atan2-natural-source/`. There was **no
all-unit cold replay**, no fabricated whole executable link or remote
Oracle receipt. The official **943 complete authored exact functions
/ 862,726 original CODE bytes** remain unchanged.
