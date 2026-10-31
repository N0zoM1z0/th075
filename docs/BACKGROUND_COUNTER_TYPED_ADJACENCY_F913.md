# F913 — Typed adjacent animation-counter window, eleven native leaves preserved

**Original Japanese TH075 v1.11**, verified against the pinned
native PE, not simply historical C++ comments.

An independent family of **eleven already-accepted whole leaf
functions** manipulates signed 32-bit background animation state
at receiver offset **+0x68**; the original callback
`00450BD0` additionally advances a second signed 32-bit
frame field at **+0x6C**, which wraps at 71. The native
physical x86 accesses at 00450BDA/00450BE9/00450BF8,
for example, directly prove these offsets and element
widths. The counter bodies cover simple tick increments,
the wrap cases 360/2,500/15,360, a 71-frame pair and a
reverse wrap to 3,840; they are not one generic reconstructed
function or independent afterRET subcases.

The former exact source at
[`BackgroundCountersF180.cpp`](../src/BackgroundCountersF180.cpp)
used separate raw `reinterpret_cast<int*>` expressions
for receiver+0x68 and receiver+0x6C. F913 retains the
**one honest +0x68 owner boundary**, but borrows a
minimal two-member *tail view* with two genuine
observed int fields:

    struct BackgroundCounterWindowF913 {
        int animationTick;
        int animationFrame;
    };

The frame now refers to element one of the same natural
8-byte counter window, not a disconnected raw offset.
A compile-time sizeof check enforces two contiguous
four-byte members. The original complete class owner
remains **unknown** and the borrowed two-field view is
neither allocated nor embedded as a fake complete object.

The affected file emits eleven complete original
functions, including two physical floating-point
comparison/constant relocations. **Only these eleven
already-accepted units** were cold-compiled using the
canonical `replay-exact-units.py --unit` (one shared
object) after the source edit. The true original PE
and all per-unit COFF relocation contents were checked:

| Actual affected native callback set | Whole units | Whole CODE B |
| --- | ---: | ---: |
| Four ordinary tick increments | 4 | 104 |
| Three 360-tick wrapping callbacks | 3 | 144 |
| Two original floating-point threshold callbacks | 2 | 110 |
| One tick+71-frame callback | 1 | 60 |
| One reverse cycle | 1 | 45 |
| **Affected canonical exact cold replay** | **11/11 exact** | **463** |

No accepted exact whole-function credit was lost,
and no new exact original was claimed; this is a
genuine semantic-source improvement to **463 already
accepted byte-exact native CODE bytes**. It does not
change the original game EXE or the canonical
`match-units.toml`/matches/origin ledgers.

Reproduce only the affected units:

    scripts/repo-python scripts/replay-exact-units.py \
      --unit background-counter-00449ec0 \
      --unit background-counter-0044da70 \
      --unit background-counter-0044f830 \
      --unit background-counter-00451420 \
      --unit background-counter-0044b600 \
      --unit background-counter-0044bb20 \
      --unit background-counter-0044c040 \
      --unit background-counter-0044d5e0 \
      --unit background-counter-004503e0 \
      --unit background-counter-00450bd0 \
      --unit background-counter-0044e3a0

The original full native exact unit receipts and
compiler transcript are retained locally under
`.analysis/f913-background-counter-view/`. No other
969 original accepted units or any whole-boss cold
replay was triggered.
