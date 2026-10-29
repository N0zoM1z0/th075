# F618 — complete original 45-byte polymorphic background-owner constructor

**Genuine pinned Japanese TH075 1.11 whole-original CODE reconstruction;
source-written versus compiler-generated provenance UNKNOWN, no new
accepted authored CODE.** Original executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Original complete game constructor machine-code evidence

The original registered whole native function `00449DE0` is **45 CODE
bytes, 16 complete x86 instructions**, not a fragment of the enormous
BackgroundStage loaders that call it. Its original `__thiscall` code
sets a genuine native vtable DWORD, constructs a real member at
`this+4`, constructs another real member at `this+0x18`, and returns
the original receiver with the native `MOV ESP,EBP; POP EBP; RET`
epilogue. The independently verified original actual PE operands are:

| Native full CODE field | Original typed field | Real native destination |
| --- | --- | --- |
| `+0xC` | `DIR32` polymorphic vtable | `0065844C` |
| `+0x17` | `REL32` first nontrivial member ctor | `00412620` |
| `+0x22` | `REL32` second nontrivial member ctor | `0040AD80` |

Both true native member offsets `+4/+0x18`, all x86 register roles,
operand widths and source/target call order are separately
validated. These original physical vtable and member constructor
**pointers** are proven; the complete virtual table's contents,
original class symbol spelling and historical C++ type declarations
are **not** reconstructed from these three pointers alone.

## Independent explicit and implicit natural VC7.1 sources

Tracked [`BackgroundOwnerConstructorsF618.cpp`](../probes/BackgroundOwnerConstructorsF618.cpp)
uses an ordinary **explicit empty default constructor**, a real
polymorphic owner, and two legitimately nontrivially constructed
member types. The first member has a 20-byte real data extent,
placing the second member at the genuine `this+0x18` offset.

A separate complete ordinary C++ source,
[`BackgroundOwnerConstructorsImplicitF618.cpp`](../probes/BackgroundOwnerConstructorsImplicitF618.cpp),
declares **no owner constructor**; instead, ordinary placement-new
causes VC7.1 to generate the owning type's implicit default special
member. Both fresh original-profile VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` translation units emit a
**complete 45-byte, 16-instruction** native constructor with exactly
three physical COFF fields, same real symbol identities and zero
addends. The source compiler's three relocatable DWORDs are filled
only with their independently observed original PE addresses and
REL32 callee offsets. Both complete resolved machine-code buffers
then compare **45/45 equal original bytes**, including **33/33
nonrelocation bytes** and all three full four-byte fields.
No native byte graft, manual assembly, incomplete-prefix comparison,
truncation, fake saved temporary or external debugger behavior is
needed to reproduce this whole original function.

## Independently scanned original native caller evidence

The targeted verifier
[`verify-background-owner-constructor-f618.py`](../scripts/verify-background-owner-constructor-f618.py)
independently scans real decoded `CALL` instructions in all
**4,351 registered native original PE function extents**. There are
**36 true direct calls from 36 distinct currently authored
BackgroundStage `LoadBGxx` functions** to original constructor
`00449DE0`. This confirms the function is genuinely used to
initialize the real game background resources; the direct calls
are not guessed XREFs or inferred from the F618 source.

However, these game-owned *callers* cannot decide whether the callee
was an explicitly written empty constructor or the compiler's implicit
default special member. Both different C++ alternatives produce
indistinguishable **whole original machine CODE** under the pinned
compiler. Existing `config/function-origins.csv` therefore retains
`00449DE0` as **`unknown` with `review` disposition**, alongside the
other unresolved origin-ambiguous constructors. No original function
name or complete class ownership is asserted from a matching source
probe alone.

**F618 contributes 45 source-backed whole-original CODE bytes /16
complete native x86 /3 real original typed COFF fields, but ZERO
accepted new authored exact whole functions or bytes**. With F616,
there are four separately source-backed whole origin-unknown game
constructor functions totaling **133 original CODE bytes** (still
uncredited). Official accepted whole-authored coverage remains
**943 exact functions /862,726 native CODE bytes**, with 95 origin
review cases still pending. This is separate from F617's incomplete
giants and partial native case source proofs.

No all-unit cold replay, remote Oracle acceptance, native executable
modification or ungrounded origin promotion occurred.

## Reproduce only two new original constructor source TUs

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-background-owner-constructor-f618.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Full source/COFF/PDB compilation logs, authentic original PE linked
byte comparison receipts and the native 36-caller graph live under
ignored `.analysis/f618-background-owner-verified/`. The two initial
selected C++ object/compiler controls are retained in
`.analysis/f618-bg-constructors/`.
