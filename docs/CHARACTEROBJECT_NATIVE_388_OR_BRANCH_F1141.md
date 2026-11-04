# F1141 — Actual 0x388 native ground OR status policy: original `JNP` into impact body, not after it

The SHA-pinned Japanese TH075 v1.11 original contains ONE independently authored `CharacterObject::Advance` at `0050A580`, **81,539 CODE bytes /17,435 original x86** and 567 native afterRET sparse switch DATA bytes. Its genuine physical original game-state **`0x388` at `0051B89F..0051BB8B`, 748B/160 x86**, was previously implemented in a normal VC7.1 whole-parent C++ source with correctly matched mnemonics, GPR roles, instruction widths, physical external PE call/global fields and scalar values. The full-original **physical branch-target ordinal** audit F1140 exposed a *different actual semantic bug* that those checks missed.

The original at case ordinals **116/117** is `TEST AH,0x41; JNP` with a **true target of case ordinal 124**, which enters the native impact-response body (zero Y velocity, real `0040FB40(3)`, parent `00453D40(5)`, exit). If the FPU condition does not branch, only then does the original compare status+0x7C against 0 and 6 at ordinals 118–123. Both real `JE` status checks skip the body, targeting **ordinal 134**.

The older C++ used two *nested and mutually required* guards:

```cpp
if (!(actorY + actorVy <= ground)) {
    if (status != 0 && status != 6) { hitResponse(); }
}
```

This compiled to identical original `TEST AH,0x41; JNP` mnemonics but the JNP landed at **ordinal 134**, skipping the hit response, a real game behavior discrepancy for valid floating-point inputs. The corrected original-shaped C++ uses a single short-circuit **logical OR** condition:

```cpp
if (actorY + actorVy <= ground || (status != 0 && status != 6)) {
    hitResponse();
}
```

The actual C++ retains original source function calls, signed status tests and x87 compare grammar (including unordered-aware `JNP`). A fresh pinned normal VC7.1 **entire partial 81KB parent** compile confirms **160/160 native original 0x388 mnemonics, GPR roles and instruction widths, 14/14 physical original external PE fields** and original scalar values. Crucially, all three native branch destinations now match:

| Original case 0x388 jump | Original physical target ordinal | Current C++ target ordinal |
| --- | ---: | ---: |
| `JNP` at 117 (FPU condition) | **124** | **124** |
| `JE` at 120 (status 0) | **134** | **134** |
| `JE` at 123 (status 6) | **134** | **134** |

The tracked **one-parent original PE verifier** `scripts/verify-characterobject-current-recovered-f1068.py` now independently checks these three *physical* targets and all **1,834 original game-local direct branch edges** by global native x86 ordinal. After F1140's real 0x387 fix (two branches) and this 0x388 fix (one branch), **15 direct branch-target discrepancies remain** elsewhere. Those 15 remain explicit **NONEXACT correctness debt**, not an authorized comparison mask. The current original-shaped whole still emits **81,560B/17,435 x86** against original **81,539B/17,435 x86**, with native stack and register ownership wrong; **the whole original callable remains NONEXACT and newly accepted whole-original exact CODE stays 0B**. All 979 previously accepted whole exact functions are unaffected.

Reproduce ONLY this affected whole C++ parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Rejected nested-AND source, ordinary VC7.1 OBJ/PDB and original PE branch target evidence retained under ignored `.analysis/f1141-native388-cfg/` and `.analysis/f1068-boss-live-all-native/`. No original executable modification or 979-unit mass replay.
