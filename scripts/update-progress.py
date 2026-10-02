#!/usr/bin/env python3
"""Render the README progress card from the canonical reconstruction ledgers."""
from __future__ import annotations

import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    status = json.loads(subprocess.check_output(
        [str(ROOT / "scripts/repo-python"), str(ROOT / "scripts/report-reconstruction-status.py"), "--summary", "--json"],
        cwd=ROOT, text=True))["summary"]
    count = status["candidates"]
    exact = status["exact_functions"]
    reviewed = count - status["review"]
    ratio = 100 * exact / count if count else 0
    review_ratio = 100 * reviewed / count if count else 0
    authored_ratio = status["authored_exact_percent"] or 0
    authored_label = "Confirmed authored bytes" if status["origin_review_complete"] else "Reviewed authored bytes (provisional set)"
    goal_label = "Goal achieved" if status["fifty_percent_goal_complete"] else "Goal incomplete: all origins reviewed and at least 50% authored bytes exact."
    svg = f'''<svg xmlns="http://www.w3.org/2000/svg" width="560" height="258" role="img" aria-label="TH075: {exact:,} exact functions, {status['exact_bytes']:,} exact bytes; {reviewed:,} of {count:,} candidates reviewed; {goal_label}">
  <rect width="560" height="258" rx="8" fill="#1f2335"/>
  <text x="24" y="28" fill="#f4f4f5" font-family="sans-serif" font-size="16" font-weight="600">TH075 function reconstruction</text>
  <text x="24" y="52" fill="#f4f4f5" font-family="sans-serif" font-size="13" font-weight="600">Exact functions / all provisional candidates</text>
  <text x="536" y="52" fill="#f4f4f5" text-anchor="end" font-family="monospace" font-size="13">{ratio:.2f}%</text>
  <rect x="24" y="60" width="512" height="12" rx="6" fill="#3b4058"/>
  <rect x="24" y="60" width="{512 * ratio / 100:.2f}" height="12" rx="6" fill="#9b6de3"/>
  <text x="24" y="89" fill="#c8cad2" font-family="sans-serif" font-size="12">{exact:,} exact functions · {status['exact_bytes']:,} exact bytes · cold-build verified</text>
  <text x="24" y="116" fill="#f4f4f5" font-family="sans-serif" font-size="13" font-weight="600">Origin reviewed</text>
  <text x="536" y="116" fill="#f4f4f5" text-anchor="end" font-family="monospace" font-size="13">{review_ratio:.2f}%</text>
  <rect x="24" y="124" width="512" height="12" rx="6" fill="#3b4058"/>
  <rect x="24" y="124" width="{512 * review_ratio / 100:.2f}" height="12" rx="6" fill="#9b6de3"/>
  <text x="24" y="153" fill="#c8cad2" font-family="sans-serif" font-size="12">{reviewed:,} / {count:,} candidates · {status['review']:,} pending</text>
  <text x="24" y="180" fill="#f4f4f5" font-family="sans-serif" font-size="13" font-weight="600">{authored_label}</text>
  <text x="536" y="180" fill="#f4f4f5" text-anchor="end" font-family="monospace" font-size="13">{authored_ratio:.2f}%</text>
  <rect x="24" y="188" width="512" height="12" rx="6" fill="#3b4058"/>
  <rect x="24" y="188" width="{512 * authored_ratio / 100:.2f}" height="12" rx="6" fill="#9b6de3"/>
  <text x="24" y="217" fill="#c8cad2" font-family="sans-serif" font-size="12">{status['exact_authored_bytes']:,} / {status['authored_bytes']:,} reviewed authored bytes exact</text>
  <text x="24" y="243" fill="#a0a5ba" font-family="sans-serif" font-size="11">{goal_label}</text>
</svg>
'''
    destination = ROOT / "resources/progress.svg"
    if "--check" in sys.argv[1:]:
        if not destination.exists() or destination.read_text() != svg:
            print("error: progress.svg is stale; run scripts/repo-python scripts/update-progress.py", file=sys.stderr)
            return 1
    else:
        destination.parent.mkdir(exist_ok=True)
        destination.write_text(svg)
    print(f"Progress card: {exact}/{count} exact candidates, {status['exact_bytes']} bytes.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
