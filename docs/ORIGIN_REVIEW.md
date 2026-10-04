# Origin review journal

Work resumed after R069. Finish evidence-backed origin review of every
candidate before resuming exact reconstruction, then target at least 50% exact coverage of
the confirmed authored-byte set. This order supersedes the earlier
alternating workflow. Percentages remain provisional until no origin is pending.
Auto-analysis names, adjacency, and small size do not establish origin.

## R001 — remaining shared graphics family

Reviewed 2026-10-02 against the pinned TH075 target. The fourteen functions
below implement custom shared D3D8 resource/window/texture/drawing policy.
They are classified as authored independently of source presence or exactness.

| Address | Complete bytes | Inferred role |
| --- | ---: | --- |
| `0x00401020` | 239 | `GraphicsResourceClient::~GraphicsResourceClient` |
| `0x00401110` | 1059 | `Graphics::Initialize` |
| `0x00401540` | 604 | `Graphics::SetDefaultStates` |
| `0x004017A0` | 245 | `Graphics::ResetDevice` |
| `0x004018A0` | 340 | `Graphics::ToggleWindowMode` |
| `0x00401B20` | 248 | `Graphics::Create16BitTexture` |
| `0x00401C20` | 340 | `Graphics::CreateTexture` |
| `0x00401D80` | 376 | `Graphics::CopyTextureOpaque` |
| `0x004029F0` | 857 | `Graphics::DrawTexturedQuad` |
| `0x00402D50` | 1185 | `Graphics::DrawProjectedTexturedQuad` |
| `0x00403200` | 507 | `Graphics::DrawProjectedTriangleStrip` |
| `0x00403400` | 540 | `Graphics::DrawLine` |
| `0x00403620` | 742 | `Graphics::DrawRectangleOutline` |
| `0x00403910` | 632 | `Graphics::DrawFilledRectangle` |

The lifetime count at 0x00671210 governs the shared D3D8 device/interface and
single-slot render-target arrays already evidenced in F001/F002. Initialization
uses the target's own window, resolution, presentation parameters, fallback
device-creation sequence, error strings, and logging. Default-state/reset/window
functions invoke this custom protocol. Texture creation rounds dimensions to
powers of two and applies the game's square-texture policy. Copy adds opaque
alpha after surface copy/locking. Drawing functions apply the game's global
scale, origin, RGB multiplier, texture cache, projection, and primitive policy;
these globals are distinct from D3DX/CRT internals. Called library functions
are not reclassified as authored merely because these callers are authored.

Evidence includes hash-attested Ghidra decompilation, independent Capstone 5.0.6
instruction decoding, all conditional/unconditional branch destinations, full
returns, and trailing INT3 alignment. Every body decodes completely, every jump
lands on an instruction within its body, and each has one final RET. No jump
table, shared tail, or external branch was found in these extents. The target's
integer/float/conversion helpers remain separate candidates. Names and full
interfaces remain inferred; this review grants no source or exact credit.

Private evidence: `.analysis/origin-graphics-remaining.c` and
`.analysis/origin-graphics-instructions.json`. Reproduce decompilation with
`scripts/repo-python scripts/ghidra.py decompile .analysis/review.c ADDRESS...`
in groups of at most sixteen addresses. The candidate/origin ledgers are the
durable classification state. The status command reports pending count,
confirmed authored bytes, exact authored bytes, and whether both goal gates
are actually satisfied.


## R002 — shared DirectInput lifetime, setup and polling

Reviewed 2026-10-02 after exact batch F003. The following eight complete
functions add 1,335 confirmed authored bytes. They implement custom input
ownership and device policy; their SDK/CRT/container callees keep separate
origin decisions. This batch itself grants no source or exact credit.

| Address | Complete bytes | Inferred role |
| --- | ---: | --- |
| `0x00403B90` | 76 | `InputResourceClient::InputResourceClient` |
| `0x00403BE0` | 278 | `InputResourceClient::~InputResourceClient` |
| `0x00403D20` | 95 | `Input::Initialize` |
| `0x00403D80` | 197 | `Input::CreateKeyboard` |
| `0x00403E50` | 90 | `Input::PollKeyboard` |
| `0x00403EB0` | 139 | `Input::InitializeJoysticks` |
| `0x00403F40` | 200 | `Input::PollJoysticks` |
| `0x00404010` | 260 | `Input::EnumerateJoystickDevice` |

The reference count at `0x00671340` controls shared DirectInput and keyboard
pointers at `0x0067134C/0x00671350`, plus two distinct container owners at
`0x00671368/0x00671358`. First construction resets pointers and clears both
containers; last destruction unacquires/releases keyboard and each controller,
clears containers, then releases DirectInput. This custom coordinated policy
is evidence beyond the constructor's generic count increment. Full class
layouts are unknown and must not be inferred from these count-only bodies.

Initialization stores the game's HWND/HINSTANCE at `0x00671344/0x00671348`
and calls DirectInput8Create for version 0x0800. The pinned image's GUID bytes
at `0x0065BA8C` decode to BF798030-483A-4DA2-AA99-5D64ED369700, matching the
SDK IID_IDirectInput8A; `0x0065B91C` matches GUID_SysKeyboard
6F1D2B61-D5A0-11CF-BFC7-444553540000. The keyboard data format at `0x0065A4DC`
has size 24, object stride 16, relative flags 2, data size 256 and 256 objects,
consistent with c_dfDIKeyboard. Setup uses the SDK's CreateDevice,
SetDataFormat, SetCooperativeLevel and Acquire slots. Its 0x16 cooperative
flags are NONEXCLUSIVE | FOREGROUND | NOWINKEY. Polling reads the 256-byte
buffer at `0x00671240`; failure reacquires the keyboard and zeros the buffer.
All four setup error literals at `0x00657498/0x006574BC/0x006574D8/0x006574F8`
were read from the hash-attested image and describe their respective failures.

Joystick initialization enumerates game controllers (class 4, attached-only
flag 1), stores container size in the byte at `0x00671354`, and fills the state
container with zeroed 80-byte records. Polling calls Poll, reacquires on a
negative HRESULT, then reads 80 bytes into each corresponding record. The
80-byte SDK DIJOYSTATE and the joystick data format at `0x0065A6E4` (24-byte
format, 16-byte object stride, absolute flag 1, data size 80, 44 objects) agree.
The enumeration callback appends a null device slot, creates using the GUID at
instance+4, pops the slot on failure, and otherwise sets the joystick format,
exclusive foreground cooperation (5), a 44-byte DIDEVCAPS size field, and
object enumeration callback `0x00404120` with axis flags 3. The actual callback
RET 8 agrees with the SDK BOOL stdcall callback's two arguments. Misleading
Ghidra string/back names on container helpers are not layout/origin evidence.

Independent complete Capstone decoding agrees with hash-attested decompiles.
Every jump lands on an instruction inside its function, with no shared tail,
external jump or switch table. All extents end at the final RET; the following
INT3 alignment is excluded. The initializer's compiler security-cookie load
and check remain inside its 139-byte extent, without making the surrounding
custom device policy compiler-origin. SDK/CRT helper bodies remain separately
reviewable. Private evidence is in `.analysis/origin-input-family.c` and
`.analysis/origin-input-instructions.json`; reproduce with the same attested
Ghidra workflow used for R001.


## R003 — axis policy and VC7 vector specializations

Reviewed 2026-10-02 after F004. The axis callback at `0x00404120`, 107 bytes,
is authored: it applies the game's -1000/+1000 range to each enumerated axis
by object ID on the last controller. Its DIPROPRANGE header is 24/16 bytes,
dwHow is DIPH_BYID (2), and the property identifier is DIPROP_RANGE (4).
It returns the SDK BOOL DIENUM_STOP/CONTINUE with stdcall RET 8, depending
on the negative HRESULT test. This custom callback is independent of the
following generated standard-library functions.

Fifteen complete bodies, totaling 712 bytes, are classified library/exclude:

| Address | Bytes | Corroborated VC7 vector role |
| --- | ---: | --- |
| `0x00404190` | 52 | device-vector size |
| `0x004041D0` | 49 | device-vector subscript |
| `0x00404210` | 45 | device-vector back |
| `0x00404240` | 99 | device-vector push_back |
| `0x004042B0` | 66 | device-vector pop_back |
| `0x00404300` | 19 | device-vector clear |
| `0x00404320` | 49 | DIJOYSTATE-vector subscript |
| `0x00404360` | 29 | DIJOYSTATE-vector assign(count, value) |
| `0x00404380` | 19 | DIJOYSTATE-vector clear |
| `0x004043A0` | 52 | device-vector capacity |
| `0x004043E0` | 31 | device-vector begin |
| `0x00404400` | 31 | device-vector end |
| `0x00404420` | 24 | device-vector empty |
| `0x00404440` | 114 | device-vector insert |
| `0x004044C0` | 33 | device-vector _Destroy |

**Vendor-source evidence:** The pinned VC7 header `Vc7/include/vector` has
SHA-256 `de722c2662f74e78332c6a1b7ddabb9976f3381a904780aaefba54e661a9656d`.
Its size/capacity null checks and pointer differences, iterator-based subscript
and back, capacity-dependent push_back, guarded pop_back, _Tidy-based clear,
count/value assign and insert protocol agree with complete target control
flow. Recompiling real `std::vector<IDirectInputDevice8A *>` and
`std::vector<DIJOYSTATE>` using pinned VC7 /Od /Ob0 /Gy /GR- /GX- /Zi emitted
matching complete sizes and every non-relocation byte for all fifteen bodies.
SDK headers remain shared read-only; none were rewritten to obtain evidence.

Several short fingerprints have multiple library aliases. Relocation call
roles and caller types distinguish them: device subscript uses begin/add/
dereference at `0x004043E0/0x004046C0/0x004046A0`; state subscript uses the
separate `0x00404590/0x00404740/0x00404720` family. Back uses end/subtract/
dereference at `0x00404400/0x004046F0/0x004046A0`. Clear calls distinct _Tidy
bodies at `0x004044F0` (103 bytes) and `0x00404630` (110 bytes); each also has
a complete vendor-generated non-relocation fingerprint. Assign forwards to
_Assign_n at `0x004045B0`, preserving count and DIJOYSTATE reference. These
callee candidates remain separately reviewable; this batch does not grant
them classification or authored exact credit. In particular, the Ghidra
VS2012/VS2015 wchar-string back label on `0x00404210` is unsupported and was
not used as provenance evidence.

Independent instruction decoding proves every listed extent complete, with
internal direct jump destinations, one final RET and trailing INT3 alignment.
There are no switch tables, external jumps or shared tails in these extents.
This evidence establishes library origin; the diagnostic fingerprints exclude
relocation fields and are deliberately not entered into matches/implemented
or authored coverage. Private evidence: `.analysis/origin-input-containers.c`,
`.analysis/origin-input-containers-instructions.json`,
`.analysis/origin-vector-fingerprints.json`, and
`.analysis/input-containers-probe.cpp`. To reproduce the vendor probe, include
InputDevice.hpp and vector, declare the two real vendor vector types, and call
the listed methods, including state-vector assign (not resize). Compile using
the profile above and inspect the actual decorated COFF symbols. This review
precedes exact reconstruction of the authored callback.

## R004 — remaining VC7 container, string and exception helpers

Reviewed 2026-10-02 after F005. One hundred complete bodies, totaling 4,497
bytes, are now library/exclude. Their addresses, complete sizes, inferred
vendor signatures, decorated COFF symbols, masked SHA-256 fingerprints and
159 relocation bindings are recorded in `config/vendor-origin-evidence.csv`.
These are origin records, not canonical exact-match units or recovered
original names. The batch leaves 4,189 origins pending and grants no authored
source or exact credit.

The real VC7 headers instantiate `std::vector<IDirectInputDevice8A *>` and
`std::vector<DIJOYSTATE>`, their allocators/iterators, copy/fill/destruction
algorithms, and the string/exception machinery used by vector length checks.
The public probe is `probes/VC7InputContainers.cpp`; it calls vendor interfaces
and contains no copied implementation. A fresh compile with pinned VC7.1
13.10.3077 reproduced each complete size and every non-relocation byte under:

```bash
scripts/compile-probe.sh probes/VC7InputContainers.cpp build/probes/VC7InputContainers.obj /Od /Ob0 /Gy /GR- /GX /Zi /GS /I src
```

The EH/GS profile is required by five fingerprints, including the 80-byte
value copy and cookie in state-vector `_Assign_n`. Ninety-five also reproduce
under the previously evidenced GX-disabled profile. This does not establish
one executable-wide profile. Reproduce an individual diagnostic using its
CSV COFF symbol, address and complete size with `compare-coff-function.py`;
the CSV hash replaces precisely its listed four-byte relocation fields with
zeros. Every field was checked against an actual decoded 32-bit immediate
or displacement, so opcode bytes cannot be hidden by the mask.

Short library bodies have aliases. The reviewed R003 vector callers, their
4/80-byte element strides, and mutually consistent incoming/outgoing typed
call destinations distinguish the device/state specializations. For example,
device `_Tidy` at `0x004044F0` destroys through `0x004044C0` and deallocates
through `0x00405100`; state `_Tidy` at `0x00404630` uses
`0x00405200/0x00405230`. State `_Assign_n` at `0x004045B0` copies the value
before erase/insert, preserving alias safety. Scalar pointer algorithms use
memmove; the DIJOYSTATE algorithms advance/copy 80-byte records. The CSV
bindings document compiler-intended roles at observed target destinations;
unreviewed callees receive no origin credit from these callers.

The string family uses a 16-byte small buffer, length/reserve at +20/+24,
`_Eos` termination, `_Grow`/`_Tidy` policies and char_traits copy/move calls.
`logic_error` owns a string and returns its c_str from what(); length_error
derives from it. The two vector `_Xlen` bodies use the verified literal
`vector<T> too long` and length_error throw metadata. These agree with real
`std::allocator` headers; Ghidra's DebugHeapAllocator and `_Xran` labels are
not used. The `__except_list` bindings with target zero are FS:[0] accesses,
not PE globals at address zero.

Complete Capstone decoding verifies all 100 bodies through their single final
RET, with every jump internal and direct, no switch table or shared/external
tail. Padding is excluded where present; some bodies abut their next function.
The unmatched insertion/allocation bodies and overlapping EH catch funclets
remain pending rather than being blanket-classified from adjacency. Private
attested decompiles and full instruction evidence remain under
`.analysis/origin-container-extended-*`; the source/header/compiler
fingerprints and typed call graph provide independent corroboration.

| Read-only vendor header | SHA-256 |
| --- | --- |
| vector | `de722c2662f74e78332c6a1b7ddabb9976f3381a904780aaefba54e661a9656d` |
| stdexcept | `bc3e7b40b6413b1aa2a2cc011057ca42aa03a714f409f927734c4f507aaea2a7` |
| xstring | `c715ae6f152ca41d73e701c5d77dd5da0b61832250c967d2a8376b9471656943` |
| memory | `81895e7a4ef1c432ec68484b072bcd14f953a75d99af77c0f83667c1c7cf9bf4` |
| xmemory | `e3a2baa7cb199323b2a0226cd84da797b5224777e8709f7cb1e4273b27919d94` |
| xutility | `177f47d09110228013374513e62a9de2e9be2f9bd22e4ae15bb31c584da4db7b` |

R005 subsequently resolved the identical constructor fingerprint at
`0x00405340`: it is the generated length_error copy constructor, rather than
the explicit string constructor alias. Its CSV signature/binding and origin
were corrected; it still receives no authored or exact credit.

## R005 — complete EH spans and generated exception helpers

Reviewed 2026-10-02 after F006. Twenty-five additional pending candidates are
excluded: 22 have vendor-library ownership and three are compiler-generated
exception helpers. The previously reviewed copy constructor at `0x00405340`
is also corrected from library to compiler. Current ownership totals are 47
authored, 136 library and four compiler candidates; 4,164 remain pending.
Candidate count includes retained analysis fragments, not just callable functions.

Fresh compilation of the unchanged public vendor probe under R004's EH/GS
profile reproduced five complete COFF bodies, including all non-relocation
bytes, for 2,300 distinct bytes and 91 relocation bindings. Full-range
fingerprints and the associated 19 candidates are in
`config/vendor-origin-spans.csv`. Fourteen of those candidates are split or
overlapping pieces of the five vendor functions. No candidate was deleted to
reduce the pending count, and overlapping bytes receive no authored credit.

| Vendor body start | Correct complete size | Covered candidate starts |
| --- | ---: | --- |
| `0x00404770` | 796 | 404770, 4048AB, 4049B3, 404A79 |
| `0x00405460` | 339 | 405460, 405507, 40552E, 405550 |
| `0x004055F0` | 846 | 4055F0, 405744, 40585D |
| `0x00406180` | 157 | 406180, 4061DB, 4061DD, 4061E6 |
| `0x004062D0` | 162 | 4062D0, 40632D, 40632F, 406338 |

The two vector insertion bodies implement the header's capacity/growth,
prefix/fill/suffix copy and catch cleanup policy. String `_Copy` retries
allocation at the requested size after the first allocation failure, cleans
storage and reraises on a second failure, then copies the old string into the
new buffer. The DIJOYSTATE uninitialized fill/copy helpers catch failures,
destroy only successfully constructed records and reraise. These are vendor
source policies, corroborated by the compiler's local catch labels and the
complete target control flow, rather than inferred from Ghidra labels.

The old principal extents omitted EH continuations or shared exits. Their
function-ledger sizes/end addresses now include the complete COFF ranges.
Every full range decodes completely; direct jumps remain in that range and
the compiler's same-section continuation label has the expected target offset.
Fragments are explicitly marked as non-independent analysis pieces; they need
not have standalone prologues or returns. In particular, `0x00404A79` restores
FS:[0] and returns with the insertion body's frame, and `0x004061E6` branches
back to the loop increment at `0x004061DD`. Such fragments cannot be accepted
as separate authored functions merely because auto-analysis named them.

Six other new complete helper bodies are recorded in the extended
`config/vendor-origin-evidence.csv`:

| Address | Bytes | Ownership and corroborated role |
| --- | ---: | --- |
| `0x00404BC0` | 44 | compiler: logic_error scalar deleting destructor |
| `0x00404C70` | 44 | compiler: length_error scalar deleting destructor |
| `0x00405370` | 100 | compiler: logic_error copy constructor |
| `0x00406380` | 65 | library: `_Construct<DIJOYSTATE>` |
| `0x004063D0` | 8 | library: placement operator new |
| `0x004063E0` | 5 | library: `_Destroy<DIJOYSTATE>` |

Generated copy/deleting functions lack definition auxiliary records, but each
has its own complete executable COFF section and defined function symbol.
That section supplies the independently checked full extent; no target prefix
was chosen to force a fingerprint. Deleting destructors call their specific
destructor, test the low bit (mask 1), optionally call operator delete and return this. Copy
constructors copy the exception base and string member while setting the
correct vtable. The memory helpers agree with read-only xmemory/new headers
and the allocator's typed construct/destroy callers. Short equal-body aliases
are resolved with those callee/caller roles.

The length_error ThrowInfo at `0x00667A38` points to CatchableTypeArray
`0x00667A28`. Its length_error and logic_error records at
`0x00667A0C/0x006679F0` specify 40-byte objects and copy callbacks
`0x00405340/0x00405370`; the exception record specifies 12 bytes and
`0x00640C9A`. This independently resolves R004's explicit-string/copy-constructor
alias. The corrected signature is length_error(const length_error &), its base
call is logic_error(const logic_error &), and no authored accounting changes.

Full vendor spans and the six independent helpers cover 2,566 distinct new
reviewed bytes; summing overlapping candidate sizes would overstate this.
This is origin evidence only. It grants no source-presence, canonical exact
or authored-byte credit. Private instruction, generated-symbol and attested
decompile evidence is under `.analysis/r005-*`.

## R006 — complete relocation-free runtime archive bodies

Reviewed 2026-10-02 after F007. Forty-one additional pending candidates are
library-owned static-runtime functions, covering 4,282 distinct, nonoverlapping
bytes. Current origin totals are 47 authored, 177 library and four compiler
candidates; 4,123 origins remain pending. All 4,351 candidates are retained.

The read-only VC7 runtime archives provide independent function bodies and
symbol metadata. A preliminary survey of libcmt, libcpmt, libc and libcp found
469 full-body non-relocation fingerprints at 264 pending candidate addresses.
That survey is diagnostic only: aliases and relocated callees/data still need
corroboration. This batch accepts only 41 relocation-free bodies with complete
vendor function-definition auxiliary records. Their recorded size is the
vendor's complete function size, not a selected target prefix or a section-size
fallback. Every byte, including relative branch fields, equals the target.

`config/runtime-origin-evidence.csv` records all 41 target extents, the archive
identity, original member names/offsets, COFF symbols, full-body SHA-256 values,
zero relocation counts and the extent basis. The selected archive is:

| Read-only artifact | SHA-256 |
| --- | --- |
| `.tools/msvc710/Vc7/lib/libcmt.lib` | `6e2b3742e58245de52149137f64281b73db1487a07a31e165fff269fbf9b2ee8` |

The public verifier extracts each recorded member into temporary private
scratch, uses the existing COFF reader without a size fallback, and compares
the full body against the hash-pinned PE. Complete decoding covers every byte;
each jump/call is direct and resolves to an instruction start in the same body.
There are no unresolved switch targets or external shared tails in this set.
Every body contains a return. The strcmp body ends with an internal JMP after
earlier return paths; its complete 136-byte range is retained rather than
truncated at an earlier RET. Temporary members are removed after verification.

The set includes memory/string primitives, ASCII comparisons, stack probing,
64-bit arithmetic, locale conversion helpers, small-block heap resizing and
floating-point conversion/control helpers. The runtime __ftol2 at
`0x006406AC` is now independently corroborated as a complete 117-byte archive
body, strengthening the conversion-helper bindings in F006/F007. Names in the
function ledger are vendor COFF symbol associations; original executable debug
names are not recovered by this evidence.

Some identical bodies also appear in the single-threaded archive. Their bytes
cannot establish which archive supplied the original link, executable-wide
threading mode, or one compiler profile for all functions. The recorded archive
pins the reproducible ownership evidence. No source-presence, mapping or
canonical exact credit is added by these vendor byte identities.

```bash
scripts/repo-python scripts/verify-runtime-origins.py
```

The local verifier passed all 41 bodies. The remaining 223 surveyed candidate
addresses stay pending until relocated symbol roles, aliases and complete
control flow are checked. Private survey/CFG evidence is under
`.analysis/crt-origin-survey.*` and `.analysis/r006-*`.
The same verifier also passed through the no-auth public Bash MCP; the private
RPC receipt is `.analysis/public-r006-runtime-origins.json`.

## R007 — complete CRT bodies with independently anchored calls

Reviewed 2026-10-02 under the user's revised strategy: finish every origin
review before resuming exact reconstruction. Eleven additional candidates,
813 complete bytes, are library/exclude. All 4,351 candidates remain retained.
No source, mapping or canonical exact credit is added.

The pinned libcmt archive supplies each function's own definition auxiliary
record and complete body. `runtime-origin-evidence.csv` adds the member
identities, vendor symbols, complete sizes and hashes. The 17 REL32 fields are
recorded separately in `runtime-origin-relocations.csv`. Each is a zero-addend
direct CALL to the matching vendor symbol at an independently verified R006
or R007 function. Every callee body passes its own complete-byte verification
before the batch is accepted; guessed names and unexplored targets cannot
anchor a binding. No DIR32 field, local-label ambiguity or opcode is masked.

The reviewed bodies are the integer conversion wrappers `_itoa`, `_ltoa` and
`_i64toa`, their complete 64-bit conversion worker, exception type matching,
variadic string concatenation, mantissa increment/rounding and long-double
conversion, 12-byte addition, and x87 control-word conversion. Complete
decoding verifies every byte, internal branch instruction start and verified
external CALL. The runtime verifier now rechecks all 52 bodies, 5,095 bytes
and 17 call bindings. Three public regressions reject an unexplored callee,
a mismatched vendor-symbol alias and a relocation masking MOV rather than
CALL. The remaining runtime survey addresses number 212 and stay pending.

```bash
scripts/repo-python scripts/verify-runtime-origins.py
```

Private diagnostic evidence is under `.analysis/r007-*`. Unfinished F008
exact probes, ledger changes and cold-build receipts were preserved with
hashes under `.analysis/deferred-exact-f008/`. They add no published exact
credit; accepted F001 through F007 units remain unchanged.

## R008 — complete relocation-free D3DX SDK COMDATs

Reviewed 2026-10-02. A diagnostic search of SDK static archives found 1,155
full non-relocation fingerprints at 579 candidate addresses. This review
accepts only 145 complete, relocation-free function COMDATs, 29,590 bytes,
whose independent vendor extent and control flow have been reconciled.
The other 434 candidate addresses remain pending, including bodies with
relocations, aliases requiring context, and trailing paths outside the strict
accepted cohort. The diagnostic survey alone grants no origin credit.

`config/sdk-origin-evidence.csv` records every accepted address, member
name/offset, symbol, full-body hash, complete extent and dispatch count.
The read-only evidence archive is:

| Artifact | SHA-256 |
| --- | --- |
| `.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib` | `39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28` |

These objects lack definition auxiliary sizes. The verifier independently
requires exactly one function-definition symbol in a code COMDAT, at section
offset zero, and uses the entire vendor section. It does not take a target
size as an extent fallback. Every byte must equal the target, and every body
must decode completely through its final RET. All direct jumps and direct
calls land on instruction starts within the same complete body. No unresolved
switch, external shared tail, padding prefix or relocation mask is accepted.
The 194 indirect calls are unchanged, unmasked vendor dispatch instructions;
they grant no classification to their callees.

The cohort covers SDK font/sprite/render-target methods, scalar/vector/matrix
operations, color conversion and surface filtering, and SDK-packaged JPEG,
PNG and zlib workers. Those codecs are vendor code, not authored game logic.
144 candidates are library/exclude. The complete `??_H` vector-construction
iterator at `0x00605D75` is compiler/exclude. Identical vendor aliases do not
recover original executable names, the original linked archive variant, or
one executable-wide compiler profile. This adds no authored-byte, source,
mapping or canonical exact credit.

```bash
scripts/repo-python scripts/verify-sdk-origins.py
```

Five public regressions cover independent whole-section sizing, rejection of
multiple functions and nonzero function starts, unresolved indirect jumps,
and branches into instruction interiors. Private survey and strict-cohort
evidence is under `.analysis/sdk-origin-survey.json` and
`.analysis/r008-sdk-zero-cohort.json`. Current totals are 384 origins reviewed:
47 authored, 332 library and five compiler candidates; 3,967 remain pending.

Both R007/R008 verifiers passed locally and through the unchanged no-auth
public Funnel Bash MCP using `scripts/repo-python`. The private combined RPC
receipt is `.analysis/public-r007-r008-origins.json`. Public CI passed 26 tests;
target-required tracking validation and progress freshness checks also passed.

## R009 — SDK call bindings and complete internal tails

Reviewed 2026-10-02. Twenty-six additional candidates, 7,034 bytes, are
library/exclude. Nineteen whole COMDAT bodies have 26 zero-addend REL32 calls
to independently verified SDK symbols. The public SDK verifier checks every
callee's complete body before accepting those bindings and requires each field
to be the immediate of the corresponding decoded CALL. The cohort includes
environment-map entry points, surface filtering, JPEG processing and zlib
dictionary setup. Original executable names remain unrecovered.

Seven relocation-free members end with unconditional branches back into their
own complete body after earlier RET paths. These were conservatively deferred
by R008's final-RET restriction. Full vendor section extents, complete decoding,
every instruction-start destination and earlier returns now prove these
internal tails: `0x0062068D`, `0x0062B862`, `0x0062C2A5`, `0x00620E05`,
`0x00621768`, `0x0062F65F`, and `0x0063DD61`. Their entire 3,152 bytes are
retained; no comparison is truncated at the first RET. The verifier still
rejects external tails, indirect jumps and trailing conditional fallthrough.

`sdk-origin-evidence.csv` records the full member identities and body hashes;
`sdk-origin-relocations.csv` records all call bindings. Four additional public
regressions cover mismatched call destinations, fields hiding a MOV, complete
internal tails and unresolved trailing conditional branches. Private proof is
under `.analysis/r009-sdk-*`. No authored, source, mapping or exact credit is
added by these vendor comparisons.

## R010 — SDK scalar definitions and matrix/color/codec workers

Reviewed 2026-10-02. Fifty-one additional candidates, 9,490 bytes, are
library/exclude. Their complete COMDATs are anchored by 34 direct calls to
verified SDK bodies and 128 DIR32 references to scalar constants. Every scalar
is independently defined in the same vendor member: one initialized-data
COMDAT at offset zero, exactly four or eight bytes, no relocations. Its full
data equals both the numerical bits encoded by its `__real@...` symbol and
the target bytes at the recorded address. This proves the data binding rather
than solving an address solely to hide an instruction difference.

The relocation CSV's `literal_hex` column records the scalar's little-endian
value; it is empty for CALLs. The verifier patches every recorded field,
compares all target function bytes and requires scalar fields to coincide with
complete decoded immediate/displacement fields. Opcode bytes and partial
fields cannot be hidden. Complete control flow has no unresolved jump/table
or external tail. The cohort includes projection matrices, color adjustments,
format conversion and codec calculations. As before, vendor aliases establish
ownership rather than original linked archive or debug-name recovery.

The SDK verifier now covers 222 complete bodies, 46,114 bytes, 60 direct-call
bindings, 128 scalar bindings and 315 unchanged indirect calls. Three added
public regressions validate real constant definitions and reject mismatched
vendor data or an opcode treated as a constant field. Private evidence is under
`.analysis/r010-sdk-*`. The remaining SDK survey addresses number 357.

```bash
scripts/repo-python scripts/verify-sdk-origins.py
```

## R011 — custom sprite drawing, geometry and diagnostic files

Reviewed 2026-10-02 against hash-attested Ghidra decompilation and independent
complete target instruction decoding. Sixteen functions add 4,941 confirmed
authored bytes. Their extents, target-body SHA-256 values, inferred roles and
branch/return counts are recorded in `config/authored-origin-evidence.csv`.
This is origin evidence only, without source, mapping or exact credit.

| Address | Bytes | Inferred custom role |
| --- | ---: | --- |
| `0x0040C9A0` | 115 | Draw supplied quad through a texture owner |
| `0x0040CA20` | 92 | Draw supplied projected quad |
| `0x0040CA80` | 1132 | Build and draw scaled/rotated/mirrored sprite |
| `0x0040CEF0` | 994 | Alternate sprite placement policy |
| `0x0040D2E0` | 970 | Sprite with independent X/Y scale |
| `0x0040D6B0` | 212 | Opaque sprite with mirroring |
| `0x0040D790` | 171 | Opaque sprite |
| `0x0040D840` | 35 | Opaque sprite with default white color |
| `0x0040D870` | 80 | Rectangle from texture dimensions |
| `0x0040D990` | 85 | Initialize custom 132-byte geometry owner to zero |
| `0x0040DA00` | 259 | Build its four corners from coordinates |
| `0x0040DB50` | 305 | Build its four corners from integer RECT |
| `0x0041CC00` | 67 | Select and truncate/create diagnostic file |
| `0x0041CC50` | 115 | Append diagnostic string |
| `0x0041CCD0` | 152 | Format and append integer diagnostic |
| `0x0041CD70` | 157 | Format and append floating diagnostic |

**Authored ownership evidence:** The sprite family resolves the application's
texture handle through `0x0040C8C0`, reads dimensions via `0x0040DD60`, builds
four corners using the game's origin/scale/angle/flip policy, and calls the
reviewed custom quad renderers `0x004029F0/0x00402D50`. Opaque variants select
the custom blend protocol at `0x00401F50`; the white wrapper supplies -1 color.
Corner swapping implements mirror policy. Rectangle builders produce the
TL/TR/BR/BL order consumed by this pipeline. These coordinated behaviors are
custom application policy, not generic SDK methods.

The zero initializer calls member constructors at offsets 0/16/32/48/64 and
then explicitly clears 132 bytes. This custom initialization policy is authored;
the member constructors are separately reviewable. The 132-byte owner contains
more than its first four 16-byte corner records. Its complete types, original
name and remaining member roles are unresolved; no partial owner is instantiated.
The four-float constructor at `0x0040DB10` remains pending because generic
custom and SDK constructor bodies can alias. The nearby empty constructors
and math helpers also receive no blanket ownership from these callers.

Ghidra's `CDialog::CreateIndirect` label at `0x0040D840` is unsupported: its
complete target body forwards to the custom opaque sprite renderer with white
color, with no dialog/template/window creation. The proposed role corrects
the ledger interpretation without modifying the private database.

The diagnostic family shares filename storage `0x0068BD00`. Its initializer
sets that storage through a string helper, calls CreateFileA with CREATE_ALWAYS,
then closes the result. Append functions use OPEN_EXISTING, GENERIC_WRITE and
FILE_END, write the observed byte count, then close on a valid handle. The
integer and float variants use target literals `%d` at `0x00657B2C` and `%f`
at `0x00657B30`; the floating argument is promoted to double. They form the
custom diagnostics used by graphics initialization, rather than CRT file state.
Their GS instrumentation stays inside the authored extents; CRT/Win32 helpers
keep separate origin decisions. The initializer's handle/error behavior is
recorded as observed, with no invented validation.

All sixteen bodies decode completely, have one final RET, and have only direct
internal branches to instruction starts. Some bodies abut the next candidate;
INT3 alignment is excluded where present. There is no unresolved switch table,
external branch or shared tail in the accepted extents. Names, partitions and
ABI declarations remain inferred. Private evidence is under
`.analysis/r011-geometry-*`, `.analysis/r011-log-family.*` and
`.analysis/r011-log-filename-xrefs.*`; reproduction uses the attested Ghidra
decompile workflow in groups of at most sixteen addresses.

R009/R010 complete SDK verification and R011 target-required tracking/status
checks also passed through the unchanged no-auth public Funnel Bash MCP using
`scripts/repo-python`. Private receipt:
`.analysis/public-r009-r011-origin-verification.json`. Public CI passed all 33
tests. Current totals are 477 reviewed origins: 63 authored, 409 library and
five compiler; 3,874 remain pending. Exact stays at 42 functions / 8,916 bytes
from the provisional 17,284-byte authored set (51.59%). The goal is incomplete.

## R012 — SDK normalization, transforms and codec workers

Reviewed 2026-10-02. Thirteen complete SDK function COMDATs, 3,420 bytes, are
library/exclude. They cover vector and quaternion normalization, coordinate
transforms, DXT1/3/5 decode, indexed/YUV color handling and JPEG dithering.
The pinned vendor members independently establish the complete extents. All
15 direct-call and 30 scalar bindings pass the existing complete-byte and CFG
verifier. Every called SDK peer also passes complete verification. No new
indirect dispatch or unresolved tail is present. The public evidence and
relocation CSVs contain the full member identities and fields; private plan
and acceptance receipts are under `.analysis/r012-sdk-*`.

## R013 — complete readonly SDK sections and their users

Reviewed 2026-10-02. Twenty-five further complete SDK bodies, 23,205 bytes,
are library/exclude. These include filtering/color conversion, JPEG/PNG
workers and assembly-optimized matrix/vector implementations. Their 31
direct-call bindings and 232 data-reference fields are verified against
independent vendor definitions. Eight unchanged indirect calls remain inside
the complete vendor bodies, without conferring ownership on their callees.

`config/sdk-origin-data.csv` records 81 whole readonly vendor sections,
3,843 bytes: archive/member identities, section number, full size/hash,
target base and every defined symbol with its section offset. The section
header determines the extent, rather than a selected symbol or matching
prefix. Every section is initialized, readable, non-executable, non-writable
and relocation-free. Every recorded byte equals the corresponding target
data, including neighboring constants in the same section. Relocated tables,
mutable globals and unresolved data remain pending.

`scripts/coff_data.py` extracts these full definitions. The SDK verifier
rechecks the complete sections before binding each DIR32 field to its named
definition and target base plus offset. Locally defined data must come from
the caller's same vendor member, preventing unrelated static-symbol aliases.
All references must occupy full decoded displacement/immediate fields.
Scalar `__real@...` evidence keeps its separate strict definition checks.
`sdk-origin-relocations.csv` adds `data_section_id`; the existing scalar and
call rows leave it empty. Eight public regressions protect whole extents,
readonly properties, symbol offsets and local-member identity.

The SDK verifier now covers 260 whole function bodies / 72,739 bytes,
106 verified direct-call bindings, 158 scalar bindings, 232 readonly-section
fields and 323 unchanged indirect calls. Full origin verification adds no
reconstruction source, mapping or exact credit. The remaining SDK survey
addresses number 319; unresolved switch tables require separate evidence.

```bash
scripts/repo-python scripts/verify-sdk-origins.py
```

## R014 — custom palette, texture uploads, cache and render wrappers

Reviewed 2026-10-02 against attested Ghidra decompilation and complete raw
target instruction decoding. Twelve functions add 1,475 authored bytes.
`config/authored-origin-evidence.csv` records the full extents, target hashes
and return/branch counts. Names and ABI declarations remain inferred.

| Address | Bytes | Inferred custom role |
| --- | ---: | --- |
| `0x0040C380` | 523 | Load and convert bitmap palette |
| `0x0040C590` | 340 | Upload indexed texture by handle |
| `0x0040C6F0` | 54 | Resolve handle and invoke upload |
| `0x0040C730` | 173 | Upload supplied texture/metadata |
| `0x0040C7E0` | 16 | Forward shared Present policy |
| `0x0040C7F0` | 65 | Couple blend mode with depth policy |
| `0x0040C840` | 25 | Forward custom depth mode |
| `0x0040C860` | 25 | Forward custom texture filter |
| `0x0040C880` | 25 | Forward custom pixel-shader mode |
| `0x0040C8A0` | 25 | Forward custom color multiplier |
| `0x0040C8C0` | 162 | Resolve texture with lazy upload/cache |
| `0x0040C970` | 42 | Resolve texture and draw projected strip |

The palette loader frees its previous palette, opens the supplied filename,
reads the file and checks the BMP signature and observed bits-per-pixel byte.
It allocates 512 bytes and converts 256 RGBQUAD entries starting at file
offset 54 into A1R5G5B5 using three-bit channel shifts and alpha bit 0x8000.
It then clears that alpha bit in the first entry. This transparency and
palette policy is application authored. The observed resource cleanup is
inside the valid-BMP branch; this review introduces no imagined validation
or error-path repair.

The indexed upload validates the handle against the application's texture
vector and reads a separate 44-byte-stride metadata container. Its special
flag selects the shared texture at index zero and width 256. Otherwise it
obtains the selected texture's surface description and releases the surface.
Successful LockRect calls invoke the conversion worker at `0x0041B990`,
then UnlockRect. That worker and the generic container accessors remain
separately pending; calls alone do not establish their origins.

The resolver uses a one-time guard at `0x006713B8` and cached handle at
`0x006713B4`. Special metadata entries reuse texture zero and upload only
when their handle differs from the cached handle. First use initializes the
cache to the incoming argument, so its observed first-use behavior must be
preserved. Blend modes 2/3/6 select depth mode 3; other modes select depth
mode 2 before forwarding to the already reviewed custom blend function.
The remaining wrappers connect this owner to the existing custom rendering
pipeline. These coordinated policies support authored ownership.

Every accepted body decodes completely, ends at its final RET and has only
direct internal branches to instruction starts. There are no unresolved
switch tables, shared tails or external jumps. Complete owner types and the
44-byte metadata record layout remain unknown; no partial owner or invented
padded record is instantiated. Private evidence is under
`.analysis/r014-texture-manager.*` and
`.analysis/r014-texture-manager-instructions.json`.

The separate vendor-container probe uses the real SDK DIDEVCAPS type,
which has size 44, to investigate element-size-dependent VC7 vector policy.
It does not claim that the game's metadata record is DIDEVCAPS. Its 83
diagnostic candidate addresses remain uncredited until complete bindings,
typed call context and CFG are checked. Private probe/receipts are under
`.analysis/MetadataVectorOrigins.cpp` and `.analysis/r015-metadata-vector-*`.

Current totals are 527 reviewed origins: 75 authored, 447 library and five
compiler; 3,824 remain pending. Exact is unchanged at 42 functions / 8,916
bytes from the provisional 18,759-byte authored set (47.53%). Review remains
incomplete, so exact reconstruction stays deferred.

R012/R013 SDK verification, all 52 runtime-origin bodies, target-required
tracking and current status also passed through the unchanged no-auth public
Funnel Bash MCP using `scripts/repo-python`. The private receipt is
`.analysis/public-r012-r014-origin-verification.json`. Public CI passed all
41 tests and the title-image progress SVG was regenerated from current ledgers.

## R015 — shared DirectSound and held-input policy

Reviewed 2026-10-02. Fifteen complete custom bodies add 3,352 authored bytes.
The target GUIDs at 0x0065B54C/0x0065B4AC/0x0065B48C match the pinned SDK's
CLSID_DirectSound8, IID_IDirectSound8 and IID_IDirectSoundBuffer8 definitions.
The family has its own client count, shared interfaces, window and
DSound-Error diagnostics. Initialization tries cooperative level PRIORITY,
then NORMAL, and creates the observed primary buffer. Buffer helpers replace
previous interfaces, create/query the secondary interface, Lock/copy/Unlock,
and preserve observed error/resource behavior. The RIFF reader finds WAVE,
fmt and data chunks, accepts PCM format 1, and reads an 18-byte format header.
This is custom integration policy; called Win32/CRT implementations retain
separate ownership.

Input mapping copies 40 bytes of bindings, validates its signed device
selector, and maintains 28 bytes of held counts. Negative selector uses
keyboard state at 0x00671240; otherwise it reads the reviewed joystick state.
Its two directional counts reset on direction reversal and grow signed
magnitude. Joystick thresholds are strictly below -500 or above 500. Five
button counts reset on release and increment while held. The clear and
key-state helpers participate in this same custom input protocol. Complete
owner/record types remain unknown.

The two audio-manager lifetime functions create the shared playback worker,
set thread priority 15 and perform the observed thread/handle/buffer cleanup
when the client count reaches zero. This does not grant ownership to generic
container helpers or compiler EH handlers. The empty function at 0x004073A0
remains pending because its body alone cannot distinguish source ownership.

| Address | Bytes | Inferred custom role |
| --- | ---: | --- |
| `0x00406610` | 56 | `SharedSound::AcquireClient` |
| `0x00406650` | 98 | `SharedSound::ReleaseClient` |
| `0x004066C0` | 29 | `SharedSound::ShowError` |
| `0x004066E0` | 311 | `SharedSound::Initialize` |
| `0x00406820` | 500 | `SharedSound::LoadWaveBuffer` |
| `0x00406A20` | 348 | `SharedSound::CreateBuffer` |
| `0x00406B80` | 559 | `SharedSound::ReadPcmWave` |
| `0x00406DB0` | 60 | `InputMapping::Initialize` |
| `0x00406DF0` | 19 | `InputMapping::ReleaseClient` |
| `0x00406E10` | 110 | `InputMapping::SetBindings` |
| `0x00406E80` | 741 | `InputMapping::UpdateHeldCounts` |
| `0x00407170` | 38 | `InputMapping::IsKeyDown` |
| `0x004071A0` | 30 | `InputMapping::ClearHeldCounts` |
| `0x004071C0` | 161 | `AudioStream::AcquireClient` |
| `0x00407270` | 292 | `AudioStream::ReleaseClient` |

All recorded bodies decode completely, retain their final physical RET and
have only direct internal branches to instruction starts. Full target hashes
and return/branch counts are in `authored-origin-evidence.csv`. Ghidra evidence
was attested in a read-only project; complete instructions/decompiles are
private under `.analysis/`. These origin decisions add no source, mapping
or exact credit.

## R016 — sound-bank serialization, playback and streaming worker

Reviewed 2026-10-02. Fifteen complete custom bodies add 3,318 authored bytes.
The bank loader constructs `%s\%03d.wav` names and populates the application's
sound-buffer collection. Serialized readers/writer use a four-byte count,
one-byte presence flag, four-byte buffer length, 18-byte wave format and
sample bytes. The archive variant calls the application's resource helpers.
This coordinated file format and buffer policy establishes authored ownership.
Called generic containers and archive helpers remain separately reviewable.

Playback resets the selected sound buffer, seeks to zero, converts the
sound-bank volume to `(value - 100) * 50`, then starts non-looping playback.
The tiny volume setters write actual bytes 0x0066C213 and 0x0066C214; Ghidra's
nearby length_error string label does not describe these audio globals.
Stream start uses looping playback and has a special zero-volume policy.
Volume offsets clamp to [-10000, 0]. File/archive queue wrappers select the
observed playback mode and request a 0x100000-byte streaming buffer.
The queue's imported wchar_t/string labels are unsupported and remain pending.

Fade configuration updates record fields and shared flags. The worker checks
playback status/position, refills with the 0x20000-byte policy, applies the
observed fade step times four, and handles stop/restart transitions. It waits
80 milliseconds between iterations. The complete 535-byte worker includes
its physical unreachable epilogue after the infinite loop; no body is
truncated to the decompiler's reachable statements and no return is invented.
Thread ABI, complete stream-owner types and original names remain unresolved.

| Address | Bytes | Inferred custom role |
| --- | ---: | --- |
| `0x004073B0` | 13 | `SoundBank::SetVolume` |
| `0x004073C0` | 13 | `AudioStream::SetVolume` |
| `0x004073D0` | 367 | `SoundBank::LoadWaveDirectory` |
| `0x00407540` | 341 | `SoundBank::LoadSerializedFile` |
| `0x004076A0` | 310 | `SoundBank::LoadSerializedArchiveEntry` |
| `0x004077E0` | 472 | `SoundBank::SaveSerializedFile` |
| `0x004079C0` | 142 | `SoundBank::Play` |
| `0x00407A50` | 289 | `AudioStream::QueueFile` |
| `0x00407B80` | 283 | `AudioStream::QueueArchiveEntry` |
| `0x00407CA0` | 29 | `AudioStream::ClearPlayback` |
| `0x00407CC0` | 169 | `AudioStream::Start` |
| `0x00407D70` | 88 | `AudioStream::Stop` |
| `0x00407DD0` | 129 | `AudioStream::ApplyVolumeOffset` |
| `0x00407E60` | 138 | `AudioStream::ScheduleFade` |
| `0x00407EF0` | 535 | `AudioStream::Worker` |

All recorded bodies decode completely, retain their final physical RET and
have only direct internal branches to instruction starts. Full target hashes
and return/branch counts are in `authored-origin-evidence.csv`. Ghidra evidence
was attested in a read-only project; complete instructions/decompiles are
private under `.analysis/`. These origin decisions add no source, mapping
or exact credit.

## R017 — stream records, game loop points and texture lifetimes

Reviewed 2026-10-02. Twelve complete custom bodies add 5,789 authored bytes.
File/archive stream openers read the observed WAVE offsets, choose full-load
or streaming mode by data size, and initially fill half of the requested
buffer. Archive access coordinates the shared loader/refill flags. Resource
cleanup closes a privately owned file handle according to the record flag
and releases the DirectSound interface. Initialization sets selected fields;
it does not establish every record field or its complete C++ type.

The loop-point readers scan the last 320 bytes for cue/adtl markers and
convert their observed counts into byte offsets using a factor of four.
The archive variant explicitly special-cases `wave\bgm\59.wav`, assigning
0x60E8AC and 0x5E0D90. This filename-specific policy is strong authored
ownership evidence. Preserve the original scan bounds, byte arithmetic and
error paths when reconstruction resumes.

The 1,724-byte refill function selects non-looping, full-loop or cue-loop
policy, reads/zero-fills across data boundaries, updates the circular-buffer
and file positions, and coordinates its shared flags. Its complete extent
has no unresolved switch/jump table or external branch. Read lengths,
wraparound and EOF arithmetic must be recovered from raw instructions before
natural exact source is accepted; a plausible rewritten streaming algorithm
would not establish equivalence.

Texture-manager construction/destruction combines the reviewed graphics
client protocol, palette ownership and separate texture/metadata containers.
Destruction releases textures and tears down members/base in the observed
order. Slot initialization selects byte format and allocates collections;
the shared-texture variant creates 256-by-256 textures. The two format-setting
functions have different observed condition chains at 0x0040B000/0x0040B110;
do not normalize them into an imagined common validation rule. Generic
container methods, allocator helpers and EH handlers remain separately pending.

The deque-like helpers at 0x00409520/0x004095C0/0x004096A0/0x00409740 remain
pending. The pinned VC7 deque source explains their map/index/size policy;
a fresh probe using the real 64-byte D3DMATRIX SDK type matches their complete
nonrelocation bytes and produced 76 diagnostic candidate addresses. The game
stream record is not claimed to be a matrix. Every call/data binding and
ambiguous alias still needs independent review. Private probe, object and
survey are under `.analysis/StreamDequeOrigins.cpp`,
`build/probes/StreamDequeOrigins.obj` and `.analysis/r018-stream-deque-*`.

| Address | Bytes | Inferred custom role |
| --- | ---: | --- |
| `0x00408110` | 627 | `AudioStreamRecord::OpenFile` |
| `0x00408390` | 727 | `AudioStreamRecord::OpenArchiveEntry` |
| `0x00408670` | 644 | `AudioStreamRecord::ReadLoopPointsFromFile` |
| `0x00408900` | 713 | `AudioStreamRecord::ReadLoopPointsFromArchive` |
| `0x00408BD0` | 1724 | `AudioStreamRecord::RefillBuffer` |
| `0x00409290` | 83 | `AudioStreamRecord::Initialize` |
| `0x004092F0` | 87 | `AudioStreamRecord::ReleaseResources` |
| `0x0040AD80` | 177 | `TextureManager::Initialize` |
| `0x0040AE40` | 434 | `TextureManager::ReleaseResources` |
| `0x0040B000` | 261 | `TextureManager::AllocateSharedTextures` |
| `0x0040B110` | 184 | `TextureManager::AllocateTextureSlots` |
| `0x0040B1D0` | 128 | `TextureManager::AllocateUnformattedSlots` |

All recorded bodies decode completely, retain their final physical RET and
have only direct internal branches to instruction starts. Full target hashes
and return/branch counts are in `authored-origin-evidence.csv`. Ghidra evidence
was attested in a read-only project; complete instructions/decompiles are
private under `.analysis/`. These origin decisions add no source, mapping
or exact credit.

`scripts/verify-authored-origins.py` now rechecks all 70 explicitly recorded
authored bodies / 18,875 bytes against the pinned target, their ledger entries,
complete decoding, hashes and CFG counts. Semantic ownership remains supported
by the documented manual evidence, not inferred automatically from a hash.
The verifier currently accepts final-RET bodies with direct internal branches;
other boundary forms need explicit future evidence. Three public regressions
reject incomplete instructions, hidden external tails and mid-instruction jumps.

Current totals are 569 reviewed origins: 117 authored, 447 library and five
compiler; 3,782 remain pending. Exact stays at 42 functions / 8,916 bytes from
the provisional 31,218-byte authored set (28.56%). Finish all origins before
resuming exact reconstruction; the goal remains incomplete.

All 70 recorded authored extents and the target-required tracking/status
checks also passed through the unchanged no-auth public Funnel Bash MCP with
`scripts/repo-python`; private receipt:
`.analysis/public-r015-r017-origin-verification.json`. Public CI passed all
44 tests and the title-image progress SVG is current.

## R019 — texture directories, palettes and texture-pack serialization

Reviewed 2026-10-02. Nine complete custom functions add 4,337 authored bytes.
The directory loaders construct `%s\%04d.bmp` names and populate the owner's
44-byte-stride metadata and texture collections. A failed bitmap load erases
the remaining metadata range. Successful paths choose shared/compressed or
individual textures, invoke the reviewed upload policy and release temporary
pixels. Preserve the observed repeated height test in the shared-texture
condition; width/height symmetry must not be invented from the decompile.

Texture-pack readers select among 512-byte palette blocks using the observed
signed-byte palette count/index and seek arithmetic. Per-image records contain
width, height, stride, a one-byte format and compressed byte length. A zero
compressed length selects the observed raw allocation size; higher formats
use four bytes per stored pixel. The archive variant uses the application's
resource handle helpers. The writer produces the corresponding record order,
loads additional `%s\pal%dp.bmp` palettes, invokes bitmap/RLE processing and
writes each data block. These filename, palette, format and upload policies
establish authored integration ownership. Called generic containers, memory
helpers and archive functions remain separately reviewable.

| Address | Bytes | Inferred custom role |
| --- | ---: | --- |
| `0x0040B250` | 33 | `TextureManager::ClearSlots` |
| `0x0040B280` | 727 | `TextureManager::LoadBitmapDirectory` |
| `0x0040B560` | 575 | `TextureManager::LoadBitmapDirectoryWithFormat` |
| `0x0040B7A0` | 27 | `TextureManager::LoadTexturePackDefaultPalette` |
| `0x0040B7C0` | 949 | `TextureManager::LoadTexturePack` |
| `0x0040BB80` | 31 | `TextureManager::LoadArchiveTexturePackDefaultPalette` |
| `0x0040BBA0` | 918 | `TextureManager::LoadArchiveTexturePack` |
| `0x0040BF40` | 31 | `TextureManager::SaveTexturePackDefaultPalette` |
| `0x0040BF60` | 1046 | `TextureManager::SaveTexturePack` |

Every body decodes completely, has a final RET and only direct internal
branches. Full extents, hashes and branch/return counts are recorded in the
authored evidence CSV. Original names, ABI and complete owners remain unknown.
Private evidence is under `.analysis/r019-texture-loaders.*` and
`.analysis/r019-texture-loader-instructions.json`. No source or exact credit
is added. R018's container surveys remain diagnostic and uncredited.

## R020 — compiler-generated exception cleanup dispatch

Reviewed 2026-10-02. 303 complete cleanup bodies / 3,174 bytes are
compiler/exclude. This decision uses compiler emission and actual exception
metadata, not Ghidra's Unwind labels or small-function byte similarity.

Fresh builds of `probes/VC7InputContainers.cpp` and `probes/VC7CompilerEH.cpp`
under the pinned VC7.1 /Od/EH/GS profile independently emit the compatible
handler and metadata ABI. A whole generated handler section is ten bytes:
load its FunctionInfo into EAX, then jump to the C++ personality endpoint.
Its own COFF data definition establishes a complete 28-byte, seven-word
FunctionInfo with magic 0x19930520. The additional ordinary string/value and
placement-copy fixtures produce independently bounded cleanup funclets,
including a placement context passed through the EBP+8 argument slot.
No reconstructed game owner is instantiated and no target function size is
used to select a convenient compiler prefix. This establishes ABI compatibility,
not an executable-wide original compiler build or original source type.

`compiler-eh-frames.csv` records 208 handler/FunctionInfo pairs, their parent
registrations and every unwind state entry. The verifier checks the full
handler dispatch, immutable metadata sections, complete FunctionInfo/unwind
hashes, descending state transitions and actual cleanup candidate entries.
All parents have the complete standard frame-registration prefix, including
the handler address and FS:[0] load. Try/handler tables are also read in full
and their state ranges checked. Evidence of registration does not settle the
parent's ownership or accept its entire boundary.

`compiler-origin-evidence.csv` records all cleanup extents, hashes, template
kinds, destinations and metadata references. Every body decodes completely
and contains only a recognized EBP-frame cleanup dispatch: local/member object,
allocation, placement failure or array cleanup. External tail jumps/calls must
resolve to known candidate entries; arrays also require a known callback entry.
There are no hidden conditionals, application-global accesses, unresolved
switches or instruction prefixes in these accepted bodies. Callee ownership
and behavior remain separate; the personality endpoint and deallocation
helpers receive no blanket credit from this batch. These funclets are entered
with their parent's frame context, not an invented standalone C++ ABI.

`scripts/verify-compiler-origins.py` rechecks the source-generated templates,
all metadata/registrations and every complete target cleanup body. Ten public
regressions reject unregistered tables, bad state transitions, truncated code,
unresolved tails and non-frame application policy, and exercise argument-slot
and placement cleanup. Private survey/acceptance evidence is under
`.analysis/r020-*`. Other unwind patterns and static lifetime wrappers remain
pending. These origin records grant no authored, source, mapping or exact credit.

```bash
scripts/compile-probe.sh probes/VC7InputContainers.cpp build/probes/CompilerEHOriginTemplates.obj /Od /Ob0 /Gy /GR- /GX /Zi /GS /I src
scripts/compile-probe.sh probes/VC7CompilerEH.cpp build/probes/CompilerEHParameterTemplates.obj /Od /Ob0 /Gy /GR- /GX /Zi /GS /I src
scripts/repo-python scripts/verify-compiler-origins.py
```

## R021 — bitmap pixels, run-length policy and selected progress records

Reviewed 2026-10-02. Twelve complete custom functions add 7,476 authored bytes.
The bitmap owner connects directly to the R019 texture-pack format and R014
upload path. Its initialization accepts observed formats 8/16/24/32 or zero,
tracks palette ownership and frees its pixel/owned-palette resources.
The file reader checks BMP signature 0x4D42, aligns stored pitch, converts
bottom-up rows, builds the application's 16-bit palette and applies its
first-entry/black-pixel transparency policy. The 24-bit path stores four-byte
pixels; the 32-bit path preserves observed source data. Error cleanup remains
as observed, with no invented header validation or repaired resource paths.

Serialized pixel loading uses the format/stride/compression fields from R019.
The encoder emits run-count/value pairs in byte, word or DWORD form. Its
8-bit path limits a run to 255; the wider paths retain their own observed
count arithmetic. The uploader selects raw or run-length decoding, applies
indexed palette conversion or direct copies, and respects the observed
width/stride behavior. Row-boundary run continuation and the raw 16-bit
width>>1 copy must be preserved when exact reconstruction resumes.

Four bounded indirect jumps belong to three complete bodies. Each dispatch
has an unsigned stack-selector CMP/JA guard, a load of that same selector,
a byte remap and a scale-four jump through the resulting case index.
`authored-origin-switches.csv` records every guard/site, full remap/table
extent, hash and default target. The four full 25-byte remaps and associated
jump tables occupy 168 bytes after the code extents. No data is interpreted
as instructions or counted as additional authored/exact bytes. All reachable
case/default destinations are internal instruction starts, with no branch
bypassing the range guard. The complete tables, rather than a selected prefix,
are verified by `authored_switches.py`; three public regressions protect
bounds, full table extent and selector data flow. Other switch forms remain
unsupported until reviewed independently.

The selected-record helpers use two signed-byte selectors at owner offsets
0x16AC4/0x16AC5, strides 0x17F0/0x5FC, a maximum-value update at selected
record offset 0x556 and a record counter. The separate encoded-item gate has
its own decimal-remainder rule and query offset 200. These coordinated policies
support authored ownership; exact record meaning and complete owner layout
remain unknown. Names and partitions are inferred, not recovered debug names.

| Address | Bytes | Inferred custom role |
| --- | ---: | --- |
| `0x0041A0E0` | 47 | `ProgressRecords::CheckEncodedItem` |
| `0x0041A1A0` | 37 | `ProgressRecords::SetSelection` |
| `0x0041A1D0` | 109 | `ProgressRecords::RaiseSelectedValue` |
| `0x0041A240` | 48 | `ProgressRecords::GetSelectedRecordAddress` |
| `0x0041A270` | 90 | `ProgressRecords::IncrementSelectedRecordCount` |
| `0x0041A2D0` | 57 | `BitmapData::Initialize` |
| `0x0041A310` | 105 | `BitmapData::InitializeWithFormat` |
| `0x0041A380` | 75 | `BitmapData::ReleaseResources` |
| `0x0041A3D0` | 3751 | `BitmapData::LoadBitmap` |
| `0x0041B2B0` | 326 | `BitmapData::LoadSerializedPixels` |
| `0x0041B400` | 1383 | `BitmapData::EncodeRuns` |
| `0x0041B990` | 1448 | `BitmapData::UploadDecodedPixels` |

Complete target hashes and branch/return counts are recorded in the authored
CSV. Attested Ghidra decompiles and complete instructions are private under
`.analysis/r021-*`. The scalar deleting-destructor candidates at
0x0041A110/0x0041A140/0x0041A170 and the following initializer at 0x0041BF90
remain pending for their separate compiler/type/owner evidence.

The authored verifier now covers 91 recorded bodies / 30,688 bytes, including
all four complete switch dispatches. It rechecks manual origin extents, not
automatically inferring semantic ownership or accepting source reconstruction.
Current totals: 893 reviewed origins, comprising 138 authored, 447 library and
308 compiler; 3,458 remain pending. Exact remains 42 functions / 8,916 bytes
from the provisional 43,031-byte authored set (20.72%). The goal remains
incomplete and exact reconstruction stays deferred until all origins are reviewed.

R019/R020/R021 verification also passed through the unchanged no-auth public
Funnel Bash MCP using `scripts/repo-python`. The remote run rechecked all
compiler, authored, SDK and runtime evidence and target-required tracking/status.
Private receipt: `.analysis/public-r019-r021-origin-verification.json`.
Local public-workflow CI passed all 57 target-independent regressions;
`git diff --check` and progress freshness passed. The 42 accepted exact units,
their source/header files and matching configuration were unchanged.

## R022 — externally registered exception frames

Reviewed 2026-10-02. Sixty further compiler/exclude candidates cover 611 bytes:
the complete 31-byte `__EH_prolog` helper at 0x006425A4 and 59 generated cleanup
bodies (580 bytes). The helper's pinned libcmt.lib member is
`..\build\intel\mt_obj\ehprolog.obj`, archive offset 666934. Its own function
auxiliary record establishes the entire extent, with no relocations. Every
byte equals the target and all instructions through RET are reviewed. It pushes
the state/handler/prior FS:[0] frame, installs the registration and establishes
EBP while preserving the real return address. This is compiler support policy,
not application behavior.

Twenty-eight additional complete FunctionInfo/unwind frames use a ten-byte
parent prefix: MOV EAX, its handler; CALL the independently verified
`__EH_prolog`. The verifier checks both instruction fields, actual parent entry
and the complete vendor helper before accepting external registration. It does
not infer ownership from an unverified helper name or arbitrary call target.
All 236 registered frames, including try/catch tables and state transitions,
are now verified. Full metadata also retains the unsupported cleanup entries;
retaining a reference does not classify that cleanup or its parent/callee.

The 59 accepted bodies use the existing fully decoded negative-frame
object/member/allocation templates. Thirty-nine positive-slot PUSH/CALL cleanups
remain pending until that distinct emission/context is independently reviewed.
The earlier 422-candidate tail diagnostic has 60 remaining pending candidates:
those 39 cleanup bodies and 21 static lifetime wrappers. No source/mapping/exact
credit is added. Private evidence: `.analysis/r022-compiler-accepted.json` and
attested `.analysis/r022-eh-prolog-parent.*`.

Two additional public regressions require independently verified prolog binding
and the correct handler load. `verify-runtime-origins.py` now rechecks 53 complete
vendor bodies / 5,126 bytes; `verify-compiler-origins.py` rechecks 362 cleanup
bodies / 3,754 bytes and 236 full registered frames. Current totals are 953
reviewed: 138 authored, 447 library and 368 compiler; 3,398 origins remain pending.
Exact remains 42 functions / 8,916 bytes and is deferred until all origins are
reviewed. The authored denominator remains 43,031 bytes (20.72% provisional).

R022 compiler/runtime and authored revalidation, target-required tracking and
status passed through the unchanged no-auth public Funnel MCP. Private receipt:
`.analysis/public-r022-origin-verification.json`. Local CI passed 59 regressions;
progress freshness and `git diff --check` passed. Accepted exact units remain
unchanged. Published R019/R020/R021 CI also passed:
https://github.com/N0zoM1z0/th075/actions/runs/37003418979.

## R023 — optimized allocation cleanups using reused argument slots

Reviewed 2026-10-02. All 39 previously deferred positive-slot cleanup bodies
(390 bytes) are now compiler/exclude. An independent ordinary C++ fixture,
`probes/VC7OptimizedEH.cpp`, selects between two real std::string allocations.
A fresh /O1/Ob0/EH build naturally reuses its EBP+12 argument slot for allocation
storage. The compiler emits two whole ten-byte cleanup bodies, each PUSH
DWORD[EBP+12] / CALL operator delete / POP ECX / RET. COFF definition offsets
0/10/20 in their complete 30-byte generated section independently bound both
funclets and the handler. The call relocation is independently typed as
operator delete. No target extent, fake local, padding or reconstructed owner
is used to select the emitted bodies. This is emission/ABI evidence only;
it does not establish that the target originally used this compiler build,
source type or exact fixture flags.

Each target cleanup is a complete ten-byte positive-frame PUSH/CALL/POP/RET
body with an actual candidate callee entry and full body hash. The 39 records
are referenced by two of the already verified 236 complete FunctionInfo frames,
including a 37-state allocation-selection frame. All metadata states remain
recorded. Actual caller code at 0x0061A4CC independently shows new allocations
stored in EBP+8 before the corresponding constructor/state transitions.
The target's original source types, parent ownership/boundary and deallocation
callee ownership remain separate questions; no ownership is inherited from
Ghidra's allocator labels. The full target body and pure dispatch template,
actual state references and independent optimized compiler emission support
the exclusion of these cleanup funclets.

```bash
scripts/compile-probe.sh probes/VC7OptimizedEH.cpp build/probes/CompilerEHOptimizedTemplates.obj /O1 /Ob0 /Gy /GR- /GX /Zi /GS- /I src
scripts/repo-python scripts/verify-compiler-origins.py
```

The compiler verifier requires this independent optimized probe whenever a
positive-slot allocation template is recorded. An additional public regression
covers positive argument-slot dispatch; absolute globals and indirect/unresolved
transfers remain rejected. Private evidence: `.analysis/r023-*`. The verifier
now covers 401 cleanup bodies / 4,144 bytes and 236 full frames. Only the 21
static lifetime wrappers remain pending in the earlier 422-candidate tail survey.

Current totals are 992 reviewed origins: 138 authored, 447 library and 407
compiler; 3,359 remain pending. Exact remains 42 functions / 8,916 bytes from
the provisional 43,031-byte authored set (20.72%). Exact work remains deferred
until all origins are reviewed; the full goal remains incomplete.

R023 compiler/runtime and authored verification plus target-required tracking/
status passed through the unchanged no-auth public Funnel MCP. Private receipt:
`.analysis/public-r023-origin-verification.json`. Local CI passed 60 regressions;
progress freshness and `git diff --check` passed. R022's published GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37003968089.

## R024 — generated global initialization and finalization wrappers

Reviewed 2026-10-02. Twenty-one complete compiler-generated wrappers / 468
bytes are excluded from authored reconstruction. The executable's 106-byte
startup runner at 0x0064411D walks the complete function-pointer interval
0x0066C000..0x0066C034. Eleven candidate wrappers occupy consecutive slots
0x0066C008..0x0066C030; the table has the observed zero sentinels and a
separate security-cookie initializer before them. This is actual startup
registration evidence, not a label inferred from Ghidra.

A fresh, ordinary VC7 C++ fixture defines a global string, vector, two-element
string array and one object with a constructor but no destructor. The compiler
emits separate, whole COFF code sections for the same four wrapper structures:
28-byte object init plus exit registration, 15-byte object finalization,
42/24-byte array init/finalization, and a 15-byte init-only wrapper.
`verify-static-origins.py` checks every fixture section's complete size,
instruction pattern and relocation fields. Source lives in
`probes/VC7StaticLifetime.cpp`; it does not declare the game's global types.
The array fixture uses a 28-byte string stride; the target's two-element array
uses 72 bytes. That observed target stride is retained and does not imply the
same object type. Compiler emission establishes the wrapper form only.

Target verification checks the full hash, instruction sequence and actual
fields of each body, the writable global address, complete startup slot,
known constructor/destructor entry and every callback pairing. Ten init
wrappers register ten distinct finalizers, with matching global addresses;
the remaining startup wrapper initializes without registering a finalizer.
The array pair also agrees on its constructor/destructor callback, count two,
stride 72 and array address. The registration destination at 0x0064168B is
checked against its own complete pinned libcmt `_atexit` body and the complete
vendor fingerprint of its `__onexit` call target. The latter's downstream
relocation bindings and origin remain separately pending. The wrappers' called
constructors, destructor bodies, vector iterator helpers, complete global
types and startup runner origin are not classified by inheritance.

| Wrapper group | Startup addresses | Finalizer addresses |
| --- | --- | --- |
| Single global | 0x00656D00, 0x00656D20, 0x00656D40, 0x00656D90, 0x00656DC0, 0x00656DE0, 0x00656E00, 0x00656E20, 0x00656E40 | 0x00656E60, 0x00656E70, 0x00656E80, 0x00656EB0, 0x00656EC0, 0x00656ED0, 0x00656EE0, 0x00656EF0, 0x00656F00 |
| Two-element array | 0x00656D60 | 0x00656E90 |
| Init only | 0x00656DB0 | — |

```bash
scripts/compile-probe.sh probes/VC7StaticLifetime.cpp build/probes/StaticLifetimeOrigins.obj /Od /Ob0 /Gy /GR- /GX /Zi /GS /I src
scripts/repo-python scripts/verify-static-origins.py
```

The evidence CSV records all complete extents, hashes, global/callee/callback
fields, table slots and inferred template kinds. Five public regressions reject
missing or mismatched finalizers and wrong startup membership. The earlier
422-candidate tail survey now has no pending entries. Private source inspection
and diagnostics are under `.analysis/r024-*`. These origin decisions grant no
source, mapping or exact credit.

Current totals: 1,013 reviewed origins, comprising 138 authored, 447 library
and 428 compiler; 3,338 remain pending. Exact remains 42 functions / 8,916
bytes from the provisional 43,031-byte authored set (20.72%). Finish the
remaining origins before returning to exact reconstruction.

R024 static, compiler, authored, SDK and runtime verifiers plus target-required
tracking/status passed through the unchanged no-auth public Funnel MCP. Private
receipt: `.analysis/public-r024-origin-verification.json`. Local CI passed 65
regressions; progress freshness and `git diff --check` passed. The R023 public
GitHub CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37004206011.

## R025 — complete CRT local tables and dependent conversion

Reviewed 2026-10-02. Four more library bodies / 1,881 bytes are excluded:
`__local_unwind2` at 0x00640B66 (104 bytes), two 829-byte memory-copy bodies
at 0x00640F20/0x00641260 and `__fptostr` at 0x0064F86B (119 bytes).
The first three have 93 COFF DIR32 relocations in total. Every relocation
uses an independently defined symbol in the same pinned libcmt member, with
its source addend and exact target address checked. The two memory-copy
bodies' 46 table/pointer references each remain inside their complete
829-byte vendor auxiliary extents. Their entire linked bytes, including
embedded tables and final RET, equal the target. Distinct `_memcpy` and
`_memmove` archive members emit byte-identical implementations here; the
proposed symbolic names use the matching member but the original linker's
chosen alias is not proven by bytes alone.

`__local_unwind2` has one local pointer to the preceding
`__unwind_handler` at 0x00640B44. The latter has a separate whole 34-byte
vendor function definition in the same COFF member; all 34 target bytes
match. It is not one of the original 4,351 inventory candidates. This
validates the linked pointer without granting a separate mapped/source/exact
function or extrapolating other helper ownership.

The fourth body has two zero-addend direct calls. `_strlen` was already
separately verified; `_memmove` is the newly verified complete local-relocated
body. `verify-runtime-origins.py` requires the local verifier to pass before
allowing these callees as anchors. It then checks the complete `__fptostr`
source extent, both resolved calls, full target bytes and control flow.
No mutable globals or guessed aliases were accepted through this dependency.

`runtime-local-evidence.csv` records the three complete source members,
auxiliary extents, whole hashes, relocation counts and one helper dependency.
`verify-runtime-local-origins.py` recomputes every local field from the pinned
archive. Three public regressions reject an escaped local pointer, an unverified
member-local dependency and a hidden call relocation. The existing runtime
verifier now covers 54 bodies / 5,245 bytes and 19 verified direct calls;
the separate local verifier covers three bodies / 1,762 bytes and 93 internal
relocations. They grant origin evidence only. Private selection/byte evidence
is under `.analysis/r025-*`.

Current totals are 1,017 reviewed: 138 authored, 451 library, 428 compiler;
3,334 remain pending. Exact remains 42 functions / 8,916 bytes, with a
provisional authored denominator of 43,031 (20.72%). Exact reconstruction
continues after the complete origin review.

R025 local CRT, linked runtime, static, compiler, authored and SDK origin
verifiers plus target-required tracking/status passed through the unchanged
no-auth public Funnel MCP. Private receipt:
`.analysis/public-r025-origin-verification.json`. Local CI passed 68 regressions;
progress freshness and `git diff --check` passed. R024 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37004893091.

## R026 — short whole SDK functions with typed caller witnesses

Reviewed 2026-10-02. Thirty-one complete D3DX8 SDK COMDAT bodies / 630 bytes
are excluded. These 8–30-byte functions had fallen below the earlier diagnostic
fingerprint length threshold; that threshold was never an origin decision.
A fresh survey used each vendor object's independently defined, whole,
relocation-free code section and compared every byte to a pending target
candidate. Many short implementations have multiple identical vendor symbols.
For each accepted function, a separate complete vendor caller body has an
exactly typed REL32 CALL to the selected symbol and the actual target address.
The caller's entire non-relocated extent was checked against the pinned target;
all relocation fields were masked explicitly, and the selected CALL opcode,
field and destination were then verified. This disambiguates short aliases
without granting any origin credit to the callers. Thirty-one source/caller
pairs passed; seven other short byte-identical candidates without the required
typed caller witness remain pending.

The accepted functions include D3DX file/resource/image and stack constructors,
bitmap operations, PNG getters/setters, JPEG allocation/math helpers and a zlib
free helper. Some complete bodies have unchanged indirect calls. Their callee
ownership remains independent. `sdk-short-origin-witnesses.csv` records the
specific caller/member/symbol/field for every accepted body;
`verify-sdk-short-origins.py` rechecks all 31 whole caller definitions and typed
fields. The normal SDK verifier also rechecks each short source COMDAT,
complete body hash, target bytes and control flow. Four public regressions
reject an unrelated caller opcode, a wrong symbol or a wrong destination.
Private survey and full caller checks are under `.analysis/r026-*`.

## R027 — direct-call closure from independently verified SDK bodies

Reviewed 2026-10-02. Fifteen more complete D3DX8 functions / 4,129 bytes are
excluded using 34 zero-addend direct calls. Every callee was already a
separately verified complete SDK origin when the caller was accepted; the
source COFF symbol, relocation offset, target CALL opcode and actual destination
all agree. The review started from the R026 JPEG/zlib helpers and propagated
only when every direct relocation could be bound. It reached JPEG marker,
scan, virtual-array, dithering and output-dimension helpers, plus zlib inflate
reset/block and free helpers. Unchanged indirect calls remain separately
uncredited to their callees. No mutable data, guessed imports or external tail
jumps were accepted.

`verify-sdk-origins.py` now rechecks 306 whole COMDAT bodies / 77,498 bytes,
140 direct-call bindings, 332 earlier plus 42 new unchanged indirect calls,
158 scalar bindings and 232 fields from 81 complete readonly sections.
R026/R027 add origin evidence only. Current totals are 1,063 reviewed:
138 authored, 497 library and 428 compiler; 3,288 remain pending. Exact
remains 42 functions / 8,916 bytes against the provisional 43,031-byte
authored set (20.72%). The complete-origin prerequisite is still open.

R026/R027 SDK, runtime, static, compiler and authored origin verifiers plus
target-required tracking/status passed through the unchanged no-auth public
Funnel MCP. Private receipt: `.analysis/public-r026-r027-origin-verification.json`.
Local CI passed 72 regressions; progress freshness and `git diff --check`
passed. R025 published GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37005233600.

## R028 — SDK function-pointer relocations

Reviewed 2026-10-02. Three complete D3DX8 JPEG decoder COMDATs / 830 bytes
are excluded: `jinit_huff_decoder` at 0x0062C9D3 (58 bytes),
`start_pass_phuff_decoder` at 0x0062D2DE (675 bytes), and
`jinit_phuff_decoder` at 0x0062D581 (97 bytes). Their source members have a
single complete code-function definition at section offset zero. The pinned
archive member, complete section extent and hash, linked target bytes, and
decoded control flow are independently checked for each body.

Seven DIR32 fields store pointers to separately verified complete SDK
functions. Each binding checks the source relocation symbol, zero addend,
immediate/operand field, resolved target entry and the callee's independently
verified symbol. The first decoder binds two functions, the progressive-pass
decoder binds four, and the progressive initializer binds the verified pass
decoder. The pass decoder also has two separately bound REL32 calls to
`jpeg_make_d_derived_tbl`. Its indirect calls do not identify their runtime
targets or grant any callee ownership. Mutable data and guessed pointers
remain pending.

`sdk-origin-relocations.csv` now distinguishes function-pointer fields from
scalar constants and complete readonly-section data. `verify-sdk-origins.py`
rejects an unsupported target kind, a function-pointer field claimed as a
direct call, and a pointer whose relocation symbol lacks the verified callee.
A public regression checks a valid pointer and rejects a missing callee.
The SDK verifier now covers 309 complete bodies / 78,328 bytes, 142 direct-call
bindings, 7 function-pointer bindings, 158 scalar bindings, 232 readonly
fields from 81 complete sections, and 382 unchanged indirect calls. R028 adds
origin evidence only; no source or exact credit. Current totals are 1,066
reviewed: 138 authored, 500 library and 428 compiler; 3,285 remain pending.
Exact remains 42 functions / 8,916 bytes against the provisional 43,031-byte
authored slice (20.72%). The complete-origin prerequisite is still open.

Local CI passed 73 regressions; target-required tracking, progress freshness
and `git diff --check` passed. Public no-auth Funnel verification receipt:
`.analysis/public-r028-origin-verification.json`. R027 published GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37005857354.

## R029 — whole SDK readonly data and bounded source addends

Reviewed 2026-10-02. Ten more complete D3DX8 COMDAT functions / 2,093 bytes
are excluded. Six PNG/zlib functions bind complete readonly string or local
constant sections, one exact real scalar, verified SDK function pointers and
independently reviewed direct calls. Four JPEG functions then bind whole
`jpeg_natural_order` or `_base_dither_matrix` sections: `get_dqt` (553 bytes),
`make_odither_array` (98), `create_odither_tables` (197), and
`start_pass_1_quant` (202). The last one became eligible only after its
`create_odither_tables` callee was independently reviewed.

Three DIR32 source fields carry an explicit +256 addend. The verifier checks
the source symbol's actual offset in its complete, relocation-free readonly
section, the source addend, the resolved target address, and the full target
section bytes. The two `_base_dither_matrix` fields point exactly one byte
past the 256-byte section, so the verifier permits an endpoint pointer while
rejecting any farther address; this is pointer provenance, not a claim that
the endpoint can be dereferenced. The `jpeg_natural_order` field points
inside its 576-byte source section. Real scalar constants and function
pointers still require zero source addends. A public regression checks a
bounded data addend and rejects one outside the whole section.

`sdk-origin-data.csv` adds seven completely checked readonly sections; the
earlier whole `jpeg_natural_order` section was already independently verified.
All accepted code sections have one complete function definition, pinned
archive/member identity, complete body hash, linked bytes and decoded control
flow. The ten bodies add 13 direct calls, five function-pointer fields, 12
readonly-section fields, one scalar field, and 12 unchanged indirect calls.
The SDK verifier now covers 319 bodies / 80,421 bytes, 155 direct-call fields,
12 function pointers, 159 scalars, 244 readonly fields from 88 complete
sections, and 394 unchanged indirect calls. These origin records add no source
or exact credit and do not establish the owners of called functions.

Current totals are 1,076 reviewed: 138 authored, 510 library and 428 compiler;
3,275 remain pending. Exact remains 42 functions / 8,916 bytes against the
provisional 43,031-byte authored slice (20.72%). The complete-origin
prerequisite remains open. Local CI passed 74 regressions; target-required
tracking, progress freshness and `git diff --check` passed. Public no-auth
Funnel receipt: `.analysis/public-r029-origin-verification.json`. R028 GitHub
CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37006188725.

## R030 — independently decoded PE import thunks

Reviewed 2026-10-02. Three complete six-byte `FF 25` entries are excluded as
linker-generated import thunks: 0x006036A4 for
`DINPUT8.dll!DirectInput8Create`, 0x0060499A for
`d3d8.dll!Direct3DCreate8`, and 0x00654B54 for
`KERNEL32.dll!RtlUnwind`. The pinned target PE's import directory contains
eight descriptors and 157 independently decoded IAT slots. Each six-byte
body is one complete indirect JMP, and its embedded absolute operand names
the exact recorded IAT slot. The on-disk original lookup and IAT values agree;
the descriptor's DLL and import-by-name record establish the symbol without
using Ghidra's imported label as evidence. Complete target body hashes are
recorded in `import-origin-evidence.csv` and rechecked by
`verify-import-origins.py`.

The three records classify only the linker trampolines, not the imported
implementations or their callers. Fourteen other pending six-byte `FF 25`
bodies point to non-import addresses; their opcode shape grants no import
origin. Three public regressions cover complete descriptor/slot resolution,
wrong slot or symbol, and an IAT value that differs from the original lookup.
This batch adds no source or exact credit. Current totals are 1,079 reviewed:
138 authored, 510 library, 431 compiler; 3,272 pending. Exact remains 42
functions / 8,916 bytes against the provisional 43,031-byte authored slice
(20.72%). The complete-origin prerequisite remains open.

Local CI passed 77 regressions; target-required tracking, progress freshness
and `git diff --check` passed. Public no-auth Funnel verification receipt:
`.analysis/public-r030-origin-verification.json`. R029 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37006586340.

## R031 — complete VC7 STL record templates and split catch bodies

Reviewed 2026-10-02. Eight complete vendor `std::_Uninit_fill_n` or
`std::_Uninit_copy` bodies / 1,276 distinct bytes exclude 32 original
inventory candidates. Ghidra split each actual function into four contiguous
pieces: the main entry, a two-byte catch jump, a nine-byte catch adjustment,
and the remainder through the complete RET. The first ledger row now records
the whole function extent, while the other three rows remain explicit
non-independent analysis fragments. No candidate was dropped to reduce the
pending count.

| Complete entry | Bytes | Generic template | Probe record width |
| --- | ---: | --- | ---: |
| `0x0040F780` | 157 | `_Uninit_fill_n` | 44 |
| `0x0040F880` | 162 | `_Uninit_copy` | 44 |
| `0x0045AE10` | 157 | `_Uninit_fill_n` | 16 |
| `0x0045B170` | 157 | `_Uninit_fill_n` | 116 |
| `0x0045B3C0` | 162 | `_Uninit_copy` | 16 |
| `0x0045B470` | 162 | `_Uninit_copy` | 116 |
| `0x005FA810` | 157 | `_Uninit_fill_n` | 16 |
| `0x005FA960` | 162 | `_Uninit_copy` | 16 |

The independent, ordinary VC7 probe in
`probes/VC7OriginRecordContainers.cpp` instantiates `std::vector` on synthetic
16-, 44- and 116-byte aggregates with the pinned `/Od /Ob0 /Gy /GR- /GX /Zi
/GS /I src` profile. Each selected COFF primary definition has an auxiliary
size equal to its entire COMDAT section. The compiler also emits a local
`$L...` catch label typed as a function at an interior offset; the verifier
permits that local label but rejects a second external function definition.
The synthetic types demonstrate generic compiler/STL emission and **do not**
identify the target's original record types or owner layouts.

`verify-vendor-record-origins.py` cold-compiles the probe, checks the whole
source section and target hashes, masks only the seven typed relocation fields
per body, and compares every other byte. All 56 fields are then resolved from
the target's actual instruction operands: eight EH-handler pointers, 24
`__except_list` fields, and 24 direct calls with source roles for construct,
destroy and throw. Complete target decoding proves internal branches and
terminal returns. The recorded four-piece coverage exactly partitions each
whole body; three public regressions cover a complete local-label extent and
reject an external peer or a wrong typed binding.
Called helper origins and EH-handler owners remain independent questions.

R031 adds vendor-origin exclusions only, with no authored source or exact
credit. Current totals are 1,111 reviewed: 138 authored, 542 library and 431
compiler; 3,240 remain pending. Exact remains 42 functions / 8,916 bytes
against the provisional 43,031-byte authored slice (20.72%). Local CI passed
80 regressions; target-required tracking, progress freshness and
`git diff --check` passed. Public no-auth Funnel receipt:
`.analysis/public-r031-origin-verification.json`. R030 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37007109069.

## R032 — unambiguous VC7 STL record helpers

Reviewed 2026-10-02. A complete-source survey of the same ordinary VC7
`std::vector` probe found 129 additional pending target bodies / 7,545 bytes.
Each candidate has exactly the size of a whole COFF primary function
definition, with its auxiliary size equal to its complete COMDAT section.
Every non-relocation byte agrees across the complete target body, all 398
typed relocation fields are explicitly resolved (200 REL32 and 198 DIR32),
and decoded control flow reaches the complete RET without an unresolved
outgoing jump. There are no indirect calls in these bodies.

For each target body, `verify-vendor-record-helpers.py` cold-compiles the
pinned probe and scans all 72 complete record-related source definitions of
at least 32 bytes. It accepts only when every matching source symbol reduces
to **one** STL template family after replacing the synthetic `Record16`,
`Record44`, and `Record116` type names with a neutral record placeholder.
Ninety-six targets match all three synthetic widths within one family;
33 match one width-specific definition. Neither observation establishes the
original target type. Eighteen distinct template families are represented,
including vector bounds/iterator, insert/erase, allocation, fill/copy,
construction and destruction helpers. The exact matched-source alias set,
complete hashes, source symbol, and every relocation are recorded in
`vendor-record-helper-origins.csv` and rechecked from a fresh object.

Eight other target starts match both `copy` and `copy_backward` source families
with identical complete bodies. They remain pending rather than selecting a
convenient original name. Three public regressions require one family despite
width aliases, reject two matching families, and reject a recorded symbol
whose whole body does not match. The chosen synthetic COFF symbol is a
compiler oracle, not a claim about the target's original symbol or record
layout. Callee ownership remains separate.

R032 adds library-origin evidence only, with no source or exact credit.
Current totals are 1,240 reviewed: 138 authored, 671 library and 431 compiler;
3,111 remain pending. Exact remains 42 functions / 8,916 bytes against the
provisional 43,031-byte authored slice (20.72%). The complete-origin
prerequisite is still open. Local CI passed 83 regressions; target-required
tracking, progress freshness and `git diff --check` passed. Public no-auth
Funnel receipt: `.analysis/public-r032-origin-verification.json`. R031 GitHub
CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37007728822.

## R033 — typed caller witnesses for short helpers and copy aliases

Reviewed 2026-10-02. Twenty-six more complete VC7 STL bodies / 704 bytes are
excluded: 23 short helpers (551 bytes) and three 51-byte `copy` aliases
(153 bytes). Each short helper has a whole-body match to the independently
compiled VC7 record probe and only one matching generic template family.
Short bodies can have byte-identical aliases, so each accepted one also has a
separately verified complete vendor caller whose **typed REL32 relocation**
names the selected source symbol and resolves to the actual target entry.

Three R032 dual-family bodies at 0x0040F270, 0x0045A7E0, and 0x005FA170
match both `copy` and `copy_backward` source bodies by bytes. Their complete
R032 `erase` callers at 0x0040DDC0, 0x00459900, and 0x005F8F60 respectively
have typed relocations to `copy`, fixing those three source-family choices.
The five other dual-family candidates lack a complete matching typed caller
in this probe and remain pending. Synthetic `Record16`/`Record44`/`Record116`
aliases do not identify original target types.

`verify-vendor-record-witnesses.py` cold-compiles the source probe and
rechecks each callee's complete source/target bytes, relocation fields, CFG,
matching source-symbol set, and family scope. It then independently rechecks
each witness caller's entire source and target bodies, every typed field and
the exact CALL opcode/destination. Twenty-two witnesses use R032 caller
records; four use R031 whole template callers. A caller's review status is
never inherited by its callee. Two public regressions reject a wrong source
symbol or a wrong target address at the witness field.

These are library-origin records only, with no authored source or exact credit.
Current totals are 1,266 reviewed: 138 authored, 697 library and 431 compiler;
3,085 remain pending. Exact remains 42 functions / 8,916 bytes against the
provisional 43,031-byte authored slice (20.72%). Local CI passed 85
regressions; target-required tracking, progress freshness and
`git diff --check` passed. Public no-auth Funnel receipt:
`.analysis/public-r033-origin-verification.json`. R032 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37008140937.

## R034 — additional VC7 record-width probes

Reviewed 2026-10-02. Thirty-one further complete VC7 STL helper bodies /
1,685 bytes are excluded. The independent ordinary source probe in
`probes/VC7AdditionalRecordContainers.cpp` instantiates `std::vector` for
fourteen synthetic aggregate widths: 4, 8, 12, 20, 24, 28, 32, 40, 48, 64,
72, 80, 96 and 128 bytes. The 31 accepted target bodies match complete source
COMDATs selected from widths 4, 8, 20 and 64. Width agreement is evidence of
compiler emission only; it does not recover any original record type.

`verify-vendor-additional-records.py` cold-compiles the probe and extracts all
336 complete record-related source definitions of at least 32 bytes, requiring
each primary auxiliary size to cover its whole code section. It matches each
target against *all* definitions, admits one generic STL template family,
and checks the exact source alias set, both complete-body hashes, all 26 typed
REL32 fields and decoded CFG through the terminal RET. Six template families
are represented: size, capacity, assignment, allocator `max_size`, vector
`_Ufill` and construction. No indirect calls are credited. Five
additional `copy`/`copy_backward` dual-family hits remain pending; the broader
width probe does not resolve their original family.

Two public regressions accept width variants within one family and reject
`copy`/`copy_backward` conflation. The 31 new exclusions grant no callee,
authored source or exact credit. Current totals are 1,297 reviewed: 138
authored, 728 library and 431 compiler; 3,054 remain pending. Exact remains
42 functions / 8,916 bytes against the provisional 43,031-byte authored slice
(20.72%). Local CI passed 87 regressions; target-required tracking, progress
freshness and `git diff --check` passed. Public no-auth Funnel receipt:
`.analysis/public-r034-origin-verification.json`. R033 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37008617872.

## R035 — sprite geometry, camera motion, replay records and timed scene rendering

Reviewed 2026-10-02. Twenty complete bodies / 17,149 bytes have independent
target-observed authored behavior. Their names and class boundaries are
provisional. Each entry has a pinned whole-body SHA-256 in
`config/authored-origin-evidence.csv`; `verify-authored-origins.py` decodes the
entire recorded extent, checks that its last instruction is RET, and verifies
every direct branch remains on an instruction boundary inside that extent.
All twenty have one terminal RET and no unresolved outgoing branch. This is
origin evidence only; no source or exact-match credit follows.

| Entry | Target-observed behavior supporting authored origin |
| --- | --- |
| `0x00410350` | Draws a sprite node from its own position, color, rotation and flip fields; chooses projected or ordinary custom quad drawing. |
| `0x00410A00` | Draws the mirrored node with inverted Y placement and the shared camera offsets. |
| `0x00411000` | Copies one 132-byte scene element, appends it to the scene sequence and applies a scene-specific count limit. |
| `0x00411110` | Walks that sequence, builds custom sprite quads and renders them using node texture and color state. |
| `0x00411400` | Converts four corners of a rectangle into the project's four-vertex sprite geometry. |
| `0x00411500` | Translates all four vertex positions in the project-specific 16-byte vertex layout. |
| `0x004115C0` | Scales those four positions about supplied X/Y/Z pivots, skipping unit axes. |
| `0x004116F0` | Rotates the same four positions using the project's trigonometric helpers. |
| `0x004126C0` | Clamps and eases the shared camera coordinates, damps camera shake and updates direction from tracked positions. |
| `0x00412CB0` | Sets the camera shake amplitude in the same shared camera state. |
| `0x00412CC0` | Installs a camera-position override and its three coordinates in that state. |
| `0x00412CF0` | Snaps the same camera state to current or override coordinates. |
| `0x00412DD0` | Initializes project graphics resources, loads `data\\system\\window.dat` and selects a 1024-by-512 render surface. |
| `0x00412EB0` | Builds a 571-pixel text region and draws its outline and alpha-changing fill with project sprite routines. |
| `0x00413790` | Resets record/date fields and opens `replay\\replay.tmp` for capture. |
| `0x004138E0` | Writes a 60-byte record header, copies temporary replay bytes and closes both files. |
| `0x00413AC0` | Seeks to a selected replay record and reads its packed byte fields from the game's replay file. |
| `0x00413DE0` | Writes those packed fields and variable-length 1-, 2- and 4-byte record arrays, then advances the record index. |
| `0x00414300` | Searches numbered `replay\\replay%03d.rep` paths up to slot 999 and selects the first unused file. |
| `0x004277A0` | Uses explicit millisecond intervals, sprite IDs and fade windows to draw a fixed animated scene. |

These are local observations of each body, not classifications inherited from
callers or callees. The nearby VC7 iterator/container helpers and
exception-frame code remain separately reviewed or pending. The Ghidra
decompilations used for semantic inspection are private diagnostic hypotheses
under `.analysis/r035-*-survey.*`; whole-byte and CFG claims come from the
attested target, not from decompiler text. Current totals are 1,317 reviewed:
158 authored, 728 library and 431 compiler; 3,034 remain pending. Exact
remains 42 functions / 8,916 bytes against the provisional 60,180-byte
authored slice (14.82%). The complete-origin prerequisite remains open.
Local CI passed 87 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran
the authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r035-origin-verification.json`.

## R036 — opening scene ownership and node transforms

Reviewed 2026-10-02. Six further complete game-authored bodies / 2,467 bytes
were inspected separately and recorded with whole-body hashes and complete
local CFG metadata. Each has one terminal RET and no unresolved outgoing
branch. `0x004275D0` explicitly loads `data\\system\\opening.dat`, sets up
graphics and stores an initial `timeGetTime` timestamp. This makes
`OpeningScene` a better inferred role for the already reviewed R035 timed
renderer at `0x004277A0`; only its provisional name changed. The renderer's
own time-window and sprite-ID logic remains its independent origin evidence.

| Entry | Target-observed behavior supporting authored origin |
| --- | --- |
| `0x0040FBB0` | Resets the node's custom transform, color and rotation fields to project-specific defaults. |
| `0x0040FC70` | Composes those node fields with camera offsets, flip and color policy before drawing a custom sprite quad. |
| `0x004275D0` | Creates opening-scene graphics state, loads `opening.dat` and initializes elapsed time. |
| `0x004276B0` | Releases the scene's owned graphics resource and runs its scene cleanup path. |
| `0x00427730` | Advances the scene using elapsed time, skip flags and explicit transition result codes. |
| `0x00428C80` | Runs frame/input updates and toggles window mode for a specific key combination. |

The adjacent scalar math wrapper and deleting-destructor thunk are still
pending. No caller/callee origin was inherited. R036 adds no source or exact
credit. Totals are 1,323 reviewed: 164 authored, 728 library and 431 compiler;
3,028 remain pending. Exact remains 42 functions / 8,916 bytes against a
provisional 62,647-byte authored slice (14.23%).

## R037 — generated VC7 scalar deleting destructors

Reviewed 2026-10-02. Eighty more complete 44-byte bodies / 3,520 bytes are
classified compiler/exclude. A new independent ordinary C++ fixture,
`probes/VC7DeletingDestructor.cpp`, defines a synthetic class with a virtual
destructor and invokes `delete`. A cold pinned VC7.1 build emits its generated
scalar deleting destructor as the **sole** function in a complete 44-byte
executable COMDAT. It has exactly two typed REL32 fields: the synthetic
class destructor and `operator delete`. The source class has no inferred
relationship to any game's class or layout.

`scripts/verify-scalar-deleting-origins.py` recompiles the fixture, checks
the entire COFF section, sole definition, both relocation types and symbols,
and the full source body. It then checks every target body's complete SHA-256,
all nonrelocated bytes, terminal RET and internal conditional branch. Both
target CALL opcodes and destinations are decoded: the first must reach a
recorded function entry, and the second must reach `0x00640F15`, the same
`operator delete` address bound by the independently reviewed R005 vendor
deleting-destructor examples. The 80 per-body hashes and call targets are
recorded in `config/scalar-deleting-origin-evidence.csv`. All complete
44-byte candidates with this generated shape and delete endpoint are now
accounted for: these 80 plus the two R005 compiler bodies.

These wrappers' *own* origin is compiler-generated. The first call target's
origin is not inherited, and the pending `operator delete` body is not
classified by this call-site evidence. No authored source or exact credit is
added. Four public regressions reject a changed branch/body, trailing code,
an unknown destructor entry or a different delete destination. Current totals
are 1,403 reviewed: 164 authored, 728 library and 511 compiler; 2,948 remain
pending. Exact remains 42 functions / 8,916 bytes against the provisional
62,647-byte authored slice (14.23%).
Local CI passed 91 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP
cold-ran the new verifier and target-required status checks successfully;
private receipt: `.analysis/public-r037-origin-verification.json`.

## R038 — optimized VC7 scalar deleting destructors

Reviewed 2026-10-02. Fifty-three additional complete 28-byte bodies /
1,484 bytes are compiler/exclude. The **same synthetic source fixture** from
R037, cold-compiled with VC7.1 `/O1 /Ob0 /Gy /GR- /GX- /Zi /GS`, emits a
different complete scalar deleting destructor as its sole executable COMDAT.
Its two typed REL32 fields move to offsets `+4` and `+17`; the low-bit test,
conditional deallocation, return of `this` and terminal `RET 4` remain.
This profile is evidence for the generated body shape, not a claim that the
entire target or any original class used `/O1`.

`scripts/verify-optimized-deleting-origins.py` cold-builds that fixture and
reuses R037's whole-section, unique-definition, relocation and decoded-body
checks with the optimized size and offsets. It binds each target's first CALL
to an actual candidate function entry and its second CALL to the R005-anchored
`operator delete` at `0x00640F15`. Individual whole-body hashes, source hash
and both destinations are recorded in
`config/optimized-deleting-origin-evidence.csv`. This includes the CRT-linked
`type_info` wrapper at `0x00640E8F`; only its generated wrapper is classified
here. The callee destructor and deallocator keep independent origin decisions.

All 53 complete 28-byte candidates with this generated shape and delete
endpoint are now accounted for. No authored source or exact credit is added.
Current totals are 1,456 reviewed: 164 authored, 728 library and 564
compiler; 2,895 remain pending. Exact remains 42 functions / 8,916 bytes
against the provisional 62,647-byte authored slice (14.23%).
Local CI passed 92 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP
cold-ran both deleting-destructor verifiers and target-required status checks;
private receipt: `.analysis/public-r038-origin-verification.json`.

## R039 — complete D3DX8 destructor-forwarding COMDATs

Reviewed 2026-10-02. Thirty-nine complete five-byte D3DX8 forwarding
functions / 195 bytes are library/exclude. The pinned `d3dx8.lib` contains
standalone executable COMDATs consisting of a single `JMP rel32` with one
typed REL32 relocation. Their source groups are 30 base-codec destructor
aliases, five DXT aliases, two YUV aliases and one each for the surface and
volume lock wrappers. Each accepted target body has exactly the same complete
five-byte form and reaches the group's recorded destination.

`scripts/verify-sdk-jump-origins.py` reopens the hash-pinned archive and checks
every original member, all source aliases, their complete five-byte sections
and typed destination symbol, every target extent/hash/JMP destination, and
exhaustive inventory coverage for each destination. The lock destinations
already have independent R008/R026 complete SDK origin records. For the three
codec destinations, the verifier checks each destination's **own** complete
19-, 160- or 73-byte source/target body, all relocation fields and local CFG
as corroboration for the source symbol binding. It also checks the complete
16-byte readonly codec vtable sections, all four typed pointer fields and
their linked target values. Those three callee bodies remain pending because
their external data/function dependencies have not yet been independently
resolved to the stricter SDK origin standard. Their origin is not inherited
from the forwarding functions.

`config/sdk-jump-groups.json` records the complete source alias sets and
callee/vtable evidence; `config/sdk-jump-origin-evidence.csv` records each
target extent and hash. Repeated codec aliases establish the D3DX8 library
origin but do not identify which original codec class corresponds to a given
target entry. Three public regressions reject a non-JMP, a truncated/extended
body and an incorrect typed source relocation. No authored source or exact
credit is added. Current totals are 1,495 reviewed: 164 authored, 767 library
and 564 compiler; 2,856 remain pending. Exact remains 42 functions / 8,916
bytes against the provisional 62,647-byte authored slice (14.23%).
Local CI passed 95 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
new whole-archive verifier and target-required status checks successfully;
private receipt: `.analysis/public-r039-origin-verification.json`.

## R040 — game-specific menu, replay, result and battle routines

Reviewed 2026-10-02. Twenty-three further complete target bodies / 36,859
bytes have directly observed game behavior. Each has one terminal RET, all
direct branches end on instruction boundaries within its recorded extent,
and its complete SHA-256 and branch counts are recorded in
`config/authored-origin-evidence.csv`. The roles below are inferred navigation
names, not claims about original C++ class ownership. Ghidra decompilations
used for semantic inspection are private diagnostics under `.analysis/r040-*`;
the whole-body and CFG checks use the hash-pinned executable.

| Entry | Target-observed behavior supporting authored origin |
| --- | --- |
| `0x004206D0` | Reads a file, optionally applies the game's evolving two-byte XOR stream, passes the buffer to a custom parser and can write the transformed copy. |
| `0x004259D0` | Wraps a music-room selection across the recorded track count, scrolls a ten-row window and selects track/title preview resources. |
| `0x00425C80` | Draws that track list, ten-row selection highlight, scrollbar, title and detail textures using project sprite primitives. |
| `0x00426670` | Builds a multiline track catalog from unlock state and track strings, then uploads the text to a scene-owned texture. |
| `0x004268A0` | Bounds-checks the selected track, formats its title and updates a dedicated text texture. |
| `0x00426A70` | Builds two selected-track text textures, including the fixed `No.%02d %s / %s` detail format. |
| `0x0042A340` | Updates an individual name-entry slot in character record storage, with 0x5b/0x5c keyboard commands and a nine-character cap. |
| `0x0042A560` | Draws an individual player's record/name grid, cursor and animated keyboard selection. |
| `0x0042AB90` | Polls two players' directional and confirm/cancel input, then wraps the custom 26-column/4-row name keyboard. |
| `0x0042B380` | Updates the shared name-entry buffer and its confirm/cancel state, including replay finalization on the confirm path. |
| `0x0042B570` | Draws that shared name-entry keyboard, record fields, cursor and time-driven highlight. |
| `0x0042BCD0` | Polls both controllers for the shared keyboard and applies its distinct column/row state policy. |
| `0x0042C670` | Pages replay selection by one or ten entries, navigates a subordinate slot and returns scene transitions on select/cancel. |
| `0x0042CA60` | Draws a ten-item replay list with per-entry metadata and a subordinate slot menu. |
| `0x0042D470` | Enumerates `replay\\*.rep`, opens each file and reads its header/slot metadata into the replay browser. |
| `0x0042EF10` | Draws result counters, an animated scale/alpha panel and a character-indexed result label. |
| `0x0042F530` | Extracts decimal digits from a value, selects glyph rectangles and draws a fixed or variable-width number. |
| `0x0042F970` | Navigates result pages with availability checks, builds a detail page on selection and returns game transition codes. |
| `0x00431070` | Formats a ten-row result-record page from selected progress data and uploads it as text. |
| `0x00431350` | Formats four selected progress counters and uploads the result panel text. |
| `0x004319B0` | Loads `data\\character\\%s\\cardlist.txt`, splits its newline-delimited records and stores copied strings. |
| `0x00435A70` | Renders paired character-specific sprite layers, animated panels and background state with the game's fixed coordinates. |
| `0x0043E040` | Renders the battle HUD from both players' health/state fields, gauges, character sprites and score indicators. |

The nearby vector-growth helpers, jump-table parser, and scene switch dispatchers
remain pending where complete ownership or extent is unresolved. Calling a
reviewed helper does not transfer its origin to the caller, or vice versa.
R040 adds no source, mapping or exact-match credit. Totals are 1,518 reviewed:
187 authored, 767 library and 564 compiler; 2,833 remain pending. Exact is
still 42 functions / 8,916 bytes against the provisional 99,506-byte authored
slice (8.96%). Finish all origin review before resuming exact reconstruction.
Local CI passed 95 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r040-origin-verification.json`.

## R041 — character selection, title and battle state

Reviewed 2026-10-02. Twenty-one complete target bodies / 18,004 bytes have
independent game-specific state, resource or file behavior. Each entire body
has a recorded SHA-256, one terminal RET and direct branches only to decoded
instruction starts within its own extent. `verify-authored-origins.py` checks
these properties against the pinned executable. Names and original class
boundaries remain inferred.

| Entry | Target-observed behavior supporting authored origin |
| --- | --- |
| `0x00431B60` | Reads `data\\character\\%s\\cardlist.dat`, decodes its evolving XOR stream and stores newline-delimited card records. |
| `0x00431D60` | Reads the corresponding `cardlist.txt`, applies the inverse evolving XOR stream and writes `cardlist.dat`. |
| `0x00431F60` | Dispatches game scene-transition flags through specific callbacks and 40-/10-frame countdowns. |
| `0x00432EA0` | Loads `select.dat`, `selectchar.dat` and `selectbg.dat`, resets selection state and copies unlock/progress flags. |
| `0x00433230` | Resets both character-selection slots, animation offsets, selected IDs and progress-selection fields. |
| `0x00433A40` | Processes each player's option toggle, five-step setting and cancel input with scene-specific globals. |
| `0x004348E0` | Advances a player's selection animation and interprets directional/confirm input for that choice state. |
| `0x00434CF0` | Advances the next selection state, handles confirm/cancel and sets both players' terminal selection flags. |
| `0x004350E0` | Drives choice animation, randomizes one pending choice and handles player-specific confirmation timing. |
| `0x00435870` | Advances the same selection offsets and resets a player's state on cancel input. |
| `0x00438240` | Draws paired player option panels, setting bars, cursors and character portraits. |
| `0x00438670` | Draws the single-player option panel with a setting bar, disabled region and cursor. |
| `0x0043A020` | Loads `data\\system\\title.dat`, records a millisecond baseline and initializes title-menu fade/selection fields. |
| `0x0043A7A0` | Draws the title background and ten menu rows with per-row fade and current-selection color. |
| `0x0043AD10` | Loads `data\\system\\battle.dat`, constructs battle effects, binds both player objects and sets battle mode/camera state. |
| `0x0043B1B0` | Advances both players and stage objects, handles frame timing, render callbacks, pause/fade and battle-state transitions. |
| `0x0043C930` | Resolves a zero-health player, transfers score/progress and selects round-end or next-round state. |
| `0x0043CDB0` | Detects single or double knockout, resets both players' combat fields and sets round-end countdowns. |
| `0x0043D010` | Updates per-player round-transition counters, opacity and position animation. |
| `0x0043D570` | Draws a side-specific combo counter, caps displayed count at 99 and animates its alpha/slide timing. |
| `0x0043D9D0` | Applies camera motion, renders battle layers/players and HUD, and updates the frame-rate display. |

R041 classifies only these bodies; the neighboring menu dispatchers, player
methods and data records retain separate pending or prior-reviewed origins.
No authored source, mapping or exact credit is added. Totals are 1,539
reviewed: 208 authored, 767 library and 564 compiler; 2,812 remain pending.
Exact remains 42 functions / 8,916 bytes against the provisional 117,510-byte
authored slice (7.59%). Origin review remains the prerequisite for exact work.
Local CI passed 95 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r041-origin-verification.json`.

## R042 — battle collision, overlays and visual effects

Reviewed 2026-10-02. Thirty-two complete target bodies / 37,531 bytes have
independent battle-specific behavior. `config/authored-origin-evidence.csv`
records each whole-body SHA-256, one terminal RET and all direct-branch
counts; `verify-authored-origins.py` reopens the pinned target, decodes each
entire extent and checks every direct branch stays inside it. The fifteen
`RenderPattern` names are deliberately neutral: the target shows distinct
fixed atlas/geometry/effect sequences, but their original visual-effect names
are unknown. No source or exact match is inferred.

| Entry | Target-observed behavior supporting authored origin |
| --- | --- |
| `0x004406C0` | Draws timed, randomized full-screen rectangles from live player state and a battle camera offset. |
| `0x00440B50` | Draws paired battle status effects from each player's state, resource atlas and fade fields. |
| `0x00441910` | Draws a mode-specific battle overlay, including character portraits and end-state choices. |
| `0x00442580` | Gathers active hitboxes for both players, invokes project collision decisions and emits impact effects. |
| `0x00442A70` | Transforms attack/defense rectangles and applies hit/guard responses after overlap tests. |
| `0x00442E40` | Compares transformed player body rectangles and changes both movement states on contact. |
| `0x00444020` | Applies attack damage, combo/hit state, sound and impact effects using move flags and player health. |
| `0x004443B0` | Applies the related reduced-damage response, updates combo fields and launches impact effects. |
| `0x00445830` | Updates both players' per-frame effect fields and resets them for selected battle states. |
| `0x004461D0` | Handles battle pause/continue choices, including continue-count and transition-code changes. |
| `0x00446590` | Builds several digit-glyph atlas rectangle arrays and stores the project's texture/spacing widths. |
| `0x00446B90` | Draws decimal digits from those atlas arrays with optional fixed width and per-style spacing. |
| `0x00446D80` | Advances a fixed-frame overlay schedule with position, fade and scale changes. |
| `0x00447340` | Renders that overlay from mirrored/scrolled atlas strips and timed alpha effects. |
| `0x004480D0` | Interprets a fixed set of debug keys to alter character/move/battle state. |
| `0x00448710` | Draws the battle pause-menu rows, highlighted selection and character portrait. |
| `0x00449310` | Separates overlapping player rectangles using their facing and velocity, updating both positions. |
| `0x00449EE0` | Composes randomized background, foreground and timed effect layers. |
| `0x0044B630` | Draws one atlas-based rotating/translated sprite pattern with random offsets. |
| `0x0044BB50` | Draws the related atlas pattern with its own geometry and orientation constants. |
| `0x0044C070` | Draws a third atlas pattern variant with different sprite placement. |
| `0x0044D620` | Builds and renders a parameterized quad burst from project sprite coordinates. |
| `0x0044DA90` | Uses a battle timer and trigonometric scaling to draw a layered effect variant. |
| `0x0044E3D0` | Composes a random backdrop with several project sprite/effect layers. |
| `0x0044E930` | Builds a multi-layer wave/burst from timer values, random offsets and sprite geometry. |
| `0x0044F850` | Draws another trigonometric effect pattern with a different atlas selection. |
| `0x0044FAF0` | Rotates and scales project sprite quads using a battle-timer value. |
| `0x0044FD40` | Composes timer-scaled sprite quads and render-state changes for one pulse pattern. |
| `0x00450420` | Draws a tinted battle backdrop and layered sprite pattern. |
| `0x00450C10` | Draws a related randomized layered pattern with a distinct atlas slot. |
| `0x00450EE0` | Draws timer-scaled tinted quads with its own geometry parameters. |
| `0x00451440` | Builds a multi-layer pulse from random offsets, timer-dependent colors and sprite geometry. |

Calling the game's renderer or the CRT random/trigonometric helper gives no
ownership credit to those callees. Nearby effect dispatchers and player
functions remain separately pending. R042 raises totals to 1,571 reviewed:
240 authored, 767 library and 564 compiler; 2,780 remain pending. Exact stays
42 functions / 8,916 bytes against the provisional 155,041-byte authored
slice (5.75%). Finish origin review before resuming exact reconstruction.
Local CI passed 95 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r042-origin-verification.json`.

## R043 — result pages, scene fades, character selection and staff roll

Reviewed 2026-10-02. Thirty-seven complete bodies / 21,846 bytes have
independent game-specific behavior. Each entire extent is hash-pinned, ends
in one RET, and has only in-extent direct branches to instruction starts;
`verify-authored-origins.py` checks all properties against the supplied
executable. The transition pattern names below distinguish callbacks without
claiming original C++ names. The inferred owner labels are navigational.

| Entry | Target-observed behavior supporting authored origin |
| --- | --- |
| `0x00430080` | Draws the result record page, including ten card/score rows, selected-character labels and progress values. |
| `0x00430D80` | Converts two controllers' directional and select/cancel state into result-menu fields. |
| `0x00430EE0` | Loads the selected character's numbered data pack and corresponding encoded card list. |
| `0x004315F0` | Draws a result counter as variable- or fixed-width decimal glyphs. |
| `0x00431770` | Draws exactly eight name glyphs from the project's 26-column character atlas. |
| `0x00431890` | Builds an eight-character rank/number label and delegates its glyph drawing. |
| `0x00431940` | Frees each owned card-list string and clears the list container. |
| `0x00432200` | Draws the whole-screen transition texture with a countdown-driven fading alpha. |
| `0x004322B0` | Draws the corresponding opposite alpha ramp. |
| `0x00432360` | Draws a countdown-driven color fade over a complete screen rectangle. |
| `0x00432410` | Draws the complementary countdown color fade. |
| `0x004324D0` | Draws rotating sprite quads as the transition count changes. |
| `0x00432660` | Draws the complementary rotating-quad transition. |
| `0x004327F0` | Slides/fades transition sprites according to the shared countdown. |
| `0x00432960` | Scales transition sprites from the shared countdown. |
| `0x00432AF0` | Moves a transition sprite using a trigonometric count curve. |
| `0x00432C40` | Draws a countdown-colored rotating transition sprite. |
| `0x00432D70` | Draws the paired rotating transition sprite with its own color curve. |
| `0x00433BE0` | Changes a player's character sub-selection and commits selected character/progress globals. |
| `0x00433CF0` | Advances a player's selection animation and input state across game-specific character choices. |
| `0x00437380` | Renders each player's selected character card and animated highlight layers. |
| `0x004388D0` | Copies controller state into the scene's two player-input records and processes selection controls. |
| `0x00438A80` | Looks up a selected card value in the game's nested progress-record layout. |
| `0x00438AC0` | Loads `data\\system\\staffroll.dat` and initializes a millisecond baseline. |
| `0x00438C20` | Advances staff-roll time, responds to skip input and returns a title/scene transition code. |
| `0x00438D00` | Renders fixed millisecond windows of staff-roll sprites, fades and particles. |
| `0x00439F90` | Polls the staff-roll skip key combination and window-mode shortcut. |
| `0x0043ABF0` | Polls two-player title-menu navigation, changing the selected row and its timers. |
| `0x0043B510` | Updates both battle players and decrements their per-frame counters. |
| `0x0043C8F0` | Chooses the battle round-end handler from the current mode and player state. |
| `0x0043D360` | Increments a mode-indexed counter in a game progress record. |
| `0x0043D3B0` | Writes a selected card's value into a character progress record. |
| `0x0043D3E0` | Increments the selected card's count in that record. |
| `0x0043D430` | Sets the selected card's seen/used flag. |
| `0x0043D460` | Reads that selected card's stored value. |
| `0x0043D490` | Initializes a battle combo-counter record with side, texture and off-screen position. |
| `0x0043D4D0` | Applies count/position/timer policy to the combo-counter record and starts its slide animation. |

Ambiguous tiny wrappers, empty methods, destructor bodies and three functions
with unresolved outgoing jumps stay pending. R043 adds origin evidence only;
no source, mapping or exact credit is added. Totals are 1,608 reviewed:
277 authored, 767 library and 564 compiler; 2,743 remain pending. Exact
stays 42 functions / 8,916 bytes against the provisional 176,887-byte
authored slice (5.04%). Finish origin review before resuming exact work.
Local CI passed 95 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r043-origin-verification.json`.

## R044 — complete guarded scene-state dispatchers

Three previously pending scene routines use a direct x86 jump table. Their
whole target bodies and all decoded instructions are hashed and checked by
`verify-authored-origins.py`. The new direct-switch verifier checks the exact
`cmp` / unsigned `ja` / selector `mov` / indexed `jmp` sequence, requires the
same stack slot in the bound and selector load, checks that no direct branch
enters the guard's interior, hashes every table byte, and requires every table
destination and the default destination to be an instruction start inside the
complete function extent. This resolves their outgoing indirect jumps without
guessing a callee or accepting only selected cases.

| Entry | Extent | Cases | Target-observed behavior supporting authored origin |
| --- | ---: | ---: | --- |
| `0x00433470` | 1,442 bytes | 9 | Advances the paired character-select state, dispatching player selection, animation, controller handling and scene transitions. |
| `0x0043A270` | 1,273 bytes | 10 | Dispatches title-menu selections to game-mode and transition policies, including the observed scene return codes. |
| `0x0043B610` | 4,764 bytes | 15 | Advances the battle scene through its mode/state cases, round progress, persistence and transition calls. |

The table locations, complete SHA-256 values and guard instruction addresses
are recorded in `config/authored-origin-direct-switches.csv`; the independent
whole-body hashes and local CFG counts are in
`config/authored-origin-evidence.csv`. The scene names remain inferred. R044
adds origin evidence only; no source, mapping or exact credit is added. Totals
are 1,611 reviewed: 280 authored, 767 library and 564 compiler; 2,740 remain
pending. Exact stays 42 functions / 8,916 bytes against the provisional
184,366-byte authored slice (4.84%). Finish origin review before exact work.
Local CI passed 98 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r044-origin-verification.json`.

## R045 — battle collision, fighter state and resource ownership

Twenty-seven complete game-specific bodies add 21,301 bytes of authored-origin
evidence. The pinned target supplies each complete body hash and the decoded
local CFG; every direct branch stays inside its extent and the final
instruction returns. The observations below come from the actual body and its
game data/call context, not from the provisional Ghidra label. Names describe
observed roles and remain provisional.

| Entry | Target-observed behavior supporting authored origin |
| --- | --- |
| `0x00441EA0` | Draws a battle banner with the scene's countdown-driven alpha and textured geometry. |
| `0x00442400` | Expands four collision bounds to include two project records. |
| `0x00443E90` | Applies an attack impact, including hit/guard state, damage feedback and game sound. |
| `0x00444770` | Tests an attack flag against the defender's guard state and applies the guarded result. |
| `0x00444FC0` | Resolves a special attack/defense flag pair and marks both fighter records. |
| `0x004450E0` | Resolves contact flags, records the defender response and dispatches an impact. |
| `0x004456F0` | Reads game input combinations and toggles battle pause state and sound. |
| `0x00451A00` | Draws a timed fighter sprite using the game's texture and transform API. |
| `0x00451EB0` | Chooses movement animation IDs from grounded state, movement direction and fighter flags. |
| `0x00452230` | Integrates horizontal/vertical fighter position with arena bounds. |
| `0x00452360` | Chooses an action animation from current input and attack state, including a random branch. |
| `0x00452490` | Decrements multiple paired fighter timers and updates battle-specific recovery state. |
| `0x00452C10` | Applies a calculated gauge change to the opposing fighter and its recovery timers. |
| `0x00452F10` | Converts controller/AI state to held directional and action values and per-frame commands. |
| `0x00453F70` | Renders the fighter's current pattern frames, flip, tint and stage transform. |
| `0x00454840` | Renders a side-dependent fighter effect using two animation counters and alpha. |
| `0x00454AA0` | Renders a fading side-dependent overlay based on a fighter timer. |
| `0x00455640` | Computes a paired fighter value from the opponent's state and mode. |
| `0x004567B0` | Initializes fighter-owned state, containers and resource references. |
| `0x00456910` | Releases fighter-owned pattern, stage, sound and other project resources. |
| `0x00456B60` | Loads `wave\\se%s.dat`, character pictures and character data, with a named character-specific pack path. |
| `0x00457010` | Clears round-local fighter fields and sets side-dependent spawn position and initial counters. |
| `0x00457660` | Loads `data\\character\\%s\\%s.pat`, then parses pattern records and associated resources. |
| `0x004584D0` | Loads a numbered `data\\character\\%s\\stage%d.dat` resource. |
| `0x0045BB10` | Initializes a battle-effect record with side, position, flags, collision rectangle and appearance fields. |
| `0x0045BDB0` | Advances project effect objects through virtual update calls and removes finished records. |
| `0x0045D810` | Selects a weighted fighter pattern sequence from game tables and copies the chosen entries. |

Template-like record copies and container assignment in the same address
region remain pending. R045 changes origin review only, with no source,
mapping or exact credit. Totals are 1,638 reviewed: 307 authored, 767 library
and 564 compiler; 2,713 remain pending. Exact stays 42 functions / 8,916
bytes against the provisional 205,667-byte authored slice (4.34%). Finish
origin review before exact work.
Local CI passed 98 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r045-origin-verification.json`. R044 GitHub
CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37017759236.

## R046 — Reimu-specific fighter control

Five complete neighboring bodies add 14,840 authored-origin bytes. The
initializer writes the literal character key `reimu` into the fighter record
and sets its individual parameters. The other four bodies use the same
derived object layout and project action system:

| Entry | Extent | Target-observed behavior supporting authored origin |
| --- | ---: | --- |
| `0x0046D000` | 126 bytes | Decrements a character gauge timer and activates a game action at zero. |
| `0x0046D080` | 218 bytes | Calls the fighter initializer, installs a Reimu-specific vtable, stores `reimu` and initializes per-character parameters. |
| `0x0046D160` | 120 bytes | Allocates a project-specific owned object through the character's factory path. |
| `0x0046D1E0` | 235 bytes | Clears Reimu-specific round fields before resetting the common fighter state. |
| `0x0046D300` | 14,141 bytes | Dispatches hundreds of Reimu action and pattern IDs using the project pattern lookup and action-transition routines. |

The large dispatcher has 749 decoded local branches; every direct branch
targets an instruction start within its complete body, which ends in RET.
Its whole target body, not a convenient prefix, is SHA-256 checked on cold
replay. Two adjacent forwarding/empty methods remain pending because their
ownership is not established by game behavior alone. R046 grants origin
evidence only. Totals are 1,643 reviewed: 312 authored, 767 library and 564
compiler; 2,708 pending. Exact stays 42 functions / 8,916 bytes against the
provisional 220,507-byte authored slice (4.04%).
Local CI passed 98 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r046-origin-verification.json`. R045 GitHub
CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37018599753.

## R047 — complete character action and AI routines

Thirty-one large, complete functions between `0x0047` and `0x005E` add
304,135 authored-origin bytes. They form two recurring families, confirmed
by decompilation of all 31 bodies and by their decoded direct calls. Every
whole body has its own pinned-target SHA-256, one final RET and only in-extent
direct branches. Each `CharacterAction` body combines vector access
(`0x004420B0`) with game-specific input capture (`0x00455B30`), action
transition (`0x0040FAC0`) and state clearing (`0x00453A10`). Each
`CharacterAI` body calls a math wrapper (`0x00412D90`) and fighter-state
predicate (`0x00454F90`) while branching on opponent position, game state and
character-specific action IDs. These call destinations and their behavior
were checked in the pinned target. The vector/math helpers do not inherit
authored ownership from these callers.

The ten action-dispatch entries are `0x00493470`, `0x004C0AD0`,
`0x004E2F20`, `0x00502450`, `0x0052D230`, `0x00551C00`, `0x00574370`,
`0x00597660`, `0x005C0D70` and `0x005E2310` (139,026 bytes). The 21 AI-choice
entries are `0x00472890`, `0x00474B40`, `0x00499030`, `0x0049B070`,
`0x004C6B50`, `0x004C8CD0`, `0x004E7DE0`, `0x004EA090`, `0x005086E0`,
`0x00532950`, `0x005349B0`, `0x00557380`, `0x00558F50`, `0x00579650`,
`0x0057B900`, `0x0059D240`, `0x0059F4F0`, `0x005C5D10`, `0x005C7FC0`,
`0x005E7370` and `0x005E9620` (165,109 bytes). Address-qualified labels in
the ledger distinguish these bodies without prematurely assigning character
names or original method names. Neighboring larger functions with unresolved
indirect jumps remain pending.

R047 changes origin review only; no source, mapping or exact credit is added.
Totals are 1,674 reviewed: 343 authored, 767 library and 564 compiler;
2,677 remain pending. Exact stays 42 functions / 8,916 bytes against the
provisional 524,642-byte authored slice (1.70%). Finish origin review before
exact reconstruction. These very large functions change the cost picture for
the later 50%-of-authored-bytes objective; that denominator is still
provisional until all origins are reviewed.
Local CI passed 98 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r047-origin-verification.json`. R046 GitHub
CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37019016587.

## R048 — complete character object, sequence and move dispatchers

Thirty-one large character-specific bodies add 1,155,910 authored-origin
bytes. Every body has a complete target SHA-256, one final RET and a decoded
local CFG. They contain 90 bounded indirect dispatches: 63 byte-remapped
tables and 27 directly indexed tables. The cold verifier checks each bound,
selector source, complete remap/table hash, default edge and every reachable
destination, and rejects direct branches into a guard's interior. Their
complete table metadata is recorded in the two authored-origin switch CSVs;
the whole-body hashes and branch counts are in
`config/authored-origin-evidence.csv`.

| Family | Entries | Bytes | Target-observed behavior |
| --- | ---: | ---: | --- |
| `CharacterObject` | 11 | 488,664 | Switches on an owned object's action IDs, updates position/state against its fighter and opponent, and repeatedly uses project object/effect routines. |
| `CharacterSequence` | 10 | 114,854 | Switches on a character sequence byte, advances explicit timers and coordinates, and calls the project's effect/animation routines. |
| `CharacterMove` | 10 | 552,392 | Switches on fighter move IDs, updates movement and combat state, and repeatedly calls game action/transition routines. |

The object entries are `0x00476A40`, `0x0049C8F0`, `0x004CA6E0`,
`0x004EBDA0`, `0x0050A580`, `0x00536400`, `0x0055AC80`, `0x0057D580`,
`0x005A1600`, `0x005C9CC0` and `0x005EB520`. The sequence entries are
`0x00483350`, `0x004A9050`, `0x004D4EA0`, `0x004F44D0`, `0x0051E640`,
`0x00540290`, `0x00561D40`, `0x005882B0`, `0x005AC250` and `0x005D4890`.
The move entries are `0x00486550`, `0x004AC040`, `0x004D7E70`,
`0x004F7130`, `0x005214B0`, `0x00543210`, `0x00564BE0`, `0x0058AF60`,
`0x005AEEC0` and `0x005D73C0`. The address-qualified names distinguish
complete bodies without guessing original character or method names.

R048 changes origin review only; no source, mapping or exact credit is added.
Totals are 1,705 reviewed: 374 authored, 767 library and 564 compiler;
2,646 remain pending. Exact stays 42 functions / 8,916 bytes against the
provisional 1,680,552-byte authored slice (0.53%). The large character
dispatchers materially change later exact-work prioritization, but the
denominator remains provisional until all origins are reviewed.
Local CI passed 98 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r048-origin-verification.json`. R047 GitHub
CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37019902898.

## R049 — medium character special and auxiliary routines

Forty-four complete character-specific bodies add 88,471 authored-origin
bytes. Twenty-two neighboring pairs implement a timed special action and its
renderer. Each update routine switches on ten bounded action cases through a
direct table; each renderer uses a ten-entry bounded byte remap and a complete
target table. All 22 tables, default destinations and in-body case targets
are cold-replayed from the pinned executable. The remaining 22 functions
have complete direct CFGs and one final RET each. Every body has its own
SHA-256 and branch count in `config/authored-origin-evidence.csv`.

| Group | Entries | Bytes | Target-observed behavior |
| --- | ---: | ---: | --- |
| `CharacterSpecial` | 22 | 59,248 | Eleven update/render pairs advance custom action timers and positions, then draw the paired animated sprite layers. |
| `CharacterAux` | 22 | 29,223 | Character-specific helpers spawn effects, select fighting-game command strings, update paired fighter fields, and render timed custom geometry. |

The decompiled complete bodies include explicit fighter offsets, action IDs,
project effect/render calls and command patterns such as `236236D`, `4136A`
and `6314B`. Address-qualified labels keep character identities and original
method names open. Tiny adjacent forwarders and generated-looking helpers
remain pending until their ownership is independently established. R049
changes origin review only, with no source, mapping or exact credit. Totals
are 1,749 reviewed: 418 authored, 767 library and 564 compiler; 2,602
remain pending. Exact stays 42 functions / 8,916 bytes against the
provisional 1,769,023-byte authored slice (0.50%).
Local CI passed 98 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r049-origin-verification.json`. R048 GitHub
CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37020738880.

## R050 — named character constructor and object chains

Fifty-two small, complete game bodies add 9,572 authored-origin bytes. Ten
fighter initializers call the common fighter initializer, install distinct
derived vtables and store literal character keys in the target. Reimu's
corresponding initializer was already reviewed in R046. These are direct
target observations; the inferred C++ method names and complete object
layouts remain open.

| Character key | Fighter initializer | Owned-object factory | Object initializer |
| --- | --- | --- | --- |
| `reimu` | `0x0046D080` (R046) | `0x0046D160` (R046) | `0x004769B0` |
| `marisa` | `0x00492FB0` | `0x004930B0` | `0x0049C850` |
| `sakuya` | `0x004C0820` | `0x004C0920` | `0x004CA640` |
| `alice` | `0x004E2C90` | `0x004E2D90` | `0x004EBD00` |
| `patchouli` | `0x005021C0` | `0x005022C0` | `0x0050A4E0` |
| `youmu` | `0x0052CEE0` | `0x0052D090` | `0x00536360` |
| `remilia` | `0x00551980` | `0x00551AA0` | `0x0055ABE0` |
| `yuyuko` | `0x00574100` | `0x00574210` | `0x0057D4E0` |
| `yukari` | `0x00597380` | `0x00597480` | `0x005A1560` |
| `suika` | `0x005C0AB0` | `0x005C0BB0` | `0x005C9C20` |
| `meiling` | `0x005E2090` | `0x005E2170` | `0x005EB490` |

Each of the ten newly reviewed factories allocates a project object and
directly calls its paired initializer; all eleven object initializers call
the shared object base at `0x0045B760` and install a character-associated
vtable. Ten round-reset bodies directly call the common fighter reset at
`0x00457010`. Eleven short special-variant selectors map a project mode
global to a character record byte through a complete ten-case guarded direct
jump table. All eleven tables and all 52 whole bodies are hashed and
cold-replayed with full local CFG checks. No small forwarding or generated
method gained ownership merely through adjacency.

R050 changes origin review only. Totals are 1,801 reviewed: 470 authored,
767 library and 564 compiler; 2,550 remain pending. Exact stays 42
functions / 8,916 bytes against the provisional 1,778,595-byte authored
slice (0.50%). Finish all origin review before exact work.
Local CI passed 98 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP ran the
authored-origin verifier and target-required status checks successfully;
private receipt: `.analysis/public-r050-origin-verification.json`. R049 GitHub
CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37021220821.

## R051 — whole relocation-free VC7 STL template aliases

Twenty-five more complete candidates / 1,004 bytes reproduce four
independently evidenced VC7 STL template bodies. The verifier cold-compiles
the unchanged `VC7InputContainers.cpp` probe under the pinned `/Od /Ob0 /Gy
/GR- /GX /Zi /GS` profile. For each base symbol it requires a single whole
code COMDAT with its own auxiliary extent, no relocations, the R004 source
fingerprint and an exact match to the original base target body. Every new
alias then has to match all bytes of that source body, its complete target
extent and decoded CFG. No callee or nearby address inherits ownership.

| VC7 source family | Independently verified base | New aliases | Bytes |
| --- | --- | ---: | ---: |
| vector iterator `operator+=` | `0x00405270` | 4 | 128 |
| allocator `max_size` | `0x00405B20` | 1 | 44 |
| `std::fill` | `0x00405D90` | 4 | 144 |
| `std::fill_n` | `0x00406260` | 16 | 688 |

The exact type aliases remain unresolved: a different template argument can
produce the same full relocation-free body. The library family is grounded
by the cold vendor source and complete code shape. Shorter generic matches
stay pending because a tiny byte-identical body does not independently prove
ownership. All 25 alias addresses and SHA-256 values are in
`config/vendor-identical-origin-evidence.csv`. R051 grants library origin
only; no source, authored or exact credit. Totals are 1,826 reviewed: 470
authored, 792 library and 564 compiler; 2,525 remain pending. Exact stays
42 functions / 8,916 bytes against the provisional 1,778,595-byte authored
slice (0.50%). Cold replay:
`scripts/repo-python scripts/verify-vendor-identical-origins.py`.
Local CI passed 98 regressions; target-required tracking, progress freshness
and `git diff --check` passed. The unchanged no-auth public Funnel MCP cold
compiled and verified the aliases successfully; private receipt:
`.analysis/public-r051-origin-verification.json`. R050 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37021584341.

## R052 — early game globals, archives, text and scene setup

Twenty-three complete game functions / 12,010 bytes have direct target
evidence and fully decoded local control flow. The archive pair at
`0x0041D260` and `0x0041D510` writes and reads a custom index of 108-byte
entries. The index writer XORs bytes from offset two with an evolving
two-byte sequence, then appends each source file's contents. The reader
reverses the sequence before inserting the names and offsets. These roles
describe target behavior; the full archive format and callers remain open.

The text renderer at `0x0041C2E0` handles two- and four-byte pixels,
multibyte glyphs, line wrapping, and the inline `\\c`, `\\e`, `\\n`
commands. `0x00413460` prepares a texture and invokes that renderer.
`0x004192F0` and `0x00419450` read and write the same ordered `config.ini`
fields. `0x00419920` copies live battle selection into a snapshot, and
`0x004195B0` restores it. The large default initializer at `0x00416640`
sets repeated progress-record fields; its full owner layout is open.

Other reviewed bodies initialize game globals and sound (`0x00417210`,
`0x00417430`, `0x004175A0`), choose BGM paths (`0x00419CB0`), initialize
music/replay/result scenes (`0x00425750`, `0x0042A180`, `0x0042C3D0`,
`0x0042E640`, `0x0042F710`), and render numeric or filename fields in
those scenes. Three replay numeric renderers are byte-identical but are
independent complete functions; their specific call-site roles remain
provisional. Each new body has a full target SHA-256 and verified CFG in
`config/authored-origin-evidence.csv`. No adjacent STL helper or callee
inherits ownership.

R052 is origin-only. Totals are 1,849 reviewed: 493 authored, 792 library
and 564 compiler; 2,502 remain pending. Exact stays 42 functions / 8,916
bytes against the provisional 1,790,605-byte authored slice (0.50%).
Finish all origin review before exact work.
Local CI passed 98 tests, target-required tracking and progress freshness
passed, and the unchanged no-auth public Funnel MCP reran the authored
verifier and tracking checks. Private receipt:
`.analysis/public-r052-origin-verification.json`. R051 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37022186738.

## R053 — score persistence, glyphs, archives and scene callbacks

Twenty-two more complete authored bodies / 5,215 bytes have full target
hashes and decoded local CFG in `config/authored-origin-evidence.csv`.
`0x00416B10` reads both observed `score.dat` layouts, selecting by file
size; `0x004169E0` writes the newer layout and occasionally changes a
256-byte trailing field using `rand`. `0x00416EE0` inserts a score into a
ten-entry ranking, shifting records and stamping the current date. These
functions share offsets with the R052 progress initializer but do not yet
establish a complete owner layout.

`0x0041C1B0` uses `GetGlyphOutlineA` to allocate a glyph bitmap and record
its metrics. The archive catalog functions at `0x0041CE50`, `0x0041CF80`
and `0x0041D080` manage named archive handles; `0x0041D750` and
`0x0041D800` search an archive entry and seek to its stored offset, the
latter also returning the recorded size. The decompiled iterator condition
has not yet been resolved to a natural C++ expression, so these roles are
descriptive rather than exact-source claims.

The remaining functions initialize/draw/update the battle-end, loading,
logo, replay and result-list scenes, with direct `.dat` asset names and
input-global evidence. `0x00417000` fills a game surface black.
`0x0042C270` displays a replay filename using its target prefix check.
Two similar replay input pollers write at different object offsets. The
large neighboring STL vector bodies and unresolved switch/tail bodies
remain pending; none inherits authorship from these call relationships.

R053 is origin-only. Totals are 1,871 reviewed: 515 authored, 792 library
and 564 compiler; 2,480 remain pending. Exact remains 42 functions / 8,916
bytes against the provisional 1,795,820-byte authored slice (0.50%).
Local CI passed 98 tests, target-required tracking and progress freshness
passed, and the unchanged no-auth public Funnel MCP reran all authored
origin extents and tracking checks. Private receipt:
`.analysis/public-r053-origin-verification.json`. R052 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37022645391.

## R054 — scene cleanup and battle rendering helpers

Ten complete authored functions / 2,980 bytes have full target SHA-256
evidence and decoded local CFG. `0x00433140` and `0x0043B0B0` release
different scene-owned resource fields and call the common scene teardown.
Their exact class ownership remains unresolved, so their names are
address-qualified.

Six complete draw-layer bodies at `0x00449B50`, `0x0044A2E0`, `0x0044AC60`,
`0x0044AF00`, `0x0044CC20`, and `0x0044CEC0` choose positions and draw a
fixed set of custom sprites with `FUN_0040CA80`. Some whole bodies are
byte-identical; they are independently bounded target functions, not
evidence for nearby functions. `0x00455B30` packs signs and action flags
from a battle input record into one byte, then passes it to a project
helper. `0x004574D0` copies round result fields into a player-state record.
The object layout and original names are not established.

R054 adds origin only. Totals are 1,881 reviewed: 525 authored, 792 library
and 564 compiler; 2,470 remain pending. Exact stays 42 functions / 8,916
bytes against the provisional 1,798,800-byte authored slice (0.50%).
Local CI passed 98 tests, target-required tracking and progress freshness
passed, and the unchanged no-auth public Funnel MCP reran all authored
extent and tracking checks. Private receipt:
`.analysis/public-r054-origin-verification.json`. R053 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37022960028.

## R055 — background asset constructors and paired sprite drawers

Fifty-two complete authored bodies / 8,527 bytes belong to a repeated
background-stage family. Thirty-four constructors call the same project
background base and asset loader, each with a complete observed literal
`data\\background\\BG*.dat` path. The filenames cover BG00 through BG09;
the exact address/path pairs are in `config/background-origin-evidence.csv`.
Eighteen companion routines call the project sprite renderer twice for
the left and right side images, with the same game geometry. Some draw
bodies are byte-identical, but each has a separate complete target extent.

`scripts/repo-python scripts/verify-background-origins.py` rechecks the
whole-body authored hashes and CFG, direct base/asset or sprite calls, and
the PE-resident literal path reached by each constructor. A deliberately
changed asset-path witness was rejected. The vtable addresses and selected
background-file names support origin and inferred roles; they do not prove
complete class layouts or original C++ names. Adjacent no-op virtual
methods and tiny destructor wrappers remain pending.

R055 adds origin only. Totals are 1,933 reviewed: 577 authored, 792 library
and 564 compiler; 2,418 remain pending. Exact remains 42 functions / 8,916
bytes against the provisional 1,807,327-byte authored slice (0.49%).

## R056 — repeated background transform/copy routines

Thirty-two further complete authored bodies / 2,912 bytes each call the
same two project transform helpers (`0x004115C0` and `0x004116F0`) and copy
the same fixed 0x21-word record before writing a sentinel. Every body is
91 bytes, has a complete single-RET CFG, and matches the entire first
body after masking only the two decoded call displacement fields. The
call targets themselves are checked at every address. This is
target-observed family evidence, not a claim of exact source or owner layout.

`scripts/repo-python scripts/verify-background-transform-origins.py`
replays the 32-body cohort and its complete non-call-byte comparison. R056
adds origin only. Totals are 1,965 reviewed: 609 authored, 792 library and
564 compiler; 2,386 remain pending. Exact stays 42 functions / 8,916 bytes
against the provisional 1,810,239-byte authored slice (0.49%). Continue
all origin review before exact reconstruction.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP replayed
both background verifiers, all 562 authored-origin extents and tracking.
Private receipt: `.analysis/public-r055-r056-origin-verification.json`.
R054 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37023216064.

## R057 — explicit background destructor source shape

Thirty-four complete 28-byte background destructors / 952 bytes are
classified authored. The independent synthetic VC7.1 fixture in
`probes/VC7BackgroundDestructor.cpp` defines both an explicit empty
derived virtual destructor and an implicit derived destructor. A cold
`/Od /Ob0 /Gy /GR- /GX- /Zi /GS` build gives the explicit destructor one
complete 28-byte code COMDAT with a typed vtable DIR32 field at `+12` and
a typed base-destructor REL32 call at `+20`. The implicit destructor has a
distinct complete 19-byte COMDAT with only the base-destructor call. This
distinction supports the source-defined origin of the target shape without
claiming the fixture's class names, layouts or exact source as TH075's.

`scripts/repo-python scripts/verify-background-destructor-origins.py`
cold-compiles the fixture, checks both whole source COMDAT boundaries and
typed relocations, and compares every nonrelocated target byte. Each
target body has one complete RET and direct call. Its vtable field must
equal the unique vtable written by one of the 34 independently verified
R055 asset constructors; its call must reach the common base destructor at
`0x00449D40`. Per-body hashes, source hash and bindings are in
`config/background-destructor-origin-evidence.csv`. The base destructor
and adjacent empty virtual methods keep independent pending origins.
Two other same-shaped wrappers bind to larger BG05b and BG08a constructors;
their paired constructors remain pending for separate review.

R057 adds origin only, with no reconstruction source or exact credit.
Totals are 1,999 reviewed: 643 authored, 792 library and 564 compiler;
2,352 remain pending. Exact remains 42 functions / 8,916 bytes against
the provisional 1,811,191-byte authored slice (0.49%).
Local CI passed 98 tests; target-required tracking and progress freshness
passed. The unchanged no-auth public Funnel MCP cold-compiled the probe,
verified the 34 destructors and all 596 authored-origin extents, and
rechecked tracking. Private receipt:
`.analysis/public-r057-origin-verification.json`. R055/R056 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37024184101.

## R058 — background vtable no-op methods

Eighty-six complete 11-byte bodies / 946 bytes are classified authored.
The independent synthetic source in `probes/VC7BackgroundNoOp.cpp`
defines an empty virtual member. A pinned VC7.1 cold build under
`/Od /Ob0 /Gy /GR- /GX- /Zi /GS` emits it as the sole, relocation-free
11-byte code COMDAT. All 86 target bodies match every source byte and
their own complete one-RET CFG. The byte match alone would be weak origin
evidence because the body is short and identical across functions.

`scripts/repo-python scripts/verify-background-noop-origins.py` also
requires each target address to occur exactly once in slot 1, 2 or 3 of a
target vtable whose pointer is written by an independently verified R055
background asset constructor. The exact vtable, constructor, slot, full
body hash and cold source hash for every method are in
`config/background-noop-origin-evidence.csv`. This ties each tiny method
to a project-owned background class without inferring an original method
name or complete class layout. Three other same-byte no-op candidates are
referenced by the larger BG05b/BG08a classes and remain pending until those
constructors are reviewed.

R058 adds origin only, with no reconstruction source or exact credit.
Totals are 2,085 reviewed: 729 authored, 792 library and 564 compiler;
2,266 remain pending. Exact stays 42 functions / 8,916 bytes against
the provisional 1,812,137-byte authored slice (0.49%). Continue origin
review before exact reconstruction.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP cold
verified the no-op source, the background destructor probe, all 682 authored
origin extents and tracking. Private receipt:
`.analysis/public-r058-origin-verification.json`. R057 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37024823847.

## R059 — complete larger background constructor families

Seven complete authored bodies / 441 bytes close the same reviewed
background pattern for BG05b and BG08a. The constructors at `0x0044E810`
and `0x00450B20` load the literal `BG05b.dat` and `BG08a.dat` paths and
write distinct derived vtables. Their paired 28-byte destructors at
`0x0044F2E0` and `0x00451110` match the cold VC7 explicit-destructor
COMDAT outside the typed vtable and base-call fields. Three 11-byte no-op
methods (`0x0044F230`, `0x0044F240`, `0x00450ED0`) match the cold empty
virtual-method COMDAT and occur in unique slots 2 or 3 of those same
vtables. The two constructors have extra initialization fields, so their
whole extents were checked separately rather than assumed from the smaller
R055 constructors.

The R055/R057/R058 verifiers now replay all 36 constructors, 36 paired
destructors and 89 no-op virtual members with per-row R059 evidence IDs;
the 18 side-pair drawers remain in the same background ledger. R059 adds
origin only. Totals are 2,092 reviewed: 736 authored, 792 library and 564
compiler; 2,259 remain pending. Exact remains 42 functions / 8,916 bytes
against the provisional 1,812,578-byte authored slice (0.49%).
Local CI passed 98 tests; target-required tracking and progress freshness
passed. The unchanged no-auth public Funnel MCP cold-replayed all expanded
background verifiers, all 689 authored extents and tracking. Private
receipt: `.analysis/public-r059-origin-verification.json`. R058 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37025220392.

## R060 — fighter vtable action forwards and no-op overrides

Thirty-two complete authored methods / 440 bytes belong to the eleven
previously verified playable-character fighter vtables. Each R046/R050
fighter constructor writes one distinct derived vtable. Slot 8 of every
vtable points to a 19-byte method that directly calls the separately
reviewed base action method at `0x00451EB0`; slot 18 points to an 11-byte
no-op method. Slot 9 points to another 11-byte no-op in ten vtables, while
Marisa's slot 9 method was already reviewed in R049. Exact slots,
constructor addresses, full body hashes and call targets are recorded in
`config/fighter-virtual-origin-evidence.csv`.

A cold pinned VC7.1 build of `probes/VC7FighterVirtuals.cpp` emits each
source method as a sole complete code COMDAT. The forward method has one
typed REL32 call relocation at offset 11; the no-op has none.
`scripts/repo-python scripts/verify-fighter-virtual-origins.py` checks
source sections and relocations, constructor hashes and control flow,
vtable slots, full target bodies and the direct-call destination. The
probe establishes code shape, not original class layouts or method names.

R060 adds origin evidence only: 2,124 reviewed, comprising 768 authored,
792 library and 564 compiler; 2,227 remain pending. The exact baseline
remains 42 functions / 8,916 bytes against 1,813,018 provisional authored
bytes (0.49%). Continue origin review before exact reconstruction.
Local CI passed 98 tests; target-required tracking and `git diff --check`
passed. The unchanged no-auth public Funnel MCP cold-compiled the fighter
probe, verified all 721 authored-origin extents and rechecked tracking.
Private receipt: `.analysis/public-r060-origin-verification.json`.

## R061 — generated character-derived destructors

Ten complete 19-byte methods / 190 bytes are classified compiler-generated.
They match every non-relocation byte of the implicit destructor emitted by
a cold pinned VC7.1 build of `probes/VC7BackgroundDestructor.cpp`. That
probe declares a derived class without a destructor definition; the
compiler emits a sole complete code COMDAT with one typed REL32 call to
the base destructor. The target bodies each call the separately reviewed
`FighterState::ReleaseResources` at `0x00456910`.

The R037 whole-body scalar-deleting-destructor verifier independently
checks all ten deleting wrappers and their calls to these methods.
`scripts/repo-python scripts/verify-character-implicit-destructor-origins.py`
rechecks the cold source section, target body hashes and complete CFG,
wrapper hashes and calls, and the shared authored base destination.
Individual bindings are in
`config/character-implicit-destructor-origins.csv`. This source probe
establishes generated code shape and call ownership, not original class
names or layouts.

R061 adds no authored source or exact credit. Totals are 2,134 reviewed:
768 authored, 792 library and 574 compiler; 2,217 remain pending. Exact
stays 42 functions / 8,916 bytes against 1,813,018 provisional authored
bytes (0.49%). Finish origin review before exact reconstruction.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP cold
verified the implicit destructor source, all R037 scalar deleting wrappers
and tracking. Private receipt:
`.analysis/public-r061-origin-verification.json`.

## R062 — scene lifetime and presentation hooks

Four complete authored bodies / 316 bytes close specific gaps in the
scene-code region. `0x00431F40` writes the scene base vtable and releases
the separately reviewed game-global owner. `0x00438BA0` and `0x0043A1E0`
write the respective Staff Roll and Title vtables, delete an owned member
through the independently reviewed R037 scalar-deleting wrapper, and call
that common scene cleanup. The Title destructor also copies the object's
selected byte into game state at `0x00671630`. `0x0043B5D0` directly calls
the accepted exact graphics-present routine. Original class and method
names remain inferred.

`scripts/repo-python scripts/verify-scene-lifetime-origins.py` checks each
whole body hash and CFG, exact direct-call set, and vtable writes. It
independently checks the complete R043 Staff Roll and R041 Title constructor
bodies and their matching vtables. The title-state write must still be
present. The adjacent CRT absolute-value wrapper, empty Staff Roll callback
and other ambiguous small methods remain pending.

R062 adds origin only: 2,138 reviewed (772 authored, 792 library, 574
compiler), 2,213 pending. Exact remains 42 functions / 8,916 bytes against
1,813,334 provisional authored bytes (0.49%). Continue origin review.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP verified
the scene bindings, all 725 authored-origin extents and tracking. Private
receipt: `.analysis/public-r062-origin-verification.json`. R061 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37026646605.

## R063 — complete Reimu action-state dispatcher

One complete 60,999-byte function at `0x0045DD70` is classified authored.
It is the largest reviewed game body so far and is reached through slot 1
of the vtable written by the independently reviewed R046 Reimu fighter
constructor. The code reads the fighter's action state, dispatches hundreds
of action IDs, updates movement and attack fields, and calls game action
helpers. The inferred role `ReimuFighter::AdvanceActionStatesAt0045DD70`
does not claim an original method name or complete object layout.

The target extent from `0x0045DD70` through its sole RET at `0x0046CBB6`
decodes completely: 16,837 instructions and 1,690 branches. Two directly
indexed jump tables and four byte-remapped tables follow that RET. The
six guards bound every selector; all 142 table entries resolve to
instruction starts inside the complete function. Full table and remap
hashes, guard addresses, default destinations and sizes are in
`config/authored-origin-direct-switches.csv` and
`config/authored-origin-switches.csv`. The tables are data, not additional
code in the function extent. `scripts/repo-python
scripts/verify-reimu-action-origin.py` rechecks the whole body hash and
CFG, all six complete guarded tables, the R046 constructor body and
vtable slot 1. `verify-authored-origins.py` rechecks the same extent in
the shared authored-origin ledger.

The same verifier cross-binds slot 1 of all eleven previously reviewed
fighter constructors to eleven complete authored action bodies: this new
Reimu body and ten R048 bodies. Together they contain 613,391 bytes,
32.7% of the current provisional authored-byte denominator. This is a
measured core-function cohort for planning exact work after origin review,
not exact-match credit.

R063 adds origin evidence only. Totals are 2,139 reviewed (773 authored,
792 library, 574 compiler), 2,212 pending. Exact stays 42 functions /
8,916 bytes against 1,874,333 provisional authored bytes (0.48%). This
large confirmed body is important for post-review exact-work planning;
finish the remaining origin review first.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP verified
the complete Reimu dispatcher, all eleven fighter action slots, all 726
authored-origin extents and tracking. Private receipt:
`.analysis/public-r063-origin-verification.json`. R062 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37027429693.

## R064 — Meiling and auxiliary action-state bodies

Three complete authored bodies / 43,868 bytes are reviewed in the
character-adjacent code region. A 116-byte constructor at `0x005FAB10`
writes a distinct auxiliary-object vtable. Its slot 1 points to the
31,352-byte action-state routine at `0x005FAE30`, which has 630 internal
branches and a bounded byte-remapped switch with 70 complete table
entries. Separately, slot 16 of the R050 Meiling fighter vtable points to
the 12,400-byte routine at `0x005F3D60`, with 350 internal branches and
a directly indexed 98-entry switch. Both routines mutate character
action/effect fields and call game-specific helpers. The auxiliary object's
exact identity and original method names remain unknown.

`scripts/repo-python scripts/verify-character-aux-action-origins.py`
rechecks the three whole body hashes and CFGs, both guarded table extents
and every case destination, constructor vtable writes, and the independently
reviewed R050 Meiling constructor. The tables follow their functions'
sole final RETs; they are recorded as data, not included in the code
extents. R064 adds origin only, with no source or exact credit.

Totals are 2,142 reviewed (776 authored, 792 library, 574 compiler),
2,209 pending. Exact stays 42 functions / 8,916 bytes against 1,918,201
provisional authored bytes (0.46%). Continue origin review first.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP verified
both switch bodies, all 729 authored-origin extents and tracking. Private
receipt: `.analysis/public-r064-origin-verification.json`. R063 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37028175815.

## R065 — battle loading, rendering and state dispatchers

Eight complete game-authored bodies / 19,028 bytes are reviewed. Two
battle-loading functions contain the literal `LoadCharacter...` and
`LoadStage...` diagnostic strings, call the previously reviewed game log
routine, and select owned character or stage resources from game state.
The remaining six draw a scene, advance scene and battle state, or process
fighter action data. Names describe observed behavior; class boundaries
and original method names remain provisional.

All eight extents decode to a single final RET. Their ten guarded switches
have 75 complete 32-bit table entries: nine direct tables and one
byte-remapped table. `scripts/repo-python
scripts/verify-game-dispatcher-origins.py` rechecks full body hashes,
every internal branch and table destination, all table/remap hashes,
the two literal strings and their reviewed logging calls. The switch
records are in `config/authored-origin-direct-switches.csv` and
`config/authored-origin-switches.csv`. The nearby `0x00420880` body has
complex exception machinery and remains pending; it is not included by
proximity.

R065 adds origin only, with no source or exact credit. Totals are 2,150
reviewed (784 authored, 792 library, 574 compiler), 2,201 pending.
Exact stays 42 functions / 8,916 bytes against 1,937,229 provisional
authored bytes (0.46%). Continue origin review before exact work.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP verified
all eight dispatchers, all 737 authored-origin extents and tracking. Private
receipt: `.analysis/public-r065-origin-verification.json`. R064 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37028835995.

## R066 — options, music room and progress decisions

Four complete authored bodies / 3,101 bytes cover options-state changes,
music-room catalog loading and a progress-selection decision. The catalog
loader reads the literal `musicroom.dat` through the project's archive
helper, decodes its byte stream and parses records. The options update
changes game globals and calls the independently reviewed sound routine.
The progress decision repeatedly queries a game flag helper. Method
names and owner boundaries remain inferred.

Five directly indexed, guarded switches contain 28 complete table entries.
`scripts/repo-python scripts/verify-medium-game-origins.py` rechecks
every full body hash and CFG, each table/guard/destination, the music-room
literal and archive call, and the options sound call. Nine adjacent
520/511-byte vector-template bodies have recognizable STL behavior but
remain pending until a complete cold vendor-source match and typed
bindings establish their origin; repetition alone grants no exclusion.

R066 adds origin only: 2,154 reviewed (788 authored, 792 library, 574
compiler), 2,197 pending. Exact stays 42 functions / 8,916 bytes against
1,940,330 provisional authored bytes (0.46%). Continue origin review.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP verified
the four bodies, all 741 authored-origin extents and tracking. Private
receipt: `.analysis/public-r066-origin-verification.json`. R065 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37029350867.

## R067 — effect catalog and fighter special-state origins

Six complete authored bodies / 5,219 bytes are reviewed. The effect-pattern
loader references `data\system\effect\effect.pat` and calls the already
reviewed archive opener. Two related methods allocate and initialize the
reviewed auxiliary game object. Suika and Yukari special-state update bodies
are bound to slot 19 of their independently reviewed fighter vtables; they
read character state, update timers and emit game effects. A projectile
update body applies action and position rules. Names describe observed
behavior; original method names and full layouts remain provisional.

`scripts/repo-python scripts/verify-effect-fighter-origins.py` rechecks
each full body hash, final RET, every internal branch, the catalog/archive
binding, auxiliary constructor calls and both vtable slots. No source or
exact credit is added. The repeated 520/511-byte container routines still
await cold vendor-source and typed-binding evidence.

Totals are 2,160 reviewed (794 authored, 792 library, 574 compiler),
2,191 pending. Exact stays 42 functions / 8,916 bytes against 1,945,549
provisional authored bytes (0.46%). R066 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37029800827.
Local CI passed 98 tests; target-required tracking, full authored extent
verification, progress freshness and `git diff --check` passed. The
unchanged no-auth public Funnel MCP passed its 15-check HTTPS smoke test,
including Ghidra and cold exact-unit replay. Its private receipt remains
under `.analysis/deployment/`.

## R068 — final two reviewed playable-fighter vtable entries

The shared 149-byte slot-0 method binds fighter animation data; all eleven
previously reviewed playable-character vtables point to it. Alice's
256-byte slot-19 update changes character timer/state using opponent
position. Both full bodies decode to a final RET with every branch internal.
`scripts/repo-python scripts/verify-fighter-final-virtual-origins.py`
rechecks hashes, complete CFG and all eleven slot-0 pointers plus Alice's
slot 19. This closes origin decisions for the 23-entry range inspected in
each of those eleven vtables; it does not establish complete class layouts
or original names.

R068 adds origin only: 2,162 reviewed (796 authored, 792 library, 574
compiler), 2,189 pending. Exact remains 42 functions / 8,916 bytes
against 1,945,954 provisional authored bytes (0.46%). R067 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37030747665.

## R069 — combat hit-response dispatchers

Two complete game-authored bodies / 2,129 bytes choose and apply a fighter's
hit response. The selector reads fighter and opponent state, game options
and random or scripted input. Its caller applies damage, changes state and
triggers sound/effect helpers. Their direct call edge is visible in the
target. Names describe observed behavior; original method boundaries and
full fighter layout remain provisional.

The caller's guarded byte remap covers all 31 input values and its nine-entry
table. The selector's guarded direct table has four entries. Both tables
follow the final RETs, and every reachable destination lands at an
instruction boundary inside its full owning body.
`scripts/repo-python scripts/verify-combat-reaction-origins.py` rechecks
the full body/CFG hashes, both complete table records and the caller edge.

R069 adds origin only: 2,164 reviewed (798 authored, 792 library, 574
compiler), 2,187 pending. Exact remains 42 functions / 8,916 bytes against
1,948,083 provisional authored bytes (0.46%). R068 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37031049890.

## R070 — fighter script archive loading and parsing

Two complete authored bodies / 2,518 bytes handle a fighter `.sce` resource.
The previously reviewed `FighterState::LoadResources` builds the literal
`data\\character\\%s\\%s.sce` and calls both file and archive loaders. The
archive loader opens through the reviewed game archive routine, decodes the
same byte stream as the reviewed file loader, and calls the shared parser.
The parser compares script tokens and dispatches record construction through
a guarded 100-byte remap and a complete seven-entry jump table. Ghidra could
not recover that table, so the decision uses the full target body and raw
instruction/table checks. Its original class and method names remain
inferred.

`scripts/repo-python scripts/verify-fighter-script-origins.py` rechecks
both full body hashes, all internal branch destinations and final RETs,
the complete remap/table hashes, the reviewed `.sce` filename/caller edge,
and the archive/file loader edges into the parser. No source or exact credit
is added. Totals are 2,166 reviewed (800 authored, 792 library, 574
compiler), 2,185 pending. Exact remains 42 functions / 8,916 bytes against
1,950,601 provisional authored bytes (0.46%). R069 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37031358595.

## R071 — VC7 deque map-growth template origins

Twelve complete 520/517/511-byte bodies, totaling 6,210 bytes, are verified
as VC7 `std::deque::_Growmap` library templates. Seven independent
`std::deque<DequeProbeRecord<N>>` instantiations at widths 1, 2, 4, 8, 16,
32 and 64 compile with the pinned VC7.1 toolchain. Each emitted `_Growmap`
definition occupies its entire code COMDAT and has 13 typed relocations.
For each target body, all non-relocation bytes match one template family;
every relocation is bound to its observed target destination, and the full
decoded control flow has internal branches and a complete exit. The 511-byte
variant has three matching probe aliases; this proves a common template
shape, not the original game element type.

`scripts/repo-python scripts/verify-vendor-deque-growmap-origins.py` cold
compiles the source and rechecks all complete code bodies, hashes, aliases,
relocation types/addends/destinations, control flow and ledgers. The evidence
is in `config/vendor-deque-growmap-origins.csv`. No original record type,
callee origin, reconstruction source or exact credit is claimed. The earlier
vector-template hypothesis for these bodies is superseded. A scan of the
remaining pending candidates found no more whole-body matches to the seven
probe variants.

R071 adds 12 library origins: 2,178 reviewed (800 authored, 804 library,
574 compiler), 2,173 pending. Exact stays 42 functions / 8,916 bytes
against 1,950,601 provisional authored bytes (0.46%). R070 GitHub CI passed
at https://github.com/N0zoM1z0/th075/actions/runs/37093204780.

## R072 — VC7 deque push, pop and cleanup origins

Forty-six complete 151–226-byte bodies, totaling 8,220 bytes, match the
independently compiled VC7 deque probe. The methods are `_Tidy`, `pop_back`,
`pop_front`, `push_back` and `push_front`. Their 143 typed relocations are
individually bound to target destinations, and every whole body has complete
decoded control flow. The source has 35 unique whole-COMDAT operation
definitions across seven synthetic record widths. Multiple `_Tidy` aliases
share one emitted shape; no original game record type is inferred.

`scripts/repo-python scripts/verify-vendor-deque-operation-origins.py` cold
compiles the probe, checks each whole COMDAT, compares every non-relocation
byte, verifies each relocation binding and rechecks complete control flow.
Evidence is in `config/vendor-deque-operation-origins.csv`. These are
library-template origins only; called-function origins, reconstruction
source and exact credit are independent. Shorter generic STL-like matches
remain pending until stronger ownership evidence is established.

R072 adds 46 library origins: 2,224 reviewed (800 authored, 850 library,
574 compiler), 2,127 pending. Exact remains 42 functions / 8,916 bytes
against 1,950,601 provisional authored bytes (0.46%). R071 GitHub CI passed
at https://github.com/N0zoM1z0/th075/actions/runs/37093616372.

## R073 — VC7 deque construction and helper origins

Ninety-seven complete 49–72-byte bodies, totaling 5,340 bytes, match six
independently compiled VC7 deque constructor/helper template families:
`deque` and `_Deque_val` construction, `_Uninitialized_copy`,
`_Uninitialized_fill_n`, `_Destroy_range` and `_Uninit_copy`. Their 190
typed relocations bind to observed target destinations. Each whole source
COMDAT and target body has complete decoded control flow. The synthetic
record-width aliases all resolve to one method family for each accepted
target. Original game element types and called-function origins remain
unclaimed.

`scripts/repo-python scripts/verify-vendor-deque-helper-origins.py` cold
compiles the independent source and rechecks the complete source extent,
all non-relocation bytes, hashes, aliases, typed bindings, target control
flow and ledgers. Evidence is in `config/vendor-deque-helper-origins.csv`.
The 44-byte allocator `max_size` match has no relocation witness and remains
pending. Shorter generic matches remain pending as well. This batch adds
no reconstruction source or exact credit.

R073 adds 97 library origins: 2,321 reviewed (800 authored, 947 library,
574 compiler), 2,030 pending. Exact remains 42 functions / 8,916 bytes
against 1,950,601 provisional authored bytes (0.46%). R072 GitHub CI passed
at https://github.com/N0zoM1z0/th075/actions/runs/37093860727.

## R074 — parent-backed VC7 deque callee origins

One hundred twenty-six complete 20–29-byte bodies, totaling 3,246 bytes,
match seven independently compiled VC7 deque/allocator helper families:
`allocate`, `construct`, `destroy`, `max_size`, `deallocate`,
`_Uninit_fill_n` and `_Deque_map` construction. Each target has a full
source COMDAT match, one typed relocation bound to its actual destination,
complete decoded control flow, and at least one direct call from an already
reviewed VC7 deque template. That parent call's typed source symbol names
the same method family and its raw target displacement reaches the reviewed
callee. The parent templates are cold-reverified before this batch is
accepted. This extra call witness matters because 20-byte bodies can match
unrelated implementations by coincidence.

`scripts/repo-python scripts/verify-vendor-deque-callee-origins.py` replays
all three parent batches, cold compiles the seven-width probe and verifies
the complete source/target bodies, aliases, 126 typed bindings, parent call
fields and ledgers. Evidence is in `config/vendor-deque-callee-origins.csv`.
Other short matches, including a previously observed destructor body whose
call lands in authored code, remain pending. No game element type, called
function origin, reconstruction source or exact credit is inferred.

R074 adds 126 library origins: 2,447 reviewed (800 authored, 1,073
library, 574 compiler), 1,904 pending. Exact remains 42 functions /
8,916 bytes against 1,950,601 provisional authored bytes (0.46%). R073
GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37094093913.

## R075 — parent-backed VC7 STL allocations

Twenty-two complete 17–20-byte `std::_Allocate` bodies, totaling 436 bytes,
match the pinned VC7 source probe. Each has one typed relocation and a
complete decoded exit. Each is called by a reviewed R074 allocator wrapper
whose typed symbol names the same `_Allocate` family. The raw parent call
field reaches the candidate entry, and the parent chain is cold-reverified
before this batch is accepted. The original allocated type and the origin
of the ultimate `operator new` callee remain independent questions.

`scripts/repo-python scripts/verify-vendor-deque-allocation-origins.py`
replays the parent chain, cold compiles the independent source and checks
all complete source/target bytes, aliases, typed bindings, call fields and
ledgers. Evidence is in `config/vendor-deque-allocation-origins.csv`.
Six same-shape `_Allocate` candidates without a reviewed parent remain
pending, as do the other ambiguous short helpers. No reconstruction source
or exact credit is added.

R075 adds 22 library origins: 2,469 reviewed (800 authored, 1,095 library,
574 compiler), 1,882 pending. Exact remains 42 functions / 8,916 bytes
against 1,950,601 provisional authored bytes (0.46%). R074 GitHub CI passed
at https://github.com/N0zoM1z0/th075/actions/runs/37094428035.

## R076 — fighter script initialization and field access

Four complete game-authored bodies, totaling 292 bytes, sit beside the
previously reviewed fighter script loaders and parser. The 130-byte
initializer calls a VC7 deque constructor and destructor on the owner
pointer at offset `0x7D0`, then writes `0xFFFF` into all 1,000 16-bit slots
before returning the owner pointer. The purpose of that helper sequence is
not yet resolved.
Three 53–55-byte accessors use a 16-bit slot selection and the same two
lookup calls, then return a byte at record offset 0, a word at offset 2,
or a dword at offset 4. Their common object offset and field widths are
target observations, not a complete class layout. The original method
names remain inferred.

The independently reviewed fighter initializer at `0x004567B0` calls the
script initializer. Its reviewed action and pattern-selection methods at
`0x0045CE10` and `0x0045D810` each call all three accessors. The ownership
decision combines these game-specific uses with complete body hashes and
decoded control flow. `scripts/repo-python
scripts/verify-fighter-script-accessor-origins.py` rechecks the 1,000-slot
sentinel loop, each field width, the two shared lookup calls and all fighter
caller edges. The adjacent 84-byte cleanup body at `0x004204D0` remains
pending because a composite destructor can be compiler generated.

R076 adds four authored origins: 2,473 reviewed (804 authored, 1,095
library, 574 compiler), 1,878 pending. Exact remains 42 functions /
8,916 bytes against 1,950,893 provisional authored bytes (0.46%). R075
GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37094665913.

## R077 — deque destructors bound to verified `_Tidy`

Twenty-four complete 19-byte bodies, totaling 456 bytes, match independently
compiled VC7 `std::deque` destructor definitions. Each has one typed call
relocation naming `_Tidy`, and its target is one of the 13 complete VC7
deque `_Tidy` bodies independently reviewed in R072. The R072 verifier
cold-replays those callees before this batch is accepted. This callee
identity is essential: other 19-byte lookalikes call vector helpers,
unknown functions, or authored game routines and remain pending.

`scripts/repo-python scripts/verify-vendor-deque-destructor-origins.py`
cold compiles the source and checks the complete bodies, source aliases,
typed call bindings, verified `_Tidy` body hashes, target control flow and
ledgers. Evidence is in `config/vendor-deque-destructor-origins.csv`.
The script helper at `0x004216D0`, called in R076's initializer, and the
helper at `0x00421530`, called in the adjacent cleanup body, are in this
cohort. This refines the R076 observation: the initializer calls both a
deque constructor and a deque destructor at offset `0x7D0`; why it does
so is still unknown. The composite cleanup body at `0x004204D0` remains
pending.

R077 adds 24 library origins: 2,497 reviewed (804 authored, 1,119
library, 574 compiler), 1,854 pending. Exact remains 42 functions /
8,916 bytes against 1,950,893 provisional authored bytes (0.46%). R076
GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37095046444.

## R078 — VC7 deque bounds-checked access and iterators

An independent VC7 source probe calls `std::deque<DequeAccessRecord<N>>::at`
for seven synthetic record widths. Thirty-three complete pending target
bodies, totaling 2,267 bytes, match three emitted STL families: seven
68-byte `at` methods with four typed relocations each; sixteen 57-byte
iterator additions with one typed relocation each; and ten 83–89-byte
const-iterator dereferences with no relocations. Each definition occupies
its own complete code COMDAT. The full target control flow and every typed
relocation destination are checked. Width aliases show code-shape
equivalence, not original game element types.

The two `at` methods at `0x00421360` and `0x00421570` are called by the
fighter script field accessors reviewed in R076. This supplies an
independent STL explanation for their bounds check and iterator sequence;
the custom 1,000-slot mapping remains authored. Other short access-related
template matches await additional evidence.

`scripts/repo-python scripts/verify-vendor-deque-access-origins.py`
cold compiles the probe and rechecks complete source/target bodies, aliases,
44 typed relocations, decoded control flow and ledgers. Evidence is in
`config/vendor-deque-access-origins.csv`. No reconstruction source or exact
credit is added. R078 adds 33 library origins: 2,530 reviewed (804 authored,
1,152 library, 574 compiler), 1,821 pending. Exact remains 42 functions /
8,916 bytes against 1,950,893 provisional authored bytes (0.46%). R077
GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37095398320.

## R079 — parent-backed VC7 deque `begin`

Seven complete 35-byte `std::deque::begin` bodies, totaling 245 bytes,
match the independent VC7 access probe. Each has one typed call to an
iterator constructor and a complete decoded exit. Each is also called by
one of the seven reviewed R078 `deque::at` methods through a typed
same-family `begin` relocation. The raw call field reaches the pending
helper, and the parent `at` verifier is cold-replayed before acceptance.
Six other same-shape `begin` candidates have no such reviewed parent and
remain pending.

`scripts/repo-python scripts/verify-vendor-deque-begin-origins.py`
cold compiles the probe, checks the complete source and target bodies,
typed bindings, parent calls and ledgers. Evidence is in
`config/vendor-deque-begin-origins.csv`. No original element type,
reconstruction source or exact credit is claimed. R079 adds seven library
origins: 2,537 reviewed (804 authored, 1,159 library, 574 compiler),
1,814 pending. Exact remains 42 functions / 8,916 bytes against
1,950,893 provisional authored bytes (0.46%). R078 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37095752902.

## R080 — parent-backed VC7 deque iterator construction

Seven complete 32-byte deque iterator constructors, totaling 224 bytes,
match the independent VC7 access probe. Each has one typed call to a
const-iterator constructor and a same-family direct call from one of the
seven reviewed R079 `deque::begin` bodies. The raw parent call fields and
complete source/target bodies replay. Five other same-shape iterator
constructors lack this reviewed parent witness and remain pending.
Ghidra's imported `_Vector_iterator` label on these seven candidates is
not accepted as origin evidence; the VC7 deque source and parent calls
establish the family.

`scripts/repo-python scripts/verify-vendor-deque-iterator-origins.py`
cold-replays the R079 parents, recompiles the source and checks complete
body hashes, template aliases, typed bindings, parent calls and CFG.
Evidence is in `config/vendor-deque-iterator-origins.csv`. R080 adds seven
library origins: 2,544 reviewed (804 authored, 1,166 library, 574 compiler),
1,807 pending. No source or exact credit is added.

## R081 — parent-backed VC7 deque const-iterator construction

Seven complete 33-byte const-iterator constructors, totaling 231 bytes,
match the VC7 access probe without source relocations. Each has a
same-family typed call from a reviewed R080 iterator constructor. The R080
parent chain is cold-replayed; its raw call field, full target body hash
and source symbol must reach the const-iterator candidate. A complete
no-relocation source match plus that caller witness establishes library
origin without guessing the original element type.

`scripts/repo-python scripts/verify-vendor-deque-const-iterator-origins.py`
checks the complete chain, source/target bodies, aliases, parent calls and
CFG. Evidence is in `config/vendor-deque-const-iterator-origins.csv`.
R081 adds seven library origins: 2,551 reviewed (804 authored, 1,173
library, 574 compiler), 1,800 pending. Exact remains 42 functions /
8,916 bytes against 1,950,893 provisional authored bytes (0.46%). R079
GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37095934946.

## R082 — VC7 iterator dereferences bound to verified callees

Ten complete 19-byte deque iterator dereferences, totaling 190 bytes,
match independently compiled VC7 source. Each has one typed call to a
const-iterator dereference body already verified in R078. Its target body
hash and library origin, the complete 19-byte caller, and the relocation
destination are rechecked after cold-replaying the R078 callee batch.
The bound callee is decisive: identical short instruction shells also
appear with calls to vector helpers, unknown functions and authored game
methods. Those lookalikes remain pending.

`scripts/repo-python scripts/verify-vendor-deque-dereference-origins.py`
cold compiles the source and verifies all complete bodies, source aliases,
typed calls, callee hashes, CFG and ledgers. Evidence is in
`config/vendor-deque-dereference-origins.csv`. R082 adds ten library
origins: 2,561 reviewed (804 authored, 1,183 library, 574 compiler),
1,790 pending. Exact remains 42 functions / 8,916 bytes against
1,950,893 provisional authored bytes (0.46%). R081 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37096270119.

## R083 — parent-backed VC7 iterator advance

Nine complete 31-byte deque iterator `operator+=` bodies, totaling 279
bytes, match the independent VC7 access probe without source relocations.
Each has a same-family typed direct call from a reviewed R078 iterator
addition body. The R078 parent is cold-reverified; its raw call field,
source symbol and target body hash bind the otherwise short no-relocation
helper to the VC7 template family. Seven 27-byte advance-like callees
do not match this probe profile and remain pending.

`scripts/repo-python scripts/verify-vendor-deque-iterator-advance-origins.py`
rechecks complete source and target bodies, aliases, parent calls, CFG and
ledgers. Evidence is in `config/vendor-deque-iterator-advance-origins.csv`.
R083 adds nine library origins: 2,570 reviewed (804 authored, 1,192
library, 574 compiler), 1,781 pending. Exact remains 42 functions /
8,916 bytes against 1,950,893 provisional authored bytes (0.46%). R082
GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37096537793.

## R084 — VC7 deque iterator comparisons and `end`

An independent seven-width VC7 deque iterator probe reproduces 30 complete
target bodies, totaling 1,576 bytes: seven 66-byte const-iterator
subtractions, nine 60-byte const-iterator equality checks, seven 41-byte
iterator subtractions and seven 41-byte `deque::end` methods. The first two
families have no source relocations and match every target byte. Each
iterator subtraction has a typed call to one of the seven newly verified
const-iterator subtraction bodies. Each accepted `end` method has a typed
call to an iterator constructor independently reviewed in R080. Five
similar `end` bodies whose callee does not have that verified identity
remain pending.

`scripts/repo-python scripts/verify-vendor-deque-comparison-origins.py`
cold-replays the iterator-constructor chain, cold compiles the new source,
and checks complete source/target COMDATs, aliases, all 14 typed call
bindings, callee hashes, control flow and ledgers. Evidence is in
`config/vendor-deque-comparison-origins.csv`. The original game element
types remain unknown. R084 adds 30 library origins: 2,600 reviewed
(804 authored, 1,222 library, 574 compiler), 1,751 pending. Exact remains
42 functions / 8,916 bytes against 1,950,893 provisional authored bytes
(0.46%). R083 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37096707076.

## R085 — VC7 deque copy/fill loops and corroborated helpers

An independent VC7 probe instantiates deque algorithms for seven synthetic
record widths and six scalar/pointer types. Sixteen complete target loop
bodies reproduce eight `_Copy_opt`, seven `_Copy_backward_opt` and one
`fill` template. These include the formerly pending 85-byte `0x00420050`
helper beside the fighter script code. Original game element types and the
ownership of other external callees remain unclaimed.

Fifteen complete 70-byte wrappers share the same non-relocation bytes for
`copy` and `copy_backward`. Each is distinguished by its typed call to a
complete loop body verified in this batch; the exact source callee symbol
must appear among that body's matching source definitions. Their other
typed call binds a complete 11-byte `_Ptr_cat` body. Those eight short
pointer-category helpers, eight 29-byte iterator increments and seven
29-byte iterator decrements have complete source matches plus exact
source-typed calls from the reviewed wrappers or loops. Three other
increment/decrement lookalikes without this witness remain pending.

`scripts/repo-python scripts/verify-vendor-deque-algorithm-origins.py`
cold-compiles the probe and checks all 54 full COMDAT bodies, 2,889 bytes,
108 typed relocations, all source aliases, parent/callee witnesses, decoded
control flow and origin ledgers. Evidence is in
`config/vendor-deque-algorithm-origins.csv`. This grants library origin
only, with no reconstruction source or exact credit. R085 reaches 2,654
reviewed candidates (804 authored, 1,276 library, 574 compiler), with
1,697 pending. Exact remains 42 functions / 8,916 bytes against
1,950,893 provisional authored bytes (0.46%). R084 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37097140126.

## R086 — parent-backed VC7 deque emptiness checks

Thirteen complete 25-byte `deque::empty` bodies, totaling 325 bytes, match
all bytes of seven independently compiled record-width variants without
source relocations. Each has an exact source-typed direct call from a
reviewed R072 deque operation. The caller's complete source and target body,
its typed relocation, raw call displacement and hash are cold-reverified.
That witness distinguishes the short field test from possible unrelated
owners with an identical body. Original game element types remain unknown.

`scripts/repo-python scripts/verify-vendor-deque-empty-origins.py`
replays R072 first, then cold compiles the source and checks all complete
child bodies, aliases, parent calls, control flow and ledgers. Evidence is
in `config/vendor-deque-empty-origins.csv`. R086 adds thirteen library
origins: 2,667 reviewed (804 authored, 1,289 library, 574 compiler), with
1,684 pending. Exact remains 42 functions / 8,916 bytes against
1,950,893 provisional authored bytes (0.46%). R085 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37098124930.

## R087 — short VC7 template helpers with verified callers

Sixty-four complete source/target bodies have exact source-typed calls from
reviewed R073 template parents: 32 allocator constructors (thirteen 14-byte
and nineteen 16-byte bodies), sixteen 11-byte `_Ptr_cat` helpers, and
sixteen 5-byte trivial `_Destroy_range` specializations. All 742 bytes
match without source relocations. The short code alone is insufficient;
the independently reviewed parent's complete body and exact source callee
symbol supply the library-template witness. Nontrivial destruction bodies
that do not match this probe remain pending.

`scripts/repo-python scripts/verify-vendor-deque-leaf-origins.py`
cold-replays R073, cold compiles the probe, and checks all complete child
COMDATs, source aliases, hashes, typed parent calls, raw call displacements,
control flow and ledgers. Evidence is in
`config/vendor-deque-leaf-origins.csv`. Original game types remain unknown,
with no authored source or exact credit. R087 reaches 2,731 reviewed
candidates (804 authored, 1,353 library, 574 compiler), with 1,620 pending.
Exact remains 42 functions / 8,916 bytes against 1,950,893 provisional
authored bytes (0.46%). R086 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37098464756.

## R088 — converting allocators and trivial destruction with R074 callers

Thirty-eight short bodies have complete VC7 source matches and exact
source-typed calls from reviewed R074 allocator/helper parents: sixteen
16-byte converting allocator constructors and twenty-two 5-byte `_Destroy`
specializations. Their existing record/record-pointer source definitions
match all 366 bytes without relocations. The parent witness distinguishes
these library templates from unrelated short methods with identical code.
Other nontrivial destruction bodies remain pending; original game types
are not inferred from the probe.

`scripts/repo-python scripts/verify-vendor-deque-cleanup-origins.py`
cold-replays R074 and its parent chain, then cold compiles the existing
record probe. It checks whole child COMDATs, aliases, hashes, typed parent
calls, raw displacements, full control flow and ledgers. Evidence is in
`config/vendor-deque-cleanup-origins.csv`. R088 reaches 2,769 reviewed
candidates (804 authored, 1,391 library, 574 compiler), with 1,582 pending.
Exact remains 42 functions / 8,916 bytes against 1,950,893 provisional
authored bytes (0.46%), with no new source or exact credit. R087 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37098893616.

## R089 — complete VC7 vector storage bodies

An independent vector operation probe covers ten synthetic record widths
and six scalar/pointer variants. Ten complete 126-byte `_Buy` bodies and
eight complete `_Tidy` bodies (six 103-byte and two 110-byte bodies)
reproduce all 2,098 target bytes apart from 46 declared typed relocations.
Every relocation's source symbol, type, addend and observed target are
recorded and every other byte matches. The complete target control flow
also checks. Original element types and callee ownership remain unclaimed.

`scripts/repo-python scripts/verify-vendor-vector-storage-origins.py`
cold-compiles the probe and verifies full COMDAT extents, source aliases,
hashes, all typed bindings, CFG and origin ledgers. Evidence is in
`config/vendor-vector-storage-origins.csv`. Short constructors and allocator
callees require independent comparisons before gaining their own origin
credit. Vector insertion remains pending because its complete bodies do
not match this probe; no shortened comparison is accepted.

R089 reaches 2,787 reviewed candidates (804 authored, 1,409 library,
574 compiler), with 1,564 pending. Exact remains 42 functions / 8,916 bytes
against 1,950,893 provisional authored bytes (0.46%), with no new source
or exact credit. R088 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37099620503.

## R090 — vector constructors and helpers with storage witnesses

Seventy-two complete source/target bodies, totaling 1,728 bytes, have typed
witness chains to the R089 storage functions: ten 42-byte vector default
constructors, ten 28-byte `_Vector_val` constructors, ten 14-byte default
allocator constructors, ten 16-byte copy allocator constructors, eight
19-byte maximum-size wrappers, eight 27-byte allocation wrappers, eight
25-byte deallocation wrappers and eight 20-byte `_Allocate` helpers.
The ten vector constructors have exact source-typed `_Buy` calls; every
other body has an exact source-typed call from a reviewed parent. All short
chains must reach an independently verified storage body; a circular or
unanchored chain cannot supply origin credit. Source variants remain
consistent along the recorded calls without claiming original game types.

`scripts/repo-python scripts/verify-vendor-vector-helper-origins.py`
cold-replays R089, cold compiles the same probe, and checks full COMDATs,
aliases, hashes, all 72 typed relocations, witness chains, CFG and ledgers.
Evidence is in `config/vendor-vector-helper-origins.csv`. Public graph tests
also reject mismatched source callee symbols and removed storage anchors;
these metadata tests do not replace the private complete cold comparison.
Some Ghidra `_String_val` base-constructor labels are misleading; the typed
vector calls establish the expected `_Vector_val` family for this batch.

R090 reaches 2,859 reviewed candidates (804 authored, 1,481 library,
574 compiler), with 1,492 pending. Exact remains 42 functions / 8,916 bytes
against 1,950,893 provisional authored bytes (0.46%), with no new source
or exact credit. R089 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37101591701.

## R091 — complete construction, backward copy and vector wrappers

Eleven complete `std::_Construct` bodies (ten 58-byte and one 60-byte),
four 51-byte `_Copy_backward_opt` bodies, one 99-byte vector `push_back`
and one 114-byte single-element `insert` wrapper reproduce 1,057 bytes
with 26 typed relocations. The construction helpers call the complete
8-byte placement-new body; the backward-copy helpers call the reviewed
829-byte CRT `memmove`. Both anchors are independently reverified. The
vector wrappers match complete source bodies including every typed call
and the full control flow; their callees do not gain ownership credit
without a separate complete comparison. In particular, the 795-byte
`_Insert_n` at `0x004594B0` remains pending.

`scripts/repo-python scripts/verify-vendor-vector-operation-origins.py`
cold-replays the CRT anchor and cold compiles the vector operation probe,
then checks full COMDAT extents, source aliases, hashes, typed bindings,
control flow and origin ledgers. Evidence is in
`config/vendor-vector-operation-origins.csv`. Source variants establish
library emission without identifying original game element types. The
same verifier passed through the no-auth public Funnel MCP.

R091 reaches 2,876 reviewed candidates (804 authored, 1,498 library,
574 compiler), with 1,475 pending. Exact remains 42 functions / 8,916 bytes
against 1,950,893 provisional authored bytes (0.46%), with no new source
or exact credit. R090 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37103676294.

## R092 — vector iterators and copy wrappers with complete call witnesses

Eight complete vector/iterator bodies reproduce `begin`, `end`, iterator
construction, iterator subtraction/addition, const-iterator construction
and subtraction, and iterator advance. All source variants remain
consistent along their exact typed calls from the R091 vector wrappers.
Short identical bodies gain identity from this rooted call chain, not
from their byte shape alone. Eight more complete 51-byte `copy` and
`copy_backward` wrappers bind to independently reviewed copy
implementations. The verifier cold-replays both R091 and the earlier
record-helper evidence, then compares each wrapper's exact callee source
variant against the entire reviewed target callee. A different synthetic
record name cannot bypass that full comparison.

`scripts/repo-python scripts/verify-vendor-vector-callee-origins.py`
cold-compiles the vector probe and checks all sixteen complete bodies,
660 bytes and 21 typed relocations, full COMDAT extents, hashes, source
aliases, complete CFG, typed ownership witnesses and ledgers. Evidence is
in `config/vendor-vector-callee-origins.csv`. Public metadata tests reject
exchanged `begin`/`end` source identities, altered complete callee hashes
and missing copy anchors; these tests do not replace cold byte comparison.
The complete cold verifier also passed through the no-auth public Funnel MCP.
Original game element types remain unknown. The 795-byte `_Insert_n`
callee still differs from the whole source body and remains pending.

R092 reaches 2,892 reviewed candidates (804 authored, 1,514 library,
574 compiler), with 1,459 pending. Exact remains 42 functions / 8,916 bytes
against 1,950,893 provisional authored bytes (0.46%), with no new source
or exact credit. R091 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37105091974.

## R093 — closed CRT mantissa-conversion calls

The complete 344-byte `__ld12cvt` at `0x0064F5B3` matches the pinned
`libcmt.lib` `intrncvt.obj` function auxiliary extent. All nine direct
REL32 calls bind to separately complete vendor bodies: the previously
reviewed `__RoundMan` and `__ShrMan`, and the complete 27-byte `__CopyMan`
at `0x0064F4F8` and 25-byte `__IsZeroMan` at `0x0064F51F`. Both small
helpers match every byte without relocations and have exact source-typed
calls from the conversion body. Imported names and short fingerprints
alone would not establish their ownership. The corresponding single-
threaded archive emits the same conversion body; the pinned multithreaded
archive provides reproducibility, not proof of the original link input.

`scripts/repo-python scripts/verify-runtime-origins.py` now re-extracts
57 complete vendor bodies, 5,641 bytes and 28 typed direct calls, after
rechecking the three whole local CRT anchors. It verifies archive hashes,
member identity, full function extents, every linked byte, full decoding
and all calls/branches. The existing runtime evidence and relocation CSVs
record R093, with no new verifier or source body required.
The complete runtime verification also passed through the no-auth public Funnel MCP.

R093 adds three library origins / 396 bytes / nine typed calls and reaches
2,895 reviewed candidates (804 authored, 1,517 library, 574 compiler),
with 1,456 pending. Exact remains 42 functions / 8,916 bytes against
1,950,893 provisional authored bytes (0.46%); no source or exact credit.
R092 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37105417836.

## R094 — scalar copy wrappers with complete source-family aliases

Four complete 51-byte scalar `std::copy` wrappers at `0x0040A840`,
`0x0040F310`, `0x0045A880` and `0x005FA250` match the vector probe,
including their eight typed relocations and complete control flow.
Each calls a complete 49-byte scalar `_Copy_opt` source body, which binds
its one REL32 field to the independently reverified CRT `memmove`.
These four target callees had already gained library origin in R073 from
complete `_Uninit_copy` source matches. Both full source families emit
the same target bodies and typed `memmove` binding. Their original
specialization and whether linker folding occurred remain unknown;
R094 preserves their library origins and records the alternative source
evidence without inventing additional target functions.

`scripts/repo-python scripts/verify-vendor-vector-copy-origins.py`
cold-replays the R073 callee evidence and CRT anchor, cold-compiles the
vector probe and checks full wrapper/callee COMDAT extents, hashes,
source aliases, all linked bytes, complete CFG and origin ledgers.
Evidence is in `config/vendor-vector-copy-origins.csv`. Public witness
tests reject different complete callee hashes and mismatched source-typed
calls. Original game element types remain unclaimed.
The complete cold verifier also passed through the no-auth public Funnel MCP.

R094 adds four library origins / 204 bytes / eight wrapper relocations
and reaches 2,899 reviewed candidates (804 authored, 1,521 library,
574 compiler), with 1,452 pending. Exact remains 42 functions / 8,916 bytes
against 1,950,893 provisional authored bytes (0.46%); no source or exact
credit. R093 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37105951162.

## R095 — vector/allocator wrappers with independent complete callees

Four complete 29-byte vector `assign` wrappers bind to independently
reviewed complete 96-byte `_Assign_n` bodies. Four complete 45-byte
iterator additions bind to independently reviewed 32-byte iterator
advance bodies. Three complete 29-byte allocator `construct` wrappers
bind to independently reviewed 58-byte `_Construct` implementations.
All eleven wrapper bodies reproduce 383 bytes and eleven typed calls.
Every wrapper's exact source callee variant also reproduces the entire
reviewed target callee, preserving consistent source types without
claiming the game's original element types. Existing no-relocation alias
records for iterator advances retain their own independently cold-checked
base COMDAT evidence.

`scripts/repo-python scripts/verify-vendor-vector-wrapper-origins.py`
cold-replays R034 additional-record, R051 identical-body and R091
construction evidence, then cold-compiles the vector probe and checks
full wrapper/callee COMDATs, source aliases, hashes, typed call bindings,
complete control flow and origin ledgers. Evidence is in
`config/vendor-vector-wrapper-origins.csv`. Public witness tests reject
wrong callee source families and removed iterator anchors. Exception
constructor/destructor lookalikes with unresolved vtable/data fields
remain pending.
The complete cold verifier also passed through the no-auth public Funnel MCP.

R095 reaches 2,910 reviewed candidates (804 authored, 1,532 library,
574 compiler), with 1,441 pending. Exact remains 42 functions / 8,916 bytes
against 1,950,893 provisional authored bytes (0.46%), with no new source
or exact credit. R094 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37106349760.

## R096 — named exception metadata and complete vtable/base witnesses

The message constructor at `0x00409930` (37 bytes) and destructor at
`0x00409960` (28 bytes) are reviewed as standard-library functions. The
37-byte implicit copy constructor at `0x00409E30` is compiler generated.
Complete compiler type metadata identifies the class as `std::out_of_range`:
ThrowInfo `0x00667D60` binds the destructor and CatchableTypeArray; the
first complete CatchableType binds the copy constructor and complete
TypeDescriptor with the name `.?AVout_of_range@std@@`. The target's
`length_error` sibling emits the same short method shape, so the original
shape-only name hypothesis was insufficient. The independent exception
probe supplies the correct class and implicit-copy source definitions.

`scripts/repo-python scripts/verify-vendor-exception-origins.py`
cold-replays the existing scalar deleting-destructor anchors, then cold
compiles seven natural standard exception instantiations. It checks ten
complete function COMDATs (508 bytes), every typed relocation, full CFG,
two complete eight-byte readonly vtables, their actual COFF weak `_E` to
`_G` fallback records, and four complete type-data COMDATs (91 bytes).
Source/target hashes, all linked bytes, PE section permissions, source
header hashes and origin ledgers replay. The manifest is
`config/vendor-exception-groups.json`. The deleting helpers keep their
existing compiler origins; context methods gain no new credit. Public
graph tests reject a same-shaped scene cleanup callee, a scene-update
vtable slot, a different sibling exception type name, and a library label
for the implicit copy constructor.
The complete cold verifier also passed through the no-auth public Funnel MCP.

R096 adds three origins / 102 bytes (two library, one compiler) and reaches
2,913 reviewed candidates (804 authored, 1,534 library, 575 compiler),
with 1,438 pending. Exact remains 42 functions / 8,916 bytes against
1,950,893 provisional authored bytes (0.46%); no source or exact credit.
R095 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37106781323.

## R097 — game scene destructor distinguished from the exception lookalike

The complete 28-byte `0x00424F40` writes the readonly vtable also written
by the independently reviewed `BattleEndScene::Initialize` at
`0x00424E00`, then calls the reviewed game scene cleanup at `0x00431F40`.
Two observed vtable slots point to the already-reviewed deleting wrapper
at `0x00425190` and battle-end scene update at `0x00424F60`; the deleting
wrapper's typed call targets this destructor. These are selected slot
witnesses, not a claim about the complete vtable or object layout. The
initializer's full 308-byte body updates game actor/state/history fields;
its owner provenance is independent of any standard exception byte shape.
Attested Ghidra queries also confirmed the two vtable references and the
single direct deleting-wrapper caller.

`scripts/repo-python scripts/verify-battle-end-destructor-origin.py`
checks all target bytes and CFG, complete constructor/update witnesses,
readonly virtual-slot fingerprints and direct cleanup/deleting calls. It
replays the existing scene-lifetime and deleting verifiers, then cold
compiles the existing natural explicit/implicit destructor probe. The
entire explicit 28-byte COMDAT matches with its typed vtable/base-call
fields; the implicit variant is a distinct 19-byte COMDAT. The inferred
role is `BattleEndScene::DestroyAt00424F40`. No incomplete game class is
instantiated and no reconstruction source or exact credit is added.

The complete verifier also passed through the no-auth public Funnel MCP.

R097 adds one authored origin / 28 bytes and reaches 2,914 reviewed
candidates (805 authored, 1,534 library, 575 compiler), with 1,437 pending.
There are 758 explicitly recorded authored bodies, totaling 1,938,578
bytes. Exact remains 42 functions / 8,916 bytes against 1,950,921
provisional authored bytes (0.46%). R096 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37108585900.

## R098 — CRT bodies with complete scalar and import bindings

Five complete functions match the pinned `libcmt.lib` archive members,
including all 727 bytes and every typed relocation:

| Address | Bytes | Vendor symbol | Independently checked dependencies |
| --- | ---: | --- | --- |
| `0x00641AFE` | 57 | `_time` | `GetSystemTimeAsFileTime` IAT slot and whole `__aulldiv` |
| `0x00644009` | 156 | `__fpclass` | Whole `__sptype` and complete double-zero constant |
| `0x006451CF` | 64 | `__ms_p5_test_fdiv` | Three complete double constants from its own member |
| `0x0064762B` | 188 | `__decomp` | Two double-zero references and two calls to whole `__set_exp` |
| `0x0064AB0F` | 262 | `___sbh_alloc_new_group` | `VirtualAlloc` IAT slot |

`scripts/repo-python scripts/verify-runtime-external-origins.py` freshly
extracts hash-pinned archive members and requires each function's own
definition auxiliary extent, without a caller-supplied size fallback. It
compares every byte, verifies complete decoding and internal control flow,
and checks the ledger extents for overlapping candidates. Four direct-call
fields bind separately replayed full CRT bodies; two absolute indirect-call
fields bind names and DLLs decoded from the raw PE import directory, rather
than guessed slot labels. Six scalar fields bind whole relocation-free
8-byte definitions in their own vendor members, including the exact bits
encoded by each `__real@...` symbol. Every target scalar is checked for its
full bytes and readonly section permissions. These checks credit no extra
callee or data origins.

The target imports are `KERNEL32.dll!GetSystemTimeAsFileTime` at
`0x00657188` and `KERNEL32.dll!VirtualAlloc` at `0x00657158`. The four
distinct scalar targets are `0x0065F4C8`, `0x006612B8`, `0x006612B0` and
`0x00657D00`. They are full double constants, not inferred global layouts.
The single-threaded archive also contains identical full function shapes
and typed dependencies for these five candidates; the selected multithreaded
archive is a pinned reproduction source, not proof of the original link
profile. Six public regression tests reject incorrect imports, unverified
callees, arbitrary IAT reads, untyped fields, truncated constants and writable
scalar storage.

The complete verifier passed locally and through the no-auth public Funnel
MCP. Public CI passed all 122 tests and progress freshness checks.

R098 adds five library origins / 727 bytes, reaching 2,919 reviewed
candidates (805 authored, 1,539 library, 575 compiler), with 1,432 pending.
Exact remains 42 functions / 8,916 bytes against 1,950,921 provisional
authored bytes (0.46%); no source or exact credit. R097 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37109339147.

## R099 — locale parser with a whole readonly string definition

The complete 220-byte `0x00642CC1` matches `___lc_strtolc` from the pinned
`libcmt.lib` member `setlocal.obj`. Its own function auxiliary record establishes
the full source extent; every byte, exit and internal branch is checked.
Four typed direct calls bind independently replayed `_memset`, two `_strncpy`
calls and `_strcspn`. The fifth field binds the string COMDAT at `0x00661158`.
The whole four-byte source section contains the locale delimiters `_.,`
and the terminating NUL. Its complete bytes, readonly PE permissions,
definition topology and source hash are checked; no prefix or arbitrary
string label establishes the binding.

The existing CRT external verifier now supports whole relocation-free
readonly sections in addition to scalar COMDATs. It requires the referenced
symbol at section offset zero and records every definition in that complete
section. Three public regression tests reject shrinking a section, dropping
peer definitions and treating an interior symbol as the section start.
R098's five accepted bodies are replayed by the same verifier. No new data
origin, source presence or exact credit is granted.

The complete six-body verifier passed locally and through the no-auth public
Funnel MCP. Public CI passed all 125 tests and progress freshness checks.

R099 adds one library origin / 220 bytes, reaching 2,920 reviewed candidates
(805 authored, 1,540 library, 575 compiler), with 1,431 pending. Exact remains
42 functions / 8,916 bytes against 1,950,921 provisional authored bytes
(0.46%). R098 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37109763536.

## R100 — explicit game policies around reviewed core behavior

Twelve complete short bodies implement custom game behavior and bind reviewed
authored callees. Origin acceptance comes from these operations and their
owner context, rather than a short instruction shape or a mapped name.

| Address | Bytes | Inferred role and target observations |
| --- | ---: | --- |
| `0x00412660` | 96 | Camera initialization stores four parameters in camera globals, calls the reviewed camera update and copies derived camera state |
| `0x004170D0` | 65 | Capture the primary target using a 640-by-480 `SetRect` and the reviewed opaque texture copy |
| `0x00417120` | 31 | Install the actual `0x00417160` present callback and clear the object's byte flag at `+4` |
| `0x00417160` | 98 | Build a 640-by-480 quad, select blend mode zero and draw the supplied texture with color `0xFFFFFFFF` |
| `0x004171D0` | 50 | Draw the object's texture through the reviewed quad renderer only when its `+4` byte flag is nonzero |
| `0x00425330` | 84 | Loading-scene update runs custom virtual dispatch, loads characters/stage and handles mode/progress flags and transition results |
| `0x004255D0` | 78 | Timed-scene update polls scene input, dispatches virtually, presents, increments a word counter and chooses transition `0x220D` when the counter exceeds 180 |
| `0x004256C0` | 96 | Poll keyboard/joysticks, update held counts and toggle window mode for Enter with either Alt key |
| `0x00446B60` | 35 | Call the reviewed HUD atlas-number renderer with an additional default-zero argument |
| `0x00453D40` | 32 | Forward a signed word sound index to the reviewed game sound bank at object offset `+0x6D0` |
| `0x00457490` | 31 | Set the reviewed input mapping at object offset `+0x494` from the supplied binding pointer |
| `0x005F70E0` | 84 | Load the effect pattern catalog, allocate texture slots and load `data\system\effect.dat`, with explicit `LoadEffect...` logging |

The calling roles are inferred. Byte/word reads and observed member offsets
do not establish complete object layouts or original type spellings. The
loading update's values are transition observations, not a recovered enum.
The two Alt scan codes are `0x38` and `0xB8`, and Enter is `0x1C`; their use
is explicit in the keyboard policy, not inferred from a generic wrapper.

`scripts/repo-python scripts/verify-short-game-origins.py` checks the complete
780 bytes and all exits/branches, 27 direct calls, four indirect calls and
40 selected policy instructions. It replays all recorded authored extents
and freezes 27 independently reviewed whole game anchors, including the
reviewed loader, battle/character/HUD owners and the core callees. Eight
complete-parent call edges add owner context. The primary capture and
callback use `USER32.dll!SetRect`, independently decoded from the raw PE IAT
at `0x00657210`. The remaining two indirect calls are observed game virtual
dispatch; their dynamic destinations receive no origin credit.

`Graphics::SetBlendMode` is a complete 495-byte exact context unit including
its eight-entry table. The verifier cold-builds and replays that whole unit;
it never decodes the table as instructions or narrows its credited extent.
The actual present callback pointer and two selected readonly scene virtual
slots (`0x00657BB8` and `0x00657BE4`) are checked. These selected slots do not
establish full vtable extents. Attested Ghidra caller/callee/reference queries
each supplied their own completion marker; raw decoding remains authoritative
for the complete body and fields. Four public edge tests reject omitted
calls, unrelated reviewed destinations and unreviewed/vendor owner anchors.

The full verifier passed locally and through the no-auth public Funnel MCP,
including the cold 495-byte blend-mode context. Public CI passed all 129
tests, target-required tracking and progress freshness checks.

R100 adds twelve authored origins / 780 bytes, reaching 2,932 reviewed
candidates (817 authored, 1,540 library, 575 compiler), with 1,419 pending.
There are 770 explicitly recorded authored bodies / 1,939,358 bytes. Exact
remains 42 functions / 8,916 bytes against 1,951,701 provisional authored
bytes (0.46%); no source or new exact credit. R099 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37110276865.

## R101 — effect forwarders and fixed background transforms

Eleven complete game bodies bind reviewed custom geometry/effect behavior:

| Address | Bytes | Target-observed policy |
| --- | ---: | --- |
| `0x004424E0` | 96 | Sum signed coordinate fields `+0x34/+0x3C` and `+0x38/+0x40`, convert each sum to float, divide by the readonly `2.0f` and spawn an auxiliary effect through `0x006716C8` |
| `0x0044D910`, `0x0044DDC0` | 88 each | Apply fixed scale/rotation arguments, copy 33 DWORDs and write output color word `0x80000000` |
| `0x00450040`, `0x00451BC0` | 88 each | Apply the same fixed transform and 132-byte copy with output color word `0x40FFFFFF` |
| `0x00453A70` | 65 | Spawn a battle effect through the game manager pointer at `+0x2EC`, supplying an argument-owner pointer at `+0x314` |
| `0x00453C80`, `0x00453CC0` | 57 each | Spawn auxiliary effects through the global game manager, supplying `+0x314` and two default-zero arguments |
| `0x00453D00` | 61 | Forward the configurable auxiliary-effect flags through the same global manager with argument-owner pointer `+0x314` |
| `0x005FAB90` | 61 | Spawn a peer effect through manager pointer `+0x90` with argument-owner pointer `+0x80` and default-zero arguments |
| `0x005FABD0` | 65 | Forward configurable peer-effect flags through the same observed owner fields |

The four transforms call the whole reviewed `SpriteTransform::ScaleQuad`
and `RotateQuad`; the seven effect policies call whole reviewed custom
spawn implementations. The fixed stack literals include the float bit
patterns for `0.3f`, `1.0f` and `160.0f`. Their original parameter/type
spellings remain unknown. The copy width describes an observed 132-byte
record operation, not a complete recovered class layout.

`0x00453C80` returns with 20 bytes of stack cleanup, while `0x00453CC0`
returns with 24. Their similar argument-forwarding instruction shapes do
not justify collapsing the distinct method contracts or deleting an unused
stack argument. The configurable variants return with 28 bytes. These are
target ABI observations; no source declaration or exact reconstruction is
introduced. Three public regressions preserve the cleanup distinction and
reject ordinary RET or an unreviewed trailing instruction.

`scripts/repo-python scripts/verify-effect-forwarder-origins.py` checks all
814 bytes, complete CFG, direct call destinations, explicit game-manager
and argument-owner fields, fixed transform/copy/color policy and terminal
RET cleanup. It replays the complete authored ledger and freezes eight
independent whole game anchors: five callees and three previously reviewed
caller owners. Four complete-parent call edges corroborate battle/fighter/
auxiliary-object context. Four selected readonly virtual slots corroborate
the background transform entrypoints; their presence does not establish
full vtable extents. Attested Ghidra caller/reference queries supplied their
own completion markers. The observed divisor is checked as one complete
readonly float at `0x00657480`; no additional data origin is inferred.

The full verifier passed locally and through the no-auth public Funnel MCP.
Public CI passed all 132 tests, target-required tracking and SVG freshness.

R101 adds eleven authored origins / 814 bytes, reaching 2,943 reviewed
candidates (828 authored, 1,540 library, 575 compiler), with 1,408 pending.
There are 781 explicitly recorded authored bodies / 1,940,172 bytes. Exact
remains 42 functions / 8,916 bytes against 1,952,515 provisional authored
bytes (0.46%); no source or exact credit. R100 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37110975044.

## R102 — batch scan and shared game-policy cohort verification

The read-only `scan-origin-candidates.py` examines every ledger extent and
groups the remaining candidates by full body and reviewed call context.
Its initial report covered all 1,408 pending candidates: fifty whole-body
groups, nineteen candidates calling only known game behavior, 214 with
reviewed game callers, 69 with reviewed vendor/compiler callers, 28 with
whole reviewed peers, 182 extent questions and 896 unresolved-context
candidates. These diagnostic lanes do not establish ownership or exactness.
The scan changes no accepted state and normalizes only direct-call fields,
retaining actual destinations, every data/vtable field and RET cleanup.

Manual review of the shortlisted complete bodies accepted one seventeen-
function authored cohort / 2,051 bytes:

| Address | Bytes | Observed game policy |
| --- | ---: | --- |
| `0x00417140` | 28 | Disable the present callback and enable the object's direct-draw byte flag |
| `0x00419DF0` | 27 | Schedule a game audio fade with four explicit fixed arguments |
| `0x004250C0` | 107 | Poll input and fighter controls, then handle Enter with either Alt key for window mode |
| `0x004521A0` | 132 | Gate fighter action/virtual updates on two word flags, state ranges 50/150 and the observed float field |
| `0x00453AC0` | 136 | Select an optional `+0x2F0` owner pointer for effect spawning from a stack flag |
| `0x00453B50` | 140 | Forward the same owner selection and an additional effect flag |
| `0x00453BE0` | 145 | Forward configurable effect flags with the selected owner pointer |
| `0x00453D60`, `0x0045B860`, `0x005FAC40` | 29 each | Forward a signed word sound index through the shared game sound bank at `0x00671618` |
| `0x00453E60` | 25 | Forward the camera shake argument to the reviewed custom camera function |
| `0x004549C0` | 165 | Choose facing-dependent sprite coordinates/flip from the object's `+0x2CC` byte and sprite manager at `+0x534` |
| `0x0045D5D0` | 113 | Choose text-render width argument 24 or 16 from a game progress byte and forward object/text flags |
| `0x00426600` | 106 | Poll both input mappings and apply the known Enter/Alt policy, matching the complete reviewed input peer |
| `0x0042AFF0`, `0x0042C150`, `0x0042D860` | 280 each | Draw eight signed glyph indices from a 26-column, 19-by-20 atlas with 14-unit spacing, matching the whole reviewed name renderer |

The shared `verify-short-game-origins.py --cohort R102` checks every byte,
exit and branch, 42 direct calls, five indirect calls, 66 selected policy
instructions and thirty-three independent whole game anchors. Fifteen full
parent edges supply owner context. Four complete reviewed-peer comparisons
retain exact call destinations and all non-call bytes; the peer matches are
corroboration of the explicit game behavior, not a blanket shape-based origin.
The glyph IAT calls bind `USER32.dll!SetRect` decoded from the raw PE; the two
fighter virtual dispatches credit no dynamic callee. Names, object layouts,
original parameter types and several field meanings remain provisional.
Constructor/destructor-only wrappers shortlisted by the same scan remain
pending where explicit-versus-implicit emission is unresolved.

Four new public regressions ensure changing a call destination, data/vtable
pointer or unused-argument cleanup splits a scan group. The existing R100
cohort passed again after the shared-verifier refactor, including its complete
cold 495-byte blend-mode unit and table. Attested caller queries were split
into lists of at most sixteen addresses and each completed independently.
See [batch operations](ORIGIN_BATCH_SCAN.md) for the local/public MCP commands.
Both the R102 cohort verifier and full batch scanner passed through the
no-auth public HTTPS MCP. Local CI passed all 136 public regressions,
target-required tracking and progress freshness; `git diff --check` passed.

R102 reaches 2,960 reviewed candidates (845 authored, 1,540 library, 575
compiler), with 1,391 pending. There are 798 explicitly recorded authored
bodies / 1,942,223 bytes. Exact remains 42 functions / 8,916 bytes against
1,954,566 provisional authored bytes (0.46%); no source or exact credit.
R101 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37111565207.

## R103 — grouped state, record and display policies

The refreshed batch shortlist supplied thirty-three complete game policies /
2,600 bytes. Every member has an independently reviewed whole authored parent;
no origin is inferred solely from a short field accessor or caller name.
Manual review reconciled all bytes, exits, signed field widths and indexed
policy fields before adding this cohort to the shared verifier:

| Address | Bytes | Observed policy |
| --- | ---: | --- |
| `0x0040FA30` | 142 | Increment the `+0x64` word, wrap against `+0x72`, then advance/wrap `+0x62` against `+0x70` with virtual dispatch |
| `0x00412620` | 64 | Reset five camera globals, including the explicit `20.0f` parameter |
| `0x00413420` | 64 | Set font-surface parameters and reset its dword/byte policy fields |
| `0x00413A60` | 85 | Open the object's filename, read 60 bytes to `+0x108`, then close the handle in the reviewed snapshot-restore path |
| `0x00416CE0`, `0x00416DC0` | 108, 93 | Set/test progress bits at `+0x16A9C` with signed-word indices and inclusive range 0 through 320 |
| `0x0041C060`, `0x0041C0D0` | 99, 83 | Configure/create a font with explicit constants, then acquire a DC, select it and record text metrics |
| `0x00425130` | 92 | Increment the selected game record using signed-byte selectors and strides `0x17F0` / `0x5FC` |
| `0x00441FE0`, `0x00442010` | 44 each | Read selected unsigned word tables at `+0x268` / `+0x394` with the game record stride |
| `0x00442540` | 51 | Reset four collision bounds to -10000 / +10000 |
| `0x004451D0`, `0x00445210`, `0x00445250`, `0x00445290` | 55, 55, 50, 50 | Set/get selected game-record dwords at `+8` / `+12` with both observed strides |
| `0x00446D60` | 32 | Set the HUD object's `+0x60` dword to 150 and store its argument byte at `+0x64` |
| `0x004492C0` | 68 | Combine four signed rectangle-edge differences and arithmetic-shift the sign bit, returning 0 / -1 |
| `0x00453A10`, `0x00453E20` | 89, 51 | Reset six auxiliary dwords at `+0x4F8..+0x50C` and four motion fields at `+0x50..+0x5C` in active game update paths |
| `0x00453E80` | 37 | Store the `+0x3B8` signed-word argument only when nonnegative |
| `0x00453EB0` | 181 | Choose signed camera offsets from the argument, facing byte and opponent coordinate; write observed globals with 0 / ±50 policies |
| `0x00454A70` | 35 | Set `+0x538` to `0xF0` and `+0x539` from the argument byte |
| `0x00454EE0` | 133 | Check horizontal limits using complete readonly scalars 40, 0, 880 and 1280; return the observed -1 / 0 / 1 byte policy |
| `0x00454F90`, `0x00454FD0`, `0x00455070` | 58, 61, 56 | Test signed state-word ranges 50–149, 150–199 and 95–99 |
| `0x004550B0` | 130 | Update the `+0x66` facing byte from relative opponent coordinates and report whether it changed |
| `0x00455500` | 118 | Save seven selected collision/state fields with their original dword, byte and word widths |
| `0x004574B0` | 25 | Bind the opponent pointer at `+0x2E8` in the reviewed character-loading path |
| `0x0045CD50`, `0x0045CD70` | 25, 75 | Store notice-related bytes, retaining signed-index bounds and independent flag updates |
| `0x0045D710` | 247 | Advance two signed-word levels according to mode 0/1/2, with limits 25 and 5 and guarded decrements |

`verify-short-game-origins.py --cohort R103` replays all thirty-three full
extents, 185 selected policy instructions, 22 whole independent parents and
33 complete parent edges. Its nine indirect calls include seven IAT bindings
decoded from raw PE imports and two virtual dispatches without a credited
dynamic target. Four full-width readonly float observations bind all six
actual instruction uses. These are target scalar observations, not COFF
section matches or exact reconstruction evidence.

The camera reset's writes to nonmember globals and its explicit nonzero
parameter establish game policy even though it returns `this`; its ownership
does not follow from a generic constructor shape. Other lifetime-only wrappers,
generic hexadecimal conversion and container-like helpers remain pending.
Original names, full object layouts and several field meanings are inferred
or unknown. In particular, a word range or dword value does not by itself
identify a named action, frame rate or timer unit.

Three attested Ghidra caller queries respected the sixteen-address limit and
each returned its completion marker. Local and no-auth public HTTPS MCP
cohort replays passed. Five scalar regressions cover value, readonly storage,
actual pointer and operand-width binding. After regenerating the progress
card, local CI passed 141 public tests, target-required tracking and progress
freshness; `git diff --check` passed.
Both older shared cohorts R100 and R102 passed again, including R100's full
cold blend-mode context and switch table.

R103 reaches 2,993 reviewed candidates (878 authored, 1,540 library, 575
compiler), with 1,358 pending. There are 831 explicitly recorded authored
bodies / 1,944,823 bytes. Exact remains 42 functions / 8,916 bytes against
1,957,166 provisional authored bytes (0.46%); no source or exact credit.
R102 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37113017957.

## R104 — compact game helpers from the full batch scan

The refreshed scanner supplied sixteen complete small bodies / 806 bytes with
independent whole game context. Manual review reconciled every instruction,
exit, direct target and indirect call site before recording ownership:

| Address | Bytes | Observed behavior |
| --- | ---: | --- |
| `0x0040DB10` | 51 | Store four incoming dwords into a 16-byte sprite/geometry record |
| `0x0040FAC0`, `0x0040FB00` | 52, 56 | Reset or set the observed animation counters and limits |
| `0x0040FB40`, `0x0040FC50` | 43, 18 | Clear the secondary animation counter or byte at `+0x40` |
| `0x00411BB0` | 38 | Copy three dwords into the vector at object offset 12 |
| `0x00411BE0` | 33 | Forward the object to the observed global indirect draw dispatch |
| `0x0041CA80` | 96 | Convert the observed ASCII hexadecimal digit/letter ranges |
| `0x00423C60` | 32 | Clamp the selected global dword to a nonnegative value |
| `0x00440B00` | 78 | Draw the selected battle-HUD notice through the reviewed renderer |
| `0x00455010` | 96 | Combine the reviewed state-range predicate with the observed float field test |
| `0x0045B830`, `0x005FAC20` | 21 each | Clear one selected effect dword |
| `0x0045D650` | 78 | Configure the selected notice text fields and reviewed text helper |
| `0x0045D6A0`, `0x0045D6F0` | 72, 21 | Begin or clear the observed notice transition fields |

`verify-short-game-origins.py --cohort R104` freezes all sixteen extents,
eighteen independently reviewed whole anchors, sixteen parent edges and 88
selected instruction witnesses. One complete readonly `0.0f` scalar is bound
to its actual instruction use. The draw call is retained as indirect and gives
no dynamic-callee credit. Constructor/destructor-only shapes and an ambiguous
copy/copy-backward helper remain pending. Names and complete object layouts are
inferred; ASCII conversion behavior does not recover the original API contract.

The cohort passed locally and through the no-auth public HTTPS MCP. An attested
Ghidra caller query covered all sixteen addresses and returned its completion
marker. R104 reaches 3,009 reviewed candidates (894 authored, 1,540 library,
575 compiler), with 1,342 pending. There are 847 explicitly recorded authored
bodies / 1,945,629 bytes. Exact remains 42 functions / 8,916 bytes against
1,957,972 provisional authored bytes (0.46%); no source or exact credit.
R103 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37113604310.

## R105 — closure from newly reviewed helper dependencies

R104 exposed three complete callers whose direct dependencies and parent
context are now independently reviewed:

| Address | Bytes | Observed behavior |
| --- | ---: | --- |
| `0x00427500` | 204 | Build four 16-byte rectangle-corner records through `0x0040DB10`, then copy all four records |
| `0x00443FC0` | 88 | Initialize the observed battle hit-sequence fields, reset animation state, forward one selected byte and request sound `0x26` |
| `0x0045CDC0` | 73 | Initialize four notice fields and call `0x0045D650` with argument one |

`verify-short-game-origins.py --cohort R105` checks all 365 bytes, nine whole
reviewed anchors, three full parent edges and every direct call. The attested
Ghidra caller query returned both target and query completion markers. The
cohort passed locally and through the no-auth public HTTPS MCP. A complete CRT
archive dependency-closure scan found no remaining pending candidate whose
every direct relocation resolves to an already reviewed CRT body; this is a
negative diagnostic result rather than origin evidence.

R105 reaches 3,012 reviewed candidates (897 authored, 1,540 library, 575
compiler), with 1,339 pending. There are 850 explicitly recorded authored
bodies / 1,945,994 bytes. Exact remains 42 functions / 8,916 bytes against
1,958,337 provisional authored bytes (0.46%); no source or exact credit.

## R106 — complete peers of source-reviewed VC7 families

The scanner's reviewed-peer lane contained twenty-four complete bodies / 661
bytes across seven established STL families:

| Family | Bodies | Anchor |
| --- | ---: | --- |
| vector const-iterator constructor | 10 | `0x00405A10` |
| deque iterator advance | 2 | `0x0041F630` |
| deque const-iterator constructor | 5 | `0x0041F6A0` |
| allocator deallocate | 3 | `0x004050E0` |
| deque iterator increment | 2 | `0x00415580` |
| deque iterator decrement | 1 | `0x00420130` |
| vector iterator advance | 1 | `0x004456A0` |

`verify-vendor-peer-origins.py` validates every full candidate extent and
control flow, checks the accepted anchor ownership, cold-runs the existing
deque/vector family verifiers and compares the scanner's structural signature.
Only decoded REL32 call fields are normalized, and their exact destinations
remain in that signature. All other bytes, vtable/data fields and RET cleanup
must agree. This prevents an unrelated short helper or a same-shaped call to a
different function from inheriting library ownership.

The verifier passed locally and through the no-auth public HTTPS MCP. Original
template element types remain unknown; source-family equality establishes
library origin only. R106 reaches 3,036 reviewed candidates (897 authored,
1,564 library, 575 compiler), with 1,315 pending. The authored denominator and
exact state remain 8,916 / 1,958,337 bytes (0.46%); no source or exact credit.
R105 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37114655064.

## R107 — pinned VC7 runtime leaves

Four complete target bodies / 199 bytes match complete COFF functions extracted
from the hash-pinned VC7.1 `libcmt.lib` archive:

| Address | Bytes | COFF function | Relocations |
| --- | ---: | --- | ---: |
| `0x00643680` | 123 | `__setjmp3` | one `DIR32` `__except_list` field |
| `0x00643AF0` | 31 | `__aullshr` | none |
| `0x00646B65` | 23 | `__load_CW` | none |
| `0x00646BD8` | 22 | `__checkTOS_withFB` | none |

`verify-runtime-leaf-origins.py` re-extracts the pinned archive members, checks
their names, offsets, symbol extents, relocations and hashes, compares every
target byte and validates complete control flow. The `__setjmp3` relocation is
the zero field of the observed `64 A1 00000000` FS:[0] load; it is retained as
explicit evidence rather than treated as a relocation-free match. The verifier
passed locally and through the no-auth public HTTPS MCP.

R107 reaches 3,040 reviewed candidates (897 authored, 1,568 library, 575
compiler), with 1,311 pending. The authored denominator remains 1,958,337
bytes. This is library-origin evidence and adds no reconstruction source or
exact credit. The user then completed exact batches F008 and F009 before
resuming bounded origin review with the six-candidate R108 handoff cohort.

## R108 — complete lifetime evidence and retained ambiguity

Reviewed all six handoff candidates against fresh attested local Ghidra
queries, complete target bytes, 103 independently reviewed or explicitly
pending parent/callee contexts, 98 parent edges and nine selected readonly
vtable slots. The manifest is `config/game-lifetime-origin-evidence.json`;
replay with `scripts/repo-python scripts/verify-game-lifetime-origins.py`.

The pinned VC7 probe cold-builds eleven complete source alternatives and two
implicit cleanup controls. Every COMDAT, including aux-less implicit methods,
includes its entire code section and every typed relocation. Five functions
have indistinguishable explicit and implicit alternatives:

| Address | Bytes | Retained observation |
| --- | ---: | --- |
| `0x0040D8C0` | 22 | Construct the bitmap member through reviewed `0x0041A2D0` |
| `0x0040D8E0` | 19 | Destroy the bitmap member through reviewed `0x0041A380` |
| `0x00411C10` | 25 | Construct geometry at `this + 4` |
| `0x004251C0` | 34 | Write scene vtable `0x00657B88`, then construct game globals at `this + 4` |
| `0x00449DE0` | 45 | Write stage vtable `0x0065844C`, then construct camera at `+4` and texture manager at `+0x18` |

All five remain `unknown/review`. Reviewed game callees, authored parents and
a compiler deleting wrapper cannot distinguish authorship here. The camera
callee writes five explicit globals, rather than five member fields; the
synthetic probe tests spacing only and recovers no class size or layout.
The scene vtable's three observed slots all point to `0x00641E19`; its origin
receives no credit. The six stage slots bind the existing scalar deleting
wrapper plus five `0x00641E19` pointers, without claiming a full vtable extent.

Only `0x00449D40` gains authored origin. Its full 31-byte body writes the stage
vtable and destroys the texture member at `+0x18`. It matches the natural
explicit virtual destructor; implicit nonvirtual and inherited virtual cleanup
controls emit distinct complete 22- and 30-byte bodies. The deleting slot
calls this exact function, and the reviewed derived loader/destroyer family
corroborates the lifetime pairing. Its role is inferred as
`BackgroundBase::DestroyAt00449D40`; the full layout remains unknown.

The pending bitmap parents were also inspected: `0x0040E000` combines generic
vector erase/insert calls with a copied 44-byte element and cleanup, without
independent ownership proof. `0x0040EC8A` begins at an interior catch label and
continues into shared cleanup; its 232-byte candidate span is frozen as partial
context, without accepting an enclosing function or attributing it to authored
code. The pending scene parents `0x00428D60` and `0x0042B1F0` exposed explicit
policies, subsequently reviewed independently in R109.

R108 reaches 3,041 resolved candidates (898 authored, 1,568 library, 575
compiler), with 1,310 pending. It adds 31 authored bytes, no reconstruction
source and no exact credit. Five investigated origins remain unresolved.

## R109 — explicit game policies with mixed-origin dependencies

Thirteen complete functions / 2,465 bytes now have independently reviewed game
ownership. The manifest is `config/game-context-origin-evidence.json`; replay
with `scripts/repo-python scripts/verify-game-context-origins.py`.

| Address | Bytes | Target-observed policy |
| --- | ---: | --- |
| `0x0041C130` | 119 | Release raster storage, restore/delete the selected GDI object, release the window DC and clear two fields |
| `0x0041CF00` | 113 | Search the global name list for equality and retrieve the corresponding entry from a separate list, returning zero when absent |
| `0x00428D60` | 251 | Load `data\system\option.dat`, allocate three textures, create a 1024-by-512 texture with argument 32, set byte/word defaults and apply the selection |
| `0x0042B110` | 169 | Form eight glyph bytes with signed decimal quotient/remainder indices offset by 52, use 19/20 coordinate offsets and call the reviewed glyph renderer |
| `0x0042B1F0` | 260 | Load `data\system\replay.dat`, allocate three textures, clear four word fields, derive a byte from signed global `+0x006714CE` and obtain a replay path |
| `0x004491E0` | 215 | Transform four rectangle coordinates using the argument owner's facing byte `+0x66` and position fields `+0x44/+0x48` |
| `0x00452B30` | 215 | Select word value 9999 and indexed parameter tables in the observed mode, otherwise convert `field +0x36C * 8800 / 900` and add 1201 |
| `0x00455580` | 139 | Read a queued word in mode 2, otherwise obtain a word and record it in mode 1; scale a signed range by division through 32768 |
| `0x0045BA30` | 221 | Delete nonzero pointer entries and clear exactly four lists at stride 20 |
| `0x0045BC30` | 166 | Select a list with a signed-byte index; choose virtual slot 12 or 8 from element byte `+0x67` |
| `0x0045BCE0` | 207 | Visit four lists and dispatch virtual slot 16 when element byte `+0x68` is nonzero |
| `0x005F7D00` | 114 | Select an auxiliary list with a signed-byte index and dispatch virtual slot 8 |
| `0x005F7D80` | 276 | Advance entries through virtual slot 4 across two lists, then delete/erase entries whose dword `+8` is zero |

The verifier freezes 51 complete bounded callee/parent contexts, eleven parent
edges, 157 policy instructions, exact RET cleanup, three raw PE import bindings,
four reviewed scene update/render slots and four complete readonly float
scalars. `0x00640611` and `0x00640F15` retain their explicitly decoded external
tails to `0x006405E0` and `0x00642A61`; those unresolved callees gain no origin
credit. Library helpers and dynamic dispatch likewise retain independent
ownership. Names, field meanings, original state terminology and full owner
layouts remain inferred. A scene's explicit resource/default policy establishes
its authorship despite an ambiguous base constructor.

Restored the prior R104/R105 origin replays after F008/F009 renamed eighteen
accepted functions and changed their status to matching. Explicit aliases bind
each original reviewed name to its current mapped name, address, origin batch,
size and accepted exact unit. All original body hashes and review roles are
preserved. Wrong-unit, wrong-origin and unrelated-name substitutions fail the
public regression tests.

R109 reaches 3,054 resolved candidates (911 authored, 1,568 library, 575
compiler), with 1,297 pending. There are 864 explicitly recorded authored bodies
/ 1,948,490 bytes. The provisional authored denominator is 1,960,833 bytes;
exact remains 60 functions / 9,883 bytes (0.50%). Local acceptance passed both
new verifiers, old R104/R105 replays, target-required tracking, the refreshed
scanner and 146 public tests. R110 starts with six unresolved dependencies
exposed by the effect-list policies; the five R108 lifetime ambiguities remain
pending and are not repeated acceptance targets.

The final no-auth public HTTPS MCP request passed both new verifiers, R104/R105
replays, target-required tracking, 146 public tests, progress freshness and
`git diff --check`. It also cold-built eleven objects and reproduced all 60
complete exact units / 9,883 bytes. Investigation and local verification used
the local tools; the public route was used once for final acceptance.

## R110 — deque dependencies rooted in complete game loops

All six R109 handoff dependencies now have complete library-origin evidence,
alongside their necessary whole range-erase callee: seven bodies / 501 bytes.
The manifest is `config/deque-game-dependency-origin-evidence.json`; replay
with `scripts/repo-python scripts/verify-deque-game-dependency-origins.py`.

| Address | Bytes | Independently source-typed library role |
| --- | ---: | --- |
| `0x004453C0` | 22 | Default iterator construction through the const-iterator base |
| `0x00445400` | 54 | Postfix increment, returning the saved two-word iterator |
| `0x00445530` | 33 | Default const-iterator construction, zeroing both words |
| `0x005F8110` | 17 | Deque size, reading the observed `+0x10` field |
| `0x005F8290` | 59 | Single erase through iterator addition and range erase |
| `0x005F8420` | 54 | Postfix increment through the actual reviewed prefix increment |
| `0x005F8680` | 262 | Complete range erase, including both copy/pop paths and result construction |

The independent natural VC7 probe models the already-reviewed four-list delete
policy at `0x0045BA30` and two-list advance/prune policy at `0x005F7D80`.
Both whole parents reproduce, with all twenty direct calls bound. The second
parent's access call binds the full 68-byte `at` body, including its range-error
path; a probe using unchecked `operator[]` has identical parent bytes but the
wrong typed callee and is rejected. The default-iterator chain and tiny size
getter therefore have independent typed parent evidence, rather than a short
byte-shape guess. These synthetic models do not recover complete game owner
layouts, original class names or original element types.

Cold acceptance compares 53 complete source COMDATs / 3,207 bytes and 85 typed
calls. This includes 44 independently reviewed library anchors, both complete
game parents and all seven new bodies. Every source extent comes from its
function auxiliary record and entire code section. Every target extent, branch,
return and relocation field is checked. The range erase compares all thirteen
calls, both copying directions, pop loops and returned iterator; its extent is
not shortened to fit a wrapper. Postfix increment and decrement share all
non-relocation bytes, so their exact source symbols and full prefix callees
distinguish them. Their hidden-result ABI retains `RET 8`; the single/range erase
wrappers retain `RET 12` and `RET 20` respectively.

Two external boundary contexts remain separately bounded. The unknown
five-byte delete jump at `0x00640F15` retains its exact tail to `0x00642A61` and
receives no origin credit. The 90-byte range-error body at `0x005F8790` retains
its accepted R032 library ownership and whole target hash/CFG. Its historical
vector/`length_error` source-shape alias is not proof of its original source
identity; R110 does not reinterpret that old alias or claim its exception/EH
dependencies. The actual parent probe emits the typed deque range-error call.

The evidence-only cold replay passed before ledger acceptance. Local acceptance
then passed the complete R110/R109 replays, target-required tracking, refreshed
scanner, progress freshness and 152 public tests. Tests reject decrement as
increment, a same-shaped game constructor callee, an untyped or disconnected
getter, and accidental source/exact credit. R110 reaches 3,061 resolved
candidates (911 authored, 1,575 library, 575 compiler), leaving 1,290 pending.
The exact baseline stays 60 functions / 9,883 bytes and the provisional authored
denominator stays 1,960,833 bytes. R111 starts with five diagnostic range-erase
shapes and their effect-list single-erase wrapper; none has acceptance yet.

The single final no-auth public HTTPS MCP replay passed R110 and its R109
parents, the retained R108 evidence, all 864 authored extents, target/project
attestation, 152 tests, progress freshness and `git diff --check`. It also
cold-built eleven objects and reproduced all 60 exact units / 9,883 bytes.
Investigation and intermediate acceptance used local tools.

## R111 — complete deque erase families and necessary iterator helpers

The six handoff candidates, three necessary short callees and three complete
single-erase parents now have library origin: twelve bodies / 1,654 bytes.
Replay `config/vendor-deque-erase-origins.json` with
`scripts/repo-python scripts/verify-vendor-deque-erase-origins.py`.

| Address | Bytes | Complete source-typed role |
| --- | ---: | --- |
| `0x0041E380` | 262 | Range erase for the first reviewed iterator/algorithm family |
| `0x0041E800` | 262 | Range erase for the separate second family |
| `0x00424000` | 262 | Range erase with its own actual helper destinations |
| `0x00455D30` | 262 | Range erase through a complete one-byte-element source graph |
| `0x0045C100` | 262 | Effect-list range erase |
| `0x0041DC90` | 59 | Single erase through `0x0041E380` |
| `0x0041DF10` | 59 | Single erase through `0x0041E800` |
| `0x00423EF0` | 59 | Single erase through `0x00424000` |
| `0x0045C0A0` | 59 | Single erase through `0x0045C100` |
| `0x004143D0` | 35 | Begin iterator for the one-byte source graph |
| `0x00414400` | 41 | End iterator for that same graph |
| `0x00415560` | 32 | Indexed iterator construction through reviewed const-iterator `0x00415E60` |

The independent probe cold-builds erase methods for thirteen synthetic element
types. Matching a 262-byte root alone leaves element types indistinguishable.
Instead, each valid source alternative must reproduce its entire call graph,
including copying, dereferencing, iterator arithmetic, both pop paths and
allocator destruction. Four range graphs completely reproduce with unsigned
long, float and `void*` alternatives. The fifth completely reproduces with
the checked unsigned-byte alternative. This distinguishes the source models
that fit each whole graph; it does not recover the original element types,
their signedness, or whether identical short instantiations were folded.

The verifier compares 129 distinct complete target bodies / 7,958 bytes, 203
typed call fields and 337 complete source alternatives. Its 117 old library
anchors retain their independent origin evidence and whole body hashes. All
calls resolve to complete source-typed bodies inside the graph; it has no
unresolved external dependency. Source extents come from whole code COMDATs
and function auxiliary records. Target extents, every non-relocation byte,
all fields and complete CFGs are checked again after a serial cold build.

Each range erase retains all thirteen calls and both copy/pop paths, with
`RET 20` for two value iterators and the hidden result buffer. Each single
erase retains its iterator-addition call and exact range-erase destination,
with `RET 12`. The one-byte begin/end helpers construct their returned iterator
through the same indexed constructor; that full 32-byte callee in turn binds
the independently reviewed const-iterator constructor. A shorter shape alone
does not earn origin credit, and copy direction or another same-shaped range
body cannot substitute for the actual source-typed call.

The separate 108-byte parent `0x00455CA0` remains pending. Its complete local
Ghidra observation copies an input byte, calls the newly reviewed begin/end
and range erase, then calls the unresolved 1,459-byte `0x00455E40`. R111's
erase probe does not independently type that parent or its insertion callee;
their game/library ownership is not inferred from these reviewed children.
The insertion span is provisional and contains the separate candidate
`0x00456137`; its enclosing extent and adjacent cleanup tails still need
reconciliation before any acceptance.

Evidence-only cold verification passed before ledger changes. Accepted-state
replay, target-required tracking, refreshed scanner, progress freshness and
157 public tests then passed locally. Public tests reject a foreign source
specialization, swapped copying directions, the wrong same-shaped range
callee, changed anchor ownership and accidental source/exact credit.
The checkpoint is 3,073 reviewed candidates: 911 authored, 1,587 library and
575 compiler generated, with 1,278 pending. Exact remains 60 functions /
9,883 bytes; the authored denominator remains 1,960,833 bytes. The next bounded
cohort is six remaining postfix-iterator candidates, requiring complete typed
increment/decrement discrimination and independent context.

One final no-auth public HTTPS MCP replay passed the entire R111 source graph,
retained R110 evidence, all 864 authored extents, target/project attestation,
157 public tests, progress freshness and `git diff --check`. All 60 exact units
also cold-replayed across eleven objects / 9,883 bytes. Investigation and
intermediate verification used local tools; the public route ran once.


## R112 — postfix increment identities and complete game callers

Local attested Ghidra observations and evidence-only cold verification preceded
acceptance. Six 54-byte bodies now have library origin (324 bytes); two complete
game policies add 968 authored bytes. Replay the frozen manifest
`config/deque-postfix-context-origins.json` with
`scripts/repo-python scripts/verify-deque-postfix-context-origins.py`.

| Address | Bytes | Accepted origin and inferred role |
| --- | ---: | --- |
| `0x00414970` | 54 | Library postfix increment through `0x00415580` |
| `0x00414A20` | 54 | Library postfix increment through `0x00415690` |
| `0x00414AD0` | 54 | Library postfix increment through `0x004157A0` |
| `0x0041DF90` | 54 | Library postfix increment through `0x0041ECA0` |
| `0x0041E020` | 54 | Library postfix increment through `0x0041EE00` |
| `0x00423F90` | 54 | Library postfix increment through `0x004244A0` |
| `0x00455800` | 695 | Authored `BattleInput::MatchSequenceAt00455800` |
| `0x00423B40` | 273 | Authored `EventQueue::RunWorkerAt00423B40` |

The independent natural probe emits 52 complete overload controls across
thirteen element models: postfix/prefix increment and decrement. Both postfix
families have identical non-relocation bytes. Each actual relocation at offset
27 instead binds a complete 29-byte increment callee, distinguishing thirteen
increment alternatives from thirteen decrement controls. Every complete
postfix retains its hidden-result iterator copy and `RET 8`. The R085 verifier
cold-replays its independent typed algorithm parents; the two R106 prefix
peers preserve their full prior records and reproduce the cold source of their
R085 anchor. Original element types and any linker folding remain unknown.

Complete authored callers `ReplayRecords::AppendRecord` and
`ArchiveCatalog::CloseNamed` retain their own evidence. The latter walks paired
deques, compares names and erases both entries on a match. Their game ownership
does not independently establish the library identity of a small callee.

The 695-byte input matcher receives sequence length and history offset as
signed byte arguments, derives a history iterator from the deque at `this+0x518`
and scans through its reviewed postfix increment. Its guarded character switch
maps direction digits, A/B/C/D button masks, X and facing-dependent L/R tokens.
The full code ends at `0x00455AB6`; its adjacent 68-byte pointer table and
40-byte remap table are separately frozen and checked with the range guard,
all destinations and both table hashes. The switch data is not extra code or
exact credit. The matcher compares the low nibble for direction tokens and
the high nibble for button tokens. A terminal X pattern reports the first set
button as 1/2/3/4. The complete independently authored fighter caller
`0x004724B0` supplies ownership context. Buffer capacity, invalid-pattern
semantics, the complete owner layout and original source remain unknown.

The worker waits on event global `0x0068BE34` using wait interval `0x0066C23C`,
then traverses deque `0x0068BE44`. A nonzero current entry triggers `SetEvent`
using the queue front's first dword, then postfix increment. A zero entry is
erased through the reviewed single-erase wrapper and the end iterator is
refreshed. Preserve the observed use of the front rather than silently
substituting the current entry. The full 273-byte span includes the target's
unreachable return and `RET 4`. Its exact callback address is pushed to raw
`CreateThread` IAT slot `0x0065713C` by the bounded 155-byte setup context.
The already authored, exact `0x00423C60` controls the same wait global and
has independently authored scene/battle callers. Its R104/F008 evidence,
source, provisional name and exact status are preserved; it earns no new
origin count. HANDLE representation, synchronization and termination intent
remain unproved. No game source body is added from these observations.

The verifier checks 22 complete context bodies / 6,407 bytes, 41 actual parent
edges, 112 field/literal witnesses, raw PE imports and all switch data. The
unknown setup `0x004239F0`, cleanup `0x00423A90`, default iterator
`0x00423F50`, const-iterator constructor `0x00424500` and cookie tail retain
unknown ownership. Context snapshots allow later independent review without
credit from adjacency or reviewed children. The next bounded R113 cohort
covers the queue's five small helper candidates and 96-byte enqueue policy.

The checkpoint is 3,081 reviewed candidates: 913 authored, 1,593 library and
575 compiler generated, with 1,270 pending. Exact stays 60 functions / 9,883
bytes; the provisional authored denominator is 1,961,801 bytes. The complete
recorded authored evidence now covers 866 bodies / 1,949,458 bytes. Five new
regression tests reject decrement substitution, a truncated prefix, a changed
callback/import binding, unknown game-control ancestry and false source/exact
credit. Investigation and intermediate verification use local tools; one
final public MCP request provides acceptance replay.

One final no-auth public HTTPS MCP request passed R112, retained R111/R110
source graphs, all 866 authored extents, target/project attestation, 162 tests,
progress freshness and `git diff --check`. All 60 exact units / 9,883 bytes
cold-replayed across eleven objects. Investigation and intermediate checks
used local tools; the public acceptance route ran once.


## R113 — event queue helpers and the complete game main loop

The six handoff candidates are resolved. Five helpers gain library origin /
153 bytes; the 96-byte enqueue policy and its required 2,987-byte game parent
add 3,083 authored bytes. Replay `config/event-queue-origin-evidence.json` with
`scripts/repo-python scripts/verify-event-queue-origins.py`.

| Address | Bytes | Accepted origin and inferred role |
| --- | ---: | --- |
| `0x00423F50` | 22 | Library default iterator construction |
| `0x00424500` | 33 | Library default const-iterator construction |
| `0x00423D40` | 17 | Library deque size |
| `0x00423DB0` | 49 | Library unchecked deque indexing |
| `0x00423DF0` | 32 | Library deque front |
| `0x00423C80` | 96 | Authored `EventQueue::EnqueueUniqueAt00423C80` |
| `0x00602A60` | 2987 | Authored `GameApplication::RunAt00602A60` |

The natural enqueue probe scans the shared queue for equal entries, retains a
flag rather than exiting early, and calls push_back only when the entry is
absent. Its complete 96-byte body reproduces three source-typed calls and
three DIR32 fields bound to global `0x0068BE44`. This supplies independent
source typing for the 17-byte size helper. The worker's independently reviewed
iterator use and the complete front/begin/dereference chain distinguish these
short helpers from unrelated getters or game constructors. The default
iterator binds its actual 33-byte const-iterator base constructor; two worker
locals are then used with the independently reviewed deque operations. No
ownership follows from two zero stores alone. Unchecked indexing retains
begin, iterator addition and dereference; front retains begin and dereference.

A serial cold build compares 65 whole source bodies / 4,002 bytes and all 150
typed code/data fields, including 59 old library anchors. The probe separately
retains thirteen whole shape controls for each of the five helper families.
These 65 controls demonstrate type ambiguity; they are not claimed as 65
valid complete alternative call graphs. The canonical pointer model fits the
whole checked source graph. Original game element definitions and any folding
remain unknown. This probe does not instantiate an incomplete game owner.

Nine external snapshots retain independent ownership. The pinned archive
verifier cold-rechecks the full memcpy/memmove/strlen anchors, including the
assembly methods' embedded tables. The other external throw, allocation,
exception and string-error candidates remain unknown; their frozen bytes are
context, not new reconciled extents or source identities. The already accepted
string `_Copy` COMDAT at `0x00405460` retains its entire 339 bytes and its three
interior candidates `0x00405507`, `0x0040552E`, `0x00405550` without changing
their ledgers. New accepted functions have no unresolved interior candidate.
All source relocations remain explicit, including FS:[0], exception metadata,
EH handler links, the internal catch label and the two whole vendor literals.
This replay grants no new metadata ownership or external function credit.

The unique enqueue caller creates the game's window, initializes graphics,
input and sound, opens `th075.dat`, `th075bgm.dat` and `th075b.dat`, enters the
message/scene loop and saves scores before cleanup. The literal window title
is `東方萃夢想 ～ Immaterial and Missing Power. ver1.11` in the supplied target.
It creates an event and passes the address of the local handle slot to enqueue;
the reviewed worker reads the first dword of that queued entry to signal it.
The source model's void pointer is a representation witness, not recovery of
the original handle-wrapper or complete synchronization protocol.

The game parent ends at `0x0060360A` with `RET 16`. Its directly indexed table
contains all fifteen scene destinations at `0x0060360B..0x00603646`, followed
by nine INT3 alignment bytes before `0x00603650`. The range guard, all targets,
complete 60-byte table hash, virtual calls and raw PE imports are checked.
Table bytes are separate evidence and earn no extra code or exact credit.
Full local Ghidra decompilation and independent instruction decoding cover the
complete body; partial disassembly output is not the extent authority.
Nine complete game contexts / 5,063 bytes retain 234 field/literal witnesses
and independent game initialization, transition and logo-scene evidence.
The inferred role does not recover the original WinMain spelling or interface.

Evidence-only verification passed before ledger changes. Accepted replay,
retained R112, all 868 authored extents / 1,952,541 bytes, target-required
tracking and refreshed scanner pass locally. The checkpoint is 3,088 reviewed:
915 authored, 1,598 library and 575 compiler generated, with 1,263 pending.
Exact stays 60 functions / 9,883 bytes; the provisional authored denominator
is 1,964,884 bytes. Seven regression tests reject front/back substitution,
untyped getter calls, unused constructor context, a changed queue global,
changed anchor ownership, unresolved new interiors and false source/exact credit.
The next bounded R114 cohort covers shared queue lifetime, its short wrappers,
the registered window callback and the startup entry candidate.

One final no-auth public HTTPS MCP request passed R113, retained R112,
all 868 recorded authored extents, target/project attestation, 169 public
tests, progress freshness and `git diff --check`. All 60 exact units / 9,883
bytes cold-replayed across eleven objects. Investigation and intermediate
verification used local tools; the public acceptance request ran once.


## R114 — shared queue lifetime, window callback and retained startup ambiguity

Four complete policies gain authored origin / 415 bytes. Replay
`config/queue-lifetime-origin-evidence.json` using
`scripts/repo-python scripts/verify-queue-lifetime-origins.py`.

| Address | Bytes | Decision and inferred role |
| --- | ---: | --- |
| `0x004239F0` | 155 | Authored `EventQueue::AcquireSharedServiceAt004239F0` |
| `0x00423A90` | 143 | Authored `EventQueue::ReleaseSharedServiceAt00423A90` |
| `0x004239C0` | 34 | Authored `EventQueue::LocalAcquireReleaseAt004239C0` |
| `0x00603650` | 83 | Authored `GameApplication::WindowCallbackAt00603650` |
| `0x00423B20` | 26 | Pending ordinary/compiler-generated initializer ambiguity |
| `0x0064232C` | 469 | Pending CRT startup code/data/EH bindings |

The shared service initializes only when client count `0x0068BE30` is zero.
It clamps the signed wait interval at `0x0066C23C`, calls timeBeginPeriod(1),
clears global deque `0x0068BE44`, creates event/thread handles, binds the
independently reviewed worker `0x00423B40`, sets thread priority to 15 and
sets active byte `0x0068BE40`. Every acquisition increments the client count.
Release decrements it and performs cleanup only at zero: clears the active
byte, calls TerminateThread, iterates the complete deque through its actual
size/index methods, signals entries, clears it and closes both handles.
The target passes each queue entry value directly to SetEvent. The reviewed
worker reads the first dword of an entry before signaling; that difference
remains an observation, not a repaired indirection or a proved shutdown protocol.
Raw imports identify WINMM timeBeginPeriod and the actual KERNEL32 functions.
The game main loop provides the actual acquire site and four release sites.

Natural probes cold-build the entire 155-, 143- and 83-byte policies with all
37 typed fields. The complete 19-byte clear method is identical to the older
R077 destructor-shaped body at `0x00423F30`, including its actual `_Tidy`
callee. Preserve the R077 name/evidence and original method/folding uncertainty.
The fresh size/index controls retain R113 evidence. The verifier cold-replays
R077 and R113 rather than granting new library credit from equal bytes.
Original owners, queue element types and complete object layouts remain unknown;
the synthetic complete empty probe owners are not recovered game layouts.

Ten whole lifetime controls / 274 bytes include explicit construction and
destruction, implicit member construction/destruction, persistent member
construction/destruction, an ordinary pulse, two generated initializers and a
member function returning this. The 34-byte candidate reproduces explicit local
guard construction/release, retains this in ECX/EAX and binds both complete
accepted lifetime policies. Implicit/persistent construction is 24 bytes;
implicit/persistent destruction is 19, explicit destruction 31 and the ordinary
member returning this 40. The accepted role remains constructor-like and
provisional; no call/xref or complete original owner identity was found.

The separate 26-byte candidate matches both the complete ordinary pulse and
compiler-generated copy initializer `_$E3`. Both bind the actual acquire and
release with the same two typed fields. The entire eight-byte `.CRT$XCU`
section, its two typed registrations and both generated helper bodies prove
that the second alternative is compiler emitted. The value initializer
`_$E1` is a distinct 31-byte control. Neither alternative can select ownership
for the target, whose local Ghidra query found no caller or data reference.
The candidate retains `authored-generated-initializer-ambiguity` and no source
or exact credit. A guessed destructor interpretation is not accepted.

The 83-byte registered callback handles messages 1, 2 and 0x12. Message 1
sets readiness byte `0x0068D674`; message 2 calls PostQuitMessage(0); 0x12
returns zero. Other messages return DefWindowProcA's result with the original
four arguments. The complete body has one RET 16 and eight internal branches.
Main-loop sites `0x00602B47` and `0x00602CE0` bind the function pointer and
readiness flag independently. Four complete game contexts / 3,388 bytes and
all six candidate bodies retain 336 instruction witnesses, complete CFGs,
all calls and actual imports; R113 replay owns the main loop's complete table.

The supplied PE entry's full 469-byte body matches `_WinMainCRTStartup` in
the pinned libcmt.lib `build\intel\mt_obj\wincrt0.obj` member outside every
one of its 37 relocation fields. The source's own auxiliary extent covers
both returns and the internal SEH filter. The diagnostic replay re-extracts
the whole archive member and checks its identity, full source/target hashes,
all non-field bytes and actual field destinations. Four IAT identities and
the `_WinMain@16` callback to the R113 game main loop have independent context;
32 code/data/EH associations remain unresolved. This is not a fully bound
library comparison and the entry remains unknown. It does not retroactively
rename the accepted game main loop. The already reviewed R006 stack probe
retains its complete `__chkstk` evidence; the startup survey's `__alloca_probe`
association requires alias evidence, not repeat candidate credit.

Evidence-only checks passed before ledger changes. Accepted replay, all 872
recorded authored extents / 1,952,956 bytes, target-required tracking and the
refreshed scanner pass locally. Nine regression tests reject discarded generated
alternatives, missing initializer registration, guessed destructor substitution,
wrong release calls, changed callback/readiness/API context, premature startup
acceptance, promoted unresolved bindings and source/exact credit. The checkpoint
is 3,092 resolved: 919 authored, 1,598 library and 575 compiler generated, with
1,259 pending. Exact remains 60 functions / 9,883 bytes; the provisional authored
denominator is 1,965,299 bytes. R115 targets six unreviewed startup dependencies;
none gains ownership from the pending entry's source-symbol spelling.

One final no-auth public HTTPS MCP request passed R114, retained R077/R113
dependency replays and R112 contexts, all 872 recorded authored extents,
target/project attestation, 178 public tests, progress freshness and
`git diff --check`. All 60 exact units / 9,883 bytes cold-replayed across
eleven objects. Investigation and intermediate verification used local
tools; the public acceptance request ran once.


## R115 — complete heap initialization and unresolved startup dependencies

All six handoff candidates and two required heap callees receive complete
origin review evidence. Four source bodies / 196 bytes gain library origin;
four roots / 225 bytes retain explicit pending binding reasons. Replay
`config/startup-dependency-origin-evidence.json` with
`scripts/repo-python scripts/verify-startup-dependency-origins.py`.

| Address | Bytes | Decision and source association |
| --- | ---: | --- |
| `0x0064544F` | 17 | Library `__SEH_epilog` |
| `0x00649735` | 81 | Library `__heap_init` |
| `0x0064971B` | 26 | Library `___heap_select`, required callee |
| `0x0064A6CD` | 72 | Library `___sbh_heap_init`, required callee |
| `0x00645414` | 59 | Pending SEH handler binding |
| `0x006422B2` | 36 | Pending complete CRT error chain |
| `0x0064228D` | 37 | Pending error chain and mutable exit callback |
| `0x00648FF5` | 93 | Pending multibyte initialization/classification chain |

All source bodies come from cold-extracted complete members of the previously
pinned libcmt.lib. Each comparison requires its own function-definition auxiliary
extent; static `_fast_error_exit` is included without using a chosen prefix.
The SEH epilog is a complete relocation-free 17-byte vendor assembly routine:
it restores FS:[0], saved registers and the caller's frame/return state. Its
origin is the vendor library; use by compiler-generated frames does not turn
this imported implementation into newly authored code. No assembly source is
introduced into the reconstruction or exact units.

The complete heap initializer calls raw HeapCreate, stores its handle, calls
the actual selector and saves its result. Selector value 3 invokes the complete
small-block initializer with threshold 0x3F8. If that fails, HeapDestroy receives
the same stored handle. Both failure and success returns are retained. The
selector returns 1 for platform 2 and unsigned major version >=5, otherwise 3.
The small-block initializer calls raw HeapAlloc for 0x140 bytes, checks its
result, records header-list/scan state, clears deferred/count state, stores the
threshold argument and sets list capacity to 16. The pinned vendor header
contains the five-dword HEADER definition used by this allocation. No game
object layout or owner interface is inferred from these CRT structures.

The closed three-function heap graph verifies all 17 code/data fields. Eight
four-byte globals have actual external COMMON definitions in their complete
vendor members; the two version globals use the entire 72-byte crt0dat BSS
symbol topology. Every target data range lies in writable, non-executable PE
loader zero-fill, beyond raw file bytes and within VirtualSize. The verifier
does not attempt to read virtual zeros from nonexistent file data. Zero fill
and matching widths alone establish no semantic identity: the full Heap API
flows, source data definitions, actual stores and independent version-result
provenance provide the bindings. These are reproducible source associations;
original executable debug symbol names remain unproved.

A natural SDK probe cold-emits one complete 24-byte readonly definition of
OSVERSIONINFOA size and field offsets: 148, 0, 4, 8, 12, 16. The whole defining
section and SDK/CRT header hashes are checked. The 469-byte entry observation
retains 17 independent witnesses: it allocates the 148-byte buffer, passes it
to raw GetVersionExA, reads platform at +16 and major version at +4, then stores
the selector's actual globals. Its unknown ownership is preserved; none of
these observations accepts the whole entry or renames the R113 main loop.

The prolog's complete 59-byte source pushes handler `0x00645468` and builds
its FS frame. That target has a full 230-byte `__except_handler3` archive
source body but no current Ghidra function or ledger candidate. Its validation,
global unwind, notification and local-unwind relationships still need full
binding evidence. It remains a diagnostic boundary and grants no candidate
credit. The R025 local-unwind evidence is independently replayed.

The two complete error-policy source bodies bind a shared error-mode location,
error banner/writer and either the dynamic exit slot or direct exit helper.
The latter has a 48-byte own auxiliary extent, including terminal INT3 after
ExitProcess. The ledger currently records only 47 bytes. The diagnostic freezes
all 48 bytes, both constant literals, raw import identities and the dynamic
CorExitProcess path; it does not reconcile or accept that ledger extent yet.
The full 375-byte writer and 57-byte banner remain diagnostic source contexts,
with their error table, mutable state and downstream bindings unresolved.

The complete 93-byte command-line parser has quote-state handling, whitespace
skipping, a null fallback string and lead-byte advancement. Its 30-byte initializer
and 17-byte lead-byte helper fit entire vendor source definitions. Their 336-byte
set-codepage and 51-byte classification bodies are also retained completely,
including the set-codepage cleanup helper inside its source extent. Their
lock/allocation/locale/EH and table bindings still require independent evidence.
These source associations do not accept the parser or its helper candidates.

Eight whole readonly source literals / 121 bytes are independently compared
against complete raw target definitions. Eight diagnostic source bodies /
1,144 bytes preserve all actual field
resolutions and complete instruction inventories without granting ownership.
The existing R006 61-byte stack probe is freshly compared in full. Its
`__alloca_probe` alias is an external label at the same section/offset as the
own auxiliary-record `__chkstk` definition, not an inferred name from a call.
R006 origin, name, extent and denominator remain unchanged. Retained archive
replay covers 57 old bodies / 5,641 bytes and the three R025 local bodies /
1,762 bytes, including embedded tables and complete local bindings.

Evidence-only verification passed before ledger changes. Accepted replay,
target-required tracking, refreshed scanner and public local checks pass.
Eleven regression tests reject named unknown callees, promoted pending edges,
same-width wrong version fields, incomplete SDK layouts, wrong raw API identity,
truncated INT3 extents, interior aliases, arbitrary zero spans, file-backed zeros
masquerading as loader zero-fill, missing whole literal definitions and source/exact credit. The checkpoint is
3,096 resolved: 919 authored, 1,602 library and 575 compiler generated, with
1,255 pending. Exact stays 60 functions / 9,883 bytes; the provisional authored
denominator remains 1,965,299 bytes, and recorded authored extents remain
872 / 1,952,956 bytes. R116 targets six runtime error dependencies; do not
repeat the four pending roots until their missing binding evidence changes.

One final no-auth public HTTPS MCP request passed R115, retained R114
including its R077/R113 dependency replays, R006/R025 archive anchors,
all 872 recorded authored extents, target/project attestation, 189 public
tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and
intermediate verification used local tools; the public acceptance request
ran once.


## R116 — complete dynamic CRT dispatch and shared-copy tail

All six runtime error candidates receive whole source/target and control-flow
review. Three gain library origin / 304 bytes; three roots / 446 bytes retain
explicit unresolved failure-chain reasons. Replay
`config/runtime-error-origin-evidence.json` with
`scripts/repo-python scripts/verify-runtime-error-origins.py`.

| Address | Complete bytes | Decision and source association |
| --- | ---: | --- |
| `0x006440A5` | 48 | Library `___crtExitProcess`; candidate reconciled from 47 |
| `0x0064FBFE` | 249 | Library `___crtMessageBoxA` |
| `0x00641B80` | 7 | Library `_strcpy`; complete 248-byte shared carrier |
| `0x00648C70` | 375 | Pending `__NMSG_WRITE`: cookie failure chain unresolved |
| `0x00648E11` | 57 | Pending `__FF_MSGBANNER`: writer chain unresolved |
| `0x00640611` | 14 | Pending fastcall cookie check: failure/EH chain unresolved |

The cold replay re-extracts whole members from the hash-pinned VC7.1
libcmt.lib, checks each own function auxiliary extent and compares every byte
outside all 63 typed root fields. All fields retain actual destinations;
pending code/data associations remain diagnostic. Archive spelling and a
relocation-masked fingerprint alone cannot establish ownership.

The exit dispatcher tests GetModuleHandleA("mscoree.dll"), resolves the full
"CorExitProcess" export through raw GetProcAddress and calls that actual EAX
result before unconditional raw ExitProcess. Its own 48-byte source extent
ends with INT3 at `0x006440D4`. The ledger now includes that byte; no invented
return or truncated 47-byte comparison is used. The private database remains
unchanged. R115 retains its historical 47-byte candidate snapshot and checks
this specific R116 reconciliation when replaying its complete 48-byte source.

The message-box dispatcher retains all 21 fields and the complete lookup,
guard, store, argument and indirect-call sequence. Five exports from the
whole "user32.dll" literal bind their actual pointer slots: MessageBoxA,
GetActiveWindow, GetLastActivePopup, GetProcessWindowStation and
GetUserObjectInformationA. Their defining 20-byte BSS section has five
independent source definitions at offsets 0/4/8/12/16 and actual writable PE
loader zero-fill geometry. Equal-width zero storage alone earns no identity.
Raw LoadLibraryA/GetProcAddress and six dynamic export flows are checked.

A natural SDK probe cold-builds the entire 24-byte readonly layout/flag array:
USEROBJECTFLAGS size 12, dwFlags offset 8, WSF_VISIBLE and UOI_FLAGS both 1,
and service notification flags 0x200000/0x40000. The complete target buffer,
flag read and version-dependent byte ORs bind these values. Platform/major
source globals retain independent R115 GetVersionExA-result provenance.
The dispatcher uses a four-argument MessageBoxA call with guarded parent/popup
lookups; the wrapper itself returns with caller cleanup. Original linker flags
and executable debug names remain unknown.

The seven-byte strcpy entry preserves EDI, loads its destination and jumps
to `0x00641BF5` inside the independently reviewed `_strcat` body at
`0x00641B90`. Cold extraction checks the whole relocation-free 248-byte
carrier: the two own function extents, the intervening nine-byte LEA/MOV
alignment, all shared-tail branches and every target byte. The seven-byte
entry has no local RET; ownership does not come from its tiny shape. Retained
strcat/strncpy/strlen/stack anchors total 724 bytes; R115 also cold-replays
57 R006 archive bodies and the three local R025 definitions with full tables.

The diagnostic writer controls include the complete 152-byte, nineteen-entry
error table, every pointer and all nineteen whole vendor messages. All 32
readonly literal definitions / 1,120 bytes are checked with full section
symbol topology, source hashes and readonly target geometry. Complete mutable
application/error/debug/cookie definitions retain their source sections and
initialized or loader-zero-fill target storage. These diagnostic data checks
do not close the remaining code graph. Three additional whole source contexts
/ 122 bytes retain the two R115 error policies and 49-byte cookie failure body.
The failure context includes its embedded filter RET and terminal INT3 at
`0x00640610`; its 48-byte candidate is not accepted or silently reconciled.
Its EH metadata, prolog and security error handler remain unresolved. The
14-byte fastcall check preserves ECX and its real external failure tail.

Evidence-only and accepted checks passed locally. Thirteen public regressions
reject truncated terminal/shared extents, changed shared owners, swapped dynamic
slots, missing actual store witnesses, wrong SDK layout, incomplete table or
literal definitions, guessed cache topology, premature failure ownership,
unearned exact credit and an unrelated historical boundary exception.
The checkpoint is 3,099 resolved: 919 authored, 1,605 library and 575 compiler
generated, with 1,252 pending. Exact stays 60 functions / 9,883 bytes; the
provisional authored denominator remains 1,965,299. Recorded authored extents
remain 872 / 1,952,956 bytes. R117 targets the remaining security/failure/EH
closure. Retain all R108/R114 ambiguities and unresolved R115/R116 roots until
their missing evidence changes.

One final no-auth public HTTPS MCP request passed R116, retained R115 and
R114 including R077/R113 dependency replays, R006/R025 archive anchors,
all 872 recorded authored extents, target/project attestation, 202 public
tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and
intermediate verification used local tools; the public acceptance request
ran once.


## R117 — complete security initialization and SEH dependency closure

The six handoff candidates and three necessary NLG/prolog dependencies retain
whole source/target review. Six gain library origin / 779 bytes; three roots /
394 bytes remain pending. Replay `config/security-eh-origin-evidence.json`
with `scripts/repo-python scripts/verify-security-eh-origins.py`.

| Address | Complete bytes | Decision and source association |
| --- | ---: | --- |
| `0x00645238` | 102 | Library `___security_init_cookie` |
| `0x0064FCF7` | 553 | Library `__ValidateEH3RN` |
| `0x00640B24` | 32 | Library `__global_unwind2` |
| `0x00645414` | 59 | Library `__SEH_prolog`; R115 missing handler evidence closed |
| `0x00640BF1` | 9 | Library `__NLG_Notify1`; whole shared carrier required |
| `0x00640BFA` | 24 | Library `__NLG_Notify`; observed RET 4 |
| `0x006405E0` | 49 source, 48 candidate | Pending `_report_failure` |
| `0x0064529E` | 328 | Pending `___security_error_handler` |
| `0x0064425B` | 17 | Pending `__exit` |

Cold extraction checks each complete hash-pinned libcmt.lib member, each own
function auxiliary extent, every non-field byte and all 65 typed root fields.
Original executable debug names and executable-wide compiler/linker settings
remain unknown. No source, mapping or exact ledger receives new credit.

The cookie initializer independently binds five raw KERNEL32 APIs:
GetSystemTimeAsFileTime, GetCurrentProcessId, GetCurrentThreadId, GetTickCount
and QueryPerformanceCounter. Its actual shared four-byte cookie definition
starts with the complete source value 0xBB40E64E. The body preserves nonzero,
nondefault cookies and otherwise combines observed entropy results, retaining
its actual default fallback. A natural cold SDK probe proves FILETIME and
LARGE_INTEGER sizes and low/high offsets; all actual buffers and field reads
remain in the full instruction witnesses.

The secchk.obj member's entire four-byte `.CRT$XCAA` initializer definition
binds the cookie initializer at target `0x0066C004`. Actual COFF long section
names and all relocation metadata are checked. Complete crt0init.obj boundary
objects `.CRT$XCA`/`.CRT$XCZ` bind `0x0066C000`/`0x0066C034`. The whole merged
56-byte table, including both markers and every observed pointer, is frozen.
The full 106-byte cinit context's actual begin/end loads and four-byte callback
walk prove registration. Other callbacks retain observed addresses only;
registration alone grants them no ownership. Cinit remains pending because
its other FP/RTC/atexit bindings are diagnostic.

The full 553-byte EH validator retains all internal exits and nineteen fields.
Its complete defining 76-byte BSS section contains count at offset 0, page
array at 8 and modification state at 72, including the source alignment gap.
Actual target writable loader zero-fill geometry is checked. VirtualQuery
uses a 28-byte memory-information buffer; InterlockedExchange has both direct
IAT calls and two actual EBX calls after the raw IAT load. The complete cache
lookup/promotion paths, 16-entry limit, lock release and validation failures
remain inside the comparison. Equal-width zero storage proves no identity.

The entire 120-byte readonly SDK layout/constant array cold-builds from the
pinned headers. Its thirty entries prove NT_TIB self/stack fields,
MEMORY_BASIC_INFORMATION allocation/protection/type fields, image/protection
constants, DOS/NT/section header offsets/signatures and entropy buffer fields.
Actual target accesses preserve FS:[0x18], stack bounds, PE field tests and
the writable-section mask. These are CRT observations, not game layouts.

The global unwind body binds its actual local continuation `_gu_return` at
`0x00640B3C`, source offset 24, and the complete six-byte RtlUnwind linker thunk
at `0x00654B54`. The independently decoded IAT slot `0x00657180` names
KERNEL32.dll!RtlUnwind; the external API implementation gains no origin credit.
The return continuation and observed frame/register restoration remain whole.

The two NLG own extents are contiguous at source offsets 205/214 and target
`0x00640BF1`/`0x00640BFA`. The nine-byte first entry jumps into the second at
`0x00640C04`; all 33 carrier bytes and the complete RET 4 tail are checked.
Both actual fields bind the entire 16-byte `__NLG_Destination` source definition,
including signature 0x19930520 and EAX/ECX/EBP stores at offsets 4/8/12. No tiny
shape or guessed ordinary C ABI establishes these origins.

Two non-inventoried source handlers now have complete independently bound
code evidence: `__except_handler3` at `0x00645468` (230) and `__unwind_handler`
at `0x00640B44` (34). Neither receives a new ledger candidate or origin count.
The first handler's five fields bind the complete validator/global unwind,
retained 104-byte R025 local unwind and NLG body. Local unwind's registered
handler field binds the full 34-byte second handler; its fixed same-section
NLG call is checked independently. All scope filter/handler input callbacks
retain their actual 12-byte record stride, slots, register/frame behavior and
complete dispatch paths; their application implementations are uncredited.
The full prolog's handler binding is therefore closed. R115's historical
pending manifest stays intact through a specific R117 accepted-origin guard;
its own complete source comparison still replays. The private database is
unchanged.

The remaining security failure/error/exit roots retain actual unresolved EH,
user callback and termination associations. Whole error-handler literals
remain diagnostic: nine complete definitions / 474 bytes are checked with
source topology and readonly target geometry. The failure source keeps the
filter RET and terminal INT3 at `0x00640610`; its provisional 48-byte candidate
is unchanged. The full 195-byte doexit context retains lock calls, onexit and
pre/terminal callback arrays, exit state and both returns; it does not earn
ownership from the reviewed exit dispatcher. R116 writer/banner/cookie roots
remain pending until this termination graph closes.

Evidence-only and accepted replays passed locally, including retained R116/
R115/R006/R025 evidence and all PE linker thunks. Fifteen public regressions
reject premature short-wrapper ownership, unverified callees, invented handler
candidates, truncated shared tails, incorrect cleanup, swapped SDK/API/scope
fields, arbitrary zero storage, incomplete initializer ranges/markers, lost
terminal bytes, broad historical exceptions and source/exact credit.
The checkpoint is 3,105 resolved: 919 authored, 1,611 library and 575 compiler
generated, with 1,246 pending. Exact remains 60 functions / 9,883 bytes; the
provisional authored denominator and recorded authored extents remain
1,965,299 and 872 / 1,952,956. Continue the R118 termination/lock cohort and
preserve all outstanding R108/R114 ambiguities and R115/R116/R117 roots.

One final no-auth public HTTPS MCP request passed R117, retained R116/R115,
R006/R025 runtime anchors and all PE import thunks, retained R114 including
R077/R113 dependency replays, all 872 recorded authored extents, target/project
attestation, 217 public tests, progress freshness and `git diff --check`.
All 60 exact units / 9,883 bytes cold-replayed across eleven objects.
Investigation and intermediate verification used local tools; the public
acceptance request ran once.


## R118 — complete lock initialization and termination-range controls

All six handoff candidates and three required initialization dependencies
receive whole source/target review. Five library bodies / 273 bytes are
accepted; four roots / 444 source bytes and two existing interior cleanup
candidates / 23 bytes remain pending. Replay
`config/termination-lock-origin-evidence.json` with
`scripts/repo-python scripts/verify-termination-lock-origins.py`.

| Address | Complete bytes | Decision and source association |
| --- | ---: | --- |
| `0x00646658` | 21 | Library `__unlock` |
| `0x006440E7` | 24 | Library `__initterm`; observed EAX begin ABI |
| `0x006465BA` | 73 | Library `__mtinitlocks`, required static initializer |
| `0x0065053F` | 139 | Library `___crtInitCritSecAndSpinCount`, required API wrapper |
| `0x0065052F` | 16 | Library `___crtInitCritSecNoSpinCount@8`, complete RET 8 fallback |
| `0x00644187` | 195 | Pending `_doexit`: lock/onexit graph unresolved |
| `0x00646725` | 49 | Pending `__lock`: lazy initializer/error chain unresolved |
| `0x00646685` | 160 source, 151 candidate | Pending `__mtinitlocknum` |
| `0x0064162B` | 40 | Pending `___onexitinit`: allocator chain unresolved |
| `0x0064671C` | 9 interior | Pending finally inside the 160-byte lock parent |
| `0x00644236` | 14 interior | Pending shared cleanup inside the 195-byte exit parent |

The cold replay checks every complete hash-pinned archive member, each own
auxiliary source extent and all 64 typed root fields. It rechecks full local
relocation metadata, every non-field byte, every instruction, branch and
indirect call. Complete source fingerprints and named but unreviewed callees
are insufficient ownership evidence. Exact, source and mapping ledgers are
unchanged; executable debug names and original compiler flags remain unknown.

The entire writable lock table is 288 bytes: 36 eight-byte pointer/type records.
All initial pointer words are zero; fourteen type words are 1. The complete
336-byte static critical-section BSS has its actual defining symbol and PE
loader zero-fill geometry. A cold natural SDK probe emits all forty readonly
bytes: 24-byte CRITICAL_SECTION, six field offsets, four-byte pointer size,
ERROR_NOT_ENOUGH_MEMORY and STATUS_NO_MEMORY. Source/header hashes and the
whole section definition are checked. These are complete SDK types, not game
owner layouts. Source table flags, actual stride/count, API calls and target
stores establish associations; arbitrary zero storage earns no identity.

The full 73-byte initializer walks all 36 records, assigns the fourteen static
buffers at 24-byte strides and calls the independently compared critical-section
wrapper with spin count 4000. Its failure branch clears the actual table slot
and returns zero; the complete success path returns one. The 21-byte unlock
loads the actual indexed pointer and passes it to raw LeaveCriticalSection.
The 239-byte thread-startup parent independently calls this initializer; its
FLS/TLS/allocation dependencies remain diagnostic and do not gain ownership.

The complete 139-byte wrapper retains its cached function pointer, platform
branch, full "kernel32.dll" and "InitializeCriticalSectionAndSpinCount"
literals, raw GetModuleHandleA/GetProcAddress, actual EAX lookup result/store,
fallback selection and two-argument indirect call. Its complete defining
four-byte cache BSS has actual loader geometry. R115's independent
GetVersionExA result/store witnesses preserve platform-global identity. The
16-byte fallback passes only the first input to raw InitializeCriticalSection,
returns one and removes both incoming arguments with RET 8. No guessed ordinary
C cleanup or truncated unused argument is used.

The wrapper's entire twelve-byte readonly scope table has the source enclosing
level -1 and two actual label pointers: filter `0x0065059C`, handler
`0x006505AA`. Cold COFF label definitions prove that both belong to the same
complete primary source section. The embedded filter RET, exception-code
read, STATUS_NO_MEMORY comparison, SetLastError(8), SEH epilog and main RET
remain in the 139-byte extent. The prolog/epilog and fallback bind independently
replayed complete bodies. Three full scope definitions / 36 bytes retain the
other pending parents' actual cleanup bindings as diagnostics.

The callback loop's own 24-byte source body is checked in full, including
EAX begin, stack end, null guard, four-byte advance, indirect input call and
caller cleanup. Whole doexit parent calls supply actual pre/terminal ranges;
complete crt0init.obj `.CRT$XPA`/`.CRT$XPZ` and `.CRT$XTA`/`.CRT$XTZ` boundary
objects independently define their endpoints. Both entire twelve-byte merged
ranges retain markers and their observed callback pointer. Implementations
of those callbacks receive no credit from registration.

Onexit begin/end have real four-byte COMMON definitions in crt0dat.obj and
actual loader zero-fill geometry. The full forty-byte pending initializer
retains its allocation call and both pointer stores. Its entire four-byte
`.CRT$XIC` registration and complete `.CRT$XIA`/`.CRT$XIZ` markers prove the
actual merged 28-byte input table. The whole 106-byte cinit context retains
its observed range traversal; other callbacks and dependencies remain unknown.
All three merged ranges total 52 bytes. The entire shared 72-byte CRT state
BSS and pending doexit's flag/pointer flows remain independently frozen.

The source auxiliary extent for lazy lock initialization is 160 bytes, including
its nine-byte finally at `0x0064671C`. The historical 151-byte main and nine-byte
interior candidate are preserved pending allocator/TLS dependencies. The
195-byte doexit body also owns the fourteen-byte shared cleanup entry at
`0x00644236`; its EH finally pointer starts five bytes earlier at `0x00644231`
with register preparation. Every source label and full parent byte is checked.
Neither fragment has a fabricated standalone source body or origin credit.
No comparison is truncated to the provisional candidate, and the private
Ghidra database remains unchanged.

Six additional whole source contexts / 522 bytes retain thread initialization,
cinit, malloc, errno, free and the older error policy. Three old anchors /
124 bytes independently preserve prolog, epilog and exit dispatch; R117 also
cold-replays the complete security/runtime/import graphs. Seven whole readonly
literal definitions / 105 bytes include the dynamic API controls and diagnostic
FLS names. All fields keep actual destinations without promoting open graphs.

Evidence-only and accepted replays passed locally. Sixteen public regressions
reject lost primary/cleanup extents, tiny-slice ownership, premature allocator
acceptance, substituted callees, wrong table/static storage, partial SDK layout,
changed API cache/cleanup/scope/range/ABI fields, missing literals and source/
exact credit. The checkpoint is 3,110 resolved: 919 authored, 1,616 library and
575 compiler generated, with 1,241 pending. Exact remains 60 / 9,883 bytes;
the provisional authored denominator and recorded extents remain 1,965,299
and 872 / 1,952,956. R119 targets the required allocator/TLS dependencies;
retain outstanding lifetime ambiguities and pending security/error/lock roots.

Final acceptance passed in one no-auth public HTTPS MCP request: the full
R118 verifier and retained R117/R116/R115/runtime/import graphs, R114 lifetime
controls, all 872 recorded authored extents, target/tracking/Ghidra attestation,
233 public tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and intermediate
verification used local tools.


## R119 — whole small-block heap dependencies and allocator/TLS cycle

The six allocator/TLS handoff candidates, required calloc parent and six
necessary heap/callback/TLS dependencies receive complete source/target
review. Six library dependencies / 1,818 bytes are accepted; seven roots /
607 source bytes and three existing interior cleanups / 27 bytes remain
unknown. Replay `config/allocator-thread-origin-evidence.json` with
`scripts/repo-python scripts/verify-allocator-thread-origins.py`.

| Address | Complete bytes | Decision and source association |
| --- | ---: | --- |
| `0x0064A715` | 43 | Library `___sbh_find_block` |
| `0x0064A740` | 792 | Library `___sbh_free_block` |
| `0x0064B339` | 764 | Library `___sbh_alloc_block` |
| `0x0064AA58` | 183 | Library `___sbh_alloc_new_region` |
| `0x0064EC68` | 27 | Library `__callnewh`; actual size-taking callback |
| `0x0064615D` | 9 | Library `___crtTlsAlloc@4`; raw TlsAlloc, RET 4 |
| `0x00644331` | 18 | Pending `_malloc`: heap/lock/error cycle |
| `0x00644305` | 44 | Pending `__nh_malloc`: whole allocation dependency |
| `0x0064428A` | 123 source, 111 candidate | Pending `__heap_alloc` |
| `0x00642A61` | 113 | Pending `_free`: lazy-lock/error graph |
| `0x00647F98` | 9 | Pending `__errno`: complete thread getter unresolved |
| `0x00646196` | 113 | Pending `__getptd`: calloc/error/FLS graph |
| `0x00644343` | 187 | Pending `_calloc`: lazy-lock/error cycle |
| `0x006442FC` | 9 interior | Pending shared cleanup in complete allocation parent |
| `0x006443ED` | 9 interior | Pending shared cleanup in complete calloc parent |
| `0x00642AB4` | 9 interior | Pending shared cleanup in complete free parent |

Cold extraction verifies every whole hash-pinned vendor member, every own
auxiliary extent, all non-field bytes and all 100 typed root fields. The
accepted graph's 51 fields have actual defining data/import/callee provenance.
Entire instruction inventories, exits, internal branches and indirect calls
are frozen for every root and diagnostic context. Seven retained anchors /
1,341 bytes keep independent R025/R098/R115/R117/R118 origins. Memmove's entire
829-byte code and embedded switch-data extent is independently replayed by
R025; it is not truncated to a linear disassembler's instruction prefix or
misrepresented as all instructions. Full bytes and all fields also compare
in the new verifier. No new exact, source or mapping units are added.

The complete small-block graph binds real heap/header storage, raw HeapAlloc,
HeapReAlloc, HeapFree, VirtualAlloc and VirtualFree imports, the complete
reviewed 262-byte group allocator and the full memmove carrier. Find scans
20-byte headers and uses the actual heap-data field with an unsigned 1 MiB
region test. Free retains both neighboring-entry coalescing paths, size
buckets, vector/count updates, deferred group decommit, whole-region release,
header-list compaction and scan/defer updates. Allocation retains both rover
scans, region/group creation, high/low vector selection, entry unlink/split,
front/back size marks, group count and deferred-group cancellation. The whole
183-byte region allocator retains header-list growth by sixteen records,
16,836-byte zeroed REGION allocation, 1 MiB reservation, cleanup on failure
and all final header/count stores. No larger body is accepted from a prefix.

A cold natural internal CRT/SDK probe emits all 168 readonly bytes: complete
HEADER/REGION/GROUP/LISTHEAD/ENTRY/ENTRYEND sizes and field offsets, page/group/
region constants and real Win32 allocation flags. The 140-byte `_tiddata`
control retains the six observed size/field facts for thread id, handle,
errno, random seed and exception-table pointer. These are supplied complete
runtime types, not inferred game owner layouts. Four defining header hashes,
the source hash, whole probe section and explicit reproducibility profile
are checked; original executable compiler settings remain unknown.

All nine four-byte heap globals have their actual COMMON definitions and
writable loader zero-fill geometry. R115 independently supplies the heap
creation and whole 72-byte small-block initialization/store witnesses. The
six complete defining state sections total 452 bytes: new-handler pointer,
zero-mode BSS, initialized TLS index, four FLS caches, the entire exception
section and the old lock table. The exception section is 136 bytes, including
all ten twelve-byte records and four defining control dwords; no first-record
comparison substitutes for it. Original target debug names remain unknown.

The whole 27-byte new-handler wrapper preserves a null guard, actual callback
pointer load, requested-size argument, caller cleanup and boolean result.
Its complete defining four-byte BSS has real source and loader provenance;
allocation/retry parents retain actual typed calls. No implementation origin
is granted to a user callback. The nine-byte TLS allocation fallback has its
own complete vendor extent, raw TlsAlloc identity and RET 4 despite ignoring
the supplied callback input. The complete 239-byte thread-startup context
retains the actual fallback pointer assignment, full DLL/four-export lookup
flows, four-cache topology and TLS-index result store. Five entire readonly
literal definitions / 54 bytes retain those dispatch controls. The thread
startup parent itself remains pending.

The heap-allocation auxiliary source extent is 123 bytes, ending at
`0x00644304`. Its historical 111-byte candidate ends at the main RET; a
three-byte EH head restores ESI at `0x006442F9`, followed by the nine-byte
shared cleanup at `0x006442FC`. The complete calloc parent similarly has
its EH head at +167 (`0x006443EA`) and shared cleanup at +170 (`0x006443ED`).
The free cleanup at +83 is also an existing interior candidate. All three
whole twelve-byte scope tables retain their real source label pointers and
enclosing-level sentinel. Both earlier EH heads currently have no containing
Ghidra function; the verified PE/source comparisons include them without a
database write. All provisional main/interior extents remain unchanged.
No standalone source bodies are fabricated for these parent labels.

Four complete contexts / 485 bytes preserve thread startup, lock, lazy-lock
initialization and error exit. The remaining allocator/TLS parents participate
in a real dependency cycle through lazy lock initialization, malloc/calloc,
errno/getptd and error/termination policy. Correct fields, complete masked
fingerprints or accepted small-block children do not close that cycle. The
errno offset is observed: the actual nine-byte getter adds eight bytes,
matching the natural `_terrno` field, but its thread-data callee remains pending.
All seven roots and three interior candidates retain explicit open
reasons and no source/exact credit. R118's historical diagnostic snapshots
remain unchanged and cold-replay with the same full extents.

Local complete evidence and accepted-state checks passed. Eighteen public
regressions reject truncated primary/coalescing/memmove extents, independently
promoted cleanup slices, lost EH heads, premature malloc/errno ownership,
wrong region callees, partial layout/state/exception sections, missing COMMON
storage, wrong scope labels, changed callback/TLS ABI or thread allocation
size, omitted literals and source/exact credit.

The checkpoint is 3,116 resolved: 919 authored, 1,622 library and 575 compiler
generated, with 1,235 pending. Exact stays 60 / 9,883 bytes; provisional authored
coverage and recorded extents remain 9,883 / 1,965,299 and 872 / 1,952,956.
R120 targets the six lock/error/termination roots needed to close this cycle;
retain all existing lifetime ambiguities and pending security/error parents.

Final acceptance passed in one no-auth public HTTPS MCP request: the complete
R119 verifier, retained R118/R117/R116/R115/runtime/import graphs, R114 lifetime
controls, all 872 recorded authored extents, target/tracking/Ghidra attestation,
251 public tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and intermediate
verification used local tools.

## R120 — complete CRT allocator/lock/error/termination cycle

Reviewed against the pinned supplied Japanese TH075 target. The six handoff
roots require twelve further complete source bodies to close their actual
code, data, API and EH graph. All eighteen are library origin, covering 1,928
complete source bytes and 166 typed relocation fields:

| Address | Whole bytes | Vendor source symbol |
| --- | ---: | --- |
| `0x00648C70` | 375 | `__NMSG_WRITE` |
| `0x00648E11` | 57 | `__FF_MSGBANNER` |
| `0x00640611` | 14 | `@__security_check_cookie@4` |
| `0x006405E0` | 49 | `_report_failure` |
| `0x0064529E` | 328 | `___security_error_handler` |
| `0x0064425B` | 17 | `__exit` |
| `0x00644187` | 195 | `_doexit` |
| `0x00646725` | 49 | `__lock` |
| `0x00646685` | 160 | `__mtinitlocknum` |
| `0x0064162B` | 40 | `___onexitinit` |
| `0x00644331` | 18 | `_malloc` |
| `0x00644305` | 44 | `__nh_malloc` |
| `0x0064428A` | 123 | `__heap_alloc` |
| `0x00642A61` | 113 | `_free` |
| `0x00647F98` | 9 | `__errno` |
| `0x00646196` | 113 | `__getptd` |
| `0x00644343` | 187 | `_calloc` |
| `0x0064228D` | 37 | `__amsg_exit` |

Replay `scripts/repo-python scripts/verify-runtime-cycle-origins.py`. The
verifier extracts each complete own function auxiliary extent from its
hash-pinned VC7.1 archive member, compares every source byte and relocation,
rechecks the full instruction inventory and exits, and closes every direct
code edge against another complete root or an independently accepted anchor.
The cookie check's external tail jump is accepted only at its actual typed
REL32 field to the complete failure body. Eighteen independently reviewed
anchors / 3,114 bytes are compared in full; their original control-flow and
shared-tail proofs cold-replay through R119 and the retained R115–R118 chain.
This preserves strcpy's shared carrier, memmove's embedded switch data and
the genuine chkstk/alloca source alias rather than inventing new bodies.

Three canonical boundaries expand to their complete source extents:
`0x00646685` 151 -> 160, `0x0064428A` 111 -> 123, and `0x006405E0` 48 -> 49.
The last byte of report_failure is a terminal INT3 after ExitProcess. The
allocator and lazy-lock extents include their complete cleanup entries; no
comparison stops at the earlier provisional Ghidra boundary. No target or
database write is made.

Five existing candidates are library-owned interior labels, **not five more
complete source functions**: `0x0064671C` / 9, `0x00644236` / 14,
`0x006442FC` / 9, `0x006443ED` / 9 and `0x00642AB4` / 9. Their 50 bytes overlap
reviewed parents. Names remain blank, spans remain unchanged, and exact/source
credit remains zero. Each label is re-read from its parent's actual COFF
section; the earlier EH heads (+170 doexit, +111 heap allocation, +167 calloc)
remain distinct from the later shared entries (+175, +114, +170). Seven whole
12-byte scope tables bind their actual filter/handler labels inside complete
parents, including the two newly replayed security failure scopes.

Defining data comprises fifteen whole sections / 1,048 bytes, eleven genuine
four-byte COMMON definitions, six source CRT range markers, three complete
merged callback ranges / 52 bytes, the actual four-byte onexit initializer
registration, and thirty-eight full readonly literals / 1,513 bytes. The full
152-byte error table retains all nineteen code/message pairs; each pointer
binds a whole defining literal. Writable PE storage, loader zero-fill,
source symbol offsets and every initialized pointer are checked rather than
using arbitrary zero scalars. Retained cold SDK/CRT probes establish the
complete critical-section, exception, heap and thread layouts without adding
any game class layout or source.

The 239-byte MT initializer is diagnostic context only. Its complete code,
export literals, raw fallback API slots, TLS index and FLS cache establish the
provenance of getptd's dynamic API dispatch. Its other startup/free-callback
children remain unaccepted. Optional `_pnhHeap`, `_user_handler` and `__adbgmsg`
callbacks preserve their actual call ABI and genuine whole BSS definitions;
no user callback implementation receives library origin. The security handler
retains both user arguments, caller stack cleanup, its exception filter and
continuation. The onexit callback loop similarly preserves reverse traversal,
flags, source registration and callback ABI without assigning origin to
registered application callbacks.

`origin_reconciliation.py` lets R115–R119 retain their historical pending
snapshots while accepting only the same complete own member, source/target
hashes, field provenance and specific R120 canonical classification. Historical
cold source and data checks still run. Internal labels additionally require
an accepted complete parent and cannot gain an independent name or source
credit. Fifteen new regression checks reject truncation, open graph edges,
changed parent/source identity, registration substitutions and exact credit.
All 266 public checks pass. The 60-function / 9,883-byte exact baseline and
872 recorded authored bodies / 1,952,956 bytes remain unchanged. Origin totals
are 3,139 resolved (919 authored, 1,645 library, 575 compiler), 1,212 pending.

Investigation and intermediate replay use local tools. Final acceptance is
one public no-auth HTTPS MCP request covering this verifier and retained
runtime/import proofs, R114 lifetime evidence, authored extents, target and
Ghidra attestation, all 60 cold exact units, CI, progress freshness and diff
whitespace checks. The private URL and investigation logs stay untracked.

## R121 — complete registration, heap growth and thread teardown

The six handoff roots are reviewed against the pinned supplied Japanese
TH075 target. Four roots and six required dependencies gain library origin;
ten complete source bodies cover 917 bytes and 71 typed relocation fields:

| Address | Whole bytes | Vendor source symbol |
| --- | ---: | --- |
| `0x006422B2` | 36 | `_fast_error_exit` |
| `0x00646603` | 85 | `__mtdeletelocks` |
| `0x00646166` | 29 | `__mtterm` |
| `0x0064168B` | 18 | `_atexit` |
| `0x00641653` | 56 | `__onexit` |
| `0x006415AB` | 128 | `__onexit_lk` |
| `0x00646756` | 429 | `_realloc` |
| `0x00646903` | 118 | `__msize` |
| `0x006440D5` | 9 | `__lockexit` |
| `0x006440DE` | 9 | `__unlockexit` |

Replay `scripts/repo-python scripts/verify-startup-registration-origins.py`.
Each complete own source auxiliary extent is extracted from a hash-pinned
VC7.1 archive member and all target bytes and typed fields are compared.
Control-flow inventories retain every exit, embedded cleanup and external
REL32 tail. Every accepted direct code edge closes against another complete
accepted body or nineteen independent anchors / 4,280 bytes / 162 fields;
R120 and retained R115–R119/runtime/import/layout controls cold-replay their
original CFG and shared-data extents. In particular memcpy's whole 829-byte
code/switch carrier and resize's whole 735-byte region/group logic remain
independent accepted evidence, not convenient linear instruction prefixes.

Fast error exit uses the WINCRT0 member proven by earlier complete startup
context. Narrow and wide Windows helper bodies are identical here; the
console startup members differ at non-relocation bytes 6 and 7. Neither a
first symbol hit nor this small helper alone establishes the entry variant.
The function retains the actual mutable error-mode test, full banner/writer
callees and terminal exit dispatcher. Thread teardown compares all 36 lock
records, frees dynamic critical sections first, then deletes preallocated
ones so the heap lock outlives heap frees. The FLS/TLS free dispatch retains
its actual slot, source defining cache and index reset; the complete 239-byte
MT initializer supplies API lookup/raw fallback provenance without receiving
ownership for its unresolved locale cleanup callback.

The full onexit/atexit graph retains the application callback value, growth
policy, failed first/retry realloc paths, preservation of the end offset,
pointer updates and callback store. Complete msize/realloc bodies close both
small-block and system-heap paths against real heap COMMON definitions,
whole new-mode storage, all API slots, resize/copy/free/new-handler children
and SEH labels. Registered callback implementations gain no origin merely
from registration. The genuine onexit initializer and CRT registration
remain independently replayed R120 evidence.

Canonical source extents expand only for onexit `0x00641653` 50 -> 56 and
msize `0x00646903` 106 -> 118. Three existing candidates become library-owned
interior labels, not extra complete source functions: `0x00641685` / 6,
`0x00646970` / 9 and `0x006468BE` / 9. Their 24 bytes overlap accepted parents;
spans and blank names are preserved. Onexit's finally starts +50, msize's
EH head +106 and shared entry +109, realloc's EH head +352 and shared entry
+360. Every label and scope pointer is re-read from its actual primary COFF
section. Database and target bytes are unchanged; no source or exact credit
is granted.

Defining controls include seven whole sections / 480 bytes, five actual
four-byte COMMON definitions, ten four-byte source range markers, five whole
callback ranges / 116 bytes, the four-byte onexit registration, five scopes /
72 bytes, and seven complete export literals / 89 bytes. Writable storage,
loader zero-fill, full source topology, all initialized pointers and literal
extents are checked. The FP carrier is the whole 20-byte source section:
`__FPinit` is +8, not an invented isolated scalar. The whole RTC terminator
scope and empty eight-byte marker range are diagnostic evidence only.

MT initializer `0x00646389` / 239 and cinit `0x0064411D` / 106 stay pending.
Their complete 345-byte source and 38 fields are frozen. MT init still needs
the non-inventoried 327-byte freefls parent's locale data and complete freeing
dependencies. Cinit still needs the actual FP callback's conversion table,
converter implementations and precision-control chain. Seven full contexts /
748 bytes / 63 fields cover freefls, non-inventoried RTC termination, fpmath,
freetlocinfo, cfltcvt initialization, processor-feature probing and default
precision. These footprints do not grant parent/callee origin. The two
existing freefls cleanup entries `0x00646339` / 9 and `0x00646345` / 9 remain
unknown, preserving earlier EH heads +301/+315 and shared entries +306/+318.
The non-inventoried primary bodies are not added to candidate counts.

R115 preserves its historical fast-exit snapshot through a narrow R121
reconciliation guard: same whole member/source/target identity and every
field are required, followed by the original cold replay. Sixteen new tests
reject convenient extents, console-member substitution, arbitrary TLS zeros,
unclosed parent ownership, fabricated diagnostic candidates and exact credit.
All 282 public checks pass. Current origin totals are 3,152 resolved:
919 authored, 1,658 library and 575 compiler; 1,199 remain pending. The exact
baseline stays 60 functions / 9,883 bytes, and recorded authored extents stay
872 bodies / 1,952,956 bytes. Investigation and intermediate checks use local
tools; final acceptance uses one no-auth public HTTPS MCP request. The private
URL and logs remain untracked.

## R122 — complete locale defaults, thread cleanup and initialization

The six handoff candidates are reviewed against the pinned supplied Japanese
TH075 target. Five complete bodies gain library origin / 1,159 bytes / 120
typed fields: freetlocinfo `0x00642B09` / 208, monetary cleanup `0x0064CA47` /
217, numeric cleanup `0x0064C7E8` / 95, time cleanup `0x0064C5C6` / 400 and MT
initializer `0x00646389` / 239. Replay
`scripts/repo-python scripts/verify-locale-thread-origins.py`.

The verifier also closes the complete non-inventoried fiber callback
`0x00646207`, `__freefls@4` / 327 bytes / 21 fields. This is an independently
checked whole source control, not a newly invented candidate. Its two existing
interior candidates `0x00646339` / 9 and `0x00646345` / 9 gain library origin
as source labels, retain blank names and unchanged extents, and add no separate
source or exact bytes. Their 18 bytes overlap the whole parent. Earlier EH
heads are +301/+315, shared entries +306/+318; every source label and pointer
is re-read inside its complete primary COFF section. No canonical boundaries
or database names/types are changed in this batch.

Every complete source auxiliary extent, source member/hash, byte, typed
relocation, branch, exit, callback and API witness is replayed. All code edges
of accepted candidates and the whole fiber control close against complete
accepted bodies or twelve independent anchors / 636 bytes / 44 fields. The
full R121 and retained R120/R119/R118/R117/R116/R115/runtime/import graphs
cold-replay their earlier code, data and layout controls. A matched prefix,
provisional name or correct field offset does not earn ownership.

The locale graph uses ten complete defining source sections / 2,092 bytes,
five genuine four-byte COMMON definitions, two scopes / 36 bytes and
forty-seven full readonly literals / 313 bytes. All initialized data pointers
resolve to a full source definition or literal. Source mutability and actual
PE writable/readonly storage are checked; every BSS/COMMON object retains real
loader zero-fill geometry. No arbitrary zero scalar is substituted.

Whole defining carriers include lconv's 56-byte source section at
`0x006708C8`: decimal string +0, complete 48-byte lconv +4 and global pointer
+52. The empty string is a genuine separate one-byte BSS definition at
`0x0068E684`. The full 403-byte setlocal source section at `0x0066FF20`
contains the initial 84-byte thread locale at +8, current pointer +92 and
cache/static data; its complete four-field initializer is compared. The
entire 1,284-byte readonly ctype/wctype section at `0x006626B0` is compared,
including the actual +256 pctype addend, not a 514-byte slice. The complete
184-byte C-locale time record at `0x00670808` binds all 43 pointer fields to
42 whole literals (May shares one definition). Together with the five FLS
export/kernel literals these give all 47 readonly controls.

The new natural `VC7LocaleThreadLayout.cpp` probe cold-builds a complete
55-DWORD / 220-byte control using pinned CRT/SDK headers and explicit
reproducibility flags. Whole sizes are `_tiddata` 140, `threadmbcinfo` 544,
`threadlocinfo` 84, `lconv` 48 and `__lc_time_data` 184. The actual thread
pointers are +96 multibyte and +100 locale; guesses at the end of the structure
are false. Time refcount is +180; its 7/7/12/12/2 pointer arrays and three
format fields are retained in full. These are complete vendor layouts,
not game class declarations or evidence of one executable-wide compiler
profile. No source body is reconstructed and the exact baseline is unchanged.

Cleanup retains all six actual allocated thread buffer fields, exception-table
sentinel, multibyte/locale refcounts, default/current pointer exclusions,
monetary/numeric shared-string protections, ctype allocation base adjustment,
time fields and both finally unlocks. MT initialization keeps actual FLS
lookup/fallback slots, the TLS index, calloc(1,140), exception/random/thread
initializers and all failure teardown paths. Owning the runtime callback does
not assign origin to application callbacks registered elsewhere.

The multibyte initializer `0x006504F9` / 30 remains pending: its real child
`0x006503A9` has a complete 336-byte source body but a 327-byte provisional
candidate plus nine-byte cleanup `0x006504F0`. The 400-byte `__setmbcp_lk`
context at `0x00650209` still needs complete codepage table, SBCS/case-map and
NLS binding evidence. Both contexts / 736 bytes / 52 fields and the whole
cleanup/scope are frozen without origin or boundary credit. The actual
initialization flag COMMON definition is proven; that alone cannot classify
the initialization or its children.

R121 retains its old pending MT/fiber snapshots through narrowly checked
same-source reconciliation. Complete member/source/target identity and all
fields still replay; accepting an interior additionally requires the complete
R122 locale/thread graph and all five accepted canonical roots. Eighteen new
regression checks reject convenient source/data prefixes, fabricated primary
candidates, guessed layouts, unresolved codepage ownership and exact credit.
All 300 public tests pass. Origin totals are 3,159 resolved (919 authored,
1,665 library, 575 compiler) and 1,192 pending. The 60-function / 9,883-byte
exact baseline and 872 recorded authored bodies / 1,952,956 bytes are preserved.
Investigation and intermediate verification use local tools; final acceptance
uses one no-auth public HTTPS MCP request. Private URLs and logs stay untracked.

## R123 — complete multibyte/codepage, NLS and locale dependency graph

The six handoff roots and nine necessary callee candidates gain library origin:
fifteen complete own source auxiliary bodies / 3,970 bytes / 209 typed fields.
Replay `scripts/repo-python scripts/verify-codepage-nls-origins.py`. Every byte,
relocation, instruction, branch, exit, indirect call and defining code/data/API
binding is checked against the pinned supplied Japanese TH075 target and pinned
VC7 CRT archive. Complete independent R122 and all retained runtime/import/layout
controls cold-replay. Relocation-masked fingerprints alone earn no credit.

| Complete body | Address | Source bytes |
| --- | --- | ---: |
| `___initmbctable` | `0x006504F9` | 30 |
| `__setmbcp` | `0x006503A9` | 336 |
| `__setmbcp_lk` | `0x00650209` | 400 |
| `_setSBCS` | `0x0064FFE5` | 41 |
| `_setSBUpLow` | `0x0065000E` | 396 |
| `___updatetmbcinfo` | `0x0065019A` | 111 |
| `___crtGetStringTypeA` | `0x0064DA08` | 442 |
| `___crtLCMapStringA` | `0x0065275D` | 956 |
| `__resetstkoflw` | `0x006518B9` | 227 |
| `___ansicp` | `0x00651D5F` | 67 |
| `___convertcp` | `0x00651DA2` | 457 |
| `_atol` | `0x00642619` | 136 |
| `___updatetlocinfo` | `0x00642DEB` | 59 |
| `___isctype_mt` | `0x0064980B` | 119 |
| `___updatetlocinfo_lk` | `0x00642BD9` | 193 |

The provisional setmbcp 327, mbc updater 99 and locale updater 50 extents are
reconciled to full source extents 336, 111 and 59. All contain their final cleanup
and return. Existing interior candidates `0x006504F0`, `0x00650200` and
`0x00642E1D` retain nine-byte extents and blank names; they gain library origin
as labels in the complete accepted parents. Their 27 bytes overlap the parents,
not separate whole source functions. The mbc updater's EH head is +99 while its
shared cleanup entry is +102. All source labels and earlier EH heads are checked.
No Ghidra database writes or target patches are made.

The source graph closes through fourteen whole independent anchors / 1,142 bytes /
60 fields. The stack probe callee `__alloca_probe` is the actual same-offset alias
of the complete `__chkstk` source definition; its entire 61-byte body still
replays. The other R006/R115/R117/R118/R120/R122 anchors retain their independent
ownership. No additional credit follows from their presence or caller names.

Twelve full defining source sections / 2,296 bytes, eight actual COMMON objects /
545 bytes, six complete scope tables / 96 bytes and forty-four readonly literals /
267 bytes are verified. The whole mutable 248-byte mbctype carrier includes
four type flags, source alignment and all five 48-byte records for codepages
932/936/949/950/1361. It is not treated as a readonly table or a convenient
single-record prefix. COMMON arrays are exactly mbctype 257, mbcasemap 256 and
mbulinfo 12 bytes; the copied mbulinfo loop in setmbcp retains the source's five
USHORT iterations although the complete storage has six. Undefined references
are never substituted for actual defining COMMON records. Every zero object
retains whole PE loader zero-fill geometry.

The entire 32-byte lc_handle/codepage carrier and 72-byte crt0dat platform/argv/
termination carrier bind their real interior definitions. Whole initial locale,
lconv, ctype/wctype and time defaults retain all initialized pointers and all
42 time literals. Both NLS flavor caches have their own real four-byte defining
BSS objects, not arbitrary zero values. Each NLS member's complete four-byte
wide empty-string COMDAT is checked, even though target folding shares its
address. Every initialized data pointer resolves to a complete source definition
or literal. Source and target mutability are checked independently.

Natural `VC7CodePageLayout.cpp` cold-builds a 43-DWORD / 172-byte control with
pinned CRT/SDK headers and explicit reproducibility flags. SDK sizes are CPINFO
20 (LeadByte +6, twelve bytes), MEMORY_BASIC_INFORMATION 28 and SYSTEM_INFO 36
(page size +4). Codepage records are 48 bytes, six USHORTs +4 and ranges +16;
five records occupy 240 bytes. Complete CRT structures retain multibyte 544 and
locale 84; locale codepage is +4, handle array +12, max width +40 and pctype +72.
The earlier R122 thread/locale/time layout control still cold-replays. SDK NLS,
conversion, platform and guard-page constants are included in full. These are
vendor controls, not reconstructed game layouts or executable-wide flags.

Both ANSI and wide NLS branches, including flavor detection and GetLastError,
whole count handling, size-only conversion, sort-key output, dynamic stack
allocation, all five exception filter/handler pairs, stack recovery, heap
fallback and every cleanup path are retained. Stack recovery binds actual raw
VirtualQuery/GetSystemInfo/VirtualAlloc/VirtualProtect imports and complete SDK
output structures. ANSI codepage lookup binds the actual GetLocaleInfoA buffer,
locale-aware atol and its complete character-classification/update cycle. The
cycle closes through already accepted locale cleanup and whole codepage data;
no circular name assumption substitutes for any code or state definition.

R115 and R122 keep historical pending snapshots through narrowly bounded
same-source guards: complete member/source/target/field identities still match,
and the new canonical accepted extent and classification are required. The
three old provisional boundaries remain recorded in the new evidence manifest.
Twenty-two regression checks reject truncated parents/data/arrays, unreviewed
NLS children, forged aliases, guessed layouts, changed historical fields and
source/exact credit. All 322 public checks pass. Origin totals are 3,177 resolved
(919 authored, 1,683 library, 575 compiler), with 1,174 pending. Exact/source/
mapping stays 60 functions / 9,883 bytes; recorded authored extents stay 872 /
1,952,956 bytes. Investigation and intermediate verification are local; final
acceptance uses one no-auth public HTTPS MCP request. Private URLs/logs stay
untracked. Floating-point startup and PE entry ownership remain pending.

## R124 — Complete floating-point conversion and control graph

R124 resolves 27 existing library candidates / 4,252 complete source bytes /
142 typed relocation fields. The six handoff roots expand only to the necessary
conversion, parser, locale, digit-output and arithmetic dependencies. `__cinit`
remains unknown: completed FP children do not resolve its actual initializer
callbacks. Replay `scripts/repo-python scripts/verify-floating-point-origins.py`;
the evidence manifest is `config/floating-point-origin-evidence.json`.

| Complete source body | Address | Source bytes |
| --- | --- | ---: |
| `__fpmath` | `0x006405C2` | 30 |
| `__cfltcvt_init` | `0x0064057A` | 56 |
| `__ms_p5_mp_test_fdiv` | `0x0064520F` | 41 |
| `__setdefaultprecision` | `0x006451BD` | 18 |
| `__controlfp` | `0x0064FBE8` | 22 |
| `__cfltcvt` | `0x0064516C` | 81 |
| `__fassign` | `0x00644E5F` | 62 |
| `__cftof` | `0x00645070` | 98 |
| `__cftog` | `0x006450D2` | 154 |
| `__cftoe` | `0x00644F68` | 108 |
| `__atodbl` | `0x0064F7B3` | 61 |
| `__atoflt` | `0x0064F82E` | 61 |
| `_tolower` | `0x0064F3E5` | 34 |
| `_isdigit` | `0x00642800` | 58 |
| `___tolower_mt` | `0x0064F31D` | 200 |
| `__fltout2` | `0x0064F99C` | 108 |
| `__cftof2` | `0x00644FD4` | 156 |
| `__cftoe2` | `0x00644EBA` | 174 |
| `___strgtold12` | `0x00652CD1` | 1076 |
| `__ld12tod` | `0x0064F70B` | 22 |
| `__ld12tof` | `0x0064F721` | 22 |
| `_$I10_OUTPUT` | `0x00653151` | 654 |
| `___mtold12` | `0x00652BF3` | 222 |
| `___multtenpow12` | `0x0065418C` | 134 |
| `__shift` | `0x00644E9D` | 29 |
| `___ld12mul` | `0x00653F5A` | 562 |
| `__fptrap` | `0x0064FA08` | 9 |

Every complete own COFF AUX extent, non-relocation byte, typed field, instruction,
branch, exit and indirect dispatch is compared to the pinned supplied Japanese
TH075 target and pinned VC7 CRT archive. The parser at `0x00652CD1` expands from
its provisional 1,028-byte code prefix to the whole 1,076-byte source extent,
ending at `0x00653104`. All twelve DIR32 entries in its embedded 48-byte table
bind actual instruction starts in the same source definition. The real unsigned
`eax <= 11` guard, table reference and indexed dispatch at `0x00652D34` remain
checked. The table is compared as data, not disassembled as instructions.
There are no interior candidate additions, target patches or database writes.

Five whole non-inventoried library controls / 230 bytes / ten fields close
`__cropzeros` (75), `__forcdecpt` (60), `__positive` (26), `__fpclear` (1) and
`__RTC_Terminate` (68). They earn no candidate credit. The one-byte fpclear is
its complete real vendor RET body. RTC termination retains its complete scope,
handler and actual empty two-entry range. Twenty-four whole independent anchors /
3,732 bytes / 131 fields retain their prior origins and cold R123 dependencies.
The complete 50-byte control87 is additionally decoded with its actual
abstract/hardware control-word children; previously accepted mapping helpers
remain independently verified. Identical CRT error-source alternatives preserve
the accepted R120 source identity and do not establish one executable-wide profile.

Twelve entire defining source sections / 2,744 bytes, one 12-byte RTC scope,
six whole CRT range markers / 24 bytes, three observed callback ranges / 92 bytes
and fifty readonly literals / 334 bytes are verified. There are no COMMON
substitutes. The six-slot conversion table / 24 bytes initially points to the
complete nine-byte trap in every slot; registration writes bind each real
converter/format helper, including the shared conversion slot. The whole
20-byte fpinit carrier binds fpmath and both fpclear callbacks. A weaker COMMON
FPinit reference never replaces the actual strong source definition.

The 700-byte powers carrier includes all positive and negative records and
retains its actual mutable source and target storage. Both complete 24-byte
float/double conversion-format records are retained in the whole 48-byte carrier.
The eight-byte division flags and twelve-byte multibyte/decimal-point carrier
retain all defining symbols. Decimal point is the actual character field, not
a guessed pointer. Whole locale, lconv, ctype and time defaults preserve every
initialized pointer and all 42 time literals. Every data pointer resolves to a
complete code definition, defining data object or readonly literal; whole BSS
objects retain PE loader zero-fill geometry.

Two natural independent translation units cold-build 36-DWORD / 144-byte FP
and 13-DWORD / 52-byte locale/API controls with pinned CRT/SDK headers and explicit
reproducibility flags. This avoids the real SDK/vendor DOUBLE typedef conflict
without modifying either header. DOUBLE, LONGDOUBLE and long double are eight
bytes; STRFLT is 16 with offsets 0/4/8/12. Complete exception, denormal, rounding,
precision and default control masks are retained, including 53-bit precision.
Locale remains 84 bytes with clike +36, handles +12 and pctype +72. These controls
are vendor evidence, not reconstructed game layouts or executable-wide flags.

The MP division test binds whole KERNEL32 and IsProcessorFeaturePresent strings,
actual GetModuleHandleA/GetProcAddress imports and the indirect call at
`0x00645230` with feature 0 and four-byte stack ABI. Its complete 64-byte R098
fallback retains independent evidence. Parser classification closes through
complete locale-aware tolower/isdigit, locale updating and digit/long-double
arithmetic definitions; names and masked fingerprints alone earn no credit.

The complete cinit code / 106 bytes and actual XI/XC ranges remain observations.
SSE2 initialization at `0x00648052`, non-inventoried stdio initialization at
`0x0064F08F` and non-inventoried C++ exception-filter registration at `0x0064659A`
still need their full defining dependency graphs. The latter registers the
actual callback at `0x0064654C` via SetUnhandledExceptionFilter; it is not pointer
encoding. R121's frozen cinit snapshot is retained through a narrow same-source
guard requiring the new canonical unknown R124 record. No parent ownership is
inherited from completed children. PE entry remains pending independently.

Twenty-five regression checks reject code-only parser truncation, omitted table
entries, invented local labels/candidates, carrier prefixes, unreviewed children,
guessed masks/layouts/API provenance, changed historical source fields and
source/exact credit. All 347 public checks pass. Origin totals are 3,204 resolved
(919 authored, 1,710 library, 575 compiler), with 1,147 pending. Exact/source/
mapping remains 60 functions / 9,883 bytes; recorded authored extents remain
872 / 1,952,956 bytes. Investigation and intermediate verification are local;
one final no-auth public HTTPS MCP acceptance replay passed R124, retained
runtime/import/layout and R114 dependency graphs, all 872 authored extents,
target/project attestation, 347 tests and all 60 exact units across eleven objects.
A narrow public follow-up confirms corrected documentation EOF whitespace and
progress/status; the complete cold acceptance replay ran once. Private URLs and
logs remain untracked.

## R125 — Complete initializer, IO, exception and signal graph

R125 resolves all six initializer/startup handoff roots and five necessary
exception/signal callees: eleven complete library bodies / 1,545 bytes /
77 typed relocation fields. Existing raise cleanup candidate `0x0065378A` also
receives library origin as a 13-byte overlapping label in its complete parent.
Twelve candidates are resolved, with no standalone cleanup function or invented
inventory entry. Replay `scripts/repo-python scripts/verify-initializer-startup-origins.py`;
whole evidence is in `config/initializer-startup-origin-evidence.json`.

| Complete body | Address | Source bytes |
| --- | --- | ---: |
| `__cinit` | `0x0064411D` | 106 |
| `___sse2_available_init` | `0x00648052` | 206 |
| `_has_osfxsr_set` | `0x0064801D` | 53 |
| `?__CxxUnhandledExceptionFilter@@YGJPAU_EXCEPTION_POINTERS@@@Z` | `0x0064654C` | 78 |
| `__RTC_Initialize` | `0x00649693` | 68 |
| `__ioinit` | `0x00649449` | 510 |
| `?terminate@@YAXXZ` | `0x00646478` | 53 |
| `?_ValidateExecute@@YAHP6GHXZ@Z` | `0x0064FF58` | 24 |
| `_abort` | `0x00650517` | 24 |
| `_raise` | `0x0065364F` | 377 |
| `_siglookup` | `0x0065346E` | 46 |

Every own source COFF AUX extent, source/target byte, typed relocation,
instruction, branch, return, trap, tail and indirect call is retained against
the pinned supplied Japanese TH075 target and pinned VC7 CRT archive.
All provisional primary extents already equal their full source definitions;
none is truncated to improve a comparison. Abort retains its own terminal INT3.
Raise retains the earlier EH head at +307 and actual shared cleanup entry +315,
including the internal call to that entry and whole finally path. The existing
13-byte label keeps a blank proposed name and does not become a standalone body.
No game source/header, exact ledger, target or Ghidra database is changed.

The complete 106-byte cinit is now library-owned through its actual closed
FP/XI/XC/RTC graph. Six whole source registration cells / 24 bytes bind onexit,
SSE2, stdio, multibyte, C++ exception-filter and security-cookie callbacks.
Whole XI/XC and both RTC ranges / 100 bytes retain their actual pointers;
eight complete source range markers / 32 bytes preserve CRT subsection identity.
Both RTC ranges have only their two null marker cells. Seventeen full prior
vendor anchors / 1,286 bytes / 98 fields retain independent cold R124 evidence.
The whole FPinit carrier retains its real strong source definition and both
fpclear pointers. Parent credit follows from the completed graph, not names,
registration pointers or relocation-masked fingerprints alone.

Two newly closed non-inventoried controls are initstdio `0x0064F08F` / 169 bytes /
13 fields and C++ filter registration `0x0064659A` / 19 bytes / three fields.
Two earlier R124 controls, fpclear / one byte and RTC termination / 68 bytes /
five fields, also replay completely. These four controls / 257 bytes / 21 fields
add no inventory candidates. Registration binds actual SetUnhandledExceptionFilter
and its returned prior-handler storage. The complete 78-byte callback verifies
C++ exception code, three parameters and both observed magic values before
terminate, then validates and dispatches to any previous handler. Optional
external handler implementations retain unknown ownership.

All eleven XC compiler wrappers / 309 bytes retain their exact R024 evidence
rows and independently reviewed compiler origins. The established natural
VC7StaticLifetime fixture cold-builds with its original explicit profile and
source/header hashes. Its complete emitted wrapper families and every actual
startup/registration/object/callee field replay through verify-static-origins.
The generic CRT runner does not classify those wrappers' game callees or
establish original object types. No existing compiler or authored origin credit
is changed or counted again.

Six entire defining source sections / 824 bytes, seven actual COMMON objects /
4,372 bytes, five whole EH scopes / 60 bytes and the complete 13-byte AuthenticAMD
literal close the graph. The whole twenty-record iob carrier / 640 bytes keeps
both stdin buffer pointers and all initial flags/file fields. The real stdin
buffer COMMON is 4,096 bytes; the complete pioinfo COMMON has 64 pointers /
256 bytes. Separate four-byte SSE2 COMMON definitions remain separate objects.
Every COMMON has its actual defining record and complete PE loader zero-fill
geometry, not an undefined reference or arbitrary zero region. The whole
20-byte signal-action section includes all four actions and its control-handler
installation flag. The entire 136-byte exception-action carrier includes ten
12-byte records and four count/size/FPE-index fields; no record-only prefix is
accepted. All initialized pointers bind complete definitions.

Natural VC7InitializerLayout cold-builds 73 DWORDs / 292 bytes with pinned
CRT/SDK headers and explicit reproducibility flags. IOINFO is 36 bytes with
handle +0, flags +4, pipe character +5, lock-init +8 and critical section +12;
32 records occupy 1,152 bytes and the maximum handle count is 2,048. FILE is
32 bytes with file +16; twenty records occupy 640 bytes. STARTUPINFOA is 68
with reserved count +50 and buffer +52. Full file, stream, signal and SDK
constants retain their vendor values. Thread data is 140 bytes with terminate
+108 and exception table/info/FPE fields +84/+88/+92. Exception actions are
12 bytes; EXCEPTION_RECORD is 80 with parameter count +16 and information +20,
and EXCEPTION_POINTERS is eight bytes. These are vendor controls, not game
layouts or executable-wide compiler settings.

IO initialization retains every inherited-handle allocation, bounded copy,
pipe/API guard, standard-handle lookup, type flag, critical-section path,
allocation failure and cleanup exit. Stdio initialization retains the 512-stream
allocation, 20-stream fallback, failure result and all initial stream/handle
bindings. SSE2 detection retains CPUID availability, its actual feature bit,
OSFXSR movapd probe and local exception filter/handler, full AMD comparison
and family policy. Terminate retains the actual thread callback and caught
exception path before its abort tail. Raise preserves global/per-thread actions,
signal-lock finally cleanup, default/ignore cases, FPE two-argument dispatch,
other one-argument handlers and temporary exception/FPE-state restoration.

R121 and R124 preserve frozen pending cinit observations through narrowly bounded
same-source guards requiring the new complete canonical R125 library record.
Every original member, extent, byte and typed field identity remains checked;
the earlier evidence manifests are not rewritten. Twenty-five regression checks
reject truncated functions/carriers/COMMON, missing callbacks, invented cleanup
credit, guessed offsets, changed historical fields and exact credit. All 372
public checks pass. Origin totals are 3,216 resolved (919 authored, 1,722 library,
575 compiler), with 1,135 pending. Exact/source/mapping stays 60 / 9,883 bytes;
recorded authored extents stay 872 / 1,952,956 bytes. One final no-auth public
HTTPS MCP acceptance replay passed R125 and all retained runtime/compiler/import/
layout graphs, R114 dependencies, authored extents, target/project attestation,
372 tests, progress freshness and git diff whitespace. All 60 exact units
cold-replayed across eleven objects. Investigation and intermediate verification
are local. PE entry remains pending until environment, argv, exception filtering
and other actual startup bindings close. Private URLs/logs remain untracked.

## R126 — Complete environment, command-line and PE startup graph

R126 resolves the six environment/PE-startup handoff roots and five necessary
parser, multibyte and exit wrappers: eleven complete library candidates /
2,033 bytes / 100 typed relocation fields. The supplied executable's entire
469-byte PE entry is now library-owned. Replay
`scripts/repo-python scripts/verify-environment-startup-origins.py`; the whole
manifest is `config/environment-startup-origin-evidence.json`.

| Complete source body | Address | Bytes |
| --- | --- | ---: |
| `_WinMainCRTStartup` | `0x0064232C` | 469 |
| `___crtGetEnvironmentStringsA` | `0x00649327` | 290 |
| `__setargv` | `0x00649285` | 162 |
| `__setenvp` | `0x00649052` | 199 |
| `__wincmdln` | `0x00648FF5` | 93 |
| `__XcptFilter` | `0x00648E76` | 356 |
| `_parse_cmdline` | `0x00649119` | 364 |
| `__ismbblead` | `0x006515F3` | 17 |
| `_exit` | `0x0064424A` | 17 |
| `__cexit` | `0x0064426C` | 15 |
| `_x_ismbbtype` | `0x0065152C` | 51 |

Every accepted primary retains its complete own COFF AUX extent, all source and
target bytes, typed fields, instructions, branches, exits, local exception
filter/handler and indirect calls. All provisional extents already equal their
full source definitions; no comparison is shortened. The whole 15-byte c_exit
at `0x0064427B` has no independent inventory candidate and adds no origin count.
Nineteen complete independently reviewed vendor anchors / 2,675 bytes / 173
fields replay through the retained R125 chain. The stack-probe call retains the
actual same-source chkstk/alloca alias. Identical archive alternatives for
amsg_exit and fast_error_exit preserve the previously selected wincrt0 member;
this does not establish one executable-wide compilation profile.

The startup entry validates both PE32 and PE32+ managed-image paths. Its actual
GetModuleHandleA import is loaded into EDI before both register calls; DOS/NT
signatures, optional-header magic, directory count and CLR directory address
checks remain complete. All heap/thread/RTC/IO/cinit/environment/argv children
and normal/managed/exception exit paths close independently. The actual
WinMain@16 call binds `0x00602A60`: its full 2,987-byte game-policy body, scene
switch and stdcall return of 16 bytes retain independent R113 authored evidence
through R114. A generic CRT entry does not grant vendor ownership to that game
callee, determine the game's original types or create exact reconstruction.

Environment acquisition retains the four-byte flavor cache, double-null wide
and ANSI extents, ERROR_CALL_NOT_IMPLEMENTED fallback, both WideCharToMultiByte
passes and every allocation/API cleanup exit. Raw import names remain exact,
including GetEnvironmentStrings without an A suffix. Setenvp preserves skipped
'=' entries, the complete pointer array, each copied string, allocation-failure
paths, environment initialization and source-buffer cleanup. Setargv retains
its full 261-byte program-name buffer, two calls to the complete standard
364-byte parse_cmdline, counts, argv/string allocation and null terminator.
The alternative 405-byte wildcard parser is independently re-read and rejected
for differing non-relocation bytes; its prefix earns no credit. The parser
keeps quoted program names, backslash/quote parity, doubled quotes, DBCS lead
bytes and both count-only/output modes. Lead-byte helpers retain the whole
257-byte mbctype object, its +1 indexing and mask 4.

Seven complete defining sections / 1,777 bytes include the 72-byte startup state,
12-byte environment-pointer/error-mode BSS, four-byte flavor cache, 261-byte
program-name BSS, eight-byte ctype pointers, entire 1,284-byte narrow/wide ctype
carrier and 136-byte exception-action/count carrier. Four actual COMMON objects /
269 bytes retain their defining records and complete loader zero-fill geometry.
Acmdln's selected COMMON and aenvptr's selected strong section belong to the
complete matching wincrt0 member; all actual context alternatives are enumerated
and verified. No four-byte environment prefix, undefined COMMON reference or
arbitrary zero region substitutes for a defining object. All ctype pointers
retain their actual symbols and addends. Startup's full 12-byte scope binds
both local filter and handler labels; the complete one-byte empty command-line
literal is also checked.

The full exception filter scans all ten 12-byte actions using the thread's
actual +84 table pointer and the carrier's count/size/index fields. It retains
default UnhandledExceptionFilter dispatch, ignore/die cases, all seven FPE
mappings, one-/two-argument handler ABI, clearing actions and restoration of
thread exception-information/FPE state at +88/+92. Optional installed handler
implementations remain unknown; generic dispatch does not assign their origins.

Natural VC7EnvironmentStartupLayout cold-builds 55 DWORDs / 220 bytes with
pinned CRT/SDK headers and explicit reproducibility flags. Controls include
32-bit pointer and two-byte wchar_t, 260-character API limit with a 261-byte
buffer, CP_ACP/120 fallback, OSVERSIONINFOA / 148 and STARTUPINFOA / 68 with
flags +44/show +48. DOS e_lfanew is +60; NT optional headers start +24.
PE32/PE32+ directory counts are +116/+132 and CLR addresses +232/+248.
Both magic values, signatures, directory index 14, thread/action layouts,
FPE constants and exception results retain vendor definitions. The public
mbctype header is incomplete; its 257-element bound comes from the independently
verified whole COMMON definition, not sizeof an incomplete declaration.

Frozen R114 PE-entry and R115 command-line/context observations remain intact.
Narrow guards require their original complete bytes, extents, source identities,
fields and instruction provenance plus the new canonical R126 library record.
Twenty-four regression checks reject truncated paths/data/COMMON, fabricated
c_exit credit, missing source aliases, guessed PE32+ offsets, changed historical
fields, substituted parser versions and ownership inferred from a WinMain name.
All 396 public checks pass. Canonical totals are 3,227 resolved (919 authored,
1,733 library, 575 compiler), with 1,124 pending. Exact/source/mapping remains
60 / 9,883 bytes; authored extents remain 872 / 1,952,956 recorded bytes.
One final no-auth public HTTPS MCP acceptance replays R126, retained R125 and
R114/runtime/compiler/game/import/layout graphs, all recorded authored extents,
project attestation, progress freshness, 396 tests and git diff whitespace.
All 60 exact units cold-replay across eleven objects. Investigation and
intermediate checks are local. Target/database/tool installations and game
source/headers are unchanged; private URLs, logs and vendor bytes stay untracked.

## R127 — Complete x87 dispatch and IEEE exception graph

R127 resolves all six floating-point dispatch handoff candidates and their
necessary graph: nineteen complete library primaries / 2,608 bytes / 56 typed
fields, plus four existing interior candidates / 350 overlapping bytes. Replay
`scripts/repo-python scripts/verify-fp-dispatch-origins.py`; the complete manifest
is `config/fp-dispatch-origin-evidence.json`. No source, mapping or exact units
are added. All source members come from the pinned VC7 libcmt.lib archive.

| Complete source body | Address | Bytes |
| --- | --- | ---: |
| `__trandisp1` | `0x00646980` | 103 |
| `__trandisp2` | `0x006469E7` | 140 |
| `__convertTOStoQNaN` | `0x00646B7C` | 25 |
| `__math_exit` | `0x00646BFB` | 42 |
| `__startTwoArgErrorHandling` | `0x00646CE0` | 23 |
| `__87except` | `0x006505CA` | 248 |
| `__startOneArgErrorHandling` | `0x00646CF7` | 60 |
| `__cintrindisp2` | `0x006489F0` | 62 |
| `__cintrindisp1` | `0x00648A2E` | 61 |
| `__ctrandisp1` | `0x00648C01` | 51 |
| `__ctrandisp2` | `0x00648A6B` | 406 |
| `__handle_exc` | `0x00646FD8` | 548 |
| `__raise_exc` | `0x00646D33` | 677 |
| `__set_errno` | `0x006471FC` | 40 |
| `__matherr` | `0x006506C2` | 3 |
| `__set_statfp` | `0x00647722` | 86 |
| `__statfp` | `0x006476E7` | 11 |
| `__clrfp` | `0x006476F2` | 12 |
| `_atan2` | `0x00642240` | 10 |

Each primary keeps its own complete COFF AUX extent, all source/target bytes,
typed fields, instruction starts, local branches, external transfers, indirect
jumps, exits and x86 ABI. The provisional 72-byte ctrandisp2 extent expands to
its full 406-byte source definition; it includes both existing shared exits.
Seven independently reviewed whole anchors / 462 bytes / 17 fields retain
original R006/R098/R120 origins and replay through the complete R126 chain.

Three necessary full auxiliary controls / 393 bytes / eight fields have no
independent inventory candidate: CIatan2 at `0x0064224A` / 10, the NaN/numeric
primitive owner at `0x00646A73` / 215, and the atan/trig primitive owner at
`0x00648940` / 168. They earn no candidate count. Four existing candidates gain
interior-entry origin only: rtchsifneg `0x00646B43` / 7 at primitive offset 208,
ctranexit `0x00648AB3` / 7 at ctrandisp2 offset 72, cintrinexit `0x00648ABA` / 327
at offset 79, and rtpiby2 `0x006489AC` / 9 at atan-owner offset 108. Their names
remain blank and overlapping bytes earn no standalone reconstruction credit.

Both actual atan2 callers load EDX with the complete 80-byte OP_ATAN2 table
before typed REL32 tails to the C/intrinsic dispatchers. Its operation is 16,
argument count is two and all sixteen DIR32 code entries retain actual defining
source labels, member/section/offset and complete owners. The 16-byte XAM tag
classifier, FXAM/control-word/status handling, XLAT, signed index conversion,
two-argument AH-shift/AL combination and both actual JMP [EBX] tails remain
complete. Same-section shared branches bind their own source-relative target
and actual full owner; they are not invented relocation fields. The two-argument
error entry shares the one-argument owner's offset-nine tail. Generic caller
supplied tables do not classify hypothetical custom callees or game types.

Eleven complete defining data sections / 336 source bytes retain all definitions
and fields. Two distinct eight-byte zero COMDAT definitions fold to one actual
target, leaving 328 unique target bytes; source identities remain distinct.
Controls include the 44-byte indefinite/pi/one/tag carrier, 68-byte common math
constants, 48-byte C-dispatch constants, 40-byte exception constants, 24-byte
over/underflow constants, four-byte security cookie, four-byte matherr flag,
eight-byte fastflag/adjust_fdiv BSS and complete atan2 table. Member-local One
symbols in different archive members remain distinct. Initialized sections
compare completely with typed code pointers; readonly/writable PE geometry and
BSS loader zero-fill provenance are checked. No zero prefix identifies a state.

The full exception graph preserves status/mask, precision/rounding, domain/range/
inexact paths, the default zero matherr flag and zero-return handler, errno,
thread state, IEEE operand/result records and restored control state. The actual
RaiseException import at `0x00657184` retains its complete 16-byte API argument
ABI and exception-code/parameter provenance. Optional user handlers remain
unknown; generic matherr dispatch grants no ownership to their implementations.

Natural VC7FPDispatchLayout cold-builds one whole 352-byte readonly section with
hash-pinned CRT/SDK headers and explicit reproduction flags. It emits 49 DWORD
layout/constants controls, a four-byte flags object, a 32-byte value and a
112-byte IEEE record. The compiler's eight-byte alignment gap after the flags
object is verified as emitted storage, not source padding or a twelve-byte type.
Controls retain four-byte pointers, FP80 / 10, FP128 / 16, exception structure /
32, IEEE Cause/Enable/Status at +4/+8/+12 and Operand1/Operand2/Result at
+16/+48/+80. Natural aggregate initializers verify exception flags, valid/format
bitfields, 53-bit precision and atan2 operation bits against emitted bytes.
These vendor layouts do not establish a game class or original compiler flags.

Thirty-one regression checks reject truncated shared owners, fabricated
auxiliary candidates, wrong source entries, substituted tables/classifiers,
incorrect argument/index protocol, missing data carriers, member-local symbol
confusion, undefined data references and guessed IEEE layouts. All 427 public
checks pass. Canonical totals are 3,250 resolved (919 authored, 1,756 library,
575 compiler), with 1,101 pending. Exact/source/mapping remains 60 / 9,883 bytes;
authored extents remain 872 / 1,952,956 recorded bytes.
One final no-auth public HTTPS MCP acceptance replays R127, retained R126 and
its complete runtime/compiler/game/import/layout graphs, all authored extents,
project attestation, progress freshness, 427 tests and git diff whitespace.
All 60 exact units cold-replay across eleven objects. Investigation and
intermediate checks are local. Private evidence stays untracked; target,
database, shared tool installations and game source/headers are unchanged.

## R128 — Complete elementary math parents and shared entries

R128 resolves all six trigonometric/square-root handoff candidates and the
three necessary existing C entries: three complete library primaries / 534
bytes / 41 typed fields and six interior candidates / 474 overlapping bytes.
Replay `scripts/repo-python scripts/verify-elementary-math-origins.py`; the
manifest is `config/elementary-math-origin-evidence.json`. All definitions come
from the hash-pinned VC7 libcmt.lib archive. No source, mapping or exact credit
is added.

| Complete source primary | Address | Original bytes | Whole AUX bytes | Fields |
| --- | --- | ---: | ---: | ---: |
| `__CIcos` | `0x00641740` | 20 | 174 | 14 |
| `__CIsin` | `0x006417F0` | 20 | 174 | 14 |
| `__CIsqrt` | `0x00641E40` | 20 | 186 | 13 |

Each twenty-byte provisional prefix expands to its full own COFF AUX extent.
All target/source bytes, typed fields, instructions, branches, exits and ABI
are verified. Intrinsic entries reserve twelve stack bytes, save ST(0), call
the independently reviewed classification helper and call their shared
computation at owner +29; they then release twelve bytes and return. The
C entries at owner +20 load EDX from ESP+4, call the independently reviewed
fload_withFB and fall through to the same computation. EFLAGS/EAX from those
complete helpers remain part of the input protocol.

| Existing entry | Address | Overlapping bytes | Whole owner offset |
| --- | --- | ---: | ---: |
| C cos | `0x00641754` | 9 | 20 |
| Shared cos computation | `0x0064175D` | 145 | 29 |
| C sin | `0x00641804` | 9 | 20 |
| Shared sin computation | `0x0064180D` | 145 | 29 |
| C sqrt | `0x00641E54` | 9 | 20 |
| Shared sqrt computation | `0x00641E5D` | 157 | 29 |

The three C entries have actual global source definitions at offset 20.
The shared computation entries have no independent COFF symbol; their
provenance comes from the full source primary's actual relative call at +11,
the target's corresponding call, C-entry fallthrough and instruction starts.
No invented definition or shortened comparison replaces this evidence.
All six proposed names remain blank and overlap adds no standalone source or
exact bytes. The complete thirteen-byte fast_exit at `0x00646BEE` has no
inventory candidate and earns no origin count. It preserves its actual
control-word restoration and return from the saved stack state.

Cos/sin preserve both FCOS/FSIN paths, the entire FPREM1 range-reduction loop,
status/control-word handling, NaN conversion and invalid-input handling.
Sqrt preserves the full sign, exponent/mantissa and low-word checks, signed
zero, positive infinity, NaN and invalid negative paths. All three retain
both actual fastflag dispatches, normal math_exit and complete one-argument
error handling. Normal and error paths pass operation 18 (cos), 30 (sin) or
5 (sqrt). No indirect call/jump is introduced; every external transfer binds
its actual typed source relocation and whole independent callee.

Six complete defining data sections / 136 bytes include the 68-byte common
constant carrier, eight-byte fastflag/adjust_fdiv BSS, 44-byte indefinite/pi/
classifier carrier and the three member-local name sections. Cos and sin
names are four bytes each; sqrt's complete defining section is eight bytes,
including its compiler-emitted zero suffix. The identical `_NAME_` spellings
retain distinct archive members and actual addresses `0x0066FED0`,
`0x0066FEE0`, `0x0066FEF0`. Default control word binds the common carrier +8;
the full ten-byte pi_by_2_to_61 starts +10. All initialized bytes, symbol
definitions, readonly/writable target geometry and loader BSS are verified.
A two-byte word or string prefix does not substitute for its whole section.

Six independent complete anchors / 239 bytes / three fields preserve original
R006, R107 and R127 ownership. The verifier retains the full R127 dispatch/
exception/runtime/game/import graph and independently replays R107's complete
runtime leaves. Original archive/compiler profiles remain unknown.

Natural VC7ElementaryMathLayout cold-builds twelve DWORDs / 48 bytes with
pinned vendor/SDK headers and explicit reproduction flags. It verifies pointer
4, double 8, FP80 10, exception structure 32 with type/arg1/arg2/retval at
+0/+8/+16/+24, domain value 1 and all three actual operation codes. This probe
contains complete vendor types only and establishes no game class layout.
The x87 control word 0x027f is independently observed in full source, the
actual common constant definition and target instructions; it is not inferred
from the public floating-point control API's differently encoded flags.

Twenty-six regression checks reject truncated primaries/data, fabricated
fast-exit credit, wrong parents/entries, guessed names/operation codes/stack
sizes, removed range/sign paths, lost source-call/fallthrough evidence and
member-local name confusion. All 453 public checks pass. Canonical totals
are 3,259 resolved (919 authored, 1,765 library, 575 compiler), with 1,092
pending. Exact/source/mapping remains 60 / 9,883 bytes; recorded authored
extents remain 872 / 1,952,956 bytes.
One final no-auth public HTTPS MCP acceptance replays R128, retained R127/R107
and complete runtime/compiler/game/import/layout graphs, authored extents,
project attestation, progress freshness, 453 tests and git diff whitespace.
All 60 exact units cold-replay across eleven objects. Local investigation
precedes one final public acceptance request. Target, database, shared tools
and game source/headers remain unchanged; private evidence stays untracked.
