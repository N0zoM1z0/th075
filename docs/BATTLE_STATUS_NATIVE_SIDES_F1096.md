# F1096 — Native two-player HUD status float and name-group word pairs, 3,510B whole exact

The SHA-pinned Japanese TH075 1.11 original includes one independently
accepted **3,510-byte complete `BattleStatus440B50::RenderStatus`**
at original game address `00440B50`. Its native main loop is indexed
by the two player sides and reads multiple physically adjacent pair
windows. Before F1096, the accepted exact source represented all of
them as repeated generic raw pointer/byte-offset casts.

## Observed original fields in the complete native function

Three **independent, 8-byte native float pairs** begin at HUD owner
+`0xE4`, +`0xF4` and +`0x104`; each physically contains two float
values, one for each fighter side. They feed real sprite scale,
vertical slide and secondary offsets in both player branches of the
native RenderStatus function. A borrowed `BattleStatusFloatPairF1096`
provides the observed native `float bySide[2]` window without
allocating, embedding or claiming a full reconstructed HUD owner.
The selected source replaces **45 actual original indexed float
field accesses** in the single complete game function, preserving
`i*4`, original `std`/draw calls, original rectangle construction,
native `D3DCOLOR_ARGB` args and all x87 expressions.

The **two adjacent signed 16-bit name-group choice WORDs** at actor
+`0x398` and +`0x39A` are selected according to the independent
actor+`0x39D` signed byte. The original code uses the first group
when selector equals 2, otherwise the second group, with actual
+42/+45 atlas group offsets. The narrow borrowed
`FighterNameGroupWordsF1096` at actor+`0x398` names only these
observed two shorts; actor class, other fighter memory fields,
and +0x39D selector ownership remain independent. Compile-time
size/offset checks enforce the real 4B WORD and 8B float windows.

No extra unknown fields, new draw functions, artificial runtime
locals or x86 instructions were introduced to make a byte match.
Both independent source substitutions use genuine physical original
float and signed WORD values, preserving native control flow.

## Entire native cold replay, not cropped field matches

The single affected `src/BattleStatus440B50.cpp` translation unit
was compiled from scratch with the pinned VC7.1 `/Od` profile
**twice**: after typing the three float side arrays, and again
after typing the signed name-group pair. In BOTH runs, the **entire
3,510-byte original native game callable**, all actual PE call/global
COFF targets and original game CODE passed strict cold exactness:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-status-render-00440b50

**Result: 1/1 whole original function exact; 3,510 previously accepted
CODE bytes preserved.** No new original exact CODE or whole callable
credit was added, and the other 978 exact units were not replayed.
The original Japanese EXE, manifest and COFF identity comparison
rules are unchanged. No target-byte graft, full-owner speculation,
assembler, fake stack padding or mass cold replay was used.
