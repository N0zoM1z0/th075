# F871 — Original PE-wide static caller/provenance audit of three byte-exact small leaves

This audit independently uses the SHA-pinned Japanese TH075 v1.11
original resources/th075.exe and separately rebuilds the actual
normal pinned VC7.1 C++ source for all three previously
unclassified complete native methods:

| Original complete function | Entire native CODE | C++ codegen equality | Original origin |
| --- | ---: | --- | --- |
| 004135F0 | 40 B /16 x86 | 40/40 original bytes | unknown/review |
| 00454C00 | 24 B /9 x86 | 24/24 original bytes | unknown/review |
| 00454F70 | 31 B /15 x86 | 31/31 original bytes | unknown/review |

The original PE is parsed directly from its DOS/COFF headers,
IMAGE_BASE and FIVE section descriptions (including all executable
and all nonexecutable sections). Two mutually independent static
reference modes are checked: every raw original PE section byte
is searched for the *unaligned* full 32-bit absolute function
address, and every byte in the entire 2,449,408-B executable
original .text section is tested for E8 CALL rel32 or E9 JMP
rel32 with the true resolved target address. This raw scan
does not depend on Capstone linear disassembly staying aligned
across original packed switch DATA and is not restricted to
previously assigned function-boundary lists.

The three original unknown small methods have **zero exact
absolute-VA pointer occurrences, zero direct E8 calls and zero
E9 jumps** in this original executable image. Positive control
target scans on original known game functions
0040FA30, 0040FAC0, 00453E20 find thousands of physical
direct calls, confirming the reference detector does find
real native executable references in the same file.

**What this does not prove:** Original game code may reach
these methods through an arithmetic-computed function pointer,
register-indirect call, vtable assembled dynamically,
an external trampoline, or another runtime mechanism that
does not store the methods' addresses in the original PE.
Therefore the lack of static xrefs does not establish
"unused", compiler/library origin, game-authored provenance,
the original owner class, or nominal source field types.
In particular adjacency to other authored source is not
adequate original owner identification.

The script rechecks both the entire F799 native 40B and
31B sources and the entire F805 24B source using targeted
VC7.1 compiles before auditing original static xrefs.
All three remain classified exactly as original
unknown/review in function-origins.csv.
No tracked canonical authored function, match,
origin or unit is added and **zero authored whole
CODE bytes** are credited.

Targeted audit:

    scripts/repo-python scripts/audit-unknown-leaf-native-xrefs-f871.py

The strict native evidence/PE summary and targeted C++ build logs
are preserved in ignored .analysis/f871-native-static-leaf-xrefs/.
No all-unit cold replay. Further original owner/callsite/vtable
evidence is required before any historical authored promotion.
