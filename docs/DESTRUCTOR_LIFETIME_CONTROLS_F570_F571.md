# F570/F571 — actual VC7.1 lifetime controls for two authored nonexact destructors

**Negative results, not reconstruction credit.** The original Japanese
TH075 v1.11 executable SHA256 is
bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98.
Original whole function bodies and physical COFF reference fields were
independently established by F531/F536 and F505/F533/F546.
This round tested additional *actual natural C++ pointer declaration,
reference, local-aggregate and RAII lifetime variations*, with pinned
MSVC VC7.1 profile and a separate full-function COFF comparison
for each newly compiled candidate. **None was accepted exact**.

## F570 — 171-byte nonvirtual ArchiveCatalog RAII destructor at 0041CE50

The original entire function has **171 CODE bytes, 51 x86 instructions
and 14 authentic physical COFF references**; the current best natural
C++ still matches **108/115 comparable nonrelocation bytes**, but
seven actual machine bytes remain wrong.

Physical *original* member-resource deletion stores two receiver
pointer temporaries at EBP-0xC and EBP-0x8, whereas the ordinary
small C++ source uses EBP-0x10 and EBP-0xC. The original borrowed
archive filename pointer is at EBP-0x10, whereas candidate C++
puts it at EBP-0x8. The original returned value of delete remains
at EBP-0x18. This is a **three-way local-slot ownership difference**,
not an x87 operand or missing COFF call and never solved by replacing
machine bytes.

New experiments cover real resource pointers named inside or
outside lexical scopes, double pointers and lvalue references,
const resource pointers, differing resource/filename declaration
orders, and predeclaring pointers before the loop. Compiled **18
new source TUs**, with exactly these results:

- **14/18** yield a genuine but wrong **177-byte** CODE body
  (they add actual pointer/reload instructions).
- **4/18** preserve full **171-byte** extent but remain nonexact:
  one candidate matches 108/115 comparable bytes, three 102/115.
- **0/18** achieve complete original exact CODE or COFF equality.

All per-variant source, compiler logs, COFF JSON and original-bounded
comparison output remain in ignored .analysis/f570-archive-cxx-lifetimes/.
The earlier negative F536/F544/F550/F552 controls also remain intact.

## F571 — 248-byte BattleScene virtual destructor at 0043B0B0

The independent original contains **248 CODE bytes**, a complete
75-instruction EH/texture/base/heap-release destructor and 12 actual
COFF references. The best source control still matches **191/200
nonrelocation bytes** with nine genuine stack-layout differences.

The native texture delete temporaries reside at EBP-0x14/-0x10;
the source compiler instead allocates EBP-0x20/-0x1C. Original
heap-free pointers are EBP-0x18/-0x1C/-0x20, whereas ordinary
CleanupPointers aggregate C++ uses EBP-0x18/-0x14/-0x10.
Placing the whole real aggregate before the texture deletion does
not force the original compiler allocation graph, even if the
aggregate's field order is reversed.

Ten new *ordinary C++* source experiments combined declaring the
real aggregate before texture destruction, swapping aggregate
field order, scoped texture deletion and texture pointer
reference/named variable declarations:

- Six remain 248 bytes but mismatch: **three at 191/200** and
  **three at 189/200** comparable original nonrelocation bytes.
- Two newly compile to 251 bytes and two to 255 bytes, both
  invalid original whole-function extents.
- **0/10** reproduce the original exact 248-byte destructor.

All source/object/JSON/compiler logs are preserved under ignored
.analysis/f571-scene-aggregate-lifetimes/. Historical F505/F533/F546
negative controls remain available. Neither of these two
destructors was added to the accepted source matcher, and no
hard-coded assembly, fake local array or manual stack padding
was used to manufacture a byte match.

## Reproduce only selected source compiler probes, not all exact units

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python .analysis/f570-archive-cxx-lifetimes/generate.py
    scripts/repo-python .analysis/f571-scene-aggregate-lifetimes/generate.py

Use scripts/compile-probe.sh on any chosen generated .cpp with
its original appropriate /Od /Ob0 /Gy /GR- /GX /GS /Zi profile
(the archive uses /GX-; the scene uses /GX), then run
scripts/compare-coff-function.py on *that selected* object and
the whole 171-/248-byte target. Do not run full cold replay.

**This audit changes neither current 943 accepted whole exact
functions nor their 862,726 CODE bytes, and yields no external Oracle
receipt.** It narrows plausible object-lifetime explanations and
preserves all failed/source variants instead of skipping dirty work.
