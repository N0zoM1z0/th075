# F1124 — Actual fighter auxiliary action's 10-byte signed WORD window and native X/Y positions, 6,935 whole exact bytes preserved

The pinned Japanese TH075 1.11 game has a previously independently accepted **3,935B complete authored** `AuxiliaryActor4A80F0::Update` and an independently accepted **3,000B complete** `CharacterAI507B20::ChooseAction` in the single `src/ActorAuxiliary.cpp` translation unit. F1124 changes actual C++ gameplay sources by replacing repeated raw owner offsets with narrow, physically observed signed WORD and float borrows. Both whole original callables remain **byte-identical exact** after fresh complete original-unit replay, including all original physical COFF field identities and local symbols.

The native auxiliary actor has **five adjacent signed 16-bit WORD fields** physically at **actor+0xD8/+0xDA/+0xDC/+0xDE/+0xE0**. A *borrowed-only*, 10-byte `AuxiliaryActorWordWindowF1124` names its actual stage angle, stage speed, response flag, target angle and next short storage. `sizeof` and `offsetof` compile-time checks guard native 10B/6B/8B field spacing. The original action initializes and later reads these scalars, performs native direction wrap and stage-speed adjustments, controls original parent/motion transitions, and preserves genuine `00483300` float-to-angle and local conversion behavior. The refactor replaces exactly **43 physical signed-WORD source accesses** in the complete auxiliary actor, not a new owner class allocation or a fabricated local.

The same actual original actor has two float POSITION fields at **+0x44/+0x48** and two FLOAT MOTION fields at **+0x50/+0x54**, independently verified by previously whole-byte-exact battle-frame routines and through original native code. F1124 reuses existing narrow `F1037_POSITION` and `F1037_MOTION` field windows and replaces **46 actual original float accesses** (18 X position, 18 Y position, 5 X motion, 5 Y motion). Original `Spawn`, `SetPolarVelocity`, parent X/Y offsets, real facing multiplication, and CRT/FP conversions remain in original C++ order. No guessed complete class layout is instantiated, allocated or embedded.

| Genuine original-field source improvement | Distinct original used accesses |
| --- | ---: |
| Five physical signed short words at +D8..E0 | **43** |
| Actual actor position X/Y +44/+48 | **36** |
| Actual actor motion X/Y +50/+54 | **10** |
| **Complete affected auxiliary original game function** | **89** |

Two separate targeted strict cold replays were executed using pinned ordinary VC7.1: after the 10B signed WORD view, and after the native position/motion field borrow. Both rebuild the **entire changed `ActorAuxiliary.cpp` object** and check **both full original callables** (not individual cropped x86 cases):

    scripts/repo-python scripts/replay-exact-units.py \
      --unit auxiliary-actor-update-004a80f0 \
      --unit character-ai-policy-00507b20

Both cold replays produced **2/2 strict original complete functions exact, 6,935/6,935 accepted native CODE bytes preserved**. There was **no new whole exact CODE credit** and no unrelated 979-function mass replay. Baseline accepted C++ source and normal original PE/COFF object build receipts retained under ignored `.analysis/f1124-aux-actor-words/`. Original Japanese EXE and matching manifests unchanged; no arbitrary stack padding, altered GPR binding or relaxation of `$L` local-symbol identity.
