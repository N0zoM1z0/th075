# F844 — Original grounded 130 state, distinct from other fighter's 261B finish

The selected SHA-pinned Japanese TH075 v1.11 original
fighter at 005214B0 owns 46,755 original callable CODE B
and 901 separate afterRET packed switch DATA B.
F843 reconstructed the true physical 12C/12D/12E/12F
falling recovery actions. F844 adds the next original
action 130 at physical 00526715..005267DE:
**202 complete original native CODE B /58 x86/
five genuine physically typed PE/COFF fields**.
This is not the other F654 actor's 261B/79-x86
0x130 action and cannot inherit that actor's source.

## Real gameplay CFG and byte evidence

The normal C++ source first updates vertical velocity
POS54 minus POS5C, then performs an x87
ground comparison FLD(POS48), FADD(POS54),
FCOMP the actual global 0065782C.
A grounded collision changes action to 0xA,
zeros original POS48, POS5C, POS54 IN THAT ORDER,
and exits directly to the enclosing function epilogue.
Otherwise it resets true stage/frame-zero initialization,
conditionally changes action to 9 when the native action
getter matches the actual animation status, and
prepares animation 0x1C only at original stage3/frame0.

Four whole-parent normal VC7.1 source experiments
falsify superficially equivalent but byte-inaccurate
expressions: exchanging POS54 and POS48 in the x87 sum,
reordering actual zero assignments, or changing the
original stage3 guard. All variants still emit a
202B/58-x86 interior, but each wrong expression
introduces physical nonrelocation operand-byte
differences against original PE.

The selected source now matches every one of the
original **58 native x86 instruction mnemonics,
sizes and relative locations**, all five typed
original PE operand positions/kinds/zero addends
and game global/call destinations, and every
nonrelocation byte except the original two
enclosing whole-fighter JMP operands at offsets
**84/85 and 198/199**. The remaining original
relative displacement points to the complete
game's distant epilogue 0052CB4F. Neither
operand is masked as COFF or awarded exactness.

## Recompiled entire selected parent

F844 regenerates and physically verifies F843
before compiling ONE newly expanded entire
normal VC7.1 father. The generated callable
source grows from **22,102 B/6,023 x86**
to **22,289 B/6,079 x86**, with the
original separate 901B packed dispatch DATA.

The verifier independently rechecks the complete
current actor 12C/12D/12E/12F native cases
and all 24 true physical PE fields, plus all
ELEVEN earlier original C8/C9/CA/CB/CC/CD/CE/
CF/D0/D1/D2 whole case interiors and their
physical call/global field identities. ALL FIVE
genuine packed 901B afterRET dense/sparse
switch tables are physically checked again.

The current original 46B common default/getter
retains correct physical EBP-0x10 and all
three native REL32 calls but four genuine
nonrelocation GPR operand bytes still differ
at +10/+12/+16/+19. The previous short-parent
34/34 claim does not transfer.

Reproduce ONLY the one affected giant:

    scripts/repo-python scripts/verify-scripted-fighter-grounded-130-f844.py

Fresh full C++, pinned VC7.1 COFF/PDB,
all original native target PE field checks,
and source alternatives remain under ignored
.analysis/f844-scripted-stage130/.

The original 46,755-B callable fighter is
STILL NONEXACT. No independent 130 fragment,
previous case or separate jump-table DATA earns
whole-function authored exact CODE. No full
accepted-unit cold replay occurred.
