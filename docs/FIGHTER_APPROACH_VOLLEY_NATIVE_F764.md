# F764 — original fighter 2FA state geometry restored; register phase still nonexact

**Game-source reconstruction inside one original 58KB whole fighter,
NOT exact callable-game CODE.** Pinned Japanese TH075 v1.11 original
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Actual game-authored enclosing `00543210` contains **58,294 CODE
bytes** and separately owns **943 after-RET switch DATA bytes**.
Native original action `0x2FA` occupies `005509CC..00550D97`:
**971 complete CODE bytes, 279 authentic x86 instructions and 31
real typed PE/COFF fields**. This is not an independently callable
function and earns **zero** new exact game CODE credit.

## Six real original gameplay/float corrections, not syntax padding

Earlier F699/F762 source represented the genuine stage, ground,
contact, signed-facing, opponent-relative positions, randomization,
auxiliary action and 7D/7E projectile policy, but emitted extra x87
operations, wrong signed comparison branches and an unstable GPR
allocation phase. Initial whole-parent source emitted **979 B/281
x86**, rather than the pinned original **971 B/279 x86**.

The pinned native `FCOMP/FNSTSW/TEST AH/JP` status flags and exact
original branches establish six actual source corrections. The source
[`FighterApproachVolleyNativeF764.inc`](../probes/FighterApproachVolleyNativeF764.inc)
now implements:

1. The early genuine ground collision uses
   `POS48 + POS54 <= threshold` rather than the old `>` source.
   Native x87 ordinal **46** is `JP`, not the old generated `JNE`.
2. The first actor-side boundary predicate is strict
   `actorX < sideEdge`, not `>=`; native ordinal **110** is `JP`.
3. The first opponent-relative X predicate is
   `opponentSideX + delta >= actorX`, not `<=`;
   its native ordinal **132** is `JNE`.
4. The other opponent-relative X predicate is
   `otherSideX - delta < actorX`, not `>=`;
   its native ordinal **144** is `JP`.
5. Real `00412D90` absolute actor/opponent X separation triggers
   facing selection for **`abs(deltaX) < threshold`**, not the
   former `>=`; native ordinal **202** is `JP`.
6. The original absolute-distance argument reads the observed actor
   and opponent **float members at +0x44**, not independent raw
   float loads. This restores the genuine native `MOV;MOV;FLD;FSUB`
   machine-instruction ordering around ordinals **190–194**.

The genuine `ContactAt454EE0` guard applies only to the two side-edge
conditions, not the other two opponent-relative X comparisons,
as independently reconstructed for related 1F6/1F7/1F8 and 2DB.
These corrected predicates preserve the original distinction between
ordered and unordered x87 floating-point cases.

## Fresh full-parent controls and precise remaining negative

**Twelve independently compiled whole-parent source alternatives**
varied these real six features one at a time and in combinations.
The starting 971-B/279-x86 candidate had **seven native mnemonic
mismatches** and **171 genuine nonfield byte mismatches**. Each
independently corrected predicate reduced a different native x87
branch mismatch, and borrowing both X operands restored the original
x87 GPR evaluation order. The combined natural source emits the
original full **971 CODE B /279 x86** with **ZERO mnemonic or width
mismatches** and **31/31 true zero-addend typed original PE/COFF
reference fields** at their original instruction owners and
independently checked PE destinations.

**It still has 156 genuine nonrelocation/nontail machine-byte
differences**, primarily EAX/ECX/EDX operand allocation through
the real source state. These bytes are not omitted, patched, ignored
by a false whole-function match, or called semantically equivalent
exact CODE. The source is native-geometry correct, but **not
byte-exact**. Reconstructing preceding compiler register phase or
real C++ source lifetime is still necessary.

## Related whole native source and independent DATA

The tracked [one-parent F764 verifier](../scripts/verify-fighter-approach-volley-native-f764.py)
regenerates the actual F759–F763 source and compiles **ONE** new
entire fighter VC7.1 parent using `/Od /Ob0 /Gy /GR- /GX /GS
/Zi`. It rereads original native PE boundaries, all 279 complete
2FA instructions and all **31** relocation types, zero addends,
source symbols and true physical original PE destinations, then
requires precisely the **156 remaining real nonfield byte differences**
rather than silently accepting a partially corrected case.

The new entire parent also re-verifies 2DB (**1,024 B/290 x86/34
true refs**, original nonfield/nontail bytes identical), the three
full 1F6/1F7/1F8 bodies, four C8–CB actions, three CC–CE actions,
and entire original **943-B separate after-RET dispatch DATA**
with 156 physical DIR32 switch labels and 319/319 other native
sparse bytes.

```bash
scripts/repo-python scripts/verify-fighter-approach-volley-native-f764.py
# 2FA: 971 B/279 x86/31 physical PE references, mnemonic/width aligned
# 156 true GPR/operand nonfield bytes still wrong; no exact CODE credit
# Only ONE affected entire fighter compiled, no all-unit cold replay
```

The entire new source emits **58,261** of the original **58,294
CODE bytes**, a **33-byte length deficit**, plus other actual
nonmatching operands and incomplete native whole-parent control
flow. Its shrinking from F763's 58,269 B removes the two wrong
extra x87 instructions; proximity in total size is not byte exact.
Official accepted exact whole-authored ledger remains **971
functions /865,244 original CODE B** (43.84% reviewed). The
compiler CPP, COFF/PDB, trial logs and evidence stay under ignored
`.analysis/f764-fighter-2fa-predicates/` and
`.analysis/f764-approach-volley-whole/`; normal source/verifier
are tracked. No original PE modification, synthetic padding,
full 971-unit cold replay or split-case CODE credit was used.
