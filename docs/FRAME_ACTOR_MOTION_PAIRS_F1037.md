# F1037 — Physical paired float windows in the native battle frame and actor motion

The pinned Japanese TH075 v1.11 complete frame/actor code reads
adjacent floating-point axis fields at actor **+0x44/+0x48** and
**+0x50/+0x54**. The first window holds current X/Y position;
the second holds the corresponding X/Y motion contributions used
by `AdvancePosition`. `CheckHorizontalLimits` reads the X position
on this and the real peer actor, and the guarded action handlers
read the Y position. These operations are original authored game
logic, not a mathematical approximation or proposed new gameplay.

Before F1037, two original complete functions expressed the positions
as many repeated C-style byte casts, and two other functions read the
same physical Y as `FIELD(float, this, 0x48)`. The exact same verified
address relationships now use two narrow, typed borrowed views:

- `FrameActorPositionPairF1037`: `xPosition` at native +0x44,
  `yPosition` at native +0x48.
- `FrameActorMotionPairF1037`: `xMotion` at +0x50,
  `yMotion` at +0x54.

Each window is 8 bytes with an independently checked +4 Y offset.
The still-unidentified storage between +0x48 and +0x50 is
**not** assigned a speculative member. Neither view is a complete
historical actor; no source allocates or embeds the borrowed classes.
Field read order and expression grammar are preserved, including the
original native short-circuit boundary check, repeated peer velocity
reads, direct X clamp, and floating motion additions. The typed
source code is not a fabricated register-manipulation aid.

Targeted cold verification rebuilt the **one affected `BattleFrame.cpp`
translation unit** and replayed **all 8** of its original exact units.
Each entire callable remained exact, with **1,967/1,967 prior
accepted original CODE bytes preserved**. The replay includes the
289B full actor motion step, 133B horizontal-limit predicate,
132B guarded state, 304B action chooser, 179B counter updater,
859B battle frame advance and both remaining frame functions.

No new original authored exact CODE bytes were added, and no
existing COFF/target manifests or target bytes were changed.
The 25 independently attributed nonexact original functions
remain open. No 979-unit mass replay was run.
