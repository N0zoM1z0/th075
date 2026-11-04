# F1106 — Original three complete frame-dependency functions with 109 genuinely borrowed fighter/HUD/overlay fields

The SHA-pinned Japanese TH075 v1.11 original has three previously
accepted independently whole-byte-exact game callables in ONE
`src/BattleFrameDependencies.cpp` translation unit:

| Complete original game function | Genuine original CODE B |
| --- | ---: |
| `BattleFrame::ResolveBodySeparation` | **1,861** |
| `StateFramePolicies::UpdateTransition` | **847** |
| `StateFramePolicies::AdvanceOverlay` | **1,461** |
| **One original source-object strict COFF comparison** | **4,169** |

F1106 replaces independent unsafe offset casts with physically
observed *borrowed* typed windows in the original meaningful game
source. No historical complete owner layout is asserted or newly
instantiated. Original x87 expression ordering and all native
nonlocal COFF field identities remain unchanged.

## 1. Fighter X position and X velocity, 26 original uses

The original two actor pointers at battle owner+`0x44/+0x48` refer
to the actual two fighting actors. Their **X position is native
actor+0x44**, and independent **X motion is native actor+0x50**,
observed in original `ResolveBodySeparation` and independently
established by earlier exact actor frame and movement functions.
The real velocity initialization, repeated physical collision
separation/boundary pushback and stored pairwise pushback now use
`F1037_POSITION(PLAYER(...)).xPosition` and
`F1037_MOTION(PLAYER(...)).xMotion`. The source replaces **26 actual
original reads and writes**, including five raw pointer casts and
four original macro accesses per actor for velocity, plus four
position writes per actor. No secondary actor pointer array or
extra branch is generated.

## 2. HUD native side float pairs, 14 original uses

The same original state transition source uses the native HUD owner
side-indexed `float` windows at offsets **+0xE4, +0xF4, +0xFC and
+0x104**, indexed by real player side `i` in `[0,1]`. These
values belong to separate **8-byte two-float side windows**,
not to a guessed complete HUD object or a single fabricated struct.
F1106 reuses the independently proven narrow
`F1096_STATUS_FLOAT(this,base,i)` view from the full original
3,510B `BattleStatus::RenderStatus` for the first three offsets,
and applies the same already confirmed physical 2×float view to
**+0xFC** (actual `float` slot and its adjacent right-player value).
The source replaces **14 original side-float accesses**, preserving
the true round-state timer, opacity and status transitions.

## 3. Original seven adjacent overlay float scalars, 69 uses

The original `StateFramePolicies::AdvanceOverlay` physically accesses
**seven contiguous 32-bit floats at owner+0x70/+0x74/+0x78/+0x7C/
+0x80/+0x84/+0x88**, totaling a genuine *borrow-only* **28-byte
window**. The selected source restores these **69 actually used
reads/writes** through `StateOverlayFloatWindowF1106`, whose members
are deliberately named after proven offsets rather than speculating
about source animation business semantics. The original two native
scene mode branches, native per-frame acceleration and float
conditions, time countdown and every compiler-native x87 operation
are unchanged. `sizeof` and `offsetof` constraints guard the
physical native window shape.

## Strict entire-callable cold evidence

The single changed original source object was **cold compiled three
times** under pinned normal VC7.1, with strict replay of *all three
entire original callables* after each genuine source change:
first actor X-position/motion pairs; then HUD side arrays; then
contiguous overlay float window and the real +0xFC pair.
All three actual full original game callables remained **3/3 exact**
with every native CODE byte and original COFF relocation identity
preserved; there was no renumbered local `$L` field acceptance mask.

Reproduce ONLY the affected original object, not the 979-unit corpus:

    scripts/repo-python scripts/replay-exact-units.py \
      --unit battle-frame-resolve-body-separation \
      --unit state-frame-update-transition \
      --unit state-frame-advance-overlay

These **4,169 bytes were already accepted exact**. This refactoring
adds **zero** newly accepted whole-game functions/bytes and does
not imply any unfinished 81KB fighter boss is byte-exact. Source
and original accepted baseline are retained under ignored
`.analysis/f1106-body-separation/`; compiler evidence remains in
normal exact-unit replay output. The original executable and
comparison manifests were not modified.
