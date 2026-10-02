#!/usr/bin/env python3
"""Cold-build function objects and replay complete configured comparisons."""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import subprocess
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--unit", action="append", help="unit to replay; repeatable; defaults to all")
    args = parser.parse_args()
    try:
        with (ROOT / "config/match-units.toml").open("rb") as stream:
            units = tomllib.load(stream)["units"]
        selected = sorted(set(args.unit or units))
        if not selected:
            raise ValueError("no units configured; no exact coverage can be claimed")
        groups = {}
        for name in selected:
            unit = units[name]
            key = str(unit["object"])
            shape = (unit["source"], tuple(unit["profile"]))
            if key in groups and groups[key][0] != shape:
                raise ValueError("conflicting sources/profiles share object " + key)
            groups[key] = (shape, name)
        for _, name in groups.values():
            subprocess.run([str(ROOT / "scripts/repo-python"), "scripts/build.py", "--unit", name], cwd=ROOT, check=True)
        reports = ROOT / ".analysis/replay"
        reports.mkdir(parents=True, exist_ok=True)
        results = []
        for name in selected:
            completed = subprocess.run(
                [str(ROOT / "scripts/repo-python"), "scripts/compare-coff-function.py", "--unit", name, "--json"],
                cwd=ROOT, capture_output=True, text=True,
            )
            report = json.loads(completed.stdout)
            results.append(report)
            # Fixed numeric filenames avoid treating manifest unit names as paths.
            (reports / f"unit-{len(results):04d}.json").write_text(json.dumps(report, indent=2) + "\n")
            passed = completed.returncode == 0 and report.get("result") == "exact"
            print(f"{name}: {'exact' if passed else 'FAILED'}; {report.get('size', 0)} coverage bytes")
        (reports / "summary.json").write_text(json.dumps(results, indent=2) + "\n")
        exact = sum(report.get("result") == "exact" for report in results)
        print(f"Cold replay: {exact}/{len(results)} exact units across {len(groups)} objects")
        return 0 if exact == len(results) else 1
    except (OSError, KeyError, TypeError, ValueError, subprocess.CalledProcessError) as exc:
        print(f"error: exact replay failed: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
