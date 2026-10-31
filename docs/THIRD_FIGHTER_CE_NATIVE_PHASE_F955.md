# F955 — Original 004AC040 CE reconstructed, and the authentic CC→CD→CE GPR phase

Pinned Japanese TH075 v1.11 original fighter at **004AC040**:
**82,796 complete game callable CODE B /22,721 x86**,
plus **1,126 independently owned afterRET jump DATA B**.
The current normal VC7.1 C++ father is still partial,
with many original cases missing and a different saved-this
EBP slot, so the entire original fighter is NONEXACT.

Original physical **0xCE** is
**004B0BB8..004B0D42**, **394 native CODE B /
115 x86 /9 genuine original PE-targeted call/global fields**.
F953's independently original-authored 0xCC/0xCD
have 435B/128 x86/11 PE fields each.

The pinned original 0xCE **does not** perform the stage-4
auxiliary speed/threshold action present in original
CC/CD. Its true signed stage-3 branch first issues the
original `00453C80` projectile (kind 0x3C with real raw
X/Y and char-facing ABI), THEN writes actual
`X=-10.0f`, `velocity=15.0f`, `drag=0.7f`,
and clears the real `+0x3AC` byte flag.
It retains the actual ground/collision and frame-advance
control flow, native `00454BC0`, `00453E20`,
`0040FAC0`, real PE floats `0065782C`,
and a genuine virtual frame-advance call.
The natural authored [F955 CE source](../probes/FighterThirdBossCEF955.inc)
is not a fabricated standalone function or a byte graft.

## Whole-parent experiment: prior state controls the following state's GPR phase

The independently authored, pinned original PE
[verifier](../scripts/verify-third-fighter-ce-phase-f955.py)
regenerates **four entire normal VC7.1 original-shaped
partial 82KB fighter fathers** and cold compiles
the four actual parent TUs serially:

| Complete partial source variant | Whole emitted CODE | CE source | CE native GPR errors |
| --- | ---: | --- | ---: |
| Prior original-shaped CC/CD/CE markers | 20,397 B | 15B/2 x86 marker | n/a |
| Real CE alone, CC/CD still markers | 20,776 B | **394B/115 x86** | **72** |
| Real CC+CD, CE remains marker | 21,237 B | 15B/2 x86 marker | n/a |
| **Real CC + real CD + real CE** | **21,616 B /5,859 x86** | **394B/115 x86** | **0** |

Both true source-backed CE variants emit the **entire
native 394B/115-x86 positional mnemonic and width geometry**,
and both validate **all 9 actual original typed zero-addend
PE/COFF target fields** against the physical source/native
instruction ordinals. In addition, the all-real parent
rechecks both prior 435B/128-x86 original CC/CD and their
11+11 native PE fields, the genuine following 114B/30-x86
CF source and original PE targets, the complete
151 original afterRET DIR32 label entries and
all 522 nonfield DATA bytes.

**Critical new fact:** the SAME authentic CE source has
**72 wrong GPR-role instructions when preceding CC/CD
remain placeholders**, but **ZERO wrong GPR roles with
the correct preceding native CC and CD C++ bodies
in the SAME complete partial parent**. In combination
with F953's 77→0 GPR recovery for CD itself, this
proves two consecutive compiler register-phase
dependencies in one giant: **CC→CD→CE**.
It is evidence of true whole-source control-flow
allocation rather than a reason to force registers.

Despite CE and CD reaching native x86 GPR and width
geometry, the *partial* source still saves `this`
at EBP−0x10 rather than native EBP−0x64;
the original 82KB father has an independently
verified full 0x720 stack frame and many other
non-native original call/relocation fields.
No inner case is independently accepted as
an original callable exact game function.

Reproduce bounded full-source original PE proof:

    scripts/repo-python scripts/verify-third-fighter-ce-phase-f955.py

All four compiled whole original-shaped sources,
OBJ/PDB, VC7.1 compiler logs and original PE
verification receipt stay in ignored
`.analysis/f955-third-ce-phase-proof/`. Initial
CE-alone and CC/CD+CE studies remain preserved
in ignored `.analysis/f955-third-ce/`.

**Zero new accepted original callable functions
or CODE B. No 979-unit cold replay.**
