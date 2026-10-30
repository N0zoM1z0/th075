# F818 — Whole authored Scene borrowed field views versus original stack

The pinned original TH075 1.11 authored Scene virtual destructor
0043B0B0 spans **248 callable CODE B /75 x86** and **12 real
physical PE/COFF fields**. The original texture/delete receiver
slots are EBP-0x14/-0x10 and the original three released-CRT
pointers are EBP-0x18/-0x1C/-0x20. Current baseline generated
248 B/75 x86 with correct native PE references, but still
**191/200 correct nonrelocation bytes**, with nine real EBP differences.

F818 freshly compiles seven **whole** VC7.1 /GX source variants:

| Natural source view | Source B / x86 | Original PE-backed result |
| --- | --- | --- |
| Baseline raw FIELD access | 248 /75 | 191/200, 12 real fields |
| Observed typed texture at this+8 | 248 /75 | Entire generated COFF identical |
| Typed CRT-free fields at +4C/+50/+54 | 248 /75 | Entire generated COFF identical |
| All four typed borrowed fields | 248 /75 | Entire generated COFF identical |
| Named used borrowed reference | 254 /77 | Two extra x86, nonnative frame |
| Named used borrowed pointer | 254 /77 | Two extra x86, nonnative frame |
| Named used borrowed const-pointer | 254 /77 | Two extra x86, nonnative frame |

The borrowed view contains only physically observed original member
offsets and intervening unknown bytes. It is neither instantiated
nor claimed as a complete original class. For the source-sized
248-B alternatives, verification independently resolves ALL 12
original PE field offsets, kinds, addends and native targets.
All whole source CODE and COFF references remain byte-identical
to baseline, proving plain typed views do not improve the nine
wrong actual stack-location operand bytes.

Naming the borrowed reference or pointer forces a truly used
local and generates 254-B/77-x86 code with saved this at
EBP-0x28. It cannot be truncated, relocation-masked or
accepted as the original 248-B source.

Targeted replay:

    scripts/repo-python scripts/verify-scene-borrowed-owner-f818.py

Source C++, compiled COFF and evidence are regenerable in ignored
.analysis/f818-scene-borrowed-owner/. Scene remains NONEXACT;
no whole authored function credit and no all-unit cold replay.
