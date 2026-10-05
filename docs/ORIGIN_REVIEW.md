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

## R129 — Complete short runtime, FP exception and array destruction graph

R129 reviews all six handoff candidates. Five gain library origin; abs remains
unknown because complete vendor and ordinary expression alternatives are
indistinguishable. Four necessary complete callees also gain library origin:
eight primaries / 839 bytes / 38 typed fields and one existing interior cleanup /
24 overlapping bytes. Replay `scripts/repo-python scripts/verify-short-runtime-origins.py`;
the manifest is `config/short-runtime-origin-evidence.json`. No source, mapping
or exact credit is added. All vendor definitions come from pinned libcmt.lib.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `_srand` | `0x0064189E` | 13 | 1 |
| `_rand` | `0x006418AB` | 34 | 1 |
| `_fabs` | `0x006418CD` | 177 | 8 |
| `??_M@YGXPAXIHP6EX0@Z@Z` | `0x00641D4A` | 96 | 4 |
| `?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z` | `0x00641CEC` | 94 | 4 |
| `__except1` | `0x006473C1` | 184 | 9 |
| `__handle_qnan1` | `0x0064730F` | 83 | 4 |
| `__umatherr` | `0x00647271` | 158 | 7 |

Seven primaries retain their entire own COFF AUX extents. The vector destructor
has no function-definition AUX record: its sole global function starts at zero
in a complete 96-byte defining code section. The verifier derives that extent
from the actual source header, requires executable/readable/non-writable code,
checks every definition and rejects a second global function or fabricated AUX.
The original 72-byte prefix expands to include its full cleanup. All code,
fields, instructions, local/external branches, exits and callback sites are
compared. ArrayUnwind expands from its provisional 47 bytes to its own full
94-byte AUX body, including filter/termination paths; neither comparison is
shortened. The existing 24-byte candidate `0x00641D92` is the vector owner's
source-defined local cleanup at +72. Its name remains blank and overlap earns
no standalone source or exact bytes.

Rand/srand both bind the complete independently reviewed getptd return and its
vendor holdrand field at +20. The generator updates the same unsigned 32-bit
state with multiplier 214013 and increment 2531011, shifts right 16 and masks
32767. The complete vendor thread layout is 140 bytes. Seed stores, calling
convention and returns remain complete; a thread-field guess alone is insufficient.

Fabs retains normal, special-value, quiet/signaling NaN and exception exits,
all control-word changes/restoration, its entire double-one constant and both
operation-21 transfers. Except1, handle_qnan1 and umatherr close through the
full reviewed status/raise/errno/default-matherr graph. The complete 29-entry
operation/name table is 232 bytes with all 29 DIR32 string pointers. Every whole
string COMDAT is verified: 29 definitions / 151 bytes. The full table scan,
matched/unmatched operation paths, exception record, default handler and errno
policy remain intact. No table prefix, guessed name or undefined reference
substitutes for its defining object.

Thirty-five complete data sections / 423 bytes / 32 typed fields include that
table and all strings, two full twelve-byte SEH scopes, double-one, security
cookie and matherr flag. The scopes bind the vector cleanup at +72 and actual
ArrayUnwind filter/handler labels at +47/+83. Readonly geometry is checked
after every typed field is linked; unrelocated scope bytes are not scalar
literals. Each field retains its own defining source member/section/offset.
Fourteen independent whole anchors / 1,762 bytes / 43 fields preserve original
runtime origins through the complete retained R128 graph.

Both array helpers preserve signed reverse-count traversal, element-address
updates, ECX receiver and the incoming callback at EBP+20. The vector normal
path marks completion before its local finally; the exceptional path invokes
the complete ArrayUnwind over the remaining elements. ArrayUnwind's full
exception filter/termination path and stdcall cleanup of sixteen bytes remain
inside its own source definition. Arbitrary incoming destructor implementations
and original game element types remain unknown and gain no origin credit.

Natural VC7ShortRuntimeLayout cold-builds twenty DWORDs / 80 bytes using pinned
complete vendor/SDK types. Controls include pointer/int/long / four bytes,
thread size/seed offset 140/20, RAND_MAX, exception structure / 32, FP80 / 10,
fabs operation 21 and SEH results. The eight-byte operation/name pair is an
explicit synthetic layout control, not an asserted private vendor type. A
complete synthetic single-inheritance class and member pointer emit a full
thirteen-byte callback control: ECX receiver, actual indirect call and stdcall
cleanup eight. No game owner is instantiated or embedded; this verifies the
calling protocol without claiming an original callback type or class layout.

The eleven-byte `0x00641DAA` remains unknown. Both entire abs/labs AUX definitions
match every target byte with no fields. Natural VC7AbsOriginAlternatives at
explicit /O1 emits the same complete eleven bytes from ordinary int and long
absolute-value expressions. Even whole independently reviewed runtime neighbors
and actual game callers do not distinguish authored versus library ownership,
original spelling, int/long selection or folding. The canonical pending record
retains that evidence and gains no name, source, mapping or exact credit.
The verifier cold-builds both full expressions on every replay; a masked hit
or library-neighbor name cannot erase this ownership ambiguity.

Thirty regression checks reject truncated code/data/scopes, invented AUX or
cleanup credit, wrong table fields, seed/operation/callback provenance and
promoting the abs lookalike. All 483 public checks pass. Canonical totals are
3,268 resolved (919 authored, 1,774 library, 575 compiler), with 1,083 pending.
Exact/source/mapping remains 60 / 9,883 bytes; recorded authored extents remain
872 / 1,952,956 bytes. One final no-auth public HTTPS MCP acceptance replays
R129 and the complete retained R128/runtime/compiler/game/import/layout chain,
all authored extents, project attestation, progress freshness, 483 tests and
git diff whitespace. All 60 exact units cold-replay across eleven objects.
Investigation and intermediate checks are local. Private evidence stays
untracked; target, database, shared tools and game source/headers are unchanged.

## R130 — Complete vector construction and multi-entry math parents

R130 resolves all six handoff candidates and eight necessary existing dependencies:
eleven complete library primaries / 2,511 bytes / 99 typed fields, plus three
existing interior entries / 644 overlapping bytes. Replay
`scripts/repo-python scripts/verify-vector-math-parent-origins.py`; the manifest
is `config/vector-math-parent-origin-evidence.json`. This is origin evidence,
with no new source, mapped function or exact unit. Source associations identify
hash-pinned libcmt.lib definitions; they do not recover executable debug names.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `??_L@YGXPAXIHP6EX0@Z1@Z` | `0x00641C78` | 98 | 4 |
| `__handle_qnan2` | `0x00647362` | 95 | 4 |
| `__except2` | `0x00647479` | 201 | 9 |
| `_log10` | `0x00641FD0` | 63 | 2 |
| `_ceil` | `0x00642120` | 64 | 3 |
| `__CIlog10_pentium4` | `0x00648140` | 644 | 21 |
| `___libm_error_support` | `0x006485D7` | 654 | 28 |
| `__ceil_default` | `0x00648865` | 211 | 9 |
| `__powhlp` | `0x0064E81E` | 354 | 15 |
| `__d_inttype` | `0x0064E7B0` | 110 | 4 |
| `__frnd` | `0x0065151B` | 17 | 0 |

**Target and source extents.** Ten primaries retain their own full COFF AUX
extents. The vector constructor lacks a function-definition AUX record; its
sole global function owns a complete 98-byte executable/readable/non-writable
section. All source definitions and four fields are verified. Its provisional
74-byte prefix expands through the actual local cleanup at +74, including the
normal finally call and exceptional unwind. The existing 24-byte cleanup
`0x00641CC2` binds actual source label `$L322`, the full twelve-byte scope at
`0x00660F00`, and independently replayed 94-byte ArrayUnwind. It gains no
standalone function name, source or exact bytes.

The mathematical prefixes are accepted only after comparing their entire
emitted code sections, every complete constituent AUX body and all alignment.
The log10 section is 336 bytes: C entry / 63, source-emitted NOP / 1,
`__CIlog10` / 59 and `__CIlog10_default` / 213. The vendor alignment marker
`_$$$00002` has a zero-length AUX; it is not invented as a one-byte function.
The default body includes actual global entry `__log10_default` at +20.
The complete ceil section is 285 bytes: C entry / 64 and SSE body
`__ceil_pentium4` / 221. Both entire sections and all eighteen/ten fields replay
before the canonical C extents are reconciled from provisional 152/285 to
own-AUX 63/64. No prefix-only match earns origin. The target FID cos association
at `0x00641FD0` is rejected; the actual whole LOG10 data definition at
`0x0066FF00` and full shared code identify the log10 source family.

Whole alternatives retain distinguishing evidence: atan / 282 has 74
non-field differences, log / 336 has three, modf / 328 has 223, and floor / 289
has 33. Equal-shaped C prefixes cannot substitute for complete source bodies.
Their fields remain excluded only for this negative diagnostic comparison;
accepted source bodies compare every typed field against independent actual
code/data provenance.

**Shared entries and ABI.** The log10 SSE intrinsic expands from 24 provisional
bytes to its own complete 644-byte AUX, including all computation and error
paths. Existing C entry `0x00648158` / 6 binds global `__log10_pentium4` at +24.
The existing unnamed 614-byte core `0x0064815E` starts at +30: the intrinsic's
actual same-section call at +17 targets it, and the six-byte MOVLPD C-entry
instruction falls through to it. No source symbol is invented for this core.
Both entries retain blank proposed names and overlap adds no standalone bytes.
All intra-body branch destinations and all external typed/shared transfers
must reach instruction starts in complete defining owners.

The vector constructor uses ECX as the element receiver, callback at EBP+20,
signed count at EBP+16 and stride at EBP+12. Its exceptional cleanup passes the
current element pointer, completed-element count and separate incoming destructor
at EBP+24 to reverse unwind; normal completion suppresses that work. RET 20
retains its five-argument stdcall protocol. Arbitrary incoming callbacks and
original game element types remain unknown. Qnan2 retains both double operands
at EBP+12/+20 and the control word at +28. Except2 retains operands +16/+24,
result +32 and control word +40, including every mask/raise/errno/restoration
path. Their full exception/name/default-handler graph is retained through R129.

**Dependency closure.** Nine complete auxiliary bodies / 2,723 bytes / 51 fields
include both log10 intrinsic/default entries, the ceil SSE body, fast_exit,
complete x87 primitives / 215, exponential dispatch / 519, safe_fdivr / 21,
fdiv_main_routine / 279 and adj_fdiv_r / 1,183. These unlisted source controls
do not invent inventory candidates. The existing seven-byte `__rtchsifneg`
entry `0x00646B43` retains its original R127 acceptance at primitive +208;
it is replayed without being counted again. Twenty-one independent complete
anchors / 2,430 bytes / 57 fields retain their historical origins and the full
R129/runtime/compiler/game/import chain.

Twenty-nine whole defining data sections / 3,133 bytes / 70 typed fields
include the complete 2,336-byte log10 coefficient carrier, 72-byte ceil constants,
full literals, scope, cookie, fast flags and initialized default callback.
`__pmatherr` at `0x0067064C` contains the actual DIR32 pointer to complete
three-byte `__matherr` at `0x006506C2`; it is not null loader state. All three
indirect libm error calls use that slot. Later installed callbacks remain
unknown. The full 90-byte infinity/EXP carrier has four code pointers and
requires the complete exponential owner and pow helpers. The full 352-byte
fdiv carrier retains all 64 DIR32 dispatch entries to actual labels inside
complete adj_fdiv_r; the safe wrapper's unrelocated same-section call retains
complete fdiv_main_routine. A ten-byte infinity or 21-byte safe-wrapper hit
alone is insufficient. One four-byte SSE2-enable COMMON has its complete source
definition and actual loader zero-fill geometry; no guessed initial value or
truncated table substitutes for the defining storage.

**Compiler observations and limits.** Natural VC7VectorMathParentLayout
cold-builds thirteen DWORDs / 52 bytes from complete pinned vendor/SDK types:
pointer/int / 4, double / 8, exception / 32 with both operand/result offsets,
FP80 / 10, member pointer / 4 and SEH results. Its complete synthetic class
emits a thirteen-byte member-call control with ECX receiver and RET 8. No
incomplete game owner is instantiated or embedded. Explicit probe flags and
VC7.1 build 3077 are reproducibility settings, not an executable-wide compiler
profile. Vendor assembly COFF bodies supply archive origin evidence; no
assembly, target byte arrays or conditional matching bodies are added to game
source.

Thirty-four regression checks reject missing whole carriers/default bodies,
false alignment credit, truncated tables, wrong callback/operand/control-word
slots, invented shared symbols, lost COMMON/default-handler bindings and
recounting the R127 entry. All 517 public checks pass. Canonical totals are
3,282 resolved (919 authored, 1,788 library, 575 compiler), with 1,069 pending.
Exact/source/mapping remains 60 / 9,883 bytes; recorded authored extents remain
872 / 1,952,956 bytes and the provisional denominator remains 1,965,299.
Local investigation and verification are followed by one final no-auth public
HTTPS MCP acceptance covering R130 and retained graphs, all authored extents,
project attestation, progress freshness, 517 tests and whitespace checks.
All 60 exact units cold-replay across eleven objects. Private evidence stays
untracked; target, private database, shared tools and game source are preserved.

## R131 — Complete localtime, time-zone and environment dependency graph

R131 resolves all six handoff candidates and fourteen necessary existing
entries: seventeen complete library primaries / 4,384 bytes / 237 typed fields
and three existing nine-byte cleanup entries. Replay
`scripts/repo-python scripts/verify-time-zone-origins.py`; the manifest is
`config/time-zone-origin-evidence.json`. No source, mapping or exact credit is
added. Source associations come from the hash-pinned libcmt.lib archive, not
from Ghidra names or the presence of reviewed callees.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `_localtime` | `0x0064197E` | 384 | 13 |
| `__tzset_lk` | `0x00647778` | 680 | 62 |
| `__isindst_lk` | `0x00647BD8` | 391 | 30 |
| `___tzset` | `0x00647D5F` | 76 | 9 |
| `__isindst` | `0x00647DE0` | 62 | 6 |
| `_gmtime` | `0x00647E1E` | 263 | 5 |
| `_cvtdate` | `0x00647A20` | 440 | 15 |
| `__getenv_lk` | `0x006506C5` | 129 | 8 |
| `___wtomb_environ` | `0x00653816` | 144 | 6 |
| `__mbsnbicoll` | `0x006537C8` | 78 | 4 |
| `___crtsetenv` | `0x00654660` | 469 | 27 |
| `___crtCompareStringA` | `0x0065422E` | 900 | 38 |
| `__mbschr` | `0x0065497E` | 123 | 4 |
| `_copy_environ` | `0x006545FF` | 97 | 3 |
| `_findenv` | `0x006545B2` | 77 | 4 |
| `_strncnt` | `0x00654212` | 28 | 0 |
| `__strdup` | `0x00642AD2` | 43 | 3 |

**Complete extents and shared cleanup.** Every primary retains its whole own
COFF AUX extent. The two lock wrappers expand from provisional 67/53 bytes to
76/62, including all finally instructions. Their existing cleanup entries
`0x00647DA2` and `0x00647E15` bind actual source labels at +67/+53. The existing
`0x00647993` entry is the time-zone reader's normal cleanup subentry at +539;
its scope points to the complete exceptional entry at +534, including the
five-byte frame adjustment before that subentry. The verifier preserves both
actual source labels, complete parents and instruction starts. All three
names remain blank; overlapping cleanup bytes gain no standalone credit.

The old 336-byte `0x0065497E` span merges different source owners. Reconciliation
retains every old byte: its own MBCS search AUX / 123, seven observed INT3
alignment bytes, and an entire separate strchr section / 206. That section
contains a sixteen-byte static success entry at `0x00654A00` and `_strchr` /
190 at `0x00654A10`; both have actual complete AUX records. The sixteen-byte
AUX includes eleven source-emitted alignment bytes after RET. The strchr
conditional branch reaches the preceding success entry in the same defining
section, so comparing only the 190-byte entry is insufficient. All 206 source
bytes replay. Only after that coverage is established is the canonical MBCS
extent reconciled to 123. Neither unlisted source control becomes an invented
inventory candidate, and the seven target alignment bytes earn no credit.

**Target-observed time and storage protocol.** Localtime rejects negative
signed epoch values and preserves both paths around the actual three-day
margins 259,200 and 2,147,224,447. It retains timezone and DST adjustments,
near-limit updates to the existing tm fields and actual tm_isdst at +32.
Gmtime uses the getptd return's +68 buffer slot, allocates a complete 36-byte tm,
and falls back to its whole static tm when allocation fails. All calendar,
leap-year, month/day, weekday and time-of-day arithmetic stays inside its full
263-byte AUX; both complete thirteen-element month tables replay together.
The original time representation is the observed 32-bit signed CRT model;
this is not a claim about current operating-system time APIs.

The initializer uses time lock 6, while its TZ environment read uses lock 7.
The first-time flag, cached lastTZ pointer, Windows API path, environment path,
failed allocations/conversions, cache invalidation, default names and both
cleanup paths remain intact. The transition converter and DST tester retain
both start/end records, year caching, relative/absolute Windows transition
forms and both orderings of the start/end dates. The full Windows timezone
object is 172 bytes; SYSTEMTIME is sixteen with WORD fields. No Japanese-zone
value is inferred merely from the executable's language. Writable values,
OS/environment inputs and the runtime locale remain unknown.

**Environment, NLS and API closure.** Getenv's conversion branch invokes the
entire wide-to-multibyte environment converter, which in turn reaches the
whole crtsetenv parent and its real local copy/find helpers. Allocation,
duplication, environment-vector updates, failures and SetEnvironmentVariableA
remain source-typed. Name comparison reaches complete mbsnbicoll and the
900-byte crtCompareStringA, including ANSI/wide API selection, both conversions,
stack/heap allocation, both stack-overflow filters/handlers and cleanup. All
raw IAT fields bind their actual descriptor names; register-indirect calls
retain complete source instructions and the actual loaded IAT value. The
existing chkstk owner retains its source-defined alloca_probe alias; an alias
without its own function AUX is not treated as a separate function.

Two complete vendor alternatives remain explicit. Copy_environ / 97 also
has a wide-family source body with equal non-field bytes and a different
duplication symbol. Strncnt / 28 occurs in another complete NLS member. The
selected narrow environment/CompareStringA parents actually define and call
their own local symbols; all selected fields bind complete defining owners.
Equivalent shapes alone do not identify a source unit, original spelling or
folding. Natural narrow/wide duplication call controls both emit seventeen
bytes, retaining distinct REL32 symbols `__strdup`/`__wcsdup`; symbolic calls
cannot be merged merely because their unlinked bodies are equal.

Fifteen whole defining data sections / 679 bytes / nine typed fields include
all time-zone defaults and name pointers / 152, the full timezone/cache/once
BSS carrier / 184, both transition records / 24, both month tables / 104,
static tm / 36, complete environment and locale carriers, cookie, literal TZ,
NLS flag and four full SEH scope definitions. The three time-zone scopes are
twelve bytes each; CompareStringA's complete two-record scope is 24 with all
four filter/handler pointers. Both environment-initialized and MBCS-info
COMMON definitions retain their full four-byte declarations and loader
zero-fill geometry. No table or writable-carrier prefix substitutes for a
complete defining object. Twenty-one independent anchors / 2,607 bytes / 108
fields retain historical origins and the entire R130/runtime/compiler/game
chain; no new origin is inherited from those anchors.

**Compiler observations and limits.** Natural VC7TimeZoneLayout cold-builds
53 DWORDs / 212 bytes using complete pinned CRT/SDK types and a synthetic
three-int transition control. It verifies time_t/pointer/int/long / 4,
wchar_t / 2, tm / 36 and all nine fields, thread / 140 with gmtime/MBCS slots
+68/+96, complete MBCS info / 544, SYSTEMTIME / 16, timezone / 172 and all
relevant offsets, transition / 12, locks and epoch constants. Eleven complete
vendor source files and nine headers are hash-pinned privately by the manifest.
The synthetic transition model is a layout control, not a recovered game
owner. No incomplete game object is instantiated or embedded. Explicit probe
flags and VC7.1 build 3077 are reproducibility settings; no executable-wide
compiler profile is inferred. Vendor strchr assembly COFF is archive evidence;
no assembly or target-byte arrays are added to game source.

Thirty-eight regression checks reject truncated parents/scopes/tables,
misbound cleanup or COMMON, lost thread/time/SDK layouts, conflated narrow/wide
calls, wrong local source parents and discarding/recounting the old MBCS span.
All 555 public checks pass. Canonical totals are 3,302 resolved (919 authored,
1,808 library, 575 compiler), with 1,049 pending. Exact/source/mapping remains
60 / 9,883 bytes; recorded authored extents remain 872 / 1,952,956 bytes and
the provisional denominator remains 1,965,299. One final no-auth public HTTPS
MCP acceptance replays R131 and retained graphs, all authored extents, project
attestation, progress freshness, 555 tests and whitespace checks. All 60 exact
units cold-replay across eleven objects. Investigation and intermediate checks
are local; private evidence stays untracked and shared tools remain read-only.

## R132 — Complete low-level file I/O, handle locking and error graph

R132 resolves all six handoff roots and twelve necessary existing entries:
fourteen complete library primaries / 2,338 bytes / 109 typed fields and four
existing cleanup entries / 33 overlapping bytes. Replay
`scripts/repo-python scripts/verify-low-io-origins.py`; the manifest is
`config/low-io-origin-evidence.json`. Every primary uses its complete own COFF
AUX from the hash-pinned libcmt.lib. No source, mapping or exact credit is added.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__lseek_lk` | `0x0064EC83` | 116 | 6 |
| `__lseek` | `0x0064ECF7` | 171 | 12 |
| `__lseeki64_lk` | `0x006523AC` | 131 | 6 |
| `__write` | `0x0064EF70` | 171 | 12 |
| `__read` | `0x00653A81` | 171 | 12 |
| `__close_lk` | `0x00654835` | 131 | 9 |
| `__get_osfhandle` | `0x00652066` | 65 | 4 |
| `__dosmaperr` | `0x00647FAA` | 115 | 7 |
| `__lock_fhandle` | `0x006520A7` | 160 | 10 |
| `___doserrno` | `0x00647FA1` | 9 | 1 |
| `__unlock_fhandle` | `0x00652147` | 34 | 2 |
| `__write_lk` | `0x0064EDA2` | 462 | 13 |
| `__read_lk` | `0x006538A6` | 475 | 9 |
| `__free_osfhnd` | `0x00651FE7` | 127 | 6 |

**Complete extent and EH observations.** The lock initializer expands the old
148-byte provisional span to its entire 160-byte AUX. Its exceptional cleanup
includes three stack-adjustment bytes at +148 before the existing nine-byte
entry `0x0065213E` / +151 / `$L20250`. The three 171-byte lseek/write/read
wrappers each retain both error paths, the normal return and the cleanup at
+135. Their existing eight-byte entries are `0x0064ED7E` / `$L20662`,
`0x0064EFF7` / `$L20376` and `0x00653B08` / `$L20375`. The complete twelve-byte
scopes point at +132, before the three-byte stack adjustment; the scope entry
and normal cleanup subentry must remain distinct. All cleanup names stay
blank. Their bytes overlap full owners and gain no standalone exact credit.
The verifier reads back actual source definitions, complete target instructions,
all branches/exits and every typed field. Library children alone confer no
origin on remaining stream parents.

**Target operations and ABI.** Handle validation uses unsigned bounds against
_nhandle, group selection by shift 5 / mask 31, and 36-byte ioinfo stride. The
FOPEN flag lives at +4, pipech at +5, lock initialization at +8 and the complete
24-byte CRITICAL_SECTION at +12. Lock creation preserves its double check,
lock-table guard, failure return, finally release and eventual handle lock.
Unlock uses the same actual critical-section field. The complete thread object
is 140 bytes; errno and OS errno occupy +8/+12. The nine-byte OS-errno accessor
returns the actual getptd result plus twelve.

Both seeks bind actual SetFilePointer and GetLastError IAT slots, retain the
all-ones low-word sentinel plus OS-error check, and clear FEOFLAG on success.
The 64-bit seek uses a truthful eight-byte low/high union, passes the high-word
address to SetFilePointer and returns EDX:EAX. The complete write parent retains
append seek, text CRLF conversion, binary write, short writes, device/control-Z
and error mapping. The read parent retains pipe lookahead, CRLF translation,
control-Z EOF, broken-pipe behavior, one-byte lookahead/seek restoration and
all failure/success paths. Close preserves stdout/stderr handle alias handling,
CloseHandle failure, handle release, flag clearing and OS-error mapping. The
free-handle helper resets standard handles only for application type 1;
the observed target has initial GUI application type 2. Runtime handles,
buffer contents and file/device state remain unknown; no game I/O is executed.

**Whole data and definition provenance.** Seven complete defining sections /
420 bytes / five DIR32 fields retain all four scopes / 48, the whole 45-entry
OS-error map / 360, cookie / 4 and application-state/exit-pointer carrier / 8.
The ordered error map retains both occurrences of OS code 6, including the
second source entry whose comment says 124. The source definition and target
bytes govern acceptance; the table is not silently repaired. Both access-error
and execution-error fallback ranges and default EINVAL stay in the whole
115-byte error mapper. The complete source COMMON declarations retain all
64 handle-array pointers / 256 and nhandle / 4 in their actual writable loader
zero-fill region. Runtime allocated arrays are not guessed from initial zeros.

Application state has five strong archive definitions. The retained full
469-byte GUI entry at `0x0064232C` independently binds R126's wincrt0 source
member. That same member defines the entire two-word carrier, with app_type at
+4 and a typed exit pointer at +0 to the independently reviewed __exit owner.
All five actual definitions remain recorded and are read back from the whole
archive. Selection does not use the first masked match and does not establish
original source spelling, source-unit identity or folding. Eleven complete
anchors / 1,011 bytes / 72 fields retain independent origins; their complete
code/data/EH dependencies replay through the full R131 chain, including R125
I/O initialization. No new origin is inherited from these anchors.

**Compiler observations and limits.** Natural VC7LowIoLayout cold-builds
48 DWORDs / 192 bytes with complete pinned CRT/SDK types. It verifies pointer,
int and long / 4, int64 / 8, ioinfo / 36 and all actual fields, critical section
/ 24, handle geometry, whole pointer/group storage sizes, thread offsets,
error-entry layout and file/error/standard-handle constants. The independent
11-byte cdecl file-offset identity body loads low/high into EAX/EDX and returns
without callee argument cleanup. Its full AUX and all instructions replay.
The offset union and error-entry pair are synthetic layout controls, not
reconstructed game objects. Nine vendor source files and eight headers remain
hash-pinned. Probe flags and VC7.1 build 3077 are reproducibility settings;
no executable-wide compiler profile is inferred.

Thirty-three regression checks reject truncated owners, conflated cleanup
entries, incomplete error/handle/application carriers, wrong thread/SDK/int64
layouts, missing text/EOF policies and arbitrary application-state definitions.
All 588 public checks pass. Canonical totals are 3,320 resolved (919 authored,
1,826 library, 575 compiler), with 1,031 pending. Exact/source/mapping remains
60 / 9,883 bytes; recorded authored extents remain 872 / 1,952,956 bytes and
the provisional denominator remains 1,965,299. One final no-auth public HTTPS
MCP acceptance replays R132 and retained graphs, authored extents, project
attestation, progress freshness, 588 tests and whitespace checks. All 60 exact
units cold-replay across eleven objects. Investigation and intermediate checks
use local tools; private evidence stays untracked and shared tools read-only.

## R133 — Complete stream buffering, character pushback and close wrapper

R133 resolves all six stream buffer/close handoff roots and one existing cleanup
entry: six complete library primaries / 879 bytes / 29 typed fields and an
eight-byte overlapping cleanup. Replay
`scripts/repo-python scripts/verify-stream-buffer-origins.py`; the whole manifest
is `config/stream-buffer-origin-evidence.json`. Every primary retains its entire
own COFF AUX from the hash-pinned libcmt.lib. No source, mapping or exact credit
is added. Reviewed low-level callees alone establish none of these origins.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__filbuf` | `0x0065163C` | 225 | 4 |
| `__flsbuf` | `0x006443FE` | 281 | 9 |
| `__getbuf` | `0x0064F01B` | 68 | 2 |
| `__isatty` | `0x0064F05F` | 42 | 2 |
| `__ungetc_lk` | `0x0065171D` | 108 | 1 |
| `__close` | `0x006548B8` | 155 | 11 |

**Target behavior and complete boundaries.** The refill parent retains stream
access/string checks, allocation/reuse, read count, EOF/error distinction,
control-Z policy, small-buffer restoration, unsigned narrow-byte return and
both complete returns. Its safe-handle branch uses the entire badioinfo object
when FILE._file is -1. The flush parent retains read-to-write switching only at
EOF, stdout/stderr device handling, buffer allocation, buffered write, append
seek for an empty buffer, single-character output, short-write error and the
unsigned-byte return. Both paths bind the actual complete R132 read/write/seek
parents. Neither formatting caller gains origin through this association.

Getbuf increments the actual cflush state, requests 4096 bytes from the complete
reviewed malloc wrapper and preserves its allocation-failure branch. The
fallback points at FILE._charbuf / +20, with runtime buffer size two; the
underlying integer field occupies four bytes. Isatty uses unsigned bounds,
shift 5 / mask 31 and 36-byte handle stride. It returns raw FDEV / 0x40 or zero,
not a normalized boolean and not an errno-setting invalid-handle failure.
Pushback rejects EOF and incompatible stream modes, allocates when needed,
preserves buffer-limit checks, compares and rolls back pointers for a string
stream without writing that source buffer, and writes the character only on
the ordinary-buffer branch. Success increments count, clears EOF, sets READ
and returns the unsigned byte.

The whole 155-byte close wrapper retains validation, locking, second FOPEN
check, close_lk call, error cases, finally cleanup and complete SEH epilog.
Its existing eight-byte cleanup `0x0065492F` is the actual `$L20316` label at
+119; the complete twelve-byte scope points at `$L20314` / +116, including
three bytes that reload the handle before the label. Both source definitions
and actual instruction starts replay. The initial invalid-handle branch clears
OS errno; the post-lock FOPEN failure sets EBADF and preserves the distinct
source behavior. Cleanup names remain blank and overlapping bytes earn no
standalone source or exact credit. Every branch, exit, indirect instruction,
code/data/EH field and direct external edge is checked against the full source.

**Whole data, loader and retained graph.** Four complete defining sections /
692 bytes / three DIR32 fields comprise badioinfo / 36, all twenty FILE records
/ 640, cflush / 4 and the close scope / 12. Both stdin pointer/base fields bind
the entire input-buffer COMMON / 4096. Stdout/stderr comparisons bind actual
__iob addends +32/+64. The source's stale stderr index comment does not override
the observed third record / index two. Initial FILE flags, handles, buffer size,
pointers and all seventeen unused records replay; runtime stream state remains
unknown. Badioinfo preserves handle -1, FTEXT / 128, pipe lookahead / 10 and
complete lock/padding storage. Cflush is a full defining BSS section, correcting
the prior diagnostic COMMON association; its actual loader zero-fill geometry
replays. The source explains its link retention of stdio termination, while
complete initializer/terminator registrations retain R125 evidence.

Three complete COMMON declarations / 4356 bytes retain the input buffer / 4096,
all 64 handle-array pointers / 256 and nhandle / 4. All loader-zero spans remain
in the actual writable PE region; runtime allocated handle arrays are unknown.
Eleven complete anchors / 950 bytes / 62 fields retain independent origins and
replay the entire R132 code/data/API/EH/ABI chain, including R125 initialization.
These anchors and their existing cleanup entries receive no new origin credit.
No table prefix, guessed pointer or shape-only library name replaces complete
source definition and actual target binding.

**Compiler observations and limits.** Natural VC7StreamBufferLayout cold-builds
53 DWORDs / 212 bytes with complete pinned FILE / 32 and all eight fields,
20-record array / 640, char / 1, wchar_t / 2, buffer sizes, flags, complete
ioinfo / 36, critical section / 24, thread / 140 and error slots +8/+12. Its
13-byte narrow-byte load control uses MOVZX from one byte through FILE._ptr;
its 21-byte pushback call control preserves the actual __ungetc_lk REL32
symbol, parameter order and eight-byte caller cleanup. Both whole own AUX
bodies and every instruction replay. Eight vendor source files and eight
headers remain hash-pinned. These controls do not instantiate any incomplete
game owner or earn reconstruction exact credit. Explicit flags and VC7.1 build
3077 remain reproducibility settings, without an executable-wide profile claim.

Thirty-three regression checks reject truncated source owners, misbound cleanup,
incomplete FILE/input/handle/BSS objects, lost stdin fields or stdout/stderr
addends, wide-byte substitutions, incorrect pushback ABI and changed initial
records. All 621 public checks pass. Canonical totals are 3,327 resolved
(919 authored, 1,833 library, 575 compiler), with 1,024 pending. Exact/source/
mapping remains 60 / 9,883 bytes; recorded authored extents remain 872 /
1,952,956 bytes and the provisional denominator remains 1,965,299. One final
no-auth public HTTPS MCP acceptance replays R133 and retained graphs, authored
extents, target/project attestation, progress freshness, 621 tests and whitespace
checks. All 60 exact units cold-replay across eleven objects. Investigation
and intermediate verification use local tools; private evidence stays
untracked and shared tools remain read-only.

## R134 — Complete output formatting, dispatch and conversion graph

R134 resolves the six output-format handoff roots and four required existing
callee candidates: ten complete library primaries / 2629 bytes / 50 typed
fields. Replay `scripts/repo-python scripts/verify-output-format-origins.py`;
the manifest is `config/output-format-origin-evidence.json`. Every source owner
retains its entire own COFF AUX from the hash-pinned libcmt.lib, including data
inside that extent. No source, mapping or exact reconstruction credit is added.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `_sprintf` | `0x006404F0` | 88 | 2 |
| `__scprintf` | `0x00640548` | 49 | 1 |
| `__snprintf` | `0x0064254D` | 87 | 2 |
| `__vsnprintf` | `0x006425C3` | 86 | 2 |
| `__output` | `0x006445C4` | 2042 | 34 |
| `_write_char` | `0x00644517` | 51 | 1 |
| `_write_string` | `0x0064456E` | 55 | 1 |
| `_write_multi_char` | `0x0064454A` | 36 | 1 |
| `_wctomb` | `0x0064F250` | 39 | 4 |
| `___wctomb_mt` | `0x0064F1F0` | 96 | 2 |

**Target behavior and boundaries.** The output owner is 2010 instruction bytes
plus its own 32-byte eight-entry DIR32 table at +2010 / `0x00644D9E`; its complete
extent ends at `0x00644DBD`. The former provisional 2010-byte ledger is expanded
to 2042. The actual unsigned state guard, EAX-times-four indirect jump, local
source table definition, all eight fields and all actual case instruction
starts replay. The table address is data, while its destinations are code
entries inside the complete source owner. No prefix or relocation mask earns
acceptance. All width, precision, flag, string, counted-string, integer, int64,
floating conversion, `%n`, error and return paths remain in the full comparison.

The four wrappers preserve the whole synthetic FILE setup and output call.
Sprintf uses the actual INT_MAX count and WRITE|STRG / 66 flags; bounded
wrappers retain the historic size_t-to-int count conversion and termination
attempt. They can exhaust the count without adding a terminator; modern snprintf
behavior is not substituted. Vsnprintf uses the actual pointer va_list. Scprintf
uses a null-base counting stream; both character and string helpers preserve
that fast path, while ordinary streams retain byte output and complete flsbuf
binding. Source-local helper spelling alone is insufficient: multiple archive
variants exist, and the actual defining output member selects the complete
51-/55-/36-byte bodies. The private optimized character call passes the byte in
AL, FILE in ECX and counter pointer in ESI. The source's local cdecl declaration
does not justify adding an external cdecl prototype for that register contract.
All helper returns retain zero callee stack cleanup.

Wctomb retains thread lookup, actual locale pointer comparison/update and the
complete three-argument conversion call. The converter preserves null-buffer
behavior, C-locale byte conversion, EILSEQ / 42 for an unrepresentable value,
and the actual WideCharToMultiByte IAT binding and default-character rejection.
Its complete source-defined thread locale object is 84 bytes, with codepage
+4, handle array +12, mb_cur_max +40 and pctype +72. The thread object is 140
bytes, with locale pointer +100. Runtime locale/codepage values remain unknown.

**Whole data and callback provenance.** Fifty-six complete defining sections /
2361 bytes / 68 fields retain the entire 89-byte combined character-class/state
lookup, both narrow/wide null-string pointers and literals, complete CTYPE
carrier / 1284, full default-locale carrier / 403, lconv / 56, C time locale /
184 and all recursively bound day/month/time strings. Signed-looking lookup
addends retain their actual 32-bit arithmetic. Defined BSS uses actual loader
zero-fill geometry. No guessed subobject prefix replaces the defining section.

The FP dispatch object at `0x00670120` is exactly six slots / 24 bytes. All six
initial image fields bind the complete R124 fatal stub. The complete R124
initializer's actual stores support the initialized view: cfltcvt, cropzeros,
fassign, forcdecpt, positive, cfltcvt again. Output uses slot offsets 0, 12 and
4. Both initial and initialized views replay; runtime execution/current slot
contents remain unknown. Cropzeros / 75, forcdecpt / 60 and positive / 26 are
three complete non-inventoried auxiliary controls / 161 bytes / five fields,
retaining R124 dependency evidence without inventing new candidates. Fifteen
complete independent anchors / 1195 bytes / 65 fields retain their origins.
The verifier replays the full R133 stream/handle graph and its complete retained
locale, FP, heap, security, import and initialization evidence. Game callers gain
no ownership from these library children.

**Compiler observations and limits.** Two independent natural probes preserve
real vendor types: a 136-byte format layout and a 52-byte SDK/thread/locale
layout. The vendor DOUBLE struct and SDK DOUBLE typedef are kept in separate
translation units, with no macro substitution or ABI misdeclaration. Controls
retain FILE / 32, va_list / 4, complete DOUBLE and LONGDOUBLE carriers / 8,
signed-short counted-string fields / 8 and conversion buffer / 512. The full
53-byte variadic int64 control advances the argument pointer by eight and loads
EDX:EAX; the full 25-byte typed PF0 control pushes five arguments and removes
20 bytes in the caller. Six complete vendor source files and pinned headers
replay. Build 3077 and explicit flags remain reproducibility settings, without
an executable-wide compiler claim or an incomplete game-owner layout.

Thirty-eight regression checks reject truncated output owners, discarded or
misclassified tables, misbound cases, invented auxiliary origin credit, missing
FP slots/initializer stores, incomplete locale/CTYPE/null data, incorrect natural
layouts and changed variadic/PF0 calling contracts. All 659 public checks pass.
Canonical totals are 3337 resolved (919 authored, 1843 library, 575 compiler),
with 1014 pending. Exact/source/mapping remains 60 / 9883 bytes; recorded authored
extents remain 872 / 1952956 bytes and the provisional denominator is 1965299.
One final no-auth public HTTPS MCP acceptance replays R134 and retained graphs,
authored extents, target/project attestation, progress freshness, 659 tests and
whitespace checks. All 60 exact units cold-replay across eleven objects. Local
tools perform investigation and intermediate verification; private evidence
stays untracked and shared tools remain read-only.

## R135 — Complete input scanning, multibyte and NLS query graph

R135 resolves all six input-format/locale handoff roots and four required
existing dependencies: ten complete library primaries / 4801 bytes / 129 typed
fields. Replay `scripts/repo-python scripts/verify-input-format-origins.py`;
the manifest is `config/input-format-origin-evidence.json`. Every primary
retains its entire own AUX from the hash-pinned libcmt.lib, with all source,
code/data/API/SEH fields and full control flow compared. No source, mapping or
exact reconstruction credit is added. Reviewed children alone prove no parent.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `_sscanf` | `0x00642A2D` | 52 | 2 |
| `__input` | `0x0064993C` | 3452 | 60 |
| `__inc` | `0x006498FC` | 22 | 1 |
| `___mbtowc_mt` | `0x006517CE` | 192 | 3 |
| `_mbtowc` | `0x0065188E` | 43 | 4 |
| `___getlocaleinfo` | `0x006519EE` | 295 | 15 |
| `_isxdigit` | `0x0064283A` | 63 | 4 |
| `_isspace` | `0x00642879` | 58 | 4 |
| `___crtGetLocaleInfoW` | `0x00653B2C` | 304 | 18 |
| `___crtGetLocaleInfoA` | `0x00653C5C` | 320 | 18 |

**Target behavior and complete boundaries.** Sscanf constructs a local stack
FILE / 32 with READ|STRG|MYBUF / 73, original string pointer/base, complete
strlen-derived count and actual pointer va_list at EBP+16. The stale source
comment about static storage does not override the declaration or emitted
stack object. Its entire input call and return replay. The source-local inc
helper belongs to the same actual defining input member, passes FILE in EDX,
loads an unsigned byte on its fast path and calls the full R133 filbuf on
exhaustion. Its private optimized register contract is preserved without
inventing an external cdecl declaration. Both returns have zero callee cleanup.

The complete 3452-byte input owner retains width/length/suppression policies,
whitespace, literal matching, character/string/scanset conversion, decimal,
hex/octal/int64 parsing, floating text, `%n`, pushback, matched-versus-assigned
EOF policy and every final exit. It contains a four-byte exception filter and
its real handler, with no separate inventory candidate or new origin credit.
The narrow scanset is 32 bytes / 256 bits, allocated on the stack with real
resetstkoflw and heap fallback after an exception; fallback allocation failure
and final conditional free remain inside the full extent. Float text storage
is `_CVTBUFSIZE + 1` / 350 bytes, with width limit 349, distinct from the prior
output buffer / 512. The int64 multiplication binds full R006 allmul / 52,
including both actual RET 16 exits. No instruction prefix or masked field earns
acceptance; no game caller gains ownership from this association.

Mbtowc retains thread lookup / locale update and the full four-argument worker
call. The worker handles null/zero-length input, null-character output, optional
destination, C-locale unsigned-byte conversion, lead-byte classification,
signed count comparisons and all actual MultiByteToWideChar calls. Flags are
MB_PRECOMPOSED|MB_ERR_INVALID_CHARS / 9; failures retain the source's distinct
lead-byte validation policy and EILSEQ / 42. Isxdigit/isspace retain actual
thread locale and complete isctype worker bindings, including the single-byte
raw classification masks / 128 and 8. Runtime codepage and allocated locale
state remain unknown.

Getlocaleinfo retains its full string and integer query branches. The string
branch starts with 128 bytes, checks ERROR_INSUFFICIENT_BUFFER / 122, queries
size, allocates a temporary when required, allocates the returned string,
binds the complete strncpy / 292 and frees only its owned temporary on every
success/failure path. The integer branch retains all four wide characters /
eight bytes, low-byte extraction, digit tests and unsigned-byte accumulation.
Both complete A/W wrappers probe the real GetLocaleInfoW API, distinguish
ERROR_CALL_NOT_IMPLEMENTED / 120, retain separate flavor caches, use the
source's default-codepage fallback, and preserve direct and converted queries,
size-only paths, SEH stack allocation, heap fallback and cleanup. Their actual
GetLocaleInfoA/W and multibyte/wide conversion IAT identities replay. API
availability, cached runtime flavors and returned locale values are unknown.

**Whole data, SEH and callback provenance.** Fifty-nine complete defining
sections / 2327 bytes / 72 fields retain the full mb_cur_max/decimal carrier /
12, complete CTYPE / 1284, default locale / 403, full C time/lconv objects and
all recursively bound literals. Complete source-defined BSS retains integer
query storage / 8, distinct W/A flavor caches / 4 each and full locale-handle
carrier / 32, with actual writable PE loader zero-fill geometry.

Three whole twelve-byte scope records retain enclosing level -1 and both actual
filter/handler code pointers. Input's entries are +1578/+1582, W query's are
+184/+188 and A query's are +175/+179. Every filter's four bytes return one;
each handler restores ESP from EBP-24 and calls the real full R123 stack reset.
Source labels, full parent extents and actual instruction starts replay; none
are promoted into invented standalone candidates. All direct source branches,
full returns and indirect calls remain in the complete comparison.

The full six-slot FP table / 24 retains initial fatal stubs and the actual R124
initializer's six supported callback stores. Input's one actual indirect call
uses slot +8 / fassign. All six owners replay; current runtime slot contents
remain unknown. Three non-inventoried FP helper controls / 161 bytes / five
fields retain R124/R134 evidence without new candidate credit. Twenty-three
complete independent anchors / 2021 bytes / 71 fields preserve prior origins.
The verifier replays the entire R134 output/FP graph, R133 streams, R132 handles
and retained locale, heap, security, import and initialization chains.

**Compiler observations and limits.** Two independent natural probes preserve
real types: format / 136 and SDK/thread/locale / 112. Controls verify FILE / 32,
va_list and destination pointers / 4, wchar_t / 2, locale / 84, thread / 140,
actual locale pointer/field offsets, 32-byte scanset and 349/350 float limits.
The full 44-byte variadic pointer control advances by four; the full 26-byte
int64 multiply control emits the actual allmul symbol and its callee cleanup
contract. A full 21-byte typed PF2 control removes twelve caller bytes. The
full 42-byte SDK API control uses the real stdcall import, six arguments and
flags / 9. Vendor FP and SDK DOUBLE contexts remain separate. Nine complete
vendor source files and pinned headers replay. VC7.1 build 3077 and explicit
flags are reproducibility settings, without a global executable compiler claim.

Forty-three regression checks reject truncated owners, invented filter/auxiliary
credit, lost or misbound scope entries, wrong filter/handler execution, incomplete
locale/CTYPE/BSS/FP carriers, conflated NLS caches, unsupported current runtime
claims, incorrect scanset/float/ABI layouts and lost API/error policy. All 702
public checks pass. Canonical totals are 3347 resolved (919 authored, 1853
library, 575 compiler), with 1004 pending. Exact/source/mapping remains 60 /
9883 bytes; recorded authored extents remain 872 / 1952956 bytes and the
provisional denominator is 1965299. One final no-auth public HTTPS MCP request
replays R135 and retained graphs, authored extents, target/project attestation,
progress freshness, 702 tests and whitespace checks. All 60 exact units
cold-replay across eleven objects. Investigation and intermediate verification
use local tools; private evidence stays untracked and shared tools read-only.

## R136 — Complete locale construction, category and enumeration graph

R136 resolves all six locale-construction/category handoff roots and seventeen
required existing dependencies: 23 complete library primaries / 5949 bytes /
421 typed fields. Replay
`scripts/repo-python scripts/verify-locale-construction-origins.py`; its manifest
is `config/locale-construction-origin-evidence.json`. Every primary retains its
entire own AUX from the hash-pinned libcmt.lib. Complete source bodies, actual
code/data/API fields, branches and exits compare without differences. No source,
mapping or exact reconstruction credit is added. Accepted children alone prove
no parent origin.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__get_lc_time` | `0x0064C25F` | 871 | 46 |
| `___init_numeric` | `0x0064C847` | 461 | 39 |
| `___init_monetary` | `0x0064CB20` | 575 | 42 |
| `___init_ctype` | `0x0064CD5F` | 490 | 26 |
| `__expandlocale` | `0x00642EE5` | 348 | 24 |
| `__setlocale_set_cat` | `0x00643041` | 655 | 42 |
| `___get_qualified_locale` | `0x0064D853` | 437 | 38 |
| `___lc_lctostr` | `0x00642D9D` | 78 | 5 |
| `_TranslateName` | `0x0064D114` | 96 | 1 |
| `_GetLcidFromLangCountry` | `0x0064D778` | 134 | 16 |
| `_GetLcidFromLanguage` | `0x0064D7FE` | 85 | 11 |
| `_GetLcidFromCountry` | `0x0064D741` | 55 | 7 |
| `_GetLcidFromDefault` | `0x0064D174` | 26 | 4 |
| `_ProcessCodePage` | `0x0064D18E` | 118 | 9 |
| `__stricmp` | `0x00651B15` | 105 | 6 |
| `_GetPrimaryLen` | `0x0064D33A` | 29 | 0 |
| `_crtGetLocaleInfoA@16` | `0x0064D222` | 227 | 10 |
| `_LangCountryEnumProc@4` | `0x0064D45C` | 538 | 49 |
| `__strnicmp` | `0x00651B7E` | 127 | 6 |
| `_TestDefaultCountry` | `0x0064D204` | 30 | 1 |
| `_TestDefaultLanguage` | `0x0064D3EB` | 113 | 8 |
| `_LanguageEnumProc@4` | `0x0064D676` | 203 | 18 |
| `_CountryEnumProc@4` | `0x0064D357` | 148 | 13 |

**Target behavior and source ownership.** Time construction retains allocation,
all abbreviated/full weekday and month names, AM/PM and date/time strings,
locale/calendar fields, refcount initialization and complete failure cleanup.
Numeric and monetary initialization retain the complete lconv / 48, string and
integer queries, source-inlined grouping conversion, allocation/refcounts,
replacement and rollback paths. Grouping converts ASCII digits and semicolons
according to the original source. Complete R122 freeing owners remain separate
independent anchors; no runtime allocation or current locale value is assumed.

CTYPE initialization retains GetCPInfo, the complete CPINFO / 20, lead-byte
ranges, the actual 768-byte classification allocation, 257-byte character
buffer, EOF slot, all 256 classification inputs, lead-byte marker / 32768,
254-byte prefix copy, refcounts and cleanup. Category compatibility compares
128 shorts / 256 bytes, including the defining style terminator. The full
source carrier is 383 bytes: 256 style bytes followed by 127 character bytes.
These historical source paths are preserved without changing their policy or
adding padding. SDK MB_LEN_MAX is 5, established by the pinned natural probe.
The allocated runtime table, selected codepage and resulting classifications
remain unknown.

Expandlocale retains its C-locale shortcut, complete parse/qualification,
131-byte input/output caches, actual 130-character threshold, six-byte LC_ID
copy, four-byte codepage copy, output formatting and all exits. The cache ID
and codepage share a complete twelve-byte defining BSS carrier; LC_ID itself
remains three WORDs / six bytes. The default locale and both caches belong to
the complete 403-byte source carrier, rather than invented separate sections.
Stricmp/strnicmp retain their whole thread/locale update, ASCII fast paths,
count/termination behavior and independently bound lowercase worker.

Qualification retains language/country translation, complete binary-search
name tables, primary/default language policy, ACP/OCP and numeric codepage
selection, real locale/codepage validation, default-LCID lookup and all three
enumeration callbacks. The complete compatibility helper preserves size-only,
string/integer query and fallback-record behavior. The source-defined special
language cases and all full table literals remain evidence; no current system
locale or API result is inferred.

**Actual callbacks and whole defining state.** The category table at
`0x006700B8` retains six complete twelve-byte records / 72 bytes / 17 fields.
All six initializer pointers at +8/+20/+32/+44/+56/+68 bind actual source
owners: dummy, collate, ctype, monetary, numeric and time. The source-local
category helper's real call at `0x0064326A` uses `[ebx + 0x6700c0]`. Dummy and
collate each retain three bytes; time retains 95 bytes / ten fields. These
three non-inventoried controls / 101 bytes / ten fields gain no candidate
credit. The LC_ALL dummy is source-defined and documented unused. Category
bounds validation belongs to the pending parent. The helper retains actual
allocation, compatibility, callback and failure paths; its rollback restores
locale, handle and codepage according to the original source. It does not
establish a more general transaction guarantee.

Three actual EnumSystemLocalesA registrations bind source-local callbacks:
`0x0064D778` to `0x0064D45C`, `0x0064D7FE` to `0x0064D676`, and `0x0064D741` to
`0x0064D357`. Each real push sequence supplies LCID_INSTALLED / 1 and its
actual callback pointer to IAT `0x00657118`. All three complete callbacks
return with RET 4. Country registration schedules INC/MOV between argument
pushes and the API call; acceptance verifies the real argument sequence,
without requiring artificial instruction adjacency. Ordinary Ghidra caller
counts omit these indirect registrations and do not establish unused code.

The query pointer at `0x0068E6B0` is the final DWORD / +32 in the complete
36-byte `_iLcidState` BSS carrier. It starts null. Full qualification selects
raw GetLocaleInfoA at IAT `0x0065711C` on the actual NT platform comparison / 2,
or stores the complete source-local compatibility helper at `0x0064D222`.
All nine real indirect query sites remain inside full source owners. The
helper retains RET 16 and the natural SDK control preserves the same stdcall
contract. Runtime selection and query results remain unknown.

The graph retains 198 whole defining sections / 6378 bytes / 220 typed fields
and five complete four-byte COMMON declarations / 20 bytes. COMMON refcounts
and the ctype pointer require their actual source definitions and writable PE
loader zero-fill geometry. Whole data includes country records / 184, language
records / 520, fallback locale records / 1188, ten nondefault WORD IDs / 20,
all C time strings and the full 184-byte time record, complete CTYPE / 1284,
lconv/default carriers and all recursively bound literals. Names, pointer
fields and mutable-state ownership follow defining source topology, without
claims about post-startup contents.

Twenty-five full independent anchors / 4402 bytes / 215 fields preserve prior
origins. Memcpy retains its full R025 829-byte own AUX: seven actual code
regions / 709 bytes and six embedded tables / 120 bytes. Every complete table,
source label, typed DIR32 field and actual case instruction start replays.
Decoding tables as instructions or accepting a 709-byte prefix is rejected.
Its vendor assembly is archive evidence; no assembly or byte arrays are added
to reconstructed game source. The entire R135 input/NLS graph and all retained
output, stream, handle, locale, heap, security and initialization chains replay.

**Compiler observations and verification.** The single natural probe
`probes/VC7LocaleConstructionLayout.cpp` cold-builds the complete 340-byte layout
array. Pinned CRT/SDK types establish LC_ID / 6, LC_STRINGS / 144, category / 12,
name / 8, fallback record / 44, compatibility / 8, lconv / 48, time / 184,
thread locale / 84, CPINFO / 20 and actual offsets/constants. Source-local
record models do not establish reconstructed game owners. Four complete
45-/17-/8-/24-byte controls preserve real stdcall callback RET 4, SDK enumeration
import/flag, zero-argument cdecl category call and four-argument stdcall query
cleanup. Ten complete vendor sources and eight pinned headers replay. VC7.1
build 3077 and explicit flags provide reproducibility, without an executable-wide
compiler-profile claim.

Thirty-eight regression checks reject shortened owners/carriers, invented
candidate credit, wrong defining callbacks, missing table fields, ABI/flag/API
mistakes, guessed runtime selection, incorrect cache/CTYPE layouts and incomplete
memcpy code/table partitioning. All 740 public checks pass. Canonical totals
are 3370 resolved (919 authored, 1876 library, 575 compiler), with 981 pending.
Exact/source/mapping remains 60 / 9883 bytes; recorded authored extents remain
872 / 1952956 bytes and the provisional denominator is 1965299. One final
no-auth public HTTPS MCP request replays R136 and retained graphs, authored
extents, target/project attestation, progress freshness, tests and whitespace.
All 60 exact units cold-replay across eleven objects. Investigation and
intermediate checks use local tools; private evidence stays untracked and
shared tools read-only.

## R137 — Complete locale parents and time-formatting graph

R137 resolves all six locale/time-parent handoff roots and the required existing
expandtime worker: seven complete library primaries / 3033 bytes / 100 typed
fields. One existing nine-byte finally candidate gains library origin within
its complete 346-byte parent. This resolves eight existing candidates, without
counting overlapping bytes twice. Replay
`scripts/repo-python scripts/verify-locale-time-parent-origins.py`; its manifest
is `config/locale-time-parent-origin-evidence.json`. Every primary retains its
complete own AUX and all source/code/data/API fields, branches and exits. No
source, mapping or exact reconstruction credit is added.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__setlocale_get_all` | `0x00642E26` | 191 | 21 |
| `__setlocale_lk` | `0x006432D0` | 473 | 24 |
| `_setlocale` | `0x006434A9` | 346 | 30 |
| `__store_winword` | `0x0064BCB1` | 1162 | 14 |
| `__Strftime_mt` | `0x0064C13B` | 197 | 1 |
| `__Strftime` | `0x0064C200` | 50 | 4 |
| `__expandtime` | `0x0064BA4B` | 614 | 6 |

**Target behavior and boundaries.** Get-all retains allocation and construction
of all category name/value strings and separators, full strcmp/free paths,
same-locale selection and all returns. Its full strcat / 232 anchor retains
its own AUX; the entire 248-byte strcpy/strcat shared carrier remains protected
by independent R116 evidence through the retained graph.

The locked locale interpreter retains category-specific query/set behavior,
LC_ALL compound parsing, known-category matching, ignored unknown categories,
full strpbrk/strncmp/strlen/strcspn/strncpy dependencies, stack locale buffer /
131, locale expansion, category updates and every success/failure exit. Its
source accepts partial category success; it does not establish an all-or-nothing
transaction. Original copy-length behavior is preserved without added bounds
checks or claims about arbitrary caller inputs.

Public setlocale validates categories 0 through 5 and uses the actual
SETLOCALE lock / 12. The entire 346-byte owner retains query-only local unwind,
allocation of threadlocinfo / 84, six handles, locale/codepage/classification,
lconv and time pointer/refcount snapshots, old-object freeing, new-global
pointer installation, thread update, failed-allocation cleanup and both final
returns. The nine-byte existing entry at `0x006435F2` is source label `$L20503`
/ parent +329. Its actual PUSH 12 / unlock / POP / RET is shared by normal
execution and the full finally scope; it is not a standalone source body.
Runtime allocations, reference counts and thread locale remain unknown.

Strftime retains the real thread locale at `_tiddata` +100, comparison with
the independent global locale, update and full six-argument worker call. The
worker / 197 retains explicit-or-thread time locale selection, zero-capacity
exit, percent/hash alternate formatting, inline lead-byte classification,
invalid trailing lead-byte failure, remaining-count tracking and final NUL
termination/zero-on-failure policy. Expandtime / 614 retains all conversion
cases, actual string/number helper contracts, locale day/month/AMPM strings,
numeric year/hour/week behavior, recursion into the full WinWord worker,
timezone initialization/name selection, literal percent, invalid-specifier
exit and all original capacity decisions. The compiler emitted conditional
branches rather than an unaccounted indirect switch table.

WinWord formatting retains all 1162 bytes, including the four-byte exception
filter, handler, API branch and every localized fallback branch after its
ordinary return. Gregorian formatting preserves repetition-based date/time
specifier selection, AM/PM spellings, quoted literals, source-defined alternate
form, multibyte handling, output pointer/count changes and recursive expansion.
No successful decompile or prefix match substitutes for full source comparison.

**SDK dispatch, scopes and defining state.** Non-Gregorian formatting uses
GetDateFormatA at IAT `0x0065714C` or GetTimeFormatA at `0x00657150`, selected
by the actual clock field / 2. The selected pointer is saved at EBP-48. The
real capacity query at `0x0064BD58` passes null output and zero count; the
output call at `0x0064BDCD` uses the saved pointer and allocated buffer/count.
Both actual six-argument sequences and real stdcall @24 imports replay.
SYSTEMTIME is a complete sixteen-byte SDK type. The source writes year +1900,
month +1, day/hour/minute/second and zero milliseconds; no initialization of
its day-of-week field is claimed. Runtime calendar, selected API and returned
values remain unknown. Stack allocation, reset after exception, heap fallback,
conditional freeing, output-copy loop and localized fallback remain complete.

Two full twelve-byte scope records retain enclosing level -1. Finally at
`0x00661180` has a null filter and handler at parent +329. Exception scope at
`0x006626A0` binds actual filter +211 and handler +215 in the WinWord owner.
The filter's entire four-byte body returns one; the handler restores ESP from
EBP-24 and calls the full R123 reset worker. Actual defining COFF labels,
parent field references and instruction starts replay. No new filter/handler
candidate is fabricated.

Seventy whole defining sections / 2582 bytes / 83 typed fields retain the
full six-record category table / 72 / 17 fields, initial locale plus caches /
403, all C time strings and full time record / 184, whole CTYPE / 1284,
lconv/default/locale-handle carriers, two complete scopes and the complete
152-byte timezone carrier with both defining name pointers. Five actual COMMON
pointer/refcount declarations / 20 bytes retain source identities and PE loader
zero-fill geometry. Whole data is compared after independently binding every
field, without carrier prefixes or assumed current mutable values.

Thirty-four full independent anchors / 6576 bytes / 358 fields preserve their
origins. The six actual category callbacks and three non-inventoried controls
/ 101 bytes / ten fields retain R136 evidence without new inventory credit.
The full R136 locale construction/enumeration graph and all retained R135
input/NLS/FP/SEH, output, stream, handle, heap, security and lifetime evidence
replay. Reviewed children alone grant no parent or game-caller origin.

**Compiler observations and local acceptance.** The natural probe
`probes/VC7LocaleTimeParentLayout.cpp` cold-builds a full 260-byte layout array:
tm / 36 and all nine fields, SYSTEMTIME / 16 and all fields, thread locale /
84 and its full snapshot offsets, thread / 140 with locale pointer +100,
time locale / 184 and fields, actual category/cache/lock and private format
selector constants. Complete 19-/35-/39-/66-byte controls preserve two-argument
locale cdecl cleanup / 8, six-argument format cdecl cleanup / 24, seven-argument
expansion cleanup / 28 and real six-argument SDK stdcall / 24 dispatch. Two
whole defining vendor sources and seven pinned headers replay. VC7.1 build
3077 and explicit flags are reproducibility settings, without a global target
compiler-profile claim.

Thirty-one regression checks reject shortened owners, invented interior credit,
missing or misbound scope fields, wrong actual filter/finally/reset execution,
incomplete state and category carriers, ABI/layout/import mistakes, guessed
runtime selection and lost actual API sizing/output contracts. All 771 public
checks pass. Canonical totals are 3378 resolved (919 authored, 1884 library,
575 compiler), with 973 pending. Exact/source/mapping remains 60 / 9883 bytes;
recorded authored extents remain 872 / 1952956 bytes and the provisional
denominator is 1965299. Full new and retained origin evidence, ledger guards,
authored extents, target/project attestation, progress freshness, tests and
whitespace checks pass locally. All 60 exact units cold-replay across eleven
objects. On 2026-10-04 the user waived public MCP acceptance to accelerate
continued review; R137 uses local final verification. Existing no-auth route
and private path remain unchanged. Private evidence stays untracked and shared
tools read-only.

## R138 — Complete locale time snapshots and classification graph

R138 resolves all five locale snapshot/classification handoff candidates:
five complete library primaries / 965 bytes / 54 typed fields. Replay
`scripts/repo-python scripts/verify-locale-snapshot-origins.py`; its manifest
is `config/locale-snapshot-origin-evidence.json`. Every primary retains its
complete own AUX, source member, branches, exits and independently bound fields.
No source, mapping or exact reconstruction credit is added. No new auxiliary,
interior, COMMON or exception-scope inventory entries are fabricated.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__Getdays` | `0x0064B635` | 127 | 8 |
| `__Getmonths` | `0x0064B6B4` | 149 | 8 |
| `__Gettnames` | `0x0064B749` | 563 | 30 |
| `_isalpha` | `0x0064274D` | 63 | 4 |
| `_isalnum` | `0x006428ED` | 63 | 4 |

**Target observations and source behavior.** Getdays sizes all seven abbreviated
and full weekday names, adds two separators per pair and one final NUL, then
allocates and assembles the complete colon-delimited result. Getmonths performs
the corresponding complete twelve-month sizing and copy loops. Both preserve
null-allocation returns, real strlen/strcpy dependencies, all separator writes
and final termination. Their runtime strings and resulting allocation lengths
remain unknown. Ordinary Ghidra caller counts for all three time snapshot
owners are zero; this does not establish unused code or callback/export status.

Gettnames sizes all 43 strings: fourteen weekday names, twenty-four month
names, two AM/PM names and three date/time formats, including their terminators.
It allocates the whole time record / 184 plus the complete string storage,
copies all 184 bytes through the real memcpy and retargets every pointer into
that single allocation. All seven/twelve loops, five trailing pointer copies,
allocation failure and final return remain inside its full 563-byte owner.
The record's LCID, calendar type and refcount are copied with the other fields;
no artificial refcount reset or incomplete object copy is introduced. The
source uses a captured pointer to size/copy strings but reads the current global
again for the record copy. This is the original behavior, without a guarantee
of an atomic or coherent snapshot during concurrent locale mutation. Runtime
pointer values, record contents, allocations and ownership consumers are unknown.

Isalpha and isalnum retain their complete 63-byte bodies and both returns.
Each reads the thread's locale at `_tiddata` +100, compares the actual global
locale pointer and calls the complete independent update worker when needed.
For mb_cur_max at locale +40 greater than one, each calls the full isctype_mt
worker with the actual locale, original signed integer input and mask, then
removes twelve caller bytes. Otherwise it uses the locale's pctype at +72,
loads the unsigned short classification indexed by the original integer and
applies the same mask. Alpha uses `_ALPHA` / 259 / 0x103; alnum uses
`_ALPHA | _DIGIT` / 263 / 0x107. These are classification bit results, without
Boolean normalization or added input-range checks. The natural header control
retains EOF / -1; arbitrary invalid input behavior is not redefined. Runtime
locale, byte width and returned classification remain unknown.

**Complete data and independent dependencies.** Forty-eight whole defining
sections / 2191 bytes / 59 typed fields retain the complete C time record /
184 and its 43 original pointer fields at offsets 0 through 168. All original
strings, full initial-locale/cache carrier / 403, whole CTYPE carrier / 1284,
C lconv/default carrier and current-time pointer retain actual defining COFF
identities, source/target hashes, mutability and all recursively bound fields.
The initial locale's full source-defined pointer topology is preserved without
splitting convenient prefixes or claiming post-startup pointer contents.

Seven complete independent anchors / 1284 bytes / 65 fields preserve their
prior origins: strlen, malloc, strcpy, memcpy, getptd, locale update and the
isctype_mt worker. The seven-byte strcpy entry still depends on the entire
248-byte shared strcpy/strcat carrier through independent R116 evidence.
Memcpy retains its full R025 829-byte own AUX, seven code regions / 709 bytes
and six complete embedded tables / 120 bytes. Every defining table label,
actual code case start and typed field replays. Its full partition is retained,
rather than decoding data as instructions or shortening the owner. All new
primaries use direct calls and branches; no unexplained indirect dispatch is
added. The entire R137 locale/time parent graph and retained R136/R135
category, enumeration, SDK, SEH, FP, stream, handle, heap and lifetime chains
replay. Reviewed library children do not grant origin to game parents.

**Compiler observations and local acceptance.** The natural probe
`probes/VC7LocaleSnapshotLayout.cpp` cold-builds a complete 132-byte layout array.
It establishes the full time / 184 and every field/array size, all 43 pointers,
thread locale / 84, thread / 140, actual locale/classification offsets,
unsigned-short width / 2, distinct alpha/alnum masks and EOF / -1. The complete
26-byte copy control passes the real memcpy symbol and 184-byte count and
retains twelve-byte cdecl caller cleanup. Two complete 67-byte controls use
the original header's alpha/alnum macros, actual multibyte worker declaration,
mask, table load and twelve-byte cdecl cleanup. These are type/ABI controls,
without target reconstruction exact credit. Three complete vendor sources and
nine pinned headers replay. VC7.1 build 3077 and explicit flags are per-probe
reproducibility settings, without an executable-wide compiler-profile claim.

Twenty-eight regression checks reject truncated owners, invented scope/interior
credit, incomplete time/locale/CTYPE carriers, missing strings, wrong masks,
EOF/width/offset mistakes, guessed runtime snapshot consistency, incorrect copy
or worker contracts, unexplained indirect calls and incomplete memcpy partitions.
All 799 public checks pass. Canonical totals are 3383 resolved (919 authored,
1889 library, 575 compiler), with 968 pending. Exact/source/mapping remains
60 / 9883 bytes; recorded authored extents remain 872 / 1952956 bytes and the
provisional denominator is 1965299. Complete new and retained origin replay,
canonical ledger guards, target/project/query attestation, authored extents,
progress/scanner freshness, tests and whitespace checks pass locally. All 60
exact units cold-replay across eleven objects. The user's 2026-10-04 waiver of
public MCP acceptance remains in force. Private evidence stays untracked and
shared tools read-only.

## R139 — Complete floating conversion and operation graph

R139 resolves all six floating conversion/operation handoff candidates as
library origin: six complete own-AUX primaries / 1750 bytes / 52 typed fields.
Replay `scripts/repo-python scripts/verify-floating-operation-origins.py` with
`config/floating-operation-origin-evidence.json`. Full defining COFF members,
source/target hashes, every relocation, branch and exit are preserved. No
source, mapping or exact reconstruction credit is added, and no auxiliary,
interior, COMMON or exception-scope inventory entries are fabricated.

| Complete vendor primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__atoldbl` | `0x0064F7F0` | 62 | 4 |
| `___STRINGTOLD` | `0x00653105` | 76 | 4 |
| `__floor_default` | `0x0064E980` | 211 | 9 |
| `__logb` | `0x00643C38` | 235 | 10 |
| `__nextafter` | `0x00643D23` | 675 | 10 |
| `_ldexp` | `0x0064EA53` | 491 | 15 |

**Target observations.** Both conversion wrappers use the local storage between
EBP-16 and the security cookie at EBP-4. They pass seven stack arguments / 28
bytes to strgtold12, then two / eight bytes to ld12told, and remove the combined
36 caller bytes. Atoldbl passes flag one and a local end-pointer slot, then
returns the converter's status. STRINGTOLD preserves the parser's status and
ORs bit two when the converter returns one. Neither status policy is replaced
with a guessed Boolean result. The retained converter reads input through
word offset ten and writes output DWORDs at zero/four and a WORD at eight:
twelve-byte input storage and ten-byte output span are distinct observations.
Original private record typedefs and signedness remain unknown.

Floor_default saves/restores the raw x87 control word, uses its actual newcw
object, retains all special-value/error paths, and calls the complete frnd
worker. Frnd is an ordinary stack-double / ST0-return worker: it loads the
argument at ESP+12 after two pushes, executes FRNDINT, stores/reloads a double
and returns with no callee cleanup. It is not assigned an invented ST0-input
ABI. Logb, nextafter and ldexp retain raw operation control 0x133F and mask
0xFFFF, complete classification/decomposition/exponent helpers, NaN/error
paths and control restoration. Nextafter retains both exponent scaling paths
(+0x600 and -0x600), sign/mantissa updates and the full two-argument error
policy. Ldexp retains integer-limit and both range paths, copysign, set_exp and
exception handling. All six complete returns are caller cleaned. Runtime
operands, current control/status and error-handler behavior remain unknown.
Attested Ghidra reports no ordinary callers for these six roots; that does
not establish unused code or callback/export status.

**Whole dependencies and data.** Thirteen complete independent anchors / 2184
bytes / 59 fields preserve their existing origins, including the full parser,
converter, cookie checker, x87 controls, decomposition, rounding and error
workers. The parser's own AUX is 1076 bytes: 1028 real code bytes followed by
one 48-byte table with twelve DIR32 cases. Its defining $L1157 label, selector
field, every case definition and actual instruction entry replay. Data is not
decoded as instructions, and the comparison still covers all 1076 bytes and
26 fields. The entire R138 and retained R137/R136/runtime/FP/locale/heap/game
chains replay independently; reviewed children do not grant origin to parents.

Eight whole defining data sections / 88 bytes / zero relocations retain the
complete cookie, four-byte newcw carrier, forty-byte d_inf carrier and folded
double constants. Source newcw initially contains 0x173F; runtime contents
are unknown. Repeated COMDAT constants from separate defining members are
checked separately: 88 is the sum of defining source sections, not unique
target coverage. No eight-byte infinity prefix substitutes for its forty-byte
owner. Source/target hashes, defining symbols and mutability are retained.

**Compiler observations and acceptance.** The natural
`probes/VC7FloatingOperationLayout.cpp` cold-builds a complete 108-byte layout
array using pinned math.h, float.h and fpieee.h. It establishes pointers/int /
four, double and C long double / eight, complete SDK FP80 / ten, exception /
32 with its offsets, and abstract CRT control/status macros. Those macros are
distinct from raw x87 words. Five complete 20-/29-/24-/19-/88-byte natural
function-pointer controls retain unary/binary/scaling caller cleanup of eight,
sixteen/twelve, pointer output, meaningful twelve-byte parser storage and the
status merge. They model ABI/storage and do not assert recovered private C
types. Original private math/conversion C files are absent in the supplied
source tree; ownership rests on pinned full COFF definitions and typed fields,
not invented recovered source. VC7.1 build 3077 and explicit flags remain
per-probe reproducibility settings, without an executable-wide compiler claim.

Thirty-four regression checks reject truncated owners, missing fields/cases,
data entries treated as code, unavailable source claims, incorrect widths,
status/stack/control policies, guessed runtime state and incomplete retained
graphs. All 833 public checks pass. Canonical totals are 3389 resolved (919
authored, 1895 library, 575 compiler), with 962 pending. Exact/source/mapping
remains 60 / 9883 bytes; recorded authored extents remain 872 / 1952956 bytes
and the provisional denominator is 1965299. Full new/retained cold origin
replay, canonical ledger guards, target/project/query attestation, authored
extents, progress/scanner freshness, tests and whitespace checks pass locally.
All 60 exact units cold-replay across eleven objects. The user's 2026-10-04
public MCP acceptance waiver remains in force. Private evidence stays
untracked and shared tools read-only.

## R140 — Complete stream finalization and path-access graph

R140 resolves all four stream finalization/path-access handoff candidates as
library origin: four complete own-AUX primaries / 282 bytes / 11 typed fields.
Replay `scripts/repo-python scripts/verify-stream-finalization-origins.py` with
`config/stream-finalization-origin-evidence.json`. Every defining member,
source/target hash, typed field, complete branch and exit is retained. No
source, mapping or exact reconstruction credit is added, and no auxiliary,
interior, COMMON, data or exception-scope inventory entries are fabricated.

| Complete vendor primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__freebuf` | `0x00654953` | 43 | 1 |
| `__fclose_lk` | `0x00653E01` | 76 | 4 |
| `__flush` | `0x00652588` | 93 | 1 |
| `__access` | `0x00641B37` | 70 | 5 |

**Target observations and original source.** Freebuf is void and assumes its
caller holds the stream lock. It acts only when inuse / 0x83 and the CRT-owned
buffer bit / eight are both set. It frees the actual base pointer, clears
IOMYBUF and IOSETVBUF / 0x408 (the target uses WORD mask 0xFBF7), and clears
base, current pointer and count. It does not free the user's buffer or add
an invented return value. The complete original `_freebuf.c` is supplied.

Flush checks that the read/write direction bits select writing, bigbuf /
0x108 is set and ptr-minus-base is positive. It passes descriptor, base and
full requested count to the complete write worker, with twelve caller bytes.
Only an equal returned count is success; on a read/write stream success clears
IOWRT, while any unequal result sets IOERR / 0x20 and returns EOF. Every path
resets ptr to base and count to zero, including errors and no-write paths.
No retry, added count normalization or disk-commit policy is introduced.

Fclose_lk initializes its result to EOF. If the stream is in use, it orders
flush, buffer release and low-level close. A negative close result forces EOF;
a nonnegative close frees a non-null temporary filename and clears that pointer.
If close fails, the temporary filename is not freed by this owner. The final
flag reset occurs on every path, and a successful close preserves an earlier
flush error. All original fclose.c/fflush.c branches and exits remain inside
their own 76-/93-byte owners. The helpers assume a caller-held stream lock;
runtime locking, stream/handle validity, buffer/name ownership and IO results
remain unknown. A zero ordinary caller count for fclose_lk is not unused-code
or export/callback evidence.

Access calls the actual GetFileAttributesA import. An invalid attribute result
calls GetLastError and dosmaperr and returns minus one. Otherwise it rejects
the combination of FILE_ATTRIBUTE_READONLY / one and the caller's write-mode
bit / two, setting CRT errno / EACCES / thirteen and DOS error / five. Other
cases return zero. This is the original attribute test, without added ACL or
mode validation. The real caller at `0x00414300` retains its independently
accepted R035 ReplayRecords::FindAvailablePath origin; the library child does
not establish or reclassify caller ownership. Caller paths/modes, ACP and
current error state remain unknown.

**Independent dependency and variant closure.** Six complete anchors / 572
bytes / 42 fields retain free, close, write, dosmaperr, errno and doserrno's
prior R120/R132/R133 origins. Every defining source and typed field replays,
along with the full R139 and older stream/handle/thread/heap/error/FP/game
chains. The new primaries need no standalone data carrier or COMMON definition;
their runtime data belongs to caller-provided streams and retained dependencies.

The complete seventy-byte waccess alternative / five fields has the same code
shape outside relocations. It is retained as a diagnostic rejected variant,
including its own AUX, full defining member, hashes and all typed fields. The
actual PE IAT slot `0x0065718C` imports GetFileAttributesA, whereas its source
requires GetFileAttributesW. That independent contradiction rejects the wide
association even though patching relocation numbers makes its full bytes
congruent. The verifier binds both actual indirect API instruction fields and
all helpers. No masked comparison, convenient prefix or imported database name
supplies acceptance.

**Compiler observations and local acceptance.** The natural
`probes/VC7StreamFinalizationLayout.cpp` cold-builds a complete 112-byte layout
array. It preserves complete FILE / 32 and actual ptr/count/base/flag/file/
tmpfname offsets 0/4/8/12/16/28, char/wchar widths one/two, all ownership/error
masks, DWORD attribute sentinel, distinct CRT/DOS errors and EOF. Five complete
92-/172-/131-/92-/92-byte controls use real pinned declarations and natural
buffer/flush/close/A/W policies. Five full original vendor files and nine
headers replay; available source is not replaced with guessed private types.
These are ownership/type/ABI controls, without exact reconstruction credit.
VC7.1 build 3077 and explicit flags are per-probe reproducibility settings.

Thirty-six regression checks reject incomplete owners, invented scope/data
credit, wrong masks/offsets/ABI, lost short-write/reset/close/error policies,
unexplained dispatch, omitted sources/headers, guessed runtime ownership and
an unsupported wide variant rejection. All 869 public checks pass. Canonical
totals are 3393 resolved (919 authored, 1899 library, 575 compiler), with 958
pending. Exact/source/mapping remains 60 / 9883 bytes; recorded authored
extents remain 872 / 1952956 bytes and the provisional denominator is 1965299.
Full new/retained cold origin replay, canonical guards, target/project/query
attestation, authored extents, progress/scanner freshness, tests and whitespace
checks pass locally. All sixty exact function records and tracked source,
header, build and match inputs are unchanged from R139 `db26a05`; that batch's
60/60 cold exact replay across eleven objects remains applicable. No affected
exact unit needs another replay. The user's 2026-10-04 public MCP acceptance
waiver remains in force. Private evidence stays untracked and shared tools
read-only.

## R141 — Complete exception frame and unwind graph

R141 resolves all six exception frame/unwind handoff roots and their required
callee/parent closure: 27 complete library primaries / 3,502 bytes / 116 typed
fields, plus two existing interior cleanup candidates. Replay
`scripts/repo-python scripts/verify-exception-frame-origins.py` with
`config/exception-frame-origin-evidence.json`. All 29 canonical candidates gain
library origin only. No source, mapping or exact credit is added; three complete
non-inventory auxiliary controls / 123 bytes / four fields gain no invented
candidate rows. The six roots account for 1,503 bytes / 65 fields.

| Root | Address | Previous bytes | Complete own AUX | Fields |
| --- | --- | ---: | ---: | ---: |
| `___FrameUnwindToState` | `0x006455D6` | 173 | 206 | 10 |
| `___DestructExceptionObject` | `0x006456D4` | 52 | 69 | 5 |
| `CallCatchBlock` | `0x0064592D` | 332 | 452 | 16 |
| `BuildCatchObject` | `0x00645AF1` | 368 | 380 | 22 |
| `___CxxExceptionFilter` | `0x00645C6D` | 293 | 293 | 7 |
| `CatchIt` | `0x00645D92` | 103 | 103 | 5 |

**Complete extents and scope entries.** All six roots retain their complete
frame.obj member / 379030 definitions, AUX extents, source/target hashes and
all typed fields. Five canonical extents expand, including the four roots
above and JumpToContinuation / `0x00640721`, 43 to 48 bytes. Its final five
bytes are real POP EBX, LEAVE and RET 8 after JMP EAX, not invented alignment.
CallCatchBlock has three actual INT3 alignment bytes at source offsets
332–334 before its finally entry; its full 452-byte owner includes them.
No first-return or old provisional prefix supplies acceptance.

The existing `0x00645689` / 27-byte and `0x00645A82` / 111-byte candidates
are actual source-defined body labels $L19974 / +179 and $L20060 / +341 inside
complete parents `0x006455D6` and `0x0064592D`. Their real scope handlers start
six bytes earlier, at +173 / `0x00645683` and +335 / `0x00645A7C`. The full
parents include these prologues, body labels, all filters and handler tails.
The two labels gain no standalone function/source/exact interpretation.
Read-only Ghidra helper queries attest the target and complete successfully;
its provisional function inventory does not contain the four queried scope
entries. Raw target mapping, full COFF fields and independent whole decoding
provide extent and callback evidence without database writes.

Five whole readonly source scope tables / 84 bytes contain seven complete
12-byte enclosing/filter/handler records and twelve typed callback fields:
$T19981 / `0x006614E8`, $T20002 / `0x00661500`, $T20075 / `0x00661530`,
$T20094 / `0x00661548` and $T18949 / `0x006615C0`. Every signed enclosing level,
null finally filter, actual non-null handler and filter instruction start is
checked against its complete source parent. The mutable four-byte inconsistency
handler / `0x00670140` has one complete initial pointer to the retained terminate
worker; its current runtime value remains unknown. The full four-byte cookie
at `0x0066FE30` is retained. These are seven whole defining data sections /
92 bytes / thirteen fields, not carrier prefixes or reconstructed private types.

**Dependency and actual ABI closure.** The other 21 complete primaries close
inconsistency, CallSettingFrame, all three member-call trampolines, create/unlink/
destruction frame-chain checks, CallCatchBlock2, abnormal termination, read/write
validators, AdjustPointer, nested unwind, continuation, InternalCxxFrameHandler,
FindHandler, foreign exception handling, try-range selection, SE translation
and TranslatorGuardHandler. Three full non-inventory controls retain
FrameUnwindFilter / 30, CatchGuardHandler / 59 and unwind_handler / 34 bytes.
Eight full anchors / 1,183 bytes / 65 fields retain SEH prolog/epilog, getptd,
terminate, memmove, execute validation, TypeMatch and NLG_Notify1's prior origins.
Memmove's whole 829-byte owner has seven code regions / 709 bytes and six whole
inline tables / 120 bytes; every source-typed case reaches a real code start.
The retained R117 graph still owns NLG_Notify1's shared notification parent.

The nested-unwind REL32 calls the complete six-byte compiler linker thunk at
`0x00654B54`. Its raw IAT slot `0x00657180` independently imports
KERNEL32.dll!RtlUnwind. The thunk retains R030 compiler ownership and its full
hash/extent; the imported implementation gains no library credit. Validator
fields bind actual IsBadReadPtr and IsBadWritePtr imports, without assuming
runtime pointer validity or outcomes. All direct transfers retain either an
actual typed relocation or the same complete defining source section.

Optimized private helpers cannot be declared from their decorated names:
BuildCatchObject copies incoming ECX/EDX to ESI/EDI and reads two stack inputs;
AdjustPointer uses EAX as the base pointer and ECX as adjustment-field storage;
TypeMatch uses ESI/EDI and one stack input; FrameUnwindFilter receives exception
pointer storage in EAX. Canonical calling convention/signature fields stay
unset. The three seven-byte member trampolines pop ECX, exchange the target and
return address on the stack and tail-jump EAX, delegating cleanup to the actual
worker; no fake RET is introduced. CallSettingFrame returns with twelve callee
bytes and switches EBP to the supplied frame plus twelve. Nested unwind and
the continuation epilogue return with eight callee bytes. SE translator calls
use the actual thread field +0x74 and two consecutive caller-cleanup POPs.
The forward-compatible exception handler consumes eight stack arguments / 32
caller bytes. Actual opaque member/funclet/continuation/translator/handler
indirect sites are inventoried completely; current callback targets and results
remain unknown.

**Compiler observations and source limits.** The original private
frame.cpp/ehdata.h/ehhooks.h/trnsctrl.h files are unavailable in the supplied
tree. Full pinned vendor COFF definitions establish ownership, extent, typed
fields and scope provenance; they do not recover complete original private
record identities or source. The real available exsup.inc supports exception
constants. The cold natural `probes/VC7ExceptionFrameLayout.cpp` uses six actual
SDK/CRT headers and a complete 128-byte layout array: EXCEPTION_RECORD / 80,
EXCEPTION_POINTERS / eight, CONTEXT / 716 and _tiddata / 140 bytes, with translator/
current-exception/context/frame-chain offsets 116/124/128/136. Filter results and
handler dispositions are distinguished. Complete independent member classes,
translator/stdcall calls, SEH finally/filter policies and C++ integer throw/catch
produce nine complete 38-/20-/11-/15-/19-/94-/143-/28-/82-byte controls.

All seven generated defining data sections / 167 bytes replay whole, including
the complete 80-byte catch metadata section and all its neighbouring definitions,
not only FuncInfo. The separate ten-byte compiler EH handler has no AUX; its
complete defining code section, full symbol topology, flags and both typed
fields replay. It is a compiler model, not a new target candidate or an invented
private record. Complete generated metadata does not establish TH075's original
private type names/layouts. VC7.1 build 3077 and explicit probe flags remain
per-probe reproducibility settings.

**Local acceptance.** Forty regression checks reject truncated scopes/owners,
wrong enclosing or null-handler records, non-instruction callbacks, invented
source labels, absent tables/dependencies, false private cdecl declarations,
wrong member/translator cleanup, missing SDK facts and descriptor prefixes.
All 909 public checks pass. The new complete origin replay and full retained
R140/older EH/thread/heap/error/stream/FP/game chain cold-replay locally, with
canonical guards, target/project/query attestation, all 872 authored extents,
progress/scanner freshness and whitespace checks. Totals are 3,422 resolved
(919 authored, 1,928 library, 575 compiler), 929 pending and 2,503 excluded.
Source/mapping/exact remains 60 / 9,883 bytes; recorded authored extents remain
872 / 1,952,956 bytes and the provisional denominator is 1,965,299. All exact
function records and source/header/build/match inputs are unchanged from R139
`db26a05`, retaining its 60/60 cold replay across eleven objects. No affected
exact unit needs another replay. Public MCP acceptance remains waived by the
user's 2026-10-04 instruction. Private evidence stays untracked; shared tools
remain read-only. Original private types, current exception/frame/thread state
and opaque callback behavior remain explicitly unknown.

## R142 — Complete C++ throw/frame and standard exception graph

R142 resolves all four C++ throw/frame/standard-exception handoff roots and
the required lifetime/delete closure: eight complete own-AUX library primaries /
331 bytes / twenty typed fields, plus the existing nine-byte type_info finally
entry. Replay `scripts/repo-python scripts/verify-standard-exception-origins.py`
with `config/standard-exception-origin-evidence.json`. Nine candidates gain
library origin only. The thirteen-byte non-inventory what control gains no
invented candidate. Two deleting-destructor controls retain their existing
R038 compiler origins; they are not reclassified as library functions.

| Complete primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__CxxThrowException@8` | `0x00640C12` | 58 | 2 |
| exception copy constructor | `0x00640C9A` | 74 | 4 |
| type_info destructor | `0x00640E49` | 70 | 7 |
| `___CxxFrameHandler` | `0x006407B8` | 54 | 1 |
| exception default constructor | `0x00640C4C` | 17 | 1 |
| exception assignment | `0x00640DD6` | 31 | 2 |
| exception destructor | `0x00640CE4` | 22 | 2 |
| operator delete | `0x00640F15` | 5 | 1 |

**Complete target extents and behavior.** The type_info destructor expands
from the provisional 61-byte prefix to its whole seventy-byte own AUX. The
existing `0x00640E86` / nine-byte candidate is its actual source-defined
$L19209 finally entry at +61, which pushes lock fourteen, calls the complete
unlock worker, pops the caller argument and returns. The parent acquires that
same lock before checking/freeing cached-name storage at +4, invokes finally
on its normal path and retains the complete scope entry/tail. It does not
reset the dying object's cached pointer. This finally label starts at its
scope callback, unlike R141's six-byte-later body labels. No standalone source,
exact or mapping credit is assigned to it.

The complete frame shim saves incoming EAX as opaque function metadata and
forwards four stack handler inputs, that saved metadata and three zeros to the
whole retained InternalCxxFrameHandler. It cleans 32 caller bytes, restores its
registers and returns the handler result. Zero ordinary Ghidra callers does
not imply unused code: independent compiler EH carriers load metadata in EAX
and transfer to this symbol. Its private ABI cannot be replaced by a five-stack-
argument conventional prototype; canonical declarations remain unset.

Throw copies exactly eight DWORDs from its whole readonly 32-byte template at
`0x00660E74`. Complete values are exception code E06D7363, noncontinuable flag
one, zero record/address, parameter count three, magic 19930520 and two zero
input slots. It fills the object/opaque descriptor slots at template +24/+28,
passes code/flags/count and the three-word parameter address at +20 to the
actual KERNEL32.dll!RaiseException IAT slot `0x00657184`, and retains its real
RET 8. The supplied SDK EXCEPTION_RECORD is eighty bytes, with fifteen maximum
parameters; it does not establish an invented complete private 32-byte type.
Original private throw descriptors and exception delivery outcomes remain
unknown. The 84 observed callers gain no ownership from the reviewed worker;
older unresolved catch/parent extents remain pending.

Exception default construction clears message +4 and ownership flag +8 and
writes the actual exception vtable. Copy construction copies the ownership
flag: an unowned message pointer is borrowed directly; an owned message gets
strlen-plus-one allocation and strcpy only when allocation succeeds. A failed
allocation leaves the copied ownership flag and a null message, matching the
whole original body. Assignment guards self-assignment, destroys the current
object and invokes the complete copy constructor on the same storage. The
ordinary destructor frees +4 only when the ownership flag is nonzero. The
complete thirteen-byte what control returns +4 or the complete original
18-byte literal `Unknown exception`. Copy/assignment return with four callee
bytes. The five-byte operator delete is a source-bound tail transfer to the
independently reviewed free worker, without a fake return or a new allocation
policy. Runtime object/message ownership and allocation outcomes stay unknown.

**Whole vtable, RTTI and weak-reference provenance.** Fifteen complete defining
source data sections / 260 bytes / eighteen fields close both classes' vtables,
locators, descriptors, hierarchy/base graphs, the throw template, finally scope
and fallback literal. The exception vtable address point is +4 inside a whole
12-byte section at `0x00660E94`; type_info's is +4 inside a whole eight-byte
section at `0x00660ED8`. Each prefix is a real typed locator pointer, not omitted
padding. A source anchor at +4 selects the whole section; every definition,
byte and field is compared from its actual base. The two base arrays are five
bytes each, including the real byte after their pointer; four-byte prefixes
are rejected. All initial writable type descriptors and readonly metadata
retain complete source/target extents and actual storage mutability.

The vtable fields reference weak `??_Eexception` / `??_Etype_info` symbols.
Their actual storage-class-105 COFF records each have one AUX, fallback tag 17
and search-characteristics value two. The referenced external scalar symbol
also has a complete strong definition in that same pinned member. The full
archive has no strong definition of the weak E symbol. This evidence is not
rewritten as an unconditional alias/search-mode-three claim. Actual vtable
pointers land on complete 28-byte scalar controls at `0x00640DBA` and
`0x00640E8F`, whose whole defining sections have no function AUX. Their full
COFF topology, flags, bytes and both fields replay, along with the independent
53-body R038 cold compiler control. R038 names/origins remain unchanged.
Original link inputs/search decisions beyond the supplied archive evidence
remain unknown. Every weak callback still requires a real strong source code
entry in the complete catalog, never a guessed same-address label.

Eleven full anchors / 641 bytes / 26 fields retain nine prior library owners
(strlen, malloc, strcpy, SEH prolog/epilog, lock/unlock, free and the complete
internal EH handler) and the two compiler controls. R141 and its full older
EH/thread/heap/error/stream/FP/game chain replay, together with R038. The seven-
byte strcpy entry retains its independently reviewed full shared parent through
that chain. Current RTTI caches and private handler behavior are not inferred
from complete initialized metadata or raw API identity.

**Compiler observations and local acceptance.** The original private
throw.cpp/stdexcpt.cpp/typinfo.cpp/trnsctrl.cpp implementation files are absent
from the supplied tree. Real stdexcpt.h delegates to the supplied complete
exception header; typeinfo.h supplies the real SDK type_info interface. The
natural `probes/VC7StandardExceptionLayout.cpp` cold-builds an 88-byte layout
array and all 81 actual included headers are hash-pinned. SDK exception,
type_info and the RTTI exception classes are twelve bytes; the independent
complete message owner is twelve bytes with its own public +4/+8 fields.
This independent model does not instantiate an incomplete TH075 game owner.
The required /Zc:wchar_t satisfies the actual internal yvals.h requirement;
VC7.1 build 3077 and all flags remain per-probe reproducibility settings,
not an executable-wide compiler profile.

Twenty-two complete SDK/placement/member/delete/raise/ownership/integer-throw/
catch controls / 1,010 bytes / 36 fields replay. Eight complete generated data
sections / 219 bytes / thirteen fields include both the whole 36-byte ownership
EH metadata section and the whole 80-byte catch metadata section. Three no-AUX
code carriers / 81 bytes / seven fields replay whole: a 44-byte independent
scalar control, the complete 27-byte section containing a cleanup funclet and
its following EH handler, and the separate ten-byte integer-catch EH handler.
No cleanup prefix or FuncInfo-only view substitutes for its defining section.
These are compiler/source-family controls without target exact credit.

Forty-two regression checks reject incomplete parents, omitted locator prefixes,
wrong weak AUX tags/search modes, invented source/private ABI, lost ownership/
self-assignment/unlock policies, wrong cleanup/API identity and partial model
metadata/carriers. All 951 public checks pass. Full new/retained cold origin
replays, canonical guards, target/project/query attestation, all 872 authored
extents, progress/scanner freshness and whitespace checks pass locally. Totals
are 3,431 resolved (919 authored, 1,937 library, 575 compiler), 920 pending and
2,512 excluded. Source/mapping/exact remains 60 / 9,883 bytes; recorded authored
extents remain 872 / 1,952,956 bytes and the provisional denominator is
1,965,299. Exact rows and all source/header/build/match inputs are unchanged
from R139 `db26a05`, preserving its 60/60 cold replay across eleven objects.
No affected exact unit needs another replay. The user's public MCP acceptance
waiver remains in force. Private evidence is untracked; shared tools are read-only.

## R143 — Complete derived RTTI-exception lifetime families

R143 resolves the three existing handoff candidates as library origins:
`0x00640D38`, `0x00640D74` and `0x00640DAF`. Each retains its complete
11-byte own-AUX extent and both typed fields: 33 bytes and six fields in all.
Replay `scripts/repo-python scripts/verify-derived-exception-origins.py` with
`config/derived-exception-origin-evidence.json`. No source, mapping or exact
credit is assigned. Original target names remain provisional.

| Provisional source role | Destructor | Constructed vtable address point | Destruction-stage address point | Retained R038 compiler caller |
| --- | --- | --- | --- | --- |
| bad_cast | `0x00640D38` | `0x00660EB8` | `0x00660EB8` | `0x00640DF5` |
| bad_typeid | `0x00640D74` | `0x00660EC4` | `0x00660EC4` | `0x00640E11` |
| __non_rtti_object | `0x00640DAF` | `0x00660ED0` | `0x00660EC4` | `0x00640E2D` |

**Target observations and whole source alternatives.** Each complete
primary writes the destruction-stage vtable through ECX and tail-jumps
straight to the complete R142 base exception destructor `0x00640CE4`.
There is no standalone RET or fabricated intermediate bad_typeid destructor
call. The last two source COFF bodies, including their two source relocation
records, are identical. Their linked target bytes differ in the address-
dependent REL32 tail displacement. This corrects the preceding handoff's
statement that all eleven target bytes were equal. Both full source owners
match both targets after independent relocation; the bad_cast owner matches
only `0x00640D38` when its real vtable object is bound. All three complete
source alternatives are retained and cold-read, with full own AUX extents,
source definitions, every typed field and complete relocated results.
Neither relocation masking nor a short destructor shape chooses class identity.

The paired graph supplies context independently of that equal body. Six
non-inventory message/copy constructors retain their own complete AUX:
`0x00640D07` / 25, `0x00640D20` / 24, `0x00640D43` / 25,
`0x00640D5C` / 24, `0x00640D7F` / 24 and `0x00640D97` / 24 bytes.
The first two classes call complete base exception message/copy constructors;
non-rtti construction calls the complete bad_typeid message/copy pair and
then installs its own constructed vtable. Each preserves RET 4 and ECX member
calling behavior. The whole 61-byte base message constructor at `0x00640C5D`
allocates strlen-plus-one storage, conditionally copies the message and sets
ownership to one even if allocation fails. The complete thirteen-byte what
control at `0x00640CFA` retains the whole fallback literal. These eight
non-inventory bodies / 220 bytes / seventeen fields gain no invented rows.

**Complete defining data and callbacks.** Thirty-one whole vtable/RTTI/literal
sections / 543 bytes / 48 fields close the three derived classes and the
exception/type_info base metadata. The three constructed vtables occupy whole
12-byte sections at `0x00660EB4`, `0x00660EC0` and `0x00660ECC`; their real
address points are +4 and their locator prefixes and both callback slots are
compared. Derived type descriptors preserve all 23, 25 and 32 source bytes and
initial writable state. Base arrays preserve all nine, nine and thirteen bytes,
including the byte after their last pointer. The non-rtti base sequence is
non-rtti, bad_typeid, exception. Every locator, hierarchy, base descriptor,
base-array pointer, type_info vtable and literal retains its actual full
source section, typed fields and storage mutability.

Five actual weak E records retain storage class 105, one AUX, their real
fallback tags and search-characteristics two. Their corresponding G symbols
have strong definitions in complete no-AUX code sections; the supplied whole
archive has no strong E definition. Search mode two is not rewritten as a
forced alias mode three. Actual derived vtable callbacks land on the three
whole 28-byte R038 compiler controls, and each control's full source-bound
REL32 field calls its paired destructor. The complete constructed vtable,
RTTI and constructor graph identifies the source role context even where the
standalone destructor owners remain equal alternatives. Original link inputs
and search decisions beyond this supplied archive remain unknown.

Ten complete anchors / 400 bytes / eighteen fields preserve five existing
library origins (base destructor/copy constructor, strlen, malloc and strcpy)
and five existing R038 compiler origins (the three derived deleting controls,
exception and type_info). R142 replays its entire older dependency chain and
the independent 53-body R038 cold proof. No compiler control is reclassified.

**Compiler observations and acceptance.** The original stdexcpt.cpp is absent.
The real supplied typeinfo.h declares complete SDK bad_cast and bad_typeid
classes deriving from exception, and __non_rtti_object deriving from
bad_typeid. The natural `probes/VC7DerivedExceptionLayout.cpp` uses those actual
complete interfaces and separate complete inheritance models; it does not
instantiate an incomplete reconstructed game owner. A cold 32-byte array
reports four-byte pointers and twelve-byte SDK/model class sizes. All eleven
actual included headers are hash-pinned. The explicit final /GR enables RTTI
for this independent model, while /Zc:wchar_t satisfies the actual header;
these are probe reproducibility settings, not a target-wide compiler profile.

Twenty-three complete natural SDK constructor/copy/destructor/delete/member
controls and model bodies / 1,017 bytes / 33 fields replay. All twenty generated
RTTI/vtable data sections / 406 bytes / 33 fields replay from their complete
bases. All three no-AUX generated scalar code sections / 132 bytes / six fields
also replay. No short scalar, vtable address point or base-array pointer is
substituted for its defining section.

Thirty-one regression checks reject truncated extents, lost compiler ownership,
swapped incoming destructor callbacks, wrong destruction-stage vtables, omitted
locator prefixes/trailing array bytes, false intermediate calls, incorrect
constructor/copy/cleanup ABI, changed weak search semantics, removed full
source alternatives, partial generated sections and invented SDK/runtime
claims. All 982 public checks pass. The full new/retained cold evidence replay
passes once, followed by canonical ledger write/read-back guards; it was not
repeated merely for the ledger update. Target/project/query attestation, all
872 recorded authored extents, exact-input preservation, progress/scanner
freshness and whitespace checks pass locally. Totals are 3,434 resolved
(919 authored, 1,940 library, 575 compiler), 917 pending and 2,515 excluded.
Source/mapping/exact remains 60 / 9,883 bytes; recorded authored extents remain
872 / 1,952,956 bytes and the provisional denominator is 1,965,299. All exact
inputs/rows are unchanged from R139 db26a05, preserving its 60/60 cold proof
across eleven objects. No affected exact unit requires another cold build.
The user's public MCP acceptance waiver remains in force; the no-auth route
and private random path remain unchanged. Private evidence is untracked.

## R144 — Complete longjmp and SEH read-probe graph

R144 resolves both handoff candidates as library origins:
`0x00643604` / complete 121-byte `_longjmp` and `0x0064DC10` / complete
66-byte `__rt_probe_read4@4`. Their eight typed fields retain full code,
actual defining source/absolute/scope/API context and independent SDK controls.
Replay `scripts/repo-python scripts/verify-jump-unwind-origins.py` with
`config/jump-unwind-origin-evidence.json`. No source, mapping or exact credit
is assigned. Original executable names and private declarations remain
provisional even where the supplied source/target bodies agree completely.

**Complete target extents and behavior.** Longjmp's own COFF AUX is 121 bytes,
including the real RET at `0x0064367C` after the indirect saved-return jump.
The provisional 120-byte ledger omitted that byte; its complete extent now
ends at `0x0064367C`. The RET is present in the pinned source and target, not
invented to obtain a match. No existing interior inventory candidate is inside
either complete primary, and no standalone label row is invented.

Longjmp loads the saved EBP and exception registration before comparing the
registration to FS:[0]. When they differ it calls the complete global unwind
worker. For a nonzero registration it probes the cookie at +32; a readable
VC20 cookie (`0x56433230`) permits the opaque +36 UnwindFunc callback, invoked
with the buffer pointer on the stack. A null callback skips local unwind;
a missing/unreadable/wrong cookie takes the complete old local-unwind path
with saved TryLevel +28. The saved EIP +20 is passed in EAX to the complete
NLG notify worker with saved EBP and stack code zero. Longjmp then restores
EBX, EDI, ESI and ESP, adds four to the restored stack and jumps to saved EIP.
CMP-one/ADC-zero maps zero return input to one while preserving every nonzero
input, including negative values. The saved callback identity/ABI, live
registrations, valid saved state and runtime outcomes remain unknown.
The two ordinary callers gain no ownership from this reviewed library child.

The read probe's entire 66-byte own AUX includes its ordinary load/success
path, filter at +29 and exception handler at +49. Ghidra's ordinary flow skips
that filter/handler region; the full source and target decode does not.
Successful DWORD access returns one. Its filter follows the exception-pointer
chain and returns one only for access violation `0xC0000005`; other exception
codes return zero, preserving continue-search semantics. The handler restores
saved ESP and returns zero through the common epilog. The filter has RET 0;
the callable primary has RET 4. The one whole readonly 12-byte `$T19221`
section at `0x006639E8` has enclosing level -1 and typed filter/handler pointers
`0x0064DC2D` / `0x0064DC41`. Both land on actual defining source entries in the
complete primary, with no guessed same-address label or partial callback body.

**Actual ABS and retained dependency provenance.** Longjmp's first field is
DIR32 `__except_list` at +12 in its FS comparison, resolved to zero. This is
not an object at PE virtual address zero. The whole supplied libcmt archive
has one external defining symbol: exsup.obj member 1210238, storage class two,
section -1 (ABS), value zero. The longjmp member retains the actual external
undefined referring record. The verifier rereads the defining member identity,
scans the whole archive for competing strong definitions, checks the exact
symbol record and proves the field is the displacement of the FS instruction.
No undefined/static symbol, guessed zero binding or GS instruction substitutes
for this independent ABS provenance.

Five whole anchors / 236 bytes / five fields preserve prior library origins:
global unwind 32, local unwind 104, NLG notify 24, SEH prolog 59 and SEH epilog
17 bytes. The full R141 replay retains their R117/R025 source owners, actual
shared tails, scope/NLG state and unwind import route through its dependency
chain. Private unwind/NLG register contracts are kept explicit: NLG receives
EAX destination, EBP saved frame and a stack code, rather than an invented
three-stack-argument prototype. Canonical private calling declarations remain
unset. Complete source/body comparisons and every typed code/data/absolute
field are required; relocation masking is never acceptance evidence.

**Compiler observations and acceptance.** Original longjmp.asm/sehsupp.c
implementation files are unavailable. The supplied exsup.inc preserves the
jump-buffer fields and VC20 cookie, while the real SDK setjmp.h supplies a
complete 64-byte x86 `_JUMP_BUFFER`/jmp_buf and cdecl longjmp declaration.
The probed cookie and old-unwind fallback do not establish the version or
extent of a live original saved buffer. The natural `probes/VC7JumpUnwindLayout.cpp` cold-builds an 88-byte layout array
with all eleven buffer offsets, six-word unwind-data size, real NT_TIB FS
exception-list offset and SDK exception/filter constants. All 72 actual
included headers and the complete exsup.inc are hash-pinned. The probe uses
complete actual SDK types and independent behavior controls, without defining
an original game owner or inventing private callback layouts.

Eight complete natural SDK jump/capture/result/member/SEH/filter/finally
controls / 338 bytes / twelve fields replay. Both generated whole scope data
sections / 24 bytes / three fields replay. All generated code sections are
covered by complete own AUX extents; there are no orphan code carriers in
this probe. Debug controls can retain source-emitted returns even under a
noreturn declaration; emitted body observations are recorded faithfully.
VC7.1 build 3077 and all explicit flags remain per-probe reproducibility
settings, not an executable-wide target compiler profile.

Thirty-six regression checks reject omitted final RET/filter/handler code,
wrong cleanup or exception policies, incomplete scopes, lost saved-register/
return/cookie/normalization behavior, invented callback identity and wrong ABS
provenance. Synthetic real COFF records and decoded segment instructions
exercise absent/undefined/static/duplicate/nonzero ABS definitions, referring
record identity, FS-versus-GS and actual displacement placement. All 1,018
public checks pass. The complete new/retained cold evidence replay passes once,
followed by canonical ledger write/read-back guards. Target/project/query
attestation, all 872 recorded authored extents, unchanged exact inputs,
progress/scanner freshness and whitespace checks pass locally. Totals are
3,436 resolved (919 authored, 1,942 library, 575 compiler), 915 pending and
2,517 excluded. Source/mapping/exact remains 60 / 9,883 bytes; recorded authored
extents remain 872 / 1,952,956 bytes and the provisional denominator is
1,965,299. All exact inputs/rows remain unchanged from R139 db26a05, preserving
its 60/60 cold proof across eleven objects. No affected exact unit needs a
repeat build. The public MCP acceptance waiver remains in force; the no-auth
route and private random path remain unchanged. Private evidence is untracked.

## R145 — Complete small-block heap integrity worker

R145 resolves `0x0064AFC5` / complete 793-byte `___sbh_heap_check` as a
library origin. Replay `scripts/repo-python scripts/verify-small-heap-integrity-origins.py`
with `config/small-heap-integrity-origin-evidence.json`. The complete own COFF
AUX agrees with the provisional extent through `0x0064B2DD`: all 61 branches,
both early/shared epilogues and every final error-return tail are retained.
No interior candidate is present, no wrapper is invented and no source,
mapping or exact reconstruction credit is assigned.

**Target and source observations.** The worker checks the full header range,
each REGION, committed groups and their eight pages, entry front/back tags,
allocated counters, 64 free-list size classes, links/counts/closure and final
group/header allocation vectors. Actual supplied winheap.h defines HEADER
20 bytes, REGION 16,836 bytes, GROUP 516 bytes, ENTRY 12 bytes, LISTHEAD eight
bytes and ENTRYEND four bytes. The allocation group spans 32,768 bytes, each
page 4,096 bytes and each region 32 groups. Page entries start at +12; valid
sizes are aligned to 16 bytes with a 16-byte minimum and 4,080-byte maximum.
Allocated entries are limited to 1,024 bytes. A clear most-significant commit
bit selects a committed group; low front-tag bit one marks an allocated entry.
Free-list class is `(size >> 4) - 1`, upper-clamped to 63. Source returns zero,
-1, -2 and -4 through -17; no -3 result is invented. These are static target/
vendor observations, not an assertion that the live game heap is valid.

All eight DIR32 fields have independent complete provenance. Three real
indirect calls target IsBadWritePtr's KERNEL32.dll IAT slot `0x00657154`:
header count times 20, REGION size 16,836 and group range 32,768. Five fields
bind `___sbh_cntHeaderList` / `0x0068FA60` and `___sbh_pHeaderList` /
`0x0068FA64`. Each has one actual external four-byte tentative COMMON record
in the entire pinned archive, sbheap.obj member 827680. The verifier scans
all members for nonzero COMMON/strong alternatives and rereads complete
source/member records. These are not initialized source pointers. Their
actual complete PE storage is in the writable loader zero-fill tail of .data.
Both independent bindings retain R120's already accepted heap provenance and
its full cold dependency replay. Original external linker inputs beyond the
supplied archive, live pointers/counts/contents and API outcomes remain unknown.
The absence of ordinary Ghidra callers grants no ownership or unused-code claim.

**Independent compiler evidence.** The supplied complete read-only sbheap.c
was cold-built with pinned VC7.1 build 3077 using explicit `/O1 /Ob1 /Gy /Zi
/GS /D_CRTBLD /D_MT` and the actual CRT source include path. Its selected
complete own-AUX function reproduces all 793 source bytes and all eight typed
field records from the archive. Both archive and cold C bodies are linked
from the independently resolved COMMON/API destinations and compared against
every target byte, with no masked or prefix acceptance. The other functions
and data emitted by that translation unit gain no reviewed origin credit.
The complete source, winheap.h and all 72 actual included headers are pinned.
These flags are per-control reproducibility settings, not an executable-wide
compiler profile or a claim about original private declarations.

The natural `probes/VC7SmallHeapIntegrityLayout.cpp` independently cold-builds
a complete 152-byte layout array and six complete range/entry/class/commit
controls / 217 bytes / three API fields. Every allocated probe code/data
section is accounted for; no orphan data or no-AUX code carrier is present.
Its complete actual vendor/SDK types do not define a reconstructed game owner.
Thirty regression checks reject shortened extents, missing epilogues/branches/
API calls, wrong COMMON definitions/storage/alternatives, lost retained heap
context, changed vendor reproduction inputs/layout/bit/class semantics and
invented runtime knowledge. Independent linker fixtures exercise actual
addends, full extents, wrong destinations, overlaps and missing provenance.

The complete new/retained cold evidence replay passes, followed by canonical
ledger write/read-back. All 1,048 public checks, authored-extent verification,
target/project/query attestation, progress/scanner freshness and whitespace
checks pass locally. Totals are 3,437 resolved (919 authored, 1,943 library,
575 compiler), 914 pending and 2,518 excluded. Source/mapping/exact remains
60 / 9,883 bytes. All tracked exact inputs and 60 accepted rows remain
unchanged from R139 db26a05, preserving its 60/60 cold proof over eleven
objects; no affected exact unit requires replay. Recorded authored extents
remain 872 / 1,952,956 bytes and the provisional denominator is 1,965,299.
Public MCP acceptance remains waived. The no-auth route and private random
path remain unchanged; private logs/objects/diagnostics remain untracked.

## R146 — Complete power dispatch and both math parents

R146 resolves four existing candidates as library origins: `0x00643770` /
complete 59-byte `__CIpow`, `0x0064DC60` / complete 2,886-byte
`__CIpow_pentium4`, its actual exported `__pow_pentium4` entry at
`0x0064DC79` / +25, and the actual static `start` entry at `0x006437CD` /
+34 inside the full 527-byte `__CIpow_default` parent. The latter extends
through its whole 493-byte shared tail. Replay
`scripts/repo-python scripts/verify-power-math-origins.py` with
`config/power-math-origin-evidence.json`. No source, mapping or exact credit
is assigned; both interior entries remain evidence-backed labels, without
invented independent AUX records or canonical private declarations.

**Complete extent and source-family reconciliation.** The provisional CI
wrapper was 84 bytes, crossing into the fallback's 25-byte CI prelude. Its
own AUX is 59 bytes. The provisional SSE parent was only 25 bytes; its own
AUX is 2,886, containing every exceptional/shared/return tail and the existing
+25 entry. The original 221-byte fallback core candidate is the real source
`start` label at +34; its complete defining parent retains the entire 493-byte
continuation through `0x006439B9`. These reconciliations compare full defining
owners, never convenient truncated extents. The entire 650-byte source code
carrier at `0x00643730` contains a 63-byte C wrapper, one actual NOP with a
zero-length `_$$$00002` AUX, the 59-byte CI wrapper and the 527-byte default
parent. The alignment byte gains no candidate credit. Non-inventory complete
source controls remain controls, including the real C default entry at +25.

The complete atan/log/log10 CI wrappers are each 59 bytes and indistinguishable
outside their two typed fields. Their whole defining code carriers are
282 / 336 / 336 bytes and differ at 106 / 146 / 146 non-field positions.
R146 retains those complete negative alternatives. The actual typed SSE
operation binds the complete pow parent; both default and SSE source owners
match completely with independent fields. This distinguishes pow without
inferring ownership from a library child or a matching wrapper prefix.
Original handwritten math assembly implementations are unavailable; complete
pinned archive COFF and independent real SDK controls supply the evidence.

**Target dispatch and private ABI observations.** The CI wrapper checks the
actual SSE dispatch state, MXCSR exception-mask bits `0x1F80` and x87
exception-mask bits `0x7F`. It restores its eight-byte scratch stack before
tail transfer; disabled or unsuitable states reach the full x87 fallback.
The SSE CI prelude aligns its stack, swaps the x87 pair, stores both doubles
and calls the actual exported +25 stack entry. All sixteen SSE RET sites and
62 branches remain in the full parent. The default CI path marshals its pair,
loads the high argument word in EAX and calls `start` +34; the exported C path
uses the complete fload helper and falls through that same source entry.
Its full default-control-word checks, special values/error routes, four RET
sites and 33 branches remain. SDK public pow/matherr/controlfp controls do
not supply invented private CI/helper prototypes. Live dispatch state,
control words, inputs, numerical accuracy and runtime outcomes remain unknown.

Six whole defining data sections / 14,862 bytes / four fields replay. The
pow constant/table source section is 14,640 bytes at `0x00663A00`, containing
all 21 actual named definitions, complete reciprocal/log/exp tables and masks.
Its SIGMASK anchor is interior at +14,480 / `0x00667290`; comparison starts
at the real whole section base. No single-mask prefix or guessed array count
substitutes for the whole table. Full default-name, fastflag, x87 constants,
return-dispatch pointers and floating adjustment state also replay. Every
code/data pointer reaches its actual complete source owner and instruction
entry. The SSE dispatch state is the unique four-byte tentative COMMON from
cpu_disp.obj at `0x0068FBA0`, with whole-archive alternatives, complete loader
zero-fill and independent retained R130 provenance. Original external linker
inputs and live mutable state are not inferred.

The two own-AUX primaries cover 2,945 bytes / 61 fields. Five whole auxiliary
controls cover 787 bytes / 32 fields. Nine whole independent retained anchors
cover 1,957 bytes / 66 fields, including complete libm error, load/control-word,
argument-error, pow helper and enclosing x87/return-dispatch owners. The two
non-inventory anonymous parents and fast-exit control retain their full R130
source identity; no new inventory credit is invented. Full R130 and its
independent dependency chain cold-replay. All newly reviewed own bodies and
the full carrier are linked from independently defined fields and compared
against every byte, unmasked. Every actual local/shared/direct edge is checked
against complete source and target instruction starts.

**Compiler observations and local acceptance.**
`probes/VC7PowerMathLayout.cpp` uses complete actual SDK/vendor records and
public ABI/intrinsic controls. Its 104-byte layout includes the real 32-byte
_exception, ten-byte FP80, full field offsets and math/exception/control-word
constants. All 77 actual included headers are pinned. Five complete natural
controls / 160 bytes / three fields cold-build; every allocated probe code/
data section is accounted for, with no orphan sections or game-owner layout.
Flags are explicit per-control reproducibility settings under VC7.1 build
3077, not an executable-wide compiler claim. Thirty-nine regression checks
exercise full extents/tables/source alternatives, real shared entries/dispatch
contracts and actual independent DIR32/REL32 arithmetic, typed source symbols,
field ranges, overlaps and complete linked-byte preservation.

The new/retained cold evidence replay passes, followed by canonical ledger
write/read-back. All 1,087 public checks, target/project/query attestation,
authored-extent verification, unchanged exact inputs, progress/scanner freshness
and whitespace checks pass locally. Totals are 3,441 resolved (919 authored,
1,947 library, 575 compiler), 910 pending and 2,522 excluded. Source/mapping/
exact remains 60 / 9,883 bytes. All exact inputs and 60 accepted rows remain
unchanged from R139 db26a05, preserving its 60/60 cold proof across eleven
objects. No affected exact unit requires replay. Recorded authored extents
remain 872 / 1,952,956 bytes; the provisional denominator is 1,965,299.
The public MCP acceptance waiver remains in force. The no-auth route/private
random path remain unchanged; private logs, objects and diagnostics are untracked.

## R147 — Complete acos parent and actual shared core

R147 resolves the two handoff candidates as library origins: `0x00643B10` /
complete 203-byte `__CIacos`, and `0x00643B2D` / actual source static `start`
+29 with its entire 174-byte shared continuation. Replay
`scripts/repo-python scripts/verify-acos-math-origins.py` with
`config/acos-math-origin-evidence.json`. No source, mapping or exact credit is
assigned; original private declarations and executable symbol names remain
provisional. The core is an actual entry in the complete parent, without an
invented independent AUX or complete game-owner layout.

**Extent reconciliation and target behavior.** The provisional parent was a
20-byte CI prefix; its complete own AUX is 203 bytes through `0x00643BDA`.
The real exported `_acos` C entry is +20, and static `start` is +29. The CI
path stores ST0 without popping into twelve-byte scratch space, calls the
complete checkTOS helper, calls static start and restores the scratch stack.
The C entry points EDX at its stack argument, calls the complete fload helper
and falls through the same static entry. The core's former 12,494-byte span
was a provisional Ghidra boundary running through many unrelated contexts.
The actual complete shared continuation is 174 bytes through the parent's
final RET. Exactly these two ledger rows change; every other origin row,
candidate and independently accepted extent is preserved. The complete
203-byte parent is compared, not a shortened selection from the huge span.

Incoming helper EAX/EDX and ZF are part of the actual private protocol.
PUSH EDX / WAIT / FNSTCW preserve the flags before the actual JE special-value
route; no ordinary C prototype is invented for that flags-dependent entry.
The full default-control-word check uses `0x027F`. The observed ordinary path
computes `(1+x)*(1-x)`, takes SQRT, exchanges the x87 pair and uses FPATAN.
Complete high/fraction/sign tests select FLDPI for the -1 endpoint and FLDZ
for +1. NaN conversion calls the actual complete helper, while invalid/range
paths load the extended-precision indefinite constant and retain complete
one-argument error handling. The two fastflag routes reach the same complete
fast-exit owner. Operation code 13 and the actual operation-name context are
preserved. Both RET sites and all fourteen branches replay. These are static
source/target observations; numerical accuracy, live classification/control
state, NaN payloads and runtime matherr/exception outcomes remain unknown.
The lack of ordinary callers grants no unused-code or ownership inference.

**Independent complete ownership and data evidence.** All thirteen typed
fields are linked from independently defined whole code/data owners, then
every relocated source byte is compared unmasked with the target. Seven
whole retained FP anchors / 252 bytes / three fields preserve checkTOS,
fload, load-CW, fast-exit, math-exit, QNaN conversion and one-argument error
owners. Their canonical origins remain unchanged. The non-inventory fast-exit
source retains its actual complete R146/R130 context, without new candidate
credit. Full R146 and its independent math/runtime dependency chain cold-replay.

Three whole defining source data sections / 60 bytes are preserved: the
complete eight-byte loader-zero fastflag storage at `0x0068E2C0`, complete
eight-byte operation-name section at `0x00670110`, and whole 44-byte x87
constant/classification section at `0x00670270`. No four-byte fastflag, name
prefix or single ten-byte indefinite value substitutes for its whole defining
section. Complete initialized bytes, source records, actual writable target
storage and loader zero-fill are checked. Original handwritten acos source is
unavailable; complete pinned archive COFF and independent SDK controls supply
the evidence without claims about original external inputs or live state.

**Compiler controls and acceptance.** `probes/VC7AcosMathLayout.cpp` uses
complete actual SDK math/exception/FP80 records and public acos/matherr/
controlfp declarations. Its 88-byte layout and five complete public ABI/range/
NaN/control-word controls / 157 bytes / five fields cold-build. Both generated
whole eight-byte positive/negative-unit sections are covered; all code/data
sections are accounted for and no orphan code carriers are emitted. All 74
actual included headers are pinned. Private intrinsic/helper declarations
remain unset. Explicit flags under VC7.1 build 3077 are per-control
reproducibility settings, not an executable-wide compiler profile.
Thirty regression checks reject prefix/huge-span acceptance, missing shared
entries/returns, partial state, lost helper flags, wrong endpoint/NaN/error
routes, incomplete generated constants and invented runtime/private ABI claims.

The complete new/retained cold evidence replay passes, followed by canonical
ledger write/read-back and exact two-row/prior-origin preservation guards.
All 1,117 public checks, authored-extent verification, target/project/query
attestation, unchanged exact inputs, progress/scanner freshness and whitespace
checks pass locally. Totals are 3,443 resolved (919 authored, 1,949 library,
575 compiler), 908 pending and 2,524 excluded. Source/mapping/exact remains
60 / 9,883 bytes. All exact inputs and sixty accepted rows remain unchanged
from R139 db26a05, preserving its 60/60 cold proof over eleven objects; no
affected exact unit requires replay. Recorded authored extents remain
872 / 1,952,956 bytes; the provisional denominator remains 1,965,299.
The public MCP acceptance waiver remains in force, with the existing no-auth
route/private random path unchanged. Private logs/objects/diagnostics remain
untracked. The complete-origin objective remains unfinished.

## R148 — Complete floor dispatch and defining source carrier

R148 resolves the existing `0x006439C0` candidate as library origin `_floor`.
Its complete own COFF AUX is 64 bytes through `0x006439FF`; the former
289-byte extent is the entire defining carrier containing the contiguous
225-byte `__floor_pentium4` at `0x00643A00`. The complete 289-byte carrier
is compared without masking or truncation. The SSE owner has no inventory
candidate and earns no additional credit. Replay
`scripts/repo-python scripts/verify-floor-math-origins.py` with
`config/floor-math-origin-evidence.json`. Exactly one existing origin row
changes; every independently accepted owner is preserved. There is no
source, mapping, private ABI or exact credit.

**Whole operation and provenance.** The wrapper checks the actual SSE state,
MXCSR mask `0x1F80` and x87 mask `0x7F`, restores its eight-byte scratch area,
and selects the actual default tail or complete SSE owner. The default
`0x0064E980` / 211-byte `__floor_default` retains R139; the complete 654-byte
libm error owner retains R130. Their combined 865 bytes and 37 fields have
independent retained source evidence. Full R146 and R139 cold controls replay
before acceptance, preserving all prior origins. All ten wrapper/SSE fields
bind independently defined whole code/data/COMMON owners before complete
unmasked comparison. The unique whole-archive SSE COMMON definition remains
the independently retained four-byte CPU-dispatch owner and actual loader
zero-fill region; its original external inputs and live value remain unknown.

The complete SSE control handles positive/negative exponent thresholds,
truncation and negative fractional correction, both signed-zero routes,
NaN classification and operation code 1005 (`0x3ED`) at the actual complete
error worker. All six branches and five RET sites are retained. These are
static source/target observations, not claims about runtime numerical
accuracy, NaN payloads, live rounding state or matherr/exception outcomes.
The two ordinary game callers establish no ownership by themselves.
The complete 80-byte defining constant section begins at `0x00661190`:
One, Bns, NegOne, NegZero and S occupy offsets 0/16/32/48/64. The actual Bns
reference is an interior anchor at +16, not the start of a single-value
comparison. All source definitions and every initialized byte are preserved.

Complete ceil and modf alternatives retain their whole 285-/328-byte source
carriers. Their wrappers have the same non-relocation shape, while their
whole carrier bodies differ at 30/224 non-field positions. The floor identity
therefore requires both the actual whole SSE operation and independently
accepted default owner. A shared wrapper shape or reviewed child alone
cannot substitute for the complete operation/source binding.

**Cold controls and acceptance.** `probes/VC7FloorMathLayout.cpp` uses actual
complete SDK exception/FP80 records and public math/classification/control
word/SSE declarations. The complete 84-byte layout and six natural controls
cover 180 bytes and six fields; all 77 included headers are pinned. Every
emitted code/data section is accounted for, without an orphan carrier.
Per-control VC7.1 build 3077 flags are reproducibility settings, not proof
of an executable-wide compiler profile. Thirty-one regression checks guard
whole extents/carriers/constants, actual masks/dispatch, signed fraction/zero,
NaN/error paths, independent retained owners and unknown runtime/private ABI.

The complete new and retained evidence cold-replay passed before canonical
write/read-back; exactly one row changed and all unrelated rows were checked
against HEAD. All 1,148 public checks, authored-extent verification,
target/project/query attestation, scanner/progress freshness, exact-input
preservation and whitespace checks pass locally. Totals are 3,444 resolved
(919 authored, 1,950 library, 575 compiler), 907 pending and 2,525 excluded.
The 60 source/mapped/exact functions / 9,883 bytes and every exact input
remain unchanged from R139 db26a05, preserving its 60/60 cold replay across
eleven objects; no affected exact unit needs another replay. Recorded
authored extents remain 872 / 1,952,956 bytes, with the provisional exact
coverage denominator 1,965,299. The public MCP waiver remains in force;
the existing no-auth route and private random path remain unchanged.
Private logs, generated objects and diagnostics remain untracked. The
complete-origin objective remains unfinished.

## R149 — Complete deque size families and shared receivers

R149 resolves six library origins / 102 bytes: `0x004094B0`, `0x00414430`,
`0x00414620`, `0x00414810`, `0x0041DD50` and `0x0045BF50`. Each complete
17-byte no-field body compares unmasked with all thirteen actual VC7 deque
size source alternatives. Replay
`scripts/repo-python scripts/verify-deque-size-context-origins.py` with
`config/deque-size-context-origin-evidence.json`. Original element types,
folding/aliasing, private declarations and complete game owner layouts remain
unknown. There is no source, mapping, private ABI or exact credit.

**Independent ownership context.** Identical getter bytes alone are
insufficient. Six complete independently authored parents / 5,610 bytes
retain their full extents, control flow and original ownership. Exact,
uninterrupted receiver-producing instruction sequences bind each candidate
to the same object as a separately complete, independently reviewed library
producer/consumer. Five contexts use their actual fixed global receivers;
the sixth proves equal owner/index/stride/field expressions through two
register variants. The observed twenty-byte container stride and +4 member
position do not establish a complete game class layout. Changing the owner,
index, field, direct destination or receiver-producing sequence invalidates
the proof. No origin follows from a game caller or reviewed child by itself.

The four complete push_back and two complete at anchors retain R072/R078
source and origin records. Their full cold verifiers replay serially, together
with the independent complete R110/R113 source-typed game/deque graphs.
No existing anchor is reclassified, renamed or assigned additional credit.
The target caller observations remain separate from the natural complete
SDK source controls and original-type inference.

**Compiler controls and acceptance.** `probes/VC7DequeSizeContexts.cpp` uses
thirteen real complete SDK deque specializations and natural const-receiver
size calls. All 26 emitted functions / 390 bytes cold-build with their own
complete AUX, source hashes and every typed field retained. The complete
32-byte readonly defining layout section establishes actual SDK container,
iterator and size-type records. Every emitted code/data carrier is accounted
for; all 27 actual included headers are pinned and checked against the cold
compiler include list. Per-probe VC7.1 build 3077 flags remain reproducibility
settings, not an executable-wide compiler inference. Fifteen regression
checks guard the full source family/layout, uninterrupted equal receivers,
independent anchors/cold proofs and pending nested origins.

Exactly six existing canonical rows changed after the complete new and
retained cold proof passed; write/read-back preserves every unrelated row
and all candidate extents. All 1,163 public checks, authored-extent verification,
target/project/query attestation, scanner/progress freshness, unchanged exact
inputs and whitespace checks pass locally. Totals are 3,450 resolved
(919 authored, 1,956 library, 575 compiler), 901 pending and 2,531 excluded.
The 60 source/mapped/exact functions / 9,883 bytes and all exact inputs remain
unchanged from R139 db26a05, preserving its 60/60 cold replay over eleven
objects; no affected exact unit needs replay. Recorded authored extents remain
872 / 1,952,956 bytes; the provisional coverage denominator is 1,965,299.
The public MCP waiver and existing private no-auth route remain unchanged.

**Retained nested uncertainty.** `0x00421550` and `0x0045DD50` remain pending.
A separate private natural nested-deque source control reproduces the entire
66-byte `0x0045DD00` parent and complete 45-byte `0x004215C0` back worker,
then follows a diagnostic graph of 43 complete bodies / 2,562 bytes / 103
fields and nine original external snapshots. This is source association,
not accepted independent provenance: nested/EH code/data bindings still
need complete reconciliation. The parent, back worker and other unknown
iterator controls receive no ownership credit. Their actual complete bodies,
original ledger extents, private declarations and prior owners are preserved.
The complete-origin objective remains unfinished.

## R150 — Complete nested deque code, data and EH provenance

R150 resolves the two complete 17-byte size candidates `0x00421550` and
`0x0045DD50` as library origins / 34 bytes. Replay
`scripts/repo-python scripts/verify-nested-deque-size-origins.py` with
`config/nested-deque-size-origin-evidence.json`. The actual nested SDK source
has a twenty-byte outer container holding complete twenty-byte inner SDK
containers. Original element definitions, folding, private declarations and
complete game owner layouts remain unknown. There is no source, mapping,
private ABI or exact credit; no auxiliary owner is reclassified in this batch.

**Independent actual receivers.** The entire independently authored
2,301-byte R070 parser preserves its observed owner +0x7D0 outer receiver for
back and size. Back-returned EAX is transferred directly into ECX for the
independently cold-replayed complete R072 byte push_back producer. The entire
66-byte count observation follows the signed-short index map, rejects a
negative mapped index, calls the actual outer at owner and transfers its
returned EAX into ECX for the inner size call. The natural source model uses
an observed 1000-short index map and real complete nested SDK containers;
it is a synthetic observation model, not a recovered complete game owner.
Actual uninterrupted receiver/returned-object instructions, full parent
bytes and complete control flow are checked. Identical getter bytes or a
reviewed library child alone establish neither origin.

**Whole independently linked provenance.** Fifty-three complete code owners /
2,980 bytes and all their typed fields are cold-linked through separately
complete source code/data definitions or explicit retained whole controls.
Every relocated byte is compared unmasked; target-derived field solving is
not used by the acceptance linker. Real own AUX extents are distinguished
from the few complete compiler-emitted code sections without AUX. The whole
string _Copy body and actual internal table/catch entries remain intact;
all original interior candidates and ledger extents are preserved.

Seventeen entire defining data sections / 524 bytes retain the complete
27-byte invalid-deque-subscript literal, out_of_range throw/catch information,
three complete type descriptors, two whole virtual tables, npos and all five
EH metadata owners. Five complete EH code carriers / 82 bytes preserve actual
cleanup/handler partitions and independent R020 frame records. FuncInfo is
an interior source anchor: the actual Xran owner is 36 bytes from 0x0066886C,
not a selected 28-byte header; the shared _Copy scope owner is the entire
132-byte section. Code/data callbacks bind actual complete owners, including
the independently emitted 23-byte SDK string destructor. Both actual weak
vector-deleting references retain their complete strong fallback records.
The whole type_info virtual table and runtime exception/frame-handler owners
retain the complete independent R119 source/data evidence; nine original
R113 external snapshots preserve their prior status, including the two
unresolved string throw workers. Live exception/cache outcomes remain unknown.

The existing R032 vector/length-error shape observation at 0x00421B70 is
preserved unchanged. It does not identify the actual operation: the new whole
literal and type/throw data bind out_of_range independently. The existing
library origin remains accepted, with the legacy name/source shape explicitly
separate from the stronger new operation evidence.

**Controls and acceptance.** `probes/VC7NestedDequeSizeContexts.cpp` cold-builds
all 82 ordinary emitted functions and eighteen entire emitted data sections,
including the complete 40-byte SDK/nested/iterator/observed-index-map layout.
All 27 actual included headers are pinned; every code/data carrier is covered.
The VC7.1 build 3077 flags are per-probe reproducibility settings. Full R149
and R119 cold evidence replay preserves prior deque/runtime/exception proofs.
Twenty regression checks guard complete extents/sections, actual nested and
returned-object typing, source/legacy separation and independently linked
unmasked fields, including PC-relative arithmetic, missing owners and overlap.
Pure receiver/producer read-back guards do not change the cold source,
headers, profile, fields or emitted data.

Exactly two existing canonical rows change after the complete cold evidence
passes; write/read-back checks every unrelated row against HEAD. All 1,183
public checks, authored-extent verification, target/project/query attestation,
scanner/progress freshness, exact-input preservation and whitespace checks
pass locally. Totals are 3,452 resolved (919 authored, 1,958 library,
575 compiler), 899 pending and 2,533 excluded. The 60 source/mapped/exact
functions / 9,883 bytes and every exact input remain unchanged from R139
db26a05, preserving its 60/60 cold replay across eleven objects; no affected
exact unit needs replay. Recorded authored extents remain 872 / 1,952,956
bytes; the provisional exact coverage denominator remains 1,965,299.
The public MCP waiver and private no-auth route remain unchanged. Private
logs, exploratory controls and objects remain untracked. The complete-origin
objective remains unfinished.

## R151 — Complete nested deque helper families

R151 resolves four existing library candidates: outer back `0x004215C0`
(45 bytes), mutable iterator dereference `0x00421FC0` (19), iterator
subtraction assignment `0x00422540` (27) and const iterator dereference
`0x00422560` (83). All 174 bytes retain their original complete extents.
Replay `scripts/repo-python scripts/verify-nested-deque-helper-origins.py`
with `config/nested-deque-helper-origin-evidence.json` and the natural SDK
controls in `probes/VC7NestedDequeHelpers.cpp`.

Thirteen real SDK element families preserve four complete positive graphs:
twenty-byte observation records and nested byte, word and pointer deques.
Each graph contains nine independently complete code owners / 368 bytes;
all four graphs / 36 source bodies / 1472 bytes compare unmasked after every
actual typed call is bound through its complete callee. Original element
types and folding remain unknown. Back reaches end, binary iterator minus
and mutable dereference; mutable dereference reaches the actual const owner.
The original five accepted dependency origins and all their extents remain
unchanged. Full R150 code/data/EH/receiver provenance cold-replays, including
the independently authored complete parser and its actual returned-inner
byte producer; a reviewed child alone does not establish a parent origin.

Nine rejected full type graphs retain actual differing const-dereference
owners. Byte/word/dword/pointer and eight-byte record owners have different
complete extents; sixteen-, twenty-four-, thirty-two- and sixty-four-byte
record owners retain the same 83-byte extent but differ in three, one, three
and three actual bytes respectively. Equal-shaped back/mutable/subtraction
operations alone do not identify a complete type family. No prefix or masked
comparison grants acceptance. Source `??Ziterator` is signed subtraction
assignment with a reference return, not iterator decrement; its actual NEG,
addition-assignment callee, stack cleanup and whole control flow are retained.

The pinned VC7.1 build 3077 cold-build covers all 169 ordinary emitted
functions / 5537 bytes, the entire 32-byte SDK layout section and 27 actual
included headers, with no orphan ordinary code/data carriers. Flags are
per-probe reproducibility settings. Eighteen regression checks guard complete
graphs/extents, independently typed callees, actual call sites, signed
overloads, rejected type differences and retained whole provenance.

Exactly four canonical rows change after complete cold acceptance; read-back
checks every unrelated row against R150 HEAD. All 1201 public checks,
authored-extent verification, attested target/project/queries, fresh scanner
and progress, exact-input preservation and whitespace checks pass locally.
Totals are 3456 resolved (919 authored, 1962 library, 575 compiler), 895
pending and 2537 excluded. The 60 source/mapped/exact functions / 9883 bytes
and all exact inputs remain unchanged from R139 db26a05; its 60/60 cold
replay across eleven objects remains applicable. No affected exact unit
needs replay. Authored extents remain 872 / 1952956 bytes and the provisional
exact denominator remains 1965299. No source, mapping, private ABI or exact
credit is added. The synthetic 66-byte count observation remains unknown;
neither its model nor these SDK helpers recover the complete game owner.
Public MCP acceptance remains waived; the private no-auth route is unchanged.
Private logs, generated output and objects remain untracked. The complete
origin objective remains unfinished.

## R152 — Complete script count map policy and independent game context

R152 resolves the complete 66-byte `0x0045DD00` as authored, provisionally
named `FighterScript::CountPatternEntries`. Replay
`scripts/repo-python scripts/verify-script-count-origins.py` with
`config/script-count-origin-evidence.json`. This supersedes the unknown
ownership recorded for the synthetic R150 count observation; that earlier
complete source control and its original metadata remain unchanged.

**Observed target policy.** The actual signed-short argument indexes the
owner's short map. A negative mapped value returns zero in AX. Otherwise
the mapped value is passed to the actual outer at owner +0x7D0; returned
EAX becomes ECX for the complete inner size owner. Both internal branches,
the final RET 4, the full 66-byte extent and fourteen following alignment
bytes are checked. This is a domain-specific missing-entry policy over the
script map, not origin inferred from a reviewed SDK child or matching wrapper
shape. The provisional role describes observed behavior, not an original name.

**Independent producers and consumers.** Six entire previously authored
owners / 5729 bytes preserve their own hashes, complete CFG, original roles,
origin evidence and guarded switch tables: script initializer `0x00420440`
(R076), byte/word accessors `0x00420530` / `0x00420570` (R076), full parser
`0x00420880` (R070), action processor `0x0045CE10` (R065) and pattern chooser
`0x0045D810` (R045). Initializer iteration writes -1 to 1000 actual short
entries. Parser decimal accumulation checks ASCII digits and multiplies the
short label by ten; after appending an outer entry it stores outer size minus
one in that label's map slot. The two complete game parents contain eleven
actual count calls, three and eight respectively. Uninterrupted instructions
preserve their short arguments, the actual fighter owner +0x714 receiver and
signed AX result used in loop/range comparisons. Neither an accepted game
caller alone nor the old natural model decides ownership: the combined
independent producer/domain/consumer policy supports authored classification.

**Compiler observations and unknowns.** Complete R150 cold source/code/data/EH
provenance replays, including its whole natural synthetic Count body and
independently linked actual SDK callees. No new source or compiler profile is
introduced. Ordinary special-member synthesis does not supply this label-map
and missing-entry/count policy. This is a semantic ownership inference from
actual independent game state, not proof of original source spelling. Original
types, folding, declarations and complete game layouts remain unknown. The
count body has no local index bounds guard; the parser's short accumulation
does not prove malformed-input or overflow safety. No complete game owner is
instantiated. The old R150 unknown context is retained as historical evidence,
without rewriting prior accepted sources or origins.

Exactly one existing canonical origin/function row changes, and one complete
authored body/CFG record is appended. Read-back guards preserve every unrelated
row against R151 HEAD and require the unique new authored extent record.
The additional pure registration guard leaves all cold source/profile/fields
unchanged. Twenty regression checks guard complete bodies, real signed ABI,
map sentinel/domain/decimal writes, independent parent ownership, actual
returned-inner receiver, all game uses and unique authored registration.
All 1221 public checks, target/project/query attestation, authored extents,
fresh scanner/progress, exact-input preservation and whitespace checks pass.
Totals are 3457 resolved (920 authored, 1962 library, 575 compiler), 894
pending and 2537 excluded. Recorded authored extents are 873 / 1953022 bytes;
the provisional exact denominator is 1965365 bytes. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs remain unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No exact unit needs
replay; no source, mapping, private ABI or exact credit is added. Public MCP
acceptance remains waived and the private no-auth route is unchanged.
Private queries, logs and objects remain untracked. The complete-origin
objective remains unfinished.

## R153 — Complete script record buffer lifetime policy

R153 resolves two authored candidates: `0x00421200` / 24 bytes, provisionally
`FighterScript::InitializeRecordBuffer`, and `0x00421220` / 43 bytes,
provisionally `FighterScript::ReleaseRecordBuffer`. Original extents, all
returns/branches and following alignment remain intact. Replay
`scripts/repo-python scripts/verify-script-buffer-origins.py` with
`config/script-buffer-origin-evidence.json`. The natural source controls in
`probes/VC7ScriptBufferLifetimes.cpp` are complete synthetic observation
records, not recovered game declarations; no game source or exact unit is added.

**Independent game ownership context.** The entire independently authored
R070 parser / 2301 bytes preserves its original guarded switch, CFG and hash.
Eight actual local constructor/copy/release pairs retain the same local
receiver, actual R072 push_back producer and explicit cleanup. The full pointer
producer allocates the quoted text length plus one, stores returned storage
at record +4, reads that same pointer back, copies the substring and writes
the terminating byte. Complete R020 frame metadata and all eight eight-byte
record cleanup entries, plus the entire R037 44-byte scalar-deleting owner,
retain original evidence and extents. Those compiler contexts identify real
lifetime use; they alone do not identify a destructor's source ownership.

The accepted R072 producer is its complete 215-byte `DequeProbeRecord<8>`
control, an eight-byte byte-record model. Earlier "byte producer" wording
must not be taken as an original unsigned-char element declaration. The
actual game pointer/command observations and the synthetic nested R150 size
controls remain separate; those generic size bodies do not recover original
element types. All prior accepted source/control metadata and origins remain
unchanged. The actual buffer lifetime and parser protocol supply the additional
independent game policy evidence in this batch.

**Whole typed source controls.** Four guarded primitive-array constructor /
destructor families agree unmasked across all 67 bytes, totaling eight whole
source bodies / 268 bytes. Each destructor's actual field at +32 binds to
the independently complete five-byte archive array-delete owner at 0x0064169D
(delete2.obj, member 854462), then the unchanged complete accepted R142 scalar
delete owner at 0x00640F15 and R120 free owner / 113 bytes. Both five-byte
source owners compare unmasked through actual typed fields. Whole archive
members, source hashes, original accepted free boundary and every target byte
are read back; unchanged prior runtime inputs do not require another recursive
cold replay. The array-delete auxiliary retains its original unknown ledger
status and receives no new classification in R153.

The 43-byte guarded scalar-delete source has the same relocation-masked shape,
but differs in three actual relocation bytes after its independently typed
scalar-delete field is bound. It is rejected. A standalone 24-byte SDK auto_ptr
constructor differs in fourteen actual bytes; its complete destructor and
both implicit SDK/custom-owned record lifetimes have different extents.
The unguarded array destructor is a complete 34-byte owner, not a 43-byte
prefix match. Eight whole rejected controls preserve these genuine differences.
Raw implicit records emit no owning special-member policy. Under /Ob1 and
/Ob2, the complete emitted source inventories contain no own 24/43-byte
functions; inlined fragments cannot replace an entire target candidate.

The pinned build 3077 cold-builds all three explicit profiles: 90 ordinary
functions / 3897 bytes and all 107 entire ordinary code/data/EH sections /
4458 bytes, including seven complete EH code/data pairs and the full 40-byte
SDK/observation layout. All 24 actual included headers per profile are pinned.
Flags are per-probe reproducibility settings, not an executable-wide compiler
claim. Explicit null initialization and guarded array release, their independent
parser ownership policy and the differing bounded implicit/SDK alternatives
support authored inference. Original source spelling, names, types/folding,
complete game layouts and untested source alternatives remain unknown.

Exactly two existing canonical rows change and two complete authored body/CFG
records are appended; read-back preserves every unrelated row against R152
HEAD. Additional pure inventory/registration guards preserve all already cold
source/profile/field inputs. Twenty-three regression checks guard complete
extents/carriers/layouts, typed array/scalar separation, actual buffer writes,
paired lifetimes and independent original ownership/registration. All 1244
public checks, attested target/project/queries, authored extents, fresh scanner
and progress, exact-input preservation and whitespace checks pass. Totals are
3459 resolved (922 authored, 1962 library, 575 compiler), 892 pending and
2537 excluded. Recorded authored extents are 875 / 1953089 bytes; the exact
coverage denominator remains provisional at 1965432. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs remain unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No exact unit needs
replay. No source, mapping, private ABI or exact credit is added. Public MCP
acceptance remains waived; the private no-auth route is unchanged. Private
queries, diagnostics and objects remain untracked. The origin objective remains
unfinished.

## R154 — Complete allocation API provenance

R154 resolves three library owners, preserving their complete original extents:
scalar new at `0x0064159D` / 14 bytes, array delete at `0x0064169D` / 5 bytes,
and array new at `0x006416A2` / 5 bytes. Replay
`scripts/repo-python scripts/verify-allocation-api-origins.py` with
`config/allocation-api-origin-evidence.json`. Complete own-AUX code from the
pinned libcmt.lib new.obj, delete2.obj and new2.obj members compares unmasked
across all 24 bytes, including every actual typed relocation and return/tail.
The matching five-byte shapes alone provide no ownership proof.

Scalar new pushes the observed new-handler flag 1 and original caller size,
calls the independently complete accepted R120 `__nh_malloc` / 44 bytes, then
balances its cdecl stack. Array new's actual source field routes to that full
scalar-new owner; array delete routes to the different independently complete
R142 scalar-delete owner, then the existing whole R120 free owner. All archive
members, full source/target hashes and actual fields are pinned. Original
accepted callee evidence, boundaries and classification remain unchanged.
The full R120 allocation/handler/data/API/EH provenance and its retained cold
source dependencies replay successfully, followed by the complete R153 buffer
lifetime source profiles and independent whole parser/cleanup contexts.

Natural controls in `probes/VC7AllocationCalls.cpp` cold-build eight complete
SDK allocation/release functions / 196 bytes. Three distinct primitive/complete
observation array types route through array operations; explicitly declared
scalar storage operations route through the different scalar owners. All nine
ordinary code/data sections / 212 bytes, their complete definitions and typed
fields, the entire 16-byte observation layout and eight actual included SDK
headers are read back. Build 3077 and explicit /Od /Ob0 flags are probe
reproducibility settings, not an executable-wide compiler claim. Synthetic
observation records do not recover or instantiate incomplete game owners.
Original linker inputs, original game element declarations, user-installed
handlers and live allocation outcomes remain unknown.

Exactly three existing unknown canonical rows become library/excluded;
every unrelated row and authored body record is unchanged against R153 HEAD.
Nineteen regression checks reject incomplete owners/carriers, wrong typed
array/scalar destinations, altered handler/input protocol, skipped independent
provenance and exact credit. All 1263 public workflow tests, local attested
queries, authored extents, fresh scanner/progress, exact-input preservation
and whitespace checks pass. Totals are 3462 resolved (922 authored, 1965
library, 575 compiler), 889 pending and 2540 excluded. Recorded authored
extents remain 875 / 1953089 bytes; provisional exact coverage remains
9883 / 1965432. The 60 source/mapped/exact functions / 9883 bytes, all exact
inputs and R139 db26a05's 60/60 cold replay across eleven objects remain
preserved; no changed exact unit requires replay. No game source, mapping,
private ABI or exact credit is added. Public MCP acceptance remains waived,
and the private no-auth route is unchanged. Private queries, surveys and
objects remain untracked. The complete-origin objective remains unfinished.

A fresh private whole-own-AUX CRT survey identifies full diagnostic controls
for ui64toa / 27 bytes, SEH longjmp unwind / 27, FillZeroMan / 12 and finite /
21. A separate complete atox.obj check identifies the five-byte atoi owner
and its actual typed tail to accepted whole atol / 136 bytes. These five
candidates form the bounded R155 cohort; these diagnostics grant no origin.
Both 11-byte abs-shaped candidates have complete abs/labs source alternatives.
R129 already proves ordinary expression controls can also reproduce the
entire shape; preserve that ownership ambiguity instead of repeating an
acceptance from the new survey.

## R155 — Short CRT provenance and unsupported leaf ownership

R155 reviews five complete candidates / 92 bytes. Three gain library origin:
`0x006426A1` / 5 bytes (`_atoi` source association), `0x0064554E` / 27 bytes
(`__seh_longjmp_unwind@4`), and `0x00651D44` / 27 bytes (`__ui64toa`).
The entire 21-byte `0x00643FC6` finite association and 12-byte `0x0064F513`
FillZeroMan association remain unknown/pending. Replay
`scripts/repo-python scripts/verify-short-crt-origins.py` with
`config/short-crt-origin-evidence.json`. No original executable symbol or
private game declaration is established by these provisional archive names.

Every candidate's complete positive COFF AUX extent is extracted without a
size override. All target bytes agree unmasked with the pinned whole archive
source, including actual typed fields and final return/tail instructions.
The accepted atoi tail routes to independently complete R123 atol / 136 bytes;
the saved-context helper routes to unchanged R025 local unwind / 104 bytes;
the unsigned-wide formatter routes to unchanged R007 x64toa / 109 bytes and
its original typed unsigned division dependency. Whole original runtime
metadata and canonical evidence remain unchanged. Complete codepage/NLS,
jump/unwind, security/EH and runtime verifiers replay successfully, including
retained cold source/layout/data/API/EH dependencies and all 57 original whole
runtime bodies / 5641 bytes with 28 actual bindings.

**Complete SEH source carrier.** The saved-context helper is a positive
27-byte own AUX inside exsup3's larger source section. Its entire 265-byte
carrier compares unmasked: the eight-byte `VC20XC00` source marker, complete
230-byte original handler, full helper at offset 238 and all six actual typed
fields are retained. It reads actual SDK saved Ebp, Registration and TryLevel,
calls full local unwind with the real registration/try-level pair and restores
the frame with four-byte argument cleanup. The SDK saved-context declaration
and the whole source carrier independently corroborate this operation;
a library child or absent direct callers alone supplies no origin proof.

**Bounded pending controls.** The entire twelve-byte FillZeroMan source also
matches an ordinary natural source control clearing a complete three-word
observation with memset. The cold compiler emits all twelve identical bytes,
without any relocation masking. No actual direct caller or independent owning
context distinguishes the two sources, so library origin is withheld. Finite
has a complete 21-byte vendor/SDK association, while the ordinary exponent
expression emits a complete different 20-byte function. Its failed control
must not be compared against a twenty-byte target prefix, and it does not
exclude other original compiler/source variants or prove ownership. It also
has no observed direct caller or independent owning context and remains
pending. Both rows retain their original unknown origin records, empty owner
and proposed-name fields, and full extents; only durable evidence/notes change.

`probes/VC7ShortCrtCalls.cpp` cold-builds all eight complete SDK/source controls /
109 bytes and every one of nine entire ordinary code/data sections / 153 bytes.
The complete 44-byte layout freezes real 64-byte jump buffers, saved-field
offsets, actual primitive/observation sizes, JBLEN and floating exponent range;
all five actual SDK headers are pinned. The synthetic three-word observation
is not an original floating/game structure. Build 3077 and /O1 /Oi /Ob0 are
per-probe reproducibility settings; original flags/linker inputs, source
spelling/types and live decimal/radix/floating/jump outcomes remain unknown.

Exactly three canonical origins and five bounded function evidence rows
change against R154 HEAD; both pending origins, every unrelated row and all
authored records remain unchanged. Additional pure source/carrier registration
guards preserve all already cold inputs. Twenty-two regression checks reject
partial extents/carriers/layouts, wrong fields/SDK operations, altered saved
context and false pending/exact/ABI credit. All 1285 public workflow tests,
local target/project/query attestation, authored extents, fresh scanner/progress,
exact-input preservation and whitespace checks pass. Totals are 3465 resolved
(922 authored, 1968 library, 575 compiler), 886 pending and 2543 excluded.
Authored records remain 875 / 1953089 bytes; exact coverage remains provisionally
9883 / 1965432. All 60 source/mapped/exact functions / 9883 bytes and exact
inputs remain unchanged from R139 db26a05, preserving its 60/60 cold replay
across eleven objects. No affected exact unit needs replay. No source, mapping,
private ABI or exact credit is added. Public MCP acceptance remains waived;
the private no-auth route is unchanged. Private queries, diagnostics and objects
remain untracked. The complete-origin objective remains unfinished.

The next bounded R156 cohort is two previously unreviewed complete 211-byte
deque-like producers and their four 27-/29-byte allocation/construction
callees. Independent full R070 parser and R040 replay-file scanning parents,
plus unchanged full R071 grow-map owners, provide investigation context.
Diagnostic target observations show distinct 20-/60-byte element scales;
these sizes do not recover original element declarations. No next-cohort
classification follows from scanner rank or these source-shape observations.

## R156 — Complete paired deque producers and typed allocation/construction

R156 accepts six library owners / 534 bytes: the complete 211-byte producers
`0x004215F0` and `0x0042DBE0`, their 27-byte element-allocator wrappers
`0x00421EE0` and `0x0042E000`, and their 29-byte construction wrappers
`0x00421F00` and `0x0042E020`. Replay
`scripts/repo-python scripts/verify-paired-deque-producer-origins.py` with
`config/paired-deque-producer-origin-evidence.json`. The provisional names
describe verified SDK source associations, not original executable symbols.
Every accepted owner has its entire positive own COFF AUX extent; the full
branch/return and actual relocation inventory compares without masking.

**Independent original contexts.** The full unchanged R070 parser / 2301 bytes
calls the first producer at `0x00420CE4`, and the full R040 replay-file scan /
613 bytes calls the second at `0x0042D684`. Actual receiver/value instruction
windows and both parents' complete authored CFG/switch evidence are retained.
Both unchanged R071 growth owners / 511 bytes also compare completely. Source
typing distinguishes the element allocator from the separate pointer-map
allocator; calls continue through actual scalar-new and placement-new owners.
R154 allocation and R142 standard-exception verifiers cold-replay their
independently complete source/data/SDK/runtime dependencies. The retained
R150 nested-deque verifier also completes a fresh cold replay in this batch.
A game caller or an accepted library child alone does not establish ownership.

**Entire source and state.** `probes/VC7PairedDequeProducers.cpp` cold-builds
all 187 ordinary emission sections / 11917 bytes. The linked closure contains
162 entire code/EH sections / 11016 bytes and 22 complete data sections /
835 bytes. All 436 genuine typed fields resolve through complete independent
source definitions, source weak fallback metadata, original data owners or
retained external operations; all linked target bytes agree unmasked.
Where implicit SDK constructors or EH carriers have no positive own function
AUX, the entire defining code section is compared instead. Two genuine weak
references retain their complete strong fallback definitions and actual COFF
AUX metadata. RTTI/vtables, strings, exception state and the absolute FS
exception-list offset are kept distinct from ordinary executable functions.
Ten full original R020 registered frames retain unwind/try/catch/parent evidence,
including FuncInfo records inside larger complete data carriers.

The complete 32-byte layout records `[8,20,60,20,20,4,8,8]`; all 27 actual SDK
headers are pinned. The 20-byte observation contains a real SDK deque and the
60-byte observation is a complete synthetic file record. Their declarations
are source controls, not recovered game record types. The eight-byte inner
observation declares destruction through truthful C++ ABI and binds the
independently complete 43-byte authored R153 lifetime policy. Its authored
ownership remains separate from the SDK operations that invoke it. Original
element fields/declarations, spelling, linker inputs and live runtime outcomes
remain unknown. Build 3077 and /Od /Ob0 /Gy /GR- /GX /Zi /GS are explicit
per-probe reproducibility settings, not an executable-wide compiler claim.

**Shared tails and unchanged ledgers.** The SDK copy control at `0x00422A50`
compares its whole 241 bytes, and insertion at `0x00422D70` compares all 1545
bytes, including shared tails. Their historical provisional canonical extents
remain 195 and 1483 bytes, respectively, and both origins remain unknown.
Whole EH carriers likewise include their cleanup/dispatch tails without
altering historical compiler entry extents. These complete auxiliary source
associations grant no new boundary, authored/library/compiler classification,
source, private ABI, mapping or exact credit. Original opaque string-throw
workers and all other auxiliary canonical snapshots remain unchanged.

Exactly six origin rows and their six function evidence rows change against
R155 HEAD 9734107. All unrelated canonical rows and every authored record are
preserved. Twenty-seven regression checks protect entire AUX/code/data/layout
extents, actual typed operations, original parent and policy evidence, weak
fallbacks, whole shared tails and false ABI/exact credit. All 1312 public tests,
local target/project/query attestation, authored extents, fresh scanner/progress,
exact-input preservation and whitespace checks pass. Totals are 3471 resolved
(922 authored, 1974 library, 575 compiler), 880 pending and 2549 excluded.
Authored evidence remains 875 records / 1953089 bytes; provisional exact
coverage remains 9883 / 1965432. All 60 source/mapped/exact functions / 9883
bytes and all exact inputs remain unchanged from R139 db26a05, preserving its
60/60 cold replay across eleven objects. No affected exact unit needs replay.
Public MCP acceptance remains waived and the private no-auth route is unchanged.
Private queries, logs and objects remain untracked. The complete-origin
objective remains unfinished.

The next bounded R157 cohort is four still-unknown lower-level helpers /
213 bytes: `0x004228A0` / 20, `0x004228C0` / 108, `0x0042E4D0` / 20 and
`0x0042E4F0` / 65. R156 already retains their complete source controls, actual
calls and state, but gives them no classification. Use the accepted typed
allocator/construction parents as independent context and explicitly retain
ordinary authored allocation/placement/copy alternatives. Preserve the unknown
record-copy wrapper and full-copy/insertion parents; do not infer their origin
from these operations or treat the observations as recovered element types.

## R157 — Element operations with byte-equal ordinary source alternatives

R157 accepts four complete library owners / 213 bytes: SDK `_Allocate`
associations `0x004228A0` and `0x0042E4D0` / 20 bytes each, plus `_Construct`
associations `0x004228C0` / 108 and `0x0042E4F0` / 65. Replay
`scripts/repo-python scripts/verify-deque-element-origins.py` with
`config/deque-element-origin-evidence.json`. Every SDK owner and ordinary
control has its full positive own COFF AUX extent, without a size override.
All original extents, source/ABI fields and exact percentages remain unchanged.

**Positive provenance and explicit ambiguity.** Each actual original helper
has one observed caller: respectively the complete R156 element allocator
`0x00421EE0`, construction wrapper `0x00421F00`, element allocator
`0x0042E000` and construction wrapper `0x0042E020`. Independent full parent
source fields name the actual SDK element operation, distinguishing it from
the pointer-map allocator. The scalar operations call the unchanged whole
R154 scalar-new owner; construction routes through actual placement-new,
the full original queue-copy dependency and registered exception state, or
the complete fifteen-word file-record copy. Full R156 parent/source/code/data/
EH/runtime evidence cold-replays, including R154/R142 dependencies, unchanged
game/growth context and independently authored R153 inner destruction.

Four ordinary natural allocation and placement-copy controls in
`probes/VC7DequeElementAlternatives.cpp` cold-emit all 213 identical bytes.
Every real field is linked and compared unmasked. Body equality alone thus
cannot determine ownership. Library classification is an inference from
the independently complete accepted SDK parents, their real source-typed
calls and the unchanged full SDK source family, rather than from a short
body, adjacency or a library child alone. No original symbol, spelling or
record declaration is recovered, and untested original source/compiler
alternatives are not excluded. This evidence is stronger than the unrelated
R129/R155 leaf ambiguities that lack independent owning context; those prior
pending rows remain untouched.

**Whole ordinary EH and source.** The ordinary queue construction also
retains its full 27-byte cleanup/dispatch carrier and whole 36-byte exception
data, including unwind storage before its embedded 28-byte FuncInfo.
Together the six complete code/data controls cover 276 bytes and fourteen
genuine typed fields. The entire defining EH carrier is used where an
individual positive own function AUX is unavailable. Source definitions,
local-label offsets, field roles and destinations follow independently whole
retained owners; compiler-local labels belong to their own COFF object and
their generated numbers are not treated as cross-object global identities.
The new cold source freezes all 193 ordinary emission sections / 12193 bytes,
all 27 actual SDK headers and its actual included R156 observation source.
The original full 32-byte layout, 162 whole linked code/EH owners / 11016
bytes, 22 data owners / 835 bytes, 436 actual fields and ten full registered
frames remain protected by the retained cold verifier. These are origin
controls, not new exact units or reconstructed game owner layouts.

**Bounded canonical follow-up.** R156 retains its original immutable manifest.
Its snapshot verifier now permits only these four exact R157 transitions,
requiring the hash-pinned follow-up manifest, exact original snapshots and
exact new function/origin records. It does not skip arbitrary auxiliary
metadata or permit other new classifications. The transition guards and all
auxiliary snapshots are read back after acceptance. Only the final summary
wording changes after the unchanged cold proof; no source/profile/header/
relocation input or comparison behavior changes. Whole shared-tail copy/
insertion controls, record-copy ownership, interior catch rows, opaque throw
workers and authored lifetime policy keep their original classifications and
canonical extents. Ordinary source controls do not classify those owners.

Exactly four origin rows and their four function rows change against R156
HEAD 4608784; all unrelated rows and every authored record remain unchanged.
Twenty-eight regression checks protect full AUX/code/data/emission/header/
layout extents, real parent/operation roles, byte-equal alternatives, exact
bounded follow-up transitions and false source/private ABI/exact credit.
All 1340 public tests, local target/project/query attestation, authored extents,
fresh scanner/progress, exact-input preservation and whitespace checks pass.
Totals are 3475 resolved (922 authored, 1978 library, 575 compiler), 876 pending
and 2553 excluded. Authored evidence remains 875 records / 1953089 bytes;
provisional exact coverage remains 9883 / 1965432. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs are unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No affected exact
unit needs replay. Public MCP acceptance remains waived and the private
no-auth route is unchanged. Private logs, queries and objects stay untracked.
The complete-origin objective remains unfinished.

The next bounded R158 cohort is the complete queue copy/insertion source
family and its interior catch/shared-return candidates, plus the unresolved
record-copy wrapper. The original 195-/1483-byte parent candidates must be
reconciled against their whole 241-/1545-byte source owners before acceptance;
the 46-/48-/62-byte catch entries are interior source spans, not independent
whole functions. The 28-byte record-copy wrapper requires genuine implicit
versus ordinary explicit source controls. No classification follows merely
from these existing full source associations or the SDK children.

## R158 — Whole deque copy/insertion, interior catch policy and copy ambiguity

R158 reviews all six handoff candidates. Five gain library origin: the complete
SDK copy owner `0x00422A50` / 241 bytes, insertion owner `0x00422D70` / 1545
bytes, and three interior catch/source-policy candidates `0x00422B13` / 46,
`0x0042308D` / 48 and `0x0042333B` / 62. The complete 28-byte record-copy
wrapper `0x004229D0` remains unknown/pending. Replay
`scripts/repo-python scripts/verify-deque-copy-insert-origins.py` with
`config/deque-copy-insert-origin-evidence.json`. The two whole SDK owners
cover 1786 distinct bytes; the catch spans overlap them and are neither three
new whole functions nor additional source byte credit. Candidate counts and
complete function counts remain distinct.

**Required extent reconciliation.** The copy row's original 195-byte boundary
ended after the normal branch at `0x00422B11`, omitting its return through
`0x00422B24`. The full positive own COFF AUX and defining section cover all
241 bytes through `0x00422B40`. Insertion's old 1483-byte boundary similarly
omitted the final shared normal epilogue at `0x0042335F`; the complete positive
own AUX covers all 1545 bytes through `0x00423378`. The first insertion catch
also branches from `0x004230B8` to that same return. Both full owners decode
completely, end in their real RET and retain every internal branch target.
Canonical size/span_end change only for these two original parent rows.
Observed fifteen-/seven-byte CC alignment after the owners and the following
original candidates remain outside the accepted extents and unchanged.
The private Ghidra project is queried read-only and retains its original
split inventory; accepted canonical extents come from complete target CFG,
source AUX, actual state and byte comparison, not the initial Ghidra boundary.

**Interior library policy and compiler mechanics.** Original full R020 frames
`0x006556B0` / FuncInfo `0x00668930` and `0x006556C0` / `0x006689B4`
retain complete unwind, try, catch and parent registration evidence. Whole
80-/132-byte source data carriers include all state and handler tables.
Their three actual catch-all records name exactly the interior candidates,
with ranges 0/0/1, 0/0/1 and 2/2/3. Each candidate's entire observed span is
verified inside its whole compared parent; the 48-byte insertion span reaches
a shared epilogue beyond its own provisional span, which remains part of the
full 1545-byte owner. No individual full-function AUX is fabricated for a
catch label and no isolated prefix is accepted as a standalone function.

The SDK copy constructor explicitly calls `_Tidy` and rethrows on failure;
the bidirectional insertion source explicitly restores the old size by
`pop_front` or `pop_back` and rethrows. Whole source/body and all typed fields
establish that these are library source policies. Ghidra Catch names, absence
of direct callers and registration alone establish no origin. The compiler
frame/dispatch mechanics retain their independently reviewed compiler evidence;
the source rollback policy is not relabeled compiler-owned merely because
the compiler creates a local catch entry. Original game element destruction
retains its independent authored R153 provenance, with no inferred copy policy
or original record layout. Live success/failure and unwind outcomes remain
unknown.

**Complete implicit/explicit ambiguity.** The entire implicit record-copy
defining code section / 28 bytes agrees unmasked with the target. An ordinary
explicit copy constructor of a complete observation record emits all 28
identical bytes and the same real SDK deque-copy call. The latter has a full
positive own AUX; the implicit source control is compared as its entire
defining section where a complete positive function AUX is unavailable.
Full R157 construction and the whole SDK copy dependency establish operation,
not implicit-versus-authored ownership. The original record declaration and
source ownership therefore remain unknown. Only durable function evidence/
notes change; its origin row, empty name/owner/source/ABI fields and full
extent remain unchanged. Do not revisit it from a library child, scanner rank
or another same-shaped control without new independent ownership evidence.

`probes/VC7DequeCopyAlternatives.cpp` cold-builds all 194 ordinary sections /
12303 bytes and the whole 48-byte SDK/observation layout
`[8,20,60,20,20,4,8,8,20,20,20,8]`. Fourteen complete code/data/EH controls /
2416 bytes and all 104 genuine typed fields compare unmasked. This includes
the two whole SDK owners, full state/dispatch carriers, implicit/explicit
record constructors and complete ordinary placement-copy controls with their
entire exception carriers. All 27 SDK headers and the actual included R156
observation source are pinned. Complete R157/R156 source/code/data/EH/runtime
evidence cold-replays, including independent R154/R142 dependencies. Original
source spelling/compiler/linker choices and game types remain unknown;
build 3077 and the explicit flags are per-probe reproducibility settings.

R156/R157 manifests remain immutable. The R156 snapshot guard now permits
only the existing four exact R157 transitions and six exact hash-pinned R158
transitions, including the pending row's evidence-only update. It requires
exact original snapshots and exact accepted function/origin records; all
other canonical snapshots remain unchanged. These guards read back after
acceptance. A subsequent pure catch-all guard strengthens the already checked
actual handler schema; summary wording changes without altering any source,
profile/header/relocation input or cold comparison. Exactly five origin rows,
six function evidence rows and two parent extents change against R157 HEAD
42e9466. Every unrelated row, authored record, opaque boundary and exact input
remains preserved.

Thirty-four regression checks protect whole parents, actual registered catches,
source policy versus compiler mechanics, shared returns, alignment, entire
state/emission/layout/header evidence, pending ambiguity and exact bounded
follow-up transitions. All 1374 public tests, local target/project/query
attestation, authored extents, fresh scanner/progress, exact-input preservation
and whitespace checks pass. Totals are 3480 resolved (922 authored, 1983
library, 575 compiler), 871 pending and 2558 excluded. Authored evidence remains
875 records / 1953089 bytes; provisional exact coverage stays 9883 / 1965432.
All 60 source/mapped/exact functions / 9883 bytes and exact inputs are unchanged
from R139 db26a05, preserving its 60/60 cold replay across eleven objects.
No affected exact unit needs replay. Public MCP acceptance remains waived;
the private no-auth route is unchanged. Private queries, logs and objects
remain untracked. The complete-origin objective remains unfinished.

The next bounded R159 cohort is eight still-unknown SDK endpoint/dispatch
dependencies / 296 bytes exposed by the complete copy/insertion parents:
const begin/end, insert dispatch, distance/advance wrappers and their actual
category/distance/advance callees. Retain the existing R085 copy/copy-backward
owners unchanged. The eleven-byte category body's shape alone cannot identify
an original tag declaration; use independently whole real overload dispatch
and retain original type/name uncertainty. No next-cohort classification
follows from these already retained source controls or reviewed children.

## R159 — Complete deque endpoints and actual category/operation dispatch

R159 accepts eight library owners / 296 bytes: const begin `0x00422B50` / 35,
const end `0x00422B80` / 41, insert dispatcher `0x00422CB0` / 67, distance
dispatcher `0x00423680` / 55, advance dispatcher `0x004236C0` / 43, category
helper `0x00422D60` / 11, distance operation `0x004237E0` / 27 and advance
operation `0x00423800` / 17. Replay
`scripts/repo-python scripts/verify-deque-endpoint-dispatch-origins.py` with
`config/deque-endpoint-dispatch-origin-evidence.json`. All eight retain their
full positive own COFF AUX extents and canonical size/span_end; all bytes
and genuine typed fields compare without masking. Names remain provisional
SDK source associations, with no recovered original function/type declaration.

The entire R158 copy / 241 bytes actually calls both const endpoints and
insert dispatch; the full R158 insertion / 1545 bytes actually calls distance
and advance dispatch. Those three dispatchers call the actual category helper.
The selected distance/advance operations bind original whole const-iterator
difference `0x004235F0` / 66 (R084) and addition-assignment `0x004239A0` / 31
(R106). Both endpoints bind the unchanged complete R081 const-iterator
constructor `0x00422660` / 33. Independent original source/field/owner records
remain preserved, including R085 copy/copy-backward algorithms. Complete
R158/R157/R156 source/code/data/EH/runtime evidence cold-replays, preserving
original shared tails/interior source policies, opaque boundaries and the
independently authored R153 destruction policy. A library child alone does
not establish any new parent's ownership.

**Category ambiguity and real operations.** Actual SDK category instantiations
for complete forward and bidirectional traits observations emit the same
entire eleven bytes as the target. Input-category source emits a different
complete eleven-byte body, including different return transport in this
compiler's source ABI. No ledger ABI or original tag declaration follows.
The shape of an eleven-byte helper cannot uniquely identify category/type
or ownership; library origin is inferred from the independently complete
accepted SDK parents and their real overload/source relationship. Real SDK
random-access tag inheritance permits the selected bidirectional insertion,
while its distance/advance operations use difference and addition-assignment.
The original category and element declarations remain unknown.

Natural SDK input-distance / 49 bytes and bidirectional-advance / 59 bytes
are full different operation controls, compared as complete source extents,
never against truncated 27-/17-byte target prefixes. Their whole definitions
and actual source fields remain in cold emission evidence. The input-category
control is compared at its complete equal length and fails whole byte equality;
it is not a masked or partial target association. These bounded alternatives
do not exclude every possible original source/compiler variant.

`probes/VC7DequeEndpointDispatch.cpp` cold-builds all 197 ordinary emission
sections / 12245 bytes, twelve complete linked code controls / 2104 bytes and
all 76 actual fields. Every linked owner has full positive own AUX. The entire
72-byte SDK/traits layout is `[8,20,60,20,20,4,8,8,20,8,4,1,1,1,1,1,1,1]`;
all 27 SDK headers and the actual included unchanged R156 observation source
are pinned. Complete observations are source controls, not reconstructed
game records/iterators. Build 3077 and explicit flags are reproducibility
settings per probe; original flags/spelling/linker inputs, live range/offset
values, allocation/lifetime and iterator outcomes remain unknown.

Exactly eight origin rows and eight function evidence rows change against
R158 HEAD c9fe356. All unrelated rows, every authored record, prior R085
algorithm and original extents remain unchanged. R156/R157/R158 manifests
stay immutable. The R156 snapshot guard permits only eight additional exact
hash-pinned R159 transitions. R158's original insert-parent and adjacent
const-begin snapshot checks use that same exact guard, rather than skipping
classification/name/extent metadata; both read back after acceptance. The
final summary wording changes after the unchanged cold proof, without source,
profile/header/relocation or comparison changes. Thirty regression checks
protect whole ownership/dispatch, actual field routes, full differing and
byte-equal controls, layout/header/emission coverage, original algorithms,
bounded parent/alignment follow-ups and false source/private ABI/exact credit.

All 1404 public tests, local target/project/query attestation, authored extents,
fresh scanner/progress, exact-input preservation and whitespace checks pass.
Totals are 3488 resolved (922 authored, 1991 library, 575 compiler), 863 pending
and 2566 excluded. Authored evidence remains 875 records / 1953089 bytes;
provisional exact coverage stays 9883 / 1965432. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs remain unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No affected exact
unit needs replay. Public MCP acceptance remains waived; the private no-auth
route is unchanged. Private queries, diagnostics and objects stay untracked.
The complete-origin objective remains unfinished.

The next bounded R160 cohort is five remaining full source-associated unknowns:
file allocator max_size / 44, iterator indexing / 38, iterator subtraction-
assignment / 27, inner element destruction / 15 and placement delete / 5.
Keep the R158 28-byte record-copy ambiguity protected. Source controls and
reviewed children alone grant none of these remaining owners origin credit.
In particular, `_Destroy` calls the complete unchanged R037 generated scalar
deleting wrapper / 44 bytes, which then calls authored R153 destruction;
do not bind its field directly to the authored destructor or conflate origins.
The five-byte placement-delete body needs ordinary no-op alternatives plus
its independent complete SDK placement/construction and EH cleanup protocol.

## R160 — Remaining deque leaves and byte-equal ordinary alternatives

R160 accepts five library owners / 129 bytes: file allocator max_size
`0x0042E3B0` / 44, iterator indexing `0x00423550` / 38, subtraction-assignment
`0x00422480` / 27, element destruction `0x004229B0` / 15 and two-argument
placement delete `0x00412300` / 5. Replay
`scripts/repo-python scripts/verify-deque-leaf-origins.py` with
`config/deque-leaf-origin-evidence.json`. All five have complete positive own
COFF AUX extents and unchanged canonical size/span_end. Every actual field
compares unmasked; no source/private ABI/mapping/exact credit follows. Names
are provisional SDK associations, not recovered original declarations.

**Byte-equal alternatives.** A complete ordinary capacity observation emits
all 44 target bytes, an ordinary explicit destructor call emits all 15 bytes
and a natural two-argument empty function emits all five placement-delete
bytes. None of these leaf shapes proves library ownership or uniquely identifies
original source. The source-level library inference uses the independently
accepted entire typed SDK parent/source relationships and actual protocol:
R074 deque max_size / 22 in complete R071 file growth / 511; entire R158
insertion / 1545 calling indexing; whole R078 iterator subtraction / 57
calling subtraction-assignment; and whole R074 allocator destruction / 25.
Indexing really calls addition `0x00421F40` and dereference `0x00421F20`;
subtraction-assignment negates the supplied offset before actual addition-
assignment `0x00422460`. Every reviewed callee remains independently classified.

Destruction passes zero flags to the unchanged complete R037 generated scalar
deleting wrapper `0x004229F0` / 44. That wrapper calls independently authored
R153 destructor `0x00421220` / 43 and gates R142 scalar delete `0x00640F15`
/ 5 on flag bit one. Its origin is compiler, the actual destruction policy is
authored, and the SDK leaf is library; no call bypasses the intervening wrapper.
No new compiler or authored credit is awarded.

Placement delete follows the independently whole R157 SDK `_Construct`
`0x004228C0` / 108, with actual R005 placement new `0x004063D0` / 8 and
its original complete 27-byte cleanup/frame carrier `0x00655690` and entire
36-byte state-data section `0x006688D8`. Actual cleanup loads the placement
address from `[ebp+8]` and the placement-new result from `[ebp-0x14]`, pushes
both, calls `0x00412300` and removes eight stack bytes. The separate registered
frame entry remains at carrier offset 17. No live constructor failure or
exception outcome is observed. The whole R158 28-byte implicit/ordinary copy
ambiguity remains unknown and unchanged; constructing its record does not
establish the original constructor declaration.

`probes/VC7DequeLeafAlternatives.cpp` cold-builds all 191 ordinary sections
/ 12034 bytes. Seventeen full linked controls contain sixteen code carriers
/ 2532 bytes, entire construction EH data / 36 bytes and 88 actual fields.
All accepted leaves, ordinary alternatives and applicable SDK parents retain
positive own AUX; compiler/EH/data carriers retain their independently whole
defining sections. The full 72-byte observation layout is
`[8,20,60,20,20,4,8,8,8,20,60,20,20,4,8,8,1,1]`.
All 27 SDK headers and the actual unchanged included R156 observation source
are pinned. Complete synthetic observations do not recover game records.
Generated local `$` labels are resolved from this object's actual sections,
including the cleanup's actual state-data field; equal names in a prior object
cannot establish local ownership. Build 3077 and explicit flags are per-probe
reproducibility settings. Original source/type/compiler/linker inputs and live
capacity/index/offset/construction/lifetime outcomes remain unknown.

Exactly five function evidence rows and five origin rows change against
R159 HEAD e8f059e. All unrelated rows, every authored record and protected
copy ambiguity remain unchanged. R156/R157/R158/R159 manifests stay immutable.
The R156 snapshot guard permits only the exact five hash-pinned R160 follow-up
transitions and reads every full original snapshot back after acceptance.
Twenty-five regression checks protect full source/protocol extents, actual
fields/local offsets, ordinary alternatives, distinct compiler/authored roles,
protected copy uncertainty, layout/header/emission coverage and false credit.
The unchanged complete R159/R158/R157/R156/runtime source chain cold-replays
before canonical acceptance; only its final follow-up summary wording changes
after that proof. All 1429 public tests, local target/project/query attestation,
fresh scanner/progress, authored extents, exact-input preservation and whitespace
checks pass. Public MCP acceptance remains waived; no-auth/private route and
untracked private diagnostics remain unchanged.

Totals are 3493 resolved (922 authored, 1996 library, 575 compiler), 858 pending
and 2571 excluded. Authored evidence remains 875 bodies / 1953089 bytes;
provisional exact coverage stays 9883 / 1965432. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs remain unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No affected exact unit
needs replay. The complete-origin objective remains unfinished. The closed
R156 primary source graph now has only its protected R158 record-copy owner
remaining unknown; this does not exhaust the wider 858-function backlog.

The next bounded R161 cohort is nine unknown STL source-context candidates / 237 bytes:

| Candidate | Full provisional extent | Actual investigation context |
| --- | ---: | --- |
| `0x00409760`, `0x00409E60` | 31 each | first vector begin/end pair in the unchanged whole R034 assign / 96 and R095 assign-wrapper source family; actual iterator construction `0x0040A120` |
| `0x0040E1F0`, `0x0040E680` | 31 each | second vector begin/end pair in the unchanged whole R034 assign / 96 and R095 wrapper family; actual iterator construction `0x0040E9E0` |
| `0x0040A120`, `0x0040E9E0` | 28 each | corresponding still-unknown iterator constructors; reconcile complete source/extent/type and ordinary constructor alternatives, not a reviewed-child inference |
| `0x0040A190` | 27 | iterator subtraction-assignment in the accepted whole iterator-subtraction parent `0x00409DF0`; actual independently accepted R106 addition-assignment `0x0040A5E0` / 31 |
| `0x0040A830`, `0x0040F9F0` | 15 each | actual SDK destruction in unchanged allocator parents R074 `0x00409D60` / 25 and R033 `0x0040F860` / 25; respective unchanged R037 generated deleting wrappers `0x0040A9F0`, `0x0040FA00` / 44 |

This cohort is a diagnostic investigation scope, not nine promised acceptances.
Build complete natural SDK observation families, retain each entire accepted
parent and every genuine field/source operation, and establish independent
compiler/authored destructor policy before any library decision. Constructor
or destructor shapes and accepted children alone do not identify ownership,
original element kinds/declarations or source. Ordinary byte-equal alternatives
must remain explicit. Keep the R158 record-copy ambiguity and all other protected
lifetime/leaf ambiguities unchanged. Preserve R156/R157/R158/R159/R160 manifests;
any follow-up canonical transition needs its own exact bounded hash-pinned
snapshot evidence. The private route and all 60-function exact inputs remain
preserved. No exact scope or recovered game layout is authorized.

## R161 — Vector endpoints, explicit constructors and genuine deque operation context

R161 reviews all nine candidates / 237 bytes and accepts eight library owners
/ 222 bytes: begin/end pairs `0x00409760`, `0x00409E60`, `0x0040E1F0`,
`0x0040E680` / 31 each; mutable iterator constructors `0x0040A120`,
`0x0040E9E0` / 28 each; deque subtraction-assignment `0x0040A190` / 27; and
SDK destruction `0x0040A830` / 15. SDK/ordinary destruction `0x0040F9F0`
/ 15 remains unknown. Replay
`scripts/repo-python scripts/verify-vector-endpoint-origins.py` with
`config/vector-endpoint-origin-evidence.json`. Every accepted candidate has
its complete positive own COFF AUX extent and unchanged size/span_end. All
bytes and genuine fields compare unmasked. Original declarations remain
unknown; provisional SDK names grant no source/private ABI/mapping/exact credit.

Entire original R034 assignment parents `0x00409780` and `0x0040E210`
/ 96 actually call both endpoint pairs. Their complete R095 assign wrappers
`0x00409470`, `0x0040DF20` / 29, R032 erase contexts / 99 and insert contexts
/ 33 remain independently retained and compare as whole source variants with
all real fields. SDK endpoint constructors call actual independently accepted
R106 const-iterator constructors `0x0040A590`, `0x0040F120` / 24. Source
observations use two complete four-byte records; their matching whole generic
assignment does not recover the original element type or a game container
layout. The actual SDK observations have vector size 16 and mutable/const
iterator sizes four; the offset-deque iterator observation is eight bytes.
These are source/compiler observations, not inferred original declarations.

**Operation refinement without new origin credit.** The original R078
`0x00409DF0` / 57 association used whole SDK deque addition `??Hiterator`,
whose recorded source field `??Yiterator` was bound to the then-unreviewed
`0x0040A190`. That original evidence remains byte-identical and is retained
as source-shape evidence. The actual leaf `0x0040A190` negates its argument
before calling full addition-assignment `0x0040A5E0` / 31. New complete SDK
subtraction `??Giterator` / 57 binds its genuine `??Ziterator` field to that
27-byte leaf and compares unmasked. Full SDK addition / 57 instead binds
its real `??Yiterator` to the independently complete 31-byte addition leaf;
linking that actual operation differs from the target only within the real
four-byte call field. Neither comparison truncates a function or masks an
accepted field. The parent's provisional role/evidence is refined to
subtraction; its R078 library origin, extent and origin credit remain unchanged.
The earlier masked/direct-binding shape alone could not distinguish operations.

Complete ordinary begin/end / 31 each, derived pointer constructor / 28,
base pointer constructor / 24 and two explicit destructor wrappers / 15 each
are fully byte-equal to their corresponding SDK target controls. Those six
ordinary controls / 144 bytes show that endpoint/constructor/destruction
shapes alone cannot identify original ownership or source. Library inference
uses the independent whole typed SDK parents, constructor/base and actual
operation relationships. No incomplete reconstructed game owner is instantiated.

The first destruction leaf compares through full unchanged R074 allocator
destruction `0x00409D60` / 25 and complete R037 generated deleting wrapper
`0x0040A9F0` / 44, with independently authored R017 resource policy
`0x004092F0` / 87 and R142 scalar delete `0x00640F15` / 5. The second
allocator parent is unchanged R033 `0x0040F860` / 25, whose SDK/ordinary
15-byte child calls full R037 wrapper `0x0040FA00` / 44. That wrapper calls
protected R108 lifetime policy `0x0040D8E0` / 19. Its original explicit/implicit
source ambiguity remains unresolved. The complete SDK/ordinary operation and
parent association do not resolve surrounding lifetime declarations; the
second 15-byte candidate remains unknown and receives evidence notes only.
Generated wrappers, authored policy and unknown policy remain separately
classified. No library leaf is bound directly past the intervening wrapper.

`probes/VC7VectorEndpointAlternatives.cpp` cold-builds all 176 ordinary
sections / 9404 bytes. Thirty-one full code controls / 1169 bytes and 41 actual
fields compare unmasked, including four whole original erase/insert variants
and six ordinary controls. Applicable owners have full positive own AUX;
both generated wrappers retain their whole unique defining COMDAT. The entire
68-byte layout is `[4,4,16,16,4,4,4,4,1,1,4,4,16,1,8,1,1]` and all 28 actual
SDK headers are pinned. Fourteen original parent/helper/compiler/policy records
are retained. Source evidence files remain immutable; the growing authored
evidence registry is checked by exact membership of its original R017 record,
not by freezing unrelated future additions. Only declared full selected
controls compare to target bytes; all ordinary emission is cold inventory
coverage, not an executable-wide match. Build 3077 and explicit flags are
per-probe reproducibility settings. Original source/type/compiler/linker inputs
and live count/range/offset/iterator/lifetime outcomes remain unknown.

Exactly eight origin rows and ten function-evidence rows change against
R160 HEAD ea7d1c0: eight library candidates, one pending destruction evidence
update and one retained R078 parent operation refinement. All unrelated and
protected rows, every authored record and previous evidence manifests remain
unchanged. Thirty-five regression checks protect full source/parent extents,
actual constructor/operation fields, immutable historical shape evidence,
whole genuine addition/subtraction controls, ordinary alternatives, independent
compiler/authored/unknown roles, pending-origin conservation and false credit.
Cold comparison precedes canonical acceptance; exact bounded rows read back
afterward. All 1464 public tests, local target/project/query attestation,
fresh scanner/progress, authored extents, exact-input and whitespace checks
pass. Public MCP acceptance remains waived, with the no-auth/private route
unchanged and private diagnostics/objects untracked.

Totals are 3501 resolved (922 authored, 2004 library, 575 compiler), 850 pending
and 2579 excluded. Authored evidence remains 875 bodies / 1953089 bytes;
provisional exact coverage stays 9883 / 1965432. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs remain unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No affected exact unit
needs replay. The complete-origin objective remains unfinished. A fresh private
whole own-AUX source survey finds 258 relocation-excluding diagnostic
associations; these are not origin or exact acceptance. Genuine destination,
complete independent parent/context and full extent evidence remain necessary.

The next bounded R162 cohort is fifteen remaining vector endpoint/constructor
source-context candidates / 447 bytes. These are diagnostic associations, not
promised origin acceptances:

| Candidate group | Full provisional extents | Independent context to retain |
| --- | ---: | --- |
| `0x0040DCE0`, `0x0040DD00`, `0x0040E4A0` | 31, 31, 28 | whole R019 game parents `0x0040B280` / 727 and `0x0040B560` / 575; actual const-iterator constructor `0x0040E990`; pending assignment `0x0040E000` / 158 must not be truncated to the R034 96-byte source variant |
| `0x00411CC0`, `0x004121C0` | 31, 28 | whole R035 game parent `0x00411110` / 746; actual const-iterator constructor `0x00412440`; preserve the related still-unknown 42-byte iterator-producing helpers |
| `0x0041D980`, `0x0041EF00` | 31, 28 | whole R052 parent `0x0041D260` / 686 and R053 parent `0x0041D750` / 164; actual const-iterator constructor `0x0041F770`; preserve adjacent 42-byte source contexts |
| `0x00531DD0`, `0x00532300` | 31, 28 | actual const-iterator constructor `0x005323C0`; surrounding 42-byte producers remain unknown, so a source shape or reviewed child alone grants no origin |
| `0x005F8490`, `0x005F8EF0`, `0x005F95B0` | 31, 31, 28 | actual const-iterator constructor `0x005F9DB0`; pending assignment `0x005F84B0` / 167 and its lifetime/EH extent require independent full reconciliation, never a 96-byte prefix match |
| `0x005F8B50`, `0x005F9350`, `0x005F9600` | 31, 31, 28 | unchanged whole R034 assignment `0x005F8B70` / 96; actual const-iterator constructor `0x005F9E00`; freeze every real source/call field and original parent evidence |

Build natural complete SDK and ordinary alternatives, reconcile full own-AUX
or entire defining-source extents, and retain entire independently reviewed
game/library parents. Source parameter/return roles and all actual field
owners matter; the six R161 ordinary controls demonstrate that short endpoint
and constructor shapes alone do not establish original ownership or declarations.
A pending parent is not accepted because its child is library. Original record
sizes/kinds, container layouts and live outcomes remain unknown. Keep all R108
lifetime ambiguities, R158 record-copy ambiguity and R161 second destruction
leaf `0x0040F9F0` / 15 protected. Keep original R078 source-shape evidence and
R161 genuine operation refinement intact. All prior manifests, the private
route and 60-function exact inputs remain preserved; no exact scope is added.

## R162 — Complete vector producer observations and conservative ownership

R162 reviews fifteen short vector endpoint/constructor candidates / 447 bytes.
Only `0x005F8B50` / 31, `0x005F9350` / 31 and `0x005F9600` / 28 gain library
origin, totaling 90 bytes. Their independent whole R034 assignment
`0x005F8B70` / 96, complete R032 erase / 99 and insert / 33, and actual R106
const-iterator constructor / 24 supply a coherent retained SDK source context.
Every byte and actual relocation compares unmasked. Full own positive AUX
extents and canonical size/span_end are unchanged. The inference identifies
library ownership, not original record declarations or an original source file.

The other twelve candidates / 357 bytes remain unknown, as do the two full
assignment parents `0x0040E000` / 158 and `0x005F84B0` / 167. Complete ordinary
begin/end / 31 and derived iterator constructor / 28 are byte-equal to SDK
controls. More significantly, natural ordinary C++ members using a complete
SDK vector base, a real local record, erase and insert reproduce both entire
nontrivial assignment bodies and their complete exception cleanup/state data.
A reviewed game caller or library child does not independently settle ownership
of those original short leaves or parent declarations. Seventeen function rows
receive bounded evidence notes, while exactly three origin rows change; the
fourteen pending records retain their names, ownership and dispositions.

The 158-byte parent copies all 44 bytes of an observed local value; the
167-byte parent copies all 16 bytes. Each registers one unwind state and calls
its actual destructor both normally and through cleanup. Synthetic observation
types declare external destructors; these declarations are probe ABI inputs,
not recovered game declarations. The actual unknown policies `0x0040D8E0`
/ 19 (protected R108 ambiguity) and `0x004588B0` / 43 remain unknown. Existing
copy `0x004229D0` / 28 and destruction `0x0040F9F0` / 15 remain protected.
Neither nontrivial assignment is compared to a convenient 96-byte prefix.

For each SDK and ordinary parent, the whole 18-byte defining EH carrier has an
eight-byte destructor cleanup tail followed by the ten-byte handler entry.
The cleanup jumps to the actual destructor; the handler loads the genuine
FuncInfo and jumps to unchanged full R142 `0x006407B8` / 54. Entire 36-byte
state sections include both unwind records and FuncInfo, with the primary
FuncInfo definition at offset eight. Every local symbol is bound from this
cold object's own section definitions. Original R020 frames at `0x00654F68`
and `0x006566F8`, their owner registration sites, state/cleanup data and actual
field destinations are retained and revalidated. The `__except_list` value
zero is an FS offset, not PE data. Whole cleanup/handler carriers include
both shared tails; no positive own AUX is invented for generated local entries.

The pinned build 3077 rejects `/GS-` with an unknown `/G-` warning. The accepted
probe profile omits `/GS` and emits the full no-cookie 158/167-byte bodies.
A separately cold-built explicit `/GS` negative profile emits entire
174/183-byte SDK alternatives containing genuine cookie load/check fields.
Their lengths differ from target extents; they earn no match or origin credit.
This is a bounded compiler observation, not an executable-wide flag profile.
The short endpoint shapes cannot distinguish those flag choices.

Replay `scripts/repo-python scripts/verify-vector-producer-origins.py` with
`config/vector-producer-origin-evidence.json` and natural complete source
`probes/VC7VectorProducerContexts.cpp`. Forty-three full code/EH/state controls
/ 2039 bytes and 95 genuine fields compare unmasked. The primary cold inventory
covers all 244 ordinary sections / 13520 bytes, and the `/GS` negative inventory
covers all 244 sections / 13616 bytes. All 27 actual SDK headers and the complete
92-byte observation layout are pinned. Observations have record sizes 44, 16
and four, SDK vector sizes 16, and iterator sizes four; complete ordinary bases
are instantiated without declaring or instantiating an incomplete game owner.
Inventory coverage does not claim every emitted section matches the executable.
Original source, game layouts, lifetime declarations, linker choices and live
iterator/value outcomes remain unknown. No source/private ABI/mapping/exact
credit is added.

Five whole previously authored game parents retain all eight actual candidate
call windows: R019 `0x0040B280` / 727 and `0x0040B560` / 575, R035
`0x00411110` / 746, R052 `0x0041D260` / 686 and R053 `0x0041D750` / 164.
These are independently retained game evidence, not proof of callee ownership.
Six surrounding full 42-byte producer helpers and two eight-byte bridges remain
unknown and preserve their whole CFG. They cannot be accepted as 31-byte
endpoint prefixes. Nineteen original SDK/runtime/game records are retained by
immutable evidence files or exact authored-row membership. The growing authored
registry is not frozen against unrelated future additions.

Cold whole comparisons precede canonical acceptance. Exact bounded readback
against R161 HEAD a5c512e confirms three library-origin and seventeen function-
evidence changes; all unrelated rows, all authored evidence, previous manifests,
private route and exact inputs are unchanged. Thirty-four public regression
checks guard complete parents/EH/state/ordinary alternatives, actual fields,
protected unknown ownership and false source/ABI/exact credit. All 1498 public
checks, local target/project/query attestation, fresh scanner/progress, authored
extents, exact-input preservation and whitespace checks pass. Public MCP
acceptance remains waived by the user; private diagnostics and objects remain
untracked.

Totals are 3504 resolved (922 authored, 2007 library, 575 compiler), 847 pending
and 2582 excluded. Authored evidence remains 875 bodies / 1953089 bytes.
The 60 source/mapped/exact functions / 9883 bytes and all exact inputs remain
unchanged from R139 db26a05; its previous 60/60 cold replay across eleven objects
remains applicable. No affected exact unit needs replay. Provisional authored
coverage remains 9883 / 1965432 (0.50%). The full origin-review objective is
unfinished; this batch makes three conservative ownership decisions and retains
complete negative/ambiguous evidence for subsequent review.

The next bounded R163 cohort is twelve string-length wrapper/worker candidates
/ 253 provisional bytes. These are diagnostic associations, not promised origin
acceptances:

| Candidate pair | Full provisional extents | Required independent context |
| --- | ---: | --- |
| `0x0040D900`, `0x0040D920` | 17, 28 | whole source/runtime worker and actual string argument; retain protected R108 lifetime declarations independently |
| `0x0040D940`, `0x0040D960` | 17, 28 | second complete wrapper/worker; byte equality does not establish shared original ownership |
| `0x00412D90`, `0x00412DB0` | 17, 28 | actual complete caller and string/storage roles, not a name-only strlen binding |
| `0x00428D20`, `0x00428D40` | 17, 28 | complete string/source context and every real call/data/import field |
| `0x00438A60`, `0x00641FB8` | 17, 11 | whole independently reviewed game callers and full runtime/import/possible shared-tail extent |
| `0x00449A60`, `0x00449A80` | 17, 28 | whole authored parent `0x004491E0` and actual string arguments, keeping lifetime origins separate |

A fresh R162 full own-AUX survey yields 363 relocation-excluding diagnostic
associations; this does not grant origin or exact credit. The 17-byte shape also
fits an allocation wrapper when its real destination is ignored. Reconcile each
entire worker, source/ABI meaning, imports, CFG, exits, alignment and full own-AUX
or justified defining-source carrier before accepting anything. Compare natural
complete SDK, intrinsic/runtime and ordinary alternatives as applicable; retain
ambiguous user wrappers as unknown. Do not infer a parent from a reviewed child
or infer ownership from a reviewed game caller alone. Protect all prior R108
lifetime, R158 copy and R161 destruction ambiguities, the R161 retained R078
operation refinement, and the fourteen unknown R162 endpoint/assignment records.
All existing evidence and exact inputs remain preserved; no exact scope is added.

## R163 — Real math chains refute the diagnostic string-length label

R163 reviews all twelve candidates / 253 bytes from the R162 shortlist. Actual
full worker instructions and independently reviewed runtime destinations refute
that shortlist's string-length interpretation. Five 17-byte wrappers call whole
28-byte float-operation workers, and the sixth calls a whole eleven-byte integer
absolute-value body. The addresses and extents remain unchanged; the earlier
shortlist was a diagnostic association, never accepted ownership or source proof.

The five actual chains are `0x0040D900` to `0x0040D920` to C cos entry
`0x00641754`; `0x0040D940` to `0x0040D960` to C sin entry `0x00641804`;
`0x00412D90` to `0x00412DB0` to fabs `0x006418CD`; `0x00428D20` to
`0x00428D40` to C sqrt entry `0x00641E54`; and `0x00449A60` to `0x00449A80`
to ceil `0x00642120`. Workers load the four-byte floating argument, store an
eight-byte stack argument, make the real double-operation call, then store a
four-byte result observation before returning through x87. These instructions
and source variants establish a math operation context, not live rounding or
exception outcomes or an original function/type declaration.

The first, second and fourth destinations are source-defined C stack-double
entries at offset 20 inside whole unchanged R128 x87 primaries `0x00641740`
/ 174, `0x006417F0` / 174 and `0x00641E40` / 186. They are not the __CI entry
at offset zero, which receives an x87 register argument. Existing labels retain
their type-zero COFF definitions and overlapping nine-byte target extents;
no standalone AUX or independent source function is invented for them. Full
R129 fabs / 177 and R130 ceil / 64 remain accepted independently. All five
whole runtime primaries / 775 bytes replay from fresh extraction of the pinned
CRT archive, with every original actual field. Existing ceil source/shared-tail
reconciliation remains intact; no enclosing source carrier is redefined here.

`0x00438A60` / 17 calls `0x00641FB8` / 11, whose full signed branch/negation
body returns an integer absolute value. It is not a strlen worker or import
thunk. Fresh whole positive-AUX abs.obj and labs.obj controls both reproduce the
entire body. The prior natural R129 int/long expression source cold-builds both
complete eleven-byte alternatives and also reproduces this new target. The
separate original R129 abs candidate `0x00641DAA` remains unknown and unchanged.
Source spellings, int/long choice, library versus authored ownership and possible
linker folding cannot be inferred from these byte-equal alternatives.

Natural complete `probes/VC7MathOverloadContexts.cpp` emits genuine math.h
float overloads / 17, C float workers / 28 and the long abs overload / 17.
Separate ordinary C++ helpers with explicit double operations and ordinary
outer wrappers reproduce every target byte and real call field in the five
chains. An ordinary long wrapper is also byte-equal. Both entire source chains
are retained; binding a generic 17-byte shape to an assumed strlen or allocation
operation would hide the actual float/integer ABI and callee meaning. Complete
SDK/ordinary equality also leaves original wrapper/worker ownership unresolved.
Previously authored callers alone do not resolve that ambiguity. All twelve
origins therefore remain unknown; twelve function rows receive corrected bounded
evidence notes only, preserving names, extents, ownership and dispositions.

Replay `scripts/repo-python scripts/verify-math-overload-origins.py` with
`config/math-overload-origin-evidence.json`. Twenty-two whole positive-own-AUX
SDK/ordinary controls / 484 bytes and 22 actual unmasked REL32 fields compare.
All 29 cold ordinary sections / 602 bytes, six actual SDK headers and the full
16-byte layout `[4,8,4,4]` are pinned. These are observation/compiler sizes,
not recovered game declarations. The two original CRT abs/labs sections and
two newly cold ordinary expression controls each compare as entire eleven-byte
bodies. Existing source/runtime evidence is retained by exact record membership
and immutable file hashes; no previous origin is reopened or newly accepted.

Five whole authored game contexts / 8610 bytes retain twenty actual call
windows: R011 sprite parent `0x0040CA80` / 1132, R035 camera `0x004126C0`
/ 1520 and opening scene `0x004277A0` / 5339, R041 character selection
`0x00433A40` / 404 and R109 bounds policy `0x004491E0` / 215. Their complete
CFG, switch data where applicable, whole body hashes and argument/return windows
are verified. Exact original authored-row membership permits unrelated future
registry additions. All protected R108 lifetime, R158 copy, R161 destruction,
R162 endpoint/assignment and old R129 abs records remain unchanged.

Cold whole source comparisons precede the canonical evidence update. Readback
against R162 HEAD 6035ba5 confirms exactly twelve function-evidence changes and
zero origin, extent, name, source, ABI or exact changes. All unrelated ledgers,
previous manifests and authored records remain unchanged. Twenty-nine regression
checks guard full source chains, real math/C-entry ABI, complete runtime owners,
ordinary alternatives, pending ownership and false credit. All 1527 public
checks, local target/project/query attestation, fresh scanner, authored extents,
exact-input preservation and whitespace checks pass. Public MCP acceptance
remains waived; private diagnostics/objects and the unchanged no-auth route
remain private.

Totals remain 3504 resolved (922 authored, 2007 library, 575 compiler), 847
pending and 2582 excluded. Authored evidence remains 875 bodies / 1953089 bytes.
All 60 source/mapped/exact functions / 9883 bytes and source/header/build/match
inputs remain unchanged from R139 db26a05; its earlier 60/60 cold replay across
eleven objects remains applicable without affected-unit replay. Provisional
coverage remains 9883 / 1965432 (0.50%). This batch replaces a false semantic
shortlist with reproducible whole math/ordinary evidence and leaves uncertainty
explicit. The full remaining-origin goal is not complete.

The next bounded R164 cohort is five unresolved SDK dependency candidates
/ 504 provisional bytes, each reached from an independently accepted full
library parent. These are diagnostic contexts, not promised acceptances:

| Candidate | Full provisional extent | Independent whole parent to retain |
| --- | ---: | --- |
| `0x00415F60` | 44 | R074 `0x00415A80` / 22, provisionally named `VC7::max_size_00415A80` |
| `0x00422290` | 151 | R072 deque tidy `0x00421DD0` / 177; retain actual children `0x00422270`, `0x00422610` independently |
| `0x0042E120` | 151 | R072 deque tidy `0x0042DEF0` / 177; retain actual children `0x0042E100`, `0x0042E390` independently |
| `0x0045AFB0` | 50 | R033 generic copy `0x0045A7E0` / 51, with actual worker `0x0045AAE0` independently unresolved |
| `0x0045B640` | 108 | R033 construct `0x0045B2B0` / 29; actual `0x004063D0` and `0x004591E0` ownership remains independent |

Read the full actual parent and every source field; original generic names are
not source-type or ABI proof. Build natural complete SDK and ordinary controls,
reconcile full CFG, exits, shared tails, EH/data and own-AUX or defining-section
extents. A library parent supplies independent context but does not automatically
classify a child. Keep original parent evidence immutable. Do not instantiate
an incomplete reconstructed game owner or truncate a comparison to an emitted
source variant. Preserve all prior R108 lifetime, R158 copy, R161 destruction,
R162 endpoint/assignment and R163 math/abs ownership ambiguities, including the
unchanged R129 abs alternative and R161 R078 operation refinement. No exact
scope is added. The full origin-review goal remains active and unfinished.

## R164 — Complete SDK dependencies through retained whole library parents

R164 accepts five library bodies / 504 bytes. Cold own-AUX source comparisons
use genuine SDK operations with every actual field, through independently
accepted full R074/R072/R033 parents. Original parent evidence remains immutable.

| Address | Complete bytes | SDK observation | Independent whole library parent |
| --- | ---: | --- | --- |
| `0x00415F60` | 44 | allocator max_size, two-byte observation | R074 `0x00415A80` / 22 |
| `0x00422290` | 151 | deque pop_back, 20-byte nontrivial observation | R072 tidy `0x00421DD0` / 177 |
| `0x0042E120` | 151 | deque pop_back, 60-byte trivial observation | R072 tidy `0x0042DEF0` / 177 |
| `0x0045AFB0` | 50 | forward nonscalar copy, 116-byte observation | R033 generic copy `0x0045A7E0` / 51 |
| `0x0045B640` | 108 | placement construction with copy and EH | R033 allocator construct `0x0045B2B0` / 29 |

Target observations distinguish the full forward copy from a complete 48-byte
backward alternative: both forward pointers advance by 116, and the actual
assignment destination is unresolved `0x0045AAE0` / 368. Placement construction
calls independently accepted placement new `0x004063D0` / 8 and unresolved
record copy `0x004591E0` / 417. The complete registered R020 frame binds handler
`0x00656391`, cleanup `0x00656380`, unwind `0x00669C30` and FuncInfo
`0x00669C38`. The new object supplies both complete 27-byte cleanup/handler
carriers and both complete 36-byte unwind/FuncInfo sections, with actual placement
delete `0x00412300` / 5 and runtime handler `0x006407B8` / 54. No EH or data
prefix is accepted. FS exception-list fields represent offset zero, not PE data.

Replay `scripts/repo-python scripts/verify-sdk-dependency-origins.py` using
`config/sdk-dependency-origin-evidence.json`. The explicit /Od /Ob0 /Gy /GR-
/GX /Zi /GS profile cold-builds one natural synthetic observation source. All
55 ordinary sections / 2360 bytes and 28 actual SDK headers are pinned. The
whole 60-byte layout is `[2,20,60,116,20,20,20,1,1,1,1,1,20,20,1]`;
these are probe/compiler facts, not original game declarations or object layouts.
Externally declared genuine copy/assignment/destruction operations preserve the
observed ABI without instantiating an incomplete reconstructed game owner.

Thirty-nine whole source/code/EH/data controls / 1988 bytes retain 57 real
fields. Thirty-seven full comparisons / 1686 bytes are positive. Five complete
ordinary capacity/copy/placement/empty alternatives / 252 bytes are byte-equal.
Two entire ordinary deque-pop alternatives / 302 bytes each differ at eight
local-stack displacement bytes; their full source/target CFG and every actual
field remain checked. They receive no positive comparison credit. Their source
is preserved without adjusting local names to force equality. The complete
48-byte backward-copy negative uses its own source extent and actual assignment
field; it is never truncated to the target or compared as a convenient prefix.
Ordinary source similarity alone does not establish original ownership; the
library inferences require the separate complete accepted SDK-parent context.

Seventeen exact original evidence records and 41 full canonical/body snapshots
retain independent parents, runtime/compiler boundaries and unknown policies.
Allocator destroy `0x00422610` / 25 and `0x0042E390` / 25, their actual
15-/5-byte destruction children, opaque record assignment/copy, protected
R108/R158/R161/R162 lifetime/copy policies and R163 math/abs alternatives remain
unknown. The R037 deleting wrapper stays compiler generated; its 72-byte game
lifetime child receives no ownership from library callers. The already accepted
five-byte map-pointer destruction helpers retain R088 ownership.

Full cold comparisons precede ledger acceptance. Readback against R163 HEAD
1923ec1 verifies exactly five function and five origin transitions, with all
unrelated rows, previous manifests, authored evidence and exact inputs preserved.
Thirty-four regression checks guard complete fields/extents, whole negative
comparisons, source-versus-ordinary distinctions, EH/data, opaque children and
false credit. All 1561 public checks, local target/project/query attestation,
fresh scanner, 875 authored extents / 1953089 bytes, exact-input preservation
and whitespace checks pass. Public MCP acceptance remains waived.

Totals are 3509 resolved (922 authored, 2012 library, 575 compiler), 842 pending
and 2587 excluded. All 60 source/mapped/exact functions / 9883 bytes remain
unchanged from R139 db26a05; its earlier 60/60 cold replay across eleven objects
remains applicable. Provisional coverage remains 9883 / 1965432 (0.50%).
No reconstructed source, private ABI, mapping or exact credit is added.
The next R165 cohort is the two 25-byte allocator-destruction wrappers reached
from the newly accepted full deque-pop parents. Their 15-/5-byte children and
separate game lifetime ownership remain independent. The full goal is unfinished.

## R165 — Allocator destruction wrappers with independent full deque parents

R165 accepts two library wrappers / 50 bytes: `0x00422610` / 25 and
`0x0042E390` / 25. Their complete genuine SDK allocator.destroy bodies call
`0x004229C0` / 15 and `0x0042E580` / 5 respectively, with the observed
thiscall return cleanup. The unchanged full R164 deque-pop parents
`0x00422290` and `0x0042E120` / 151 each supply independent coherent library
context. Ghidra's preexisting container-proxy label is not element-type evidence.

Replay `scripts/repo-python scripts/verify-allocator-destroy-origins.py` using
immutable `config/allocator-destroy-origin-evidence.json`. One new cold probe
includes the original hash-pinned R164 complete observations and adds natural
ordinary allocator/destruction controls. All 61 ordinary sections / 2472 bytes,
28 actual SDK headers and the actual original probe include are checked.
The two readonly observation arrays share one whole 68-byte section, with
definitions at offsets zero and 60. The complete seventeen-word layout is
`[2,20,60,116,20,20,20,1,1,1,1,1,20,20,1,1,1]`; no array prefix or
fabricated separate section is accepted. These remain compiler/probe inputs,
not recovered original game types or layouts.

Thirteen full own-AUX/unique defining-section controls / 536 bytes compare
unmasked with twelve real fields. They retain both full candidates, both full
deque parents, actual empty/destruction children, and the entire R037 compiler
deleting wrapper. Four complete ordinary allocator/destruction alternatives
/ 70 bytes are byte-equal. This does not identify original declarations or
resolve the two independently unknown 15-/5-byte destruction children. The
72-byte lifetime callee `0x004212A0` remains unknown; R037 `0x00422A20` / 44
stays compiler generated and R142 `0x00640F15` / 5 stays library.

Four exact retained evidence records and 41 full canonical/body snapshots
preserve independent parents, runtime and protected policies. All prior
manifests stay byte-identical. R164's verifier gains only the two exact
original-to-accepted R165 snapshot transitions, guarded by the immutable new
manifest and exact row equality; unrelated or altered original rows fail.
Its entire source/code/EH/data cold replay passes after acceptance. No broader
historical snapshot exemption or recursive replay of unaffected batches is added.

Cold comparison precedes acceptance. Readback against R164 HEAD d172412 confirms
exactly two function and two origin changes, with unrelated rows, previous
evidence, authored records and exact inputs preserved. Thirty new regression
checks and all 1591 public checks pass, along with local target/project/query
attestation, fresh scanning, authored extents and whitespace checks.
Public MCP acceptance remains waived. Totals are 3511 resolved (922 authored,
2014 library, 575 compiler), 840 pending and 2589 excluded. Authored evidence
remains 875 bodies / 1953089 bytes. All 60 source/mapped/exact functions / 9883
bytes and R139 db26a05 exact inputs remain unchanged; its earlier cold 60/60
replay across eleven objects remains applicable. No source/private ABI/mapping/
exact credit is added; provisional exact coverage remains 0.50%.

The next R166 cohort is four diagnostic game-parent context candidates / 600
bytes: `0x00410F30` / 104, `0x0045B760` / 203, `0x0045B920` / 131 and
`0x005F7140` / 162. Retain the complete R045/R050/R065 authored parents and
actual calls listed in the handoff. Parent/child relationships alone do not
resolve ownership. The full remaining-origin goal is active and unfinished.

## R166 — Custom game policies with complete independent parent and source context

R166 accepts all four handoff candidates / 600 bytes as authored. Independent
whole game context and each full custom behavior support these decisions;
scanner labels and library children alone are insufficient.

| Address | Entire bytes | Target-observed custom policy | Independent whole game parent |
| --- | ---: | --- | --- |
| `0x00410F30` | 104 | Store incoming identifier, flags 15 and mode 5; clear the member at +4, with complete EH | R045 resource loader `0x00456B60` / 1186 |
| `0x0045B760` | 203 | Base construction, observed vptr and fifteen sparse scalar default writes | R050 Reimu initializer `0x004769B0` / 134 |
| `0x0045B920` | 131 | Construct four 20-byte deque observations at +4, then explicitly loop over clear calls | R045 fighter initializer `0x004567B0` / 345 |
| `0x005F7140` | 162 | Delete each pointer in two deque observations, clearing each queue after its loop | R065 character loader `0x004176F0` / 3232 |

Replay `scripts/repo-python scripts/verify-game-parent-policy-origins.py` using
`config/game-parent-policy-origin-evidence.json`. Three whole natural C++
policies / 397 bytes compare unmasked, including every actual call and complete
own-AUX extent. The 203-byte initializer has full target instruction witnesses,
all fifteen observed zero stores and complete independent game context; it has
no positive source-match claim. Its entire implicit virtual-construction control
is 31 bytes, not a compared target prefix. Full implicit list and array controls
are 25 and 40 bytes versus the explicit 104 and 131. These generated source
definitions lack primary AUX records; the verifier checks the complete unique
code COMDAT, all actual symbol metadata, every source byte and full CFG.
None earns positive comparison, reconstructed source or exact credit.

Nineteen full source/code/EH/state comparisons / 1340 bytes retain 63 genuine
unmasked fields. They include complete list and deque contexts and both entire
21-/32-byte cleanup/handler carriers with their whole 36-byte unwind/FuncInfo
sections. Original R020 frames at handlers `0x0065501B` and `0x006563B6`
remain unchanged. Real fields bind independently accepted whole runtime vector
constructor/destructor iterators / 98 and 96 bytes and the runtime handler.
FS exception-list fields represent offset zero, not PE data.

All 146 cold ordinary sections / 6709 bytes, 29 actual SDK headers and the whole
36-byte layout `[20,20,84,84,40,4,4,12,20]` are pinned. Complete observations
use unsigned list values, float array-deque values and unsigned pointees for
the pointer queues; these separate real source owners retain coherent allocator
destinations. They do not recover original element/node types or private owner
layouts. The four-byte virtual observer is a negative model only; no incomplete
original game owner is instantiated. Source sizes and flags are probe/compiler
observations, not executable-wide compiler provenance.

Both SDK clear and destructor bodies can emit the entire same 19-byte form
calling the same Tidy. Original R077 destructor evidence is retained verbatim;
the new clear association preserves original spelling ambiguity. R073's 72-byte
deque constructor stays library. The 56-/153-/19-byte list operations, their
22-byte custom wrapper, base constructors and other unresolved helpers retain
their original independent origins. One readonly four-byte vtable slot at
`0x00659064` binds `0x0045B880` / 149, which stays unknown; this observation
establishes neither a whole vtable extent nor original virtual ABI.

Four whole authored anchors / 4897 bytes retain exact original evidence rows,
complete CFG and actual argument/return windows. The R065 parent retains both
entire guarded switch tables / 44 and 20 bytes. Eleven prior source/runtime
records and 88 complete body/canonical snapshots preserve all unrelated owners
and protected R108/R158/R161/R162/R163/R165 ambiguities. Growing authored
registry additions are permitted through exact retained-row membership; no whole
registry hash is frozen. No older manifest needs a transition exemption for
these four previously unrecorded candidates.

Complete cold comparison precedes acceptance. Readback against R165 HEAD
646a2f3 confirms exactly four function/origin transitions and four appended
authored extent records / 600 bytes. All 875 original authored records, headers
and order, unrelated rows, previous manifests and exact inputs are preserved.
Forty-two regression guards and all 1633 public checks pass, with local
target/project/query attestation, fresh scanner, authored extents and whitespace
checks. Public MCP acceptance remains waived. Totals are 3515 resolved (926
authored, 2014 library, 575 compiler), 836 pending and 2589 excluded. Authored
evidence is 879 bodies / 1953689 bytes. All 60 source/mapped/exact functions
/ 9883 bytes and R139 db26a05 exact inputs remain unchanged; its earlier cold
60/60 replay across eleven objects remains applicable. Provisional exact coverage
is 9883 / 1966032 (0.50%), with no new reconstructed source/private ABI/mapping/
exact credit. The full remaining-origin goal is unfinished.

The next R167 cohort is the four unresolved list-policy dependencies / 250
bytes (`0x00411C30`, `0x004110F0`, `0x00411D60`, `0x00411C70`) with their
new complete R166 custom parent, whole wrapper and full EH cleanup context.
Retain all actual lower node/allocator fields and unknown original types.

## R167 — complete list-policy dependencies and whole node allocation

The bounded four-candidate R167 cohort expands only to its necessary complete
list/allocator dependency graph. One authored wrapper / 22 bytes and eleven
library definitions / 718 bytes are accepted through the unchanged whole R166
custom policy `0x00410F30` / 104 and complete R045 game parent `0x00456B60` /
1186. Caller labels, byte shapes and a compiled method name alone prove no
ownership. Replay `scripts/repo-python scripts/verify-list-policy-dependency-origins.py`
against immutable `config/list-policy-dependency-origin-evidence.json`.

| Address | Accepted complete bytes | Inferred source role | Origin |
| --- | ---: | --- | --- |
| `0x004110F0` | 22 | custom owner clear, delegates to list at receiver +4 | authored |
| `0x00411C30` | 56 | SDK list constructor | library |
| `0x00411C70` | 19 | SDK list destructor, calls complete `_Tidy` | library |
| `0x00411D60` | 153 | SDK list clear, all six real node-operation fields | library |
| `0x00411FE0` | 223 | SDK `_Buynode`, including local catch and shared tail | library |
| `0x004120C0` | 100 | SDK `_Tidy`, clear and sentinel link destruction/deallocation | library |
| `0x00412130` | 53 | SDK `_List_val` constructor | library |
| `0x00412170` | 14 | SDK value allocator constructor | library |
| `0x004121A0` | 25 | SDK node allocator destroy wrapper | library |
| `0x004123E0` | 27 | SDK node allocator allocation wrapper | library |
| `0x00412420` | 25 | SDK node-pointer allocator destroy wrapper | library |
| `0x004125A0` | 23 | SDK `_Allocate`, actual 172-byte node multiplier | library |

Target observation: the old `_Buynode` candidate ends at `0x0041206E`, before
its catch. The actual complete primary is `0x00411FE0..0x004120BE` / 223 bytes.
Both forward catch/shared-tail branches are internal to that full primary; the
complete source's own positive AUX extent is also 223 bytes. A local typed COFF
catch label at +143 corresponds to `0x0041206F`. The complete 80-byte
try/catch/unwind/FuncInfo section at `0x00668194` retains all four real fields,
including the actual catch entry, catch table, unwind array and try map. Original
R020 registrations at `0x0065501B` and `0x00655030` are read back and verified.
The canonical primary extent is reconciled before library acceptance; no 143-byte
prefix earns complete evidence. The independently listed 80-byte catch interior
stays unknown, with the overlap explicit and no separate primary AUX claim.

Compiler/source observation: a complete `std::list` of a synthetic 164-byte
record emits the observed 172-byte node allocation, plus the complete list
constructor, clear, destructor, allocation and destruction graph. All 31 entire
positive controls / 1288 bytes compare unmasked, retaining 62 genuine fields
through one coherent catalog of actual defining code/local EH/data symbols.
Every regular positive has its own full AUX extent. Full EH carriers are 21 and
10 bytes; complete registered state carriers are 36 and 80 bytes. Existing
allocator hierarchy/construct/deallocate records and full R142 frame/throw/delete
and R154 scalar-new boundaries remain independent. Thirteen original records
and 103 full canonical/body snapshots are retained; the growing authored CSV is
checked by exact original-row membership, never an immutable whole-file hash.

An ordinary delegating destructor reproduces the entire 19-byte SDK destructor;
original spelling remains unknown. A full implicit 22-byte owner destructor
calls `0x00411C70`, whereas the actual custom wrapper calls `0x00411D60`.
Their complete real-callee fields differ. The entire unsigned-list node
allocation is 20 bytes and differs from the full 23-byte target allocation; no
prefix or masked comparison is used. These two complete negatives / 42 bytes
retain their actual SDK destinations. The 164-byte payload is an observation,
not original element identity or a reconstructed game layout. No incomplete
original game owner is instantiated.

All 182 cold ordinary sections / 8150 bytes, 29 actual SDK headers plus the
unchanged pinned R166 probe include, and the entire combined 56-byte readonly
layout `[20,20,84,84,40,4,4,12,20,164,20,12,1,16]` are frozen. The full unchanged
104-byte custom policy retains every real field and operation; its independent
1186-byte game anchor retains the original authored record, complete CFG and
actual argument/call window. The original R166 manifest is immutable. Its
verifier permits only these exact R167 original-to-accepted transitions and
cold-replays successfully. Its older 143-byte node snapshot remains historical
context; the new acceptance independently compares the whole 223-byte primary.

Unknowns remain explicit: `0x00411E80` / 8, `0x00411E90` / 11, `0x00412580` /
5 and `0x00412600` / 5 receive no ownership from SDK-shaped pointer/no-op bodies.
The separate catch interior and every prior protected lifetime/copy/math/
destruction policy retain their original rows. Complete cold evidence preceded
canonical changes. Strict R166 HEAD adbe743 readback confirms exactly twelve
function/origin changes, only one primary extent refinement, and one new authored
22-byte record; all 879 old authored rows, original headers/order, previous
manifests and exact source/header/build/ABI/mapping/match inputs remain unchanged.
Thirty-two new regression checks and all 1665 public checks pass, as do fresh
scanning, full authored extents, local attestation and whitespace checks.

Totals are 3527 resolved (927 authored, 2025 library, 575 compiler), 824 pending
and 2600 excluded. Authored evidence is 880 complete bodies / 1953711 bytes.
The exact baseline remains 60 functions / 9883 bytes, with provisional coverage
9883 / 1966054 (0.50%); the earlier R139 60/60 cold replay across eleven objects
remains applicable. No reconstructed source, private ABI, mapping or exact
credit is added. Public MCP acceptance stays waived; the complete-origin goal
is active and unfinished. The next bounded R168 cohort is the seven list-iterator
policies / 233 bytes recorded in the current handoff, with complete independent
game parents and necessary lower operation/EH dependencies.

## R168 — whole list iterator, insertion, erase and exception graphs

Nineteen library definitions / 1097 bytes are accepted through the complete
seven-candidate iterator cohort and necessary closed dependencies. Replay
`scripts/repo-python scripts/verify-list-iterator-policy-origins.py` with
immutable `config/list-iterator-policy-origin-evidence.json`. Full unchanged R035
custom game parents `0x00411000` / 183 and `0x00411110` / 746 retain original
authored records, complete instructions, CFG and actual argument/value context.
Their field/stack/copy/render policies provide independent game context; ownership
is inferred from the entire defining SDK graph, not those caller labels alone.

| Address | Complete bytes | Inferred SDK role |
| --- | ---: | --- |
| `0x00411C90` | 42 | list begin |
| `0x00411CC0` | 31 | list end |
| `0x00411CE0` | 17 | list size |
| `0x00411D00` | 40 | list pop-front |
| `0x00411D30` | 42 | list push-back |
| `0x00411E00` | 19 | mutable iterator arrow |
| `0x00411E20` | 42 | mutable iterator postincrement |
| `0x004121C0` | 28 | mutable iterator node constructor |
| `0x00411F20` | 186 | list erase |
| `0x00411EA0` | 115 | list insertion |
| `0x004121E0` | 19 | mutable iterator dereference |
| `0x00412200` | 22 | mutable iterator preincrement |
| `0x00412240` | 189 | value-node allocation, catch and shared tail |
| `0x00412310` | 126 | size growth with full length-error path |
| `0x00412460` | 25 | const iterator dereference |
| `0x00412480` | 35 | const iterator preincrement |
| `0x004124D0` | 22 | list maximum size |
| `0x00412510` | 53 | SDK node constructor with whole value copy |
| `0x00412550` | 44 | value allocator maximum size |

Target observation: the old value-node allocation ends at `0x004122C8` before
catch. The complete primary is `0x00412240..0x004122FC` / 189 bytes. It includes
the +137 catch and complete shared tail, all branches/exits, placement allocation,
actual node construction, cleanup/deallocation and rethrow. Own primary source
AUX is 189 bytes. The entire 27-byte placement-cleanup/handler carrier and
88-byte unwind/catch/try/FuncInfo carrier are compared with all real fields.
R020 registration at `0x00655051` remains unchanged. Canonical primary extent
is refined before acceptance; no 137-byte prefix earns evidence. The independent
52-byte catch candidate `0x004122C9` stays unknown with the overlap explicit.

Compiler/source observation: genuine SDK mutable/const iterator, erase, insertion,
node construction and size-growth definitions form one coherent catalog, through
unchanged R167 allocation/destruction, R106 iterator constructor and placement
helpers. The complete synthetic 164-byte value record produces the actual
172-byte node and capacity divisor 164. All 93 whole positive source/code/EH/
throw/RTTI/data controls / 4248 bytes compare unmasked with 210 genuine fields.
This includes the full length-error string, throw descriptors, catchable-type
arrays, type descriptors, exception/string code and every EH/state carrier.
Six original R020 frames are verified against their real owners. R004/R005
exception/string/compiler classifications, R142 exception/frame/throw/delete,
R154 scalar new and R006/R025 string/memory runtime boundaries are retained;
no whole-executable compiler profile or reclassification is inferred.

Ordinary size, arrow and postincrement alternatives reproduce all 17/19/42
bytes / 78 bytes, using the same independent complete real operation boundaries.
They demonstrate source-shape ambiguity; original method spelling and declaration
identity remain unresolved. Regular positives retain full own AUX extents.
The existing 37-/100-byte implicit exception copy constructors lack primary AUX
and are checked as their entire unique defining code COMDATs, preserving their
original compiler ownership. No prefix, fake return, padding, inert local or
conditional source body is used. Complete observers instantiate no incomplete
original game owner. The value width is an observation, not recovered private
layout. One actual readonly four-byte external type-info slot is retained without
claiming a whole vtable extent.

All 225 cold ordinary sections / 10007 bytes, 29 actual SDK headers plus the two
unchanged pinned R166/R167 probe includes, and entire combined 76-byte layout
`[20,20,84,84,40,4,4,12,20,164,20,12,1,16,4,4,12,1,4]` are frozen. Sixteen prior
records and 182 complete canonical/body snapshots preserve all existing ownership.
The R162 manifest remains immutable. For its two pending candidate records,
only the exact R162 accepted-pending to R168 accepted-library rows are allowed;
for the two separate snapshot contexts, only exact original-to-R168 transitions
are allowed. Both old ordinary and cookie-negative source profiles cold-replay.
Its original unresolved decisions remain historical evidence, with later full
acceptance checked separately. All other old ambiguities remain unchanged.

Tiny pointer/node/value accessors at `0x00411E80`, `0x00411E90`, `0x004124B0`
and `0x004124C0`, both empty destruction children and both catch interiors keep
unknown ownership. Earlier unrelated lifetime/copy/math/destruction policies are
preserved. Complete cold evidence precedes canonical changes. Strict R167 HEAD
70876bb readback verifies exactly nineteen function/origin changes, only one
primary extent refinement, and no new authored rows. All 880 original authored
rows/order, prior manifests and exact source/header/build/ABI/mapping/match inputs
are preserved. Thirty-four new regression checks and all 1699 public checks pass,
as do fresh scanning, authored extents, local attestation and whitespace checks.

Totals are 3546 resolved (927 authored, 2044 library, 575 compiler), 805 pending
and 2619 excluded. Authored evidence remains 880 complete bodies / 1953711
bytes. The exact baseline remains 60 functions / 9883 bytes with provisional
coverage 9883 / 1966054 (0.50%); R139's earlier 60/60 cold replay across eleven
objects remains applicable. No source/private ABI/mapping/exact credit is added.
Public MCP acceptance remains waived and the full remaining-origin goal is active
and unfinished. The next bounded R169 cohort is five archive-list dependencies
/ 160 bytes with full R052 write/index policies, recorded in the current handoff.

## R169 — complete archive-list graph and independent value width

Thirteen library definitions / 753 bytes are accepted through the five-candidate
archive-list cohort and necessary complete SDK dependencies. Replay
`scripts/repo-python scripts/verify-archive-list-policy-origins.py` with immutable
`config/archive-list-policy-origin-evidence.json`. Full unchanged R052 archive
write/index policies `0x0041D260` / 686 and `0x0041D510` / 429 retain complete
instructions, actual field/value/argument context, original authored records
and CFG. Their archive-specific behavior provides independent ownership context;
caller labels, mapped types and short byte shapes alone prove no ownership.

| Address | Complete bytes | Inferred SDK role |
| --- | ---: | --- |
| `0x0041D950` | 42 | list begin |
| `0x0041D980` | 31 | list end |
| `0x0041D9A0` | 17 | list size |
| `0x0041D9C0` | 42 | list push-back |
| `0x0041EF00` | 28 | iterator node constructor |
| `0x0041E120` | 115 | list insertion |
| `0x0041EF60` | 186 | complete value-node allocation, catch and shared tail |
| `0x0041F020` | 126 | size growth with full length-error path |
| `0x0041F0F0` | 27 | node allocator allocation |
| `0x0041F980` | 53 | SDK node constructor and whole value copy |
| `0x0041F800` | 22 | list maximum size |
| `0x0041FD90` | 20 | node allocation with actual 116-byte multiplier |
| `0x0041F9C0` | 44 | value allocator maximum size |

Target observation: the archive reader processes an observed 108-byte stride;
actual node placement allocates 116 bytes. This list's capacity calculation uses
value width 108. The complete allocation is `0x0041EF60..0x0041F019` / 186
bytes, including local catch at +134 and shared tail. Its previous provisional
134-byte entry stops before catch. Source primary AUX covers the whole 186
bytes. The complete 27-byte cleanup/handler carrier at `0x006554C0` and 88-byte
unwind/catch/try/FuncInfo carrier at `0x00668690` retain every actual field and
R020 registration `0x006554D1`. The separate 52-byte catch candidate
`0x0041EFE6` remains unknown; no independent primary AUX/ownership is claimed.

Compiler/source observation: a complete synthetic 108-byte record produces the
116-byte node and genuine list/iterator/insertion/allocation graph. All eighty
whole positive source/code/EH/throw/RTTI/data controls / 3752 bytes compare
unmasked with 189 real fields through one coherent actual defining-symbol
catalog. These include full string/length-error, throw/catchable-type/type
metadata and actual exception/runtime boundaries. Existing R106 constructor/
deallocation, R160 placement delete, R004/R005 string/exception/compiler,
R142 exception/frame/throw/delete, R154 scalar new and R006/R025 string/memory
owners remain independent. Six original R020 frames are verified. The existing
37-/100-byte implicit exception copies are checked as complete unique code
COMDATs despite lacking primary AUX; all regular positives have full own AUX.

The entire ordinary size alternative / 17 bytes is byte-equal. Original method
spelling stays unknown. The full previous 164-byte-payload node allocation /
23 bytes is negative against the entire 20-byte target; the full unsigned-node
allocation / 20 bytes differs at its genuine node-width immediate. Together these
two negatives / 43 bytes retain actual scalar new, never compare target prefixes
and earn no positive source/exact credit. Neither the 108-byte observation nor
the complete source emission recovers the original archive entry declaration,
packing, member identity or private game layout. No incomplete original owner
is instantiated and no target byte array, assembly, fake return or inert padding
is used. One actual four-byte readonly external type-info slot establishes no
whole vtable extent.

All 250 cold ordinary sections / 11163 bytes, 29 actual SDK headers plus the
unchanged pinned R166/R167/R168 probe includes, and entire combined 88-byte
layout `[20,20,84,84,40,4,4,12,20,164,20,12,1,16,4,4,12,1,4,108,12,4]` are
frozen. Eleven prior records and 205 complete canonical/body snapshots preserve
existing context. R162's manifest remains immutable; its two relevant pending
candidate records allow only exact accepted-pending to R169 library transitions,
and two separate snapshots allow only exact original-to-R169 transitions.
Both old ordinary and cookie-negative profiles cold-replay. Previous R168
transitions remain exact and intact; all other historical pending decisions and
protected opaque owners stay unchanged.

Link accessors `0x0041E100` / 8 and `0x0041E110` / 11, node getter
`0x0041F7E0` / 16 and the catch interior receive no origin from source-equal
short bodies. Earlier independent getters, empty destruction children and
lifetime/copy/math policies are preserved. Complete cold evidence preceded
canonical changes. Strict R168 HEAD ca7566f readback verifies exactly thirteen
function/origin changes, only one full primary extent refinement and no authored
additions. All 880 original authored rows/order, previous manifests and exact
source/header/build/ABI/mapping/match inputs remain intact. Thirty-six new
regression checks and all 1735 public checks pass, with fresh scanning, full
authored extents, local attestation and whitespace checks.

Totals are 3559 resolved (927 authored, 2057 library, 575 compiler), 792 pending
and 2632 excluded. Authored evidence remains 880 complete bodies / 1953711
bytes. Exact stays 60 functions / 9883 bytes, with provisional coverage
9883 / 1966054 (0.50%); R139's earlier cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added.
Public MCP acceptance stays waived; the full remaining-origin goal is active
and unfinished. The next bounded R170 cohort is five character-list dependencies
/ 160 bytes through the complete R049 1008-byte game policy, recorded in the
current handoff. Its value width must be established independently.

## R170 — character-list graph with independently observed value width

Twelve complete library definitions / 720 bytes are accepted through the five
character-list roots and necessary complete SDK dependencies. Replay
`scripts/repo-python scripts/verify-character-list-policy-origins.py` with immutable
`config/character-list-policy-origin-evidence.json`. The unchanged independently
authored R049 game policy `0x005301B0` / 1008 bytes retains every instruction,
original authored record, complete CFG and switch records. Actual push-back and
size calls at `0x00530225` / `0x00530233` provide independent argument/value
context. Caller labels, mapped types and short byte shapes alone prove no owner.

| Address | Complete bytes | Inferred SDK role |
| --- | ---: | --- |
| `0x00531DA0` | 42 | list begin |
| `0x00531DD0` | 31 | list end |
| `0x00531C60` | 17 | list size |
| `0x00531CB0` | 42 | list push-back |
| `0x00532300` | 28 | mutable iterator node constructor |
| `0x00531DF0` | 115 | list insertion |
| `0x00532110` | 186 | complete value-node allocation with catch and shared tail |
| `0x005321D0` | 126 | size growth with full length-error path |
| `0x005322A0` | 27 | node allocator allocation |
| `0x005323E0` | 64 | node constructor with complete four-word value copy |
| `0x00532360` | 22 | list maximum size |
| `0x005324A0` | 20 | node allocation with actual 24-byte multiplier |

Target observation: actual node placement requests 24 bytes at `0x0053214D`;
the node constructor copies the complete observed 16-byte value. Capacity uses
value width 16. The complete primary `0x00532110..0x005321C9` is 186 bytes,
including its local catch at +134 and shared tail; the previous 134-byte extent
stops before catch. Source primary AUX independently covers all 186 bytes.
The whole 27-byte cleanup/handler carrier `0x00656520` and 88-byte unwind/catch/
try/FuncInfo carrier `0x00669E5C` retain every real field and R020 registration
`0x00656531`. The separate 52-byte interior `0x00532196` stays unknown; its
local-label membership supplies no separate primary AUX or ownership evidence.

Compiler/source observation: a complete synthetic 16-byte value produces a
24-byte node and the genuine SDK list/iterator/insertion/allocation graph. The
64-byte node constructor differs naturally from the previous larger-record
copy strategy. All eighty complete positive source/code/EH/throw/RTTI/data
controls / 3763 bytes compare unmasked with 189 genuine fields through one
coherent actual defining-symbol catalog. Full string/length-error, throw and
catchable-type/type metadata retain independent exception/runtime boundaries.
Existing R106 const-iterator construction `0x005323C0` / 24 and deallocation,
R032 allocator maximum size `0x00532420` / 44, R160 placement delete,
R004/R005 string/exception/compiler, R142 exception/frame/throw/delete,
R154 scalar new and R006/R025 string/memory records remain unchanged. Six
original R020 frames are verified. Existing 37-/100-byte implicit exception
copies retain their complete unique defining COMDATs despite lacking primary
AUX; every regular positive has its own full primary AUX.

The whole ordinary size alternative / 17 bytes is byte-equal, so original
method spelling remains provisional. Two entire prior-108 and unsigned node
allocation negatives / 20 bytes each compare against the entire 20-byte target,
retaining actual scalar new. Each differs at genuine node-width immediate byte
+8. Neither negatives nor short equivalent shapes earn positive/exact credit.
Widths 16/24 are observations of this list, independent of earlier 164/172 and
108/116 observations; original character-entry declaration, packing, fields and
private game layout remain unknown. The complete synthetic observer establishes
no original owner, and uses no target arrays, assembly, fake returns or inert
padding. One four-byte readonly external type-info slot establishes no whole
vtable extent.

All 275 cold ordinary sections / 12330 bytes, 29 actual SDK headers plus four
unchanged pinned R166/R167/R168/R169 probe includes, and the entire 100-byte
combined layout are frozen. Its 25 words are
`[20,20,84,84,40,4,4,12,20,164,20,12,1,16,4,4,12,1,4,108,12,4,16,12,4]`.
Eleven prior records, including the complete R169 node allocation, and 227
complete canonical/body snapshots preserve existing context. R162's manifest
stays immutable. Only two exact accepted-pending to R170 library transitions
and two exact separate original-to-R170 snapshot transitions are allowed. Both
old ordinary and cookie-negative profiles cold-replay. R168/R169 transitions
remain exact; all unrelated historical pending decisions stay unchanged.

Link accessors `0x00531D80` / 8 and `0x00531D90` / 11, node getter
`0x00532350` / 16 and the catch interior remain unknown. All prior opaque
getters, empty destruction children and lifetime/copy/math policies are preserved.
Full cold evidence preceded canonical changes. Strict R169 HEAD e9ba039 readback
verifies exactly twelve function/origin changes, only the one full primary extent
refinement and no authored additions. All 880 original authored rows/order,
previous manifests and source/header/build/ABI/mapping/match inputs remain
intact. Thirty-six new regression checks and all 1771 public checks pass, with
fresh scanning, full authored extents, local attestation and whitespace checks.

Totals are 3571 resolved (927 authored, 2069 library, 575 compiler), 780 pending
and 2644 excluded. Authored evidence stays 880 complete bodies / 1953711 bytes.
Exact stays 60 functions / 9883 bytes with provisional coverage
9883 / 1966054 (0.50%); the earlier R139 cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added. Public
MCP acceptance stays waived. The full remaining-origin goal is active and
unfinished; the next bounded cohort is the three complete default deque
const-iterator candidates and their actual whole producer/consumer contexts.

## R171 — complete replay deque iterator graphs

Twelve whole SDK definitions / 381 bytes are accepted through the three default
const-iterator candidates and necessary complete construction/endpoint context.
Replay `scripts/repo-python scripts/verify-replay-deque-iterator-origins.py` with
immutable `config/replay-deque-iterator-origin-evidence.json`. The independently
authored R035 `ReplayRecords::AppendRecord` at `0x00413DE0` / 1252 remains
unchanged, with its original full record, instructions, fourteen branches, one
return and switch rows. Its 26 actual iterator construction/endpoint/step/
comparison/dereference edges are frozen. Default temporaries feed the actual
iteration and write loops; observed stream widths 1/2/4 supply independent
context for the three entire specialization graphs. Caller labels, mapped
names and two zero stores alone are insufficient ownership evidence.

| Address | Complete bytes | Inferred SDK role |
| --- | ---: | --- |
| `0x00414930` | 22 | default iterator |
| `0x004149E0` | 22 | default iterator |
| `0x004145C0` | 35 | begin |
| `0x004145F0` | 41 | end |
| `0x00414A90` | 22 | default iterator |
| `0x004147B0` | 35 | begin |
| `0x004147E0` | 41 | end |
| `0x004155A0` | 33 | default const iterator |
| `0x004156B0` | 33 | default const iterator |
| `0x00415670` | 32 | node iterator constructor |
| `0x004157C0` | 33 | default const iterator |
| `0x00415780` | 32 | node iterator constructor |

Compiler/source observation: complete `std::deque<unsigned char>`,
`std::deque<unsigned short>` and `std::deque<unsigned long>` observers emit
three natural default/endpoint/postfix/prefix/comparison/dereference graphs.
All 36 entire genuine SDK definitions / 1437 bytes retain 21 real call fields
and compare unmasked through one coherent actual defining-symbol catalog.
This includes the already accepted R111 byte endpoints/node construction,
R112 postfix operations, R085/R106 prefix operations and const-node constructors,
R032 inequality, R084 equality and R078 complete dereference bodies. The
three specializations independently retain their actual destinations; widths
and synthetic types do not recover original signedness, declarations, method
spelling or private replay/game owner layout.

Entire ordinary base/default and derived constructors / 33 and 22 bytes are
byte-equal to the byte iterator construction pair, including the one actual
base-construction field. These expose short-shape ambiguity rather than proving
original ownership. With these controls the whole positive comparison is
38 bodies / 1492 bytes and 22 genuine unmasked fields. Every regular positive
has its full own primary AUX extent and complete CFG. No external call or data
field is guessed or masked. No target byte arrays, assembly, fake returns,
inert padding or incomplete original game owner are used.

All 43 cold ordinary sections / 1903 bytes, including complete observer/ordinary
code and readonly layout, and 27 actual SDK headers are frozen. The whole
48-byte layout is `[1,2,4,20,20,20,8,8,8,8,8,8]`. Seventy canonical/body snapshots
preserve all prior protected unknowns and complete existing SDK/game bodies.
The full original R110 and R113 peer records at `0x00445530` / `0x00424500`
and their immutable manifests remain unchanged. Those peers are diagnostic
context and never replace the independent whole R035 parent or genuine new
source graph. The prior R170 manifest is pinned; no historical transition or
relaxed pending-ledger exception is needed for this cohort.

Full cold evidence preceded canonical acceptance. Strict R170 HEAD f68a5d0
readback checks exactly twelve function/origin transitions, unchanged extents,
all 880 original authored rows/order and all prior tracked configuration.
All previous evidence and source/header/build/ABI/mapping/match inputs stay
unchanged. Thirty-two new regression checks and all 1803 public checks pass,
with fresh scanning, full authored extents, local Ghidra attestation and
whitespace checks. Every protected getter, empty destruction child and
catch/lifetime/copy/math policy retains its independent unknown origin.

Totals are 3583 resolved (927 authored, 2081 library, 575 compiler), 768 pending
and 2656 excluded. Authored evidence stays 880 complete bodies / 1953711 bytes.
Exact stays 60 functions / 9883 bytes; provisional coverage remains
9883 / 1966054 (0.50%). The prior R139 cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added.
Public MCP acceptance stays waived. The full remaining-origin goal is active
and unfinished. The next bounded R172 cohort is three complete front helpers
through these actual SDK graphs and independent full fighter/battle policies.

## R172 — complete front helpers with independent consumer widths

Three complete library front helpers / 96 bytes are accepted: `0x00454D50`,
`0x00454E10` and `0x004464C0`, each 32 bytes. Replay
`scripts/repo-python scripts/verify-replay-deque-front-origins.py` with immutable
`config/replay-deque-front-origin-evidence.json`. Each whole SDK front body calls
its actual begin and then iterator dereference, with both real fields unmasked:
byte `0x004143D0` / `0x00414950`, word `0x004145C0` / `0x00414A00`, and
dword `0x004147B0` / `0x00414AB0`. Full own primary AUX and complete CFG are
verified for every positive source definition.

Independent target context is preserved in three full authored policies:
R045 fighter controls `0x00452F10` / 2815, R109 recorded random selection
`0x00455580` / 139 and R065 battle sequence `0x00445A00` / 1958, totaling 4912
bytes. Their complete original records, instructions, CFG, switches and eight
actual front calls remain unchanged. Actual returned-pointer loads at
`0x00452FBB`, `0x004555B3` and `0x00445A4E` independently observe byte/word/
dword widths 1/2/4. The verifier checks actual decoded memory operand widths,
base EAX and zero index/displacement. This supplies new consumer evidence;
R171's scalar observations and mapped caller names alone are not inherited as
ownership proof. Original scalar declarations, signedness and private owner
layouts remain unknown; later signed use does not recover the original template
argument.

Compiler/source observation: natural SDK front definitions for three complete
scalar specializations close through the full accepted R171 iterator/endpoint/
comparison/step/dereference graph. A complete synthetic class derives naturally
from the byte deque and implements `first()` as `*begin()`. Its entire 32-byte
body is byte-equal with both genuine SDK call fields, so original method spelling
remains provisional. No incomplete original owner is instantiated. No target
arrays, assembly, fake returns, inert padding or guessed ABI are used.

All 42 entire SDK/ordinary controls / 1620 bytes compare unmasked with 30 real
fields through one coherent defining-symbol catalog. All 51 cold ordinary
sections / 2111 bytes and 27 actual SDK headers plus the pinned original R171
probe include are frozen. The whole 76-byte readonly layout is
`[1,2,4,20,20,20,8,8,8,8,8,8,1,2,4,20,20,20,20]`. All 38 prior R171 controls
retain their complete source/body/CFG/field identities. Seventy-six canonical/
body snapshots and fifteen original complete accepted records preserve earlier
SDK/game/peer evidence. The immutable R109 manifest retains its historical
unknown child snapshots; its existing verifier explicitly permits later
independent origin review while checking complete unchanged context. That
verifier passes without changes or new relaxed callbacks. All protected
getters, empty destruction children and catch/lifetime/copy/math owners stay
unknown.

Full cold evidence preceded canonical acceptance. Strict R171 HEAD 63339e6
readback checks exactly three function/origin transitions, all unchanged
extents, all 880 original authored rows/order and every prior tracked manifest/
configuration. Thirty new regression checks and all 1833 public checks pass,
with fresh scanning, full authored extents, local Ghidra attestation and
whitespace checks. All prior source/header/build/ABI/mapping/match inputs stay
unchanged.

Totals are 3586 resolved (927 authored, 2084 library, 575 compiler), 765 pending
and 2659 excluded. Authored evidence stays 880 complete bodies / 1953711 bytes.
Exact stays 60 functions / 9883 bytes; provisional coverage remains
9883 / 1966054 (0.50%). The earlier R139 cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added. Public
MCP acceptance remains waived. The full remaining-origin goal is active and
unfinished; the next bounded R173 cohort is four complete iterator/index
candidates through the unchanged R019 bitmap-directory policies.

## R173 — complete texture-vector access and erase context

Seven complete library definitions / 235 bytes are accepted through the four
iterator/index roots and necessary full iterator dependencies. Replay
`scripts/repo-python scripts/verify-texture-vector-access-origins.py` with immutable
`config/texture-vector-access-origin-evidence.json`. The complete R019 bitmap
policies `0x0040B280` / 727 and `0x0040B560` / 575 retain all original authored
records, instructions, CFG and switch rows. Their 33 actual size/index/endpoint/
arithmetic/erase calls provide independent complete game value/argument context.
The earlier sprite label in the shortlist was corrected against the original
R019 bitmap-directory records; no origin depends on that temporary label.

| Address | Complete bytes | Inferred SDK role |
| --- | ---: | --- |
| `0x0040DCE0` | 31 | begin |
| `0x0040DD00` | 31 | end |
| `0x0040DD60` | 49 | unchecked index |
| `0x0040DFD0` | 45 | iterator addition |
| `0x0040E4A0` | 28 | mutable pointer iterator constructor |
| `0x0040E4C0` | 19 | mutable iterator dereference |
| `0x0040E4E0` | 32 | mutable iterator addition assignment |

Target observations independently agree on element width 44: the complete
32-byte iterator addition assignment multiplies the offset by `0x2C` at
`0x0040E4EA`, and whole 57-byte size calculation divides the pointer difference
by 44 at `0x0040DD48..0x0040DD4E`. The complete 99-byte erase, real copy and
range-destruction paths preserve that same width. Actual bitmap loading writes
and reads record fields and passes the real index/iterator/erase values; original
record declarations, packing, names and complete private owner layouts remain
unknown. A preliminary 16-byte diagnostic observer was corrected before any
manifest or canonical acceptance and supplies no evidence.

Compiler/source observation: a complete synthetic 44-byte record with an external
lifetime declaration closes the natural SDK vector access/size/erase/copy/
destruction graph. All 22 full SDK/compiler controls / 815 bytes retain 22 real
fields. Existing R032/R033 size/erase/copy/destruction/equality and R106 const
construction remain independent. The entire 44-byte scalar deleting thunk
`0x0040FA00` preserves compiler origin R037, its original full evidence row,
actual opaque destructor and independently reviewed scalar delete. This generated
function has no primary AUX; its entire unique defining code COMDAT is verified.
Every regular positive retains its own full primary AUX and complete CFG.
No source prefix, target array, assembly, fake return, inert padding, masked field
or private ABI misdeclaration is used.

Whole ordinary begin/end/index alternatives / 31,31,49 bytes are byte-equal with
all five actual fields. They preserve the ambiguity of short method bodies.
Library ownership is an inference from the newly complete actual index/stride/
size/erase/copy/destruction graph and whole independent bitmap policies, rather
than mapped names, caller labels or byte equality alone. Original method spelling
stays provisional. With these alternatives, all 25 full controls / 926 bytes
compare unmasked with 27 genuine fields through one coherent defining-symbol
catalog. All 35 cold ordinary sections / 1129 bytes, 27 actual SDK headers and
whole 24-byte layout `[44,16,4,4,16,1]` are frozen. Container/iterator observation
sizes do not recover a complete original game owner.

Fifty-five canonical/body snapshots and five original full pending/runtime/
compiler records preserve previous evidence. Only three exact R162 historical
accepted-pending to R173 accepted-library ledger transitions are added, with
both old source profiles cold-replayed. The immutable R162 manifest and all
R168/R169/R170 transitions remain intact. The original 158-byte assignment
`0x0040E000`, 16-byte const pointer getter `0x0040E9B0`, 15-byte destruction
wrapper `0x0040F9F0` and 19-byte custom lifetime policy `0x0040D8E0` remain
independently unknown, as do all earlier protected opaque owners. Successful
source reproduction of a low-level child grants no separate ownership.

Full cold evidence preceded canonical acceptance. Strict R172 HEAD cfb1d52
readback verifies exactly seven function/origin changes, unchanged extents,
all 880 original authored rows/order and every earlier tracked configuration.
Thirty-four new regression checks and all 1867 public checks pass, with fresh
scanning, complete authored extents, local Ghidra attestation and whitespace
checks. All prior source/header/build/ABI/mapping/match inputs stay unchanged.

Totals are 3593 resolved (927 authored, 2091 library, 575 compiler), 758 pending
and 2666 excluded. Authored evidence remains 880 complete bodies / 1953711 bytes.
Exact stays 60 functions / 9883 bytes with provisional coverage
9883 / 1966054 (0.50%); the earlier R139 cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added. Public
MCP acceptance remains waived; the full remaining-origin goal is active and
unfinished. The next bounded R174 cohort is the secondary texture-vector index
and mutable dereference candidates through complete R017 resource policies and
independently accepted R161/R095/R034 SDK context.

## R174 — independent secondary texture-vector access

Two complete library definitions / 68 bytes are accepted: unchecked index
`0x0040DEE0` / 49 and mutable iterator dereference `0x0040E530` / 19. Replay
`scripts/repo-python scripts/verify-secondary-texture-access-origins.py` with
immutable `config/secondary-texture-access-origin-evidence.json`. The entire
R017 texture initialization `0x0040AD80` / 177 and resource release `0x0040AE40`
/ 434 preserve their original 611 bytes, authored records, instructions, CFG
and switch evidence. Their five actual index calls and returned-pointer slot
accesses supply independent game argument/value context. Unchanged R034
assignment `0x0040E210` / 96 and full R161 endpoint records remain independent.

Target observation: the actual 32-byte iterator addition assignment
`0x0040EA00` uses `LEA EAX,[ECX+EDX*4]` at `0x0040EA0F`. The full game policies
read and clear four-byte slots through actual index results. This independently
observed width is four, rather than an inherited width from another container.
The original slot type, method names and complete private owner layout remain
unknown. A query initially requested an interior address while locating the
const constructor; only the actual complete `0x0040F120` / 24 target extent
and genuine defining source supply evidence.

Compiler/source observation: a complete synthetic four-byte record closes eight
entire SDK definitions / 244 bytes with seven genuine fields. Actual index calls
the accepted R161 begin, R095 addition and the mutable dereference. Its const
getter and both complete iterator constructors are compared through their own
full primary AUX extents. Whole ordinary begin/index/dereference alternatives
/ 31,49,19 bytes are byte-equal with five fields. They preserve original method
spelling uncertainty. Library ownership is an inference from this complete
typed source graph and the independent entire game policies; neither caller
labels nor byte equality alone is sufficient.

All eleven whole controls / 343 bytes compare without masks using twelve actual
fields and one coherent defining-symbol catalog. All fifteen cold ordinary
sections / 414 bytes, 27 actual SDK headers and whole 24-byte readonly layout
`[4,16,4,4,16,4]` are frozen. Forty-three canonical/body snapshots and two whole
prior R161 records preserve previous evidence. The 16-byte const getter
`0x0040EA20` remains independently unknown, together with all previously protected
opaque getter, destruction, assignment, lifetime, math and catch policies.

Complete cold replay preceded acceptance. Strict R173 HEAD eed679a readback
permits exactly two function/origin changes with unchanged extents, preserves
all 880 original authored evidence rows/order and all earlier tracked
configuration. Thirty new regression checks and all 1897 public checks pass.
Fresh scanning, full authored extent validation, pinned target and local Ghidra
attestation, exact-input preservation and whitespace checks pass. No prior
source/header/build/ABI/mapping/match input changes require an exact replay.

Totals are 3595 resolved (927 authored, 2093 library, 575 compiler), 756 pending
and 2668 excluded. Authored evidence remains 880 complete bodies / 1953711 bytes.
Exact stays 60 functions / 9883 bytes with provisional coverage
9883 / 1966054 (0.50%); the prior R139 cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added. Public
MCP acceptance remains waived. The full remaining-origin goal remains active
and unfinished. Original R108 full explicit/implicit alternatives already leave
0x00411C10, 0x004251C0 and 0x00449DE0 indistinguishable; they are not repeated
as new acceptance candidates. The next bounded R175 review examines three
resource-release parents, with genuine compiler-generated lifetime alternatives
required wherever ownership remains ambiguous.

## R175 — explicit resource-release policies and whole list cleanup graphs

Three complete authored release policies / 286 bytes and ten complete library
cleanup definitions / 644 bytes are accepted. Replay
`scripts/repo-python scripts/verify-resource-release-policy-origins.py` with
immutable `config/resource-release-policy-origin-evidence.json`. All candidate
extents, returns, internal branches, actual direct/indirect calls and registered
unwind state transitions are reconciled. Original R017 texture release / 434
and R045 fighter release / 588 retain their full 1022 bytes, authored records,
instructions, CFG and switch evidence. Three entire R037 scalar deleting
parents / 132 bytes and their original evidence remain compiler-owned.

| Address | Entire bytes | Origin and inferred role |
| --- | ---: | --- |
| `0x00412E50` | 83 | authored: SharedResource::ReleaseInterfaceAndTexturesAt00412E50 |
| `0x0041D1F0` | 98 | authored: ArchiveResource::CloseHandleAndClearEntriesAt0041D1F0 |
| `0x0052D020` | 105 | authored: CharacterResource::ClearEntriesAndReleaseBaseAt0052D020 |
| `0x0041D9F0` | 153 | library: std::list::clearAt0041D9F0 |
| `0x0041D930` | 19 | library: std::list::destructorAt0041D930 |
| `0x0041E280` | 100 | library: std::list::_TidyAt0041E280 |
| `0x0041E360` | 25 | library: std::list::allocator::destroyNodeAt0041E360 |
| `0x0041F130` | 25 | library: std::list::allocator::destroyNodePointerAt0041F130 |
| `0x00531CE0` | 153 | library: std::list::clearAt00531CE0 |
| `0x00531C40` | 19 | library: std::list::destructorAt00531C40 |
| `0x00532010` | 100 | library: std::list::_TidyAt00532010 |
| `0x005320F0` | 25 | library: std::list::allocator::destroyNodeAt005320F0 |
| `0x005322E0` | 25 | library: std::list::allocator::destroyNodePointerAt005322E0 |

Target observation: the 83-byte shared resource policy invokes the third
interface slot through the pointer at offset zero, then destroys the texture
subobject at +40. The 98-byte archive policy tests its handle, calls the actual
KERNEL32.dll CloseHandle import at `0x00657138`, explicitly clears its list at
+4 and then invokes member destruction. The 105-byte character policy writes
one observed vtable address, explicitly clears its list at +0xFEC, destroys
that member and calls the complete independently authored fighter base release.
Whole original R020 frames preserve complete cleanup tables and registration.
These explicit release/clear operations distinguish the bodies from a generated
sequence that only destroys members and bases. Original class declarations,
method spelling, private owner layouts and the selected virtual target remain
independent and unresolved where previously unresolved.

Compiler/source observation: complete natural archive and shared resource
destructors reproduce all 98 and 83 target bytes, including their genuine
exception registration fields, whole 21-byte cleanup/handler carriers and
36-byte unwind/FuncInfo carriers. Explicitly documented synthetic intervening
scalars test only the observed shared-resource +40 subobject spacing. Complete
compiler-generated alternatives are 22 bytes each and lack the explicit handle
close/list clear or interface release. They retain their entire unique defining
code COMDAT and actual missing primary AUX metadata, rather than receiving an
invented function size or a sliced source prefix.

The character policy is accepted from its whole target CFG and actual explicit
clear-before-member/base destruction. A complete small synthetic base tests
source call order without reproducing the +0xFEC original layout. Its complete
explicit 99-byte and implicit 75-byte destructors show the additional clear call
and subsequent automatic member/base destruction. Neither control is a positive
byte match for the 105-byte target; no authored source-match credit is claimed.
The exact source profile is a reproducibility setting, not an executable-wide
compiler inference.

The two complete SDK list cleanup graphs use independent existing R169/R170
108-/16-byte value-node contexts. Full clear, tidy, list destructor and node/
node-pointer allocator destruction definitions compare with their actual
entire children and real fields. Both whole ordinary 19-byte tidy wrappers are
byte-equal. Library ownership is an inference from the closed typed graph and
whole explicit game policies; short method spelling remains provisional.
Eight-/eleven-byte node-link getters and five-byte destruction children stay
unknown. All other protected opaque ownership stays unchanged.

All 28 entire positive custom/SDK/ordinary/EH/data controls / 1085 bytes compare
unmasked with 56 genuine fields through one coherent defining-symbol catalog.
All 52 cold ordinary sections / 1858 bytes, 28 actual SDK headers and whole
44-byte readonly layout `[108,16,12,12,16,16,44,44,4,16,16]` are frozen.
Four whole compiler/source alternatives preserve 218 bytes of explicit/implicit
emission. Sixty-eight canonical/body snapshots, five full previous node/deleting
records and three whole original registered frames preserve historical evidence.
Only one observed four-byte virtual slot is frozen; no whole vtable extent or
complete original owner is inferred. The actual PE import directory is read back.

Cold full-source replay preceded canonical acceptance. Strict R174 HEAD 4f6a698
readback permits exactly thirteen function/origin changes with unchanged extents
and exactly three new full authored records. All 880 original authored rows/order
and earlier tracked configurations remain unchanged. Thirty-five new guards and
all 1932 public checks pass, together with full authored extent validation, fresh
scanning, pinned target/local Ghidra attestation and whitespace checks. All prior
source/header/build/ABI/mapping/match inputs remain unchanged; no exact replay
is required for this origin-only addition.

Totals are 3608 resolved (930 authored, 2103 library, 575 compiler), 743 pending
and 2678 excluded. Authored evidence is 883 whole bodies / 1953997 bytes.
Exact stays 60 functions / 9883 bytes, with provisional coverage
9883 / 1966340 (0.50%). The earlier R139 cold 60/60 exact replay across eleven
objects remains applicable. No reconstructed source/private ABI/mapping/exact
credit is added. Public MCP acceptance remains waived; the complete-origin
goal remains active and unfinished. The next bounded R176 diagnostic cohort
is four iterator arithmetic wrappers through independent whole R078/R083 SDK
parent/child evidence; derive each actual type-width/argument flow independently.

## R176 — whole deque retreat graphs and real addition destinations

Four complete library iterator subtraction-assignment definitions / 108 bytes
are accepted: `0x0041F650`, `0x0041F6F0`, `0x00455D10` and `0x005F9530`, each
27 bytes. Replay `scripts/repo-python scripts/verify-deque-retreat-origins.py`
with immutable `config/deque-retreat-origin-evidence.json`. Whole accepted
R078 addition/subtraction-shaped callers and R083 addition-assignment bodies
retain their original records, extents, canonical names and ownership.

Target observation: every wrapper negates the incoming signed offset at +10
and calls its entire 31-byte addition-assignment child at +16. Each 57-byte
subtraction caller passes the incoming offset to that wrapper. The separate
real addition caller instead calls the 31-byte child directly. These complete
routes distinguish actual subtraction from the historical addition-shaped
association, even though the 57-byte wrapper shapes are otherwise identical.
Earlier source evidence remains unchanged and historical names remain provisional.
No element access or scaled pointer arithmetic occurs here; original element
width/type and full private container declarations remain unknown.

Compiler/source observation: four complete natural SDK iterator graphs use
synthetic value widths 1,2,4,64. Every corresponding subtraction assignment,
addition assignment, subtraction and genuine addition body has the same
emission across widths. Four complete ordinary derived-iterator retreat methods
/ 27 bytes are also byte-equal. Library ownership is an inference from the
closed typed SDK graph and twelve entire independently accepted parent/child
records, rather than short method shape or caller labels alone. The ordinary
alternatives preserve original method spelling uncertainty.

All twenty entire SDK/ordinary controls / 796 bytes compare unmasked through
one coherent defining-symbol catalog with sixteen genuine fields. Four whole
57-byte real-addition negatives retain their genuine addition-assignment call
destinations; comparison against the subtraction parents differs inside those
actual fields. No field is masked, substituted to the subtraction child, or
omitted. Every positive and negative retains its own complete primary AUX
extent. All 33 cold ordinary sections / 1152 bytes, 27 actual SDK headers and
whole 48-byte layout `[1,2,4,64,8,8,8,8,8,8,8,8]` are frozen. Iterator sizeof 8
is a source observation, not a claim about a complete original owner.

Eighty-four canonical/body snapshots, twelve original full R078/R083 records,
old probe source and entire earlier evidence files remain unchanged. All 37
previously protected opaque lifetime, assignment, math, catch, getter and
destruction owners stay unknown. Earlier R078/R083 proofs cold-replay and the
new whole source proof cold-builds before canonical acceptance.

Strict R175 HEAD f107bcd readback permits exactly four function/origin changes,
unchanged extents, all 883 prior authored rows/order and every earlier tracked
configuration. Twenty-eight new regression guards and all 1960 public checks
pass, together with full authored extent validation, fresh scanning, pinned
target/local Ghidra attestation and whitespace checks. All prior source/header/
build/ABI/mapping/match inputs are unchanged; no exact replay is required.

Totals are 3612 resolved (930 authored, 2107 library, 575 compiler), 739 pending
and 2682 excluded. Authored evidence remains 883 whole bodies / 1953997 bytes.
Exact remains 60 functions / 9883 bytes, with provisional coverage
9883 / 1966340 (0.50%). The earlier R139 cold 60/60 exact replay across eleven
objects remains applicable. No reconstructed source/private ABI/mapping/exact
credit is added. Public MCP acceptance stays waived; the full remaining-origin
goal is active and unfinished. The next bounded R177 diagnostic cohort is
three static resource parent bodies and their direct release helper, preserving
whole original R024/R073/R077 and R017/R166 evidence without granting ownership
from those labels.

## R177 — explicit static resource policies and owned vector cleanup

Eight complete bodies / 701 bytes are accepted: four authored policies / 595
bytes and four library dependencies / 106 bytes. Replay
`scripts/repo-python scripts/verify-static-resource-policy-origins.py` with
immutable `config/static-resource-policy-origin-evidence.json`.

| Address | Complete bytes | Inferred ownership and policy |
| --- | ---: | --- |
| `0x00413650` | 132 | authored: initialize the handle after four deque constructions |
| `0x004136E0` | 161 | authored: clear four queues, guard CloseHandle, zero the handle, then destroy members |
| `0x00413880` | 67 | authored: explicit ascending-order clear of the four queues |
| `0x005F6FF0` | 235 | authored: release queue entries, delete nonnull vector entries and clear the vector before automatic member cleanup |
| `0x005F8380` | 49 | library: pointer-vector unchecked index |
| `0x005F8320` | 19 | library: pointer-vector destructor |
| `0x005F83E0` | 19 | library: pointer-vector clear |
| `0x005F8EA0` | 19 | library: mutable pointer-iterator dereference |

Target observation: the 132-byte constructor constructs deque members at
+0x154, +0x168, +0x17C and +0x190, then explicitly writes zero to the handle at
+0. The 161-byte destructor first calls the entire 67-byte helper, tests that
handle, calls actual KERNEL32.dll CloseHandle through IAT slot `0x00657138`,
and zeros the handle inside the nonzero branch. Automatic deque destruction
then visits +0x190, +0x17C, +0x168 and +0x154. The helper visits those members in
ascending construction order and performs four clear calls. Historical R077
source-shape destructor labels remain unchanged; labels do not establish the
meaning of these explicit clear operations. Whole R024 initializer/finalizer
registrations independently retain the same static object at `0x00671750`.

The whole 235-byte policy starts with authored R166 `0x005F7140` / 162, then
iterates the vector at +0x78 with unsigned indices. Each nonnull pointer slot
is deleted through complete R037 `0x005F7EA0` / 44 with flags 1. Explicit vector
clear precedes automatic vector destruction, R017 texture release and the
whole compiler array-destruction helper for two 20-byte deque members.
The static finalizer independently binds global `0x006716C8`. Complete vector
size and iterator-add bodies establish four-byte pointer slots; that width is
also independently observed in this policy's actual pointer loads.

Source/compiler observation: complete small synthetic owners distinguish
explicit defaults, ascending queue clear, guarded handle release and explicit
owned-pointer deletion from automatic construction/destruction. They preserve
natural member ordering under both /GX and the otherwise identical profile
without /GX. Nine whole operation-order controls total 988 bytes. These are
source-operation observations, not byte-positive comparisons of the four game
roots. Their layouts differ from the unrecovered original layouts. In
particular, the synthetic pointer-owner destructor is also 235 bytes, but its
vector offset is 44 rather than the target's 120; equal size earns no match.
No padding, incomplete original owner, invented ABI or target-byte source is
used. The two 55-byte no-EH queue controls still have different forward-clear
and reverse-destruction call orders. The actual whole constructor/destructor
establish the original member order independently.

Twenty-two complete SDK/compiler/ordinary controls / 724 bytes compare
unmasked with 23 genuine fields through one defining-symbol catalog. Four
ordinary index/begin/dereference/cleanup alternatives / 118 bytes are byte-equal;
original method names remain provisional. Ownership is inferred from the
whole typed vector graph and independent explicit game policy. The 16-byte
const getter `0x005F9640` and separate 72-byte pointed-owner destructor
`0x005F7ED0` remain unknown. The five-byte scalar destruction child
`0x005FA700` retains its previously accepted R087 library evidence.

All 112 primary ordinary sections / 4968 bytes, 96 secondary sections / 3879
bytes, 28 actual SDK headers in each build and the complete 48-byte readonly
layout are frozen. The verifier retains 121 full canonical/body snapshots,
39 protected unknown bodies, five complete prior compiler/deleting records,
three entire registered R020 EH frames and two authored anchors / 596 bytes.
Earlier immutable manifests and all prior authored rows/order are preserved.
Both source profiles cold-build serially. Evidence-only replay passes before
canonical mutation; accepted-state cold replay, old static evidence, full
authored validation, target/tracking, fresh scanning and local Ghidra attestation
pass afterwards. Strict R176 HEAD f81d4f2 readback permits only eight function/
origin changes and four complete new authored records. Thirty-seven new
regression guards and all 1997 public checks pass; progress and whitespace
checks pass. All sixty source/header/build/ABI/mapping/match inputs remain
unchanged from R139 db26a05, so its earlier cold 60/60 replay across eleven
objects remains applicable.

Totals are 3620 resolved (934 authored, 2111 library, 575 compiler), 731 pending
and 2686 excluded. Authored evidence totals 887 whole bodies / 1954592 bytes.
Exact remains 60 functions / 9883 bytes, with provisional coverage
9883 / 1966935 (0.50%). No reconstruction source/private ABI/mapping/exact
credit is added. Public MCP acceptance remains waived. The full remaining-origin
goal remains active and unfinished. Continue with fresh whole lifetime-policy
candidates; a compiler parent alone grants no ownership.

## R178 — remaining explicit construction and raster lifetime policies

Two entire authored policies / 271 bytes are accepted: `0x005F6F60` / 142 and
`0x0041BFD0` / 129. Replay
`scripts/repo-python scripts/verify-remaining-lifetime-policy-origins.py` with
immutable `config/remaining-lifetime-policy-origin-evidence.json`.

Target observation: the constructor first invokes the full 98-byte array
construction helper for two 20-byte deque members, the R017 texture constructor
at +0x28 and R090 vector constructor at +0x78. After all members are constructed,
it explicitly clears the two queues in ascending order and clears the vector.
The historical R077 deque destructor-shaped aliases are preserved; the actual
post-construction operation and complete source controls distinguish explicit
clear from automatic construction. Whole R024 registration binds the same
static object `0x006716C8` as the accepted R177 destructor. The entire original
three-state R020 frame `0x00656629` and all cleanup registrations are retained.

The 129-byte raster lifetime policy guards storage at +0x14, performs scalar
delete and zeros that slot. It restores the selected GDI object through actual
SelectObject, passes the returned object to DeleteObject, releases the DC through
ReleaseDC, then resets fields +8, +12 and +4. All actual import slots are read
back from the PE directory. The complete R037 deleting parent retains flags-1
allocation cleanup; that parent alone supplies no authored evidence. R109's
entire 119-byte independent raster release policy is preserved as context,
including its own two resets rather than this candidate's three. Original
owner identity, field meanings and complete game layout remain unknown.

Compiler/source observation: seven full natural small-owner controls / 457
bytes distinguish explicit constructor clears and raster cleanup from automatic
construction/cleanup. Source constructors are 142/108 bytes; raster explicit
cleanup is 129 bytes and the implicit raw-member observation has no cleanup
operations. These controls grant no target-source positive or reconstruction
credit. The 142-byte synthetic constructor has vector offset 44 rather than
120. The full 129-byte raster source comparison binds all four genuine fields
without masking and differs at offsets 14,23,44 because its storage offset is
16 rather than 20. No unused field or arbitrary padding is added to hide these
differences. Original layouts are not instantiated.

The third candidate `0x004170B0` / 27 remains unknown. Its entire interface
Release through virtual slot +8 is byte-equal to both a complete explicit
interface destructor and an ordinary smart-owner destructor. Both full primary
AUX extents / 54 bytes compare without fields to exclude. A complete generated
19-byte member-owner destructor supplies additional operation context. These
observations preserve game-versus-library ownership uncertainty; the deleting
parent and Release shape alone do not classify the owner.

All 119 ordinary source sections / 5446 bytes, 28 actual SDK headers and the
whole 48-byte readonly layout are frozen. The verifier retains 133 complete
canonical/body snapshots, 40 protected unknowns, three whole authored anchors
/ 531 bytes, five original compiler/policy records and the original full EH
frame. Previous R177 evidence cold-replays unchanged. New evidence-only cold
replay precedes canonical mutation; accepted-state cold replay, full authored
validation, target/tracking, fresh scanning and local Ghidra attestation pass.
Strict R177 HEAD 09fccb7 readback permits only two function/origin changes and
two full new authored records, preserving all 887 prior rows/order and every
previous configuration. Thirty-four new regression guards and all 2031 public
checks pass; progress/whitespace checks pass. The exact-input preservation
check confirms that the earlier R139 cold 60/60 replay remains applicable.

Totals are 3622 resolved (936 authored, 2111 library, 575 compiler), 729 pending
and 2686 excluded. Authored evidence totals 889 bodies / 1954863 bytes. Exact
remains 60 functions / 9883 bytes with provisional coverage
9883 / 1967206 (0.50%). No reconstructed source/private ABI/mapping/exact credit
is added. Public MCP acceptance remains waived; the full remaining-origin goal
is active and unfinished. Continue with fresh whole resource-operation context.

## R179 — music catalog transformation and readable-file registration

Two complete authored policies / 431 bytes are accepted: `0x00427300` / 298 and
`0x0041D6C0` / 133. Replay
`scripts/repo-python scripts/verify-file-resource-policy-origins.py` with
immutable `config/file-resource-policy-origin-evidence.json`.

Target observation: the first policy opens literal `musicroom.csv`, obtains
its size, allocates byte storage, reads and closes the input. It creates
`musicroom.dat`, transforms each byte with an evolving XOR mask initialized to
0x5C and step 0x5A, adds that step to the mask and increments the step by 0x3D,
then writes and closes the output. Both file-open failure branches, the entire
unsigned loop and final array deletion are retained. The independent whole
R066 game catalog loader / 916 bytes reads its own `musicroom.dat` literal at
`0x00657C80` and uses the same mask/step/increment before parsing game records.
This is game resource policy evidence, rather than ownership inferred from
file APIs or a short XOR shape alone. Names remain inferred.

The second policy checks whether the supplied file can be opened, records its
size, copies its name, closes the handle and appends the full record to the
archive list at owner +4. Complete R169 source evidence establishes value/node
widths 108/116. The record pointer passed from stack -0x78 includes the filename
region, size at record +100 and zero-initialized field at +104; these are copied
data, not inert locals. The full original R053 archive registration / 245 and
R052 archive index reader / 429 provide independent project ownership context.
The list insertion, array allocation/deallocation, strcpy and security-cookie
helper retain their separate accepted library origins. Every real import slot
is verified against the PE directory.

Compiler/source observation: complete natural small-owner methods emit 298 and
130 bytes / 428 total. These are operation controls, not target-byte positives.
The whole 298-byte music source negative binds all eleven genuine code/data
fields and retains 33 differences; equal length does not earn a match. Complete
14-byte CSV/DAT source strings compare independently and their exact fields
bind to the two actual target string locations. The 133-byte registration
extent is never truncated to the 130-byte source control. Its complete source
record includes both metadata fields, with sizeof 108 and list sizeof 12 as
source observations. Original full owner layout, original record spelling and
meaning of the zero-initialized field remain unknown; no padding or incomplete
original owner is introduced.

All 86 ordinary source sections / 4266 bytes, 28 actual SDK headers and the whole
16-byte readonly layout are frozen. Both entire methods retain their own full
primary AUX extent. The verifier preserves 143 complete canonical/body
snapshots, 40 protected unknowns, three whole authored anchors / 1590 bytes with
all original guarded switch records, and four full R169 archive/list records.
The earlier R169 80-control / 3752-byte closed source graph with 189 genuine
fields cold-replays unchanged. Evidence-only cold replay precedes canonical
mutation; accepted-state cold replay, complete authored validation, target/
tracking, fresh scanning and local Ghidra attestation pass. Strict R178 HEAD
9f31228 readback permits exactly two function/origin changes and two complete
new authored records, preserving all 889 prior rows/order and every earlier
configuration. Thirty-seven new regression guards and all 2068 public checks
pass; progress and whitespace checks pass. All exact inputs remain unchanged,
so the earlier R139 cold 60/60 replay across eleven objects remains applicable.

Totals are 3624 resolved (938 authored, 2111 library, 575 compiler), 727 pending
and 2686 excluded. Authored evidence totals 891 whole bodies / 1955294 bytes.
Exact remains 60 functions / 9883 bytes with provisional coverage
9883 / 1967637 (0.50%). No reconstructed source/private ABI/mapping/exact credit
is added. Public MCP acceptance remains waived; the full remaining-origin goal
is active and unfinished. The next bounded cohort investigates two directional
binding copies, explicit queue cleanup and archive construction defaults.

## R180 — directional indexed copies and explicit owner policies

Four entire authored policies / 343 bytes are accepted. Replay
`scripts/repo-python scripts/verify-indexed-owner-policy-origins.py` with
immutable `config/indexed-owner-policy-origin-evidence.json`.

| Address | Complete bytes | Inferred operation |
| --- | ---: | --- |
| `0x00416E20` | 84 | store working eight bytes into the selected nested record |
| `0x00416E80` | 85 | load selected nested eight bytes into working storage |
| `0x004204D0` | 84 | explicitly clear the member queue before automatic destruction |
| `0x0041D190` | 90 | initialize the scalar state and clear the constructed archive list |

Target observation: both copies preserve signed byte selectors at owner
+0x16AC4/+0x16AC5 and the incoming signed byte index. The actual bank/category
strides are 0x17F0/0x5FC, the record stride is sixteen and payload base is +0x55C.
Working storage is +0x16A94. Both call the complete R025 memcpy / 829 with length
eight, in opposite directions. Complete R052 replay initializer / 315 and R040
name-entry update / 541 independently supply game context. Original field
meaning and complete owner layout remain unknown; the provisional binding
shortlist title does not recover an input-binding type.

The queue policy at +0x7D0 first performs an explicit clear and then automatic
member destruction. Both complete 19-byte SDK callees share the same entire
177-byte _Tidy; their historical R077 destructor-shaped aliases are unchanged.
Complete natural clear/destruction controls distinguish two explicit/automatic
calls from one automatic call. The whole R045 fighter release / 588 is preserved.
The archive constructor first constructs the list at +4, explicitly sets the
scalar at +0 to zero and calls the entire R175 list clear / 153. Whole R053
archive registration / 245 and the original one-state EH frames independently
preserve owner context. Constructor dependency ownership is not borrowed.

Compiler/source observation: six complete small-owner controls / 268 bytes
observe copy direction, explicit queue clear and explicit archive defaults,
with full generated alternatives. They grant no target-byte positive. The
queue source owner has no original +0x7D0 layout; source queue value width four
is not an original element-type claim. The synthetic archive constructor is
also 90 bytes, but equal length earns no match. Complete source record/list
widths 108/12 and owner sizeof 16 are source observations, not complete original
owner declarations. No padding, incomplete original owner or target byte source
is introduced.

Four separate construction dependencies remain unknown: `0x0041D8F0` / 56,
`0x0041E330` / 14, `0x0041E2F0` / 53 and `0x0041E1A0` / 143. The last provisional
span ends in an external jump at `0x0041E22D` to `0x0041E264`. Its cold source
section is 223 bytes, including local exception cleanup and the shared tail.
The separate `Catch@0041e22f` ledger span / 80 includes subsequent owner code;
its own extent also needs reconciliation. These are pending context observations,
not accepted prefixes or truncated comparisons.

All 61 ordinary source sections / 2497 bytes, 29 actual SDK headers and the
whole 40-byte readonly layout are frozen. Every explicit source body retains
its own full primary AUX extent; generated alternatives retain their unique
whole defining COMDAT. The verifier preserves 157 full canonical/body snapshots,
40 protected unknowns, four whole authored anchors / 1689 bytes with all original
switch records, three entire R025/R175 library records and two original full
R020 EH frames. The unchanged R025 runtime proof passes all three entire vendor
bodies / 1762 bytes with 93 genuine local fields. New evidence-only cold replay
precedes canonical mutation; accepted-state cold replay, full authored checks,
local Ghidra attestation, target/tracking and fresh scanning pass. Strict R179
HEAD 0f62552 readback permits exactly four function/origin changes and four full
new authored records, preserving all 891 prior rows/order and every earlier
configuration. Thirty-eight new regression guards and all 2106 public checks
pass; progress/whitespace checks pass. All sixty exact inputs remain unchanged,
so the earlier R139 cold 60/60 replay across eleven objects remains applicable.

Totals are 3628 resolved (942 authored, 2111 library, 575 compiler), 723 pending
and 2686 excluded. Authored evidence totals 895 whole bodies / 1955637 bytes.
Exact remains 60 functions / 9883 bytes with provisional coverage
9883 / 1967980 (0.50%). No reconstructed source/private ABI/mapping/exact credit
is added. Public MCP acceptance remains waived; the full remaining-origin goal
is active and unfinished. Next reconcile the whole default-list construction
graph, local exception entry and shared tail before assigning any new ownership.

## R181 — complete list construction and source-owned shared exception entry

Four library entries are accepted through cold
`scripts/repo-python scripts/verify-list-construction-origins.py` and immutable
`config/list-construction-origin-evidence.json`.

| Address | Complete ledger bytes | Inferred source owner |
| --- | ---: | --- |
| `0x0041D8F0` | 56 | default list constructor |
| `0x0041E2F0` | 53 | list value-base constructor |
| `0x0041E1A0` | 223, reconciled from 143 | complete default-node allocation, local catch and shared owner exit |
| `0x0041E22F` | 80 | source-local catch entry including shared owner exit |

The four ledger extents total 412 bytes, including 80 overlapping bytes.
Distinct primary code totals 332 bytes. No distinct-byte or exact-reconstruction
credit is inferred from the overlap. Target observation: the old node prefix
ends with JMP at `0x0041E22D` to the owner exit `0x0041E264`. Its complete defining
source function owns 223 bytes through `0x0041E27E`, with the local entry at
+143 and shared exit at +196. The source-local entry has a unique static typed
COFF definition and is named by the actual complete handler table. Full parent
primary AUX/COMDAT metadata, all 223 bytes, both branches and return reconcile
the owner; the entire 80-byte entry view is supported through that owner. No
standalone callback primary AUX or convenient prefix is claimed.

Compiler/source observation: the pinned SDK list header defines the allocation,
link construction, catch cleanup, deallocation and rethrow policy. The original
R020 frame at `0x00655470` registers owner `0x0041E1A0`; the complete 80-byte
readonly EH carrier starts at `0x006685F8`, with FuncInfo at `0x0066862C` and
try map at `0x00668618`. Its actual catch-all handler table points to
`0x0041E22F`. The generated ten-byte handler has its own unique complete COMDAT
and retains its observed static definition without inventing primary AUX.
Full data/code linkage and every genuine field are replayed without masking.
The library inference belongs to the SDK source-defined catch policy;
compiler exception-entry ABI alone would not establish that ownership.

Independent game observations retain the complete R180 archive constructor
/ 90 and R179 file-record append / 133, all prior rows and switch evidence.
The latter's 108-byte record copy and original R169 node-allocation records
supply width context; source value/node widths 108/116 do not identify original
field names or complete game owner layout. The SDK empty allocator constructor
and distinct ordinary empty-class constructor both emit the same entire
14 bytes at `0x0041E330`; this entry remains unknown. Original eight-/eleven-byte
node-link helpers and five-byte no-op destruction also remain unknown.

Evidence-only cold replay precedes canonical mutation; accepted-state cold
replay matches 22 full SDK/code/EH/data/ordinary controls / 795 bytes and all
35 genuine fields. All 65 ordinary sections / 2690 bytes, 29 SDK headers plus
the pinned prior probe include, and the entire coalesced 52-byte readonly layout
are frozen. The verifier preserves 168 canonical/body snapshots, 41 protected
unknowns, two full authored anchors / 223 bytes, four complete R169 records
and the original R020 frame. The old R180 manifest stays byte-for-byte immutable;
its verifier permits only the three exact original-to-R181 row transitions,
including the sole 143-to-223 extent correction. All old 143-byte observations,
external jump and pending source controls remain replayed as historical context,
without prefix acceptance. R180 cold replay passes before and after acceptance.

Strict R180 HEAD 7ab03b1 readback permits exactly four function/origin changes,
only the complete node size/span correction, and no authored additions. All
895 prior authored rows/order and previous configuration evidence are preserved.
Local target/Ghidra preflight, tracking, full authored verification, fresh scan,
44 new regression guards and all 2150 public checks pass. Generated progress
and whitespace checks pass. All sixty exact inputs remain unchanged, retaining
the prior R139 60/60 cold replay across eleven objects. No source/private ABI,
mapping, reconstructed owner layout or exact credit is added.

Totals are 3632 resolved (942 authored, 2115 library, 575 compiler), 719 pending
and 2690 excluded. Authored evidence remains 895 whole bodies / 1955637 bytes.
Exact remains 60 functions / 9883 bytes, with provisional authored denominator
1967980 (0.50%). Public MCP acceptance remains waived; the whole remaining-origin
goal is active and unfinished. Next investigate the complete shared math-table
operations and indexed counter policy with independent game parents.

## R182 — shared math-table policies and signed indexed word counter

Five complete authored policies / 326 bytes are accepted. Replay
`scripts/repo-python scripts/verify-math-table-policy-origins.py` with immutable
`config/math-table-policy-origin-evidence.json`.

| Address | Complete bytes | Inferred operation |
| --- | ---: | --- |
| `0x0041CAE0` | 82 | build the used 3600-entry cosine table |
| `0x0041CB40` | 43 | absolute converted index modulo 3600 into that table |
| `0x0041CB70` | 49 | same table with the actual 900.0f phase subtraction |
| `0x0041CBB0` | 73 | zero-divisor guard, phase lookup and ratio against the ordinary lookup |
| `0x00454D00` | 79 | increment the selected native word counter using signed bank/index selectors |

Target observation: the build iterates indices 0 through 3599, computes
index / 10.0 * 3.1415926535 / 180.0, calls the actual R128 `_cos` C entry and
stores floats at `0x006884C0` with stride four. The two lookups multiply by
10.0f, retain the distinct phase subtraction, call complete R006 `__ftol2`
and the still-unknown 11-byte integer absolute-value helper, then use remainder
3600. The ratio retains the actual x87 equality/zero branch, one phase call
and two ordinary lookup calls. This shared explicit table policy, whole startup
R113 application parent / 2987 and whole R048 character consumer / 43845
support the authored inference. A CRT callee or game caller alone is not used
as ownership proof. All original parent switch records and complete CFG remain
frozen; selected witnesses preserve the actual call sites.

The counter retains signed byte bank/index loads, native bank stride 0x17F0,
word load/add/store with index stride two and counter base +0x394. Actual whole
R109 resource-selection parent / 215 sets ECX to `0x006718F8` before the call.
Whole R052 replay initialization / 315 and immutable R180 indexed-copy evidence
supply independent context. Original field meanings, word signedness and
complete game owner layout remain provisional. The complete small observer
uses two three-word banks and sizeof 14; its entire increment / 67 and caller
/ 17 are operation controls, not an original owner declaration or a target-byte
match. The target's 79-byte body is never shortened to the source model.

Compiler/source observation: three whole natural table functions / 174 bytes
match byte-for-byte with every actual field. The full 73-byte ratio control is
a negative: six bytes at offsets 48–53 differ because the live float store and
argument-stack cleanup exchange instruction order. Both complete bodies retain
the same explicit operations and CFG. All five ratio fields are compared
unmasked; equal length or semantic behavior earns no exact credit. No padding,
inert local, fake return, assembly, conditional source body or invented ABI is
introduced. Ten whole code/constant controls / 283 bytes freeze all 19 genuine
fields; the three positives are not generalized into a four-function match.

The source table is an external complete array declaration. Its 14400-byte
used range fits the loaded virtual `.data` extent, including zero-filled bytes
beyond file-backed data. The verifier reads PE virtual sizes for this writable,
non-executable range, rather than assuming a file-backed span. This is a used
range claim, not the whole original allocation or a runtime-content hash.
All six complete readonly float/double constants / 36 bytes are independently
verified. The complete R128 cosine primary / 174 and its original nine-byte C
entry record, R006 conversion / 117 and R129 abs diagnostic / 11 stay unchanged.
R129 replays before and after acceptance, including vendor abs/labs and cold
ordinary alternatives that preserve the integer helper's unknown ownership.

All 13 cold ordinary sections / 383 bytes, two actual SDK headers and whole
16-byte readonly layout are frozen. Evidence-only cold replay precedes canonical
mutation; accepted-state cold replay passes. The verifier retains 179 complete
canonical/body snapshots, 41 protected unknowns, four entire authored parents
/ 47362 bytes and four original runtime/interior/opaque records. Strict R181
HEAD bf663e0 readback changes exactly five function/origin rows, preserves
all extents and appends five complete authored records while retaining all
895 prior rows/header/order. Full authored verification now covers 900 bodies
/ 1955963 bytes. Local target/tracking/Ghidra query completion, fresh scanning,
47 new regression guards and all 2197 public checks pass; generated progress
and whitespace checks pass. Every prior configuration manifest/record and all
sixty exact inputs are preserved. No source/private ABI/mapping/exact credit
is added; prior R139 cold 60/60 replay across eleven objects remains applicable.

Totals are 3637 resolved (947 authored, 2115 library, 575 compiler), 714 pending
and 2690 excluded. Exact remains 60 functions / 9883 bytes, with provisional
coverage 9883 / 1968306 (0.50%). Public MCP acceptance remains waived; the whole
remaining-origin goal is active and unfinished. Next investigate the complete
font byte-decoding/classification and graphic-resource initialization cohort.

## R183 — complete font byte policy and explicit resource defaults

Two complete authored policies / 149 bytes are accepted through cold
`scripts/repo-python scripts/verify-font-byte-policy-origins.py` and immutable
`config/font-byte-policy-origin-evidence.json`. The 85-byte entry at
`0x0041C9D0` decodes a packed text unit; the 64-byte entry at `0x0041BF90`
stores the incoming window value and explicitly clears resource state.
The 77-byte fixed-range classifier at `0x0041CA30` remains unknown.

Target observation: the double-byte route performs two DWORD loads, masks
0xFF/0xFF00, shifts and combines the first two bytes, writes a full integer
output and returns two. The fallback sign-extends one byte and returns one.
Complete R052 rasterizer / 1766 uses this result to advance text, distinguish
backslash control sequences, parse game formatting through the existing hex
helper and render either pixel-width path. All three original decoder calls,
backslash comparison and full original parent CFG are frozen. These explicit
operations and independent font/texture/music-room game context support the
outer authored inference; callee ownership is kept separate.

The initializer preserves the incoming value at +0 and zero stores at
+4/+8/+0xC/+0x14. The complete R052 texture parent / 398 allocates 0x38 bytes,
passes zero to the constructor and uses the resulting owner in the original
rasterizer. Full R040 music-room text parent / 555 independently calls the same
initializer. Complete R178 release / 129 and R109 release / 119 preserve the
actual guarded storage delete, GDI selection/deletion and DC release, including
three original PE imports. A 56-byte allocation and partial field interface do
not recover the full original owner or license instantiating it.

Compiler/source observation: the natural char-input decoder emits 74 bytes,
against all 85 original bytes. Its one real classifier-call field is linked
unmasked; 44 positions in the shorter source span differ and the original has
11 additional bytes. Both complete CFGs are checked separately. No target prefix
or memory-read equivalence is claimed: the original DWORD reads remain distinct
from the model's byte loads. The complete small resource owner has five live
fields and sizeof 20. Its 64-byte constructor has one difference at offset 50:
source storage offset 0x10 versus original 0x14. Equal length is not a match;
no arbitrary field/padding is added to remove the difference. Generated default
POD construction is retained as a full 25-byte caller with no explicit field
initialization, independently of the explicit constructor/caller controls.

The full 77-byte member classifier and distinct ordinary member classifier are
byte-equal to the original helper. Both implement the actual unsigned ranges
0x81–0x9F and 0xE0–0xFE; their equality does not distinguish ownership or recover
original class/type/charset identity. A complete 25-byte pinned SDK `_ismbblead`
macro observer retains its genuine DIR32 `_mbctype` table field with addend one.
It is source context only, with no invented original table binding. This
negative SDK shape does not prove the other helper is custom authored. The
classifier's original canonical rows remain unchanged and unknown.

Four complete source comparisons / 292 bytes preserve both whole negatives
and two equal opaque-classifier alternatives. Five complete SDK/implicit/caller
controls / 196 bytes retain their own primary AUX extents. All 14 cold ordinary
code/EH/data sections / 588 bytes, ten actual SDK headers and the entire 24-byte
readonly layout are frozen. The verifier preserves 187 complete canonical/body
snapshots, 42 protected unknowns, five entire authored game/release anchors
/ 2967 bytes, two full R178/R109 release records and two original R020 frames.
R178 cold replay passes before and after acceptance; all earlier manifests stay
immutable. Evidence-only cold replay precedes canonical mutation; accepted-state
cold replay passes. No root target-byte-positive claim is made.

Strict R182 HEAD b2c365e readback changes exactly two function/origin rows and
adds two full authored records, preserving every original extent, all 900 prior
rows/header/order and all earlier configuration evidence. Full authored checks
now cover 902 bodies / 1956112 bytes. Local target/tracking/Ghidra attestation
and both query completion markers, fresh scanning, 46 new regression guards
and all 2243 public checks pass; progress and whitespace checks pass. All sixty
exact inputs are unchanged, retaining the earlier R139 cold 60/60 replay across
eleven objects. No source/private ABI/mapping/exact credit is added.

Totals are 3639 resolved (949 authored, 2115 library, 575 compiler), 712 pending
and 2690 excluded. Exact remains 60 functions / 9883 bytes with provisional
coverage 9883 / 1968455 (0.50%). Public MCP acceptance remains waived; the whole
remaining-origin goal is active and unfinished. A fresh read of the pinned
D3DX8 survey finds 291 pending source-body diagnostic associations. Next review
the bounded fifteen-candidate / 7667-byte cohort whose observed fields have
accepted library, actual import or same-member scalar-constant context. Old
masked survey hits are discovery only and never new acceptance evidence.

## R184 — complete D3DX8 file/image objects and independent real fields

Fifteen complete vendor functions / 7667 bytes are classified library/exclude.
The historical masked SDK survey supplied discovery addresses only. Fresh
extraction from the read-only pinned d3dx8.lib archive independently derives
every complete single-function COMDAT extent, reopens each source member and
compares all original bytes after binding every genuine relocation field.
The archive SHA-256 remains
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`.

| Address | Whole bytes | Vendor operation |
| --- | ---: | --- |
| `0x0061FF67` | 269 | CD3DXStringBuffer::AddString |
| `0x0060BF05` | 272 | CD3DXFile::Open |
| `0x0060C015` | 202 | CD3DXFile::Create |
| `0x0060C0DF` | 65 | CD3DXFile::Close |
| `0x0061FB45` | 110 | CD3DXDwStack::Push |
| `0x0061FC33` | 179 | CD3DXSzStack::Push |
| `0x00618EC7` | 224 | CD3DXCodec_D3DX_A16R16G16B16::Decode |
| `0x006111EA` | 701 | TF_SetupTriangle |
| `0x0060EC42` | 195 | CD3DXImage::Initialize |
| `0x0060ED05` | 1814 | CD3DXImage::LoadDIB |
| `0x0060F41B` | 740 | CD3DXImage::SaveDIB |
| `0x0060F9D1` | 1191 | CD3DXImage::LoadTGA |
| `0x0060FE78` | 646 | CD3DXImage::LoadPPM |
| `0x0063B803` | 993 | D3DX::jpeg_idct_float |
| `0x00629921` | 66 | D3DX::png_create_struct |

All 83 code fields are explicit: 35 REL32 calls to ten independently accepted
complete source records, 20 actual PE IAT fields with exact DLL/name and source
symbol spelling, and 28 complete same-member readonly scalar fields. Nothing
is masked. The shared symbol catalogue forbids inconsistent destinations.
Complete native decoding retains all returns and internal branches, including
the genuine final internal jump, and 24 byte-identical indirect dispatches.
There are no unresolved external jumps, switch transfers or interior inventory
entries in these accepted extents. Indirect callees receive no new credit.

Ten immutable original library records are retained, with every full own source
primary and complete native ledger carrier. `_floor` keeps its original whole
289-byte wrapper/SSE carrier and the independent 64-byte primary plus complete
225-byte SSE owner; no new 64-byte canonical boundary is invented. The actual
`__alloca_probe` alias is freshly proved at the same source section/offset as
the complete 61-byte `__chkstk` primary, with its real untyped external symbol
metadata. The two names are not treated as separate function AUX definitions.
Original new/delete/character-classifier/malloc/helper records, every source
member hash, native carrier hash and prior manifest are frozen.

Replay `scripts/repo-python scripts/verify-sdk-file-image-origins.py`. Its
`--evidence-only` mode passes before acceptance; accepted-state replay reopens
all actual archive members, full bodies, own extents, fields and target CFG.
For a changed retained dependency, `--replay-dependencies` runs the six complete
provenance roots serially. These roots passed in this batch: runtime, runtime
leaves, allocation API, standard exception, floor math and the original SDK
validator. R148 already recursively cold-replays the complete input-format,
floating-point and runtime-cycle graphs; their duplicate second invocation
was stopped after the first complete PASS. A fresh private call-graph readback
records that coverage. No parallel compiler or writable Ghidra session is used.

Strict R183 HEAD a535ae3 readback changes exactly fifteen function/origin rows
and preserves every original extent, all 902 authored records and all previous
configuration/source/ABI/mapping/match inputs. Full authored checks still cover
902 bodies / 1956112 bytes. Target/tracking/project attestation, query completion
marker, fresh scanning, 22 meaningful field/extent/provenance regression checks,
all 2265 public checks, progress and whitespace checks pass. The supplied target
is unchanged. Compiler build/flags for these archived bodies and complete game
class layouts remain unknown. Origin evidence adds no source, ABI, mapping or
exact credit; the prior cold sixty-unit replay remains applicable to unchanged
inputs. Public MCP acceptance remains waived.

Totals are 3654 resolved (949 authored, 2130 library, 575 compiler), 697 pending
and 2705 excluded. Exact remains 60 functions / 9883 bytes, with provisional
coverage 9883 / 1968455 (0.50%). The whole remaining-origin goal is active and
unfinished. The next bounded cohort is six newly anchored D3DX parents/leaves
/ 762 bytes: 0x0060D11A, 0x0060D044, 0x0061FC02, 0x00610F96, 0x0061FE1F and
0x006255A0. Reopen complete source members and bind all seventeen actual calls
through the immutable R184/earlier source bodies; survey hits remain diagnostic.

## R185 — complete D3DX debug parents and typed image/stack/PNG leaves

The bounded six-candidate cohort resolves five complete vendor functions
/ 724 bytes as library/exclude and preserves the sixth candidate as unknown.
Fresh extraction independently derives each entire own code COMDAT from the
same pinned d3dx8.lib. All 16 actual accepted REL32 calls are bound without
masking through six immutable complete source records, including the original
19-byte R026 CD3DXSzStack constructor.

| Address | Whole bytes | Vendor operation |
| --- | ---: | --- |
| `0x0060D11A` | 375 | CD3DXAssembler::UpdateDebugFileLine |
| `0x0060D044` | 214 | CD3DXAssembler::UpdateDebugText |
| `0x0061FC02` | 49 | CD3DXSzStack::~CD3DXSzStack |
| `0x00610F96` | 48 | CD3DXImage::LoadBMP |
| `0x006255A0` | 38 | D3DX::png_create_info_struct |

The two complete assembler operations preserve five/seven genuine calls to the
whole 110-byte R184 CD3DXDwStack::Push body, with their native debug-state and
stack accesses. The full 49-byte string-stack destructor retains its actual
non-null element deletion loop and separate container release, the full vendor
constructor and the unchanged R184 string-stack Push context. The complete
48-byte BMP gate checks the original header size, BM signature and input
length before passing its remainder to the full 1814-byte LoadDIB owner. The
38-byte PNG info allocation operation reaches the complete 66-byte
png_create_struct source body. Names alone and region proximity establish none
of these decisions. Complete source operations, real fields, typed retained
children and all native CFG/exits are frozen.

The full 38-byte `0x0061FE1F` buffer initializer is byte-equal to the whole
CD3DXBuffer::Init vendor COMDAT, including its one actual call to the complete
14-byte operator new owner. It remains unknown: this allocation-and-field-write
body lacks independently confirmed original owning-object/interface context.
The original canonical rows, full native body, own source extent, real field
and complete positive diagnostic comparison are preserved; no prefix, masked
field, inferred complete class or library promotion is introduced.

Replay `scripts/repo-python scripts/verify-sdk-debug-parent-origins.py`. Before
canonical mutation, `--evidence-only` verifies the complete six-candidate
positive/ambiguity result. Accepted-state replay verifies the five new rows
and unchanged pending row. Each invocation reopens the complete immutable R184
archive graph, all 15 bodies and 83 fields, the ten earlier source/native
carriers, and the original SDK validator's 319 bodies / 80421 bytes and typed
short-owner evidence. The six newly retained full own source records total
2028 bytes. Prior source/ABI inputs are unchanged; the already passed R184
cold dependency roots remain applicable without duplicate compiler replays.

Strict R184 HEAD 82be796 readback changes exactly five function/origin rows,
preserving every original extent, all 902 authored records / 1956112 bytes and
all earlier configuration/source/ABI/mapping/match inputs. Target/tracking/
project attestation and query completion, full authored verification, fresh
scanning, eight new meaningful ambiguity/owner/field guards, all 2273 public
checks, progress and whitespace checks pass. No original target or database
write occurs. Source, complete game layouts, ABI, mapping and exact credit
remain independent; exact stays 60 functions / 9883 bytes and provisional
coverage 9883 / 1968455 (0.50%). Public MCP acceptance remains waived.

Totals are 3659 resolved (949 authored, 2135 library, 575 compiler), 692 pending
and 2710 excluded. The whole remaining-origin goal is active and unfinished.
Next investigate the bounded R186 buffer/interface cohort: the unchanged
38-byte initializer and three entire 71-byte QueryInterface candidates at
0x00609F11, 0x0060A1FA and 0x00620093. Their historical masked vendor diagnostic
uses different original GUID addresses; it does not identify the same
interface. Independently prove each complete SDK GUID, retain full negatives
for incompatible interface constants, and reconcile complete owning vtables/
callers/source members before assigning any new owner. Do not infer an IID
from a name, same-shaped COM body or memory region.

## R186 — full SDK GUID identities and D3DX interface-owner context

Four whole candidates / 251 bytes are classified library/exclude. The old
masked CD3DXBuffer QueryInterface survey hid two different interface GUIDs.
The full original values independently identify ID3DXRenderToSurface at
0x0065DDCC, ID3DXRenderToEnvMap at 0x0065DDBC, and ID3DXBuffer at 0x0065DDFC.
Each complete 71-byte query is freshly extracted from its correct original
SDK member, rather than retaining the wrong buffer association.

| Address | Whole bytes | Vendor operation |
| --- | ---: | --- |
| `0x00609F11` | 71 | CD3DXRenderToSurface::QueryInterface |
| `0x0060A1FA` | 71 | CD3DXRenderToEnvMap::QueryInterface |
| `0x00620093` | 71 | CD3DXBuffer::QueryInterface |
| `0x0061FE1F` | 38 | CD3DXBuffer::Init |

The natural probe `probes/VC7D3DXInterfaceGuids.cpp` includes actual initguid
and d3dx8 headers. Cold compilation freezes all 47 ordinary readonly GUID
sections / 752 bytes and all 84 actual included headers. The three entire
interface GUID COMDATs / 48 bytes agree with their complete original readonly
values. IUnknown at 0x00660E58 is independently proved by the entire 16-byte
readonly definition in Uuid.Lib member obj\i386\unknwn_i.obj, offset 328782.
The UUID archive SHA-256 is
`91e2caa3832f1574ee317ca53fe3db8b389856d2da5e138a20805ac1399b4bab`.
Compiler settings describe the GUID observation only, not an original
executable-wide build profile or a reconstructed game layout.

All three owning source/native pointer carriers are retained in full: 36 bytes
at 0x0065D39C, 52 bytes at 0x0065D3C0 and 28 bytes at 0x0065DE1C, totaling
116 bytes / 29 genuine slots. Source pointer definitions, every real field and
every original pointer value are frozen. Thirty-three entire source functions
/ 2693 bytes are compared without masking, with all 25 real code fields bound
through a coherent complete source catalogue, actual GUIDs and complete own
vtables. All native branches/exits and 73 unchanged indirect dispatches remain
explicit. The buffer's genuine weak `_E` deleting-pointer reference is verified
from its real COFF AUX/search/fallback metadata and complete same-member `_G`
primary; no fictitious standalone weak function extent is introduced.

The original full GetDesc/scene/lost-device/Cube/Sphere/Hemisphere/Parabolic
SDK owners and their complete typed records provide independent library peer
context. The full buffer callback/destructor/init graph closes through the
actual seven-slot buffer vtable, its real QueryInterface GUID and full earlier
new/delete owners. This supplies the previously missing owning context for the
whole 38-byte initializer. No full original object layout or private ABI is
declared or instantiated. Non-inventory callback controls receive no new
canonical rows or origin credit. Existing compiler deleting wrappers retain
their original compiler classification.

The entire 35-byte EnvMap Face and 227-byte EnvMap End source/native controls
are read and frozen, including their real unsolved fields and full native CFG.
Their downstream EndScene/filter linkage is unresolved: no positive body/linkage
claim is made, no field is masked and no owner is accepted from those controls.
The full 52-byte owning carrier still retains both slots, rather than dropping
them to compare a convenient prefix. Independently established EnvMap query/
GUID and the complete existing library peers support only the bounded query
decision. All other original anchor rows stay unchanged.

Two entire wrong-buffer QueryInterface comparisons / 142 bytes remain negative:
each has its actual interface pointer difference at code byte 35, plus the
complete sixteen-byte GUID difference. A source IID_ID3DXBuffer field is never
relabelled as another interface merely because solved native fields fit.
Replay `scripts/repo-python scripts/verify-sdk-interface-origins.py`; its
`--evidence-only` cold replay passes before mutation, and accepted-state cold
replay passes. It reopens the complete original R185/R184/SDK graphs serially,
with unchanged already-passed cold dependency inputs. R185's manifest remains
immutable. Its validator permits only the exact new buffer transition, guarded
by frozen whole original/accepted record digest
`84329381c12dbf07a0af4e12a907fba7eb7b03253e21439873e6cf2c3f8b5658`.
R186 also pins the updated R185 validator. All former pending-byte comparisons
and original extent/source facts remain checked.

Strict R185 HEAD 5d6dbb6 readback changes exactly four function/origin rows and
preserves every original extent, all 902 authored records / 1956112 bytes and
all previous configuration manifests. All sixty source/header/build/match
inputs remain unchanged from the prior cold exact replay. Target/tracking/
project/query attestations, full authored replay, fresh scanning, fourteen new
meaningful GUID/table/opaque-field/transition guards, all 2287 public checks,
progress and whitespace checks pass. No target or database write occurs.
No source, ABI, mapping or exact credit is added. Public MCP acceptance is waived.

Totals are 3663 resolved (949 authored, 2139 library, 575 compiler), 688 pending
and 2714 excluded. Exact stays 60 functions / 9883 bytes and provisional
coverage 9883 / 1968455 (0.50%). The whole remaining-origin goal remains active
and unfinished. Next review the three complete source-owner destructors
/ 89 bytes already read as original context: 0x0061FE0A / 21, 0x00609EEF / 34,
and 0x0060A7D2 / 34. Retain the entire R186 GUID/table/callback graph and all
original R038 generated wrapper facts. Apply only an explicitly frozen narrow
anchor transition if new independent destructor evidence is accepted; do not
rewrite the R186 manifest or promote the two opaque EnvMap controls.


## R187 — explicit SDK destructor policy and generated wrapper ownership

Three complete D3DX8 source-owner destructors / 89 bytes are classified
library/exclude, independently of the existing compiler deleting wrappers.

| Address | Whole bytes | Vendor operation |
| --- | ---: | --- |
| `0x0061FE0A` | 21 | CD3DXBuffer::~CD3DXBuffer |
| `0x00609EEF` | 34 | CD3DXRenderToSurface::~CD3DXRenderToSurface |
| `0x0060A7D2` | 34 | CD3DXRenderToEnvMap::~CD3DXRenderToEnvMap |

All three original SDK COMDAT extents, source/native hashes, six actual fields
and complete branches/exits are reopened. Each real vtable write binds its
entire R186 owning pointer carrier and independently proved interface GUID.
The buffer releases its storage through the complete earlier delete owner.
The two render destructors call their distinct complete OnLostDevice owners,
then release the COM member through slot +8 and clear that member. The
same-shaped render source bodies do not merge their distinct source symbols,
vtable definitions or cleanup targets. All fields remain unmasked.

The natural `probes/VC7SDKReleasePolicies.cpp` uses complete observer classes
and real public SDK interfaces, with no incomplete original owner instance.
Cold VC7.1 compilation with `/Od /Ob0 /Gy /GR- /GX /Zi /GS /showIncludes`
retains eight entire ordinary sections / 205 bytes, seven full code controls
/ 193 bytes, 84 actual SDK/CRT headers and the whole twelve-byte observer
layout [4, 4, 4]. Default raw-pointer lifetime end emits no cleanup call.
Explicit Surface/EnvMap observer policies reach the actual public cleanup
slots +28/+44. Their natural generated deleting wrappers are complete
44-byte bodies, including the real destructor and delete fields; they are not
truncated to the original 28-byte wrapper shape. These controls establish the
explicit/default/generated distinction, with no false target-positive claim,
invented original ABI, object layout or reconstructed source presence.

The three original R038 deleting-wrapper records and canonical compiler rows
remain unchanged. All 53 R038 wrappers / 1484 bytes cold-replay successfully.
The entire R186 interface/GUID/owner graph and R185/R184/SDK dependencies also
replay serially. R186's manifest remains immutable; its validator permits only
the three complete hash-pinned original-to-R187 accepted transitions, with
record digests checked against the actual new manifest. The two opaque EnvMap
controls cannot use that transition. Replay
`scripts/repo-python scripts/verify-sdk-destructor-origins.py`.
Manifest SHA-256:
`506e7fac5ff1cc392d381c1e16373fc15f9d0285158793ddfff0d5658262ccd1`.
Both evidence-only cold replay before mutation and accepted-state cold replay
pass. Strict R186 HEAD 0151132 readback changes exactly three function/origin
rows, preserving every original extent, all 902 authored records / 1956112
bytes and every earlier configuration manifest. All sixty exact inputs remain
unchanged from the prior cold replay. Fourteen meaningful source-policy,
interface-field, wrapper and anchor-transition guards bring public checks to
2301. Target/tracking/project/query markers, complete authored verification,
fresh scanning, progress and whitespace checks pass. No target/database write
or new source/ABI/mapping/exact credit occurs. Public MCP acceptance is waived.

Totals are 3666 resolved (949 authored, 2142 library, 575 compiler), 685 pending
and 2717 excluded. Exact stays 60 functions / 9883 bytes and provisional
coverage 9883 / 1968455 (0.50%). The whole origin goal remains active and
unfinished. The next bounded R188 cohort is the full six-byte public
D3DXVec3Normalize dispatcher at 0x0061AF34 and 328-byte D3DXMatrixLookAtRH
at 0x0061CA33. Their actual linkage was freshly reached through the complete
pending EnvMap End/EndScene/Render/Setup graph. Prove the complete runtime
dispatch carrier, its real nonzero +28 field and implementation/initializer
context before accepting either function. Do not treat a relocated pointer
as an independent symbol identity or promote the still-unresolved texture/
lock/codec graph. This discovery does not change any additional canonical row.


## R188 — complete x86 SDK pointer policies, lookup data and registry imports

The planned public Normalize/matrix cohort exposed unresolved CPU selection,
shared source entries and guarded projection tables. Both original public
rows remain unknown. This bounded dependency batch instead accepts three
entire explicit SDK policies / 354 bytes, with no convenient parent promotion.

| Address | Whole bytes | Vendor operation |
| --- | ---: | --- |
| `0x006292BC` | 60 | x86_D3DXInitFastTable |
| `0x006209EF` | 92 | GetD3DRegValue |
| `0x00629081` | 202 | x86_D3DXVec3Normalize |

Ten full own COMDAT source/native comparisons / 1268 bytes bind all fourteen
genuine fields. The initializer writes eight real function pointers, each
bound to its separately complete original x86 implementation. The full 227-
and 142-byte matrix implementations retain their R008 library records; five
other vector implementations remain non-inventory controls. No new canonical
rows are created for them. The complete pointer-writing policy is explicit SDK
selection code, rather than a generated lifetime/template operation.

The normalizer retains its entire x87 zero/unit/lookup/scale paths, all branch
targets and final RET 8. Its indexed data reads use the actual source symbol
_invSqrtTab at 0x0066D2A0 with distinct source addends 0 and +4. The whole
initialized source data section is 4104 bytes, including _invSqrtTab and the
neighboring _a1/_a2 definitions at offsets 4096/4100. All original bytes,
definitions and source permissions agree. This source section is writable:
the observation compares the original file image and does not assert runtime
immutability. The index mask 0xFF8 bounds the paired reads within the first
4096 bytes; the remaining source definitions are still retained and compared.
The public D3DXVec3Normalize dispatcher at 0x0061AF34 is a separate unknown
candidate; this accepted implementation does not grant its wrapper credit.

The registry helper's whole 28-byte readonly source definition is
Software\Microsoft\Direct3D at 0x0065DE70. All three real IAT fields independently
resolve through the actual PE import directory to ADVAPI32 RegOpenKeyA,
RegQueryValueExA and RegCloseKey, with their genuine decorated source symbols.
The complete helper preserves success/error exits and handle cleanup. These
full SDK registry and lookup/implementation source owners establish library
policy independently of auto-analysis names, nearby code or masked similarity.

The entire 460-byte writable original D3DX source pointer carrier / 112 fields
is retained as observed context. Every source definition, source field, actual
pointer and intervening byte remains present. Unrelated pointers receive no
false independently proved linkage claim. The whole 221-byte CPU selector
and public Normalize 6-/LookAtRH 328-byte original/source snapshots likewise
remain unresolved context with their real fields, hashes and unknown rows.
Private discovery identifies unresolved Intel exception/filter paths, local
projection tables and SIMD source aliases/assembly tails. No dynamic CPU
selection or unrelated implementation is inferred from the initial carrier.

Replay `scripts/repo-python scripts/verify-sdk-x86-policy-origins.py`. Its
manifest SHA-256 is
`dfba474686f4032271ad6ba4f2f9fde62ed221590e40c13f354bf7086e2872f1`.
Evidence-only replay before mutation and accepted-state replay pass. Every
source body is freshly extracted from the pinned original archive, with all
fields included; this archive-only origin batch adds no reconstructed source
or exact compilation credit. Strict R187 HEAD 53cd473 readback changes exactly
three function/origin rows and preserves every other extent, all 902 authored
records / 1956112 bytes and every earlier configuration manifest. Source,
headers, flags, ABI, mapping and all sixty exact inputs remain unchanged from
the prior cold replay. Target/tracking/project/query markers, full authored
verification, fresh scanning, twelve meaningful whole-data/addend/import/
pointer/scope guards, all 2313 public checks, progress and whitespace pass.
Public MCP acceptance remains waived. No target/database write occurs.

Totals are 3669 resolved (949 authored, 2145 library, 575 compiler), 682 pending
and 2720 excluded. Exact stays 60 functions / 9883 bytes and provisional
coverage 9883 / 1968455 (0.50%). The whole origin goal remains active and
unfinished. Next review the bounded R189 SSE/SSE2 initializer pair at
0x00628900 / 262 and 0x00628A10 / 266. Each complete source COMDAT carrier is
272 bytes, retaining its actual post-RET LEA alignment. Independently reconcile
the reachable function extent and that alignment; compare the full carriers,
every pointer and each whole source callback including any genuine local $$1
entry/shared body. Do not cut a source section to fit the provisional native
extent or treat its padding as executable function credit.
