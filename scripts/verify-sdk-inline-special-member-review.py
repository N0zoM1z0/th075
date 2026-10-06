#!/usr/bin/env python3
"""Cold-replay complete inline explicit/implicit special-member alternatives."""
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import uuid

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-inline-special-member-review-evidence.json'
MANIFEST_SHA256 = '399e138ed205302ab549415671a8ce3d00212b19ee6e84d1b2bd8ebf6259d48d'
spec = importlib.util.spec_from_file_location('inline_special_member_prior', ROOT / 'scripts/verify-sdk-string-buffer-review.py')
V = importlib.util.module_from_spec(spec)
spec.loader.exec_module(V)


def control_report(body, output, ctl, target):
    emission = V.ORDINARY(body, V.C, V.CO)
    sections, definitions, layout = [], {}, None
    for r in emission:
        raw, fields, source = V.E.section_carrier(body, r['section'], V.C, V.CO)
        sections.append(dict(source=V.COMMON.SOURCE.BASE.canonical_source(source, body),
                             fields=fields, source_sha256=V.digest(raw)))
        aux = next((a for a in source['aux_records'] if a['symbol'] == '.text'), None)
        for d in source['definitions']:
            if d['type'] == 32 and d['storage'] == 2:
                definitions[d['symbol']] = (d, raw, fields, source, aux)
            if d['symbol'] == '?InlineBufferLayout@@3QBKB':
                layout = list(struct.unpack('<3I', raw))
    comparisons = []
    for symbol, address, target_size in ctl['compare']:
        definition, raw, fields, source, aux = definitions[symbol]
        if aux is None or len(bytes.fromhex(aux['aux_hex'])) != 18:
            raise ValueError('ordinary inline member lacks its actual section AUX')
        a = int(address, 16)
        native = V.C.pe_bytes_at(target, a, target_size)
        bindings = [dict(field=f, target_address=ctl['catalog'][f['symbol']]) for f in fields]
        complete = bytes(V.linked(raw, fields, bindings, a))
        comparisons.append(dict(symbol=symbol, definition=definition, size=len(raw), source=V.COMMON.SOURCE.BASE.canonical_source(source, body),
                                fields=fields, bindings=bindings, section_aux=aux, selection=bytes.fromhex(aux['aux_hex'])[14],
                                source_sha256=V.digest(raw), target=address, target_size=target_size,
                                target_sha256=V.digest(native), linked_sha256=V.digest(complete), whole_equal=complete == native,
                                differences=sum(x != y for x, y in zip(complete, native)) if len(complete) == len(native) else None,
                                instructions=[dict(offset=i.address, mnemonic=i.mnemonic, operands=i.op_str) for i in V.F.instructions(raw, 0, len(raw))]))
    if layout != [16, 24, 24]:
        raise ValueError('complete natural inline owner layouts differ')
    return dict(emission=emission, sections=sections, layout=layout, comparisons=comparisons,
                headers=V.HEADERS(output), compiler=V.probe_compile(body))


def cold_controls(plan, target):
    reports = []
    for ctl in plan['controls']:
        if V.digest((ROOT / ctl['source']).read_bytes()) != ctl['source_sha256']:
            raise ValueError('complete natural inline declaration source differs')
        with tempfile.TemporaryDirectory(prefix='th075-inline-special-members-') as directory:
            obj = Path(directory) / 'Inline.obj'
            result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / ctl['source']), str(obj), *ctl['profile']],
                                    cwd=ROOT, capture_output=True, text=True, check=True)
            reports.append(control_report(obj.read_bytes(), result.stdout + result.stderr, ctl, target))
    return reports


def target_symbol_reference(target):
    """Read the exact external PDB reference; it does not contain private types."""
    pe = struct.unpack_from('<I', target, 60)[0]
    header = struct.unpack_from('<HHIIIHH', target, pe + 4)
    optional = pe + 24
    if target[pe:pe+4] != b'PE\0\0' or struct.unpack_from('<H', target, optional)[0] != 0x10b:
        raise ValueError('target PDB reference is not the pinned PE32 format')
    count = struct.unpack_from('<I', target, optional + 92)[0]
    if count <= 6:
        raise ValueError('target debug directory disappeared')
    rva, size = struct.unpack_from('<II', target, optional + 96 + 6*8)
    if size != 28:
        raise ValueError('whole original target debug directory differs')
    raw = V.C.pe_bytes_at(target, 0x400000 + rva, size)
    characteristics, timestamp, major, minor, typ, length, data_rva, pointer = struct.unpack('<IIHHIIII', raw)
    payload = target[pointer:pointer+length]
    if (typ != 2 or length < 25 or len(payload) != length or payload[:4] != b'RSDS'
            or payload != V.C.pe_bytes_at(target, 0x400000 + data_rva, length)
            or payload[-1:] != b'\0' or b'\0' in payload[24:-1]):
        raise ValueError('whole genuine target CodeView RSDS record differs')
    return dict(coff_symbol_table_offset=header[3], coff_symbol_count=header[4],
                debug_directory=dict(rva=rva, size=size, sha256=V.digest(raw)),
                entry=dict(characteristics=characteristics, timestamp=timestamp, major=major, minor=minor,
                           type=typ, size=length, data_rva=data_rva, file_offset=pointer),
                signature='RSDS', payload_sha256=V.digest(payload),
                guid=str(uuid.UUID(bytes_le=payload[4:20])), age=struct.unpack_from('<I', payload, 20)[0],
                original_path=payload[24:-1].decode('utf-8'), path_bytes_hex=payload[24:].hex(),
                limitation='External PDB identity only; no recovered private type/declaration or ownership/exact credit.')


