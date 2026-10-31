# F874 — Borrowed owner 1FD/1FE, correct native CFG and remaining 1-byte codegen problem

The pinned original Japanese TH075 v1.11 fighter
at 005214B0 owns 46,755 callable native CODE B and
five independently owned packed afterRET switch tables
totalling 901 DATA B. Actual original game cases 1FD
and 1FE at 0052882E and 005289B0 contain
**386B/107 x86/9 original PE fields** and
**392B/107 x86/9 original PE fields**, respectively.

Both game states have stage-zero reset and true owner
state counters, launch a stage2/state+7C==1 float
projectile0x50 through native 00453C80, and modify
the truly observed associated owner pointer +0x2E8.
The actual original 1FD invokes the associated
owner's 0040FAC0 action0x66 THEN its native
00453E20 Reset; original 1FE calls those methods
in the reverse order. Both construct another real
facing*80 FILD X update on owner+0x44, then
transition this actor to 1FF or 200, respectively.
No historical owner class layout is asserted:
the borrowed C++ class exposes only two actual
callees, not an instantiable original object layout.

## Important actual control-flow correction

The original owner float-Y comparison is a true x87
global-first FUCOMPP on owner+0x48 against 0065782C.
Within the stage2/frame0 branch the **correct**
native status assignment is:

    status = (ownerY == ground &&
              (ownerStage < 50 || ownerStage > 149))
             ? 1 : 0;

The old plausible nested-if source set status 0
only when ownerY was unequal, accidentally leaving
status unchanged when ownerY was equal but the
owner stage fell in the inclusive range 50..149.
The original x86 JLE at ordinal100 instead
branches to the status=0 store at ordinal104.
F874 restores this functional C++ control flow
and requires source and original x86 jump
destinations BOTH be ordinal104 (not ordinal103).

## Whole original byte/codegen honesty

Ten genuine used-owner source variants were
compiled under normal pinned VC7.1 profile.
An explicit intermediate float value generates
extra MOV/stack instructions. Directly storing
the actual owner+0x44 value restores the
native x86 mnemonic geometry.

One new entire current VC7.1 parent emits
**30,860 callable CODE B/8,652 x86**,
versus F873 30,110B/8,442 x86. All
18 physical original PE field kinds/offsets,
zero addends, true call/global targets
and source callee identities across the
two cases were rechecked.

- Original **1FE** now has matching **392B/107-x86**
  complete mnemonic/width/relative-offset geometry
  and nine physical PE fields. However 66 real
  source GPR operand bytes and four genuine
  enclosing original giant epilogue JMP operand
  bytes still differ: this is NOT original exact CODE.
- Original **1FD** is 386B/107 x86. Selected
  natural C++ is still **385B/107 x86** even though
  all nine physical original PE fields and the
  correct control-flow targets are verified.
  At native x86 ordinal99 original requires
  **CMP ECX,0x95 (6B)** while VC7.1 naturally chooses
  **CMP EAX,0x95 (5B)**. One-byte source-length
  mismatch must NOT be covered by truncation,
  manual register forcing, relocation masking,
  independent case acceptance or patching the EXE.

The newly compiled parent physically rechecks
ALL **46 earlier complete source-backed original
game case interiors**, original PE field locations
and honest nonfield differences, the corrected
stage-zero 1A0 multiplier scope, all five original
901B packed afterRET jump DATA tables, and the
native shared 46B getter's four real GPR wrong
operand bytes (+10/+12/+16/+19) and three
correct original PE call targets.

Reproduce the one affected whole fighter:

    scripts/repo-python scripts/verify-scripted-fighter-owner-dual-f874.py

Current source, VC7.1 COFF/PDB, source expression
controls and strict original PE evidence are kept in
ignored .analysis/f874-scripted-owner-dual/.
Original whole 46,755B giant remains NONEXACT.
No new accepted authored whole callable CODE bytes
and no mass cold replay.
