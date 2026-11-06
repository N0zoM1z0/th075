# F1158 — Complete Boss operand and jump-table destination proof

The original `0050A580` callable remains NONEXACT: 81,539 original
CODE bytes versus 81,542 normal C++ bytes, with 522 wrong GPR
instruction positions and five wrong instruction widths. This whole
audit adds no accepted CODE bytes and does not waive those differences.

## Complete original references and operands

The existing one-parent verifier now independently checks **all 1,357
CODE relocation targets**, including the two actual switch-data references,
against the pinned Japanese PE. It reads each original physical field at
the corresponding native instruction/within-instruction position and
resolves the actual REL32 or DIR32 destination. Local source offsets are
mapped through the complete native instruction sequence or original
afterRET extent. No target PE or COFF file is patched.

An in-memory candidate copy with those genuine relocations resolved is
decoded across the entire 17,435-x86 callable. All nonbranch operands
agree after diagnostic normalization of the remaining EAX/ECX/EDX
scratch identities and their word/byte forms. Memory access widths,
object displacements, stack operands, immediate values, non-scratch
registers and x87 operands are retained in the comparison. All 1,834
actual direct branch destinations are independently compared by native
instruction ordinal, so they are not hidden by operand normalization.

The exact remaining instruction/operand debts are written to
`.analysis/f1068-boss-live-all-native/whole-native-operands.json`.
The only five width differences are at whole ordinals 10,330, 10,461,
10,729, 17,328 and 17,333, in the provisional 35B/35E/3E6 handlers.

## All 92 dense-table destinations are now explicitly compared

Pairwise table-alias equivalence alone does not establish which original
instruction a source table entry reaches. The verifier now requires
**every one of the 92 original dense DIR32 targets** to have the same
whole-instruction ordinal as its actual source COFF label. This passed,
as did the complete 199-byte sparse dispatch map and all original
5,717 EBP stack operands /0x3A0 frame /saved-this EBP-0xAC.

These are logical destination and operand proofs. Candidate whole CODE
and therefore physical relocation offsets are still not identical to
the original; neither original relocation-offset equality nor full
callable byte equality is claimed.

## Consistent existing helper parameter views

The caller-side declarations now use three float coordinates for native
`0040FBB0` and a signed short animation counter for `0040FB40`, as in
the existing independently cold-exact helper sources. All coordinate
inputs at the affected call sites remain zero. This preserves all
**82,109 generated CODE+DATA bytes** and all **1,449 physical COFF
offset/kind/addend/local-offset records**. Only the two corresponding
external decorated names change; the native PE destinations are unchanged.
The full parent cold verification passed with the corrected declarations.

Six natural operator/helper-parameter probes and six switch-exit probes
preceded the complete audit. None reduced the GPR debt; two arithmetic
forms worsened an operand. Their whole-source candidates were preserved,
and no artificial register steering or padding was adopted.

Reproduce only this one parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Detailed source/COFF/field receipts and the before/after helper declaration
comparison remain under ignored `.analysis/f1154-whole-native-operands/`;
the negative controls remain under `.analysis/f1152-native-gpr-operators/`
and `.analysis/f1153-native-switch-exits/`. The current accepted ledger
remains 981 entire exact functions /868,662 original CODE bytes.
