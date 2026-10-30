# F746 — 94-B original BG05b authored counter policy COLD EXACT

**New original whole-function exact CODE: 94 bytes, one complete R212-authored
callable game function.** Original input is user-provided Japanese TH075 v1.11
`resources/th075.exe`, pinned SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Original native `0044E8D0..0044E92E` comprises exactly **94 CODE bytes,
32 x86 instructions, zero PE/COFF relocations**. The independently
reviewed R212 authored provenance, BG05b loader/teardown ownership and
read-only table caller evidence were present before this source was written;
none of that proves the full historical original private class layout.

## Actual entire original source and codegen

Tracked normal C++ [`src/BackgroundCountersF746.cpp`](../src/BackgroundCountersF746.cpp)
implements all three original signed-DWORD state transitions in native order:

```cpp
--FIELD(0x68);
if (FIELD(0x68)<0) FIELD(0x68)=0xF00;
++FIELD(0x6C);
if (FIELD(0x6C)>=42) FIELD(0x6C)=0;
++FIELD(0x70);
```

Original native `+0x68` is decremented and reset to 3840 on underflow;
original `+0x6C` increments and wraps at 42; original `+0x70` counts
upward independently. All fields are actual used native object storage,
not fabricated compiler-frame slots. The code uses native thiscall
prologue `PUSH EBP; MOV EBP,ESP; PUSH ECX`, actual `EBP−4` receiver,
three member accesses and regular `RET`, and nothing has been truncated.

MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` emits the **entire
94/94 original machine bytes and all 32/32 ordered x86 instruction
positions**, without any relocation masking: the original and object
both have **zero physically typed COFF fields**. The observed member
words are not evidence for the full BG05b class allocation.

## Reproducible one-unit cold replay and formal accounting

The new original whole unit
`background-stage-bg05b-timer-ticks-0044e8d0` declares the original
physical `0044E8D0`, entire 94-B source/code, matching VC7.1 flags,
correct decorated C++ method symbol, and `relocations = []`.
The canonical tool cold-built only the new C++ object and checked
**1/1 complete authored game function EXACT**, leaving all existing
965 accepted units untouched:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit background-stage-bg05b-timer-ticks-0044e8d0
# Cold replay: 1/1 exact across 1 object
```

Formal accepted original-authored ledger is now **966 complete
byte-exact functions /966 source-present /966 canonical units**,
**864,118 original CODE bytes**, **43.78% reviewed authored
coverage** and **43.71% conservative** with 3,420 origin-pending
bytes included in the goal denominator. Existing giant boss bodies,
WinMain, Scene and Archive destructor remain NONEXACT. No all-965
cold replay was attempted; no original PE bytes were modified.
