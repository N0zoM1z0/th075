# F806 — Restore all four native scripted fighter shared-getter entries and the 46B default tail

**Positive new complete original action/tail source recovery,
not entire-function exact acceptance.**

The independently verified user-supplied Japanese TH075 1.11
PE has authored fighter `005214B0`, **46,755 complete
callable CODE bytes** and **901 separately owned after-RET
jump DATA bytes**. The compiled F600 intermediate source
previously represented the original first 23 cases accurately
but ended the default handler in an artificial marker
assignment. The original native source instead has
a real **46-byte, 16-x86** default and shared getter
suffix at `0052CB25..0052CB52`.

## New original physical control-flow evidence

Four and only four full original early actions jump to
the real shared getter `0052CB47`:

| Original action | Original native unconditional JMP |
| --- | --- |
| 0 | `00521709` |
| 2 | `00521891` |
| 4 | `00521974` |
| 5 | `00521983` |

The real native fallback at `0052CB25` first calls
`0040FA30`, compares the returned action against
signed `this+0x70`, and conditionally calls
`0040FAC0(0)`; its own break short-jumps over
the getter to the epilogue. The shared block
`0052CB47..0052CB4E` calls `0040FA30`
once more and then enters original epilogue
`0052CB4F`. Earlier actions 0/2/4/5
jump to that block, not to the default guard or
directly to ordinary epilogue.

New tracked source
`probes/FighterScriptedNativeDefaultF806.inc` and
`probes/FighterScriptedSharedGetterF806.inc`
restores the actual natural C++ control flow;
the four early branch exits use a shared
`goto native_script_shared_getter` label.
**No dummy calls, target-byte copies, fake
local variables or inserted assembly.**

## Whole-parent compiler verification

The verifier *first regenerates and revalidates*
F600's complete first **23 original action cases**
from its tracked source generator, then builds
the *entire affected* VC7.1 parent with the new
shared tail. The reconstructed parent expands from
**6,830 CODE B/1,638 x86** to **6,868 CODE B/1,650 x86**
while preserving the original **901B DATA**,
with authentic first 23 case native instruction
geometry, all 80 true PE fields across their
11 additional second-switch cases, all 139
genuine dense jump pointers and 345 sparse
index bytes from its seven original switch
tables. The original remaining actions are
still explicit diagnostic placeholders;
the source is NOT the complete original 46KB game function.

The newly generated last **46B /16 x86**
exactly matches the original tail's instruction
offsets, mnemonics, sizes, branch layout and
GPR register identities. Three real original
REL32 call offsets `+0x04/+0x1C/+0x26`
resolve to authentic PE destinations
`0040FA30/0040FAC0/0040FA30`, all with
zero source addends. Every early action's
actual JMP-to-shared-getter location matches
the original **relative to the beginning
of its own independent action case**.

The only four different non-relocation tail
bytes are the physically honest saved-receiver
EBP displacements at original suffix offsets
`2/13/26/36`: **original EBP-0x10**
versus incomplete current source **EBP-4**.
These are NOT masked as exact. The full
native game function is much longer than the
current source, so no 46-byte or internal
case exact-unit credit is possible.

Targeted reproduction:

```bash
scripts/repo-python scripts/verify-scripted-fighter-native-shared-tail-f806.py
```

This invokes only the selected F600 original
`005214B0` verification plus the changed
single full-parent VC7.1 compilation; **no
979-unit cold replay**. Original full-length
source, COFF, compiler logs, and physical
verification JSON are regenerated in ignored
`.analysis/f806-scripted-default/`.
