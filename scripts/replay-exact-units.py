#!/usr/bin/env python3
"""Cold-build function objects and replay complete configured comparisons."""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import runpy
import struct
import subprocess
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--unit", action="append", help="unit to replay; repeatable; defaults to all")
    parser.add_argument("--batch", action="store_true", help="compile all selected objects in profile groups")
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
        reports = ROOT / ".analysis/replay"
        reports.mkdir(parents=True, exist_ok=True)
        summary = reports / "summary.json"
        summary.unlink(missing_ok=True)
        build = [str(ROOT / "scripts/repo-python"), "scripts/build.py"]
        if args.batch:
            batch_units = [value for _, name in groups.values() for value in ("--batch-unit", name)]
            subprocess.run([*build, *batch_units], cwd=ROOT, check=True)
        else:
            for _, name in groups.values():
                subprocess.run([*build, "--unit", name], cwd=ROOT, check=True)
        comparator = runpy.run_path(str(ROOT / "scripts/compare-coff-function.py"))
        inputs = comparator["load_unit_comparison"]()
        results = []
        exact = 0
        for name in selected:
            try:
                report = comparator["compare_configured_unit"](name, *inputs)
            except (OSError, KeyError, TypeError, ValueError, struct.error) as exc:
                report = {"result": "error", "error": str(exc)}
            results.append(report)
            # Fixed numeric filenames avoid treating manifest unit names as paths.
            (reports / f"unit-{len(results):04d}.json").write_text(json.dumps(report, indent=2) + "\n")
            passed = report.get("result") == "exact"
            exact += passed
            print(f"{name}: {'exact' if passed else 'FAILED'}; {report.get('size', 0)} coverage bytes")
        summary.write_text(json.dumps(results, indent=2) + "\n")
        print(f"Cold replay: {exact}/{len(results)} exact units across {len(groups)} objects")
        return 0 if exact == len(results) else 1
    except (OSError, KeyError, TypeError, ValueError, subprocess.CalledProcessError) as exc:
        print(f"error: exact replay failed: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
