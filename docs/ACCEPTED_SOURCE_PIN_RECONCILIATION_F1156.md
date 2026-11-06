# F1156 — Reconcile accepted source revisions after affected-only cold replay

The acceptance checkpoint still pinned pre-refactor hashes for 65 source
files whose later native field/lifetime improvements were already tracked.
The first small checkpoint check after F1155 correctly rejected this drift
at `BattleCombat.cpp`. The source revisions were retained and reviewed;
no accepted body or historical origin decision was reset or removed.

The affected scope was derived from the live canonical manifests:

- 65 changed source files, 65 compiler objects, 259 exact units.
- 29 new borrowed-view headers used by those sources.
- Nine additional consumers of the new notice header in the original
  `GamePolicyHelpers.cpp` object, also freshly cold-replayed.

**All 268 affected complete units across 66 serial compiler objects are
exact**, including their complete native extents, every physical relocation
and strict original local symbols. No other units were rebuilt. This is
not a full-corpus replay and adds no accepted CODE bytes by itself.

The adoption manifest now retains each of the 65 previous hashes alongside
its verified current hash in the F1156 `source_revision_batches` entry, and guards
the current source contents. It also pins the 29 new borrowed headers and
the baseline helper source. Every consumer of those new headers is in the
268-unit cold scope. Existing unchanged general graphics/input headers were
outside this revision and were not used to broaden the rebuild scope.

No checkpoint assertion was weakened or bypassed. The manifest guard was
refreshed only after all affected canonical comparisons passed; complete
R268 and later accepted origin/function evidence remains preserved.
The small exact/checkpoint/byte-accounting check set then passed, with no
compiler builds performed by that check set.

Machine-local before/current hashes, the derived dependency/consumer graph,
both complete replay receipts, compiler logs and the scope scripts remain
under ignored `.analysis/f1156-source-pin-reconciliation/`. The tracked
adoption manifest records the exact affected unit names and input hashes.
For a future actual change, replay only its affected units; do not repeat
this already completed reconciliation without new evidence of drift.
