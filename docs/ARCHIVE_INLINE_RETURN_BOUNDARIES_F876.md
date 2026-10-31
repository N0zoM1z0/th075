# F876 — Real Archive resource-return helper boundaries versus native destructor

The SHA-pinned Japanese TH075 v1.11 independent
ArchiveCatalog destructor at 0041CE50 owns
**171 complete callable native CODE B/51 x86/
14 physically typed original PE call/global fields**.
Actual native stack roles: EBP-4 loop index,
resource pointer EBP-0xC, deleting receiver EBP-8,
filename EBP-0x10, saved this EBP-0x14 and
scalar-delete return temp EBP-0x18.

The direct-list-access natural C++ baseline matches
all 171 original mnemonic/width instructions and
all 14 physically located original PE field targets,
but only **108/115 native nonrelocation bytes**;
seven genuine operand bytes still differ at full
function offsets 79,82,85,88,96,132,135.

F876 tests a different historical C++ hypothesis:
real list element resource/name pointers may be
returned by ordinary inline, __forceinline, or
typed template pointer-value dereference helpers.
Ten independently compiled full destructors
use the actual observed resource/name values and
retain real scalar deletion, CRT free and both
archive container Clear calls. No synthetic padding
locals, manual x86 or invented executable bytes
are introduced. All use pinned VC7.1
/Od /Ob0 /GX- for the original nonvirtual destructor.

| Complete source model | Whole emitted destructor | Original native outcome |
| --- | --- | --- |
| Direct native getter baseline | 171B/51 x86/14 PE fields | 108/115 native nonfield B |
| Four single ordinary/forceinline getters | **167B/50 x86/13 refs** | Actual original list At() call replaced by helper |
| Two double resource + name getter sources | **163B/49 x86/12 refs** | Both original list element calls moved outside destructor |
| Two typed pointer-value template sources | **178B/53 x86/15 refs** | Extra C++ return-helper call |
| Typed helper for BOTH values | **185B/55 x86/16 refs** | Two extra C++ helper calls |

In this actual /Od /Ob0 toolchain, even __forceinline
does NOT preserve the original destructor's native direct
list element call sites. Source resource helper replaces
real call target 0041DB40 with helper symbol; name helper
replaces original 0041DDC0. Consequently, merely similar
semantics cannot establish original whole-function source.

The tracked verifier checks every original complete
171B/51-x86 instruction and ALL FOURTEEN original
physical PE fields, including true CRT free 0064169D,
and independently records complete COFF/x86 output and
actual callees for each of ten normal source variants.
No new source restores the true original EBP owner slots
or all 171 original machine bytes.

Targeted reproduction of ONLY this independent small function:

    scripts/repo-python scripts/verify-archive-inline-return-boundaries-f876.py

Source, COFF/PDB, native PE comparisons and strict JSON
receipts remain under ignored
.analysis/f876-archive-inline-return/.
Original authored Archive remains NONEXACT;
zero new accepted whole callable CODE;
no mass cold replay.
