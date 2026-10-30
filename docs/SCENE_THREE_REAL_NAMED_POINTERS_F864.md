# F864 — Three genuinely freed named Scene pointers do not restore original EBP slots

The pinned Japanese TH075 1.11 virtual Scene destructor
at 0043B0B0 has **248 complete callable CODE B/75 native
x86/12 physically typed original PE call/global fields**.
The native physical temp ownership is texture EBP-0x14,
scalar-delete receiver EBP-0x10, and three actually
freed resources EBP-0x18/-0x1C/-0x20.
Earlier aggregate-based source achieves
only **191/200 original nonrelocation byte equality**.

F864 tests a different source hypothesis:
three real, separately declared pointer variables,
each assigned from and genuinely passed to free
for scene fields +0x4C/+0x50/+0x54, rather than
an aggregate with three released members.
The twelve entire pinned VC7.1 /Od /GX
source variants include declaration after texture,
before texture, at function top, reversed/rotated
declaration order, register/volatile variants,
branch-scoped true named locals, and actual
branch-scoped references or pointers to
real member fields. No declared variable
is inert; all models retain genuine free,
texture delete, state-setter and base destructor.

| Genuine source type | Native-length whole CODE | Original physical result |
| --- | --- | --- |
| Previous aggregate baseline | **248B/75 x86/12 PE fields** | **191/200** nonrelocation original bytes |
| Nine independent named/branch pointer source models | **248B/75 x86/12 PE fields** | **189/200** original nonrelocation bytes, WORSE |
| Two true branch reference/pointer-to-field sources | **254B/78 x86/12 source COFF fields** | Wrong original whole extent and genuine extra x86 |

The independent whole verifier physically checks
all twelve original call/global symbol identities.
For all ten 248B/75-x86 source variants it checks
each original native mnemonic/width and all twelve
physical PE field offsets, relocation kinds,
zero addends and real game targets, comparing
all 200 nonrelocation machine bytes without
hiding any wrong stack allocation operands.

The named pointer source still allocates texture
and delete receiver at EBP-0x20/-0x1C, while
the real freed pointer locals become
EBP-0x10/-0x18/-0x14; native slots are
-0x18/-0x1C/-0x20. Moving declarations
before the clock condition does not change
those compiler slots. The actual source
pointer references instead materialize three
additional x86 instructions and 254B CODE.

Thus the independently used named free-pointer
source lifetime is physically falsified
as an original five-temporary-slot solution.
No source-equivalent cleanup sequence is
accepted without entire native byte exactness.

Targeted reproduction of ONLY Scene:

    scripts/repo-python scripts/verify-scene-three-named-release-f864.py

Full C++ variants, VC7.1 COFF/PDB and
original target PE receipts are retained in
ignored .analysis/f864-scene-named-release-slots/.
The authored Scene destructor still NONEXACT;
zero new accepted whole callable CODE,
no accepted-unit cold replay.
