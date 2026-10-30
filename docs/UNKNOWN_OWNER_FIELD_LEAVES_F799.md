# F799 — Two complete native owner-field leaves with honest unknown provenance

**New complete target-machine-code matches, not formally accepted
original authored functions.** The original Japanese TH075 v1.11
`resources/th075.exe` PE was hash-verified and independently
disassembled; both candidates are in the current native
`config/functions.csv` and remain
`unknown/review` in `config/function-origins.csv`.
No original independent owner or historical implementation
provenance has been proved.

## Complete physical whole functions

| Original native entry | Actual source policy | Native CODE/x86 | Real PE/COFF fields |
| --- | --- | --- | --- |
| `004135F0` | Set byte field `this+0x24`, then dword fields `this+0x1C/+0x20` | **40/40 B, 16/16 x86** | 0 |
| `00454F70` | Read pointer `this+0x74`, then flags dword `+0x3C`, return bit-mask `0x20` as unsigned greater-than-zero | **31/31 B, 15/15 x86** | 0 |

Both methods are naturally compiled from the *same*
`probes/UnknownOwnerFieldLeavesF799.cpp` source under
the pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` profile.
The temporary C++ classes are explicitly borrowed
source-compatible views: byte offsets in the PE are
observed; earlier private fields, complete class sizes,
historical names, inheritance and additional methods
remain unknown. These partial layout views must never
be instantiated or used to assert nominal historical type identity.

The setter's real original thiscall convention ends in
`RET 0x0C`, consistent with its three true source
parameters. The flag getter ends in plain `RET`;
its original native `AND 0x20` is followed by
`XOR EAX,EAX; CMP EAX,EDX; SBB EAX,EAX; NEG EAX`.
A natural unsigned `0 < (mask & 0x20)` expression
emits that *exact* 31-byte C++ code.

The verifier additionally builds a **deliberately
semantically equivalent C++ control** with `mask != 0`:
the compiler emits **29 B /14 x86**, not the
original 31 B /15 x86. Semantic plausibility alone
is therefore insufficient for exact-source claims.

## Reproducible validation and limits

```bash
scripts/repo-python scripts/verify-unknown-owner-field-leaves-f799.py
```

It regenerates the full VC7.1 COFF methods from source,
reopens the original pinned PE, checks complete per-symbol
sizes and exact full original machine bytes/instruction
boundaries, requires zero original relocation fields,
and checks the original provenance record remains unknown.
No function truncation, embedded machine-byte arrays,
ABI abuse, or original binary changes are used.

Neither unknown candidate appears as a formally
accepted independent authored unit. Real exact
code generation is not evidence of historical
origin; **zero new authored exact functions or
authored CODE bytes** are counted in the official
`config/matches.csv` / `config/exact-adoptions.json`.
The user's 98% goal remains incomplete.
