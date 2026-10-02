# Origin review journal

The active objective is to finish origin review of every candidate and then
reach at least 50% exact coverage of the confirmed authored-byte set.
Finish evidence-backed origin review of every candidate before resuming exact
reconstruction. This supersedes the earlier alternating workflow. Percentages remain provisional until no origin is pending.
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
