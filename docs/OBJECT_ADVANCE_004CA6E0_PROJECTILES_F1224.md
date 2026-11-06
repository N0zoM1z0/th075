# F1224 — recover original 004CA6E0 reflection and projectile phases

The [same natural C++ body](../probes/CharacterObjectActions004CA6E0F1222.cpp)
now has **35 of55 actual nondefault states**, adding all **805–811**.
These seven native intervals total **8,797 original interior B /2,328 x86**;
all written intervals total **22,757 original interior B /6,039 x86**.
All **42,511 original whole CODE bytes remain pending**: partial states are
not independently accepted functions. Native extent, independent R048 origin,
constructor/vtable and complete read-only Ghidra exports remain in
[F1222](OBJECT_ADVANCE_004CA6E0_INITIAL_STATES_F1222.md).

## Recovered native behavior and source choices

805/806 retain state5's immediate clear, distinct owner lower thresholds
70/50, upper bound150 and signed **phase<1** predicate. This must not become
phase==0: the original physical CMP1/JGE also handles negative short values.
Both actual reward blocks preserve the conditional995 effect and **four
separate996 effects**, with no invented loop or loop index.

The two initialization orders differ: 805 enables the transform before
clearing velocities; 806 clears them first. Both retain motion before the
D8 increment/clamp, the actual phase0 polar update, separate angle calls,
owner314/318 parameters, effect812 and every observed owner transform write
before tracked813. The tracked-effect ABI remains the independently exact
00453AC0 short/float/float/signed-byte/signed-byte/unsigned-byte contract.

805's ceiling/side reflection limit is **two**; 806's is **one**, with an
additional floor check. Their side tests preserve facing-specific velocity
signs and independently re-read the counter. Angle reflection uses **>0**
in805 versus **>=0** in806, followed by an independent negative-angle test;
these are not an else-if pair. Every sound11 call uses the actual owner
receiver. The new borrowed short sound declaration matches independently
accepted00453D40 and does not define or duplicate that callee.

Four comparison predicates require original physical x87 load order:
`selfY > ownerCeiling` and `selfX > ownerRight`, separately in805/806.
The first source ordering reversed FLD/FCOMP operands and status masks;
reviewed ordering restores all native mnemonic/operand positions. Both retain
hit reset1, native bounds, double0.25 bounce, gravity0.5, rotation40 and exits.

807 retains the exact compound cancellation guard and repeated owner reads,
then tests bounds before the owner400–405/frame0/self-phase0 force transition.
That transition restores alpha, resets phase1 and velocities and returns.
The normal phase2 path emits effects before its polar update; actual speed
17.5 and fresh aim at phase2/frame0 remain. Hit/reset3 and later falling
behavior are separate original paths.

808 retains its different **2000/-1000 X bounds**, phase-qualified speed,
D8 increment, hit-count-qualified wrapping fade and scale0.3 growth. 809/810
remain separately emitted identical gameplay bodies, with repeated owner
500/501/502/503 guards, owner phase thresholds10/4 and Y offset132. Their
native scale expressions, signed facing rotation, raw D0 copy, alpha
subtraction12 and follow-up phase reset remain in order. 811 preserves both
flight ranges, phase counters20/40, owner-F14 reset, actual degree conversion
before FTOL, repeated phase6/frame0 tests and original early exits.

## Selected fresh compiler evidence and unresolved scope

Only this affected draft was serially compiled, using headless pinned VC7.1:
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`.
Selected **flight.obj** emits **22,951 CODE B /6,088 x86**, frame **0x1D8**
versus native0x288. Original this **EBP-4** and actual ESI remain. The partial
switch has36 dense entries and198 sparse bytes. All selected entries/default
and every written mnemonic/operand diagnostic agree, retaining original
fields, scalar bits, COFF constant payloads, call destinations and native
branch ordinals under explicit GPR/negative-stack normalization.

The prefix, **800–807** and **812–829** have zero raw GPR/EBP/width debt.
The prefix frame value and forward branches/tables still depend on missing
code. All current states through829 have the original raw EBP positions;
**808–811 still have32/117/117/181 GPR differences**, with8/4 width differences
in809/810. First GPR difference: **004CCBD7**, whole ordinal **2,526**, in808
immediately after its D8 increment. Native loads ECX, source EAX. Later
990/991/995–997 retain context-dependent GPR/temporary differences.
A real prefix-to-postfix D8 increment control emits identical CODE/DATA,
COFF shapes and symbol names; selected source is restored. Do not repeat it.

Twenty states remain: **830–839,901,903–911**. Complete these in this body
before whole-function comparison and any eventual canonical affected-unit
cold acceptance. No source marker bodies, fake locals, forced storage,
assembly, masks, extra defensive branches or conditional source splits.

`.analysis/f1224-object-4ca6e0-projectiles/` preserves before CPP/HPP, original
native constant/callee/exit receipts, reflection/reviewed-reflection/flight
and postfix-control source/header/object/listing/build-log stages, source
diagnostics and `verified-summary.json`. Ghidra target preflight passed via
the existing read-only wrapper. No accepted source, origin ledger, match
manifest or canonical infrastructure changes; no full CI, corpus replay,
origin retest or new per-function test is required or run.
