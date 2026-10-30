# F803 — Re-test the native 32B fighter default guard in fifteen whole 58KB parents

**Original Japanese TH075 v1.11 native whole-function evidence;
not accepted exact.** The real target `0x00543210`
fighter owns 58,294 callable CODE B and 943
separate after-RET switch DATA B, with exactly
16,471 original x86 instructions. F781 recovered
the actual fallback at original PE `0x00551598`:
**32 original CODE B /10 x86 /two real
zero-addend REL32 calls** to `0x0040FA30`
(state getter) then `0x0040FAC0` (state setter).
Its fallback must short-jump across the adjacent
8-byte getter-only tail reached by only the
four actual earlier action-0/2/4/5 jumps.

The current complete natural C++ has this behavior,
but the original fallback guard still differs by
**four genuine nonfield GPR register-operand bytes**
at native-relative offsets `+0x0A/+0x0C/+0x10/+0x13`:

| Native | Current compiled 58KB source |
| --- | --- |
| `MOVSX ECX,AX` | `MOVSX EDX,AX` |
| `MOV EDX,[EBP-44h]` | `MOV EAX,[EBP-44h]` |
| `MOVSX EAX,[EDX+70h]` | `MOVSX ECX,[EAX+70h]` |
| `CMP ECX,EAX` | `CMP EDX,ECX` |

F803 independently compiles fifteen **full 58KB
source parents** under the pinned ordinary VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` profile:
source baseline; swapping stage/getter operand
order; casting getter and stage to meaningful
signed/int types; reading the observed `+0x70`
field through typed borrowed layout or a reference;
negating the inequality; equivalent integer subtraction,
ternary expression and actual condition scope/
if-else grammar.

**Nine** natural C++ alternatives emit *byte-identical*
entire 59,236-B COFF CODE+DATA objects (58,293
source CODE +943 DATA) and all 1,863 identical
relocation shapes. Independent original PE
field checks attest the entire **46-B shared
suffix and three actual physical native CALL
destinations**, including the two fallback calls;
each of the nine still differs in the same
four genuine GPR bytes. The untouched original
`0x58/0x59/0x60/0x61/0x63` case
source mismatches and 943 native jump DATA
are freshly checked in the baseline parent.

**Six** other source forms change genuine native
control-flow geometry, register operations, source
size or even COFF reference counts. For example,
reversing the operand expression to
`stage == GetNativeAction()` yields 58,295
whole source bytes and two additional x86, while
the superficially plausible ternary form emits
58,315 B; neither is the original native fallback.
Matching semantics or having a nominal 32-B guard
does not establish literal original PE correctness.

```bash
scripts/repo-python scripts/verify-fighter-default-source-grammar-f803.py
```

Only the affected giant is compiled, no whole accepted-unit
corpus cold replay occurs. Full C++, COFF and native
comparison results remain under the ignored local
`.analysis/f803-fighter-default-compare/`.
The complete 58KB giant remains **NONEXACT**
with no new formal authored CODE credit.
