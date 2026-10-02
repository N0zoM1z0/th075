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
        for path in [*sorted((ROOT / "scripts").glob("*.sh")), ROOT / "scripts/repo-python"]:
            subprocess.run(["bash", "-n", str(path)], check=True)
        for command in [
            [str(ROOT / "scripts/repo-python"), "scripts/validate-tracking.py", "--skip-target-bytes"],
            [str(ROOT / "scripts/repo-python"), "scripts/build.py", "--check"],
            [str(ROOT / "scripts/repo-python"), "-m", "unittest", "discover", "-s", "tests", "-v"],
        ]:
            subprocess.run(command, cwd=ROOT, check=True)
        print("Public function-workflow checks passed.")
        return 0
    except (OSError, SyntaxError, subprocess.CalledProcessError) as exc:
        print("error: public checks failed: " + str(exc), file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
