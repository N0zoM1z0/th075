"""Reconcile historical runtime snapshots against the bounded R120 acceptance.

This only updates ledger expectations. Callers still replay their complete
historical source, target bytes, relocation fields, and independent controls.
"""
from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TARGET = 'bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98'
ROOT_CONFIDENCE = 'complete-vendor-runtime-cycle-with-code-data-api-eh-provenance'
LABEL_CONFIDENCE = 'complete-interior-label-of-reviewed-vendor-parent'


def manifest():
    result = json.loads((ROOT / 'config/runtime-cycle-origin-evidence.json').read_text())
    if result['evidence_id'] != 'R120' or result['target_sha256'] != TARGET:
        raise ValueError('runtime reconciliation loses its bounded target identity')
    return result


def same_source(old, new):
    for key in ('address', 'coff_symbol', 'size', 'span_end', 'member_offset',
                'member', 'member_sha256', 'source_sha256', 'body_sha256'):
        if old[key] != new[key]:
            raise ValueError('historical runtime source identity differs: ' + key)
    keys = ('offset', 'type', 'symbol', 'addend', 'target_address')
    if ([tuple(b[k] for k in keys) for b in old['relocation_bindings']] !=
            [tuple(b[k] for k in keys) for b in new['relocation_bindings']]):
        raise ValueError('historical runtime complete relocation provenance differs')
    for a, b in zip(old['relocation_bindings'], new['relocation_bindings']):
        if 'local_symbol_offset' in a and a['local_symbol_offset'] != b['local_symbol_offset']:
            raise ValueError('historical runtime local relocation provenance differs')


def check_root(row, function, origin):
    matches = [r for r in manifest()['functions'] if r['address'] == row['address']]
    if len(matches) != 1 or matches[0]['decision'] != 'library':
        raise ValueError('runtime reconciliation is outside its accepted root cohort')
    accepted = matches[0]
    same_source(row, accepted)
    if (origin['evidence_id'] != 'R120' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != ROOT_CONFIDENCE
            or function['owner'] != 'library' or function['module'] != 'VC71CRT'
            or function['status'] != 'excluded'
            or function['proposed_name'] != accepted['coff_symbol']
            or int(function['size']) != accepted['size']
            or function['span_end'] != accepted['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('runtime reconciliation loses complete origin-only acceptance')


def check_label(row, function, origin, functions, origins):
    m = manifest()
    matches = [r for r in m['interior_labels'] if r['address'] == row['address']]
    if len(matches) != 1:
        raise ValueError('runtime reconciliation is outside its interior label cohort')
    accepted = matches[0]
    for key in ('address', 'size', 'parent', 'source_offset', 'source_symbol'):
        if row[key] != accepted[key]:
            raise ValueError('historical interior source label differs')
    parent = next(r for r in m['functions'] if r['address'] == accepted['parent'])
    check_root(parent, functions[parent['address']], origins[parent['address']])
    if (origin['evidence_id'] != 'R120' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE
            or function['owner'] != 'library' or function['module'] != 'VC71CRT'
            or function['status'] != 'excluded' or function['proposed_name']
            or int(function['size']) != accepted['size']
            or int(function['span_end'], 16) != int(row['address'], 16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('runtime interior label gains unsupported independent/source credit')
