# F569 — original CharacterObject parent/cooldown/sparse-dispatch C++ source

**Original Japanese TH075 1.11 PE native evidence and pinned VC7.1
source compiles; NOT entire original giant CODE exactness.**
Original SHA256:
bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98.

F567 proves all 11 distinct CharacterMove multi-switch fighters can
naturally compile real action cases 0..10. F569 works on the **other
eleven different CharacterObject giant originals, containing
488,664 total native CODE bytes**. These originals have only one
original compressed switch group, starting at action ID 0x320.
No multi-switch action0..10 C++ is mistakenly reused here.

## The genuine native prefix the compiler now reproduces

F569 independently derives normal C++ from the original first native
instructions, rather than copying a decompiler record or guessing
a game class's layout:

- A real parent pointer chain at receiver +0xE4 -> +0x2E8 -> +0x3BA
  performs the first 16-bit signed state guard.
- A separate check on parent +0x3BA combined with the *own*
  signed 16-bit +0x8A flag may return early.
- The native 10-instruction signed-short cooldown at receiver +0x82
  decrements that field and exits when nonzero.
- The actual next action dispatch reads the signed short at
  receiver +0x60, subtracts **0x320**, bounds-checks against the
  real role-specific upper index **0xC5, 0xC6 or 0xC7**,
  looks up an original byte-index table and jumps through
  the corresponding physical DWORD handler table.

This produces a normal **17-instruction parent/owner check,
10-instruction cooldown and 11-instruction sparse dispatch**
source structure for each native original context. These are
38 actual original instruction roles per giant, 418 across eleven
contexts; control-flow guards are verified separately from later
unfinished game action bodies.

## Fresh physical source/data evidence

The new tracked
[verify-characterobject-single-switch-source.py](../scripts/verify-characterobject-single-switch-source.py)
re-reads and hashes every complete original fighter, regenerates
one natural C++ Advance() using original action-to-handler IDs, then
serially fresh-compiles ONLY the selected new diagnostic source TUs
under the pinned VC7.1 /Od /Ob0 /Gy /GR- /GX- /GS /Zi profile.

The original-only proof checks:

- **11/11 true parent-state guards** have exactly the authentic
  original 17 x86 instruction/operand/branch roles, after normalizing
  only saved receiver EBP slot and equivalent within-block branch
  target addresses.
- **11/11 10-instruction native cooldown control/dataflow policies**,
  with 10/11 matching exact original EAX/ECX/EDX allocation. The
  different 00536400 allocation is not silently called byte-exact.
- **11/11 original 11-instruction compressed single-table dispatch
  codegen policies**, preserving signed input, 0x320 subtraction,
  original role-specific bound 0xC5/0xC6/0xC7, index register
  dataflow and indirect jump. **9/11 match exact native GPR selection**.
  On 00536400 the real source has additional pre-dispatch game logic
  changing register assignment, which this source probe has not
  recreated.
- **752/752 genuine DIR32 physical COFF jump-label fields**,
  each with zero native COFF addend, all original default and repeated
  handler destination equivalence partitions, **2,185
  byte-identical original sparse index bytes** with original SHA,
  and the full **5,193 after-RET DATA-shape bytes**. This is DATA,
  NOT CODE credit.

Original 0050A580 has a true wide EBP-0xAC receiver frame
and EBP-0xB0 action state. It uses 3 widened owner reads in the
guard, 3 in cooldown and 6 in the dispatcher: the original
11-instruction dispatch is **70 bytes versus the small probe's
52 bytes**, explained exactly by the 6 actual disp32 saved-owner/state
loads at +3 bytes each. Another register-allocation difference in
this original context is recorded separately and remains unresolved.

| Original CharacterObject giant | Original whole CODE still unmatched | Concrete switch action IDs (marker stores only) | Native GPR dispatch allocation exact? | Physical jump COFF fields | Original literal sparse bytes |
| --- | ---: | ---: | --- | ---: | ---: |
| 0x00476A40 | 50,915 | 65 | Yes | 66 | 199 |
| 0x0049C8F0 | 46,596 | 75 | Yes | 76 | 199 |
| 0x004CA6E0 | 42,511 | 55 | Yes | 56 | 198 |
| 0x004EBDA0 | 33,293 | 59 | Yes | 60 | 198 |
| 0x0050A580 | 81,539 | 91 | No (register dataflow checked) | 92 | 199 |
| 0x00536400 | 39,999 | 66 | No (register dataflow checked) | 67 | 199 |
| 0x0055AC80 | 28,432 | 57 | Yes | 58 | 198 |
| 0x0057D580 | 43,845 | 70 | Yes | 71 | 198 |
| 0x005A1600 | 43,599 | 76 | Yes | 77 | 200 |
| 0x005C9CC0 | 43,501 | 67 | Yes | 68 | 198 |
| 0x005EB520 | 34,434 | 60 | Yes | 61 | 199 |

## Important limitation and targeted reproduction

The 741 source switch labels are explicitly **diagnostic-only
marker-store placeholders**, selected from the original physical
handler-to-action map. They are **NOT 741 reconstructed game action
bodies**. Some native original fighters have extensive additional
gameplay behavior *before* their one-switch dispatcher (notably
00536400) which this new prototype has not restored. The complete
11 functions totaling **488,664 native CODE bytes are still nonexact**
and uncredited, even though their actual native prefix and physical
jump DATA are verified.

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-fighter-boss-family.py
    scripts/repo-python scripts/verify-characterobject-single-switch-source.py --boss 0x0050A580
    # Or build the eleven newly affected, source-only TUs serially:
    scripts/repo-python scripts/verify-characterobject-single-switch-source.py

Fresh normal C++/OBJ/PDB, compiler and case-data summaries are retained
under ignored .analysis/f569-characterobject-original-source/.
Native original disassembly, initial negative controls and original
register-difference studies remain under .analysis/f569-characterobject/.
**No accepted whole original giant CODE/DATA, no invented exact
action bodies, no all-unit cold replay and no external Oracle receipt.**
