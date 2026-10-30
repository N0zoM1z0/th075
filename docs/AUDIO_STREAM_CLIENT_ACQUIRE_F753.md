# F753 — complete original audio client lifecycle cold-exact, with independent EH proof

**New complete original authored game-function CODE: 161 native bytes, 42 x86
instructions, 18 original physically typed PE/COFF fields.** Pinned target:
user-supplied Japanese TH075 v1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original function `004071C0..00407261` was **independently reviewed
R015-authored** before F753 source reconstruction. The historical
`AudioStream::AcquireClient` label is provisional; the native function's
complete `thiscall` shape is constructor-like, including an actual STL
member constructor and exception unwind state.

## Real native C++ behavior and precise ABI

The entire normal C++ [`AudioStreamAcquireF753.cpp`](../src/AudioStreamAcquireF753.cpp)
models a **real 16-byte VC7.1 vector subobject at `this+0`**, whose
member layout is directly witnessed in the pinned original STL
initializer and cleanup at `00409350/00409380`: used vector fields
`+4`, `+8`, `+0xC`. Its constructor naturally invokes the actual
`00409350` vector constructor and generates the native MSVC EH
state-zero and cleanup lifetime. It is not a pointer-only object
masquerading as a complete historical audio class; the remaining
private audio owner layout is unknown.

The authored function then implements the actual shared-audio policy:

1. If the real shared client count **`[00671388] == 0`**, initialize
   the shared audio collection through `00409740`, using the
   original borrowed global owner **`006713A0`**.
2. If the worker handle **`[00671398]`** is null, call actual Win32
   **`CreateThread`** through the real import pointer **`[0065713C]`**,
   passing the original native callback **`00407EF0`**, thread-id
   address **`0067139C`**, and original zero parameters. Store the
   returned handle into `00671398` and call imported
   **`SetThreadPriority(handle,15)`** through **`[00657140]`**.
3. Regardless of client count, call actual vector `Clear` at
   **`00409490`** on the same embedded vector member and increment
   the original shared client count at **`00671388`**. Restore the
   actual `FS:[0]` exception chain and return `this`.

These are actual game policies, not generic compiler-generated
library functions. The native callback, imported Windows API
functions, and STL implementations themselves remain their own
code; **no callee CODE is re-credited**. The original native complete
return and saved receiver at `EBP−0x10` are reproduced naturally
with pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi`.

## Native whole CODE and every original typed field

Under one fresh compiler object the entire function is **161/161
original CODE B, 42/42 ordered native x86 and 89/89 native
nonrelocation bytes**, with all **18** authentic physical fields:

| Original CODE field(s) | Actual native PE target / role | Kind |
| --- | --- | --- |
| `+0x06` | EH handler **`00654DE8`** | DIR32 |
| `+0x0C/+0x14/+0x99` | Native FS exception list pointer slot | DIR32 |
| `+0x20` | Vector constructor `00409350` | REL32 |
| `+0x2D/+0x7C/+0x85` | Shared client count `00671388` | DIR32 |
| `+0x35` | Shared collection owner `006713A0` | DIR32 |
| `+0x3A` | Shared collection initialize `00409740` | REL32 |
| `+0x40/+0x60/+0x67` | Thread handle `00671398` | DIR32 |
| `+0x48` | Thread ID storage `0067139C` | DIR32 |
| `+0x51` | Worker entry `00407EF0` | DIR32 |
| `+0x5B` | Win32 imported CreateThread `[0065713C]` | DIR32 |
| `+0x6E` | Win32 imported SetThreadPriority `[00657140]` | DIR32 |
| `+0x76` | Vector clear `00409490` | REL32 |

Every field has the **original native instruction location,
zero COFF addend, type, decorated compiler source symbol and real
PE destination** in the canonical complete-function comparison.
Neither truncated CODE nor a nonfield-only structural comparison
qualifies; this function passed canonical cold matching.

## Independent real exception carrier proof

The new object also produces a real **18-byte `.text$x` cleanup/
handler stub** starting at **`00654DE0`** in the original PE,
whose handler entry is `00654DE8`. Its **6/6 nonrelocation bytes**
match the original, with original `REL32` vector destructor
`00409380`, a local `DIR32` pointer to **`00667CAC`** and the
native `REL32` `___CxxFrameHandler` at **`006407B8`**.

The associated true **36-byte `.xdata$x` unwind table** begins
at original **`00667CA4`**; its **28/28 native nonrelocation
bytes** and two actual `DIR32` links to the cleanup stub
`00654DE0` and table base `00667CA4` also match the freshly
cold-built source object. All **five EH carrier relocations**
have correct native targets and types. This independently supports
the same MSVC exception lifetime; **the stub and unwind DATA
are not counted again as authored callable game CODE**.

## Targeted canonical acceptance and accounting

Only this new native entire-function source unit was cold-built:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit audio-stream-client-acquire-004071c0
# Cold replay: 1/1 exact units across 1 object.
```

The approved `config/match-units.toml` unit records complete native
`004071C0` length 161, all 18 actual relocations, source, decorated
symbol and the verified `/GX` build profile. The original R015
authorship classification remains unchanged; no previously accepted
967-unit replay or origin-unknown promotion was performed.

**Official F753 authored ledger: 968 exact complete source-present
game functions /968 canonical units, 864,380 original CODE bytes,
43.79% reviewed authored coverage and 43.72% conservative**
including 3,420 origin-pending native bytes. The 22 entire giant
functions plus WinMain/Scene/Archive complete owners remain NONEXACT;
the 98% objective is still incomplete. Original private class names
and layout beyond the demonstrated vector remain provisional.
