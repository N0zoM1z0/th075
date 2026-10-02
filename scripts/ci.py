#!/usr/bin/env python3
"""Run public function-workflow checks without a target or private database."""
from __future__ import annotations
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    try:
        for path in [*sorted((ROOT / "scripts").glob("*.py")), *sorted((ROOT / "tests").glob("*.py"))]:
            compile(path.read_text(), str(path), "exec")
        for path in sorted((ROOT / "scripts").glob("*.sh")):
            subprocess.run(["bash", "-n", str(path)], check=True)
        for command in [
            [sys.executable, "scripts/validate-tracking.py", "--skip-target-bytes"],
            [sys.executable, "scripts/build.py", "--check"],
            [sys.executable, "-m", "unittest", "discover", "-s", "tests", "-v"],
        ]:
            subprocess.run(command, cwd=ROOT, check=True)
        print("Public function-workflow checks passed.")
        return 0
    except (OSError, SyntaxError, subprocess.CalledProcessError) as exc:
        print("error: public checks failed: " + str(exc), file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
