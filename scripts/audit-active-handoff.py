#!/usr/bin/env python3
"""Read-only consistency audit for current TH075 agent-facing documentation.

The source of truth is live tracking and original provenance. Does not hardcode
an exact progress count, alter files, build code or run any cold replay.
Historical research journals may contain explicitly superseded snapshots.
"""
from __future__ import annotations

import csv
from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def text_file(path: str) -> str:
    return (ROOT / path).read_text()


def expect(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def check_local_markdown_links(relative_path: str) -> None:
    """Prevent active/archived documentation moves breaking relative links.

    Only Markdown local file paths are checked; URLs/anchors are not
    pretext for external network access or historical content edits.
    """
    doc = ROOT / relative_path
    source = doc.read_text()
    for match in re.finditer(r'\]\(([^)]+)\)', source):
        target = match.group(1)
        if not target or target.startswith(('http://', 'https://', 'mailto:', '#')):
            continue
        path = target.split('#',1)[0]
        expect((doc.parent / path).exists(),
               f'Broken local Markdown link in {relative_path}: {target}')


def main() -> None:
    with (ROOT / 'config/functions.csv').open(newline='') as f:
        rows = list(csv.DictReader(f))
    # `functions.csv.owner` only identifies the 25 formerly investigated
    # negative cases; 11 other independently authored small/medium rows
    # deliberately have blank owner while their source is still missing.
    # Authorship is authoritative in function-origins.csv, NOT this field.
    with (ROOT / 'config/function-origins.csv').open(newline='') as f:
        origins = {x['address']:x for x in csv.DictReader(f)}
    expect(all(x['address'] in origins for x in rows),
           'Native candidate missing an independent origin decision')
    accepted = [x for x in rows if x['status'] == 'matching']
    authored = [x for x in rows if origins[x['address']]['origin'] == 'authored']
    pending = [x for x in authored if x['status'] != 'matching']
    expect(len(authored) == len(accepted) + len(pending)
           and all(origins[x['address']]['origin'] == 'authored' for x in accepted),
           'Accepted game CODE or independent authored backlog conflicts with origin ledger')
    giants = [x for x in pending if int(x['size']) >= 20000]
    exact_count = len(accepted)
    exact_bytes = sum(int(x['size']) for x in accepted)
    sizesum = sum(int(x['size']) for x in giants)
    by_address = {x['address']: x for x in rows}
    expect(len(giants) >= 1, 'No big-boss cohort; re-audit documentation instead of assuming old backlog')

    report = subprocess.run([str(ROOT / 'scripts/repo-python'),
                             str(ROOT / 'scripts/report-reconstruction-status.py'),
                             '--summary'], capture_output=True, text=True, check=True, cwd=ROOT).stdout
    status = re.search(r'Reconstruction: mapped (\d+), source (\d+), exact (\d+) \((\d+) bytes\), units (\d+)', report)
    expect(status is not None, 'Reconstruction status output changed')
    expect(int(status.group(3)) == exact_count and int(status.group(4)) == exact_bytes,
           'Current canonical status conflicts with live functions.csv')
    cover = re.search(r'Authored bytes: (\d+)/(\d+) exact \((\d+\.\d+)%', report)
    expect(cover is not None and int(cover.group(1)) == exact_bytes,
           'Failed to recover live authored-byte percentage')
    percent = cover.group(3)
    denominator = int(cover.group(2))
    conservative = re.search(r'Conservative authored coverage: (\d+\.\d+)%', report)
    expect(conservative is not None, 'No conservative coverage')

    handoff = text_file('docs/RE_HANDOFF.md')
    readme = text_file('README.md')
    kb = text_file('docs/KNOWLEDGE_BASE.md')
    expect(f'**{exact_count} functions / {exact_count} exact units**' in handoff,
           'Current handoff exact count stale')
    expect(f'**{denominator:,}**' in handoff and f'{denominator:,}' in readme,
           'Current reviewed authored-byte denominator stale')
    expect(f'**{exact_bytes:,} original CODE bytes**' in handoff,
           'Current handoff accepted CODE stale')
    expect(f'**{percent}%**' in handoff and f'**{conservative.group(1)}%**' in handoff,
           'Current handoff coverage numbers stale')
    medium = [x for x in pending if int(x['size']) < 20000]
    medium_bytes = sum(int(x['size']) for x in medium)
    expect(f'**{len(authored):,}**' in handoff and
           f'**{len(pending)} authored functions remain nonexact**' in handoff and
           f'**{len(giants)} large original state advances**' in handoff and
           f'**{len(medium)} other original small/medium whole functions**' in handoff,
           'Current handoff is missing the complete origin-backed backlog; '
           'do not use only functions.csv.owner')
    expect(f'**{sizesum:,} CODE bytes**' in handoff and
           f'**{medium_bytes:,} CODE bytes**' in handoff,
           'Current handoff original large/small pending CODE bytes stale')
    expect(f'**{len(pending)}**' in readme and f'**{len(giants)}**' in readme
           and f'**{len(medium)}**' in readme,
           'README must show the entire independently authored pending backlog')
    expect(f'**{exact_count} / {exact_count}**' in readme and f'**{exact_bytes:,}**' in readme,
           'README exact count/CODE stale')
    expect(f'**{percent}%**' in readme and f'**{conservative.group(1)}%**' in readme,
           'README coverage stale')
    expect(f'**{exact_count} cold-exact source-present functions**' in kb and
           f'**{exact_bytes:,} original authored' in kb,
           'Knowledge base first-screen current status stale')
    expect('**historical**' in kb[:1200] or 'chronological experiment log' in kb[:1200],
           'Knowledge base must warn that later text is historical')
    expect('Truly **nonexact** current work includes' not in kb[:4000],
           'Knowledge base front still has false current nonexact claims')
    expect(Path(ROOT / 'docs/STORAGE_HYGIENE.md').exists() and
           'docs/STORAGE_HYGIENE.md' in readme,
           'Storage recovery link missing')
    for doc in ('README.md', 'docs/RE_HANDOFF.md',
                'docs/STORAGE_HYGIENE.md',
                'docs/history/RE_HANDOFF_F653_THROUGH_F753_2026-10-30.md'):
        check_local_markdown_links(doc)
    expect('scripts/archive-frozen-giant-traces.py' in readme and
           'archive-frozen-giant-traces.py' in handoff,
           'Current local frozen-trace archive/restore path absent from agent-facing docs')

    accepted_previous = ('0x00425130', '0x0042C270', '0x0042B110',
                         '0x00431890', '0x00438C20', '0x00411110',
                         '0x005C3FB0', '0x005F7D80', '0x00435870',
                         '0x00410A00', '0x004183D0')
    for address in accepted_previous:
        expect(by_address[address]['status'] == 'matching',
               f'Formerly disputed full original function no longer exact: {address}')
    for x in medium:
        expect(x['address'][2:].lower() in handoff.lower() and f'{int(x["size"]):,}' in handoff,
               f'One currently pending medium authored function is missing from active handoff: {x["address"]}')
    print(f'Agent docs concordant: {exact_count} exact whole functions, '
          f'{exact_bytes:,} original CODE bytes ({percent}% reviewed); '
          f'{len(authored)} independently authored original candidates, '
          f'{len(pending)} ALL still nonexact: '
          f'{len(giants)} giant ({sizesum:,} CODE B) + '
          f'{len(medium)} other whole functions ({medium_bytes:,} CODE B). '
          'No cold replay or files modified.')


if __name__ == '__main__':
    try:
        main()
    except (RuntimeError, KeyError) as error:
        print(f'ACTIVE-HANDOFF AUDIT FAILED: {error}', file=sys.stderr)
        raise SystemExit(1)
