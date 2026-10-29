# F537 — native action-ID to whole-fighter-boss handler mapping

**Status: entire original-Japanese 1.11 PE research, not reconstructed C++.**
This resolves *which complete original native instruction receives a given
input action ID*, independently for **all 22** unaccepted giant fighters.
It does **not** claim source ownership or any matched CODE/after-RET DATA.
The exact game binary, not a decompiler or an old hypothesis, is the authority:
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Original function dispatch has been fully resolved

The read-only [`report-fighter-action-handlers.py`](../scripts/report-fighter-action-handlers.py)
validates each **entire original 28K–82K-byte CODE extent** against its
independently frozen SHA256, Capstone instruction boundaries/sole final RET,
every in-CODE indexed `JMP DWORD PTR`, all actual dense table DWORDs and
compressed sparse-index bytes with their original SHA256, each target's
real instruction boundary, and each complete contiguous after-RET DATA
SHA256. Unlike the earlier table inventory, it **also decodes actual
`SUB`, `MOV`, `CMP`, `JA`, `MOVZX`, and `JMP` operands** to recover action-ID
base, unsigned upper bound, original stack slot and original default
branch. It rejects divergent table bounds, guard sources, index registers,
default branches, overlapping action IDs, missing slots or bad destinations.
All isolated equality actions are separately read from actual native
`CMP [state], id; JE entry` instruction pairs and verified within CODE.

Across 22 complete original bosses there are:

- **7,088** per-ID indexed mappings: **6,687** from the compressed byte-index
  maps and **401** via direct DWORD dispatch (not 7,088 distinct handlers).
- **64** independent native singleton equality branches outside those ranges.
- **7,152 total** unique per-boss action-ID to native-entry mappings,
  which may repeat a destination for multiple IDs.
- **4,847 indexed action IDs** lead to the same physical native default
  instruction as the corresponding `JA` out-of-range guard. Hence just
  **2,241 indexed IDs** enter a nondefault native target; many large sparse
  arrays intentionally collapse otherwise different inputs. These are
  *action inputs*, not separate C++ functions or bytes matched.
- Still **1,102,055 unaccepted authored CODE bytes** (292,761 instructions,
  16,861 native calls) and **16,123 original post-RET DATA bytes** (2,359
  DWORD slots + 6,687 sparse-index bytes). None is exact CODE credit.

## Independently verified per-boss dispatch coverage

| Whole native function | Original CODE | Indexed IDs | Singleton IDs | Indexed IDs to JA default | Actual native entry for out-of-range JA |
| --- | ---: | ---: | ---: | ---: | --- |
| `0x0045DD70` | 60,999 | 543 | 5 | 405 | `0x0046CB88` |
| `0x00476A40` | 50,915 | 199 | 0 | 134 | `0x00483116` |
| `0x00486550` | 50,735 | 462 | 6 | 310 | `0x00492B51` |
| `0x0049C8F0` | 46,596 | 199 | 0 | 124 | `0x004A7EE7` |
| `0x004AC040` | 82,796 | 543 | 5 | 397 | `0x004C037D` |
| `0x004CA6E0` | 42,511 | 198 | 0 | 143 | `0x004D4CE2` |
| `0x004D7E70` | 43,601 | 458 | 6 | 333 | `0x004E2893` |
| `0x004EBDA0` | 33,293 | 198 | 0 | 139 | `0x004F3FA1` |
| `0x004F7130` | 44,211 | 461 | 6 | 334 | `0x00501DB5` |
| `0x0050A580` | 81,539 | 199 | 0 | 108 | `0x0051E3F4` |
| `0x005214B0` | 46,755 | 379 | 6 | 245 | `0x0052CB25` |
| `0x00536400` | 39,999 | 199 | 0 | 133 | `0x00540033` |
| `0x00543210` | 58,294 | 380 | 6 | 239 | `0x00551598` |
| `0x0055AC80` | 28,432 | 198 | 0 | 141 | `0x00561B83` |
| `0x00564BE0` | 61,872 | 371 | 6 | 246 | `0x00573D56` |
| `0x0057D580` | 43,845 | 198 | 0 | 128 | `0x005880B8` |
| `0x0058AF60` | 49,230 | 386 | 6 | 246 | `0x00596F80` |
| `0x005A1600` | 43,599 | 200 | 0 | 124 | `0x005AC043` |
| `0x005AEEC0` | 71,616 | 458 | 6 | 306 | `0x005C0652` |
| `0x005C9CC0` | 43,501 | 198 | 0 | 131 | `0x005D46A1` |
| `0x005D73C0` | 43,282 | 462 | 6 | 342 | `0x005E1CA4` |
| `0x005EB520` | 34,434 | 199 | 0 | 139 | `0x005F3B96` |

Every table's normalized **inclusive action range**, physical jump site,
original native EBP stack state slot, used case-slot count, and *actual*
32-bit handler locations are available in the JSON and CSV outputs below.
The CSV's `kind=singleton` entries have no DWORD slot; their `table`
column is the actual original `JE` instruction address. A table case that
reaches the same JA-default target is not a distinct C++ case implementation.

## Two whole large-function control-flow consequences

