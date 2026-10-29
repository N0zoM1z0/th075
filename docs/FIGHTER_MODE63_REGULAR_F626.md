# F626 — five complete 109-instruction native mode-event cases in giant fighters

**Pinned original Japanese TH075 1.11 PE** SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`. All containing fighter `Advance()` functions remain **NONEXACT**. These are strictly verified **internal case bodies**, never separately accepted authored whole-function CODE.

F624 proved two special original cases `0x63` have **118 x86** and an extra `this+0x370+index` bonus-action branch. Seven other fighter originals contain an authentically different **109-x86** `0x63`, without the bonus branch. The real original second packed-switch sparse map has `0x63` at dense slot25 and the default handler at slot26. **Slot26 does not bound the native 0x63 game CODE**: the next actual original handler is action `0x8C`, or action `0x89` in the special `0058AF60`. The verifier validates the physically registered native next handler and the source's next correctly typed case marker, rather than cutting a truncated subrange at the default table entry.

The authentic control flow tests original signed byte global `006714B4` using `mode!=3 || this+0x2CD == 0` (first native `JNE` reaches ordinal7, second reaches ordinal27); uses signed-byte indexed conditions at `this+0x32A+index`, owner state `this+0x2E8`, live frame action getter and real `0x31C`/`0x5F` transitions. When the native `+0x32A` result equals 2, original `0040FAC0(0x31C)` ends that case directly, with **no** optional `+0x370` bonus action. Other two independent branches handle `==1` and `==0`, optionally set the original byte `this+0x3CF`; original `0040FA30` and `0040FB40(2)` complete the sequence. The actual source is [`FighterMode63BasicF626.inc`](../probes/FighterMode63BasicF626.inc), compiled under genuine pinned MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`.

[`verify-fighter-mode63-basic-f626.py`](../scripts/verify-fighter-mode63-basic-f626.py) fresh-compiles only the selected **whole giant C++ source TU**, strictly checks all **109 native original x86 widths, mnemonics, GPR/x87/CFG roles** and 7 actual zero-addend original PE-targeted COFF fields. The native fields are real global `006714B4` at x86 ordinal0 (`DIR32`), four `0040FAC0` action calls at ordinals22/48/71/94, getter `0040FA30` at ordinal99, and auxiliary transition `0040FB40` at ordinal107. Only the physically proven native `DIR32` global operand is normalized against the source's unlinked `[0]`. It also reruns all **30 earlier native case grammar/COFF checks through F614 plus the entire separately owned original after-RET dense/sparse jump DATA** in the *same fresh new whole giant OBJ*.

| Still-unmatched original giant owner | Original complete `0x63` CODE | Native x86/GPR/x87/CFG | Real PE/COFF fields |
| --- | ---: | ---: | ---: |
| `004AC040` | 417 B | **109/109** | 7 |
| `00486550` | 417 B | **109/109** | 7 |
| `00543210` | 417 B | **109/109** | 7 |
| `004D7E70` | 417 B | **109/109** | 7 |
| `005214B0` | 417 B | **109/109** | 7 |
| **Five strict interior cases** | **2,085 native CODE bytes** | **545 x86 roles** | **35** |

**Two original negative controls are retained, not hidden:** native `004F7130` (109 x86/416 native bytes) and `0058AF60` (109 x86/417 bytes) generate the same 109 x86 source instruction count and seven typed fields but still have **67 original GPR/CFG role mismatches each after source global resolution**. The former also differs in opcode width and the latter's true next action is `0x89`; neither receives strict case credit. Other actors belong to separate 118/138-instruction families. No fabricated saved-frame locals, ASM, manual original byte graft, fragment-as-function acceptance or full 943-unit cold replay was used.

Previous F598–F624 strict source case study: **341 original interior action bodies /88,614 original inner CODE bytes**. F626 adds five/2,085: **346 strict native interior case bodies /90,699 original native inner CODE bytes** across independently compiled whole giant probes, **not 346 accepted independently callable full functions**. Official authored whole-function exact ledger remains **943 whole functions /862,726 original CODE bytes**.

```bash
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py --boss 0x004AC040
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py --negative-actor 0x004F7130
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py --negative-actor 0x0058AF60
# Optional only the five newly affected giant TUs:
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py
```

The new complete source/COFF/PDB/compiler logs, real native case physical field receipts and independently negative register proofs are retained in ignored `.analysis/f626-mode63-regular/verified/`. Initial independent experiments and an archived duplicate alternate-verifier draft remain in ignored `.analysis/f626-mode63-regular/`.
