# F1150 — Original 81KB frame and every EBP stack displacement recovered

The complete native `0050A580` source now recovers original frame
`0x3A0`, saved-this `EBP-0xAC` and all **5,717 original EBP stack
operand positions**. Its normal pinned-VC7.1 whole CODE decreases
from 81,572 to **81,542 bytes**, three bytes beyond original 81,539.
It remains NONEXACT: 522 native instruction GPR-role positions and
five instruction widths are still different.

## Original stack evidence identifies real source lifetimes

A whole-instruction mapping from the pinned original PE to the current
COFF showed that native loop-index slots initially agreed, then diverged
by four bytes after each source `int random` declaration. Original random
values instead occupy the later conversion-temporary region: e.g. the
first random-result slot is original `EBP-0x150`, versus source named
`EBP-0x38`. There are eleven such explicit random locals across the
five long actions, five 365–369 actions and 389. The second loop in 38A
also used a distinct source index slot, while both native loops use
the same `EBP-0xA8` index.

The source now passes `double(RandomBoundaryAt00455580(0,4)-2)`
directly into the genuine random-scale expression, preserving integer
subtraction before conversion, call count and evaluation behavior.
It uses one real `shot` index for both consecutive 38A loops. No
dummy local, fabricated stack owner, padding or assembly is involved.

Removing eleven named locals moves saved-this from -0xDC to -0xAC.
The real random conversion spills remain compiler temporaries; reusing
the loop index reduces total frame allocation by four bytes. Every
original EBP displacement now agrees, including all conversion spills.

## Whole-parent cold verification and exactness boundary

Only the changed parent was cold-built. The live verifier now checks
the original frame and compares every EBP operand across all 17,435
ordered native instructions, alongside all 1,834 direct jump destinations,
83 strict interiors, 1,275 physical external PE fields, 3,013 scalar
positions and afterRET switch partitions/sparse bytes. All passed.

The five width differences are at whole instruction ordinals 10,330,
10,461, 10,729, 17,328 and 17,333. They are genuine accumulator versus
nonaccumulator CMP encodings caused by wrong GPR roles in 35B, 35E
and 3E6; no branch-width difference remains. Eight provisional cases
still contain 522 wrong GPR instruction positions. Equal stack offsets
and a three-byte length gap do not establish complete byte equality.

The accepted ledger remains **979 complete functions /868,243 original
CODE bytes**, and all 25 authored whole-function backlog entries remain.

Reproduce only the affected parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Original-to-source slot mapping, previous source/COFF/receipt, the
normal full candidate, diagnostic reports and final verifier output
are retained under ignored `.analysis/f1150-native-stack/`.
