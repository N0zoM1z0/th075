# F940 — Native +0x511 command byte shared by AI and priority input, nine whole units exact

Original SHA-pinned Japanese TH075 v1.11 PE has an
independently observed **one-byte command/status field at
fighter input receiver+0x511**. This is not an inference
from the earlier source macros alone. Original whole
x86 directly writes its byte at, for example:

- **00472890** fighter AI policy: native
  004729EC `MOV BYTE PTR [ECX+511h],AL`
  and **70 original byte accesses** within that
  one 8,871-B complete callable AI function.
- **00474B40** independent card AI policy:
  original 00474CC3 byte write, with **67
  original byte accesses** inside its 7,780-B whole function.
- **00532520** input priority resolver:
  native 0053252A first clears byte+0x511 and
  **28 original byte writes** select the real
  priority command codes among 27 pattern checks.
- **004724B0** separate input polling:
  native 004724BA clears the same byte and
  26 original writes target the same offset.

The [borrowed one-byte view](../src/FighterCommandByteF940.hpp)
contains ONLY the independently observed unsigned
8-bit command field and a strict size/offset check.
It is accessed at the *actual* receiver+0x511,
not instantiated or embedded as a fabricated full
0x512-byte fighter/input class. All unknown
fields at earlier offsets remain unknown.

The full original source in CharacterAIPolicy.cpp
(six independent 8,871-byte AI callers),
CharacterAICardPolicy.cpp (two independent
7,780-byte AI callers) and
CharacterInputPriorityF370.cpp (one 1,060-byte
priority resolver) now use the **same actual
borrowed typed field** for that command slot
rather than three unrelated raw offset expressions.
This does not modify their chooser priorities,
random selection, fighter behavior, pattern strings,
return values or original calling conventions.

## Critical strict-relocation negative: polling must stay untouched

An initial four-function pilot replay showed that the
separate native `004724B0` polling source **fails
canonical exact despite 982/982 structural bytes
and all nonrelocation instruction bytes matching**.
The reason was ORIGINAL COFF symbol identity:
the 25 real native `$SG370`, `$SG375`, ...
pattern string references were renumbered
to `$SG390`, `$SG395`, ... after including
the extra borrowed type. A separate ordinary
one-line inline C++ type declaration also changed
`$SG370` to `$SG378`. These are genuine
source relocation-identity mismatches even though
the executable opcode and instruction widths are unchanged.

**Therefore the touched CharacterInputPollingFamily.cpp
edit was reverted before commit.** This protects all
eight previously exact independent polling functions.
Do not fake fixed string labels, rewrite source to
force arbitrary debug/compiler source line numbers,
ignore original PE relocation types, or claim 982-B
structural equality as full matching acceptance.

## Strict targeted cold replay: 9/9 whole original units

Only the remaining **three actually modified translation
units** were freshly compiled with their individual
pinned native VC7.1 profiles, and the canonical checker
reverified every one of their original callable CODE
ranges and all actual manifest PE/COFF references:

| Original complete accepted type | Functions | Original callable CODE |
| --- | ---: | ---: |
| Six independent normal fighter AI strategies | 6 | 53,226 B |
| Two independent card AI strategies | 2 | 15,560 B |
| Input priority controller | 1 | 1,060 B |
| **Total exact original functions affected** | **9/9** | **69,846 B** |

Actual cold replay result:

    Cold replay: 9/9 exact units across 3 objects

The full command and receipt are retained under local,
ignored `.analysis/f940-command-slot/strict-nine-cold.log`.
The failed original polling test and all five comparative
complete compiler source/OBJ/COFF variants are retained
under `.analysis/f940-command-slot/`, preserving the
negative rather than silently discarding it.

**All 69,846 bytes were accepted original whole CODE
before this source-semantic improvement. No newly
accepted whole game function or CODE byte, and NO
979-unit cold replay.**
