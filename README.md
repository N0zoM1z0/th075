# 東方萃夢想 ～ Immaterial and Missing Power

Agent workflow: follow the highest-priority requirements in [AGENTS.md](AGENTS.md).

<p align="center"><img src="resources/title-screen.png" width="640" alt="User-supplied TH075 title screen"></p>
<p align="center"><img src="resources/progress.svg" alt="Original authored-byte reconstruction progress"></p>

A function-by-function C++ reconstruction of the Japanese TH075 v1.11
executable, rebuilt with the original VC7.1 compiler. It is not a playable
game. A function counts only when its whole callable body, including every
relocation, cold-builds byte-identical to the original.

## Status

`scripts/repo-python scripts/report-reconstruction-status.py --summary`
prints the live numbers. At the time of writing:

| | |
| --- | --- |
| Target | user-supplied `resources/th075.exe` v1.11, SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| Exact functions | 982 (871,649 original CODE bytes) |
| Authored coverage | 44.16% of 1,973,704 bytes (44.09% counting 95 origin-unknown candidates) |
| Remaining authored functions | 22, all giant per-character `Advance` state machines (1,102,055 bytes) |

The 98% authored-byte goal is not met.

## Where to start

- [Handoff](docs/RE_HANDOFF.md): current work and next steps.
- [Giants](docs/GIANTS.md): the 22 remaining functions, their research
  parents and measured register debt.
- [Knowledge base](docs/KNOWLEDGE_BASE.md): class structure, layouts and
  VC7.1 code-generation rules.
- [Workflow](docs/RE_WORKFLOW.md) and [storage policy](docs/STORAGE_HYGIENE.md).

Source is in `src/`, organised around the classes recovered from the PE
vtables: `Actor`, `Fighter`, one `<Char>Fighter` per character and
`CharacterObject`. Research parents for the giants are in `probes/`, and
`config/match-units.toml` records every accepted unit's source, flags, extent
and relocations.

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
