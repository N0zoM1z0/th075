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
