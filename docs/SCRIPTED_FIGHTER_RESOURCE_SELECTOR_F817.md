# F817 — Native 0x62 resource selector exposes another downstream GPR phase

The original Japanese TH075 v1.11 fighter at 005214B0 has
46,755 original callable CODE B, 13,230 x86 instructions
and 901 separately owned afterRET packed switch DATA B.
F816's recent whole-parent C++ source produced 11,551 B,
restored original saved this EBP-0x10 and generated
the real 46B/16-x86 default/getter with **34/34
nonrelocation bytes identical** plus three true PE calls.

F817 adds the original next packed action 0x62 at
00523BA4..00523C9C: **249 real native CODE B,
65 x86, 4 true zero-addend REL32 PE calls**.
Natural source in probes/FighterScriptedResourceSelectorF817.inc
retains actual signed facing times +0x4DC and four unsigned
resource status fields at +0x4E8..+0x4F4, writes a genuine
+0xF00 short flag, then chooses original action 0x5F,
0x5D or 0x5E depending on the native resource and
action getter result. The native final JMP targets
the enclosing function epilogue directly; normal
return in this void Advance method reproduces that
actual control-flow exit without fake C++ ABI tricks.

The tracked verifier regenerates and strictly revalidates
F816's entire selected whole-parent source before inserting
the new 0x62 case and compiling the one affected VC7.1
translation unit. The new parent emits **11,785 source
callable CODE B/3,069 x86**, preserving the original
901B afterRET jump DATA and its true PE table bounds.

F817 independently checks all 5F/60/61/62 full native
case intervals, instruction widths, GPR/x87 opcode
mnemonics, actual physical original PE/COFF destinations
and their zero addends. Native 5F/60/61 still differ
only in genuine parent-external long-JMP relative operands
(2/4/4 bytes respectively). The newly generated 249B/65-x86
0x62 contains **10 real GPR operand byte differences**
and **two original parent-final JMP operand differences**:
these are NOT COFF relocations or accepted exact bytes.

Adding actual 0x62 source preserves the original
EBP-0x10 receiver slot but naturally rotates later
default register allocation, making **four true
non-relocation GPR bytes at suffix offsets
10/12/16/19 different again**. Every other
default 46B nonrelocation byte, including real
saved-this frame offsets, remains native-exact,
and all three physical original default REL32
calls still resolve correctly. Thus F816's
temporary local suffix exactness must NOT
be asserted for the larger F817 whole parent.

Selected targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-resource-selector-f817.py

The native 46,755B original game giant is still
incomplete; no internal action or shared tail
receives formal independent callable exact CODE
credit. Generated C++, COFF/PDB and physical
comparison summary are retained under ignored
.analysis/f817-scripted-selector/. No full
979-unit accepted corpus cold replay occurred.
