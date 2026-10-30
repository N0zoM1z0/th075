# F869 — Actual 1F7 307B special stage4–6 transition

Original pinned Japanese TH075 v1.11 fighter 005214B0
owns 46,755 callable native CODE B and five original
afterRET packed switch DATA tables totaling 901 B.
The real original action1F7 at 00528166..00528298 is
**307 complete native interior CODE B/90 x86/
11 physical PE call/global fields**.

At stage0/frame0 the normal C++ performs the original
ResetAt453E20, state counter writes and FLAG clear.
When the motion height is positive, it subtracts
the real global 00657478 and clamps at threshold0065782C.
The game-specific transition fires ONLY for stage>3
and stage<7 and unsigned this+0x511 equal 0x14,
whereupon action0x1F8 is set, the actor resets
and native game effect00455B30 is called before
returning directly to the *enclosing fighter* epilogue.
After normal action0 checks, stage3/frame0 fires
sprite0x337 through native 00453A70 with genuine
8-bit facing and calls PrepareActionAt453D40(3).

The original PE, not the preceding 1F6 source, proves
the different stage bounds, action1F8, sprite0x337
and Prepare3. Five entire selected VC7.1 parent
sources test the native C++ versus wrong upper bound,
wrong unsigned flag value, wrong sprite and Prepare2.
Each wrong control introduces a new original byte
mismatch even though its whole source has the same
length/instruction/PE-field counts.

A fresh full selected parent compiles **28,756 callable
CODE B/8,039 x86**, versus F868 28,464/7,951.
Within its new complete original 1F7 interior, all
90 native mnemonic/size/address-offset pairs and
11 PE fields are physically matched. The real native
COFF field offsets are [26,70,89,107,176,184,192,
205,229,288,298], with all types/zero addends,
source symbols and actual original target destinations
rechecked independently.

The source remains **NONEXACT**: 50 genuine native
register-operand nonrelocation bytes plus two real
enclosing-giant final JMP operand pairs at case-relative
+197/+198 and +303/+304 remain different.
The newly generated parent also re-verifies all
40 earlier native original source-backed game states,
their typed PE fields, original 1A0 guarded multiply
control flow and honest register/JMP negatives,
all five original 901B separately owned jump tables,
and the native 46B getter's four current GPR errors
(+10/+12/+16/+19) and three correct PE call targets.

Targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-conditional-1f7-f869.py

Complete source, VC7.1 COFF/PDB, alternate full-parent
controls and physical Japanese PE receipts are retained
under ignored .analysis/f869-scripted-state1f7/.
The original 46,755B whole fighter is still NONEXACT.
No independent case, suffix or DATA is credited as
whole callable authored exact CODE; no mass cold replay.
