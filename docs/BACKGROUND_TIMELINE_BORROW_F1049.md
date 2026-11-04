# F1049 — Typed background timeline receiver in 54 whole native exact policies

The SHA-pinned Japanese TH075 v1.11 battle background stage methods
borrow a directly callable `TimelineDrawing438D00` interface from
receiver physical offset **+0x18**. This is not a separately owned
pointer stored at +0x18; the original x86 passes a receiver formed
by adding the 0x18 byte displacement to the actual background stage.
The complete stage type/lifetime is not established, and no source
may instantiate an enclosing inferred class merely from this view.

Before F1049, `src/BackgroundPoliciesF178.cpp` performed **36 separate
`reinterpret_cast<TimelineDrawing438D00*>(this+0x18)` expressions**
to draw pairs of real background sprites. The code was correct in
machine bytes but failed to expose the repeated original receiver
identity. The new `BackgroundTimelineBorrowF1049.hpp` records this
actual **borrowed call-only subobject** and each real draw expression
now uses `F1049_BACKGROUND_TIMELINE(this).DrawSprite(...)`.
This is an ordinary natural C++ lvalue call to the same receiver,
not a fabricated embedded object, owner pointer, or helper function.
It introduces no new runtime call and does not alter render state,
floating arguments, textures or game logic.

The one modified translation unit contains **54 separately accepted
complete native functions**, including native background transform,
side sprite pairing, dark/light sprite copy and related policies.
A normal pinned VC7.1 cold compilation was performed **once for the
changed object** and all 54 complete original functions and their
physical COFF relocations were checked independently. Targeted
`replay-exact-units.py` returned **54/54 exact** across one object,
**preserving all 6,612 previously accepted original CODE bytes**.

Reproduce exactly the affected source units, not the 979-function
corpus, by selecting every configured match unit whose
`source == "src/BackgroundPoliciesF178.cpp"`, for example:

    scripts/repo-python - <<'PY'
    import subprocess, tomllib
    with open('config/match-units.toml', 'rb') as stream:
        units = tomllib.load(stream)['units']
    selected = [k for k, v in units.items()
                if v['source'] == 'src/BackgroundPoliciesF178.cpp']
    assert len(selected) == 54
    subprocess.run(['scripts/repo-python', 'scripts/replay-exact-units.py',
                    *[word for k in selected for word in ('--unit', k)]],
                   check=True)
    PY

Native SHA, source-object and complete function cold replay evidence
is retained in ignored `.analysis/f1049-background-timeline-replay.log`
and the standard `.analysis/replay/` reports. No original EXE bytes,
reconstruction manifests, accepted function count or coverage
percentages changed. **This is semantic source progress preserving
previously exact callable CODE, not newly accepted game bytes**.
