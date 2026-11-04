# F1041 — Preserve the complete 58KB original-shaped Fighter in Git

The independently authored Japanese TH075 v1.11 fighter `Advance`
`00543210` remains one **nonexact 58,294-byte / 16,471 x86** original
callable, followed by 943 separately owned switch DATA bytes.
The strongest generated full source was previously only an ignored
local C++ research file
`.analysis/f917-native-burst-x87-verified/F917-borrowed-real-X.cpp`.
That entire source is now verbatim and Git-backed as
`probes/FighterWhole00543210F1041.cpp`. Their matching source SHA-256
is `5c9668dee35e104f00ce8ec31ba9d172c7086eda1d57296ab69a3e3b724ff268`.

The actual original-native F1025 verifier was modified to compile the
**tracked best current source directly**, not unnecessarily regenerate
two historical native F781/F917 alternatives on every check. The
historical paired source-recovery experiment still exists and is
reproducible via `verify-fighter-native-burst-x87-f917.py`.

Fresh normal VC7.1 cold build and pinned-original PE verification:

| Complete callable evidence | Actual result |
| --- | --- |
| Original source function | `00543210`: 58,294B / 16,471 x86 |
| Best tracked generated C++ | 58,293B / 16,471 x86 |
| Wrong original ordered x86 mnemonics | **0** |
| Wrong original x86 widths | **3** (ordinal 2934, 2977, 3000) |
| Wrong original register operand roles | **1,741** |
| Original physical external PE targets | **1,697/1,697 verified** |
| Original CODE-local jump fields | 10 |
| Genuine original afterRET DIR32 fields | 156 |
| Actual literal afterRET nonfield bytes | **319/319** |

The native `FSUBR` projectile-X recovery from F917 is preserved in
this tracked source, with the genuine ordinary source expression and
typed borrowed coordinate; it is not a binary byte patch. The
source still has a real one-byte CODE length deficit, original
instruction width/register differences and physically shifted
COFF sites. No original entire function was newly accepted exact.

Targeted complete source verification:

    scripts/repo-python scripts/verify-fighter-whole-58kb-pe-targets-f1025.py

Preserve the older ignored .analysis sources/objects and original PE
proof; moving the selected readable C++ into Git does not imply
those older native research artifacts can be discarded. No all-979
cold replay or fake internal case credit was performed.
