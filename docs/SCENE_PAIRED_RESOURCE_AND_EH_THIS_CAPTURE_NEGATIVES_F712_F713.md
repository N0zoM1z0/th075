# F712/F713 — full native EH destructor and Scene lifetime reconstructions (negative)

**Actual original PE/VC7.1 source-negative results, not complete-function
exact acceptance.** The original is user-supplied Japanese TH075 v1.11
`resources/th075.exe`, pinned SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
All experiments preserve the *entire* original target function extent
and read original instruction and stack locations anew. No dummy saved
locals, artificial stack padding, raw target-byte assembly, imported
machine grafts, executable edits or full 943-unit cold replay.

## F712: one complete 73-byte, provenance-UNKNOWN derived virtual destructor

Native `0061A453` is **73 original CODE B /23 x86** with real MSVC
EH prologue `MOV EAX,00656B2C; CALL 006425A4`, saved `this`
`EBP−0x10`, EH-state initialization `AND [EBP−4],0`, actual
vtable assignment, `CALL 00619172`, conditional member
`this+0x106C` CRT release through `00640F15`, and original
base virtual destructor `0061535A` before `FS:[0]` restoration.
This registered function's origin is **still unknown**, and even
byte-exact source alone would not authorize a game-authored match.

Earlier F688/F707 tried direct destructor, source `try` scopes and
function-try-block alternatives. F712 tested a *different, meaningful
source-owner hypothesis*: whether an exception handler's real use of
`this` and its actual resource `this+0x106C` could naturally force
the original additional saved-this and EH state-owner slots. Each
candidate actually runs the observed real `00619172` cleanup and
CRT release on the normal path, with scoped handler resource release,
rethrow or swallow alternatives (the last is a semantic negative,
not asserted to be original exception behavior).

| Whole native-style C++ source | Fresh VC7.1 `/O1 /GX` result | Original 73 B/23 x86 |
| --- | --- | --- |
| Body-scoped cleanup catch/rethrow, free-scoped catch release/rethrow, and complete cleanup/free catch release/rethrow | **3** variants, **69 B/22 x86/7 source fields** | NONEXACT; original EBP−0x10 owner and state initialization still missing |
| Body-scoped cleanup catch that releases the real member and swallows the exception | **1** variant, **39 B/13 x86/4 fields** | NONEXACT; compiler removes the expected original EH handling structure |
| Destructor function-try-block with member release and rethrow | **1** variant, **107 B/39 x86/9 fields** | NONEXACT; extra EH handlers/instructions |
| Function-try-block with actual member test and rethrow | **1** variant, **91 B/35 x86/8 fields** | NONEXACT; different original EH state/handler shape |
| **Total** | **6 entire original-shape source experiments** | **0** exact whole native functions |

The actual source/COFF/first x86 sequence is preserved in ignored
`.analysis/f712-derived-eh-this-capture/`, and a **portable,
tracked, source-generating selected verifier** is
[`verify-derived-eh-this-capture-f712.py`](../scripts/verify-derived-eh-this-capture-f712.py).
It re-reads the whole original 73-B/23-x86 PE before compiling
**one** complete C++ translation unit (default or `--case`) or just
these six affected small C++ units (`--all`) and checks the authentic
complete compiler lengths/x86/COFF counts. None is a historical
SDK class/source-ownership proof or eligible authored exact match.

## F713: real complete 248-byte game Scene destructor, twelve paired-owner hypotheses

Original authored virtual `0043B0B0` owns **248 CODE B /75 native x86 /
12 physically typed PE/COFF fields**, with genuine EH state, two
texture scalar-delete temporaries, three actual `free()` calls and
real base destructor. Original x86 store ordinals/EBP offsets are:

| Original ordinal | Real original semantic owner | Native EBP | Previous and F713 source |
| ---: | --- | --- | --- |
| 26 / 28 | Texture pointer and scalar-delete receiver | `−0x14 / −0x10` | `−0x20 / −0x1C` |
| 42 / 52 / 62 | Three actually freed resources | `−0x18 / −0x1C / −0x20` | Different source permutations within `−0x10/−0x14/−0x18` |

F713 genuinely changes the source object-lifetime *ownership model*,
not only casts: the three **actually freed** values are represented
as a **two-member used `CleanupPair` aggregate plus one separately
used scalar pointer**. All three choices of which resource is
standalone were tested, together with both real two-member orderings
and declaring the pair/scalar before texture deletion versus after.
Every one of the **12 distinct source TUs** retains all original
3 `free()` uses, actual conditional texture scalar `delete`, scene
state code, EH mode and base destructor. Nothing is unused padding.

| Real full native C++ pair+scalar ownership | Cases | Original PE/COFF match |
| --- | ---: | --- |
| First standalone free or reversed pair arrangement (8 combinations) | **8** | Full **248 B/75 x86/12 fields**, **189/200** original nonrelocation bytes equal |
| Middle or final freed value standalone, nonreversed meaningful pair (with early or late true declaration) | **4** | Full **248 B/75 x86/12 fields**, **191/200** nonrelocation bytes equal |
| **Total** | **12** | **0** complete original 248-B functions exact |

Every candidate actually matches the **75 original ordered mnemonic
and instruction-width positions** and preserves all original 12
physical typed zero-addend field records. However, *all* retain
texture deletion scratch `EBP−0x20/−0x1C` instead of original
`−0x14/−0x10`, and the true free owner slots remain wrongly assigned.
This genuinely excludes the simplest two-field used resource
aggregation plus standalone scalar as a solution to the native
five-way temporary allocation, including early declaration scope.
It does **not** establish the true original Scene C++ class layout.

The initial actual CPP/OBJ/PDB, compiler log and whole 248-B original
comparison JSON are retained in Git-ignored
`.analysis/f713-scene-two-plus-one-owner/`.
The portable new tracked generator/verifier
[`verify-scene-pair-scalar-owners-f713.py`](../scripts/verify-scene-pair-scalar-owners-f713.py)
cold-compiles a **selected complete 248-byte native-shaped C++ Scene
function** (default or `--case`) or exactly these twelve affected
C++ units with `--all`. It independently verifies native original
75 x86, 12 typed zero-addend fields, exact 248-byte geometry, every
native/compiled x86 mnemonic/width, original five raw scratch owners
and 189/200 or 191/200 genuine nonrelocation byte negatives.

## Reproduce only affected complete functions

```bash
scripts/repo-python scripts/verify-scene-pair-scalar-owners-f713.py --case solo1-pairrev0-early0
scripts/repo-python scripts/verify-derived-eh-this-capture-f712.py --case body-try-resource-catch-rethrow
# Optional: 12 Scene + 6 derived small C++ objects; not all 943 exact units
scripts/repo-python scripts/verify-scene-pair-scalar-owners-f713.py --all
scripts/repo-python scripts/verify-derived-eh-this-capture-f712.py --all
scripts/repo-python scripts/validate-tracking.py --require-target
```

Both native originals remain **NONEXACT**, and `0061A453` stays
**origin unknown**. The authored exact ledger is unchanged at **943
whole game functions /862,726 original CODE bytes (43.71% reviewed)**.
No target EXE modification, no added canonical match unit, no
unreviewed author-origin promotion, no full 943-unit cold replay.
