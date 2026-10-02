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
        [sys.executable, str(ROOT / "scripts/report-reconstruction-status.py"), "--summary", "--json"],
        cwd=ROOT, text=True))["summary"]
    count = status["candidates"]
    exact = status["exact_functions"]
    reviewed = count - status["review"]
    ratio = 100 * exact / count if count else 0
    review_ratio = 100 * reviewed / count if count else 0
    svg = f'''<svg xmlns="http://www.w3.org/2000/svg" width="560" height="194" role="img" aria-label="TH075: {exact:,} exact functions, {status['exact_bytes']:,} exact bytes; {reviewed:,} of {count:,} candidates reviewed">
  <rect width="560" height="194" rx="8" fill="#1f2335"/>
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
  <text x="24" y="179" fill="#a0a5ba" font-family="sans-serif" font-size="11">Authored-function denominator unknown; candidates include runtime and library code.</text>
</svg>
'''
    destination = ROOT / "resources/progress.svg"
    if "--check" in sys.argv[1:]:
        if not destination.exists() or destination.read_text() != svg:
            print("error: progress.svg is stale; run scripts/update-progress.py", file=sys.stderr)
            return 1
    else:
        destination.parent.mkdir(exist_ok=True)
        destination.write_text(svg)
    print(f"Progress card: {exact}/{count} exact candidates, {status['exact_bytes']} bytes.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
