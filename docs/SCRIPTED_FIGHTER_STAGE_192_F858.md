# F858 — Native actor 192 changes action, stage and float owner member

Pinned Japanese TH075 v1.11 original fighter at 005214B0
owns 46,755 callable CODE B plus 901 separately owned
packed afterRET dispatch DATA bytes. Its original 0x192
at 00527521..005275F9 has **217 whole original interior
CODE B/64 native x86/six original PE REL32 call fields**.
This state looks like 0x190 but their correct C++ gameplay
parameters are genuinely different.

Native original 0x192 uses state2 (not 0), spawns
projectile kind0x320 at **stage4** (not stage3), stores
**3.0f** into observed owner member this+0x314 (not 1.0f),
starts animation0xFA and then PrepareActionAt453D40(0),
and sets +0x7C to one at **stage5** (not stage4).
These values were independently checked in the pinned
original PE. Four normal whole-parent C++ variants
individually change the real sprite stage, float owner
value or state; each wrong candidate produces additional
real nonrelocation machine-byte differences even though
they emit the same 217B/64x86 size and PE field count.

The selected normal source, compiled as ONE complete
affected VC7.1 fighter, produces the original native
64 x86 mnemonic/size/position grammar and all SIX
original PE call target addresses, field offsets,
types, zero addends and source symbols.
The source still differs at 39 genuine GPR operand
bytes and two original final enclosing-giant JMP
relative bytes +213/+214. Neither difference
is masked or declared exact callable original CODE.

F858 regenerates and physically rechecks the previous
F857 whole source, then compiles its own new 0x192
parent. The generated callable source grows from
**25,488B/7,038 x86 to 25,690B/7,100 x86**.
All NINE preceding GPR-affected 136/186..191 case
interiors, TWENTY earlier C8..135 source-backed
native cases and their actual PE fields are rechecked.
All five original packed afterRET tables are also
physically reverified with their total 901B DATA.

The shared original 46B/16-x86 getter currently
has four genuine nonrelocation GPR byte differences
at offsets 10/12/16/19 (though all three real
PE REL32 calls remain correctly targeted).
Do NOT inherit the shorter F857 native-default
34/34 equality label without rechecking the
larger new compiler context.

Selected targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-stage-192-f858.py

All source variants, VC7.1 COFF/PDB and original
PE comparison evidence remain in ignored
.analysis/f858-scripted-stage192/.
Original whole 46,755B fighter remains NONEXACT.
Zero independent original case/whole CODE adopted.
No all-unit cold replay.
