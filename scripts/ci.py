#!/usr/bin/env python3
"""Run basic syntax, ledger and whitespace checks without compiler builds."""
from pathlib import Path
import argparse
import ast
import json
import os
import subprocess
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def main():
    argparse.ArgumentParser(description=__doc__).parse_args()
    try:
        names = subprocess.check_output(
            ["git", "ls-files", "--cached", "--others", "--exclude-standard", "-z"],
            cwd=ROOT,
        ).decode().split("\0")
        for name in sorted(set(names) - {""}):
            path = ROOT / name
            if not path.is_file() or path.is_symlink():
                continue
            if path.suffix == ".py":
                ast.parse(path.read_text(encoding="utf-8"), filename=name)
            elif path.suffix == ".json":
                json.loads(path.read_text(encoding="utf-8"))
            elif path.suffix == ".toml":
                tomllib.loads(path.read_text(encoding="utf-8"))
            elif path.suffix == ".sh" or name == "scripts/repo-python":
                subprocess.run(["bash", "-n", str(path)], check=True)
        for script, flag in (("validate-tracking.py", "--skip-target-bytes"),
                             ("build.py", "--check")):
            subprocess.run([sys.executable, str(ROOT / "scripts" / script), flag],
                           cwd=ROOT, check=True)
        subprocess.run(["git", "diff", "--check", "HEAD"], cwd=ROOT, check=True)
        if os.environ.get("CI"):
            base = os.environ.get("CI_BASE", "")
            command = (["git", "diff", "--check", base, "HEAD"]
                       if base and set(base) != {"0"}
                       else ["git", "show", "--format=", "--check", "HEAD"])
            subprocess.run(command, cwd=ROOT, check=True)
        print("Basic checks passed. Run affected exact comparisons separately.")
        return 0
    except (OSError, ValueError, SyntaxError, subprocess.CalledProcessError) as exc:
        print(f"error: basic checks failed: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
