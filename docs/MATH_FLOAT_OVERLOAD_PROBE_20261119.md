# Floating math helper reconstruction (2026-11-19)

**Status: all three game-side float wrappers are recovered as natural C++; the two 28-byte SDK-inline workers for `fabsf` and `sqrtf` remain origin-unknown.**

## Accepted angle pair (R269/R270)

`0x00483300` is the 21-byte game-owned `AngleAt00483300(float, float)` wrapper. Its 16 distinct callers are independently classified authored game functions and contain 211 direct calls in total. The shared source is `src/MathFloatHelpers.cpp`:

```cpp
float __cdecl AngleAt00483300(float y, float x)
{
    return atan2f(y, x);
}
```

VC7.1 `/Od /Ob0` emits the wrapper with its original single REL32 at +0x0C. The referenced 37-byte function at `0x00483320` is the x86 inline `atan2f` implementation from `.tools/msvc710/Vc7/include/math.h` (line 439): it widens both floats, calls CRT `_atan2` at `0x00642240`, and narrows the result. It is separately classified library/exclude as VC71CRT. The original wrapper, worker, call edges and complete authored caller set are checked by `scripts/verify-angle-at-00483300-origin.py`.

| Native | Bytes | Original relocation | Source/origin |
| --- | ---: | --- | --- |
| `0x00483300` | 21 | +0x0C REL32 to `0x00483320` | Authored game wrapper, R269; exact single-unit replay |
| `0x00483320` | 37 | +0x17 REL32 to `_atan2` at `0x00642240` | VC7.1 `math.h` inline `atan2f`, library/exclude, R270 |

## Accepted absolute-value and square-root wrappers (R271)

Two more complete game-side wrappers are now recovered in the same natural C++ source:

```cpp
float __cdecl AbsFloatAt00412D90(float value)
{
    return fabsf(value);
}

float __cdecl MagnitudeAt00428D20(float value)
{
    return sqrtf(value);
}
```

`0x00412D90` has 30 independently authored caller functions / 68 direct call sites. `0x00428D20` has three / six. Each original 17-byte wrapper has exactly one real REL32 at +0x08 to its 28-byte worker. The complete caller-body hashes and individual direct call sites are frozen in `config/math-float-helper-origin-evidence.json`.

| Wrapper | Bytes | Worker | VC7.1 x86 inline overload | Caller evidence |
| --- | ---: | --- | --- | --- |
| `0x00412D90` | 17 | `0x00412DB0` (28 B) | `fabsf`, `math.h` line 449 | 30 parents / 68 calls |
| `0x00428D20` | 17 | `0x00428D40` (28 B) | `sqrtf`, `math.h` line 469 | 3 parents / 6 calls |

The 28-byte workers reproduce the pinned VC7.1 `math.h` inline overload bodies and call the original CRT `_fabs` (`0x006418CD`) and `_sqrt` (`0x00641E54`) entries. However, the complete R163 SDK and ordinary-expression alternatives remain unresolved for those two worker addresses. They stay `unknown/review`; no worker or CRT body receives game-authored credit. Structural equality alone is not used to promote them.

## Focused verification

```sh
scripts/repo-python scripts/verify-angle-at-00483300-origin.py
scripts/repo-python scripts/verify-math-float-helper-origins.py
scripts/repo-python scripts/replay-exact-units.py \
  --unit math-angle-at-00483300 \
  --unit math-absolute-float-at-00412d90 \
  --unit math-square-root-float-at-00428d20
```

The three complete wrapper units cold-replay exact (3/3) in one shared natural C++ object. The verifier checks the original complete caller sets, every call edge, the SDK header source, the three genuine wrapper relocations and the separate worker dispositions. No ASM, padding, dead code, target-byte literals, relocation masks or callee double-credit are used. Original private declarations, source spellings and full math module layout remain provisional.
