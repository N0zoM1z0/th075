# F1086 — Two 149B native animation-binding leaf functions share a genuine 12B borrowed window

Pinned Japanese TH075 1.11 original code contains two **separately
accepted exact complete game callables** which update real animation
bindings through different typed native row implementations:

| Original game leaf | Original exact CODE | Original row method |
| --- | ---: | --- |
| `BattleAnimationBindingF139::BindAnimation` at `0045B880` | **149B** | nested `std::vector`-style `.at()` |
| `FighterAnimationReset453D80::BindAnimation` at `00453D80` | **149B** | native sequence `.At()` |
| **Both original complete functions** | **298B** | **2 independent callables** |

Each original native actor layout has physically identical adjacent
binding fields beginning at **actor+0x70** despite the two genuinely
different row/frame types:

| Native original actor field | Real observed type | New borrowed member |
| --- | --- | --- |
| `+0x70` | signed 16-bit count | `sequenceFrameCountAt70` |
| `+0x72` | unsigned 16-bit frame duration | `frameDurationAt72` |
| `+0x74` | native 32-bit frame pointer | `currentFrameAt74` |
| `+0x78` | native 32-bit row/sequence pointer | `currentRowAt78` |

The new `AnimationBindingWindowF1086<Frame,Row>` is a **12-byte
borrowed original field window**, *not* a guessed full fighter
owner, padding or newly allocated object. The frame/row pointer
pointee types are preserved by template specialization for each
real source. The original actor+0x08 active-frame pointer remains
separately owned and is not falsely merged into the 0x70 window.
C++ compile-time assertions check the original **12-byte extent,
32-bit pointers and field offsets 2/4/8** separately for both
native source instantiations, using the actual pinned 32-bit
MSVC7.1 toolchain.

The real original operations remain unchanged: select the frame
through actual current action+0x60 and frame index+0x62, publish
new current frame at +0x74 and active frame at +0x08, copy the
actual frame duration from native frame+0x04 to +0x72, set the
sequence frame count at +0x70, then record the real row pointer at
+0x78. Neither source's actual `.at()` versus `.At()` implementation
or original call targets were collapsed into a fictional universal
native engine class. No extra runtime call or helper is emitted.

## Whole-function native cold replay, not cropped expression proof

The two actually changed source translation units were cold built
under pinned normal VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`.
Strict comparison verified the full original native CODE bytes and
physical COFF relocations for **both** complete 149B functions;
initial typed window addition and subsequent genuine C++
`sizeof`/`offsetof` checks were both replayed:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-animation-bind-0045b880 \
        --unit fighter-bind-animation-00453d80

**Result: 2/2 independently complete whole original callables
exact, 298/298 original CODE B preserved.** The previously accepted
298B is not new authored coverage. The original Japanese EXE,
manifest and strict acceptance criteria were unchanged; no all-979
cold replay. Unmodified accepted baselines and scoped compiler
receipts reside under ignored `.analysis/f1086-animation-borrow/`.
