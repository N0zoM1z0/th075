# F1040 — Retain the complete original-shaped 46KB Fighter as tracked C++

**Current continuation:** F1197 restores 56 ordinary exit targets and the
three original 18B guard destinations; see the
[whole CFG/stack/operand proof](FIGHTER_46KB_WHOLE_CFG_F1197.md).
The SHA256 below records the original F1040 adoption, not today's source.
The whole callable remains NONEXACT with 2,736 GPR /five-width debt.

The original Japanese TH075 1.11 authored Fighter `Advance` at
`005214B0` is a **single** nonexact callable: **46,755 original CODE
bytes / 13,230 x86**, followed by **901 separately owned DATA bytes**.
For a long time the strongest real complete ordinary-VC7.1 C++
parent was retained only under ignored
`.analysis/f901-fighter-31b/Boss005214B0-F901-whole.cpp`. The target
source is now preserved verbatim as the tracked
`probes/FighterWhole005214B0F1040.cpp`.

The tracked C++ source contains the complete original-shaped state
machine including the actual F901 `31B` and `31C` late actions, the
real native calls/fields and the original afterRET switch data. No
new body was invented or inferred from a decompiler. Comparing both
source files' SHA-256 gives the same checksum:

`95c1c6bcc2bb96573d858b3da2e8b23af4ce7ff82994b332d3ca0321b41251b8`.

The existing targeted original-native verifier
`scripts/verify-fighter-whole-46kb-pe-targets-f1026.py` has been
corrected to compile the **new Git-backed source**, not an ignored
historical experiment. It freshly compiles the entire Fighter with
pinned VC7.1 and independently checks the original PE. Actual full
verification passes with **1,341/1,341 physical native external
call/global targets**, 11 internal COFF fields, 139 authentic
original afterRET DIR32, 345 literal DATA bytes and all 13,230
original mnemonic ordinals. There are still **five original
instruction-width defects**, and emitted CODE is **46,754**, not
46,755 original bytes. The original entire function is **NONEXACT**
and earns **zero** new original authored-byte credit.

The previously ignored research source/OBJ/PDB and reproducible
native receipts are not deleted or assumed to be backed up in Git.
The stored normal-shaped source in `probes/` is the live base for
further original `0x63`, `0x1FD`, `0x252/0x254` and other full-state
recovery experiments. The .analysis artifact remains historical
only, rather than an implicit dependency for rebuilding this parent.

Reproduce only the affected whole giant:

    scripts/repo-python scripts/verify-fighter-whole-46kb-pe-targets-f1026.py

No 979-unit all-function cold replay was requested or performed.
