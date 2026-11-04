# F1142 — Original 0x330 native ground JNP impact target 173, not 183; real OR collision policy

The pinned Japanese TH075 1.11 original has ONE authored 81,539-byte /17,435-x86 `CharacterObject::Advance` at `0050A580`, followed by genuine 567B afterRET sparse switch DATA. Original case **`0x330` at `0050D17A..0050D53A` is 960 native CODE B /209 x86**; the current one-switch parent remains an incomplete normal pinned-VC7.1 C++ reconstruction and is **NONEXACT** as an entire original callable.

An independent [F1140 whole-native original PE CFG audit](CHARACTEROBJECT_ORIGINAL_WHOLE_CFG_AUDIT_F1140.md) demonstrated that the older 0x330 C++ emitted all original 209 x86 mnemonics/GPR roles/widths, physical PE targets and scalar values **but had the wrong actual JNP destination**. Original `TEST AH,0x41; JNP` at case ordinal **166** lands at **173**, *inside* the stage-2 impact response body. The two subsequent signed status comparisons at 168/171 have `JE`s at ordinals **169 and 172** that skip the response, targeting **183**.

The previous C++ used a single `!(actorY+actorVy<=ground) && status!=0 && status!=6` predicate. This demanded that both the FPU condition and valid hit-status flag be true. The actual Japanese original tests **the FPU ground condition first and enters the body on its own; otherwise only then checks status flags 0 and 6**. F1142 restores the native short-circuit OR:

```cpp
if ((actorY + actorVy <= ground) || (status != 0 && status != 6)) {
    // Native Y-motion=0, stage action 0040FB40(3), parent 00453D40(5)
}
```

This is a substantive original gameplay fix, **not** just a compiler jump-size trick. The native collision/ground `TEST AH,0x41; JNP` unordered-aware flag grammar remains unchanged, as do the original status comparisons and their branch destinations. A cold compile of the **entire affected partial 81KB source** under the pinned normal VC7.1 compiler proves:

| Real original 0x330 branch | Native original target ordinal | Corrected C++ target ordinal |
| --- | ---: | ---: |
| FPU `JNP` at ordinal 166 | **173** | **173** |
| status-zero `JE` at ordinal 169 | **183** | **183** |
| status-six `JE` at ordinal 172 | **183** | **183** |

The entire 0x330 native case still matches **209/209 original mnemonics, GPR roles and instruction widths**, and every independently verified original physical PE external target and scalar literal is unaffected. The tracked `scripts/verify-characterobject-current-recovered-f1068.py` now also asserts all three original 0x330 physical branch target ordinals, and the **whole 81KB game's 1,834 direct jump destinations** by global native x86 ordinal, rejecting new regression. The known remaining true CFG mismatches have decreased **18 → 16 (F1140, 0x387) → 15 (F1141, 0x388) → 14 (this F1142, 0x330)**. Those 14 are still **real nonexact behavior debt**.

The one-parent source still generates **81,560B /17,435 x86** against the real game **81,539B /17,435 x86**, with wrong saved-this EBP stack position, 8 GPR-provisional original cases and two unsolved 0x391 x87 original PE fields. No newly accepted whole-original CODE bytes are claimed; **979 existing exact whole callables remain unchanged**.

Reproduce only the changed giant current parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Real original PE instruction/branch receipts, rejected AND-guard C++ and fresh pinned normal compiler output are retained under ignored `.analysis/f1142-native330-cfg/` and `.analysis/f1068-boss-live-all-native/`. No entire 979-unit cold replay or target EXE patch.
