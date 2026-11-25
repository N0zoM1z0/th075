# 東方萃夢想 ～ Immaterial and Missing Power

Agent workflow: follow the highest-priority requirements in [AGENTS.md](AGENTS.md).

<p align="center"><img src="resources/title-screen.png" width="640" alt="User-supplied TH075 title screen"></p>
<p align="center"><img src="resources/progress.svg" alt="Original authored-byte reconstruction progress"></p>

A function-by-function C++ reconstruction of the Japanese TH075 v1.11
executable, rebuilt with the original VC7.1 compiler. A function counts only
when its whole callable body, including every
relocation, cold-builds byte-identical to the original.

## Status

`scripts/repo-python scripts/report-reconstruction-status.py --summary`
prints the live exact coverage and origin counts. The conservative
coverage exceeds the 98% authored-byte goal. All per-character fighter
and object `Advance` methods have exact units. The stage base constructor
is the remaining independently authored function awaiting a cold exact
source unit. Pending function origins are reviewed separately.

## Where to start

- [Handoff](docs/RE_HANDOFF.md) with current work and blockers
- [Advance reconstruction](docs/GIANTS.md) with the accepted source index and compiler evidence
- [Pending origin evidence](docs/ORIGIN_PENDING_REVIEW.md#r288--remaining-origin-evidence)
- [Knowledge base](docs/KNOWLEDGE_BASE.md), [workflow](docs/RE_WORKFLOW.md) and [storage policy](docs/STORAGE_HYGIENE.md)

The C++ sources are in `src/` and `probes/`. `config/match-units.toml`
records the exact units, compiler flags, extents and relocations. The target
is the Japanese TH075 v1.11 `resources/th075.exe` supplied by the user. See
the handoff for its pinned identity.

## Build

Build the configured translation units as a Windows x86 COFF library:

    scripts/repo-python scripts/build.py --library

This writes `build/program/th075.lib` and the compiler and librarian logs
under `build/program/`. The build uses the manifest's per-source flags,
the pinned VC7.1 toolchain and the game's headless Factory Wine prefix.

Build the Windows x86 executable:

    scripts/repo-python scripts/build.py --program

This writes `build/program/th075.exe`, `build/program/th075.map` and
`build/program/link.log`. Both aggregate builds use the pinned original
executable in `resources/` to supply the remaining read-only data. See
the [handoff](docs/RE_HANDOFF.md) for build details.

For a runtime check, stage the executable beside `th075.dat`,
`th075bgm.dat`, and `th075b.dat` from the Japanese installation.
Create a writable `replay/` directory beside them. Story mode opens
`replay/replay.tmp` before loading the first battle.
[Runtime and position independence checks](docs/POSITION_INDEPENDENCE.md)

## Checks

Read-only preflight:

    git status --short --branch
    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/ghidra.py check

Accept or re-verify a function with a cold build and complete comparison;
pass several `--unit` flags to build each shared object once:

    scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME

`scripts/repo-python scripts/ci.py` checks syntax, tracking and build
manifests and whitespace without a compiler. Replay only new or affected
units, keep compiler builds serial, and never substitute `th075c.exe`.
