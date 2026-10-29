# F540 — original giant-fighter action 0: normal C++ x87 case logic

**New native C++ source-level hypothesis with compiled structural proof,
not a whole-giant CODE match or independent 180-byte function.** The original
Japanese TH075 1.11 PE identity remains SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The physical [F538 case-zero inventory](FIGHTER_ACTION_ZERO_NATIVE_LAYOUT.md)
independently established full *original* case start/end boundaries in all
**eleven** giant multi-switch controller functions. F539 then proved that a
**single ordinary VC7.1 C++ switch** generates the original Reimu and
CharacterMove 66-instruction dispatch geometry and all their native compressed
action-index maps. F540 attacks the *first real action handler itself*, not
just its dispatch table.

## Reconstructed case-zero semantics

An original receiver-relative signed-byte flag lives at `this + 0x3AC`;
the x87 float position at `this + 0x50`. Complete original action-zero
code does the following (method and global source names are provisional):

```cpp
if (signedFlag == 0) {
    ResetAt453E20();
} else {
    if (position > g_ThresholdAt0065782C) {
        position -= g_SubtractAt00657478;
        if (position < g_ThresholdAt0065782C) {
            ResetAt453E20();
            signedFlag = 0;
        }
    }
    if (position < g_ThresholdAt0065782C) {
        position += g_RiseAt00658050; // original global is double
        if (position > g_ThresholdAt0065782C) {
            ResetAt453E20();
            signedFlag = 0;
        }
    }
}
```

The two main float tests are deliberately **separate `if` statements**,
not `else if`: their original executed branches can observe the mutated
float position. Every inequality is significant for original MSVC7.1 x87
`FCOMP`, `FNSTSW AX`, `TEST AH,0x41` and `TEST AH,0x05`, including unordered
cases. In particular, replacing either `<` with `<=` changes the emitted
`JP` conditions; using a float instead of the original *double* rise global
changes `FADD qword ptr` to the wrong instruction. The source compiler
receives genuine signed-character loads, floats/double and a nonvirtual
thiscall to the original `00453E20` routine (whose semantic name is **not**
verified by the call-target address alone).

## Two fresh natural C++ compilations, all eleven complete native cases

The read-only [source/codegen verifier](../scripts/verify-fighter-actionzero-natural-source.py)
first checks **all eleven original giant CODE SHA256 fingerprints**, native
case boundaries, 50 decoded original instructions, original global/callee
addresses, real EBP receiver stack slots and 14 owner reloads. It then
regenerates the F539 C++ single-switch prototypes for the 60,999-byte Reimu
and 82,796-byte CharacterMove giant functions, **replacing only case 0's
dummy marker store** with the natural C++ code above. It uses the pinned
original VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` profile and compiles only
these two small probe translation units, not the complete 60K/82K fighters.

| Physical native case-zero property | Reimu original | CharacterMove original |
| --- | ---: | ---: |
| Natural C++ source case produced | 50 instructions | 50 instructions |
| Original case size / generated case size | **180 / 180 bytes** | **180 / 180 bytes** |
| Ordered original opcode + control/x87 operand grammar | **50 / 50** | **50 / 50** |
| Original receiver-register allocation pattern | **50 / 50** | **50 / 50** |
| Actual candidate COFF references corresponding to original operands | **9 / 9** | **9 / 9** |
| Original `00453E20` thiscall sites | 3 | 3 |
| Original physical constant references | 4 × `0065782C`, 1 × `00657478`, 1 × `00658050` | Same |

The complete native 50-instruction control flow, its internal branch graph,
**all nine physical `REL32`/`DIR32` COFF references**, the native 18 x87
operations, and actual operand widths are validated. Original displacements
and original branch/call targets are **not byte-identical in the isolated
small compiler probe**: the probe has a different receiver EBP stack slot,
external unresolved symbols and a dummy rest of the giant action function.
This is natural source and native-codegen **structural** reproduction,
not an accepted partial `codegen_exact` function.

Cross-checking this same C++ body against the *other nine* independent
fully original giant fighter cases gives **50/50 identical opcodes,
branch-graph roles, float operation/operand widths and 9/9 physical
call/data targets**, modulo normal register allocation rotations. Explicit
local dataflow checking still requires the receiver to be read before its
property accesses and requires every thiscall receiver to be **ECX**;
registers are not simply ignored. Ten original action-zero blocks are
**180 bytes** with disp8 owner-stack reloads. The exceptional
`00564BE0` giant uses **222 bytes** because its real saved owner is at
EBP-0x88: the same **14** owner reloads each widen by exactly **3** bytes.
The 222-byte original has been fully validated, **not** separately
compiled into a fake 222-byte body with padding.

## Run only the affected native compiler probes

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-fighter-action-handlers.py --boss 0x0045DD70
scripts/repo-python scripts/verify-fighter-natural-switch-probes.py --boss Reimu
scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py
# One affected prototype rather than both:
scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py --boss CharacterMove
```

Generated `.cpp`, `.obj`, compiler logs and summary stay under ignored
`.analysis/f540-natural-actionzero-source/`; no manual opaque target bytes,
assembler or made-up case implementation for the remaining 142/150 actions
are part of the accepted repository source. This work changes **zero
exactness-credited CODE bytes**. Real acceptance still requires the
**entire original big function**, correct genuine C++ local lifetimes,
physical relocation fields, complete after-RET data and targeted cold
replay. No full all-unit cold replay or external Oracle receipt was used.
