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
