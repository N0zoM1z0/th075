# F1134 — Native fighter HUD slide, style-indexed limits, gauge and shade bytes: 9,841B whole callable remains exact

The pinned Japanese TH075 1.11 original contains one previously independently accepted **9,841B complete** `BattleHud43E040::RenderHud` at `0043E040`. F1134 reconstructs **127 actual native source field accesses** as narrow, borrowed C++ typed storage inside its one original source object, without allocating or claiming an unverified complete historic HUD/fighter owner. The original physical native code, COFF relocations and local symbols remain **whole-callable byte exact**.

## Physically observed original native owner windows

- **77 original accesses** to the HUD owner's *single physical float* at **+0x8C** now use `F1134_HUD_SLIDE(this).verticalSlideAt8C`. The actual source uses both positive/negative scroll offsets and the original `Translate`, number drawing and health-bar placement expressions; no extra local state was introduced.
- **15 original signed-byte accesses** to the actual fighter-side visual style selector **actor+0x39D** now use `F1134_FIGHTER_SELECTION(...).styleAt39D`, for three left-side and twelve right-side source uses.
- **Eight original indexed signed-short health denominator accesses** to fighter+**0x33E** now use a borrowed **three signed 16-bit WORD** `F1134_FIGHTER_HEALTH_LIMIT(fighter,style)` window indexed by the original style selector. The source still uses authentic integer division and actual native bar geometry, and does not invent range checking absent from the original.
- **One original three-signed-byte display-choice indexed access** at fighter+**0x32A** now uses `F1134_FIGHTER_VARIANT(fighter,style)` with the actual original selector.
- **Twelve original +0x3B0/+0x3B6 signed gauge WORD uses** now reuse the independently proven `F980_GAUGE` narrow native gauge window for both fighters (four native meter reads and two cooldown reads per side). **Eight +0x36C native float accesses** now use a borrowed four-byte fighter `F1134_FIGHTER_CHARGE` window, preserving actual 0..900 charge-to-sprite conversion and original x87 operations.
- **Six true adjacent HUD owner unsigned shade bytes** at **+0x98/+0x99** now use a two-byte borrowed `F1134_HUD_SHADES` window (three original reads of each byte), preserving original ARGB argument placement and input signs.

The source originally used raw `(char*)this + offset`, repeated macro pointer arithmetic and direct `(signed short*)` indexed arrays. The selected code replaces those accesses with *existing physically observed signedness, widths and native offsets*, guarded with `sizeof` and `offsetof` checks for all windows; no complete type layout, local class instance, extra branch, helper call, unconditional dummy load or target-byte graft was introduced.

| Original native field view | Actually replaced source occurrences |
| --- | ---: |
| HUD floating vertical slide +0x8C | **77** |
| Fighter signed style byte +0x39D | **15** |
| Three signed health-limit WORDs +0x33E | **8** |
| Three signed display-mode bytes +0x32A | **1** |
| Fighter signed gauge WORDs +0x3B0/+0x3B6 | **12** |
| Fighter charge float +0x36C | **8** |
| HUD adjacent unsigned shade bytes +0x98/+0x99 | **6** |
| **Total** | **127** |

## Full original 9,841B cold replay, not an internal branch test

The single affected `src/BattleHud43E040.cpp` was **cold compiled four times** with the pinned ordinary VC7.1 toolchain: after the HUD float slide view, after actor selection/health/variant fields, after fighter gauge/charge views, and after the byte-shade pair. Every complete comparison returned:

    scripts/repo-python scripts/replay-exact-units.py --unit battle-hud-render-0043e040

**1/1 original entire game callable exact, 9,841/9,841 previously accepted original CODE B preserved.** The final independent COFF/PE comparison also returned **`exact`**, not merely a mnemonic, structural or afterRET-less match. The original Japanese EXE and canonical manifests were not modified. Baseline source and serial native build receipts are retained under ignored `.analysis/f1134-hud-native/`; no 979-unit full corpus replay. This is real original-shaped source and memory-layout recovery, **zero newly accepted whole original game CODE bytes**.
