# F1232 — native-backed middle states in 005A1600

The live partial parent in `probes/CharacterObjectActions005A1600F1231.cpp`
now writes **32 of 76** nondefault states, adding **811 and 813–826** to
[F1231](OBJECT_ADVANCE_005A1600_INITIAL_PARENT_F1231.md). These fifteen complete
native case intervals contain **11,543 CODE bytes /3,148 instructions**.
They are research inside one enclosing function, not accepted callables.
**All 43,599 original CODE bytes remain pending; 44 states are unwritten.**

## Original-backed behavior

811 retains the second Y-plus-velocity floor test with **<= 0.0f** and phase
**< 7**, then clears velocity/Y, shakes the camera, resets to 7, plays sound 10
and emits two auxiliary 129 packets in native order. The else path preserves
phase 8 fade, animation advance and phase 6/frame 0 speed -18/sound5.

813/814 keep separate F0E lifetimes, limits 20/30 and backward speeds -3/-2.
Their actual ST0 absolute-distance call is compared with 100.0f before reset 3,
speed 10 and the empty receiver call 0045B850(8). The latter is borrowed with
its observed RET4/int-argument contract; no original typedef or ownership is
invented. Later fade, bounds, frame exhaustion, hit-qualified retry and phase
resets keep the original early exits and physical nonzero-hit branch order.
814 additionally preserves the owner 3B8/self 8A gate.

815 retains the F10 lifetime, owner-window reflections selected by facing and
velocity sign, the strict negative floor/velocity bounce, sound 13, phase 5
fade, and the native phase 2/phase 4 motion/repeat policy. 816/817 preserve their
distinct offsets 126/127 and rotations +5/-5. 816 keeps its extra owner 490
reset and direction calculation: a used floating comparison is
converted to a 0/1 compiler temporary before the signed velocity product.
The source expresses this directly, without adding a user local or padding.

818/820/822 preserve the four FUCOMPP equality load orders and owner-bound
coordinate attachment. 819/821/823 each retain all four independent motion
phases, repeated frame-zero guards, five native effect packets and final
phase resets. An independent native comparison finds only the actual parent
action/effect-number changes for 821, plus the four signed-speed magnitude changes from 12 to 16 for
823. The common guard uses the actual **D8 > 5** CMP/JG form. 824–826 retain
their distinct parent action guards and raw DWORD coordinate transport.

The added borrowed declarations expose only camera shake 00453E60(float),
auxiliary effect 00453C80(short,float,float,signed-char,signed-char), the empty
0045B850 receiver call, and existing one-float/ST0 absolute helper 00412D90.
No helper body, complete owner layout, accepted input or origin changes.

## Selected partial build and precise limits

Two new serial headless VC7.1 builds use
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`. The selected `orbit.obj`
contains **19,399 CODE bytes /5,218 instructions**, frame **0xAC**, receiver
**EBP-0xC**, 33 dense entries/200 sparse bytes and 378 COFF records. All 32
written cases, the prefix and default remain represented in one source body.
Written native case intervals total **19,230B /5,171 instructions**.

All written mnemonic sequences, local branch target ordinals and normalized
operand shapes agree. The source diagnostic independently rereads actual
COFF constant payloads. **Raw differences still total 527 GPR positions,
14 widths and 1,685 EBP operands.** Normalized agreement is not byte equality.
All 26 written states 800–826 (812 is a native default input) have zero raw GPR
debt. Their eight width differences are actual MOV/FILD displacement widths
in 819–822: source temporaries are 16 bytes above their original slots. Four
real native loop indices remain in unwritten states; do not add fake locals
to force the native frame 0x21C or receiver EBP-0x1C. Later 988/989/995–997/999
register allocation and six widths remain provisional in this partial parent.

Retained evidence: `.analysis/f1232-object-5a1600-middle/` contains before,
middle and orbit immutable CPP/HPP/OBJ/listings/build logs, selected native
constants/callees/spans, related-state differences, both source diagnostics,
the actual `partial-raw-width-debt.json` and `verified-summary.json`.
Selected CPP SHA256:
`5a090b2c5e8d55fd6a8aeff14431e37cf11b32839aae56c14e99c1312de57ef0`;
OBJ SHA256:
`ce0e828ba669020e249134fa4690f8ec670707228de9c5d039db4f4dc755517b`.
F1231 retains the complete original CODE/DATA/constructor/vtable evidence.

Continue at 827 and the remaining real states. This partial function has no
canonical exact unit. Target/tracking/status/handoff checks, read-only Ghidra,
affected-parent compilations and whitespace checks are sufficient here; no
full CI, corpus replay, origin retest or per-function tests were added.
