"""Run the origin and library-review verifiers against the real evidence.

usage: scripts/repo-python scripts/check-origins.py [SUBSTRING ...]

Without arguments, runs every scripts/verify-*.py that no other script loads
(the target and Python-environment checks excepted). Many of the loaded ones
serve only as shared code now: on their own they still compare frozen ledger
snapshots or need CRT sources the shared toolchain lacks, and fail. A
SUBSTRING runs every verifier whose name contains it, loaded or not.
Verifiers run one at a time because several cold-build probes. Prints one
line per verifier and a summary; exits nonzero if any fails. Run it when you
change origin evidence, a verifier or a library such as coff_data.py;
routine function acceptance does not need it.
"""
from __future__ import annotations

import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
NOT_ORIGIN = {"verify-target.py", "verify-python-env.py"}


def verifiers(filters: list[str]) -> list[Path]:
    paths = sorted(p for p in (ROOT / "scripts").glob("verify-*.py") if p.name not in NOT_ORIGIN)
    if filters:
        return [p for p in paths if any(f in p.name for f in filters)]
    loaded = set()
    for script in (ROOT / "scripts").glob("*.py"):
        loaded.update(set(re.findall(r"verify-[a-z0-9-]+\.py", script.read_text())) - {script.name})
    return [p for p in paths if p.name not in loaded]


def main(argv: list[str]) -> int:
    paths = verifiers(argv)
    if not paths:
        print("no verifier matches " + " ".join(argv), file=sys.stderr)
        return 2
    failed = []
    for path in paths:
        start = time.monotonic()
        run = subprocess.run([str(ROOT / "scripts/repo-python"), str(path)], cwd=ROOT,
                             capture_output=True, text=True)
        lines = (run.stdout + run.stderr).strip().splitlines() or [""]
        status = "ok  " if run.returncode == 0 else "FAIL"
        print(f"{status} {path.name} ({time.monotonic() - start:.1f}s): {lines[-1][:120]}",
              flush=True)
        if run.returncode:
            failed.append(path.name)
    print(f"{len(paths) - len(failed)} of {len(paths)} verifiers passed")
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
