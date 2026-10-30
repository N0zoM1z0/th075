# F763 — native fighter 2DB collision, abs-distance and typed X operands

**Complete original action grammar, still inside one NONEXACT giant.**
The independently authored original callable fighter is `00543210`,
**58,294 game CODE bytes** plus **943 separately owned after-RET
switch DATA bytes**. Original target is the hash-pinned Japanese
TH075 v1.11 `resources/th075.exe` with SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original `0x2DB` internal handler at **`0054E451..0054E851`**
comprises **1,024 complete native CODE bytes, 290 x86 instructions
and 34 genuine typed PE/COFF fields**. An internal case is not
an independently callable authored game function, so **no formal
CODE bytes are accepted from it** until the whole parent matches.

## Why previous original-source hypotheses were wrong

The older [F715](FIGHTER_COMPLEX_MOVEMENT_F714_F715.md) C++ expressed
real state, animation, ground/contact checks, directional targeting
and random attack selection, but emitted a nonnative
**1,032-B/292-x86** version of the original 1,024-B/290-x86 case.
Simply replacing two raw actor X comparisons with typed members
restored those extra x87 instructions, yet left **15 genuine original
nonrelocation byte mismatches** in the newly compiled whole parent.
These are source-policy and operand-order evidence, not padding.

The pinned original x87 status flags resolve three actual source mistakes:

1. At original native x86 ordinal **109**, the side-edge predicate
   compiles to `TEST AH,5; JP`, not `TEST AH,0x41; JP`. The original
   first side-edge comparison is strict **`actorX < sideEdge`**, not
   the old source `actorX <= sideEdge`. In particular, the unordered
   floating case is not silently treated as ordinary inclusive
   comparison.
2. At original x86 ordinal **220–221**, the threshold for the genuine
   `00412D90` absolute position delta uses `TEST AH,5; JP` to bypass
   facing randomization unless **`abs(deltaX) < threshold`**.
   The old reconstructed `>=` predicate generated the wrong
   `TEST AH,1; JNE` and was a real gameplay logic error.
3. The original subtractive X delta at ordinals **210–213** is
   `MOV EDX,[ACTOR+0x2E8]; MOV EAX,[EBP−0x44]; FLD [EAX+0x44];
   FSUB [EDX+0x44]`. A raw cast first loaded the opponent value
   with `FLD` and changed the `MOV/FLD` instruction order and GPR
   operands. The original uses observed float members on **both**
   the actor and borrowed opponent at physical `+0x44`.

Eleven independently freshly compiled complete-parent C++ controls
tested each real predicate and borrowed member independently and
in combination, never compiling a standalone case. The first guard
fix changed 15→14 wrong bytes, the absolute-distance fix 15→13,
and both combined 15→12; borrowed actor ownership alone reduced
15→3. **All three genuine semantic/typed fixes combined** recover
**zero** remaining original nonfield/nontail mismatch bytes with
correct 290 native mnemonics/widths. The source in
[`FighterApproachNativeF763.inc`](../probes/FighterApproachNativeF763.inc)
uses the validated full game action, not asm, target-pasted bytes,
unreachable padding or artificially unused locals.

## Whole parent, COFF and after-RET evidence

The tracked [F763 one-owner verifier](../scripts/verify-fighter-approach-native-f763.py)
regenerates the **entire** original 58KB source-shaped fighter from
F759–F762 tracked C++, substitutes this one recovered 2DB source,
then cold-compiles **one affected VC7.1 C++ translation unit** under
`/Od /Ob0 /Gy /GR- /GX /GS /Zi`. It independently rereads the
original PE and checks the **entire 1,024-B game case**, all 290
native x86 start/width/mnemonic positions, every one of the **34
originally positioned zero-addend REL32/DIR32 COFF references**,
physical owner opcode and original PE destination, and all remaining
nonfield source bytes. The **only** source bytes not matching the
original in the case are its genuine external full-parent shared-tail
relative JMP displacement bytes; those are explicitly uncredited.

The same fresh parent also rechecks full original C8–CE and
1F6/1F7/1F8 action evidence, and the complete original **943-B
after-RET switch DATA** (156 genuine DIR32 switch labels and 319/319
other original sparse bytes). That DATA is separate from game CODE.

```bash
scripts/repo-python scripts/verify-fighter-approach-native-f763.py
# Original full 2DB: 1024B /290 x86 /34 fields, zero other byte differences
# Complete 00543210 still NONEXACT; no all-unit cold replay
```

The current entire compiled parent is **58,269 CODE B**, versus
**58,294 original**, a **25-byte deficit** plus real residual
nonmatching parent machine code. That deficit grows from F762's
17 bytes because recovering the formerly extra two FPU instructions
shortens the generated 2DB by the genuine eight bytes; it is not
an exact-game-function regression. Original `2FA` is still
**971-B/279-x86** but its source emits **979 B/281 x86** with
incorrect floating operations and associated register phases.
The independent official whole-authored exact ledger remains
**971 functions /865,244 original CODE bytes** (43.84% reviewed).

The generated complete CPP, OBJ/PDB, compiler transcript and original
PE/COFF proof are stored under ignored
`.analysis/f763-approach-native-whole/`; natural source and verifier
are tracked. No other accepted unit was rebuilt or changed, and
no full 971-unit cold replay was performed.
