# F780 — Whole original ordinary SpriteDrawing quad (0040C9A0)

Original R011 authored `0040C9A0..0040CA12` is a complete 115-byte,
37-instruction native function. Ghidra-native full disassembly, target
bytes, the reviewed `function-origins.csv` and fresh pinned VC7.1
compilation agree on the complete function boundary; no internal
helper source or after-RET data is credited.

The actual native order is:

- Call texture resolver `0040C8C0` and save returned pointer at `EBP-8`.
- Call native VC7 STL vector-size `0040DD20` with receiver `this+8`,
  store count at `EBP-4` (this library callee is excluded from authored credit).
- Copy exactly 33 dwords from the quad argument using `REP MOVSD`
  to local position array beginning at `EBP-8Ch`.
- Resolve texture again and call authored graphics draw `004029F0`
  on the copied 132-byte quad.

The 140-byte `LocalDrawContextF780` in
`src/SpriteOrdinaryQuadF780.cpp` is an explicitly provisional
source-compatible **stack view** of the 132-byte quad, saved first
texture and vector-size return. It produces the real `sub esp,90h`
frame, `EBP-90h` saved `this`, and authentic native short
`mov [ebp-8],eax`. Separate independent C++ local declarations
were disproven by their 118-byte emitted function, with first
texture pointer incorrectly at `EBP-8Ch`. No fake padding or
borrowed complete historical owner is asserted.

Full 115/115 byte comparison: all 99 original nonfield bytes match;
four genuine original REL32 fields at `0x1C` (`0040C8C0`),
`0x2D` (`0040DD20`), `0x4F` (`0040C8C0`) and `0x64`
(`004029F0`) match their physically resolved destinations and
zero addends. Fresh one-unit cold-build replay of
`sprite-drawing-ordinary-quad-native-0040c9a0` is **1/1 exact**.
The native function origin is authored, while its VC7 STL size
callee remains library-owned. Giant fighter functions are separate,
still nonexact.
