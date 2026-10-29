# F620 — original native 44-x86 action0x5F in giant `005AEEC0` and the unresolved predecessor register cycle

**Pinned Japanese TH075 1.11 real original PE, selected ordinary VC7.1
whole-parent C++ compilation. Entire huge original function remains
NONEXACT, and no fragment becomes independently accepted CODE.**
Original executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Original PE: three separate full case boundaries, not guesswork

The original fighter `005AEEC0` owns three genuine adjacent indexed
handlers in its *second* packed native switch:

| Original action | Actual physical dense slot | Genuine complete case native extent | Original typed PE/call fields |
| --- | ---: | ---: | ---: |
| `0x5D` | 19 | **210 bytes /64 complete x86** | 3 actual native `REL32` calls |
| `0x5E` | 20 | **210 bytes /64 complete x86** | 3 actual native `REL32` calls |
| `0x5F` | 21 | **144 bytes /44 complete x86** | 3 actual native `REL32` calls |
| Original subsequent `0x60` | 22 | Next true native boundary, not part of 0x5F | Separately owned |

The original `0x5D/0x5E` air-transition sources set live `+0x50`
to **+11.0f** or **−11.0f** on actual stage 2/frame 0, call native
frame query `0040FA30`, conditionally set original states 0/1 via
`0040FAC0`, update direction byte from independent original
`+0x44`/owner `+0x2E8` x87 comparisons, and clear position when
stage 14/frame 0. These cases have an original *64-instruction*
grammar, NOT the other fighters' 101-instruction F617 template.
A natural C++ source
[`FighterSimpleAirTransitionF619.inc`](../probes/FighterSimpleAirTransitionF619.inc)
reproduces each **210-byte/64-x86 physical instruction geometry and
all 3 true native PE call targets**, but **42 GPR/CFG operand roles
remain nonexact in each case**. This is intentionally a diagnostic
candidate, not a claimed source-perfect original action.

Original `0x5F` instead consists of a native frame check
`0040FA30` against signed-short `+0x70`, transitions to states
**0 then 1** depending on the real `+0x4E0` counter, and two
independent x87 float-facing checks from real member `+0x44`
against the target owner's `+0x44`. Native comparison results use
the real `TEST AH,0x41` and `TEST AH,5` branches, with the first
`JNE` targeting the **second** comparison, not bypassing both.
Tracked C++
[`FighterFacing5FF620.inc`](../probes/FighterFacing5FF620.inc)
uses genuine ordinary C++ independent `if` statements and
`*(&F32(0x44))` lvalue to recover this real ordering.

## Why enclosing C++ source matters even for a 44-instruction case

The selected original-backed
[`verify-fighter-facing5f-f620.py`](../scripts/verify-fighter-facing5f-f620.py)
cold-compiles **one affected giant fighter `Advance()` source
translation unit**, not a tiny isolated 44-instruction function.
It retains and reruns actual strict native PE/COFF verification of
all **30 earlier F598–F614 game source cases**, plus the complete
original separately owned after-RET physical packed jump DATA.

- **Positive context:** Keep the currently unfinished original
  `0x5D/0x5E` as explicitly diagnostic switch placeholders, insert
  real `0x5F` C++ into the whole giant, and compare actual original
  native 0x5F/0x60 bounds. The resulting normal VC7.1 C++ 0x5F
  subrange matches **44/44 true original GPR/x87/CFG instruction
  roles, all 144 normal CODE bytes of physical case geometry and
  3 genuinely typed, zero-addend `REL32` source fields**, against
  actual original targets `0040FA30` and `0040FAC0` (twice).
- **Independent negative context:** Substitute the normal C++
  64-instruction native-shaped F619 source for both real `0x5D`
  and `0x5E` preceding this SAME `0x5F` source, again fresh-compile
  one whole-giant TU and recheck all prior 30 cases. All three
  subranges still have their correct 64/64/44 original x86 count,
  original 210/210/144 byte widths and all three physical COFF
  fields each, but **original GPR/CFG mismatches are 42/42/26**.
  The source-register cycle has shifted even for the initially
  role-matching 0x5F, with no change in that 0x5F source expression.

This establishes a genuine *whole-function VC7.1 register
allocation dependency* on predecessor-case source context. The
positive 0x5F is a useful strict original compiler grammar proof,
but **the three real cases are NOT simultaneously source-exact**;
there is no license to credit or mask the 42/42/26 mismatch as
relocation bytes. For other original fighters, the same 0x5F
source usually exhibits **26 GPR-role differences**, and original
`0058AF60` has an entirely different **86-x86** 0x5F action. These
were independently explored in ignored negative compiler probes,
not silently extrapolated as matching this 44-x86 source.

**F620 adds exactly ONE strict source-backed original inner case
/44 x86 roles/144 original inner CODE bytes/3 real typed PE/COFF
fields** under the stated positive context, not ten other
0x5F cases. F598–F617 previous strict case count was 336/
86,902 internal native CODE bytes; the bounded study now has
**337 strict internal case subranges/87,046 original internal CODE
bytes**, but these are NOT 337 independently accepted complete
functions. The giant `005AEEC0` still has unresolved native
0x5D/0x5E/0x5F simultaneous codegen and its *whole* 60+KB
original CODE is NONEXACT. Official 943 completed authored
whole-function sources/862,726 native CODE bytes are unchanged.

No full all-unit cold replay, unverified vtable/source promotion,
machine-byte graft, native target executable modification or remote
Oracle exact acceptance occurred.

## Run one positive and one genuine negative C++ source compilation

```bash
scripts/repo-python scripts/verify-fighter-facing5f-f620.py
scripts/repo-python scripts/verify-fighter-facing5f-f620.py --negative-context
scripts/repo-python scripts/validate-tracking.py --require-target
```

The actual pinned original native PE cases, compiler objects/PDBs,
complete source, typed COFF fields and strict GPR negative receipts
are retained under ignored `.analysis/f620-fighter-facing-source/`.
Earlier 64-x86 and 44-x86 original compiler experiments are under
`.analysis/f619-small-air/` and `.analysis/f620-facing/`.
