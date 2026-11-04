# F1035 — Native fighter pattern extension typed without losing 3,696 exact bytes

The pinned Japanese TH075 v1.11 complete authored fighter-pattern loader
`00457660` is **3,696 original callable CODE bytes**. Its source had
three unrelated byte/short/float offset-cast macros on the same dynamically
owned extension, obscuring the actual .pat record structure. The original
`ReadFile` calls and float assignments establish a **36-byte borrowed
window**, but do not establish the original allocating owner class.

The named `FighterPatternExtensionBorrowF1035` view now represents:

| Extent | Physical source use |
| --- | --- |
| `+0x00..+0x01` | a single signed short read, then **a second byte read at +1** into the very same storage; modeled by a union, not two disjoint fields |
| `+0x02,+0x03,+0x04` | independent single-byte reads |
| `+0x05` | naturally inserted alignment gap, not assigned a fabricated meaning |
| `+0x06,+0x08,+0x0A` | three original signed short reads |
| `+0x0C,+0x10,+0x14` | three float stores after an authentic scaled short conversion |
| `+0x18,+0x1C,+0x20` | three float stores after an authentic float conversion |

The view is only dereferenced through the preexisting `PatternFrame116::extension`
pointer. It is never instantiated, embedded in the incomplete frame class, or
claimed to recover the entire historical extension owner. `sizeof` and
`offsetof` constraints enforce the physical observed 36-byte window.

## Real VC7.1 COFF hazard and resolution

An initial honest attempt placed the type declaration at translation-unit
scope. Native instructions and all 3,696 bytes were unmodified in intent,
but the real VC7.1 compiler advanced both preexisting string-literal COFF
symbols from `$SG60160/$SG60161` to `$SG60204/$SG60205`.
This **failed** the strict complete original comparison and could not
remain as an accepted source change. Simply rewriting the relocation
manifest to fit changed symbol identities was not allowed.

The type is instead introduced at its genuine first use site, inside the
frame-type-2 record branch, *after* the existing two original filename
literals have been compiled. Normal VC7.1 then produces the original
literal identities, full body, all relocation fields and all nonfield
bytes. No conditional exact-only bodies, assembler, padding, byte masks or
fabricated locals were used.

Targeted cold original verification:

    scripts/repo-python scripts/replay-exact-units.py --unit fighter-pattern-load-00457660

**Result: 1/1 complete exact, 3,696/3,696 original callable CODE bytes.**
This preserves previously accepted credit; it adds **zero** new original
CODE bytes and does not solve any of the 25 pending authored functions.
The earlier failed compile is not accepted evidence; the successful
cold replay is the relevant checkpoint. No 979-unit full replay was run.
