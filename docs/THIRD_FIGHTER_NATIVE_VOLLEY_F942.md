# F942 — Real 004AC040 0x60/0x61 native resource volleys: 1,106B, 316 x86, 20 PE targets

Original SHA-pinned Japanese TH075 v1.11 authored
**004AC040** giant: **82,796 complete callable CODE
B/22,721 x86** and **1,126 separately owned afterRET
DATA B**. The source currently has only a
**partially reconstructed** whole natural C++ parent.
Do not treat inner cases as independently callable
exact original game functions.

The original physical case boundaries are:

| Real original handler | Physical original PE interval | Original native |
| --- | --- | --- |
| 0x60 | **004AE390..004AE5B9** | **553 B/158 x86/10 PE fields** |
| 0x61 | **004AE5B9..004AE7E2** | **553 B/158 x86/10 PE fields** |
| **Both genuine consecutive cases** | | **1,106 B/316 x86/20 PE fields** |

The previously tracked F941 whole partial father had
**15-byte/2-instruction markers** at both physical actions.
The older F748 source from the **different**
original 00543210 58KB actor was an insufficient
historical assumption:

- Its 0x60 used `stage==3`, emitting only
  **541 B/154 x86** instead of actual 004AC040
  **553 B/158 x86**.
- Its 0x61 used `stage>3 && stage<5`, wrong
  true stage boundaries, auxiliary action 5,
  and stage2 initialization.
- The **actual original 004AC040 PE** independently
  proves both actions use signed short
  **stage>2 && stage<6** (native two CMP instructions
  at original local x86 ordinals 86/90, immediates
  2 and 6); both push **aux action6** at ordinal 110;
  both have stage**3** initialization at ordinal 134.
- Both original actions have the genuine ten-shot
  loop, real actor motion/facing and resource
  availability checks, contact/floor branch,
  original native action getter/setter,
  and signed-short F00/F02 velocity projection
  using physical original float **006590B8** twice.

The new ordinary C++ is tracked at
[`probes/FighterThirdBossVolley6061F942.inc`](../probes/FighterThirdBossVolley6061F942.inc).
It keeps the actual sprite/side, original conditional
C++ and true game calls, but changes the actor-specific
stage tests and auxiliary literal to original-PE-derived
values. It does NOT insert register directives, dummy
locals, original machine byte arrays or a fabricated
complete fighter layout.

The reproducible
[`scripts/verify-third-fighter-volley-f942.py`](../scripts/verify-third-fighter-volley-f942.py)
fresh-compiles **three complete original-shaped
partial 82KB giant parents** under pinned VC7.1:
previous F941 markers, the original F748 58KB
actor's uncorrected values, and actual original
F942 004AC040 stage-specific values.
It independently decodes the pinned original PE,
physical afterRET case labels and original x86,
validates every true **20 typed zero-addend
PE-targeted `REL32`/`DIR32` field**, and
rechecks all preceding natural real actions
0x58,0x59,0x5D,0x5E,0x5F on the same new
whole-parent source.

| Whole *partial* original-shaped source | F941 two markers | Wrong old F748 source | Correct F942 source |
| --- | ---: | ---: | ---: |
| Emitted whole C++ CODE B | 17,086 | 18,150 | **18,161** |
| Emitted whole C++ x86 | 4,520 | 4,828 | **4,832** |
| Real 0x60 emitted CODE/x86 | 15B/2 | 541B/154 | **553B/158** |
| Real 0x61 emitted CODE/x86 | 15B/2 | 553B/158 | **553B/158** |
| Original 0x60 positional wrong mnemonics/widths/GPR roles | n/a | unaligned | **0/0/0** |
| Original 0x61 positional wrong mnemonics/widths/GPR roles | n/a | 100 GPR roles | **0/0/0** |
| Original typed PE external fields verified | 0 | partial | **10+10** |
| Entire afterRET DATA and relocated local case labels | 1,126B/151 | 1,126B/151 | **1,126B/151** |
| Native separate nonfield DATA equal | 522/522 | 522/522 | **522/522** |

The **all 316 original x86 mnemonic, instruction
width, and GPR-role sequences are now naturally
matched by C++ in these two real game cases**.
This does NOT imply raw case byte-exactness:
the partial father's saved `this` is at EBP−0x10,
whereas original game 004AC040 uses EBP−0x64.
Actual source and native relocation absolute
positions still differ; outgoing shared-parent
JMP displacements differ. For transparency,
the verifier reports actual unmasked nonfield
byte differences rather than calling
same mnemonic/register streams exact native CODE.

Reproduce only the touched giant:

    scripts/repo-python scripts/verify-third-fighter-volley-f942.py

Full compiled source, OBJ/PDB, original PE checks,
and verified receipt stay under machine-local
ignored `.analysis/f942-third-original-volley/`
and first exploratory controls at
`.analysis/f942-third-resource-volley/`.
The other independently accepted 979 source units
were NOT cold-replayed.

**The entire original 82,796-B callable giant
remains NONEXACT; 0 new accepted whole functions
and 0 newly accepted game CODE B.**
