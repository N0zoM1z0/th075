# F946 — Real adjacent AI signed-short state fields, 8 complete exact functions retained

The original SHA-pinned Japanese TH075 v1.11 native PE
independently proves real AI receiver signed **16-bit**
fields at **+0x512, +0x514 and +0x516**. This is
not an inference from a previous historical C++ sketch:

- Original AI `00472890` (8,871 native CODE B) reads
  +0x512 as a 16-bit word at 004728DF, stores the
  word at 004728ED, and uses the adjacent +0x514
  word at 00472911/00472929. Its full native
  function includes 11 actual +0x512 and
  28 actual +0x514 x86 field accesses.
- Original independent card AI `00474B40` (7,780 B)
  contains the same +0x512 and +0x514 word fields
  and an additional signed short +0x516 card/countdown
  field (original 00474BC9 signed MOVSX and 00474BE3
  16-bit store). The complete native function has
  16 actual +0x516 field accesses.
- The byte-valued command at +0x511 from F940 is
  immediately adjacent to, but distinct from,
  the signed-short +0x512 field. A fabricated
  naturally aligned `byte;short` complete class
  would insert a non-original padding byte. It
  is **not** modeled as such.

The [FighterAIShortFieldsF946.hpp](../src/FighterAIShortFieldsF946.hpp)
defines only a **borrowed 6-byte window** based on the
actual receiver+0x512. The three genuine signed
short fields have internal offsets 0,2,4 and
pinned-compiler compile-time sizeof/offsetof
checks. This incomplete tail view is NOT
instantiated, embedded or treated as a full
original actor/AI object. The live code in
`CharacterAIPolicy.cpp` (six independent
complete 8,871-B functions) uses the actual
first two fields, and `CharacterAICardPolicy.cpp`
(two independent 7,780-B functions) uses all
three in the original normal action policy.

The source edits replace only the corresponding
raw short offset casts with real typed member
accesses. The original action decisions,
per-actor value policy, random number use,
native callback/argument ABI, branching, and
previous F940 command byte remain unchanged.
No manual assembly, forced EBP allocation,
unrealistic padding or target byte grafts.

## Exact canonical affected-unit verification

After two independent native whole-function pilot
cold replays passed, all **eight** affected
full original callable functions were cold-built
under their per-unit real VC7.1 compiler options
from the two changed translation units.
The canonical checker revalidated all actual
whole-function native CODE ranges and PE/COFF
relocation symbol names/types/targets/addends:

| Entire original function cohort | Functions | Original CODE B |
| --- | ---: | ---: |
| 6 distinct normal fighter AIs | 6 | 53,226 |
| 2 distinct card fighter AIs | 2 | 15,560 |
| **Total affected original accepted source** | **8/8** | **68,786** |

Receipt:

    Cold replay: 8/8 exact units across 2 objects

Reproduce only these two source files' accepted units:

    scripts/repo-python scripts/replay-exact-units.py \
      --unit character-ai-00472890 \
      --unit character-ai-004e7de0 \
      --unit character-ai-00579650 \
      --unit character-ai-0059d240 \
      --unit character-ai-005c5d10 \
      --unit character-ai-005e7370 \
      --unit character-ai-00474b40 \
      --unit character-ai-005e9620

The private compiler/native PE receipt and source
control build logs are under ignored
`.analysis/f946-ai-short-window/`.

**All 68,786 original game CODE bytes were already
accepted exact before this type restoration.
No new complete original function has been
claimed and no full 979-unit cold replay was run.**