Reimu's `0045DD70..0046CBB6` function (60,999 CODE bytes) has six indexed
switches with **543 indexed IDs**, **five singleton IDs**, and **405 indexed
inputs sent to native default**. One genuinely indexed input is action
`0x254`; its final special singleton is `0x25B`. The full original
82,796-byte CharacterMove function `004AC040..004C03AB` likewise has
**543 indexed IDs**, **five singleton IDs**, and **397 indexed inputs sent
to native default**, but it reverses the distinction: `0x254` is a
native equality branch, while `0x25B` is an indexed action. Both have
**exactly the same set of 548 explicitly in-range or separately compared input IDs** (this fact was
recovered by joining the native mapped and singleton input sets, not by
assuming they have interchangeable source logic). All their 548 native
case-entry addresses differ, as their original code bodies are distinct.

The shared 68-byte `0x08F..0x0D2` sparse-index map agrees for **all 68
inputs** and both bosses, but its physical DWORD target tables and their
code bodies are independent. Likewise 7-switch families partition some
inputs into additional `0x1F5..` and later ranges; their individual
base/upper bounds and sentinel action IDs vary. **Do not copy source
switch ranges or handlers blindly from one fighter to another.**

### Original PE samples (full physical action-to-destination witnesses)

| Function / action ID | Original dispatch | Exact native destination |
| --- | --- | --- |
| `0x0045DD70` / `0x000` | dense, `0x0045DDCB` slot 0 | `0x0045DEE9` |
| `0x0045DD70` / `0x032` | singleton, `0x0045DDB8` | `0x0045E74A` |
| `0x0045DD70` / `0x036` | sparse, `0x0045DE05` slot 25 | `0x0046CB88` |
| `0x0045DD70` / `0x08f` | sparse, `0x0045DE42` slot 0 | `0x004608BB` |
| `0x0045DD70` / `0x254` | sparse, `0x0045DEB8` slot 27 | `0x00467F10` |
| `0x0045DD70` / `0x25b` | singleton, `0x0045DE8F` | `0x004685B8` |
| `0x004AC040` / `0x000` | dense, `0x004AC09B` slot 0 | `0x004AC1B9` |
| `0x004AC040` / `0x032` | singleton, `0x004AC088` | `0x004ACA6C` |
| `0x004AC040` / `0x036` | sparse, `0x004AC0D5` slot 26 | `0x004C037D` |
| `0x004AC040` / `0x08f` | sparse, `0x004AC112` slot 0 | `0x004AEAFB` |
| `0x004AC040` / `0x254` | singleton, `0x004AC15F` | `0x004B7825` |
| `0x004AC040` / `0x25b` | sparse, `0x004AC1B2` slot 6 | `0x004B84BA` |
| `0x00476A40` / `0x320` | sparse, `0x00476AEB` slot 0 | `0x00476AF2` |
| `0x00476A40` / `0x3e6` | sparse, `0x00476AEB` slot 64 | `0x00482E6F` |

Original entry destinations can be individual action handlers, shared
fall-through blocks, or the same physical default branch: this table by
itself does not prove separate C++ `case` bodies or their variable names.

## F539 natural C++ generation follow-up

A separate pinned VC7.1 compiler experiment has now recovered both
**325-byte / 66-instruction native dispatch shapes** from a single natural
C++ `switch` (143/151 explicit case IDs). All 522 sparse-map bytes per
boss, all 142/151 physical COFF DWORD slots and default-target partitioning
match the original; **the large case bodies themselves are still nonexact**.
See [the full native switch codegen probe](FIGHTER_SWITCH_CODEGEN_RECONSTRUCTION.md)
and run `scripts/repo-python scripts/verify-fighter-natural-switch-probes.py`.

## Reproduction, including complete 7,152-row index

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-boss-family.py
scripts/repo-python scripts/report-fighter-action-handlers.py
scripts/repo-python scripts/report-fighter-action-handlers.py --boss 0x0045DD70
scripts/repo-python scripts/report-fighter-action-handlers.py --boss 0x004AC040 --json
mkdir -p .analysis/f537-fighter-actions
scripts/repo-python scripts/report-fighter-action-handlers.py \
  --csv .analysis/f537-fighter-actions/whole-original-action-handlers.csv
sha256sum .analysis/f537-fighter-actions/whole-original-action-handlers.csv
```

The reproducible CSV has **7,152 rows** plus its six-column header,
ordered by native boss, native table and ascending ID within each
range, followed by ascending singleton IDs per boss. Its SHA256 is
`3a265d8d4c44fe0672fb8f8184bce18775d36a80ad4707134ed5b3ccc6e08b08`. The large generated index lives
under ignored `.analysis/`; the read-only analysis script and this
source-facing explanation are tracked. This avoids embedding a second
unreviewed 7,152-row frozen truth store in the repository.

**Next source milestone:** reconstruct the original, *complete* natural
C++ state and action logic, including local lifetimes, x87 expressions,
actual conditions and all action handlers, for at least one whole giant.
The mapping makes every branch's original native entry explicit and
finds the many default/sentinel entries, but **does not** replace a
full-function byte-accurate object. No giant boss cold-built or credited,
no hand-authored target ASM, no truncated function, no full replay and
no external Oracle receipt.