def verify_scope(plan):
    if (plan['evidence_id'] != 'R266' or len(plan['cold']) != 2
            or [ctl['profile'][2] for ctl in plan['controls']] != ['/Ob0', '/Ob1']
            or plan['decision'] != 'unknown; no canonical transition or exact credit'):
        raise ValueError('bounded inline source-declaration review changes scope or assigns ownership')
    for report, size, ctor_size in zip(plan['cold'], [672, 681], [26, 30]):
        if (len(report['emission']) != 32 or sum(r['size'] for r in report['emission']) != size
                or report['layout'] != [16, 24, 24] or len(report['headers']) != 92
                or report['compiler']['frontend'] != [13, 10, 3077] or report['compiler']['backend'] != [13, 10, 3077]):
            raise ValueError('whole inline emission/includes/layout/compiler differs')
        compared = {r['symbol']: r for r in report['comparisons']}
        expected = {
            '??0InlineBuffer@@QAE@XZ': (24, 2, True),
            '??1InlineBuffer@@UAE@XZ': (16, 1, False),
            '??0ExplicitInlineStringBuffer@@QAE@XZ': (ctor_size, 2, False),
            '??1ExplicitInlineStringBuffer@@UAE@XZ': (11, 2, False),
            '??0ImplicitInlineStringBuffer@@QAE@XZ': (ctor_size, 2, False),
            '??1ImplicitInlineStringBuffer@@UAE@XZ': (5, 2, True),
        }
        if set(compared) != set(expected):
            raise ValueError('complete inline explicit/implicit alternatives are omitted')
        for symbol, facts in expected.items():
            r = compared[symbol]
            if (r['size'], r['selection'], r['whole_equal']) != facts or r['size'] != r['source']['size']:
                raise ValueError('inline source body is cropped or COMDAT/equality is substituted')
    if {r['function']['address']: r['origin']['origin'] for r in plan['protected_pairs']} != {
            '0x006200DA': 'unknown', '0x00620132': 'unknown'}:
        raise ValueError('inline explicit positives or implicit5 invent original source ownership')


def main():
    path = ROOT / EVIDENCE
    if V.digest(path.read_bytes()) != MANIFEST_SHA256:
        raise ValueError('immutable complete inline special-member evidence differs')
    plan = json.loads(path.read_text())
    verify_scope(plan)
    for p, sha in plan['retained_sha256'].items():
        if V.digest((ROOT / p).read_bytes()) != sha:
            raise ValueError('retained complete source/declaration proof differs: ' + p)
    for n, sha in plan['canonical_sha256'].items():
        if V.PRIOR.metadata_digest(V.rows(n)) != sha:
            raise ValueError('inline review alters canonical state')
    old = json.loads((ROOT / V.EVIDENCE).read_text())
    V.verify_scope(old)
    functions, origins = ({r['address']: r for r in V.rows(n)} for n in ['functions.csv', 'function-origins.csv'])
    for r in plan['protected_pairs']:
        a = r['function']['address']
        if functions.get(a) != r['function'] or origins.get(a) != r['origin']:
            raise ValueError('inline review substitutes an unresolved literal pair')
    target = V.C.verified_target()
    if V.digest(target) != plan['target_sha256'] or V.native_review(old, target) != old['native']:
        raise ValueError('whole original source contribution/provider/debug/CFG proof differs')
    if target_symbol_reference(target) != plan['target_symbol_reference']:
        raise ValueError('original external PDB identity differs')
    if cold_controls(plan, target) != plan['cold']:
        raise ValueError('whole cold inline emission/AUX/fields/alternatives differ')
    print('R266 inline review OK:two complete cold profiles,32 ordinary sections672/681,92 headers/layout16/24/24;'
          'explicit inline ctor24 and implicit dtor5 whole positives, both ANY2;explicit inline dtor11 ANY2 and derived ctor26/30 whole negatives;'
          'whole original R264 contribution/providers/CFG and prior out-of-line alternatives retained;'
          'both original special members stay unknown, no origin transition or exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
