# F562 — independent 102/115/102-instruction native fighter actions in 004D7E70

**Complete original Japanese TH075 1.11 whole-boss evidence and normal
VC7.1 source-codegen experiments; not an accepted 43K whole function.**
Original PE SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Whole original fighter `004D7E70` has **43,601 native CODE bytes**, seven
actual compiler-generated switch groups, and **969 original post-RET
DATA bytes**. These entire function/switch fingerprints are checked
before compiling any new diagnostic source. No other role's case
addresses, constants, or guessed original owner type are substituted.

## The native three-case algorithm differs from every prior source family

The original first switch's actual seventh/eighth/ninth/tenth DWORD
handler targets physically delimit action cases 6, 7, 8. Their **complete
original CODE sizes** are **352, 393, 352 bytes**, and the corresponding
complete x86 instruction counts are **102, 115, 102** respectively.
All three retain the true native `this+0x511` unsigned state tests 3/5/4,
the original `0040FAC0` arguments 0xCC/0xCD/0xCE, signed-short frame/stage
action update, two x87 contact tests and genuine actor vtable method.
Original stage threshold is **2**; actual `this+0x54` velocity is
**15.0f**, and `this+0x5C` speed is **0.65f**. Original stage-position
initializers in action 6/7/8 are **0.0f / +5.0f / −5.0f** respectively.
The stored native floats were independently read at the real physical
`MOV [owner+field], immediate` instructions.

Only **action 7** contains a true extra-stage x87 branch:

```cpp
if (S16(0x62) == 4 && POS54 < g_ExtraThresholdAt00657D14)
    SetAuxActionAt40FB40(5);
```

This real 13-instruction branch occurs *after* collision, before frame
increment. Neither native action 6 nor 8 includes this call. Unlike the
117-instruction F556 or 115-instruction F557 families, **all three
original cases omit `FLAG = 0` during the stage motion stores**.
The actor's final native virtual-call register also genuinely changes:
**`call dword ptr [eax]` for action 6**, but **`[edx]` for actions 7/8**.
The compiler emits these actual per-action GPR choices naturally from
the correct source conditions and flow; the code does not require inline
ASM, copied target bytes or synthetic locals.

## Physical COFF/source proof: 1 new affected original-backed C++ compile

[`scripts/verify-fighter-split-stage-4d7e70.py`](../scripts/verify-fighter-split-stage-4d7e70.py)
reads all native whole-giant CODE and physically bounded inner cases
from the pinned PE, regenerates a C++ `switch` with these three true
cases and **diagnostic-only marker stores for other unfinished cases**.
The new source TU is freshly compiled under pinned MSVC 7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, without building any of the 943
accepted exact units. Results:

- **319/319 complete original x86 GPR/x87/control-flow instructions**,
  every physical source case byte length and real per-case virtual-call
  indirect register form are reproduced.
- **20/20 genuine physical `DIR32`/`REL32` original call/float COFF
  references**, six in actions 6/8 and eight in action 7, all checked
  for native instruction ordinal, field kind and original callee/global.
- **140 physical original-style switch DWORD COFF destinations**, all
  original repeated/default case partitions, **409 byte-identical native
  compressed index bytes** and the complete **969 original after-RET
  DATA-shape bytes** are verified and remain separate from CODE.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-boss-family.py
# Rebuild only this new selected TU, not all-unit cold replay:
scripts/repo-python scripts/verify-fighter-split-stage-4d7e70.py
```

All source, compiler logs, COFF/PDB and structured comparison output
remain under ignored `.analysis/f562-split-stage-source/`; original
negative and codegen controls under `.analysis/f562-4D7E70-actor-case/`.
**All 1,097 real inner case CODE bytes remain part of the still-unmatched
whole 43,601-byte giant**. There is no exact standalone 352/393-byte
function or accepted whole-fighter coverage, no manual stack padding,
all-unit cold replay or external Factory/Oracle receipt.
