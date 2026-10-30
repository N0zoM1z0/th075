# F813 — Original scripted fighter stage-three action 0x59 reconstructed in the same giant

**New whole-internal game action source, not a whole callable function exact match.**

The original SHA-pinned Japanese TH075 1.11 PE has a complete
46,755-B callable scripted fighter at 005214B0 and 901 separately
owned post-RET jump DATA B. F812 had recreated thirty complete
original action interiors inside a still incomplete parent,
including a real ten-projectile 0x58 loop and the authentic F806
46-B/16-x86 default and shared getter tail.

The next actual packed second-switch handler is 0x59:
native PE 0052327A..005233DD, **356 original CODE B,
95 x86 and 16 genuine PE/COFF fields**. Its real control flow
begins with *signed stage equal to three*, reads and modifies
the authentic +0x30 float field through original global 00657858,
updates +0x54 position and +0x5C drag, executes the original
x87 contact and two float-to-short conversions, then performs the
real game trajectory callbacks. The later native action getter
selects **auxiliary state 3**; stage-three/frame-zero motion
reads actual +0xF00/+0xF02 short values and multiplies by genuine
globals 006590BC/00658044, then calls original motion setup.

The earlier other-fighter F752 source had tested stage >1 and
auxiliary state 2. **Those are not the physical actor-specific
0x59 semantics here.** The new tracked natural C++ in
probes/FighterScriptedBounce59F813.inc uses the independently
observed stage ==3 and aux state 3, not an assumed
historical type owner.

The tracked verifier builds *one complete affected VC7.1 source
parent*, first regenerating and physically validating F614's
previous thirty complete game action bodies. Its source now
emits **9,636 callable CODE B/2,432 x86**, compared with F812
**9,295 B/2,339 x86**. The newly inserted 0x59 independently
matches **all 95 original source instruction mnemonics and
all original x86 widths**, exact full **356-B** case extent,
and **all 16 authentic native PE relocation field positions,
kinds, zero addends and physical call/global destinations**.
The prior 30 actions and complete original 901-B packed switch
DATA are rechecked in the newly built parent.

F813 also physically checks the complete 46-B/16-x86
default/getter geometry, all three original PE calls and
each of the four original early action0/2/4/5 JMP positions.
No original binary bytes or x86 registers are patched.

**Important unresolved bytes:** the current case59 source has
**57 genuine unmasked nonrelocation machine-byte differences**
due to GPR/stack-frame context despite the exact instruction
geometry and real PE references. The native tail has eight
real wrong bytes (four GPR and four saved-this EBP positions).
These are **not** relocation bytes, must not be suppressed,
and are not evidence that the entire original 46KB giant is exact.

Targeted verification only, without full corpus replay:

    scripts/repo-python scripts/verify-scripted-fighter-stage3-bounce-f813.py

Complete generated C++, compiler object/PDB, source diagnostics
and verified physical results are preserved in ignored
.analysis/f813-scripted-59/. The entire game giant still
remains NONEXACT and earns zero new accepted authored CODE.
