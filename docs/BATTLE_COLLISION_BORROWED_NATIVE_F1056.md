# F1056 — Typed battle collision bounds and actor fields, five complete native functions unchanged

The pinned original Japanese TH075 v1.11 battle collision actor methods
borrowed the same native physically observed fields through independent
raw byte-offset casts. F1056 replaces these in the real accepted source
`src/BattleCollision.cpp`, not just a synthetic analysis probe.

- The stage/actor's four 32-bit signed collision bounds at `this+0x34`
  through `this+0x40` form one **16-byte `RECT` borrowed window**.
  `BattleCollision::ClearBounds` still initializes native
  `(-10000,-10000,10000,10000)` fields, and `IncludePair` performs the
  original exact conditional comparisons/updates for two real input RECTs.
  The borrowed view is a pointer to in-place storage; it is **not** a
  pointer field at +0x34 and does not assert a complete original class.
- Original `BattleCombatResponses::ApplyImpact` borrows adjacent **signed
  WORD health current at actor+0x324 and recoverable at +0x326**, using
  the already independently native-replayed `FighterVitalBorrowedF999`
  view. The existing native `F1027_TIMERS` WORD pair at +0x80/+0x82
  remains unchanged.
- Original collision rectangle transformation reads the actual signed
  float X/Y position fields at actor+0x44/+0x48 using the previously
  verified borrowed `F1037_POSITION` view. All four genuine native
  `CeilCollisionCoordinate` arguments, source RECT axes and facing
  conditional bounds remain unmodified; there is no invented byte
  alias or fake local.

This is a semantic recovery of overlapping source roles while retaining
normal pinned VC7.1 C++ code-generation grammar. No new method, memory
allocation, asm, target-byte patch, or inferred complete actor layout
was introduced. All the already exact entire native callable units from
**the one affected C++ translation unit** were cold-built together and
verified independently against pinned original PE COFF/target fields:

| Native complete match unit | Original exact CODE B |
| --- | ---: |
| `battle-combat-apply-impact` | 304 |
| `battle-collision-clear-bounds` | 51 |
| `battle-collision-include-pair` | 217 |
| `battle-collision-test-overlap` | 68 |
| `battle-collision-transform-bounds` | 215 |
| **Total retained** | **5/5 exact; 855/855 original B** |

Reproduce **only** these affected full callables, not all 979:

    scripts/repo-python scripts/replay-exact-units.py \
      --unit battle-combat-apply-impact \
      --unit battle-collision-clear-bounds \
      --unit battle-collision-include-pair \
      --unit battle-collision-test-overlap \
      --unit battle-collision-transform-bounds

All original native target bytes and entire strict unit manifests are
unchanged. F1056 retains **previously credited** 855 original CODE
bytes, not new whole-function exact coverage. No all-unit cold replay.
